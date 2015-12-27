// file: $isip/class/math/scalar/Boolean/bool_01.cc
// version: $Id: bool_01.cc 5161 2000-10-04 19:01:01Z picone $
//

// isip include files
//
#include <Console.h>
#include <Long.h>
#include "Boolean.h"

// method: debug
//
// arguments:
//  const unichar* msg: (input) message to print
//
// return: a boolean value indicating status
//
bool8 Boolean::debug(const unichar* msg_a) const {
  
  // declare local variables
  //
  String output;
  String value;
  
  // dump the data
  //
  value.assign((bool8)value_d);
  output.debugStr(name(), msg_a, L"value_d", value);
  Console::put(output);

  // exit gracefully
  //
  return true;
}
