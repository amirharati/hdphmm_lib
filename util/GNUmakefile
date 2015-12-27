# file: $isip/util/GNUmakefile
# version: $Id: GNUmakefile 9603 2004-06-30 15:35:03Z gao $
#

# this make file builds the util hierarchy recursively
# 
ISIP_EXCLUDE = demo/

# in order to build utilities we must have the libraries build. hence
# we add a dependency to the lowest-level library -- lib_system.a, and
# include a rule at the bottom of this file to build and install all
# classes if this library is not found.
#
ISIP_DEPS:=$(ISIP_DEVEL)/lib/$(ISIP_BINARY)/lib_system.a

# include the isip standard make template
#
include $(ISIP_DEVEL)/lib/scripts/make/traverse.make

# define an extra directive to build the libraries
#
$(ISIP_DEVEL)/lib/$(ISIP_BINARY)/lib_system.a: 
	echo "need to build the classes"
	$(MAKE) --directory $(ISIP_DEVEL)/class depend install

#
# end of file
