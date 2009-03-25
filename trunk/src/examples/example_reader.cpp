/**
 * Driver program to demonstrate reading with the NeXMLCPP library.
 * Brandon Chisham
 * 24 March 2009
 */

#include <nexml.hpp>
#include <parser/parser.hpp>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>

using namespace std;

struct Environment {
   string infile_name;
   string outfile_name;
};


const string INFLAG = "-i";

void useage();
Environment process_args( int argc, char** argv );


int main( int argc, char** argv ){
   Environment env = process_args( argc, argv );
   NeXML::Nexml* doc = NeXML::DOM_PARSER::parser( env.infile_name );
   if ( doc ){
       cerr << "Successfully read document\n";
       cerr << "Writing back out....\n";
       cout << doc;
   }
   return 0;
}


void useage(){
  cout << "./example_reader -i FILE_NAME" << endl;
  return;
}

Environment process_args( int argc, char** argv ){
 //minimum number of arguments
  const unsigned int EXPECTED_ARGS = 2;
  if ( argc < EXPECTED_ARGS ){ 
    useage(); 
    exit( 0 );
  }
  Environment ret;
  for ( unsigned int i = 1; i < argc-1; ++i ){
     if ( argv[i] == INFLAG ){
         ret.infile_name = argv[ i + 1 ];
     }
  }
  return ret;
}
