# file: $isip/class/dstr/Queue/GNUmakefile
# version: $Id: GNUmakefile 5382 2000-10-24 22:19:24Z srivasta $
#
# this make file builds the Queue class
#

# define the source files
#
ISIP_FILES =

# define the header files that need to be installed
#
ISIP_HEADER_FILES = Queue.h QueueDiagnose.h

# define other dependencies (headers are included automatically)
#
ISIP_DEPS = DoubleLinkedList.h String.h Char.h Console.h

# define the compilation flags
# 
ISIP_CFLAGS =

# define the diagnose class (we put diagnose method outside the header
# file in QueueDiagnose.h)
#
DIAG_CLASS = QueueDiagnose
DIAG_HEADER = $(ISIP_DEVEL)/class/dstr/Queue/QueueDiagnose.h

# define the diagnose mode for generic template classes
#
ISIP_DIAGNOSE_MODE = template-diagnose

# include the isip standard make template
#
include $(ISIP_DEVEL)/lib/scripts/make/compile.make

#
# end of file
