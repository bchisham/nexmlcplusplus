#ifndef ROW_HPP_
#define ROW_HPP_
#include <fstream>
#include <vector>

#include "cell.hpp"
#include "otu.hpp"
#include "id.hpp"

/**
 */
namespace NeXML {
  /**
   */
  class Row : public Identifiable, public Serializable {
  public:
    /**
     */
    Row(Otu* otu, Glib::ustring label);
    /**
     */
    ~Row();
    /**
     */
    void addcell( Cell* );
    /**
     */
    Cell* getcell( unsigned int i )const;
    /**
     *
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
