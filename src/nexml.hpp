#ifndef NEXML_HPP_
#define NEXML_HPP_
#include <vector>
#include "otus.hpp"
#include "characters.hpp"
//#include "tree.hpp"
#include "network.hpp"
#include "annotation.hpp"
#include "serializable.hpp"
#include "trees.hpp"

namespace NeXML {
  /**
   * Represents a Nexml document
   */
  class Nexml : public Annotable,
                public Serializable {
  public:
    Nexml();
    ~Nexml();
    /**
     * (re)set the otus block. 
     */
    void setotus( Otus* otus );
    /**
     * get the otus block
     */
    Otus* getotus( )const{ return otus_; }
    Otus* getotus( ){ return otus_;}
    /**
     *  add a new matrix (including state and character definitions).
     */
    void addmatrix( Characters* matrix );
    /**
     *  Get the number of matrices in the document.
     */
    unsigned int getnummatrices()const{ return  characters_.size(); }
    /**
     * Get the specified matrix (including state and character definitions).
     */
    const Characters* getmatrix( unsigned int mat )const{ return mat < characters_.size() ? characters_.at( mat ) : NULL ; }
    Characters* getmatrix( unsigned int mat ){ return mat < characters_.size() ? characters_.at( mat ) : NULL ; }

    /**
     * Get the trees block
     */
    const Trees* gettrees()const{ return trees_;}
    Trees* gettrees(){ return trees_; }
    /**
     * (re)set the trees block.
     */
    void settrees( Trees* t );
    /**
     * Serialize
     */
    friend std::ostream& operator<<( std::ostream& out, const Nexml& rhs );
    /**
     * Serialize
     */
    friend std::ostream& operator<<( std::ostream& out, const Nexml* rhs );
    /**
     * Serialize
     */
    virtual std::ostream& serialize( std::ostream& out )const;
  private:
    Otus* otus_;
    Trees* trees_;
    std::vector< Characters* > characters_;
  };

}

#endif
