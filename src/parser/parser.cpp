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

static NeXML::Otus* process_otus( xmlpp::NodeSet nodes );
//process trees
static NeXML::Trees*     process_trees( xmlpp::NodeSet nodes, const NeXML::Otus* );
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
  NeXML::Nexml* ret = NULL;
  if (node){
     ret = new NeXML::Nexml();

#ifdef EBUG_V
    cerr << "process_root( node: " << node->get_name() << " path: "<< node->get_path() <<")" << endl;
  //  cerr << "preparing to process the following children...\n";
   // xmlpp::Node::NodeList l = node->get_children();
  //  for (xmlpp::Node::NodeList::iterator i = l.begin(); i != l.end(); ++i){
  //     cerr << (*i)->get_namespace_prefix() << ":" <<(*i)->get_name()  << " path: " << (*i)->get_path() << endl;
  //  }
#endif
    xmlpp::NodeSet otus = node->find(  "descendant::*[name()='"+ NeXML::OTUS_TAG+"']" );
#ifdef EBUG_V
    cerr << "found " << otus.size() << " otus" << endl;
#endif
     ret ->setotus( process_otus( otus ) );
#ifdef EBUG_V
     cerr << "processed the otus!\n";
     cerr << "otus addr: " << (void*)(ret->getotus()) << "\n";
#endif
     ret->settrees( process_trees( node->find("descendant::*[name()='" + NeXML::TREES_TAG + "']"), ret->getotus() ) );
 
#ifdef EBUG_V
      cerr << "processed the trees!\n";
#endif
 
     xmlpp::NodeSet matrices = node->find( "descendant::*[name()='" + NeXML::CHARACTERS_TAG + "']");

#ifdef EBUG_V
    cerr << "Found: " << matrices.size() << " matrices, processing....\n";
#endif

     for (xmlpp::NodeSet::iterator it = matrices.begin(); it != matrices.end(); ++it){
          ret->addmatrix( process_characters(*it, ret->getotus()) );
     }
#ifdef EBUG_V
     cerr << "Processed Matrices!\n";
#endif
     }
     return ret;
  }
 /*
 * Handle processing of the otus block. 
 */
static NeXML::Otus* process_otus( xmlpp::NodeSet nodes ){
  NeXML::Otus* ret = NULL;
  if (nodes.size() ){
     ret = new NeXML::Otus();
     xmlpp::NodeSet otu_defs = nodes.at( 0 )->find( "descendant::*[name()='" + NeXML::OTU_TAG + "']" );
     for (xmlpp::NodeSet::iterator it = otu_defs.begin(); it != otu_defs.end(); ++it){
#ifdef EBUG_V_OTUS
       cerr << "processing node: " << (*it)->get_name() << "\n";
#endif
            ret->addotu( process_otu( *it ) );
     }
  }
  return ret;
}
/*
 * Processes a single otu.
 */
NeXML::Otu* process_otu( xmlpp::Node* node ){
  NeXML::Otu* ret = NULL;
  if ( node ){
#ifdef EBUG_V_OTU
    cerr << "process_otu( node: " << node->get_name() << ")" << endl;
#endif

    if (xmlpp::Element* ele = dynamic_cast< xmlpp::Element* >( node ) ){
      xmlpp::Attribute* labelattr = ele->get_attribute("label");
      xmlpp::Attribute* idattr    = ele->get_attribute( "id" );
      if ( idattr && labelattr ){
        Glib::ustring label = labelattr->get_value(); 
        ret = new NeXML::Otu( label );
#ifdef EBUG_V_OTU
        cerr << "processed otu id: \"" << idattr->get_value() << "\" label: \"" << label << "\"" <<endl;
#endif
        otus_processed_[ idattr->get_value() ] = ret;
      }
    }
  }
    return ret;
}
/*
 * Process a characters block.
 */
NeXML::Characters* process_characters( xmlpp::Node* node, const NeXML::Otus* otus ){ 
  NeXML::Characters* ret = NULL;
  if (node){
    if (xmlpp::Element* ele = dynamic_cast< xmlpp::Element* >( node ) ){
      if (xmlpp::Attribute* typeattr = ele->get_attribute( "type" ) ){
        //size 1
        xmlpp::NodeSet format = node->find( "descendant::*[name()='"  + NeXML::FORMAT_TAG + "']" );
        //size 1
        xmlpp::NodeSet matrix = node->find(  "descendant::*[name()='"  + NeXML::MATRIX_TAG + "']" );
        //may be several annotations.
        xmlpp::NodeSet annotations = node->find("descendant::*[name()='"  + NeXML::ANNOTATION_TAG + "']");
        //only process if required elements are present.
        if (format.size() && matrix.size()){
          //get the type of characters type
          ustring type = typeattr->get_value();
          ret = new NeXML::Characters(type, otus);
          xmlpp::Node::NodeList list = node->get_children();
          ret->setformat( process_format( format.at( 0 ) ) );
          ret->setmatrix( process_matrix( matrix.at( 0 ) ) );
          for (xmlpp::NodeSet::iterator it = annotations.begin(); it != annotations.end(); ++it){
             ret->addannotation( process_annotation( *it ) );
          }
        }
      }
    }
  }
  return ret; 
}
/*
 * process the tress block.
 */
