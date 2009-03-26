#include "trees.hpp"
#include "tags.hpp"

using namespace NeXML;
using namespace std;

Trees::~Trees(){
  for (vector< const Network* >::iterator i = trees_.begin(); i != trees_.end(); ++i ){
     delete *i;
  }
  trees_.empty();
  trees_by_label_.empty();
}

void Trees::addgraph( const Network* graph ){
  if ( graph ){
     trees_.push_back( graph );
     trees_by_label_[ graph->getlabel() ] = graph;
  }
  return;
}

const Network* Trees::getgraph( const Glib::ustring label)const{
    map< Glib::ustring, const Network* >::const_iterator ret = trees_by_label_.find( label );
    return ret == trees_by_label_.end() ? NULL : ret->second;
}


std::ostream& Trees::serialize( std::ostream& out )const{
  
   out << "<" << TREES_TAG << " id=\"" << getid() << "\" otus=\"" << otus_->getid() << "\">\n";
   out << dynamic_cast< const Annotable* >( this );
   for ( unsigned int i = 0; i < trees_.size(); ++i ){
       out << trees_.at( i );
   }
   out << "</" << TREES_TAG << ">\n";
   return out;
}
