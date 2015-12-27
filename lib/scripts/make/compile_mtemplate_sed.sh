#! /bin/sh

# file: $ISIP_IFC/scripts/make/compile_mtemplate_sed.sh
# version: $Id: compile_mtemplate_sed.sh 9612 2004-07-03 18:12:07Z picone $
#

# inputs will come from stdin and contain a single object file stem
# name. These names will first have the source file, a period, then
# have the template arguments seperated by periods. For example,
#
#   mscl_00.cc for MScalar<Long,long> would look like:
#   mscl_00.Long.long
#

# the first will be the root name, where the source file can be found
#
if (test "$1" = "source_name") then
    /bin/sed -e 's/\..*$//' -e 's/^\(.*\)$/\1.cc/' 
fi

if (test "$1" = "modifier") then
    /bin/sed -e 's/^[^\.]*\.//' -e 's/^\(.*\)$/\1~/' -e 's/\~\([^\~]*\)\~/~\1/' -e 's/\.\([^\~]*\)\~/_\1~/' -e 's/\.\([^\~]*\)\~/_\1~/' -e 's/\.\([^\~]*\)\~/_\1~/' -e 's/\~/\./' -e 's/^\(.\)/\.\1/' -e 's/\./\ -DISIP_TEMPLATE_/g' -e 's/\-DISIP_TEMPLATE_$//'
fi

# the template args will be the full template args, seperated by
# commas
#
if (test "$1" = "template_args") then
    /bin/sed -e 's/^[^.]*\.//' -e 's/.o$//' -e 's/\./,/g' -e 's/\~.*$//' -e 's/\_1/\</' -e 's/\_2/\>/'
fi

# t1 is the first template argument
#
if (test "$1" = "t0") then
    /bin/sed -e 's/^[^.]*\.\([^.]*\).*$/\1/' -e 's/\~.*$//' -e 's/\_1/\</' -e 's/\_2/\>/'
fi

# t2 is the second template argument
#
if (test "$1" = "t1") then
    /bin/sed -e 's/^[^.]*\.[^.]*\.\([^.]*\).*$/\1/' -e 's/\~.*$//' -e 's/\_1/\</' -e 's/\_2/\>/'
fi

# t3 is the third template argument
#
if (test "$1" = "t2") then
    /bin/sed -e 's/^[^.]*\.[^.]*\.[^.]*\.\([^.]*\).*$/\1/' -e 's/\~.*$//' -e 's/\_1/\</' -e 's/\_2/\>/'
fi

#
# end of file
