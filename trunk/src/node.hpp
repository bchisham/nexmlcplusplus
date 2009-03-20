#ifndef NODE_HPP_
#define NODE_HPP_

#include <glibmm/ustring.h>
#include "id.hpp"
#include "otu.hpp"
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
    Node( const Glib::ustring& label="",  
          const Otu* otu=NULL, bool isroot=false ):Annotable(), 
                                        Identifiable ( label ),
                                        label_( label ),
                                        otu_(otu), 
                                        isroot_(isroot){}
    /**
     * Cleanup.
     */
    ~Node(){}
    /**
     * Get the node id.
     */
    //const Glib::ustring& getid()const{ return id_.getid(); }
    const Glib::ustring& getlabel()const{ return label_; }
    void setlabel( Glib::ustring& label ){ label_ = label; this->setid( label_ + otu_->getid() );}
    /**
     * Get the name of the associated OTU.
     */
    const NeXML::Otu* getotu()const{ return otu_; }
    void setotu( const NeXML::Otu*& otu ){ otu_ = otu; this->setid( label_ + otu_->getid() ); }
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
    const Otu* otu_;
    bool isroot_;
  };
  
}


#endif
