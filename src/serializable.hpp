#ifndef SERIALIZABLE_HPP_
#define SERIALIZABLE_HPP_

#include <fstream>

namespace NeXML {
   /**
    * Provides an interface for classes that are serializable can implement.
    */
   class Serializable {
   public:
     virtual  std::ostream& serialize( std::ostream& out )const=0;
   };

}
#endif
