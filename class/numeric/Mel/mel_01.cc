// file: $isip/class/numeric/Mel/mel_01.cc
// version: $Id: mel_01.cc 6808 2001-04-24 15:39:20Z srivasta $
//

// isip include files
//
#include "Mel.h"

// method: debug
//
// arguments:
//  const unichar* msg: (input) message to print
//
// return: a boolean value indicating status
//
bool8 Mel::debug(const unichar* msg_a) const {

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

