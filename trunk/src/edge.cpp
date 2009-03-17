#include "edge.hpp"

using namespace NeXML;

void Edge::setsource( const Node* src ){
   src_ = src;
   updateid();
}

void Edge::settarget( const Node* target ){
   target_ = target;
   updateid();
}

void Edge::updateid(){
    id_.setid( src_->getid() + target_->getid() );
}


std::ostream& NeXML::operator<<( std::ostream& out, const Edge& rhs){
  
  out << "<edge id=\"" << rhs.getid() << "\" source=\"" << rhs.getsource() << "\" target=\"" << rhs.gettarget() << "\""; 
  if (unsigned int ann = rhs.getnumannotations() ){
    out << ">\n";
       for (unsigned int i = 0; i < ann; ++i){
          out << rhs.getannotation( i );
       }
     out << "</edge>\n";
  }
  else {
      out << "/>\n";
  }

  return out;
}
std::ostream& NeXML::operator<<( std::ostream& out, const Edge* rhs){
  if ( rhs ){ out << *rhs; }
  return out;
}

