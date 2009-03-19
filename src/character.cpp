#include "character.hpp"
#include "tags.hpp"
using namespace NeXML;


std::ostream& Character::serialize( std::ostream& out )const{
  out << "<" << CHAR_TAG << " id=\"" << getid() << "\" states=\"" << states_->getid() << "\">\n";
  //print any annotations.
  out << dynamic_cast< const Annotable* >( this );
  out << "</" << CHAR_TAG << ">\n";
  return out;
}

std::ostream& NeXML::operator<<( std::ostream& out, const Character& rhs ){
  return rhs.serialize( out );
}
std::ostream& NeXML::operator<<( std::ostream& out, const Character* rhs ){
  if ( rhs ){ rhs->serialize( out ); }
  return out;
}

