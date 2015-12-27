// file: $isip/class/system/Checksum/cksm_04.cc
// version: $Id: cksm_04.cc 5660 2000-11-22 17:24:28Z picone $
//

// isip include files
//
#include "Checksum.h"
#include <Console.h>

// method: init
//
// arguments: none
//
// return: a bool8 value indicating status
//
// this method pre-computes various constants used in this class
//
bool8 Checksum::init() {

  // check algorithm: CRC_16_CCITT
  //
  if (algorithm_d == CRC_16_CCITT) {
    return initCrc(CRC_16_CCITT_POLYNOMIAL);
  }

  // check algorithm: CRC_16
  //
  else if (algorithm_d == CRC_16) {
    return initCrc(CRC_16);
  }

  // check algorithm: CRC_12
  //
  else if (algorithm_d == CRC_12) {
    return initCrc(CRC_12);
  }

  // check algorithm: MD5
  //
  else if (algorithm_d == MD5) {
    return Error::handle(name(), L"init",
			 Error::ARG, __FILE__, __LINE__);
  }  

  // check algorithm: unknown
  //
  else {
    return Error::handle(name(), L"init",
			 Error::ARG, __FILE__, __LINE__);
  }  

  // exit gracefully
  //
  return true;
}

// method: reset
//
// arguments: none
//
// return: a bool8 value indicating status
//
// this method resets the internal checksum register
//
bool8 Checksum::reset() {

  // check algorithm: CRC_16_CCITT, CRC_16, CRC_12
  // fast or slow methods use the same initial value
  //
  if ((algorithm_d == CRC_16_CCITT) ||
      (algorithm_d == CRC_16) ||
      (algorithm_d == CRC_12)) {
    cksum_d = CRC_INITIAL_VALUE;
  }

  // check algorithm: MD5
  //
  else if (algorithm_d == MD5) {
    return Error::handle(name(), L"reset",
			 Error::ARG, __FILE__, __LINE__);
  }  

  // check algorithm: unknown
  //
  else {
    return Error::handle(name(), L"reset",
			 Error::ARG, __FILE__, __LINE__);
  }  

  // exit gracefully
  //
  return true;
}

// method: initCrc
//
// arguments:
//  uint32 poly: (input) a specification for the CRC polynomial
//
// return: a bool8 value indicating status
//
// this method pre-computes various constants used in this class.
// see the compute methods for more details about the algorithms used.
//
bool8 Checksum::initCrc(uint32 poly_a) {

  // check implementation: SLOW
  //
  if (implementation_d == SLOW) {

    // do nothing
    //
  }

  // check implementation: FAST
  //
  else if (implementation_d == FAST) {

    // check for a valid polynomial
    //
    if (poly_a == 0) {
      return Error::handle(name(), L"initCrc", ERR_POLY,
			   __FILE__, __LINE__);
    }

    // loop over all entries in the table
    //
    for (int32 n = 0; n < CRC_TABLE_LENGTH; n++) {

      // compute table values bit-by-bit
      //
      uint32 crc = n;

      for (int32 i = 0; i < 8; i++) {

	// gotta luv those bit-level manipulations
	//
	if (crc & 1) {
	  crc >>= 1;
	  crc ^= poly_a;
	}
	else {
	  crc >>= 1;
	}

	// assign the value to the table
	//
	crc_table_d[n] = crc;
      }
    }
  }

  // check implementation: unknown
  //
  else {
    return Error::handle(name(), L"initCrc",
			 Error::ARG, __FILE__, __LINE__);
  }  

  // clear the crc register
  //
  cksum_d = (uint32)0;

  // make the status valid
  //
  is_valid_d = true;

  // exit gracefully
  //
  return true;
}

// method: compute
//
// arguments:
//  const SysString& input: (input) character data
//
// return: a bool8 value indicating status
//
// this method selects the appropriate computational method
//
bool8 Checksum::compute(const SysString& input_a) {

  // declare local variables
  //
  bool8 status = false;
  
  // check valid flag
  //
  if (!is_valid_d) {
    init();
  }

  // check algorithm: crc*
  //
  if ((algorithm_d == CRC_16_CCITT) ||
      (algorithm_d == CRC_16) ||
      (algorithm_d == CRC_12)) {
    
    // check implementations
    //
    if (implementation_d == FAST) {
      status = computeCrcFast(input_a);
    }
    else if (implementation_d == SLOW) {
      return Error::handle(name(), L"compute",
			   Error::ARG, __FILE__, __LINE__);
    }
    else {
      return Error::handle(name(), L"compute",
			   Error::ARG, __FILE__, __LINE__);
    }
  }

  // check algorithm: md5
  //
  else if (algorithm_d == MD5) {
    return Error::handle(name(), L"compute",
			 Error::ARG, __FILE__, __LINE__);
  }  

  // check algorithm: unknown
  //
  else {
    return Error::handle(name(), L"compute",
			 Error::ARG, __FILE__, __LINE__);
  }  

  // provide some useful debugging information
  //
  if (debug_level_d > Integral::NONE) {
    if (debug_level_d >= Integral::ALL) {
      debug(CLASS_NAME);
      Console::increaseIndention();
    }    
    if (debug_level_d >= Integral::DETAILED) {
      input_a.debug(CLASS_NAME);
    }
    if (debug_level_d >= Integral::BRIEF) {
      SysString value;
      SysString output;
      value.assign((uint32)cksum_d);
      output.debugStr(name(), CLASS_NAME, L"output", value);
      Console::put(output);
    }
    if (debug_level_d >= Integral::ALL) {
      Console::decreaseIndention();
    }    
  }

  // exit gracefully
  //
  return status;
}

