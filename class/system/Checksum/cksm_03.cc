// file: $isip/class/system/Checksum/cksm_03.cc
// version: $Id: cksm_03.cc 5553 2000-11-17 18:15:35Z duncan $
//

// system include files
//
#include <string.h>

// isip include files
//
#include "Checksum.h"

// method: assign
//
// arguments:
//  const Checksum& arg: (input) object to assign
//
// return: a bool8 value indicating status
//
// this method assigns the input argument to the current argument
//
bool8 Checksum::assign(const Checksum& arg_a) {

  // assign common data
  //
  algorithm_d = arg_a.algorithm_d;
  implementation_d = arg_a.implementation_d;
  debug_level_d = arg_a.debug_level_d;

  // check common algorithms: crc*
  //
  if ((arg_a.algorithm_d == CRC_16_CCITT) ||
      (arg_a.algorithm_d == CRC_16) ||
      (arg_a.algorithm_d == CRC_12) ) {

    // check implementation: fast
    //
    if (arg_a.implementation_d == FAST) {

      // do nothing
      //
    }

    // check implementation: slow
    //
    else if (arg_a.implementation_d == SLOW) {

      // do nothing
      //
    }

    // check implementation: unknown
    //
    else {
      return Error::handle(name(), L"assign",
			   Error::ARG, __FILE__, __LINE__);
    }
  }

  // check common algorithms: md5
  //
  else if (arg_a.algorithm_d == MD5) {
    return Error::handle(name(), L"assign",
			 Error::ARG, __FILE__, __LINE__);
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
bool8 Checksum::clear(Integral::CMODE ctype_a) {

  // for retain, simply reset the buffers
  //
  if (ctype_a == Integral::RETAIN) {
    reset();
  }

  // for all other modes call init to reset the algorithm as well.
  //
  else {
    reset();
    init();
  }
  
  // exit gracefully
  //
  return true;
}

// method: eq
//
// arguments:
//  const Checksum& arg: (input) input object to assign
//
// return: a bool8 value indicating status
//
// this method checks if two Checksum objects are the same
//
bool8 Checksum::eq(const Checksum& arg_a) const {

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

  // check specific algorithms: crc*
  //
  else if ((algorithm_d == CRC_16_CCITT) ||
	   (algorithm_d == CRC_16) ||
	   (algorithm_d == CRC_12)) {

    // check the implementation
    //
    if ((implementation_d == SLOW) ||
	(implementation_d == FAST)   ) { 

      // do nothing
      //
    }
    else {
      return Error::handle(name(), L"eq",
			 Error::ARG, __FILE__, __LINE__);
    }
  }

  // check specific algorithms: integration
  //
  else if (algorithm_d == MD5) {
    return Error::handle(name(), L"eq",
			 Error::ARG, __FILE__, __LINE__);
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
