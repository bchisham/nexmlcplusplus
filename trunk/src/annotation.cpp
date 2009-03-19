#include "annotation.hpp"
#include "tags.hpp"

using namespace NeXML;

Annotable::~Annotable(){
  for ( std::vector< const Annotation* >::iterator i = notes_.begin(); i != notes_.end(); ++i){
      delete *i;
  }
}

std::ostream& Annotation::serialize( std::ostream& out )const{
  
   out << "<" << ANNOTATION_TAG << ">\n";
   out << literal_note_ << "\n";
   out << "</" << ANNOTATION_TAG << ">\n";

   return out;
}

std::ostream& Annotable::serialize( std::ostream& out )const{
  for (unsigned int i =0 ; i < notes_.size(); ++i){
      out << notes_.at( i );
  }
  return out;
}
