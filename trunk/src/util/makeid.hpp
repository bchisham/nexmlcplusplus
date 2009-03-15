#ifndef MAKEID_HPP_
#define MAKEID_HPP_
#include <gcrypt.h>
#include <glibmm/ustring.h>

/*
 * Brandon Chisham
 * 14 March 2009
 * Class to create unique id's given some text.
 */

namespace NeXML {

  /**
   * Make an id given the data text.
   */
  class LabelMaker {
  public:
    /**
     * Make a unique id.
     * The given the same data parameter the generated id should be invariant.
     */
    virtual Glib::ustring makeid( const Glib::ustring& data )=0;
  };
  
  /**
   * Make an id using the SHA1 algorithm
   */
  class Sha1LabelMaker : public LabelMaker {
  public:
    /**
     * Initializs
     */
    Sha1LabelMaker();
    /**
     * Cleanup.
     */
    virtual ~Sha1LabelMaker();
    /**
     * Make an id.
     */
    virtual Glib::ustring makeid( const Glib::ustring& data);
  private:
    
  };
  
}
#endif
