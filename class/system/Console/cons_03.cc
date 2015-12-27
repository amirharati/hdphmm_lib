// file: $isip/class/system/Console/cons_03.cc
// version: $Id: cons_03.cc 4882 2000-09-20 12:51:47Z hamaker $
//

// isip include files
//
#include "Console.h"
#include <SysString.h>

// method: open
//
// arguments:
//  const unichar* filename: (input) file to open
//  MODE mode: (input) open mode
//
// return: a bool8 value indicating status
//
// open the file
//
bool8 Console::open(const unichar* filename_a, MODE mode_a) {

  SysString temp(filename_a);
  
  // call the master function
  //
  return open(temp, mode_a);
}

// method: open
//
// arguments:
//  const SysString& filename: (input) file to open
//  MODE mode: (input) open mode
//
// return: a bool8 value indicating status
//
// open the file to be the new console, push the current console
// pointer into the stack
//
bool8 Console::open(const SysString& filename_a, MODE mode_a) {
  
  // open the new console
  //
  File new_cons;
  if (!new_cons.open(filename_a, mode_a)) {  
    return Error::handle(name(), L"open", Error::IO, __FILE__, __LINE__);
  }
  
  if (!new_cons.isWritable()) {
    return Error::handle(name(), L"open", Error::IO, __FILE__, __LINE__);
  }

  // set the new console's line wrap
  //
  new_cons.setLineWrap(DEF_LINE_WRAP);
  
  // push the current console onto the stack
  //
  if (!push(cons_d)) {
    return Error::handle(name(), L"open", Error::IO, __FILE__, __LINE__);
  }

  // start using the new console, then exit
  //
  return cons_d.swap(new_cons);
}

// method: open
//
// arguments:
//  STREAM stream: (input) file stream
//
// return: a bool8 value indicating status
//
// this is stream open command
//
bool8 Console::open(STREAM stream_a) {

  // open the new console
  //
  File new_cons(stream_a);

  if (!new_cons.isWritable()) {
    return Error::handle(name(), L"open", Error::IO, __FILE__, __LINE__);
  }
  
  // set the new console's line wrap
  //
  new_cons.setLineWrap(DEF_LINE_WRAP);

  // push the current console onto the stack
  //
  if (!push(cons_d)) {
    return Error::handle(name(), L"open", Error::IO, __FILE__, __LINE__);
  }
  
  // start using the new console, then exit
  //
  return cons_d.swap(new_cons);
}

// method: close
//
// arguments: none
//
// return: a bool8 value indicating status
//
// close the file
//
bool8 Console::close() {

  // local variables
  //
  File top;
  File backup;
  
  // pop the stack
  //
  if (!pop(top)) {
    return Error::handle(name(), L"close", Error::IO, __FILE__, __LINE__);
  }
  
  // save cons_d while we close backup
  //
  if (!backup.swap(cons_d)) {
    return Error::handle(name(), L"close", Error::IO, __FILE__, __LINE__);
  }
  
  // assign the new pointer
  //
  if (!cons_d.swap(top)) {
    return Error::handle(name(), L"close", Error::IO, __FILE__, __LINE__);
  }
  
  // close the old console safely
  //
  if (!backup.close()) {
    return Error::handle(name(), L"close", Error::IO, __FILE__, __LINE__);
  }
  
  // exit gracefully
  //
  return true;
}
