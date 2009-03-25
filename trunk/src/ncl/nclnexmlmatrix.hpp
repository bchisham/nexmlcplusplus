#ifndef NCL_NEXML_MATRIX_HPP_
#define NCL_NEXML_MATRIX_HPP_
#include "nclxslt.h"
#include "../nxscharactersblock.h"

#include <vector>
#include <map>
#include <string>
#include <set>

/*
 *
 * Author: Brandon Chisham
 * Date: August 27, 2008
 * Description: Representation of NeXML matrix.
 */
class NxsNexmlMatrix : public NxsCharactersBlockAPI {
  public:
     /*
      * Initialize the matrix with the specified document tree.
      */
     NxsNexmlMatrix(xmlDocPtr source);
     /*
      * Typical cleanup. The matrix does not take ownership of the
      * document source pointer, and it is not freed here.
      */
     ~NxsNexmlMatrix();


     virtual unsigned	ApplyExset(NxsUnsignedSet &exset);
     virtual bool		AddNewExSet(const std::string &label, const NxsUnsignedSet & inds);
     virtual bool		IsRespectCase() const ;
     virtual unsigned	GetNCharTotal() const;
     virtual NxsTransformationManager & GetNxsTransformationManagerRef();
     virtual const NxsTransformationManager & GetNxsTransformationManagerRef() const;
     virtual std::vector<const NxsDiscreteDatatypeMapper *> GetAllDatatypeMappers() const;
     virtual bool AddNewCodonPosPartition(const std::string &label, const NxsPartition & inds, bool isDefault);

       
     virtual unsigned int GetMaxIndex() const;
     virtual unsigned int GetIndicesForLabel(const std::string&, NxsUnsignedSet*) const;
     virtual unsigned int GetIndexSet(const std::string&, NxsUnsignedSet*) const;
     virtual bool AddNewIndexSet(const std::string&, const NxsUnsignedSet&);
     virtual bool AddNewPartition(const std::string&, const NxsPartition&);
     
     
  private:
     /*
      * Pointer to the transformation
      */
     xsltStylesheetPtr style;
     /*
      * Shared document tree.
      */
     xmlDocPtr source;
     /*
      * Transformed matrix block of the original document.
      */
     xmlDocPtr matrix;
     std::string id_; 
     std::vector< std::string > taxa_;
     std::vector< std::string > characters_;

     std::vector< std::vector< std::string > > matrix_;
     
     std::map< std::string, NxsUnsignedSet > exsets_;
     std::map< std::string, NxsUnsignedSet > indexsets_;
     std::map< std::string, NxsPartition > partitions_;
     NxsTransformationManager transformationManager_;
     std::vector< const NxsDiscreteDatatypeMapper* > datatypeMappers_;
     std::map< std::string, std::pair< NxsPartition, bool > > codonPartitions_;
};

#endif
