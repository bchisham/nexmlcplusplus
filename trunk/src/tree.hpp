#ifndef TREE_HPP_
#define TREE_HPP_

#include <vector>
#include <map>
#include <glibmm/ustring.h>
#include "network.hpp"
#ifdef EBUG_V
#include <iostream>
#endif
namespace NeXML {
  /**
   * Represents a tree block in a NeXML file.
   */
  class Tree : public Network {
  public:
    /**
     */
    Tree(Glib::ustring label, Glib::ustring type ):Network(label, type){
#ifdef EBUG_V_TREE
      std::cerr << "Tree( label: " << label << " type: " << type << ")" << std::endl;
#endif
    }
    /**
     */
   virtual  ~Tree(){}
    virtual std::ostream& serialize(std::ostream& out )const;
    friend std::ostream& operator<<( std::ostream& out, const Tree& rhs){ return rhs.serialize( out ); }
    friend std::ostream& operator<<( std::ostream& out, const Tree* rhs){ 
      if (rhs){ rhs->serialize( out );}
      return out;
    }
  };
  
}

#endif
