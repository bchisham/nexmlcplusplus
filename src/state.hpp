#ifndef STATE_HPP_
#define STATE_HPP_

#include <fstream>
#include <set>
#include <glibmm/ustring.h>
#include <algorithm>
#include "id.hpp"
#include "annotation.hpp"
#include "serializable.hpp"
namespace NeXML {
  /**
   * @author Brandon Chisham
   * @date March 15, 2009
   * State represents a state definition.
   */
  class State : public Annotable, 
                public Identifiable,
                public Serializable {
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
    virtual ~State(){}
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
    //These operators support searching for states in STL containers based
    //on some label. 
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
    std::ostream& serialize( std::ostream& out )const;
  private:
    //ID id_;
    Glib::ustring label_;
    Glib::ustring symbol_;
  };

  /**
   * State set models a state that is a collection of states
   * such as the Polymorphic and Uncertain states. 
   */
  class StateSet : public Serializable {
  public:
    /**
     * Creates an empty set.
     */
    StateSet():members_(){}
    /**
     * Empty set deletes set members
     */
    virtual ~StateSet();
    /**
     * Add a new state to the set.
     */
    void addstate( const State* state){ members_.insert( state ); }
    /**
     * Determine if a particular state is a memeber of the set.
     */
    const bool hasstate( const Glib::ustring& label){ 
      return binary_search(members_.begin(), members_.end(), label); 
    }
    friend std::ostream& operator<<( std::ostream& out, const StateSet& rhs){ return rhs.serialize( out ); }
    friend std::ostream& operator<<( std::ostream& out, const StateSet* rhs){ if (rhs){ rhs->serialize( out ); } return out; }
    std::ostream& serialize(std::ostream& out)const;
  private:
    std::set< const State* > members_;
  };
  /**
   * Uncertain state models uncertain state definitions
   * in a NeXML document.
   */
  class UncertainState : public State,
                         public Serializable,
                         private StateSet {
   public:
     /**
      * Specifies the state's symbol and label.
      */
     UncertainState(const Glib::ustring& label, 
                    const Glib::ustring& symbol):State(label, symbol),
                                                 StateSet(){}
     /**
      * Cleanup the state.
      */
     virtual ~UncertainState(){}
     /**
      * Serialize the state.
      */
     friend std::ostream& operator<<(std::ostream& out, const UncertainState& rhs );
     /**
      * Serialize the state.
      */
     friend std::ostream& operator<<(std::ostream& out, const UncertainState* rhs );
     std::ostream& serialize( std::ostream& out )const;
   private:
  };
  /**
   * Models a NeXML polymorphic state
   */
  class PolymorphicState : public State,
                           public Serializable,
                           private StateSet {
   public:
     /**
      * Initialize the state with the specified label and symbol.
      */
     PolymorphicState(const Glib::ustring& label, 
                      const Glib::ustring& symbol):State(label, symbol),
                                                   StateSet(){}
     /**
      * Cleanup
      */
     virtual ~PolymorphicState(){}
      /**
      * Serialize the state.
      */
     friend std::ostream& operator<<(std::ostream& out, const PolymorphicState& rhs );
     /**
      * Serialize the state.
      */
     friend std::ostream& operator<<(std::ostream& out, const PolymorphicState* rhs );
     /**
      * Serializable interface.
      */
      std::ostream& serialize( std::ostream& out )const;
   private:
  };

}

#endif
