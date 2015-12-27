// file: $isip/class/math/scalar/Double/dbl_01.cc
// version: $Id: dbl_01.cc 5095 2000-10-01 14:54:55Z picone $
//

// isip include files
//
#include "Double.h"
#include <Console.h>

// method: debug
//
// arguments:
//  const unichar* msg: (input) message to print
//
// return: a boolean value indicating status
//
bool8 Double::debug(const unichar* msg_a) const {
  
  // declare local variables
  //
  String output;
  String value;
  
  // dump the data
  // 
  value.assign((float64)value_d);
  output.debugStr(name(), msg_a, L"value_d", value);
  Console::put(output);

  // exit gracefully
  //
  return true;
}

