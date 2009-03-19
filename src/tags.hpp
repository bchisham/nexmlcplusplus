#ifndef TAGS_HPP_
#define TAGS_HPP_
#include <glibmm/ustring.h>

/*
 * Brandon Chisham
 * 16 March 2009
 * Named constants for tags used in a NeXML file.
 */

namespace NeXML {

 const Glib::ustring ANNOTATION_TAG = "meta";
 const Glib::ustring CHAR_TAG       = "char";
 const Glib::ustring CHARACTERS_TAG = "characters";
 const Glib::ustring CELL_TAG       = "cell";
 const Glib::ustring EDGE_TAG       = "edge";
 const Glib::ustring FORMAT_TAG     = "format";
 const Glib::ustring MATRIX_TAG     = "matrix";
 const Glib::ustring MEMBER_TAG     = "member";
 const Glib::ustring NODE_TAG       = "node";
 const Glib::ustring NETWORK_TAG    = "network";
 const Glib::ustring OTUS_TAG       = "otus";
 const Glib::ustring OTU_TAG        = "otu";
 const Glib::ustring POLY_TAG       = "polymorphic_state_set";
 const Glib::ustring SEQ_TAG        = "seq";
 const Glib::ustring STATE_TAG      = "state";
 const Glib::ustring STATES_TAG     = "states";
 const Glib::ustring TREE_TAG       = "tree";
 const Glib::ustring UNCERT_TAG     = "uncertain_state_set";
 



}

#endif
