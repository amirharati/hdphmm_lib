// file: wish_03.cc
// version: $Id: wish_03.cc 5060 2013-07-18 Amir Harati $
//

// isip include files
//
#include "Wishart.h"

// method: assign
//
// arguments:
//  const RandomVecotr& arg: (input) object to assign
//
// return: a bool8 value indicating status
//
// this method assigns the input argument to the current argument
//
bool8 Wishart::assign(const Wishart& arg_a) {

  // assign common data
  //
  algorithm_d = arg_a.algorithm_d;
  implementation_d = arg_a.implementation_d;
  debug_level_d = arg_a.debug_level_d;
  seed_d=arg_a.seed_d;
  Sigma_DI_d=arg_a.Sigma_DI_d;
  DF_d=arg_a.DF_d;
  Using_Sigma_d=arg_a.Using_Sigma_d;
 
  // force initialization:
  //  note that rather than copy the data, we regenerate the data
  //  via an initialization.
  //
  is_valid_d = false;

  // exit gracefully
  //
  return true;
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
bool8 Wishart::clear(Integral::CMODE ctype_a) {

  // if the ctype_a is RESET, RELEASE or FREE clean up all memory:
  //  in this case, this means resetting algorithms and implementations
  //
  if ((ctype_a == Integral::RESET) ||
      (ctype_a == Integral::RELEASE) ||
      (ctype_a == Integral::FREE)) {
    
    // reset algorithm, implementation, and seed
    //
    algorithm_d = DEF_ALGORITHM;
    implementation_d = DEF_IMPLEMENTATION;
    seed_d = DEF_SEED;
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
  is_valid_d = false;

  // exit gracefully
  //
  return true;
}

// method: eq
//
// arguments:
//  const RandomVecotr& arg: (input) input object to assign
//
// return: a bool8 value indicating status
//
// this method checks if two Random objects are the same
//
bool8 Wishart::eq(const Wishart& arg_a) const {

  // check the algorithm
  //
  if (algorithm_d != arg_a.algorithm_d) {
    return false;
  }

  // check parameters common to all algorithms
  //
  else if (implementation_d != arg_a.implementation_d) {
    return false;
  }

  // check specific algorithms
  //
  else if ((algorithm_d == INVERSE)|| (algorithm_d == FORWARD)) {

    // check the implementation
    //
    if ((implementation_d == TRANSFORMATION)) {

      // check the seeds
      //
      if (seed_d != arg_a.seed_d) {
	return false;
      }
    }
    else {
      return Error::handle(name(), L"eq",
			 Error::ARG, __FILE__, __LINE__);
    }
  }

  // check specific algorithms: unknown
  //
  else {
    return Error::handle(name(), L"eq",
			 Error::ARG, __FILE__, __LINE__);
  }

  // exit gracefully
  //
  return true;
}
