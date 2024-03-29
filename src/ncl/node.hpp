#ifndef CDAO_NODE_HPP_
#define CDAO_NODE_HPP_

#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include <util/util.hpp>
//#include "global_defs.hpp"
namespace CDAO {
  class Node;
  typedef void (*tree_op_t)(const Node*);
  
  /*
   * Represents a single node in the tree i.e. a TU.
   */
  class Node {
    static unsigned counter_;
  public:
    /*
     * A delegate is a functor that wraps a call-back operation
     * for use with the tree traversal interface.
     */
    class Delegate {
    public:
      Delegate(){}
      virtual ~Delegate(){}
      virtual void operator()(const Node* in)=0;
    };
    /*
     * A static function delegate wraps a static c-style function.
     */
    class StaticFunctionDelegate : public Delegate {
    public:
      StaticFunctionDelegate(tree_op_t lambda ):lambda_( lambda ){}
      virtual ~StaticFunctionDelegate(){}
      virtual  void operator()(const Node* in){ (*lambda_)( in ); }
    private:
      tree_op_t lambda_;
    };

    Node(const std::string label="Anonymous", 
	 const Node* ancestor = NULL):label_(label),
    			        ancestor_(ancestor){ 
      descendants_ = std::vector<const Node*>( 0 );
      if (label == "Anonymous"){ label_ += convert( ++counter_ );  } 
    } 
    /*
     * Retrieve the name of the node.
     */
    const std::string& getLabel()const{ return label_; }
    /*
     * Set the name of the node.
     */
    void   setLabel(const std::string& label){ label_ = label;}
    /**
     * Retrieve the node weight
     */
    double getWeight()const{ return weight_; }
    /**
     * Set the node weight.
     */
    void setWeight( double weight ){ weight_ = weight; }
    /*
     * Retrieve the ancestor of the node.
     */
    const Node* getAncestor()const{ return ancestor_; }
    
    const bool hasAncestor()const{ return NULL == ancestor_; }
    /*
     * Get the path back to the root from a given node.
     */
    std::vector<const Node*> getAncestors()const;
    /**
     * Finds the most recent common ancestor between this and rhs.
     */
    const Node* getMrca( const Node* rhs )const;
    
    /*
     * Set the ancestor of the node.
     */
    void setAncestor(Node* ancestor){ this->ancestor_ = ancestor; }
    /*
     * Get descendants of the node.
     */
    const std::vector<const Node*>& getDescendants()const{ return descendants_;}
    const std::vector< const Node*> getAllDescendants()const;
    /**
     * Collects and returns all the leaves that are descendants of the given node.
     */
    const std::vector<const Node*> getLeaves( const Node* )const;
    /*
     * Add a descendant to the node.
     */
    void addDescendant(const Node* descendant ){ descendants_.push_back(descendant); }
    /*
     * Print a representation of the tree.
     */
    void printTree(unsigned int level=0,  std::ostream& out=std::cout  )const;
    /*
     * Determines if the node does or does not have any children
     */
    bool hasChildren()const{ return descendants_.size() ;  }
    /*
     * Process the tree pre-order with the specified deligate.
     */
    void preOrderTraversal( Delegate* callback )const;
    /*
     * Process the tree post-order with the specified deligate.
     */
    void postOrderTraversal( Delegate* callback)const;
  private:
    /*
     * Do the pre order traversal.
     */
    void doPreOrderTraversal( Delegate* cb, const Node* current)const;
    /*
     * Do the post order traversal.
     */
    void doPostOrderTraversal( Delegate* cb, const Node* current)const;
    
    std::string label_;
    double weight_;
    const Node* ancestor_;
    std::vector<const Node*> descendants_;
    
    
  }; 
  
}


#endif
