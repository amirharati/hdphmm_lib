// file: $isip/class/shell/Sdb/sdb_01.cc
// version: $Id: sdb_01.cc 9236 2003-06-23 18:12:22Z gao $
//

// isip include files
//
#include "Sdb.h"
#include <Console.h>

// method: debug
//
// arguments:
//  const unichar* msg: (input) message to print
//
// return: a bool8 value indicating status
//
bool8 Sdb::debug(const unichar* msg_a) const {

  // declare local variables
  //
  String value;
  String output;
  
  // display the files
  //
  files_d.debug(L"files_d");

  // display the stacks
  //
  output.debugStr(name(), msg_a, L"displaying queue_d:");
  Console::put(output);
  Console::increaseIndention();
  queue_d.debug(L"queue_d");
  Console::decreaseIndention();

  output.debugStr(name(), msg_a, L"displaying tags_d:");
  Console::put(output);
  Console::increaseIndention();
  tags_d.debug(L"tags_d");
  Console::decreaseIndention();

  output.debugStr(name(), msg_a, L"displaying nums_d:");
  Console::put(output);
  Console::increaseIndention();
  nums_d.debug(L"nums_d");
  Console::decreaseIndention();

  // display other paramters
  //
  value.assign(lookahead_d);
  output.debugStr(name(), msg_a, L"lookahead_d", value);
  Console::put(output);

  value.assign(at_first_d);
  output.debugStr(name(), msg_a, L"at_first_d", value);
  Console::put(output);

  output.debugStr(name(), msg_a, L"output_directory_d", output_directory_d);
  Console::put(output);

  value.assign(dir_pres_d);
  output.debugStr(name(), msg_a, L"dir_pres_d", value);
  Console::put(output);

  output.debugStr(name(), msg_a, L"output_extension_d", output_extension_d);
  Console::put(output);

  output.debugStr(name(), msg_a, L"output_basename_d", output_basename_d);
  Console::put(output);  

  value.assign(debug_level_d);
  output.debugStr(name(), msg_a, L"debug_level_d", value);
  Console::put(output);
  
  // exit gracefully
  //
  return true;
}
