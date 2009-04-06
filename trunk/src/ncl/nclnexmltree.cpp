#include "nclnexmltree.hpp"
//#include "tree.h"
//#include "nclxsltxx.hpp"

#include <cassert>

using namespace std;
using namespace NeXML;

static string get_newick_string( const NeXML::Node* current, const NeXML::Network* tree );
static Network* parse_newick_string( string tree );

/*
 * Initialize the trees block
 */
NxsNexmlTree::NxsNexmlTree(  NeXML::Trees* trees){
   
    trees_ = trees;

    index_sets_ = map< string, NxsUnsignedSet >();
    partition_sets_ = map< string, NxsPartition >();
}

NxsNexmlTree::NxsNexmlTree( NxsTreesBlock& nxstrees, const Otus* otus){
  
    trees_ = new Trees( otus );
    
    for (unsigned i = 0; i < nxstrees.GetNumTrees(); ++i ){
       trees_->addgraph(  parse_newick_string( nxstrees.GetTreeDescription( i ) ) );
    }

    index_sets_ = map< string, NxsUnsignedSet >();
    partition_sets_ = map< string, NxsPartition >();

}

/* Clean-up private info. */
NxsNexmlTree::~NxsNexmlTree(){
  delete trees_;
  index_sets_.empty();
  partition_sets_.empty();
}

 /*NCL Trees interface*/
unsigned	NxsNexmlTree::GetNumDefaultTree(){ return 1; }

//return the number of trees in the description.
unsigned	NxsNexmlTree::GetNumTrees(){ return this->trees_->getnumtrees(); }
unsigned	NxsNexmlTree::GetNumTrees()const{ return this->trees_->getnumtrees(); }


//retrieve the name of a particular tree.
NxsString	NxsNexmlTree::GetTreeName(unsigned i){ 
  assert( i < this->GetNumTrees()); 
  return NxsString(this->trees_->getgraph( i )->getlabel().c_str()); 
}

//Retrieve a particular tree description
NxsString	NxsNexmlTree::GetTreeDescription(unsigned i){
      return NxsString( get_newick_string( trees_->getgraph( i )->getnode( 0 ) , trees_->getgraph( i ) ).c_str() );
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
  return trees_->getgraph( i )->hasroot() ; 
}
//get the maximum valid tree index.
unsigned int    NxsNexmlTree::GetMaxIndex()const{
   return this->GetNumTrees() - 1;
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

string get_newick_string( const NeXML::Node* current, const NeXML::Network* tree ){
      if ( current && tree ) {
        string ret = "(";
        vector< const NeXML::Node* > children = tree->getchildren( current );
        for ( vector< const NeXML::Node* >::const_iterator child = children.begin(); child != children.end(); ++child){
              ret += (*child)->getlabel() + ":" + tree->getedge( current, *child)->getlength() + " " +  get_newick_string( *child, tree );
        }
        ret += ")" + current->getlabel();
        return ret;
   }
   //unsigned int i = 0;
   //for (vector< pair< string, string > >::const_iterator ch = tree[ parent].begin(); ch != tree[ parent ].end(); ++ch, ++i ){
    // ret += ch->first + ":" + ch->second;
   //  if ( i < tree[ parent ].size() - 1){ ret += ' '; }
  // }
   return ""; 

}

static Network* parse_newick_string( string tree ){
 return NULL;
}

