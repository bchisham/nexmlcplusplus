
AM_CXXFLAGS=`pkg-config glibmm-2.4 --cflags` `pkg-config libxml++-2.6 --cflags` `libgcrypt-config --cflags` -g -DEBUG_V

lib_LTLIBRARIES=libNeXMLCpp.la
libNeXMLCpp_la_SOURCES=annotation.cpp \
                       character.cpp \
		       characters.cpp \
		       edge.cpp \
		       format.cpp \
		       id.cpp \
		       row.cpp \
		       cell.cpp \
		       matrix.cpp  \
		       network.cpp \
		       nexml.cpp \
		       node.cpp \
		       otu.cpp \
		       otus.cpp \
		       state.cpp \
		       states.cpp \
		       tree.cpp \
		       trees.cpp \
		       util/makeid.cpp \
		       parser/parser.cpp

check_PROGRAMS = example_reader
TESTS= $(check_PROGRAMS)

example_reader_SOURCES = examples/example_reader.cpp
example_reader_LDFLAGS = `pkg-config glibmm-2.4 --libs` `pkg-config libxml++-2.6 --libs` `libgcrypt-config --libs` libNeXMLCpp.la


