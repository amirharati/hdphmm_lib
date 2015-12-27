// file: $isip/class/math/scalar/ComplexLong/clong_02.cc
// version: $Id: clong_02.cc 7408 2001-10-14 04:26:05Z bahety $
//

// isip include files
//
#include <Console.h>
#include "ComplexLong.h"

// method: diagnose
//
// arguments:
//  Integral::DEBUG level: (input) debug level for diagnostics
//
// return: a bool8 value indicating status
//
bool8 ComplexLong::diagnose(Integral::DEBUG level_a) {

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
  MComplexScalar<int32, int32>::diagnose(level_a);
  
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
    ComplexLong tmp;
    tmp.debug(L"debug");
  }
    
  // test constructors
  //
  ComplexLong val00(2, -5);
  ComplexLong val01(L"2 - 5j");
  
  if ((val00 != complexlong(2, -5)) || (val00 != val01)) {
    return Error::handle(name(), L"constr", Error::TEST, __FILE__, __LINE__);
  }

  // test assign method
  //  
  ComplexLong val0;
  val0.assign(complexlong(10, 11));

  ComplexLong val1;  
  val1.assign(val0);

  if ((val0.value_d != complexlong(10, 11)) || (val0 != val1)) {
    return Error::handle(name(), L"assign", Error::TEST, __FILE__, __LINE__);
  }

  // test operator=
  //
  ComplexLong val4(L"3 - 4j");

  // test methods specific for complex numbers
  //
  if (val4.value_d != complexlong(3, -4)) {
    return Error::handle(name(), L"operator=", Error::TEST,
			 __FILE__, __LINE__);
  }

  if (val4.real() != 3) {
    return Error::handle(name(), L"real", Error::TEST, __FILE__, __LINE__);
  }

  if (val4.imag() != -4) {
    return Error::handle(name(), L"imag", Error::TEST, __FILE__, __LINE__);
  }

  if (val4.mag() != 5) {
    return Error::handle(name(), L"mag", Error::TEST, __FILE__, __LINE__);
  }

  if (!Integral::almostEqual(val4.angle(), -0.9273)) {
    return Error::handle(name(), L"angle", Error::TEST, __FILE__, __LINE__);
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
  val0 = (int32)3;
  val1 = (int32)6;
  
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
  ComplexLong val2;
  ComplexLong val3;

  if (!val2.read(tmp_file0, (int32)0) || (!val2.almostEqual(val0))) {
    return Error::handle(name(), L"read", Error::TEST, __FILE__, __LINE__);
  }

  val2 = (int32)0;
  
  if (!val2.read(tmp_file1, (int32)0) || (!val2.almostEqual(val0))) {
    return Error::handle(name(), L"read", Error::TEST, __FILE__, __LINE__);
  }

  if (!val3.read(tmp_file0, (int32)1) || (!val3.almostEqual(val1))) {
    return Error::handle(name(), L"read", Error::TEST, __FILE__, __LINE__);
  }

  val3 = (int32)0;
  
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
  ComplexLong val5;
  val5.assign((int32)30); 
  ComplexLong val6(val5);

  if (!val5.eq(val6)) {
    return Error::handle(name(), L"eq", Error::TEST, __FILE__, __LINE__);
  }
    
  // test memory allocation methods
  //  
  ComplexLong* ptr;
  ComplexLong::setGrowSize((int32)731);

  for (int32 j = 0; j <= 1000; j++) {

    // test the new and delete operators
    //   
    ptr = new ComplexLong();
    ptr->assign((int32)4);
    delete ptr;

    // test the new[] and delete[] operators
    //    
    ptr = new ComplexLong[100];
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
