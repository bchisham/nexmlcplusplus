#include "otu.hpp"
#include "tags.hpp"
using namespace NeXML;
Otu::~Otu(){}

std::ostream& Otu::serialize( std::ostream& out )const{
  out << "<" << OTU_TAG << " id=\"" << getid() << "\" label=\"" << label_ << "\">\n";
  //print annotations. 
  out << dynamic_cast< const Annotable* >( this );
  out << "</" << OTU_TAG << ">\n";
  return out;
}


