// file: $isip/class/shell/CommandLine/cmdl_01.cc
// version: $Id: cmdl_01.cc 9209 2003-06-15 03:41:40Z picone $
//

// isip include files
// 
#include "CommandLine.h"
#include <Console.h>

// method: debug
//
// arguments:
//  const unichar* msg: (input) message to print
//
// return: a bool8 value indicating status
//
// this is the debug method and dumps the contents of an object to console
//
bool8 CommandLine::debug(const unichar* msg_a) const {

  // declare local variables
  //
  String value;
  String param;
  String output;

  // display the program name
  //
  output.debugStr(name(), msg_a, L"prog_name_d", prog_name_d);
  Console::put(output);

  // display the various objects holding argument information
  //
  output.debugStr(name(), msg_a, L"options_d:");
  Console::put(output);
  Console::increaseIndention();
  options_d.debug(msg_a);
  Console::decreaseIndention();
  
  output.debugStr(name(), msg_a, L"types_d:");
  Console::put(output);
  Console::increaseIndention();
  types_d.debug(msg_a);
  Console::decreaseIndention();
  
  output.debugStr(name(), msg_a, L"used_d:");
  Console::put(output);
  Console::increaseIndention();
  used_d.debug(msg_a);
  Console::decreaseIndention();
  
  output.debugStr(name(), msg_a, L"args_d:");
  Console::put(output);
  Console::increaseIndention();
  args_d.debug(msg_a);
  Console::decreaseIndention();
  
  output.debugStr(name(), msg_a, L"values_d:");
  Console::put(output);
  Console::increaseIndention();
  args_d.debug(msg_a);
  Console::decreaseIndention();
  
  // display message-related variables
  //
  value.assign(echoc_flag_d);
  output.debugStr(name(), msg_a, L"echoc_flag_d", value);
  Console::put(output);

  value.assign(help_flag_d);
  output.debugStr(name(), msg_a, L"help_flag_d", value);
  Console::put(output);

  value.assign(usage_flag_d);
  output.debugStr(name(), msg_a, L"usage_flag_d", value);
  Console::put(output);

  value.assign(version_flag_d);
  output.debugStr(name(), msg_a, L"version_flag_d", value);
  Console::put(output);

  output.debugStr(name(), msg_a, L"help_msg_d", help_msg_d);
  Console::put(output);
  
  output.debugStr(name(), msg_a, L"usage_msg_d", usage_msg_d);
  Console::put(output);
  
  output.debugStr(name(), msg_a, L"version_msg_d", version_msg_d);
  Console::put(output);

  output.debugStr(name(), msg_a, L"expanded_d", expanded_d);
  Console::put(output);

  // display an Sdb object
  //
  if (debug_level_d >= Integral::DETAILED) {
    output.debugStr(name(), msg_a, L"sdb_d:");
    Console::put(output);
    Console::increaseIndention();
    if (sdb_d != (Sdb*)NULL) {
      sdb_d->debug(msg_a);
    }
    Console::decreaseIndention();
  }
  
  // debug the objects
  //
  output.debugStr(name(), msg_a, L"objects:");
  Console::put(output);
  
  Console::increaseIndention();
  for (int32 i = 0; i < options_d.length(); i++) {
    param.assign(L"objects_d[");
    value.assign(i);
    param.concat(value);
    param.concat(L"]");
    value.assign(objects_d[i]);
    output.debugStr(name(), msg_a, (unichar*)param, value);
    Console::put(output);
  }
  Console::decreaseIndention();
  
  // display the internal flags
  //
  value.assign(usage_printed_d);
  output.debugStr(name(), msg_a, L"usage_printed_d", value);
  Console::put(output);
  
  value.assign(test_mode_d);
  output.debugStr(name(), msg_a, L"test_mode_d", value);
  Console::put(output);
  
  // exit gracefully
  //
  return true;
}
