#ifndef EDGE_HPP_
#define EDGE_HPP_

#include "id.hpp"
#include "annotation.hpp"
#include "node.hpp"
#include <glibmm/ustring.h>

namespace NeXML {
  /**
   * Edge represents a single edge in Tree or Network.
   */
  class Edge : public Annotable {
  public:
    /**
     * Initialize the edge with the specified source and target nodes.
     */
    Edge( const Node* src, const Node* target):id_( ),
                                   src_(src), 
                                   target_(target){ updateid();}
    const Glib::ustring& getid()const{ return id_.getid(); }
    /**
     * Change the source node id.
     */
    void setsource( const Node* src );
    /**
     * Get the source node id.
     */
    const Node* getsource()const{ return src_; }
    /**
     * Set the target node id.
     */
    void settarget( const Node* target);
    /**
     * Get the target node id.
     */
    const Node* gettarget()const{ return target_; }
    friend std::ostream& operator<<( std::ostream& out, const Edge& rhs);
    friend std::ostream& operator<<( std::ostream& out, const Edge* rhs);
  protected:
    /**
     * Update the edge id.
     */
    void updateid();
  private:
    ID id_;
    const Node* src_;
    const Node* target_;
  };
  
}

#endif
