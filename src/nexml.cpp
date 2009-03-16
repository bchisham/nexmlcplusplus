#include "nexml.hpp"

using namespace NeXML;
using namespace std;

Nexml::Nexml():otus_(NULL), 
	       characters_(), 
	       trees_(), 
	       networks_(){}

Nexml::~Nexml(){
  delete otus_;
  for ( unsigned int i = 0; i < characters_.size(); ++i ){
    delete characters_[ i ];
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

void Nexml::addmatrix( Characters* matrix ){
  if ( matrix ) {
    characters_.push_back( matrix );
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

std::ostream& NeXML::operator<<(std::ostream& out, const Nexml& rhs){
     out << "<?xml version=\"1.0\"?>\n";
     out << "<nexml xmlns:nex=\"http://www.nexml.org/1.0\" xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\" xmlns=\"http://www.nexml.org/1.0\">\n";
     
     if ( rhs.otus_ ){
          out << *(rhs.otus_);
     }
     
     for (vector< Annotation* >::const_iterator i = rhs.annotations_.begin(); i != rhs.annotations_.end(); ++i){
        out << *i;
     }

     for ( vector< Characters* >::const_iterator i = rhs.characters_.begin(); i != rhs.characters_.end(); ++i){
          out << *i;
     }
     for ( vector< Tree* >::const_iterator i = rhs.trees_.begin(); i != rhs.trees_.end(); ++i){
          out << *i;
     }
     for ( vector< Network* >::const_iterator i = rhs.networks_.begin(); i != rhs.networks_.end(); ++i){
          out << *i;
     }


     out << "</nexml>";
     return out;

}
