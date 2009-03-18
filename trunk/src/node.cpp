#include "node.hpp"
#include "tags.hpp"

using namespace NeXML;

std::ostream& NeXML::operator<<( std::ostream& out, const Node& rhs ){
  out << "<" << NODE_TAG << " id=\""<< rhs.getid() << "\" label=\"" <<  rhs.label_ <<"\" otu=\"" << rhs.otu_ << "\"";
  if (rhs.isroot_){ out << " root=\"true\""; }
  out << "/>\n";
  return out;
}
std::ostream& NeXML::operator<<( std::ostream& out, const Node* rhs ){
  if (rhs){ out << *rhs; }
  return out;
}
