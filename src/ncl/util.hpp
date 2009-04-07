#ifndef CDAO_UTIL_HPP_
#define CDAO_UTIL_HPP_
#include <string>

namespace CDAO {
  /*
   * Generate a document-wide unique identifier
   */
  std::string labelMaker( std::string tag_type );
  /*
   * Convert numbers to strings.
   */
  std::string number_to_string( unsigned int number );
  std::string convert( unsigned int number ){ return number_to_string( number ); }
  std::string number_to_string( double number );
  std::string convert( double number ){ return number_to_string( number ); }
}
#endif
