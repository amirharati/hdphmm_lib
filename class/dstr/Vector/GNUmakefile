# file: $isip/class/dstr/Vector/GNUmakefile
# version: $Id: GNUmakefile 5379 2000-10-24 21:32:38Z srivasta $
#
# this make file builds the Vector class
#

# define the source files
#
ISIP_FILES =

# define the header files that need to be installed
#
ISIP_HEADER_FILES = Vector.h

# define other dependencies (headers are included automatically)
#
ISIP_DEPS = DstrBase.h DoubleLinkedList.h Long.h String.h Char.h \
	    Console.h

# define the compilation flags
# 
ISIP_CFLAGS =

# define the diagnose class (we put diagnose method outside the header
# file in VectorDiagnose.h)
#
DIAG_CLASS = VectorDiagnose
DIAG_HEADER = $(ISIP_DEVEL)/class/dstr/Vector/VectorDiagnose.h

# define the diagnose mode for generic template classes
#
ISIP_DIAGNOSE_MODE = template-diagnose

# include the isip standard make template
#
include $(ISIP_DEVEL)/lib/scripts/make/compile.make

#
# end of file
