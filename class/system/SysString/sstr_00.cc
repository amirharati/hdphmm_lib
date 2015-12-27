// file: $isip/class/system/SysString/sstr_00.cc
// version: $Id: sstr_00.cc 6366 2001-02-15 23:11:39Z duncan $
//
// notes:
// (1) (7/27/2010): "default format strings" are designed for 32/64-bit
//     Machines and might need an Update in the futture for 128-bit Machines

// isip include files
//
#include "SysString.h"
// method: copy constructor
//
// arguments:
//  const SysString& arg: (input) string to copy
//
// return: none
//
// this method is the copy constructor for the SysString class
//
SysString::SysString(const SysString& arg_a) {

  // initialize the data
  //
  capacity_d = 0;
  value_d = (unichar*)NULL;
  
  // allocate the 0 length string
  //
  allocateMem();

  // assign the string
  //
  assign(arg_a);

  // exit gracefully
  //
}

// method: constructor
//
// arguments:
//  const unichar* data: (input) buffer of data
//
// return: none
//
// this method is the assignment constructor for the SysString class
//
SysString::SysString(const unichar* data_a) {

  // initialize the data
  //
  capacity_d = 0;
  value_d = (unichar*)NULL;
  
  // allocate the 0 length string
  //
  allocateMem();

  // assign the string
  //
  assign(data_a);

  // exit gracefully
  //
}

// method: constructor
//
// arguments:
//  const byte* data: (input) buffer of data
//  SysChar::ENCODE encoding: (input) what encoding scheme to use
//
// return: none
//
// this method is the assignment constructor for the SysString class
//
SysString::SysString(const byte8* data_a, SysChar::ENCODE encoding_a) {

  // initialize the data
  //
  capacity_d = 0;
  value_d = (unichar*)NULL;
  
  // allocate the 0 length string
  //
  allocateMem();

  // assign the string
  //
  assign(data_a, BIG_BUFFER_LENGTH, encoding_a);

  // exit gracefully
  //
}

// method: default constructor
//
// arguments: none
//  long capacity: (input) initial capacity for the string
//
// return: none
//
// this method is the default constructor for the SysString class. capacity_a
// is an optional argument
//
SysString::SysString(int32 capacity_a) {

  // initialize the data
  //
  capacity_d = 0;
  value_d = (unichar*)NULL;
  
  // allocate the 0 length string
  //
  allocateMem();

  // set the capacity
  //
  setCapacity(capacity_a);

  // exit gracefully
  //
}

//-----------------------------------------------------------------------------
//
// we define non-integral constants in the default constructor
//      
//-----------------------------------------------------------------------------

// constants: class name
//
const SysString SysString::CLASS_NAME(L"SysString");

// constants: special strings
//
const unichar SysString::NULL_STRING[] = L"";
const SysString SysString::NULL_PTR(L"null");

// constants: text corresponding to boolean values
//
const SysString SysString::BOOL_TRUE(L"true");
const SysString SysString::BOOL_FALSE(L"false");

// constants: text corresponding to debug values
//
const SysString SysString::DBG_NONE(L"none");
const SysString SysString::DBG_BRIEF(L"brief");
const SysString SysString::DBG_DETAILED(L"detailed");
const SysString SysString::DBG_ALL(L"all");

// constants: text corresponding to compare values
//
const SysString SysString::CMP_EQUAL(L"equal");
const SysString SysString::CMP_LESSER(L"lesser");
const SysString SysString::CMP_GREATER(L"greater");

// constants: text corresponding to file mode values
//
const SysString SysString::MODE_READ_ONLY(L"read only");
const SysString SysString::MODE_READ_PLUS(L"read plus");
const SysString SysString::MODE_WRITE_ONLY(L"write only");
const SysString SysString::MODE_WRITE_PLUS(L"write plus");
const SysString SysString::MODE_APPEND_ONLY(L"append only");
const SysString SysString::MODE_APPEND_PLUS(L"append plus");

// constants: text corresponding to file type values
//
const SysString SysString::TYPE_TEXT(L"text");
const SysString SysString::TYPE_BINARY(L"binary");

// constants: text corresponding to file binary mode values
//
const SysString SysString::BMODE_NATIVE(L"native");
const SysString SysString::BMODE_SWAP(L"swap");
const SysString SysString::BMODE_BIG_ENDIAN(L"big_endian");
const SysString SysString::BMODE_LITTLE_ENDIAN(L"little_endian");

// constants: text corresponding to SysChar encode values
//
const SysString SysString::ENCODE_ASCII(L"ascii");
const SysString SysString::ENCODE_UTF8(L"utf8");
const SysString SysString::ENCODE_UTF16(L"utf16");

// constants: text corresponding to MemoryManager modes
//
const SysString SysString::MMGR_MODE_OPTIMIZE(L"optimize");
const SysString SysString::MMGR_MODE_TRACK(L"track");

// constants: format for debug method output
//
const SysString SysString::DBG_FORMAT_0(L"(");
const SysString SysString::DBG_FORMAT_1(L" >= ");
const SysString SysString::DBG_FORMAT_2(L") \"");
const SysString SysString::DBG_FORMAT_3(L"\"");

// constants: format for debugStr method output
//
const SysString SysString::DBGS_FORMAT_0(L"<");
const SysString SysString::DBGS_FORMAT_1(L"::");
const SysString SysString::DBGS_FORMAT_2(L"> ");
const SysString SysString::DBGS_FORMAT_3(L" = ");

// constants: 8-bit version of the default format strings (for efficiency)
///*
const char SysString::DEF_FMT_VOIDP_8BIT[] = "%p";
const char SysString::DEF_FMT_ULONG_8BIT[] = "%lu";
const char SysString::DEF_FMT_ULLONG_8BIT[] = "%llu";
const char SysString::DEF_FMT_LONG_8BIT[] = "%ld";
const char SysString::DEF_FMT_LLONG_8BIT[] = "%lld";
const char SysString::DEF_WFMT_FLOAT_8BIT[] = "%.6g";
const char SysString::DEF_RFMT_FLOAT_8BIT[] = "%g";
const char SysString::DEF_RFMT_DOUBLE_8BIT[] = "%lg";
const char SysString::DEF_WFMT_DOUBLE_8BIT[] = "%.17lg";

// constants: default value of the class data
//
const SysString SysString::DEF_VALUE(L"");

// static instantiations: debug level
//
Integral::DEBUG SysString::debug_level_d = Integral::NONE;
