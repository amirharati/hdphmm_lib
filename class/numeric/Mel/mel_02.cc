// file: $isip/class/numeric/Mel/mel_02.cc
// version: $Id: mel_02.cc 6808 2001-04-24 15:39:20Z srivasta $
//

// isip include files
//
#include <Console.h>
#include "Mel.h"

// method: diagnose
//
// arguments:
//  Integral::DEBUG level: (input) debug level for diagnostics
//
// return: a bool8 value indicating status
//
bool8 Mel::diagnose(Integral::DEBUG level_a) {
  
  //---------------------------------------------------------------------
  //
  // 0. preliminaries
  //
  //---------------------------------------------------------------------

  // output the class name
  //
  if (level_a > Integral::NONE) {
    String output(L"diagnosing class ");
    output.concat(CLASS_NAME);
    output.concat(L": ");
    Console::put(output);
    Console::increaseIndention();
  } 

  //--------------------------------------------------------------------
  //
  // 1. required public methods
  //
  //--------------------------------------------------------------------

  // set indentation
  //
  if (level_a > Integral::NONE) {
    Console::put(L"testing required public methods...\n");
    Console::increaseIndention();
  }

  // test destructor/constructor(s) and memory management
  //
  Mel mel_fw;
  
  Mel::setGrowSize((int32)500);

  for (int32 j = 1; j <= 100; j++) {
    Mel** ml = new Mel*[j * 100];
    
    // create the objects
    //
    for (int32 i = 0; i < j * 100; i++) {
      ml[i] = new Mel();
    }
    
    // delete objects
    //
    for (int32 i = (j * 100) - 1; i >= 0; i--) {
      delete ml[i];
    }
    
    delete [] ml;
  }
  
  // reset indentation
  //
  if (level_a > Integral::NONE) {
    Console::decreaseIndention();
  }
  
  //--------------------------------------------------------------------------
  //
  // 2. class-specific public methods:
  //     computational methods
  //
  //--------------------------------------------------------------------------

  // set indentation
  //
  if (level_a > Integral::NONE) {
    Console::put(L"testing class-specific public methods: computational methods...\n");
    Console::increaseIndention();
  }

  // declare the test variables
  //
  VectorFloat vec_input1;
  VectorFloat vec_output_mel1;
  VectorFloat res_vec_output_mel1;

  vec_input1.assign(L"100, 500, 1000, 1500");  
  res_vec_output_mel1.assign(L"150.48910241, 607.44591966, 999.98553714, 1290.5574429");

  mel_fw.compute(vec_output_mel1, vec_input1);

  if (!vec_output_mel1.almostEqual(res_vec_output_mel1)) {
    vec_output_mel1.debug(L"vec_output_mel1");
    res_vec_output_mel1.debug(L"res_vec_output_mel1");
    return Error::handle(name(), L"compute", Error::TEST, __FILE__, __LINE__);
  }

  // reset indentation
  //
  if (level_a > Integral::NONE) {
    Console::decreaseIndention();
  }
  
  //--------------------------------------------------------------------
  //
  // 4. print completion message
  //
  //--------------------------------------------------------------------

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
