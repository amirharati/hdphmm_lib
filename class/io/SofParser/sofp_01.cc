// file: $isip/class/io/SofParser/sofp_01.cc
// version: $Id: sofp_01.cc 7815 2002-02-26 22:59:31Z alphonso $
//

// isip include files
//
#include "SofParser.h"

// method: debug
//
// arguments:
//  const unichar* message: (input) debugging message
//
// return: a bool8 value indicating status
//
bool8 SofParser::debug(const unichar* message_a) const {

  // dump characters
  //
  terminator_char_d.debug(L"terminator_char_d");
  assignment_char_d.debug(L"assignment_char_d");
  comment_char_d.debug(L"comment_char_d");
  blockstart_char_d.debug(L"blockstart_char_d");
  blockstop_char_d.debug(L"blockstop_char_d");
  delimiter_char_d.debug(L"delimiter_char_d");
  
  // dump numeric values
  //
  SysString output;
  SysString value;

  setString(value, state_d);
  output.debugStr(name(), message_a, L"state_d", value);
  Console::put(output);
  
  value.assign(block_count_d);
  output.debugStr(name(), message_a, L"block_count_d", value);
  Console::put(output);

  value.assign(token_count_d);
  output.debugStr(name(), message_a, L"token_count_d", value);
  Console::put(output);

  value.assign(param_d);
  output.debugStr(name(), message_a, L"param_d", value);
  Console::put(output);

  // dump the list
  //
  index_d.debug(L"index_d");
  
  value.assign(used_size_d);
  output.debugStr(name(), message_a, L"used_size_d", value);
  Console::put(output);
  
  output.debugStr(name(), message_a, L"used_d");
  Console::put(output);
  
  Console::increaseIndention();
  output.clear();
  for (int32 i = 0; i < (used_size_d - 1); i++) {
    value.assign(used_d[i]);
    value.concat(L",");
    output.concat(value);
  }

  if (used_size_d > 0) {
    value.assign(used_d[used_size_d - 1]);
    output.concat(value);
  }
  
  Console::put(output);
  Console::decreaseIndention();
  
  // positions within the current statement
  //
  value.assign(statement_asgn_d);
  output.debugStr(name(), message_a, L"statement_asgn_d", value);
  Console::put(output);
  
  value.assign(statement_term_d);
  output.debugStr(name(), message_a, L"statement_term_d", value);
  Console::put(output);
  
  value.assign(statement_last_token_d);
  output.debugStr(name(), message_a, L"statement_last_token_d", value);
  Console::put(output);

  // output the limits of file space
  //
  value.assign(base_position_d);
  output.debugStr(name(), message_a, L"base_position_d", value);
  Console::put(output);
  
  value.assign(full_size_d);
  output.debugStr(name(), message_a, L"full_size_d", value);
  Console::put(output);
  
  // output the debug level
  //
  value.assign(debug_level_d);
  output.debugStr(name(), message_a, L"debug_level_d", value);
  Console::put(output);

  // exit gracefully
  //
  return true;
}

// method: setString
//
// arguments:
//  SysString& str: (output) string of the value
//  STATE state: (input) state value
//
// return: a bool8 value indicating status
//
// create a string out of the state, this is used for debug
//
bool8 SofParser::setString(SysString& str_a, STATE state_a) const {

  // branch on state
  //
  if (state_a == NO_GPI) {
    str_a.assign(STATE_NO_GPI);
  }
  else if (state_a == COMMENT_OP_NO_GPI) {
    str_a.assign(STATE_COMMENT_OP_NO_GPI);
  }
  else if (state_a == LITERAL_OP) {
    str_a.assign(STATE_LITERAL_OP);
  }
  else if (state_a == GPI) {
    str_a.assign(STATE_GPI);
  }
  else if (state_a == QUOTE_OP) {
    str_a.assign(STATE_QUOTE_OP);
  }
  else if (state_a == LITERAL_OP_IN_QUOTE) {
    str_a.assign(STATE_LITERAL_OP_IN_QUOTE);
  }
  else if (state_a == GPI_LWS) {
    str_a.assign(STATE_GPI_LWS);
  }
  else if (state_a == COMMENT_OP_GPI) {
    str_a.assign(STATE_COMMENT_OP_GPI);
  }
  else if (state_a == TERMINAL_TRIM_LWS) {
    str_a.assign(STATE_TERMINAL_TRIM_LWS);
  }
  else if (state_a == BLOCK_GPI) {
    str_a.assign(STATE_BLOCK_GPI);
  }
  else if (state_a == BLOCK_GPI_LWS) {
    str_a.assign(STATE_BLOCK_GPI_LWS);
  }
  else {
    return Error::handle(name(), L"setString - undefined state", Error::ENUM, __FILE__,__LINE__);
  }
  
  // exit gracefully
  //
  return true;
}

// method: memSize
//
// arguments: none
//
// return: a int32 number
//
// return the memory size of the class in bytes
//
int32 SofParser::memSize() {
  
  // create size variable and set to the size of default protected
  // data
  //
  int32 size = table_d.memSize();
  size += index_d.memSize();

  // character values
  //
  size += sizeof(terminator_char_d);
  size += sizeof(assignment_char_d);
  size += sizeof(comment_char_d);
  size += sizeof(blockstart_char_d);
  size += sizeof(blockstop_char_d);
  size += sizeof(delimiter_char_d);

  // integer values: states, indexes, and counts
  //
  size += sizeof(state_d);
  size += sizeof(param_d);
  size += sizeof(block_count_d);
  size += sizeof(token_count_d);
  
  // integer values: file positions
  //
  size += sizeof(token_start_d);
  size += sizeof(token_stop_d);
  size += sizeof(statement_asgn_d);
  size += sizeof(statement_term_d);
  size += sizeof(statement_last_token_d);

  // integer values: sizes
  //
  size += sizeof(base_position_d);
  size += sizeof(full_size_d);

  // bool8 values
  //
  size += sizeof(open_index_d);
  size += sizeof(implicit_object_d);
  size += sizeof(implicit_block_d);
  size += sizeof(nest_d);

  // debug level
  //
  size += sizeof(debug_level_d);
    
  // exit gracefully
  //
  return size;
}
