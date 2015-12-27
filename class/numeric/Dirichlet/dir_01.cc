// file: randv_01.cc
// version: $Id: randv_01.cc 5047 2013-07-18  Amir Harati $
//

// isip include files
//
#include "Dirichlet.h"
#include <Console.h>

// method: debug
//
// arguments:
//  const unichar* msg: (input) message to print
//
// return: a bool8 value indicating status
//
bool8 Dirichlet::debug(const unichar* msg_a) const {

  // declare local variables
  //
  SysString value;
  SysString output;
 
  // output an information message
  //
  output.debugStr(name(), msg_a, L":");
  Console::put(output);
  Console::increaseIndention();
  
  // display seed
  //
  value.assign((int32)seed_d);
  output.debugStr(name(), msg_a, L"seed_d", value);
  Console::put(output);

  // display debug_level
  //
  value.assign((int32)debug_level_d);
  output.debugStr(name(), msg_a, L"debug_level_d", value);
  Console::put(output);

  // display is_valid
  //
  value.assign((int32)is_valid_d);
  output.debugStr(name(), msg_a, L"is_valid_d", value);
  Console::put(output);

  //  params
  //
  dist_len_d.debug(L"vector_len_d(dist_len)");
  concentration_d.debug(L"concentration_d");

  // rnd1 & rnd2  debug info
  //
  rnd_d.debug(L"rnd_d");

  // result info
  //
  result_d.debug(L"result_d");
 
  // exit gracefully
  //
  return true;
}
