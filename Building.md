# Introduction #

This page describes how to build the NeXMLCpp library on a Linux system.
Other Unix-like systems should be similar.

# Building #

## Getting the Source ##
The download the latest [release.](http://code.google.com/p/nexmlcplusplus/downloads/list)

## Dependencies ##
  * [libxml++](http://libxmlplusplus.sourceforge.net/) for parsing XML
  * [gcrypt](http://www.gnupg.org/documentation/manuals/gcrypt/) for creating unique id's.
  * [gtkmm](http://www.gtkmm.org/) supplies a Unicode string library used by libxml++.
  * [NCL](https://sourceforge.net/projects/ncl/)**this currently isn't a dependency, but will be in the next versions that support NCL interoperability.**

## Compiling ##
  * Use the following command to unpack the source ```
tar -xzvf NeXMLCpp-0.00000001.tar.gz```
  * ```
cd NeXMLCpp-0.00000001```
  * ```
./configure```
  * ```
make```
  * ```
make install```