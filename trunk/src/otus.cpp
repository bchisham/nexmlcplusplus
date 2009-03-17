#include "otus.hpp"
using namespace NeXML;
using namespace std;

Otus::Otus():Annotable(),otus_(), otus_by_id_(){}

Otus::~Otus(){
  for ( unsigned int i = 0; i < otus_.size(); ++i ){
    delete otus_[ i ];
  }
}

void Otus::addotu( Otu* otu ){
  if ( otu ){
    otus_.push_back( otu );
    otus_by_id_[ otu->getid() ] = otu;
  }
  return;
}

Otu* Otus::getotu( Glib::ustring id )const{
 // map< string, Otu* >::const_iterator res = find( otus_by_id_.begin(), otus_by_id_.end(), id  );
  Otu* ret = NULL;
 // if ( res != otus_by_id_.end() ){
 //   ret = res->second;
 // }
  return ret;
}

std::ostream& NeXML::operator<<( std::ostream& out, const Otus& rhs){
  out << "<otus id=\"" << rhs.id_ << "\">\n";
  for ( vector< Otu* >::const_iterator i = rhs.otus_.begin(); i != rhs.otus_.end(); ++i){
      out << *i;
  }
  out << "</otus>\n";
  return out;
}
std::ostream& NeXML::operator<<( std::ostream& out, const Otus* rhs){
  if (rhs){ out << *rhs; }
  return out;
}

