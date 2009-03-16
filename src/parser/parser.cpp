#include "parser.hpp"

#include <iostream>
#include <cassert>

#include "../annotation.hpp"
#include "../cell.hpp"
#include "../character.hpp"
#include "../characters.hpp"
#include "../edge.hpp"
#include "../format.hpp"
#include "../id.hpp"
#include "../matrix.hpp"
#include "../network.hpp"
#include "../node.hpp"
#include "../otu.hpp"
#include "../otus.hpp"
#include "../state.hpp"
#include "../states.hpp"
#include "../tree.hpp"

//root processing.
static NeXML::Nexml* process_root( xmlpp::Node* node );
//First level processing
static NeXML::Characters* process_characters( xmlpp::Node* node );
static NeXML::Tree*      process_tree( xmlpp::Node* node );
static NeXML::Network*   process_network( xmlpp::Node* node );
//Next-level of heirarchy
static NeXML::Format* process_format( xmlpp::Node* node );
static NeXML::States* process_states( xmlpp::Node* node );
static NeXML::Matrix* process_matrix( xmlpp::Node* node );

static NeXML::Row* process_row( xmlpp::Node* node );
//lowest level
static NeXML::Node* process_node( xmlpp::Node* node );
static NeXML::Edge* process_edge( xmlpp::Node* node );

static NeXML::State* process_state( xmlpp::Node* node );
static NeXML::Character*   process_char( xmlpp::Node* node );

static NeXML::Cell* process_cell( xmlpp::Node* node );

static NeXML::Annotation* process_annotation( xmlpp::Node* node );


NeXML::Nexml* NeXML::DOM_PARSER::parser( const Glib::ustring& src ){
   try {
     xmlpp::DomParser parser;
     xmlpp::Node* parse_tree;
     //parser.set_validate();
     //parser.set_substitute_entities();

     parser.parse_file( src );

     if ( parser ){
       xmlpp::Node* parsetree = parser.get_document()->get_root_node();
        NeXML::Nexml* nexml_doc =  process_root( parsetree );
        return nexml_doc;
     }
   }
   catch ( const std::exception& ex){
     std::cerr << "Caught exception: " << ex.what() << std::endl;
   }
   return NULL;
}


NeXML::Nexml* process_root( xmlpp::Node* node ){
  NeXML::Nexml* ret = new NeXML::Nexml();
   
  

  return ret;
}

NeXML::Characters* process_characters( xmlpp::Node* node ){ return NULL; }
NeXML::Tree*      process_tree( xmlpp::Node* node ){ return NULL; }
NeXML::Network*   process_network( xmlpp::Node* node ){ return NULL; }

NeXML::Format* process_format( xmlpp::Node* node ){ return NULL; }
NeXML::States* process_states( xmlpp::Node* node ){ return NULL; }
NeXML::Matrix* process_matrix( xmlpp::Node* node ){ return NULL; }

NeXML::Row* process_row( xmlpp::Node* node ){ return NULL; }
//lowest level
NeXML::Node* process_node( xmlpp::Node* node ){ return NULL; }
NeXML::Edge* process_edge( xmlpp::Node* node ){ return NULL; }

NeXML::State* process_state( xmlpp::Node* node ){ return NULL; }
NeXML::Character*   process_char( xmlpp::Node* node ){ return NULL; }

NeXML::Cell* process_cell( xmlpp::Node* node ){ return NULL; }

NeXML::Annotation* process_annotation( xmlpp::Node* node ){ return NULL; }

