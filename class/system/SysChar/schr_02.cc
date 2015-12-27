// file: $isip/class/system/SysChar/schr_02.cc
// version: $Id: schr_02.cc 7770 2002-02-20 20:41:47Z yuan $
//

// isip include files
//
#include "SysChar.h"
#include <SysString.h>
#include <Console.h>
 
// method: diagnose
//
// arguments:
//  Integral::DEBUG level: (input) debug level for diagnostics
//
// return: a bool8 value indicating status
//
bool8 SysChar::diagnose(Integral::DEBUG level_a) {

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
 
  // test the constructors:
  //  assign method is being tested inside copy constructor
  //
  SysChar* ptr0, *ptr1, *ptr2, *ptr3;
  ptr0 = new SysChar();
  ptr1 = new SysChar(*ptr0);
  ptr2 = new SysChar(L'e');
  ptr3 = new SysChar((byte8*)"h");

  SysChar c0;
  SysChar c1(c0);
  SysChar c2(L'e');
  SysChar c3((byte8*)"h");
  
  SysChar c4(L'.');
  SysChar c5(L'\n');
  SysChar c6(L'9');
  SysChar c7(c2);
  SysChar c8;
  
  // test the destructors
  //
  delete ptr0;
  delete ptr1;
  delete ptr2;
  delete ptr3;

  // test the debug methods
  //
  setDebug(debug_level_d);

  if (level_a > Integral::BRIEF) {
    c0.debug(L"debug");
  }  

  // test the operator= method
  //
  c0 = c1;
  
  // test eq methods
  //
  if (!c7.eq(c2)) {
    Error::handle(name(), L"eq", Error::TEST, __FILE__, __LINE__);
  }

  // test the clear methods
  //
  c8.clear(Integral::RELEASE);

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
  //--------------------------------------------------------------------------

  // set indentation
  //
  if (level_a > Integral::NONE) {
      Console::put(L"testing class-specific public methods: extensions to required methods...\n");
	 Console::increaseIndention();
  }

  // test the constructor
  //
  int32 len;
  SysChar c9((byte8*)"");
  
  // test assign methods
  //
  c0.assign(L't');
  c1.assign((byte8)'e');
  c2.assign((byte8)180);
  c3.assign(len, (byte8*)"");

  // test eq methods
  //
  if (c7.eq((unichar)L's')) {
    Error::handle(name(), L"ne", Error::TEST, __FILE__, __LINE__);
  }
  
  // test ne methods
  //
  if (!c7.ne(c2)) {
    Error::handle(name(), L"eq", Error::TEST, __FILE__, __LINE__);
  }

  if (c7.ne((unichar)L'e')) {
    Error::handle(name(), L"ne", Error::TEST, __FILE__, __LINE__);
  }

  // test the memSize methods
  //
  c7.memSize();

  // reset indentation
  //
  if (level_a > Integral::NONE) {
     
	Console::decreaseIndention();
  }
  
  //---------------------------------------------------------------------------
  //
  // 3. class-specific public methods:
  //     casting and conversion methods   
  //
  //--------------------------------------------------------------------------

  // set indentation
  //
  if (level_a > Integral::NONE) {
      
    Console::put(L"testing class-specific public methods: casting and conversion methods...\n");
    Console::increaseIndention();
  }

  // test operator unichar() method
  //
  unichar temp = c0;
  
  if (temp != (unichar)'t') {
    Error::handle(name(), L"operator unichar ()", Error::TEST,
		  __FILE__, __LINE__);
  }

  // declare local variables to test get methods
  //
  unichar x0;
  byte8 x1;
  byte8 buf[5];

  // test get methods
  //
  c0.get(x0);
  c1.get(len, (byte8*)buf);
  c3.get(x1);
  
  if (x0 != (byte8)'t') {
    Error::handle(name(), L"get", Error::TEST, __FILE__, __LINE__);
  }
  if (*buf != (byte8)'e') {
    Error::handle(name(), L"get", Error::TEST, __FILE__, __LINE__);
  }
  if (x1 != L'') {
    Error::handle(name(), L"get", Error::TEST, __FILE__, __LINE__);
  }  

  // test case conversion methods
  //
  c1.toUpper();
  if (c1 != L'E') {
    Error::handle(name(), L"toUpper", Error::TEST, __FILE__, __LINE__);
  }
  
  c5.assign(c3);
  c3.toUpper();
  if (c3 != c5) {
    Error::handle(name(), L"toUpper", Error::TEST, __FILE__, __LINE__);
  }
  
  c3.toLower();
  if (c3 != c5) {
    Error::handle(name(), L"toLower", Error::TEST, __FILE__, __LINE__);
  }
  
  c1.toLower();
  if (c1 != L'e') {
    Error::handle(name(), L"toLower", Error::TEST, __FILE__, __LINE__);
  }
  
  // reset indentation
  //
  if (level_a > Integral::NONE) {
      
	Console::decreaseIndention();
  }

  //---------------------------------------------------------------------------
  //
  // 4. class-specific public methods:
  //     character classification methods
  //
  //--------------------------------------------------------------------------

  // set indentation
  //
  if (level_a > Integral::NONE) {
    Console::put(L"testing class-specific public methods: character classification methods...\n");
    Console::increaseIndention();
  }

  // test isAlnum methods
  //
  if ((!c0.isAlnum()) ||
      (!c1.isAlnum()) ||
      (c2.isAlnum()) ||
      (c3.isAlnum()) ||
      (c4.isAlnum()) ||
      (c5.isAlnum()) ||
      (!c6.isAlnum())) {
    Error::handle(name(), L"isAlnum", Error::TEST, __FILE__, __LINE__);
  }

  // test isAlpha methods
  //  
  if ((!c0.isAlpha()) ||
      (!c1.isAlpha()) ||
      (c2.isAlpha()) ||
      (c3.isAlpha()) ||
      (c4.isAlpha()) ||
      (c5.isAlpha()) ||
      (c6.isAlpha())) {
    Error::handle(name(), L"isAlpha", Error::TEST, __FILE__, __LINE__);
  }

  // test isDigit methods
  //  
  if ((c0.isDigit()) ||
      (c1.isDigit()) ||
      (c2.isDigit()) ||
      (c3.isDigit()) ||
      (c4.isDigit()) ||
      (c5.isDigit()) ||
      (!c6.isDigit())) {
    Error::handle(name(), L"isDigit", Error::TEST, __FILE__, __LINE__);
  }

  // test isLower methods
  //  
  if ((!c0.isLower()) ||
      (!c1.isLower()) ||
      (c2.isLower()) ||
      (c3.isLower()) ||
      (c4.isLower()) ||
      (c5.isLower()) ||
      (c6.isLower())) {
    Error::handle(name(), L"isLower", Error::TEST, __FILE__, __LINE__);
  }

  // test isPrint methods
  //  
  if ((!c0.isPrint()) ||
      (!c1.isPrint()) ||
      (c2.isPrint()) ||
      (c3.isPrint()) ||
      (!c4.isPrint()) ||
      (c5.isPrint()) ||
      (!c6.isPrint())) {
    Error::handle(name(), L"isPrint", Error::TEST, __FILE__, __LINE__);
  }

  // test isPunct methods
  //  
  if ((c0.isPunct()) ||
      (c1.isPunct()) ||
      (c2.isPunct()) ||
      (c3.isPunct()) ||
      (!c4.isPunct()) ||
      (c5.isPunct()) ||
      (c6.isPunct())) {
    Error::handle(name(), L"isPunct", Error::TEST, __FILE__, __LINE__);
  }

  // test isSpace methods
  //  
  if ((c0.isSpace()) ||
      (c1.isSpace()) ||
      (c2.isSpace()) ||
      (!c3.isSpace()) ||
      (c4.isSpace()) ||
      (!c5.isSpace()) ||
      (c6.isSpace())) {
    Error::handle(name(), L"isSpace", Error::TEST, __FILE__, __LINE__);
  }

  // test isUpper methods
  //  
  if ((c0.isUpper()) ||
      (c1.isUpper()) ||
      (c2.isUpper()) ||
      (c3.isUpper()) ||
      (c4.isUpper()) ||
      (c5.isUpper()) ||
      (c6.isUpper())) {
    Error::handle(name(), L"isUpper", Error::TEST, __FILE__, __LINE__);
  }
  
  // reset indentation
  //
  if (level_a > Integral::NONE) {
				   Console::decreaseIndention();
  }

  //---------------------------------------------------------------------------
  //
  // 5. class-specific public methods:
  //     relational and logical methods
  //
  //--------------------------------------------------------------------------

  // set indentation
  //
  if (level_a > Integral::NONE) {
    Console::put(L"testing class-specific public methods: relational and logical methods...\n");
    Console::increaseIndention();
  }

  // test relational methods
  //
  c0.assign(L't');
  c1.assign(L'e');
  if ((c0.eq(c1)) ||
      (c0.eq((unichar)L'e')) ||
      (!c0.ne(c1)) ||
      (c0.ne((unichar)L't')) ||
      (!c0.gt(c1)) ||
      (!c0.gt(L'e')) ||
      (c0.lt(c1)) ||
      (c0.lt(L'e')) ||
      (!c0.ge(c1)) ||
      (!c0.ge(L'e')) ||
      (c0.le(c1)) ||
      (c0.le(L'e'))) {
    Error::handle(name(), L"equality", Error::TEST, __FILE__, __LINE__);
  }
  
  // reset indentation
  //
  if (level_a > Integral::NONE) {
	    Console::decreaseIndention();
  }

  //---------------------------------------------------------------------------
  //
  // 6. print completion message
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
