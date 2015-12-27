// file: $isip/class/system/SysHeap/sh_01.cc
// version: $Id: sh_01.cc 5660 2000-11-22 17:24:28Z picone $
//

// isip include files
//
#include "SysHeap.h"
#include <SysString.h>
#include <Console.h>

// method: debug
//
// arguments:
//  const unichar* msg: (input) message to print
//
// return: a bool8 value indicating status
//
bool8 SysHeap::debug(const unichar* msg_a) const {

  // declare strings to hold class data and values
  //
  SysString value;
  SysString output;
  SysString param;

  // output data only when the debug level is ALL
  //
  if (debug_level_d == Integral::ALL) {

    // debug the data
    //
    for (int32 i = 0; i < num_elements_d; i++) {
      param.assign(L"data_d[");
      value.assign(i);
      param.concat(value);
      param.concat(L"]");
      value.assign(data_d[i]);
      output.debugStr(name(), msg_a, (unichar*)param, value);
      Console::put(output);
    }
  }
    
  // display the number of elements
  //
  value.assign(num_elements_d);
  output.debugStr(name(), msg_a, L"num_elements_d", value);
  Console::put(output);
  
  // display the capacity
  //
  value.assign(capacity_d);
  output.debugStr(name(), msg_a, L"capacity_d", value);
  Console::put(output);

  // display the capacity
  //
  value.assign(grow_factor_d);
  output.debugStr(name(), msg_a, L"grow_factor_d", value);
  Console::put(output);

  // exit gracefully
  //
  return true;
}
