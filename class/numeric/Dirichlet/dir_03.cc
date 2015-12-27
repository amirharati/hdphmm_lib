// file: randv_03.cc
// version: $Id: randv_03.cc 5060 2013-07-18 Amir Harati $
//

// isip include files
//
#include "Dirichlet.h"

// method: assign
//
// arguments:
//  const RandomVecotr& arg: (input) object to assign
//
// return: a bool8 value indicating status
//
// this method assigns the input argument to the current argument
//
bool8 Dirichlet::assign(const Dirichlet& arg_a) {

  // assign common data
  //
  debug_level_d = arg_a.debug_level_d;
  seed_d=arg_a.seed_d;
  concentration_d=arg_a.concentration_d;

 
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
bool8 Dirichlet::clear(Integral::CMODE ctype_a) {

  // if the ctype_a is RESET, RELEASE or FREE clean up all memory:
  //  in this case, this means resetting algorithms and implementations
  //
  if ((ctype_a == Integral::RESET) ||
      (ctype_a == Integral::RELEASE) ||
      (ctype_a == Integral::FREE)) {
    
    // reset algorithm, implementation, and seed
    //
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
bool8 Dirichlet::eq(const Dirichlet& arg_a) const {

  // check parameters
  //
  if (concentration_d.eq(arg_a.concentration_d) == false){
    return false;
  }

  // check the seeds
  //
  if (seed_d != arg_a.seed_d) {
    return false;
  }

  // exit gracefully
  //
  return true;
}
