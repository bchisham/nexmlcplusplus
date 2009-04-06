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
   * Represents a collection of Otus.
   */
  class Otus : public Annotable, public Identifiable, public Serializable  {
  public:
    /**
     * Create an empty set of Otus.
     */
    Otus();
    Otus( std::vector< Otu* > in );
    /**
     * Clean-up
     */
    ~Otus();
    /**
     * Add a new otu.
     */
    void addotu( Otu* otu );
    /**
     * Get the specified otu.
     */
    Otu* getotu( unsigned int otu )const{ return otus_.at( otu ); }
    /**
     * Get the specified otu
     */
    Otu* getotu( Glib::ustring id )const;
    /**
     * Get the total number of otus.
     */
    const unsigned int size()const{ return otus_.size(); }

    //const Glib::ustring& getid()const{ return id_.getid(); }
    /**
     * Output for instances.
     */
    friend std::ostream& operator<<( std::ostream& out, const Otus& rhs){ return rhs.serialize( out ); }
    /**
     * output for pointers to instances
     */
    friend std::ostream& operator<<( std::ostream& out, const Otus* rhs){ if (rhs){ rhs->serialize( out ); } return out; }
    /**
     * Serializable interface
     */
    std::ostream& serialize( std::ostream& out )const;
  private:
   // ID id_;
    std::vector< Otu* > otus_;
    std::map< Glib::ustring, Otu* > otus_by_id_;
  };
  
}

#endif
