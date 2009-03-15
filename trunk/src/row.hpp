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
  class Row {
  public:
    Row(Otu* otu);
    ~Row();
    void addcell( Cell* );
    Cell* getcell( unsigned int i )const;
    friend std::ostream& operator<<( std::ostream& out, const Row& rhs);
    friend std::ostream& operator<<( std::ostream& out, const Row* rhs);
  private:
    ID id_;
    Otu* otu_;
    std::vector< Cell* > cells_;
  };

}

#endif
