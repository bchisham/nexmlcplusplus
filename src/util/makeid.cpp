#include "makeid.hpp"

#include <cstdio>
using namespace NeXML;

Sha1LabelMaker::Sha1LabelMaker(){}

Sha1LabelMaker::~Sha1LabelMaker(){}

Glib::ustring Sha1LabelMaker::makeid( const Glib::ustring& data){
  const unsigned int HASH_LEN = gcry_md_get_algo_dlen( GCRY_MD_SHA1 );
  char* out  = new char[ HASH_LEN * 2 + 1];
  char* outit = out;
  char  hash[ HASH_LEN ];
  //compute the hash of the input
  gcry_md_hash_buffer( GCRY_MD_SHA1, hash, data.c_str(), data.size() );
  //convert the hash to hex text.
  for (unsigned int i = 0; i < HASH_LEN; ++i, outit+=2){
    snprintf( outit, 3, "%02x", hash[i]);
  }
  //prepare to return.
  Glib::ustring ret( out );
  //cleanup
  delete[] out;
  return ret;
}
