# file: $isip/class/system/SysComplex/GNUmakefile
# version: $Id: GNUmakefile 10636 2007-01-26 22:18:09Z tm334 $
#
# this make file builds the SysComplex class
#

# define the source files
#
ISIP_FILES = *.cc

# define the header files that need to be installed
#
ISIP_HEADER_FILES = SysComplex.h

# define other dependencies (headers are included automatically)
#
ISIP_DEPS = Integral.h

# define the output library
#
ISIP_OLIB = lib_system.a

# define the compilation flags
# 
ISIP_CFLAGS = 

# define the diagnose class (we put diagnose method outside the header
# file in DoubleLinkedListDiagnose.h)
#
DIAG_CLASS = SysComplexDiagnose
DIAG_HEADER = $(ISIP_DEVEL)/class/system/SysComplex/SysComplexDiagnose.h
TEMPLATE_DIAGNOSE_CLASS = float

# define the diagnose mode for generic template classes
#
ISIP_DIAGNOSE_MODE = template-diagnose

# include the isip standard make template
#
include $(ISIP_DEVEL)/lib/scripts/make/compile.make

#
# end of file
