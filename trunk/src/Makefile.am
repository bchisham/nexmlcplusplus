INCLUDES=$(DEPS_CFLAGS)
AM_CXXFLAGS=`pkg-config glibmm-2.4 --cflags` `pkg-config libxml++-2.6 --cflags` `libgcrypt-config --cflags` `pkg-config nclv2.1 --cflags` -g -DEBUG_V -D_GNU_SOURCE

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
		       parser/parser.cpp \
		       ncl/nclnexml.cpp \
		       ncl/nclnexmltaxa.cpp \
		       ncl/nclnexmlmatrix.cpp \
		       ncl/nclnexmltree.cpp

libNeXMLCpp_la_LIBADD= $(DEPS_LIBS)
check_PROGRAMS = example_reader
TESTS= $(check_PROGRAMS)

example_reader_SOURCES = examples/example_reader.cpp
example_reader_LDFLAGS = `pkg-config glibmm-2.4 --libs` `pkg-config libxml++-2.6 --libs` `libgcrypt-config --libs` `pkg-config nclv2.1 --libs` libNeXMLCpp.la


