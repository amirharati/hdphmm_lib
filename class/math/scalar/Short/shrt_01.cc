// file: $isip/class/math/scalar/Short/shrt_01.cc
// version: $Id: shrt_01.cc 5178 2000-10-05 02:28:53Z picone $
//

// isip include files
//
#include "Short.h"
#include <Console.h>

// method: debug
//
// arguments:
//  const unichar* msg: (input) message to print
//
// return: a boolean value indicating status
//
bool8 Short::debug(const unichar* msg_a) const {
  
  // declare local variables
  //
  String output;
  String value;

  // dump the data
  //
  value.assign((int32)value_d);
  output.debugStr(name(), msg_a, L"value_d", value);
  Console::put(output);

  // exit gracefully
  //
  return true;
}