// method: compute
//
// arguments:
//  const byte8* input: (input) bit-stream data
//  int32 nbytes: (input) number of bytes to process
//
// return: a bool8 value indicating status
//
// this method selects the appropriate computational method
//
bool8 Checksum::compute(const byte8* input_a, int32 nbytes_a) {

  // declare local variables
  //
  bool8 status = false;
  
  // check valid flag
  //
  if (!is_valid_d) {
    init();
  }

  // check algorithm: crc*
  //
  if ((algorithm_d == CRC_16_CCITT) ||
      (algorithm_d == CRC_16) ||
      (algorithm_d == CRC_12)) {
    
    // check implementations
    //
    if (implementation_d == FAST) {
      status = computeCrcFast(input_a, nbytes_a);
    }
    else if (implementation_d == SLOW) {
      return Error::handle(name(), L"compute",
			   Error::ARG, __FILE__, __LINE__);
    }
    else {
      return Error::handle(name(), L"compute",
			   Error::ARG, __FILE__, __LINE__);
    }
  }

  // check algorithm: md5
  //
  else if (algorithm_d == MD5) {
    return Error::handle(name(), L"compute",
			 Error::ARG, __FILE__, __LINE__);
  }  

  // check algorithm: unknown
  //
  else {
    return Error::handle(name(), L"compute",
			 Error::ARG, __FILE__, __LINE__);
  }  

  // exit gracefully
  //
  return status;
}


// method: computeCrcFast
//
// arguments:
//  const SysString& input: (input) input data
//
// return: a bool8 value indicating status
//
// this method computes a checksum using a cyclic redundancy code (CRC)
// and a table lookup for speed. Two excellent sources for these
// algorithms are:
//
//  G.J. Holzmann, Design and Validation of Computer Protocols,
//  Prentice-Hall, New York, New York, USA, pp. 57-63, 1991.
//
// or,
//
//  K. Pohlmann, Principles of Digital Audio (Third Edition),
//  McGraw-Hill, New York, New York, USA, pp. 142-147, 1995.
//
// or,
//
//  R.N. Williams, A Painless Guide To CRC Error Detection Algorithms,
//  http://www.repairfaq.org/filipg/LINK/F_crc_v3.html
//  E-Mail : ross@guest.adelaide.edu.au 
//  Date : 19 August 1993 
//  Version : 3.00 
//  FTP: ftp.adelaide.edu.au/pub/rocksoft/crc_v3.txt 
//  WWW: http://www.on.net/clients/rocksoft/rocksoft/ 
//  Company : Rocksoft(tm) Pty Ltd 
//  Snail : 16 Lerwick Avenue, Hazelwood Park 5066, Australia 
//  Fax : +61 8 373-4911 (c/- Internode Systems Pty Ltd) 
//  Phone : +61 8 379-9217 (10am to 10pm Adelaide Australia time) 
// 
// the principle feature of this approach is a table is used to
// compute the bulk of the checksum. this code has been verified
// against other implementations and seems to produce a generally
// accepted result:
//
//  Test vector: "Joe"   		Result: 42810
//  Test vector: "abcdefghijkl"		Result: 15564
//
// unfortunately, the code is cryptic. better implementations, such
// as Williams implementation listed above, are even more obtuse...
// but efficient
//
bool8 Checksum::computeCrcFast(const SysString& input_a) {

  // you wanted a fast method... which means the code is
  // damn near unreadable...
  //
  int32 i_end = input_a.length();

  for (int32 i = 0; i < i_end; i++) {
    cksum_d = crc_table_d[(cksum_d ^ (uint32)input_a(i)) & 0xff]
      ^ (cksum_d >> 8);
  }

  // clip the result to 16 bits
  //
  cksum_d = cksum_d & 0xffff;

  // exit gracefully
  //
  return true;
}

// method: computeCrcFast
//
// arguments:
//  const byte8* input: (input) bit-stream data
//  int32 nbytes: (input) number of bytes to process
//
// return: a bool8 value indicating status
//
// this method computes a checksum using a cyclic redundancy code
// (CRC) and a table lookup for speed. this is the same algorithm as
// listed above.  
//
bool8 Checksum::computeCrcFast(const byte8* input_a, int32 nbytes_a) {

  // you wanted a fast method... which means the code is
  // damn near unreadable...
  //
  for (int32 i = 0; i < nbytes_a; i++) {
    cksum_d = crc_table_d[(cksum_d ^ (uint32)input_a[i]) & 0xff]
      ^ (cksum_d >> 8);
  }

  // clip the result to 16 bits
  //
  cksum_d = cksum_d & 0xffff;

  // exit gracefully
  //
  return true;
}
