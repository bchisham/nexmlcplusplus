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
    Network(Glib::ustring label = "", 
            Glib::ustring type = ""):Annotable(), 
                                     Identifiable(label+type),
                                     label_(label),
                                     type_(type_),
                                     nodes_(), 
                                     edges_by_id_(), 
                                     edges_(){}
    /**
     * Clean-up
     */
    ~Network();
    /**
     * Get the label
     */
    const Glib::ustring getlabel()const{ return label_; }
    /**
     * Get the type.
     */
    const Glib::ustring gettype()const{ return type_; }
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
    Glib::ustring label_;
    Glib::ustring type_;
    std::vector< const Node* > nodes_;
    std::map< Glib::ustring, const Edge* > edges_by_id_;
    std::vector< const Edge* > edges_;
  };
}

#endif
