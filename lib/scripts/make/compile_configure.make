# file: $ISIP/scripts/make/compile_configure.make.in
#
# this makefile contains all of the installation/target specific variables
# as determined by configure.
#
PERL = /usr/bin/perl
TCL = /usr/bin/wish
SH = /bin/sh
SED = /bin/sed
AWK = /usr/bin/awk
JAVA = /usr/bin/java
JAVAC = /usr/bin/javac
JAR = /usr/bin/jar
SCLITE = 
MYSQL = @MYSQL@

LINK_CMD = /bin/ln -s
UNLINK_CMD = /usr/bin/unlink

# these will be parse-able by sed
#
PERL_PAT = $(subst /,\\/,$(PERL))
TCL_PAT = $(subst /,\\/,$(TCL))
SH_PAT = $(subst /,\\/,$(SH))
SED_PAT = $(subst /,\\/,$(SED))
AWK_PAT = $(subst /,\\/,$(AWK))
SCLITE_PAT = $(subst /,\\/,$(SCLITE))
MYSQL_PAT = $(subst /,\\/,$(MYSQL))
JAVA_PAT = $(subst /,\\/,$(JAVA))
JAVAC_PAT = $(subst /,\\/,$(JAVAC))
JAR_PAT = $(subst /,\\/,$(JAR))

# list out all the substitutions that will be made
#
SED_SUBST = -e "s/\@PERL\@/$(PERL_PAT)/g" -e "s/\@TCL\@/$(TCL_PAT)/g" -e "s/\@SH\@/$(SH_PAT)/g" -e "s/\@SED\@/$(SED_PAT)/g" -e "s/\@AWK\@/$(AWK_PAT)/g" -e "s/\@SCLITE\@/$(SCLITE_PAT)/g" -e "s/\@MYSQL\@/$(MYSQL_PAT)/g" -e "s/\@JAVA\@/$(JAVA_PAT)/g"   -e "s/\@JAVAC\@/$(JAVAC_PAT)/g"  -e "s/\@JAR\@/$(JAR_PAT)/g" 

#
# end of file
