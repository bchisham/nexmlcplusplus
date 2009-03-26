#include "nclnexmlmatrix.hpp"
//#include "matrix.h"
#include <cassert>
#include <cctype>

using namespace std;



/*
 * Process observation data. 
 */
static vector<string> characterStatesFromString( const string& in );

//<-----Class members------------------>
/*
 * Wraps the NeXML::Characters* block with ncl api.
 */
NxsNexmlMatrix::NxsNexmlMatrix( NeXML::Characters* matrix){
    matrix_ = matrix;
    //<---NCL Implementation----->
    exsets_ = map< string, NxsUnsignedSet >();
    indexsets_ = map< string, NxsUnsignedSet >();
    partitions_ = map< string, NxsPartition >();
    transformationManager_ = NxsTransformationManager();
    datatypeMappers_ = vector< const NxsDiscreteDatatypeMapper*>();
    codonPartitions_ = map< string, pair< NxsPartition, bool > >();

   
}
NxsNexmlMatrix::~NxsNexmlMatrix(){
    //xsltFreeStylesheet( style );
    //xmlFreeDoc( matrix );
}

unsigned NxsNexmlMatrix::ApplyExset(NxsUnsignedSet &exset){ 
  return 0; 
}
bool NxsNexmlMatrix::AddNewExSet(const std::string &label, const NxsUnsignedSet & inds){ 
  exsets_[ label ] = inds;
  return false; 
}
bool NxsNexmlMatrix::IsRespectCase() const { 
  return false; 
}
unsigned NxsNexmlMatrix::GetNCharTotal() const{ 
  return matrix_->getNChar(); 
}
NxsTransformationManager & NxsNexmlMatrix::GetNxsTransformationManagerRef(){
  return transformationManager_;
}
const NxsTransformationManager & NxsNexmlMatrix::GetNxsTransformationManagerRef() const{
  return transformationManager_;
}
std::vector<const NxsDiscreteDatatypeMapper *> NxsNexmlMatrix::GetAllDatatypeMappers() const{
  return datatypeMappers_;
}
bool NxsNexmlMatrix::AddNewCodonPosPartition(const std::string &label, const NxsPartition & inds, bool isDefault){
  codonPartitions_[ label ] = pair< NxsPartition, bool >( inds, isDefault );
  return true;
}

unsigned int NxsNexmlMatrix::GetMaxIndex() const { 
  return this->GetNCharTotal() -1;
}

unsigned int NxsNexmlMatrix::GetIndicesForLabel(const std::string& label, NxsUnsignedSet* uset) const{
  assert( NULL != uset );
  *uset = exsets_.find( label )->second;
  return uset->size(); 
}

unsigned int NxsNexmlMatrix::GetIndexSet(const std::string& label, NxsUnsignedSet* uset) const{ 
  assert( NULL != uset );
  *uset = indexsets_.find( label )->second;
  return uset->size();
}

bool NxsNexmlMatrix::AddNewIndexSet(const std::string& label, const NxsUnsignedSet& uset){ 
  indexsets_[ label ] = uset;
  return false;
}

bool NxsNexmlMatrix::AddNewPartition(const std::string& label, const NxsPartition&  partition){ 
  partitions_[ label ] = partition;
  return false; 
}
//TODO Implement stub with something reasonable.
std::string NxsNexmlMatrix::GetDefaultCodonPosPartitionName() const{
   return "";
}
//TODO Make sure this it the right thing to do.
NxsPartition NxsNexmlMatrix::GetCodonPosPartition(const std::string& in ) const{
    map< string, NxsPartition >::const_iterator ret = partitions_.find( in );
    return ret == partitions_.end() ? NxsPartition() : ret->second;
}


vector<string> characterStatesFromString( const string& in ){
   //take care of the empty string case right away.
   vector<string> ret = vector<string>();
   if ( in.size() != 0 ){
     //strings with white-space have characters delimited by spaces.
     if ( in.find(' ') == string::npos || in.find('\t') == string::npos ){
        string current = "";
        for ( unsigned int i = 0; i < in.size(); ++i ){ 
           if ( isspace(  in.at( i ) ) ){ ret.push_back( current ); }
           else { current += in.at( i ); }
        }
     }
     //otherwise assume each position in the string is a character state observation.
     else {
        for ( unsigned int i = 0; i < in.size(); ++i ){
           ret.push_back( string("") += in.at( i )  );
        }
     }
   }
   return ret;
}
