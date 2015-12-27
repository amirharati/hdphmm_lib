# file: $isip/class/math/scalar/MScalar/GNUmakefile
# version: $Id: GNUmakefile 10636 2007-01-26 22:18:09Z tm334 $
#
# note:
# AH (07/28/2010): ISIP_TEMPLATE_TARGETS has been updated
# this make file builds the MScalar class
# 

# define the source files. note that mscl_06.cc needs to be built only
# once so it is on a different list than all the other source files.
#
ISIP_FILES = *.cc
ISIP_NON_TEMPLATE_FILES = mscl_06.cc

# define the header files that need to be installed
#
ISIP_HEADER_FILES = MScalar.h MScalarMethods.h

# define other dependencies (headers are included automatically)
#
ISIP_DEPS = Integral.h SysComplex.h Random.h String.h

# define the template targets that we need explicit instantiations
# for. this list is a space-delimited list of template types. if there
# are multiple template arguments they should be delimeted by periods,
# "Byte" is the first template argument and "byte" is the second for
# the first target. each template type can also have modifiers, which
# are specified after the equals (=) character. byte, ushort, ullong,
# and ullong all have the unsigned modifier so those types will be
# compiled with an additional -DISIP_TEMPLATE_unsigned variable.
#
ISIP_TEMPLATE_TARGETS = byte8.byte8~unsigned uint16.uint16~unsigned \
			uint32.uint32~unsigned uint64.uint64~unsigned \
			int16.int16 int32.int32 int64.int64 \
			float32.float32 float32.float64 \
			float64.float64~complex \
			float32.float32~complex \
			int32.int32~complex 

# define the output library
#
ISIP_OLIB = lib_math_scalar.a

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
