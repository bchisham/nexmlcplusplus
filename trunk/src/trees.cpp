#include "trees.hpp"
#include "tags.hpp"

using namespace NeXML;

std::ostream& Trees::serialize( std::ostream& out )const{
  
   out << "<" << TREES_TAG << " id=\"" << getid() << "\" otus=\"" << otus_->getid() << "\">\n";
   out << dynamic_cast< const Annotable* >( this );
   for ( unsigned int i = 0; i < trees_.size(); ++i ){
       out << trees_.at( i );
   }
   out << "</" << TREES_TAG << ">\n";
   return out;
}