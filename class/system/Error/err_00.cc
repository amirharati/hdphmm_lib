// file: $isip/class/io/Error/err_00.cc
// version: $Id: err_00.cc 6532 2001-03-26 16:59:11Z duncan $
//
// note:
// (1) AH (07/27/2010): I have  deleted  volatile   qualifier from exit definitin
//                      to fix a warning in gcc-4.4.4 with  -Wextra
//
// isip include files
//
#include "Error.h"
#include <SysString.h>
#include <Console.h>

//---------------------------------------------------------------
// these methods have to be in the same file so they can use the same
// static exiting pointer.
//---------------------------------------------------------------
//

// flag to control if we are exiting or not. this way our normally
// careful destructors will not call the error handler, which could
// cause infinite loops.
//
static bool8 is_exiting_d = false;

// method: exit
//
// arguments: none
//
// return: none
//
void Error::exit() {

  // set the exiting flag
  //
  is_exiting_d = true;
  
  // call the Sof close method (dynamically linked). this will go up
  // in the hierarchy and close all open Sof files (if any exist).
  //
  closeSof();

  // clean up all temporary files
  //
  
  File::cleanTemps();

  // close all the consoles
  //
  Console::closeStack();
  
  // exit very ungracefully
  //
  ::exit(Integral::SYS_RETURN_ERROR);
}

// method: isExiting
//
// arguments: none
//
// return: a bool8 value indicating status
//
// this method gets the status if we are in the middle of exiting.
// in some cases, modules behave differently if we are exiting. once
// the program is dying, you don't want to keep calling the error
// handler. this method is not inlined because it needs to use the
// static exiting pointer
//
bool8 Error::isExiting() {

  // return the exiting flag
  //
  return is_exiting_d;
}

//-----------------------------------------------------------------------------
//
// we define non-integral constants in the default constructor
//      
//-----------------------------------------------------------------------------

// constants: class name
//

const SysString Error::CLASS_NAME(L"Error");

// constants: format and components of error messages
//
const SysString Error::CODE_FMT(L"%8.8ld");
const SysString Error::DEF_EXTRAS(L"");
const SysString Error::ERROR_MESSAGE_00(L":");
const SysString Error::ERROR_MESSAGE_01(L": Error in ");
const SysString Error::ERROR_MESSAGE_02(L"Error in ");
const SysString Error::ERROR_MESSAGE_03(L"::");
const SysString Error::ERROR_MESSAGE_04(L" [");
const SysString Error::ERROR_MESSAGE_05(L"] ");
const SysString Error::ERROR_MESSAGE_99(L"\n");

// constants: error messages
//
const SysString Error::UNDEFINED_MESSAGE(L"Undefined error code");

// static instantiations: internal states
//
bool8 Error::initialized_d = false;
Error::EXIT Error::exit_level_d = Error::ERROR;

// static instantiations: debug level
//
Integral::DEBUG Error::debug_level_d = Integral::DETAILED;
