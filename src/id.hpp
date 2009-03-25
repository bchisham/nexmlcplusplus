#ifndef ID_HPP_
#define ID_HPP_
#include "util/makeid.hpp"
#include <glibmm/ustring.h>
#include <fstream>

namespace NeXML {
  /**
   * Represents an id for some element.
   */
  class ID {
  public:
    /**
     * Construct a new id.
     */
    ID(const Glib::ustring& data):lmaker_( new Sha1LabelMaker() ),
				  label_( "id" + lmaker_->makeid( data + convert_serial() ) ){serialno++;}
    /**
     * Cleanup
     */
    virtual ~ID(){ delete lmaker_; }
    /**
     * Get the id string.
     */
    const Glib::ustring& getid()const{ return label_; }
    /**
     * Set the id string. 
     */
    void setid( const Glib::ustring& data ){ label_ = "id" + lmaker_->makeid( data );  }
    /**
     * Short-cut to getting the string.
     */
    const Glib::ustring& operator()(void)const{ return this->getid(); }
    /**
     * Create an id that is the concatination of two id's. 
     */
    ID operator+( const ID& rhs )const{ return ID( this->getid() + rhs.getid() ); }
    /**
     * Serialize an id.
     */
    friend std::ostream& operator<<( std::ostream& out, const ID& rhs ){ out << rhs.label_; return out; }
    /**
     * Compare id's
     */
    inline const bool operator==( const ID& rhs )const{ return this == &rhs || this->label_ == rhs.label_; }
    inline const bool operator!=( const ID& rhs )const{ return !( *this == rhs ); }
  private:
    /**
     * Converts the serial number to a string for use as nounce. 
     */
    Glib::ustring convert_serial()const;
    LabelMaker* lmaker_;
    Glib::ustring label_;
    static unsigned serialno;
  };
  /**
   * Manages tying id behavior to NeXML document objects.
   */
  class Identifiable {
  public:
    Identifiable( const Glib::ustring& id ):id_( id ){}
    ~Identifiable(){}
    const Glib::ustring& getid()const{ return id_(); }
    void setid( const Glib::ustring& id ){ id_.setid( id ); return; }

  private:
    ID id_;
  };

}

#endif
