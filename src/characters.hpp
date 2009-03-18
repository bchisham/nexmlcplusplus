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
namespace NeXML {
  /**
   * Represents a NeXML characters block.
   */
  class Characters : public Annotable, 
                     public Identifiable {
    public:
      /**
       * Initilize the block
       */
      Characters(Glib::ustring type, Otus* otus, Format* format = NULL, Matrix* matrix = NULL);
      /**
       * Cleanup the block
       */
      ~Characters();
      /**
       * Get the format element
       */
      Format* getformat()const{return format_;}
      /**
       * Set the format element.
       */
      void setformat(Format*);
      /**
       * Get the matrix element.
       */
      Matrix* getmatrix()const{return matrix_;}
      /**
       * Set the matrix element.
       */
      void setmatrix(Matrix*);
      /**
       * Write the characters block.
       */
      friend std::ostream& operator<<(std::ostream& out, const Characters& rhs );
      friend std::ostream& operator<<(std::ostream& out, const Characters* rhs );
    private:
      //ID id_;
      Otus* otus_;
      Glib::ustring type_;
      Format* format_;
      Matrix* matrix_;
   };

}

#endif
