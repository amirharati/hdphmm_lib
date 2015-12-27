// file: $isip/class/numeric/Chebyshev/cheb_01.cc
// version: $Id: cheb_01.cc 7145 2001-07-04 22:57:11Z picone $
//

// isip include files
//
#include "Chebyshev.h"

// method: debug
//
// arguments:
//  const unichar* msg: (input) message to print
//
// return: a boolean value indicating status
//
bool8 Chebyshev::debug(const unichar* msg_a) const {

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

