// file: $isip/class/vector/VectorComplexLong/vclng_02.cc
// version: $Id: vclng_02.cc 10636 2007-01-26 22:18:09Z tm334 $
//

// isip include files
//
#include <Console.h>
#include <String.h>
#include "VectorComplexLong.h"

// method: diagnose
//
// arguments:
//  Integral::DEBUG level: (input) debug level for diagnostics
//
// return: a bool8 value indicating status
//
bool8 VectorComplexLong::diagnose(Integral::DEBUG level_a) {
  
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
  //  MComplexVector<ComplexLong, complexlong>::diagnose(level_a);
  MVector<ComplexLong, complexlong>::diagnose(level_a);

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

  // test destructor/constructor(s)
  //
  VectorComplexLong val0(5);
  val0.assign(L"1, 3, 5, 7, 9");
  
  VectorComplexLong val1(val0);
  if (val0.ne(val1)) {
    return Error::handle(name(), L"copy constructor", Error::TEST,
			 __FILE__, __LINE__);
  }

  // test the operator= method
  //
  val1 = val0;
  if (val1.ne(val0)) { 
    return Error::handle(name(), L"=", Error::TEST, __FILE__, __LINE__);
  }

  // test io methods
  // create two special vectors of length 0 and 1
  //
  VectorComplexLong val_0;
  VectorComplexLong val_1(1, (complexlong)42);

  // create vectors to write
  //
  long test_size = 1024;
  VectorComplexLong val2;
  VectorComplexLong val3;
  VectorComplexLong val4(test_size);  
  for (int32 i = 0; i < test_size; i++) {
    val4(i) = (int32)i * 3;
  }
  
  // we need binary and text sof files
  //
  String tmp_filename0;
  Integral::makeTemp(tmp_filename0);
  String tmp_filename1;
  Integral::makeTemp(tmp_filename1);
  
  // open files in write mode
  //
  Sof text_file;
  text_file.open(tmp_filename0, File::WRITE_ONLY, File::TEXT);
  Sof bin_file;
  bin_file.open(tmp_filename1, File::WRITE_ONLY, File::BINARY);
  
  // write the values
  //
  val_0.write(text_file, 10);          // this is a 0 length vector
  val_0.write(bin_file, 10);
  
  val_1.write(text_file, 11);          // this is a single length vector
  val_1.write(bin_file, 11);
  
  val4.write(text_file, 7);         
  val4.write(bin_file, 7);
  
  // close the files
  //
  text_file.close();
  bin_file.close();

  // open the files in read mode
  //
  text_file.open(tmp_filename0);
  bin_file.open(tmp_filename1);
  
  val2.clear();
  
  // test reading zero and single element vector
  //
  if (!val2.read(text_file, 10) || (val2.length() != 0)) {
    val2.debug(L"length 0 vector");
    return Error::handle(name(), L"read-text", Error::TEST,__FILE__, __LINE__);
  }
  val2.clear();
    
  if (!val2.read(bin_file, 10) || (val2.length() != 0)) {
    val2.debug(L"length 0 vector");
    return Error::handle(name(), L"read-bin", Error::TEST,__FILE__, __LINE__);
  }
  val2.clear();
  
  if (!val2.read(text_file, 11) || (val2.length() != 1)
      || (!val2(0).almostEqual(42))) {
    val2.debug(L"length 1 vector");
    return Error::handle(name(), L"read-text", Error::TEST,__FILE__, __LINE__);
  }
  val2.clear();
  
  if (!val2.read(bin_file, 11) || (val2.length() != 1)
      || (!val2(0).almostEqual(42))) {
    val2.debug(L"length 1 vector");
    return Error::handle(name(), L"read-bin", Error::TEST,__FILE__, __LINE__);
  }
  val2.clear();
  
  // read the other values back in
  //
  if (!val2.read(text_file, 7) || (!val4.almostEqual(val2))) {
    return Error::handle(name(), L"read-big-text", Error::TEST,
			 __FILE__, __LINE__);
  }
  val2.clear();
  
  if (!val2.read(bin_file, 7) || (!val4.almostEqual(val2))) {
    return Error::handle(name(), L"read-big-bin", Error::TEST,
			 __FILE__, __LINE__);
  }
  val2.clear();
  
  // close and  delete the temporary files
  //
  text_file.close();
  bin_file.close();
  File::remove(tmp_filename0);
  File::remove(tmp_filename1);

  // test new and delete
  //
  VectorComplexLong* dyn_val0 = new VectorComplexLong(5);             
  dyn_val0->assign(L"1, 3, 5, 7, 9");
  
  VectorComplexLong* dyn_val1 = new VectorComplexLong(*dyn_val0);
  if (dyn_val0->ne(*dyn_val1)) {
    return Error::handle(name(), L"new", Error::TEST,
			 __FILE__, __LINE__);
  }
  
  delete dyn_val0;
  delete dyn_val1;
  
  // test large allocation construction and deletion
  //
  if (level_a == Integral::ALL) {
    
    int32 num_elem = 20;
    Console::put(L"testing large chunk memory allocation and deletion:\n");
    
    // set the memory to a strange block size so we can hopefully catch any
    // frame overrun errors
    //
    VectorComplexLong::setGrowSize(731);
    
    // loop for a large number of times creating and deleting a large number
    // of vectors at each loop
    //
    for (int32 j = 1; j <= 100; j++) {
      VectorComplexLong** vectors = new VectorComplexLong*[j * 100];
      
      // create the vectors
      //
      for (int32 i = 0; i < j * 100; i++) {
	vectors[i] = new VectorComplexLong(num_elem);
      }
      
      // delete vectors
      //
      for (int32 i = (j * 100) - 1; i >= 0; i--) {
	delete vectors[i];
      }
      
      delete [] vectors;
    }

    // perform the same test using the new[] and delete [] operators
    //
    for (int32 j = 1; j <= 100; j++) {
      
//       // allocate a large number of vectors
//       //
//       VectorComplexLong* vectors = new VectorComplexLong[j * 100](num_elem);
      
//       // clean up memory
//       //
//       delete [] vectors;

    }
  }
  
  // reset indentation
  //
  if (level_a > Integral::NONE) {
    Console::decreaseIndention();
  }
  
  //---------------------------------------------------------------------
  //
  // 3. class-specific public methods
  //     extensions to required methods
  //
  //---------------------------------------------------------------------

  // set indentation
  //
  if (level_a > Integral::NONE) {
    Console::put(L"testing class-specific public methods: extensions to required methods...\n");
    Console::increaseIndention(); 
  }
    
  // string constructor
  //
  val0 = (complexlong)5;
  String str(L"5, 5, 5, 5, 5");
  VectorComplexLong temp_vect_1(str);

  if (val0.ne(temp_vect_1)) {
    return Error::handle(name(), L"string constructor", Error::TEST,
			 __FILE__, __LINE__);
  }

  // unichar constructor
  //
  VectorComplexLong temp_vect_2(L"5, 5, 5, 5, 5");

  if (val0.ne(temp_vect_2)) {
    return Error::handle(name(), L"unichar constructor", Error::TEST,
			 __FILE__, __LINE__);
  }
  
  val0 = (complexlong)5;
  if (val0.ne((complexlong)5)) { 
    return Error::handle(name(), L"=", Error::TEST, __FILE__, __LINE__);
  }
  
  // reset indentation
  //
  if (level_a > Integral::NONE) {
    Console::decreaseIndention();
  }

  //---------------------------------------------------------------------
  //
  // 3. class-specific public methods
  //     complex functions
  //
  //---------------------------------------------------------------------

  // set indentation
  //
  if (level_a > Integral::NONE) {
    Console::put(L"testing class-specific public methods: complex functions...\n");
    Console::increaseIndention();
  }


  VectorLong a;
  VectorComplexLong b(L"4+3j, 2, 0 + 4j");

  VectorComplexLong c;
  c.conjugate(b);

  VectorComplexLong d(L"4 -3j, 2, 0 -4j");

  if (!c.almostEqual(d)) {
    return Error::handle(name(), L"conjugate", Error::TEST, __FILE__,
			 __LINE__);
  }

  VectorLong res;

  b.real(a);
  res.assign(L"4,2,0");
  if (!res.almostEqual(a)) {
    return Error::handle(name(), L"real", Error::TEST, __FILE__,
			 __LINE__);
  }

  b.imag(a);
  res.assign(L"3,0,4");
  if (!res.almostEqual(a)) {
    return Error::handle(name(), L"imag", Error::TEST, __FILE__,
			 __LINE__);
  }
  
  b.abs(a);
  res.assign(L"5,2,4");
  if (!res.almostEqual(a)) {
    return Error::handle(name(), L"abs", Error::TEST, __FILE__,
			 __LINE__);
  }

  b.mag(a);
  res.assign(L"5,2,4");
  if (!res.almostEqual(a)) {
    return Error::handle(name(), L"mag", Error::TEST, __FILE__,
			 __LINE__);
  }

  b.angle(a);
  res.assign(L"0.643501108,0,1.57079632");
  if (!res.almostEqual(a)) {
    a.debug(L"computed angle");
    return Error::handle(name(), L"angle", Error::TEST, __FILE__,
			 __LINE__);
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
    SysString output(L"diagnostics passed for class ");
    output.concat(name());
    output.concat(L"\n");
    Console::put(output);
  }

  // exit gracefully
  //
  return true;
}
