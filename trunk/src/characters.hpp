#ifndef CHARACTERS_HPP_
#define CHARACTERS_HPP_
#include <fstream>
#include <glibmm/ustring.h>
#include <vector>
#include "otus.hpp"
#include "matrix.hpp"
#include "format.hpp"
#include "id.hpp"
#include "annotation.hpp"
#include "serializable.hpp"

namespace NeXML {
  /**
   * Represents a NeXML characters block.
   */
  class Characters : public Annotable, 
                     public Identifiable,
                     public Serializable {
    public:
      /**
       * Initilize the block
       */
      Characters(Glib::ustring type, const Otus* otus,const  Format* format = NULL, const Matrix* matrix = NULL);
      /**
       * Cleanup the block
       */
      ~Characters();
      /**
       * Get the format element
       */
      const Format* getformat()const{return format_;}
      /**
       * Set the format element.
       */
      void setformat(const Format*);
      /**
       * Get the matrix element.
       */
      const Matrix* getmatrix()const{return matrix_;}
      /**
       * Set the matrix element.
       */
      void setmatrix(const Matrix*);
      /**
       * Write the characters block.
       */
      friend std::ostream& operator<<(std::ostream& out, const Characters& rhs );
      friend std::ostream& operator<<(std::ostream& out, const Characters* rhs );
      std::ostream& serialize( std::ostream& out )const;
    private:
      //ID id_;
      const Otus* otus_;
      Glib::ustring type_;
      const Format* format_;
      const Matrix* matrix_;
   };

}

#endif
