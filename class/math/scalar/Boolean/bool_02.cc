// file: $isip/class/math/scalar/Boolean/bool_02.cc
// version: $Id: bool_02.cc 5660 2000-11-22 17:24:28Z picone $
//

// isip include files
//
#include <Console.h>
#include <Long.h>
#include "Boolean.h"

// method: diagnose
//
// arguments:
//  Integral::DEBUG level: (input) debug level for diagnostics
//
// return: a bool8 value indicating status
//
bool8 Boolean::diagnose(Integral::DEBUG level_a) {

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
    Boolean tmp;
    tmp.debug(L"debug");
  }

  // test constructors
  //
  Boolean val0;

  // test assign method
  //
  val0.assign(true);
   
  Boolean val1(val0);

  if (level_a > Integral::ALL) {
    val1.setDebug(Integral::NONE);
    val1.debug(L"val1");
  }

  if (!val0.value_d || (!val0.eq(val1))) {
    return Error::handle(name(), L"assign", Error::TEST, __FILE__, __LINE__);
  }

  val1 = !val0;

  Long mem_size = val0.memSize();
  
  if (level_a > Integral::ALL) {
    mem_size.debug(L"mem_size of Boolean");
  }

  // test operator=
  //
  Boolean val4;
  val4 = true;

  if (!val4.value_d) {
    return Error::handle(name(), L"operator=", Error::TEST,
			 __FILE__, __LINE__);
  }
    
  // test i/o methods
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
  Boolean val2;
  Boolean val3;

  if (!val2.read(tmp_file0, (int32)0) ||
      (!Integral::almostEqual(val2, val0))) {
    return Error::handle(name(), L"read", Error::TEST, __FILE__, __LINE__);
  }

  val2 = 0;
  
  if (!val2.read(tmp_file1, (int32)0) ||
      (!Integral::almostEqual(val2, val0))) {
    return Error::handle(name(), L"read", Error::TEST, __FILE__, __LINE__);
  }

  if (!val3.read(tmp_file0, (int32)1) ||
      (!Integral::almostEqual(val3, val1))) {
    return Error::handle(name(), L"read", Error::TEST, __FILE__, __LINE__);
  }

  val3 = 0;
  
  if (!val3.read(tmp_file1, (int32)1) ||
      (!Integral::almostEqual(val3, val1))) {
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
  Boolean val5;
  val5.assign(true);
  Boolean val6(val5);
  
  if (!val5.eq(val6)) {
    return Error::handle(name(), L"eq", Error::TEST, __FILE__, __LINE__);
  }  
  
  // test memory management methods
  //
  Boolean* ptr;

  Boolean::setGrowSize((int32)731);
  
  for (int32 j = 0; j <= 1000; j++) {

    // test the new and delete operators
    //
    ptr = new Boolean();
    ptr->assign((bool8)true);
    delete ptr;

    // test the new[] and delete[] operators
    //
    ptr = new Boolean[100];
    delete [] ptr;
  }

  // reset indentation
  //
  if (level_a > Integral::NONE) {
    Console::decreaseIndention();
  }

  //---------------------------------------------------------------------
  //
  // 2. class-specific public methods
  //
  //---------------------------------------------------------------------

  // set indentation
  //
  if (level_a > Integral::NONE) {
    Console::put(L"testing class-specific public methods...\n");
    Console::increaseIndention(); 
  }

  // test assign methods
  //
  String str;
  str.assign(val0);
  val1.assign(str);
  if (val1 != val0) {
    return Error::handle(name(), L"assign", Error::TEST, __FILE__, __LINE__);
  }

  // test eq method
  //
  Boolean val7;
  val7.assign(true);
  Boolean val8(val7);
  
  if (!Integral::almostEqual(val7, val8)) {
    return Error::handle(name(), L"almostEqual", Error::TEST,
			 __FILE__, __LINE__);
  }
  
  // test operator=
  //
  val0 = !val0;

  // test get method
  //
  val0.get(str);
  val1.assign(str);
  if (val1 != val0) {
    return Error::handle(name(), L"assign", Error::TEST, __FILE__, __LINE__);
  }

  val0 = !val1;
  
  // test the random method
  //
  Boolean rand;
  int32 N = 1000;
  float64 avg = 0.0;

  for (int32 i = 0; i < N; i++) {
    avg += rand.rand();
  }
  avg /= (float64)N;

  if (!Integral::almostEqual(avg, 0.5, 1.0)) {
    return Error::handle(name(), L"rand", Error::TEST, __FILE__, __LINE__);
  }

  // reset indentation
  //
  if (level_a > Integral::NONE) {
    Console::decreaseIndention();
  }
  
  //---------------------------------------------------------------------
  //
  // 3. print completion message
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
