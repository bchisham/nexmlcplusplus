#include "tree.hpp"
#include "tags.hpp"
using namespace NeXML;
using namespace std;


std::ostream& Tree::serialize( std::ostream& out )const{
  
  out << "<" << NeXML::TREE_TAG << " id=\"" << this->getid() << "\""<< " label=\"" << this->getlabel()  << "\" type=\"" << this->gettype() << "\">" << endl;

  for (vector< const Node* >::const_iterator it = nodes_.begin(); it != nodes_.end(); ++it){
      out << *it; 
  }
  for (vector< const Edge* >::const_iterator it = edges_.begin(); it != edges_.end(); ++it){
      out << *it;
  }
  
  out << "</" << NeXML::TREE_TAG << ">" << endl;

  return out;
}

