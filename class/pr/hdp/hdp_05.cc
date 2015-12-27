// file: hdp_05.cc
// version: $Id: hdp_05.cc 2013-07-25 Amir Harati$
//

// system include files
//
#include <typeinfo>

// isip include files
//
#include "HDP.h"

// method: assign
//
// arguments:
//  const GaussianModel& arg: (input) data to copy
//
// return: a bool8 value indicating status
//
// copy the input model to current model
//
bool8 HDP::assign(const HDP& arg_a) {

  return Error::handle(name(), L"assign is empty", Error::ARG, __FILE__, __LINE__);
  
}


// method: clear
//
// arguments:
//  Integral::CMODE ctype: (input) clear mode
//
// return: a bool8 value indicating status
//
// this method clears all internal data
//
bool8 HDP::clear(Integral::CMODE ctype_a) {

  // if the ctype_a is RESET, RELEASE or FREE clean up all memory:
  //  in this case, this means resetting algorithms and implementations
  //
  if ((ctype_a == Integral::RESET) ||
      (ctype_a == Integral::RELEASE) ||
      (ctype_a == Integral::FREE)) {
    
    // reset algorithm, implementation, and seed
    //
    
  }

  // if RETAIN, do nothing (a placeholder)
  //
  else if (ctype_a == Integral::RETAIN) {
  }

  // else: invalid mode
  //
  else {
    return Error::handle(name(), L"clear",
                         Error::ARG, __FILE__, __LINE__);
  }  

  // reset all other internal data:
  //  in all cases, we must do this
  //
  

  // exit gracefully
  //
  return true;
}