NeXML::Trees* process_trees( xmlpp::NodeSet nodes, const NeXML::Otus* otus ){
  NeXML::Trees* ret = NULL;
   if ( nodes.size() ){

#ifdef EBUG_V
     cerr << "process_trees( set_size: " << nodes.size() << ", otus: " << otus << ")" << endl;
#endif

        ret = new NeXML::Trees( otus );
        //xmlpp::Node::NodeList list = node.at( 0 )->get_children();
        xmlpp::NodeSet trees = nodes.at( 0 )->find( "descendant::*[name()='"  + NeXML::TREE_TAG + "']");
        xmlpp::NodeSet networks = nodes.at( 0 )->find( "descendant::*[name()='"  + NeXML::NETWORK_TAG + "']");
        xmlpp::NodeSet annotations = nodes.at( 0 )->find( "descendant::*[name()='" + NeXML::ANNOTATION_TAG + "']" );
#ifdef EBUG_V
        cerr << "Found trees: " << trees.size() << " networks: " << networks.size() << " notes: " << annotations.size() << ", processing....." << endl;
#endif

        //process trees
        for (xmlpp::NodeSet::iterator it = trees.begin(); it != trees.end(); ++it){
             ret->addgraph( process_tree( *it ) );
        }
#ifdef EBUG_V
        cerr << "Processed Trees starting networks" << endl;
#endif
        //process networks
        for ( xmlpp::NodeSet::iterator it = networks.begin(); it != networks.end(); ++it ){
             ret->addgraph( process_network( *it ) );
        }
#ifdef EBUG_V
        cerr << "Processed Networks processing notes" << endl;
#endif
        //process annotations
        for ( xmlpp::NodeSet::iterator it = annotations.begin(); it != annotations.end(); ++it){
             ret->addannotation( process_annotation( *it ) );
        }
#ifdef EBUG_V
        cerr << "Processed notes returning\n";
#endif
    }
    return ret;
}
/*
 * Process a single tree.
 */
NeXML::Tree* process_tree( xmlpp::Node* node ){ 
  NeXML::Tree* ret = NULL;
  if (node){
    //reset the nodes map.
    nodes_processed_ = map< Glib::ustring, NeXML::Node* >();
    
    if (xmlpp::Element* ele = dynamic_cast< xmlpp::Element* >( node )){
        xmlpp::Attribute* typeattr = ele->get_attribute( "type" );
        xmlpp::Attribute* labelattr = ele->get_attribute( "label" );
        if ( typeattr && labelattr ){
             ustring type = typeattr->get_value();
             ustring label = labelattr->get_value();
             ret = new NeXML::Tree(label, type);
             xmlpp::NodeSet nodes = node->find("descendant::*[name()='" + NeXML::NODE_TAG + "']" );
             xmlpp::NodeSet edges = node->find("descentant::*[name()='" + NeXML::EDGE_TAG + "']");
             xmlpp::NodeSet rootedge = node->find("descendant::*[name()='" + NeXML::ROOTEDGE_TAG + "']" );
             xmlpp::NodeSet annotations = node->find("descendant::*[name()='" + NeXML::ANNOTATION_TAG + "']");
             
             for (xmlpp::NodeSet::iterator it = nodes.begin(); it != nodes.end(); ++it){
                 ret->addnode( process_node( *it ));
             }
             for (xmlpp::NodeSet::iterator it = edges.begin(); it != edges.end(); ++it){
                 ret->addedge( process_edge( *it ) );
             }
             for (xmlpp::NodeSet::iterator it = rootedge.begin(); it != rootedge.end(); ++it ){
                 ret->addedge( process_rootedge( *it ) );
             }
             for (xmlpp::NodeSet::iterator it = annotations.begin(); it != annotations.end(); ++it){
                 ret->addannotation( process_annotation( *it ) );
             }

         }
    }
  }
  return ret; 
}
/*
 * Process a network
 */
