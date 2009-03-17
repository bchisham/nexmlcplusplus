#ifndef ANNOTATION_HPP_
#define ANNOTATION_HPP_

#include <glibmm/ustring.h>
#include <fstream>
#include <vector>

namespace NeXML {

  class Annotation {
  public:
    friend std::ostream& operator<<(std::ostream& out, const Annotation& rhs){ return out; }
    friend std::ostream& operator<<(std::ostream& out, const Annotation* rhs){ if (rhs){out << *rhs; } return out; }
  private:
  };
  
  class Annotable {
  public:
     Annotable():notes_(){}
     ~Annotable(){}
     void addannotation( Annotation* n ){ if (n){ notes_.push_back(n); } }
     Annotation* getannotation(unsigned int i )const{ return i < notes_.size() ? notes_.at( i ) : NULL; }
     unsigned int getnumannotations()const{ return notes_.size(); }
  private:
     std::vector< Annotation* > notes_;
  };
}

#endif
