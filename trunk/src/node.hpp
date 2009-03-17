#ifndef NODE_HPP_
#define NODE_HPP_

#include <glibmm/ustring.h>
#include "id.hpp"
#include "annotation.hpp"

namespace NeXML {
  /**
   * Represents a node in a NeXML document
   */
  class Node : public Annotable {
  public:
    /**
     * Initializes the node
     */
    Node( const Glib::ustring& otu ):id_(otu), otu_(otu){}
    /**
     * Cleanup.
     */
    ~Node(){}
    /**
     * Get the node id.
     */
    const Glib::ustring& getid()const{ return id_.getid(); }
    /**
     * Get the name of the associated OTU.
     */
    const Glib::ustring& getotu()const{ return otu_; }
    /**
     * See if the node is the root.
     */
     bool isroot()const{ return isroot_; }
  private:
    ID id_;
    Glib::ustring otu_;
    bool isroot_;
  };
  
}


#endif
