#include "row.hpp"
#include "tags.hpp"
using namespace NeXML;
using namespace std;

Row::Row(Otu* otu, Glib::ustring label):Identifiable(label),
                                        Serializable(),
                                        otu_(otu),
                                        label_(label),
                                        cells_(){}
Row::~Row(){
   for (unsigned int i =0; i < cells_.size(); ++i){
      delete cells_[ i ];
   }
}

void Row::addcell( Cell* c ){
   if (c){ cells_.push_back( c ); }
   return;
}

Cell* Row::getcell( unsigned int i )const{
    Cell* ret = i < cells_.size() ? cells_.at( i ) : NULL;
    return ret;
}

std::ostream& NeXML::operator<<( std::ostream& out, const Row& rhs){
   return out;
}
std::ostream& NeXML::operator<<( std::ostream& out, const Row* rhs){
  if (rhs){ out << *rhs; }
  return out;
}
std::ostream& serialize( std::ostream& out )const{
  out << "<" << ROW_TAG <<" id=\"" << getid() << "\" label=\"" << label_ << "\" otu=\"" << otu_->getid() << "\">\n";
  
  for (vector< Cell* >::const_iterator i = cells_.begin(); i != cells_.end(); ++i){
    out << *i;
  }
  out << "</"<< ROW_TAG <<">\n";

   return out;
}
