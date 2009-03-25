#ifndef OTUS_HPP_
#define OTUS_HPP_

#include "otu.hpp"
#include "id.hpp"
#include "annotation.hpp"
#include <vector>
#include <map>
#include <glibmm/ustring.h>
#include <fstream>
#include "serializable.hpp"
namespace NeXML {
  /**
   */
  class Otus : public Annotable, public Identifiable, public Serializable  {
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
     
    const unsigned int size()const{ return otus_.size(); }

    //const Glib::ustring& getid()const{ return id_.getid(); }

    friend std::ostream& operator<<( std::ostream& out, const Otus& rhs){ return rhs.serialize( out ); }
    friend std::ostream& operator<<( std::ostream& out, const Otus* rhs){ if (rhs){ rhs->serialize( out ); } return out; }
    std::ostream& serialize( std::ostream& out )const;
  private:
   // ID id_;
    std::vector< Otu* > otus_;
    std::map< Glib::ustring, Otu* > otus_by_id_;
  };
  
}

#endif
