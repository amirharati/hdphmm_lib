# file: $ISIP_IFC/scripts/make/compile.make
# version: $Id: compile_mtemplate.make 10638 2007-01-26 22:46:57Z tm334 $
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
NTSRCS := $(wildcard $(ISIP_NON_TEMPLATE_FILES))
TSRCS := $(filter-out $(NTSRCS), $(wildcard $(ISIP_FILES)))
SRCS := $(TSRCS) $(NTSRCS)

# make a dependency search path for header files. first all locally
# checked out code, next the user specified include directories,
# finally the standard isip include directory(ies)
#
HEADER_DIRS = $(subst -I, ,$(ISIP_IFLAGS) $(ISIP_INCLUDE))
HEADER_VPATH = $(CLASS_DIRS) $(HEADER_DIRS) 

# define the diagnostic program's path
#
DIAG_PROGRAM := $(ISIP_DEVEL)/util/devel/diagnose_class
DMALLOC_RUN := $(ISIP_DEVEL)/bin/scripts/isip_dmalloc_run
CHECK_CODE := $(ISIP_DEVEL)/bin/scripts/isip_check_code
MTEMPLATE_PARSER = $(ISIP_DEVEL)/lib/scripts/make/compile_mtemplate_sed.sh

# initialize all the library variables to null
#
ISIP_OLIB_BASE :=
HOME_OLIB_BASE :=
OLIB_BASE :=
OLIB_DIR := 
OLIB := 

# if an ISIP_OLIB is specified, set the variables
#
ifneq "$(ISIP_OLIB)" ""
	ISIP_OLIB_BASE := $(ISIP_DEVEL)/lib
	OLIB_BASE := $(ISIP_OLIB_BASE)
	OLIB_DIR = $(OLIB_BASE)/$(ISIP_BINARY)
	OLIB = $(OLIB_DIR)/$(ISIP_OLIB)
	INSTALL_DIRECTIVE := install-actual
else
	INSTALL_DIRECTIVE := install-skip
endif

# if TEMPLATE_TARGETS are specified, expand out the object files
#
ifneq "$(ISIP_TEMPLATE_TARGETS)" ""
	NTOBJS := $(subst .cc,.o,$(NTSRCS))
	TOBJS := $(foreach tsrc,$(subst .cc,,$(TSRCS)),$(foreach targ,$(ISIP_TEMPLATE_TARGETS), $(tsrc).$(targ).o)) 
	OBJS := $(TOBJS) $(NTOBJS)
else
	OBJS := You_must_define_ISIP_TEMPLATE_TARGETS
endif

CLASS_DIRS := ""
LOC_OLIB := 
HDR_FILES := 
HDR_INST := 

OLIB_LOCKFILE = $(OLIB).lock

HDR_FILES = $(ISIP_HEADER_FILES)
HDR_INST = $(foreach hdr,$(HDR_FILES),$(ISIP_DEVEL)/include/$(notdir $(hdr)))

vpath %.h $(HEADER_VPATH)

# define flags for the C++ and C compilers
#
I_FLAGS =  $(ISIP_IFLAGS) $(CLASS_I_FLAGS) $(ISIP_INCLUDE)
CPLUS_FLAGS  = -Wall -fno-strict-aliasing -ftemplate-depth-50 $(ISIP_CFLAGS) $(filter-out -dmalloc,$(DEBUG)) -c
C_FLAGS      = 

# define variables used by the diagnose directive
#
DIAG_CLASS := $(basename $(firstword $(ISIP_HEADER_FILES)))
CURRENT_DIR:=$(shell pwd)
DIAG_SUBST := $(shell echo "'s/CLASS_NAME/$(DIAG_CLASS)/g'")

# diagnostic test program should be deleted with a make clean
#
EXEC := $(filter $(DIAG_CLASS).exe, $(wildcard *.exe))

