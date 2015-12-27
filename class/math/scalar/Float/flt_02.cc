// file: $isip/class/math/scalar/Float/flt_02.cc
// version: $Id: flt_02.cc 10636 2007-01-26 22:18:09Z tm334 $
//

// isip include files
//
#include <Console.h>
#include "Float.h"

// method: diagnose
//
// arguments:
//  Integral::DEBUG level: (input) debug level for diagnostics
//
// return: a bool8 value indicating status
//
bool8 Float::diagnose(Integral::DEBUG level_a) {

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
  // 1. template diagnose method
  //
  //---------------------------------------------------------------------

  // set indentation
  //
  if (level_a > Integral::NONE) {
    Console::put(L"testing template diagnose method...\n");
    Console::increaseIndention();
  }
  
  // call the template diagnose method
  //
  MScalar<float32, float32>::diagnose(level_a);

  // reset indentation
  //
  if (level_a > Integral::NONE) {
    Console::decreaseIndention();
  }

  //---------------------------------------------------------------------
  //
  // 2. required public methods
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
    Float tmp;
    tmp.debug(L"debug");
  }
    
  // test constructors
  //
  Float val0;

  // test assign method
  //  
  val0.assign((float32)10);

  Float val1;  
  val1.assign(val0);

  if ((val0.value_d != 10) || (val0 != val1)) {
    return Error::handle(name(), L"assign", Error::TEST, __FILE__, __LINE__);
  }

  // increment val1 so they have different values
  //
  val1.value_d++;

  // test operator=
  //
  Float val4;
  val4 = (float32)31;

  if (val4.value_d != 31) {
    return Error::handle(name(), L"operator=", Error::TEST,
			 __FILE__, __LINE__);
  }
    
  // test the i/o methods
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
  val0 = (float32)3.1;
  val1 = (float32)6.2;
  
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
  Float val2;
  Float val3;

  if (!val2.read(tmp_file0, (int32)0) || (!val2.almostEqual(val0))) {
    return Error::handle(name(), L"read", Error::TEST, __FILE__, __LINE__);
  }

  val2 = 0;
  
  if (!val2.read(tmp_file1, (int32)0) || (!val2.almostEqual(val0))) {
    return Error::handle(name(), L"read", Error::TEST, __FILE__, __LINE__);
  }

  if (!val3.read(tmp_file0, (int32)1) || (!val3.almostEqual(val1))) {
    return Error::handle(name(), L"read", Error::TEST, __FILE__, __LINE__);
  }

  val3 = 0;
  
  if (!val3.read(tmp_file1, (int32)1) || (!val3.almostEqual(val1))) {
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
  Float val5;
  val5.assign((float32)30); 
  Float val6(val5);

  if (!val5.eq(val6)) {
    return Error::handle(name(), L"eq", Error::TEST, __FILE__, __LINE__);
  }
    
  // test memory allocation methods
  //  
  Float* ptr;
  Float::setGrowSize((int32)731);

  for (int32 j = 0; j <= 1000; j++) {

    // test the new and delete operators
    //   
    ptr = new Float();
    ptr->assign((float32)4);
    delete ptr;

    // test the new[] and delete[] operators
    //    
    ptr = new Float[100];
    delete [] ptr;

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
