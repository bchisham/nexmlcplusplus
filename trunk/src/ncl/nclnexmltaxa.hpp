#ifndef NCL_NEXML_TAXA_HPP_
#define NCL_NEXML_TAXA_HPP_
//#include "nclxslt.h"
#include <nxstaxablock.h>
#include <set>
#include <map>
#include <vector>

#include "../otus.hpp"
#include "../otu.hpp"

/*
 * Author: Brandon Chisham
 * Date: August 27, 2008
 * Description: Representation of the taxa block.
 */
class NxsNexmlTaxa : public NxsTaxaBlockAPI {
   public:
      /*
       * Initialize the taxa block from the source document tree.
       * Does not take owership of the source document.
       */
      NxsNexmlTaxa(NeXML::Otus* otus);
      ~NxsNexmlTaxa();
      //<-------NxsTaxaBlock interface---------------------->
      //Return the max valid index of the label list
      virtual unsigned int GetMaxIndex()const;
      //Get all the indices for a label
      virtual unsigned int GetIndicesForLabel( const std::string&, NxsUnsignedSet* ) const;
      //Get the specified index set
      virtual unsigned int GetIndexSet( const std::string&, NxsUnsignedSet* )const ;
      //Save a new index set
      virtual bool NxsAddNewIndexSet( const std::string&, const NxsUnsignedSet&);
      //Save a new partition
      virtual bool NxsAddNewPartition( const std::string&, const NxsPartition&);
      //Add a new taxon label
      virtual unsigned int AddTaxonLabel( const std::string& );
      //update the specified taxon label
      virtual void ChangeTaxonLabel(unsigned int, NxsString);
      //get the label associated with index
      virtual NxsString GetTaxonLabel( unsigned int )const;
      //find the index of the specified label
      virtual unsigned int FindTaxon( const NxsString& )const;
      //find the index of the specified label
      virtual unsigned int TaxLabelToNumber( const std::string& ) const;
      //true if the specified label is already in the set
      virtual bool IsAlreadyDefined( const std::string& );
      //get the max length of a taxon label.
      virtual unsigned int GetMaxTaxonLabelLength();
      //get the number of taxon labels in this set.
      virtual unsigned int GetNumTaxonLabels() const;
      //get the number of taxon labels in this set.
      virtual unsigned int GetNTax() const;
      //get the number of taxon labels in this set.
      virtual unsigned int GetNTaxTotal() const;
      //find the index associated with a label
      virtual unsigned int TaxonLabelToNumber( const std::string& ) const;
      //
      virtual void HandleTaxLabels( NxsToken& );
      //Write the nexml format taxa block
      virtual void WriteTaxLabelsCommand( std::ostream& ) const;
      //part of the ncl interface n-tax cannot be reset since it depends only
      //on the number of taxa actually in the block. 
      virtual void SetNtax( unsigned int );
      //Get the size of the active taxa set.
      virtual unsigned int GetNumActiveTaxa() const;
      //True if the specified index is in the active taxon set.
      virtual bool IsActiveTaxon( unsigned int ) const;
      //Add the following taxa to the active taxa set.
      virtual unsigned int ActivateTaxa( const std::set< unsigned int >& );
      //Remove the following taxa from the active taxa set.
      virtual unsigned int InactivateTaxa(const std::set< unsigned int >& );
      //in-activate a particular taxon
      virtual unsigned int InactivateTaxon( unsigned int );
      //activate a particular taxon.
      virtual unsigned int ActivateTaxon( unsigned int );
      //add a new index set.
      virtual bool AddNewIndexSet( const std::string&, const NxsUnsignedSet& );
      //add a new partition.
      virtual bool AddNewPartition( const std::string&, const NxsPartition& );
   private:
      //void populate_model();
      //xsltStylesheetPtr style;
      //xmlDocPtr source;
     // xmlDocPtr taxa;
      std::string block_name_;
      NeXML::Otus* otus_; 
      /* Data structures to support NxsBlock interface */
      std::set< unsigned int > inactive_taxa_;
      std::set< unsigned int > active_taxa_;
      //std::vector< NxsString > taxa_;
      std::map< std::string, NxsPartition > partitions_;
      std::map< std::string, NxsUnsignedSet > index_sets_;

};

#endif
