// file: $isip/class/algo/Kernel/kern_01.cc
// version: $Id: kern_01.cc 7197 2001-07-20 15:51:56Z hamaker $
//

// isip include files
//
#include "Kernel.h"
#include <Console.h>

// method: debug
//
// arguments:
//  const unichar* msg: (input) message to print
//
// return: a boolean value indicating status
//
bool8 Kernel::debug(const unichar* msg_a) const {

  // declare local variables
  //
  String value;
  String output;
  String empty_str;

  // output an information message
  //
  output.debugStr(name(), msg_a, L":");
  Console::put(output);
  Console::increaseIndention();
  
  // display the algorithm name
  //
  output.debugStr(name(), msg_a, L"algorithm_d",
		  ALGO_MAP.getName((long)algorithm_d));
  Console::put(output);

  // display the constants
  //
  constants_d.debug(L"constants_d");
  
  // decrease indention
  //
  Console::decreaseIndention();
 
  // exit gracefully
  //
  return true;
}
