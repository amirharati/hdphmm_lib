# file: $isip/class/algo/Random/GNUmakefile
# version: $Id: GNUmakefile 5283 2000-10-10 20:57:29Z duncan $
#
# this make file builds the Random class
# 

# define the source files
#
ISIP_FILES = *.cc

# define the header files that need to be installed
#
ISIP_HEADER_FILES = Random.h

# define other dependencies (ISIP_HEADER_FILES is included automatically)
#
ISIP_DEPS = SysString.h MemoryManager.h

# define the output library
#
ISIP_OLIB = lib_system.a

# define the compilation flags
# 
ISIP_CFLAGS = -fopenmp

# include the isip standard make template
#
include $(ISIP_DEVEL)/lib/scripts/make/compile.make

#
# end of file
