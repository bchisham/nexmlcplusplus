#ifndef TREE_HPP_
#define TREE_HPP_

#include <vector>
#include <map>
#include <glibmm/ustring.h>
#include "network.hpp"

namespace NeXML {
  /**
   * Represents a tree block in a NeXML file.
   */
  class Tree : public Network {
  public:
    /**
     */
    Tree(Glib::ustring label = "", Glib::ustring type ="" ):Network(label, type){}
    /**
     */
    ~Tree();
    
  };
  
}

#endif
