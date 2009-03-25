#include "nclnexmlmatrix.hpp"
#include "matrix.h"
#include <cassert>
#include <cctype>

using namespace std;
/*
 * Symbolic names for the tags used in the transformation result.
 */
/*
namespace MatrixTags {
  static const string MATRIX = "matrix";
  static const string ID     = "id";
  static const string ROW    = "row";
  static const string OTU    = "otu";
  static const string DATA      = "data";
  static const string CELL      = "cell";
  static const string CELLDATA  = "cellwise-data";
  static const string CHARACTER = "character";
  static const string STATE     = "state";
}
*/
//<----pointers to class members--->
//static string* tid;
//static vector< string >* ttaxa;
//static vector< string >* tcharacters;
//static vector< vector< string > >* tmatrix;
//<----aux data used to keep track of where the cellwise
//     process is------->
//static int current_row_ = -1;
//static int current_col_ = -1;

//using namespace MatrixTags;
//<------Tag Processing------------>
/*
 * True if the specified node is a matrix.
 */
//static bool is_matrix_tag( xmlNode* );
/*
 * Process the specified matrix.
 */
//static void process_matrix_tag( xmlNode* );

/*
 * True if the specified node is an id.
 */
//static bool is_id_tag( xmlNode* );
/*
 * Process the specified id.
 */
//static void process_id_tag( xmlNode* );

/*
 * True if the specified node is a row.
 */
//static bool is_row_tag( xmlNode* );
/*
 * Process the specified row.
 */
//static void process_row_tag( xmlNode* );

/*
 * True if the specified node is an OTU
 */
//static bool is_otu_tag( xmlNode* );
/*
 * Process the specified otu.
 */
//static void process_otu_tag( xmlNode* );

/*
 * True if the specified node is row data.
 */
//static bool is_data_tag( xmlNode* );
/*
 * Process the specified row data.
 */
//static void process_data_tag( xmlNode* );

/*
 * True if the specified node is cellwise data.
 */
//static bool is_cellwise_data_tag( xmlNode* );
/*
 * Process the specified cellwise data.
 */
//static void process_cellwise_data_tag( xmlNode* );

//static bool is_cell_tag( xmlNode* );

//static void process_cell_tag( xmlNode* );

/*
 * True if the specified node is a character tag
 */
//static bool is_character_tag( xmlNode* );
/*
 * Process the specified character node.
 */
//static void process_character_tag( xmlNode* );

/*
 * True if the specified node is a state tag.
 */
//static bool is_state_tag( xmlNode* );
/*
 * Process the specified state node.
 */
//static void process_state_tag( xmlNode* );
/*
 * Process observation data. 
 */
static vector<string> characterStatesFromString( const string& in );

//<-----Class members------------------>
/*
 * Wraps the NeXML::Characters* block with ncl api.
 */
NxsNexmlMatrix::NxsNexmlMatrix(NeXML::Characters* matrix){
    //style = mktemp_xslt_file( MATRIX_H_STR );
    //this->source = source;
    //this->matrix = xsltApplyStylesheet( this->style, this->source, NULL );
    matrix_ = matrix;
    //id_ = "";
    //taxa_ = vector< string >();
    //characters_ = vector< string >();
    //matrix_ = vector< vector< string > >();
    exsets_ = map< string, NxsUnsignedSet >();
    indexsets_ = map< string, NxsUnsignedSet >();
    partitions_ = map< string, NxsPartition >();
    transformationManager_ = NxsTransformationManager();
    datatypeMappers_ = vector< const NxsDiscreteDatatypeMapper*>();
    codonPartitions_ = map< string, pair< NxsPartition, bool > >();

    //tid = &id_;
    //ttaxa = &taxa_;
    //tcharacters = &characters_;
    //tmatrix  = &matrix_;

    //traverse( xmlDocGetRootElement(matrix), is_matrix_tag, process_matrix_tag );

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
bool            NxsNexmlMatrix::AddNewCodonPosPartition(const std::string &label, const NxsPartition & inds, bool isDefault){
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

//<-----Tag Processing---------->
/*
bool is_matrix_tag( xmlNode* in ){
   return NULL != in && (const char*)in->name == MATRIX;  
}*/
/*
void process_matrix_tag( xmlNode* mat){
  assert( is_matrix_tag( mat ) );
  traverse( mat->children, is_id_tag, process_id_tag);
  traverse( mat->children, is_row_tag, process_row_tag );
  return;
}*/
/*
bool is_id_tag( xmlNode* in ){
   return NULL != in && (const char*)in->name == ID; 
}
*/
/*
void process_id_tag( xmlNode* idt ){
   assert( is_id_tag( idt ) );
   *tid = (const char*)xmlNodeGetContent( idt );
   return;
}
*/
/*
bool is_row_tag( xmlNode* in ){
   return NULL != in && (const char*)in->name == ROW; 
}
*/
/*
void process_row_tag( xmlNode* row ){
   assert( is_row_tag( row ) );
   current_row_++;
   current_col_ = 0;
   traverse( row->children, is_otu_tag, process_otu_tag );
   //only 1 of the following will actually do anything since a matrix
   //has either data or cellwise data but not a mix of the two.
   traverse( row->children, is_data_tag, process_data_tag );
   traverse( row->children, is_cellwise_data_tag, process_cellwise_data_tag);
   return;

}
*/
/*
bool is_otu_tag( xmlNode* in ){
   return NULL != in && (const char*)in->name == OTU; 
}
void process_otu_tag( xmlNode* otu){
   assert( is_otu_tag( otu ) );
   return;
}
*/
/*
bool is_data_tag( xmlNode* in ){
   return NULL != in && (const char*)in->name == DATA; 
}
void process_data_tag( xmlNode* data){
    assert( is_data_tag( data ) );
    tmatrix->push_back( characterStatesFromString((const char*)xmlNodeGetContent( data )) );
    return;
}
*/
/*
bool is_cellwise_data_tag( xmlNode* in ){
   return NULL != in && (const char*)in->name == CELLDATA; 
}
void process_cellwise_data_tag( xmlNode* cwd){
  assert( is_cellwise_data_tag( cwd ) );
  current_col_ = -1;
  traverse( cwd->children, is_cell_tag, process_cell_tag );
  //traverse( cwd->children, is_character_tag, process_character_tag );
  //traverse( cwd->children, is_state_tag, process_state_tag );
  return;
}
*/
/*
bool is_cell_tag( xmlNode* in ){
   return NULL != in && (const char*)in->name == CELL;
}
*/
/*
void process_cell_tag( xmlNode* in ){
  assert( is_cell_tag( in ) );  
  if (-1 == current_col_ ){ (*tmatrix)[current_row_] = vector< string >(); }
  current_col_++;
  traverse( in->children, is_character_tag, process_character_tag );
  traverse( in->children, is_state_tag, process_state_tag );

  return;
}
*/
/*
bool is_character_tag( xmlNode* in ){
   return NULL != in && (const char*)in->name == CHARACTER; 
}
void process_character_tag( xmlNode* ch){
   assert( is_character_tag( ch ) );
   return;
}
*/
/*
bool is_state_tag( xmlNode* in ){
   return NULL != in && (const char*)in->name == STATE; 
}
*/
/*
void process_state_tag( xmlNode* state){
   assert( is_state_tag( state ) );
   tmatrix->at( current_row_ ).push_back( (const char*)xmlNodeGetContent( state ) );
   return;
}
*/
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
