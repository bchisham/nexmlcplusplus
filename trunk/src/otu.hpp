#ifndef OTU_HPP_
#define OTU_HPP_
#include "id.hpp"
#include <glibmm/ustring.h>
#include <fstream>
#include "annotation.hpp"
#include "serializable.hpp"

namespace NeXML {
  /**
   * Represents an OTU definition.
   */
  class Otu : public Annotable,
              public Identifiable,
              public Serializable {
  public:
    /**
     * Initialize the otu.
     */
    Otu(Glib::ustring& label):Annotable(),
                              Identifiable( label ),
			      label_( label ){}
    /**
     * Clean-up the otu.
     */
    virtual ~Otu();
    /**
     * Get the OTU id.
     */
    //Glib::ustring getid()const{ return id_.getid();}
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
    friend std::ostream& operator<<( std::ostream& out, const Otu& rhs ){ return rhs.serialize( out ); }
    friend std::ostream& operator<<( std::ostream& out, const Otu* rhs ){ if (rhs){ rhs->serialize( out ); } return out;}
    std::ostream& serialize( std::ostream& out )const;
  private:
    //ID id_;
    Glib::ustring label_;
    
  };
  
}

#endif
