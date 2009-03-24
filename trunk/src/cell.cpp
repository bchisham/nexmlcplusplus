#include "cell.hpp"

using namespace NeXML;
using namespace std;

void Cell::setchar( Character* ch ){ char_ = ch; }

void Cell::setstate( State* state ){ state_ = state; }

std::ostream& Cell::serialize( std::ostream& out )const{
  out << "<cell char=\"" << char_->getid() << "\" state=\"" << state_->getid() << "\"/>\n"; 
  return out;
}


ostream& NeXML::operator<<( ostream& out, const Cell& rhs ){
  
  return rhs.serialize( out );
}

ostream& NeXML::operator<<( ostream& out, const Cell* rhs ){
  if (rhs){ rhs->serialize( out ); }
  return out;
}
