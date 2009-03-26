#include "network.hpp"
#include "tags.hpp"
#include <algorithm>
using namespace NeXML;
using namespace std;

Network::~Network(){

  for (vector< const Edge* >::iterator it = edges_.begin(); it != edges_.end(); ++it ){
      delete *it;
  }
   
  for (vector< const Node* >::iterator it = nodes_.begin(); it != nodes_.end(); ++it){
      delete *it;
  }
  nodes_by_id_.empty();
  edges_by_id_.empty();
  targets_.empty();

}

const Node* Network::getnode( const Glib::ustring& id )const{
  map< Glib::ustring, const Node* >::const_iterator ret = nodes_by_id_.find( id );
  return ret == nodes_by_id_.end() ? NULL: ret->second;

}

const Edge* Network::getedge( const Glib::ustring& id)const{
  map< Glib::ustring, const Edge* >::const_iterator ret = edges_by_id_.find( id );
  return ret == edges_by_id_.end() ? NULL: ret->second;
}

/**
 * Get the immedate descendants of the specified node
 */
vector< const Node* > Network::getchildren( const Node* parent )const{
   map< const Node*, vector< const Node* > >::const_iterator ret = targets_.find( parent );
   //vector< const Edge* > ret = vector< const Edge* >();
   return ret == targets_.end() ? vector< const Node* >() : ret->second;
}

/**
 * Get the immedate ancestor of the specified node.
 */
const Node* Network::getparent( const Node* child )const{
  map< const Node*, const Node* >::const_iterator ret = source_.find( child );
  return ret == source_.end() ? NULL : ret->second;
}

void Network::addnode( const Node* node ){
   if ( node ){
        nodes_.push_back( node );
        nodes_by_id_[ node->getid() ] = node;
        if ( node->isroot() ){ root_ = node; }
   }
   return;
}


void Network::addedge( const Edge* edge ){
   if ( edge ){
        edges_.push_back( edge );
        edges_by_id_[ edge->getid() ] = edge;
        targets_[ edge->getsource() ].push_back( edge->gettarget() );
        source_[ edge->gettarget() ] = edge->getsource();
   }
   return;
}

const Edge* Network::getedge( const Node* source, const Node* target)const{
   for (vector< const Edge* >::const_iterator i = edges_.begin(); i != edges_.end(); ++i){
      if ( (*i)->getsource() == source && (*i)->gettarget() == target ){ return *i; }
   }
   return NULL;
}

std::ostream& Network::serialize( std::ostream& out )const{
  
  out << "<" << NeXML::NETWORK_TAG << " id=\"" << getid() << "\""<< " label=\"" << label_  << "\" type=\"" << type_ << "\">" << endl;
  for (vector< const Node* >::const_iterator it = nodes_.begin(); it != nodes_.end(); ++it){
      out << *it;
  }
  for (vector< const Edge* >::const_iterator it = edges_.begin(); it != edges_.end(); ++it){
      out << *it;
  }
  
  out << "</" << NeXML::NETWORK_TAG << ">" << endl;

  return out;
}

