#include "node.hpp"
#include <cassert>
#include <utility>


using namespace std;
namespace CDAO {
  unsigned Node::counter_ = 0; 
  class LeafAccumulatorDelegate : public Node::Delegate {
  public:
    LeafAccumulatorDelegate(){ leaves_ = vector< const Node* >(); }
    virtual ~LeafAccumulatorDelegate(){}
    virtual void operator()(const Node* in){ if ( in != NULL && !(in->hasChildren())){ leaves_.push_back( in ); } return; }
    vector< const Node* > getLeaves()const{ return leaves_; }
  private:
    vector< const Node* > leaves_;
  };
  
  void Node::printTree(unsigned int level,  std::ostream& out  )const{
    for (unsigned int i = 0; i < level; ++i ){ out << "  ";}
    out <<"Name:" << this->getLabel() <<" Weight:" << this->getWeight() <<"\n";
    for (unsigned int i = 0; i < descendants_.size(); ++i){
      descendants_[i]->printTree( level + 1, out);
    }
    return;
  }
  
  void Node::preOrderTraversal( Delegate* callback )const{
    assert( callback != NULL );
    doPreOrderTraversal( callback, this);
    return;
  }
  
  void Node::doPreOrderTraversal( Delegate* cb, const Node* current)const{
    assert( cb != NULL );
    if ( current){
      (*cb)( current );
      for( vector<const Node*>::const_iterator it = descendants_.begin(); it != descendants_.end(); ++it){
	(*it)->doPreOrderTraversal( cb, *it );
      }
    }
  }
  
  void Node::postOrderTraversal( Delegate* callback )const{
    assert( callback != NULL );
    doPostOrderTraversal( callback, this);
    return;
  }
  
  void Node::doPostOrderTraversal( Delegate* cb, const Node* current)const{
    if ( current ){
    for( vector<const Node*>::const_iterator it = descendants_.begin(); it != descendants_.end(); ++it){
	(*it)->doPostOrderTraversal( cb, *it );
      }
      (*cb)( current );
    }
  }
  vector<const Node*> Node::getAncestors()const{
    vector<const Node*> ret = vector<const Node*>();
    const Node* current = this;
    while (current->getAncestor()){  
      ret.push_back( (current = current->getAncestor()) );
    }
    return ret;
  }
  
  
  const Node* Node::getMrca(const Node* rhs )const{
    assert( rhs );
    if ( this == rhs){ return this; }
    //if ( ! this->hasAncestor()){ return this; }
    vector<const Node*> myAncestors = this->getAncestors();
    vector<const Node*> rhsAncestors = rhs->getAncestors();
    if (myAncestors.size() && rhsAncestors.size() ){
    //move back through the heirarchy until a mismatch is found.
    //a mismatch will be found since rhs != lhs
    reverse( myAncestors.begin(), myAncestors.end()  );
    reverse( rhsAncestors.begin(), rhsAncestors.end() );
    
    pair<vector<const Node*>::const_iterator, vector<const Node*>::const_iterator> 
      first_mismatch;
    if (myAncestors.size() > rhsAncestors.size()){
     first_mismatch = mismatch( myAncestors.begin(), 
				myAncestors.end(), 
				rhsAncestors.begin());
    }
    else {
      first_mismatch = mismatch(rhsAncestors.begin(), rhsAncestors.end(), myAncestors.begin()  );
    }
    if (first_mismatch.first == myAncestors.begin()){
      /*Nodes have no ancestors in common! */
      return NULL;
    }
    else {
      //the Node just before the mismatch is the last that was in common.
      //i.e. the most recent common ancestor.
      return *(--(first_mismatch.first));
    }
    }
    else { return this; }
  }
  const vector< const Node*> Node::getAllDescendants()const{
    vector < const Node* > ret = vector< const Node* >();
    if (this->hasChildren()){
      vector< const Node* > children = this->getDescendants();
      for (vector< const Node* >::const_iterator i = children.begin(); i != children.end(); ++i){
	vector< const Node* > allDesc = (*i)->getAllDescendants();
	ret.insert( ret.end(), allDesc.begin(), allDesc.end() );
	//ret.push_back( *i );
      }
     
    }
    ret.push_back ( this );
    return ret;
  }
  const vector< const Node* > Node::getLeaves( const  Node* in )const{
    vector< const Node* > ret = vector< const Node* >();
    Delegate* lad = new LeafAccumulatorDelegate();
    this->preOrderTraversal( lad );
    ret = dynamic_cast< LeafAccumulatorDelegate* >(lad)->getLeaves();
    delete lad;
    /*if (NULL != in){
      if ( in->hasChildren() ){
	// get the leaves of the children and merge them. 
	vector< const Node* > children = in->getDescendants();
	for (vector< const Node* >::const_iterator i = children.begin(); i != children.end(); ++i){
	  vector< const Node* > leaves = getLeaves( *i );
	  ret.insert( ret.end(), leaves.begin(), leaves.end()  );
	}
      }
      else {
	//base case
	ret.push_back( in );
      }
    }
    */
    return ret;
  }

}

