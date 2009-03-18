#include "character.hpp"
#include "tags.hpp"
using namespace NeXML;

std::ostream& NeXML::operator<<( std::ostream& out, const Character& rhs ){
  
  out << "<" << CHAR_TAG << " id=\"" << rhs.getid() << "\" states=\"" << rhs.states_ << "\"/>\n";

  return out;
}
std::ostream& NeXML::operator<<( std::ostream& out, const Character* rhs ){
  if ( rhs ){ out << *rhs; }
  return out;
}

