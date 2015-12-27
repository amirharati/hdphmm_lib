// file: $isip/class/math/scalar/String/str_02.cc
// version: $Id: str_02.cc 5660 2000-11-22 17:24:28Z picone $
//

// isip include files
//
#include "String.h"
#include <Console.h>
#include <Long.h>
#include <Double.h>
#include <Float.h>
#include <Llong.h>
#include <Byte.h>
#include <Ullong.h>
#include <Ulong.h>
#include <Short.h>
#include <Ushort.h>
#include <Boolean.h>

// method: diagnose
//
// arguments:
//  Integral::DEBUG level: (input) debug level for diagnostics
//
// return: a bool8 value indicating status
//
bool8 String::diagnose(Integral::DEBUG level_a) {

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
    String tmp;
    tmp.debug(L"debug");
  }

  // test constructors
  //
  String val0((unichar*)L"hello my name is");
  String val1(val0);
  
  if (!val1.eq(val0)) {
    return Error::handle(name(), L"copy constructor", Error::TEST,
			 __FILE__, __LINE__);
  }
  
  val1.assign(L"second testing string");

  // test conversions
  //
  String num0;
  String num1;
  String num2;
  String num3;
  
  // test conversions with Byte
  //
  Byte scalar_byte;
  scalar_byte.assign((byte8)43);
  num0.assign(scalar_byte);
  num1.assign((byte8)43);
  scalar_byte.get(num2);
  num3.assign(L"43");
  
  if (num3.ne(num0) || num3.ne(num1) || num3.ne(num2)) {
    return Error::handle(name(), L"assign(Byte)", Error::TEST,
			 __FILE__, __LINE__);
  }

  // test conversions with Boolean
  //
  Boolean scalar_boolean;
  scalar_boolean.assign((bool8)true);
  num0.assign(scalar_boolean);
  num1.assign((bool8)true);
  scalar_boolean.get(num2);
  num3.assign(L"true");
  
  if (num3.ne(num0) || num3.ne(num1) || num3.ne(num2)) {
    return Error::handle(name(), L"assign(Boolean)", Error::TEST,
			 __FILE__, __LINE__);
  }

  // test conversions with Double
  //
  Double scalar_double;
  scalar_double.assign((float64)43);
  num0.assign(scalar_double);
  num1.assign((float64)43);
  scalar_double.get(num2);
  
  if (num2.ne(num0) || num2.ne(num1)) {
    return Error::handle(name(), L"assign(Double)", Error::TEST,
			 __FILE__, __LINE__);
  }

  // test conversions with Float
  //
  Float scalar_float;
  scalar_float.assign((float32)43);
  num0.assign(scalar_float);
  num1.assign((float32)43);
  scalar_float.get(num2);
  
  if (num2.ne(num0) || num2.ne(num1)) {
    return Error::handle(name(), L"assign(Float)", Error::TEST,
			 __FILE__, __LINE__);
  }

  // test conversions with Llong
  //
  Llong scalar_llong;
  scalar_llong.assign((int64)43);
  num0.assign(scalar_llong);
  num1.assign((int64)43);
  scalar_llong.get(num2);
  num3.assign(L"43");
  
  if (num3.ne(num0) || num3.ne(num1) || num3.ne(num2)) {
    return Error::handle(name(), L"assign(Llong)", Error::TEST,
			 __FILE__, __LINE__);
  }

  // test conversions with Long
  //
  Long scalar_long;
  scalar_long.assign((int32)43);
  num0.assign(scalar_long);
  num1.assign((int32)43);
  scalar_long.get(num2);
  num3.assign(L"43");
  
  if (num3.ne(num0) || num3.ne(num1) || num3.ne(num2)) {
    return Error::handle(name(), L"assign(Long)", Error::TEST,
			 __FILE__, __LINE__);
  }

  // test conversions with Short
  //
  Short scalar_short;
  scalar_short.assign((int16)43);
  num0.assign(scalar_short);
  num1.assign((int16)43);
  scalar_short.get(num2);
  num3.assign(L"43");
  
  if (num3.ne(num0) || num3.ne(num1) || num3.ne(num2)) {
    return Error::handle(name(), L"assign(Short)", Error::TEST,
			 __FILE__, __LINE__);
  }

  // test conversions with Ullong
  //
  Ullong scalar_ullong;
  scalar_ullong.assign((uint64)43);
  num0.assign(scalar_ullong);
  num1.assign((uint64)43);
  scalar_ullong.get(num2);
  num3.assign(L"43");
  
  if (num3.ne(num0) || num3.ne(num1) || num3.ne(num2)) {
    return Error::handle(name(), L"assign(Ullong)", Error::TEST,
			 __FILE__, __LINE__);
  }

  // test conversions with Ulong
  //
  Ulong scalar_ulong;
  scalar_ulong.assign((uint32)43);
  num0.assign(scalar_ulong);
  num1.assign((uint32)43);
  scalar_ulong.get(num2);
  num3.assign(L"43");
  
  if (num3.ne(num0) || num3.ne(num1) || num3.ne(num2)) {
    return Error::handle(name(), L"assign(Ulong)", Error::TEST,
			 __FILE__, __LINE__);
  }

  // test conversions with Ushort
  //
  Ushort scalar_ushort;
  scalar_ushort.assign((uint16)43);
  num0.assign(scalar_ushort);
  num1.assign((uint16)43);
  scalar_ushort.get(num2);
  num3.assign(L"43");
  
  if (num3.ne(num0) || num3.ne(num1) || num3.ne(num2)) {
    return Error::handle(name(), L"assign(Ushort)", Error::TEST,
			 __FILE__, __LINE__);
  }

  // test operator=
  //
  String val4;
  val4 = (unichar*)L"testing";

  if (!val4.eq((unichar*)L"testing")) {
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
  String val2;
  String val3;

  if (!val2.read(tmp_file0, (int32)0) || (val2.ne(val0))) {
    if (level_a > Integral::ALL) {
      val2.debug(L"val2: read from text");
    }
    return Error::handle(name(), L"read", Error::TEST, __FILE__, __LINE__);
  }

  val2.clear();
  
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

  val3.clear();
  
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
  
  // make some random strings
  //
  val0.rand(5, 20);
  val1.rand(5, 20);
  val2.rand(5, 20);
  val3.rand(5, 20);

  if (level_a > Integral::ALL) {
    val0.debug(L"val0 rand");
    val1.debug(L"val1 rand");
    val2.debug(L"val2 rand");
    val3.debug(L"val3 rand");
  }

  // test eq method
  //
  String val5;
  val5.assign(L"another test"); 
  String val6(val5);

  if (!val5.eq(val6)) {
    return Error::handle(name(), L"eq", Error::TEST, __FILE__, __LINE__);
  }
  
  // test memory allocation methods
  //
  String* ptr;
  String::setGrowSize((int32)731);
  
  for (int32 j = 0; j <= 1000; j++) {

    // test the new and delete operators
    //    
    ptr = new String();
    ptr->assign(L"hello");
    delete ptr;

    // test the new[] and delete[] operators
    //   
    ptr = new String[100];
    delete [] ptr;
  }

  // test the hash function
  //
  String foo(L"Rick");
  int32 hash = foo.hash(128);
  if (hash != 70) {
    return Error::handle(name(), L"hash", Error::TEST, __FILE__, __LINE__);
  }
  
  foo.assign(L"Ricky");
  hash = foo.hash(128);
  if (hash != 66) {
    return Error::handle(name(), L"hash", Error::TEST, __FILE__, __LINE__);
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
