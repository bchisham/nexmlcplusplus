#include "node.hpp"
#include "tags.hpp"

std::ostream& NeXML::operator<<( std::ostream& out, const Node& rhs ){
  out << "<" << NODE_TAG << " id=\""<< rhs.id_ << "\" otu=\"" << rhs.otu_ << "\"";
  if (rhs.isroot_){ out << " root=\"true\""; }
  out << "/>\n";
  return out;
}
std::ostream& NeXML::operator<<( std::ostream& out, const Node* rhs ){
  if (rhs){ out << *rhs; }
  return out;
}
