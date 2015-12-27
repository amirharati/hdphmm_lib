#! /usr/local/bin/perl

# this perl script is used as cgi script to find the part where the
# error code resides in the error message file
# 
#   usage in html file: 
#    <a href="/cgi/bin/find_error.pl?file=[$isip/class/system/Error/ErrorMessages.h]&err=00045005[&debug=1]>
#
#  where the file and the debug are optional
#


# initialize the output with standard ISIP Documentation Headers
#
print ("Content-type: text/html\n\n");
print ("<html>\n");
print ("<title>\"ISIP Software Documentation\"></title>\n");

$file_to_cat = '/templates/documentation/header/header.html';
&cat_file;

$file_to_cat = '/templates/documentation/body/bar.html';
&cat_file;

print ("<center><font color=\"#006699\" size=\"+2\">\n");
print ("<b>ErrorMessages.h</b></font></center><br>\n");

print ("<pre>\n");

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
$err_code = "";
$debug = 0;

$DELETED_STRING = "\n[snipped]\n";

# find the file name, error code etc. variables in query 
#
foreach $entry (@entries) {
    
    # parse '+' into space
    #
    $entry =~ s/\+/ /g;
    
    # split into key and value
    #
    ($var, $val) = split(/=/, $entry);
    
    if ($var eq "err") {
        $err_code = $val;
    }
    elsif ($var eq "file") {
        $file = $val;
    }
    elsif ($var eq "debug") {
        $debug = $val;
    }
}


# specify the default error message file
#
if ($file eq "") {
    $file = "$isip/class/system/Error/ErrorMessages.h";
}

# possibly give some debug information
#
if ($debug > 0) {
    print "file = >$file<\nerr_code = >$err_code<\n\n";
}

# check argument
#
if ($err_code eq "") {
    print "Error in arguments\n\n";
}

$length = length($err_code);
if ($length != 8) {
    print "error code length $length\n";
}

# open the file
#
open(FP, $file) or print "File $file could not be opened: $!\n\n";


# print the error message file name and the string indicating snip
#
print "// file: $file\n//\n";
print "$DELETED_STRING";


# find a substring in the error code, which is used for matching the error code
#
$err_code =~ /(0*)(.*)/;
$zero = $1;
$err_ini = $2;

if (length($err_ini) == 0) {
    # error code is 00000000, we use 0000000 to match the error code later
    #
    $zero =~ /^(.*)0$/;
    $zero = $1;
}
elsif (length($err_ini) == 1) {
    
    # error code is 0000000x, we use 0000000 to match the error code later
    #
    $err_ini ="";
}

elsif (length($err_ini) == 2) {

    # error code is 000000xy, we use 000000x to match the error code later
    #
    $err_ini =~ /(.)./;
    $err_ini = "$1";
}

elsif (length($err_ini) > 2) {

    # others, we use the zeros and the first two non-zero numbers to match 
    # the error code later
    #
    $err_ini =~ /(..).*/;
    $err_ini = $1;
}


$found = 0;
$count = 0;
$section_start = 1;

# loop through the file
#
while (<FP>) {
    
    chop();

    # remember the comment of this session
    #
    if ($_ =~ /\s*\/\/.*errors\s*$/) {
	$comment = $_;
	
	# we reach the next comment, if the error code already found
	# stop. or else reset count and continue to next section
	#
	if ($found == 1) {
	    $section_start = 0;
	}
	else {
	    $count = 0;
	}
    }
    
    # if the error code initial matches and we are in the correct section 
    # print the comment and the message lines out
    #
    elsif (($_ =~ /L\"$zero$err_ini.*/) && 
	   ($section_start != 0)) {
	
	if ($count == 0) {
	    print "\n$comment\n";
	    print "  \/\/\n";
	    $count = 1;
	}
	# higlight the line with the error
        #
	if ($found == 0) {
	    if ($_ =~ /L\"$err_code.*/) {
		print("<b>");
	    }
	}
	print "$_";
	
	# find the exact error code
	# 
	if ($_ =~ /L\"$err_code.*/) {
	    $found = 1;

	    # print a mark to highlight this line
	    #
	    print "</b>";
	}
	print "\n";

    }
}

if ($found == 0) {
    print "\nError code $err_code not found in ErrorMessages.h\n";
}

# print the end message
#
print ("$DELETED_STRING");
print ("//\n// end of file\n\n");
print ("</pre>\n");

$file_to_cat = '/templates/general/footer/footer.html';
&cat_file;

# main program exit
#

# cat_file:  list the file - simulate the server-side #include
#
# set $file_to_cat to file name and then call &cat_file
#
sub cat_file {

# open the file
#
open(FP1, "/ftp/pub$file_to_cat") or print "File \"/ftp/pub$file_to_cat\" could not be opened: $!\n\n";

while (<FP1>) {
    chop();
    print "$_\n";
    }

}

#
# end of file
