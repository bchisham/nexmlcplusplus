#ifndef STATE_HPP_
#define STATE_HPP_

#include <fstream>
#include <set>
#include <glibmm/ustring.h>
#include <algorithm>
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
    //Comparable interface
    const bool operator==( const State& rhs )const{ return this ==&rhs || label_ == rhs.label_; }
    const bool operator<(const State& rhs)const{ return label_ < rhs.label_; }
    //convenience for the state set.
    friend const bool operator==( const State& lhs, const Glib::ustring& rhs){
        return lhs.label_ == rhs;
    }
    friend const bool operator==( const State* lhs, const Glib::ustring& rhs){
        if (lhs){ return *lhs == rhs; }
        return false;
    }
    friend const bool operator==( const Glib::ustring& rhs, const State* lhs){
        if (lhs){ return *lhs == rhs; }
        return false;
    }

    friend const bool operator<( const State* lhs, const Glib::ustring& rhs){
        if (lhs){ return lhs->label_ < rhs; }
        return false;
    }
    friend const bool operator<( const Glib::ustring& rhs, const State* lhs ){
        if (lhs){ return lhs->label_ < rhs; }
        return false;
    }

  private:
    //ID id_;
    Glib::ustring label_;
    Glib::ustring symbol_;
  };

  /**
   *
   */
  class StateSet {
  public:
    /**
     *
     */
    StateSet():members_(){}
    /**
     *
     */
    virtual ~StateSet();
    /**
     *
     */
    void addstate( const State* state){ members_.insert( state ); }
    /**
     *
     */
    const bool hasstate( const Glib::ustring& label){ 
      return binary_search(members_.begin(), members_.end(), label); 
    }
  private:
    std::set< const State* > members_;
  };

  class UncertainState : public State,
                         private StateSet {
   public:
     UncertainState(const Glib::ustring& label, 
                    const Glib::ustring& symbol):State(label, symbol),
                                                 StateSet(){}
     ~UncertainState(){}
   private:
  };

  class PolymorphicState : public State,
                           private StateSet {
   public:
     PolymorphicState(const Glib::ustring& label, 
                      const Glib::ustring& symbol):State(label, symbol),
                                                   StateSet(){}
     ~PolymorphicState(){}
   private:
  };

}

#endif
