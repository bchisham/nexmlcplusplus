#include "nclnexmlcharacters.hpp"
//#include "matrix.h"
#include <cassert>
#include <cctype>
#include "../tags.hpp"
using namespace std;

map< Glib::ustring, NxsCharactersBlock::DataTypesEnum > NxsNexmlCharacters::types_ = map< Glib::ustring, NxsCharactersBlock::DataTypesEnum >();

/*
 * Process observation data. 
 */
static vector<string> characterStatesFromString( const string& in );

//<-----Class members------------------>
/*
 * Wraps the NeXML::Characters* block with ncl api.
 */
NxsNexmlCharacters::NxsNexmlCharacters( NeXML::Characters* matrix):nxscharblock_( NULL ){
    matrix_ = matrix;
    //<---NCL Implementation----->
    exsets_ = map< string, NxsUnsignedSet >();
    indexsets_ = map< string, NxsUnsignedSet >();
    partitions_ = map< string, NxsPartition >();
    transformationManager_ = NxsTransformationManager();
    datatypeMappers_ = vector< const NxsDiscreteDatatypeMapper*>();
    codonPartitions_ = map< string, pair< NxsPartition, bool > >();
    
    if (types_.size() == 0){
        types_[ NeXML::STANDARD_TYPE ]   = NxsCharactersBlock::standard;
        types_[ NeXML::DNA_TYPE ]        = NxsCharactersBlock::dna;
        types_[ NeXML::RNA_TYPE ]        = NxsCharactersBlock::rna;
        types_[ NeXML::NUCLEOTIDE_TYPE ] = NxsCharactersBlock::nucleotide;
        types_[ NeXML::PROTEIN_TYPE ]    = NxsCharactersBlock::protein;
        types_[ NeXML::CODON_TYPE ]      = NxsCharactersBlock::codon;
        types_[ NeXML::CONTINUOUS_TYPE ] = NxsCharactersBlock::continuous;
        types_[ NeXML::MIXED_TYPE ]      = NxsCharactersBlock::mixed;
    }
   
}

NxsNexmlCharacters::NxsNexmlCharacters( NxsCharactersBlock* nxsblock ):nxscharblock_( nxsblock ){
    //<---NCL Implementation----->
    exsets_ = map< string, NxsUnsignedSet >();
    indexsets_ = map< string, NxsUnsignedSet >();
    partitions_ = map< string, NxsPartition >();
    transformationManager_ = nxsblock->GetNxsTransformationManagerRef();
    datatypeMappers_ = nxsblock->GetAllDatatypeMappers(); //vector< const NxsDiscreteDatatypeMapper*>();
    codonPartitions_ = map< string, pair< NxsPartition, bool > >();
    
    if (types_.size() == 0){
        types_[ NeXML::STANDARD_TYPE ]   = NxsCharactersBlock::standard;
        types_[ NeXML::DNA_TYPE ]        = NxsCharactersBlock::dna;
        types_[ NeXML::RNA_TYPE ]        = NxsCharactersBlock::rna;
        types_[ NeXML::NUCLEOTIDE_TYPE ] = NxsCharactersBlock::nucleotide;
        types_[ NeXML::PROTEIN_TYPE ]    = NxsCharactersBlock::protein;
        types_[ NeXML::CODON_TYPE ]      = NxsCharactersBlock::codon;
        types_[ NeXML::CONTINUOUS_TYPE ] = NxsCharactersBlock::continuous;
        types_[ NeXML::MIXED_TYPE ]      = NxsCharactersBlock::mixed;
    }

}

