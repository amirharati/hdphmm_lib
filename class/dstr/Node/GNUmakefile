# file: $isip/class/dstr/Node/GNUmakefile
# version: $Id: GNUmakefile 5358 2000-10-23 21:46:46Z srivasta $
#
# this make file builds the Node class
#

# define the source files
#
ISIP_FILES =

# define the header files that need to be installed
#
ISIP_HEADER_FILES = Node.h

# define other dependencies (headers are included automatically)
#
ISIP_DEPS = String.h Char.h Console.h

# define the compilation flags
# 
ISIP_CFLAGS =

# define the diagnose class (we put diagnose method outside the header
# file in NodeDiagnose.h)
#
DIAG_CLASS = NodeDiagnose
DIAG_HEADER = $(ISIP_DEVEL)/class/dstr/Node/NodeDiagnose.h

# define the diagnose mode for generic template classes
#
ISIP_DIAGNOSE_MODE = template-diagnose

# include the isip standard make template
#
include $(ISIP_DEVEL)/lib/scripts/make/compile.make

#
# end of file
