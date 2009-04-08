#ifndef NCL_NEXML_MATRIX_HPP_
#define NCL_NEXML_MATRIX_HPP_
//#include "nclxslt.h"
#include <nxscharactersblock.h>

#include <vector>
#include <map>
#include <string>
#include <set>

#include "../characters.hpp"

/*
 *
 * Author: Brandon Chisham
 * Date: August 27, 2008
 * Description: Representation of NeXML matrix.
 */
class NxsNexmlCharacters : public NxsCharactersBlockAPI {
  public:
     /*
      * Initialize the matrix with the specified document tree.
      */
     NxsNexmlCharacters(  NeXML::Characters* matrix);
     NxsNexmlCharacters( NxsCharactersBlock* nxsblock );
     /*
      * Typical cleanup. The matrix does not take ownership of the
      * document source pointer, and it is not freed here.
      */
     ~NxsNexmlCharacters();


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
     
     virtual std::string GetDefaultCodonPosPartitionName() const;
     virtual NxsPartition GetCodonPosPartition(const std::string&) const;
  private:
     NeXML::Characters*  matrix_;
     NxsCharactersBlock* nxscharblock_;   
     std::map< std::string, NxsUnsignedSet > exsets_;
     std::map< std::string, NxsUnsignedSet > indexsets_;
     std::map< std::string, NxsPartition > partitions_;
     NxsTransformationManager transformationManager_;
     std::vector< const NxsDiscreteDatatypeMapper* > datatypeMappers_;
     std::map< std::string, std::pair< NxsPartition, bool > > codonPartitions_;
};

#endif
