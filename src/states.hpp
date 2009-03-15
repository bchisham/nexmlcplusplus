#ifndef STATES_HPP_
#define STATES_HPP_

#include <fstream>
#include <vector>

#include "id.hpp"
#include "state.hpp"

namespace NeXML {

  class States {
  public:
    States():id_(),states_(){}
    ~States();
    void addstate( State* state );
    State* getstate( unsigned int i )const;
    friend std::ostream& operator<<( std::ostream& out, const States& rhs );
    friend std::ostream& operator<<( std::ostream& out, const States* rhs );
  private:
    ID id_;
    std::vector< State* > states_;
  };

}

#endif
