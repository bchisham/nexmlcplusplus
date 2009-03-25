#include "node.hpp"
#include "tags.hpp"
#ifdef EBUG_V
#include <iostream>
#endif

using namespace NeXML;
using namespace std;

ostream& Node::serialize( ostream& out )const{
  out << "<" << NODE_TAG << " id=\""<< this->getid() <<"\"";
  if (label_ != "" ){ out << " label=\"" <<  this->label_  << "\""; }
  if (otu_ && label_ != ""){  out << " otu=\"" << otu_->getid() << "\""; }
  if (isroot_){ out << " root=\"true\""; }
  out << "/>\n";
  return out;
}

ostream& NeXML::operator<<( ostream& out, const Node& rhs ){
    return rhs.serialize( out );
}
ostream& NeXML::operator<<( ostream& out, const Node* rhs ){
  if (rhs){ rhs->serialize( out ); }
  return out;
}

