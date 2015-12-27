// file: $isip/class/numeric/Chebyshev/cheb_02.cc
// version: $Id: cheb_02.cc 7150 2001-07-04 23:58:10Z picone $
//

// isip include files
//
#include <Console.h>
#include "Chebyshev.h"

// method: diagnose
//
// arguments:
//  Integral::DEBUG level: (input) debug level for diagnostics
//
// return: a bool8 value indicating status
//
bool8 Chebyshev::diagnose(Integral::DEBUG level_a) {
  
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
  Chebyshev chebyshev_fw;
  
  Chebyshev::setGrowSize((int32)500);

  for (int32 j = 1; j <= 100; j++) {
    Chebyshev** ml = new Chebyshev*[j * 100];
    
    // create the objects
    //
    for (int32 i = 0; i < j * 100; i++) {
      ml[i] = new Chebyshev();
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

  // check the compute methods using the vector method (which in turn checks
  // the scalar methods)
  //
  VectorFloat inp(L"1.0, 2.0");
  VectorFloat ans(L"1.0, 7.0");
  VectorFloat out;
  
  Chebyshev::compute(out, inp, 2);

  if (!ans.almostEqual(out)) {
    ans.debug(L"expected result:");
    out.debug(L"wrong result:");
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
