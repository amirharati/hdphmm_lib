// file: $isip/class/shell/Filename/fn_01.cc
// version: $Id: fn_01.cc 9209 2003-06-15 03:41:40Z picone $
//

// isip include files
//
#include "Filename.h"
#include <String.h>
#include <Console.h>

// method: debug
//
// arguments:
//  const unichar* msg: (input) message to print
//
// return: a bool8 value indicating status
//
bool8 Filename::debug(const unichar* msg_a) const {

  // dump the data
  //
  String output;
  String value;
  String numeric;
  
  value.assign((unichar*)DBG_FORMAT_0);

  // get the capacity
  //
  numeric.assign((int32)capacity_d);
  value.concat(numeric);
  value.concat((unichar*)DBG_FORMAT_1);

  // get the length
  //
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
