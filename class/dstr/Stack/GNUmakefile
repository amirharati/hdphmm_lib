# file: $isip/class/dstr/Stack/GNUmakefile
# version: $Id: GNUmakefile 5367 2000-10-24 00:45:02Z srivasta $
#
# this make file builds the Stack class
#

# define the source files
#
ISIP_FILES =

# define the header files that need to be installed
#
ISIP_HEADER_FILES = Stack.h

# define other dependencies (headers are included automatically)
#
ISIP_DEPS = DoubleLinkedList.h String.h Char.h Console.h

# define the compilation flags
# 
ISIP_CFLAGS =

# define the diagnose class (we put diagnose method outside the header
# file in StackDiagnose.h)
#
DIAG_CLASS = StackDiagnose
DIAG_HEADER = $(ISIP_DEVEL)/class/dstr/Stack/StackDiagnose.h

# define the diagnose mode for generic template classes
#
ISIP_DIAGNOSE_MODE = template-diagnose

# include the isip standard make template
#
include $(ISIP_DEVEL)/lib/scripts/make/compile.make

#
# end of file
