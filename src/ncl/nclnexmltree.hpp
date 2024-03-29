#ifndef NCL_NEXML_TREE_HPP_
#define NCL_NEXML_TREE_HPP_
#include <vector>
#include <string>
#include <map>
#include <vector>
#include <set>
//#include "nclxslt.h"
#include <nxstreesblock.h>
#include "../trees.hpp"
#include "../otus.hpp"

/*
 * Author: Brandon Chisham
 * Date: August 27, 2008
 * Description: Represents a set of nexml trees.
 */
class NxsNexmlTree : public NxsTreesBlockAPI {
	public:
		/*
		 * Initialize the trees block from the source document tree.
		 */
		NxsNexmlTree( NeXML::Trees* trees );
                NxsNexmlTree( NxsTreesBlock& nxstrees, const NeXML::Otus* otus);
		~NxsNexmlTree();
                /*NCL Trees interface*/
                virtual unsigned	GetNumDefaultTree();
		virtual unsigned	GetNumTrees();
                virtual unsigned        GetNumTrees()const;
		virtual NxsString	GetTreeName(unsigned i);
		virtual NxsString	GetTreeDescription(unsigned i);
		virtual NxsString	GetTranslatedTreeDescription(unsigned i);
		virtual bool		IsDefaultTree(unsigned i);
		virtual bool		IsRootedTree(unsigned i);

                virtual unsigned int    GetMaxIndex() const;
                virtual unsigned int    GetIndicesForLabel(const std::string&, NxsUnsignedSet*) const;
                virtual unsigned int    GetIndexSet(const std::string&, NxsUnsignedSet*) const;
                virtual bool            AddNewIndexSet(const std::string&, const NxsUnsignedSet&);
                virtual bool            AddNewPartition(const std::string&, const NxsPartition&);
	private:
                
                NeXML::Trees* trees_;
                
                std::map< std::string, NxsUnsignedSet > index_sets_;

                std::map< std::string, NxsPartition > partition_sets_;

};

#endif
