#ifndef EDGE_HPP_
#define EDGE_HPP_

#include "id.hpp"
#include "annotation.hpp"
#include "node.hpp"
#include "serializable.hpp"
#include <glibmm/ustring.h>

namespace NeXML {
  /**
   * Edge represents a single edge in Tree or Network.
   */
  class Edge : public Annotable, public Identifiable, public Serializable {
  public:
    /**
     * Initialize the edge with the specified source and target nodes.
     */
    Edge( const Node* src, const Node* target):Annotable(), 
                                               Identifiable(),
                                               src_(src), 
                                               target_(target){ updateid();}
    //const Glib::ustring& getid()const{ return id_.getid(); }
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
    /**
     * Serialize
     */
    friend std::ostream& operator<<( std::ostream& out, const Edge& rhs);
    /**
     * Serialize
     */
    friend std::ostream& operator<<( std::ostream& out, const Edge* rhs);
    /**
     * Serialize
     */
    std::ostream& serialize( std::ostream& out )const;
    /**
     * Compare edges.
     */
    const bool operator==( const Edge& rhs )const{ return this == &rhs || this->getid() == rhs.getid(); }
    const bool operator!=( const Edge& rhs )const{ return !( *this == rhs ); }
    const bool operator<(  const Edge& rhs )const{ return this->getid() < rhs.getid(); }
  protected:
    /**
     * Update the edge id.
     */
    void updateid();
  private:
    //ID id_;
    const Node* src_;
    const Node* target_;
  };
  /**
   *
   */
  class Rootedge : public Edge, public Serializable {
  public:
     /**
      *
      */
     Rootedge( const Node* target ):Edge( NULL, target ),Serializable(){}
     /**
      *
      */
     virtual ~Rootedge(){}
     /**
      * Serialize
      */
     friend std::ostream& operator<<( std::ostream& out, const Rootedge& rhs){ return rhs.serialize( out ); }
     /**
      * Serialize
      */
     friend std::ostream& operator<<( std::ostream& out, const Rootedge* rhs){ if (rhs) rhs->serialize( out ); return out;}
     /**
      * Serialize
      */
     std::ostream& serialize( std::ostream& out )const;
  private:
  };

}

#endif
