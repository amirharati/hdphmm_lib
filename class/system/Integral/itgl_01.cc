// file: $isip/class/system/Integral/itgl_01.cc
// version: $Id: itgl_01.cc 4939 2000-09-21 22:24:25Z duncan $
//

// isip include files
//
#include "Integral.h"

#include <Console.h>
#include <SysString.h>
#include <Error.h>

// method: debug
//
// arguments:
//  const unichar* msg: (input) debugging message
//  
// return: a boolean value indicating status
//
bool8 Integral::debug(const unichar* msg_a) {
  
  // declare local variables
  //
  SysString output;
  static SysString no_value(L"");

  // dump the data
  //
  output.debugStr(name(), msg_a, L"no data", no_value);

  // clip the equal sign
  //
  output.trimRight(L"= ");
  
  // exit gracefully
  //
//  return Console::put(output);
    return true;
}
