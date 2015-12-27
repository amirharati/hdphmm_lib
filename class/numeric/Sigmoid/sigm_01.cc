// file: $isip/class/numeric/Sigmoid/sigm_01.cc
// version: $Id: sigm_01.cc 6925 2001-05-03 18:21:56Z srivasta $
//

// isip include files
//
#include "Sigmoid.h"
#include <Console.h>

// method: debug
//
// arguments:
//  const unichar* msg: (input) message to print
//
// return: boolean value indicating status
//
bool8 Sigmoid::debug(const unichar* msg_a) const {

  // declare local variables
  //
  String value;
  String output;

  // output an information message
  //
  output.debugStr(name(), msg_a, L":");
  Console::put(output);
  Console::increaseIndention();

  // output sigmoid parameters
  //
  gain_d.debug(L"gain_d");
  slope_d.debug(L"slope_d");
  xoffset_d.debug(L"xoffset_d");
  yoffset_d.debug(L"yoffset_d");

  // decrease indention
  //
  Console::decreaseIndention();

  // exit gracefully
  //
  return true;
}
