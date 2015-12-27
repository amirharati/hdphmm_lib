// file: $isip/class/math/scalar/ComplexDouble/cdbl_01.cc
// version: $Id: cdbl_01.cc 6796 2001-04-23 21:16:41Z peng $
//

// isip include files
//
#include "ComplexDouble.h"
#include <Console.h>

// method: debug
//
// arguments:
//  const unichar* msg: (input) message to print
//
// return: a boolean value indicating status
//
bool8 ComplexDouble::debug(const unichar* msg_a) const {
  
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
