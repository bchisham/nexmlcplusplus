#include "states.hpp"

using namespace NeXML;
using namespace std;

States::~States(){
  for (vector< State* >::iterator i = states_.begin(); i != states_.end(); ++i){
     delete *i;
  }
}

void States::addstate( State* state){
  if (state){ states_.push_back( state ); }
  return;
}

State* States::getstate( unsigned int i )const{
   State* ret = i < states_.size() ? states_.at( i ) : NULL;
   return ret;
}

std::ostream& NeXML::operator<<( std::ostream& out, const States& rhs ){
  out << "<states id=\"" << rhs.id_ << "\">\n";
  for (vector< State* >::const_iterator i = rhs.states_.begin(); i != rhs.states_.end(); ++i){
     out << *i;
  }
  out << "</states>\n";
  return out;
}
std::ostream& NeXML::operator<<( std::ostream& out, const States* rhs ){
  if (rhs){ return out << *rhs;}
  return out;
}

