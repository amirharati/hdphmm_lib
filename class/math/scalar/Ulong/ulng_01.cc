// file: $isip/class/math/scalar/Ulong/ulng_01.cc
// version: $Id: ulng_01.cc 5180 2000-10-05 02:42:12Z picone $
//

// isip include files
//
#include "Ulong.h"
#include <Console.h>

// method: debug
//
// arguments:
//  const unichar* msg: (input) message to print
//
// return: a boolean value indicating status
//
bool8 Ulong::debug(const unichar* msg_a) const {
  
  // declare local variables
  //
  String output;
  String value;

  // dump the data
  //
  value.assign((uint32)value_d);
  output.debugStr(name(), msg_a, L"value_d", value);
  Console::put(output);

  // exit gracefully
  //
  return true;
}
