// file: $isip/class/shell/DebugLevel/dbgl_02.cc
// version: $Id: dbgl_02.cc 9210 2003-06-15 14:48:40Z picone $
//

// isip include files
//
#include "DebugLevel.h"

// method: diagnose
//
// arguments:
//  Integral::DEBUG level: (input) debug level for diagnostics
//
// return: a bool8 value indicating status
//
bool8 DebugLevel::diagnose(Integral::DEBUG level_a) {

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

  // test constructors
  //
  DebugLevel val0;
  val0 = Integral::BRIEF;
   
  DebugLevel val1(val0);
  
  if (val0 != val1) {
    return Error::handle(name(), L"assign", Error::TEST, __FILE__, __LINE__);
  }

  // change val1 so it has a  different value
  //
  val1 = Integral::ALL; 

  // test the constructors
  //
  String val1_str;
  val1_str.assign(val1.getName());
  DebugLevel val2(val1_str);
  if (val1 != val2) {
    return Error::handle(name(), L"constructor",
			 Error::TEST, __FILE__, __LINE__);
  }

  // test the debug methods
  //
  setDebug(debug_level_d);

  if (level_a > Integral::BRIEF) {
    val0.debug(L"debug");
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
  DebugLevel val3;

  if ((!val2.read(tmp_file0, (int32)0)) || (val0 != val2)) {
    return Error::handle(name(), L"read", Error::TEST, __FILE__, __LINE__);
  }

  if ((!val2.read(tmp_file1, (int32)0)) || (val0 != val2)) {
    return Error::handle(name(), L"read", Error::TEST, __FILE__, __LINE__);
  }

  if ((!val3.read(tmp_file0, (int32)1)) || (val1 != val3)) {
    return Error::handle(name(), L"read", Error::TEST, __FILE__, __LINE__);
  }

  if ((!val3.read(tmp_file1, (int32)1)) || (val1 != val3)) {
    return Error::handle(name(), L"read", Error::TEST, __FILE__, __LINE__);
  }

  // close and delete the temporary files
  //
  tmp_file0.close();
  tmp_file1.close();
  File::remove(tmp_filename0);
  File::remove(tmp_filename1);
  
  // test memory-management methods
  //
  DebugLevel* ptr;

  DebugLevel::setGrowSize((int32)731);
  
  for (int32 j = 1; j <= 1000; j++) {
    ptr = new DebugLevel();
    *ptr = Integral::BRIEF;
    delete ptr;

    ptr = new DebugLevel[100];
    delete [] ptr;
  }
  
  // reset indentation
  //
  if (level_a > Integral::NONE) {
    Console::decreaseIndention();
  }
  
  //---------------------------------------------------------------------------
  //
  // 2. class-specific methods:
  //     extensions to required methods
  //
  //---------------------------------------------------------------------------

  // set indentation
  //
  if (level_a > Integral::NONE) {
    Console::put(L"testing class-specific methods: extensions to required methods...\n");
    Console::increaseIndention();
  }

  // test assign method
  //
  String str(L"BRIEF");
  
  val1.assign(str);

  if (val1 != val0) {
    return Error::handle(name(), L"assign", Error::TEST, __FILE__, __LINE__);
  }

  // test operator = methods
  //
  val1 = Integral::DETAILED;

  if (val1.eq(val0)) {
    return Error::handle(name(), L"operator=", Error::TEST,
			 __FILE__, __LINE__);
  }

  // test operator == methods
  //
  val1 = Integral::DETAILED;

  if (!(val1 == Integral::DETAILED)) {
    return Error::handle(name(), L"operator==", Error::TEST,
			 __FILE__, __LINE__);
  }
  
  // test operator > methods
  //
  if (!(val1 > Integral::BRIEF)) {
    return Error::handle(name(), L"operator>", Error::TEST,
			 __FILE__, __LINE__);
  }
  
  // test operator >= methods
  //
  if (!(val1 >= Integral::DETAILED)) {
    return Error::handle(name(), L"operator>=", Error::TEST,
			 __FILE__, __LINE__);
  }
  
  // test operator < methods
  //
  if (!(val0 < Integral::DETAILED)) {
    return Error::handle(name(), L"operator<", Error::TEST,
			 __FILE__, __LINE__);
  }
    
  // test operator <= methods
  //
  if (!(val1 <= Integral::DETAILED)) {
    return Error::handle(name(), L"operator<=", Error::TEST,
			 __FILE__, __LINE__);
  }
  
  // test operator != methods
  //
  if (!(val0 != Integral::DETAILED)) {
    return Error::handle(name(), L"operator!=", Error::TEST,
			 __FILE__, __LINE__);
  }
  
  // reset indentation
  //
  if (level_a > Integral::NONE) {
    Console::decreaseIndention();
  }

  //---------------------------------------------------------------------------
  //
  // 3. class-specific public methods:
  //     get methods
  //
  //---------------------------------------------------------------------------
  
  // set indentation
  //
  if (level_a > Integral::NONE) {
    Console::put(L"testing class-specific methods: get methods...\n");
    Console::increaseIndention();
  }

  // test getIndex methods
  //
  if (val0.getIndex(str) != (int32)1) {
    return Error::handle(name(), L"getIndex", Error::TEST, __FILE__, __LINE__);
  }

  // test getName methods
  //
  String str1(val0.getName());

  if (str1.ne(str)) {
    return Error::handle(name(), L"getName", Error::TEST, __FILE__, __LINE__);
  }

  // test casting operator
  //
  if (val0 != Integral::BRIEF) {
    return Error::handle(name(), L"cast", Error::TEST, __FILE__, __LINE__);
  }
 
  Integral::DEBUG dval0 = val0;
  if (dval0 != Integral::BRIEF) {
    return Error::handle(name(), L"cast", Error::TEST, __FILE__, __LINE__);
  }

  String sval0;
  sval0.insert(val0, 0);
  if (sval0.ne(L"BRIEF")) {
    return Error::handle(name(), L"cast", Error::TEST, __FILE__, __LINE__);
  }

  // reset indention
  //
  if (level_a > Integral::NONE) {
    Console::decreaseIndention();
  }

  //---------------------------------------------------------------------------
  //
  // 4. print completion message
  //
  //---------------------------------------------------------------------------

  // reset indentation
  //
  if (level_a > Integral::NONE) {
    Console::decreaseIndention();
  }
  
  if (level_a > Integral::NONE) {
    String output(L"diagnostics passed for class ");
    output.concat(name());
    output.concat(L"\n");
    Console::put(output);
  }
  
  // exit gracefully
  //
  return true;
}
