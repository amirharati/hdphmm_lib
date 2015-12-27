// file: $isip/class/shell/DebugLevel/dbgl_01.cc
// version: $Id: dbgl_01.cc 5884 2000-12-14 16:05:53Z hamaker $
//

// isip include files
//
#include "DebugLevel.h"
#include <Console.h>

// method: debug
//
// arguments:
//  const unichar* msg: (input) message to print
//
// return: a bool8 value indicating status
//
bool8 DebugLevel::debug(const unichar* msg_a) const {
  
  // dump the namemap
  //
  LEVEL_MAP.debug(msg_a);

  // dump the data
  //
  String output;
  String value(LEVEL_MAP.getName(value_d));
  output.debugStr(name(), msg_a, L"value_d", value);
  Console::put(output);

  // exit gracefully
  //
  return true;
}
