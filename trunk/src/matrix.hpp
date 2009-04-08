#ifndef MATRIX_HPP_
#define MATRIX_HPP_

#include <vector>
#include <fstream>
#include "row.hpp"
#include "annotation.hpp"
#include "serializable.hpp"
namespace NeXML {
  /**
   * Represents a single matrix block in a NeXML file.
   */
  class Matrix : public Annotable, public Serializable {
  public:
    /**
     * Create an empty matrix
     */
    Matrix():rows_(){}
    /**
     * Clean-up.
     */
    virtual ~Matrix();
    /**
     * Add a new row to the matrix.
     */
    void addrow( Row* row );
    /**
     * Get the specified row from the matrix.
     */
    Row* getrow( unsigned int row )const;
    /**
     * Get the specified cell from the matrix.
     */
    Cell* getcell( unsigned int row, unsigned int col )const;
    /**
     * Get the number of rows in the matrix.
     */
    const unsigned getrowcount()const{ return rows_.size(); }
    /**
     * Serializable interface impl.
     */
    std::ostream& serialize( std::ostream& out )const;
    /**
     */
    friend std::ostream& operator<<(std::ostream& out, const Matrix& rhs);
    /**
     */
    friend std::ostream& operator<<(std::ostream& out, const Matrix* rhs);
  private:
    std::vector< Row* > rows_;
  };
  
}

#endif
