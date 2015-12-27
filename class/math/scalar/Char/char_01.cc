// file: $isip/class/math/scalar/Char/char_01.cc
// version: $Id: char_01.cc 5167 2000-10-04 23:37:36Z picone $
//

// isip include files
//
#include "Char.h"
#include <Console.h>

// method: debug
//
// arguments:
//  const unichar* msg: (input) message to print
//
// return: a bool8 value indicating status
//
bool8 Char::debug(const unichar* msg_a) const {
  
  // declare local variables
  //
  String output;
  String value;

  // start with an integer index for the character
  //
  value.assign((int32)value_d);

  // push the integer to the end of the string, output
  // the character itself.
  //
  value.insert(L"> <, ", 0);
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
