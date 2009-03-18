#ifndef NETWORK_HPP_
#define NETWORK_HPP_
#include <map>
#include <vector>
#include <glibmm/ustring.h>
#include "node.hpp"
#include "edge.hpp"
#include "annotation.hpp"
#include "id.hpp"
namespace NeXML {
  /**
   * Represents a network/tree 
   */
  class Network : public Annotable,
                  public Identifiable {
  public:
    /**
     *
     */
    Network():Annotable(), 
              Identifiable(), 
              nodes_(), 
              edges_by_id_(), 
              edges_(){}
    /**
     * Clean-up
     */
    ~Network();
    /**
     *
     */
    Node* getnode(const  Glib::ustring& id );
    /**
     *
     */
    void addnode( const Node* node );
    /**
     *
     */
    Edge* getedge( const Glib::ustring& id );
    /**
     *
     */
    void addedge( const Edge* );
  protected:  
    std::vector< const Node* > nodes_;
    std::map< Glib::ustring, const Edge* > edges_by_id_;
    std::vector< const Edge* > edges_;
  };
}

#endif
