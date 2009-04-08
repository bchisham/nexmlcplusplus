#include "matrix.hpp"
#include "tags.hpp"
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

Cell* Matrix::getcell( unsigned int row, unsigned int col )const{
  Cell* ret = NULL; 
  Row* trow = getrow( row );
  if ( trow ){ ret = trow->getcell( col ); }
  return ret;
}

std::ostream& Matrix::serialize( std::ostream& out )const{ 
  out << "<" << MATRIX_TAG << ">" << endl;
  for (unsigned int i = 0; i < rows_.size(); ++i ){ out << rows_.at( i ); }
  out << "</" << MATRIX_TAG << ">" << endl;
  return out;
}

std::ostream& NeXML::operator<<(std::ostream& out, const Matrix& rhs){
   return rhs.serialize( out );
  }
std::ostream& NeXML::operator<<(std::ostream& out, const Matrix* rhs){
  if (rhs){ rhs->serialize( out ); }
  return out;
}

