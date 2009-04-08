#ifndef ROW_HPP_
#define ROW_HPP_
#include <fstream>
#include <vector>

#include "cell.hpp"
#include "otu.hpp"
#include "id.hpp"

/*
 *
 */
namespace NeXML {
  /**
   * Represents a row of observations
   */
  class Row : public Identifiable, public Serializable {
  public:
    /**
     * Initialize a row with an otu and label.
     */
    Row(Otu* otu, Glib::ustring label);
    /**
     * Clean-up.
     */
    ~Row();
    /**
     * Add a new cell to the row.
     */
    void addcell( Cell* );
    /**
     * Get the specified cell from the row
     */
    Cell* getcell( unsigned int i )const;
    /**
     * Get the size of the row
     */
    unsigned size()const;
    /**
     * Serializable interfac impl.
     */
    friend std::ostream& operator<<( std::ostream& out, const Row& rhs);
    friend std::ostream& operator<<( std::ostream& out, const Row* rhs);
    std::ostream& serialize( std::ostream& out )const;
  private:
    //ID id_;
    Otu* otu_;
    Glib::ustring label_;
    std::vector< Cell* > cells_;
  };

}

#endif
