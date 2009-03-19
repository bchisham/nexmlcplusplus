#ifndef ANNOTATION_HPP_
#define ANNOTATION_HPP_

#include <glibmm/ustring.h>
#include <fstream>
#include <vector>
#include "serializable.hpp"

namespace NeXML {
  /**
   * Represents an annotation in a NeXML document
   */
  class Annotation : public Serializable {
  public:
    /**
     * Write out the annotation
     */
    friend std::ostream& operator<<(std::ostream& out, const Annotation& rhs){ return rhs.serialize( out ); }
    /**
     * Write out the annotation.
     */
    friend std::ostream& operator<<(std::ostream& out, const Annotation* rhs){ if (rhs){ rhs->serialize( out ); } return out;  }
    /**
     * Get the rdf literal of the annotation.
     */
    Glib::ustring getliteral()const{ return literal_note_; }
    /**
     * Set the rdf literal of the annotation.
     */
    void setliteral( const Glib::ustring& lit ){ literal_note_ = lit; }
    /**
     * Serializable interface.
     */
    virtual std::ostream& serialize( std::ostream& out )const;
  private:
     Glib::ustring literal_note_;
  };
  /**
   * Adds annotation behavior to a NeXML object.
   */
  class Annotable : public Serializable {
  public:
     /**
      * Initialize empty annotation block
      */
     Annotable():notes_(){}
     /**
      * Cleanup
      */
     ~Annotable();
     /**
      * Add a new annotation to the collecton.
      */
     void addannotation( const Annotation* n ){ if (n){ notes_.push_back(n); } }
     /**
      * Get the specified annotation.
      */
     const Annotation* getannotation(unsigned int i )const{ return i < notes_.size() ? notes_.at( i ) : NULL; }
     /**
      * Get the number of annotations in the block. 
      */
     unsigned int getnumannotations()const{ return notes_.size(); } 
     /**
      * Serializable interface.
      */
     virtual std::ostream& serialize(std::ostream& out)const;
  private:
     std::vector< const Annotation* > notes_;
  };
}

#endif
