#include "nexml.hpp"

#ifdef EBUG_V
#include <iostream>
#endif

using namespace NeXML;
using namespace std;

Nexml::Nexml():otus_(NULL),
               trees_(NULL),
	       characters_(){}

Nexml::~Nexml(){
  delete otus_;
  delete trees_;
  for ( unsigned int i = 0; i < characters_.size(); ++i ){
    delete characters_[ i ];
  }  
}


void Nexml::setotus( Otus* otus ){
#ifdef EBUG_V_OTUS
  cerr << "NeXML::setotus( otus: " << (void*)otus << ")" <<  endl;
  cerr << "current otus_ :" << (void*)otus_ << endl;
#endif
  if (otus_ && otus != otus_){ delete otus_; }
  otus_ = otus;
  if ( trees_ ){ trees_->setotus( otus_ ); }
  return;
}

void Nexml::addmatrix( Characters* matrix ){
  if ( matrix ) {
    characters_.push_back( matrix );
  }
  return;
}

void Nexml::settrees( Trees* t ){
   if ( trees_ && trees_ != t){ delete trees_; }
   trees_ = t;
   trees_->setotus( otus_ );
   return;
}

std::ostream& Nexml::serialize( std::ostream& out )const{
     out << "<?xml version=\"1.0\"?>\n";
     out << "<nexml xmlns:nex=\"http://www.nexml.org/1.0\" xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\" xmlns=\"http://www.nexml.org/1.0\">\n";
     out << dynamic_cast< const Annotable* >( this );
    
     out << otus_;
     out << trees_;
         
     for ( vector< Characters* >::const_iterator i = characters_.begin(); i != characters_.end(); ++i){
          out << *i;
     }
    

     out << "</nexml>";


  return out;
}

std::ostream& NeXML::operator<<(std::ostream& out, const Nexml& rhs){
         return rhs.serialize( out );

}

std::ostream& NeXML::operator<<( std::ostream& out, const Nexml* rhs ){
  if ( rhs ){ rhs->serialize( out ); }
  return out;
}
