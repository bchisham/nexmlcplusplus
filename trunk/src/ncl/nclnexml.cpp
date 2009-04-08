#include "nclnexml.hpp"
#include <parser/parser.hpp>
#include <algorithm>

using namespace std;

NxsNexml::NxsNexml( const string& nexml_source ){
    this->doc_ =  NeXML::DOM_PARSER::parser( nexml_source );
    this->taxa_   = new NxsNexmlTaxa( this->doc_->getotus() );
    this->matrix_ = vector< NxsNexmlCharacters* >( this->doc_->getnummatrices() );
    for (unsigned i = 0; i != matrix_.size(); ++i){
      matrix_[i] = new NxsNexmlCharacters( this->doc_->getmatrix(i) );
    }
    this->tree_   = new NxsNexmlTree( this->doc_->gettrees() );

}

NxsNexml::~NxsNexml(){
    delete doc_;
    delete taxa_;
    for (unsigned i = 0; i < matrix_.size(); ++i){
        delete matrix_.at( i );
    }
    delete tree_;
}
