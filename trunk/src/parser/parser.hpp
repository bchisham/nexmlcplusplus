#ifndef PARSER_HPP_
#define PARSER_HPP_

#include <glibmm/ustring.h>
#include <libxml++/libxml++.h>

#include "../nexml.hpp"



namespace NeXML {
  typedef NeXML::Nexml* (*parser_t)(const Glib::ustring&);

  namespace DOM_PARSER {
    NeXML::Nexml* parser( const Glib::ustring& source );
  }
  
  namespace SAX_PARSER {
    NeXML::Nexml* parser( const Glib::ustring& source ){}
  
  }
  
  class Parser {
  public:
    Parser( parser_t p  ):parser_(p){}
    ~Parser();
    Nexml* parse( const Glib::ustring& source ){ return (*parser_)( source); }
  private:
    parser_t parser_;
  };

}

#endif
