#!/usr/local/bin/perl

# this perl script is used as cgi script to find the part where the
# method resides in the file
# 
#   usage in html file: 
#    <a href="/cgi/bin/ifc_document.pl?file=$isip/class/shell/CommandLine/cmdl_io_00.cc&method=read&instance=0">
#
#  where the instance and debug are optional
#  instance = 0 denotes that the first time the method in query appears
#

if ((defined $ENV{ISIP}) && ($ENV{ISIP} ne "")) {
    $isip = $ENV{ISIP};
}
else {
    $isip = "/isip/tools/devel";
}

# split the query string using delimiter &
#
@entries = split(/\&/, $ENV{QUERY_STRING});

# initialize the variables
#
$file = "";
$method = "";
$debug = 0;
$instance = -1;
$DELETED_STRING = "\n[snipped]\n\n";


# find the file name, method name, etc. variables in query 
#
foreach $entry (@entries) {

    # parse '+' into space
    #
    $entry =~ s/\+/ /g;
    
    # split into key and value
    #
    ($var, $val) = split(/=/, $entry);

    # convert %XX from hex to ascii
    #
    $var =~ s/%(..)/pack("c",hex($1))/ge;
    $val =~ s/%(..)/pack("c",hex($1))/ge;
    
    if ($var eq "file") {
        $file = $val;
    }
    elsif ($var eq "method") {
	# replace ( ) with \( \)
	#
	$val =~ s/\(/\\\(/;
	$val =~ s/\)/\\\)/;

        $method = $val;
    }
    elsif ($var eq "instance") {
        $instance = $val;
    }
    elsif ($var eq "debug") {
        $debug = $val;
    }
}


# check argument
#
if ($file eq "") {
    print "Error in arguments\n\n";
}

$file =~ s/\$isip/$isip/;
$file =~ s/\$ISIP/$isip/;

# initialize the output with standard ISIP Documentation Headers
#
print "Content-type: text/html\n\n";
print "<html>\n";

# set up title, background color and preformated tag
#
print "<title>$file</title>\n";
$file_to_cat = '/ftp/pub/templates/documentation/header/header.html';
&cat_file;

$file_to_cat = '/ftp/pub/templates/documentation/body/bar.html';
&cat_file;

print ("<center><font color=\"#006699\" size=\"+2\">\n");
print ("<b>$file</b></font></center><br>\n");

print "<pre>\n";

# possibly give some debug information
#
if ($debug == 1) {
    print "file = >$file<\nmethod = >$method<\ninstance = >$instance<\n\n";
}

# if no method is given, cat the entire file
# otherwise, find the specified method
#
if ($method eq "") {
    
    $file_to_cat = $file;
    &cat_file_with_replace;
} else {
    
# open the file
#
open(FP, $file) or print "File $file could not be opened: $!\n\n";

$printing = 2;
$icount = 0;
$brac_count = 0;

# replace [ ] with \[ \] in the $method string, eg. new[] to new\[\]
# for the purpose of string matching, 
#
$method =~ s/\[/\\\[/;
$method =~ s/\]/\\\]/;

# if it is already in \[\] format, change it back
#
$method =~s/\\\\/\\/g;

# loop through the file
#
while (<FP>) {
	# replace < and >
	#
	$_ =~ s/\</\&lt\;/g;
	$_ =~ s/\>/\&gt\;/g;

    if (/\/\/\ method\: (.*)$/) {
	
	# replace [ ] with \[ \]
	#
	$mm = $1;

	$mm =~ s/\[/\\\[/;
	$mm =~ s/\]/\\\]/;
	# replace ( ) with \( \)
	#
	$mm =~ s/\(/\\\(/;
	$mm =~ s/\)/\\\)/;

	# if this the method in query
	#
	if ($mm eq $method || $mm =~ /^$method\s.*/) {
	    
	    # if instance is specified, only output one of the methods
	    #
	    if ($instance >= 0) {
		if ($icount == $instance) {
		    $printing = 1;
		} else {
		    if ($printing == 1) {
			print $DELETED_STRING;
		    }
		    $printing = 0;
		}
		
		# increase instance count
		#
		$icount++;
	    } else {
		$printing = 1;
	    }
	}
	else {
	    if ($printing == 1) {
		print $DELETED_STRING;
	    }
	    $printing = 0;
	}
    }
    
    if ($printing == 1) {
	print;
	
	chop($_);

	# check for open braces
	#
	if (/\.*\{.*$/) {

	    # increment the brace count
	    #
	    $brac_count++;
	}

	# check for close braces
	#
	if(/\.*\}$/) {
	    
	    # decrement the brace count
	    #
	    $brac_count--;

	    # if the count equals zero
	    # print the line
	    # and set $printing = 0
	    #
	    if($brac_count == 0) {
		$printing = 0;
		print $DELETED_STRING;		
	    }
	}
    }
    
    if ($printing == 2) {
	print;
	if (/^\#include/) {
	    $printing = 3;
	}
    }
    elsif (($printing == 0) && (/\/\/ isip include files/)) {
	print "\n$_";
	$printing = 2;
    }
    elsif ($printing == 3) {
	if (/^\#include/) {
	    print;
	}
	else {
	    $printing = 0;
	    print $DELETED_STRING;
	}
    }
}

if ($printing <= 1) {
    print "//\n// end of file\n\n";
}
}

# close out the html
#
print "</pre>\n";

$file_to_cat = '/ftp/pub/templates/general/footer/footer.html';
&cat_file;

# main program exit
#

###########################
#   S U B R O U T I N E S #
###########################

# cat_file:  list the file - simulate the server side #include
#
# set $file_to_cat to file name and then call &cat_file
#
sub cat_file {

# open the file
#
open(FP1, "$file_to_cat") or print "File $file_to_cat could not be opened: $!\n\n";

while (<FP1>) {
    chop();
    print "$_\n";
    }

}

# cat_file:  list the file - simulate the server side #include
#
# set $file_to_cat to file name and then call &cat_file_with_replace
#
sub cat_file_with_replace {

# open the file
#
open(FP1, "$file_to_cat") or print "File $file_to_cat could not be opened: $!\n\n";

while (<FP1>) {
    chop();

    # replace < and >
    #
    $_ =~ s/\</\&lt\;/g;
    $_ =~ s/\>/\&gt\;/g;

    print "$_\n";
    }

}

#
# end of file
