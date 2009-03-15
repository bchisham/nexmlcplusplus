#ifndef STATE_HPP_
#define STATE_HPP_

#include <fstream>
#include <glibmm/ustring.h>

#include "id.hpp"
namespace NeXML {
  /**
   * @author Brandon Chisham
   * @date March 15, 2009
   * State represents a state definition.
   */
  class State {
  public:
    /**
     * Initialize the state
     */
    State(Glib::ustring label, Glib::ustring symbol):id_(label), label_(label), symbol_(symbol){}
    /**
     * Cleanup the state
     */
    ~State(){}
    /**
     * Set the label.
     */
    void setlabel( Glib::ustring l ){ label_ = l; id_.setid( l ); }
    /**
     * Get the state label.
     */
    Glib::ustring getlabel()const{ return label_; }
    /**
     * Get the state symbol.
     */
    Glib::ustring getsymbol()const{ return symbol_; }
    /**
     * Serialize the state.
     */
    friend std::ostream& operator<<( std::ostream& out, const State& rhs);
    friend std::ostream& operator<<( std::ostream& out, const State* rhs);
  private:
    ID id_;
    Glib::ustring label_;
    Glib::ustring symbol_;
  };

}

#endif