# modify the c_flags from the command line arguments.  notice that
# 'make DEBUG=' will nullify a specified debug flag in the user
# makefile. note that we need to compare the origin of the variable
# with the string undefined instead of just a ifdef DEBUG because
# ifdef DEBUG does not consider a null setting (which is useful to
# disable all debuging/optimization).
#

# if the DEBUG is specified on the command line, ignore what the
# makefile tells us about debugging
#
ifneq "$(origin DEBUG)" "undefined"
	ISIP_CFLAGS	:= $(filter-out -g,$(ISIP_CFLAGS))
	ISIP_CFLAGS	:= $(filter-out -ggdb3,$(ISIP_CFLAGS))
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
ifneq "$(filter -ggdb3,$(ISIP_CFLAGS))" ""
	ISIP_CFLAGS	:= $(filter-out -ggdb3,$(ISIP_CFLAGS))
	DEBUG += -ggdb3
endif
ifneq "$(filter -dmalloc,$(ISIP_CFLAGS))" ""
	ISIP_CFLAGS 	:= $(filter-out -dmalloc,$(ISIP_CFLAGS))
	DEBUG += -dmalloc
endif

# if the optimize is set on the command line, override
#
ifneq "$(origin OPTIMIZE)" "undefined"
	CPLUS_FLAGS	:= $(filter-out -O%,$(CPLUS_FLAGS))
else
	OPTIMIZE = -O2
endif
CPLUS_FLAGS += $(OPTIMIZE)

GDBINIT := 

# some classes cannot have a diagnostic run (like templates), allow
# for them to specify a NO_DIAGNOSE flag
#
ifeq "$(ISIP_DIAGNOSE_MODE)" "none"
	DIAGNOSE_DIRECTIVE = diagnose-skip
	TEST_DIRECTIVE = test-skip	
else
	GDBINIT := install-gdbinit
	DIAGNOSE_DIRECTIVE = diagnose-actual

	ifeq "$(filter -dmalloc,$(DEBUG))" ""
	     TEST_DIRECTIVE = test-actual
	else
	     TEST_DIRECTIVE = test-actual-dmalloc
	endif

	# for template diagnose, redefine gdbinit
	#
	ifeq "$(ISIP_DIAGNOSE_MODE)" "template-diagnose"
		GDBINIT := install-gdbinit-template
	endif
endif

# possibly dump a gdbinit file
#
ifneq "$(filter -dmalloc,$(DEBUG))" ""
#	I_FLAGS += -I/usr/local/include
	CPLUS_FLAGS += -DISIP_DMALLOC
	ifneq "$(filter -g,$(DEBUG))" ""
		GET_GDBINIT := $(GDBINIT)
	endif
endif

# define dependencies: note that we include, by default, a makefile
#  located in the current directory, so that changes to the makefile
#  will trigger a make.
#
ALL_DEPS = $(ISIP_DEVEL)/class/GNUmakefile ./GNUmakefile $(ISIP_DEPS) \
	$(ISIP_HEADER_FILES) $(wildcard *.h)

# define suffixes (none)
#
.SUFFIXES:

# make sure we clean up
#  note: this code is executed ALL the time
#
.DONE:

# make everything silent
#
.SILENT:

.PHONY: all clean test_make check diagnose diagnose-skip diagnose-actual 
.PHONY: diagnose-skip test test-actual test-skip install-skip install-actual
.PHONY: install-gdbinit
#------------------------------------------------------------------------------
#
# define targets and dependencies
#
#------------------------------------------------------------------------------

# make all objects
#
all: $(OBJS)

# include file dependencies (define only the significant relationships)
#
$(OBJS): $(ALL_DEPS)

# define source file dependencies
#

# this is the basic rule used, one source file to one object file
#
$(NTOBJS): %.o : %.cc
	echo $(ISIP_CPLUS_COMPILER) $(I_FLAGS) $(CPLUS_FLAGS) $(C_FLAGS) $<
	$(ISIP_CPLUS_COMPILER) $(I_FLAGS) $(CPLUS_FLAGS) $(C_FLAGS) $<

