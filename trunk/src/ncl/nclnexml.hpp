#ifndef NCL_NEXML_HPP_
#define NCL_NEXML_HPP_
/*
 * Author: Brandon Chisham
 * Date: August 27, 2008
 * Description: Interface to nexml using xslt and libxml2
 */
//#include "nclxslt.h"
#include "../nexml.hpp"
#include "nclnexmltaxa.hpp"
#include "nclnexmlmatrix.hpp"
#include "nclnexmltree.hpp"
#include <string>

/*
 * NxsNexml represents a single Nexml document.
 */
class NxsNexml {
   public:
	/*
	 * Initialize the NxsNexml document with it's source location.
	 */
	NxsNexml(const std::string& nexml_source);
	/*
	 * Clean-up document resources.
	 */
	~NxsNexml();

   private:
        NeXML::Nexml* doc_;
//	xmlDocPtr source;
        NxsNexmlTaxa* taxa_;
        NxsNexmlMatrix* matrix_;
        NxsNexmlTree* tree_;
};

#endif
