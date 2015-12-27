// file: $isip/class/numeric/Bark/bark_01.cc
// version: $Id: bark_01.cc 6810 2001-04-24 19:22:15Z srivasta $
//

// isip include files
//
#include "Bark.h"

// method: debug
//
// arguments:
//  const unichar* msg: (input) message to print
//
// return: a boolean value indicating status
//
bool8 Bark::debug(const unichar* msg_a) const {

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

