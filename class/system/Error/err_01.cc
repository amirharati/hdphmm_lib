// file: $isip/class/system/Error/err_01.cc
// version: $Id: err_01.cc 4883 2000-09-20 12:58:09Z hamaker $
//

// isip include files
//
#include "Error.h"
#include <SysString.h>
#include <Console.h>

// method: debug
//
// arguments:
//  const unichar* msg: (input) debugging message
//  
// return: a bool8 value indicating status
//
bool8 Error::debug(const unichar* msg_a) {
  
  // dump the data
  //
 SysString output;
  SysString value;
  
  value.assign((bool8)initialized_d);
  output.debugStr(name(), msg_a, L"initialized_d", value);
  Console::put(output);
  
  value.assign((int32)exit_level_d);
  output.debugStr(name(), msg_a, L"exit_level_d", value);
  Console::put(output);
  
  value.assign(debug_level_d);
  output.debugStr(name(), msg_a, L"debug_level_d", value);
  Console::put(output);

  // exit gracefully
  //
  return true;
}
