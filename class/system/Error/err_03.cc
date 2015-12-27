// file: $isip/class/system/Error/err_03.cc
// version: $Id: err_03.cc 10675 2009-07-21 01:13:30Z tm334 $
//

// isip include files
//
#include "Error.h"
#include <SysString.h>
#include <Console.h>

// include the internal header file
//
#define ISIP_INTERNAL_USE_ONLY
#include "ErrorMessages.h"
#undef ISIP_INTERNAL_USE_ONLY

// method: handle
//
// arguments:
//  const SysString& cname: (input) class name in which the Error occurred
//  const unichar* mname: (input) method name in which the Error occurred
//  int32 code: (input) error code
//  const char* file: (input) filename in which the error occurs
//  int32 line: (input) line number in file in which the error occurs
//  EXIT level: (input) level of the error being handled
//  const SysString& extras: (input) any extra information to be printed
//
// return: a bool8 value indicating status
//
// this method reports an error.
//

bool8 Error::handle(const SysString& cname_a, const unichar* mname_a,
		      int32 code_a, const char* file_a, int32 line_a,
		      EXIT level_a, const SysString& extras_a) {

  // create a temporary string
  //
  SysString temp(mname_a);
  
  // call the master function
  //
  return handle(cname_a, temp, code_a, file_a, line_a, level_a, extras_a);
}

// method: handle
//
// arguments:
//  const SysString& cname: (input) class name in which the Error occurred
//  const SysString& mname: (input) method name in which the Error occurred
//  int32 code: (input) Error code
//  const char* file: (input) filename in which the error occurs
//  int32 line: (input) line number in file in which the error occurs
//  EXIT level: (input) level of the error being handled
//  const SysString& extras: (input) any extra information to be printed
//
// return: a bool8 value indicating status
//
// this method reports an error. whether the program exits or not
// depends on the exit_level_d:
//
//  exit_level_d - NONE:  never exit regardless of level_a
//  exit_level_d - ERROR: exit if the level_a is ERROR
//  exit_level_d - WARNING: always exit no matter level_a is ERROR or WARNING
//
//  note that level_a = NONE is not meaningful, therefore it is treated
//  as the level ERROR
///

bool8 Error::handle(const SysString& cname_a, const SysString& mname_a,
		      int32 code_a, const char* file_a, int32 line_a,
		      EXIT level_a, const SysString& extras_a) {

  // if the extras string is present, output it.
  //
  if (extras_a.length() > 0) {
    Console::put(extras_a);
  }
  
  // build a string to print
  //
  static SysString output(ERROR_MESSAGE_SIZE);
  output.clear();
  SysString num;

  if (debug_level_d > Integral::BRIEF) {

    // start with the filename
    //
    output.assign((const byte8*)file_a);
    output.concat(ERROR_MESSAGE_00);

    // add the line number
    //
    num.assign(line_a);
    output.concat(num);

    // add the start message
    //
    output.concat(ERROR_MESSAGE_01);
  }
  else {

    // add the basic start message
    //
    output.assign(ERROR_MESSAGE_02);
  }
  
  // the rest is unchanged
  //
  output.concat(cname_a);
  output.concat(ERROR_MESSAGE_03);
  output.concat(mname_a);
  output.concat(ERROR_MESSAGE_04);

  // add the error code number
  //
  num.assign((int32)code_a);
  output.concat(num);
  output.concat(ERROR_MESSAGE_05);
    
  // look up the message from the code
  //
  SysString msg;
  getMessage(msg, code_a);
  output.concat(msg);
  
  // add a newline
  //
  output.concat(ERROR_MESSAGE_99);
  
  // print the error message
  //
  Console::put(output);

  // if level_a is NONE, treat it as ERROR
  //
  if (level_a == NONE) {
    level_a = ERROR;
  }
  
  // possibly exit
  //
  if ((exit_level_d != NONE) && (exit_level_d >= level_a)) {
    exit();
  }
  
  // a warning is sufficient, return to the main program
  //
  return false;
}

// method: getMessage
//
// arguments:
//  SysString& msg: (output) message string corresponding to error code
//  int32 code: (input) Error code
//
// return: a bool8 value indicating status
//
// this method displays an Error message corresponding to the Error code.
//
bool8 Error::getMessage(SysString& msg_a, int32 code_a) {
  
  // local variables
  //
  SysString code;
  code.assign(code_a, (unichar*)CODE_FMT);
  SysString count_code;
  
  // look for the error message
  //
  for (int32 i = 0; true; i += 2) {

    // test the length through SysString
    //
    count_code.assign(Error_messages[i]);
    if (count_code.length() == 0) {
      break;
    }

    // error code found
    //
    if (code.eq(count_code)) {
      msg_a.assign(Error_messages[i + 1]);
      return true;
    }
  }
  
  // error code not found, return unknown error code
  //
  msg_a.assign(UNDEFINED_MESSAGE);
  
  // exit gracefully
  //
  return true;
}
