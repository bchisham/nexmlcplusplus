#include "state.hpp"
using namespace NeXML;

std::ostream& NeXML::operator<<( std::ostream& out, const State& rhs){
  out << "<state id=\"" << rhs.getid() 
      << "\" label=\"" << rhs.label_ 
      << "\" symbol=\"" << rhs.symbol_ << "\"/>\n";
  return out;
}

std::ostream& NeXML::operator<<( std::ostream& out, const State* rhs){
  if (rhs){ out << *rhs; }
  return out;
}

StateSet::~StateSet(){
  for (std::set< const State* >::iterator i = members_.begin(); i != members_.end(); ++i){
      delete *i;
  }
}
