#include "characters.hpp"

using namespace NeXML;
using namespace std;

Characters::Characters(Glib::ustring t, Otus* o, Format* f, Matrix* m):type_(t),
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

std::ostream& NeXML::operator<<(std::ostream& out, const Characters& rhs ){
  out << "<characters ";
  out << "id=\"" << rhs.id_ << "\" ";
  out << "xsi:type=\"" << rhs.type_ << "\" ";
  out << "otus=" << rhs.otus_->getid() << ">\n";
  
  out << rhs.format_;
  out << rhs.matrix_;

  out << "</characters>\n";
  return out;
}
std::ostream& NeXML::operator<<(std::ostream& out, const Characters* rhs ){
  if (rhs){ out << *rhs; }
  return out;
}

