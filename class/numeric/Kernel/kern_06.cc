// file: $isip/class/algo/Kernel/kern_06.cc
// version: $Id: kern_06.cc 7197 2001-07-20 15:51:56Z hamaker $
//

// isip include files
//
#include "Kernel.h"

// method: setConstants
//
// arguments: 
//  const VectorFloat& values: (input) vector of constants
//
// return: a boolean value indicating status
//
// this method sets the constants of the Kernel
//
bool8 Kernel::setConstants(const VectorFloat& values_a) {
  
  // make sure the correct number of coefficients are specified
  // for the given algorithm
  //
  if (algorithm_d == LINEAR) {
    if (values_a.length() != DEF_LIN_CONSTANTS.length()) {
      return Error::handle(name(), L"setConstants", ERR, __FILE__, __LINE__);
    }
  }
  else if (algorithm_d == POLYNOMIAL) {
    if (values_a.length() != DEF_POLY_CONSTANTS.length()) {
      return Error::handle(name(), L"setConstants", ERR, __FILE__, __LINE__);
    }
  }
  else if (algorithm_d == RBF) {
    if (values_a.length() != DEF_RBF_CONSTANTS.length()) {
      return Error::handle(name(), L"setConstants", ERR, __FILE__, __LINE__);
    }
  }
  else if (algorithm_d == SIGMOID) {
    if (values_a.length() != DEF_SIGM_CONSTANTS.length()) {
      return Error::handle(name(), L"setConstants", ERR, __FILE__, __LINE__);
    }
  }
  else {
    return Error::handle(name(), L"setConstants", Error::ENUM,
			 __FILE__, __LINE__);
  }
  
  // set the constants
  //
  constants_d.assign(values_a);
  
  // make the kernel invalid
  //
  is_valid_d = false;
  
  // exit gracefully
  //
  return true;
}
