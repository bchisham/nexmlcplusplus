#include "nclnexmltree.hpp"
#include "tree.h"
#include "nclxsltxx.hpp"

using namespace std;

//static const string NXSNEXMLEDGE = "edge";
//static const string NXSNEXMLTREE = "tree";
/*
 * keep a temp copy of most of the data model, so that it can be
 * accessed by the static c funtions that interface with the libxml/libxslt library.
 */
//static vector< string >* tmplabels;
//static map< string, bool >* tmpisRooted;
//static map< string, map< string, vector< pair< string, string > > > >* tmpgraphs;

static string get_newick_string( string, map< string, vector< pair< string, string > > >  );

/*
 * Callback for the nclxslt traverse function.
 * True for tree or edge nodes.
 */
//bool tree_filter( xmlNode* );
/*
 * Callback for the nclxslt traverse function.
 * Processes nodes matching the filter criteria.
 */
//void tree_processor( xmlNode* );
/*
 * Recontitute the tree information
 */
NxsNexmlTree::NxsNexmlTree(NeXML::Trees* trees){
   
    trees_ = trees;

    //prepare the xslt transformation.
    //this->style = mktemp_xslt_file( TREE_H_STR );
    //this->source = source;
    //apply the transformation.
    //this->tree = xsltApplyStylesheet( this->style, this->source, NULL );
    //initialize the temporary  model.
    //labels = vector< string >();
    //isRooted = map< string, bool >();
    //graphs  = map< string, map< string, vector< pair< string, string > > > >();
    index_sets_ = map< string, NxsUnsignedSet >();
    partition_sets_ = map< string, NxsPartition >();
    //tmplabels = &(this->labels);
    //tmpisRooted = &(this->isRooted);
    //tmpgraphs   = &(this->graphs);
    //extract the tree topology from the transformed document.
    //build_tree_info();
}
/*
 * Clean-up private info. The source document isn't owned by this class, 
 * so it's left untouched.
 */
NxsNexmlTree::~NxsNexmlTree(){
    //xsltFreeStylesheet( style );
    //xmlFreeDoc( tree );
}

 /*NCL Trees interface*/
unsigned	NxsNexmlTree::GetNumDefaultTree(){ return 1; }
//return the number of trees in the description.
unsigned	NxsNexmlTree::GetNumTrees(){ return this->trees_->getnumtrees(); }
//retrieve the name of a particular tree.
NxsString	NxsNexmlTree::GetTreeName(unsigned i){ 
  assert( i < this->GetNumTrees()); 
  return NxsString(this->labels.at( i ).c_str()); 
}
//Retrieve a particular tree description
NxsString	NxsNexmlTree::GetTreeDescription(unsigned i){
      return NxsString( get_newick_string( this->graphs[ this->GetTreeName( i ) ].begin()->first, this->graphs[ this->GetTreeName( i )] ).c_str() );
}
//Retrieve a particular tree description
NxsString	NxsNexmlTree::GetTranslatedTreeDescription(unsigned i){ 
  assert( i < this->GetNumTrees());
  return this->GetTreeDescription( i );
}
//true if i is the default tree.
bool		NxsNexmlTree::IsDefaultTree(unsigned i){ return i == 0; }
//true if i is a rooted tree
bool		NxsNexmlTree::IsRootedTree(unsigned i){ 
  assert( i < this->GetNumTrees() );
  return this->isRooted[ labels[ i ] ]; 
}
//get the maximum valid tree index.
unsigned int    NxsNexmlTree::GetMaxIndex()const{
   return this->labels.size() - 1;
}
//look up the index set associated with the given label.
unsigned int    NxsNexmlTree::GetIndicesForLabel(const std::string& key, NxsUnsignedSet* val)const{
  assert( NULL != val );
  map< string, NxsUnsignedSet >::const_iterator target = index_sets_.find( key );
  if (target != index_sets_.end()){
     *val = target->second;
  }
  return 0;
}
//get the index set for the given label. 
unsigned int    NxsNexmlTree::GetIndexSet(const std::string& key , NxsUnsignedSet* val)const{
  assert( NULL != val );
  return this->GetIndicesForLabel( key, val );
}
//add a new index set.
bool            NxsNexmlTree::AddNewIndexSet(const std::string& key, const NxsUnsignedSet& value){
    index_sets_[ key ] = value;
   return true;
}
//add a new partition.
bool            NxsNexmlTree::AddNewPartition(const std::string& key, const NxsPartition& value){
   partition_sets_[ key ] = value;
   return true;
}

/*
 * Traverse the transformed document and extract the relevant information.
 */
void NxsNexmlTree::build_tree_info(){
     traverse( xmlDocGetRootElement( tree ), tree_filter, tree_processor ); 
}
/*
 * Identify tree and edge nodes
 */
bool tree_filter( xmlNode* in ){
   return (const char*)(in->name) == NXSNEXMLEDGE || (const char*)(in->name) == NXSNEXMLTREE;
}
/*
 * Process tree and edge nodes.
 */
void tree_processor( xmlNode* in ){
  //operating on the tree
  if ((const char*)(in->name) == NXSNEXMLTREE){ 
     map< string, string > attrs = get_attribute_list( in );
     tmplabels->push_back( attrs["label"] );

     (*tmpisRooted)[ attrs["label"] ] = attrs["rooted"] == "true";
     (*tmpgraphs)[ attrs["label"] ]   = map< string, vector< pair< string,string > > >();
  }
  //operating on an edge
  else {
    map< string, string >  attrs = get_attribute_list( in->children );
    (*tmpgraphs)[ tmplabels->at( tmplabels->size() - 1 ) ][ attrs["source"] ].push_back( pair<string, string>(attrs["dest"], attrs["length"]) );
  }
  return;
}


string get_newick_string( string parent, map< string, vector< pair< string, string > > > tree ){
   string ret = "(";
   unsigned int i = 0;
   for (vector< pair< string, string > >::const_iterator ch = tree[ parent].begin(); ch != tree[ parent ].end(); ++ch, ++i ){
     ret += ch->first + ":" + ch->second;
     if ( i < tree[ parent ].size() - 1){ ret += ' '; }
   }
   return ret + ')' + parent; 

}
