#ifndef CELL_HPP_
#define CELL_HPP_
#include <fstream>

#include "character.hpp"
#include "state.hpp"
#include "annotation.hpp"
#include "id.hpp"
#include "serializable.hpp"

/*
 */
namespace NeXML {
  /**
   * @author Brandon Chisham
   * @date March 15, 2009
   * Cell represents a single cell element in a matrix.
   */
  class Cell:public Annotable,
             public Identifiable,
             public Serializable {
  public:
    /**
     * Initialize the cell
     */
    Cell( Character* ch, State* state ):Annotable(), 
                                        Identifiable(), 
                                        char_(ch), 
                                        state_(state){}
    /**
     * Cleanup
     */
    ~Cell(){}
    /**
     * Set the character this cell refers to.
     */
    void setchar( Character* ch );
    /**
     * Get the character.
     */
    Character* getchar()const{ return char_;}
    /**
     * Set the cell state.
     */
    void setstate( State* state );
    /**
     * Get the cell state
     */
    State* getstate()const{ return state_; }
    /**
     * Serialize the cell.
     */
    friend std::ostream& operator<<( std::ostream& out, const Cell& rhs );
    friend std::ostream& operator<<( std::ostream& out, const Cell* rhs );
    std::ostream& serialize( std::ostream& out )const;
  private:
    Character* char_;
    State* state_;
  };

}

#endif
