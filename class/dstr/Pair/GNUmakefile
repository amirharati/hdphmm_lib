# file: $isip/class/dstr/Pair/GNUmakefile
# version: $Id: GNUmakefile 5382 2000-10-24 22:19:24Z srivasta $
#
# this make file builds the Pair class
#

# define the source files
#
ISIP_FILES =

# define the header files that need to be installed
#
ISIP_HEADER_FILES = Pair.h

# define other dependencies (headers are included automatically)
#
ISIP_DEPS = String.h Char.h Vector.h Console.h

# define the compilation flags
# 
ISIP_CFLAGS =

# define the diagnose class (we put diagnose method outside the header
# file in PairDiagnose.h)
#
DIAG_CLASS = PairDiagnose
DIAG_HEADER = $(ISIP_DEVEL)/class/dstr/Pair/PairDiagnose.h

# define the diagnose mode for generic template classes
#
ISIP_DIAGNOSE_MODE = template-diagnose-2

# include the isip standard make template
#
include $(ISIP_DEVEL)/lib/scripts/make/compile.make

#
# end of file
