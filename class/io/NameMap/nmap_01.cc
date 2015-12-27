// file: $isip/class/io/NameMap/nmap_01.cc
// version: $Id: nmap_01.cc 5871 2000-12-13 23:36:00Z duncan $
//

// isip include files
// 
#include "NameMap.h"
#include <Console.h>

// method: debug
//
// arguments:
//  const unichar* msg: (input) message to print
//
// return: a bool8 value indicating status
//
bool8 NameMap::debug(const unichar* msg_a) const {

  // declare local variables
  //
  SysString value;
  SysString output;

  // output an information message
  //
  output.debugStr(name(), msg_a, L"names_d");
  Console::put(output);
  Console::increaseIndention();

  // call the debug method of Vector<String>
  //
  for (int32 i = 0; i < size_d; i++) {
    SysString num;
    num.assign((int32)i);
    num.insert(L"element[", 0);
    num.concat(L"]");
    names_d[i].debug((unichar*)num);
  }

  // decrease indention
  //
  Console::decreaseIndention();
  
  // display the checksum
  //
  value.assign((ushort)checksum_d);
  output.debugStr(name(), msg_a, L"checksum_d", value);
  Console::put(output);

  // display the debug level
  //
  value.assign((int32)debug_level_d);
  output.debugStr(name(), msg_a, L"debug_level_d", value);
  Console::put(output);
  
  // exit gracefully
  //
  return true;
}
