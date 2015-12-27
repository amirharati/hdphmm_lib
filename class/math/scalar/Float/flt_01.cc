// file: $isip/class/math/scalar/Float/flt_01.cc
// version: $Id: flt_01.cc 5171 2000-10-05 00:25:45Z picone $
//

// isip include files
//
#include "Float.h"
#include <Console.h>

// method: debug
//
// arguments:
//  const unichar* msg: (input) message to print
//
// return: a boolean value indicating status
//
bool8 Float::debug(const unichar* msg_a) const {
  
  // declare local variables
  //
  String output;
  String value;
  
  // dump the data
  //
  value.assign((float32)value_d);
  output.debugStr(name(), msg_a, L"value_d", value);
  Console::put(output);

  // exit gracefully
  //
  return true;
}
