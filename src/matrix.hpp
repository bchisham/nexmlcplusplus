#ifndef MATRIX_HPP_
#define MATRIX_HPP_

#include <vector>
#include <fstream>
#include "row.hpp"
#include "annotation.hpp"

namespace NeXML {
  /**
   * Represents a single matrix block in a NeXML file.
   */
  class Matrix : public Annotable {
  public:
    /**
     */
    Matrix():rows_(){}
    /**
     */
    virtual ~Matrix();
    /**
     */
    void addrow( Row* row );
    /**
     */
    Row* getrow( unsigned int row )const;

    const unsigned getrowcount()const{ return rows_.size(); }

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
