#! /usr/bin/perl
#
# file: $ISIP_IFC/scripts/perl/command_line/command_line.pm
#
# this file contains the subroutines that pertain to command line parsing
#
# subroutine: command_line
#
# parse a command line in a standard robust manner. see the cl_example.pl
# script for an example of use.
#
# arguments:
#
# the first element of the argument list should be the number of fixed
# position command line options, referred to as $num_fixed.
#	$num_fixed = -1,   allow any number of fixed arguments
#	$num_fixed =  0,   no fixed arguments
#	$num_fixed >  0,   allow exactly $num_fixed fixed arguments
#
# the rest of the argument list should be a sequence of text strings
# representing allowable options followed by integers giving the number
# of arguments for that option. the integer for the number of arguments 
# follows the same rules as the indicator for the number of fixed argument.
# e.g.:
#	foo.pl -param runit.cfg -debug 3
# has two options, -param and -debug, with corresponding values of
# runit.cfg and 3. both of these options take one argument. there are no
# fixed arguments. so the call to the command_line procedure would appear as:
#	($param_file,$debug_level) = command_line(0,"-param",1,"-debug",1);
#
# the options can appear anywhere in any order on the command line,
# even intermixed with the fixed arguments. the obvious exception is that a
# variable number of option arguments must not immediately precede a
# fixed argument on the command line. e.g.:
#   isip_play -sf 8000 foo.dat -channels 0 1 2 3
# will be legal, but
#   isip_play -sf 8000 -channels 0 1 2 3 foo.dat
# is not, as the routine will not be able to distinguish if foo.dat is
# the fixed argument or the fifth channel argument. this is only for a
# variable number of option arguments, had the number of channel
# arguments been specified to 4 then either case would be valid.
#
# the return list from this subroutine will first contain $num_fixed
# fixed arguments in the order they appear on the command line,
# followed by the option values, respectively spaced to the input
# list. if an option was not specified on the command line its
# position in the list will hold a null string.
#
# an example is necessary to clarify: 
#
# consider a simplified usage of isip_play
#   usage: isip_play -sf 8000 -t ul foo.ul
# this string has two options and 1 fixed argument. so, 
#   ($sample_freq,$type,$filename) = command_line(1,"-sf",1,"-t",1);
# will do the trick. if the program had two fixed arguments, i.e.:
#   usage: isip_play -sf 8000 -t ul foo1.ul foo2.ul
# simply specify two fixed arguments,
#   ($sample_freq,$type,$f1,$f2) = command_line(2,"-sf",1,"-t",1);
#
# alternately, the fixed arguments may be returned as a list, so
#   ($sample_freq,$type,@files) = command_line(2,"-sf",1,"-t",1);
# works much the same way. this is also the approach that should be
# used if a variable number of fixed arguments is specified. perl
# handles this internally.
#
# up to this point, all options have used 1 argument. any option may
# take any number of arguments, with -1 signifying a variable number
# of arguments.  for example, flags will usually take no arguments, so 
#   usage: isip_play -swap_bytes -sf 8000 foo.ul
# will have the interface
#   ($swap_bytes,$sf,$f1) = command_line(1,"-swap_bytes",0,"-sf",1);
# while the program
#   usage: swap_channels foo.ul -channels c1 c2 -t .ul
# will interface as:
#   ($chans,$type,$file) = command_line(1,"-channels",2,"-type",1);
# the scalar variable $chans will be a space delimited string "c1 c2".
#

