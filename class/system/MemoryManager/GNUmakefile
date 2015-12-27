# file: $isip/class/system/MemoryManager/GNUmakefile
# version: $Id: GNUmakefile 5990 2000-12-18 17:50:58Z duncan $
#
# this make file builds the MemoryManager class
# 

# define the source files
#
ISIP_FILES = *.cc

# define the header files that need to be installed
#
ISIP_HEADER_FILES = MemoryManager.h MemoryNode.h MemoryManagerBase.h

# define other dependencies (headers are included automatically)
#
ISIP_DEPS = Error.h Integral.h

# define the output library
#
ISIP_OLIB = lib_system.a

# define the compilation flags
# 
ISIP_CFLAGS =

# define the memory manager's mode of operation. it should be either
# OPTIMIZE or TRACK
#
ifneq "$(origin MEM_MGR_MODE)" "undefined"
	ISIP_CFLAGS += -DMEM_MGR_MODE=$(MEM_MGR_MODE) -DMEM_MGR_MODE_$(MEM_MGR_MODE)
else
	ISIP_CFLAGS += -DMEM_MGR_MODE=OPTIMIZE -DMEM_MGR_MODE_OPTIMIZE
endif

# include the isip standard make template
#
include $(ISIP_DEVEL)/lib/scripts/make/compile.make

#
# end of file
