#include "nclnexml.hpp"
#include <parser/parser.hpp>
//#include "taxa.h"
//#include "matrix.h"
//#include "tree.h"
using namespace std;

NxsNexml::NxsNexml( const string& nexml_source ){
    this->doc_ =  NeXML::DOM_PARSER::parser( nexml_source );
    this->taxa_   = new NxsNexmlTaxa( this->doc_->getotus() );
    this->matrix_ = new NxsNexmlMatrix( this->doc_->getmatrix(0) );
    this->tree_   = new NxsNexmlTree( this->doc_->gettrees() );

}

NxsNexml::~NxsNexml(){
    delete doc_;
    delete taxa_;
    delete matrix_;
    delete tree_;
}
