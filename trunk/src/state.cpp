#include "state.hpp"
#include "tags.hpp"
using namespace NeXML;
using namespace std;
/**
 * Write a single state
 */
std::ostream& State::serialize( std::ostream& out )const{
  out << "<" << STATE_TAG << " id=\"" << getid() 
      << "\" label=\"" << label_ 
      << "\" symbol=\"" << symbol_ << "\">\n";
  //write annotations if any.
  dynamic_cast< const Annotable* >( this )->serialize( out );
  out << "</" << STATE_TAG << ">\n";

  return out;
}
/**
 * Delegate serialization.
 */
std::ostream& NeXML::operator<<( std::ostream& out, const State& rhs){
  return rhs.serialize(out);
}
/**
 * Delegate serialization.
 */
std::ostream& NeXML::operator<<( std::ostream& out, const State* rhs){
  if (rhs){ rhs->serialize( out ); }
  return out;
}

StateSet::~StateSet(){/*deletion done by ~States();*/}

std::ostream& StateSet::serialize(std::ostream& out)const{
    for ( set< const State* >::iterator i = members_.begin(); i != members_.end(); ++i){
        out << "<" << MEMBER_TAG << " state=\"" << (*i)->getid() << "\"/>";
    }
    return out;
}

std::ostream& UncertainState::serialize(std::ostream& out)const{
  out << "<" << UNCERT_TAG << " id=\"" << getid() << "\" symbol=\"" << getsymbol() << "\">\n";
  //print annotations if any.
  out << dynamic_cast< const Annotable* >(this );
  //print the state set members.
  out << dynamic_cast< const StateSet* >( this );
  out << "</" << UNCERT_TAG << ">\n";

  return out;
}
//delegate serialization.
std::ostream& operator<<(std::ostream& out, const UncertainState& rhs ){
  return rhs.serialize( out ); 
}
//deletegate serialization.
std::ostream& operator<<(std::ostream& out, const UncertainState* rhs ){
  if (rhs){ rhs->serialize( out ); }
  return out;
}

std::ostream& PolymorphicState::serialize( std::ostream& out )const{
  
  out << "<" << POLY_TAG << " id=\"" << getid() << "\" symbol=\"" << getsymbol() << "\">\n";
  //print annotations.
  out << dynamic_cast< const Annotable* >( this );
  //print members.
  out << dynamic_cast< const StateSet* >( this );
  out << "</" << POLY_TAG << ">\n";

  return out;
}
//delegate serialization.
std::ostream& NeXML::operator<<(std::ostream& out, const PolymorphicState& rhs ){
  return rhs.serialize( out );
}
//delegate serialization
std::ostream& NeXML::operator<<(std::ostream& out, const PolymorphicState* rhs ){
  if (rhs){ rhs->serialize( out ); }
  return out;
}

