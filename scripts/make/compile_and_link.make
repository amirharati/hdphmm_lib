# file: $ISIP_IFC/scripts/make/compile_and_link.make
# version: $Id: compile_and_link.make 10638 2007-01-26 22:46:57Z tm334 $
#

# this makefile contains a standard set of dependencies and targets
# that are used by all makefiles in the environment.
#

#------------------------------------------------------------------------------
#
# define variables section
#
#------------------------------------------------------------------------------

# create filenames
#
SRCS := $(wildcard $(ISIP_FILES))
OBJS := $(subst .cc,.o,$(SRCS))
BEXE = $(subst .exe,$(ISIP_INSTALL_EXT),$(ISIP_EXE))

# make a dependency search path for header files. first all locally
# checked out code, next the user specified include directories,
# finally the standard isip include directory(ies)
#
HEADER_DIRS := $(subst -I, ,$(ISIP_IFLAGS) $(ISIP_INCLUDE) $(EXTRA_INCLUDE))
HEADER_VPATH = $(CLASS_DIRS) $(HEADER_DIRS)

# diagnose_class has concurrency problems, transform it into
# something other than diagnose_class.o
#
DIAG_OBJ := $(subst .exe,_diag.o,$(ISIP_EXE))
ifeq "$(filter diagnose_class.o,$(OBJS))" "diagnose_class.o"
	OBJS := $(filter-out diagnose_class.o,$(OBJS))

	OBJS := $(DIAG_OBJ) $(OBJS)
endif

# make a dependency search path for the libraries: first the local
# library directory and then the isip libraries
#
LIB_DIRS := $(subst -L, ,$(filter -L%,$(ISIP_LFLAGS_BEFORE) \
	$(CLASS_LFLAGS) $(ISIP_LIBS) $(ISIP_LFLAGS_AFTER)))
LIBS := $(filter -l%,$(ISIP_LFLAGS_BEFORE) $(ISIP_LIBS) $(ISIP_LFLAGS_AFTER))

# note that everything except for -lm is an ISIP generated library,
# not a system library.
#
ILIBS := $(filter -l%,$(filter-out -lm,$(ISIP_LIBS)))

# change -l options to to library names
#
LIBFILES = $(foreach lib, $(subst -l,lib,$(ILIBS)), $(lib).a)

# define where we install libraries
#
INST_LIB_DIR := $(subst -L, ,$(firstword $(filter -L%,$(ISIP_LIBS))))

# vpath directives influence the search order for dependencies in
# other directories.
#
vpath %.h $(HEADER_VPATH)
vpath %.a $(LIB_DIRS)

# define flags for the C++ and C compilers
#
I_FLAGS      = -fopenmp $(ISIP_IFLAGS) $(CLASS_I_FLAGS) $(ISIP_INCLUDE) $(EXTRA_INCLUDE)
CPLUS_FLAGS  = -Wall -fno-strict-aliasing -ftemplate-depth-50 $(ISIP_DEFINES) $(ISIP_CFLAGS) $(filter-out -dmalloc,$(DEBUG)) -c
C_FLAGS      = 
LD_FLAGS     = $(ISIP_CFLAGS)

# modify the c_flags from the command line arguments.  notice that
# 'make DEBUG=' will nullify a specified debug flag in the user
# makefile
#

# if the DEBUG is specified on the command line, ignore what the
# makefile tells us about debugging
#
ifneq "$(origin DEBUG)" "undefined"
	ISIP_CFLAGS	:= $(filter-out -g,$(ISIP_CFLAGS))
	ISIP_CFLAGS 	:= $(filter-out -dmalloc,$(ISIP_CFLAGS))
endif

# move the debug flags from the makefile's definition of CFLAGS to our
# local variable DEBUG, which is later parsed back into
# CPLUS_FLAGS. this unifies variables set in makefiles and command line
# options.  
#
ifneq "$(filter -g,$(ISIP_CFLAGS))" ""
	ISIP_CFLAGS	:= $(filter-out -g,$(ISIP_CFLAGS))
	DEBUG += -g
endif
ifneq "$(filter -dmalloc,$(ISIP_CFLAGS))" ""
	ISIP_CFLAGS 	:= $(filter-out -dmalloc,$(ISIP_CFLAGS))
	DEBUG += -dmalloc
endif

# if the optimize is set on the command line, override
#
ifneq "$(origin OPTIMIZE)" "undefined"
	ISIP_CFLAGS	:= $(filter-out -O%,$(ISIP_CFLAGS))
	ISIP_CFLAGS 	+= $(OPTIMIZE)
