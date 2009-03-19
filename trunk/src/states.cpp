#include "states.hpp"
#include <algorithm>
#include "tags.hpp"
using namespace NeXML;
using namespace std;

States::~States(){
  for (set< const State* >::iterator i = states_.begin(); i != states_.end(); ++i){
     delete *i;
  }
}

void States::addstate( const State* state){
  if (state){ 
    states_.insert( state );  
    setid( getid() + state->getid() );
  }
  return;
}

const State* States::getstate( const Glib::ustring& i )const{
   set< const State* >::const_iterator ret = find(states_.begin(), states_.end(), i  );
   return  ret == states_.end() ? NULL : *ret ;
}

std::ostream& States::serialize( std::ostream& out )const{
  out << "<" << STATES_TAG << " id=\"" << getid() << "\">\n";
  //serialize annotations if any.
  out << dynamic_cast< const Annotable* >( this );
  //print children.
  for ( set< const State* >::const_iterator i = states_.begin(); i != states_.end(); ++i){
     out << *i;
  }
  out << "</" << STATES_TAG << ">\n";
  return out;
}

