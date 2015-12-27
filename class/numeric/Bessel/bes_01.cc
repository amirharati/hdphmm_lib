// file: $isip/class/numeric/Bessel/bes_01.cc
// version: $Id: bes_01.cc 7146 2001-07-04 22:57:40Z picone $
//

// isip include files
//
#include "Bessel.h"

// method: debug
//
// arguments:
//  const unichar* msg: (input) message to print
//
// return: a boolean value indicating status
//
bool8 Bessel::debug(const unichar* msg_a) const {

  // declare local variable
  //
  String output;

  // output the information message
  //
  output.debugStr(name(), msg_a, L":");
  Console::put(output);
  Console::increaseIndention();
  
  // decrease indention
  //
  Console::decreaseIndention();
  
  // exit gracefully
  //
  return true;
}

