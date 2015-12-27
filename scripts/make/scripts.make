# file: $ISIP_IFC/scripts/make/scripts.make
# version: $Id: scripts.make 9612 2004-07-03 18:12:07Z picone $
#

# this makefile contains a standard set of dependencies and targets
# that are used by all makefiles in the environment.
#

#------------------------------------------------------------------------------
#
# define variables section
#
#------------------------------------------------------------------------------

# define location of library
#
ifneq "$(ISIP_LIB)" ""
	LIB_DIR = $(ISIP_DEVEL)/lib/scripts/$(ISIP_LIB)
endif

# include the configuration output
#
ifeq "$(MAKING_MAKE)" ""
	include $(ISIP_DEVEL)/lib/scripts/make/compile_configure.make
else
	include ./compile_configure.make
endif

# define location of binary
#
BIN_DIR = $(ISIP_DEVEL)/bin/scripts

# extrapolate dependency list from filenames
#
BIN_FILES_LOCAL := $(patsubst %$(BIN_EXT),%,$(wildcard $(ISIP_BIN_FILES)))
BIN_FILES_LOCAL := $(patsubst %.pl,%,$(BIN_FILES_LOCAL))
BIN_FILES_LOCAL := $(patsubst %.tcl,%,$(BIN_FILES_LOCAL))
BIN_FILES_LOCAL := $(patsubst %.make,%,$(BIN_FILES_LOCAL))
BIN_FILES := $(foreach file,$(BIN_FILES_LOCAL),$(BIN_DIR)/$(file))
LIB_FILES := $(foreach file,$(wildcard $(ISIP_LIB_FILES)),$(LIB_DIR)/$(file))

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

.PHONY: all clean install
#------------------------------------------------------------------------------
#
# define targets and dependencies
#
#------------------------------------------------------------------------------
# make all does nothing
#
all: $(BIN_FILES_LOCAL)
	echo "nothing maked"

ifneq ($(strip $(REQ_PCK)),)
# define a default rule for not make this util
#
.DEFAULT:
	echo "ISIP_REQUIRE= $(ISIP_REQUIRE) $($(pck))"
	echo "$(REQ_PCK) is required for compilation"
else
# install target: actually install things
#
install: $(ALL_DEPS) depend $(LIB_FILES) $(BIN_FILES)

# define rules for library installation. currently we only support
# perl, make, and sh libraries. no configure translation will be done
# for libraries, just executables.
#
$(LIB_DIR)/%.pm: %.pm 
	echo "scripts.make: $< -> $@"
	$(SED) $(SED_SUBST) $< > $@

$(LIB_DIR)/%.make: %.make
	echo "scripts.make: $< -> $@"
	$(SED) $(SED_SUBST) $< > $@

$(LIB_DIR)/%.sh: %.sh
	echo "scripts.make: $< -> $@"
	$(SED) $(SED_SUBST) $< > $@
	chmod a+x $@

# define rules for installing executable scripts
#
$(BIN_DIR)/%: %
	echo "scripts.make: $< -> $@"
	cp -f $< $@
	chmod a+x $@

# define rules for transforming source files into executable
# files. currently we only support perl, tcl, and sh scripts.
#
%: %.pl
	echo "scripts.make: $< -> $@"
	rm -f $@
	$(SED) $(SED_SUBST) $< > $@
	chmod a+x $@

%: %.tcl
	echo "scripts.make: $< -> $@"
	rm -f $@
	$(SED) $(SED_SUBST) $< > $@
	chmod a+x $@

%: %.sh
	echo "scripts.make: $< -> $@"
	rm -f $@
	$(SED) $(SED_SUBST) $< > $@
	chmod a+x $@

# automatic directory creation
#
$(BIN_DIR):
	if ( test ! -d $(BIN_DIR)); then echo "> creating directory" $(BIN_DIR); mkdir -p $(BIN_DIR) 2>/dev/null; else echo "> found directory " $(BIN_DIR); fi

$(LIB_DIR):
	if ( test ! -d $(LIB_DIR)); then echo "> creating directory" $(LIB_DIR); mkdir -p $(LIB_DIR) 2>/dev/null; else echo "> found directory " $(LIB_DIR); fi

# depend directive: this directive is called by recursive make before
# any other, so header files will be in place before any code is
# compiled. for this makefile only create needed directories
#
depend: $(LIB_DIR) $(BIN_DIR)

# clean up (remove executable scripts)
#
clean:
	-rm $(BIN_FILES_LOCAL) 2>/dev/null

# distclean
#
distclean: clean

test:
	echo "no test can be run for script, skipping"

debug_make:
	echo "> ISIP_BIN = $(ISIP_BIN)"
	echo "> ISIP_LIB = $(ISIP_LIB)" 
	echo "> LIB_FILES = $(LIB_FILES)"
	echo "> BIN_FILES = $(BIN_FILES)"
	echo "> BINE_FILES = $(BINE_FILES)"
	echo "> BASE_LIB = $(BASE_LIB)"
	echo "> BASE_LIB_MAIN = $(BASE_LIB_MAIN)"
	echo "> BIN_DIR = $(BIN_DIR)"
	echo "> BASE_BIN_MAIN = $(BASE_BIN_MAIN)"
	echo "> LIB_DIR = $(LIB_DIR)"
	echo "> ISIP_LIB_FILES = $(ISIP_LIB_FILES)"
	echo "> ISIP_BIN_FILES = $(ISIP_BIN_FILES)"
	echo "> SED_SUBST = " $(SED_SUBST)

# diagnostics (meaningless for utilities right now)
#
diagnose:
run-diagnose:

# this utility can be maked
#
endif

#
# end of file
