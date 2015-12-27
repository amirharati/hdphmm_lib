// file: $isip/class/math/scalar/Ullong/ullg_01.cc
// version: $Id: ullg_01.cc 5179 2000-10-05 02:38:17Z picone $
//

// isip include files
//
#include "Ullong.h"
#include <Console.h>

// method: debug
//
// arguments:
//  const unichar* msg: (input) message to print
//
// return: a boolean value indicating status
//
bool8 Ullong::debug(const unichar* msg_a) const {
  
  // declare local variables
  //
  String output;
  String value;

  // dump the data
  //
  value.assign((uint64)value_d);
  output.debugStr(name(), msg_a, L"value_d", value);
  Console::put(output);

  // exit gracefully
  //
  return true;
}
