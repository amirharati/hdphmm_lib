// file: $isip/class/math/scalar/ComplexDouble/cdbl_02.cc
// version: $Id: cdbl_02.cc 7408 2001-10-14 04:26:05Z bahety $
//

// isip include files
//
#include <Console.h>
#include "ComplexDouble.h"

// method: diagnose
//
// arguments:
//  Integral::DEBUG level: (input) debug level for diagnostics
//
// return: a bool8 value indicating status
//
bool8 ComplexDouble::diagnose(Integral::DEBUG level_a) {

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
  MComplexScalar<float64, float64>::diagnose(level_a);
  
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
    ComplexDouble tmp;
    tmp.debug(L"debug");
  }
  
  // test constructors
  //
  ComplexDouble val00(2.5, -5.7);
  ComplexDouble val01(L"2.5 - 5.7j");
  
  if ((val00 != complexdouble(2.5, -5.7)) || (val00 != val01)) {
    return Error::handle(name(), L"constr", Error::TEST, __FILE__, __LINE__);
  }

  // test assign method
  //  
  ComplexDouble val0;
  val0.assign(complexdouble(-10.12, -14.489));

  ComplexDouble val1;
  val1.assign(val0);

  if ((val0.value_d != complexdouble(-10.12, -14.489)) || (val0 != val1)) {
    return Error::handle(name(), L"assign", Error::TEST, __FILE__, __LINE__);
  }

  // test operator=
  //
  ComplexDouble val4(L"0.3 - 0.4j");

  if (val4.value_d != complexdouble(0.3, -0.4)) {
    return Error::handle(name(), L"operator=", Error::TEST,
			 __FILE__, __LINE__);
  }

  // test methods specific for complex numbers
  //
  if (!Integral::almostEqual(val4.real(), 0.3)) {
    return Error::handle(name(), L"real", Error::TEST, __FILE__, __LINE__);
  }

  if (!Integral::almostEqual(val4.imag(), -0.4)) {
    return Error::handle(name(), L"imag", Error::TEST, __FILE__, __LINE__);
  }

  if (!Integral::almostEqual(val4.mag(), (float64)0.5)) {
    val4.debug(L"val4");
    return Error::handle(name(), L"mag", Error::TEST, __FILE__, __LINE__);
  }

  if (!Integral::almostEqual(val4.angle(), -0.9273)) {
    return Error::handle(name(), L"angle", Error::TEST, __FILE__, __LINE__);
  }

  val4.conjugate();
  if (val4.almostEqual(complexdouble(0.3, 0.4))) {
    return Error::handle(name(), L"conjugate",
			 Error::TEST, __FILE__, __LINE__);
  }

  val4 = L"0.3 - 0.4j";
  if (val4.sign(val4) != Integral::POSITIVE) {
    return Error::handle(name(), L"sign", Error::TEST, __FILE__, __LINE__);
  }

  val4 = L"-0.3 + 0.4j";
  if (val4.sign(val4) != Integral::NEGATIVE) {
    return Error::handle(name(), L"sign", Error::TEST, __FILE__, __LINE__);
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
  val0 = complexdouble(3.1, -5.43);
  val1 = complexdouble(-6.2, 7.28);
  
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
  ComplexDouble val2;
  ComplexDouble val3;

  if (!val2.read(tmp_file0, (int32)0) || (!val2.almostEqual(val0))) {
    return Error::handle(name(), L"read", Error::TEST, __FILE__, __LINE__);
  }

  val2 = (float64)0;
  
  if (!val2.read(tmp_file1, (int32)0) || (!val2.almostEqual(val0))) {
    return Error::handle(name(), L"read", Error::TEST, __FILE__, __LINE__);
  }

  if (!val3.read(tmp_file0, (int32)1) || (!val3.almostEqual(val1))) {
    return Error::handle(name(), L"read", Error::TEST, __FILE__, __LINE__);
  }

  val3 = (float64)0;
  
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
  ComplexDouble val5;
  val5.assign(complexdouble(30.34, 45.67)); 
  ComplexDouble val6(val5);

  if (!val5.eq(val6)) {
    return Error::handle(name(), L"eq", Error::TEST, __FILE__, __LINE__);
  }
    
  // test memory allocation methods
  //  
  ComplexDouble* ptr;
  ComplexDouble::setGrowSize((int32)731);

  for (int32 j = 0; j <= 1000; j++) {

    // test the new and delete operators
    //   
    ptr = new ComplexDouble();
    ptr->assign((float64)4.2);
    delete ptr;

    // test the new[] and delete[] operators
    //    
    ptr = new ComplexDouble[100];
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
