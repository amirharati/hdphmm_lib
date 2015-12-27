// file: $isip/class/system/SysChar/schr_01.cc
// version: $Id: schr_01.cc 4887 2000-09-20 13:29:52Z hamaker $
//

// isip include files
//
#include "SysChar.h"
#include <SysString.h>
#include <Console.h>
// method: debug
//
// arguments:
//  const unichar* msg: (input) debugging message
//  
// return: a bool8 value indicating status
//
bool8 SysChar::debug(const unichar* msg_a) const {
  
  // dump the data
  //
  SysString output;
  SysString value;

  // start with an integer index for the character
  //
  value.assign((int32)value_d);

  // push the integer to the end of the string, output
  // the character itself.
  //
  value.insert(L"> <, ", 0);

  // check the value of character
  //
  if (value_d != 0) {

    // put the character between the brackets
    //
    value(1) = value_d;
  }
  else {

    // delete the space and put null within the brackets
    //
    value.deleteRange(1, 1);
    value.insert(L"null", 1);
  }

  // build the debug string
  //
  output.debugStr(name(), msg_a, L"value_d", value);

  // output the string
  //
   Console::put(output); 
  
  // exit gracefully
  //
  return true;
}
