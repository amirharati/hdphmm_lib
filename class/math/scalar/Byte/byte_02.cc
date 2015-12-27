// file: $isip/class/math/scalar/Byte/byte_02.cc
// version: $Id: byte_02.cc 10640 2007-01-27 02:36:04Z tm334 $
//

// isip include files
//
#include "Byte.h"
#include <Console.h>

// method: diagnose
//
// arguments:
//  Integral::DEBUG level: (input) debug level for diagnostics
//
// return: a boolean value indicating status
//
bool8 Byte::diagnose(Integral::DEBUG level_a) {

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
  MScalar<byte8, byte8>::diagnose(level_a);

  Byte val_0;
  Byte val_1;
  Byte val_2;

  // test operator %
  //
  val_0.assign((byte8)8);
  val_1.assign((byte8)3);
  val_2 = val_0 % val_1;
  if (val_2 != (byte8)2.0) {
    return Error::handle(name(), L"operator%",
		   Error::TEST, __FILE__, __LINE__);
  }

  // test operator %=
  //
  val_0 %= (byte8)10;
  if (!val_0.almostEqual((byte8)8)) {
    val_0.debug(L"val_0");
    return Error::handle(name(), L"operator%=",
	   Error::TEST, __FILE__, __LINE__);
  }

  // test mod
  //
  val_0.assign((byte8)8);
  val_1.assign((byte8)3);
  val_2.mod(val_0, val_1);
  if (val_2 != (byte8)2) {
    return Error::handle(name(), L"mod", Error::TEST, __FILE__, __LINE__);
  }

  // unless the type is floating point, test bitwise methods
  //
  if (val_0.band(6, 2) != 2) {
    return Error::handle(name(), L"band", Error::TEST, __FILE__, __LINE__);
  }
    
  if (val_0.bor(6, 2) != 6) {
    return Error::handle(name(), L"bor", Error::TEST, __FILE__, __LINE__);
  }
    
  if (val_0.bxor(6, 2) != 4) {
    return Error::handle(name(), L"bxor", Error::TEST, __FILE__, __LINE__);
  }
    
  if (val_0.brs(6, 2) != 1) {
    return Error::handle(name(), L"brs", Error::TEST, __FILE__, __LINE__);
  }
    
  if (val_0.bls(6, 2) != 24) {
    return Error::handle(name(), L"bls", Error::TEST, __FILE__, __LINE__);
  }
    
  // this is tricky with different lengths; constrain to 8 bits
  //
  if (((byte8)val_0.bcmpl((byte8)6) & (byte8)0xFF) != (byte8)0xF9) {
    return Error::handle(name(), L"bcmpl", Error::TEST, __FILE__, __LINE__);
  }

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
    Byte tmp;
    tmp.debug(L"debug");
  }
  
  // test constructors
  //
  Byte val0;

  // test assign method
  //
  val0.assign((byte8)10);
 
  Byte val1(val0);

  if ((val0.value_d != 10) || (val0 != val1)) {
    return Error::handle(name(), L"assign", Error::TEST, __FILE__, __LINE__);
  }
  
  // increment val1 so they have different values
  //
  val1.value_d++;

  // test operator=
  //
  Byte val4;
  val4 = (byte8)20;

  if (val4.value_d != 20) {
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
  Byte val2;
  Byte val3;

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
  Byte val5;
  val5.assign((byte8)30); 
  Byte val6(val5);

  if (!val5.eq(val6)) {
    return Error::handle(name(), L"eq", Error::TEST, __FILE__, __LINE__);
  }

  // test assign method
  //
  val3.assign(val5);
  if (!val5.eq(val3)) {
    return Error::handle(name(), L"eq", Error::TEST, __FILE__, __LINE__);
  }

  // test memory allocation methods
  //
  Byte* ptr;
  Byte::setGrowSize((int32)731);
  
  for (int32 j = 0; j <= 1000; j++) {

    // test the new and delete operators
    //
    ptr = new Byte();
    ptr->assign((byte8)4);
    delete ptr;

    // test the new[] and delete[] operators
    //    
    ptr = new Byte[100];
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
