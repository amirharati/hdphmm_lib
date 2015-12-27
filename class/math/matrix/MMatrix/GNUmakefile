# file: $isip/class/math/matrix/MMatrix/GNUmakefile
# version: $Id: GNUmakefile 7772 2002-02-20 22:48:26Z hamaker $
#
# this make file builds the MMatrix class
# 

# define the source files
#
ISIP_FILES = *.cc
ISIP_NON_TEMPLATE_FILES = mmat_11.cc mmat_13.cc

# define the header files that need to be installed
#
ISIP_HEADER_FILES = MMatrix.h MMatrixMethods.h

# define other dependencies (headers are included automatically)
#
ISIP_DEPS = MVector.h MScalar.h MMatrixDiagnose.h

# define the template targets that we need explicit instantiations
# for. this list is a space-delimited list of template types. if there
# are multiple template arguments they should be delimeted by periods,
# "Byte" is the first template argument and "byte" is the second for
# the first target.
#
ISIP_TEMPLATE_TARGETS = Byte.byte8~unsigned \
			ComplexDouble.complexdouble~complex \
			ComplexFloat.complexfloat~complex \
			ComplexLong.complexlong~complex \
			Double.float64~fp Float.float32~fp \
			Llong.int64 Long.int32 Short.int16 \
			Ulong.uint32~unsigned Ullong.uint64~unsigned \
			Ushort.uint16~unsigned

# define the output library
#
ISIP_OLIB = lib_math_matrix.a

# define the compilation flags
# 
ISIP_CFLAGS = -fopenmp

# since this is a template, diagnose cannot be run directly
#
ISIP_DIAGNOSE_MODE = none

# include the isip standard make template
#
include $(ISIP_DEVEL)/lib/scripts/make/compile_mtemplate.make

#
# end of file
