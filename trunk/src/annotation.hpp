#ifndef ANNOTATION_HPP_
#define ANNOTATION_HPP_

#include <glibmm/ustring.h>
#include <fstream>

namespace NeXML {

  class Annotation {
  public:
    friend std::ostream& operator<<(std::ostream& out, const Annotation& rhs){ return out; }
    friend std::ostream& operator<<(std::ostream& out, const Annotation* rhs){ if (rhs){out << *rhs; } return out; }
  private:
  };

}

#endif
