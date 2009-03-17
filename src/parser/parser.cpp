#include "parser.hpp"

#include <iostream>
#include <cassert>
#include <map>

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

using namespace std;
using namespace Glib;

//root processing.
//Process the root/nexml node.
static NeXML::Nexml* process_root( xmlpp::Node* node );
//First level processing
//Process a characters block
static NeXML::Characters* process_characters( xmlpp::Node* node, NeXML::Otus* );

static NeXML::Otus* process_otus( xmlpp::Node* );

//process a tree.
static NeXML::Tree*      process_tree( xmlpp::Node* node );
//process a network
static NeXML::Network*   process_network( xmlpp::Node* node );
//Next-level of heirarchy
//process a format block
static NeXML::Format* process_format( xmlpp::Node* node );
//process a states block
static NeXML::States* process_states( xmlpp::Node* node );
//process a matrix block
static NeXML::Matrix* process_matrix( xmlpp::Node* node );
//process a matrix row
static NeXML::Row* process_row( xmlpp::Node* node );
//lowest level
//process an node element. 
static NeXML::Node* process_node( xmlpp::Node* node );
//process an edge element.
static NeXML::Edge* process_edge( xmlpp::Node* node );
//process a state definition element.
static NeXML::State* process_state( xmlpp::Node* node );
//process a character declaraction.
static NeXML::Character*   process_char( xmlpp::Node* node );
//process a cell.
static NeXML::Cell* process_cell( xmlpp::Node* node );
//process an annotation element.
static NeXML::Annotation* process_annotation( xmlpp::Node* node );

static const ustring ANNOTATION_TAG = "meta";
static const ustring CHAR_TAG       = "char";
static const ustring CHARACTERS_TAG = "characters";
static const ustring CELL_TAG       = "cell";
static const ustring EDGE_TAG       = "edge";
static const ustring FORMAT_TAG     = "format";
static const ustring MATRIX_TAG     = "matrix";
static const ustring NODE_TAG       = "node";
static const ustring NETWORK_TAG    = "network";
static const ustring OTUS_TAG       = "otus";
static const ustring OTU_TAG        = "otu";
static const ustring TREE_TAG       = "tree";




NeXML::Nexml* NeXML::DOM_PARSER::parser( const Glib::ustring& src ){
   try {
     //initialize
     xmlpp::DomParser parser;
     xmlpp::Node* parse_tree;
     //parser.set_validate();
     //parser.set_substitute_entities();
     
     //parse and process
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
  if (node){
     NeXML::Nexml* ret = new NeXML::Nexml();
     xmlpp::Node::NodeList list = node->get_children();
     for (xmlpp::Node::NodeList::iterator it = list.begin(); it != list.end(); ++it ){
         //process children.
         if ((*it)->get_name() == OTUS_TAG){
            //add the otus block to the document.
            ret->setotus( process_otus( *it ) );
         } else if ((*it)->get_name() == CHARACTERS_TAG ){
            //add the matrix and attached characters and states definitions
            ret->addmatrix( process_characters( *it, ret->getotus() ) );
         } else if ((*it)->get_name() == TREE_TAG ){
            //add the tree. 
            ret->addtree( process_tree( *it ));
         } else if ((*it)->get_name() == NETWORK_TAG ){
           //add the network.
           ret->addnetwork( process_network( *it ));
         } else if ((*it)->get_name() == ANNOTATION_TAG ){
            //add the annotation.
            ret->addannotation( process_annotation( *it ) );
         } else {
             std::cerr << "Unknown element: " << (*it)->get_name() << std::endl;
         }
     }

     return ret;
  }
  return NULL;
}

static NeXML::Otus* process_otus( xmlpp::Node* ){
   
  return NULL;
}


NeXML::Characters* process_characters( xmlpp::Node* node, NeXML::Otus* otus ){ 
  if (node){
    //get the type of characters type
    ustring type = dynamic_cast< xmlpp::Element* >( node )->get_attribute( "type" )->get_value();
    NeXML::Characters* ret = new NeXML::Characters(type, otus);
    xmlpp::Node::NodeList list = node->get_children();
    //process the children
    for ( xmlpp::Node::NodeList::iterator it = list.begin(); it != list.end(); ++it ){
      if ( (*it)->get_name() == FORMAT_TAG ){
         ret->setformat( process_format( *it ) );
      } else if ( (*it)->get_name() == MATRIX_TAG ){
         ret->setmatrix( process_matrix( *it ) );
         
      } else if ( (*it)->get_name() == ANNOTATION_TAG ){
          ret->addannotation( process_annotation( *it ) );
      } else {
         std::cerr << "Unknown element: " << (*it)->get_name() << std::endl;
      }
    }
     return ret;
  }
  return NULL; 
}
NeXML::Tree*      process_tree( xmlpp::Node* node ){ 
  if (node){
       
  }
  return NULL; 
}
NeXML::Network*   process_network( xmlpp::Node* node ){ 
  if (node){

  }
  return NULL; 
}

NeXML::Format* process_format( xmlpp::Node* node ){ 
  if (node){

  }
  return NULL; 
}
NeXML::States* process_states( xmlpp::Node* node ){ 
  if (node){

  }
  return NULL; 
}
NeXML::Matrix* process_matrix( xmlpp::Node* node ){ 
  if (node){

  }
  return NULL; 
}

NeXML::Row* process_row( xmlpp::Node* node ){ 
  if (node){

  }
  return NULL;
}
//lowest level
NeXML::Node* process_node( xmlpp::Node* node ){ 
  if (node){

  }
  return NULL; 
}
NeXML::Edge* process_edge( xmlpp::Node* node ){ 
  if (node){

  }
  return NULL;
}

NeXML::State* process_state( xmlpp::Node* node ){ 
  if (node){
  
  
  }
  return NULL;
}
NeXML::Character*   process_char( xmlpp::Node* node ){ 
  if (node){

  }
  return NULL;
}

NeXML::Cell* process_cell( xmlpp::Node* node ){ 
  if (node){

  }
  return NULL; 
}

NeXML::Annotation* process_annotation( xmlpp::Node* node ){ 
  if (node){

  }
  return NULL;
}

