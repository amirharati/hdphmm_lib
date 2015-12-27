# file: $isip/class/dstr/SingleLinkedList/GNUmakefile
# version: $Id: GNUmakefile 5822 2000-12-10 14:31:21Z picone $
#
# this make file builds the SingleLinkedList class
#

# define the source files
#
ISIP_FILES = 

# define the header files that need to be installed
#
ISIP_HEADER_FILES = SingleLinkedList.h SingleLinkedNode.h

# define other dependencies (headers are included automatically)
#
ISIP_DEPS = DstrBase.h VectorLong.h String.h Char.h \
	    Long.h Console.h Stack.h

# define the compilation flags
# 
ISIP_CFLAGS =

# define the diagnose class (we put diagnose method outside the header
# file in SingleLinkedListDiagnose.h)
#
DIAG_CLASS = SingleLinkedListDiagnose
DIAG_HEADER = $(ISIP_DEVEL)/class/dstr/SingleLinkedList/SingleLinkedListDiagnose.h

# define the diagnose mode for generic template classes
#
ISIP_DIAGNOSE_MODE = template-diagnose

# include the isip standard make template
#
include $(ISIP_DEVEL)/lib/scripts/make/compile.make

#
# end of file
