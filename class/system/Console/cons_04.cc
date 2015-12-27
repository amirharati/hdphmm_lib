// file: $isip/class/system/Console/cons_04.cc
// version: $Id: cons_04.cc 6630 2001-04-09 22:38:24Z duncan $
//

// isip include files
//
#include "Console.h"
#include <SysString.h>

// method: push
//
// arguments:
//  File& arg: (input) file pointer to use for console output
//
// return: a bool8 value indicating status
//
// push a new file pointer to be the top of the stack
//
bool8 Console::push(File& arg_a) {

  // check the argument
  //
  if (!arg_a.isWritable()) {
    return Error::handle(name(), L"push", Error::ARG, __FILE__, __LINE__);
  }
  
  // check the size of the stack, increase if necessary
  //
  if ((size_d + 1) >= stack_size_d) {
    return Error::handle(name(), L"push", ERR_OPENMAX, __FILE__, __LINE__);
  }
  
  // assign arg to be at the top of the stack (via swap)
  //
  stack_d[size_d].swap(arg_a);
  size_d++;

  // exit gracefully
  //
  return true;
}

// method: pop
//
// arguments:
//  File& cur: (output) the popped item
//
// return: a bool8 value indicating status
//
// pop the stack
//
bool8 Console::pop(File& cur_a) {

  // make sure there is console in the stack
  //
  if (size_d <= 0) {
    return Error::handle(name(), L"pop", Error::STACK_EXCEEDED,
			 __FILE__, __LINE__);
  }
  
  // make sure cons_d is clear
  //
  if (cur_a.isOpen()) {
    return Error::handle(name(), L"pop", File::ERR_NOTCLS, __FILE__, __LINE__);
  }
  
  // decrement stack pointer
  //
  size_d--;

  // assign cons_d to the current top of stack
  //
  cur_a.swap(stack_d[size_d]);

  // exit gracefully
  //
  return true;
}

// method: closeStack
//
// arguments: none
//  
// return: a bool8 value indicating status
//
// this is a hierarchical close method, which closes all open consoles
// (except the top level stdout).
//
bool8 Console::closeStack() {

  bool8 status = true;
  
  // close every console on the stack (leaving open the top level
  // default stdout as cons_d)
  //
  while (size_d > 0) {
    status &= close();
  }
  
  // exit gracefully
  //
  return status;
}

// method: put
//
// arguments:
//  const unichar* str: (input) string to output
//  
// return: a bool8 value indicating status
//
// print a message to the console
//
bool8 Console::put(const unichar* str_a) {

  SysString temp(str_a);
  
  // call the master function
  //
  return put(temp);
}

// method: put
//
// arguments:
//  const SysString& str: (input) string to output
//  
// return: a bool8 value indicating status
//
// print a message to the console
//
bool8 Console::put(const SysString& str_a) {

  // make sure the line wrapping has been set
  //
  if ((size_d == 0) && (!initialized_wrap_d)) {
    cons_d.setLineWrap(DEF_LINE_WRAP);
    initialized_wrap_d = true;
  }

  bool8 added_newline = false;
  
  // make sure the string has a newline
  //
  if (str_a(str_a.length()-1) != L'\n') {
    const_cast< SysString& >(str_a).concat(L"\n");
    added_newline = true;
  }

  // tell the current file pointer to print
  //
  cons_d.put(str_a);

  // flush the output
  //
  cons_d.flush();

  // strip the newline if we added it
  //
  if (added_newline) {
    const_cast< SysString& >(str_a).trimRight(L"\n");
  }
  
  // exit gracefully
  //
  return true;
}

// method: putNoWrap
//
// arguments:
//  const unichar* str: (input) string to output
//  
// return: a bool8 value indicating status
//
// print a message to the console
//
bool8 Console::putNoWrap(const unichar* str_a) {

  SysString temp(str_a);
  
  // call the master function
  //
  return put(temp);
}

// method: putNoWrap
//
// arguments:
//  const SysString& str: (input) string to output
//  
// return: a bool8 value indicating status
//
// print a message to the console
//
bool8 Console::putNoWrap(const SysString& str_a) {

  // store and disable the current line wrap setting
  //
  int32 len = getLineWrap();
  setLineWrap(File::NO_WRAP);

  // call the master put method
  //
  bool8 status = put(str_a);

  // restore the setting
  //
  setLineWrap(len);

  // exit gracefully
  //
  return status;
}

// method: broadcast
//
// arguments:
//  const unichar* str: (input) string to output
//  
// return: a bool8 value indicating status
//
// this is a hierarchical message method, printing a message to all
// consoles.
//
bool8 Console::broadcast(const unichar* str_a) {

  SysString temp(str_a);
  
  // call the master function
  //
  return broadcast(temp);
}

// method: broadcast
//
// arguments:
//  const SysString& str: (input) string to output
//  
// return: a bool8 value indicating status
//
// this is a hierarchical message method, printing a message to all
// consoles.
//
bool8 Console::broadcast(const SysString& str_a) {

  // make sure the string has a newline
  //
  if (str_a(str_a.length()-1) != L'\n') {
    const_cast< SysString& >(str_a).concat(L"\n");
  }
  
  // tell the current file pointer to print
  //
  cons_d.put(str_a);
  
  // make sure that the line wrap has been set for the default console
  //
  if ((size_d > 0) && !initialized_wrap_d) {
    stack_d[size_d - 1].setLineWrap(DEF_LINE_WRAP);
    initialized_wrap_d = true;
  }
  
  // tell each console on the stack to print
  //
  for (int32 i = size_d - 1; i >= 0; i--) {
    stack_d[i].put(str_a);
  }
  
  // exit gracefully
  //
  return true;
}
