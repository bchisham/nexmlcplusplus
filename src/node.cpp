#include "node.hpp"
#include "tags.hpp"

using namespace NeXML;

std::ostream& Node::serialize( std::ostream& out )const{
   out << "<" << NODE_TAG << " id=\""<< getid() << "\" label=\"" <<  label_ <<"\" otu=\"" << otu_ << "\"";
  if (isroot_){ out << " root=\"true\""; }
  out << "/>\n";
  return out;
}

std::ostream& NeXML::operator<<( std::ostream& out, const Node& rhs ){
    return rhs.serialize( out );
}
std::ostream& NeXML::operator<<( std::ostream& out, const Node* rhs ){
  if (rhs){ rhs->serialize( out ); }
  return out;
}

