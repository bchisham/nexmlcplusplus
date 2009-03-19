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
#include "../trees.hpp"
#include "../tags.hpp"

using namespace std;
using namespace Glib;

//root processing.
//Process the root/nexml node.
static NeXML::Nexml* process_root( xmlpp::Node* node );
//First level processing
//Process a characters block
static NeXML::Characters* process_characters( xmlpp::Node* node, const NeXML::Otus* );

static NeXML::Otus* process_otus( xmlpp::Node* );
//process trees
static NeXML::Trees*     process_trees( xmlpp::Node* node, const NeXML::Otus* );
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
static NeXML::Edge* process_rootedge( xmlpp::Node* node );
//process a state definition element.
static NeXML::State* process_state( xmlpp::Node* node );
//process a character declaraction.
static NeXML::Character*   process_char( xmlpp::Node* node );
//process a cell.
static NeXML::Cell* process_cell( xmlpp::Node* node );
//process an annotation element.
static NeXML::Annotation* process_annotation( xmlpp::Node* node );
static NeXML::Otu* process_otu( xmlpp::Node* node );


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
         if ((*it)->get_name() == NeXML::OTUS_TAG){
            //add the otus block to the document.
            ret->setotus( process_otus( *it ) );
         } else if ((*it)->get_name() == NeXML::CHARACTERS_TAG ){
            //add the matrix and attached characters and states definitions
            ret->addmatrix( process_characters( *it, ret->getotus() ) );
         } else if ((*it)->get_name() == NeXML::TREES_TAG ){
            //add the tree. 
            ret->settrees( process_trees( *it, ret->getotus() ));
         } else if ((*it)->get_name() == NeXML::ANNOTATION_TAG ){
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

static NeXML::Otus* process_otus( xmlpp::Node* node ){
  if ( node ){
    ustring id = dynamic_cast< xmlpp::Element* >( node )->get_attribute( "id" )->get_value();
    NeXML::Otus* ret = new NeXML::Otus();
    xmlpp::Node::NodeList list = node->get_children();
    for ( xmlpp::Node::NodeList::iterator it = list.begin(); it != list.end(); ++it ){
       if ( (*it)->get_name() == NeXML::OTU_TAG ){
           ret->addotu( process_otu( *it ) );
       }
       else if ( (*it)->get_name() == NeXML::ANNOTATION_TAG ){
           ret->addannotation( process_annotation( *it ) );
       }
       else {
       
       }
    }
    return ret;
  }
  return NULL;
}

NeXML::Otu* process_otu( xmlpp::Node* node ){
  if ( node ){
     ustring label = dynamic_cast< xmlpp::Element* >( node )->get_attribute( "label" )->get_value();
     NeXML::Otu* ret = new NeXML::Otu( label );
     return ret;
  }
  return NULL;
}


NeXML::Characters* process_characters( xmlpp::Node* node, const NeXML::Otus* otus ){ 
  if (node){
    //get the type of characters type
    ustring type = dynamic_cast< xmlpp::Element* >( node )->get_attribute( "type" )->get_value();
    NeXML::Characters* ret = new NeXML::Characters(type, otus);
    xmlpp::Node::NodeList list = node->get_children();
    //process the children
    for ( xmlpp::Node::NodeList::iterator it = list.begin(); it != list.end(); ++it ){
      if ( (*it)->get_name() == NeXML::FORMAT_TAG ){
         ret->setformat( process_format( *it ) );
      } else if ( (*it)->get_name() == NeXML::MATRIX_TAG ){
         ret->setmatrix( process_matrix( *it ) );
         
      } else if ( (*it)->get_name() == NeXML::ANNOTATION_TAG ){
          ret->addannotation( process_annotation( *it ) );
      } else {
         std::cerr << "Unknown element: " << (*it)->get_name() << std::endl;
      }
    }
     return ret;
  }
  return NULL; 
}

NeXML::Trees*     process_trees( xmlpp::Node* node, const NeXML::Otus* otus ){
    if ( node ){
        NeXML::Trees* ret = new NeXML::Trees( otus );
        xmlpp::Node::NodeList list = node->get_children();
        for ( xmlpp::Node::NodeList::iterator i = list.begin(); i != list.end(); ++i ){
          if ( (*i)->get_name() == NeXML::TREE_TAG ){
             ret->addgraph( process_tree( *i ) );
           }
          else if ((*i)->get_name() == NeXML::NETWORK_TAG ){
              ret->addgraph( process_network( *i ) );
          }
          else if ( (*i)->get_name() == NeXML::ANNOTATION_TAG ){
             ret->addannotation( process_annotation( *i ) );
          }
          else {
              std::cerr << "Unknown element: " << (*i)->get_name() << std::endl;
          }
        }
        return ret;
    }
    return NULL;
}

NeXML::Tree*      process_tree( xmlpp::Node* node ){ 
  if (node){
    ustring type = dynamic_cast< xmlpp::Element* >( node )->get_attribute( "type" )->get_value();
    ustring label = dynamic_cast< xmlpp::Element* >( node )->get_attribute( "label" )->get_value();
    NeXML::Tree* ret = new NeXML::Tree(label, type);
    xmlpp::Node::NodeList l = node->get_children();
    for (xmlpp::Node::NodeList::iterator i = l.begin(); i != l.end(); ++i ){
        if ( (*i)->get_name() == NeXML::NODE_TAG){
             ret->addnode( process_node( *i ) );
        } else if ( (*i)->get_name() == NeXML::EDGE_TAG ){
             ret->addedge( process_edge( *i ) );
        }
        else if  ( (*i)->get_name() == NeXML::ROOTEDGE_TAG ){
              ret->addedge( process_rootedge( *i ) );
        }
        else if ( (*i)->get_name() == NeXML::ANNOTATION_TAG){
              ret->addannotation( process_annotation( *i ) );
        }
        else {
           std::cerr << "Unknown element: " << (*i)->get_name() << std::endl;
        }
    }

  }
  return NULL; 
}
NeXML::Network*   process_network( xmlpp::Node* node ){ 
  if (node){
  ustring type = dynamic_cast< xmlpp::Element* >( node )->get_attribute( "type" )->get_value();
    ustring label = dynamic_cast< xmlpp::Element* >( node )->get_attribute( "label" )->get_value();
    NeXML::Network* ret = new NeXML::Network(label, type);
    xmlpp::Node::NodeList l = node->get_children();
    for (xmlpp::Node::NodeList::iterator i = l.begin(); i != l.end(); ++i ){
        if ( (*i)->get_name() == NeXML::NODE_TAG){
             ret->addnode( process_node( *i ) );
        } else if ( (*i)->get_name() == NeXML::EDGE_TAG ){
             ret->addedge( process_edge( *i ) );
        }
        else if  ( (*i)->get_name() == NeXML::ROOTEDGE_TAG ){
              ret->addedge( process_rootedge( *i ) );
        }
        else if ( (*i)->get_name() == NeXML::ANNOTATION_TAG){
              ret->addannotation( process_annotation( *i ) );
        }
        else {
           std::cerr << "Unknown element: " << (*i)->get_name() << std::endl;
        }
    }

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

NeXML::Edge* process_rootedge( xmlpp::Node* node ){

  if ( node ){

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