# define some useful constants for the command line and help routines
#
$DEFAULT_ISIP_HELP_OPTION = "(?:-help|-\\?)";
$DEFAULT_ISIP_HELP_COMMAND = "more";
@tmp = split(/\//,$0);
$DEFAULT_ISIP_PROG_NAME = pop(@tmp);
$DEFAULT_ISIP_HELP_FILE = <<__DEF_ISIP_HELP_HF__;

The creator of the script you are using has not included online help
for this tool. If help is not available through examples, please
consult with the project manager, or help\@isip.msstate.edu.
__DEF_ISIP_HELP_HF__

# subroutine: isip_help
#
# arguments: none
#
# this subroutine handles the "help" option inherently. all isip programs
# accept a help option. a 'isip_help' subroutine should be defined
# which outputs user help to stdout. the call to isip_help is
# wrapped in a eval structure so an error will not be produced if this
# subroutine is not found. the help option will not be returned in
# the return list.
#
sub isip_help { 

    # make sure both the help command or help file are defined, or set 
    # to defaults
    #
    if (!(defined $ISIP_HELP_COMMAND)) {
	$ISIP_HELP_COMMAND = $DEFAULT_ISIP_HELP_COMMAND;
    }
    if (!(defined $ISIP_HELP_FILE)) {
	$ISIP_HELP_FILE = $DEFAULT_ISIP_HELP_FILE;
    }

    # run the help file through more and exit
    #
    exec "echo \"$ISIP_HELP_FILE\" | $ISIP_HELP_COMMAND";
}	

# this subroutine should be used by programmers instead of the perl
# internal die command. it gives an error message and calls a function
# isip_clean_exit, which does cleanup before exit.
#
sub isip_die {
    $error_msg = join(' ',@_);

    if (!(defined $ISIP_PROG)) {
	$ISIP_PROG = $DEFAULT_ISIP_PROG_NAME;
    }
    print "\t$ISIP_PROG: $error_msg\n";
    eval "isip_clean_exit";
    if ($! ne "") {
	die "ERROR_CODE: $!\n";
    } else {
	exit;
    }
}

sub command_line {

    my $num_fixed = shift(@_);
    my @param_list = @_;
    
    # if the user defined the help option, use it. else use the default.
    #
    if (!(defined $ISIP_HELP_OPTION)) {
	$ISIP_HELP_OPTION = $DEFAULT_ISIP_HELP_OPTION;
    }

    # create a single line from the command line arguments
    #
    my $line = join(' ',@ARGV);
    
    # now split the subroutine arguments into useful lists
    #
    my @param_names = ();
    my @param_nums = ();
	
    $j = $#param_list + 1;

    # make sure that the number of arguments is valid
    #
    if (($j % 2) != 0) {
	isip_die "invalid number of arguments to command_line";
    } else {
	$j = $j / 2;
	for ($i=0; $i<$j; $i++) {
	    push(@param_names, shift(@param_list));
	    push(@param_nums, shift(@param_list));
	}
    }
    
    # look for the help option
    #
    if ($line =~ s/^(.*)$ISIP_HELP_OPTION(.*)$/$1$2/) {
	isip_help;
	$line =~ s/^\s*(.*)\s*$/$1/;
	isip_die;
    }

    # ret will hold the values corresponding to the list of options
    #
    @ret = ();

    # loop through the possible options
    #
    foreach $num (@param_nums) {

	$param = shift(@param_names);
	
	# make sure the help option was not specified.
	#
	if ($param eq $ISIP_HELP_OPTION) {
	    print "Error: do not specify a help option, as it is done";
	    print " automatically\nInstead define a isip_help method.";
	    isip_die "invalid argument";
	}
	
	if ($num > 0) {
	    $args = "\\s+\\S+" x $num;
	    $args = "($args)";
	} elsif ($num == 0) {
	    $args = "\\s*";
	} elsif ($num < 0) {

	    # generate a list of delimiters: the remaining options
	    #
	    @delims = ("\$");
	    foreach $delim_param (@param_names) {
		push(@delims,"\\s+($delim_param.*)");
	    }
	    
	    # join the list of possible delimiters
	    #
	    $delim_str = join('',"(?:",join('|',@delims),")");
	    $args = "(.*?)$delim_str";
	    
	    # hardcoded method to perform this task
	    # this is kept around (temporarily) in case the above 
	    # method breaks anything
	    #
	    #$args = "(.*?)(?:\\s+(-.+)|\$)";

	}
	$regexp = "^(.*?\\s*)$param$args(\\s*.*)\$";

	# if the option is found, remove it from the string and 
	# push it onto the option value list
	#
	if ($line =~ /$regexp/) {

	    if ($num == 0) {

		$value = 1;
		$line = "$1$2";
		push(@ret,$value);

	    } else {

		$value = $2;
		$line = "$1$3";
		$value =~ s/^\s*(.*)\s*$/$1/;

		@values = split(/\s+/,$value);
		push(@ret,join(' ',@values));

	    }

	    $line =~ s/^\s*(.*)\s*$/$1/;

	} else {
	    
	    # option not specified, use a null place holder
	    #
	    push(@ret,"");
	}
    }
    
    # now that all specified options have been removed from $line,
    # deal with the fixed arguments
    #
    @fixed = split(/\s+/,$line);

    # if num_fixed is specified, make sure the # of fixed arguments matches
    #
    if ($num_fixed >=0) {
	$nfixed = $#fixed + 1;
	if ($nfixed != $num_fixed) {
	    print "invalid number of fixed arguments: $num_fixed expected, $nfixed found\n";
	    isip_help;
	    exit;
	}
    }

    # set up the return list: first fixed args then options
    #
    @vals = ();
    push(@vals,@ret);
    push(@vals,@fixed);
    @vals;
    
}

# exit gracefully
#
1;
#
# end of file
