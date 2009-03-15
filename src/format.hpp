#ifndef FORMAT_HPP_
#define FORMAT_HPP_
#include <vector>
#include <fstream>

#include "states.hpp"
#include "character.hpp"
namespace NeXML {

  class Format {
  public:
    Format(){}
    ~Format(){}
    friend std::ostream& operator<<( std::ostream& out, const Format& rhs );
    friend std::ostream& operator<<( std::ostream& out, const Format* rhs );
  private:
    States* states_;
    std::vector< Character* > chars_;
  };

}

#endif
