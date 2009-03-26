#ifndef NETWORK_HPP_
#define NETWORK_HPP_
#include <map>
#include <vector>
#include <set>
#include <glibmm/ustring.h>
#include "node.hpp"
#include "edge.hpp"
#include "annotation.hpp"
#include "id.hpp"
#include "serializable.hpp"
#ifdef EBUG_V
#include <iostream>
#endif
namespace NeXML {
  /**
   * Represents a network/tree 
   */
  class Network : public Annotable,
                  public Identifiable,
                  public Serializable{
  public:
    /**
     *
     */
    Network(Glib::ustring label, 
            Glib::ustring type ):Annotable(), 
                                 Identifiable(label+type),
                                 Serializable() {
#ifdef EBUG_V_NET
          std::cerr << "Network( label: " << label << ", type: " << type << ")" << std::endl;
#endif
          label_ = label;
          type_ = type;
          root_ = NULL;
          nodes_ = std::vector< const Node* >();
          nodes_by_id_ = std::map< Glib::ustring, const Node* >();
          edges_by_id_ = std::map< Glib::ustring, const Edge* >();
          edges_ = std::vector< const Edge* >();
          targets_ = std::map< const Node*, std::vector< const Node* > >();
          source_ = std::map< const Node*,  const Node*  >();
    }
    /**
     * Clean-up
     */
    ~Network();
    const bool hasroot()const{ return root_ != NULL; }
    /**
     * Get the label
     */
    const Glib::ustring getlabel()const{ return label_; }
    /**
     * Get the type.
     */
    const Glib::ustring gettype()const{ return type_; }
    /**
     * Get the specified node.
     */
    const Node* getnode(const  Glib::ustring& id )const;
    const Node* getnode( const unsigned i )const{ return i < nodes_.size() ? nodes_.at( i ) : NULL; }
    /**
     * Add a new node
     */
    void addnode( const Node* node );
    /**
     * Get the specified edge
     */
    const Edge* getedge( const Glib::ustring& id )const;
    const Edge* getedge( const unsigned i )const{ return i < edges_.size() ? edges_.at( i )  : NULL; }
    const Edge* getedge( const Node*, const Node* )const;
    /**
     * Get the immedate descendants of the specified node.
     * For networks edges don't have directions but NeXML 
     * encodes all edges in a uniform way, so don't let the 
     * name fool you the edges are only actually directed if
     * this is called from a Tree instance.
     */
    std::vector< const Node* > getchildren( const Node* )const;
    /**
     * Get the immedate ancestor of the specified node.
     */
     const Node* getparent( const Node* )const;
    /**
     * Add a new edge.
     */
    void addedge( const Edge* );
    /**
     * Serializable interface.
     */
    virtual std::ostream& serialize( std::ostream& out )const;
    friend std::ostream& operator<<(std::ostream& out, const Network& rhs){ return rhs.serialize( out );}
    friend std::ostream& operator<<(std::ostream& out, const Network* rhs){ 
       if (rhs){ rhs->serialize( out ); }
       return out;
    }
  protected: 
    Glib::ustring label_;
    Glib::ustring type_;
    const Node* root_;
    std::vector< const Node* > nodes_;
    std::map< Glib::ustring, const Node* > nodes_by_id_;
    std::map< Glib::ustring, const Edge* > edges_by_id_;
    std::map< const Node*, std::vector< const Node* > > targets_;
    std::map< const Node*,  const Node* > source_;
    std::vector< const Edge* > edges_;
  };
}

#endif
