#include "nclnexml.hpp"
#include "taxa.h"
#include "matrix.h"
#include "tree.h"
using namespace std;

NxsNexml::NxsNexml( const string& nexml_source ){
    //this->source = xmlParseFile( nexml_source.c_str() );
    this->taxa_   = new NxsNexmlTaxa( this->source );
    this->matrix_ = new NxsNexmlMatrix( this->source );
    this->tree_   = new NxsNexmlTree( this->source );

}

NxsNexml::~NxsNexml(){
    //xmlFreeDoc( this->source );
    delete doc_;
    delete taxa_;
    delete matrix_;
    delete tree_;
}
