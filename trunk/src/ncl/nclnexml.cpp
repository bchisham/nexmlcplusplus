#include "nclnexml.hpp"
#include "taxa.h"
#include "matrix.h"
#include "tree.h"
using namespace std;

NxsNexml::NxsNexml( const string& nexml_source ){
    this->source = xmlParseFile( nexml_source.c_str() );
    this->taxa   = new NxsNexmlTaxa( this->source );
    this->matrix = new NxsNexmlMatrix( this->source );
    this->tree   = new NxsNexmlTree( this->source );

}

NxsNexml::~NxsNexml(){
    xmlFreeDoc( this->source );
    delete taxa;
    delete matrix;
    delete tree;
}
