#include "edge.hpp"
#include "tags.hpp"

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
   this->setid( src_->getid() + target_->getid() );
}


std::ostream& NeXML::operator<<( std::ostream& out, const Edge& rhs){
  return rhs.serialize( out );
}
std::ostream& NeXML::operator<<( std::ostream& out, const Edge* rhs){
  if ( rhs ){ rhs->serialize( out ); }
  return out;
}

std::ostream& Edge::serialize( std::ostream& out )const{
   out << "<" << EDGE_TAG << " id=\"" << getid() << "\" source=\"" << getsource()->getid() << "\" target=\"" << gettarget()->getid() << "\" length=\""<< getlength() << "\">\n"; 
  // out << dynamic_cast< const Annotable* >( this );
   out << "</" << EDGE_TAG << ">\n";
  return out;
}

std::ostream& Rootedge::serialize( std::ostream& out )const{
  out << "<" << ROOTEDGE_TAG << " id=\"" << getid() << "\" target=\"" << gettarget()->getid() << "\">\n";
 // out << dynamic_cast< const Annotable* >( this );
  out << "</" << ROOTEDGE_TAG << ">\n";
  return out;
}
