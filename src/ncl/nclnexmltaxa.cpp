#include "nclnexmltaxa.hpp"
//#include "nclxslt.h"
//#include "taxa.h"
#include <limits.h>
#include <cassert>
#include <algorithm>
#include <glibmm/ustring.h>

using namespace std; 
using namespace NeXML;

NxsNexmlTaxa::NxsNexmlTaxa( NeXML::Otus* otus ){
      this->otus_ = otus;
      this->block_name_ = "Taxa Block";
      //<------data-model-------------------------------->
      this->inactive_taxa_ = set< unsigned int >();
      this->active_taxa_ = set< unsigned int >();
      this->partitions_ = map< string, NxsPartition >();
      this->index_sets_ = map< string, NxsUnsignedSet >();
}

NxsNexmlTaxa::NxsNexmlTaxa( NxsTaxaBlock nTax ){
  vector< Otu* > otus = vector< Otu* >();
  for ( unsigned i = 0; i < nTax.GetNTaxTotal(); ++i ){
     otus.push_back( new Otu( Glib::ustring( nTax.GetTaxonLabel( i ).c_str() ) ) );
  }
  this->otus_ = new Otus( otus );
  this->block_name_ = "Taxa Block";
  //<------data-model-------------------------------->
  this->inactive_taxa_ = set< unsigned int >();
  this->active_taxa_ = set< unsigned int >();
  this->partitions_ = map< string, NxsPartition >();
  this->index_sets_ = map< string, NxsUnsignedSet >();

}

NxsNexmlTaxa::~NxsNexmlTaxa(){}
/**
 * Build a Nexus version of the block's data.
 */
NxsTaxaBlock NxsNexmlTaxa::getNexusBlock()const{
   NxsTaxaBlock ret = NxsTaxaBlock();
   for ( unsigned i = 0; i < this->GetNTaxTotal(); ++i ){
      ret.AddTaxonLabel( this->GetTaxonLabel( i ) );
   }
   return ret;
}


//<-------NxsTaxaBlock interface---------------------->
/*
 * Returns the maximum valid index
 */
unsigned int NxsNexmlTaxa::GetMaxIndex()const{ return otus_->size() -1 ; }
/*
 * Look up the index set associated with the specified label
 */
unsigned int NxsNexmlTaxa::GetIndicesForLabel( const std::string& key, NxsUnsignedSet* val)const{
  assert( val );
  return this->GetIndexSet( key, val );
}
/*
 * Lookup the index set associated with the specified label. 
 */
unsigned int NxsNexmlTaxa::GetIndexSet( const std::string& key, NxsUnsignedSet* val)const{  
   assert( val );
   map<string, NxsUnsignedSet >::const_iterator target = index_sets_.find( key );
   if ( target != index_sets_.end()){
     *val = target->second;
   }
   return val->size();
}
/*
 * Adds a new index set.
 */
bool NxsNexmlTaxa::NxsAddNewIndexSet( const std::string& key, const NxsUnsignedSet& val){ 
  index_sets_[ key ] = val;
  return true;
}
/*
 * Adds a new partition.
 */
bool NxsNexmlTaxa::NxsAddNewPartition( const std::string& key, const NxsPartition& val){
  partitions_[ key ] = val;
  return true;
}
/*
 * Adds a new taxon label.
 */
unsigned int NxsNexmlTaxa::AddTaxonLabel( const std::string& nval ){  Glib::ustring gstring = nval; otus_->addotu( new NeXML::Otu( gstring ) ); return otus_->size(); }
/*
 * Updates the specified taxon label.
 */
void NxsNexmlTaxa::ChangeTaxonLabel(unsigned int i, NxsString nval){ assert( i < otus_->size() ); otus_->getotu( i )->setlabel( nval ); }
/*
 * Get the label associated with the taxon number.
 */
NxsString NxsNexmlTaxa::GetTaxonLabel( unsigned int i )const{ assert( i < otus_->size()); return NxsString( otus_->getotu( i )->getlabel().c_str() ); }
/*
 * Find the taxon number associated with the specified label.
 */
unsigned int NxsNexmlTaxa::FindTaxon( const NxsString& key )const{ 
    unsigned int ret = 0;
    for (; ret < this->GetNTax() && this->GetTaxonLabel( ret ) != key; ++ret);
    return ret;
}
/*
 * Find the number associated with the specified label.
 */
unsigned int NxsNexmlTaxa::TaxLabelToNumber( const std::string& key ) const{ 
     return this->FindTaxon( NxsString( key.c_str() ) );
}
/*
 * Determine if the label is already in use.
 */
bool NxsNexmlTaxa::IsAlreadyDefined( const std::string& key ){
     return this->FindTaxon( NxsString( key.c_str() ) ) < this->GetNTax();
}
/*
 * Determine the max taxon label length.
 */
