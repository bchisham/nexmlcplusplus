#include "nclnexmltree.hpp"
//#include "tree.h"
//#include "nclxsltxx.hpp"

#include "tree_description_parser.hpp"
#include "node.hpp"
#include "../tree.hpp"
#include "../network.hpp"
#include "../node.hpp"
#include "../id.hpp"
#include <cassert>

using namespace std;
using namespace NeXML;
using namespace CDAO;

static string get_newick_string( const NeXML::Node* current, const NeXML::Network* tree );
static Network* parse_newick_string( string tree, const NeXML::Otus* otus );
/**
 * Delegate to process a CDAO node from the tree description parse and produce
 * a network with nexml nodes.
 */
class parse_node_to_nex_node : public CDAO::Node::Delegate {
  public:
    /**
     * Creates an empty network and prepares the delegate for use.
     */
    parse_node_to_nex_node(Glib::ustring label, Glib::ustring type, const NeXML::Otus* otus):net_( new Network( label, type ) ), otus_(otus){}
    /**
     * Clean-up
     */
    virtual ~parse_node_to_nex_node(){}
    /**
     * Delegate interface implementation.
     */
    virtual void operator()(const CDAO::Node* in){ doConversion( in ); }
    /**
     * Retrieve the partially constructed network
     */
    NeXML::Network* getnetwork()const{ return net_; }
  private:
    /**
     * Do the conversion from a CDAO::Node to a NeXML::Node
     */
    void doConversion( const CDAO::Node* in ){
      if (in->hasChildren()){
         //this is an internal node it doesn't have an associated otu.
         if (in->hasAncestor()){
           net_->addnode( new NeXML::Node( in->getLabel() ) );
         }
         else {
           //this node doesn't have an ancestor it must be the root.
           net_->addnode( new NeXML::Node( in->getLabel(), NULL, true ) );
         }
      }
      else {
         //this is a terminal node it should be associated with an otu.
         ID otuid = ID( in->getLabel() );
         net_->addnode( new NeXML::Node( in->getLabel(), otus_->getotu(otuid.getid()) ) );
      }
      return;
    }
    NeXML::Network* net_;
    const NeXML::Otus* otus_;
};
/**
 * Create edge instances based on the already converted nodes and the 
 * parsetree of CDAO nodes
 */
class process_edges : public CDAO::Node::Delegate {
  public:
    /**
     * Net is the partially constructed Network obtained after applying
     * the parse_node_to_nex_node delegate has been applied to the parsetree.
     */
    process_edges( NeXML::Network* net/*, NeXML::Otus* otus*/ ):net_( net )/*, 
                                                               otus_(otus)*/{}
    /**
     * Cleanup
     */
    virtual ~process_edges(){}
    /**
     * Delegate Interface
     */
    virtual void operator()(const CDAO::Node* in){ doConversion( in ); }
    /**
     * Get the constructed network.
     */
    NeXML::Network* getnetwork()const{ return net_; }
  private:
    /**
     * Do the edge creation.
     */
    void doConversion(const CDAO::Node* in){
         const vector< const CDAO::Node* > children = in->getDescendants();
         ID parent_id = ID( in->getLabel() );
         for (vector< const CDAO::Node* >::const_iterator i = children.begin(); i != children.end(); ++i ){
            ID child_id = ID( (*i)->getLabel() );
            const NeXML::Node* parent = net_->getnode( parent_id.getid() );
            const NeXML::Node* child  = net_->getnode( child_id.getid() );
            net_->addedge( new NeXML::Edge( parent, child, convert( (*i)->getWeight() ) ) );
         }
       
    }
    NeXML::Network* net_;
    //NeXML::Otus* otus_;
};

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
       trees_->addgraph(  parse_newick_string( nxstrees.GetTreeDescription( i ), otus ) );
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

static Network* parse_newick_string( string tree, const NeXML::Otus* otus ){
  TreeDescriptionParser parser = TreeDescriptionParser( tree );
  CDAO::Node* parsetree = parser.getParseTree();
  NeXML::Network* ret = NULL;
  if ( parsetree ){
    //TODO find a reasonable way of getting the type.
    parse_node_to_nex_node pntnn = parse_node_to_nex_node( parsetree->getLabel(),"FloatTree",otus);
    parsetree->preOrderTraversal( &pntnn  );
    ret = pntnn.getnetwork();
    process_edges pe = process_edges( ret );
    parsetree->preOrderTraversal( &pe );
  }
 return ret;
}

