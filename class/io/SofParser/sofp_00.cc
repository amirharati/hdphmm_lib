// file: $isip/class/io/SofParser/sofp_00.cc
// version: $Id: sofp_00.cc 6809 2001-04-24 16:33:22Z duncan $
//

// isip include files
//
#include "SofParser.h"
 
// method: destructor
//
// arguments: none
//
// return: none
//
// this is the default destructor for the SofParser class
//
SofParser::~SofParser() {

  if (used_d != (bool8*)NULL) {
    delete [] used_d;
  }
  
  // exit gracefully
  //
}

// method: copy constructor
//
// arguments:
//  const SofParser& arg: (input) SofParser object
//
// return: none
//
// this is the copy constructor for the SofParser class
//
SofParser::SofParser(const SofParser& arg_a) {
  
  // set the table
  //
  index_d.setTable(table_d);
  
  // initialize all variables
  //
  state_d = NO_GPI;
  param_d = SofSymbolTable::NO_SYMB;
  block_count_d = 0;
  token_count_d = 0;

  used_d = (bool8*)NULL;

  token_start_d = 0;
  token_stop_d = 999999999;
  
  statement_asgn_d = -1;
  statement_term_d = -1;
  statement_last_token_d = -1;

  base_position_d = 0;
  full_size_d = FULL_OBJECT;

  open_index_d = false;
  implicit_object_d = false;
  implicit_block_d = false;
  nest_d = false;
  is_token_d = false;
  load_error_d = false;
  
  debug_level_d = Integral::NONE;
  
  // copy the class data from arguments
  //
  terminator_char_d.assign(arg_a.terminator_char_d);
  assignment_char_d.assign(arg_a.assignment_char_d);
  comment_char_d.assign(arg_a.comment_char_d);
  blockstart_char_d.assign(arg_a.blockstart_char_d);
  blockstop_char_d.assign(arg_a.blockstop_char_d);
  delimiter_char_d.assign(arg_a.delimiter_char_d);

  used_size_d = arg_a.used_size_d;
  if (used_size_d > 0) {
    used_d = new bool8[used_size_d];
    memcpy(used_d, arg_a.used_d, used_size_d * sizeof(bool8));
  }
  
  // exit gracefully
  //
}

// method: constructor
//
// arguments:
//  SysChar terminator_char: (input) terminator character
//  SysChar assignment_char: (input) assignment character
//  SysChar comment_char: (input) comment character
//  SysChar blockstart_char: (input) start block character
//  SysChar blockstop_char: (input) end block character
//  SysChar delimiter_char: (input) delimit tokens
//
// return: none
//
// this is the non-default constructor for the SofParser class
//
SofParser::SofParser(SysChar terminator_char_a,
                     SysChar assignment_char_a,
                     SysChar comment_char_a,
                     SysChar blockstart_char_a,
                     SysChar blockstop_char_a,
                     SysChar delimiter_char_a) {
  
  // set the class data from arguments
  //
  terminator_char_d.assign(terminator_char_a);
  assignment_char_d.assign(assignment_char_a);
  comment_char_d.assign(comment_char_a);
  blockstart_char_d.assign(blockstart_char_a);
  blockstop_char_d.assign(blockstop_char_a);
  delimiter_char_d.assign(delimiter_char_a);

  // set the table
  //
  index_d.setTable(table_d);
  
  // initialize all variables
  //
  state_d = NO_GPI;
  param_d = SofSymbolTable::NO_SYMB;
  block_count_d = 0;
  token_count_d = 0;

  token_start_d = 0;
  token_stop_d = 999999999;
  
  statement_asgn_d = -1;
  statement_term_d = -1;
  statement_last_token_d = -1;

  used_d = (bool8*)NULL;
  used_size_d = 0;

  base_position_d = 0;
  full_size_d = FULL_OBJECT;

  open_index_d = false;
  implicit_object_d = false;
  implicit_block_d = false;
  nest_d = false;
  is_token_d = false;
  load_error_d = false;
  
  debug_level_d = Integral::NONE;
  
  // exit gracefully
  //
}

// method: default constructor
//
// arguments:
//
// return: none
//
// this is the default constructor for the SofParser class
//
SofParser::SofParser() {

  // set the class data to defaults
  //
  terminator_char_d.assign(DEF_TERMINATOR_CHAR);
  assignment_char_d.assign(DEF_ASSIGNMENT_CHAR);
  comment_char_d.assign(DEF_COMMENT_CHAR);
  blockstart_char_d.assign(DEF_BLOCKSTART_CHAR);
  blockstop_char_d.assign(DEF_BLOCKSTOP_CHAR);
  delimiter_char_d.assign(DEF_DELIMITER_CHAR);
  used_d = (bool8*)NULL;
  used_size_d = 0;
  
  // set the table
  //
  index_d.setTable(table_d);
  
  // initialize all variables
  //
  state_d = NO_GPI;
  param_d = SofSymbolTable::NO_SYMB;
  block_count_d = 0;
  token_count_d = 0;

  token_start_d = 0;
  token_stop_d = 999999999;
  
  statement_asgn_d = -1;
  statement_term_d = -1;
  statement_last_token_d = -1;

  base_position_d = 0;
  full_size_d = FULL_OBJECT;

  open_index_d = false;
  implicit_object_d = false;
  implicit_block_d = false;
  nest_d = false;
  is_token_d = false;
  load_error_d = false;
  
  debug_level_d = Integral::NONE;
  
  // exit gracefully
  //
}


//-----------------------------------------------------------------------------
//
// we define non-integral constants in the default constructor
//      
//-----------------------------------------------------------------------------

// constants: class name
//
const SysString SofParser::CLASS_NAME(L"SofParser");

// constants: for file parsing 
//
const SysString SofParser::IMPLICIT_PARAM(L"__SOF_PARSER_IMPLICIT_PARAM");

// constants: names for states in state machine
//
const SysString SofParser::STATE_NO_GPI(L"no_gpi");
const SysString SofParser::STATE_COMMENT_OP_NO_GPI(L"comment_op_no_gpi");
const SysString SofParser::STATE_LITERAL_OP(L"literal_op");
const SysString SofParser::STATE_GPI(L"gpi");
const SysString SofParser::STATE_QUOTE_OP(L"quote_op");
const SysString SofParser::STATE_LITERAL_OP_IN_QUOTE(L"literal_op_in_quote");
const SysString SofParser::STATE_GPI_LWS(L"gpi_lws");
const SysString SofParser::STATE_COMMENT_OP_GPI(L"comment_op_gpi");
const SysString SofParser::STATE_TERMINAL_TRIM_LWS(L"terminal_trim_lws");
const SysString SofParser::STATE_BLOCK_GPI(L"block_gpi");
const SysString SofParser::STATE_BLOCK_GPI_LWS(L"block_gpi_lws");
