// file: $isip/class/system/Random/rand_01.cc
// version: $Id: rand_01.cc 5047 2000-09-28 18:44:12Z picone $
//

// isip include files
//
#include "Random.h"
#include <Console.h>

// method: debug
//
// arguments:
//  const unichar* msg: (input) message to print
//
// return: a bool8 value indicating status
//
bool8 Random::debug(const unichar* msg_a) const {

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

  // display us_ma_d
  //
  output.debugStr(name(), msg_a, L"displaying us_ma_d:");
  Console::put(output);

  Console::increaseIndention();
  for (int32 i = 0; i < US_MDIM; i++) {
    output.debugStrPrefix(name(), msg_a);
    output.concat(L"us_ma_d[");
    value.assign(i);
    output.concat(value);
    output.concat(L"] = ");
    value.assign(us_ma_d[i]);
    output.concat(value);
    Console::put(output);
  }
  Console::decreaseIndention();

  // display us_inext
  //
  value.assign((int32)us_inext_d);
  output.debugStr(name(), msg_a, L"us_inext_d", value);
  Console::put(output);

  // display us_inextp
  //
  value.assign((int32)us_inextp_d);
  output.debugStr(name(), msg_a, L"us_inextp_d", value);
  Console::put(output);

  // decrease indention
  //
  Console::decreaseIndention();

  // exit gracefully
  //
  return true;
}
