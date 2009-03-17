#ifndef NETWORK_HPP_
#define NETWORK_HPP_
#include <map>
#include <vector>
#include <glibmm/ustring.h>
#include "node.hpp"
#include "edge.hpp"
#include "annotation.hpp"

namespace NeXML {
  /**
   *
   */
  class Network : public Annotable {
  public:
    /**
     *
     */
    Network():nodes_(), edges_by_id_(), edges_(){}
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
    void addnode(  Node* node );
    /**
     *
     */
    Edge* getedge( Glib::ustring& id );
    /**
     *
     */
    void addedge( Edge* );
  protected:  
    std::map< Glib::ustring, Node* > nodes_;
    std::map< Glib::ustring, Edge* > edges_by_id_;
    std::vector< Edge* > edges_;
  };
}

#endif
