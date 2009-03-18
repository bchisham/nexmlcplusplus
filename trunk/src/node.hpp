#ifndef NODE_HPP_
#define NODE_HPP_

#include <glibmm/ustring.h>
#include "id.hpp"
#include "annotation.hpp"
#include <fstream>
namespace NeXML {
  /**
   * Represents a node in a NeXML document
   */
  class Node : public Annotable,
               public Identifiable {
  public:
    /**
     * Initializes the node
     */
    Node( const Glib::ustring& label,  
          const Glib::ustring& otu ):Annotable(), Identifiable ( label + otu ), label_( label ),otu_(otu){}
    /**
     * Cleanup.
     */
    ~Node(){}
    /**
     * Get the node id.
     */
    //const Glib::ustring& getid()const{ return id_.getid(); }
    const Glib::ustring& getlabel()const{ return label_; }
    void setlabel( Glib::ustring& label ){ label_ = label; this->setid( label_ + otu_ );}
    /**
     * Get the name of the associated OTU.
     */
    const Glib::ustring& getotu()const{ return otu_; }
    void setotu( const Glib::ustring& otu ){ otu_ = otu; this->setid( label_ + otu_ ); }
    /**
     * See if the node is the root.
     */
     bool isroot()const{ return isroot_; }
    /**
     * Declare the node to be a root node.
     */
     void setroot(bool root){ isroot_ = root;}
     friend std::ostream& operator<<( std::ostream& out, const Node& rhs );
     friend std::ostream& operator<<( std::ostream& out, const Node* rhs );
  private:
   // ID id_;
    Glib::ustring label_;
    Glib::ustring otu_;
    bool isroot_;
  };
  
}


#endif
