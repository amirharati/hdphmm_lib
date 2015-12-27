// file: $isip/class/system/Error/err_02.cc
// version: $Id: err_02.cc 4883 2000-09-20 12:58:09Z hamaker $
//

// isip include files
//
#include "Error.h"
#include <SysString.h>
#include <Console.h>

// method: diagnose
//
// arguments:
//  Integral::DEBUG level: (input) debug level for diagnostics
//
// return: a bool8 value indicating status
//
bool8 Error::diagnose(Integral::DEBUG level_a) {

  //---------------------------------------------------------------------------
  //
  // 0. preliminaries
  //
  //---------------------------------------------------------------------------
  
  // output the class name
  //
  if (level_a > Integral::NONE) {
  SysString output(L"diagnosing class ");
    output.concat(CLASS_NAME);
    output.concat(L": ");
    Console::put(output);
    Console::increaseIndention();
  }

  //---------------------------------------------------------------------------
  //
  // 1. required public methods
  //
  //---------------------------------------------------------------------------

  // set indentation
  //
  if (level_a > Integral::NONE) {
    Console::put(L"testing required public methods...\n");
    Console::increaseIndention();
  }
  
  // test the debug methods
  //
  setDebug(debug_level_d);

  if (level_a > Integral::BRIEF) {
    Error::debug(L"debug");
  }
  
  // reset indentation
  //
  if (level_a > Integral::NONE) {
   Console::decreaseIndention();
  }

  //---------------------------------------------------------------------------
  //
  // 2. class-specific public methods:
  //     error handler methods
  //
  //---------------------------------------------------------------------------

  // set indentation
  //
  
  if (level_a > Integral::NONE) {
    Console::put(L"testing class-specific public methods: error handle methods ...\n");
    Console::increaseIndention();
  }

  // all these error messages will get pretty annoying going to
  // stdout, let's push the console to a temp file
  //
  if (level_a > Integral::BRIEF) {
    Console::put(L"read diagnose_error.out for the output");
  }

  SysString diagnose_error_file;
  Integral::makeTemp(diagnose_error_file);
  Console::open(diagnose_error_file, File::WRITE_ONLY);
   
  // use the default level "ERROR"
  //
  reset();
  
  // generate a warning message, since WARNING is greater than ERROR,
  // this will not exit
  //
  handle(Error::name(), L"warning", TEST, __FILE__, __LINE__, WARNING);
  
  // set the mode to never exit, try a regular error
  //
  reset();
  set(NONE);
  
  if (level_a > Integral::BRIEF) {
    Error::debug(L"set exit to none");
  }

  // this still will not exit since we set exit_level_d to NONE
  //
  handle(Error::name(), L"error no exit", TEST, __FILE__, __LINE__);
  
  // do a set without a reset, should have no effect
  //
  set(WARNING);

  // try an undefined error code
  //
  handle(Error::name(), L"error, no exit undef", -54, __FILE__, __LINE__);

  // try a defined error code
  //
  handle(Error::name(), L"error, still no exit", TEST, __FILE__, __LINE__);

  // reset the mode back to full exit
  //
  reset();
  set(WARNING);
  if (level_a > Integral::BRIEF) {
    Error::debug(L"set exit to warning");
  }
  
  // close and delete the file console and resume using stdout
  //
  
  Console::close();
  File::remove(diagnose_error_file);
  
  // reset indentation
  //
  if (level_a > Integral::NONE) {
    Console::decreaseIndention();
  }

  //---------------------------------------------------------------------------
  //
  // 3. class-specific public methods:
  //     exit related methods
  //
  //---------------------------------------------------------------------------

  // set indentation
  //
  if (level_a > Integral::NONE) {
    Console::put(L"testing class-specific public methods: exit related methods ...\n");
    Console::increaseIndention();
  }
  
  // test isExiting
  //
  if (!isExiting()) {

    // this is testing the exit method, it will exit the diagnose
    // after testing, comment this out
    //
    // Error::exit();
  }
  
  // reset indentation
  //
  
  if (level_a > Integral::NONE) {
    Console::decreaseIndention();
  }

  //---------------------------------------------------------------------------
  //
  // 4. print completion message
  //
  //---------------------------------------------------------------------------

  // reset indentation
  //
  if (level_a > Integral::NONE) {
    Console::decreaseIndention();
  }
  
  if (level_a > Integral::NONE) {
    SysString output(L"diagnostics passed for class ");
    output.concat(name());
    output.concat(L"\n");
    Console::put(output);
    }
  // exit gracefully
  //
  return true;
}

