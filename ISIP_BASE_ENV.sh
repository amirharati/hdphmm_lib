#!/bin/sh
# file: $isip/ISIP_BASE_ENV.sh
#
# This shell sets the minimal required environmental variables for
# building ISIP software
#

# ----------------------------------------
# define the necessary environmental variables
# ----------------------------------------

# ISIP, ISIP_DEVEL, and isip both point to the base of the ISIP source tree
#

ISIP_IFC=`pwd`
ISIP=$ISIP_IFC
ISIP_DEVEL=$ISIP_IFC
isip_ifc="$ISIP_IFC";
PATH=$ISIP_IFC/bin/linux-gnu:$PATH
# define a make command
#
ISIP_MAKE="nice -5 gmake";

# define the location of c++
#
ISIP_CPLUS_COMPILER="g++";

# define a binary directory. if uname does not work on your system,
# you need to create some arbitrary string which will be unique across
# each architecture you use. our values for ISIP_BINARY are
# i386_SunOS_5.6 or sparc_SunOS_5.6
#
ISIP_BINARY=linux-gnu

# ----------------------------------------
# you shouldn't need to edit anything below this line
# ----------------------------------------

prefix=$ISIP_IFC
exec_prefix=${prefix};

# if the library directory was specialized in configure, point users
# to that directory.
#
if (test "$ISIP_IFC/lib" = "${exec_prefix}/lib") then
   ISIP_LIB_DIR="$ISIP_IFC/lib/$ISIP_BINARY"
else
   ISIP_LIB_DIR="${exec_prefix}/lib"
fi

# if the include directory was specialized in configure, point users
# to that directory.
#
if (test "$ISIP_IFC/include" = "${prefix}/include") then
   ISIP_INCLUDE_DIR="$ISIP_IFC/include"
else
   ISIP_INCLUDE_DIR="${prefix}/include"
fi

# if the bin directory was specialized in configure, point users
# to that directory. note that if they don't specify a directory
# we split out scripts from binaries internally.
#
if (test "$ISIP_IFC/bin" = "${exec_prefix}/bin") then
   PATH="$PATH:$ISIP_IFC/bin/$ISIP_BINARY/:$ISIP_IFC/bin/scripts";
else
   PATH="$PATH:${exec_prefix}/bin";
fi

ISIP_INCLUDE="-I$ISIP_INCLUDE_DIR -I./";
ISIP_LIBS="-L$ISIP_LIB_DIR -l_asr -l_pr -l_search -l_sp -l_algo -l_stat -l_mmedia -l_shell -l_numeric -l_math_matrix -l_math_vector -l_math_scalar -l_io -l_system -lm";

EXTRA_LIBS="    -L -lexpat ";
EXTRA_INCLUDE="   -I  ";
ISIP_VERSION="ver_0";
if test \! -z ""
then
	#ISIP_DEFINES="$ISIP_DEFINES -DHAVE_AUDIOFILE"
        ISIP_DEFINES="$ISIP_DEFINES"
fi

if test \! -z ""
then
	#ISIP_DEFINES="$ISIP_DEFINES -DHAVE_SPHERE"
        ISIP_DEFINES="$ISIP_DEFINES"
fi

if test \! -z ""
then
	#ISIP_DEFINES="$ISIP_DEFINES -DHAVE_COMMUNICATOR"
        ISIP_DEFINES="$ISIP_DEFINES"
fi

if test \! -z "-L -lexpat "
then
	#ISIP_DEFINES="$ISIP_DEFINES -DHAVE_EXPAT"
	#ISIP_MAKE_EXPAT="true"
        ISIP_DEFINES="$ISIP_DEFINES"
fi

if test \! -z ""
then
	#ISIP_DEFINES="$ISIP_DEFINES -DHAVE_EXPATIMPL"
	#ISIP_MAKE_EXPATIMPL="true"
        ISIP_DEFINES="$ISIP_DEFINES"
fi

GC_HOME=

# export all variables
#
export ISIP_IFC isip_ifc ISIP_DEVEL ISIP_MAKE ISIP_CPLUS_COMPILER ISIP_BINARY 
export ISIP_INCLUDE ISIP_LIBS ISIP_VERSION PATH EXTRA_LIBS EXTRA_INCLUDE ISIP_DEFINES GC_HOME ISIP_MAKE_EXPAT ISIP_MAKE_EXPATIMPL

# if a partial ISIP envioronment is running, it could cause problems. 
# unset a few variables
#
unset ISIP_WORK

#
# end of file
