#include "id.hpp"
#include <cstdlib>
#include <cstdio>
using namespace NeXML;
#define NUMBER_WIDTH 20

unsigned ID::serialno = 0;

Glib::ustring ID::convert_serial()const{
   char* buff = (char*)calloc( NUMBER_WIDTH, sizeof(char) );
   snprintf(buff, NUMBER_WIDTH, "%6d", serialno );
   Glib::ustring ret( buff );
   free( buff );
   return ret;
}
