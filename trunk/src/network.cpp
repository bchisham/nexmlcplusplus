#include "network.hpp"
using namespace NeXML;
using namespace std;

Network::~Network(){

  for (vector< const Edge* >::iterator it = edges_.begin(); it != edges_.end(); ++it ){
      delete *it;
  }
   
  for (vector< const Node* >::iterator it = nodes_.begin(); it != nodes_.end(); ++it){
      delete *it;
  }
  edges_by_id_.empty();

}

void Network::addnode( const Node* node ){
   if ( node ){
        nodes_.push_back( node );
   }
   return;
}


void Network::addedge( const Edge* edge ){
   if ( edge ){
        edges_.push_back( edge );
        edges_by_id_[ edge->getid() ] = edge;
   }
   return;
}
