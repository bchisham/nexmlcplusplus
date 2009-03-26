#!/usr/bin/perl -w
#Brandon Chisham
#25 March 2009
#Script to generate swig interfaces from header files

use strict;
my $includes = "-I/usr/bin/include " . "-I/usr/lib64/gcc/x86_64-pc-linux-gnu/4.1.2/include/g++-v4 " . "/usr/lib64/gcc/x86_64-pc-linux-gnu/4.1.2/include/g++-v4/x86_64-pc-linux-gnu/bits " .`pkg-config glibmm-2.4 --cflags` . `pkg-config libxml++-2.6 --cflags` .`libgcrypt-config --cflags`. `pkg-config nclv2.1 --cflags`; 
my $headers=`find * | grep "hpp\$"`;
my @split_head = split /[ \t\n]/, $headers;
my $swig_dir = "swig";
my $meta_header = "swig.hpp";
my $module_name = "nexml";
my $ifacefile = $module_name . ".i";
#open OUTFILE, ">$swig_dir/$ifacefile" or die  "Unable to create interface file: \"$ifacefile\" error: \"$!\"";
#make a header that includes everything 
open OUTFILE, ">$swig_dir/$meta_header" or die "Unable to open file for writing $!\n";
print OUTFILE "#ifndef SWIG_HPP_\n";
print OUTFILE "#define SWIG_HPP_\n";
foreach my $header (@split_head) {
   print OUTFILE "#include \"../$header\"\n";
}
print OUTFILE "#endif\n";
close OUTFILE;
#Make the interface file.
open OUTFILE, ">$swig_dir/$ifacefile" or die "Unable to open file for writing $!\n";
print OUTFILE "%module nexml\n";
print OUTFILE "%{\n";
print OUTFILE "#include \"$meta_header\"\n";
print OUTFILE "%}\n";
print OUTFILE "#include \"$meta_header\"\n";
close OUTFILE;

