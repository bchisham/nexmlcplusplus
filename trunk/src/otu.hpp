#ifndef OTU_HPP_
#define OTU_HPP_
#include "id.hpp"
#include <glibmm/ustring.h>
namespace NeXML {
  /**
   * Represents an OTU definition.
   */
  class Otu {
  public:
    /**
     * Initialize the otu.
     */
    Otu(Glib::ustring& label):id_( label  ),
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
  private:
    ID id_;
    Glib::ustring label_;
    
  };
  
}

#endif
