// file: $isip/class/system/SysChar/schr_03.cc
// version: $Id: schr_03.cc 7770 2002-02-20 20:41:47Z yuan $
//

// isip include files
//
#include "SysChar.h"
#include <Error.h>
#include <Console.h>
#include <SysString.h>

// method: assign
//
// arguments: 
//  unichar arg: (input) value to set
//
// return: a bool8 value indicating status
//
// this method assigns a unichar to the class data
//
bool8 SysChar::assign(unichar arg_a) {

  // assign input value to class data in case of fixed length encoding
  //
  if ((arg_a & UTF16_FIXED) == 0) {
    value_d = arg_a;
  }

  // error off in case of variable length characters
  //
  else {
    return Error::handle(name(), L"assign", ERR_UNUTF16,
			 __FILE__, __LINE__, Error::WARNING);
  }
  
  // exit gracefully
  //
  return true;
}

// method: assign
//
// arguments: 
//  int32& len: (output) number of characters consumed
//  const byte8* data: (input) stream of data from which to set value
//  int32 encoding: (input) type of encoding to expect
//
// return: a bool8 value indicating status
//
// this method assigns the stream of byte8 values to class data
//
bool8 SysChar::assign(int32& len_a, const byte8* data_a, ENCODE encoding_a) {

  // declare local variables
  //
  static byte8 val_1;
  static uint16 val_2;

  // brach on encoding flags
  //

  // check if it is ascii encoding
  //
  if (encoding_a == ENCODE_ASCII) {
    val_1 = (*data_a);
    value_d = (unichar)val_1;
    len_a = 1;
  }

  // check if it is a fixed length encoding
  //
  else if (encoding_a == ENCODE_UTF8) {
    val_1 = (*data_a);
    if ((val_1 & UTF8_FIXED) == 0) {
      value_d = (unichar)val_1;
      len_a = 1;
    }
    else {
      return Error::handle(name(), L"assign", ERR_UNUTF8,
			   __FILE__, __LINE__, Error::WARNING);
    }
  }

  // check if it is a variable length encoding
  //
  else if (encoding_a == ENCODE_UTF16) {
      MemoryManager::memcpy(&val_2, data_a, sizeof(int16));  
    if ((val_2 & UTF16_FIXED) == 0) {
      value_d = (unichar)val_2;
      len_a = 2;
    }
    else {
      return Error::handle(name(), L"assign", ERR_UNUTF16,
			   __FILE__, __LINE__, Error::WARNING);
    }
  }
  else {
    return Error::handle(name(), L"assign", ERR_UNKENC,
			 __FILE__, __LINE__, Error::WARNING);
  }
  
  // exit gracefully
  //
  return true;
}

// method: assign
//
// arguments: 
//  const SysString& arg: (input) string to set the character to
//
// return: a bool8 value indicating status
//
// this method converts the string into a character
//
bool8 SysChar::assign(const SysString& arg_a) {

  // if the length of the input string is 1, just assign it's value
  //
  if (arg_a.length() == 1) {
    return assign(arg_a(0));
  }

  // debugging statement
  //
  if (debug_level_d > Integral::BRIEF) {
   Console::put(L"SysChar::assign: assignment from multi-char string"); 
  }
  
  // assignment was unsuccessful
  //
  return false;
}

// method: clear
//
// arguments:
//  Integral::CMODE ctype: (input) clear mode
//
// return: a bool8 value indicating status
//
// this method resets the character value
//
bool8 SysChar::clear(Integral::CMODE ctype_a) {

  // clear structure in all of the clear modes
  //
  if ((ctype_a == Integral::RETAIN) || (ctype_a == Integral::RESET) ||
      (ctype_a == Integral::RELEASE) || (ctype_a == Integral::FREE)) {

    // set the variable
    //
    value_d = DEF_VALUE;
  }

  // else: unknown clear mode
  //
  else {
    return Error::handle(name(), L"clear", Error::UNK_CMODE,
			 __FILE__, __LINE__);
  }

  // exit gracefully
  //
  return true;
}

// method: get
//
// arguments: 
//  int32& len: (output) number of characters consumed
//  byte8* data: (input) stream of data to place value into
//  ENCODE encoding: (input) type of encoding to expect
//
// return: a bool8 value indicating status
//
// this is the ASCII conversion routine for the SysChar class
//
bool8 SysChar::get(int32& len_a, byte8* data_a, ENCODE encoding_a) const {

  // declare local variables
  //
  static byte8 val_1;
  static uint16 val_2;

  // branch on encoding flags
  //

  // check if it is ascii encoding
  //
  if (encoding_a == ENCODE_ASCII) {
    val_1 = (byte8)value_d;
    *data_a = val_1;
    len_a = 1;
  }

  // check if it is a fixed length encoding
  //
  else if (encoding_a == ENCODE_UTF8) {
    if ((value_d & UTF8_FIXED) == 0) {
      val_1 = (byte8)value_d;
      *data_a = val_1;
      len_a = 1;
    }
    else {
      return Error::handle(name(), L"get", ERR_UNUTF8,
			   __FILE__, __LINE__, Error::WARNING);
    }
  }

  // check if it is a variable length encoding
  //
  else if (encoding_a == ENCODE_UTF16) {
    
    if ((value_d & UTF16_FIXED) == 0) {
      val_2 = (unsigned int16)value_d;
      MemoryManager::memcpy(data_a, &val_2, sizeof(int16)); 
      len_a = 2;
    }
    else {
      return Error::handle(name(), L"get", ERR_UNUTF16,
			   __FILE__, __LINE__, Error::WARNING);
    }
  }

  // else: unknown encoding
  //
  else {
    return Error::handle(name(), L"get", ERR_UNKENC,
			 __FILE__, __LINE__, Error::WARNING);
  }
  
  // exit gracefully
  //
  return true;
}
