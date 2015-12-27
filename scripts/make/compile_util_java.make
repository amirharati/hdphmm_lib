# file: $ISIP_IFC/scripts/make/compile_java.make
# version: $Id: compile_util_java.make 9656 2004-07-23 19:00:24Z gao $
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

# define the source and object files
#
ISIP_SRCS = $(wildcard $(ISIP_FILES))
ISIP_OBJS = $(subst .java,.class,$(ISIP_SRCS))

# if the DEBUG or OPTIMIZE is specified on the command line, ignore what the
# makefile tells us about debugging
#
ifeq "$(origin DEBUG)" "undefined"
ISIP_JFLAGS     := $(filter-out -g,$(ISIP_JFLAGS))
endif
ifeq "$(origin OPTIMIZE)" "undefined"
ISIP_JFLAGS     := $(filter-out -O,$(ISIP_JFLAGS))
endif

# define location of script installation
#
BIN_DIR = $(ISIP_DEVEL)/bin/scripts

# define location of jar installation
#
JAR_DIR = $(ISIP_DEVEL)/lib/java

# extrapolate dependency list from filenames
#
BIN_FILES_LOCAL := $(patsubst %.sh,%,$(wildcard $(ISIP_DRIVER_SCRIPT)))

BIN_FILES := $(foreach file,$(BIN_FILES_LOCAL),$(BIN_DIR)/$(file))

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

#------------------------------------------------------------------------------
#
# define targets and dependencies
#
#------------------------------------------------------------------------------

# make all objects
#
all: $(ISIP_OBJS) $(BIN_FILES_LOCAL)
	echo "all objects maked"

ifneq ($(strip $(REQ_PCK)),)
# define a default rule for not make this util
#
.DEFAULT:
	echo "ISIP_REQUIRE= $(ISIP_REQUIRE) $($(pck))"
	echo "$(REQ_PCK) is required for compilation"
else
# include file dependencies (define only the significant relationships)
#
$(ISIP_OBJS): $(ISIP_DEPS)

# define source file dependencies
#
%.class: %.java
	echo $(ISIP_JAVA_COMPILER) $(ISIP_JFLAGS) -classpath $(ISIP_CLASSPATH):${CLASSPATH} $<
	$(ISIP_JAVA_COMPILER) $(ISIP_JFLAGS) -classpath $(ISIP_CLASSPATH):${CLASSPATH} $<

# target the install command
#
install: all $(BIN_FILES) $(JAR_DIR) $(ISIP_RESOURCE_INSTALL) docs
	echo "> installing" $(ISIP_JARFILE_NAME) *.class
	if (test ! -z "$(JAR_DIR)/$(ISIP_JARFILE_NAME)"); then touch $(JAR_DIR)/$(ISIP_JARFILE_NAME);fi	
	jar uvf $(JAR_DIR)/$(ISIP_JARFILE_NAME) *.class

# target the clean command (the -rm lets make continue after errors)
#
clean:
	echo "> removing" *.class $(ISIP_JARFILE_NAME) $(BIN_FILES_LOCAL)
	-rm -f *.class $(ISIP_JARFILE_NAME) $(BIN_FILES_LOCAL)

# target the diagnose command
#
diagnose:
	echo "> no diagnostics may be built for java"

# target the test command
#
test: diagnose

# we also need a dummy depend target
#
depend:

# target the distclean command (the -rm lets make continue after errors)
#
distclean: $(ISIP_RESOURCE_CLEAN)
	echo "> removing" $(ISIP_JARFILE_NAME) $(ISIP_OBJS) $(BIN_FILES_LOCAL)
	-rm -f *.class $(ISIP_JARFILE_NAME) $(ISIP_OBJS) $(BIN_FILES_LOCAL)
	echo "> removing API documentation ./docs" 
	-rm -rf ./docs

# check existence
#
check: $(ISIP_SRCS)

# define rules for installing executable scripts
#
$(BIN_DIR)/%: %
	echo "compile_java.make: $< -> $@"
	cp -f $< $@
	chmod a+x $@

%: %.sh
	echo "scripts.make: $< -> $@"
	rm -f $@
	$(SED) $(SED_SUBST) $< > $@
	chmod a+x $@

# create documentation using javadoc
#
docs: $(ISIP_FILES)
	echo "> creating API documentation in ./docs"
	echo $(ISIP_JAVADOC) -classpath $(ISIP_CLASSPATH):${CLASSPATH} $(ISIP_FILES) -d ./docs
	$(ISIP_JAVADOC) -classpath $(ISIP_CLASSPATH):${CLASSPATH} $(ISIP_FILES) -d ./docs

# automatic directory creation
#
$(BIN_DIR):
	if ( test ! -d $(BIN_DIR)); then echo "> creating directory" $(BIN_DIR); mkdir -p $(BIN_DIR) 2>/dev/null; else echo "> found directory " $(BIN_DIR); fi

# automatic directory creation
#
$(JAR_DIR):
	if ( test ! -d $(JAR_DIR)); then echo "> creating directory" $(JAR_DIR); mkdir -p $(JAR_DIR) 2>/dev/null; else echo "> found directory " $(JAR_DIR); fi

# this utility can be maked
#
endif

#
# end of file
