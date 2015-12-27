# file: $isip/class/math/vector/MVector/GNUmakefile
# version: $Id: GNUmakefile 10636 2007-01-26 22:18:09Z tm334 $
#

# define the source files. note that mvec_12.cc needs to be built only
# once so it is on a different list than all the other source files.
#
ISIP_FILES = *.cc
ISIP_NON_TEMPLATE_FILES = mvec_12.cc

# define the header files that need to be installed
#
ISIP_HEADER_FILES = MVector.h MVectorMethods.h

# define other dependencies (headers are included automatically)
#
ISIP_DEPS = MScalar.h MComplexScalar.h \
	    Byte.h ComplexDouble.h ComplexFloat.h ComplexLong.h \
	    Double.h Float.h Llong.h Long.h Short.h String.h \
	    Ullong.h Ulong.h Ushort.h

# define the template targets that we need explicit instantiations
# for. this list is a space-delimited list of template types. if there
# are multiple template arguments they should be delimeted by periods,
# "Byte" is the first template argument and "byte" is the second for
# the first target.
#

ISIP_TEMPLATE_TARGETS = Byte.byte8~unsigned \
			Ushort.uint16~unsigned \
			Ulong.uint32~unsigned \
			Ullong.uint64~unsigned \
			Short.int16~signed \
			Long.int32~signed \
			Llong.int64~signed \
			Float.float32~float \
			Double.float64~float \
			ComplexLong.complexlong~complex \
			ComplexFloat.complexfloat~complex \
			ComplexDouble.complexdouble~complex

# define the output library
#
ISIP_OLIB = lib_math_vector.a

# define the compilation flags
# 
ISIP_CFLAGS =

# since this is a template, diagnose cannot be run directly
#
ISIP_DIAGNOSE_MODE = none

# include the isip standard make template
#
include $(ISIP_DEVEL)/lib/scripts/make/compile_mtemplate.make

#
# end of file
