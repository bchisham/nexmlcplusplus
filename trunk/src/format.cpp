#include "format.hpp"
#include "tags.hpp"

using namespace NeXML;
using namespace std;

void Format::setstates( const States* s ){
   if (states_ && states_ != s ){ delete states_; }
   states_ = s;
   return;
}

std::ostream& Format::serialize( std::ostream& out )const{
  out << "<" << FORMAT_TAG << ">\n";
  out << dynamic_cast< const Annotable* >( this );
  out << states_;
  for (vector< const Character* >::const_iterator i = chars_.begin(); i != chars_.end(); ++i){
     out << *i;
  }
  out << "</" << FORMAT_TAG << ">\n";

  return out;
}

std::ostream& NeXML::operator<<( std::ostream& out, const Format& rhs ){
   return rhs.serialize( out );
}
std::ostream& NeXML::operator<<( std::ostream& out, const Format* rhs ){
  if (rhs){ rhs->serialize( out ); }
  return out;
}

