#ifndef STATES_HPP_
#define STATES_HPP_

#include <fstream>
#include <vector>

#include "id.hpp"
#include "annotation.hpp"
#include "serializable.hpp"

#include "state.hpp"

namespace NeXML {
  /**
   * Represents a NeXML states block
   */
  class States : public Annotable, 
                 public Identifiable,
                 public Serializable {
  public:
    /**
     * Create an empty block
     */
    States(const Glib::ustring& id=""):Annotable(), 
                                       Identifiable( id ), 
                                       Serializable(),
                                       states_(){}
    /**
     * Clean-up.
     */
    ~States();
    /**
     * Add a new state to the block
     */
    void addstate( const State* state );
    /**
     * Get the specified state.
     */
    const State* getstate( const Glib::ustring&  i )const;
    const State* getstate( const unsigned i )const;
    /**
     * Serialize the block.
     */
    friend std::ostream& operator<<( std::ostream& out, const States& rhs ){ return rhs.serialize( out ); }
    friend std::ostream& operator<<( std::ostream& out, const States* rhs ){ if (rhs){ rhs->serialize( out );}  return out; }
    std::ostream& serialize( std::ostream& out )const;
  private:
    //ID id_;
    std::vector< const State* > states_;
  };

}

#endif
