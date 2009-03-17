#ifndef OTUS_HPP_
#define OTUS_HPP_

#include "otu.hpp"
#include "id.hpp"
#include "annotation.hpp"
#include <vector>
#include <map>
#include <glibmm/ustring.h>
#include <fstream>

namespace NeXML {
  /**
   */
  class Otus : public Annotable {
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

    const Glib::ustring& getid()const{ return id_.getid(); }

    friend std::ostream& operator<<( std::ostream& out, const Otus& rhs);
    friend std::ostream& operator<<( std::ostream& out, const Otus* rhs);
  private:
    ID id_;
    std::vector< Otu* > otus_;
    std::map< Glib::ustring, Otu* > otus_by_id_;
  };
  
}

#endif
