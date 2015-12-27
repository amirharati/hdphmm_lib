# file: $isip/class/math/scalar/MComplexScalar/GNUmakefile
# version: $Id: GNUmakefile 10636 2007-01-26 22:18:09Z tm334 $
#
# this make file builds the MComplexScalar class
# 

# define the source files. note that mscl_06.cc needs to be built only
# once so it is on a different list than all the other source files.
#
ISIP_FILES = *.cc
ISIP_NON_TEMPLATE_FILES = mcscl_06.cc

# define the header files that need to be installed
#
ISIP_HEADER_FILES = MComplexScalar.h MComplexScalarMethods.h

# define other dependencies (headers are included automatically)
#
ISIP_DEPS = SysComplex.h MScalar.h

# define the template targets that we need explicit instantiations
# for. this list is a space-delimited list of template types. if there
# are multiple template arguments they should be delimeted by periods,
# "Byte" is the first template argument and "byte" is the second for
# the first target. each template type can also have modifiers, which
# are specified after the equals (=) character. byte, ushort, ullong,
# and ullong all have the unsigned modifier so those types will be
# compiled with an additional -DISIP_TEMPLATE_unsigned variable.
#
ISIP_TEMPLATE_TARGETS = float32.float32~complex float64.float64~complex int32.int32~complex

# define the output library
#
ISIP_OLIB = lib_math_scalar.a

# define the compilation flags
# 
ISIP_CFLAGS = -fpermissive 

# since this is a template, diagnose cannot be run directly
#
ISIP_DIAGNOSE_MODE = none

# include the isip standard make template
#
include $(ISIP_DEVEL)/lib/scripts/make/compile_mtemplate.make

#
# end of file
