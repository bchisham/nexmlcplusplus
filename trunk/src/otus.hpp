#ifndef OTUS_HPP_
#define OTUS_HPP_

#include "otu.hpp"
#include <vector>
#include <map>
#include <glibmm/ustring.h>
namespace NeXML {
  /**
   */
  class Otus {
  public:
    /**
     */
    Otus();
    /**
     */
    ~Otus();
    /**
     */
    void addotu( Otu* otu );
    /**
     */
    Otu* getotu( unsigned int otu )const{ return otus_.at( otu ); }
    /**
     */
    Otu* getotu( Glib::ustring id )const;
  private:
    std::vector< Otu* > otus_;
    std::map< Glib::ustring, Otu* > otus_by_id_;
  };
  
}

#endif