unsigned int NxsNexmlTaxa::GetMaxTaxonLabelLength(){ return INT_MAX; }
/*
 * Get the number of taxon labels in the set
 */
unsigned int NxsNexmlTaxa::GetNumTaxonLabels() const{ return this->GetNTax(); }
/*
 * Get the number of taxon labels in the set.
 */
unsigned int NxsNexmlTaxa::GetNTax() const{ return this->otus_->size(); }
/*
 * Get the number of taxon labels in the set.
 */
unsigned int NxsNexmlTaxa::GetNTaxTotal() const{ return this->GetNTax(); }
/*
 * Get the number associated with the taxon label.
 */
unsigned int NxsNexmlTaxa::TaxonLabelToNumber( const std::string& label ) const{
  return this->TaxLabelToNumber( label );
}
/*
 * Do nothing. libxml is handling the parsing.
 */
void NxsNexmlTaxa::HandleTaxLabels( NxsToken& ){ return; }
/*
 * Write an nexml format taxa block.
 */
void NxsNexmlTaxa::WriteTaxLabelsCommand( std::ostream& out) const{ 
 out << otus_;
  // out << "\t<otus id=\"taxa1\" label=\"" << block_name_ << "\">" << endl;
  //for (unsigned int i = 0; i < taxa_.size(); ++i ){
  //    out << "\t\t<otu id=\"t" << i << "\" label=\"" << taxa_.at( i ) << "\" />" << endl; 
  //}
 // out << "\t</otus>" << endl;
  return; 
}
/*
 */
void NxsNexmlTaxa::SetNtax( unsigned int val ){ return; }
/*
 */
unsigned int NxsNexmlTaxa::GetNumActiveTaxa() const{ return active_taxa_.size(); }
/*
 */
bool NxsNexmlTaxa::IsActiveTaxon( unsigned int tax)const{
   assert( tax < otus_->size() );
   return binary_search( active_taxa_.begin(), active_taxa_.end(), tax );
}
/*
 */
unsigned int NxsNexmlTaxa::ActivateTaxa( const std::set< unsigned int >& atax ){
  //initialization boilerplate
  set< unsigned int > tunion = set< unsigned int >();
  set< unsigned int > tdifference = set< unsigned int >();
  insert_iterator< set< unsigned int > > tuit  = inserter< set< unsigned int > >( tunion, tunion.begin() );
  insert_iterator< set< unsigned int > > tdiff = inserter< set< unsigned int > >( tdifference, tdifference.begin() );
  //the new active taxa is the union of the currently active and the newly active.
  set_union( active_taxa_.begin(), active_taxa_.end(), atax.begin(), atax.end(), tuit );
  //remove the newly active taxa from the inactive taxa.
  set_difference(inactive_taxa_.begin(), inactive_taxa_.end(), atax.begin(), atax.end(), tdiff );
  //update with working copy.
  active_taxa_ = tunion;
  inactive_taxa_ = tdifference;
  return active_taxa_.size();
}
/*
 */
unsigned int NxsNexmlTaxa::InactivateTaxa(const std::set< unsigned int >& itax){
 //initialization boilerplate
 set< unsigned int > tunion = set< unsigned int >();
 set< unsigned int > tdifference = set< unsigned int >();
 insert_iterator< set< unsigned int > > tuit  = inserter< set< unsigned int > >( tunion, tunion.begin() );
 insert_iterator< set< unsigned int > > tdiff = inserter< set< unsigned int > >( tdifference, tdifference.begin() );
 //add the newly inactive taxa to the set of inactive taxa.
 set_union( inactive_taxa_.begin(), inactive_taxa_.end(), itax.begin(), itax.end(), tuit);
 //remove newly inactive taxa from the set of active taxa.
 set_difference(active_taxa_.begin(), active_taxa_.end(), itax.begin(), itax.end(), tdiff);
 //update with working copy.
 inactive_taxa_ = tunion;
 active_taxa_ = tdifference;
 return inactive_taxa_.size();
}
/*
 */
unsigned int NxsNexmlTaxa::InactivateTaxon( unsigned int tax ){
   active_taxa_.erase( tax );
   inactive_taxa_.insert( tax );
   return inactive_taxa_.size();
}
/*
 */
unsigned int NxsNexmlTaxa::ActivateTaxon( unsigned int tax){
  inactive_taxa_.erase( tax );
  active_taxa_.insert( tax );
  return active_taxa_.size();
}
/*
 */
bool NxsNexmlTaxa::AddNewIndexSet( const std::string& key , const NxsUnsignedSet& iset){ 
  index_sets_[ key ] = iset; 
  return true; 
}
/*
 */
bool NxsNexmlTaxa::AddNewPartition( const std::string& key , const NxsPartition& part){ 
  partitions_[ key ] = part; 
  return true; 
}



