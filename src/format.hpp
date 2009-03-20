#ifndef FORMAT_HPP_
#define FORMAT_HPP_
#include <vector>
#include <fstream>

#include "states.hpp"
#include "character.hpp"
#include "serializable.hpp"

namespace NeXML {

  class Format : public Annotable, public Serializable {
  public:
    Format():states_(), chars_(){}
    ~Format(){}
    friend std::ostream& operator<<( std::ostream& out, const Format& rhs );
    friend std::ostream& operator<<( std::ostream& out, const Format* rhs );
    const States* getstates()const{ return states_; }
    void setstates( const States* states );
    void addchar( const Character* ch ){ chars_.push_back( ch ); }
    const Character* getchar( unsigned int i )const{ return i < chars_.size() ? chars_.at( i ) : NULL;  }
    unsigned int getnumchars()const{ return chars_.size(); }
    std::ostream& serialize( std::ostream& out )const;
  private:
    const States* states_;
    std::vector< const Character* > chars_;
  };

}

#endif
