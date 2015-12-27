// file: $isip/class/io/Sof/sof_01.cc
// version: $Id: sof_01.cc 5643 2000-11-21 19:50:11Z duncan $
//

// isip include files
//
#include "Sof.h"
#include <Console.h>

// method: debug
//
// arguments:
//  const unichar* msg: (input) debugging message
//
// return: a bool8 value indicating status
//
// this method displays the values of all internal data
//
bool8 Sof::debug(const unichar* msg_a) const {
  
  // dump general information
  //
  name_d.debug(L"name_d");
  expanded_name_d.debug(L"expanded_name_d");

  SysString output;
  SysString value;

  // output file type
  //
  if (file_type_d == File::TEXT) {
    value.assign(File::TYPE_TEXT);
  }
  else if (file_type_d == File::BINARY) {
    value.assign(File::TYPE_BINARY);
  }
  else {
    return Error::handle(name(), L"debug", Error::ENUM, __FILE__, __LINE__);
  }
  
  output.debugStr(name(), msg_a, L"file_type_d", value);
  Console::put(output);
  
  // unix I/O related variables
  //
  fp_d.debug(L"fp_d");
  
  // auxiliary information
  //
  SysChar c;
  c.assign(delimiter_d);
  c.debug(L"delimiter_d");
  
  value.assign(end_of_header_d);
  output.debugStr(name(), msg_a, L"end_of_header_d", value);
  Console::put(output);

  value.assign(end_of_data_d);
  output.debugStr(name(), msg_a, L"end_of_data_d", value);
  Console::put(output);

  value.assign(cur_pos_d);
  output.debugStr(name(), msg_a, L"cur_pos_d", value);
  Console::put(output);

  value.assign(partial_write_d);
  output.debugStr(name(), msg_a, L"partial_write_d", value);
  Console::put(output);

  value.assign(cur_data_d);
  output.debugStr(name(), msg_a, L"cur_data_d", value);
  Console::put(output);

  value.assign(disable_lock_d);
  output.debugStr(name(), msg_a, L"disable_lock_d", value);
  Console::put(output);
  
  value.assign(lock_retry_d);
  output.debugStr(name(), msg_a, L"lock_retry_d", value);
  Console::put(output);

  value.assign(lock_delay_d);
  output.debugStr(name(), msg_a, L"lock_delay_d", value);
  Console::put(output);

  value.assign(file_checksum_d);
  output.debugStr(name(), msg_a, L"file_checksum_d", value);
  Console::put(output);

  // linked lists used to process the object index
  //
  index_d.debug(L"index_d");
  
  // scratch space for magic number manipulations
  //
  cname_d.debug(L"cname_d");
  version_d.debug(L"version_d");
  magic_d.debug(L"magic_d");
  
  // debugging parameters
  //
  value.assign(debug_level_d);
  output.debugStr(name(), msg_a, L"debug_level_d", value);
  Console::put(output);

  // exit gracefully
  //
  return true;
}
