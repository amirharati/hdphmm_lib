#! /usr/local/bin/perl
#
# file: $isip/scripts/perl/command_line/cl_example.pl
#
# this is an example use of the command_line.pl command line parsing
# module. 

# load the command_line source
#
require "$ENV{'ISIP'}/lib/scripts/perl/command_line.pm";

# define the help function to be called if -help is present on the
# command line. this should print a help file to the screen.
#

$ISIP_HELP_FILE = <<__ISIP_HELP_HERE_FILE__;
name: cl_example
synopsis: cl_example [options] file1 file2
descr: provide example code for the perl command line module
example: cl_example -viterbi foo1.dat foo2.dat

options:
 -viterbi: example flag option
 -opts: an option with three arguments

arguments: two filenames are expected as fixed arguments

man page: none
__ISIP_HELP_HERE_FILE__

my $method = 1;

# method 1, below
#
if ($method == 0) {
    ($vit,$opts,$f1,$f2) = command_line(2,"-viterbi",0,"-opts",3);

    # note that / / works as the split string because the subroutine
    # guarantees a single space to be the delimiter.
    #
    ($o1,$o2,$o3) = split(/ /,$opts);

}

# nearly equivalent to the above, but neater if you have many fixed 
# arguments. also allows a variable number of -opts arguments.
#
if ($method == 1) {
    ($opts,$vit,@files) = command_line(2,"-opts",-1,"-viterbi",0);
    ($o1,$o2,$o3) = split(/ /,$opts);
    ($f1,$f2) = @files;
}

# -1 may be given to the number of fixed arguments (first argument to
# either version) and it will return any number of fixed arguments. in
# this case use method 1 to specify a list to place the variable
# number of fixed arguments. obviously you cannot place a variable
# number of option arguments immeadiately preceding your fixed
# arguments on the command line, as there would be no way to tell
# which was which.
#
if ($method == 2) {
    ($opts,$vit,@files) = command_line(-1,"-opts",3,"-viterbi",0);
    ($o1,$o2,$o3) = split(/ /,$opts);
    if (($#files+1) >= 2) {
	($f1,$f2) = @files;
    } else {
	isip_die("not enough fixed arguments");
    }
}

# print out the user input
#
print "f1 = >$f1<\n";
print "f2 = >$f2<\n";
print "vit = >$vit<\n";
print "opts = >$o1<\n";
print "opts = >$o2<\n";
print "opts = >$o3<\n";

#
# end of file




