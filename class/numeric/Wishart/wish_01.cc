// file: wish_01.cc
// version: $Id: wish_01.cc 5047 2013-07-18  Amir Harati $
//

// isip include files
//
#include "Wishart.h"
#include <Console.h>

// method: debug
//
// arguments:
//  const unichar* msg: (input) message to print
//
// return: a bool8 value indicating status
//
bool8 Wishart::debug(const unichar* msg_a) const {

  // declare local variables
  //
  SysString value;
  SysString output;
 
  // output an information message
  //
  output.debugStr(name(), msg_a, L":");
  Console::put(output);
  Console::increaseIndention();
  
  // display the algorithm choice
  //
  value.assign((int32)algorithm_d);
  output.debugStr(name(), msg_a, L"algorithm_d", value);
  Console::put(output);

  // display the implementation name
  //
  value.assign((int32)implementation_d);
  output.debugStr(name(), msg_a, L"implementation_d", value);
  Console::put(output);

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
  Sigma_DI_d.debug(L"Sigma_DI_d");
  DF_d.debug(L"DF_d");
  Using_Sigma_d.debug(L"Using_Sigma_d");


  // rnd1 & rnd2  debug info
  //
  rnd1_d.debug(L"rnd1");
  rnd2_d.debug(L"rnd2");
  
  // temp_result
  //
  temp_result_d.debug(L"temp_result");

  // result info
  //
  result_d.debug(L"result");

  

  //
  // exit gracefully
  //
  return true;
}
