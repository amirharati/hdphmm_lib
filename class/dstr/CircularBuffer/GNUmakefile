# file: $isip/class/dstr/CirularBuffer/GNUmakefile
# version: $Id: GNUmakefile 8122 2002-04-19 13:06:05Z zheng $
#	
# this make file builds the CircularBuffer class
#

# define the source files
#
ISIP_FILES =

# define the header files that need to be installed
#
ISIP_HEADER_FILES = CircularBuffer.h

# define other dependencies (headers are included automatically)
#
ISIP_DEPS = Vector.h Float.h Console.h

# define the compilation flags
# 
ISIP_CFLAGS =

# define the diagnose class (we put diagnose method outside the header
# file in CircularBufferDiagnose.h)
#
DIAG_CLASS = CircularBufferDiagnose
DIAG_HEADER = $(ISIP_DEVEL)/class/dstr/CircularBuffer/CircularBufferDiagnose.h

# define the diagnose mode for generic template classes
#
ISIP_DIAGNOSE_MODE = template-diagnose

# include the isip standard make template
#
include $(ISIP_DEVEL)/lib/scripts/make/compile.make

#
# end of file
