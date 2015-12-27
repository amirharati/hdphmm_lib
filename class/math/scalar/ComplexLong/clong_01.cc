// file: $isip/class/math/scalar/ComplexLong/clong_01.cc
// version: $Id: clong_01.cc 7210 2001-07-22 15:25:31Z jelinek $
//

// isip include files
//
#include "ComplexLong.h"
#include <Console.h>

// method: debug
//
// arguments:
//  const unichar* msg: (input) message to print
//
// return: a boolean value indicating status
//
bool8 ComplexLong::debug(const unichar* msg_a) const {
  
  // declare local variables
  //
  String output;
  String value;
  
  // dump the data
  //
  value.assign(value_d);
  output.debugStr(name(), msg_a, L"value_d", value);
  Console::put(output);

  // exit gracefully
  //
  return true;
}
