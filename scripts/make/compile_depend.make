# file: $ISIP_IFC/scripts/make/compile_depend.make
# version: $Id: compile_depend.make 9612 2004-07-03 18:12:07Z picone $
#

# this makefile contains a standard set of dependencies and targets
# that are used by all makefiles in the environment.
#

#------------------------------------------------------------------------------
#
# define variables section
#
#------------------------------------------------------------------------------

# include configure variables
#
ifeq "$(MAKING_MAKE)" ""
	include $(ISIP_DEVEL)/lib/scripts/make/compile_configure.make
else
	include ./compile_configure.make
endif

# define command for installing header file
#
INSTALL_CMD = $(LINK_CMD)
UNINSTALL_CMD = $(UNLINK_CMD)

# define header files
#
HDR_FILES = $(ISIP_HEADER_FILES)
HDR_INST = $(foreach hdr,$(HDR_FILES),$(ISIP_DEVEL)/include/$(notdir $(hdr)))

HDR_REMOVE = $(foreach hdr,$(HDR_FILES),dc_$(notdir $(hdr)))

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

.PHONY: all clean test_make check
#------------------------------------------------------------------------------
#
# define targets and dependencies
#
#------------------------------------------------------------------------------

# define all and install to just to depend
#
all: depend
install: all

# make copy from the class to the $isip/include directory, if necessary
#
$(HDR_INST): $(ISIP_DEVEL)/include/%.h: %.h 
	echo "> linking" `pwd`/$< "to" $@
	-$(UNINSTALL_CMD) $@ 2>/dev/null
	$(INSTALL_CMD) `pwd`/$< $@

$(HDR_REMOVE): dc_%.h:
	if (test -r "$(ISIP_DEVEL)/include/$*.h"); then echo "compile_depend.make: unlinking $(ISIP_DEVEL)/include/$*.h"; $(UNINSTALL_CMD) $(ISIP_DEVEL)/include/$*.h; fi

# create the $(ISIP_DEVEL)/include directory if necessary
#
$(ISIP_DEVEL)/include: 
	-mkdir $(ISIP_DEVEL)/include 2>/dev/null

# depend directive: this directive is called by recursive make before
# any other, so header files will be in place before any code is
# compiled.
#
depend: $(ISIP_DEVEL)/include $(HDR_INST)

# clean does nothing for make depend
#
clean:
distclean: $(HDR_REMOVE)

test_make:
	echo "In compile_depend.make"
	echo "hdr_files = " $(HDR_FILES)
	echo "hdr_inst = " $(HDR_INST)

# check existence
#
check: $(HDR_FILES)

#
# end of file

