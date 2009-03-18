#ifndef CHARACTER_HPP_
#define CHARACTER_HPP_

#include <fstream>
#include <glibmm/ustring.h>

#include "annotation.hpp"
#include "id.hpp"


namespace NeXML {

  class Character : public Annotable,
                    public Identifiable {
  public:
    Character(const Glib::ustring& states):Annotable(),
                                           Identifiable(states),
                                           states_( states ){}
    ~Character(){}
    friend std::ostream& operator<<( std::ostream& out, const Character& rhs );
    friend std::ostream& operator<<( std::ostream& out, const Character* rhs );
  private:
    Glib::ustring states_;
  };

}

#endif
