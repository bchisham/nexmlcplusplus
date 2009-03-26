#ifndef TREES_HPP_
#define TREES_HPP_

#include <fstream>
#include <vector>
#include <map>
#include "network.hpp"
#include "tree.hpp"
#include "otus.hpp"
#include "id.hpp"
#include "serializable.hpp"
#include "annotation.hpp"

namespace NeXML {
  /**
   * Represents a nexml trees block
   */
  class Trees : public Annotable,
                public Identifiable,
                public Serializable {

  public:
    /**
     * Initialize with the specified otus block
     */
    Trees( const Otus* otus ):Annotable(),
                              Identifiable( "trees" + otus->getid() ),
                              Serializable(), trees_(), trees_by_label_(){}
    ~Trees();
    /**
     * Add a new tree to the set.
     */
    void addgraph( const Network* graph );
    /**
     * Get a tree from the set.
     */
    const Network* getgraph( unsigned int i )const{ return i < trees_.size() ? trees_.at( i ) : NULL ; }
    const Network* getgraph( const Glib::ustring label)const;
    /**
     * Get the number of trees in the set.
     */
    const unsigned int getnumtrees()const{ return trees_.size(); }
    
    void setotus( const Otus* o ){ if (o){ otus_ = o; setid("trees" + otus_->getid());} return;}

    /**
     * Serialize
     */
     friend std::ostream& operator<<( std::ostream& out, const Trees& rhs ){ return rhs.serialize( out ); }
     friend std::ostream& operator<<( std::ostream& out, const Trees* rhs ){ if (rhs){ rhs->serialize( out ); } return out; }
     std::ostream& serialize( std::ostream& out )const;

  private:
    const Otus* otus_;
    std::vector< const Network* > trees_;
    std::map< Glib::ustring, const Network* > trees_by_label_;
  };
}
#endif
