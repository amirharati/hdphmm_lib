// file: $isip/class/system/Checksum/cksm_01.cc
// version: $Id: cksm_01.cc 5029 2000-09-26 23:02:27Z picone $
//

// isip include files
//
#include "Checksum.h"
#include <Console.h>


// method: debug
//
// arguments:
//  const unichar* msg: (input) message to print
//
// return: a bool8 value indicating status
//
bool8 Checksum::debug(const unichar* msg_a) const {

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

  // display the current checksum
  //
  value.assign((uint32)cksum_d);
  output.debugStr(name(), msg_a, L"cksum_d", value);
  Console::put(output);

  // display is_valid_d
  //
  value.assign((int32)is_valid_d);
  output.debugStr(name(), msg_a, L"is_valid_d", value);
  Console::put(output);

  // display the table
  //
  output.debugStr(name(), msg_a, L"crc_table_d", L"");
  Console::put(output);
  Console::increaseIndention();
  for (int32 i = 0; i < CRC_TABLE_LENGTH; i++) {
    value.assign((uint32)crc_table_d[i]);
    output.debugStr(name(), msg_a, L"crc_table_d", value);
    Console::put(output);
  }
  Console::decreaseIndention();

  // exit gracefully
  //
  return true;
}
