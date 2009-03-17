#ifndef OTU_HPP_
#define OTU_HPP_
#include "id.hpp"
#include <glibmm/ustring.h>
#include <fstream>
#include "annotation.hpp"
namespace NeXML {
  /**
   * Represents an OTU definition.
   */
  class Otu : public Annotable {
  public:
    /**
     * Initialize the otu.
     */
    Otu(Glib::ustring& label):Annotable(),
                              id_( label  ),
			      label_( label ){}
    /**
     * Clean-up the otu.
     */
    ~Otu();
    /**
     * Get the OTU id.
     */
    Glib::ustring getid()const{ return id_.getid();}
    /**
     * Get the OTU label.
     */
    Glib::ustring getlabel()const{ return label_;}
    /**
     * Set the OTU label.
     */
    void setlabel( const Glib::ustring& label ){ label_ = label; }
    /**
     */
    bool operator==( const Otu& rhs )const{ 
        return this->label_ == rhs.label_;
    }
    bool operator<( const Otu& rhs)const{
        return this->label_ < rhs.label_;
    }
    friend std::ostream& operator<<( std::ostream& out, const Otu& rhs );
    friend std::ostream& operator<<( std::ostream& out, const Otu* rhs );
  private:
    ID id_;
    Glib::ustring label_;
    
  };
  
}

#endif