NeXML::Network* process_network( xmlpp::Node* node ){ 

 NeXML::Network* ret = NULL;
 if (node){
 //reset the nodes map.
    nodes_processed_ = map< Glib::ustring, NeXML::Node* >();
    
    if (xmlpp::Element* ele = dynamic_cast< xmlpp::Element* >( node )){
        xmlpp::Attribute* typeattr = ele->get_attribute( "type" );
        xmlpp::Attribute* labelattr = ele->get_attribute( "label" );
        if ( typeattr && labelattr ){
             ustring type = typeattr->get_value();
             ustring label = labelattr->get_value();
             ret = new NeXML::Network(label, type);
             xmlpp::NodeSet nodes = node->find("descendant::*[name()='" + NeXML::NODE_TAG + "']" );
             xmlpp::NodeSet edges = node->find("descendant::*[name()='" + NeXML::EDGE_TAG + "']" );
             xmlpp::NodeSet annotations = node->find("descendant::*[name()='" + NeXML::ANNOTATION_TAG + "']"); 
             for (xmlpp::NodeSet::iterator it = nodes.begin(); it != nodes.end(); ++it){
                 ret->addnode( process_node( *it ));
             }
             for (xmlpp::NodeSet::iterator it = edges.begin(); it != edges.end(); ++it){
                 ret->addedge( process_edge( *it ) );
             }
             for (xmlpp::NodeSet::iterator it = annotations.begin(); it != annotations.end(); ++it){
                 ret->addannotation( process_annotation( *it ) );
             }

         }
    }
  }
  return ret; 
}
/*
 * Process a format block
 */
NeXML::Format* process_format( xmlpp::Node* node ){ 
  NeXML::Format* ret = NULL;
  if (node){
    NeXML::Format* ret = new NeXML::Format();
    xmlpp::NodeSet states = node->find( "descendant::*[name()='" + NeXML::STATES_TAG + "']" );
    xmlpp::NodeSet chars  = node->find( "descendant::*[name()='" + NeXML::CHAR_TAG   + "']");
    xmlpp::NodeSet notes  = node->find( "descendant::*[name()='" + NeXML::ANNOTATION_TAG + "']" );

    for (xmlpp::NodeSet::iterator it = states.begin(); it != states.end(); ++it ){
      ret->setstates( process_states( *it ) );
    }
    for (xmlpp::NodeSet::iterator it = chars.begin(); it != chars.end(); ++it ){
      ret->addchar( process_char( *it ) );
    }
    for (xmlpp::NodeSet::iterator it = notes.begin(); it != notes.end(); ++it ){
      ret->addannotation( process_annotation( *it ) );
    }
  }
  return ret; 
}
/*
 * Process a states block
 */
NeXML::States* process_states( xmlpp::Node* node ){ 
  NeXML::States* ret = NULL;
  if (node){
    if (xmlpp::Element* ele = dynamic_cast< xmlpp::Element* >( node )){
        if (xmlpp::Attribute* idattr = ele->get_attribute( "id" )){
            ustring id = idattr->get_value();
            ret = new NeXML::States( id );
            xmlpp::NodeSet states = node->find("descendant::*[name()='"  + NeXML::STATE_TAG + "']");
            xmlpp::NodeSet notes  = node->find("descendant::*[name()='"  + NeXML::ANNOTATION_TAG + "']");

            for (xmlpp::NodeSet::iterator it = states.begin(); it != states.end(); ++it){
              ret->addstate( process_state( *it ) );
            }
            for (xmlpp::NodeSet::iterator it = notes.begin(); it != notes.end(); ++it){
              ret->addannotation( process_annotation( *it ) );
            }
        }
    }
  }
  return ret; 
}
/*
 * Process a matrix.
 */
NeXML::Matrix* process_matrix( xmlpp::Node* node ){ 
  NeXML::Matrix* ret = NULL;
  if (node){
     
    xmlpp::NodeSet rows = node->find( "descendant::*[name()='"  + NeXML::ROW_TAG + "']");
    xmlpp::NodeSet notes = node->find("descendant::*[name()='"  + NeXML::ANNOTATION_TAG + "']");
     ret = new NeXML::Matrix();

     for (xmlpp::NodeSet::iterator it = rows.begin(); it != rows.end(); ++it){
       ret->addrow( process_row( *it ) );
     }
     for (xmlpp::NodeSet::iterator it = notes.begin(); it != notes.end(); ++it){
       ret->addannotation( process_annotation( *it ) );
     }
  }
  return ret; 
}
/*
 * Process a single row.
 */
NeXML::Row* process_row( xmlpp::Node* node ){ 
  NeXML::Row* ret = NULL;
  if (node){
       if (xmlpp::Element* ele = dynamic_cast< xmlpp::Element* >( node )){
            xmlpp::Attribute* lab = ele->get_attribute( "label" );
            xmlpp::Attribute* otua = ele->get_attribute( "otu" );
            if ( otua ){
              NeXML::Otu* otu = otus_processed_[ otua->get_value() ];
              ustring label;
              if (lab){  label = lab->get_value(); }
              NeXML::Row* ret = new NeXML::Row( otu, label );
              xmlpp::NodeSet cells = node->find( "descendant::*[name()='"  + NeXML::CELL_TAG + "']" ); 
              for ( xmlpp::NodeSet::iterator  it = cells.begin(); it != cells.end(); ++it ){
                  ret->addcell( process_cell( *it ) );
              }
            }
        }
  }
  return ret;
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

