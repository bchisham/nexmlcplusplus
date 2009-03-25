#include "otus.hpp"
#include "tags.hpp"
using namespace NeXML;
using namespace std;

Otus::Otus():Annotable(),Identifiable("temp"),otus_(), otus_by_id_(){}

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


std::ostream& Otus::serialize( std::ostream& out )const{
  out << "<" << OTUS_TAG << " id=\"" << getid() << "\">\n";
  out << dynamic_cast< const Annotable* >( this );
  for ( vector< Otu* >::const_iterator i = otus_.begin(); i != otus_.end(); ++i){
      out << *i;
  }
  out << "</" << OTUS_TAG << ">\n";
  return out;
}

