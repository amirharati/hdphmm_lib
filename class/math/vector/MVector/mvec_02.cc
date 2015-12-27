// file: $isip/class/math/vector/MVector/mvec_02.cc
// version: $Id: mvec_02.cc 10636 2007-01-26 22:18:09Z tm334 $
//

// isip include files
//
#include "MVector.h"
#include <Console.h>
#include <SofParser.h>
#include <typeinfo>

// method: diagnose
//
// arguments:
//  Integral::DEBUG level: (input) debug level
//
// return: a bool8 value indicating status
//
template<class TVector, class TScalar, class TIntegral>
bool8 MVectorMethods::diagnose(Integral::DEBUG level_a) {

  //---------------------------------------------------------------------------
  //
  // 0. preliminaries
  //
  //---------------------------------------------------------------------------

  // output the class name
  //
  if (level_a > Integral::NONE) {
    SysString output(L"diagnosing class ");
    output.concat(name());
    output.concat(L": ");
    Console::put(output);
    Console::increaseIndention();
  }
 
  //---------------------------------------------------------------------------
  //
  // 1. required public methods and extensions to required public methods
  //
  //---------------------------------------------------------------------------

  // set indentation
  //
  if (level_a > Integral::NONE) {
    Console::put(L"testing required public methods...\n");
    Console::increaseIndention();
  }
  
  diagnose1<TVector, TScalar, TIntegral>(level_a);

  diagnose2<TVector, TScalar, TIntegral>(level_a);

  // reset indentation
  //
  if (level_a > Integral::NONE) {
    Console::decreaseIndention();
  }
  
  //---------------------------------------------------------------------------
  //
  // 2. class-specific public methods:
  //     equality and comparison methods
  //
  //---------------------------------------------------------------------------

  // set indentation
  //
  if (level_a > Integral::NONE) {
    Console::put(L"testing class-specific public methods: comparison methods...\n");
    Console::increaseIndention();
  }

  diagnose2<TVector, TScalar, TIntegral>(level_a);

  // reset indentation
  //
  if (level_a > Integral::NONE) {
    Console::decreaseIndention();
  }
  
  //---------------------------------------------------------------------------
  //
  // 3. class-specific public methods:
  //     get and set methods
  //
  //---------------------------------------------------------------------------

  // set indentation
  //
  if (level_a > Integral::NONE) {
    Console::put(L"testing class-specific public methods: get/set methods...\n");
    Console::increaseIndention();
  }

  diagnose3<TVector, TScalar, TIntegral>(level_a);

  // reset indentation
  //
  if (level_a > Integral::NONE) {
    Console::decreaseIndention();
  }

  //---------------------------------------------------------------------------
  //
  // 4. class-specific public methods:
  //     bitwise methods - these are only tested for non-complex
  //     integer types.
  //
  //---------------------------------------------------------------------------

  if ((typeid(TIntegral) != typeid(float32)) &&
      (typeid(TIntegral) != typeid(float64)) &&
      (typeid(TIntegral) != typeid(complexlong)) &&
      (typeid(TIntegral) != typeid(complexfloat)) &&
      (typeid(TIntegral) != typeid(complexdouble))) {

    // set indentation
    //
    if (level_a > Integral::NONE) {
      Console::put(L"testing class-specific public methods: bitwise methods...\n");
      Console::increaseIndention();
    }

    // call the diagnose method
    //
    diagnose4<TVector, TScalar, TIntegral>(level_a);

    // reset indentation
    //
    if (level_a > Integral::NONE) {
      Console::decreaseIndention();
    }
  }

  //---------------------------------------------------------------------------
  //
  // 5. class-specific public methods:
  //     basic mathematical methods
  //
  //--------------------------------------------------------------------------
  
  // set indentation
  //
  if (level_a > Integral::NONE) {
    Console::put(L"testing class-specific public methods: basic mathematical methods...\n");
    Console::increaseIndention();
  }
  
  diagnose5<TVector, TScalar, TIntegral>(level_a);

  // reset indentation
  //
  if (level_a > Integral::NONE) {
    Console::decreaseIndention();
  }
  
  //---------------------------------------------------------------------------
  //
  // 6. class-specific public methods:
  //     other mathematical methods
  //
  //--------------------------------------------------------------------------

  // set indentation
  //
  if (level_a > Integral::NONE) {
    Console::put(L"testing class-specific public methods: other mathematical methods...\n");
    Console::increaseIndention();
  }

  diagnose6<TVector, TScalar, TIntegral>(level_a);

  // reset indentation
  //
  if (level_a > Integral::NONE) {
    Console::decreaseIndention();
  }

  //--------------------------------------------------------------------------
  //
  // 7. class-specific public methods:
  //     sign and dsp related methods 
  //
  //--------------------------------------------------------------------------

  // set indentation
  //
  if (level_a > Integral::NONE) {
    Console::put(L"testing class-specific public methods: dsp methods...\n");
    Console::increaseIndention();
  }
  
  diagnose7<TVector, TScalar, TIntegral>(level_a);

  // reset indentation
  //
  if (level_a > Integral::NONE) {
    Console::decreaseIndention();
  }
  
  //---------------------------------------------------------------------------
  //
  // 8. class-specific public methods:
  //  position operation and search methods
  //
  //--------------------------------------------------------------------------

  // set indentation
  //
  if (level_a > Integral::NONE) {
    Console::put(L"testing class-specific public methods: position and search methods...\n");
    Console::increaseIndention();
  }

  diagnose8<TVector, TScalar, TIntegral>(level_a);

  // reset indentation
  //
  if (level_a > Integral::NONE) {
    Console::decreaseIndention();
  }

  //---------------------------------------------------------------------------
  //
  // 9. class-specific public methods:
  //  complex type methods which is best to test separately
  //
  //--------------------------------------------------------------------------

#ifdef ISIP_TEMPLATE_complex  

  // set indentation
  //
  if (level_a > Integral::NONE) {
    Console::put(L"testing class-specific public methods: complex type methods...\n");
    Console::increaseIndention();
  }

  // test complex functions
  //
  diagnose9<TVector, TScalar, TIntegral>(level_a);
  
  // reset indentation
  //
  if (level_a > Integral::NONE) {
    Console::decreaseIndention();
  }

#endif
  
  //---------------------------------------------------------------------------
  //
  // 10. print completion message
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

// method: diagnose1
//
// arguments:
//  Integral::DEBUG level: (input) debug level for diagnostics
//
// return: a bool8 value indicating status
//
// this method tests required public methods
//
template<class TVector, class TScalar, class TIntegral>
bool8 MVectorMethods::diagnose1(Integral::DEBUG level_a) {

  // declare local variables
  //
  String tmp_filename0;
  String tmp_filename1;
  
  // create some temporary files for I/O tests
  //
  Integral::makeTemp(tmp_filename0);
  Integral::makeTemp(tmp_filename1);

  // test constructors
  //
  TVector val0;
  val0.assign(L"1, 3, 5, 7, 9");

  int32 num_elem = 5;
  TVector val1(num_elem);
  val1.assign(L"0, 2, 4, 6, 8");

  TVector val2;
  TVector val3;

  int32 test_size = 1024;
  TVector val4(test_size);
  TVector val5(test_size);
  
  // assign elements to a vector
  //
  for (int32 i = 0; i < test_size; i++) {
#ifdef ISIP_TEMPLATE_complex
    val4(i) = (TIntegral)(complexlong(i, i*3));
#endif    
    val4(i) = (TIntegral)(i * 3);
  }

  // test scalar assignment
  //
  TVector val6(50);
  for (int32 i = 0; i < 50; i++) {
#ifdef ISIP_TEMPLATE_complex
    val6(i) = (TIntegral)(complexlong(i, i + 1));
#endif
    val6(i) = (TIntegral)i;
  }

  if (level_a > Integral::BRIEF) {
    val6.debug(L"val6");
  }
      
  // test assign methods
  //
  val2.assign(val4);
  val4.swap(val5);

  // test eq methods
  //
  if (val5.ne(val2)) {
    return Error::handle(TVector::name(), L"swap", Error::TEST, __FILE__,
			 __LINE__);
  }
  
  if (val4.ne((TIntegral)0)) {
    return Error::handle(TVector::name(), L"swap", Error::TEST, __FILE__,
			 __LINE__);
  }
  
  //---------------------------------------------------------------------------
  //
  // test get methods for real numbers
  //
  //---------------------------------------------------------------------------

#ifndef ISIP_TEMPLATE_complex

  // real types
  //
  String val_str;
  val1.get(val_str);

  if (val_str.ne(L"0, 2, 4, 6, 8")) {
    val_str.debug(L"val_str");
    return Error::handle(name(), L"get", Error::TEST, __FILE__, __LINE__);
  }

  val1.get(val_str, L"xyz");

  if (val_str.ne(L"0xyz2xyz4xyz6xyz8")) {
    val_str.debug(L"val_str");
    return Error::handle(name(), L"get", Error::TEST, __FILE__, __LINE__);
  }

  TVector val_zero;
  val_zero.get(val_str);

  if (val_str.ne(L"")) {
    val_str.debug(L"val_str");
    return Error::handle(name(), L"get", Error::TEST, __FILE__, __LINE__);
  }

  //---------------------------------------------------------------------------
  //
  // test get methods for complex numbers
  //
  //---------------------------------------------------------------------------

#else

  // complex types
  //
  String val_str;
  val1.get(val_str);

  if (val_str.ne(L"0+0j, 2+0j, 4+0j, 6+0j, 8+0j")) {
    val_str.debug(L"val_str");
    return Error::handle(name(), L"get", Error::TEST, __FILE__, __LINE__);
  }

  val1.get(val_str, L"xyz");

  if (val_str.ne(L"0+0jxyz2+0jxyz4+0jxyz6+0jxyz8+0j")) {
    val_str.debug(L"val_str");
    return Error::handle(name(), L"get", Error::TEST, __FILE__, __LINE__);
  }

  TVector val_zero;
  val_zero.get(val_str);

  if (val_str.ne(L"")) {
    val_str.debug(L"val_str");
    return Error::handle(name(), L"get", Error::TEST, __FILE__, __LINE__);
  }

#endif
  
  //---------------------------------------------------------------------------
  //
  // continue diagnosing using the same code for all types
  //
  //---------------------------------------------------------------------------

  // swap them back and reinitialize val2
  //
  val5.swap(val4);
  
  if (val4.ne(val2)) {
    return Error::handle(TVector::name(), L"swap", Error::TEST, __FILE__,
			 __LINE__);
  }
  
  val2.setLength((int32)0);
  
  if (val5.length() == 0) {
    return Error::handle(TVector::name(), L"swap", Error::TEST,
			 __FILE__, __LINE__);
  }
  
  // make sure deletion works
  //
  val5.setLength((int32)0);
  
  if (val5.length() != 0) {
    return Error::handle(TVector::name(), L"setCapacity", Error::TEST,
			 __FILE__,  __LINE__);
  }

  // make sure deletion works
  //
  val5.setCapacity((int32)1);
  
  if (val5.getCapacity() != 1) {
    return Error::handle(TVector::name(), L"getCapacity", Error::TEST,
			 __FILE__,  __LINE__);
  }

  // test io methods
  //
  if (level_a > Integral::BRIEF) {
    Console::put(L"testing io methods:\n");
  }
  
  // create two special vectors of length 0 and 1
  //
  TVector val_0;
  TVector val_1(1);
  TVector big_val(80000);
  big_val.rand();
  val_1(0) = 42;
  
  // open files in write mode
  //
  Sof text_file;
  text_file.open(tmp_filename0, File::WRITE_ONLY, File::TEXT);
  Sof bin_file;
  bin_file.open(tmp_filename1, File::WRITE_ONLY, File::BINARY);
  
  // write the values
  //
  val_0.write(text_file, (int32)10);          // this is a 0 length vector
  val_0.write(bin_file, (int32)10);
  
  val_1.write(text_file, (int32)11);          // this is a single length vector
  val_1.write(bin_file, (int32)11);
  
  val0.write(text_file, (int32)0);
  val0.write(bin_file, (int32)0);
  
  val1.write(text_file, (int32)1);
  val1.write(bin_file, (int32)1);
  
  val4.write(text_file, (int32)7);         
  val4.write(bin_file, (int32)7);
    
  big_val.write(text_file, (int32)9);
  big_val.write(bin_file, (int32)9);
  
  // close the files
  //
  text_file.close();
  bin_file.close();

  // print some vectors out
  //
  if (level_a > Integral::DETAILED) {
    val_1.setDebug(Integral::NONE);
    val_1.debug(L"val_1");
    val0.debug(L"val0");
  }
  
  // open the files in read mode
  //
  text_file.open(tmp_filename0);
  bin_file.open(tmp_filename1);

  if (level_a > Integral::BRIEF) {
    Console::put(L"files written, closed, and opened:\n");
  }
  
  // test reading zero and single element vector
  //
  if (!val2.read(text_file, (int32)10) || (val2.length() != 0)) {
    return Error::handle(TVector::name(), L"read-text", Error::TEST,
			 __FILE__, __LINE__);
  }
  val2.clear();
    
  if (!val2.read(bin_file, (int32)10) || (val2.length() != 0)) {
    return Error::handle(TVector::name(), L"read-bin", Error::TEST,
			 __FILE__, __LINE__);
  }
  val2.clear();
  
  if (!val2.read(text_file, (int32)11) || (val2.length() != 1)
      || (!val2(0).almostEqual(42))) {
    return Error::handle(TVector::name(), L"read-text", Error::TEST,
			 __FILE__, __LINE__);
  }
  val2.clear();
  
  if (!val2.read(bin_file, (int32)11) || (val2.length() != 1)
      || (!val2(0).almostEqual(42))) {
    return Error::handle(TVector::name(), L"read-bin", Error::TEST,
			 __FILE__, __LINE__);
  }
  val2.clear();
  
  // read other values back in
  //
  if (!val2.read(text_file, (int32)0) || (!val2.almostEqual(val0))) {
    val0.debug(L"val0");
    val2.debug(L"val2");
    return Error::handle(TVector::name(), L"read-text", Error::TEST,
			 __FILE__, __LINE__);
  }
  val2.clear();
  
  if (!val2.read(bin_file, (int32)0) || (!val2.almostEqual(val0))) {
    return Error::handle(TVector::name(), L"read-bin", Error::TEST,
			 __FILE__, __LINE__);
  }
  val2.clear();
  
  if (!val2.read(text_file, (int32)1) || (!val2.almostEqual(val1))) {
    val2.debug(L"val2");
    val1.debug(L"val1");
    return Error::handle(TVector::name(), L"read-text", Error::TEST,
			 __FILE__, __LINE__);
  }
  val2.clear();
  
  if (!val2.read(bin_file, (int32)1) || (!val2.almostEqual(val1))) {
    return Error::handle(TVector::name(), L"read-bin", Error::TEST,
			 __FILE__, __LINE__);
  }
  val2.clear();
  
  if (level_a > Integral::DETAILED) {
    Console::put(L"reading big text\n");
  }
  
  if (!val2.read(text_file, (int32)7) || (!val4.almostEqual(val2))) {
    return Error::handle(TVector::name(), L"read-big-text", Error::TEST,
			 __FILE__, __LINE__);
  }
  val2.clear();
  
  if (level_a > Integral::DETAILED) {
    Console::put(L"reading big binary\n");
  }
  
  if (!val2.read(bin_file, (int32)7) || (!val4.almostEqual(val2))) {
    return Error::handle(TVector::name(), L"read-big-bin", Error::TEST,
			 __FILE__, __LINE__);
  }
  val2.clear();
  
  if (level_a > Integral::DETAILED) {
    Console::put(L"completed read big\n");
  }
  
  if (!val2.read(bin_file, (int32)9) || (!big_val.almostEqual(val2))) {
    return Error::handle(TVector::name(), L"read-big-bin", Error::TEST,
			 __FILE__, __LINE__);
  }
  val2.clear();
  
  if (!val2.read(bin_file, (int32)9) || (!big_val.almostEqual(val2))) {
    return Error::handle(TVector::name(), L"read-big-bin", Error::TEST,
			 __FILE__, __LINE__);
  }
  val2.clear();

  // close the temporary files
  //
  text_file.close();
  bin_file.close();


  // reset indentation
  //
  if (level_a > Integral::NONE) {
    Console::decreaseIndention();
  }
  
  // set indentation
  //
  if (level_a > Integral::NONE) {
    Console::put(L"testing class-specific public methods: ext. to required methods...\n");
    Console::increaseIndention();
  }
  
  val0.assign(L"1, 3, 5, 7, 9");
  val1.assign(L"0, 2, 4, 6, 8");
  
  test_size = 1024;
  val4.setLength(test_size);
  val5.setLength(test_size);

  // open files in read mode
  //
  text_file.open(tmp_filename0, File::READ_ONLY, File::TEXT);
  bin_file.open(tmp_filename1, File::READ_ONLY, File::BINARY);
  
  // test partial reads (last 128 entries, specify 256)
  //
  if (level_a > Integral::BRIEF) {
    Console::put(L"testing partial io methods:\n");
  }

  if (!text_file.find(TVector::name(), (int32)7)) {
    return Error::handle(name(), L"find", Error::TEST, __FILE__, __LINE__);
  }

  if (!bin_file.find(TVector::name(), (int32)7)) {
    return Error::handle(name(), L"find", Error::TEST, __FILE__, __LINE__);
  }
  
  if (!val2.readStart(text_file)) {
    return Error::handle(name(), L"readStart", Error::TEST, __FILE__,
			 __LINE__);
  }

  if (!val3.readStart(bin_file)) {
    return Error::handle(name(), L"readStart", Error::TEST, __FILE__,
			 __LINE__);
  }

  if (val2.readPartialData(text_file, test_size - 128, 256) != 128) {
    return Error::handle(TVector::name(), L"readPartial (text)", Error::TEST,
			 __FILE__, __LINE__);
  }
  if (val3.readPartialData(bin_file, test_size - 128, 256) != 128) {
    return Error::handle(TVector::name(), L"readPartial (binary)", Error::TEST,
			 __FILE__, __LINE__);
  }
  
  for (int32 i = 0; i < 128; i++) {
    if (!val2(i).almostEqual((test_size - 128 + i) * 3)) {
      return Error::handle(TVector::name(), L"readPartialData (text)",
			   Error::TEST, __FILE__, __LINE__);
    }
    if (!val3(i).almostEqual((test_size - 128 + i) * 3)) {
      return Error::handle(TVector::name(), L"readPartialData (binary)",
			   Error::TEST, __FILE__, __LINE__);
    }
  }

  // test readTerminate
  //
  val2.readTerminate(text_file);
  val3.readTerminate(bin_file);

  // test partial reads (last 128 entries, specify 64)
  //
  val2.clear();
  val3.clear();
  
  if (!text_file.find(TVector::name(), (int32)7)) {
    return Error::handle(name(), L"find", Error::TEST, __FILE__, __LINE__);
  }

  if (!bin_file.find(TVector::name(), (int32)7)) {
    return Error::handle(name(), L"find", Error::TEST, __FILE__, __LINE__);
  }

  if (!val2.readStart(text_file)) {
    return Error::handle(name(), L"readStart", Error::TEST, __FILE__,
			 __LINE__);
  }

  if (!val3.readStart(bin_file)) {
    return Error::handle(name(), L"readStart", Error::TEST, __FILE__,
			 __LINE__);
  }

  if (val2.readPartialData(text_file, test_size - 128, 64) != 64) {
    return Error::handle(TVector::name(), L"readPartial (text)", Error::TEST,
			 __FILE__, __LINE__);
  }
  if (val3.readPartialData(bin_file, test_size - 128, 64) != 64) {
    return Error::handle(TVector::name(), L"readPartial (binary)", Error::TEST,
			 __FILE__, __LINE__);
  }
  
  for (int32 i = 0; i < 64; i++) {
    if (!val2(i).almostEqual((test_size - 128 + i) * 3)) {
      return Error::handle(TVector::name(), L"readPartialData (text)",
			   Error::TEST,  __FILE__, __LINE__);
    }
    if (!val3(i).almostEqual((test_size - 128 + i) * 3)) {
      val3.debug(L"Wrong vector:");
      return Error::handle(TVector::name(), L"readPartialData (binary)",
			   Error::TEST,  __FILE__, __LINE__);
    }
  }
  val2.clear();
  val3.clear();

  val2.readTerminate(text_file);
  val3.readTerminate(bin_file);

  text_file.close();
  bin_file.close();

  // test partial write
  //
  text_file.open(tmp_filename0, File::WRITE_ONLY, File::TEXT);
  bin_file.open(tmp_filename1, File::WRITE_ONLY, File::BINARY);

  val4.setLength(0);
  
  val1.setLength(50);
  text_file.put(val1.name(), 0, -1);
  bin_file.put(val1.name(), 0, val4.sofSize());
  val1.writeStart(text_file);
  val1.writeStart(bin_file);

  val1.assign((TIntegral)20);
  val4.concat(val1);
  val1.writePartialData(text_file, 0, val1.length());
  val1.writePartialData(bin_file, 0, val1.length());

  val1.assign((TIntegral)25);
  val4.concat(val1);
  val1.writePartialData(text_file, 0, val1.length());
  val1.writePartialData(bin_file, 0, val1.length());

  val1.assign((TIntegral)30);
  val4.concat(val1);
  val1.writePartialData(text_file, 0, val1.length());
  val1.writePartialData(bin_file, 0, val1.length());

  val1.assign((TIntegral)35);
  val4.concat(val1);
  val1.writePartialData(text_file, 0, val1.length());
  val1.writePartialData(bin_file, 0, val1.length());

  val1.writeTerminate(text_file);
  val1.writeTerminate(bin_file);

  text_file.close();
  bin_file.close();

  text_file.open(tmp_filename0);
  bin_file.open(tmp_filename0);

  val2.read(text_file, 0);
  val3.read(bin_file, 0);

  if (val2.length() != 200) {
    val2.debug(L"Wrong Vector:");
    return Error::handle(name(), L"writePartial", Error::TEST, __FILE__,
			 __LINE__);
  }

  if (val3.length() != 200) {
    return Error::handle(name(), L"writePartial", Error::TEST, __FILE__,
			 __LINE__);
  }

  if (!val2.almostEqual(val4)) {
    return Error::handle(name(), L"writePartial", Error::TEST, __FILE__,
			 __LINE__);
  }

  // close and  delete the temporary files
  //
  text_file.close();
  bin_file.close();
  File::remove(tmp_filename0);
  File::remove(tmp_filename1);

  // test assignment methods
  //
  val0.setLength(num_elem);
  val1.setLength(num_elem);
  
  // assign values
  //
  val0.assign((TIntegral)43);
  val1.assign(val0);
  
  if (val0.ne(val1)) {
    return Error::handle(TVector::name(), L"assign", Error::TEST,
			 __FILE__, __LINE__);
  }
  
  // test assignments
  //
  uint16* scalar_ushort = new uint16[num_elem];
  uint32* scalar_ulong = new uint32[num_elem];
  uint64* scalar_ullong = new uint64[num_elem];
  int16* scalar_short = new int16[num_elem];
  int32* scalar_long = new int32[num_elem];
  int64* scalar_llong = new int64[num_elem];
  float32* scalar_float = new float32[num_elem];
  float64* scalar_double = new float64[num_elem];
  byte8* scalar_byte = new byte8[num_elem];
  complexdouble* complex_double = new complexdouble[num_elem];
  complexfloat* complex_float = new complexfloat[num_elem];
  complexlong* complex_long = new complexlong[num_elem];
  
  MVector<Byte, byte8> vector_byte(num_elem);
  MVector<Ushort, uint16> vector_ushort(num_elem);
  MVector<Ulong, uint32> vector_ulong(num_elem);
  MVector<Ullong, uint64> vector_ullong(num_elem);
  MVector<Short, int16> vector_short(num_elem);
  MVector<Long, int32> vector_long(num_elem);
  MVector<Llong, int64> vector_llong(num_elem);
  MVector<Float, float32> vector_float(num_elem);
  MVector<Double, float64> vector_double(num_elem);
  MVector<ComplexDouble, complexdouble> vector_complexdouble(num_elem);
  MVector<ComplexFloat, complexfloat> vector_complexfloat(num_elem);
  MVector<ComplexLong, complexlong> vector_complexlong(num_elem);  
  
  for (int i = 0; i < num_elem; i++) {
    scalar_ushort[i] = (uint16)43;
    scalar_ulong[i] = (uint32)43;
    scalar_ullong[i] = (uint64)43;
    scalar_short[i] = (int16)43;
    scalar_long[i] = (int32)43;
    scalar_llong[i] = (int64)43;
    scalar_float[i] = (float32)43.0;
    scalar_double[i] = (float64)43.0;
    scalar_byte[i] = (byte8)43;
    complex_double[i] = complexdouble(43, 40);
    complex_float[i] = complexfloat(43, 40);
    complex_long[i] = complexlong(43, 40);    
  }
  
  vector_byte.assign(num_elem, scalar_byte);
  vector_ushort.assign(num_elem, scalar_ushort);
  vector_ulong.assign(num_elem, scalar_ulong);
  vector_ullong.assign(num_elem, scalar_ullong);
  vector_short.assign(num_elem, scalar_short);
  vector_long.assign(num_elem, scalar_long);
  vector_llong.assign(num_elem, scalar_llong);
  vector_float.assign(num_elem, scalar_float);
  vector_double.assign(num_elem, scalar_double);
  vector_complexdouble.assign(num_elem, complex_double);
  vector_complexfloat.assign(num_elem, complex_float);
  vector_complexlong.assign(num_elem, complex_long);  
 
  
  // test assignments from uint16
  //
  val0.assign(num_elem, scalar_ushort);
  if (val0.ne((TIntegral)43)) {
    return Error::handle(TVector::name(), L"assign(int32, uint16*)",
			 Error::TEST, __FILE__, __LINE__);
  }
  
  val1.assign(vector_ushort);
  if (val0.ne(val1)) {
    return Error::handle(TVector::name(), L"assign(vector_ushort)",
			 Error::TEST, __FILE__, __LINE__);
  }
  
  // test assignments from uint32
  //
  val0.assign(num_elem, scalar_ulong);
  if (val0.ne((TIntegral)43)) {
    return Error::handle(TVector::name(), L"assign(int32, uint32*)", Error::TEST,
			 __FILE__, __LINE__);
  }
  
  val1.assign(vector_ulong);
  if (val0.ne(val1)) {
    return Error::handle(TVector::name(), L"assign(vector_ulong)", Error::TEST,
			 __FILE__, __LINE__);
  }
  
  // test assignments from uint64
  //
  val0.assign(num_elem, scalar_ullong);
  if (val0.ne((TIntegral)43)) {
    return Error::handle(TVector::name(), L"assign(int32, uint64*)",
			 Error::TEST, __FILE__, __LINE__);
  }
  
  val1.assign(vector_ullong);
  if (val0.ne(val1)) {
    return Error::handle(TVector::name(), L"assign(vector_ullong)",
			 Error::TEST, __FILE__, __LINE__);
  }
  
  // test assignments from int16
  //
  val0.assign(num_elem, scalar_short);
  if (val0.ne((TIntegral)43)) {
    return Error::handle(TVector::name(), L"assign(int32, int16*)", Error::TEST,
			 __FILE__, __LINE__);
  }
  
  val1.assign(vector_short);
  if (val0.ne(val1)) {
    return Error::handle(TVector::name(), L"assign(vector_short)", Error::TEST,
			 __FILE__, __LINE__);
  }
  
  // test assignments from int32
  //
  val0.assign(num_elem, scalar_long);
  if (val0.ne((TIntegral)43)) {
    return Error::handle(TVector::name(), L"assign(int32, int32*)", Error::TEST,
			 __FILE__, __LINE__);
  }
  
  val1.assign(vector_long);
  if (val0.ne(val1)) {
    return Error::handle(TVector::name(), L"assign(vector_long)", Error::TEST,
			 __FILE__, __LINE__);
  }
  
  // test assignments from int64
  //
  val0.assign(num_elem, scalar_llong);
  if (val0.ne((TIntegral)43)) {
    return Error::handle(TVector::name(), L"assign(int32, int64*)", Error::TEST,
			 __FILE__, __LINE__);
  }
  
  val1.assign(vector_llong);
  if (val0.ne(val1)) {
    return Error::handle(TVector::name(), L"assign(vector_llong)", Error::TEST,
			 __FILE__, __LINE__);
  }
  
  // test assignments from float
  //
  val0.assign(num_elem, scalar_float);
  if (val0.ne((TIntegral)43)) {
    return Error::handle(TVector::name(), L"assign(int32, float32*)", Error::TEST,
			 __FILE__, __LINE__);
  } 
  
  val1.assign(vector_float);
  if (val0.ne(val1)) {
    return Error::handle(TVector::name(), L"assign(vector_float)", Error::TEST,
			 __FILE__, __LINE__);
  }
  
  // test assignments from float64
  //
  val0.assign(num_elem, scalar_double);
  if (val0.ne((TIntegral)43)) {
    return Error::handle(TVector::name(), L"assign(int32, float64*)",
			 Error::TEST, __FILE__, __LINE__);
  }
  
  val1.assign(vector_double);
  if (val0.ne(val1)) {
    return Error::handle(TVector::name(), L"assign(vector_double)",
			 Error::TEST, __FILE__, __LINE__);
  }
  
  // test assignments from byte
  //
  val0.assign(num_elem, scalar_byte);
  if (val0.ne((TIntegral)43)) {
    return Error::handle(TVector::name(), L"assign(int32, byte8*)", Error::TEST,
			 __FILE__, __LINE__);
  }
  
  val1.assign(vector_byte);
  if (val0.ne(val1)) {
    return Error::handle(TVector::name(), L"assign(vector_byte)", Error::TEST,
			 __FILE__, __LINE__);
  }

#ifdef ISIP_TEMPLATE_complex  
  // test assignments from complexdouble
  //
  val0.assign(num_elem, complex_double);
  if (val0.ne((TIntegral)complexdouble(43, 40))) {
    return Error::handle(TVector::name(), L"assign(int32, complexdouble*)",
			 Error::TEST,  __FILE__, __LINE__);
  }
  
  val1.assign(vector_complexdouble);
  if (val0.ne(val1)) {
    return Error::handle(TVector::name(), L"assign(vector_complexdouble)",
			 Error::TEST,  __FILE__, __LINE__);
  }

  // test assignments from complexfloat
  //
  val0.assign(num_elem, complex_float);
  if (val0.ne((TIntegral)complexfloat(43, 40))) {
    return Error::handle(TVector::name(), L"assign(int32, complexfloat*)",
			 Error::TEST,  __FILE__, __LINE__);
  }
  
  val1.assign(vector_complexfloat);
  if (val0.ne(val1)) {
    return Error::handle(TVector::name(), L"assign(vector_complexfloat)",
			 Error::TEST,  __FILE__, __LINE__);
  }
  
  // test assignments from complexlong
  //
  val0.assign(num_elem, complex_long);
  if (val0.ne((TIntegral)complexlong(43, 40))) {
    return Error::handle(TVector::name(), L"assign(int32, complexlong*)",
			 Error::TEST,  __FILE__, __LINE__);
  }
  
  val1.assign(vector_complexlong);
  if (val0.ne(val1)) {
    return Error::handle(TVector::name(), L"assign(vector_complexlong)",
			 Error::TEST,  __FILE__, __LINE__);
  }  
  
#endif    
  
  // free memory
  //
  delete [] scalar_ushort;
  delete [] scalar_ulong;
  delete [] scalar_ullong;
  delete [] scalar_short;
  delete [] scalar_long;
  delete [] scalar_llong;
  delete [] scalar_float;
  delete [] scalar_double;
  delete [] scalar_byte;
  delete [] complex_double;
  delete [] complex_float;
  delete [] complex_long;
  
  val0.assign((int32)20, (TIntegral)27);
  if (val0.ne((TIntegral)27) || ((int32)(val0.length_d) != 20)) {
    return Error::handle(TVector::name(), L"assign", Error::TEST, __FILE__,
			 __LINE__);
  }

  // test clear
  //
  val0.clear(Integral::RETAIN);
  if (val0.ne(TScalar::DEF_VALUE) || ((int32)(val0.length_d) != 20)) {
    return Error::handle(TVector::name(), L"clear", Error::TEST, __FILE__,
			 __LINE__);
  }

  // get the memsize
  //
  int32 mem_size = val0.memSize();
  
  if (level_a > Integral::BRIEF) {
    SysString numeric;
    numeric.assign(mem_size);
    SysString output(L"memSize of sof_0: ");
    output.concat(numeric);
    Console::put(output);
  }
    
  // exit gracefully
  //
  return true;
}

// method: diagnose2
//
// arguments:
//  Integral::DEBUG level: (input) debug level for diagnostics
//
// return: a bool8 value indicating status
//
// this method tests equality and comparison methods
//
template<class TVector, class TScalar, class TIntegral>
bool8 MVectorMethods::diagnose2(Integral::DEBUG level_a) {

  // declare local variables
  //
  int32 num_elem = 5;

  TVector val0;
  val0.assign(L"1, 3, 5, 7, 9");

#ifdef ISIP_TEMPLATE_complex
  val0.assign(L"1+2j, 3+4j, 5+6j, 7+8j, 9+7j");
#endif  
  
  TVector val1;

  // equality methods and operator != and ==
  // 
  val1.setLength(num_elem);
  val1.assign(val0);
  if (val0.ne(val1)) {
    return Error::handle(TVector::name(), L"assign", Error::TEST, __FILE__,
			 __LINE__);
  }

  val1.assign(val0);
  if (!val0.eq(val1)) {
    return Error::handle(TVector::name(), L"eq", Error::TEST, __FILE__,
			 __LINE__);
  }

  // check relational operations and operator >, <,  >=, <=
  //
  val0.assign((TIntegral)30);
  val1.assign((TIntegral)43);
  
  if (val0.gt(42)) {
    return Error::handle(TVector::name(), L"gt", Error::TEST, __FILE__,
			 __LINE__);
  }
  
  if (val0 > (42)) {
    return Error::handle(TVector::name(), L"gt", Error::TEST, __FILE__,
			 __LINE__);
  }
  
  if (val1.lt(42)) {
    return Error::handle(TVector::name(), L"lt", Error::TEST, __FILE__,
			 __LINE__);
  }

  if (val1 < (42)) {
    return Error::handle(TVector::name(), L"lt", Error::TEST, __FILE__,
			 __LINE__);
  }
  
  if (!val1.ge(43)) {
    return Error::handle(TVector::name(), L"ge", Error::TEST, __FILE__,
			 __LINE__);
  }

  if (!(val1 >= (43))) {
    return Error::handle(TVector::name(), L"ge", Error::TEST, __FILE__,
			 __LINE__);
  }    
  
  if (val1.le(42)) {
    return Error::handle(TVector::name(), L"le", Error::TEST, __FILE__,
			 __LINE__);
  }
  
  if (val1 <= (42)) {
    return Error::handle(TVector::name(), L"le", Error::TEST, __FILE__,
			 __LINE__);
  }
    
  if (val0.eq(val1) || !(val1 == ((TIntegral)43))) {
    return Error::handle(TVector::name(), L"eq", Error::TEST, __FILE__,
			 __LINE__);
  }
  
  if (!val0.ne(val1) || val1 != ((TIntegral)43)) {
    return Error::handle(TVector::name(), L"ne", Error::TEST, __FILE__,
			 __LINE__);
  }
  
  // exit gracefully
  //
  return true;
}

// method: diagnose3
//
// arguments:
//  Integral::DEBUG level: (input) debug level for diagnostics
//
// return: a bool8 value indicating status
//
// this method tests get and set methods
//
template<class TVector, class TScalar, class TIntegral>
bool8 MVectorMethods::diagnose3(Integral::DEBUG level_a) {

  // declare local variables
  //
  // test constructors
  //
  TVector val_0;

  // test setLength and length
  //
  int32 num_elem = 5;
  val_0.setLength(num_elem);

  if (val_0.length() != num_elem) {
    return Error::handle(TVector::name(), L"length", Error::TEST,
			 __FILE__,  __LINE__);
  }

  // test operator ()
  //
  val_0.assign((TIntegral)1);
  if (!val_0(2).almostEqual(1)) {
    return Error::handle(TVector::name(), L"operator()", Error::TEST,
			 __FILE__,  __LINE__);
  }

  // exit gracefully
  //
  return true;
}

// method: diagnose4
//
// arguments:
//  Integral::DEBUG level: (input) debug level for diagnostics
//
// return: a bool8 value indicating status
//
// this method tests bitwise methods (for non-complex integer types only)
//
template<class TVector, class TScalar, class TIntegral>
bool8 MVectorMethods::diagnose4(Integral::DEBUG level_a) {

  //---------------------------------------------------------------------------
  //
  // test bitwise methods
  //
  //---------------------------------------------------------------------------

  // declare local variables
  //
  TVector val0;
  val0.assign(L"1, 3, 5, 7, 9");

  TVector val1;
  val1.assign(L"0, 2, 4, 6, 8");

  TVector val2;

  // modulus
  //
  val1.assign((TIntegral)10);
  val0.mod(val0, val1);
  
  if (val0.ne((TIntegral)3)) {
    return Error::handle(TVector::name(), L"mod",
			 Error::TEST, __FILE__, __LINE__);
  }
  
  val0.assign((TIntegral)43);
  val0.mod(val0, (TIntegral)2);
  
  if (val0.ne((TIntegral)1)) {
    return Error::handle(TVector::name(), L"mod",
			 Error::TEST, __FILE__, __LINE__);
  }
  
  if (level_a > Integral::BRIEF) {
    Console::put(L"testing bitwise operations:\n");
  }
  
  // bitwise operations (num2 = num0 op num1)
  //
  TIntegral num0;
  TIntegral num1;   
  TIntegral num2;
  
  val0.setLength(10);
  val1.setLength(10);
  val2.setLength(10);
  
  // test band
  //
  num0 = 6;
  num1 = 2;
  num2 = 2;
  val0.assign(num0);
  val1.assign(num0);
  val2.assign(num1);
  
  val0.band(val2);
  val1.band(num1);
  
  if ((val0.ne(num2)) || (val1.ne(num2))) {
    return Error::handle(TVector::name(), L"band",
			 Error::TEST, __FILE__, __LINE__);
  }
  
  // test bor
  //
  num2 = 6;
  val0.assign(num0);
  val1.assign(num0);
  val2.assign(num1);
  
  val0.bor(val2);
  val1.bor(num1);
  
  if ((val0.ne(num2)) || (val1.ne(num2))) {
    return Error::handle(TVector::name(), L"bor",
			 Error::TEST, __FILE__, __LINE__);
  }
  
  // test bxor
  //
  num2 = 4;
  val0.assign(num0);
  val1.assign(num0);
  val2.assign(num1);
  
  val0.bxor(val2);
  val1.bxor(num1);
  
  if ((val0.ne(num2)) || (val1.ne(num2))) {
    return Error::handle(TVector::name(), L"bxor",
			 Error::TEST, __FILE__, __LINE__);
  }
  
  // test brs
  //
  num2 = 1;
  val0.assign(num0);
  val1.assign(num0);
  val2.assign(num0);
  
  val0.brs(val2, num1);
  val1.brs(num1);
  
  if ((val0.ne(num2) || (val1.ne(num2)))) {
    val0.debug(L"val0");
    val1.debug(L"val1");
    return Error::handle(TVector::name(), L"brs",
			 Error::TEST, __FILE__, __LINE__);
  }
  
  // test bls
  //
  num2 = 24;
  val0.assign(num0);
  val1.assign(num0);
  val2.assign(num0);
  
  val0.bls(val2, num1);
  val1.bls(num1);
  
  if ((val0.ne(num2)) || (val1.ne(num2))) {
    return Error::handle(TVector::name(), L"bls",
			 Error::TEST, __FILE__, __LINE__);
  }
  
  // test bcmpl: this is tricky with different lengths, constrain to 8 bits
  // 
  num2 = (TIntegral)0xF9;
  num1 = (TIntegral)0xFF;	         // mask off result
  val0.assign(num0);
  val0.bcmpl();
  val0.band(num1);
  
  if (val0.ne(num2)) {
    return Error::handle(TVector::name(), L"bcmpl",
			 Error::TEST, __FILE__, __LINE__);
  }
  
  // exit gracefully
  //
  return true;
}

// method: diagnose5
//
// arguments:
//  Integral::DEBUG level: (input) debug level for diagnostics
//
// return: a bool8 value indicating status
//
// this method tests basic mathematical methods
//
template<class TVector, class TScalar, class TIntegral>
bool8 MVectorMethods::diagnose5(Integral::DEBUG level_a) {

  // declare local variables
  //
  TVector val0;
  val0.assign(L"1, 3, 5, 7, 9");
  TVector val1;
  val1.assign(L"0, 2, 4, 6, 8");
  
  // addition
  //
  val1.assign((TIntegral)40);
  val0.add(val1, 1);
  val0.add(2);
  
  if (!val0.almostEqual((TIntegral)43)) {
    return Error::handle(TVector::name(), L"add",
			 Error::TEST, __FILE__, __LINE__);
  }
  
  val1.assign((TIntegral)10);
  val0.add(val1);
  val0.add(7);
  
  if (!val0.almostEqual((TIntegral)60)) {
    return Error::handle(TVector::name(), L"add",
			 Error::TEST, __FILE__, __LINE__);
  }
  
  // subtraction
  //
  val1.assign((TIntegral)10);
  val0.sub(val1);
  val0.sub(7);
  
  if (!val0.almostEqual((TIntegral)43)) {
    return Error::handle(TVector::name(), L"sub",
			 Error::TEST, __FILE__, __LINE__);
  }
  
  // multiplication
  //
  val1.assign((TIntegral)2);
  val0.mult(val1);
  val0.mult((TIntegral)2);
  
  if (!val0.almostEqual((TIntegral)172)) {
    return Error::handle(TVector::name(), L"mult",
			 Error::TEST, __FILE__, __LINE__);
  }
  
  // division
  //
  val1.assign((TIntegral)2);
  val0.div(val1);
  val0.div(2);
  
  if (!val0.almostEqual((TIntegral)43)) {
    return Error::handle(TVector::name(), L"div",
			 Error::TEST, __FILE__, __LINE__);
  }
  
  // exit gracefully
  //
  return true;
}

// method: diagnose6
//
// arguments:
//  Integral::DEBUG level: (input) debug level for diagnostics
//
// return: a bool8 value indicating status
//
// this method test other mathematical methods
//
template<class TVector, class TScalar, class TIntegral>
bool8 MVectorMethods::diagnose6(Integral::DEBUG level_a) {

  // declare local variables
  //
  int32 num_elem = 5;

  TVector val0;
  val0.assign(L"1, 3, 5, 7, 9");
  TVector val1;
  val1.assign(L"0, 2, 4, 6, 8");
  
  TVector val2;
  val2.setLength(num_elem);

  TVector val3;
  
  // test log/exp
  //
  val0.assign((TIntegral)55);                  // exp**4.007 = 55.0
  val1.log(val0);
  if (!val1.almostEqual((TIntegral)4.00733318523)) {
    val1.debug(L"log");
    return Error::handle(TVector::name(), L"log",
    			 Error::TEST, __FILE__, __LINE__);
  }
  
  val1.exp();
  if (!val0.almostEqual(val1)) {
    val1.debug(L"val1 exp");
    val0.debug(L"val0 exp");
    return Error::handle(TVector::name(), L"exp",
			 Error::TEST, __FILE__, __LINE__);
  }
  
  // test log1p
  //
  val0.assign((TIntegral)54);                 // exp**4.007 = 55
  val1.log1p(val0);
  if (!val1.almostEqual((TIntegral)4.00733318523)) {
    val1.debug(L"log1p");
    return Error::handle(TVector::name(), L"log1p",
			 Error::TEST, __FILE__, __LINE__);
  }
  
  // test log2/exp2
  //
  val0.assign((TIntegral)64);
  val1.log2(val0);
  if (!val1.almostEqual((TIntegral)6)) {
    val1.debug(L"log2");
    return Error::handle(TVector::name(), L"log2",
			 Error::TEST, __FILE__, __LINE__);
  }
  
  val1.exp2();
  if (!val0.almostEqual(val1)) {
    val1.debug(L"exp2");
    return Error::handle(TVector::name(), L"exp2",
			 Error::TEST, __FILE__, __LINE__);
  }
  
  // test log10/exp10
  //
  val0.assign((TIntegral)100);
  val1.log10(val0);
  if (!val1.almostEqual((TIntegral)2)) {
    val1.debug(L"log10");
    return Error::handle(TVector::name(), L"log10",
			 Error::TEST, __FILE__, __LINE__);
  }
  
  val1.exp10();
  if (!val0.almostEqual(val1)) {
    val1.debug(L"exp10 test");
    return Error::handle(TVector::name(), L"exp10",
			 Error::TEST, __FILE__, __LINE__);
  }
  
  // test square root/ square
  //
  val0.assign((TIntegral)81);
  val1.sqrt(val0);
  
  if (!val1.almostEqual((TIntegral)9)) {
    val1.debug(L"sqrt(81)");
    return Error::handle(TVector::name(), L"sqrt",
			 Error::TEST, __FILE__, __LINE__);
  }
  
  val1.square();
  if (!val0.almostEqual(val1)) {
    val1.debug(L"square(9)");
    return Error::handle(TVector::name(), L"square",
			 Error::TEST, __FILE__, __LINE__);
  }
  
  // test inverse
  //
  val0.assign((TIntegral)27);
  val1.inverse(val0);
  val0.inverse();
  
  if (!val1.almostEqual((TIntegral)1 / (TIntegral)27) ||
      !val0.almostEqual((TIntegral)1 / (TIntegral)27)) {
    val1.debug(L"inverse(27)");
    val0.debug(L"inverse(27)");
    return Error::handle(TVector::name(), L"inverse",
			 Error::TEST, __FILE__, __LINE__);
  }
  
  // test pow
  //
  val0.assign((TIntegral)5);
  val0.pow((float64)3.0);
  if (!val0.almostEqual((TIntegral)125)) {
    val0.debug(L"sqrt(5^3)");
    return Error::handle(TVector::name(), L"pow",
			 Error::TEST, __FILE__, __LINE__);
  }
  
  // test factorial
  //
  val0.assign((TIntegral)5);
  val2.assign((TIntegral)120);
  val1.factorial(val0);
  
  if (!val1.almostEqual(val2)) {
    val1.debug(L"5! = ");
    return Error::handle(TVector::name(), L"factorial",
			 Error::TEST, __FILE__, __LINE__);
  }
  
  // test ramp
  //
  val0.setLength(25);
  val0.ramp(5, 2);
  val1.assign(L"5,7,9,11,13,15,17,19,21,23,25,27,29,31,33,35,37,39,41,43,45,47,49,51,53");
  
  if (!val1.almostEqual(val0)) {
    val0.debug(L"ramp");
    return Error::handle(TVector::name(), L"ramp",
			 Error::TEST, __FILE__, __LINE__);
  }
  
  // test the ramp overload
  //
  val0.setLength(0);
  val0.ramp(5, 2, 53);
  
  if (!val1.almostEqual(val0)) {
    val0.debug(L"ramp");
    return Error::handle(TVector::name(), L"ramp",
			 Error::TEST, __FILE__, __LINE__);
  }

  // test sort
  //
  if (level_a > Integral::BRIEF) {
    Console::put(L"testing sort:\n");
  }

  val0.setLength(10);
  TVector val0a;
  
  val0.assign(L"71,9,13,17,25,21,123,25,127,53");    
  val0a.sort(val0);
  
  for (int32 i = 0; i < 9; i++) {
    if (val0a(i) > val0a(i + 1)) {
      val0a.debug(L"sort");
      return Error::handle(TVector::name(), L"sort",
			   Error::TEST, __FILE__, __LINE__);
    }
  }
  
  val0a.sort(val0, Integral::DESCENDING);
  
  for (int32 i = 0; i < 9; i++) {
    if (val0a(i) < val0a(i + 1)) {
      val0a.debug(L"sort");
      return Error::handle(TVector::name(), L"sort",
			   Error::TEST, __FILE__, __LINE__);
    }
  }
  val0a.clear();
  
  
  // test float and float64 specific operations
  //
  if ((typeid(TIntegral) == typeid(float32)) ||
      (typeid(TIntegral) == typeid(float64))) {
    
    if (level_a > Integral::BRIEF) {
      Console::put(L"testing floating point methods:\n");
    }
    
    val0.setLength(10);
    val1.setLength(10);
    val2.setLength(10);
    val3.setLength(10);
    
    // test round
    //
    TIntegral num0 = (TIntegral)2.4;
    TIntegral num1 = (TIntegral)2.6;
    TIntegral res0 = (TIntegral)2.0;
    TIntegral res1 = (TIntegral)3.0;
    
    val0.assign(num0);
    val1.assign(num1);
    val2.assign(res0);
    val3.assign(res1);
    
    val0.round();
    val1.round();
    
    if ((!val0.almostEqual(val2)) || (!val1.almostEqual(val3))) {
      return Error::handle(TVector::name(), L"round",
			   Error::TEST, __FILE__, __LINE__);
    }
    
    // test floor
    //
    num0 = (TIntegral)2.4;
    num1 = (TIntegral)-20.3;
    res0 = (TIntegral)2.0;
    res1 = (TIntegral)-21.0;
    
    val0.assign(num0);
    val1.assign(num1);
    val2.assign(res0);
    val3.assign(res1);
    
    val0.floor();
    val1.floor();
    if ((!val0.almostEqual(val2)) || (!val1.almostEqual(val3))) {
      return Error::handle(TVector::name(), L"floor",
			   Error::TEST, __FILE__, __LINE__);
    }
    
    // test ceil
    //
    num0 = (TIntegral)2.4;
    num1 = (TIntegral)-20.3;
    res0 = (TIntegral)3.0;
    res1 = (TIntegral)-20.0;
    
    val0.assign(num0);
    val1.assign(num1);
    val2.assign(res0);
    val3.assign(res1);
    
    val0.ceil();
    val1.ceil();
    if ((!val0.almostEqual(val2)) || (!val1.almostEqual(val3))) {
      return Error::handle(TVector::name(), L"floor",
			   Error::TEST, __FILE__, __LINE__);
    }
    
    // test rfloor
    //
    num0 = (TIntegral)2.4;
    num1 = (TIntegral)-20.3;
    res0 = (TIntegral)-0.4;
    res1 = (TIntegral)-0.7;
    
    val0.assign(num0);
    val1.assign(num1);
    val2.assign(res0);
    val3.assign(res1);
    
    val0.rfloor();
    val1.rfloor();
    if ((!val0.almostEqual(val2)) || (!val1.almostEqual(val3))) {
      return Error::handle(TVector::name(), L"floor",
			   Error::TEST, __FILE__, __LINE__);
    }
    
    // test rceil
    //
    num0 = (TIntegral)2.4;
    num1 = (TIntegral)-20.3;
    res0 = (TIntegral)0.6;
    res1 = (TIntegral)0.3;
    
    val0.assign(num0);
    val1.assign(num1);
    val2.assign(res0);
    val3.assign(res1);
    
    val0.rceil();
    val1.rceil();
    if ((!val0.almostEqual(val2)) || (!val1.almostEqual(val3))) {
      return Error::handle(TVector::name(), L"floor",
			   Error::TEST, __FILE__, __LINE__);
    }
    
    // test fraction
    //
    num0 = (TIntegral)2.4;
    num1 = (TIntegral)-34.1;
    res0 = (TIntegral)0.4;
    res1 = (TIntegral)-0.1;
    
    val0.assign(num0);
    val1.assign(num1);
    val2.assign(res0);
    val3.assign(res1);
    
    val0.fraction();
    val1.fraction();
    if ((!val0.almostEqual(val2)) || (!val1.almostEqual(val3))) {
      return Error::handle(TVector::name(), L"fraction",
			   Error::TEST, __FILE__, __LINE__);
    }
    
    // test sin/asin
    //
    num0 = (TIntegral)(Integral::PI / 6);
    num1 = (TIntegral)0.5;
    val0.assign(num0);
    val2.assign(num1);
    
    val1.sin(val0);
    
    if (!val1.almostEqual(val2)) {
      return Error::handle(TVector::name(), L"sin",
			   Error::TEST, __FILE__, __LINE__);
    }
    
    val1.asin();
    if (!val0.almostEqual(val1)) {
      return Error::handle(TVector::name(), L"asin",
			   Error::TEST, __FILE__, __LINE__);
    }
    
    // test asinh / sinh
    //
    val0.assign((TIntegral)(Integral::PI / (float64)6));
    val1.sinh(val0);
    val1.asinh();
    if (!val0.almostEqual(val1)) {
      val0.debug(L"val0.asinh");
      val1.debug(L"val1.asinh");              
      return Error::handle(name(), L"asinh", Error::TEST, __FILE__, __LINE__);
    }

    
    // test cos/acos
    //
    num0 = (TIntegral)(Integral::PI / 3);
    num1 = (TIntegral)0.5;
    val0.assign(num0);
    val2.assign(num1);
    
    val1.cos(val0);
    
    if (!val1.almostEqual(val2)) {
      return Error::handle(TVector::name(), L"cos",
			   Error::TEST, __FILE__, __LINE__);
    }
    
    val1.acos();
    if (!val0.almostEqual(val1)) {
      return Error::handle(TVector::name(), L"acos",
			   Error::TEST, __FILE__, __LINE__);
    }
    
    // test acosh / cosh
    //
    val0.assign((TIntegral)(Integral::PI / (float64)3));
    val1.cosh(val0);
    val1.acosh();    
    if (!val0.almostEqual(val1)) {
      val0.debug(L"val0.acosh");
      val1.debug(L"val1.acosh");      
      return Error::handle(name(), L"acosh", Error::TEST, __FILE__, __LINE__);
    }
    
    // test tan/atan
    //
    num0 = (TIntegral)(Integral::QUARTER_PI);
    num1 = (TIntegral)1.0;
    val0.assign(num0);
    val2.assign(num1);
    
    val1.tan(val0);
    
    if (!val1.almostEqual(val2)) {
      return Error::handle(TVector::name(), L"tan",
			   Error::TEST, __FILE__, __LINE__);
    }
    
    val1.atan();
    if (!val0.almostEqual(val1)) {
      return Error::handle(TVector::name(), L"atan",
			   Error::TEST, __FILE__, __LINE__);
    }

    // test atanh /tanh
    //
    val0.assign((TIntegral)(Integral::QUARTER_PI));    
    val1.tanh(val0);
    val1.atanh();    
    if (!val0.almostEqual(val1)) {
      val0.debug(L"val0.atanh");
      val1.debug(L"val1.atanh");              
      return Error::handle(name(), L"atanh", Error::TEST, __FILE__, __LINE__);
    }
  }

  // testing vector to scalar mathematical methods
  //
  val0.assign(L"-1, 3, 5, 7, -9");
  TScalar new_value;
  
  new_value = val0.sum();
  if (!new_value.almostEqual((TIntegral)5)) {
    return Error::handle(TVector::name(), L"sum",
			 Error::TEST, __FILE__, __LINE__);
  }
  
  new_value = val0.sumSquare();
  if (!new_value.almostEqual((TIntegral)165)) {
    return Error::handle(TVector::name(), L"sumSquare",
			 Error::TEST, __FILE__, __LINE__);
  }
  
  new_value = val0.mean();
  if (!new_value.almostEqual((TIntegral)1)) {
    return Error::handle(TVector::name(), L"mean",
			 Error::TEST, __FILE__, __LINE__);
  }

  // test median for a vector of odd length
  //
  TVector val_ss;
  val_ss.assign(L"1, 3, 9, 6, 7");
  
  new_value = val_ss.median();

  if (!new_value.almostEqual((TIntegral)6)) {
    val_ss.debug(L"vector");
    new_value.debug(L"new_value");
    return Error::handle(TVector::name(), L"median",
			 Error::TEST, __FILE__, __LINE__);
  }

  // test median for an even vector
  //
  val_ss.assign(L"1, 3, 4, 6, 7, 9");
  new_value = val_ss.median();
    
  if (!new_value.almostEqual((TIntegral)5)) {
    val_ss.debug(L"vector");
    new_value.debug(L"new_value");
    return Error::handle(TVector::name(), L"median",
			 Error::TEST, __FILE__, __LINE__);
  }
  
  new_value = val0.rms() + (TIntegral)0.4;
  if (!new_value.almostEqual((TIntegral)6.144562647)) {
    val0.debug(L"val0");
    new_value.debug(L"rms");
    return Error::handle(TVector::name(), L"rms",
			 Error::TEST, __FILE__, __LINE__);
  }
  
  new_value = val0.var();
  if (!new_value.almostEqual((TIntegral)32)) {
    return Error::handle(TVector::name(), L"var",
			 Error::TEST, __FILE__, __LINE__);
  }
  
  new_value = val0.stdev() + (TIntegral)0.4;
  if (!new_value.almostEqual((TIntegral)6.05685424949238058)) {
    val0.debug(L"val0");
    new_value.debug(L"stdevcl");
    return Error::handle(TVector::name(), L"stdev",
			 Error::TEST, __FILE__, __LINE__);
  }
  
  new_value = val0.dotProduct(val0);    
  if (!new_value.almostEqual((TIntegral)165)) {
    return Error::handle(TVector::name(), L"dotProduct ",
			 Error::TEST, __FILE__, __LINE__);
  }
  
  new_value = val0.norm();

  if (!new_value.almostEqual((TIntegral)12.8452)) {
    new_value.debug(L"norm");
    return Error::handle(TVector::name(), L"norm",
			 Error::TEST, __FILE__, __LINE__);
  }
  
  val1.assign(L"1, 5, 5, 5, -7");
  
  new_value = val0.distance(val1);
  if (!new_value.almostEqual((TIntegral)4.0000)) {
    new_value.debug(L"distance");
    return Error::handle(TVector::name(), L"distance",
			 Error::TEST, __FILE__, __LINE__);
  }
  
  new_value = val0.distanceSquare(val1);
  if (!new_value.almostEqual((TIntegral)16)) {
    new_value.debug(L"distanceSquare");
    return Error::handle(TVector::name(), L"distanceSquare ",
			 Error::TEST, __FILE__, __LINE__);
  }
  
  int32 count = val0.numNotEqual(3);
  if (count != 4) {
    return Error::handle(TVector::name(), L"numNotEqual",
			 Error::TEST, __FILE__, __LINE__);
  }
  
  count = val0.numEqual(3);
  if (count != 1) {
    return Error::handle(TVector::name(), L"numNotEqual",
			 Error::TEST, __FILE__, __LINE__);
  }

  //---------------------------------------------------------------------------
  //
  // testing vector to scalar mathematical methods for complex numbers
  //
  //---------------------------------------------------------------------------

#ifdef ISIP_TEMPLATE_complex

  val0.assign(L"-1-3j, 3+2j, 5+7j, 7+4j, -9-8j");
  
  new_value = val0.dotProduct(val0);    
  if (!new_value.almostEqual(TIntegral(307, 0))) {
    return Error::handle(TVector::name(), L"dotProduct ",
			 Error::TEST, __FILE__, __LINE__);
  }

  val1.assign(L"2+4j, -4-5j, 7+2j, 6+0j, -3+4j");
  new_value = val0.dotProduct(val1);
  if (!new_value.almostEqual(TIntegral(50, -128))) {
    return Error::handle(TVector::name(), L"dotProduct ",
			 Error::TEST, __FILE__, __LINE__);
  }
#endif
  
  // exit gracefully
  //
  return true;
}

// method: diagnose7
//
// arguments:
//  Integral::DEBUG level: (input) debug level for diagnostics
//
// return: a bool8 value indicating status
//
// this method tests sign and dsp related methods 
//
template<class TVector, class TScalar, class TIntegral>
bool8 MVectorMethods::diagnose7(Integral::DEBUG level_a) {

  // declare local variables
  //
  TVector val0;
  val0.assign(L"1, 3, 5, 7, 9");
  TVector val1;
  val1.assign(L"0, 2, 4, 6, 8");
  
  TVector val2;
  
  // if the type is signed, test sign-specific functions
  //
  if ((typeid(TIntegral) != typeid(uint16)) &&
      (typeid(TIntegral) != typeid(uint32)) &&
      (typeid(TIntegral) != typeid(uint64)) &&
      (typeid(TIntegral) != typeid(byte8))) {
    
    if (level_a > Integral::BRIEF) {
      Console::put(L"testing signed mathematical methods:\n");
    }
    
    // use these vectors for testing
    //
    val0.assign((TIntegral)-44);
    val1.assign((TIntegral)200);

#ifndef ISIP_TEMPLATE_complex 
    // test abs
    //
    val2.abs(val0);
    if (!val2.almostEqual((TIntegral)44)) {
      val2.debug(L"val2");
      val0.debug(L"val0");      
      return Error::handle(TVector::name(), L"abs",
			   Error::TEST, __FILE__, __LINE__);
    }
    
    val2.abs(val1);
    if (!val2.almostEqual((TIntegral)200)) {
      return Error::handle(TVector::name(), L"abs",
			   Error::TEST, __FILE__, __LINE__);
    }
    
    // test sign
    //
    val2.sign(val0);
    if (!val2.almostEqual((TIntegral)-1)) {
      return Error::handle(TVector::name(), L"sign",
			   Error::TEST, __FILE__, __LINE__);
    }
#endif
    
    val2.sign(val1);
    if (!val2.almostEqual((TIntegral)1)) {
      return Error::handle(TVector::name(), L"sign",
			   Error::TEST, __FILE__, __LINE__);
    }
    
    // test neg
    //
    val2.neg(val0);
    if (!val2.almostEqual((TIntegral)44)) {
      return Error::handle(TVector::name(), L"neg",
			   Error::TEST, __FILE__, __LINE__);
    }
    
    val2.neg(val1);
    if (!val2.almostEqual((TIntegral)-200)) {
      return Error::handle(TVector::name(), L"neg",
			   Error::TEST, __FILE__, __LINE__);
    }
    
    // test mins and maxes (signed version)
    //
    if (level_a > Integral::BRIEF) {
      Console::put(L"testing mins and maxes (signed):\n");
    }
    
    // test min, minMag, max, maxMag
    //
    val0.assign(L"-1, 3, 5, 7, -9");
    
    int32 pos = 0;
    TIntegral min = 0;
    TIntegral max = 0;
    float64 min_mag = 0;
    float64 max_mag = 0;
    
    // test min
    //
    min = val0.min(pos);
#ifndef ISIP_TEMPLATE_complex    
    if ((min != (TIntegral)-9) || (pos != 4)) {
      return Error::handle(TVector::name(), L"min",
			   Error::TEST, __FILE__, __LINE__);
    }
#endif
    
    // test minMag
    //
    min_mag = val0.minMag(pos);
    if ((min_mag != (float64)1) || (pos != 0)) {
      return Error::handle(TVector::name(), L"minMag",
			   Error::TEST, __FILE__, __LINE__);
    }
    
    // test max
    //
    max = val0.max(pos);
#ifndef ISIP_TEMPLATE_complex        
    if ((max != (TIntegral)7) || (pos != 3)) {
      return Error::handle(TVector::name(), L"max",
			   Error::TEST, __FILE__, __LINE__);
    }
#endif
    
    // test maxMag
    //
    max_mag = val0.maxMag(pos);
    if ((max_mag != (float64)9) || (pos != 4)) {
      return Error::handle(TVector::name(), L"maxMag",
			   Error::TEST, __FILE__, __LINE__);
    }
    
#ifndef ISIP_TEMPLATE_complex
    // test DSP functions (signed version)
    //
    if (level_a > Integral::BRIEF) {
      Console::put(L"testing DSP methods (signed):\n");
    }
    
    // test limit
    //
    val2.setLength((int32)5);
    val2.limit(1, 7, val0);
    val1.assign(L"1, 3, 5, 7, 1");
    if (val2.ne(val1)) {
      val2.debug(L"limit");
      val1.debug(L"limit");      
      return Error::handle(TVector::name(), L"limit",
			   Error::TEST, __FILE__, __LINE__);
    }
    
    // test limitMin
    //
    val2.limitMin((TIntegral)3, val0);
    val1.assign(L"3, 3, 5, 7, 3");
    if (val2.ne(val1)) {
      val2.debug(L"limitMin");
      return Error::handle(TVector::name(), L"limitMin",
			   Error::TEST, __FILE__, __LINE__);
    }
    
    // test limitMax
    //
    val2.limitMax((TIntegral)5, val0);
    val1.assign(L"-1, 3, 5, 5, -9");
    if (val2.ne(val1)) {
      val2.debug(L"limitMax");
      return Error::handle(TVector::name(), L"limitMax",
			   Error::TEST, __FILE__, __LINE__);
    }
    
    val2.limitMag((TIntegral)5, (TIntegral)-1, val0);
    val1.assign(L"-1, 3, -1, -1, -1");
    if (val2.ne(val1)) {
      val2.debug(L"limitMag");
      return Error::handle(TVector::name(), L"limitMag",
			   Error::TEST, __FILE__, __LINE__);
    }
    
    // test centerClip
    //
    //
    if ((typeid(TIntegral) == typeid(float32)) ||
	(typeid(TIntegral) == typeid(float64))) {    
      val2.centerClip((TIntegral)0, (TIntegral)8, val0);
      val1.assign(L"-1, 0, 8, 8, -9");
      if (val2.ne(val1)) {
	val2.debug(L"centerclip");
	return Error::handle(TVector::name(), L"centerClip",
			     Error::TEST, __FILE__, __LINE__);
      }
    }
#endif
  }

  // do unsigned-specific testing
  //
  else {
    
    // test DSP functions (unsigned version)
    //
    if (level_a > Integral::BRIEF) {
      Console::put(L"testing DSP methods (unsigned):\n");
    }
    
    // use these vectors for testing
    //
    val0.assign((TIntegral)44);
    val1.assign((TIntegral)200);

    // test mins and maxes (unsigned version)
    //
    if (level_a > Integral::BRIEF) {
      Console::put(L"testing mins and maxes (unsigned):\n");
    }
    
    // test min, minMag, max, maxMag
    //
    val0.assign(L"1, 3, 5, 7, 27");
    int32 pos = 0;
    TIntegral min = 0;
    TIntegral max = 0;
    float64 min_mag = 0;
    float64 max_mag = 0;
    
    // test min
    //
    min = val0.min(pos);
    if ((min != (TIntegral)1) || (pos != 0)) {
      return Error::handle(TVector::name(), L"min",
			   Error::TEST, __FILE__, __LINE__);
    }
    
    // test minMag
    //
    min_mag = val0.minMag(pos);
    if ((min_mag != (float64)1) || (pos != 0)) {
      return Error::handle(TVector::name(), L"minMag",
			   Error::TEST, __FILE__, __LINE__);
    }
    
    // test max
    //
    max = val0.max(pos);
    if ((max != (TIntegral)27) || (pos != 4)) {
      return Error::handle(TVector::name(), L"max",
			   Error::TEST, __FILE__, __LINE__);
    }
    
    // test maxMag
    //
    max_mag = val0.maxMag(pos);
    if ((max_mag != (float64)27) || (pos != 4)) {
      return Error::handle(TVector::name(), L"maxMag",
			   Error::TEST, __FILE__, __LINE__);
    }

#ifndef ISIP_TEMPLATE_complex
    // test DSP functions (unsigned version)
    //
    if (level_a > Integral::BRIEF) {
      Console::put(L"testing DSP methods (unsigned):\n");
    }
    
    val2.assign(L"1, 3, 5, 7, 27");
    
    // test limit
    //
    val2.limit(1, 7, val0);
    val1.assign(L"1, 3, 5, 7, 7");
    if (val2.ne(val1)) {
      val2.debug(L"limit");
      val1.debug(L"limit");
      return Error::handle(TVector::name(), L"limit",
			   Error::TEST, __FILE__, __LINE__);
    }
    
    // test limitMin
    //
    val2.limitMin((TIntegral)3, val0);
    val1.assign(L"3, 3, 5, 7, 27");
    if (val2.ne(val1)) {
      val2.debug(L"limitMin");
      return Error::handle(TVector::name(), L"limit",
			   Error::TEST, __FILE__, __LINE__);
    }
    
    // test limitMax
    //
    val2.limitMax((TIntegral)5, val0);
    val1.assign(L"1, 3, 5, 5, 5");
    if (val2.ne(val1)) {
      val2.debug(L"limitMax");
      return Error::handle(TVector::name(), L"limitMax",
			   Error::TEST, __FILE__, __LINE__);
    }
    
    val2.limitMag((TIntegral)5, (TIntegral)200, val0);
    val1.assign(L"1, 3, 200, 200, 200");
    if (val2.ne(val1)) {
      val2.debug(L"limitmag");
      return Error::handle(TVector::name(), L"limitMag",
			   Error::TEST, __FILE__, __LINE__);
    }
    
    // test centerClip
    //
    if ((typeid(TIntegral) == typeid(float32)) &&
	(typeid(TIntegral) == typeid(float64))) {      
      val2.centerClip((TIntegral)0, (TIntegral)8, val0);
      val1.assign(L"0, 0, 8, 8, 27");
      if (val2.ne(val1)) {
	val2.debug(L"centerclip");
	return Error::handle(TVector::name(), L"centerClip",
			     Error::TEST, __FILE__, __LINE__);
      }
    }
#endif
    
  }

  // test random number generation methods
  //
  if (level_a > Integral::BRIEF) {
    Console::put(L"testing rand methods:\n");
  }

  // test rand
  //
  val0.rand();
  val0.rand((TIntegral)3, (TIntegral)20);
  if (val0.lt((TIntegral)3) || val0.gt((TIntegral)20)) {
    return Error::handle(TVector::name(), L"rand",
			 Error::TEST, __FILE__, __LINE__);
  }

  // test grand: a simple test simply to make sure it doesn't crash
  //
  TIntegral mean = 10;
  TIntegral stvar = 2;
  val0.grand(mean, stvar);
  
  // exit gracefully
  //
  return true;
}

// method: diagnose8
//
// arguments:
//  Integral::DEBUG level: (input) debug level for diagnostics
//
// return: a bool8 value indicating status
//
// this method tests position operation and search methods
//
template<class TVector, class TScalar, class TIntegral>
bool8 MVectorMethods::diagnose8(Integral::DEBUG level_a) {

  // declare local variables
  //
  int32 num_elem = 5;

  // test constructors
  //
  TVector val0;
  TVector val1(num_elem);
  
  val0.assign(L"1, 3, 5, 7, 9");
  val1.assign(L"0, 2, 4, 6, 8");
  
  // assign values
  //
  val0.setLength(num_elem);
  val0.assign((TIntegral)0);
  val1.assign(L"40, 41, 42, 43, 44");
  
  // move 4 elements starting from the 2nd element in val1, put into val0
  // starting from 2nd element, val0 will be resized
  // 
  val0.move(val1, 4, 1, 1);
  
  TVector result;
  result.assign(L"0, 41, 42, 43, 44");
  
  if (val0.ne(result)) {
    val0.debug(L"move ->");
    return Error::handle(TVector::name(), L"move",
			 Error::TEST, __FILE__, __LINE__);
  }
  
  // move 2 elements starting from the 1st element
  // in val1, put into val0 starting from 0st element
  //
  val0.move(val1, 2, 1, 0);  
  result.assign(L"41, 42, 42, 43, 44");
  
  if (val0.ne(result)) {
    val0.debug(L"move ->");
    return Error::handle(TVector::name(), L"move",
			 Error::TEST, __FILE__, __LINE__);
  } 
  
  // test shift
  //
  val0.assign(L"43, 43, 0, 0, 0");
  val0.shift(2);
  result.assign(L"0, 0, 43, 43, 0");
  
  if (val0.ne(result)) {
    return Error::handle(TVector::name(), L"shift right",
			 Error::TEST, __FILE__, __LINE__);
  }
  
  val0.shift(-1);
  result.assign(L"0, 43, 43, 0, 0");
  
  if (val0.ne(result)) {
    return Error::handle(TVector::name(), L"shift left",
			 Error::TEST, __FILE__, __LINE__);
  }
  
  // test concat
  //
  val0.assign((int32)2, (TIntegral)0);
  val1.setLength(3);
  val0.concat(val1);
  
  result.assign(L"0, 0, 40, 41, 42");
  if (val0.ne(result)) {
    return Error::handle(TVector::name(), L"concat",
			 Error::TEST, __FILE__, __LINE__);
  }
  
  // test deleteRange for deleting from the start
  //
  val0.assign(L"0, 1, 2, 3, 4, 5, 6, 7, 8, 9");
  val0.deleteRange(0, 3);
  result.assign(L"3, 4, 5, 6, 7, 8, 9");

  if (result.ne(val0)) {
    return Error::handle(TVector::name(), L"deleteRange",
			 Error::TEST, __FILE__, __LINE__);
  }
  
  // test deleteRange for deleting from the middle
  //
  val0.assign(L"0, 1, 2, 3, 4, 5, 6, 7, 8, 9");
  val0.deleteRange(2, 3);
  result.assign(L"0, 1, 5, 6, 7, 8, 9");

  if (result.ne(val0)) {
    return Error::handle(TVector::name(), L"deleteRange",
			 Error::TEST, __FILE__, __LINE__);
  }
  
  // test deleteRange for deleting from the end
  //
  val0.assign(L"0, 1, 2, 3, 4, 5, 6, 7, 8, 9");
  val0.deleteRange(6, 4);
  result.assign(L"0, 1, 2, 3, 4, 5");

  if (result.ne(val0)) {
    return Error::handle(TVector::name(), L"deleteRange",
			 Error::TEST, __FILE__, __LINE__);
  }

  // test deleteRange for deleting from the start
  //
  val0.assign(L"0, 1, 2, 3, 4, 5, 6, 7, 8, 9");
  val1.deleteRange(val0, 0, 3);
  result.assign(L"3, 4, 5, 6, 7, 8, 9");

  if (result.ne(val1)) {
    return Error::handle(TVector::name(), L"deleteRange",
			 Error::TEST, __FILE__, __LINE__);
  }
  
  // test deleteRange for deleting from the middle
  //
  val0.assign(L"0, 1, 2, 3, 4, 5, 6, 7, 8, 9");
  val1.deleteRange(val0, 2, 3);
  result.assign(L"0, 1, 5, 6, 7, 8, 9");

  if (result.ne(val1)) {
    return Error::handle(TVector::name(), L"deleteRange",
			 Error::TEST, __FILE__, __LINE__);
  }
  
  // test deleteRange for deleting from the end
  //
  val0.assign(L"0, 1, 2, 3, 4, 5, 6, 7, 8, 9");
  val1.deleteRange(val0, 6, 4);
  result.assign(L"0, 1, 2, 3, 4, 5");

  if (result.ne(val1)) {
    return Error::handle(TVector::name(), L"deleteRange",
			 Error::TEST, __FILE__, __LINE__);
  }

  // test setRange for setting from the start
  //
  val0.assign(L"0, 1, 2, 3, 4, 5");
  val0.setRange(0, 3, 7);
  result.assign(L"7, 7, 7, 3, 4, 5");

  if (result.ne(val0)) {
    val0.debug(L"output vector");
    result.debug(L"result vector");
    return Error::handle(TVector::name(), L"setRange",
			 Error::TEST, __FILE__, __LINE__);
  }
  
  // test setRange for setting from the middle
  //
  val0.assign(L"0, 1, 2, 3, 4, 5");
  val0.setRange(2, 3, 7);
  result.assign(L"0, 1, 7, 7, 7, 5");

  if (result.ne(val0)) {
    val0.debug(L"output vector");
    result.debug(L"result vector");    
    return Error::handle(TVector::name(), L"setRange",
			 Error::TEST, __FILE__, __LINE__);
  }
  
  // test setRange for setting from the end
  //
  val0.assign(L"0, 1, 2, 3, 4, 5");
  val0.setRange(5, 1, 7);
  result.assign(L"0, 1, 2, 3, 4, 7");

  if (result.ne(val0)) {
    val0.debug(L"output vector");
    result.debug(L"result vector");    
    return Error::handle(TVector::name(), L"setRange",
			 Error::TEST, __FILE__, __LINE__);
  }
 
  // find the first matching element a few times
  //
  int32 pos = 0;
  val1.assign(L"2, 3, 20, 3, 15, 32, 6, 2, 3, 2, 7");
  pos = val1.first((TIntegral)3);
  if (pos != 1) {
    return Error::handle(TVector::name(), L"first",
			 Error::TEST, __FILE__, __LINE__);
  }
  
  pos = val1.first((TIntegral)3, pos + 1);
  if (pos != 3) {
    return Error::handle(TVector::name(), L"first",
			 Error::TEST, __FILE__, __LINE__);
  }
  
  pos = val1.first((TIntegral)3, pos + 1);
  if (pos != 8) {
    return Error::handle(TVector::name(), L"first",
			 Error::TEST, __FILE__, __LINE__);
  }
  
  pos = val1.first((TIntegral)3, pos + 1);
  if (pos != Integral::NO_POS) {
    return Error::handle(TVector::name(), L"first",
			 Error::TEST, __FILE__, __LINE__);
  }
  
  // find the last matching element a few times
  //
  pos = val1.last((int32)2);
  if (pos != 9) {
    return Error::handle(TVector::name(), L"last",
			 Error::TEST, __FILE__, __LINE__);
  }
  
  pos = val1.last((int32)2, pos - 1);
  if (pos != 7) {
    return Error::handle(TVector::name(), L"last",
			 Error::TEST, __FILE__, __LINE__);
  }
  
  pos = val1.last((int32)2, pos - 1);
  if (pos != 0) {
    return Error::handle(TVector::name(), L"last",
			 Error::TEST, __FILE__, __LINE__);
  }
  
  // ordering / sorting
  //
  if (level_a > Integral::BRIEF) {
    Console::put(L"testing reorder methods\n");
  }
  
  MVector<Long, int32> order_vector;
  order_vector.assign(L"1, 2, 4, 0, 3");
  
  val0.assign(L"1, 3, 5, 7, 9");
  
  val0.reorder(order_vector);
  val1.assign(L"3, 5, 9, 1, 7");
  
  if (val0.ne(val1)) {
    return Error::handle(TVector::name(), L"reorder",
			 Error::TEST, __FILE__, __LINE__);
  }
  
  val0.clear();
  order_vector.clear();
  order_vector.setLength(1000);
  val0.setLength(1000);
  
  TVector val0a;

  val0.rand();
  val0a.assign(val0);
  val0a.sort();
 
  val0.index(order_vector);
  val0.reorder(order_vector);
  
  if (!val0.eq(val0a)) {
    val0a.debug(L"index/reorder");
    return Error::handle(TVector::name(), L"index/reorder",
			 Error::TEST, __FILE__, __LINE__);
  }
  val0a.clear();
  val0.clear();
  
  // ordering / sorting
  //
  if (level_a > Integral::BRIEF) {
    Console::put(L"testing reverse methods\n");
  }
  
  val0.assign(L"1, 7, 6, 5, 4, 12");  
  val0.reverse();
  val1.assign(L"12, 4, 5, 6, 7,1"); 
  if (val0.ne(val1)) {
    return Error::handle(TVector::name(), L"reverse",
			 Error::TEST, __FILE__, __LINE__);
  }

  
  // test the randperm method
  //
  // create a random permuation of the first 20 integers and make sure
  // all exist in the resultant vector
  //
  MVector<Long, int32> perm;
  MVector<Long, int32> marker_vec(20);
  marker_vec.assign((int32)-1);
  perm.randperm(20);

  // loop through and find all indices
  //
  for (int32 i = 0; i < 20; i++) {
    marker_vec((int32)(perm(i))) = 0;
  }

  // loop and make sure all indices were accounted for
  //
  for (int32 i = 0; i < 20; i++) {
    if ((int32)(marker_vec(i)) != 0) {
      perm.debug(L"randperm");
      return Error::handle(TVector::name(), L"randperm",
			   Error::TEST, __FILE__, __LINE__);
    }
  }   
  
  // exit gracefully
  //
  return true;
}

// method: diagnose9
//
// arguments:
//  Integral::DEBUG level: (input) debug level for diagnostics
//
// return: a bool8 value indicating status
//
// this method tests some methods - these need to test separately for
// complex types
//
template<class TVector, class TScalar, class TIntegral>
bool8 MVectorMethods::diagnose9(Integral::DEBUG level_a) {

  // declare local variables
  //
  TVector val_0(5);
  TVector val_1(5);
  TVector val_2(5);  
  
  // addition
  //
  val_1.assign((TIntegral)complexdouble(40, 25));
  val_0.add(val_1, (TIntegral)complexdouble(5, 20));
  val_0.add((TIntegral)complexdouble(1, 1));
  
  if (!val_0.almostEqual((TIntegral)complexdouble(46, 46))) {
    return Error::handle(TVector::name(), L"add",
			 Error::TEST, __FILE__, __LINE__);
  }

  val_1.assign((TIntegral)complexdouble(10, 10));
  val_0.add(val_1);
  val_0.add((TIntegral)complexdouble(7, 7));
  
  if (!val_0.almostEqual((TIntegral)complexdouble(63, 63))) {
    return Error::handle(TVector::name(), L"add",
			 Error::TEST, __FILE__, __LINE__);
  }
  
  // subtraction
  //
  val_1.assign((TIntegral)complexdouble(10, 10));
  val_0.sub(val_1);
  val_0.sub((TIntegral)complexdouble(7, 7));
  
  if (!val_0.almostEqual((TIntegral)complexdouble(46, 46))) {
    return Error::handle(TVector::name(), L"sub",
			 Error::TEST, __FILE__, __LINE__);
  }
  
  // multiplication
  //
  val_1.assign((TIntegral)complexdouble(2, 2));
  val_0.mult(val_1);
  val_0.mult((TIntegral)complexdouble(2, 2));
  if (!val_0.almostEqual((TIntegral)complexdouble(-368, 368))) {
    val_0.debug(L"val_0.mult");  
    val_1.debug(L"val_0.mult");      
    return Error::handle(TVector::name(), L"mult",
    			 Error::TEST, __FILE__, __LINE__);
  }
  
  // division
  //
  val_1.assign((TIntegral)complexdouble(2, 2));
  val_0.div(val_1);
  val_0.div(complexdouble(2, 2));
  if (!val_0.almostEqual((TIntegral)complexdouble(46, 46))) {
    val_0.debug(L"val_0.div");  
    val_1.debug(L"val_1.div");    
    return Error::handle(TVector::name(), L"div",
			 Error::TEST, __FILE__, __LINE__);
  }
  
  for (int32 i = 0; i < 5; i++) {
    val_0(i) = (TIntegral)(complexlong(i + 1, i));
  }

  if (typeid(TIntegral) != typeid(complexlong)) {
    // test log/exp
    //
    val_1.log(val_0);
    if (!val_1(3).almostEqual((TIntegral)complexdouble(1.60944, 0.643501))) {
      val_1.debug(L"log");
      return Error::handle(name(), L"log", Error::TEST, __FILE__, __LINE__);
    }

    val_1.log(val_0);
    val_1.exp();
    if (!val_0.almostEqual(val_1)) {
      val_1.debug(L"exp");
      return Error::handle(name(), L"exp", Error::TEST, __FILE__, __LINE__);
    }
    
    // test log1p
    //
    val_1.log1p(val_0);
    if (!val_1(3).almostEqual((TIntegral)complexdouble(1.76318, 0.54042))) {
      val_1.debug(L"log");
      return Error::handle(name(), L"log1p", Error::TEST, __FILE__, __LINE__);
    }
    
    // test log2/exp2
    //
    val_1.log2(val_0);
    if (!val_1(3).almostEqual((TIntegral)complexdouble(2.32193, 0.928376))) {
      val_1.debug(L"log");
      return Error::handle(name(), L"log2", Error::TEST, __FILE__, __LINE__);
    }

    val_1.log2(val_0);
    val_1.exp2();
    if (!val_0.almostEqual(val_1)) {
      val_1.debug(L"exp2 test");
      return Error::handle(name(), L"exp2", Error::TEST, __FILE__, __LINE__);
    }
    
    // test log10/exp10
    //
    val_1.log10(val_0);
    if (!val_1(3).almostEqual((TIntegral)complexdouble(0.69897, 0.279469))) {
      val_1.debug(L"log");
      return Error::handle(name(), L"log10", Error::TEST, __FILE__, __LINE__);
    }

    val_1.log10(val_0);
    val_1.exp10();
    if (!val_0.almostEqual(val_1)) {
      val_1.debug(L"exp10 test");
      return Error::handle(name(), L"exp10", Error::TEST, __FILE__, __LINE__);
    }
    
    // test square root
    //
    val_1.assign ((TIntegral)complexdouble(3.3, 4.3));
    val_2.sqrt(val_1);
    if (!val_2.almostEqual((TIntegral)complexdouble(2.0881, 1.02964))) {
      val_2.debug(L"sqrt");
      return Error::handle(name(), L"sqrt", Error::TEST, __FILE__, __LINE__);
    }
	
    // test inverse
    //
    val_1.assign((TIntegral)complexdouble(4, 3));
    val_1.inverse();
    if (!val_1.almostEqual((TIntegral)complexdouble(0.16, -0.12))) {
      return Error::handle(name(), L"inverse", Error::TEST, __FILE__,
			   __LINE__);
    }
    
    // test rceil
    //
    val_0.assign ((TIntegral)complexdouble(3.3, 4.3));
    val_2.rceil(val_0);
    if (!val_2.almostEqual((TIntegral)complexdouble(0.7, 0.7))) {
      val_2.debug(L"rceil");
      return Error::handle(name(), L"rceil", Error::TEST, __FILE__, __LINE__);
    }
  
    // test rfloor
    //
    val_2.rfloor(val_0);
    if (!val_2.almostEqual((TIntegral)complexdouble(-0.3, -0.3))) {
      val_2.debug(L"rfloor");
      return Error::handle(name(), L"rfloor", Error::TEST, __FILE__, __LINE__);
    }
  
    // test round
    //
    val_2.round(val_0);
    if (!val_2.almostEqual((TIntegral)complexdouble(3, 4))) {
      val_2.debug(L"round");
      return Error::handle(name(), L"round", Error::TEST, __FILE__, __LINE__);
    }
    
    // test sign
    //
    val_2.sign(val_0);
    if (!val_2.almostEqual((TIntegral)complexdouble(1, 0))) {
      val_2.debug(L"sign");
      return Error::handle(name(), L"sign", Error::TEST, __FILE__, __LINE__);
    }
  
    // test sin
    //
    val_0.assign((TIntegral)complexdouble(Integral::PI / (float64)6, 0.5));
    val_1.sin(val_0);
    if (!val_1.almostEqual((TIntegral)complexdouble(0.5638, 0.4513))) {
      val_1.debug(L"sin");
      return Error::handle(name(), L"sin", Error::TEST, __FILE__, __LINE__);
    }

    // test sinh
    //
    val_1.assign((TIntegral)complexdouble(Integral::PI / (float64)6, 0.5));  
    val_2.sinh(val_1);
    if (!val_2.almostEqual((TIntegral)complexdouble(0.4808, 0.5467)))  {
      val_1.debug(L"val_1.sinh");
      val_2.debug(L"val_2.sinh");    
      return Error::handle(name(), L"sinh", Error::TEST, __FILE__, __LINE__);
    }
    
    // test asin
    //
    val_0.assign((TIntegral)complexdouble(Integral::PI / (float64)6, 0.5));
    val_1.sin(val_0);
    val_1.asin();
    if (!val_0.almostEqual(val_1)) {
      val_0.debug(L"val_0.asin");
      val_1.debug(L"val_1.asin");          
      return Error::handle(name(), L"asin", Error::TEST, __FILE__, __LINE__);
    }
    
    // test asinh
    //
    val_0.assign((TIntegral)complexdouble(Integral::PI / (float64)6, 0.5));    
    val_1.sinh(val_0);
    val_1.asinh();    
    if (!val_0.almostEqual(val_1)) {
      val_0.debug(L"val_0.asinh");
      val_1.debug(L"val_1.asinh");              
      return Error::handle(name(), L"asinh", Error::TEST, __FILE__, __LINE__);
    }
    
    // test cos
    //
    val_0.assign((TIntegral)complexdouble(Integral::PI / (float64)3, 0.5));
    val_1.cos(val_0);
    if (!val_1.almostEqual((TIntegral)complexdouble(0.5638, -0.4513))) {
      val_0.debug(L"val_0.cos");
      val_1.debug(L"val_1.cos");                  
      return Error::handle(name(), L"cos", Error::TEST, __FILE__, __LINE__);
    }
    
    // test cosh
    //
    val_0.assign((TIntegral)complexdouble(Integral::PI / (float64)3, 0.5));
    val_1.cosh(val_0);
    if (!val_1.almostEqual((TIntegral)complexdouble(1.404, 0.599))) {
      val_0.debug(L"val_0.cosh");
      val_1.debug(L"val_1.cosh");                      
      return Error::handle(name(), L"cosh", Error::TEST, __FILE__, __LINE__);
    }

    // test acos
    //    
    val_0.assign((TIntegral)complexdouble((Integral::PI / 3), 0.5));
    val_1.cos(val_0);
    val_1.acos();
    if (!val_0.almostEqual(val_1)) {
      val_0.debug(L"val_0.acos");
      val_1.debug(L"val_1.acos");      
      return Error::handle(name(), L"acos", Error::TEST, __FILE__, __LINE__);
    }

    // test acosh
    //
    val_0.assign((TIntegral)complexdouble(Integral::PI / 3, 0.5));
    val_1.cosh(val_0);
    val_1.acosh();
    if (!val_0.almostEqual(val_1)) {
      val_0.debug(L"val_0.acosh");
      val_1.debug(L"val_1.acosh");      
      return Error::handle(name(), L"acosh", Error::TEST, __FILE__, __LINE__);
    }
    
    // test tan
    //
    val_0.assign((TIntegral)complexdouble(Integral::QUARTER_PI, 0.5));
    val_1.tan(val_0);
    if (!val_1.almostEqual((TIntegral)complexdouble(0.648, 0.7616))) {
      val_1.debug(L"tan");      
      return Error::handle(name(), L"tan", Error::TEST, __FILE__, __LINE__);
    }

    // test atan
    //
    val_0.assign((TIntegral)complexdouble(Integral::QUARTER_PI, 0.5));    
    val_1.tan(val_0);
    val_1.atan();    
    if (!val_0.almostEqual(val_1)) {
      val_0.debug(L"val_0.atan");
      val_1.debug(L"val_1.atan");              
      return Error::handle(name(), L"atan", Error::TEST, __FILE__, __LINE__);
    }
    
    // test atanh / tanh
    //
    val_0.assign((TIntegral)complexdouble(Integral::QUARTER_PI, 0.5));        
    val_1.tanh(val_0);
    val_1.atanh();    
    if (!val_0.almostEqual(val_1)) {
      val_0.debug(L"val_0.atanh");
      val_1.debug(L"val_1.atanh");              
      return Error::handle(name(), L"atanh", Error::TEST, __FILE__, __LINE__);
    }
  }
  
  // test square
  //
  val_0.assign ((TIntegral)complexdouble(3, 4));
  val_2.square(val_0);
  if (!val_2.almostEqual((TIntegral)complexdouble(-7, 24))) {
    val_2.debug(L"square");
    return Error::handle(name(), L"square", Error::TEST, __FILE__, __LINE__);
  }
  
  // test neg
  //
  val_2.neg(val_0);
  if (!val_2(3).almostEqual((TIntegral)complexdouble(-3, -4))) {
    val_2.debug(L"neg");
    return Error::handle(name(), L"neg", Error::TEST, __FILE__, __LINE__);
  }
  
  // test pow
  //
  val_0.pow((float64)2);
  if (!val_0(3).almostEqual((TIntegral)complexlong(-7, 24))) {
    val_2.debug(L"pow");
    return Error::handle(name(), L"pow", Error::TEST, __FILE__, __LINE__);
  }
  
  // check relational operations
  //
  val_0.assign((TIntegral)complexdouble(30, 10));
  val_1.assign((TIntegral)complexdouble(43, 20));
  
  if (val_0.gt((TIntegral)complexdouble(42, 9))) {
    return Error::handle(TVector::name(), L"gt", Error::TEST, __FILE__,
			 __LINE__);
  }
  
  if (val_1.lt((TIntegral)complexdouble(42, 20))) {
    return Error::handle(TVector::name(), L"lt", Error::TEST, __FILE__,
			 __LINE__);
  }
  
  if (!val_1.ge((TIntegral)complexdouble(43, 20))) {
    return Error::handle(TVector::name(), L"ge", Error::TEST, __FILE__,
			 __LINE__);
  }
  
  if (val_1.le((TIntegral)complexdouble(42, 20))) {
    return Error::handle(TVector::name(), L"le", Error::TEST, __FILE__,
			 __LINE__);
  }
  
  if (val_0.eq(val_1) || !val_1.eq((TIntegral)complexdouble(43, 20))) {
    return Error::handle(TVector::name(), L"eq", Error::TEST, __FILE__,
			 __LINE__);
  }
  
  if (!val_0.ne(val_1) || val_1.ne((TIntegral)complexdouble(43, 20))) {
    return Error::handle(TVector::name(), L"ne", Error::TEST, __FILE__,
			 __LINE__);
  }

  // test operator ()
  //
  val_0.assign((TIntegral)complexdouble(1, 2));
  if (!val_0(2).almostEqual((TIntegral)complexdouble(1, 2))) {
    return Error::handle(TVector::name(), L"operator()", Error::TEST,
			 __FILE__,  __LINE__);
  }
  
  // declare local variables
  //
  int32 num_elem = 5;
  
  // assign values
  //
  val_0.setLength(num_elem);
  val_0.assign((TIntegral)0);
  val_1.assign(L"40+20j, 41+30j, 42+40j, 43+55j, 44+60j");
  
  // move 4 elements starting from the 2nd element in val_1, put into val_0
  // starting from 2nd element, val_0 will be resized
  // 
  val_0.move(val_1, 4, 1, 1);
  
  TVector result;
  result.assign(L"0+0j, 41+30j, 42+40j, 43+55j, 44+60j");
  
  if (val_0.ne(result)) {
    val_0.debug(L"move ->");
    return Error::handle(TVector::name(), L"move",
			 Error::TEST, __FILE__, __LINE__);
  }
  
  // move 2 elements starting from the 1st element
  // in val_1, put into val_0 starting from 0st element
  //
  val_0.move(val_1, 2, 1, 0);  
  result.assign(L"41+30j, 42+40j, 42+40j, 43+55j, 44+60j");
  
  if (val_0.ne(result)) {
    val_0.debug(L"move ->");
    return Error::handle(TVector::name(), L"move",
			 Error::TEST, __FILE__, __LINE__);
  } 
  
  // test shift
  //
  val_0.assign(L"43+20j, 43+30j, 0+0j, 0+0j, 0+0j");  
  val_0.shift(2);
  result.assign(L"0+0j, 0+0j, 43+20j, 43+30j, 0+0j"); 
  
  if (val_0.ne(result)) {
    return Error::handle(TVector::name(), L"shift right",
			 Error::TEST, __FILE__, __LINE__);
  }
  
  val_0.shift(-1);
  result.assign(L"0+0j, 43+20j, 43+30j, 0+0j, 0+0j"); 
  
  if (val_0.ne(result)) {
    return Error::handle(TVector::name(), L"shift left",
			 Error::TEST, __FILE__, __LINE__);
  }
  
  // test concat
  //
  val_0.assign((int32)2, (TIntegral)0);
  val_1.setLength(3);
  val_0.concat(val_1);
  
  result.assign(L"0+0j, 0+0j, 40+20j, 41+30j, 42+40j"); 
  if (val_0.ne(result)) {
    val_0.debug(L"concat");
    val_1.debug(L"concat");
    result.debug(L"concat");
    return Error::handle(TVector::name(), L"concat",
			 Error::TEST, __FILE__, __LINE__);
  }
  
  // test deleteRange for deleting from the start
  //
  val_0.assign(L"0+1j, 1+2j, 2+3j, 3+4j, 4+5j, 5+6j, 6+7j, 7+8j, 8+9j, 9+8j");
  val_0.deleteRange(0, 3);
  result.assign(L"3+4j, 4+5j, 5+6j, 6+7j, 7+8j, 8+9j, 9+8j");

  if (result.ne(val_0)) {
    return Error::handle(TVector::name(), L"deleteRange",
			 Error::TEST, __FILE__, __LINE__);
  }
  
  // test deleteRange for deleting from the middle
  //
  val_0.assign(L"0+1j, 1+2j, 2+3j, 3+4j, 4+5j, 5+6j, 6+7j, 7+8j, 8+9j, 9+8j");
  val_0.deleteRange(2, 3);
  result.assign(L"0+1j, 1+2j, 5+6j, 6+7j, 7+8j, 8+9j, 9+8j");

  if (result.ne(val_0)) {
    return Error::handle(TVector::name(), L"deleteRange",
			 Error::TEST, __FILE__, __LINE__);
  }
  
  // test deleteRange for deleting from the end
  //
  val_0.assign(L"0+1j, 1+2j, 2+3j, 3+4j, 4+5j, 5+6j, 6+7j, 7+8j, 8+9j, 9+8j");
  val_0.deleteRange(6, 4);
  result.assign(L"0+1j, 1+2j, 2+3j, 3+4j, 4+5j, 5+6j");

  if (result.ne(val_0)) {
    return Error::handle(TVector::name(), L"deleteRange",
			 Error::TEST, __FILE__, __LINE__);
  }

  // test deleteRange for deleting from the start
  //
  val_0.assign(L"0+1j, 1+2j, 2+3j, 3+4j, 4+5j, 5+6j, 6+7j, 7+8j, 8+9j, 9+8j");
  val_1.deleteRange(val_0, 0, 3);
  result.assign(L"3+4j, 4+5j, 5+6j, 6+7j, 7+8j, 8+9j, 9+8j");

  if (result.ne(val_1)) {
    return Error::handle(TVector::name(), L"deleteRange",
			 Error::TEST, __FILE__, __LINE__);
  }
  
  // test deleteRange for deleting from the middle
  //
  val_0.assign(L"0+1j, 1+2j, 2+3j, 3+4j, 4+5j, 5+6j, 6+7j, 7+8j, 8+9j, 9+8j");
  val_1.deleteRange(val_0, 2, 3);
  result.assign(L"0+1j, 1+2j, 5+6j, 6+7j, 7+8j, 8+9j, 9+8j");

  if (result.ne(val_1)) {
    return Error::handle(TVector::name(), L"deleteRange",
			 Error::TEST, __FILE__, __LINE__);
  }
  
  // test deleteRange for deleting from the end
  //
  val_0.assign(L"0+1j, 1+2j, 2+3j, 3+4j, 4+5j, 5+6j, 6+7j, 7+8j, 8+9j, 9+8j");
  val_1.deleteRange(val_0, 6, 4);
  result.assign(L"0+1j, 1+2j, 2+3j, 3+4j, 4+5j, 5+6j");

  if (result.ne(val_1)) {
    return Error::handle(TVector::name(), L"deleteRange",
			 Error::TEST, __FILE__, __LINE__);
  }

  // test setRange for setting from the start
  //
  val_0.assign(L"0+1j, 1+2j, 2+3j, 3+4j, 4+5j, 5+6j");
  val_0.setRange(0, 3, (TIntegral)complexdouble(7, 1));
  result.assign(L"7+1j, 7+1j, 7+1j, 3+4j, 4+5j, 5+6j");

  if (result.ne(val_0)) {
    val_0.debug(L"output vector");
    result.debug(L"result vector");
    return Error::handle(TVector::name(), L"setRange",
			 Error::TEST, __FILE__, __LINE__);
  }
  
  // test setRange for setting from the middle
  //
  val_0.assign(L"0+1j, 1+2j, 2+3j, 3+4j, 4+5j, 5+6j");
  val_0.setRange(2, 3, (TIntegral)complexdouble(7, 1));
  result.assign(L"0+1j, 1+2j, 7+1j, 7+1j, 7+1j, 5+6j");

  if (result.ne(val_0)) {
    val_0.debug(L"output vector");
    result.debug(L"result vector");    
    return Error::handle(TVector::name(), L"setRange",
			 Error::TEST, __FILE__, __LINE__);
  }
  
  // test setRange for setting from the end
  //
  val_0.assign(L"0+1j, 1+2j, 2+3j, 3+4j, 4+5j, 5+6j");
  val_0.setRange(5, 1, (TIntegral)complexdouble(7, 1));
  result.assign(L"0+1j, 1+2j, 2+3j, 3+4j, 4+5j, 7+1j");

  if (result.ne(val_0)) {
    val_0.debug(L"output vector");
    result.debug(L"result vector");    
    return Error::handle(TVector::name(), L"setRange",
			 Error::TEST, __FILE__, __LINE__);
  }
 
  // find the first matching element a few times
  //
  int32 pos = 0;
  val_1.assign(L"2+1j, 3+4j, 20+18j, 3+4j, 15+5j, 32+4j, 6+7j, 2+1j, 3+4j, 2+1j, 7+6j");
  pos = val_1.first((TIntegral)complexdouble(3, 4));
  if (pos != 1) {
    return Error::handle(TVector::name(), L"first",
			 Error::TEST, __FILE__, __LINE__);
  }
  
  pos = val_1.first((TIntegral)complexdouble(3, 4), pos + 1);
  if (pos != 3) {
    return Error::handle(TVector::name(), L"first",
			 Error::TEST, __FILE__, __LINE__);
  }
  
  pos = val_1.first((TIntegral)complexdouble(3, 4), pos + 1);
  if (pos != 8) {
    return Error::handle(TVector::name(), L"first",
			 Error::TEST, __FILE__, __LINE__);
  }
  
  pos = val_1.first((TIntegral)complexdouble(3, 4), pos + 1);
  if (pos != Integral::NO_POS) {
    return Error::handle(TVector::name(), L"first",
			 Error::TEST, __FILE__, __LINE__);
  }
  
  // find the last matching element a few times
  //
  pos = val_1.last((TIntegral)complexdouble(2, 1));
  if (pos != 9) {
    return Error::handle(TVector::name(), L"last",
			 Error::TEST, __FILE__, __LINE__);
  }
  
  pos = val_1.last((TIntegral)complexdouble(2, 1), pos - 1);
  if (pos != 7) {
    return Error::handle(TVector::name(), L"last",
			 Error::TEST, __FILE__, __LINE__);
  }
  
  pos = val_1.last((TIntegral)complexdouble(2, 1), pos - 1);
  if (pos != 0) {
    return Error::handle(TVector::name(), L"last",
			 Error::TEST, __FILE__, __LINE__);
  }
  
  // ordering / sorting
  //
  if (level_a > Integral::BRIEF) {
    Console::put(L"testing reorder methods\n");
  }
  
  MVector<Long, int32> order_vector;
  order_vector.assign(L"1, 2, 4, 0, 3");
  
  val_0.assign(L"1+2j, 3+4j, 5+6j, 7+8j, 9+7j");
  
  val_0.reorder(order_vector);
  val_1.assign(L"3+4j, 5+6j, 9+7j, 1+2j, 7+8j");
  
  if (val_0.ne(val_1)) {
    return Error::handle(TVector::name(), L"reorder",
			 Error::TEST, __FILE__, __LINE__);
  }

  // reverse
  //
  if (level_a > Integral::BRIEF) {
    Console::put(L"testing reverse methods\n");
  }
  
  val_0.assign(L"1-2j, 3+4j, 5+6j, 7-8j, 9+7j");  
  val_0.reverse();
  val_1.assign(L"9+7j, 7-8j, 5+6j, 3+4j, 1-2j");
  
  if (val_0.ne(val_1)) {
    return Error::handle(TVector::name(), L"reverse",
			 Error::TEST, __FILE__, __LINE__);
  }
  
  val_0.clear();
  order_vector.clear();
  order_vector.setLength(100);
  val_0.setLength(100);

  
  TVector val0a;
  
  val_0.rand();
  val0a.assign(val_0);
  val0a.sort();
  
  val_0.index(order_vector);
  val_0.reorder(order_vector);
    
  if (!val_0.eq(val0a)) {
    val0a.debug(L"index/reorder");
    return Error::handle(TVector::name(), L"index/reorder",
			 Error::TEST, __FILE__, __LINE__);
  }
  val0a.clear();
  val_0.clear();


  // exit gracefully
  //
  return true;
}

// explicit instantiations. note that the sub-diagnose methods don't need
// their own instantiations since they are private and nothing but the
// primary diagnose method (also in this file) call them.
//
template bool8
MVectorMethods::diagnose<MVector<ISIP_TEMPLATE_TARGET>, ISIP_TEMPLATE_TARGET>
(Integral::DEBUG level);
