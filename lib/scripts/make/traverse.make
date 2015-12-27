# file: $ISIP_IFC/scripts/make/traverse.make
# version: $Id: traverse.make 9612 2004-07-03 18:12:07Z picone $
#

# this makefile contains a standard set of dependencies and targets
# that are used by all makefiles in the environment.
#

# include the output of configure
#
include $(ISIP_DEVEL)/lib/scripts/make/compile_configure.make

#------------------------------------------------------------------------------
#
# define variables section
#
#------------------------------------------------------------------------------

# create filenames
#
EXCLUDE_DIRS := $(dir $(ISIP_EXCLUDE))
SRC_DIRS := $(dir $(wildcard */GNUmakefile))

# if the ISIP_ORDER variable is set, use the specified order
#
ifneq "$(ISIP_ORDER)" ""
	SRC_DIRS := $(ISIP_ORDER) $(filter-out $(ISIP_ORDER), $(SRC_DIRS))
else
	SRC_DIRS := $(SRC_DIRS)
endif

SRC_DIRS:= $(filter-out $(EXCLUDE_DIRS), $(SRC_DIRS))

# append a string for dummy rule names. note we can't use .PHONY here
# because make needs to think that it is doing something.
#
B1TARGETS := $(foreach dir,$(SRC_DIRS),b1target_$(dir))
B2TARGETS := $(foreach dir,$(SRC_DIRS),b2target_$(dir))
CTARGETS := $(foreach dir,$(SRC_DIRS),ctarget_$(dir))
DCTARGETS := $(foreach dir,$(SRC_DIRS),dctarget_$(dir))
FTARGETS := $(foreach dir,$(SRC_DIRS),ftarget_$(dir))
DTARGETS := $(foreach dir,$(SRC_DIRS),dtarget_$(dir))
G1TARGETS := $(foreach dir,$(SRC_DIRS),g1target_$(dir))
G2TARGETS := $(foreach dir,$(SRC_DIRS),g2target_$(dir))

# modify the c_flags from the command line arguments.  notice that
# 'make DEBUG=' will nullify a specified debug flag in the user
# makefile
#
ifneq "$(origin DEBUG)" "undefined"
	export DEBUG
endif

ifneq "$(origin OPTIMIZE)" "undefined"
	export OPTIMIZE
else
	OPTIMIZE += -O2
	export OPTIMIZE
endif

# define dependencies: note that we include, by default, a makefile
#  located in the current directory, so that changes to the makefile
#  will trigger a make.
#
ALL_DEPS = ./GNUmakefile $(ISIP_DEPS)

#------------------------------------------------------------------------------
#
# check required packages for make
#
#------------------------------------------------------------------------------

# if the ISIP_REQUIRE variable is set, set the correct variable
# if any of the package required is not there, REQ_PCK will be
# set to the name of that package
#
#ifneq "$(ISIP_REQUIRE)" ""

ifneq ($(strip $(ISIP_REQUIRE)),)
	REQ_PCK := $(foreach pck,$(ISIP_REQUIRE),$(if $($(pck)),,$(pck)))
else
	REQ_PCK :=
endif

# make sure we clean up
#  note: this code is executed ALL the time
#
.DONE:

# make everything silent
#
.SILENT:

.PHONY: all clean
#------------------------------------------------------------------------------
#
# define targets and dependencies
#
#------------------------------------------------------------------------------

ifneq ($(strip $(REQ_PCK)),)
# define a default rule for not make this util
#
all:
	echo "ISIP_REQUIRE= $(ISIP_REQUIRE) $($(pck))"
	echo "$(REQ_PCK) is required for compilation"

.DEFAULT:
	echo "ISIP_REQUIRE= $(ISIP_REQUIRE) $($(pck))"
	echo "$(REQ_PCK) is required for compilation"
else
# make all directories
#
all: $(ALL_DEPS) depend $(B1TARGETS)
	echo "compiled all of" $(SRC_DIRS)

# this loops through all directories
#
b1target_% : %
	$(MAKE) --directory $* -w 

# install target: just here for convenience
#
install: $(ALL_DEPS) depend $(B2TARGETS) $(ISIP_POST_INSTALL)

# this loops through all directories
#
b2target_% : %
	$(MAKE) --directory $* -w install

	
# clean up
#
clean: $(CTARGETS)
	echo "cleaned all of" $(SRC_DIRS)

# this loops through all directories
#
ctarget_% : %
	$(MAKE) --directory $* -w clean

# distribution cleanup
#
distclean: $(DCTARGETS) distclean-local 
	echo "distcleaned all of" $(SRC_DIRS)

# this loops through all directories
#
dctarget_% : %
	$(MAKE) --directory $* -w distclean 

# format check
#
format: $(FTARGETS)
	echo "format checked all of" $(SRC_DIRS)

# this loops through all directories
#
ftarget_% : %
	$(MAKE) --directory $* -w format

# build dependencies
#
depend: $(DTARGETS)
	echo "made dependencies for all of" $(SRC_DIRS)

# this loops through all directories
#
dtarget_% : %
	$(MAKE) --directory $* -w depend

distclean-local:
	echo "> traverse.make: removing" $(ISIP_DISTCLEAN)
	rm -fr $(ISIP_DISTCLEAN)

# build dependencies
#
diagnose: install $(G1TARGETS) 
	echo "built diagnostics for all of" $(SRC_DIRS)

# this loops through all directories
#
g1target_% : %
	$(MAKE) --directory $* -w diagnose

# build dependencies
#
test: install $(G2TARGETS) 
	echo "ran diagnostics for all of" $(SRC_DIRS)

# this loops through all directories
#
g2target_% : %
	$(MAKE) --directory $* -w test

test_make: 
	echo "dirs =" $(SRC_DIRS)
	echo "exclude =" $(EXCLUDE_DIRS)
	echo "debug =" $(DEBUG)
	echo "optimize =" $(OPTIMIZE)

# this utility can be maked
#
endif

#
# end of file
