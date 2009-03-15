#include "nexml.hpp"

using namespace NeXML;
using namespace std;

Nexml::Nexml():otus_(NULL), 
	       matrices_(), 
	       trees_(), 
	       networks_(){}

Nexml::~Nexml(){
  delete otus_;
  for ( unsigned int i = 0; i < matrices_.size(); ++i ){
    delete matrices_[ i ];
  }
  for ( unsigned int i = 0; i < trees_.size(); ++i ){
    delete trees_[ i ];
  }
  for ( unsigned i = 0; i < networks_.size(); ++i ){
    delete networks_[ i ];
  }
  
}


void Nexml::setotus( Otus* otus ){
  if (otus_ && otus != otus_){ delete otus_; }
  otus_ = otus;
  return;
}

void Nexml::addmatrix( Matrix* matrix ){
  if ( matrix ) {
    matrices_.push_back( matrix );
  }
  return;
}

void Nexml::addtree( Tree* tree ){
  if ( tree ){
    trees_.push_back( tree );
  }
  return;
}

void Nexml::addnetwork( Network* network ){
  if ( network ){
    networks_.push_back( network );
  }
  return;
}
