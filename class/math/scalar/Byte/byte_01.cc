// file: $isip/class/math/scalar/Byte/byte_01.cc
// version: $Id: byte_01.cc 5165 2000-10-04 23:22:25Z picone $
//

// isip include files
//
#include "Byte.h"
#include <Console.h>

// method: debug
//
// arguments:
//  const unichar* msg: (input) message to print
//
// return: a boolean value indicating status
//
bool8 Byte::debug(const unichar* msg_a) const {
  
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
