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
//<------------------Tool-kit for walking the parse tree------------->
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
static void          process_member( xmlpp::Node* node, NeXML::StateSet* stateset );
//process a character declaraction.
static NeXML::Character*   process_char( xmlpp::Node* node );
//process a cell.
static NeXML::Cell* process_cell( xmlpp::Node* node );
//process an annotation element.
static NeXML::Annotation* process_annotation( xmlpp::Node* node );
static NeXML::Otu* process_otu( xmlpp::Node* node );
//<-------Keep some info handy while parsing----------------->
//Elements compute their own id's based on their contents which
//might not match up with the id's they have in the original document.
static map< Glib::ustring, NeXML::State* > states_processed_;
static map< Glib::ustring, NeXML::Character* > chars_processed_;
static map< Glib::ustring, NeXML::States* > states_blocks_processed_;
static map< Glib::ustring, NeXML::Network* > trees_processed_;
static map< Glib::ustring, NeXML::Node* > nodes_processed_;
static map< Glib::ustring, NeXML::Otu* > otus_processed_;
//<---------------------------------------------------------->
/*
 * Set things up and start walking the parse tree.
 */
NeXML::Nexml* NeXML::DOM_PARSER::parser( const Glib::ustring& src ){
   try {
     //initialize
     states_processed_ = map< Glib::ustring, NeXML::State* >();
     chars_processed_ = map< Glib::ustring, NeXML::Character* >();
     states_blocks_processed_ = map< Glib::ustring, NeXML::States* >();
     trees_processed_ = map< Glib::ustring, NeXML::Network* >();
     nodes_processed_ = map< Glib::ustring, NeXML::Node* >();
     otus_processed_ = map< Glib::ustring, NeXML::Otu* >();

     xmlpp::DomParser parser;
     xmlpp::Node* parse_tree;
     //parser.set_validate();
     //parser.set_substitute_entities();
     
     //parse and process
     parser.parse_file( src );
     if ( parser ){
       //parsing was successful
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
/*
 * Handle processing of the document root. 
 */
NeXML::Nexml* process_root( xmlpp::Node* node ){
  if (node){
     NeXML::Nexml* ret = new NeXML::Nexml();
     xmlpp::Node::NodeList list = node->get_children();
     //process child elements. we expect otus, characters (matrices), trees, and maybe annotations.
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
/*
 * Handle processing of the otus block. 
 */
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
/*
 * Processes a single otu.
 */
NeXML::Otu* process_otu( xmlpp::Node* node ){
  if ( node ){
     ustring label = dynamic_cast< xmlpp::Element* >( node )->get_attribute( "label" )->get_value();
     ustring id    = dynamic_cast< xmlpp::Element* >( node )->get_attribute( "id" )->get_value();
     NeXML::Otu* ret = new NeXML::Otu( label );
     otus_processed_[ id ] = ret;
     return ret;
  }
  return NULL;
}
/*
 * Process a characters block.
 */
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
/*
 * process the tress block.
 */
NeXML::Trees* process_trees( xmlpp::Node* node, const NeXML::Otus* otus ){
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
/*
 * Process a single tree.
 */
NeXML::Tree* process_tree( xmlpp::Node* node ){ 
  if (node){
    //reset the nodes map.
    nodes_processed_ = map< Glib::ustring, NeXML::Node* >();

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
/*
 * Process a network
 */
NeXML::Network* process_network( xmlpp::Node* node ){ 
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
/*
 * Process a format block
 */
NeXML::Format* process_format( xmlpp::Node* node ){ 
  if (node){
    NeXML::Format* ret = new NeXML::Format();
    xmlpp::Node::NodeList l = node->get_children();
    for ( xmlpp::Node::NodeList::iterator i = l.begin(); i != l.end(); ++i ){
        if ((*i)->get_name() == NeXML::STATES_TAG){
            ret->setstates( process_states( *i) );
        } 
        else if ((*i)->get_name() == NeXML::CHAR_TAG){
             ret->addchar( process_char( *i ) );
        }
        else if ((*i)->get_name() == NeXML::ANNOTATION_TAG){
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
/*
 * Process a states block
 */
NeXML::States* process_states( xmlpp::Node* node ){ 
  if (node){
    xmlpp::Node::NodeList l = node->get_children();
    Glib::ustring id = dynamic_cast< xmlpp::Element* >( node )->get_attribute( "id" )->get_value();
    NeXML::States* ret = new NeXML::States( id );
    states_blocks_processed_[ id ] = ret;
    for ( xmlpp::Node::NodeList::iterator i = l.begin(); i != l.end(); ++i ){
         ret->addstate( process_state( *i ) );
    }

  }
  return NULL; 
}
/*
 * Process a matrix.
 */
NeXML::Matrix* process_matrix( xmlpp::Node* node ){ 
  if (node){
     xmlpp::Node::NodeList l = node->get_children();
     NeXML::Matrix* mat = new NeXML::Matrix();
     for ( xmlpp::Node::NodeList::iterator i = l.begin(); i != l.end(); ++i ){
        if ( (*i)->get_name() == NeXML::ROW_TAG ){
           mat->addrow( process_row( *i ) );
        }
        else if ( (*i)->get_name() == NeXML::ANNOTATION_TAG ){
           mat->addannotation( process_annotation( *i ) );
        }
        else {
           std::cerr << "Unknown element: " << (*i)->get_name() << std::endl;
        }
     }
     return mat;
  }
  return NULL; 
}
/*
 * Process a single row.
 */
NeXML::Row* process_row( xmlpp::Node* node ){ 
  if (node){
       if (xmlpp::Element* ele = dynamic_cast< xmlpp::Element* >( node )){
            NeXML::Otu* otu = otus_processed_[ ele->get_attribute( "otu" )->get_value() ];
            xmlpp::Attribute* lab = ele->get_attribute( "label" );
            ustring label = "";
            if (lab){  label = lab->get_value(); }
            NeXML::Row* ret = new NeXML::Row( otu, label );
            xmlpp::Node::NodeList l = node->get_children();
            for ( xmlpp::Node::NodeList::iterator i = l.begin(); i != l.end(); ++i ){
                ret->addcell( process_cell( *i ) );
            }
            return ret;
       }
  }
  return NULL;
}
//lowest level
/*
 * Process a single node.
 */
NeXML::Node* process_node( xmlpp::Node* node ){ 
  if (node){
     if (xmlpp::Element* ele = dynamic_cast< xmlpp::Element* >( node )){
       ustring id = ele->get_attribute( "id" )->get_value();
       //get optional attributes
       xmlpp::Attribute* label = ele->get_attribute( "label" );
       xmlpp::Attribute* otu   = ele->get_attribute( "otu"   );
       xmlpp::Attribute* isroot = ele->get_attribute( "root" );
       NeXML::Otu* otup;
       ustring labelstr = "";
       bool root = false;
       if ( label ){ labelstr = label->get_value(); }
       if ( otu ){ otup = otus_processed_[ otu->get_value() ]; }
       if ( isroot ){ root = isroot->get_value() == "true"; }
       NeXML::Node* ret = new NeXML::Node( labelstr, otup, root );
       nodes_processed_[ id ] = ret;
       return ret;
     }
  }
  return NULL; 
}
/*
 * Process a single edge.
 */
NeXML::Edge* process_edge( xmlpp::Node* node ){ 
  if (node){
       if (xmlpp::Element* ele = dynamic_cast< xmlpp::Element* >(node)){
            NeXML::Node* src = nodes_processed_[ ele->get_attribute("source")->get_value() ];
            NeXML::Node* target = nodes_processed_[ ele->get_attribute("target")->get_value() ];
            xmlpp::Attribute* len = ele->get_attribute( "length" );
            ustring length = "";
            if (len){ length = len->get_value(); }
            NeXML::Edge* ret = new NeXML::Edge( src, target, length);
            return ret;
       }
  }
  return NULL;
}
/*
 * Process a rootedge.
 */
NeXML::Edge* process_rootedge( xmlpp::Node* node ){
  if ( node ){

  }
  return NULL;
}
/*
 * Process a state.
 */
NeXML::State* process_state( xmlpp::Node* node ){ 
  NeXML::State* ret = NULL;
  if (node){
    xmlpp::Element* ele = dynamic_cast< xmlpp::Element* >( node );
        if ( ele ){
       Glib::ustring id = ele->get_attribute( "id" )->get_value();
       Glib::ustring symbol = ele->get_attribute( "symbol" )->get_value();
       if (node->get_name() == NeXML::POLY_TAG){
          ret = new NeXML::PolymorphicState( id, symbol );
       }
       else if (node->get_name() == NeXML::UNCERT_TAG){
          ret = new NeXML::UncertainState( id, symbol );
       }
       else if ( node->get_name() == NeXML::STATE_TAG){
          ret = new NeXML::State( id, symbol );
          //add to the states symbol table.
          states_processed_[ id ] = ret;
       }
    }
  }
  return ret;
}
/*
 * Process a member element for polymorphic and uncertain states.
 */
void process_member( xmlpp::Node* node, NeXML::StateSet* stateset ){
  if (node && stateset){
    xmlpp::Node::NodeList l = node->get_children();
    for ( xmlpp::Node::NodeList::iterator i = l.begin(); i != l.end(); ++i ){
        Glib::ustring state = dynamic_cast< xmlpp::Element* >( *i )->get_attribute( "state" )->get_value();
        //link back to the previously processed state. 
        stateset->addstate( states_processed_[ state ] );
    }
  }
  return;
}
/*
 * Process a char element.
 */
NeXML::Character* process_char( xmlpp::Node* node ){ 
  if (node){
       if (xmlpp::Element* ele = dynamic_cast< xmlpp::Element* >(  node )){
          Glib::ustring id = ele->get_attribute( "id" )->get_value();
          Glib::ustring state = ele->get_attribute( "states" )->get_value();
          NeXML::Character* ret =  new NeXML::Character( states_blocks_processed_[ state ] );
          chars_processed_[ id ] = ret;
          return ret;
       }
  }
  return NULL;
}
/*
 * Process a cell.
 */
NeXML::Cell* process_cell( xmlpp::Node* node ){ 
  if (node){
      if (xmlpp::Element* ele = dynamic_cast< xmlpp::Element* >( node )){
           Glib::ustring ch = ele->get_attribute( "char" )->get_value();
           Glib::ustring st = ele->get_attribute( "state" )->get_value();
           NeXML::Cell* ret = new NeXML::Cell( chars_processed_[ch], states_processed_[ st ] );
           return ret;
      }
  }
  return NULL; 
}
/*
 * Process an annotation.
 */
NeXML::Annotation* process_annotation( xmlpp::Node* node ){ 
  if (node){

  }
  return NULL;
}

