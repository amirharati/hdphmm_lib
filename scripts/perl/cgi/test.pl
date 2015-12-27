#!/usr/bin/perl
use CGI;
my $query= new CGI;
print $query->header;
print "hello people in my head\n";
