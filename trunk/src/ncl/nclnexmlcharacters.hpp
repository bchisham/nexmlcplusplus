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
     //<---NCL NxsCharactersBlock Interface----->
     NxsCharactersBlock::DataTypesEnum GetDataType() const;
     NxsCharactersBlock::DataTypesEnum GetOriginalDataType() const;
     const NxsDiscreteStateRow & GetDiscreteMatrixRow(unsigned taxNum) const;
     char GetGapSymbol() const;
     void SetGapSymbol(char);
     virtual VecBlockPtr GetImpliedBlocks();
     //unsigned GetIndicesForLabel(const std::string &label, NxsUnsignedSet *inds) const;
     int GetInternalRepresentation(unsigned i, unsigned j, unsigned k = 0) const;
     std::vector<std::string> GetItems() const;
     char GetMatchcharSymbol() const ;
     //unsigned GetMaxIndex() const;
     virtual unsigned GetMaxObsNumStates(bool countMissingStates=true) const ;
     char GetMissingSymbol() const;
     unsigned GetNCharTotal()  ;
     //unsigned GetNCharTotal() const ;
     unsigned GetNTaxWithData() const ;
     unsigned GetNumActiveChar() const ;
     unsigned GetNumIncludedChars() const ;
     unsigned GetNumEliminated() const ;
     unsigned GetNumEquates() const ;
     unsigned GetNumUserEquates() const;
     unsigned GetNumMatrixCols() const ;
     unsigned GetNumMatrixRows() const ;
     unsigned GetNChar() const;
     unsigned GetNumChar() const;
     unsigned GetNumStates(unsigned i, unsigned j) const ;
     //<------NCL NxsCharactersBlockAPI interface------------->
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
     static std::map< Glib::ustring, NxsCharactersBlock::DataTypesEnum > types_;
};

#endif
