// file: $isip/class/math/matrix/MatrixComplexFloat/mcflt_02.cc
// version: $Id
//

// isip include files
// 
#include "MatrixComplexFloat.h"
#include <Console.h>
#include <String.h>

// method: diagnose
//
// arguments:
//  Integral::DEBUG level: (input) debug level for diagnostics
//
// return: a bool8 value indicating status
//
bool8 MatrixComplexFloat::diagnose(Integral::DEBUG level_a) {

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
  MMatrix<ComplexFloat, complexfloat>::diagnose(level_a);

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
  MatrixComplexFloat mat(4, 4, Integral::FULL);
  mat.setDebug(level_a);

  if (level_a > Integral::BRIEF) {
    mat.debug(L"debug");
  }

  // test destructor/constructor(s)
  //
  MatrixComplexFloat mat0(4, 4, Integral::FULL);
  MatrixComplexFloat mat1(4, 4, Integral::SYMMETRIC);
  MatrixComplexFloat mat2(4, 4, Integral::LOWER_TRIANGULAR);
  MatrixComplexFloat mat3(4, 4, Integral::DIAGONAL);

  MatrixComplexFloat mat5(mat0);
  MatrixComplexFloat mat6(mat1);
  MatrixComplexFloat mat7(mat2);
  MatrixComplexFloat mat8(mat3);

  // test io methods
  //
  MatrixComplexFloat val0;
  MatrixComplexFloat val1(3, 3, Integral::DIAGONAL);
  MatrixComplexFloat val2(2, 2, Integral::SYMMETRIC);
  MatrixComplexFloat val3(3, 3, Integral::LOWER_TRIANGULAR);

  // check i/o for 0x0 matrix
  //
  MatrixComplexFloat val4(0, 0, L"");

  // check i/o for 1x1 matrix
  //
  MatrixComplexFloat val5(1, 1, L"1");

  // check i/o for 1x3 matrix
  //
  MatrixComplexFloat val6(1, 3, L"1, 2, 3");

  // check i/o for 3x1 matrix
  //
  MatrixComplexFloat val7(3, 1, L"1, 2, 3");

  // test i/o for sparse matrix
  //
  MatrixComplexFloat val8(3, 3, Integral::SPARSE);
  val8.setValue(1, 1, 1);
  val8.setValue(1, 2, 2);
  val8.setValue(2, 2, 3);
  
  MatrixComplexFloat test_val;

  // declare the array of data
  //  
  float32 data[9] = {
    1, 2, 3, 2, 4, 5, 3, 5, 6
  };

  // assign the array of data to matrices
  //  
  val0.assign(3, 3, data);
  val1.assign(9);
  val2.assign(3, 3, data);
  val3.assign(3, 3, data);

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

  val2.write(tmp_file0, (int32)2);
  val2.write(tmp_file1, (int32)2);

  val3.write(tmp_file0, (int32)3);
  val3.write(tmp_file1, (int32)3);

  val4.write(tmp_file0, (int32)4);
  val4.write(tmp_file1, (int32)4);

  val5.write(tmp_file0, (int32)5);
  val5.write(tmp_file1, (int32)5);

  val6.write(tmp_file0, (int32)6);
  val6.write(tmp_file1, (int32)6);

  val7.write(tmp_file0, (int32)7);
  val7.write(tmp_file1, (int32)7);

  val8.write(tmp_file0, (int32)8);
  val8.write(tmp_file1, (int32)8);

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
  if (!test_val.read(tmp_file0, (int32)0) || (test_val.ne(val0))) {
    return Error::handle(name(), L"diagnose", Error::TEST, __FILE__, __LINE__);
  }
  
  if (!test_val.read(tmp_file1, (int32)0) || (test_val.ne(val0))) {
    return Error::handle(name(), L"diagnose", Error::TEST, __FILE__, __LINE__);
  }

  test_val.read(tmp_file0, (int32)1);
  if (!test_val.read(tmp_file0, (int32)1) || (test_val.ne(val1))) {
    return Error::handle(name(), L"diagnose", Error::TEST, __FILE__, __LINE__);
  }
  
  if (!test_val.read(tmp_file1, (int32)1) || (test_val.ne(val1))) {
    return Error::handle(name(), L"diagnose", Error::TEST, __FILE__, __LINE__);
  }
  
  test_val.read(tmp_file0, (int32)2);
  if (!test_val.read(tmp_file0, (int32)2) || (test_val.ne(val2))) {
    return Error::handle(name(), L"diagnose", Error::TEST, __FILE__, __LINE__);
  }
  
  if (!test_val.read(tmp_file1, (int32)2) || (test_val.ne(val2))) {
    return Error::handle(name(), L"diagnose", Error::TEST, __FILE__, __LINE__);
  }

  test_val.read(tmp_file0, (int32)3);
  if (!test_val.read(tmp_file0, (int32)3) || (test_val.ne(val3))) {
    return Error::handle(name(), L"diagnose", Error::TEST, __FILE__, __LINE__);
  }
  
  if (!test_val.read(tmp_file1, (int32)3) || (test_val.ne(val3))) {
    return Error::handle(name(), L"diagnose", Error::TEST, __FILE__, __LINE__);
  }

  if (!test_val.read(tmp_file0, (int32)4) || (test_val.ne(val4))) {
    return Error::handle(name(), L"diagnose", Error::TEST, __FILE__, __LINE__);
  }

  if (!test_val.read(tmp_file1, (int32)4) || (test_val.ne(val4))) {
    return Error::handle(name(), L"diagnose", Error::TEST, __FILE__, __LINE__);
  }

  if (!test_val.read(tmp_file0, (int32)5) || (test_val.ne(val5))) {
    return Error::handle(name(), L"diagnose", Error::TEST, __FILE__, __LINE__);
  }

  if (!test_val.read(tmp_file1, (int32)5) || (test_val.ne(val5))) {
    return Error::handle(name(), L"diagnose", Error::TEST, __FILE__, __LINE__);
  }

  if (!test_val.read(tmp_file0, (int32)6) || (test_val.ne(val6))) {
    return Error::handle(name(), L"diagnose", Error::TEST, __FILE__, __LINE__);
  }

  if (!test_val.read(tmp_file1, (int32)6) || (test_val.ne(val6))) {
    return Error::handle(name(), L"diagnose", Error::TEST, __FILE__, __LINE__);
  }

  if (!test_val.read(tmp_file0, (int32)7) || (test_val.ne(val7))) {
    return Error::handle(name(), L"diagnose", Error::TEST, __FILE__, __LINE__);
  }

  if (!test_val.read(tmp_file1, (int32)7) || (test_val.ne(val7))) {
    return Error::handle(name(), L"diagnose", Error::TEST, __FILE__, __LINE__);
  }

  if (!test_val.read(tmp_file0, (int32)8) || (test_val.ne(val8))) {
    return Error::handle(name(), L"diagnose", Error::TEST, __FILE__, __LINE__);
  }

  if (!test_val.read(tmp_file1, (int32)8) || (test_val.ne(val8))) {
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
  MatrixComplexFloat* ptr;
  ptr = new MatrixComplexFloat(5);
  int32 grow_size = 100;

  ptr->setGrowSize(grow_size);
  ptr->assign((float)4);
  delete ptr;

  ptr = new MatrixComplexFloat[100];
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
  MatrixComplexFloat temp_mat(2, 3, L"5, 5, 5, 5, 5, 5");
  
  if ((temp_mat.getNumRows() != 2) || (temp_mat.getNumColumns() != 3) ||
      (temp_mat.getType() != 0)) {
    return Error::handle(name(), L"constructor",
			 Error::TEST, __FILE__, __LINE__);
  }
  
  // test the operator= overload method
  //
  ComplexFloat val(complexfloat(5.0, 0.0));

  mat0 = val;
  mat1 = val;
  mat2 = val;
  mat3 = val;

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
