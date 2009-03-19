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
 * 
 */
std::ostream& NeXML::operator<<( std::ostream& out, const State& rhs){
  return rhs.serialize(out);
}

std::ostream& NeXML::operator<<( std::ostream& out, const State* rhs){
  if (rhs){ rhs->serialize( out ); }
  return out;
}

StateSet::~StateSet(){
  for (std::set< const State* >::iterator i = members_.begin(); i != members_.end(); ++i){
      delete *i;
  }
}

std::ostream& StateSet::serialize(std::ostream& out)const{
    for ( set< const State* >::iterator i = members_.begin(); i != members_.end(); ++i){
        out << "<" << MEMBER_TAG << " state=\"" << (*i)->getid() << "\"/>";
    }
    return out;
}

std::ostream& UncertainState::serialize(std::ostream& out)const{
  out << "<" << UNCERT_TAG << " id=\"" << getid() << "\" symbol=\"" << getsymbol() << "\">\n";
  out << dynamic_cast< const StateSet* >( this );
  out << "</" << UNCERT_TAG << ">\n";

  return out;
}

std::ostream& operator<<(std::ostream& out, const UncertainState& rhs ){
  return rhs.serialize( out ); 
}
std::ostream& operator<<(std::ostream& out, const UncertainState* rhs ){
  if (rhs){ rhs->serialize( out ); }
  return out;
}

std::ostream& PolymorphicState::serialize( std::ostream& out )const{
  
  out << "<" << POLY_TAG << " id=\"" << getid() << "\" symbol=\"" << getsymbol() << "\">\n";
  out << dynamic_cast< const StateSet* >( this );
  out << "</" << POLY_TAG << ">\n";

  return out;
}

std::ostream& NeXML::operator<<(std::ostream& out, const PolymorphicState& rhs ){
   
  return out;
}
std::ostream& NeXML::operator<<(std::ostream& out, const PolymorphicState* rhs ){
  if (rhs){ out<< *rhs; }
  return out;
}

