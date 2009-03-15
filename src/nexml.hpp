#ifndef NEXML_HPP_
#define NEXML_HPP_
#include <vector>
#include "otus.hpp"
#include "characters.hpp"
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
    void addmatrix( Characters* matrix );
    /**
     */
    unsigned int getnummatrices()const{ return  characters_.size(); }
    /**
     */
    Characters* getmatrix( unsigned int mat )const{ return characters_.at( mat ); }
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
    friend std::ostream& operator<<(std::ostream& out, const Nexml& rhs);
  private:
    Otus* otus_;
    std::vector< Characters* > characters_;
    std::vector< Tree* > trees_;
    std::vector< Network* > networks_;
  };

}

#endif
