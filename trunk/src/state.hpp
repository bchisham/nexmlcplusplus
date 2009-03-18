#ifndef STATE_HPP_
#define STATE_HPP_

#include <fstream>
#include <glibmm/ustring.h>

#include "id.hpp"
#include "annotation.hpp"
namespace NeXML {
  /**
   * @author Brandon Chisham
   * @date March 15, 2009
   * State represents a state definition.
   */
  class State : public Annotable, 
                public Identifiable {
  public:
    /**
     * Initialize the state
     */
    State( const Glib::ustring& label, const Glib::ustring& symbol):Annotable(), 
                                                     Identifiable( label + symbol ), 
                                                     label_(label), 
                                                     symbol_(symbol){}
    /**
     * Cleanup the state
     */
    ~State(){}
    /**
     * Set the label.
     */
    void setlabel( const Glib::ustring& l ){ label_ = l; this->setid( l + symbol_ ); }
    /**
     * Get the state label.
     */
    Glib::ustring getlabel()const{ return label_; }
    /**
     * Set the symbol. 
     */
    void setsymbol( const Glib::ustring& s){ symbol_ = s; this->setid( label_ + s ); }
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
    //ID id_;
    Glib::ustring label_;
    Glib::ustring symbol_;
  };

}

#endif
