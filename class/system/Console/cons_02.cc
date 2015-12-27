// file: $isip/class/system/Console/cons_02.cc
// version: $Id: cons_02.cc 5992 2000-12-18 20:00:09Z duncan $
//

// isip include files
//
#include <SysString.h>
#include "Console.h"

// method: diagnose
//
// arguments:
//  Integral::DEBUG level: (input) debug level for diagnostics
//
// return: a bool8 value indicating status
//
bool8 Console::diagnose(Integral::DEBUG level_a) {

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
    Console::debug(L"debug");
  }
  
  // reset indentation
  //
  if (level_a > Integral::NONE) {
    Console::decreaseIndention();
  }
  
  //---------------------------------------------------------------------------
  //
  // 2. class-specific public methods:
  //     open and close methods
  //
  //---------------------------------------------------------------------------

  // set indentation
  //
  if (level_a > Integral::NONE) {
    Console::put(L"testing class-specific public methods: open and close methods...\n");
    Console::increaseIndention();
  }
  
  // test open methods, the debug message will be output to the files
  // instead of stdout
  //
  SysString out0_name;
  Integral::makeTemp(out0_name);
  Console::open(out0_name, File::WRITE_ONLY);
  Console::debug(L"second try");
   
  SysString out1_name;
  Integral::makeTemp(out1_name);
  Console::open(out1_name, File::WRITE_ONLY);
  Console::debug(L"third try");
  
  // now let's generate a warning
  //
  Error::reset();
  SysString temp;
  SysString in_name;
  Integral::makeTemp(in_name);

  File in;
  in.setOpenRetry(0, File::DEF_OPEN_DELAY);
  in.open(in_name, File::READ_ONLY);
  in.setOpenRetry(File::DEF_OPEN_RETRY, File::DEF_OPEN_DELAY);
  in.close();
  
  // close the top console -- out1_name
  //
  Console::close();
  
  // close the second console -- out0_name
  //
  temp.assign(L"supercalifradjiwatuzik");
  temp.debug(L"in out0, I hope");
  Console::close();
  
  // if you try to pop the Console and have exceeded the stack,
  // a fatal error will occur. since that would prevent the diagnose method
  // from completing, we can't test this directly. if you uncomment the
  // two lines below, you will force this type of error (stack exceeded??).
  //
  // Console::debug(L"about to error off");
  // Console::close();

  // clean up temp files: opening in_name failed, so we don't have to remove it
  //
  File::remove(out0_name);
  File::remove(out1_name);
  
  // reset indentation
  //
  if (level_a > Integral::NONE) {
    Console::decreaseIndention();
  }
  
  //---------------------------------------------------------------------------
  //
  // 2. class-specific public methods:
  //     message display methods
  //
  //---------------------------------------------------------------------------

  // set indentation
  //
  if (level_a > Integral::NONE) {
    Console::put(L"testing class-specific public methods: message display methods...\n");
    Console::increaseIndention();
  }
  
  // test broadcast methods
  //
  if (level_a > Integral::BRIEF) {
    Console::broadcast(L"broadcast to all consoles\n");
  }
  
  // reset indentation
  //
  if (level_a > Integral::NONE) {
    Console::decreaseIndention();
  }
  
  //---------------------------------------------------------------------------
  //
  // 3. class-specific public methods:
  //     formatting methods
  //
  //---------------------------------------------------------------------------

  // set indentation
  //
  if (level_a > Integral::NONE) {
    Console::put(L"testing class-specific public methods: formatting methods...\n");
    Console::increaseIndention();
  }
  
  // test indentation and wrapping
  //
  
  // set the line wrap
  //
  Console::setLineWrap(50);
  if (Console::getLineWrap() != 50) {
    return Error::handle(name(), L"set/getLineWrap", Error::TEST,
			 __FILE__, __LINE__);
  }
  
  // get the current line length
  //
  int32 line_len = Console::getLineLength();
  
  // increase the indention, this should decrease the available line length
  //
  Console::increaseIndention();
  
  if (Console::getLineLength() != (line_len - INDENT_STR.length())) {
    return Error::handle(name(), L"getLineLength", Error::TEST,
			 __FILE__, __LINE__);
  }
  
  // decrease the indention, the available line length should resume
  //
  Console::decreaseIndention();
  
  if (Console::getLineLength() != line_len) {
    return Error::handle(name(), L"getLineLength", Error::TEST,
			 __FILE__, __LINE__);
  }
  
  // restore the default line wrap setting
  //
  Console::setLineWrap(DEF_LINE_WRAP);

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

  // test closeStack method: this is for the Console class only.
  //  it will close all the consoles including stdout,
  //  so it has to be done as the last step of this diagnose method.
  //  other classes will not call this method directly in their
  //  diagnose method.
  //
  closeStack();

  // exit gracefully
  //
  return true;
}
