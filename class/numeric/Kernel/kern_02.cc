// file: $isip/class/algo/Kernel/kern_02.cc
// version: $Id: kern_02.cc 7197 2001-07-20 15:51:56Z hamaker $
//

// isip include files
//
#include "Kernel.h"
#include <Console.h>

// method: diagnose
//
// arguments:
//  Integral::DEBUG level: (input) debug level for diagnostics
//
// return: a bool8 value indicating status
//
bool8 Kernel::diagnose(Integral::DEBUG level_a) {

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
  //     class constructors
  //
  //--------------------------------------------------------------------------

  // set indentation
  //
  if (level_a > Integral::NONE) {
    Console::put(L"testing required public methods...\n");
    Console::increaseIndention();
  }
  
  Kernel kern0;
  kern0.setAlgorithm(LINEAR);
  kern0.init();

  Kernel kern1(kern0);
  
  if (!kern1.eq(kern0)) {
    return Error::handle(name(), L"copy constructor", Error::TEST,
			 __FILE__, __LINE__);
  }

  // test large allocation construction and deletion
  //
  if (level_a == Integral::ALL) {
    
    Console::put(L"\ntesting large chunk memory allocation and deletion:\n");
    
    // set the memory to a strange block size so we can hopefully catch any
    // frame overrun errors
    //
    
    Kernel::setGrowSize((int32)500);
    
    Kernel* pkern = new Kernel();

    for (int32 j = 1; j <= 100; j++) {
      Kernel** pkerns = new Kernel*[j * 100];
      
      // create the objects
      //
    for (int32 i = 0; i < j * 100; i++) {
      pkerns[i] = new Kernel();
    }
    
    // delete objects
    //
    for (int32 i = (j * 100) - 1; i >= 0; i--) {
      delete pkerns[i];
    }
    
    delete [] pkerns;
    } 
    
    delete pkern;
  }

  // reset indentation
  //
  if (level_a > Integral::NONE) {
    Console::decreaseIndention();
  }
  
  //--------------------------------------------------------------------------
  //
  // 2. required public methods
  //     i/o methods 
  //
  //--------------------------------------------------------------------------

  // set indentation
  //
  if (level_a > Integral::NONE) {
    Console::put(L"testing required public methods: i/o methods...\n");
    Console::increaseIndention();
  }

  // declare a reference object
  //
  kern0.setAlgorithm(RBF);
  kern0.init();

  // we need binary and text sof files
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

  kern0.write(tmp_file0, (int32)0);
  kern0.write(tmp_file1, (int32)0);

  // close the files
  //
  tmp_file0.close();
  tmp_file1.close();

  // open the files in read mode
  //
  tmp_file0.open(tmp_filename0);
  tmp_file1.open(tmp_filename1);

  // read the object back
  //
  kern1.read(tmp_file0, (int32)0);
  kern1.init();

  if (!kern0.eq(kern1)) {
    return Error::handle(name(), L"i/o", Error::TEST,
			 __FILE__, __LINE__);
  }
    
  kern1.read(tmp_file1, (int32)0);
  kern1.init();

  if (!kern0.eq(kern1)) {
    return Error::handle(name(), L"i/o", Error::TEST,
			 __FILE__, __LINE__);
  }
    
  // close and delete the temporary files
  //
  tmp_file0.close();
  tmp_file1.close();
  File::remove(tmp_filename0);
  File::remove(tmp_filename1);

  // reset indentation
  //
  if (level_a > Integral::NONE) {
    Console::decreaseIndention();
  }

  //--------------------------------------------------------------------------
  //
  // 3. class-specific public methods
  //     set and get methods
  //
  //--------------------------------------------------------------------------

  // set indentation
  //
  if (level_a > Integral::NONE) {  
    Console::put(L"testing class-specific public methods: set and get methods...\n");
    Console::increaseIndention();
  }

  // establish an object
  //
  kern0.setAlgorithm(SIGMOID);
  VectorFloat tmp(L"1.4, 3.0");

  // check that the values were set
  //
  if (kern0.algorithm_d != SIGMOID) {
    return Error::handle(name(), L"setAlgorithm", Error::TEST,
			 __FILE__, __LINE__);
  }

  // test setConstants
  //
  kern0.setConstants(tmp);

  if (!kern0.constants_d.eq(tmp)) {
    return Error::handle(name(), L"setConstants", Error::TEST,
			 __FILE__, __LINE__);
  }

  // reset indentation
  //
  if (level_a > Integral::NONE) {
    Console::decreaseIndention();
  }
  
  //--------------------------------------------------------------------------
  //
  // 4. class-specific public methods
  //     computation methods
  //
  //--------------------------------------------------------------------------

  // set indentation
  //
  if (level_a > Integral::NONE) {  
    Console::put(L"testing class-specific public methods: computational methods...\n");
    Console::increaseIndention();
  }

  // test the basic compute method under each algorithm:
  //  create two simple test vectors
  //
  VectorFloat x_flt(L"1, 3, 5");
  VectorFloat y_flt(L"2, 4, 6");

  VectorDouble x_dbl(L"1, 3, 5");
  VectorDouble y_dbl(L"2, 4, 6");

  float32 output_flt;
  float64 output_dbl;

  Double ans;

  // test the linear kernel
  //
  kern0.setAlgorithm(LINEAR);
  kern0.init();

  ans = 44.0;

  kern0.compute(output_flt, x_flt, y_flt);
  kern0.compute(output_dbl, x_dbl, y_dbl);

  if (!ans.almostEqual(output_flt) || !ans.almostEqual(output_dbl)) {
    return Error::handle(name(), L"compute", Error::TEST,
			 __FILE__, __LINE__);
  }

  // test the polynomial kernel
  //
  kern0.setAlgorithm(POLYNOMIAL);
  kern0.init();

  ans = 91125;

  kern0.compute(output_flt, x_flt, y_flt);
  kern0.compute(output_dbl, x_dbl, y_dbl);

  if (!ans.almostEqual(output_flt) || !ans.almostEqual(output_dbl)) {
    return Error::handle(name(), L"compute", Error::TEST,
			 __FILE__, __LINE__);
  }

  // test the rbf kernel
  //
  kern0.setAlgorithm(RBF);
  kern0.init();

  ans = 0.22313016;

  kern0.compute(output_flt, x_flt, y_flt);
  kern0.compute(output_dbl, x_dbl, y_dbl);

  if (!ans.almostEqual(output_flt) || !ans.almostEqual(output_dbl)) {
    return Error::handle(name(), L"compute", Error::TEST,
			 __FILE__, __LINE__);
  }

  // test the sigmoid kernel
  //
  kern0.setAlgorithm(SIGMOID);
  kern0.init();

  ans = 1.0000000;

  kern0.compute(output_flt, x_flt, y_flt);
  kern0.compute(output_dbl, x_dbl, y_dbl);

  if (!ans.almostEqual(output_flt) || !ans.almostEqual(output_dbl)) {
    return Error::handle(name(), L"compute", Error::TEST,
			 __FILE__, __LINE__);
  }

  // reset indentation
  //
  if (level_a > Integral::NONE) {
    Console::decreaseIndention();
  }

  //--------------------------------------------------------------------------
  //
  // 5. print completion message
  //
  //--------------------------------------------------------------------------

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
