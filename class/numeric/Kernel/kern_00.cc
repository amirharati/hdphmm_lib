// file: $isip/class/algo/Kernel/kern_00.cc
// version: $Id: kern_00.cc 7197 2001-07-20 15:51:56Z hamaker $
//

// isip include files
//
#include "Kernel.h"

//------------------------------------------------------------------------
//
// required public methods
//
//-----------------------------------------------------------------------

// method: assign
//
// arguments:
//  const Kernel& arg: (input) object to be assigned
//
// return: a bool8 value indicating status
//
// this method assigns the input object to the current object
//
bool8 Kernel::assign(const Kernel& arg_a) {

  // assign protected data from argument
  //
  algorithm_d = arg_a.algorithm_d;
  constants_d.assign(arg_a.constants_d);

  // set initialization flag
  //
  is_valid_d = arg_a.is_valid_d;

  // exit gracefully
  //
  return true;
}

// method: eq
//
// arguments:
//  const Kernel& arg: (input) object to be compared
//
// return: a bool8 value indicating status
//
// this method checks whether the current object is identical to the
// input object
//
bool8 Kernel::eq(const Kernel& arg_a) const {

  // compare parameters related to algorithm choices
  //
  if ((algorithm_d != arg_a.algorithm_d) ||
      (!constants_d.almostEqual(arg_a.constants_d))) {
    return false;
  }

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
// this method resets the data members to the default values
//
bool8 Kernel::clear(Integral::CMODE ctype_a) {
  
  // reset the data members unless the mode is RETAIN
  //
  if (ctype_a != Integral::RETAIN) {
    algorithm_d = DEF_ALGORITHM;
    constants_d.clear(ctype_a);
  }

  // set the initialization flag
  //
  is_valid_d = false;

  // exit gracefully
  //
  return true;
}

// method: init
//
// arguments: none
//
// return: a bool8 value indicating status
//
// initialize the object so it is ready for use
//
bool8 Kernel::init() {

  // initialize according to the kernel being used
  //
  // algorithm: RECTANGULAR
  //
  if (algorithm_d == LINEAR) {

    // assign the constants if necessary
    //
    if (constants_d.length() != 0) {
      return Error::handle(name(), L"init", ERR_PRM, __FILE__, __LINE__);
    }
  }

  // algorithm: POLYNOMIAL
  //
  else if (algorithm_d == POLYNOMIAL) {

    // assign the constants if necessary
    //
    if (constants_d.length() == 0) {
      constants_d.assign(DEF_POLY_CONSTANTS);
    }
    else if (constants_d.length() != 1) {
      return Error::handle(name(), L"init", ERR_PRM, __FILE__, __LINE__);
    }
  }

  // Algorithm: RBF
  //
  else if (algorithm_d == RBF) {

    // assign the constants if necessary
    //
    if (constants_d.length() == 0) {
      constants_d.assign(DEF_RBF_CONSTANTS);
    }
    else if (constants_d.length() != 1) {
      return Error::handle(name(), L"init", ERR_PRM, __FILE__, __LINE__);
    }
  }

  // algorithm: SIGMOID
  //
  else if (algorithm_d == SIGMOID) {

    // assign the constants if necessary
    //
    if (constants_d.length() == 0) {
      constants_d.assign(DEF_SIGM_CONSTANTS);
    }
    else if (constants_d.length() != 2) {
      return Error::handle(name(), L"init", ERR_PRM, __FILE__, __LINE__);
    }
  }

  // set flag
  //
  is_valid_d = true;

  // exit gracefully
  //
  return true;
}

//-----------------------------------------------------------------------------
//
// we define non-integral constants in the default constructor
//      
//-----------------------------------------------------------------------------

// constants: class name
//
const String Kernel::CLASS_NAME(L"Kernel");

// constants: i/o related constants
//
const String Kernel::DEF_PARAM(L"");
const String Kernel::PARAM_ALGORITHM(L"algorithm");
const String Kernel::PARAM_CONSTANTS(L"constants");

// constants: default constants for each Kernel algorithm
//
const VectorFloat Kernel::DEF_LIN_CONSTANTS(L"");
const VectorFloat Kernel::DEF_POLY_CONSTANTS(L"3.0");
const VectorFloat Kernel::DEF_RBF_CONSTANTS(L"0.5");
const VectorFloat Kernel::DEF_SIGM_CONSTANTS(L"1.0, 1.0");

// constants: NameMap(s) for the enumerated values
//
const NameMap Kernel::ALGO_MAP(L"LINEAR, POLYNOMIAL, RBF, SIGMOID");
  
// static instantiations: memory manager
//
MemoryManager Kernel::mgr_d(sizeof(Kernel), Kernel::name());
Integral::DEBUG Kernel::debug_level_d = Integral::NONE;
