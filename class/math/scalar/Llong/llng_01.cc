// file: $isip/class/scalar/Llong/llng_01.cc
// version: $Id: llng_01.cc 5172 2000-10-05 01:47:06Z picone $
//

// isip include files
//
#include "Llong.h"
#include <Console.h>

// method: debug
//
// arguments:
//  const unichar* msg: (input) message to print
//
// return: a boolean value indicating status
//
bool8 Llong::debug(const unichar* msg_a) const {
  
  // declare local variables
  //
  String output;
  String value;

  // dump the data
  //
  value.assign((int64)value_d);
  output.debugStr(name(), msg_a, L"value_d", value);
  Console::put(output);

  // exit gracefully
  //
  return true;
}
