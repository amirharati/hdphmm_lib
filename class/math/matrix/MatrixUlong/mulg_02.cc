// file: $isip/class/math/matrix/MatrixUlong/mulg_02.cc
// version: $Id: mulg_02.cc 5831 2000-12-11 20:14:46Z duncan $
//

// isip include files
// 
#include "MatrixUlong.h"
#include <Console.h>
#include <String.h>

// method: diagnose
//
// arguments:
//  Integral::DEBUG level: (input) debug level for diagnostics
//
// return: a bool8 value indicating status
//
// this is the diagnostics method
//
bool8 MatrixUlong::diagnose(Integral::DEBUG level_a) {

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
  MMatrix<Ulong, uint32>::diagnose(level_a);

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
  
  // test the debug methods
  //
  MatrixUlong mat(4, 4, Integral::FULL);
  mat.setDebug(level_a);

  if (level_a > Integral::BRIEF) {
    mat.debug(L"debug");
  }

  // test destructor/constructor(s)
  //
  MatrixUlong mat0(4, 4, Integral::FULL);
  MatrixUlong mat1(4, 4, Integral::SYMMETRIC);
  MatrixUlong mat2(4, 4, Integral::LOWER_TRIANGULAR);
  MatrixUlong mat3(4, 4, Integral::DIAGONAL);

  MatrixUlong mat5(mat0);
  MatrixUlong mat6(mat1);
  MatrixUlong mat7(mat2);
  MatrixUlong mat8(mat3);

  // test io methods
  //
  MatrixUlong val0;
  MatrixUlong val1(3, 3, Integral::DIAGONAL);
  MatrixUlong val2;
  MatrixUlong val3;
  MatrixUlong val4;
  MatrixUlong val5;

  // declare the array of data
  //    
  uint32 data[9] = {
    1, 2, 3, 2, 4, 5, 3, 5, 6
  };

  // assign the array of data to matrices
  //    
  val0.assign(3, 3, data);
  val1.assign(9);
  val4.assign(3, 3, data);
  val4.changeType(Integral::SYMMETRIC);

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

  // write the values
  //
  val0.write(tmp_file0, (int32)0);
  val0.write(tmp_file1, (int32)0);
  
  val1.write(tmp_file0, (int32)1);
  val1.write(tmp_file1, (int32)1);

  val4.write(tmp_file0, (int32)2);
  val4.write(tmp_file1, (int32)2);
  
  // close the files
  //
  tmp_file0.close();
  tmp_file1.close();

  // open the files in read mode
  //
  tmp_file0.open(tmp_filename0);
  tmp_file1.open(tmp_filename1);

  // read the value back
  //
  if (!val2.read(tmp_file0, (int32)0) || (val2.ne(val0))) {
    return Error::handle(name(), L"diagnose", Error::TEST, __FILE__, __LINE__);
  }
  
  if (!val2.read(tmp_file1, (int32)0) || (val2.ne(val0))) {
    return Error::handle(name(), L"diagnose", Error::TEST, __FILE__, __LINE__);
  }

  val3.read(tmp_file0, (int32)1);
  if (!val3.read(tmp_file0, (int32)1) || (val3.ne(val1))) {
    return Error::handle(name(), L"diagnose", Error::TEST, __FILE__, __LINE__);
  }

  if (!val3.read(tmp_file1, (int32)1) || (val3.ne(val1))) {
    return Error::handle(name(), L"diagnose", Error::TEST, __FILE__, __LINE__);
  }

  val5.read(tmp_file0, (int32)2);
  if (!val5.read(tmp_file0, (int32)2) || (val5.ne(val4))) {
    return Error::handle(name(), L"diagnose", Error::TEST, __FILE__, __LINE__);
  }
  
  if (!val5.read(tmp_file1, (int32)2) || (val5.ne(val4))) {
    return Error::handle(name(), L"diagnose", Error::TEST, __FILE__, __LINE__);
  }

  // close and  delete the temporary files
  //
  tmp_file0.close();
  tmp_file1.close();

  File::remove(tmp_filename0);
  File::remove(tmp_filename1);
  
  // test new and delete
  //
  MatrixUlong* ptr;
  ptr = new MatrixUlong();
  int32 grow_size = 100;

  ptr->setGrowSize(grow_size);

  ptr->assign((uint32)4);
  delete ptr;

  ptr = new MatrixUlong[100];
  delete [] ptr;

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
  
  // test unichar* constructor
  //
  MatrixUlong temp_mat(2, 3, L"5, 5, 5, 5, 5, 5");
  
  if ((temp_mat.getNumRows() != 2) || (temp_mat.getNumColumns() != 3) ||
      (temp_mat.getType() != 0)) {
    return Error::handle(name(), L"constructor",
			 Error::TEST, __FILE__, __LINE__);
  }
  
  // test the operator= overload method
  //  
  mat0 = 5;
  mat1 = 5;
  mat2 = 5;
  mat3 = 5;

  mat0 = mat5;
  mat1 = mat6;
  mat2 = mat7;
  mat3 = mat8;
  
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