# this more complicated rule allows for splitting each template source
# file into seperate object files for each template. note that within
# each source file these macros are define:
#   ISIP_TEMPLATE_TARGET: the full target (like Float,float)
#   ISIP_TEMPLATE_T0:     the first template argument (like Float)
#   ISIP_TEMPLATE_T1:     the second template argument (like float)
#   ISIP_TEMPLATE_T2:     the third template argument
#   ISIP_TEMPLATE_<mod>	  any modifiers after an '=' character.
#
$(TOBJS): %.o: 
	echo $(ISIP_CPLUS_COMPILER) $(I_FLAGS) $(CPLUS_FLAGS) $(C_FLAGS) -o $*.o `echo $* | $(MTEMPLATE_PARSER) source_name` -DISIP_TEMPLATE_TARGET="`echo $* | $(MTEMPLATE_PARSER) template_args`" -DISIP_TEMPLATE_T0="`echo $* | $(MTEMPLATE_PARSER) t0`" -DISIP_TEMPLATE_T1="`echo $* | $(MTEMPLATE_PARSER) t1`" -DISIP_TEMPLATE_T2="`echo $* | $(MTEMPLATE_PARSER) t2`" `echo $* | $(MTEMPLATE_PARSER) modifier`

	$(ISIP_CPLUS_COMPILER) $(I_FLAGS) $(CPLUS_FLAGS) $(C_FLAGS) -o $*.o `echo $* | $(MTEMPLATE_PARSER) source_name` -DISIP_TEMPLATE_TARGET="`echo $* | $(MTEMPLATE_PARSER) template_args`" -DISIP_TEMPLATE_T0="`echo $* | $(MTEMPLATE_PARSER) t0`" -DISIP_TEMPLATE_T1="`echo $* | $(MTEMPLATE_PARSER) t1`" -DISIP_TEMPLATE_T2="`echo $* | $(MTEMPLATE_PARSER) t2`" `echo $* | $(MTEMPLATE_PARSER) modifier`

# include the dependency rules for these template source files. this has to be 
# generated automatically. note that the rule below the include statement
# is what generates the rule file. it is deleted in make clean.
#
-include .GNUmakefile_tobjs_rules

.GNUmakefile_tobjs_rules: GNUmakefile
	rm -f $@
	for f in $(TOBJS:.o=); do echo "$$f.o: `echo $$f | $(MTEMPLATE_PARSER) source_name`" >> $@; done

# install into a library
#
install: $(INSTALL_DIRECTIVE)

install-actual: $(ISIP_DEVEL)/include $(HDR_INST) $(OBJS) $(OLIB_DIR) $(LOC_OLIB) 
	while (test -r $(OLIB_LOCKFILE)); do echo "> waiting for lock on" $(OLIB); sleep 1; done
	echo "> installing in" $(OLIB)
	touch $(OLIB_LOCKFILE)
	-ar crus $(OLIB) $(OBJS)
	rm $(OLIB_LOCKFILE)

install-skip: $(ISIP_DEVEL)/include $(HDR_INST) 
	echo "> skipping install"

# make the library directory if necessary
#
$(OLIB_DIR) : 
	echo "> creating directory" $(OLIB_DIR)
	-mkdir -p $(OLIB_DIR) 2>/dev/null

# make a link from the class to the $isip/include directory, if necessary
#
$(HDR_INST): $(HDR_FILES)
	echo "> checking header dependencies"
	$(MAKE) -f $(ISIP_DEVEL)/lib/scripts/make/compile_depend.make ISIP_HEADER_FILES="$(ISIP_HEADER_FILES)"

# create the $(ISIP_DEVEL)/include directory if necessary
#
$(ISIP_DEVEL)/include:
	-mkdir $(ISIP_DEVEL)/include 2>/dev/null

