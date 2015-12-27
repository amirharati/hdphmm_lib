// file: $isip/class/system/Console/cons_01.cc
// version: $Id: cons_01.cc 6627 2001-04-09 18:44:18Z duncan $
//

// isip include files
//
#include <SysString.h>
#include "Console.h"

// method: debug
//
// arguments:
//  const unichar* msg: (input) debugging message
//  
// return: a bool8 value indicating status
//
// this is the debug method
//
bool8 Console::debug(const unichar* msg_a) {

  // build the debug string
  //
  SysString output;
  SysString value(L"");
  output.debugStr(name(), msg_a, L"", value);
  output.trimRight(L"= ");
  Console::put(output);

  // output the current console
  //
  cons_d.debug(L"cons_d");
  
  // output the size of the console
  //
  value.assign((int32)size_d);
  output.debugStr(name(), msg_a, L"size_d", value);
  Console::put(output);
  
  // output the initialized flag
  //
  value.assign(initialized_wrap_d);
  output.debugStr(name(), msg_a, L"initialized_wrap_d", value);
  Console::put(output);

  // output each console in the stack
  //
  SysString var;  
  
  for (int32 i = size_d - 1; i >= 0; i--) {
    var.assign((int32)i);
    var.insert(L"stack_d[", 0);
    var.concat(L"]");
    stack_d[i].debug(var);
  }
  
  // exit gracefully
  //
  return true;
}
