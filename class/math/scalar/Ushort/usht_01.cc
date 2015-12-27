// file: $isip/class/math/scalar/Ushort/usht_01.cc
// version: $Id: usht_01.cc 5181 2000-10-05 02:44:18Z picone $
//

// isip include files
//
#include "Ushort.h"
#include <Console.h>

// method: debug
//
// arguments:
//  const unichar* msg: (input) message to print
//
// return: a boolean value indicating status
//
bool8 Ushort::debug(const unichar* msg_a) const {
  
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
