#include "otu.hpp"
#include "tags.hpp"
using namespace NeXML;
Otu::~Otu(){}

std::ostream& NeXML::operator<<( std::ostream& out, const Otu& rhs ){
  out << "<" << OTU_TAG << " id=\"" <<rhs.id_ << "\" label=\"" << rhs.label_ << "\"/>\n";
  return out;
}

std::ostream& NeXML::operator<<( std::ostream& out, const Otu* rhs ){
  if (rhs){ out << *rhs; }
  return out;
}

