// file: $isip/class/system/Checksum/cksm_02.cc
// version: $Id: cksm_02.cc 5553 2000-11-17 18:15:35Z duncan $
//

// isip include files
//
#include "Checksum.h"
#include <Console.h>
// method: diagnose
//
// arguments:
//  Integral::DEBUG level: (input) debug level for diagnostics
//
// return: a bool8 value indicating status
//
bool8 Checksum::diagnose(Integral::DEBUG level_a) {

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
    Checksum tmp;
    tmp.debug(L"debug");
  }
  
  // testing class constructors
  //
  Checksum cksm_1;
  Checksum cksm_2(cksm_1);
  Checksum cksm_3;

  // testing the operator= operator and assign method
  //
  cksm_3 = cksm_1;

  // testing i/o methods 
  //

  // testing the equality method
  //
  if (!cksm_3.eq(cksm_1)) {
    return Error::handle(name(), L"assign method/eq", Error::TEST,
			 __FILE__, __LINE__);
  }  
  if (!cksm_2.eq(cksm_1)) {
    return Error::handle(name(), L"copy constructor/eq", Error::TEST,
			 __FILE__, __LINE__);
  }
  
  // testing memory management methods
  //
  Checksum::setGrowSize((int32)500);

  for (int32 j = 1; j <= 10; j++) {
    Checksum** dyn_cal = new Checksum*[j * 100];
    
    // create the objects
    //
    for (int32 i = 0; i < j * 100; i++) {
      dyn_cal[i] = new Checksum();
    }
    
    // delete objects
    //
    for (int32 i = (j * 100) - 1; i >= 0; i--) {
      delete dyn_cal[i];
    }
      
    delete [] dyn_cal;
  }

  // reset indentation
  //
  if (level_a > Integral::NONE) {
    Console::decreaseIndention();
  }

  //---------------------------------------------------------------------
  //
  // 2. class-specific public methods
  //     set and get methods
  //
  //---------------------------------------------------------------------

  // set indentation
  //
  if (level_a > Integral::NONE) {
    Console::put(L"testing class-specific public methods: set and get methods...\n");
    Console::increaseIndention(); 
  }

  // set the algorithm
  //
  Checksum cksm_6;

  if (!cksm_6.setAlgorithm(CRC_16_CCITT)) {
    return Error::handle(name(), L"set algorithm", Error::TEST,
			 __FILE__, __LINE__);
  }
  
  // set the implementation
  //
  if (!cksm_6.setImplementation(FAST)) {
    return Error::handle(name(), L"set implementation", Error::TEST,
			 __FILE__, __LINE__);
  }

  // get the algorithm
  //
  if (cksm_6.getAlgorithm() != CRC_16_CCITT) {
    return Error::handle(name(), L"get algorithm", Error::TEST,
			 __FILE__, __LINE__);
  }
  
  // get the implementation
  //
  if (cksm_6.getImplementation() != FAST) {
    return Error::handle(name(), L"get implementation", Error::TEST,
			 __FILE__, __LINE__);
  }

  //---------------------------------------------------------------------
  //
  // 3. class-specific public methods
  //     initialization and computational methods
  //
  //---------------------------------------------------------------------
  
  // create some reference data
  //
  SysString input_1(L"Joe");
  SysString input_2(L"abcdefghijkl");
  uint32 answer_1 = 42810;
  uint32 answer_2 = 15564;

  // compute answer_1
  //
  Console::increaseIndention();
  cksm_6.init();
  cksm_6.compute(input_1);
  uint32 result = cksm_6.get();
  Console::decreaseIndention();
  
  // finally, check the result
  //
  if (result != answer_1) {
    return  Error::handle(name(), L"compute", ERR,
			  __FILE__, __LINE__);
  }

  // compute answer_2
  //
  Console::increaseIndention();
  cksm_6.init();
  cksm_6.compute(input_2);
  result = cksm_6.get();
  Console::decreaseIndention();
  
  // finally, check the result
  //
  if (result != answer_2) {
    return  Error::handle(name(), L"compute", ERR,
			  __FILE__, __LINE__);
  }

  // compute answer_1 through the byte8 interface
  //
  cksm_6.init();
  cksm_6.compute((byte8*)input_1, input_1.length());
  result = cksm_6.get();

  if (result != answer_1) {
    return  Error::handle(name(), L"compute", ERR,
			  __FILE__, __LINE__);
  }

  // compute answer_2 through the byte8 interface
  //
  cksm_6.init();
  cksm_6.compute((byte8*)input_2, input_2.length());
  result = cksm_6.get();

  if (result != answer_2) {
    return  Error::handle(name(), L"compute", ERR,
			  __FILE__, __LINE__);
  }

  

  // reset indentation
  //
  if (level_a > Integral::NONE) {
    Console::decreaseIndention();
  }
  
  //---------------------------------------------------------------------
  //
  // 4. print completion message
  //
  //---------------------------------------------------------------------

  // reset indentation
  //
  if (level_a > Integral::NONE) {
    Console::decreaseIndention();
  }
  
  if (level_a > Integral::NONE) {
    SysString output(L"diagnostics passed for class");
    output.concat(name());
    output.concat(L"\n");
    Console::put(output);
  }

  // exit gracefully
  //
  return true;
}

