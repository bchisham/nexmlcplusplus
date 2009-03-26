#!/usr/bin/perl -w
#Brandon Chisham
#25 March 2009
#Script to generate swig interfaces from header files

use strict;
#find all the headers in the project
my $headers=`find * | grep "hpp\$"`;
my @split_head = split /[ \t\n]/, $headers;
#specify where the swig interface will go
my $swig_dir = "swig";
#specify the name of the swig header
my $meta_header = "swig.hpp";
#specify the name of the module
my $module_name = "nexml";
#specify the name of the interface file.
my $ifacefile = $module_name . ".i";

#make a header that includes everything 
open OUTFILE, ">$swig_dir/$meta_header" or die "Unable to open file $meta_header for writing $!\n";
print OUTFILE "#ifndef SWIG_HPP_\n";
print OUTFILE "#define SWIG_HPP_\n";
print OUTFILE "/*Created by make_swig_interfaces.pl */\n";
print OUTFILE "/*\n Generated on: " . `date` . "*/\n";
print OUTFILE "/*Report problems to: bchisham\@cs.nmsu.edu */\n";
foreach my $header (@split_head) {
   print OUTFILE "#include \"../$header\"\n";
}
print OUTFILE "#endif\n";
close OUTFILE;

#Make the interface file.
open OUTFILE, ">$swig_dir/$ifacefile" or die "Unable to open file $ifacefile for writing $!\n";
print OUTFILE "%module nexml\n";
print OUTFILE "%{\n";
print OUTFILE "#include \"$meta_header\"\n";
print OUTFILE "%}\n";
print OUTFILE "#include \"$meta_header\"\n";
close OUTFILE;
