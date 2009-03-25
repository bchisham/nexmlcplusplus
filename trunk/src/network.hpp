#ifndef NETWORK_HPP_
#define NETWORK_HPP_
#include <map>
#include <vector>
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
          nodes_ = std::vector< const Node* >();
          edges_by_id_ = std::map< Glib::ustring, const Edge* >();
          edges_ = std::vector< const Edge* >();
                                     }
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
    std::ostream& serialize( std::ostream& out )const;
    friend std::ostream& operator<<(std::ostream& out, const Network& rhs){ return rhs.serialize( out );}
    friend std::ostream& operator<<(std::ostream& out, const Network* rhs){ 
       if (rhs){ rhs->serialize( out ); }
       return out;
    }
  protected: 
    Glib::ustring label_;
    Glib::ustring type_;
    std::vector< const Node* > nodes_;
    std::map< Glib::ustring, const Edge* > edges_by_id_;
    std::vector< const Edge* > edges_;
  };
}

#endif
