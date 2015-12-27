// file: $isip/class/system/Random/rand_03.cc
// version: $Id: rand_03.cc 5060 2000-09-29 16:00:10Z picone $
//
// 07/06/2013 (amir harati): added a set method and support for a
//                           gamma distribution.
//
// isip include files
//
#include "Random.h"

// method: setParameters
//
// arguments:
//  float64 value_a: (input) an algorithm-specific parameter that
//                           controls the shape of a distribition
//
// return: a bool8 value indicating status
//
// this method sets internal parameters for an algorithm.
//
bool8 Random::setParameters(float64 value) {

  // Algorithm: UNIFORM and GAUSSIAN
  //  these algorithms don't need this
  //
  if ((algorithm_d == UNIFORM) || (algorithm_d == GAUSSIAN)) {
    return false;
  }

  // algorithm: GAMMA
  //
    gacc_alpha_d = value;
  

  // exit gracefully
  //
  return true;
}

// method: getParameters
//
// arguments: none
//
// return: a float64 containing an internal parameter
//
float64 Random::getParameters() {

  // Algorithm: UNIFORM and GAUSSIAN
  //  these algorithms don't use internal parameters
  //
  if ((algorithm_d == UNIFORM) || (algorithm_d == GAUSSIAN)) {
    return Error::handle(name(), L"getParameters",
			 Error::ARG, __FILE__, __LINE__);
  }

  // exit gracefully
  //
  return gacc_alpha_d;
}

// method: assign
//
// arguments:
//  const Random& arg: (input) object to assign
//
// return: a bool8 value indicating status
//
// this method assigns the input argument to the current argument
//
bool8 Random::assign(const Random& arg_a) {

  // assign common data
  //
  algorithm_d = arg_a.algorithm_d;
  implementation_d = arg_a.implementation_d;
  debug_level_d = arg_a.debug_level_d;

  // check common algorithms: uniform
  //
  if (arg_a.algorithm_d == UNIFORM) {

    // check implementation: subtractive
    //
    if (arg_a.implementation_d == SUBTRACTIVE) {

      // assign seeds
      //
      seed_d = arg_a.seed_d;
    }

    // check implementation: unknown
    //
    else {
      return Error::handle(name(), L"assign",
			   Error::ARG, __FILE__, __LINE__);
    }
  }

  // check common algorithms: Gaussian
  //
  else if (arg_a.algorithm_d == GAUSSIAN) {

    // check implementation: transformation
    //
    if (arg_a.implementation_d == TRANSFORMATION) {

      // assign seeds
      //
      seed_d = arg_a.seed_d;
    }

    // check implementation: unknown
    //
    else {
      return Error::handle(name(), L"assign",
			   Error::ARG, __FILE__, __LINE__);
    }
  }
  else if (arg_a.algorithm_d == GAMMA) {
    if (arg_a.implementation_d == ACCREJ ) {
      
      // assign seeds
      //
      seed_d=arg_a.seed_d;
    }    
    
  
  } 
  // check common algorithms: unknown
  //
  else {
    return Error::handle(name(), L"assign",
			 Error::ARG, __FILE__, __LINE__);
  }  

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
bool8 Random::clear(Integral::CMODE ctype_a) {

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
//  const Random& arg: (input) input object to assign
//
// return: a bool8 value indicating status
//
// this method checks if two Random objects are the same
//
bool8 Random::eq(const Random& arg_a) const {

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

  // check specific algorithms: uniform
  //
  else if ((algorithm_d == UNIFORM) || (algorithm_d == GAUSSIAN) || (algorithm_d == GAMMA)) {

    // check the implementation
    //
    if ((implementation_d == SUBTRACTIVE) ||
	(implementation_d == CONGRUENTIAL) ||
	(implementation_d == TRANSFORMATION)||
	(implementation_d== ACCREJ)) {

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
