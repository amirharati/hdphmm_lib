# file: $isip/class/dstr/DoubleLinkedList/GNUmakefile
# version: $Id: GNUmakefile 10636 2007-01-26 22:18:09Z tm334 $
#
# this make file builds the DoubleLinkedList class
#

# define the source files
#
ISIP_FILES =

# define the header files that need to be installed
#
ISIP_HEADER_FILES = DoubleLinkedList.h DoubleLinkedNode.h

# define other dependencies (headers are included automatically)
#
ISIP_DEPS = DstrBase.h VectorLong.h String.h Char.h \
	    Long.h Console.h

# define the compilation flags
# 
ISIP_CFLAGS =

# define the diagnose class (we put diagnose method outside the header
# file in DoubleLinkedListDiagnose.h)
#
DIAG_CLASS = DoubleLinkedListDiagnose
DIAG_HEADER = $(ISIP_DEVEL)/class/dstr/DoubleLinkedList/DoubleLinkedListDiagnose.h

# define the diagnose mode for generic template classes
#
ISIP_DIAGNOSE_MODE = template-diagnose

# include the isip standard make template
#
include $(ISIP_DEVEL)/lib/scripts/make/compile.make

#
# end of file
