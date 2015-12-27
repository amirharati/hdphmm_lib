// file: $isip/class/math/scalar/String/str_01.cc
// version: $Id: str_01.cc 5194 2000-10-05 18:44:52Z picone $
//

// isip include files
//
#include "String.h"
#include <Console.h>

// method: debug
//
// arguments:
//  const unichar* msg: (input) message to print
//
// return: a bool8 value indicating status
//
bool8 String::debug(const unichar* msg_a) const {
  
  // dump the data
  //
  String output(length() + 50);
  String value(length() + 50);
  String numeric;
  
  value.assign((unichar*)DBG_FORMAT_0);

  numeric.assign((int32)capacity_d);
  value.concat(numeric);
  value.concat((unichar*)DBG_FORMAT_1);

  numeric.assign((int32)length());
  value.concat(numeric);
  value.concat((unichar*)DBG_FORMAT_2);
  
  value.concat(*this);
  value.concat((unichar*)DBG_FORMAT_3);
  
  output.debugStr(name(), msg_a, L"value_d", value);

  Console::put(output);

  // exit gracefully
  //
  return true;
}