NxsNexmlCharacters::~NxsNexmlCharacters(){
    //xsltFreeStylesheet( style );
    //xmlFreeDoc( matrix );
}

 //<---NCL NxsCharactersBlock Interface----->
     NxsCharactersBlock::DataTypesEnum NxsNexmlCharacters::GetDataType() const{
       
     }
     NxsCharactersBlock::DataTypesEnum NxsNexmlCharacters::GetOriginalDataType() const {
     
     }
     const NxsDiscreteStateRow & NxsNexmlCharacters::GetDiscreteMatrixRow(unsigned taxNum) const{
     
     }
     char NxsNexmlCharacters::GetGapSymbol() const{
     
     }
     void NxsNexmlCharacters::SetGapSymbol(char sym){
     
     }
     VecBlockPtr NxsNexmlCharacters::GetImpliedBlocks(){
     
     }
     int NxsNexmlCharacters::GetInternalRepresentation(unsigned i, unsigned j, unsigned k ) const{
     
     }
     std::vector<std::string> NxsNexmlCharacters::GetItems() const{
     
     }
     char NxsNexmlCharacters::GetMatchcharSymbol() const {
     
     }
     unsigned NxsNexmlCharacters::GetMaxObsNumStates(bool countMissingStates) const {
     
     }
     char NxsNexmlCharacters::GetMissingSymbol() const{
     
     }
     unsigned NxsNexmlCharacters::GetNCharTotal()  {
     
     }
     unsigned NxsNexmlCharacters::GetNTaxWithData() const {
     
     }
     unsigned NxsNexmlCharacters::GetNumActiveChar() const {
     
     }
     unsigned NxsNexmlCharacters::GetNumIncludedChars() const {
     
     }
     unsigned NxsNexmlCharacters::GetNumEliminated() const {
     
     }
     unsigned NxsNexmlCharacters::GetNumEquates() const {
     
     }
     unsigned NxsNexmlCharacters::GetNumUserEquates() const{
     
     }
     unsigned NxsNexmlCharacters::GetNumMatrixCols() const {
     
     }
     unsigned NxsNexmlCharacters::GetNumMatrixRows() const {
     
     }
     unsigned NxsNexmlCharacters::GetNChar() const{
     
     }
     unsigned NxsNexmlCharacters::GetNumChar() const{
     
     }
     unsigned NxsNexmlCharacters::GetNumStates(unsigned i, unsigned j) const {
     
     }

//<------NCL NxsCharactersBlcokAPI interface impl.----------->
unsigned NxsNexmlCharacters::ApplyExset(NxsUnsignedSet &exset){ 
  return 0; 
}
bool NxsNexmlCharacters::AddNewExSet(const std::string &label, const NxsUnsignedSet & inds){ 
  bool ret = false;
  if ( nxscharblock_ ){ ret = nxscharblock_->AddNewExSet( label, inds); }
  exsets_[ label ] = inds;
  return ret; 
}
bool NxsNexmlCharacters::IsRespectCase() const { 
  bool ret = false;
  if ( nxscharblock_){ ret = nxscharblock_->IsRespectCase(); }
  return ret; 
}
unsigned NxsNexmlCharacters::GetNCharTotal() const{ 
  return matrix_->getNChar(); 
}
NxsTransformationManager & NxsNexmlCharacters::GetNxsTransformationManagerRef(){
  return transformationManager_;
}
const NxsTransformationManager & NxsNexmlCharacters::GetNxsTransformationManagerRef() const{
  return transformationManager_;
}
std::vector<const NxsDiscreteDatatypeMapper *> NxsNexmlCharacters::GetAllDatatypeMappers() const{
  return datatypeMappers_;
}
bool NxsNexmlCharacters::AddNewCodonPosPartition(const std::string &label, const NxsPartition & inds, bool isDefault){
  codonPartitions_[ label ] = pair< NxsPartition, bool >( inds, isDefault );
  return true;
}

unsigned int NxsNexmlCharacters::GetMaxIndex() const { 
  return this->GetNCharTotal() -1;
}

unsigned int NxsNexmlCharacters::GetIndicesForLabel(const std::string& label, NxsUnsignedSet* uset) const{
  assert( NULL != uset );
  *uset = exsets_.find( label )->second;
  return uset->size(); 
}

unsigned int NxsNexmlCharacters::GetIndexSet(const std::string& label, NxsUnsignedSet* uset) const{ 
  assert( NULL != uset );
  *uset = indexsets_.find( label )->second;
  return uset->size();
}

bool NxsNexmlCharacters::AddNewIndexSet(const std::string& label, const NxsUnsignedSet& uset){ 
  bool ret = false;
  indexsets_[ label ] = uset;
  if ( nxscharblock_ ){ ret = nxscharblock_->AddNewIndexSet( label, uset ); }
  return ret;
}

bool NxsNexmlCharacters::AddNewPartition(const std::string& label, const NxsPartition&  partition){ 
  bool ret = false;
  partitions_[ label ] = partition;
  if ( nxscharblock_ ){ ret = nxscharblock_->AddNewPartition(label, partition ); }
  return ret; 
}
//TODO Implement stub with something reasonable.
std::string NxsNexmlCharacters::GetDefaultCodonPosPartitionName() const{
   std::string ret = "";
   if ( nxscharblock_ ){ ret = nxscharblock_->GetDefaultCodonPosPartitionName(); }
   return ret;
}
//TODO Make sure this it the right thing to do.
NxsPartition NxsNexmlCharacters::GetCodonPosPartition(const std::string& in ) const{
    if ( nxscharblock_ ){ return nxscharblock_->GetCodonPosPartition( in ); }
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
