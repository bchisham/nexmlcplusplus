#ifndef CHARACTER_HPP_
#define CHARACTER_HPP_

#include <fstream>
#include <glibmm/ustring.h>

#include "annotation.hpp"
#include "id.hpp"
#include "serializable.hpp"
#include "states.hpp"
namespace NeXML {
  /**
   * Represents a single character definition.
   */
  class Character : public Annotable,
                    public Identifiable,
                    public Serializable {
  public:
    /**
     * Initializes the character with the specified states block reference
     */
    Character(const States* states):Annotable(),
                                    Identifiable( "character" + states->getid()),
                                    states_( states ){}
    /**
     * Cleanup.
     */
    ~Character(){}
    /**
     * Serialize.
     */
    friend std::ostream& operator<<( std::ostream& out, const Character& rhs );
    friend std::ostream& operator<<( std::ostream& out, const Character* rhs );
    std::ostream& serialize( std::ostream& out )const;
  private:
    const States* states_;
  };

}

#endif
