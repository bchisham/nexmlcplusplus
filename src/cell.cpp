#include "cell.hpp"

using namespace NeXML;
using namespace std;

void Cell::setchar( Character* ch ){ char_ = ch; }

void Cell::setstate( State* state ){ state_ = state; }

ostream& operator<<( ostream& out, const Cell& rhs ){
  
  out << "<cell char=\"" << char_->getid() << "\" state=\"" << state_->getid() << "\"/>\n"; 

  return out;
}

ostream& operator<<( ostream& out, const Cell* rhs ){
  if (rhs){ out << *rhs; }
  return out;
}