else
	ISIP_CFLAGS 	+= -O2
endif

ifneq "$(filter -dmalloc,$(DEBUG))" ""
#	I_FLAGS += -I/usr/local/include
	CPLUS_FLAGS += -DISIP_DMALLOC
	LIB_DIRS += /usr/local/lib
	LIBS += -ldmalloc
endif
# amir
LIBS += -lgomp
# define dependencies: note that we include, by default, a makefile
#  located in the current directory so that changes to the makefile
#  will trigger a make. note also the dependency on isip libraries and
#  local copies of libraries
#
ALL_DEPS = $(ISIP_DEVEL)/util/GNUmakefile $(ISIP_DEVEL)/class/GNUmakefile \
           $(wildcard $(LIB_DIRS)/*.a) $(ISIP_DEPS)

# define libraries
#
ALL_LIBS = $(foreach dir, $(LIB_DIRS), -L$(dir)) $(LIBS) $(EXTRA_LIBS)

# define suffixes
#
.SUFFIXES: .cc

# make sure we clean up
#  note: this code is executed ALL the time
#
.DONE:

# make everything silent
#
.SILENT:

#------------------------------------------------------------------------------
#
# define targets and dependencies
#
#------------------------------------------------------------------------------

# define executable dependencies
#
$(ISIP_EXE): $(OBJS) $(LIBFILES)
	echo "> linking" $(ISIP_EXE)
	echo $(ISIP_CPLUS_COMPILER) $(LD_FLAGS) "-o" $(ISIP_EXE) \
		$(OBJS) $(ALL_LIBS)
	$(ISIP_CPLUS_COMPILER) $(LD_FLAGS) -o $(ISIP_EXE) $(OBJS) $(ALL_LIBS)

# include file dependencies (define only the significant relationships)
#
$(OBJS): $(ALL_DEPS)

# diagnose object
#

# define source file dependencies
#
.cc.o:
	echo $(ISIP_CPLUS_COMPILER) $(I_FLAGS) $(CPLUS_FLAGS) $(C_FLAGS) $<
	$(ISIP_CPLUS_COMPILER) $(I_FLAGS) $(CPLUS_FLAGS) $(C_FLAGS) $<

$(DIAG_OBJ): $(ALL_DEPS)
	echo $(ISIP_CPLUS_COMPILER) "-o" $(DIAG_OBJ) $(I_FLAGS) $(CPLUS_FLAGS) $(C_FLAGS) "diagnose_class.cc"
	$(ISIP_CPLUS_COMPILER) -o $(DIAG_OBJ) $(I_FLAGS) $(CPLUS_FLAGS) $(C_FLAGS) diagnose_class.cc

# define a mechanism to create missing libraries
#
$(LIBFILES): %.a:
	echo "> building placeholder library $*.a:"
	echo "void placeholder_$*() {} " | gcc -x c++ -p -c -o $(INST_LIB_DIR)/ph_$*.o -
	ar -r $(INST_LIB_DIR)/$*.a $(INST_LIB_DIR)/ph_$*.o
	rm -f $(INST_LIB_DIR)/ph_$*.o

# define a link-only target
#
link: $(OBJS)
	echo "> linking $(ISIP_EXE)"
	$(ISIP_CPLUS_COMPILER) $(LD_FLAGS) -o $(ISIP_EXE) $(OBJS) $(ALL_LIBS)

# install
#
install: $(ISIP_EXE) $(LOCAL_INSTALL_ERROR) $(ISIP_BIN) $(ISIP_RESOURCE_INSTALL)
	echo "> installing binary" $(ISIP_BIN)/$(BEXE)
	cp $(ISIP_EXE) $(ISIP_BIN)/$(BEXE)

$(ISIP_BIN):
	echo "> creating directory" $(ISIP_BIN)
	-mkdir $(ISIP_BIN) 2>/dev/null

# depend directive: this directive is called by recursive make before
# any other, so header files will be in place before any code is
# compiled. for this makefile only create directories
#
depend: $(ISIP_BIN)

# clean up (the -rm lets make continue after errors)
#
clean:
	echo "> removing objects and binary" $(wildcard *.o) $(ISIP_EXE)
	-rm -f $(wildcard *.o) $(ISIP_EXE) 

# distclean should do nothing more than clean
#
distclean: clean $(ISIP_RESOURCE_CLEAN)

# diagnostics (meaningless for utilities right now)
#
diagnose:
	echo "no diagnostic can be built for utility, skipping"
test:
	echo "no diagnostic can be run for utility, skipping"

# check existence
#
check: $(SRCS)

#
# end of file
