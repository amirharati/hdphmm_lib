# file: $isip/class/pr/VerifyHMM/GNUmakefile
# version: $Id: GNUmakefile 9334 2003-11-07 16:15:02Z tang $
#
# this make file builds the VerifyHMM class
# 

# define the source files
#
ISIP_FILES = *.cc

# define the header files that need to be installed
#
ISIP_HEADER_FILES = HDP.h 

# define other dependencies (headers are included automatically)
#
ISIP_DEPS = Database.h Random.h Wishart.h Dirichlet.h MatrixDouble.h VectorDouble.h MatrixLong.h VectorLong.h Vector.h Double.h Long.h

# define the output library
#
ISIP_OLIB = lib_pr.a

# define the compilation flags
# 
ISIP_CFLAGS = -fopenmp

# include the isip standard make template
#
include $(ISIP_DEVEL)/lib/scripts/make/compile.make

#
# end of file




