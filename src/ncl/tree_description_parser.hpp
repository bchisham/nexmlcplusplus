#ifndef TREE_DESCRIPTION_PARSER_HPP_
#define TREE_DESCRIPTION_PARSER_HPP_

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <ncl/tree_description_scanner.hpp>
#include <util/util.hpp>
#include <ncl/node.hpp>
namespace CDAO {
 
  /*
   * Parses a Newick/Nexus tree string into a tree. 
   */
  class TreeDescriptionParser {
  public:
    /*
     * Initialize the parser with the specified target string.
     */
    TreeDescriptionParser( std::string target ):parsetree_(NULL), scanner( target ){ parse(); }
    /*
     * Retrieve the parse tree.
     */
    Node* getParseTree()const{ return parsetree_;}

  protected:
    /*
     * Parse the specified string.
     */
    void parse();
  private:
    /*
     * Consume a single tree.
     * TREE -> ( TREE_LIST ) LABEL
     */
    void consume_tree(  Node* current );
    /*
     * Consume a list of trees.
     * TREE_LIST -> TREE
     *           -> LABEL
     *           -> TREE , TREE_LIST
     *           -> LABEL, TREE_LIST
     */
    void consume_tree_list( Node* current );
    /*
     * Consume a single label.
     * LABEL->[a-zA-Z0-9]+
     */
    void consume_label(  Node* current);
    /*
     * Consume a start tree token.
     * START_TREE -> '('
     */
    void consume_start_tree(  Node* current );
    /*
     * Consume an end tree token.
     * END_TREE -> ')'
     */
    void consume_end_tree(   Node* current );
    /*
     * Consume a delimiter.
     * DELIMITER -> ','
     */
    void consume_delimiter(  Node* current );
    /*
     * Consume weight/comment after tree labels.
     * EXTENDED_META -> WEIGHT | COMMENT | WEIGHT COMMENT
     */
    void consume_extended_meta( Node* current );
    
    void consume_weight( Node* current );
    /*
     * Consume a comment.
     * COMMENT -> '[' (LABEL | SPACE)* ']'
     */
    void consume_comment( Node* current );
    Node* parsetree_;
    
    TreeDescriptionScanner scanner;
    
  };
}
#endif