# depend directive: this directive is called by recursive make before
# any other, so header files will be in place before any code is
# compiled.
#
depend: $(ISIP_DEVEL)/include $(HDR_INST) $(OLIB_DIR)

# clean up (the -rm lets make continue after errors)
#
clean:
	echo "> removing objects" $(wildcard *.o) $(EXEC)
	-rm -f $(wildcard *.o) $(EXEC)
	-rm -f .GNUmakefile_tobjs_rules

# distclean will also delete the library
#
distclean: clean
	if (test -r $(OLIB)); then echo "> removing library" $(OLIB); rm -f $(OLIB) 2>/dev/null; fi
	-rm -f $(OLIB_LOCKFILE)
	
test_make:
	echo "In compile.make"
	echo "debug = " $(DEBUG)
	echo "c_flags = " $(CPLUS_FLAGS)
	echo "hdr_files = " $(HDR_FILES)
	echo "hdr_inst = " $(HDR_INST)
	echo "ISIP_TEMPLATE_TARGETS = " $(ISIP_TEMPLATE_TARGETS)
	echo "TOBJS = " $(TOBJS)
	echo "OBJS = " $(OBJS)

# check existence
#
check: $(SRCS)

# check format
#
format: $(SRCS)
	$(CHECK_CODE) -methods $(SRCS) $(FMT_OPTS)

# create a diagnostic program in the current directory (without
# re-compiling library)
#
diagnose: install $(DIAGNOSE_DIRECTIVE)

diagnose-actual: install $(GET_GDBINIT)
	
	echo "creating diagnostic program for" $(DIAG_CLASS) \
	     "in directory" $(CURRENT_DIR)
	
	$(MAKE) -k GNUmakefile CLASS_NAME=$(DIAG_CLASS) \
		ISIP_BIN=$(CURRENT_DIR) ISIP_INSTALL_EXT=.exe \
		ISIP_DIAGNOSE_MODE="$(ISIP_DIAGNOSE_MODE)" \
		USE_ISIP_WORK=$(USE_ISIP_WORK) DEBUG="$(DEBUG)" \
		OPTIMIZE=$(OPTIMIZE) -w \
		ISIP_LFLAGS_BEFORE="$(ISIP_DIAG_LIBS)" \
		--directory $(DIAG_PROGRAM) install 

	$(MAKE) -k GNUmakefile CLASS_NAME=$(DIAG_CLASS) \
		USE_ISIP_WORK=$(USE_ISIP_WORK) \
		--directory $(DIAG_PROGRAM) clean
	
install-gdbinit: $(DIAG_PROGRAM)/gdbinit_example.text
	echo "creating a gdbinit"
	sed -e $(DIAG_SUBST) < $(DIAG_PROGRAM)/gdbinit_example.text > $(CURRENT_DIR)/.gdbinit

install-gdbinit-template: $(DIAG_PROGRAM)/gdbinit_example_template.text
	echo "creating a template gdbinit"
	sed -e $(DIAG_SUBST) < $(DIAG_PROGRAM)/gdbinit_example_template.text > $(CURRENT_DIR)/.gdbinit

diagnose-skip: install
	echo "no diagnostic can be built for" $(DIAG_CLASS)", skipping"

test: install $(TEST_DIRECTIVE)

test-actual: install diagnose-actual

	echo "running diagnostic program for" $(DIAG_CLASS) \
	     "in directory" $(CURRENT_DIR)
	
	./$(DIAG_CLASS).exe $(DIAG_OPTS)

test-actual-dmalloc: install diagnose-actual

	echo "running diagnostic program (including memory) for" $(DIAG_CLASS)\
		"in directory" $(CURRENT_DIR)

	$(DMALLOC_RUN) ./$(DIAG_CLASS).exe -static $(DIAG_OPTS)
	
test-skip: install
	echo "no test can be run for" $(DIAG_CLASS)", skipping"
#
# end of file
