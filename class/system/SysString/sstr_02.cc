// file: $isip/class/system/SysString/sstr_02.cc
// version: $Id: sstr_02.cc 9418 2004-03-10 17:11:33Z parihar $
//
// notes:
//  (1) JP (07/07/2010): had to adjust tests for character string size
//      for 64-bit architectures.
//

// system include files:
//  note that we need some basic string functions. these are not included
//  in Integral.h since users are not expected to use these functions.
//
#include <strings.h>
//#include <widec.h>

// isip include files
//
#include "SysString.h"
#include <Console.h>

// method: diagnose
//
// arguments:
//  Integral::DEBUG level: (input) debug level for diagnostics
//
// return: a bool8 value indicating status
//

bool8 SysString::diagnose(Integral::DEBUG level_a) {

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
  
  //--------------------------------------------------------------------------
  //
  // 1. required public methods
  //
  //--------------------------------------------------------------------------

  // set indentation
  //
  if (level_a > Integral::NONE) {
    Console::put(L"testing required public methods...\n");
    Console::increaseIndention();
  }

  // do a quick test of constructors and destructors
  //
  SysString* ptr0, *ptr1, *ptr2, *ptr3;
  ptr0 = new SysString((byte8*)"hello my name is");
  ptr1 = new SysString(L"rick");
  ptr2 = new SysString(100);
  ptr3 = new SysString(*ptr1);
  
  delete ptr0;
  delete ptr1;
  delete ptr2;
  delete ptr3;

  // constructors
  //
  SysString str1((byte8*)"hello my name is");
  SysString str2(L"rjck");
  SysString str3(100);
  SysString str4(str2);

  // check setDebug method
  //
  setDebug(debug_level_d);
  
  if (level_a > Integral::BRIEF) {
    str1.debug(L"str1");
  }
  if (level_a > Integral::BRIEF) {
    str2.debug(L"str2");
  }
  if (level_a > Integral::BRIEF) {
    str3.debug(L"str3");
  }
  if (level_a > Integral::BRIEF) {
    str4.debug(L"str4");
  }

  // test operator= methods
  //
  SysString sstr_old(L"old");
  SysString sstr_new(L"new");

  sstr_old = sstr_new;
  
  // reset indentation
  //
  if (level_a > Integral::NONE) {
    Console::decreaseIndention();
  }
  
  //---------------------------------------------------------------------------
  //
  // 2. class-specific public methods:
  //     extensions to required methods     
  //
  //---------------------------------------------------------------------------

  // set indentation
  //
  if (level_a > Integral::NONE) {
    Console::put(L"testing class-specific public methods: extensions to required methods...\n");
    Console::increaseIndention();
  }

  // test assign methods
  //
  SysChar chr(L'h');
  str3.assign(chr);

  if ((str3.value_d[0] != L'h') || (str3.length() != 1)) {
    Error::handle(name(), L"assign SysChar", Error::TEST, __FILE__, __LINE__);
  }

  str3.assign(L'h');
  if ((str3.value_d[0] != L'h') || (str3.length() != 1)) {
    Error::handle(name(), L"assign SysChar", Error::TEST, __FILE__, __LINE__);
  }

  str3.assign(str2);
  if (str3.ne(str2)) {
    Error::handle(name(), L"re-assign unichar", Error::TEST,
                  __FILE__, __LINE__);
  }
  
  str2.assign(L" Rick");
  if (str2.length() != 5) {
    Error::handle(name(), L"re-assign unichar", Error::TEST,
                  __FILE__, __LINE__);
  }
  
  str4.assign((byte8*)"new byte8* text");
  if (str4.ne(L"new byte8* text")) {
    Error::handle(name(), L"re-assign byte", Error::TEST, __FILE__, __LINE__);
  }
  
  // make sure that an empty string fails
  //
  SysString num;
  int32 i;
  if (num.get(i)) {
    return Error::handle(name(), L"get", Error::TEST, __FILE__, __LINE__);
  }

  // make sure that non numeric types fail for get
  //
  num.assign(L"abc");
  if (num.get(i)) {
    return Error::handle(name(), L"get", Error::TEST, __FILE__, __LINE__);
  }

  // make sure that strings greater than length 1 fail for a get on SysChar
  //
  SysChar tmp_char;
  if (num.get(tmp_char)) {
    return Error::handle(name(), L"get", Error::TEST, __FILE__, __LINE__);
  }

  // setup temporary variables
  //
  byte8 dbyte = (int32)27;
  byte8 dbyte_v;

  int16 dshort = (int32)27;
  int16 dshort_v;

  int32 dlong = (int32)277;
  int32 dlong_v;
  
  int64 dllong = (int64)13020756033LL;
  int64 dllong_v;
  
  uint16 dushort = (uint16)6907;
  uint16 dushort_v;
  
  uint32 dulong = (uint32)2777;
  uint32 dulong_v;
  
  uint64 dullong = (uint64)1302075603332LL;
  uint64 dullong_v;

  float32 dfloat = (float32)27.27e-19;
  float32 dfloat_v;
  
  float64 ddouble = (float64)272727272727.272727e+20;
  float64 ddouble_v;

  bool8 dboolean = true;
  bool8 dboolean_v;
  
  void* dvoidp = (void*)27;
  void* dvoidp_v;

  // test the byte conversions
  //
  num.assign(dbyte);
  num.get(dbyte_v);

  if (dbyte != dbyte_v) {
    Error::handle(name(), L"assign(byte8)", Error::TEST, __FILE__, __LINE__);
  }

  num.assign(dbyte, L"asdf = %u xyz");
  if (num.ne(L"asdf = 27 xyz")) {
    Error::handle(name(), L"assign(byte8)", Error::TEST, __FILE__, __LINE__);
  }
  
  // test the int16 conversions
  //
  num.assign(dshort);
  num.get(dshort_v);

  if (dshort != dshort_v) {
    Error::handle(name(), L"assign(int16)", Error::TEST, __FILE__, __LINE__);
  }

  num.assign(dshort, L"asdf = %d xyz");
  if (num.ne(L"asdf = 27 xyz")) {
    Error::handle(name(), L"assign(int16)", Error::TEST, __FILE__, __LINE__);
  }
  
  // test the int32 conversions
  //
  num.assign(dlong);
  num.get(dlong_v);
   
  if (dlong != dlong_v) {
    Error::handle(name(), L"assign(int32)", Error::TEST, __FILE__, __LINE__);
  }

   num.assign(dlong, L"asdf = %ld xyz");
  if (num.ne(L"asdf = 277 xyz")) {
    Error::handle(name(), L"assign(int32)", Error::TEST, __FILE__, __LINE__);
  }

  // test the int64 conversions
  //
  num.assign(dllong);
  num.get(dllong_v);  
  if (dllong != dllong_v) {
    Error::handle(name(), L"assign(int64)", Error::TEST, __FILE__, __LINE__);
  }
  
  num.assign(dllong, L"asdf = %lld xyz");
  if (num.ne(L"asdf = 13020756033 xyz")) {
    Error::handle(name(), L"assign(int64)", Error::TEST, __FILE__, __LINE__);
  }

  // test the uint16 conversions
  //
  num.assign(dushort);
  num.get(dushort_v);
  
  if (dushort != dushort_v) {
    Error::handle(name(), L"assign(uint16)", Error::TEST, __FILE__, __LINE__);
  }

  num.assign(dushort, L"asdf = %lu xyz");
  if (num.ne(L"asdf = 6907 xyz")) {
    Error::handle(name(), L"assign(uint16)", Error::TEST, __FILE__, __LINE__);
  }

  // test the uint32 conversions
  //
  num.assign(dulong);
  num.get(dulong_v);

  if (dulong != dulong_v) {
    Error::handle(name(), L"assign(uint32)", Error::TEST, __FILE__, __LINE__);
  }

  num.assign(dulong, L"asdf = %lu xyz");
  if (num.ne(L"asdf = 2777 xyz")) {
    Error::handle(name(), L"assign(uint32)", Error::TEST, __FILE__, __LINE__);
  }

  // test the uint64 conversions
  //
  num.assign(dullong);
  num.get(dullong_v);

  if (dullong != dullong_v) {
    Error::handle(name(), L"assign(uint64)", Error::TEST, __FILE__, __LINE__);
  }

  num.assign(dullong, L"asdf = %llu xyz");
  if (num.ne(L"asdf = 1302075603332 xyz")) {
    num.debug(L"");
    Error::handle(name(), L"assign(long)", Error::TEST, __FILE__, __LINE__);
  }

  // test the float32 conversions
  //
  num.assign(dfloat);
  num.get(dfloat_v);

  if (level_a > Integral::ALL) {
    num.debug(L"float32");
  }
  
  if (!Integral::almostEqual(dfloat, dfloat_v)) {
    fprintf(stdout, "%f != %f != '%s'\n", dfloat, dfloat_v, (char*)(byte8*)num);
    Error::handle(name(), L"assign(float32)", Error::TEST, __FILE__, __LINE__);
  }

  num.assign(dfloat, L"asdf = %e xyz");
  if (num.ne(L"asdf = 2.727000e-18 xyz")) {
    Error::handle(name(), L"assign(float32)", Error::TEST, __FILE__, __LINE__);
  }

  // test the float64 conversions
  //
  num.assign(ddouble);
  num.get(ddouble_v);

  if (level_a > Integral::ALL) {
    num.debug(L"float64");
  }
  
  if (!Integral::almostEqual(ddouble, ddouble_v)) {
    fprintf(stdout, "%f != %f != '%s'\n", ddouble, ddouble_v,
            (char*)(byte8*)num);
    Error::handle(name(), L"assign(float64)", Error::TEST, __FILE__, __LINE__);
  }

  num.assign(ddouble, L"asdf = %e xyz");
  if (num.ne(L"asdf = 2.727273e+31 xyz")) {
    Error::handle(name(), L"assign(float64)", Error::TEST, __FILE__, __LINE__);
  }

  // test the bool8 conversions
  //
  num.assign(dboolean);
  num.get(dboolean_v);

  if (dboolean != dboolean_v) {
    Error::handle(name(), L"assign(bool8)", Error::TEST, __FILE__, __LINE__);
  }

  num.assign(dboolean, L"asdf = %s xyz");
  if (num.ne(L"asdf = true xyz")) {
    Error::handle(name(), L"assign(bool8)", Error::TEST, __FILE__,
		  __LINE__);
  }
  
  // test the pointer conversions
  //
  num.assign(dvoidp);
  num.get(dvoidp_v);

  if (dvoidp != dvoidp_v) {
    Error::handle(name(), L"assign(void*)", Error::TEST, __FILE__, __LINE__);
  }

  dvoidp = NULL;
  num.assign(dvoidp);
  num.get(dvoidp_v);

  if (dvoidp != dvoidp_v) {
    Error::handle(name(), L"assign(void*)", Error::TEST, __FILE__, __LINE__);
  }
  
  // pointers are printed differently on different platforms so we generate
  // a reference string rather than assuming one. The functions used to do 
  // this have been tested above this point.
  //
  SysString voidp_tmp1(L"asdf = ");
  SysString voidp_tmp2;
  voidp_tmp2.assign((void*)NULL);
  SysString voidp_tmp3(L" xyz");
  SysString voidp_ref(voidp_tmp1);
  voidp_ref.concat(voidp_tmp2);
  voidp_ref.concat(voidp_tmp3);

  num.assign(dvoidp, L"asdf = %p xyz");
  if (num.ne(voidp_ref)) {
    voidp_ref.debug(L"reference");
    num.debug(L"num");
    Error::handle(name(), L"assign(voidp)", Error::TEST, __FILE__,
		  __LINE__);
  }

  voidp_tmp2.assign((void*)0x8192);
  voidp_ref.assign(voidp_tmp1);
  voidp_ref.concat(voidp_tmp2);
  voidp_ref.concat(voidp_tmp3);

  num.assign((void*)0x8192, L"asdf = %p xyz");
  if (num.ne(voidp_ref)){
    voidp_ref.debug(L"reference");
    num.debug(L"num");
    Error::handle(name(), L"assign(voidp)", Error::TEST, __FILE__,
		  __LINE__);
  }

  Error::set(Error::NONE);
  
  // test complex assign & such
  //
  SysComplex<float32> dcfloat(3, 2);	// number in quadrant I
  num.assign(dcfloat);
  SysComplex<float32> dcfloat_v;
  num.get(dcfloat_v);
  if (dcfloat != dcfloat_v) {
    num.debug(L"dcfloat");
    Error::handle(name(), L"assign(complex)", Error::TEST, __FILE__, __LINE__);
  }

  dcfloat = SysComplex<float32>(3, -2);	// number in quadrant IV
  num.assign(dcfloat);
  num.get(dcfloat_v);
  if (dcfloat != dcfloat_v) {
    num.debug(L"dcfloat");
    Error::handle(name(), L"assign(complex)", Error::TEST, __FILE__, __LINE__);
  }

  num.assign(dcfloat, L"asdf = %s xyz");
  if (num.ne(L"asdf = 3-2j xyz")) {
    Error::handle(name(), L"assign(complex)", Error::TEST, __FILE__,
		  __LINE__);
  }

  dcfloat = SysComplex<float32>(-23,-24);	// number in quadrant III
  num.assign(dcfloat);
  num.get(dcfloat_v);
  if (dcfloat != dcfloat_v) {
    num.debug(L"dcfloat");
    Error::handle(name(), L"assign(complex)", Error::TEST, __FILE__, __LINE__);
  }

  dcfloat = SysComplex<float32>(-23,24);	// number in quadrant II
  num.assign(dcfloat);
  num.get(dcfloat_v);
  if (dcfloat != dcfloat_v) {
    num.debug(L"dcfloat");
    Error::handle(name(), L"assign(complex)", Error::TEST, __FILE__, __LINE__);
  }

  dcfloat = SysComplex<float32>(23,0);	// number on positive X axis
  num.assign(dcfloat);
  num.get(dcfloat_v);
  if (dcfloat != dcfloat_v) {
    num.debug(L"dcfloat");
    Error::handle(name(), L"assign(complex)", Error::TEST, __FILE__, __LINE__);
  }

  dcfloat = SysComplex<float32>(-23,0);	// number on negative X axis
  num.assign(dcfloat);
  num.get(dcfloat_v);
  if (dcfloat != dcfloat_v) {
    num.debug(L"dcfloat");
    Error::handle(name(), L"assign(complex)", Error::TEST, __FILE__, __LINE__);
  }

  dcfloat = SysComplex<float32>(0, 23);	// number on positive Y axis
  num.assign(dcfloat);
  num.get(dcfloat_v);
  if (dcfloat != dcfloat_v) {
    num.debug(L"dcfloat");
    Error::handle(name(), L"assign(complex)", Error::TEST, __FILE__, __LINE__);
  }

  dcfloat = SysComplex<float32>(0, -23);	// number on negative Y axis
  num.assign(dcfloat);
  num.get(dcfloat_v);
  if (dcfloat != dcfloat_v) {
    num.debug(L"dcfloat");
    Error::handle(name(), L"assign(complex)", Error::TEST, __FILE__, __LINE__);
  }

  dcfloat = SysComplex<float32>(0, -1);	// -j
  num.assign(L"-j");
  num.get(dcfloat_v);
  if (dcfloat != dcfloat_v) {
    num.debug(L"dcfloat");
    Error::handle(name(), L"assign(complex)", Error::TEST, __FILE__, __LINE__);
  }

  dcfloat = SysComplex<float32>(0, 1);	// j
  num.assign(L"j");
  num.get(dcfloat_v);
  if (dcfloat != dcfloat_v) {
    num.debug(L"dcfloat");
    Error::handle(name(), L"assign(complex)", Error::TEST, __FILE__, __LINE__);
  }

  dcfloat = SysComplex<float32>(2, 1);	// 2+j
  num.assign(L"2+j");
  num.get(dcfloat_v);
  if (dcfloat != dcfloat_v) {
    num.debug(L"dcfloat");
    Error::handle(name(), L"assign(complex)", Error::TEST, __FILE__, __LINE__);
  }

  dcfloat = SysComplex<float32>(3, -1);	// 3-j
  num.assign(L"3 - j");
  num.get(dcfloat_v);
  if (dcfloat != dcfloat_v) {
    num.debug(L"dcfloat");
    Error::handle(name(), L"assign(complex)", Error::TEST, __FILE__, __LINE__);
  }
  
  // test assign enum type data
  //
  SysString str6(str1);
  str6.assign(Integral::DETAILED);
  if (str6.ne(DBG_DETAILED)) {
    str6.debug(L"str6");
    Error::handle(name(), L"assign(Integral::DEBUG arg)",
                  Error::TEST, __FILE__, __LINE__);
  }

  str6.assign(Integral::EQUAL);
  if (str6.ne(CMP_EQUAL)) {
    str6.debug(L"str6");
    Error::handle(name(), L"assign(Integral::COMPARE arg)",
                  Error::TEST, __FILE__, __LINE__);
  }
    
  str6.assign(File::READ_PLUS);
  if (str6.ne(MODE_READ_PLUS)) {
    Error::handle(name(), L"assign(File::arg)",
                  Error::TEST, __FILE__, __LINE__);
  }
  
  str6.assign(SysChar::ENCODE_ASCII);
  if (str6.ne(ENCODE_ASCII)) {
    Error::handle(name(), L"assign(SysChar::ENCODE arg)",
                  Error::TEST, __FILE__, __LINE__);
  }

  str6.assign(File::BIG_ENDIAN);
  if (str6.ne(BMODE_BIG_ENDIAN)) {
    Error::handle(name(), L"assign(File::BMODE arg)",
                  Error::TEST, __FILE__, __LINE__);
  }

  // test formated strings
  //
  str2.assign(L"qwer", L"asdf %20s xyz");
  if (str2.ne(L"asdf                 qwer xyz")) {
    return Error::handle(name(), L"assign", Error::TEST, __FILE__, __LINE__);
  }

  // test formated chars
  //
  str2.assign(L'a', L"asdf %20c xyz");
  if (str2.ne(L"asdf                    a xyz")) {
    return Error::handle(name(), L"assign", Error::TEST, __FILE__, __LINE__);
  }

  // reset indentation
  //
  if (level_a > Integral::NONE) {
    Console::decreaseIndention();
  }
  
  //---------------------------------------------------------------------------
  //
  // 3. class-specific public methods:
  //     relational and logical methods
  //
  //---------------------------------------------------------------------------

  // set indentation
  //
  if (level_a > Integral::NONE) {
    Console::put(L"testing class-specific public methods: relational and logical methods...\n");
    Console::increaseIndention();
  }

  // test generic compare methods
  //
  str1.assign(L"red");
  str2.assign(L"boat");
  str3.assign(L"boat");
  
  if (str1.compare(str2) != Integral::GREATER) {
    Error::handle(name(), L"compare 0", Error::TEST, __FILE__, __LINE__);
  }
  
  if (str2.compare(str1) != Integral::LESSER) {
    Error::handle(name(), L"compare 1", Error::TEST, __FILE__, __LINE__);
  }
  
  if (str2.compare(str3) != Integral::EQUAL) {
    Error::handle(name(), L"compare 2", Error::TEST, __FILE__, __LINE__);
  }

  if (str2.comparePartial(str3, 1, 2, 1) != Integral::EQUAL) {
    Error::handle(name(), L"comparePartial", Error::TEST, __FILE__, __LINE__);
  }

  if (str2.comparePartial(L"boat", 1, 2, 1) != Integral::EQUAL) {
    Error::handle(name(), L"comparePartial", Error::TEST, __FILE__, __LINE__);
  }

  if (str1.eq(str2)) {
    Error::handle(name(), L"eq", Error::TEST, __FILE__, __LINE__);
  }
  
  if (!str2.eq(str3)) {
    Error::handle(name(), L"eq", Error::TEST, __FILE__, __LINE__);
  }

  str3.assign(L"Boat");
  if (str2.eq(str3)) {
    Error::handle(name(), L"eq, case sensitive ", Error::TEST, __FILE__,
                  __LINE__);
  }
  if (str2.ne(str3, false)) {
    Error::handle(name(), L"ne, case insensitive", Error::TEST, __FILE__,
                  __LINE__);
  }

  str3.toLower();
  if (!str1.gt(str2)) {
    Error::handle(name(), L"gt", Error::TEST, __FILE__, __LINE__);
  }

  // test relational methods
  //
  if (str2.gt(str3)) {
    Error::handle(name(), L"gt", Error::TEST, __FILE__, __LINE__);
  }
  
  if (!str1.ge(str2)) {
    Error::handle(name(), L"ge", Error::TEST, __FILE__, __LINE__);
  }
  
  if (!str2.ge(str3)) {
    Error::handle(name(), L"ge", Error::TEST, __FILE__, __LINE__);
  }
  
  if (!str2.lt(str1)) {
    Error::handle(name(), L"lt", Error::TEST, __FILE__, __LINE__);
  }
  
  if (str3.lt(str2)) {
    Error::handle(name(), L"lt", Error::TEST, __FILE__, __LINE__);
  }
  
  if (!str2.le(str1)) {
    Error::handle(name(), L"le", Error::TEST, __FILE__, __LINE__);
  }
  
  if (!str3.le(str2)) {
    Error::handle(name(), L"le", Error::TEST, __FILE__, __LINE__);
  }
  
  if (!str2.ne(str1)) {
    Error::handle(name(), L"ne", Error::TEST, __FILE__, __LINE__);
  }
  
  if (str2.ne(str3)) {
    Error::handle(name(), L"ne", Error::TEST, __FILE__, __LINE__);
  }
  
  // reset indentation
  //
  if (level_a > Integral::NONE) {
    Console::decreaseIndention();
  }
  
  //---------------------------------------------------------------------------
  //
  // 4. class-specific public methods:
  //     indexing methods
  //
  //---------------------------------------------------------------------------

  // set indentation
  //
  if (level_a > Integral::NONE) {
    Console::put(L"testing class-specific public methods: indexing methods...\n");
    Console::increaseIndention();
  }

  // declare a string
  //
  SysString oper_str(L"rjck");

  unichar c = oper_str(1);
  if (c != L'j') {
    Error::handle(name(), L"operator scalar <-", Error::TEST,
                  __FILE__, __LINE__);
  }
  
  c = L'i';
  oper_str(1) = c;
  if (oper_str.ne(L"rick")) {
    Error::handle(name(), L"operator scalar ->", Error::TEST,
                  __FILE__, __LINE__);
  }  

  // reset indentation
  //
  if (level_a > Integral::NONE) {
    Console::decreaseIndention();
  }
  
  //---------------------------------------------------------------------------
  //
  // 5. class-specific public methods:
  //     conversion methods
  //
  //---------------------------------------------------------------------------

  // set indentation
  //
  if (level_a > Integral::NONE) {
    Console::put(L"testing class-specific public methods: conversion methods...\n");
    Console::increaseIndention();
  }

  // test byte8* and unichar* conversion methods
  //
  // pull out all the values at once. interleave the different width
  // characters to test alignment. Note that sparcs are long word
  // aligned while pentiums are not, so a program which runs on a
  // pentium may not run on a sparc. If you get a bus error on a Sun
  // for a program that works on a Pentium, check that your addresses
  // are long word aligned.
  //
  SysString priv_str1((byte8*)"hello my name is");
  SysString priv_str2(L"rick");
  
  unichar* ws1 = priv_str1;
  byte8* s1 = priv_str1;
  unichar* ws2 = priv_str2;
  byte8* s2 = priv_str2;
  
  if (isip_wcscmp(ws1, L"hello my name is") != 0) {
    Error::handle(name(), L"operator unichar* 1", Error::TEST,
                  __FILE__, __LINE__);
  }

  if (isip_wcscmp(ws2, L"rick") != 0) {
    Error::handle(name(), L"operator unichar* 2", Error::TEST,
                  __FILE__, __LINE__);
  }

  if (strcmp((char*)s1, (char*)"hello my name is") != 0) {
    Error::handle(name(), L"operator byte8* 1", Error::TEST,
                  __FILE__, __LINE__);
  }
  if (strcmp((char*)s2, (char*)"rick") != 0) {
    Error::handle(name(), L"operator byte8* 2", Error::TEST,
                  __FILE__, __LINE__);
  }

  // all the get methods have been tested in "extensions to the
  // required public methods" part of diagnose method
  //
  
  // reset indentation
  //
  if (level_a > Integral::NONE) {
    Console::decreaseIndention();
  }
  
  //---------------------------------------------------------------------------
  //
  // 6. class-specific public methods:
  //     size related methods
  //
  //---------------------------------------------------------------------------

  // set indentation
  //
  if (level_a > Integral::NONE) {
    Console::put(L"testing class-specific public methods: size related methods...\n");
    Console::increaseIndention();
  }

  // declare a string
  //
  SysString tmp(L"12"); 
  // test memSize
  int32 ref_size = (1)*sizeof(value_d) + (2+1)*sizeof(unichar)+sizeof(capacity_d);
  if (tmp.memSize() != ref_size) {
    Error::handle(name(), L"memSize", Error::TEST, __FILE__, __LINE__);
  }

  // test memSize
  //
  int32 len = tmp.length();
  if (len != 2) {
    fprintf(stdout, "len = %ld",(long) len);
    Error::handle(name(), L"length", Error::TEST, __FILE__, __LINE__);
  }

  // test setCapacity
  //
  tmp.setCapacity(5);
  if (tmp.capacity_d != 5) {
    Error::handle(name(), L"setCapacity", Error::TEST, __FILE__, __LINE__);
  }
  
  // reset indentation
  //
  if (level_a > Integral::NONE) {
    Console::decreaseIndention();
  }
  
  //---------------------------------------------------------------------------
  //
  // 7. class-specific public methods:
  //     string manipulation methods
  //
  //---------------------------------------------------------------------------

  // set indentation
  //
  if (level_a > Integral::NONE) {
    Console::put(L"testing class-specific public methods: string manipulation methods...\n");
    Console::increaseIndention();
  }

  // test insert methods
  //
  SysString str5(L"alphonso");
  str2.assign((byte8*)"hello my name is");
  str3.assign(L"real ");
  str4.assign(L" duncan");

  str2.insert(str3, 9);
  if (level_a > Integral::ALL) {
    str2.debug(L"str2");
  }
  if (str2.ne(L"hello my real name is")) {
    Error::handle(name(), L"insert", Error::TEST, __FILE__, __LINE__);
  }
  
  str2.insert(str4, 9999);
  if (level_a > Integral::ALL) {
    str2.debug(L"str2");
  }
  if (str2.ne(L"hello my real name is duncan")) {
    Error::handle(name(), L"insert", Error::TEST, __FILE__, __LINE__);
  }
  
  str3.assign(L" jennings");
  str2.insert(str3, 21);
  if (level_a > Integral::ALL) {
    str2.debug(L"str2");
  }
  if (str2.ne(L"hello my real name is jennings duncan")) {
    Error::handle(name(), L"insert", Error::TEST, __FILE__, __LINE__);
  }
  
  str3.assign(L"richard ");
  str2.insert(str3, 22);
  if (level_a > Integral::ALL) {
    str2.debug(L"str2");
  }
  if (str2.ne(L"hello my real name is richard jennings duncan")) {
    Error::handle(name(), L"insert", Error::TEST, __FILE__, __LINE__);
  }

  // test replace methods
  //
  str3.assign(L"JoeBobb");
  str2.replace(str3, 22);
  if (level_a > Integral::ALL) {
    str2.debug(L"str2");
  }
  if (str2.ne(L"hello my real name is JoeBobb jennings duncan")) {
    Error::handle(name(), L"replace", Error::TEST, __FILE__, __LINE__);
  }

  str3.assign(str2);
  str3.replace(L" duncan", L"");
  if (str3.ne(L"hello my real name is JoeBobb jennings")) {
    Error::handle(name(), L"replace", Error::TEST, __FILE__, __LINE__);
  }

  str3.replaceAll(L" ", L"");
   if (str3.ne(L"hellomyrealnameisJoeBobbjennings")) {
    Error::handle(name(), L"replace", Error::TEST, __FILE__, __LINE__);
  }

  str5.replaceAll(L"o", L" o ");
  if (str5.ne(L"alph o ns o ")) {
    Error::handle(name(), L"replace", Error::TEST, __FILE__, __LINE__);
  }   
  
  str4.assign(L"...or maybe not");
  str2.replace(str4, str2.length());
  if (level_a > Integral::ALL) {
    str2.debug(L"str2");
  }
  if(str2.ne(L"hello my real name is JoeBobb jennings duncan...or maybe not")){
    Error::handle(name(), L"replace", Error::TEST, __FILE__, __LINE__);
  }

  // test deleteRange methods
  //
  str2.deleteRange(str2.length() - 15, -1);
  if (level_a > Integral::ALL) {
    str2.debug(L"str2");
  }
  if (str2.ne(L"hello my real name is JoeBobb jennings duncan")) {
    Error::handle(name(), L"deleteRange", Error::TEST, __FILE__, __LINE__);
  }
  
  str2.deleteRange(22, 8);
  if (level_a > Integral::ALL) {
    str2.debug(L"str2");
  }
  if (str2.ne(L"hello my real name is jennings duncan")) {
    Error::handle(name(), L"deleteRange", Error::TEST, __FILE__, __LINE__);
  }
  
  str2.deleteRange(22, 9);
  if (level_a > Integral::ALL) {
    str2.debug(L"str2");
  }
  if (str2.ne(L"hello my real name is duncan")) {
    Error::handle(name(), L"deleteRange", Error::TEST, __FILE__, __LINE__);
  }

  // test boundary condition for deleteRange
  //
  SysString str(L"0123456789");
  str.deleteRange(8, 2);
  if (str.length() != 8) {
    return Error::handle(name(), L"deleteRange", Error::TEST, __FILE__,
			 __LINE__);
  }
  
  // test concat methods
  //
  str1.assign(L"Hello my name");
  str1.concat(L" is");
  if (level_a > Integral::ALL) {
    str1.debug(L"str1");
  }
  if (str1.ne(L"Hello my name is")) {
    Error::handle(name(), L"concat", Error::TEST, __FILE__, __LINE__);
  }
  
  str2.assign(L" Rick");
  str3.assign(str1);
  str3.concat(str2);
  if (level_a > Integral::ALL) {
    str3.debug(L"str3");
  }
  if (str3.ne(L"Hello my name is Rick")) {
    Error::handle(name(), L"concat", Error::TEST, __FILE__, __LINE__);
  }
  
  str4.concat(str1, str2);
  if (str4.ne(L"Hello my name is Rick")) {
    Error::handle(name(), L"concat", Error::TEST, __FILE__, __LINE__);
  }

  str4.concat((unichar)L'y');
  if (str4.ne(L"Hello my name is Ricky")) {
    str4.debug(L"str4");
    Error::handle(name(), L"concat", Error::TEST, __FILE__, __LINE__);
  }

  str4.concat((unichar)L'J', L"asdf %c qwer");
  if (str4.ne(L"Hello my name is Rickyasdf J qwer")) {
    str4.debug(L"str4");
    Error::handle(name(), L"concat", Error::TEST, __FILE__, __LINE__);
  }

  str4.concat(L"xyz", L"asdf %s qwer");
  if (str4.ne(L"Hello my name is Rickyasdf J qwerasdf xyz qwer")) {
    str4.debug(L"str4");
    Error::handle(name(), L"concat", Error::TEST, __FILE__, __LINE__);
  }

  str4.concat(str, L"num = %s xyz");
  if (str4.ne(L"Hello my name is Rickyasdf J qwerasdf xyz qwernum = 01234567 xyz")) {
    str4.debug(L"str4");
    Error::handle(name(), L"concat", Error::TEST, __FILE__, __LINE__);
  }

  
  // make sure we can concat an empty string
  //
  SysString foo;
  SysString bar;
  foo.concat(bar);
  if (foo.length() != 0) {
    return Error::handle(name(), L"concat", Error::TEST, __FILE__, __LINE__);
  }

  // test numeric concat methods
  //
  
  // test the byte conversions
  //
  num.clear();
  num.concat(dbyte);
  num.get(dbyte_v);

  if (dbyte != dbyte_v) {
    Error::handle(name(), L"assign(byte8)", Error::TEST, __FILE__, __LINE__);
  }

  num.clear();
  num.concat(dbyte, L"asdf = %u xyz");
  if (num.ne(L"asdf = 27 xyz")) {
    Error::handle(name(), L"assign(byte8)", Error::TEST, __FILE__, __LINE__);
  }
  
  // test the int16 conversions
  //
  num.clear();
  num.concat(dshort);
  num.get(dshort_v);

  if (dshort != dshort_v) {
    Error::handle(name(), L"assign(int16)", Error::TEST, __FILE__, __LINE__);
  }

  num.clear();
  num.concat(dshort, L"asdf = %d xyz");
  if (num.ne(L"asdf = 27 xyz")) {
    Error::handle(name(), L"assign(int16)", Error::TEST, __FILE__, __LINE__);
  }
  
  // test the int32 conversions
  //
  num.clear();
  num.concat(dlong);
  num.get(dlong_v);

  if (dlong != dlong_v) {
    Error::handle(name(), L"assign(int32)", Error::TEST, __FILE__, __LINE__);
  }

  num.clear();
  num.concat(dlong, L"asdf = %ld xyz");
  if (num.ne(L"asdf = 277 xyz")) {
    Error::handle(name(), L"assign(int32)", Error::TEST, __FILE__, __LINE__);
  }

  // test the int64 conversions
  //
  num.clear();
  num.concat(dllong);
  num.get(dllong_v);
  
  if (dllong != dllong_v) {
    Error::handle(name(), L"assign(int64)", Error::TEST, __FILE__, __LINE__);
  }
  
  num.clear();
  num.concat(dllong, L"asdf = %lld xyz");
  if (num.ne(L"asdf = 13020756033 xyz")) {
    Error::handle(name(), L"assign(int64)", Error::TEST, __FILE__, __LINE__);
  }

  // test the uint16 conversions
  //
  num.clear();
  num.concat(dushort);
  num.get(dushort_v);
  
  if (dushort != dushort_v) {
    Error::handle(name(), L"assign(uint16)", Error::TEST, __FILE__, __LINE__);
  }

  num.clear();
  num.concat(dushort, L"asdf = %lu xyz");
  if (num.ne(L"asdf = 6907 xyz")) {
    Error::handle(name(), L"assign(uint16)", Error::TEST, __FILE__, __LINE__);
  }

  // test the uint32 conversions
  //
  num.clear();
  num.concat(dulong);
  num.get(dulong_v);

  if (dulong != dulong_v) {
    Error::handle(name(), L"assign(uint32)", Error::TEST, __FILE__, __LINE__);
  }

  num.clear();
  num.concat(dulong, L"asdf = %lu xyz");
  if (num.ne(L"asdf = 2777 xyz")) {
    Error::handle(name(), L"assign(uint32)", Error::TEST, __FILE__, __LINE__);
  }

  // test the uint64 conversions
  //
  num.clear();
  num.concat(dullong);
  num.get(dullong_v);

  if (dullong != dullong_v) {
    Error::handle(name(), L"assign(uint64)", Error::TEST, __FILE__, __LINE__);
  }

  num.clear();
  num.concat(dullong, L"asdf = %llu xyz");
  if (num.ne(L"asdf = 1302075603332 xyz")) {
    num.debug(L"");
    Error::handle(name(), L"assign(uint64)", Error::TEST, __FILE__, __LINE__);
  }

  // test the float32 conversions
  //
  num.clear();
  num.concat(dfloat);
  num.get(dfloat_v);

  if (level_a > Integral::ALL) {
    num.debug(L"float32");
  }
  
  if (!Integral::almostEqual(dfloat, dfloat_v)) {
    fprintf(stdout, "%f != %f != '%s'\n", dfloat, dfloat_v, (char*)(byte8*)num);
    Error::handle(name(), L"assign(float32)", Error::TEST, __FILE__, __LINE__);
  }

  num.clear();
  num.concat(dfloat, L"asdf = %e xyz");
  if (num.ne(L"asdf = 2.727000e-18 xyz")) {
    Error::handle(name(), L"assign(float32)", Error::TEST, __FILE__, __LINE__);
  }

  // test the float64 conversions
  //
  num.clear();
  num.concat(ddouble);
  num.get(ddouble_v);

  if (level_a > Integral::ALL) {
    num.debug(L"float64");
  }
  
  if (!Integral::almostEqual(ddouble, ddouble_v)) {
    fprintf(stdout, "%f != %f != '%s'\n", ddouble, ddouble_v,
            (char*)(byte8*)num);
    Error::handle(name(), L"assign(float64)", Error::TEST, __FILE__, __LINE__);
  }

  num.clear();
  num.concat(ddouble, L"asdf = %e xyz");
  if (num.ne(L"asdf = 2.727273e+31 xyz")) {
    Error::handle(name(), L"assign(float64)", Error::TEST, __FILE__, __LINE__);
  }

  // test the bool8 conversions
  //
  num.clear();
  num.concat(dboolean);
  num.get(dboolean_v);

  if (dboolean != dboolean_v) {
    Error::handle(name(), L"assign(bool8)", Error::TEST, __FILE__, __LINE__);
  }

  num.clear();
  num.concat(dboolean, L"asdf = %s xyz");
  if (num.ne(L"asdf = true xyz")) {
    Error::handle(name(), L"assign(bool8)", Error::TEST, __FILE__,
		  __LINE__);
  }
  
  // test the pointer conversions
  //
  num.clear();
  num.concat(dvoidp);
  num.get(dvoidp_v);

  if (dvoidp != dvoidp_v) {
    Error::handle(name(), L"assign(void*)", Error::TEST, __FILE__, __LINE__);
  }

  dvoidp = NULL;
  num.clear();
  num.concat(dvoidp);
  num.get(dvoidp_v);

  if (dvoidp != dvoidp_v) {
    Error::handle(name(), L"assign(void*)", Error::TEST, __FILE__, __LINE__);
  }

  // pointers are printed differently on different platforms so we generate
  // a reference string rather than assuming one. The functions used to do 
  // this have been tested above this point.
  //
  voidp_tmp2.assign((void*)NULL);
  voidp_ref.assign(voidp_tmp1);
  voidp_ref.concat(voidp_tmp2);
  voidp_ref.concat(voidp_tmp3);
  num.clear();
  num.concat(dvoidp, L"asdf = %p xyz");
  if (num.ne(voidp_ref)) {
    voidp_ref.debug(L"reference");
    num.debug(L"num");
    Error::handle(name(), L"assign(voidp)", Error::TEST, __FILE__,
		  __LINE__);
  }

  voidp_tmp2.assign((void*)0x8192);
  voidp_ref.assign(voidp_tmp1);
  voidp_ref.concat(voidp_tmp2);
  voidp_ref.concat(voidp_tmp3);
  num.clear();
  num.concat((void*)0x8192, L"asdf = %p xyz");
  if (num.ne(voidp_ref)) {
    voidp_ref.debug(L"reference");
    num.debug(L"num");
    Error::handle(name(), L"assign(voidp)", Error::TEST, __FILE__,
		  __LINE__);
  }

  // test complex assign & such
  //
  dcfloat = SysComplex<float32>(3, 2);
  num.clear();
  num.concat(dcfloat);
  num.get(dcfloat_v);
  if (dcfloat != dcfloat_v) {
    num.debug(L"dcfloat");
    Error::handle(name(), L"assign(complex)", Error::TEST, __FILE__, __LINE__);
  }

  dcfloat = SysComplex<float32>(3, -2);
  num.clear();
  num.concat(dcfloat);
  num.get(dcfloat_v);
  if (dcfloat != dcfloat_v) {
    num.debug(L"dcfloat");
    Error::handle(name(), L"assign(complex)", Error::TEST, __FILE__, __LINE__);
  }

  num.clear();
  num.concat(dcfloat, L"asdf = %s xyz");
  if (num.ne(L"asdf = 3-2j xyz")) {
    Error::handle(name(), L"assign(complex)", Error::TEST, __FILE__,
		  __LINE__);
  }
  
  // test trim methods
  //
  str1.assign(L"   ...Hello my name is ...     ");
  if (level_a > Integral::ALL) {
    str1.debug(L"str1");
  }
  str2.assign(str1);
  str3.assign(str1);
  str4.assign(str1);

  str4.trim();
  if (level_a > Integral::ALL) {
    str4.debug(L"str4");
  }
  if (str4.ne(L"...Hello my name is ...")) {
    Error::handle(name(), L"trim 1", Error::TEST, __FILE__, __LINE__);
  }
  
  str4.trim(L". ");
  if (level_a > Integral::ALL) {
    str4.debug(L"str4");
  }
  if (str4.ne(L"Hello my name is")) {
    Error::handle(name(), L"trim 2", Error::TEST, __FILE__, __LINE__);
  }
  
  str4.trim(L"Hello ");
  if (str4.ne(L"my name is")) {
    Error::handle(name(), L"trim 3", Error::TEST, __FILE__, __LINE__);
  }
  
  str2.trimLeft();
  if (level_a > Integral::ALL) {
    str2.debug(L"str2");
  }
  if (str2.ne(L"...Hello my name is ...     ")) {
    Error::handle(name(), L"trimLeft 1", Error::TEST, __FILE__, __LINE__);
  }
  
  str2.trimLeft(L". ");
  if (level_a > Integral::ALL) {
    str2.debug(L"str2");
  }
  if (str2.ne(L"Hello my name is ...     ")) {
    Error::handle(name(), L"trimLeft 2", Error::TEST, __FILE__, __LINE__);
  }

  str2.trimLeft(L"Hello ");
  if (str2.ne(L"my name is ...     ")) {
    str2.debug(L"str2");
    Error::handle(name(), L"trimLeft 3", Error::TEST, __FILE__, __LINE__);
  }
  
  str3.trimRight();
  if (level_a > Integral::ALL) {
    str3.debug(L"str3");
  }

  if (str3.ne(L"   ...Hello my name is ...")) {
    Error::handle(name(), L"trimRight 1", Error::TEST, __FILE__, __LINE__);
  }
  
  str3.trimRight(L". ");
  if (level_a > Integral::ALL) {
    str3.debug(L"str3");
  }
  if (str3.ne(L"   ...Hello my name is")) {
    Error::handle(name(), L"trimRight 2", Error::TEST, __FILE__, __LINE__);
  }

  str3.trimRight(L"is"); 
  if (str3.ne(L"   ...Hello my name ")) {
    Error::handle(name(), L"trimRight 3", Error::TEST, __FILE__, __LINE__);
  }
  
 str1.assign(L"hello my name is Rick duncan");
  if (level_a > Integral::ALL) {
    str1.debug(L"str1");
  }
  str2.assign(str1);

  // test case conversion methods
  //
  str2.toUpper();
  if (level_a > Integral::ALL) {
    str2.debug(L"str2");
  }
  if (str2.ne(L"HELLO MY NAME IS RICK DUNCAN")) {
    Error::handle(name(), L"toUpper", Error::TEST, __FILE__, __LINE__);
  }
  
  str2.toLower();
  if (level_a > Integral::ALL) {
    str2.debug(L"str2");
  }
  if (str2.ne(L"hello my name is rick duncan")) {
    Error::handle(name(), L"toUpper", Error::TEST, __FILE__, __LINE__);
  }
  
  str2.toMixed();
  if (level_a > Integral::ALL) {
    str2.debug(L"str2");
  }
  if (str2.ne(L"Hello My Name Is Rick Duncan")) {
    Error::handle(name(), L"toUpper", Error::TEST, __FILE__, __LINE__);
  }
  
  str3.assign(L"hello my name is rick duncan");
  str3.toMixed();
  if (level_a > Integral::ALL) {
    str3.debug(L"str3");
  }
  if (str3.ne(L"Hello My Name Is Rick Duncan")) {
    Error::handle(name(), L"toMixed", Error::TEST, __FILE__, __LINE__);
  }

  str3.assign(L"hello my-name is rick_duncan");
  str2.assign(L"-_ ");
  str3.toMixed(str2);
  if (str3.ne(L"Hello My-Name Is Rick_Duncan")) { 
    str3.debug(L"str2 ");
    Error::handle(name(), L"toMixed", Error::TEST, __FILE__, __LINE__);
  }
  
  // reset indentation
  //
  if (level_a > Integral::NONE) {
    Console::decreaseIndention();
  }

  //---------------------------------------------------------------------------
  //
  // 8. class-specific public methods:
  //     string search methods
  //
  //---------------------------------------------------------------------------

  // set indentation
  //
  if (level_a > Integral::NONE) {
    Console::put(L"testing class-specific public methods: string search methods...\n");
    Console::increaseIndention();
  }

  // test search methods
  //
  str1.assign(L"Hello, I'm Rick Duncan. People call me Rick Duncan");
  str2.assign(L"Rick");
  str3.assign(L"Ricky");
  str4.assign(str3);
  
  int32 pos = str1.firstStr(str2);
  if (pos != 11) {
    Error::handle(name(), L"firstStr 0", Error::TEST, __FILE__, __LINE__);
  }
  pos = str1.firstStr(str2, 12);
  if (pos != 39) {
    Error::handle(name(), L"firstStr 1", Error::TEST, __FILE__, __LINE__);
  }
  
  pos = str1.firstStr(str3);
  if (pos != Integral::NO_POS) {
    Error::handle(name(), L"firstStr 2", Error::TEST, __FILE__, __LINE__);
  }

  pos = str3.firstStr(str4);
  if (pos != 0) {
    Error::handle(name(), L"firstStr 2", Error::TEST, __FILE__, __LINE__);
  }

  pos = str3.lastStr(str4);
  if (pos != 0) {
    fprintf(stdout, "pos = %ld\n",(long) pos);
    Error::handle(name(), L"lastStr 2", Error::TEST, __FILE__, __LINE__);
  }
  
  pos = str1.firstStr(str2, 41);
  if (pos != Integral::NO_POS) {
    Error::handle(name(), L"firstStr 3", Error::TEST, __FILE__, __LINE__);
  }
  
  pos = str1.lastStr(str2);
  if (pos != 39) {
    Error::handle(name(), L"lastStr 0", Error::TEST, __FILE__, __LINE__);
  }
  
  pos = str1.lastStr(str2, 41);
  if (pos != 11) {
    Error::handle(name(), L"lastStr 1", Error::TEST, __FILE__, __LINE__);
  }
  
  pos = str1.lastStr(str3);
  if (pos != Integral::NO_POS) {
    Error::handle(name(), L"lastStr 2", Error::TEST, __FILE__, __LINE__);
  }
  
  pos = str1.lastStr(str2, 13);
  if (pos != Integral::NO_POS) {
    Error::handle(name(), L"lastStr 3", Error::TEST, __FILE__, __LINE__);
  }

  str1.assign(L"hello");
  str2.assign(L"..hi, world");
  if (str2.firstChr(str1) != 2) {
    Error::handle(name(), L"firstChr 1", Error::TEST, __FILE__, __LINE__);
  }

  if (str2.lastChr(str1) != 9) {
    Error::handle(name(), L"firstChr 1", Error::TEST, __FILE__, __LINE__);
  }

  if (str2.firstChr(L"he") != 2) {
    Error::handle(name(), L"firstChr 1", Error::TEST, __FILE__, __LINE__);
  }

  if (str2.lastChr(L"hi") != 3 ) {
    fprintf(stdout, "firstChr=%ld",(long) str2.firstChr(str1));
    Error::handle(name(), L"lastChr 1", Error::TEST, __FILE__, __LINE__);
  }

  if(str2.firstChr((unichar)'h') != 2) {
    Error::handle(name(), L"firstChr 1", Error::TEST, __FILE__, __LINE__);
  }

  if (str2.lastChr(L"l") != 9) {
    Error::handle(name(), L"lastChr 1", Error::TEST, __FILE__, __LINE__);
  }
  
  str1.assign(L"  123aBCd,456  ");
  
  if (str1.firstAlnum() != 2) {
    Error::handle(name(), L"firstAlnum", Error::TEST, __FILE__, __LINE__);
  }
  
  if (str1.firstAlpha() != 5) {
    Error::handle(name(), L"firstApha", Error::TEST, __FILE__, __LINE__);
  }

  if (str1.firstDigit() != 2) {
    Error::handle(name(), L"firstDigit", Error::TEST, __FILE__, __LINE__);
  }
  
  if (str1.firstLower() != 5) {
    Error::handle(name(), L"firstLower", Error::TEST, __FILE__, __LINE__);
  }

  if (str1.firstPrint() != 0) {
    Error::handle(name(), L"firstPrint", Error::TEST, __FILE__, __LINE__);
  }

  if (str1.firstPunct() != 9) {
    Error::handle(name(), L"firstPunct", Error::TEST, __FILE__, __LINE__);
  }
  
  if (str1.firstSpace() != 0) {
    Error::handle(name(), L"firstPunct", Error::TEST, __FILE__, __LINE__);
  }
  
  if (str1.firstUpper() != 6) {
    Error::handle(name(), L"firstPunct", Error::TEST, __FILE__, __LINE__);
  }

  str1.assign(L"  123aBCd,456  ");

  if (str1.lastAlnum() != 12) {
    Error::handle(name(), L"lastAlnum", Error::TEST, __FILE__, __LINE__);
  }

  if (str1.lastAlpha() != 8) {
    Error::handle(name(), L"lastApha", Error::TEST, __FILE__, __LINE__);
  }

  if (str1.lastDigit() != 12) {
    Error::handle(name(), L"lastDigit", Error::TEST, __FILE__, __LINE__);
  }
  
  if (str1.lastLower() != 8) {
    Error::handle(name(), L"lastLower", Error::TEST, __FILE__, __LINE__);
  }

  if (str1.lastPrint() != 14) {
    Error::handle(name(), L"lastPrint", Error::TEST, __FILE__, __LINE__);
  }

  if (str1.lastPunct() != 9) {
    Error::handle(name(), L"lastPunct", Error::TEST, __FILE__, __LINE__);
  }
  
  if (str1.lastSpace() != 14) {
    Error::handle(name(), L"lastSpace", Error::TEST, __FILE__, __LINE__);
  }
  
  if (str1.lastUpper() != 7) {
    Error::handle(name(), L"lastUpper", Error::TEST, __FILE__, __LINE__);
  }

  str1.assign(L"13, Aab ");

  if (str1.firstNotAlnum() != 2) {
    Error::handle(name(), L"firstNotAlnum", Error::TEST, __FILE__, __LINE__);
  }
  
  if (str1.firstNotAlpha() != 0) {
    Error::handle(name(), L"firstNotApha", Error::TEST, __FILE__, __LINE__);
  }

  if (str1.firstNotDigit() != 2) {
    Error::handle(name(), L"firstNotDigit", Error::TEST, __FILE__, __LINE__);
  }
  
  if (str1.firstNotLower() != 0) {
    Error::handle(name(), L"firstNotLower", Error::TEST, __FILE__, __LINE__);
  }

  if (str1.firstNotPrint() != Integral::NO_POS) {
    Error::handle(name(), L"firstNotPrint", Error::TEST, __FILE__, __LINE__);
  }

  if (str1.firstNotPunct() != 0) {
    Error::handle(name(), L"firstNotPunct", Error::TEST, __FILE__, __LINE__);
  }
  
  if (str1.firstNotSpace() != 0) {
    Error::handle(name(), L"firstNotSpace", Error::TEST, __FILE__, __LINE__);
  }
  
  if (str1.firstNotUpper() != 0) {
    Error::handle(name(), L"firstNotUpper", Error::TEST, __FILE__, __LINE__);
  }

  str1.assign(L"13, ABb ");
  
  if (str1.lastNotAlnum() != 7) {
    Error::handle(name(), L"lastNotAlnum", Error::TEST, __FILE__, __LINE__);
  }
  
  if (str1.lastNotAlpha() != 7) {
    Error::handle(name(), L"lastNotApha", Error::TEST, __FILE__, __LINE__);
  }

  if (str1.lastNotDigit() != 7) {
    Error::handle(name(), L"lastNotDigit", Error::TEST, __FILE__, __LINE__);
  }
  
  if (str1.lastNotLower() != 7) {
    Error::handle(name(), L"lastNotLower", Error::TEST, __FILE__, __LINE__);
  }

  if (str1.lastNotPrint() != Integral::NO_POS) {
    Error::handle(name(), L"lastNotPrint", Error::TEST, __FILE__, __LINE__);
  }

  if (str1.lastNotPunct() != 7) {
    Error::handle(name(), L"lastNotPunct", Error::TEST, __FILE__, __LINE__);
  }
  
  if (str1.lastNotSpace() != 6) {
    Error::handle(name(), L"lastNotSpace", Error::TEST, __FILE__, __LINE__);
  }
  
  if (str1.lastNotUpper() != 7) {
    Error::handle(name(), L"lastNotUpper", Error::TEST, __FILE__, __LINE__);
  }

  // test tokenization methods
  //
  str1.assign(L"oscar had a heap of apples");
  SysString sub_str;
  pos = 0;
  
  SysString temp_space(L" ");
  
  if (str1.tokenize(sub_str, pos, L" ")) {
    if (level_a > Integral::ALL) {
      sub_str.debug(L"token");
    }
  }

  while (str1.tokenize(sub_str, pos, L" ")) {
    if (level_a > Integral::ALL) {
      sub_str.debug(L"token");
    }
  }

  int32 tok = str1.countTokens(L" ");
  if (tok != 6) {
    Error::handle(name(), L"countTokens", Error::TEST, __FILE__, __LINE__);
  }
  
  int32 num_delim = str1.countDelimiters();
  if (num_delim != 5) {
    Error::handle(name(), L"countDelimiters", Error::TEST, __FILE__, __LINE__);
  }
  
  // test symbolPad methods
  //
  str1.assign(L"{where |what}&|(did) (I) ( do }");
  str2.assign(L"{}()&|");
  str1.symbolPad(str2);

  if (level_a > Integral::ALL) {
    str1.debug(L"padded");
  }
  if (str1.ne(L"{ where | what } & | ( did ) ( I ) ( do }")) {
    Error::handle(name(), L"symbolPad", Error::TEST, __FILE__, __LINE__);
  }

  // testing debugStr methods
  //
  str1.assign(L"testing method");
  str2.debugStr(name(), L"test", L"variable", str1);
  if (level_a > Integral::ALL) {
    str1.debug(L"str1");
    str2.debug(L"str2");
    Console::put(L"\n");
  }
  if (str2.ne(L"<SysString::test> variable = testing method")) {
    Error::handle(name(), L"debugStr", Error::TEST, __FILE__, __LINE__);
  }
  
  str1.assign(L"2nd testing method");
  str2.debugStr(name(), L"test2", L"variable", str1);

  if (level_a > Integral::ALL) {
    str1.debug(L"str1");
    str2.debug(L"str2");
    Console::put(L"\n");
  }
  if (str2.ne(L"<SysString::test2> variable = 2nd testing method")) {
    Error::handle(name(), L"debugStr", Error::TEST, __FILE__, __LINE__);
  }

  // test getEmptyString methods
  //
  if (getEmptyString().length() != 0) {
    return Error::handle(name(), L"getEmptyString", Error::TEST,
                         __FILE__, __LINE__);
  }
  
  // reset indentation
  //
  if (level_a > Integral::NONE) {
    Console::decreaseIndention();
  }
  
  //---------------------------------------------------------------------------
  //
  // 9. print completion message
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
