#include "characters.hpp"

using namespace NeXML;
using namespace std;

Characters::Characters(Glib::ustring t, Otus* o, Format* f, Matrix* m):Annotable(),
                                                                       Identifiable( t + o->getid() ),
                                                                       type_(t),
                                                                       otus_(o),
                                                                       format_(f), 
                                                                       matrix_(m){}
Characters::~Characters(){
   delete format_;
   delete matrix_;
}

void Characters::setformat( Format* nformat ){
  if (format_ && format_ != nformat){ delete format_; }
  format_ = nformat;
  return;
}

void Characters::setmatrix( Matrix* nmatrix ){
  if (matrix_ && matrix_ != nmatrix){ delete matrix_; }
  matrix_ = nmatrix;
  return;
}


std::ostream& Characters::serialize( std::ostream& out )const{
  out << "<characters ";
  out << "id=\"" << getid() << "\" ";
  out << "xsi:type=\"" << type_ << "\" ";
  out << "otus=" << otus_->getid() << ">\n";
  out << dynamic_cast< const Annotable* >( this );
  out << format_;
  out << matrix_;
  out << "</characters>\n";
  return out;
}

std::ostream& NeXML::operator<<(std::ostream& out, const Characters& rhs ){
    return rhs.serialize( out );
}
std::ostream& NeXML::operator<<(std::ostream& out, const Characters* rhs ){
  if (rhs){ rhs->serialize( out ); }
  return out;
}

