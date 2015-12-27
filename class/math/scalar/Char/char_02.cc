// file: $isip/class/math/scalar/Char/char_02.cc
// version: $Id: char_02.cc 5660 2000-11-22 17:24:28Z picone $
//

// isip include files
//
#include "Char.h"
#include <Console.h>

// method: diagnose
//
// arguments:
//  Integral::DEBUG level: (input) debug level for diagnostics
//
// return: a bool8 value indicating status
//
bool8 Char::diagnose(Integral::DEBUG level_a) {

  //----------------------------------------------------------------------
  //
  // 0. preliminaries
  //
  //----------------------------------------------------------------------

  // output the class name
  //
  if (level_a > Integral::NONE) {
    SysString output(L"diagnosing class ");
    output.concat(CLASS_NAME);
    output.concat(L": ");
    Console::put(output);
    Console::increaseIndention();
  }

  //---------------------------------------------------------------------
  //
  // 1. required public methods
  //
  //---------------------------------------------------------------------

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
    Char tmp;
    tmp.debug(L"debug");
  }

  // test the parent class
  //
  SysChar::diagnose(level_a);
  
  // test constructors
  //
  Char val0;
  val0.assign((unichar)'w');
  Char val1(val0);                           

  if ((val0.value_d != 'w') || (val0.ne(val1))) {
    return Error::handle(name(), L"assign", Error::TEST, __FILE__, __LINE__);
  }

  // testing byte8 assignment constructor
  //
  Char val2((byte8*)"h");
  if (level_a > Integral::ALL) {
    val1.debug(L"val1");
    val2.debug(L"val2");
  }
   
  // assign val1 a different value
  //
  val1.assign((unichar)'y');

  // test operator=
  //
  Char val4;
  val4 = (unichar)'a';

  if (val4.value_d != 'a') {
    return Error::handle(name(), L"operator=", Error::TEST,
			 __FILE__, __LINE__);
  }
  
  // test io methods
  //
  String tmp_filename0;
  Integral::makeTemp(tmp_filename0);
  String tmp_filename1;
  Integral::makeTemp(tmp_filename1);

  // open files in write mode
  //
  Sof tmp_file0;
  tmp_file0.open(tmp_filename0, File::WRITE_ONLY, File::TEXT);
  Sof tmp_file1;
  tmp_file1.open(tmp_filename1, File::WRITE_ONLY, File::BINARY);
  
  // write the values
  //
  val0.write(tmp_file0, (int32)0);
  val0.write(tmp_file1, (int32)0);

  val1.write(tmp_file0, (int32)1);
  val1.write(tmp_file1, (int32)1);

  // close the files
  //
  tmp_file0.close();
  tmp_file1.close();

  // open the files in read mode
  //
  tmp_file0.open(tmp_filename0);
  tmp_file1.open(tmp_filename1);

  // read the values back in
  //
  Char val3;

  if (!val2.read(tmp_file0, (int32)0) || (val2.ne(val0))) {
    if (level_a > Integral::ALL) {
      val2.debug(L"val2: read from text");
    }
    return Error::handle(name(), L"read", Error::TEST, __FILE__, __LINE__);
  }

  val2 = DEF_VALUE;
  
  if (!val2.read(tmp_file1, (int32)0) || (val2.ne(val0))) {
    if (level_a > Integral::ALL) {
      val2.debug(L"val2: read from binary");
    }
    return Error::handle(name(), L"read", Error::TEST, __FILE__, __LINE__);
  }

  if (!val3.read(tmp_file0, (int32)1) || (val3.ne(val1))) {
    if (level_a > Integral::ALL) {
      val3.debug(L"val3: read from text");
    }
    return Error::handle(name(), L"read", Error::TEST, __FILE__, __LINE__);
  }

  val3 = DEF_VALUE;
  
  if (!val3.read(tmp_file1, (int32)1) || (val3.ne(val1))) {
    if (level_a > Integral::ALL) {
      val3.debug(L"val3: read from binary");
    }
    return Error::handle(name(), L"read", Error::TEST, __FILE__, __LINE__);
  }

  // close and delete the temporary files
  //
  tmp_file0.close();
  tmp_file1.close();
  File::remove(tmp_filename0);
  File::remove(tmp_filename1);

  // test eq method
  //
  Char val5;
  val5.assign((unichar)'x'); 
  Char val6(val5);

  if (!val5.eq(val6)) {
    return Error::handle(name(), L"eq", Error::TEST, __FILE__, __LINE__);
  }
  
  // test memory management methods
  //
  Char* ptr;
  Char::setGrowSize((int32)731);

  for (int32 j = 0; j <= 1000; j++) {

    // test the new and delete operators
    //
    ptr = new Char();
    ptr->assign(L'5');
    delete ptr;

    // test the new[] and delete[] operators
    ptr = new Char[100];
    delete [] ptr;
  }
  
  // reset indentation
  //
  if (level_a > Integral::NONE) {
    Console::decreaseIndention();
  }
  
  //---------------------------------------------------------------------
  //
  // 2. print completion message
  //
  //---------------------------------------------------------------------

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
