#include "otus.hpp"
#include "tags.hpp"
using namespace NeXML;
using namespace std;

Otus::Otus():Annotable(),Identifiable(),otus_(), otus_by_id_(){}

Otus::~Otus(){
  for ( unsigned int i = 0; i < otus_.size(); ++i ){
    delete otus_[ i ];
  }
}

void Otus::addotu( Otu* otu ){
  if ( otu ){
    otus_.push_back( otu );
    otus_by_id_[ otu->getid() ] = otu;
    //update the id as elements are added to the set.
    this->setid( this->getid() + otu->getid() );
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
  out << "<" << OTUS_TAG << " id=\"" << rhs.getid() << "\">\n";
  for ( vector< Otu* >::const_iterator i = rhs.otus_.begin(); i != rhs.otus_.end(); ++i){
      out << *i;
  }
  out << "</" << OTUS_TAG << ">\n";
  return out;
}
std::ostream& NeXML::operator<<( std::ostream& out, const Otus* rhs){
  if (rhs){ out << *rhs; }
  return out;
}
