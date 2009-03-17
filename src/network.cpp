#include "network.hpp"
using namespace NeXML;

void Network::addnode( Node* node ){
   if ( node ){

   }
   return;
}


void Network::addedge( Edge* edge ){
   if ( edge ){
        edges_.push_back( edge );
        edges_by_id_[ edge->getid() ] = edge;
   }
   return;
}
