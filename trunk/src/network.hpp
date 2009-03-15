#ifndef NETWORK_HPP_
#define NETWORK_HPP_
#include <map>
#include <glibmm/ustring.h>
#include "node.hpp"
#include "edge.hpp"

namespace NeXML {
  /**
   *
   */
  class Network {
  public:
    /**
     *
     */
    Network():nodes_(), edges_(){}
    /**
     *
     */
    ~Network();
    /**
     *
     */
    Node* getnode( Glib::ustring& id );
    /**
     *
     */
    Edge* getedge( Glib::ustring& id );
  protected:  
    std::map< Glib::ustring, Node* > nodes_;
    std::map< Glib::ustring, Edge* > edges_;
  };
}

#endif
