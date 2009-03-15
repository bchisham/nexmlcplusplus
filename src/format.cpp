#include "format.hpp"
using namespace NeXML;
using namespace std;

std::ostream& NeXML::operator<<( std::ostream& out, const Format& rhs ){

  out << "<format>\n";
  out << rhs.states_;
  for (vector< Character* >::const_iterator i = rhs.chars_.begin(); i != rhs.chars_.end(); ++i){
     out << *i;
  }
  out << "</format>\n";

}
std::ostream& NeXML::operator<<( std::ostream& out, const Format* rhs ){
  if (rhs){ out << *rhs; }
  return out;
}

