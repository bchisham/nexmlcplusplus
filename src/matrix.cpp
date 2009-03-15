#include "matrix.hpp"

using namespace std;
using namespace NeXML;

Matrix::~Matrix(){
    for (unsigned int i = 0; i < rows_.size(); ++i){
        delete rows_[i];
    }
}

void Matrix::addrow( Row* row ){
   if (row){ rows_.push_back( row ); }
}

Row* Matrix::getrow( unsigned int i )const{
    Row* ret = i < rows_.size() ? rows_.at( i ) : NULL;
    return ret;
}
std::ostream& NeXML::operator<<(std::ostream& out, const Matrix& rhs){
   
   for (unsigned int i = 0; i < rhs.rows_.size(); ++i ){ out << rhs.rows_.at( i ); }

  return out;
}
std::ostream& NeXML::operator<<(std::ostream& out, const Matrix* rhs){
  if (rhs){ out << *rhs; }
  return out;
}

