#ifndef NEXML_HPP_
#define NEXML_HPP_
#include <vector>
#include "otus.hpp"
#include "matrix.hpp"
#include "tree.hpp"
#include "network.hpp"


namespace NeXML {
  /**
   */
  class Nexml {
  public:
    Nexml();
    ~Nexml();
    /**
     */
    void setotus( Otus* otus );
    /**
     */
    Otus* getotus( )const{ return otus_; }
    /**
     */
    void addmatrix( Matrix* matrix );
    /**
     */
    unsigned int getnummatrices()const{ return  matrices_.size(); }
    /**
     */
    Matrix* getmatrix( unsigned int mat )const{ return matrices_.at( mat ); }
    /**
     */
    void addtree( Tree* tree );
    /**
     */
    unsigned int getnumtrees()const{ return trees_.size(); }
    /**
     */
    Tree* gettree( unsigned int tree )const{ return trees_.at( tree ); }
    /**
     */
    void addnetwork( Network* network );
    /**
     */
    unsigned int getnumnetworks()const{ return networks_.size(); }
    /**
     */
    Network* getnetwork( unsigned int net )const{ return networks_.at( net ); }
  private:
    Otus* otus_;
    std::vector< Matrix* > matrices_;
    std::vector< Tree* > trees_;
    std::vector< Network* > networks_;
  };

}

#endif
