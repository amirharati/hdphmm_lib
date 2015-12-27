// file: $isip/class/math/matrix/MMatrix/mmat_02.cc
// version: $Id: mmat_02.cc 10304 2005-12-14 06:25:15Z srinivas $
//

// system include files
//
#include <typeinfo>

// isip include files
// 
#include "MMatrix.h"
#include "MMatrixMethods.h"
#include "MMatrixDiagnose.h"
#include <SofParser.h>
#include <Console.h>

// method: diagnose
//
// arguments:
//  Integral::DEBUG level: (input) debug level for diagnostics
//
// return: a bool8 value indicating status
//
// this method tests the methods of the matrix class. the test vectors
// and matrices used in this code for testing purpose have been
// pre-defined in a separate file. this is done so that the diagnose
// code is simplified. the code is designed to test all the methods
// for all combinations of types.
//
template<class TMatrix, class TScalar, class TIntegral>
bool8 MMatrixMethods::diagnose(Integral::DEBUG level_a) {

  // define TVector
  //
  typedef MVector<TScalar, TIntegral> TVector;

  //----------------------------------------------------------------------
  //
  // 0. preliminaries
  //
  //----------------------------------------------------------------------
  
  // output the class name
  //
  if (level_a > Integral::NONE) {
    SysString output(L"diagnosing class ");
    output.concat(MMatrix<TScalar, TIntegral>::name());
    output.concat(L": ");
    Console::put(output);
    Console::increaseIndention();
  }
  
  //--------------------------------------------------------------------
  //
  // 1. required public methods
  //
  //--------------------------------------------------------------------
  
  diagnose0<TScalar, TIntegral>(level_a);

  //---------------------------------------------------------------------
  //
  // 2. single matrix --> scalar methods
  //
  //---------------------------------------------------------------------
  
  diagnose1<TScalar, TIntegral>(level_a);

  //---------------------------------------------------------------------
  //
  // 3. single matrix --> vector methods
  //
  //---------------------------------------------------------------------
  
  diagnose2<TScalar, TIntegral>(level_a);
  
  //---------------------------------------------------------------------
  //
  // 4. single matrix --> matrix methods
  //
  //---------------------------------------------------------------------

  diagnose3<TScalar, TIntegral>(level_a);
  
  //---------------------------------------------------------------------
  //
  // 5. matrix, matrix --> matrix methods
  //
  //---------------------------------------------------------------------

  diagnose4<TScalar, TIntegral>(level_a);

  //---------------------------------------------------------------------
  //
  // 6. matrix, matrix --> matrix methods (complex)
  // 
  //---------------------------------------------------------------------

#ifdef ISIP_TEMPLATE_complex
  diagnose5<TScalar, TIntegral>(level_a);
#endif

  //---------------------------------------------------------------------------
  //
  // 7. print completion message
  //
  //---------------------------------------------------------------------------

  // reset indentation
  //
  if (level_a > Integral::NONE) {
    Console::decreaseIndention();
  }
  
  if (level_a > Integral::NONE) {
    SysString output(L"diagnostics passed for class ");
    output.concat(MMatrix<TScalar, TIntegral>::name());
    output.concat(L"\n");
    Console::put(output);
  }

  // exit gracefully
  //
  return true;  
}

// method: diagnose0
//
// arguments:
//  Integral::DEBUG level: (input) debug level for diagnostics
//
// return: a bool8 value indicating status
//
// this method tests required public methods of matrix - the diagnose
// method is designed in such a way that it tests the methods for 8
// different matrices and for every possible type
//
template<class TScalar, class TIntegral>
bool8 MMatrixMethods::diagnose0(Integral::DEBUG level_a) {

  // define TVector
  //
  typedef MVector<TScalar, TIntegral> TVector;

  // set indentation
  //
  if (level_a > Integral::NONE) {
    Console::put(L"testing required matrix methods...\n");    
    Console::increaseIndention();
  }

  // set up the matrix data
  //
  MMatrix<TScalar, TIntegral> arg_mats[MMAT_NUM_MATS_TEST];
  MMatrix<TScalar, TIntegral> arg_mat2;
  
  // define binary and text sof files for i/o methods
  //
  String tmp_filename0;
  Integral::makeTemp(tmp_filename0);
  String tmp_filename1;
  Integral::makeTemp(tmp_filename1);
  
  // load up the argument matrices
  //
  for (int32 i = 0; i < MMAT_NUM_MATS_TEST; i++) {
    
    // assign the arguments
    //
#ifndef ISIP_TEMPLATE_complex
    arg_mats[i].assign((int32)MMAT_ARG_MATRICES[i][MMAT_NROW_LOC], 
                       (int32)MMAT_ARG_MATRICES[i][MMAT_NCOL_LOC], 
                       (float64*)&MMAT_ARG_MATRICES[i][MMAT_DATA_LOC]);
#else
    arg_mats[i].assignComplexDiagnose((int32)MMAT_ARG_MATRICES[i][MMAT_NROW_LOC], 
                       (int32)MMAT_ARG_MATRICES[i][MMAT_NCOL_LOC], 
                       (float64*)&MMAT_ARG_MATRICES[i][MMAT_DATA_LOC]);
#endif    
  }

  // test the setDebug method
  //
  arg_mat2.setDebug(level_a);

  // loop over the number of matrices
  //
  for (int32 mat1 = 0; mat1 < MMAT_NUM_MATS_TEST; mat1++) {

    // declare local variables
    //
    Char mat1c;
    mat1c.assign((byte8)((int)'A' + mat1));

    String out;
    out.concat(mat1c);
    
    // loop over 6 different types of the matrices
    //
    for (int32 type1 = Integral::FULL; type1 <= Integral::SPARSE; type1++) {

      // check if the type conversion is possible
      //
      if (arg_mats[mat1].isTypePossible((Integral::MTYPE)type1)) {
	
	// create a diagnostic string for each matrix and its type - if there
	// is a test error, this will be used to find that for which matrix and
	// which type, there is an error
	//
	String type1_str(MMatrix<TScalar, TIntegral>::TYPE_MAP(type1));
	String arg1_str(L"testing mat1: ");
	arg1_str.concat(mat1c);
	arg1_str.concat(L", ");
	arg1_str.concat(type1_str);
	
	// define temporary matrices to be used for testing
	//
	MMatrix<TScalar, TIntegral> res_mat;
	MMatrix<TScalar, TIntegral> tmp_mat;
	MMatrix<TScalar, TIntegral> arg_mat1;
	
	// assign input matrix to arg_mat1 and change the type - type is
	// changed here so that this particular matrix can be tested for
	// every type it can have
	//
	arg_mat1.assign(arg_mats[mat1]);
	arg_mat1.changeType((Integral::MTYPE)type1);
	
	// test copy constructor
	//
	MMatrix<TScalar, TIntegral> mat_cpy(arg_mat1); 
	
	// test debug methods
	//
	if (level_a > Integral::BRIEF) {
	  mat_cpy.debug(L"debug");
	}
	
	// test block assignment
	//
	TIntegral value = 5;

#ifdef ISIP_TEMPLATE_complex
	if (mat1 >= MMAT_NUM_MATS_REAL) {
	  value = TIntegral(5, 3);
	}
#endif	
	int32 start_row, num_rows, start_col, num_cols;

	// type: FULL, SPARSE
	//  [ 3 4 7 2 ]    [ 5 5 7 2 ]
	//  [ 3 5 6 1 ]    [ 5 5 6 1 ]    
	//  [ 8 4 1 3 ] -> [ 8 4 1 3 ]
	//  [ 4 5 7 2 ]    [ 4 5 7 2 ]    
	//
	if (MMAT_ARG_MAT_TYPES[mat1] == Integral::FULL) {
	  start_row = 0;
	  start_col = 0;
	  num_rows = 2;
	  num_cols = 2;
#ifndef ISIP_TEMPLATE_complex
	  res_mat.assign((int32)MMAT_BLOCKASSIGN_RES[mat1][MMAT_NROW_LOC], 
			 (int32)MMAT_BLOCKASSIGN_RES[mat1][MMAT_NCOL_LOC], 
			 (float64*)&MMAT_BLOCKASSIGN_RES[mat1][MMAT_DATA_LOC]);
#else
	  res_mat.assignComplexDiagnose((int32)MMAT_BLOCKASSIGN_RES[mat1][MMAT_NROW_LOC], 
			 (int32)MMAT_BLOCKASSIGN_RES[mat1][MMAT_NCOL_LOC], 
			 (float64*)&MMAT_BLOCKASSIGN_RES[mat1][MMAT_DATA_LOC]);
#endif	  
	  tmp_mat.assign(arg_mat1);
	  tmp_mat.setBlock(start_row, start_col, num_rows, num_cols, value);
	  
	  if (!res_mat.almostEqual(tmp_mat)) {
	    Console::put(arg1_str);
	    arg_mat1.debug(L"source matrix");
	    res_mat.debug(L"result matrix");
	    tmp_mat.debug(L"assigned matrix");
	    Error::handle(name(), L"block assign - full", Error::TEST, __FILE__, __LINE__);
	  }	
	}

	// type: DIAGONAL
	//  this can be done only when the element is assigned to the main
	//  diagonal of the matrix, else it will error
	//  [ 5 0 0 0 ]    [ 5 0 0 0 ]
	//  [ 0 2 0 0 ]    [ 0 2 0 0 ]
	//  [ 0 0 3 0 ] -> [ 0 0 5 0 ]
	//  [ 0 0 0 4 ]    [ 0 0 0 4 ]
	//
	if (type1 == Integral::DIAGONAL) {

	  start_row = 2;
	  start_col = 2;
	  num_rows = 1;
	  num_cols = 1;
#ifndef ISIP_TEMPLATE_complex
	  res_mat.assign((int32)MMAT_BLOCKASSIGN_RES[mat1][MMAT_NROW_LOC], 
			 (int32)MMAT_BLOCKASSIGN_RES[mat1][MMAT_NCOL_LOC], 
			 (float64*)&MMAT_BLOCKASSIGN_RES[mat1][MMAT_DATA_LOC]);
#else
	  res_mat.assignComplexDiagnose((int32)MMAT_BLOCKASSIGN_RES[mat1][MMAT_NROW_LOC], 
			 (int32)MMAT_BLOCKASSIGN_RES[mat1][MMAT_NCOL_LOC], 
			 (float64*)&MMAT_BLOCKASSIGN_RES[mat1][MMAT_DATA_LOC]);
#endif	  
	  
	  tmp_mat.assign(arg_mat1);
	  tmp_mat.setBlock(start_row, start_col, num_rows, num_cols, value);
	  if (!res_mat.almostEqual(tmp_mat)) {
	    Console::put(arg1_str);
	    arg_mat1.debug(L"source matrix");
	    res_mat.debug(L"result matrix");
	    tmp_mat.debug(L"assigned matrix");
	    Error::handle(name(), L"assign", Error::TEST, __FILE__, __LINE__);
	  }	
	}
	
	// type: LOWER_TRIANGULAR
	//  this can be done only when the block falls in the lower triangular
	//  part of the matrix
	//  [ 5 0 0 0 ]    [ 5 0 0 0 ]
	//  [ 3 2 0 0 ]    [ 3 2 0 0 ]
	//  [ 2 4 3 0 ] -> [ 5 5 5 0 ]
	//  [ 1 7 5 4 ]    [ 5 5 5 4 ]
	//	
	if ((type1 == Integral::LOWER_TRIANGULAR)
	    && (mat1 != 1) && (mat1 != 9)) {

	  start_row = 2;
	  start_col = 0;
	  num_rows = 2;
	  num_cols = 3;
#ifndef ISIP_TEMPLATE_complex
	  res_mat.assign((int32)MMAT_BLOCKASSIGN_RES[mat1][MMAT_NROW_LOC], 
			 (int32)MMAT_BLOCKASSIGN_RES[mat1][MMAT_NCOL_LOC], 
			 (float64*)&MMAT_BLOCKASSIGN_RES[mat1][MMAT_DATA_LOC]);
#else
	  res_mat.assignComplexDiagnose((int32)MMAT_BLOCKASSIGN_RES[mat1][MMAT_NROW_LOC], 
			 (int32)MMAT_BLOCKASSIGN_RES[mat1][MMAT_NCOL_LOC], 
			 (float64*)&MMAT_BLOCKASSIGN_RES[mat1][MMAT_DATA_LOC]);
#endif	  
	  tmp_mat.assign(arg_mat1);
	  tmp_mat.setBlock(start_row, start_col, num_rows, num_cols, value);
	  
	  if (!res_mat.almostEqual(tmp_mat)) {
	    Console::put(arg1_str);
	    arg_mat1.debug(L"source matrix");
	    res_mat.debug(L"result matrix");
	    tmp_mat.debug(L"assigned matrix");
	    Error::handle(name(), L"assign", Error::TEST, __FILE__, __LINE__);
	  }	
	}      
	
	// type: UPPER_TRIANGULAR
	//  this can be done only when the block falls in the upper triangular
	//  part of the matrix
	//  [ 5 2 3 4 ]    [ 5 2 5 5 ]
	//  [ 0 2 2 7 ]    [ 0 2 5 5 ]
	//  [ 0 0 3 1 ] -> [ 0 0 5 5 ]
	//  [ 0 0 0 4 ]    [ 0 0 0 4 ]
	//
	if ((type1 == Integral::UPPER_TRIANGULAR)
	    && (mat1 != 1) && (mat1 != 9)) {

	  start_row = 0;
	  start_col = 2;
	  num_rows = 3;
	  num_cols = 2;
#ifndef ISIP_TEMPLATE_complex
	  res_mat.assign((int32)MMAT_BLOCKASSIGN_RES[mat1][MMAT_NROW_LOC], 
			 (int32)MMAT_BLOCKASSIGN_RES[mat1][MMAT_NCOL_LOC], 
			 (float64*)&MMAT_BLOCKASSIGN_RES[mat1][MMAT_DATA_LOC]);
#else
	  res_mat.assignComplexDiagnose((int32)MMAT_BLOCKASSIGN_RES[mat1][MMAT_NROW_LOC], 
			 (int32)MMAT_BLOCKASSIGN_RES[mat1][MMAT_NCOL_LOC], 
			 (float64*)&MMAT_BLOCKASSIGN_RES[mat1][MMAT_DATA_LOC]);
#endif	  
	  
	  tmp_mat.assign(arg_mat1);
	  tmp_mat.setBlock(start_row, start_col, num_rows, num_cols, value);
	  
	  if (!res_mat.almostEqual(tmp_mat)) {
	    Console::put(arg1_str);
	    arg_mat1.debug(L"source matrix");
	    res_mat.debug(L"result matrix");
	    tmp_mat.debug(L"assigned matrix");
	    Error::handle(name(), L"block assign - upper triangular", Error::TEST, __FILE__, __LINE__);
	  }	
	}
	
	// type: SYMMETRIC
	//  this can be done if the block is either in lower triangle or
	//  in upper triangle or is symmetric across main diagonal
	//  [ 5 2 3 4 ]    [ 5 2 3 4 ]
	//  [ 2 2 2 7 ]    [ 2 2 2 7 ]
	//  [ 3 2 3 1 ] -> [ 5 5 3 1 ]
	//  [ 4 7 1 4 ]    [ 5 5 1 4 ]
	//
	if ((type1 == Integral::SYMMETRIC) && (mat1 != 1) && (mat1 != 9)) {

	  start_row = 2;
	  start_col = 0;
	  num_rows = 2;
	  num_cols = 2;
#ifndef ISIP_TEMPLATE_complex	  
	  res_mat.assign((int32)MMAT_BLOCKASSIGN_RES[mat1][MMAT_NROW_LOC], 
			 (int32)MMAT_BLOCKASSIGN_RES[mat1][MMAT_NCOL_LOC], 
			 (float64*)&MMAT_BLOCKASSIGN_RES[mat1][MMAT_DATA_LOC]);
#else
	  res_mat.assignComplexDiagnose((int32)MMAT_BLOCKASSIGN_RES[mat1][MMAT_NROW_LOC], 
			 (int32)MMAT_BLOCKASSIGN_RES[mat1][MMAT_NCOL_LOC], 
			 (float64*)&MMAT_BLOCKASSIGN_RES[mat1][MMAT_DATA_LOC]);
#endif	  
	  tmp_mat.assign(arg_mat1);
	  tmp_mat.setBlock(start_row, start_col, num_rows, num_cols, value);
	  
	  if (!res_mat.almostEqual(tmp_mat)) {
	    Console::put(arg1_str);
	    arg_mat1.debug(L"source matrix");
	    res_mat.debug(L"result matrix");
	    tmp_mat.debug(L"assigned matrix");
	    Error::handle(name(), L"block assign - symmetric", Error::TEST, __FILE__, __LINE__);
	  }	
	}

	// test assignment of a matrix from a TAIntegral array
	//
#ifndef ISIP_TEMPLATE_complex
	tmp_mat.assign((int32)MMAT_ASSIGN_ARG[mat1][MMAT_NROW_LOC], 
		       (int32)MMAT_ASSIGN_ARG[mat1][MMAT_NCOL_LOC], 
		       (float64*)&MMAT_ASSIGN_ARG[mat1][MMAT_DATA_LOC],
		       MMAT_ARG_MAT_TYPES[mat1]);
#else
	tmp_mat.assignComplexDiagnose((int32)MMAT_ASSIGN_ARG[mat1][MMAT_NROW_LOC], 
		       (int32)MMAT_ASSIGN_ARG[mat1][MMAT_NCOL_LOC], 
		       (float64*)&MMAT_ASSIGN_ARG[mat1][MMAT_DATA_LOC],
		       MMAT_ARG_MAT_TYPES[mat1]);
#endif    
	res_mat.assign(arg_mat1);
      
	if (!res_mat.almostEqual(tmp_mat)) {
	  Console::put(arg1_str);	    
	  res_mat.debug(L"result matrix");
	  tmp_mat.debug(L"assigned matrix");
	  Error::handle(name(), L"assign from tintegral", Error::TEST, __FILE__, __LINE__);
	}

	// test assignment of a matrix from a string
	//
	if (!tmp_mat.assign((int32)MMAT_ARG_MATRICES[mat1][MMAT_NROW_LOC], 
			    (int32)MMAT_ARG_MATRICES[mat1][MMAT_NCOL_LOC],
			    MMAT_ASSIGN1_ARG[mat1],
			    MMAT_ARG_MAT_TYPES[mat1])) {
	  Console::put(MMAT_ASSIGN1_ARG[mat1]);
	  Console::put(arg1_str);
	  return Error::handle(name(), L"assignment from string", Error::ARG,
			       __FILE__, __LINE__);
	};
	res_mat.assign(arg_mat1);
      
	if (!res_mat.almostEqual(tmp_mat)) {
	  Console::put(arg1_str);	    
	  res_mat.debug(L"result matrix");
	  tmp_mat.debug(L"assigned matrix");
	  Error::handle(name(), L"assign from string", Error::TEST, __FILE__, __LINE__);
	}
	
	// test i/o method:
	//  create a unique tag by composing the mat1 and type1
	//
	int32 tag = mat1 * 100 + (int32)type1;
	
	// open files in write plus mode so that we can read as soon
	// as we write
	//
	Sof sof_text;
	Sof sof_bin;

	// try to preserve the same file throughout
	//
	if (File::exists(tmp_filename0) && File::exists(tmp_filename1)) {
	  sof_text.open(tmp_filename0, File::READ_PLUS, File::TEXT);
	  sof_bin.open(tmp_filename1, File::READ_PLUS, File::BINARY);
	}
	else {
	  sof_text.open(tmp_filename0, File::WRITE_ONLY, File::TEXT);
	  sof_bin.open(tmp_filename1, File::WRITE_ONLY, File::BINARY);
	}
	
	// write the objects in text as well as binary mode
	//
	arg_mat1.write(sof_text, tag, name());
	arg_mat1.write(sof_bin, tag, name());
	
	// close and reopen the files in read mode
	//
	sof_text.close();
	sof_bin.close();
	sof_text.open(tmp_filename0, File::READ_ONLY, File::TEXT);
	sof_bin.open(tmp_filename1, File::READ_ONLY, File::BINARY);
	
	// clear the matrix
	//
	tmp_mat.clear(Integral::RETAIN);

	// read the text file
	//
	if ((!tmp_mat.read(sof_text, tag, name())) ||
	    (!tmp_mat.almostEqual(arg_mat1))) {
	  Console::put(arg1_str);
	  return Error::handle(name(), L"read", Error::ARG,
			       __FILE__, __LINE__);
	}

	// clear the matrix
	//
	tmp_mat.clear(Integral::RETAIN);
	
	// read the binary file
	//
	if ((!tmp_mat.read(sof_bin, tag, name())) ||
	    (!tmp_mat.almostEqual(arg_mat1))) {
	  Console::put(arg1_str);	    
	  Error::handle(name(), L"read", Error::TEST, __FILE__, __LINE__);
	}

	// close the temporary Sof files
	//
	sof_text.close();
	sof_bin.close();
	
	// delete the temporary Sof files
	//      
	File::remove(tmp_filename0);
	File::remove(tmp_filename1);
	
	// test clear
	//
	res_mat.assign(arg_mat1.getNumRows(), 
		       arg_mat1.getNumColumns(), 
		       (float64*)&MMAT_CLEAR_RES[MMAT_DATA_LOC]);
	tmp_mat.assign(arg_mat1);
	
	if (tmp_mat.almostEqual(res_mat)) {
	  Console::put(arg1_str);
	  Error::handle(name(), L"assign", Error::TEST, __FILE__, __LINE__);
	}

	// test when mode is RETAIN
	//
	tmp_mat.clear(Integral::RETAIN);
	
	if (!tmp_mat.almostEqual(res_mat)) {
	  Console::put(arg1_str);
	  Error::handle(name(), L"clear", Error::TEST, __FILE__, __LINE__);
	}

	// test when mode is RESET
	//
	tmp_mat.clear(Integral::RESET);
	
	if ((tmp_mat.getNumRows() != 0) || (tmp_mat.getNumColumns() != 0)) {
	  Console::put(arg1_str);
	  tmp_mat.debug(L"output");
	  res_mat.debug(L"expected");
	  Error::handle(name(), L"clear", Error::TEST, __FILE__, __LINE__);
	}

      	// test when mode is RELEASE
	//
	tmp_mat.assign(arg_mat1);
	tmp_mat.clear(Integral::RELEASE);
	
	if ((tmp_mat.getNumRows() != 0) || (tmp_mat.getNumColumns() != 0) ||
	    (tmp_mat.m_d.length() != 0) ||
	    (tmp_mat.m_d.getCapacity() != 0)) {
	  tmp_mat.m_d.debug(L"m_d");
	
	  Console::put(arg1_str);
	  tmp_mat.debug(L"output");
	  Error::handle(name(), L"clear", Error::TEST, __FILE__, __LINE__);
	}

	// test when mode is FREE
	//
	tmp_mat.assign(arg_mat1);
	tmp_mat.clear(Integral::FREE);
	
	if ((tmp_mat.getNumRows() != 0) || (tmp_mat.getNumColumns() != 0) ||
	    (tmp_mat.m_d.length() != 0) ||
	    (tmp_mat.m_d.getCapacity() != 0)) {
	  
	  Console::put(arg1_str);
	  tmp_mat.debug(L"output");
	  Error::handle(name(), L"clear", Error::TEST, __FILE__, __LINE__);
	}
      }
    }
  }
  
  // reset indentation
  //
  if (level_a > Integral::NONE) {
    Console::decreaseIndention();
  }
  
  // exit gracefully
  //
  return true;
}

// method: diagnose1
//
// arguments:
//  Integral::DEBUG level: (input) debug level for diagnostics
//
// return: a bool8 value indicating status
//
// this method tests single matrix to scalar methods for matrix - the
// diagnose method is designed in such a way that it tests the methods
// for 8 different matrices and for every possible type
//
template<class TScalar, class TIntegral>
bool8 MMatrixMethods::diagnose1(Integral::DEBUG level_a) {
  
  // define TVector
  //
  typedef MVector<TScalar, TIntegral> TVector;
  
  // set indentation
  //
  if (level_a > Integral::NONE) {
    Console::put(L"testing class-specific public methods: single matrix --> scalar...\n");
    Console::increaseIndention();
  }
  
  // declare an array of matrix to hold all the 8 matrices used for testing
  //
  MMatrix<TScalar, TIntegral> arg_mats[MMAT_NUM_MATS_TEST];
  
  // load up the argument matrices
  //
  for (int32 i = 0; i < MMAT_NUM_MATS_TEST; i++) {
    
    // assign the arguments
    //
#ifndef ISIP_TEMPLATE_complex
    arg_mats[i].assign((int32)MMAT_ARG_MATRICES[i][MMAT_NROW_LOC], 
                       (int32)MMAT_ARG_MATRICES[i][MMAT_NCOL_LOC], 
                       (float64*)&MMAT_ARG_MATRICES[i][MMAT_DATA_LOC]);
#else
    arg_mats[i].assignComplexDiagnose((int32)MMAT_ARG_MATRICES[i][MMAT_NROW_LOC], 
                       (int32)MMAT_ARG_MATRICES[i][MMAT_NCOL_LOC], 
                       (float64*)&MMAT_ARG_MATRICES[i][MMAT_DATA_LOC]);
#endif    
  }

  // define matrices to be used in the method
  //
  MMatrix<TScalar, TIntegral> res_mat;
  MMatrix<TScalar, TIntegral> tmp_mat;
  MMatrix<TScalar, TIntegral> arg_mat1;
  
  // loop through the different matrices
  //
  for (int32 mat1 = 0; mat1 < MMAT_NUM_MATS_TEST; mat1++) {  
    
    //  create a diagnostic string 
    // to indicate the matrix and its type
    //
    String arg1_str(L"testing matrix ");
    Char mat1c;
    mat1c.assign((byte8)((int)'A' + mat1));
    arg1_str.concat(mat1c);
    
    if (level_a > Integral::BRIEF) {
      Console::put(arg1_str);
      arg_mats[mat1].debug(arg1_str);
      Console::increaseIndention();
    }
  
    // loop through different types of matrices
    //
    for (int32 type1 = Integral::FULL; type1 <= Integral::SPARSE; type1++) {
      
      // check if the type conversion is possible
      //
      if (arg_mats[mat1].isTypePossible((Integral::MTYPE)type1)) {
	
	String type1_str(MMatrix<TScalar, TIntegral>::TYPE_MAP(type1));
	arg1_str.concat(L" -> ");
	arg1_str.concat(type1_str);
	
	if (level_a > Integral::BRIEF) {
	  String out(L"converting to ");
	  out.concat(type1_str);
	  Console::put(out);
	}
       
	// assign the input matrix and change the type - type is
	// changed here so that this particular matrix can be tested for
	// every type it can have
	//
	arg_mat1.assign(arg_mats[mat1]);
	if (arg_mat1.changeType((Integral::MTYPE)type1) !=
	    MMAT_CHANGE_TYPE_RES[mat1][type1]) {
	  Console::put(arg1_str);
	  Error::handle(name(), L"changeType", Error::TEST, 
			__FILE__, __LINE__);
	}
	
	// test isTypePossible
	//
	if (arg_mats[mat1].isTypePossible((Integral::MTYPE)type1)
	    != MMAT_IS_TYPE_POSSIBLE_RES[mat1][type1]) {
	  Console::put(arg1_str);
	  Error::handle(name(), L"isTypePossible", Error::TEST, 
			__FILE__, __LINE__);
	}
	
	// test isDiagonal
	//
	if (arg_mats[mat1].isDiagonal() != MMAT_IS_DIAGONAL_RES[mat1]) {
	  Console::put(arg1_str);	  
	  Error::handle(name(), L"isDiagonal", Error::TEST, 
			__FILE__, __LINE__);
	}
	
	// test isSymmetric
	//
	if (arg_mats[mat1].isSymmetric() != MMAT_IS_SYMMETRIC_RES[mat1]) {
	  Console::put(arg1_str);	  
	  Error::handle(name(), L"isSymmetric", Error::TEST, 
			__FILE__, __LINE__);
	}
	
	// test isLowerTriangle
	//
	if (arg_mats[mat1].isLowerTriangular() !=
	    MMAT_IS_LOWERTRIANGULAR_RES[mat1]) {
	  Console::put(arg1_str);	  
	  Error::handle(name(), L"isLowerTriangle", Error::TEST, 
			__FILE__, __LINE__);
	}
	
	// test isUpperTriangle
	//
	if (arg_mats[mat1].isUpperTriangular() != 
	    MMAT_IS_UPPERTRIANGULAR_RES[mat1]) {
	  Console::put(arg1_str);	  	  
	  Error::handle(name(), L"isUpperTriangle", Error::TEST, 
			__FILE__, __LINE__);
	}
	
	// test isIdentity - note that we are not testing this method
	// for input matrix as the input matrices are not identity
	// matrices, as a solution we construct a temporary identity
	// matrix for test. we also change the type of the identity
	// matrix so that the method can be tested for all possible types.
	//
	res_mat.changeType(Integral::FULL);
	res_mat.assign(arg_mats[mat1].getNumRows(), 
		       arg_mats[mat1].getNumColumns(),
		       (float64*)&MMAT_IDENTITY_MATRICES[MMAT_DATA_LOC]);

	if (res_mat.isTypePossible((Integral::MTYPE)type1)) {	
	  res_mat.changeType((Integral::MTYPE)type1);
	}

	if (res_mat.isSquare()) {
	  if (!res_mat.isIdentity()) {
	    Console::put(arg1_str);
	    Error::handle(name(), L"isIdentity", Error::TEST, 
			  __FILE__, __LINE__);
	  }
	}
	
	// test isOrthogonal
	//
	res_mat.changeType(Integral::FULL);
	res_mat.assign(arg_mats[mat1].getNumRows(), 
		       arg_mats[mat1].getNumColumns(), 
		       (float64*)&MMAT_ORTHOGONAL_MATRICES [MMAT_DATA_LOC]);
	
	if (res_mat.isTypePossible((Integral::MTYPE)type1)) {		  
	  res_mat.changeType((Integral::MTYPE)type1);
	}

	if ((typeid(float64) == typeid(TIntegral)) ||
	    (typeid(float32) == typeid(TIntegral))) {	
	  if (res_mat.isSquare()) {
	    if (!res_mat.isOrthogonal()) {
	      MMatrix<TScalar, TIntegral> my_mat;
	      my_mat.inverse(res_mat);
	      Console::put(arg1_str);
	      my_mat.debug(L"inv");
	      my_mat.transpose(res_mat);
	      my_mat.debug(L"trans");	    
	      Error::handle(name(), L"isOrthogonal", Error::TEST, 
			    __FILE__, __LINE__);
	    }
	  }
	}
	
	// test getNumRows and getNumColumns
	//
	if (arg_mat1.getNumRows()
	    != (int32)MMAT_ARG_MATRICES[mat1][MMAT_NROW_LOC]) {
	  Console::put(arg1_str);
	  Error::handle(name(), L"getNumRows", Error::TEST, 
			__FILE__, __LINE__);
	}
	if (arg_mat1.getNumColumns()
	    != (int32)MMAT_ARG_MATRICES[mat1][MMAT_NCOL_LOC]) {
	  Console::put(arg1_str);
	  Error::handle(name(), L"getNumColumns", Error::TEST, 
			__FILE__, __LINE__);
	}
	
	// test isSquare
	//
	if (arg_mat1.isSquare(arg_mat1) != MMAT_IS_SQUARE_RES[mat1]) {
	  Console::put(arg1_str);
	  Error::handle(name(), L"isSquare", Error::TEST,
			__FILE__, __LINE__);
	}

	// test isSingular for all but unsigned datatypes
	//
	if (typeid(TIntegral) == typeid(float32) ||
	    typeid(TIntegral) == typeid(float64) ||
	    typeid(TIntegral) == typeid(Long) ||
	    typeid(TIntegral) == typeid(int32) ||
	    typeid(TIntegral) == typeid(int16)) {
	  
	  if (arg_mat1.isSquare()) {

	    if (arg_mat1.isSingular(arg_mat1,
				    MMatrix<TScalar, TIntegral>::
				    THRESH_SINGULAR) !=
		MMAT_IS_SINGULAR_RES[mat1]) {
	      Console::put(arg1_str);
	      Error::handle(name(), L"isSingular", Error::TEST,
			    __FILE__, __LINE__);
	    }
	  }
	}

	// test matrix assign from a string
	//
	tmp_mat.assign(4, 4, MMAT_ASSIGN_STRING_INPUT[type1],
		       (Integral::MTYPE)type1);
	res_mat.assign(arg_mat1);
	
	if (((mat1 == 1) && (!tmp_mat.almostEqual(res_mat)))
	    || ((mat1 != 1) && (tmp_mat.almostEqual(res_mat)))) {
	  Console::put(arg1_str);
	  Error::handle(name(), L"assign", Error::TEST, __FILE__, __LINE__);
	}
	
	// test swap
	//
	tmp_mat.assign(arg_mat1);
	tmp_mat.swap(res_mat);
	
	if (!res_mat.almostEqual(arg_mat1)) {
	  Console::put(arg1_str);
	  Error::handle(name(), L"swap", Error::TEST, __FILE__, __LINE__);
	}
	
	// test getType
	//
	if (arg_mat1.getType() != (Integral::MTYPE)type1) {
	  Console::put(arg1_str);
	  Error::handle(name(), L"getType", Error::TEST, __FILE__, __LINE__);
	}
	
	// test nextZero - note that calling this method for negative one
	// row and column indices returns the positions of first zero
	// elements of the matrix
	//
	tmp_mat.assign(arg_mat1);
	int32 row_index = -1;
	int32 col_index = -1;
	
	tmp_mat.nextZero(row_index, col_index,
			 (int32)MMAT_NEXT_ZERO_ARG[0],
			 (int32)MMAT_NEXT_ZERO_ARG[1]);
	if ((row_index != (int32)MMAT_NEXT_ZERO_RES[mat1 * 2]) ||
	    (col_index != (int32)MMAT_NEXT_ZERO_RES[mat1 * 2 + 1])) {
	  Console::put(arg1_str);
	  Error::handle(name(), L"nextZero", Error::TEST, __FILE__, __LINE__);
	}
	
	// test nextNonZero - note that calling this method for negative one
	// row and column indices returns the positions of first non-zero
	// elements of the matrix
	//      
	TIntegral tmp_val;
	tmp_mat.nextNonZero(tmp_val, row_index, col_index,
			    (int32)MMAT_NEXT_NONZERO_ARG[0],
			    (int32)MMAT_NEXT_NONZERO_ARG[1]);
#ifdef ISIP_TEMPLATE_complex	
	complexdouble tmp_complex6(MMAT_NEXT_NONZERO_RES[mat1 * 4],
				  MMAT_NEXT_NONZERO_RES[mat1 * 4 + 3]);
#endif	
	if ((row_index != (int32)MMAT_NEXT_NONZERO_RES[mat1 * 4 + 1]) ||
	    (col_index != (int32)MMAT_NEXT_NONZERO_RES[mat1 * 4 + 2]) ||
#ifndef ISIP_TEMPLATE_complex
	    (!(TScalar(tmp_val)).almostEqual(
			   (TIntegral)MMAT_NEXT_NONZERO_RES[mat1 * 4]))) {
#else
	  (!(TScalar(tmp_val)).almostEqual((TIntegral)tmp_complex6))) {
#endif
	  Console::put(arg1_str);
	  Error::handle(name(), L"nextNonZero", Error::TEST, __FILE__, __LINE__);
	}

	// test dimensions and capacity:
	//
	res_mat.setDimensions(0, 0, false, Integral::FULL);
	tmp_mat.assign(arg_mat1);
	
	// set the dimension to zero
	//
	tmp_mat.setDimensions(0, 0, false);
	
	if (((int32)(tmp_mat.m_d.length()) != 0) ||
	    ((int32)(tmp_mat.row_index_d.length()) != 0) ||
	    ((int32)(tmp_mat.col_index_d.length()) != 0) ||
	    ((int32)(tmp_mat.nrows_d) != 0) ||
	    ((int32)tmp_mat.ncols_d != 0)) {
	  Console::put(arg1_str);	
	  Error::handle(name(), L"setCapacity", Error::TEST, 
			       __FILE__, __LINE__);
	}
	
	// set the dimensions
	//
	tmp_mat.assign(arg_mat1);
	tmp_mat.setDimensions(3, 3);
	
#ifndef ISIP_TEMPLATE_complex
	res_mat.assign((int32)MMAT_SET_DIM_RES[mat1][MMAT_NROW_LOC], 
		       (int32)MMAT_SET_DIM_RES[mat1][MMAT_NCOL_LOC], 
		       (float64*)&MMAT_SET_DIM_RES[mat1][MMAT_DATA_LOC]);
#else
	res_mat.assignComplexDiagnose((int32)MMAT_SET_DIM_RES[mat1][MMAT_NROW_LOC], 
		       (int32)MMAT_SET_DIM_RES[mat1][MMAT_NCOL_LOC], 
		       (float64*)&MMAT_SET_DIM_RES[mat1][MMAT_DATA_LOC]);
#endif	
	
	if (!res_mat.eq(tmp_mat)) {
	  Console::put(arg1_str);
	  tmp_mat.debug(L"SET_DIM_RES");
	  res_mat.debug(L"res_mat");
	  Error::handle(name(), L"setDimensions", Error::TEST, __FILE__, 
			__LINE__);
	}

	// set the capacity
	//
	tmp_mat.assign(arg_mat1);
	tmp_mat.setCapacity(5, 5);
	if (!tmp_mat.eq(arg_mat1)) {
	  tmp_mat.debug(L"tmp_mat");
	  arg_mat1.debug(L"arg_mat");
	  Console::put(arg1_str);
	  Error::handle(name(), L"setCapacity", Error::TEST, __FILE__, 
			__LINE__);
	}
	
	// test special case of eq:
	//  make sure the zero elements are tested for equality.
	//
	tmp_mat.makeDiagonal((TIntegral)MMAT_MAKEDIAG_SCAL, 4,
			     (Integral::MTYPE)type1);
	
	if (tmp_mat.eq((TIntegral)MMAT_MAKEDIAG_SCAL)) {
	  return Error::handle(name(), L"eq", Error::TEST, __FILE__, __LINE__);
	}

	// test special case of lt:
	//  should return false for triangular matrices when all the
	//  elements in lower or upper triangular part of the matrix are
	//  negative
	//
	tmp_mat.clear(Integral::RETAIN);
	
	// create lower triangular matrix for test
	//
	if (arg_mat1.isSquare()) {
	  if ((type1 != Integral::UPPER_TRIANGULAR) &&
	      ((mat1 % MMAT_NUM_MATS_REAL) != 4)) {  
	    tmp_mat.setDimensions(4, 4, false,
				  Integral::LOWER_TRIANGULAR);
	    tmp_mat.setLower(arg_mat1);
	    tmp_mat.m_d.abs();
	    tmp_mat.neg();
	    
	    if (tmp_mat.isTypePossible((Integral::MTYPE)type1)) {
	      tmp_mat.changeType((Integral::MTYPE)type1);
	      
	      if (tmp_mat.lt(0)) {
		Console::put(arg1_str);
		return Error::handle(name(), L"lt", Error::TEST,
				     __FILE__, __LINE__);
	      }
	    }
	  }
	  
	  // create an upper triangular matrix for test
	  //
	  if ((type1 != Integral::LOWER_TRIANGULAR) &&
	      ((mat1 % MMAT_NUM_MATS_REAL) != 3)) {
	    tmp_mat.clear(Integral::RETAIN);
	    tmp_mat.setDimensions(4, 4, false,
				  Integral::UPPER_TRIANGULAR);
	    tmp_mat.setUpper(arg_mat1);
	    tmp_mat.m_d.abs();      
	    tmp_mat.neg();
	    
	    if (tmp_mat.isTypePossible((Integral::MTYPE)type1)) {
	      tmp_mat.changeType((Integral::MTYPE)type1);
	      
	      if (tmp_mat.lt(0)) {
		Console::put(arg1_str);
		return Error::handle(name(), L"lt", Error::TEST,
				     __FILE__, __LINE__);
	      }
	    }
	  }
  
	  // test special case of gt:
	  //  should return false for triangular matrices when all the
	  //  elements in lower or upper triangular part of the matrix are
	  //  positive
	  //
	  if ((type1 != Integral::UPPER_TRIANGULAR) &&
	      ((mat1 % MMAT_NUM_MATS_REAL) != 4)) {
	    tmp_mat.clear(Integral::RETAIN);
	    tmp_mat.setDimensions(4, 4, false,
				  Integral::LOWER_TRIANGULAR);
	    tmp_mat.setLower(arg_mat1);
	    tmp_mat.m_d.abs();
	    
	    if (tmp_mat.isTypePossible((Integral::MTYPE)type1)) {
	      tmp_mat.changeType((Integral::MTYPE)type1);
	      if (tmp_mat.gt(0)) {
		Console::put(arg1_str);
		return Error::handle(name(), L"gt", Error::TEST,
				     __FILE__, __LINE__);
	      }
	    }
	  }

	  // create an upper triangular for test
	  //
	  if ((type1 != Integral::LOWER_TRIANGULAR) &&
	      ((mat1 % MMAT_NUM_MATS_REAL) != 3)) {      
	    tmp_mat.clear(Integral::RETAIN);
	    tmp_mat.setDimensions(4, 4, false,
				  Integral::UPPER_TRIANGULAR);
	    tmp_mat.setUpper(arg_mat1);
	    tmp_mat.m_d.abs();      
	    
	    if (tmp_mat.isTypePossible((Integral::MTYPE)type1)) {
	      tmp_mat.changeType((Integral::MTYPE)type1);
	      if (tmp_mat.gt(0)) {
		Console::put(arg1_str);
		return Error::handle(name(), L"gt", Error::TEST,
				     __FILE__, __LINE__);
	      }
	    }
	  }
	}

	// test relational operators:
	//  test numEqual with two keys
	//
	if (arg_mat1.numEqual((int32)MMAT_NUM_EQUAL_VAL0)
	    != MMAT_NUM_EQUAL_RES0[mat1]) {
	  Console::put(arg1_str);
	  Error::handle(name(), L"numEqual", Error::TEST,
			__FILE__, __LINE__);
	}
	if (arg_mat1.numEqual((int32)MMAT_NUM_EQUAL_VAL1)
	    != MMAT_NUM_EQUAL_RES1[mat1]) {
	  Console::put(arg1_str);
	  Error::handle(name(), L"numEqual", Error::TEST,
			__FILE__, __LINE__);
	}
#ifdef ISIP_TEMPLATE_complex
	if (arg_mat1.numEqual((complexlong)MMAT_NUM_EQUAL_VAL2)
	    != MMAT_NUM_EQUAL_RES2[mat1]) {
	  Console::put(arg1_str);
	  Error::handle(name(), L"numEqual", Error::TEST,
			__FILE__, __LINE__);
	}
	if (arg_mat1.numEqual((complexlong)MMAT_NUM_EQUAL_VAL3)
	    != MMAT_NUM_EQUAL_RES3[mat1]) {
	  Console::put(arg1_str);
	  Error::handle(name(), L"numEqual", Error::TEST,
			__FILE__, __LINE__);
	}
#endif	

	// test numNotEqual with two keys
	//
	if (arg_mat1.numNotEqual((int32)MMAT_NUM_NOT_EQUAL_VAL0)
	    != MMAT_NUM_NOT_EQUAL_RES0[mat1]) {
	  Console::put(arg1_str);
	  Error::handle(name(), L"numNotEqual", Error::TEST,
			__FILE__, __LINE__);
	}
	if (arg_mat1.numNotEqual((int32)MMAT_NUM_NOT_EQUAL_VAL1)
	    != MMAT_NUM_NOT_EQUAL_RES1[mat1]) {
	  Console::put(arg1_str);
	  Error::handle(name(), L"numNotEqual", Error::TEST,
			__FILE__, __LINE__);
	}

#ifdef ISIP_TEMPLATE_complex
	if (arg_mat1.numNotEqual((complexlong)MMAT_NUM_NOT_EQUAL_VAL2)
	    != MMAT_NUM_NOT_EQUAL_RES2[mat1]) {
	  Console::put(arg1_str);
	  Error::handle(name(), L"numNotEqual", Error::TEST,
			__FILE__, __LINE__);
	}
	if (arg_mat1.numNotEqual((complexlong)MMAT_NUM_NOT_EQUAL_VAL3)
	    != MMAT_NUM_NOT_EQUAL_RES3[mat1]) {
	  Console::put(arg1_str);
	  Error::handle(name(), L"numNotEqual", Error::TEST,
			__FILE__, __LINE__);
	}
#endif
	
	// test gt
	//
	if (arg_mat1.gt((TIntegral)MMAT_GT_VAL0) != MMAT_GT_RES0[mat1]) {
	  Console::put(arg1_str);
	  Error::handle(name(), L"gt", Error::TEST, __FILE__, __LINE__);
	}
	if (arg_mat1.gt((TIntegral)MMAT_GT_VAL1) != MMAT_GT_RES1[mat1]) {
	  Console::put(arg1_str);
	  Error::handle(name(), L"gt", Error::TEST, __FILE__, __LINE__);
	}

#ifdef ISIP_TEMPLATE_complex
	if (arg_mat1.gt((complexdouble)MMAT_GT_VAL2) != MMAT_GT_RES2[mat1]) {
	  Console::put(arg1_str);
	  Error::handle(name(), L"gt", Error::TEST, __FILE__, __LINE__);
	}
	if (arg_mat1.gt((TIntegral)MMAT_GT_VAL1) != MMAT_GT_RES1[mat1]) {
	  Console::put(arg1_str);
	  Error::handle(name(), L"gt", Error::TEST, __FILE__, __LINE__);
	}
#endif

	// test ge
	//
	if (arg_mat1.ge((TIntegral)MMAT_GE_VAL0) != MMAT_GE_RES0[mat1]) {
	  Console::put(arg1_str);
	  Error::handle(name(), L"ge", Error::TEST, __FILE__, __LINE__);
	}
	if (arg_mat1.ge((TIntegral)MMAT_GE_VAL1) != MMAT_GE_RES1[mat1]) {
	  Console::put(arg1_str);
	  Error::handle(name(), L"ge", Error::TEST, __FILE__, __LINE__);
	}
#ifdef ISIP_TEMPLATE_complex
	if (arg_mat1.ge((TIntegral)MMAT_GE_VAL2) != MMAT_GE_RES2[mat1]) {
	  Console::put(arg1_str);
	  Error::handle(name(), L"ge", Error::TEST, __FILE__, __LINE__);
	}
	if (arg_mat1.ge((TIntegral)MMAT_GE_VAL3) != MMAT_GE_RES3[mat1]) {
	  Console::put(arg1_str);
	  Error::handle(name(), L"ge", Error::TEST, __FILE__, __LINE__);
	}
#endif	

	// test lt
	//
	if (arg_mat1.lt((TIntegral)MMAT_LT_VAL0) != MMAT_LT_RES0[mat1]) {
	  Console::put(arg1_str);
	  Error::handle(name(), L"lt", Error::TEST, __FILE__, __LINE__);
	}
	if (arg_mat1.lt((TIntegral)MMAT_LT_VAL1) != MMAT_LT_RES1[mat1]) {
	  Console::put(arg1_str);
	  Error::handle(name(), L"lt", Error::TEST, __FILE__, __LINE__);
	}
#ifdef ISIP_TEMPLATE_complex
	if (arg_mat1.lt((TIntegral)MMAT_LT_VAL2) != MMAT_LT_RES2[mat1]) {
	  Console::put(arg1_str);
	  Error::handle(name(), L"lt", Error::TEST, __FILE__, __LINE__);
	}
	if (arg_mat1.lt((TIntegral)MMAT_LT_VAL3) != MMAT_LT_RES3[mat1]) {
	  Console::put(arg1_str);
	  Error::handle(name(), L"lt", Error::TEST, __FILE__, __LINE__);
	}
#endif	
	
	// test le
	//
	if (arg_mat1.le((TIntegral)MMAT_LE_VAL0) != MMAT_LE_RES0[mat1]) {
	  Console::put(arg1_str);
	  Error::handle(name(), L"le", Error::TEST, __FILE__, __LINE__);
	}
	if (arg_mat1.le((TIntegral)MMAT_LE_VAL1) != MMAT_LE_RES1[mat1]) {
	  Console::put(arg1_str);
	  Error::handle(name(), L"le", Error::TEST, __FILE__, __LINE__);
	}
#ifdef ISIP_TEMPLATE_complex
	if (arg_mat1.le((TIntegral)MMAT_LE_VAL2) != MMAT_LE_RES2[mat1]) {
	  Console::put(arg1_str);
	  Error::handle(name(), L"le", Error::TEST, __FILE__, __LINE__);
	}
	if (arg_mat1.le((TIntegral)MMAT_LE_VAL3) != MMAT_LE_RES3[mat1]) {
	  Console::put(arg1_str);
	  Error::handle(name(), L"le", Error::TEST, __FILE__, __LINE__);
	}
#endif	
	
	// test eq
	//
	if (arg_mat1.eq((TIntegral)MMAT_EQ_VAL0) != MMAT_EQ_RES0[mat1]) {
	  Console::put(arg1_str);
	  Error::handle(name(), L"eq", Error::TEST, __FILE__, __LINE__);
	}
	if (arg_mat1.eq((TIntegral)MMAT_EQ_VAL1) != MMAT_EQ_RES1[mat1]) {
	  Console::put(arg1_str);
	  Error::handle(name(), L"eq", Error::TEST, __FILE__, __LINE__);
	}
#ifdef ISIP_TEMPLATE_complex
	if (arg_mat1.eq((TIntegral)MMAT_EQ_VAL2) != MMAT_EQ_RES2[mat1]) {
	  Console::put(arg1_str);
	  Error::handle(name(), L"eq", Error::TEST, __FILE__, __LINE__);
	}
	if (arg_mat1.eq((TIntegral)MMAT_EQ_VAL3) != MMAT_EQ_RES3[mat1]) {
	  Console::put(arg1_str);
	  Error::handle(name(), L"eq", Error::TEST, __FILE__, __LINE__);
	}
#endif	
	
	// test ne
	//
	if (arg_mat1.ne((TIntegral)MMAT_NE_VAL0) != MMAT_NE_RES0[mat1]) {
	  Console::put(arg1_str);
	  Error::handle(name(), L"ne", Error::TEST, __FILE__, __LINE__);
	}
	if (arg_mat1.ne((TIntegral)MMAT_NE_VAL1) != MMAT_NE_RES1[mat1]) {
	  Console::put(arg1_str);
	  Error::handle(name(), L"ne", Error::TEST, __FILE__, __LINE__);
	}
#ifdef ISIP_TEMPLATE_complex
	if (arg_mat1.ne((TIntegral)MMAT_NE_VAL2) != MMAT_NE_RES2[mat1]) {
	  Console::put(arg1_str);
	  Error::handle(name(), L"ne", Error::TEST, __FILE__, __LINE__);
	}
	if (arg_mat1.ne((TIntegral)MMAT_NE_VAL3) != MMAT_NE_RES3[mat1]) {
	  Console::put(arg1_str);
	  Error::handle(name(), L"ne", Error::TEST, __FILE__, __LINE__);
	}
#endif	
	
	tmp_mat.assign(arg_mat1);
	if (arg_mat1.ne(arg_mat1)) {
	  Console::put(arg1_str);
	  Error::handle(name(), L"ne", Error::TEST, __FILE__, __LINE__);
	}

	// test min and max methods
	//
	int32 row_pos;
	int32 col_pos;
	TIntegral val;
	TScalar val_res;

	// test min
	//
	val = arg_mat1.min(row_pos, col_pos);
#ifndef ISIP_TEMPLATE_complex
	val_res.assign((TIntegral)MMAT_MIN_RES[mat1][MMAT_DATA_LOC]);
#else
	complexdouble tmp_complex2(MMAT_MIN_RES[mat1][MMAT_DATA_LOC],
				  MMAT_MIN_RES[mat1][MMAT_DATA_LOC + 1]);
	val_res.assign((TIntegral)tmp_complex2);
#endif
	if ((!val_res.almostEqual(val)) ||
	    (row_pos != (int32)MMAT_MIN_RES[mat1][MMAT_NROW_LOC]) ||
	    (col_pos != (int32)MMAT_MIN_RES[mat1][MMAT_NCOL_LOC])) {
	  Console::put(arg1_str);
	  Error::handle(name(), L"min", Error::TEST, __FILE__, __LINE__);
	}
	
	// test max
	//
	val = arg_mat1.max(row_pos, col_pos);
#ifndef ISIP_TEMPLATE_complex
	val_res.assign((TIntegral)MMAT_MAX_RES[mat1][MMAT_DATA_LOC]);
#else
	complexdouble tmp_complex1(MMAT_MAX_RES[mat1][MMAT_DATA_LOC],
				  MMAT_MAX_RES[mat1][MMAT_DATA_LOC + 1]);
	val_res.assign((TIntegral)tmp_complex1);
#endif	
	if ((!val_res.almostEqual(val)) || 
	    (row_pos != (int32)MMAT_MAX_RES[mat1][MMAT_NROW_LOC]) ||
	    (col_pos != (int32)MMAT_MAX_RES[mat1][MMAT_NCOL_LOC])) {
	  Console::put(arg1_str);
	  Error::handle(name(), L"max", Error::TEST, __FILE__, __LINE__);
	}
	
	// test minMag and maxMag methods
	//
	float64 val_mag;
	float64 val_mag_res;
	
	// test minMag
	//
	val_mag = arg_mat1.minMag(row_pos, col_pos);
	val_mag_res = MMAT_MINMAG_RES[mat1][MMAT_DATA_LOC];
	if ((!Integral::almostEqual(val_mag_res, val_mag)) ||
	    (row_pos != (int32)MMAT_MINMAG_RES[mat1][MMAT_NROW_LOC]) ||
	    (col_pos != (int32)MMAT_MINMAG_RES[mat1][MMAT_NCOL_LOC])) {
	  Console::put(arg1_str);
	  Error::handle(name(), L"minMag", Error::TEST, __FILE__, __LINE__);
	}
	
	// test maxMag
	//
	val_mag = arg_mat1.maxMag(row_pos, col_pos);
	val_mag_res = MMAT_MAXMAG_RES[mat1][MMAT_DATA_LOC];
	if ((!Integral::almostEqual(val_mag_res, val_mag)) ||
	    (row_pos != (int32)MMAT_MAXMAG_RES[mat1][MMAT_NROW_LOC]) ||
	    (col_pos != (int32)MMAT_MAXMAG_RES[mat1][MMAT_NCOL_LOC])) {
	  Console::put(arg1_str);
	  Error::handle(name(), L"maxMag", Error::TEST, __FILE__, __LINE__);
	}
	
	// declare local variables
	//
	TScalar dval;

	// test determinant if matrix is square - as we test 8
	// matrices of different types (square, non-square, singular,
	// non-singular), we don't want the diagnose method to return
	// test error for obvious cases. note that the determinant is
	// only tested for signed data types.
	//
	if (typeid(TIntegral) == typeid(float32) ||
	    typeid(TIntegral) == typeid(float64) ||
	    typeid(TIntegral) == typeid(int64) ||
	    typeid(TIntegral) == typeid(int32) ||
	    typeid(TIntegral) == typeid(int16)) {

	  if (arg_mat1.isSquare()) {
	    dval = arg_mat1.determinant();
	    TScalar det_res((TIntegral)MMAT_DET_RES[mat1]);
	    if (!det_res.almostEqual(dval)) {
	      Console::put(arg1_str);
	      dval.debug(L"output");
	      det_res.debug(L"expected result");
	      Error::handle(name(), L"determinant", Error::TEST, 
			    __FILE__, __LINE__);
	    }
	  }
	}

	// test sum
	//
	dval = arg_mat1.sum();
#ifndef ISIP_TEMPLATE_complex
	val_res.assign((TIntegral)MMAT_SUM_RES[mat1]);
#else
	complexdouble tmp_complex3(MMAT_SUM_RES[mat1],
				  MMAT_SUM_RES[mat1 + MMAT_NUM_MATS_TOTAL]);
	val_res.assign((TIntegral)tmp_complex3);
#endif	
	if (!val_res.almostEqual(dval)) {
	  Console::put(arg1_str);
	  dval.debug(L"output");
	  val_res.debug(L"expected result");	
	  Error::handle(name(), L"sum", Error::TEST, __FILE__, __LINE__);
	}
	
	// test sumSquare
	//
	dval = arg_mat1.sumSquare();
#ifndef ISIP_TEMPLATE_complex
	val_res.assign((TIntegral)MMAT_SUM_SQUARE_RES[mat1]);
#else
	complexdouble tmp_complex4(MMAT_SUM_SQUARE_RES[mat1],
				  MMAT_SUM_SQUARE_RES[mat1 + MMAT_NUM_MATS_TOTAL]);
	val_res.assign((TIntegral)tmp_complex4);
#endif
	if (!val_res.almostEqual(dval)) {
	  Console::put(arg1_str);
	  dval.debug(L"sumSq");
	  Error::handle(name(), L"sumSquare", Error::TEST, __FILE__, __LINE__);
	}

	// test mean
	//
	dval = arg_mat1.mean();
#ifndef ISIP_TEMPLATE_complex
	val_res.assign((TIntegral)MMAT_MEAN_RES[mat1]);
#else
	complexdouble tmp_complex5(MMAT_MEAN_RES[mat1],
				  MMAT_MEAN_RES[mat1 + MMAT_NUM_MATS_TOTAL]);
	val_res.assign((TIntegral)tmp_complex5);
#endif	
	if (!val_res.almostEqual(dval)) {
	  Console::put(arg1_str);
	  dval.debug(L"mean");
	  Error::handle(name(), L"mean", Error::TEST, __FILE__, __LINE__);
	}
	
	// test rms
	//
	if (typeid(TIntegral) == typeid(float32) ||
	    typeid(TIntegral) == typeid(float64)) {
	  dval = arg_mat1.rms();
#ifndef ISIP_TEMPLATE_complex
	  val_res.assign((TIntegral)MMAT_RMS_RES[mat1]);
#else
	  complexdouble tmp_complex(MMAT_RMS_RES[mat1],
				    MMAT_RMS_RES[mat1 + MMAT_NUM_MATS_TOTAL]);
	  val_res.assign((TIntegral)tmp_complex);
#endif
	  if (typeid(TIntegral) != typeid(float32)) {
	    if (!val_res.almostEqual(dval, (int32)42)) {
	      Console::put(arg1_str);
	      dval.debug(L"ou rms");
	      val_res.debug(L"res rms");
	      Error::handle(name(), L"rms", Error::TEST, __FILE__, __LINE__);
	    }
	  }
	  else {
	    if (!val_res.almostEqual(dval)) {
	      Console::put(arg1_str);
	      dval.debug(L"out rms");
	      val_res.debug(L"res rms");
	      Error::handle(name(), L"rms", Error::TEST, __FILE__, __LINE__);
	    }
	  }
	}

	// test var
	//
	if (typeid(TIntegral) == typeid(float32) ||
	    typeid(TIntegral) == typeid(float64)) {	
	  dval = arg_mat1.var();
#ifndef ISIP_TEMPLATE_complex
	  val_res.assign((TIntegral)MMAT_VAR_RES[mat1]);
#else
	  complexdouble tmp_complex(MMAT_VAR_RES[mat1],
				    MMAT_VAR_RES[mat1 + MMAT_NUM_MATS_TOTAL]);
	  val_res.assign((TIntegral)tmp_complex);
#endif	  
	  if (typeid(TIntegral) != typeid(float32)) {
	    if (!val_res.almostEqual(dval)) {
	      Console::put(arg1_str);
	      dval.debug(L"out var");
	      val_res.debug(L"res var");
	      Error::handle(name(), L"var", Error::TEST, __FILE__, __LINE__);
	    }
	  }
	  else {
	    if (!val_res.almostEqual(dval)) {
	      Console::put(arg1_str);
	      dval.debug(L"out var");
	      val_res.debug(L"res var");
	      Error::handle(name(), L"var", Error::TEST, __FILE__, __LINE__);
	    }
	  }
	}

	// test trace
	//
	if (arg_mat1.isSquare()) {
	  dval = arg_mat1.trace();
#ifndef ISIP_TEMPLATE_complex
	  val_res.assign((TIntegral)MMAT_TRACE_RES[mat1]);
#else
	  complexdouble tmp_complex(MMAT_TRACE_RES[mat1],
				    MMAT_TRACE_RES[mat1 + MMAT_NUM_MATS_TOTAL]);
	  val_res.assign((TIntegral)tmp_complex);
#endif	  
	  if (!val_res.almostEqual(dval)) {
	    Console::put(arg1_str);
	    dval.debug(L"out var");
	    val_res.debug(L"res trace");
	    Error::handle(name(), L"trace", Error::TEST, __FILE__, __LINE__);
	  }
	}  

	// test sumColumn
	//
	for (int32 col = 0; col < arg_mat1.getNumColumns(); col++) {
	  TScalar res_scal(arg_mat1.sumColumn(col));
#ifndef ISIP_TEMPLATE_complex
	  if (!res_scal.almostEqual((TIntegral)MMAT_SUM_COLUMN_RES[mat1][col]))
#else	    
	    complexdouble tmp_complex(MMAT_SUM_COLUMN_RES[mat1][col],
				      MMAT_SUM_COLUMN_RES[mat1][col + MMAT_NUM_COLS]);
	  if (!res_scal.almostEqual((TIntegral)tmp_complex))
#endif
	    {  
	      Console::put(arg1_str);
	      res_scal.debug(L"res");	  
	      Error::handle(name(), L"sumColumn", Error::TEST, 
			  __FILE__, __LINE__);
	    }
	}
	
	// test sumRow
	//
	for (int32 row = 0; row < arg_mat1.getNumRows(); row++) {
	  TScalar res_scal(arg_mat1.sumRow(row));
#ifndef ISIP_TEMPLATE_complex
	  if (!res_scal.almostEqual((TIntegral)MMAT_SUM_ROW_RES[mat1][row]))
#else
	    complexdouble tmp_complex(MMAT_SUM_ROW_RES[mat1][row],
				      MMAT_SUM_ROW_RES[mat1][row + MMAT_NUM_ROWS]);
	  if (!res_scal.almostEqual((TIntegral)tmp_complex))
#endif
	    {
	      Console::put(arg1_str);
	      res_scal.debug(L"res");	  
	      Error::handle(name(), L"sumRow", Error::TEST, __FILE__, __LINE__);
	    }
	}
	
	// test operator() and getValue methods
	//
	tmp_mat.assign(arg_mat1);
	val_res.assign((TIntegral)3);
	
	// set a specific value 3 at (row, col) = (1, 1)
	//
	tmp_mat.setValue(1, 1, (TIntegral)3);
	
	if (!val_res.almostEqual(tmp_mat(1, 1))) {
	  String out(L"(1,1)");
	  out.concat(tmp_mat(1, 1));
	  Console::put(out);
	  Console::put(arg1_str);
	  Error::handle(name(), L"setValue", Error::TEST, 
			__FILE__, __LINE__);
	}
	
	if (!val_res.almostEqual(tmp_mat.getValue(1, 1))) {
	  String out(L"gv(1,1)");
	  out.concat(tmp_mat.getValue(1, 1));
	  Console::put(out);
	  Console::put(arg1_str);
	  Error::handle(name(), L"getValue", Error::TEST, 
			__FILE__, __LINE__);
	}
      }
    }
    if (level_a > Integral::BRIEF) {
	Console::decreaseIndention();
    }
  }

  // reset indentation
  //
  if (level_a > Integral::NONE) {
    Console::decreaseIndention();
  }
  
  // exit gracefully
  //
  return true;
}

// method: diagnose2
//
// arguments:
//  Integral::DEBUG level: (input) debug level for diagnostics
//
// return: a bool8 value indicating status
//
// this method tests single matrix to vector methods for matrix - the
// diagnose method is designed in such a way that it tests the methods
// for 8 different matrices and for every possible type
//
template<class TScalar, class TIntegral>
bool8 MMatrixMethods::diagnose2(Integral::DEBUG level_a) {
  
  // define TVector
  //
  typedef MVector<TScalar, TIntegral> TVector;
  
  // set indentation
  //
  if (level_a > Integral::NONE) {
    Console::put(L"testing class-specific public methods: single matrix --> vector...\n");
    Console::increaseIndention();
  }
  
  // declare an array of matrix to hold all the 8 matrices used for testing
  //  
  MMatrix<TScalar, TIntegral> arg_mats[MMAT_NUM_MATS_TEST];
  
  // load up the argument matrices
  //
  for (int32 i = 0; i < MMAT_NUM_MATS_TEST; i++) {
    
    // assign the arguments
    //
#ifndef ISIP_TEMPLATE_complex
    arg_mats[i].assign((int32)MMAT_ARG_MATRICES[i][MMAT_NROW_LOC], 
                       (int32)MMAT_ARG_MATRICES[i][MMAT_NCOL_LOC], 
                       (float64*)&MMAT_ARG_MATRICES[i][MMAT_DATA_LOC]);
#else
    arg_mats[i].assignComplexDiagnose((int32)MMAT_ARG_MATRICES[i][MMAT_NROW_LOC], 
                       (int32)MMAT_ARG_MATRICES[i][MMAT_NCOL_LOC], 
                       (float64*)&MMAT_ARG_MATRICES[i][MMAT_DATA_LOC]);
#endif    
  }
  
  // define temporary matrices to be used for testing
  //
  MMatrix<TScalar, TIntegral> tmp_mat;
  MMatrix<TScalar, TIntegral> arg_mat1;
  
  // loop over different matrices
  //
  for (int32 mat1 = 0; mat1 < MMAT_NUM_MATS_TEST; mat1++) {
    
    // declare local variables
    //
    Char mat1c;
    mat1c.assign((byte8)((int)'A' + mat1));
    
    // loop over the different types of matrices
    //
    for (int32 type1 = Integral::FULL; type1 <= Integral::SPARSE; type1++)
      
      // test if the type conversion is possible
      //
      if (arg_mats[mat1].isTypePossible((Integral::MTYPE)type1)) {
	
	// create a diagnostic string to indicate the matrix and its type
	//
	String type1_str(MMatrix<TScalar, TIntegral>::TYPE_MAP(type1));
	String arg1_str(L"testing mat1: ");
	arg1_str.concat(mat1c);
	arg1_str.concat(L", ");
	arg1_str.concat(type1_str);

	// assign the input matrix and change the type - type is
	// changed here so that this particular matrix can be tested for
	// every type it can have
	//
        arg_mat1.assign(arg_mats[mat1]);
        arg_mat1.changeType((Integral::MTYPE)type1);
	
	// test vector multiplication
        // 
        TVector in_vec;
        TVector out_vec;
        TVector vec_res;
        
	// test vmult
        //
        in_vec.assign((int32)MMAT_NUM_COLS, (float64*)MMAT_VMULT_ARG_REAL);
        vec_res.assign((int32)MMAT_VMULT_RES_REAL[mat1][0], 
                       (float64*)&MMAT_VMULT_RES_REAL[mat1][1]);
#ifdef ISIP_TEMPLATE_complex
	TVector tmp;
	tmp.assign((int32)MMAT_VMULT_RES_REAL[mat1][0], 
		   (float64*)&MMAT_VMULT_RES_REAL[mat1][1 + MMAT_NUM_COLS]);
	tmp.mult(TIntegral(0, 1));
	vec_res.add(tmp);
#endif

        // test only if the dimensions match - as we test 8 matrices
	// of different dimensions, we don't want the diagnose method to
	// return test error for obvious cases
	//
        if (arg_mat1.getNumRows() == in_vec.length()) {
          arg_mat1.vmult(out_vec, in_vec);

          if (!out_vec.almostEqual(vec_res)) {
	    out_vec.debug(L"out value");
	    vec_res.debug(L"res value");
            Console::put(arg1_str);
            Error::handle(name(), L"vmult", Error::TEST, __FILE__, __LINE__);
          }
        }

	// additional test for input vector with non-zero imaginary part
	//
#ifdef ISIP_TEMPLATE_complex
        in_vec.assign((int32)MMAT_NUM_COLS, (float64*)MMAT_VMULT_ARG_COMPLEX);
	tmp.assign((int32)MMAT_NUM_COLS,
		   (float64*)&MMAT_QUADRATIC_VEC_COMPLEX[MMAT_NUM_COLS]);
	tmp.mult(TScalar(0, 1));
 	in_vec.add(tmp);
	
        vec_res.assign((int32)MMAT_VMULT_RES_COMPLEX[mat1][0], 
                       (float64*)&MMAT_VMULT_RES_COMPLEX[mat1][1]);
	tmp.assign((int32)MMAT_VMULT_RES_COMPLEX[mat1][0],
		   (float64*)&MMAT_VMULT_RES_COMPLEX[mat1][1 + MMAT_NUM_COLS]);
	tmp.mult(TIntegral(0, 1));
 	vec_res.add(tmp);

        // test only if the dimensions match - as we test 8 matrices
	// of different dimensions, we don't want the diagnose method to
	// return test error for obvious cases
	//
        if (arg_mat1.getNumRows() == in_vec.length()) {
          arg_mat1.vmult(out_vec, in_vec);
	
          if (!out_vec.almostEqual(vec_res)) {
	    out_vec.debug(L"out value");
	    vec_res.debug(L"res value");
            Console::put(arg1_str);
            Error::handle(name(), L"vmult complex", Error::TEST, __FILE__, __LINE__);
          }
        }
#endif
	
        // test multv
        //
        in_vec.assign((int32)MMAT_NUM_ROWS, (float64*)MMAT_MULTV_ARG_REAL);
        vec_res.assign((int32)MMAT_MULTV_RES_REAL[mat1][0], 
                       (float64*)&MMAT_MULTV_RES_REAL[mat1][1]);
#ifdef ISIP_TEMPLATE_complex
	tmp.assign((int32)MMAT_MULTV_RES_REAL[mat1][0], 
		   (float64*)&MMAT_MULTV_RES_REAL[mat1][1 + MMAT_NUM_ROWS]);
	tmp.mult(TIntegral(0, 1));
	vec_res.add(tmp);
#endif

        // test only if the dimensions match - as we test 8 matrices
	// of different dimensions, we don't want the diagnose method to
	// return test error for obvious cases
	//
        if (arg_mat1.getNumColumns() == in_vec.length()) {
          arg_mat1.multv(out_vec, in_vec);

          if (!out_vec.almostEqual(vec_res)) {
	    out_vec.debug(L"out value");
	    vec_res.debug(L"res value");
            Console::put(arg1_str);
            Error::handle(name(), L"multv", Error::TEST, __FILE__, __LINE__);
          }
        }

	// additional test for input vector with non-zero imaginary part
	//
#ifdef ISIP_TEMPLATE_complex
        in_vec.assign((int32)MMAT_NUM_ROWS, (float64*)MMAT_MULTV_ARG_COMPLEX);
	tmp.assign((int32)MMAT_NUM_ROWS,
		   (float64*)&MMAT_QUADRATIC_VEC_COMPLEX[MMAT_NUM_ROWS]);
	tmp.mult(TScalar(0, 1));
 	in_vec.add(tmp);
	
        vec_res.assign((int32)MMAT_MULTV_RES_COMPLEX[mat1][0], 
                       (float64*)&MMAT_MULTV_RES_COMPLEX[mat1][1]);
	tmp.assign((int32)MMAT_MULTV_RES_COMPLEX[mat1][0],
		   (float64*)&MMAT_MULTV_RES_COMPLEX[mat1][1 + MMAT_NUM_ROWS]);
	tmp.mult(TIntegral(0, 1));
 	vec_res.add(tmp);

        // test only if the dimensions match - as we test 8 matrices
	// of different dimensions, we don't want the diagnose method to
	// return test error for obvious cases
	//
        if (arg_mat1.getNumColumns() == in_vec.length()) {
          arg_mat1.multv(out_vec, in_vec);
	
          if (!out_vec.almostEqual(vec_res)) {
	    out_vec.debug(L"out value");
	    vec_res.debug(L"res value");
            Console::put(arg1_str);
            Error::handle(name(), L"multv complex", Error::TEST, __FILE__, __LINE__);
          }
        }
#endif
	
	// test get/set row methods
	//	
        if ((mat1 == Integral::FULL) && (mat1 < 5)) {
	  in_vec.assign((int32)MMAT_NUM_COLS, (float64*)MMAT_MULTV_ARG_REAL);
          vec_res.assign(in_vec);
          tmp_mat.assign(arg_mat1);
          tmp_mat.setRow(2, in_vec);
          tmp_mat.getRow(out_vec, 2);
          if (!out_vec.almostEqual(in_vec)) {
	    Console::put(arg1_str);
            Error::handle(name(), L"getRow", Error::TEST, 
                          __FILE__, __LINE__);
          }
	}

	// test get/set column methods
	//
	if (((mat1 == Integral::FULL) || (mat1 == Integral::SPARSE))
	    && (mat1 < 6)) {
	  in_vec.assign((int32)MMAT_NUM_COLS, (float64*)MMAT_MULTV_ARG_REAL);
	  tmp_mat.assign(arg_mat1);

          tmp_mat.setColumn(2, in_vec);
	  tmp_mat.getColumn(out_vec, 2);
          if (!out_vec.almostEqual(in_vec)) {
	    Console::put(arg1_str);
            Error::handle(name(), L"getColumn", Error::TEST, 
                          __FILE__, __LINE__);
          }	  
	}
      }	
      
      // test quadratic
      //
      TScalar val_res;
      TScalar dval;
      TIntegral dval_ret;
      TVector in_vec;

      // test only if the matrix is square as quadratic method is for
      // square matrix only
      //
      if (arg_mat1.isSquare()) {
	in_vec.assign((int32)MMAT_NUM_ROWS,
		      (float64*)MMAT_QUADRATIC_VEC_REAL);
#ifndef ISIP_TEMPLATE_complex
	val_res.assign((TIntegral)MMAT_QUADRATIC_RES_REAL[mat1]);
#else
	complexdouble tmp_complex8(MMAT_QUADRATIC_RES_REAL[mat1],
				   MMAT_QUADRATIC_RES_REAL
				   [mat1 + MMAT_NUM_MATS_TOTAL]);
	val_res.assign((TIntegral)tmp_complex8);
#endif
	arg_mat1.quadratic(dval_ret, in_vec);
	dval = dval_ret;
	if (!val_res.almostEqual(dval)) {
	  dval.debug(L"out value");
	  val_res.debug(L"res value");
	  Error::handle(name(), L"quadratic real", Error::TEST, 
			__FILE__, __LINE__);
	}
	
	// additional test for input vector with non-zero imaginary part
	//
#ifdef ISIP_TEMPLATE_complex
	in_vec.assign((int32)MMAT_NUM_ROWS,
		      (float64*)MMAT_QUADRATIC_VEC_COMPLEX);
	TVector tmp;
	tmp.assign((int32)MMAT_NUM_ROWS,
		   (float64*)&MMAT_QUADRATIC_VEC_COMPLEX[MMAT_NUM_ROWS]);
	
	tmp.mult(TScalar(0, 1));
 	in_vec.add(tmp);
	
	complexdouble tmp_complex7(MMAT_QUADRATIC_RES_COMPLEX[mat1],
				   MMAT_QUADRATIC_RES_COMPLEX
				   [mat1 + MMAT_NUM_MATS_TOTAL]);
	val_res.assign((TIntegral)tmp_complex7);
	
	arg_mat1.quadratic(dval_ret, in_vec);
	dval = dval_ret;
	if (!val_res.almostEqual(dval)) {
	  dval.debug(L"out value");
	  val_res.debug(L"res value");
	  Error::handle(name(), L"quadratic complex", Error::TEST, 
			__FILE__, __LINE__);
	}
#endif
      }
  }
  

  // test the vector outerProduct methods. This doesn't go in the loop because
  // it is a conversion from vector to matrix
  //
  TVector op_vec;
  op_vec.assign(L"1,2,0,4,5");
  
  MMatrix<TScalar, TIntegral> op_vec_mat;
  op_vec_mat.assign(1, op_vec.length(),  L"1,2,0,4,5", Integral::FULL);
  MMatrix<TScalar, TIntegral> op_vec_mat_trans;
  op_vec_mat_trans.assign(op_vec.length(), 1, L"1,2,0,4,5", Integral::FULL);

  MMatrix<TScalar, TIntegral> res_mat(op_vec.length(),
				      op_vec.length(), Integral::FULL);
  res_mat.mult(op_vec_mat_trans, op_vec_mat);

  for (int32 type1 = Integral::FULL; type1 <= Integral::SPARSE; type1++) {
    MMatrix<TScalar, TIntegral> tmp_mat(0, 0, (Integral::MTYPE)type1);
    Integral::MTYPE exp_type = (type1 == Integral::SPARSE) ?
      Integral::SPARSE : Integral::FULL;

    // compute the outer product
    //
    tmp_mat.outerProduct(op_vec);

    // compare the matrix with the expected result
    //
    if ((tmp_mat.getType() != exp_type) || !tmp_mat.almostEqual(res_mat)) {
      Error::handle(name(), L"outerProduct (vector)", Error::TEST,
		    __FILE__, __LINE__);
    }
  }
    
    
  // reset indentation
  //
  if (level_a > Integral::NONE) {
    Console::decreaseIndention();
  }  

  // exit gracefully
  //
  return true;
}

// method: diagnose3
//
// arguments:
//  Integral::DEBUG level: (input) debug level for diagnostics
//
// return: a bool8 value indicating status
//
// this method tests matrix to matrix methods for matrix - the diagnose
// method is designed in such a way that it tests the methods for 8
// different matrices and for every possible type
//
template<class TScalar, class TIntegral>
bool8 MMatrixMethods::diagnose3(Integral::DEBUG level_a) {

  // define TVector
  //
  typedef MVector<TScalar, TIntegral> TVector;

  // set indentation
  //
  if (level_a > Integral::NONE) {
    Console::put(L"testing class-specific public methods: single matrix --> matrix...\n");
    Console::increaseIndention();
  }

  // declare an array of matrix to hold all the 8 matrices used for testing
  //    
  MMatrix<TScalar, TIntegral> arg_mats[MMAT_NUM_MATS_TEST];

  // load up the argument matrices
  //
  for (int32 i = 0; i < MMAT_NUM_MATS_TEST; i++) {
    
    // assign the arguments
    //
#ifndef ISIP_TEMPLATE_complex
    arg_mats[i].assign((int32)MMAT_ARG_MATRICES[i][MMAT_NROW_LOC], 
                       (int32)MMAT_ARG_MATRICES[i][MMAT_NCOL_LOC], 
                       (float64*)&MMAT_ARG_MATRICES[i][MMAT_DATA_LOC]);
#else
    arg_mats[i].assignComplexDiagnose((int32)MMAT_ARG_MATRICES[i][MMAT_NROW_LOC], 
                       (int32)MMAT_ARG_MATRICES[i][MMAT_NCOL_LOC], 
                       (float64*)&MMAT_ARG_MATRICES[i][MMAT_DATA_LOC]);
#endif    
  }

  // declare temporary matrix to be used in the whole diagnose method
  // for testing
  //
  MMatrix<TScalar, TIntegral> res_mat;
  MMatrix<TScalar, TIntegral> tmp_mat;
  MMatrix<TScalar, TIntegral> res_mat0;
  MMatrix<TScalar, TIntegral> arg_mat1;

  // loop over different matrices
  //
  for (int32 mat1 = 0; mat1 < MMAT_NUM_MATS_TEST; mat1++) {

    // declare local variables
    //
    Char mat1c;
    mat1c.assign((byte8)((int)'A' + mat1));
    
    // loop over the different types of matrices
    //
    for (int32 type1 = Integral::FULL; type1 <= Integral::SPARSE; type1++) {

      // test if the type conversion is possible
      //
      if (arg_mats[mat1].isTypePossible((Integral::MTYPE)type1)) {

	// create a diagnostic string to indicate the matrix and its type
	//	
	String type1_str(MMatrix<TScalar, TIntegral>::TYPE_MAP(type1));
	String arg1_str(L"testing mat1: ");
	arg1_str.concat(mat1c);
	arg1_str.concat(L", ");
	arg1_str.concat(type1_str);

	// assign the input matrix and change the type - type is
	// changed here so that this particular matrix can be tested for
	// every type it can have
	//
        arg_mat1.assign(arg_mats[mat1]);
        arg_mat1.changeType((Integral::MTYPE)type1);
        
        // test neg - this method is not applicable for byte8 and
        // unsigned types
        //
        if ((typeid(TIntegral) != typeid(byte8)) &&
            (typeid(TIntegral) != typeid(uint16)) &&
            (typeid(TIntegral) != typeid(uint32)) &&
            (typeid(TIntegral) != typeid(uint64))) {
          tmp_mat.neg(arg_mat1);
#ifndef ISIP_TEMPLATE_complex
          res_mat.assign((int32)MMAT_NEG_RES[mat1][MMAT_NROW_LOC], 
                         (int32)MMAT_NEG_RES[mat1][MMAT_NCOL_LOC], 
                         (float64*)&MMAT_NEG_RES[mat1][MMAT_DATA_LOC]);
#else
          res_mat.assignComplexDiagnose((int32)MMAT_NEG_RES[mat1][MMAT_NROW_LOC], 
                         (int32)MMAT_NEG_RES[mat1][MMAT_NCOL_LOC], 
                         (float64*)&MMAT_NEG_RES[mat1][MMAT_DATA_LOC]);
#endif	  
          if (!res_mat.eq(tmp_mat)) {
            Console::put(arg1_str);
            Error::handle(name(), L"neg", Error::TEST, __FILE__, __LINE__);
          }
        }

        // test matrix assign methods - here we test for all matrix
        // types as matrix assign is type specific
        //
        MMatrix<Byte, byte8> mat_byt;
        MMatrix<Ushort, uint16> mat_usht;
        MMatrix<Ulong, uint32> mat_ulng;
        MMatrix<Ullong, uint64> mat_ullg;
        MMatrix<Short, int16> mat_sht;
        MMatrix<Long, int32> mat_lng;
        MMatrix<Llong, int64> mat_llng;
        MMatrix<Float, float32> mat_flt;
        MMatrix<Double, float64> mat_dbl;

	// assign result
	//
        res_mat.assign((int32)MMAT_ARG_MATRICES[mat1][MMAT_NROW_LOC], 
                       (int32)MMAT_ARG_MATRICES[mat1][MMAT_NCOL_LOC], 
                       (float64*)&MMAT_ARG_MATRICES[mat1][MMAT_DATA_LOC]);

	// assign values to byte8 type
	//
        mat_byt.assign((int32)MMAT_ARG_MATRICES[mat1][MMAT_NROW_LOC], 
                       (int32)MMAT_ARG_MATRICES[mat1][MMAT_NCOL_LOC], 
                       (float64*)&MMAT_ARG_MATRICES[mat1][MMAT_DATA_LOC]);

        tmp_mat.assign(mat_byt);
        if (!tmp_mat.almostEqual(res_mat)) {
          Console::put(arg1_str);
          Error::handle(name(), L"assign", Error::TEST, __FILE__, __LINE__);
        }

	// assign values to ushort type
	//	
        mat_usht.assign((int32)MMAT_ARG_MATRICES[mat1][MMAT_NROW_LOC], 
                        (int32)MMAT_ARG_MATRICES[mat1][MMAT_NCOL_LOC], 
                        (float64*)&MMAT_ARG_MATRICES[mat1][MMAT_DATA_LOC]);

	tmp_mat.assign(mat_usht);
        if (!tmp_mat.almostEqual(res_mat)) {
          Console::put(arg1_str);
          Error::handle(name(), L"assign", Error::TEST, __FILE__, __LINE__);
        }

	// assign values to uint32 type
	//		
        mat_ulng.assign((int32)MMAT_ARG_MATRICES[mat1][MMAT_NROW_LOC], 
                        (int32)MMAT_ARG_MATRICES[mat1][MMAT_NCOL_LOC], 
                        (float64*)&MMAT_ARG_MATRICES[mat1][MMAT_DATA_LOC]);

        tmp_mat.assign(mat_ulng);
        if (!tmp_mat.almostEqual(res_mat)) {
          Console::put(arg1_str);
          Error::handle(name(), L"assign", Error::TEST, __FILE__, __LINE__);
        }

	// assign values to uint64 type
	//			
        mat_ullg.assign((int32)MMAT_ARG_MATRICES[mat1][MMAT_NROW_LOC], 
                        (int32)MMAT_ARG_MATRICES[mat1][MMAT_NCOL_LOC], 
                        (float64*)&MMAT_ARG_MATRICES[mat1][MMAT_DATA_LOC]);

        tmp_mat.assign(mat_ullg);
        if (!tmp_mat.almostEqual(res_mat)) {
          Console::put(arg1_str);
          Error::handle(name(), L"assign", Error::TEST, __FILE__, __LINE__);
        }
        
	// assign values to int16 type
	//				
        mat_sht.assign((int32)MMAT_ARG_MATRICES[mat1][MMAT_NROW_LOC], 
                       (int32)MMAT_ARG_MATRICES[mat1][MMAT_NCOL_LOC], 
                       (float64*)&MMAT_ARG_MATRICES[mat1][MMAT_DATA_LOC]);

        tmp_mat.assign(mat_sht);
        if (!tmp_mat.almostEqual(res_mat)) {
          Console::put(arg1_str);
          Error::handle(name(), L"assign", Error::TEST, __FILE__, __LINE__);
        }

	// assign values to int32 type
	//					
        mat_lng.assign((int32)MMAT_ARG_MATRICES[mat1][MMAT_NROW_LOC], 
                       (int32)MMAT_ARG_MATRICES[mat1][MMAT_NCOL_LOC], 
                       (float64*)&MMAT_ARG_MATRICES[mat1][MMAT_DATA_LOC]);

        tmp_mat.assign(mat_lng);
        if (!tmp_mat.almostEqual(res_mat)) {
          Console::put(arg1_str);
          Error::handle(name(), L"assign", Error::TEST, __FILE__, __LINE__);
        }

	// assign values to int64 type
	//						
        mat_llng.assign((int32)MMAT_ARG_MATRICES[mat1][MMAT_NROW_LOC], 
                        (int32)MMAT_ARG_MATRICES[mat1][MMAT_NCOL_LOC], 
                        (float64*)&MMAT_ARG_MATRICES[mat1][MMAT_DATA_LOC]);

        tmp_mat.assign(mat_llng);
        if (!tmp_mat.almostEqual(res_mat)) {
          Console::put(arg1_str);
          Error::handle(name(), L"assign", Error::TEST, __FILE__, __LINE__);
        }

	// assign values to float32 type
	//							
        mat_flt.assign((int32)MMAT_ARG_MATRICES[mat1][MMAT_NROW_LOC], 
                       (int32)MMAT_ARG_MATRICES[mat1][MMAT_NCOL_LOC], 
                       (float64*)&MMAT_ARG_MATRICES[mat1][MMAT_DATA_LOC]);

        tmp_mat.assign(mat_flt);
        if (!tmp_mat.almostEqual(res_mat)) {
          Console::put(arg1_str);
          Error::handle(name(), L"assign", Error::TEST, __FILE__, __LINE__);
        }

	// assign values to float64 type
	//								
        mat_dbl.assign((int32)MMAT_ARG_MATRICES[mat1][MMAT_NROW_LOC], 
                       (int32)MMAT_ARG_MATRICES[mat1][MMAT_NCOL_LOC], 
                       (float64*)&MMAT_ARG_MATRICES[mat1][MMAT_DATA_LOC]);

        tmp_mat.assign(mat_dbl);
        if (!tmp_mat.almostEqual(res_mat)) {
          Console::put(arg1_str);
          Error::handle(name(), L"assign", Error::TEST, __FILE__, __LINE__);
        }
	
        // test scalar addition
        //
	tmp_mat.assign(arg_mat1);
        tmp_mat.add(3);
#ifndef ISIP_TEMPLATE_complex
        res_mat.assign((int32)MMAT_ADD_SCAL_RES[mat1][MMAT_NROW_LOC], 
                       (int32)MMAT_ADD_SCAL_RES[mat1][MMAT_NCOL_LOC], 
                       (float64*)&MMAT_ADD_SCAL_RES[mat1][MMAT_DATA_LOC]);
#else
	res_mat.assignComplexDiagnose((int32)MMAT_ADD_SCAL_RES[mat1][MMAT_NROW_LOC], 
                       (int32)MMAT_ADD_SCAL_RES[mat1][MMAT_NCOL_LOC], 
                       (float64*)&MMAT_ADD_SCAL_RES[mat1][MMAT_DATA_LOC]);
#endif
	// make sure the type wasn't changed in the operation
	//
	if (arg_mat1.getType() != tmp_mat.getType()) {
          Error::handle(name(), L"add", Error::TEST, __FILE__, __LINE__);
        }

	// for a diagonal matrix, only the diagonal elements will be
	// set.
	//
	if (arg_mat1.getType() == Integral::DIAGONAL) {
	  MVector<TScalar, TIntegral> tmp_vec;
	  res_mat.getDiagonal(tmp_vec);
	  res_mat0.clear();
	  res_mat0.setDimensions(res_mat);
	  res_mat0.setDiagonal(tmp_vec);
	}
	else if (arg_mat1.getType() == Integral::LOWER_TRIANGULAR) {
	  res_mat.getLower(res_mat0);
	}
	else if (arg_mat1.getType() == Integral::UPPER_TRIANGULAR) {
	  res_mat.getUpper(res_mat0);
	}
	else {
	  res_mat0.assign(res_mat);
	}
	  
        if (!res_mat0.eq(tmp_mat)) {
	  res_mat0.debug(L"res_mat0");
	  tmp_mat.debug(L"tmp_mat");
          Console::put(arg1_str);
          Error::handle(name(), L"add", Error::TEST, __FILE__, __LINE__);
        }
	
        // test scalar subtraction - in scalar addition test, we tested
	// (matrix + 3), now we test {(matrix + 3) - 3} which should be
	// same as matrix itself
        //
        tmp_mat.sub(3);
        res_mat.assign(arg_mat1);
        if (!res_mat.eq(tmp_mat)) {
          Console::put(arg1_str);
          Error::handle(name(), L"sub", Error::TEST, __FILE__, __LINE__);
        }
        
	// make sure the type wasn't changed in the operation
	//
	if (arg_mat1.getType() != tmp_mat.getType()) {
	  Console::put(arg1_str);
          Error::handle(name(), L"add", Error::TEST, __FILE__, __LINE__);
        }

        // test scalar multiplication
        //
        tmp_mat.assign(arg_mat1);
	tmp_mat.mult(3);
        res_mat.setDimensions(4, 4, false, Integral::FULL);
#ifndef ISIP_TEMPLATE_complex
        res_mat.assign((int32)MMAT_MULT_SCAL_RES[mat1][MMAT_NROW_LOC], 
                       (int32)MMAT_MULT_SCAL_RES[mat1][MMAT_NCOL_LOC], 
                       (float64*)&MMAT_MULT_SCAL_RES[mat1][MMAT_DATA_LOC]);
#else	
        res_mat.assignComplexDiagnose((int32)MMAT_MULT_SCAL_RES[mat1][MMAT_NROW_LOC], 
                       (int32)MMAT_MULT_SCAL_RES[mat1][MMAT_NCOL_LOC], 
                       (float64*)&MMAT_MULT_SCAL_RES[mat1][MMAT_DATA_LOC]);
#endif	
	
        if (!res_mat.eq(tmp_mat)) {
          Console::put(arg1_str);
          Error::handle(name(), L"mult", Error::TEST, __FILE__, __LINE__);
        }

	// make sure the type wasn't changed in the operation
	//
	if (arg_mat1.getType() != tmp_mat.getType()) {
	  Console::put(arg1_str);
          Error::handle(name(), L"add", Error::TEST, __FILE__, __LINE__);
        }

        // test scalar division - in scalar multiplication test, we tested
	// (matrix * 3), now we test {(matrix * 3) / 3} which should be
	// same as matrix itself
        //	
        tmp_mat.div(3);
	res_mat.assign(arg_mat1);
        if (!res_mat.almostEqual(tmp_mat)) {
          Console::put(arg1_str);
          Error::handle(name(), L"div", Error::TEST, __FILE__, __LINE__);
        }

	// make sure the type wasn't changed in the operation
	//
	if (arg_mat1.getType() != tmp_mat.getType()) {
	  Console::put(arg1_str);
          Error::handle(name(), L"add", Error::TEST, __FILE__, __LINE__);
        }

	// test sortSparse
	//
	tmp_mat.assign(arg_mat1, Integral::SPARSE);
	res_mat.assign(arg_mat1);
	
	// make tmp_mat's order in mess
	//  swap the first two elements with the last two elements
	//
	int32 nelms = tmp_mat.m_d.length() - 1;
	for (int32 index = 0; index < 2; index++) {
	  TIntegral tmp_m = tmp_mat.m_d(index);
	  Long tmp_row_index = tmp_mat.row_index_d(index);
	  Long tmp_col_index = tmp_mat.col_index_d(index);

	  tmp_mat.m_d(index) = tmp_mat.m_d(nelms - index);
	  tmp_mat.row_index_d(index) = tmp_mat.row_index_d(nelms - index);
	  tmp_mat.col_index_d(index) = tmp_mat.col_index_d(nelms - index);

	  tmp_mat.m_d(nelms - index) = tmp_m;
	  tmp_mat.row_index_d(nelms - index) = tmp_row_index;
	  tmp_mat.col_index_d(nelms - index) = tmp_col_index;
	}

	tmp_mat.sortSparse();
	if (!res_mat.almostEqual(tmp_mat)) {
	  Console::put(arg1_str);
	  Error::handle(name(), L"sortSparse", Error::TEST, 
			__FILE__, __LINE__);
	}
	
        // test inverse - for this matrix should be square and a
        // non-singular matrix. only tested for signed data types
        // since the determinant method (called by isSingular) only
        // works for signed data types
        //
	if ((typeid(float64) == typeid(TIntegral)) ||
	    (typeid(float32) == typeid(TIntegral)) ||
	    (typeid(complexdouble) == typeid(TIntegral)) ||
	    (typeid(complexfloat) == typeid(TIntegral))) {

	  if (arg_mat1.isSquare() &&
	      !arg_mat1.isSingular(MMatrix<TScalar, TIntegral>::THRESH_SINGULAR)) {

	    // test inverse
	    //  multiply the input matrix by the determinants to assure
	    //  all integer values in inverse
	    //  A.inverse()
	    //
	    tmp_mat.assign(arg_mat1);
	    
            tmp_mat.inverse();
            tmp_mat.mult(arg_mat1.determinant());
            res_mat.setDimensions(4, 4, false, 
				  Integral::FULL);
	    
#ifndef ISIP_TEMPLATE_complex
            res_mat.assign((int32)MMAT_INV_RES[mat1][MMAT_NROW_LOC], 
                           (int32)MMAT_INV_RES[mat1][MMAT_NCOL_LOC], 
                           (float64*)&MMAT_INV_RES[mat1][MMAT_DATA_LOC]);
#else
	    res_mat.assignComplexDiagnose(
			   (int32)MMAT_INV_RES[mat1][MMAT_NROW_LOC], 
                           (int32)MMAT_INV_RES[mat1][MMAT_NCOL_LOC], 
                           (float64*)&MMAT_INV_RES[mat1][MMAT_DATA_LOC]);
#endif
            if (!res_mat.almostEqual(tmp_mat, 1, 0.01)) {
	      tmp_mat.debug(L"tmp_mat");
	      Console::put(arg1_str);
              Error::handle(name(), L"A.inverse()", Error::TEST, 
                            __FILE__, __LINE__);
            }

	    // test inverse
	    //  A.inverse(B)
	    //
	    for (int32 type2 = Integral::FULL;
		 type2 <= Integral::SPARSE; type2++) {
	      if (arg_mat1.isTypePossible((Integral::MTYPE)type2)) {
		tmp_mat.setDimensions(arg_mat1, false, (Integral::MTYPE)type2);
		tmp_mat.inverse(arg_mat1);

		tmp_mat.mult(arg_mat1.determinant());
		res_mat.setDimensions(4, 4, false, 
				      Integral::FULL);
#ifndef ISIP_TEMPLATE_complex
		res_mat.assign((int32)MMAT_INV_RES[mat1][MMAT_NROW_LOC], 
			       (int32)MMAT_INV_RES[mat1][MMAT_NCOL_LOC], 
			       (float64*)&MMAT_INV_RES[mat1][MMAT_DATA_LOC]);
#else
		res_mat.assignComplexDiagnose(
			   (int32)MMAT_INV_RES[mat1][MMAT_NROW_LOC], 
                           (int32)MMAT_INV_RES[mat1][MMAT_NCOL_LOC], 
                           (float64*)&MMAT_INV_RES[mat1][MMAT_DATA_LOC]);
#endif
		if (!res_mat.almostEqual(tmp_mat, 1, 0.01)) {
		  tmp_mat.debug(L"tmp_mat");
		  Console::put(arg1_str);
		  Error::handle(name(), L"A.inverse(B)", Error::TEST, 
				__FILE__, __LINE__);
		}
	      }
	    }
	  }
        }

        // test transpose
        //
	tmp_mat.assign(arg_mat1);
        tmp_mat.transpose();
        
        res_mat.setDimensions(4, 4, false, Integral::FULL);

#ifndef ISIP_TEMPLATE_complex
        res_mat.assign((int32)MMAT_TRANS_RES[mat1][MMAT_NROW_LOC], 
                       (int32)MMAT_TRANS_RES[mat1][MMAT_NCOL_LOC], 
                       (float64*)&MMAT_TRANS_RES[mat1][MMAT_DATA_LOC]);
#else
        res_mat.assignComplexDiagnose((int32)MMAT_TRANS_RES[mat1][MMAT_NROW_LOC], 
                       (int32)MMAT_TRANS_RES[mat1][MMAT_NCOL_LOC], 
                       (float64*)&MMAT_TRANS_RES[mat1][MMAT_DATA_LOC]);
#endif	
	
        if (!res_mat.eq(tmp_mat)) {
          Console::put(arg1_str);
          Error::handle(name(), L"transpose", Error::TEST, __FILE__, __LINE__);
        }

       	// test singular value decomposition and back substitution
	//
	if ((typeid(float64) == typeid(TIntegral)) ||
	    (typeid(float32) == typeid(TIntegral))) {
	  
	  // create temporary matrices
	  //
	  MMatrix<TScalar, TIntegral> U;
	  MMatrix<TScalar, TIntegral> W;
	  MMatrix<TScalar, TIntegral> V;

	  // compute the singular value decomposition
	  //
	  arg_mat1.decompositionSVD(U, W, V);
	  
	  // verification
	  //
	  int32 m = arg_mat1.getNumRows();
	  int32 n = arg_mat1.getNumColumns();
	  MVector<TScalar, TIntegral> tmp;
	  MVector<TScalar, TIntegral> tmp2;
	  
	  // this test applies to all matrices:
	  //   verify that u * w * v' == A
	  //
	  V.transpose();
	  MMatrix<TScalar, TIntegral> tmp_mat;
	  tmp_mat.mult(U, W);
	  tmp_mat.mult(V);
	  V.transpose();
	  if (!arg_mat1.almostEqual(tmp_mat)) {
	    arg_mat1.debug(L"arg_mat1");
	    U.debug(L"U");
	    W.debug(L"W");
	    V.debug(L"V");
	    tmp_mat.debug(L"U * w * V'");
	    Error::handle(name(), L"decompositionSVD: U * W * V' != arg_mat1",
			  Error::TEST,  __FILE__, __LINE__);
	  }

	  // create a temporary data vector of the appropriate size
	  //
	  MVector<TScalar, TIntegral> b(m);
	  MVector<TScalar, TIntegral> x;
	  b.rand();

	  // solve the set of equations
	  //
	  W.svdSolve(x, U, W, V, b, true);

	  // verify that x solves the set
	  //
	  MVector<TScalar, TIntegral> b_new;

	  arg_mat1.multv(b_new, x);
	  
	  // if m < n or the matrix is square and not singular we
	  // expect a perfect solution
	  //
	  if ((m < n)  || (arg_mat1.isSquare() && !arg_mat1.isSingular())) {
	    if (!b_new.almostEqual(b)) {
	      arg_mat1.debug(L"arg_mat1");
	      U.debug(L"U");
	      W.debug(L"W");
	      V.debug(L"V");
	      x.debug(L"x");
	      b.debug(L"b");
	      b_new.debug(L"b_new");
	      Error::handle(name(), L"decompositionSVD failed",
			    Error::ARG, __FILE__, __LINE__);
	    }

	    // verify that w = u' * A * v
	    //
	    U.transpose();
	    tmp_mat.mult(U, arg_mat1);
	    tmp_mat.mult(V);
	    U.transpose();
	    if (!W.almostEqual(tmp_mat)) {
	      arg_mat1.debug(L"arg_mat1");
	      U.debug(L"U");
	      W.debug(L"W");
	      V.debug(L"V");
	      tmp_mat.debug(L"U' * arg_mat1 * V");
	      Error::handle(name(),
			    L"decompositionSVD: U' * arg_mat1 * V != W",
			    Error::ARG, __FILE__, __LINE__);
	    }
	  }
	}

	// test rank, only for float32 type and float64 type
	//
#ifdef ISIP_TEMPLATE_fp	
	if ((typeid(float64) == typeid(TIntegral)) ||
	    (typeid(float32) == typeid(TIntegral))) {

	  Long rank_mat;
          rank_mat.assign((int32)MMAT_RANK_TEST[mat1]);

	  int32 rank = arg_mat1.rank();
	   if (rank != (int32)rank_mat) {
	     arg_mat1.debug(L"rank_mat");
	     Long(rank).debug(L"rank=");
	     rank_mat.debug(L"expected rank");
	     Long(mat1).debug(L"mat1=");
	     Error::handle(name(), L"rank", Error::TEST, __FILE__, __LINE__);
	   } 
	}
#endif

	// test QR decomposition
	//
	if ((typeid(float64) == typeid(TIntegral)) ||
	    (typeid(float32) == typeid(TIntegral))) {
	  
	  // create temporary matrices
	  //
	  MMatrix<TScalar, TIntegral> Q;
	  MMatrix<TScalar, TIntegral> R;

	  // compute the QR decomposition
	  //
	  arg_mat1.decompositionQR(Q, R);
	  
	  // verification
	  //
	  int32 m = arg_mat1.getNumRows();
	  int32 n = arg_mat1.getNumColumns();
	  int32 min_mn = (m < n) ? m : n;
	  for (int32 j = 0; j < min_mn; j++) {
	    for (int32 i = j + 1; i < m; i++) {
	      R.setValue(i, j, (TIntegral)0.0);
	    }
	  }
	      
	  MVector<TScalar, TIntegral> tmp;
	  MVector<TScalar, TIntegral> tmp2;
	  
	  // this test applies to all matrices:
	  //   verify that Q * R == A
	  //
	  MMatrix<TScalar, TIntegral> tmp_mat;
	  tmp_mat.mult(Q, R);
	  if (!arg_mat1.almostEqual(tmp_mat)) {
	    arg_mat1.debug(L"arg_mat1");
	    Q.debug(L"Q");
	    R.debug(L"R");
	    tmp_mat.debug(L"Q * R");
	    Error::handle(name(), L"decompositionQR: Q * R != arg_mat1",
			  Error::TEST,  __FILE__, __LINE__);
	  }
	}

       	// test LU decomposition
	//
	if ((typeid(float64) == typeid(TIntegral)) ||
	    (typeid(float32) == typeid(TIntegral))) {
	  if (arg_mat1.isSquare() && !arg_mat1.isSingular(MMatrix<TScalar, TIntegral>::THRESH_SINGULAR)) {
	    
	    tmp_mat.assign(arg_mat1);
	    
	    // declare temporary matrix to hold the lower and upper
	    // triangular result matrices after decomposition
	    //
	    MMatrix<TScalar, TIntegral> lower_mat;
	    MMatrix<TScalar, TIntegral> upper_mat;
	    
            tmp_mat.decompositionLU(lower_mat, upper_mat);

	    // test the lower triangular result matrix
	    //
            res_mat.setDimensions(4, 4, false,
				  Integral::FULL);
            res_mat.assign((int32)MMAT_DECOMPLU1_RES[mat1][MMAT_NROW_LOC], 
                           (int32)MMAT_DECOMPLU1_RES[mat1][MMAT_NCOL_LOC],
                           (float64*)&MMAT_DECOMPLU1_RES[mat1][MMAT_DATA_LOC]);

            if (!res_mat.almostEqual(lower_mat)) {
              Console::put(arg1_str);
              Error::handle(name(), L"decompositionLU", Error::TEST,
                            __FILE__, __LINE__);
            }

	    // test the upper triangular result matrix
	    //	    
            res_mat.setDimensions(4, 4, false,
				  Integral::FULL);
            res_mat.assign((int32)MMAT_DECOMPLU2_RES[mat1][MMAT_NROW_LOC], 
                           (int32)MMAT_DECOMPLU2_RES[mat1][MMAT_NCOL_LOC],
                           (float64*)&MMAT_DECOMPLU2_RES[mat1][MMAT_DATA_LOC]);

            if (!res_mat.almostEqual(upper_mat)) {
	      res_mat.debug(L"res_mat");
	      upper_mat.debug(L"upper_mat");
              Console::put(arg1_str);
              Error::handle(name(), L"decompositionLU", Error::TEST,
                            __FILE__, __LINE__);
            }
          }
        }
	
	// test Cholesky decompostion
	//
	if ((typeid(float64) == typeid(TIntegral)) ||
	    (typeid(float32) == typeid(TIntegral))) {

	  if (arg_mat1.isSquare() &&
	      !arg_mat1.isSingular(MMatrix<TScalar,TIntegral>::THRESH_SINGULAR)
	      && (arg_mat1.getType() == Integral::SYMMETRIC)) {
	    
	    tmp_mat.assign(arg_mat1);
	    
	    // declare temporary matrix to hold the lower and upper
	    // triangular result matrices after decomposition
	    //
	    MMatrix<TScalar, TIntegral> lower_mat;

            tmp_mat.decompositionCholesky(lower_mat);

	    // test the lower triangular result matrix
	    //	    	    
            res_mat.setDimensions(4, 4, false,
				  Integral::FULL);
            res_mat.assign((int32)MMAT_DECOMPCL1_RES[mat1][MMAT_NROW_LOC],
                           (int32)MMAT_DECOMPCL1_RES[mat1][MMAT_NCOL_LOC],
                           (float64*)&MMAT_DECOMPCL1_RES[mat1][MMAT_DATA_LOC]);
            if (!res_mat.almostEqual(lower_mat)) {
              Console::put(arg1_str);
              Error::handle(name(), L"decompositionCholesky", Error::TEST,
                            __FILE__, __LINE__);
            }

	    // test choleskySolve
	    //
	    // create a temporary data vector of the appropriate size
	    //
	    MVector<TScalar, TIntegral> b(4);
	    MVector<TScalar, TIntegral> x;
	    b.rand();

	    // solve the set of equations
	    //
	    lower_mat.choleskySolve(x, lower_mat, b);

	    // verify that x solves the set
	    //
	    MVector<TScalar, TIntegral> b_new;

	    tmp_mat.multv(b_new, x);

	    if (!b_new.almostEqual(b)) {
	      arg_mat1.debug(L"arg_mat1");
	      lower_mat.debug(L"lower_mat");
	      x.debug(L"x");
	      b.debug(L"b");
	      b_new.debug(L"b_new");
	      Error::handle(name(), L"choleskySolve failed",
			    Error::ARG, __FILE__, __LINE__);
	    }
	  }
	}

	// test eigen - as we test 8 matrices of different types
	// (square, non-square, singular, non-singular), we don't want
	// the diagnose method to return test error for obvious cases
        //
	if ((typeid(float64) == typeid(TIntegral)) ||
	    (typeid(float32) == typeid(TIntegral)) ||
	    (typeid(int32) == typeid(TIntegral)) ||
	    (typeid(int16) == typeid(TIntegral)) ||
	    (typeid(int64) == typeid(TIntegral))) {

	  if ((arg_mat1.isSquare()) && !arg_mat1.isSingular(MMatrix<TScalar, TIntegral>::THRESH_SINGULAR)) {
	    
	    tmp_mat.assign(arg_mat1);
	    
	    // declare temporary vector to hold the eigen values and
	    // matrix to hold the corresponding eigen vectors - the
	    // rows of the matrix contain the eigen vectors
	    //
	    MVector<TScalar, TIntegral> eigen_values;
	    MMatrix<TScalar, TIntegral> eigen_vectors;

            tmp_mat.eigen(eigen_values, eigen_vectors);
	    
	    // test eigen values
	    //
	    TVector vec_res;
	    vec_res.assign((int32)MMAT_EIGENVAL_RES[mat1][0],
			   (float64*)&MMAT_EIGENVAL_RES[mat1][1]);
#ifdef ISIP_TEMPLATE_complex
	    TVector tmp;
	    tmp.assign((int32)MMAT_EIGENVAL_RES[mat1][0],
		       (float64*)&MMAT_EIGENVAL_RES[mat1][1 + MMAT_NUM_ROWS]);
	    tmp.mult(TIntegral(0, 1));
	    vec_res.add(tmp);
#endif	    
						   
	    // for float32 or float64 test the values. it is difficult to
	    // predict exactly what the integer values will be, but at
	    // least they run the code to find linker errors and such.
	    //
	    if ((typeid(float64) == typeid(TIntegral)) ||
		(typeid(float32) == typeid(TIntegral))) {
	      
	      if (!vec_res.almostEqual(eigen_values)) {
		Console::put(arg1_str);
		vec_res.debug(L"expected");
		eigen_values.debug(L"output");
		Error::handle(name(), L"eigen", Error::TEST,
			      __FILE__, __LINE__);
	      }
	    }

	    // test eigen vectors
	    //
	    res_mat.setDimensions(4, 4, false, Integral::FULL);
	    res_mat.assign((int32)MMAT_EIGENVEC_RES[mat1][MMAT_NROW_LOC], 
			   (int32)MMAT_EIGENVEC_RES[mat1][MMAT_NCOL_LOC],
			   (float64*)&MMAT_EIGENVEC_RES[mat1][MMAT_DATA_LOC]);

	    TVector vec_row;
	    TVector vec_res1;
	    for (int32 i = 0; i < 4; i++) {
	      res_mat.getRow(vec_res, i);
	      vec_res1.mult(vec_res, (TIntegral)(-1));
	      eigen_vectors.getRow(vec_row, i);

	      // for float32 or float64 test the values. it is difficult to
	      // predict exactly what the integer values will be, but at
	      // least they run the code to find linker errors and such.
	      //
	      if ((typeid(float64) == typeid(TIntegral)) ||
		  (typeid(float32) == typeid(TIntegral))) {
		if ((!vec_res.almostEqual(vec_row)) &&
		    (!vec_res1.almostEqual(vec_row))) {
		  Console::put(arg1_str);
		  vec_res.debug(L"vec_res");
		  vec_res1.debug(L"vec_res1");
		  vec_row.debug(L"vec_row");
		  Error::handle(name(), L"eigen", Error::TEST,
				__FILE__, __LINE__);
		}
	      }
	    }
	  }
	} 

        // test concatByRow
        //
	tmp_mat.assign(arg_mat1);
	tmp_mat.concatByRow(arg_mat1);
#ifndef ISIP_TEMPLATE_complex
	res_mat.assign((int32)MMAT_CON_ROW_MAT_RES[mat1][MMAT_NROW_LOC], 
		       (int32)MMAT_CON_ROW_MAT_RES[mat1][MMAT_NCOL_LOC], 
		       (float64*)&MMAT_CON_ROW_MAT_RES[mat1][MMAT_DATA_LOC]);
#else
	res_mat.assignComplexDiagnose((int32)MMAT_CON_ROW_MAT_RES[mat1][MMAT_NROW_LOC], 
		       (int32)MMAT_CON_ROW_MAT_RES[mat1][MMAT_NCOL_LOC], 
		       (float64*)&MMAT_CON_ROW_MAT_RES[mat1][MMAT_DATA_LOC]);
#endif

	if (!res_mat.almostEqual(tmp_mat)) {
	  Console::put(arg1_str);
	  arg_mat1.debug(L"arg1");
	  res_mat.debug(L"res_mat");
	  tmp_mat.debug(L"tmp_mat");
	  Error::handle(name(), L"concatByRow", Error::TEST, 
			__FILE__, __LINE__);
	}

	// test concatByColumn
	//
	tmp_mat.assign(arg_mat1);
	tmp_mat.concatByColumn(arg_mat1);
#ifndef ISIP_TEMPLATE_complex
	res_mat.assign((int32)MMAT_CON_COL_MAT_RES[mat1][MMAT_NROW_LOC], 
		       (int32)MMAT_CON_COL_MAT_RES[mat1][MMAT_NCOL_LOC], 
		       (float64*)&MMAT_CON_COL_MAT_RES[mat1][MMAT_DATA_LOC]);
#else
	res_mat.assignComplexDiagnose((int32)MMAT_CON_COL_MAT_RES[mat1][MMAT_NROW_LOC], 
		       (int32)MMAT_CON_COL_MAT_RES[mat1][MMAT_NCOL_LOC], 
		       (float64*)&MMAT_CON_COL_MAT_RES[mat1][MMAT_DATA_LOC]);
#endif
	if (!res_mat.almostEqual(tmp_mat)) {
	  Console::put(arg1_str);
	  Error::handle(name(), L"concatByColumn", Error::TEST, 
			__FILE__, __LINE__);
	}


	// test reorderRows
	//
	tmp_mat.assign(arg_mat1);
	MVector<Long, int32> index_vec;
	index_vec.assign((int32)MMAT_NUM_ROWS, (int32*)MMAT_INDEX_VECTOR);
	if (((mat1 % MMAT_NUM_MATS_REAL) != 6) &&
	    ((mat1 % MMAT_NUM_MATS_REAL) != 7)) {
	  tmp_mat.reorderRows(tmp_mat, index_vec);
#ifndef ISIP_TEMPLATE_complex
	  res_mat.assign((int32)MMAT_REORDER_ROWS_RES[mat1][MMAT_NROW_LOC], 
			 (int32)MMAT_REORDER_ROWS_RES[mat1][MMAT_NCOL_LOC], 
			 (float64*)&MMAT_REORDER_ROWS_RES[mat1][MMAT_DATA_LOC]);
#else
	  res_mat.assignComplexDiagnose((int32)MMAT_REORDER_ROWS_RES[mat1][MMAT_NROW_LOC], 
			 (int32)MMAT_REORDER_ROWS_RES[mat1][MMAT_NCOL_LOC], 
			 (float64*)&MMAT_REORDER_ROWS_RES[mat1][MMAT_DATA_LOC]);
#endif	  
	  if (!res_mat.almostEqual(tmp_mat)) {
	    Console::put(arg1_str);
	    res_mat.debug(L"res_mat");
	    tmp_mat.debug(L"tmp_mat");
	    Error::handle(name(), L"reorderRows", Error::TEST, 
			  __FILE__, __LINE__);
	  }
        }

	// test reorderColumns
	//
	tmp_mat.assign(arg_mat1);
	tmp_mat.transpose();
	index_vec.assign((int32)MMAT_NUM_ROWS, (int32*)MMAT_INDEX_VECTOR);
	if (((mat1 % MMAT_NUM_MATS_REAL) != 6) &&
	    ((mat1 % MMAT_NUM_MATS_REAL) != 7)) {
	  tmp_mat.reorderColumns(tmp_mat, index_vec);
#ifndef ISIP_TEMPLATE_complex
	  res_mat.assign((int32)MMAT_REORDER_ROWS_RES[mat1][MMAT_NROW_LOC], 
			 (int32)MMAT_REORDER_ROWS_RES[mat1][MMAT_NCOL_LOC], 
			 (float64*)&MMAT_REORDER_ROWS_RES[mat1][MMAT_DATA_LOC]);
#else
	  res_mat.assignComplexDiagnose((int32)MMAT_REORDER_ROWS_RES[mat1][MMAT_NROW_LOC], 
			 (int32)MMAT_REORDER_ROWS_RES[mat1][MMAT_NCOL_LOC], 
			 (float64*)&MMAT_REORDER_ROWS_RES[mat1][MMAT_DATA_LOC]);
#endif
	  res_mat.transpose();
	  if (!res_mat.almostEqual(tmp_mat)) {
	    Console::put(arg1_str);
	    res_mat.debug(L"res_mat");
	    tmp_mat.debug(L"tmp_mat");
	    Error::handle(name(), L"reorderColumns", Error::TEST, 
			  __FILE__, __LINE__);
	  }
        }

	// test getMinor
	//
	for (int32 test_arg = 0; test_arg < MMAT_GTMR_ARG_SIZE / 2;
	     test_arg++) {
	  int32 mat_index = mat1 * 3 + test_arg;
	  
#ifndef ISIP_TEMPLATE_complex
	  res_mat.assign((int32)MMAT_GETMINOR_RES[mat_index][MMAT_NROW_LOC], 
			 (int32)MMAT_GETMINOR_RES[mat_index][MMAT_NCOL_LOC], 
			 (float64*)&MMAT_GETMINOR_RES[mat_index]
			 [MMAT_DATA_LOC]);
#else
	  res_mat.assignComplexDiagnose((int32)MMAT_GETMINOR_RES[mat_index][MMAT_NROW_LOC], 
			 (int32)MMAT_GETMINOR_RES[mat_index][MMAT_NCOL_LOC], 
			 (float64*)&MMAT_GETMINOR_RES[mat_index]
			 [MMAT_DATA_LOC]);
#endif
	  
	  arg_mat1.getMinor(tmp_mat, MMAT_GETMINOR_ARG[test_arg * 2],
			   MMAT_GETMINOR_ARG[test_arg * 2 + 1]);
	  if (!res_mat.almostEqual(tmp_mat)) {
	    tmp_mat.debug(L"tmp");
	    res_mat.debug(L"res");
	    Console::put(arg1_str);	    
	    Error::handle(name(), L"getMinor", Error::TEST, 
			  __FILE__, __LINE__);
	  }
	}
        
	// test swapRows
	//
	if (arg_mat1.getType() == Integral::FULL ||
	    arg_mat1.getType() == Integral::SPARSE) {
	  for (int32 test_arg = 0; test_arg < MMAT_SWRW_ARG_SIZE / 2;
	       test_arg++) {
#ifndef ISIP_TEMPLATE_complex
	    res_mat.assign((int32)MMAT_SWAPROWS_RES[mat1][MMAT_NROW_LOC], 
			   (int32)MMAT_SWAPROWS_RES[mat1][MMAT_NCOL_LOC], 
			   (float64*)&MMAT_SWAPROWS_RES[mat1][MMAT_DATA_LOC]);
#else
	    res_mat.assignComplexDiagnose((int32)MMAT_SWAPROWS_RES[mat1][MMAT_NROW_LOC], 
			   (int32)MMAT_SWAPROWS_RES[mat1][MMAT_NCOL_LOC], 
			   (float64*)&MMAT_SWAPROWS_RES[mat1][MMAT_DATA_LOC]);
#endif
	    tmp_mat.swapRows(arg_mat1, MMAT_SWAPROWS_ARG[test_arg * 2],
			     MMAT_SWAPROWS_ARG[test_arg * 2 + 1]);
	    if (!res_mat.almostEqual(tmp_mat)) {
	      Console::put(arg1_str);	    
	      Error::handle(name(), L"swapRows", Error::TEST, 
			    __FILE__, __LINE__);
	    }
	    
	    tmp_mat.assign(arg_mat1);
	    tmp_mat.swapRows(MMAT_SWAPROWS_ARG[test_arg * 2],
			     MMAT_SWAPROWS_ARG[test_arg * 2 + 1]);
	    if (!res_mat.almostEqual(tmp_mat)) {
	      Console::put(arg1_str);	    
	      Error::handle(name(), L"swapRows", Error::TEST, 
			    __FILE__, __LINE__);
	    }
	  }
	
	  // test swapColumns
	  //
	  for (int32 test_arg = 0; test_arg < MMAT_SWCL_ARG_SIZE / 2;
	       test_arg++) {
#ifndef ISIP_TEMPLATE_complex
	    res_mat.assign((int32)MMAT_SWAPCOLUMNS_RES[mat1][MMAT_NROW_LOC], 
			   (int32)MMAT_SWAPCOLUMNS_RES[mat1][MMAT_NCOL_LOC], 
			   (float64*)&MMAT_SWAPCOLUMNS_RES[mat1][MMAT_DATA_LOC]);
#else
	    res_mat.assignComplexDiagnose((int32)MMAT_SWAPCOLUMNS_RES[mat1][MMAT_NROW_LOC], 
			   (int32)MMAT_SWAPCOLUMNS_RES[mat1][MMAT_NCOL_LOC], 
			   (float64*)&MMAT_SWAPCOLUMNS_RES[mat1][MMAT_DATA_LOC]);
#endif	    
	    tmp_mat.swapColumns(arg_mat1, MMAT_SWAPCOLUMNS_ARG[test_arg * 2],
				MMAT_SWAPCOLUMNS_ARG[test_arg * 2 + 1]);
	    
	    if (!res_mat.almostEqual(tmp_mat)) {
	      Console::put(arg1_str);	    
	      Error::handle(name(), L"swapColumns", Error::TEST, 
			    __FILE__, __LINE__);
	    }
	    
	    tmp_mat.assign(arg_mat1);
	    tmp_mat.swapColumns(MMAT_SWAPCOLUMNS_ARG[test_arg * 2],
				MMAT_SWAPCOLUMNS_ARG[test_arg * 2 + 1]);
	    if (!res_mat.almostEqual(tmp_mat)) {
	      Console::put(arg1_str);	    
	      Error::handle(name(), L"swapColumns", Error::TEST, 
			    __FILE__, __LINE__);
	    }
	  }
	}

	// test the findRow and setRow methods
	//	
	if ((mat1 == Integral::FULL) && (mat1 % MMAT_NUM_MATS_REAL < 5)) {

	  // declare temporary vectors
	  //
	  TVector in_vec;
	  TVector out_vec;
	  TVector vec_res;

          in_vec.assign((int32)MMAT_NUM_COLS, (float64*)MMAT_MULTV_ARG_REAL);
          vec_res.assign(in_vec);
	  tmp_mat.assign(arg_mat1);

	  // test set row methods
	  //
          tmp_mat.setRow(2, in_vec);
	  tmp_mat.getRow(out_vec, 2);
          if (!out_vec.almostEqual(in_vec)) {
	    Console::put(arg1_str);
            Error::handle(name(), L"getRow", Error::TEST, 
                          __FILE__, __LINE__);
          }

	  // test findRow
	  //
          if (tmp_mat.findRow(in_vec) != 2) {
	    Console::put(arg1_str);
            Error::handle(name(), L"findRow", Error::TEST, 
                          __FILE__, __LINE__);
          }
          
          // test set value method, get value needn't be tested since it's
          // called inside the assign methods
          //
          tmp_mat.clear(Integral::RETAIN);
	  	  
          for (int32 i = 0; i < (int32)(MMAT_ARG_MATRICES[mat1][MMAT_NROW_LOC]);
	       i++) {
            for (int32 j = 0; j < (int32)MMAT_ARG_MATRICES[mat1][MMAT_NCOL_LOC];
                 j++) {
              tmp_mat.setValue(i, j, (TIntegral)MMAT_ARG_MATRICES[mat1][MMAT_DATA_LOC + i * (int32)MMAT_ARG_MATRICES[mat1][MMAT_NCOL_LOC] + j]);
            }
          }
	}

	// test copy - we loop over the different types of matrices
	// here so that we can test all the cases, such as, FULL.copy(DIAG),
	// SYMM.copy(FULL) etc.
	//
	for (int32 type2 = Integral::FULL; type2 <= Integral::SPARSE; type2++) {
	  
	  if (arg_mat1.isTypePossible((Integral::MTYPE)type2)) {
	    tmp_mat.setDimensions(tmp_mat.nrows_d, tmp_mat.ncols_d,
				  false, (Integral::MTYPE)type2);
	    tmp_mat.copy(arg_mat1);
	    if (!tmp_mat.almostEqual(arg_mat1)) {
	      Console::put(arg1_str);
	      Error::handle(name(), L"copy", Error::TEST, 
			    __FILE__, __LINE__);
	    }
	  }
	}

	// test makeIdentity
	//
	int32 dim = 4;
	tmp_mat.makeIdentity(dim, (Integral::MTYPE)type1);
	res_mat.assign((int32)MMAT_IDENTITY_MATRICES[MMAT_NROW_LOC], 
		       (int32)MMAT_IDENTITY_MATRICES[MMAT_NCOL_LOC], 
		       (float64*)&MMAT_IDENTITY_MATRICES[MMAT_DATA_LOC]);
    
	if (!res_mat.almostEqual(tmp_mat)) {
	  Console::put(arg1_str);
	  tmp_mat.debug(L"makeIdentity");
	  Error::handle(name(), L"makeIdentity", Error::TEST,
			__FILE__, __LINE__);
	}

	// test makeDiagonal with vector argument
	//
	TVector arg_vec(MMAT_NUM_ROWS);
	arg_vec.assign((int32)MMAT_NUM_ROWS, (float64*)MMAT_MAKEDIAG_VEC);
	res_mat.assign((int32)MMAT_MAKEDIAG_RES0[MMAT_NROW_LOC], 
		       (int32)MMAT_MAKEDIAG_RES0[MMAT_NCOL_LOC], 
		       (float64*)&MMAT_MAKEDIAG_RES0[MMAT_DATA_LOC]);

	tmp_mat.makeDiagonal(arg_vec, (Integral::MTYPE)type1);
	if (!res_mat.almostEqual(tmp_mat)) {
	  Console::put(arg1_str);
	  tmp_mat.debug(L"makeDiagonal");
	  Error::handle(name(), L"makeDiagonal", Error::TEST,
			__FILE__, __LINE__);
	}
	
	// test makeDiagonal with scalar argument
	//
	dim = 4;
	res_mat.assign((int32)MMAT_MAKEDIAG_RES1[MMAT_NROW_LOC], 
		       (int32)MMAT_MAKEDIAG_RES1[MMAT_NCOL_LOC], 
		       (float64*)&MMAT_MAKEDIAG_RES1[MMAT_DATA_LOC]);
	
	tmp_mat.makeDiagonal((TIntegral)MMAT_MAKEDIAG_SCAL, dim, (Integral::MTYPE)type1);
	if (!res_mat.almostEqual(tmp_mat)) {
	  Console::put(arg1_str);
	  tmp_mat.debug(L"makeDiagonal");
	  Error::handle(name(), L"makeDiagonal", Error::TEST,
			__FILE__, __LINE__);
	}

	// test setDiagonal, setLower, setUpper
	//
	for (int32 type2 = Integral::FULL; type2 <= Integral::SPARSE; type2++) {
	  
	  // test setDiagonal/getDiagonal:
	  //
	  if (arg_mat1.isSquare()) {
	    tmp_mat.setDimensions(arg_mat1, false, (Integral::MTYPE)type2);
	    res_mat.setDimensions(arg_mat1, false, (Integral::MTYPE)type1);
	    tmp_mat.clear(Integral::RETAIN);

	    tmp_mat.setDiagonal(arg_mat1);
	    arg_mat1.getDiagonal(arg_vec);
	    res_mat.makeDiagonal(arg_vec, (Integral::MTYPE)type1);
	    if (!res_mat.almostEqual(tmp_mat)) {
	      Console::put(arg1_str);
	      tmp_mat.debug(L"setDiagonal");
	      res_mat.debug(L"getDiagonal");
	      Error::handle(name(), L"setDiagonal", Error::TEST,
			    __FILE__, __LINE__);
	    }
	  }

	  // test setLower/getLower:
	  //
	  if ((arg_mat1.isSquare()) &&
	      ((type2 == Integral::FULL) ||
	       (type2 == Integral::SPARSE) ||
	       (type2 == Integral::LOWER_TRIANGULAR) ||
	       ((type2 == Integral::DIAGONAL) && (arg_mat1.isDiagonal())) ||
	       ((type2 == Integral::UPPER_TRIANGULAR) &&
		(arg_mat1.isDiagonal())) ||
	       ((type2 == Integral::SYMMETRIC) && (arg_mat1.isDiagonal())))) {
	    tmp_mat.setDimensions(arg_mat1, false, (Integral::MTYPE)type2);
	    res_mat.setDimensions(arg_mat1, false, (Integral::MTYPE)type2);
	    tmp_mat.clear(Integral::RETAIN);

	    tmp_mat.setLower(arg_mat1);
	    arg_mat1.getLower(res_mat);
	    if (!res_mat.almostEqual(tmp_mat)) {
	      Console::put(arg1_str);
	      tmp_mat.debug(L"setLower");
	      res_mat.debug(L"getLower");
	      Error::handle(name(), L"setLower", Error::TEST,
			    __FILE__, __LINE__);
	    }	  
	  }

	  // test setUpper/getUpper:
	  //
	  if ((arg_mat1.isSquare()) &&
	      ((type2 == Integral::FULL) ||
	       (type2 == Integral::SPARSE) ||
	       (type2 == Integral::UPPER_TRIANGULAR) ||
	       ((type2 == Integral::DIAGONAL) && (arg_mat1.isDiagonal())) ||
	       ((type2 == Integral::LOWER_TRIANGULAR) &&
		(arg_mat1.isDiagonal())) ||
	       ((type2 == Integral::SYMMETRIC) && (arg_mat1.isDiagonal())))) {
	    tmp_mat.setDimensions(arg_mat1, false, (Integral::MTYPE)type2);
	    res_mat.setDimensions(arg_mat1, false, (Integral::MTYPE)type2);
	    tmp_mat.clear(Integral::RETAIN);
	    tmp_mat.setUpper(arg_mat1);
	    arg_mat1.getUpper(res_mat);
	    if (!res_mat.almostEqual(tmp_mat)) {
	      Console::put(arg1_str);
	      tmp_mat.debug(L"setUpper");
	      res_mat.debug(L"getUpper");
	      Error::handle(name(), L"setUpper", Error::TEST,
			    __FILE__, __LINE__);
	    }	    
	  }
	}
	
	// test setDiagonal with vector argument
	//
	if (arg_mat1.isSquare()) {
	  TVector res_vec(4);
	  res_vec.assign((int32)MMAT_NUM_ROWS, (float64*)MMAT_MAKEDIAG_VEC);
	  tmp_mat.assign(arg_mat1);
	  tmp_mat.setDiagonal(res_vec);
	  tmp_mat.getDiagonal(arg_vec);  
	  if (!res_vec.almostEqual(arg_vec)) {
	    Console::put(arg1_str);
	    tmp_mat.debug(L"setDiagonal");
	    Error::handle(name(), L"setDiagonal", Error::TEST,
			  __FILE__, __LINE__);
	  }
	}
	
	// test setDiagonal with scalar argument
	//
	if (arg_mat1.isSquare()) {
	  TVector res_vec(4);
	  res_vec.assign((TIntegral)7);
	  tmp_mat.assign(arg_mat1);
	  tmp_mat.setDiagonal((TIntegral)7);
	  tmp_mat.getDiagonal(arg_vec);	  
	  if (!res_vec.almostEqual(arg_vec)) {
	    Console::put(arg1_str);
	    tmp_mat.debug(L"setDiagonal");
	    Error::handle(name(), L"setDiagonal", Error::TEST,
			  __FILE__, __LINE__);
	  }
	}

	// test random methods
	//
	TIntegral min, max;
	float64 mean, stddev;
	float64 expected_mean, expected_stddev, expected_min, expected_max;
	float64 err_mean;
	Double tmp_val;
	
	// create a 100 * 100 matrix for test
	//
	tmp_mat.setDimensions(100, 100, false, (Integral::MTYPE)type1);
	
	// determine the expected values of mean, max and min based on
	// the specific type, also compute the error
	//
	if (typeid(TIntegral) == typeid(byte8)) {
	  expected_min = 0;
	  expected_max = TScalar::RAND_BYTE_MAX - 1.0;
	  expected_mean = TScalar::RAND_BYTE_MAX / 2.0;
	  err_mean = tmp_val.abs(expected_mean - 126.76);
	}
	else if (typeid(TIntegral) == typeid(uint16)) {
	  expected_min = 0;
	  expected_max = TScalar::RAND_USHORT_MAX - 1.0;
	  expected_mean = TScalar::RAND_USHORT_MAX / 2.0;
	  err_mean = tmp_val.abs(expected_mean - 32578.44);
	}
	else if (typeid(TIntegral) == typeid(uint32)) {
	  expected_min = 0;
	  expected_mean = TScalar::RAND_ULONG_MAX / 2.0;
	  expected_max = TScalar::RAND_ULONG_MAX - 1.0;
	  err_mean = tmp_val.abs(expected_mean - 2135094016.00);
	}
	else if (typeid(TIntegral) == typeid(uint64)) {
	  expected_min = 0;
	  expected_max = TScalar::RAND_ULLONG_MAX - 1.0;
	  expected_mean = TScalar::RAND_ULLONG_MAX / 2.0;
	  err_mean = tmp_val.abs(expected_mean - 9170158972605300736.00);
	}
	else if (typeid(TIntegral) == typeid(int16)) {
	  expected_min = -TScalar::RAND_SHORT_MAX;
	  expected_max = TScalar::RAND_SHORT_MAX - 1.0;
	  expected_mean = 0;
	  err_mean = tmp_val.abs(expected_mean - 500);
	}
	else if (typeid(TIntegral) == typeid(int32)) {
	  expected_min = -TScalar::RAND_LONG_MAX;
	  expected_max = TScalar::RAND_LONG_MAX - 1.0;
	  expected_mean = 0;
	  err_mean = tmp_val.abs(expected_mean - 12389639.00);
	}
	else if (typeid(TIntegral) == typeid(int64)) {
	  expected_min = -TScalar::RAND_LLONG_MAX;
	  expected_max = TScalar::RAND_LLONG_MAX - 1.0;
	  expected_mean = 0;
	  err_mean = tmp_val.abs(expected_mean - 53213094314246144.00);
	}
	else if ((typeid(TIntegral) == typeid(float32)) ||
		 (typeid(TIntegral) == typeid(float64))) {
	  expected_min = 0;
	  expected_max = 1.0;
	  expected_mean = 0.5;
	  err_mean = tmp_val.abs(expected_mean - 0.52);
	}
	else if ((typeid(TIntegral) == typeid(complexfloat)) ||
		 (typeid(TIntegral) == typeid(complexdouble))) {
	  expected_min = 0;
	  expected_max = 1.0;
	  expected_mean = 0.5;
	  err_mean = tmp_val.abs(expected_mean - 0.52);
	}
	else if (typeid(TIntegral) == typeid(complexlong)) {
	  expected_min = -TScalar::RAND_LONG_MAX;
	  expected_max = TScalar::RAND_LONG_MAX - 1.0;
	  expected_mean = 0;
	  err_mean = tmp_val.abs(expected_mean - 30000000.00);
	}
	else {
	  Console::put(arg1_str);
	  return Error::handle(name(), L"rand", Error::TEST,
			       __FILE__, __LINE__);
	}

	// set the seed
	//
	Random::GLOBAL_UNIFORM.seed(27);
	
	// generate elements of matrix with a uniformly distributed random
	// value
	//
	tmp_mat.rand();
	
	// compute mean, minimum, maximum values
	//
	mean = 0;
	for (int32 index = 0, nelms = tmp_mat.m_d.length();
	     index < nelms; index++) {
#ifdef ISIP_TEMPLATE_complex
	  mean += tmp_mat.m_d(index).real();
#else
	  mean += tmp_mat.m_d(index);
#endif
	}
	mean /= tmp_mat.m_d.length();
	min = tmp_mat.m_d.min();
	max = tmp_mat.m_d.max();

	// check if the computed values are in the proper range
	//  here we don't check the diagonal or sparse matrix because it
	//  does not have not enough elements for test
	//
	if ((tmp_val.abs(mean - expected_mean) > err_mean) &&
	     ((type1 != (int32)Integral::DIAGONAL) &&
	      (type1 != (int32)Integral::SPARSE))) {
	  Console::put(arg1_str);
	  return Error::handle(name(), L"rand", Error::TEST,
			       __FILE__, __LINE__);
	}

#ifdef ISIP_TEMPLATE_complex
	if (min < ((TIntegral)expected_min).real()) {
#else	  
	if ((float64)min < (float64)expected_min) {
#endif	  
	  Console::put(arg1_str);
	  return Error::handle(name(), L"rand", Error::TEST,
			       __FILE__, __LINE__);
	}

#ifdef ISIP_TEMPLATE_complex
	if (max > ((TIntegral)expected_max).real()) {
#else	  
	if ((float64)max > (float64)expected_max) {
#endif	  
	  Console::put(arg1_str);
	  return Error::handle(name(), L"rand", Error::TEST,
	  			       __FILE__, __LINE__);
	}

	// set the seed
	//
	Random::GLOBAL_UNIFORM.seed(27);

	// generate elements of matrix with a uniformly distributed random
	// value between expected minimum and maximum values
	//
	expected_min = 10;
	expected_max = 100;
	expected_mean = (expected_min + expected_max) / 2;
	tmp_mat.rand((TIntegral)expected_min, (TIntegral)expected_max);
	
	// compute mean, minimum, maximum values
	//
	mean = 0;
	for (int32 index = 0, nelms = tmp_mat.m_d.length();
	     index < nelms; index++) {
#ifdef ISIP_TEMPLATE_complex
	  mean += (float64)((tmp_mat.m_d(index)).real());
#else
	  mean += tmp_mat.m_d(index);
#endif
	}
	mean /= tmp_mat.m_d.length();
	min = tmp_mat.m_d.min();
	max = tmp_mat.m_d.max();

	// check if the computed values are in the proper range
	//
	if (!Integral::almostEqual(mean, expected_mean, 10)) {
	  Console::put(arg1_str);
	  return Error::handle(name(), L"rand", Error::TEST,
			       __FILE__, __LINE__);
	}

	if (min < (TIntegral)expected_min) {
	  Console::put(arg1_str);
	  return Error::handle(name(), L"rand", Error::TEST,
			       __FILE__, __LINE__);
	}
	
	if (max > (TIntegral)expected_max) {
	  Console::put(arg1_str);
	  return Error::handle(name(), L"rand", Error::TEST,
			       __FILE__, __LINE__);
	}	

	// test grand
	//  determine the expected values based on the specific type:
	//  choose a mean and stdev that works for all datatypes
	//
	expected_mean = 128.0;
	expected_stddev = 10.0;
	
	// set the seed
	//
	Random::GLOBAL_GAUSSIAN.seed(27);
	
	// generate elements of matrix with a uniformly distributed gaussian
	// random value
	//
	tmp_mat.grand((TIntegral)expected_mean, (TIntegral)expected_stddev);
	
	// compute the mean and standart deviation
	//
	mean = 0;
	stddev = 0;
	for (int32 index = 0, nelms = tmp_mat.m_d.length();
	     index < nelms; index++) {

	  // update the mean / stddev
	  //
#ifdef ISIP_TEMPLATE_complex
	  float64 value = tmp_mat.m_d(index).real();
#else	  
	  float64 value = tmp_mat.m_d(index);
#endif	  
	  mean += value;
	  stddev += value * value;
	}

	// normalize the mean and stddev:
	//  note stddev = sqrt(E(x^2) - (Ex)^2)
	//
	mean /= tmp_mat.m_d.length();
	stddev = sqrt(stddev / tmp_mat.m_d.length() - mean * mean);
	
	// check if the computed values are in the proper range
	//
	if (!Integral::almostEqual(mean, expected_mean, 10.0)) {
	  Console::put(arg1_str);
	  printf("mean = %f", mean);
	  printf("exp_mean = %f", expected_mean);	  
	  return Error::handle(name(), L"grand", Error::TEST,
			       __FILE__, __LINE__);
	}
	
	if (!Integral::almostEqual(stddev, expected_stddev, 10.0)) {
	  Console::put(arg1_str);
	  printf("std = %f\n", stddev);
	  printf("exp_std = %f\n", expected_stddev);	  	  
	  return Error::handle(name(), L"grand", Error::TEST,
			       __FILE__, __LINE__);
	}
      }
    }
  }

  // reset indentation
  //
  if (level_a > Integral::NONE) {
    Console::decreaseIndention();
  }

  // exit gracefully
  //
  return true;
}

// method: diagnose4
//
// arguments:
//  Integral::DEBUG level: (input) debug level for diagnostics
//
// return: a bool8 value indicating status
//
// this method tests (matrix, matrix)->matrix methods for real matrix -
// thus this method tests output.operation(matrix1, matrix2), where
// operations are addition, subtraction and multiplication. this method
// also tests methods like matrix equality
//
template<class TScalar, class TIntegral>
bool8 MMatrixMethods::diagnose4(Integral::DEBUG level_a) {

  // define TVector
  //
  typedef MVector<TScalar, TIntegral> TVector;

  // set indentation
  //
  if (level_a > Integral::NONE) {
    Console::put(L"testing class-specific public methods: matrix, matrix --> matrix...\n");
    Console::increaseIndention();
  }

  // declare an array of matrix to hold all the 8 matrices used for testing
  //      
  MMatrix<TScalar, TIntegral> arg_mats[MMAT_NUM_MATS_TEST];

  // load up the argument matrices
  //
  for (int32 i = 0; i < MMAT_NUM_MATS_REAL; i++) {
    
    // assign the arguments
    //
#ifndef ISIP_TEMPLATE_complex
    arg_mats[i].assign((int32)MMAT_ARG_MATRICES[i][MMAT_NROW_LOC], 
                       (int32)MMAT_ARG_MATRICES[i][MMAT_NCOL_LOC], 
                       (float64*)&MMAT_ARG_MATRICES[i][MMAT_DATA_LOC]);
#else
    arg_mats[i].assignComplexDiagnose((int32)MMAT_ARG_MATRICES[i][MMAT_NROW_LOC], 
                       (int32)MMAT_ARG_MATRICES[i][MMAT_NCOL_LOC], 
                       (float64*)&MMAT_ARG_MATRICES[i][MMAT_DATA_LOC]);
#endif    
  }

  // declare temporary matrices to be used for testing
  //
  MMatrix<TScalar, TIntegral> res_mat;
  MMatrix<TScalar, TIntegral> tmp_mat;
  MMatrix<TScalar, TIntegral> tmp_mat2;
  MMatrix<TScalar, TIntegral> arg_mat1;
  
  // loop through the different matrices (first operand)
  //
  for (int32 mat1 = 0; mat1 < MMAT_NUM_MATS_REAL; mat1++) {

    // declare local variables
    //
    Char mat1c;
    mat1c.assign((byte8)((int)'A' + mat1));

    // loop through the different types of matrices
    //
    for (int32 type1 = Integral::FULL; type1 <= Integral::FULL; type1++) {

      // check if the type conversion is possible
      //
      if (arg_mats[mat1].isTypePossible((Integral::MTYPE)type1)) {

	// create a diagnostic string to indicate the matrix and its type
	//		
	String type1_str(MMatrix<TScalar, TIntegral>::TYPE_MAP(type1));
	String arg1_str(L"testing mat1: ");
	arg1_str.concat(mat1c);
	arg1_str.concat(L", ");
	arg1_str.concat(type1_str);

	// assign the first matrix operand and change the type - type is
	// changed here so that this particular matrix can be tested for
	// every type it can have
	//
        arg_mat1.assign(arg_mats[mat1]);
        arg_mat1.changeType((Integral::MTYPE)type1);

        // loop through the different matrices (second operand)
        //
        for (int32 mat2 = 0; mat2 < MMAT_NUM_MATS_REAL; mat2++) {

	  // declare local variables
	  //
          Char mat2c;
          mat2c.assign((byte8)((int)'A' + mat2));
          
          // loop through the different types of matrices
          //
          for (int32 type2 = Integral::FULL; type2 <= Integral::SPARSE;
	       type2++) {

	    // check if type conversion is possible
	    //
            if (arg_mats[mat2].isTypePossible((Integral::MTYPE)type2)) {

	      // assign the second matrix operand and change the type - type is
	      // changed here so that this particular matrix can be tested for
	      // every type it can have
	      //	      
	      MMatrix<TScalar, TIntegral> arg_mat2;	      
              arg_mat2.assign(arg_mats[mat2]);	      
              arg_mat2.changeType((Integral::MTYPE)type2);

	      // create a diagnostic string to indicate both matrix
	      // operands and their type
	      //			      
              String type2_str(arg_mat2.TYPE_MAP(type2));
              String arg2_str;
              arg2_str.assign(L"; mat2: ");
              arg2_str.concat(mat2c);
              arg2_str.concat(L", ");
              arg2_str.concat(type2_str);
              arg2_str.insert(arg1_str, 0);

              // test matrix equality
	      //
              if ((mat1 == mat2)
                  && ((!arg_mat1.almostEqual(arg_mat2))
                      ||(!arg_mat2.almostEqual(arg_mat1)))) {
                Console::put(arg2_str);
                Error::handle(name(), L"eq", Error::TEST, __FILE__, __LINE__);
              }
              else if ((mat1 != mat2)
                       && ((arg_mat1.almostEqual(arg_mat2))
                           || (arg_mat2.almostEqual(arg_mat1)))) {
                Console::put(arg2_str);
                Error::handle(name(), L"eq", Error::TEST, __FILE__, __LINE__);
              }
	      
	      // loop over 6 different types of the matrices for output
	      //
	      for (int32 type3 = Integral::FULL; type3 <= Integral::SPARSE;
		   type3++) {
		
		// create a diagnostic string to indicate both matrix
		// operands and their type
		//			      
		String type3_str(arg_mat2.TYPE_MAP(type3));
		String arg3_str;
		arg3_str.assign(L"; output: ");
		arg3_str.concat(type3_str);
		arg3_str.insert(arg2_str, 0);
		
		// addition and subtraction require the same dimensions
		//
		if (arg_mat1.checkDimensions(arg_mat2)) {
		  
		  if (
		      // all things can be tested full or sparse
		      //
		      (type3 == Integral::FULL) || (type3 == Integral::SPARSE)

		      // or if one input is diagonal, we can test to the other
		      // for all types but symmetric
		      //
		      || ((type1 == Integral::DIAGONAL) && (type3 == type2))
		      || ((type2 == Integral::DIAGONAL) && (type3 == type1))

		      // or if both are upper and the output is upper
		      //
		      || ((type1 == Integral::UPPER_TRIANGULAR)
			  && (type1 == type2) && (type1 == type3))

		      // or if both are lower and the output is lower
		      //
		      || ((type1 == Integral::LOWER_TRIANGULAR)
			  && (type1 == type2) && (type1 == type3))) {
		      
		    tmp_mat.clear();
		    tmp_mat.changeType((Integral::MTYPE)type3);

		    // test matrix addition
		    //
		    tmp_mat.add(arg_mat1, arg_mat2);
		    res_mat.assign((int32)MMAT_ADD_MAT_RES_REAL[mat1]
				   [mat2][MMAT_NROW_LOC], 
				   (int32)MMAT_ADD_MAT_RES_REAL[mat1][mat2]
				   [MMAT_NCOL_LOC], 
				   (float64*)&MMAT_ADD_MAT_RES_REAL[mat1][mat2]
				   [MMAT_DATA_LOC]);

		    // make sure the type wasn't changed
		    //
		    if (tmp_mat.type_d != type3) {
		      Console::put(arg3_str);
		      return Error::handle(name(), L"add", Error::ARG,
					   __FILE__, __LINE__);
		    }
		    
		    if (!res_mat.almostEqual(tmp_mat)) {
		      Console::put(arg3_str);
		      tmp_mat.debug(L"xxx");
		      res_mat.debug(L"yyy");
		      Error::handle(name(), L"add", Error::TEST, 
				    __FILE__, __LINE__);
		    }

		    // test matrix subtraction:
		    //  the unsigned types are not tested here because there
		    //  will be some negative values in the result matrices
		    //
		    if ((typeid(byte8) != typeid(TIntegral)) &&
			(typeid(uint16) != typeid(TIntegral)) &&
			(typeid(uint32) != typeid(TIntegral)) &&
			(typeid(uint64) != typeid(TIntegral))) {

		      tmp_mat.changeType((Integral::MTYPE)type3);
		      tmp_mat.sub(arg_mat1, arg_mat2);
		      res_mat.assign((int32)MMAT_SUB_MAT_RES_REAL[mat1][mat2]
				     [MMAT_NROW_LOC], 
				     (int32)MMAT_SUB_MAT_RES_REAL[mat1][mat2]
				     [MMAT_NCOL_LOC], 
				     (float64*)&MMAT_SUB_MAT_RES_REAL[mat1][mat2]
				     [MMAT_DATA_LOC]);

		      // make sure the type wasn't changed
		      //
		      if (tmp_mat.type_d != type3) {
			Console::put(arg3_str);
			return Error::handle(name(), L"sub", Error::TEST,
					     __FILE__, __LINE__);
		      }
		      
		      if (!res_mat.eq(tmp_mat)) {
			Console::put(arg3_str);
			Error::handle(name(), L"sub", Error::TEST, 
				      __FILE__, __LINE__);
		      }
		    }
		  }
		}
              
		// test matrix multiplication if dimensions agree
		//
		if (arg_mat1.getNumColumns() == arg_mat2.getNumRows()) {
		  
		  if (
		      // all things can be tested full or sparse
		      //
		      (type3 == Integral::FULL) || (type3 == Integral::SPARSE)

		      // or if one input is diagonal, we can test to the other
		      // for all types but symmetric
		      //
		      || ((type1 == Integral::DIAGONAL) && (type3 == type2) &&
			  (type3 != Integral::SYMMETRIC))
		      || ((type2 == Integral::DIAGONAL) && (type3 == type1) &&
			  (type3 != Integral::SYMMETRIC))

		      // or if both are upper and the output is upper
		      //
		      || ((type1 == Integral::UPPER_TRIANGULAR)
			  && (type1 == type2) && (type1 == type3))

		      // or if both are lower and the output is lower
		      //
		      || ((type1 == Integral::LOWER_TRIANGULAR)
			  && (type1 == type2) && (type1 == type3))) {

		    tmp_mat.clear();
		    tmp_mat.changeType((Integral::MTYPE)type3);
		    tmp_mat.mult(arg_mat1, arg_mat2);
		    res_mat.assign((int32)MMAT_MULT_MAT_RES_REAL[mat1][mat2]
				   [MMAT_NROW_LOC], 
				   (int32)MMAT_MULT_MAT_RES_REAL[mat1][mat2]
				   [MMAT_NCOL_LOC], 
				   (float64*)&MMAT_MULT_MAT_RES_REAL[mat1][mat2]
				   [MMAT_DATA_LOC]);

		    if (tmp_mat.getType() != type3) {
		      Console::put(arg3_str);
		      return Error::handle(name(), L"mult", Error::TEST,
					   __FILE__, __LINE__);
		    }
		    if (!res_mat.almostEqual(tmp_mat)) {
		      Console::put(arg3_str);
		      Error::handle(name(), L"mult", Error::TEST, 
				    __FILE__, __LINE__);
		    }
		  }
		}

		// test the matrix outer product if dimensions agree
		//
		if (arg_mat1.getNumColumns() == arg_mat2.getNumRows()) {
		  
		  if (
		      // all things can be tested full or sparse
		      //
		      (type3 == Integral::FULL) || (type3 == Integral::SPARSE)

		      // or if one input is diagonal, we can test to the other
		      // for all types but symmetric
		      //
		      || ((type1 == Integral::DIAGONAL) && (type3 == type2) &&
			  (type3 != Integral::SYMMETRIC))
		      || ((type2 == Integral::DIAGONAL) && (type3 == type1) &&
			  (type3 != Integral::SYMMETRIC))

		      // or if both are upper and the output is upper
		      //
		      || ((type1 == Integral::UPPER_TRIANGULAR)
			  && (type1 == type2) && (type1 == type3))

		      // or if both are lower and the output is lower
		      //
		      || ((type1 == Integral::LOWER_TRIANGULAR)
			  && (type1 == type2) && (type1 == type3))) {

		    // we use a transpose of arg_mat2 so that the result is
		    // the same as for multiplication:
		    //  transpose(transpose(mat)) = mat
		    //
		    tmp_mat.clear();
		    tmp_mat2.transpose(arg_mat2);
		    tmp_mat.changeType((Integral::MTYPE)type3);
		    tmp_mat.outerProduct(arg_mat1, tmp_mat2);
		    res_mat.assign((int32)MMAT_MULT_MAT_RES_REAL[mat1][mat2]
				   [MMAT_NROW_LOC], 
				   (int32)MMAT_MULT_MAT_RES_REAL[mat1][mat2]
				   [MMAT_NCOL_LOC], 
				   (float64*)&MMAT_MULT_MAT_RES_REAL[mat1][mat2]
				   [MMAT_DATA_LOC]);

		    if (tmp_mat.getType() != type3) {
		      Console::put(arg3_str);
		      return Error::handle(name(), L"outerProduct", Error::TEST,
					   __FILE__, __LINE__);
		    }
		    if (!res_mat.almostEqual(tmp_mat)) {
		      Console::put(arg3_str);
		      arg_mat1.debug(L"arg_mat1");
		      arg_mat2.debug(L"arg_mat2");
		      tmp_mat2.debug(L"tmp_mat2");
		      res_mat.debug(L"res_mat");
		      tmp_mat.debug(L"tmp_mat");
		      Error::handle(name(), L"outerProduct", Error::TEST, 
				    __FILE__, __LINE__);
		    }
		  }
		}

		// test the matrix quadratic methods
		//
		if (arg_mat1.getNumColumns() == arg_mat2.getNumRows()) {
		  
		  // the central matrix must be square
		  //
		  if (arg_mat2.isSquare()) {

		    // create the transpose matrix
		    //
		    tmp_mat.transpose(arg_mat1);
		      
		    // create a temporary matrix to store the expected
		    // results
		    //
		    MMatrix<TScalar, TIntegral> res_mat;
		    res_mat.mult(arg_mat1, arg_mat2);
		    res_mat.mult(res_mat, tmp_mat);

		    // compute the quadratic form
		    //
		    MMatrix<TScalar, TIntegral> out_mat;
		    arg_mat2.quadratic(out_mat, arg_mat1);

		    // verify the results
		    //
		    if (!res_mat.almostEqual(out_mat)) {
		      Console::put(arg3_str);
		      arg_mat1.debug(L"arg_mat1");
		      arg_mat2.debug(L"arg_mat2");
		      res_mat.debug(L"res_mat");
		      out_mat.debug(L"out_mat");
		      Error::handle(name(), L"outerProduct", Error::TEST, 
				    __FILE__, __LINE__);
		    }
		  }
		}
	      }
	    }
	  }
	}
      } 
    }
  }

  // reset indentation
  //
  if (level_a > Integral::NONE) {
    Console::decreaseIndention();
  }

  // exit gracefully
  //
  return true;
}

#ifdef ISIP_TEMPLATE_complex
// method: diagnose5
//
// arguments:
//  Integral::DEBUG level: (input) debug level for diagnostics
//
// return: a bool8 value indicating status
//
// this method tests (matrix, matrix)->matrix methods for complex matrix -
// thus this method tests output.operation(matrix1, matrix2), where
// operations are addition, subtraction and multiplication. this method
// also tests methods like matrix equality
//
template<class TScalar, class TIntegral>
bool8 MMatrixMethods::diagnose5(Integral::DEBUG level_a) {

  // define TVector
  //
  typedef MVector<TScalar, TIntegral> TVector;

  // set indentation
  //
  if (level_a > Integral::NONE) {
    Console::put(L"testing class-specific public methods: matrix, matrix --> matrix...\n");
    Console::increaseIndention();
  }

  // declare an array of matrix to hold all the 8 matrices used for testing
  //      
  MMatrix<TScalar, TIntegral> arg_mats[MMAT_NUM_MATS_TEST];

  // load up the argument matrices
  //
  for (int32 i = 0; i < MMAT_NUM_MATS_TEST; i++) {
    
    // assign the arguments
    //
    arg_mats[i].assignComplexDiagnose((int32)MMAT_ARG_MATRICES[i][MMAT_NROW_LOC], 
                       (int32)MMAT_ARG_MATRICES[i][MMAT_NCOL_LOC], 
                       (float64*)&MMAT_ARG_MATRICES[i][MMAT_DATA_LOC]);
  }

  // declare temporary matrices to be used for testing
  //
  MMatrix<TScalar, TIntegral> res_mat;
  MMatrix<TScalar, TIntegral> tmp_mat;
  MMatrix<TScalar, TIntegral> tmp_mat2;
  MMatrix<TScalar, TIntegral> arg_mat1;
  
  // loop through the different matrices (first operand)
  //
  for (int32 mat1 = MMAT_NUM_MATS_REAL; mat1 < MMAT_NUM_MATS_TEST; mat1++) {

    // declare local variables
    //
    Char mat1c;
    mat1c.assign((byte8)((int)'A' + mat1));

    // loop through the different types of matrices
    //
    for (int32 type1 = Integral::FULL; type1 <= Integral::SPARSE; type1++) {

      // check if the type conversion is possible
      //
      if (arg_mats[mat1].isTypePossible((Integral::MTYPE)type1)) {

	// create a diagnostic string to indicate the matrix and its type
	//		
	String type1_str(MMatrix<TScalar, TIntegral>::TYPE_MAP(type1));
	String arg1_str(L"testing mat1: ");
	arg1_str.concat(mat1c);
	arg1_str.concat(L", ");
	arg1_str.concat(type1_str);

	// assign the first matrix operand and change the type - type is
	// changed here so that this particular matrix can be tested for
	// every type it can have
	//
        arg_mat1.assign(arg_mats[mat1]);
        arg_mat1.changeType((Integral::MTYPE)type1);

        // loop through the different matrices (second operand)
        //
        for (int32 mat2 = MMAT_NUM_MATS_REAL; mat2 < MMAT_NUM_MATS_TEST; mat2++) {

	  // declare local variables
	  //
          Char mat2c;
          mat2c.assign((byte8)((int)'A' + mat2));
          
          // loop through the different types of matrices
          //
          for (int32 type2 = Integral::FULL; type2 <= Integral::SPARSE;
	       type2++) {

	    // check if type conversion is possible
	    //
            if (arg_mats[mat2].isTypePossible((Integral::MTYPE)type2)) {

	      // assign the second matrix operand and change the type - type is
	      // changed here so that this particular matrix can be tested for
	      // every type it can have
	      //	      
	      MMatrix<TScalar, TIntegral> arg_mat2;	      
              arg_mat2.assign(arg_mats[mat2]);	      
              arg_mat2.changeType((Integral::MTYPE)type2);

	      // create a diagnostic string to indicate both matrix
	      // operands and their type
	      //			      
              String type2_str(arg_mat2.TYPE_MAP(type2));
              String arg2_str;
              arg2_str.assign(L"; mat2: ");
              arg2_str.concat(mat2c);
              arg2_str.concat(L", ");
              arg2_str.concat(type2_str);
              arg2_str.insert(arg1_str, 0);

              // test matrix equality
	      //
              if ((mat1 == mat2)
                  && ((!arg_mat1.almostEqual(arg_mat2))
                      ||(!arg_mat2.almostEqual(arg_mat1)))) {
                Console::put(arg2_str);
                Error::handle(name(), L"eq", Error::TEST, __FILE__, __LINE__);
              }
              else if ((mat1 != mat2)
                       && ((arg_mat1.almostEqual(arg_mat2))
                           || (arg_mat2.almostEqual(arg_mat1)))) {
                Console::put(arg2_str);
                Error::handle(name(), L"eq", Error::TEST, __FILE__, __LINE__);
              }
	      
	      // loop over 6 different types of the matrices for output
	      //
	      for (int32 type3 = Integral::FULL; type3 <= Integral::SPARSE;
		   type3++) {
		
		// create a diagnostic string to indicate both matrix
		// operands and their type
		//			      
		String type3_str(arg_mat2.TYPE_MAP(type3));
		String arg3_str;
		arg3_str.assign(L"; output: ");
		arg3_str.concat(type3_str);
		arg3_str.insert(arg2_str, 0);
		
		// addition and subtraction require the same dimensions
		//
		if (arg_mat1.checkDimensions(arg_mat2)) {
		  
		  if (
		      // all things can be tested full or sparse
		      //
		      (type3 == Integral::FULL) || (type3 == Integral::SPARSE)

		      // or if one input is diagonal, we can test to the other
		      // for all types but symmetric
		      //
		      || ((type1 == Integral::DIAGONAL) && (type3 == type2))
		      || ((type2 == Integral::DIAGONAL) && (type3 == type1))

		      // or if both are upper and the output is upper
		      //
		      || ((type1 == Integral::UPPER_TRIANGULAR)
			  && (type1 == type2) && (type1 == type3))

		      // or if both are lower and the output is lower
		      //
		      || ((type1 == Integral::LOWER_TRIANGULAR)
			  && (type1 == type2) && (type1 == type3))) {
		      
		    tmp_mat.clear();
		    tmp_mat.changeType((Integral::MTYPE)type3);

		    // test matrix addition
		    //
		    tmp_mat.add(arg_mat1, arg_mat2);
		    res_mat.assignComplexDiagnose(
			           (int32)MMAT_ADD_MAT_RES_COMPLEX[mat1 - MMAT_NUM_MATS_REAL][mat2 - MMAT_NUM_MATS_REAL][MMAT_NROW_LOC],
				   (int32)MMAT_ADD_MAT_RES_COMPLEX[mat1 - MMAT_NUM_MATS_REAL][mat2 - MMAT_NUM_MATS_REAL] [MMAT_NCOL_LOC], 
				   (float64*)&MMAT_ADD_MAT_RES_COMPLEX[mat1 - MMAT_NUM_MATS_REAL][mat2 - MMAT_NUM_MATS_REAL] [MMAT_DATA_LOC]);

		    // make sure the type wasn't changed
		    //
		    if (tmp_mat.type_d != type3) {
		      Console::put(arg3_str);
		      return Error::handle(name(), L"add", Error::ARG,
					   __FILE__, __LINE__);
		    }
		    
		    if (!res_mat.almostEqual(tmp_mat)) {
		      Console::put(arg3_str);
		      Error::handle(name(), L"add", Error::TEST, 
				    __FILE__, __LINE__);
		    }

		    // test matrix subtraction:
		    //  the unsigned types are not tested here because there
		    //  will be some negative values in the result matrices
		    //
		    if ((typeid(byte8) != typeid(TIntegral)) &&
			(typeid(uint16) != typeid(TIntegral)) &&
			(typeid(uint32) != typeid(TIntegral)) &&
			(typeid(uint64) != typeid(TIntegral))) {

		      tmp_mat.changeType((Integral::MTYPE)type3);
		      tmp_mat.sub(arg_mat1, arg_mat2);
		      res_mat.assignComplexDiagnose(
				     (int32)MMAT_SUB_MAT_RES_COMPLEX[mat1 - MMAT_NUM_MATS_REAL][mat2 - MMAT_NUM_MATS_REAL][MMAT_NROW_LOC], 
				     (int32)MMAT_SUB_MAT_RES_COMPLEX[mat1 - MMAT_NUM_MATS_REAL][mat2 - MMAT_NUM_MATS_REAL][MMAT_NCOL_LOC], 
				     (float64*)&MMAT_SUB_MAT_RES_COMPLEX[mat1 - MMAT_NUM_MATS_REAL][mat2 - MMAT_NUM_MATS_REAL][MMAT_DATA_LOC]);

		      // make sure the type wasn't changed
		      //
		      if (tmp_mat.type_d != type3) {
			Console::put(arg3_str);
			return Error::handle(name(), L"sub", Error::TEST,
					     __FILE__, __LINE__);
		      }
		      
		      if (!res_mat.eq(tmp_mat)) {
			Console::put(arg3_str);
			Error::handle(name(), L"sub", Error::TEST, 
				      __FILE__, __LINE__);
		      }
		    }
		  }
		}
              
		// test matrix multiplication if dimensions agree
		//
		if (arg_mat1.getNumColumns() == arg_mat2.getNumRows()) {
		  
		  if (
		      // all things can be tested full or sparse
		      //
		      (type3 == Integral::FULL) || (type3 == Integral::SPARSE)

		      // or if one input is diagonal, we can test to the other
		      // for all types but symmetric
		      //
		      || ((type1 == Integral::DIAGONAL) && (type3 == type2) &&
			  (type3 != Integral::SYMMETRIC))
		      || ((type2 == Integral::DIAGONAL) && (type3 == type1) &&
			  (type3 != Integral::SYMMETRIC))

		      // or if both are upper and the output is upper
		      //
		      || ((type1 == Integral::UPPER_TRIANGULAR)
			  && (type1 == type2) && (type1 == type3))

		      // or if both are lower and the output is lower
		      //
		      || ((type1 == Integral::LOWER_TRIANGULAR)
			  && (type1 == type2) && (type1 == type3))) {

		    tmp_mat.clear();
		    tmp_mat.changeType((Integral::MTYPE)type3);
		    tmp_mat.mult(arg_mat1, arg_mat2);
		    res_mat.assignComplexDiagnose((int32)MMAT_MULT_MAT_RES_COMPLEX[mat1 - MMAT_NUM_MATS_REAL][mat2 - MMAT_NUM_MATS_REAL]
				   [MMAT_NROW_LOC], 
				   (int32)MMAT_MULT_MAT_RES_COMPLEX[mat1 - MMAT_NUM_MATS_REAL][mat2 - MMAT_NUM_MATS_REAL]
				   [MMAT_NCOL_LOC], 
				   (float64*)&MMAT_MULT_MAT_RES_COMPLEX[mat1 - MMAT_NUM_MATS_REAL][mat2 - MMAT_NUM_MATS_REAL]
				   [MMAT_DATA_LOC]);

		    if (tmp_mat.getType() != type3) {
		      Console::put(arg3_str);
		      return Error::handle(name(), L"mult", Error::TEST,
					   __FILE__, __LINE__);
		    }
		    if (!res_mat.almostEqual(tmp_mat)) {
		      Console::put(arg3_str);
		      Error::handle(name(), L"mult", Error::TEST, 
				    __FILE__, __LINE__);
		    }
		  }
		}

		// test the matrix outer product if dimensions agree
		//
		if (arg_mat1.getNumColumns() == arg_mat2.getNumRows()) {
		  
		  if (
		      // all things can be tested full or sparse
		      //
		      (type3 == Integral::FULL) || (type3 == Integral::SPARSE)

		      // or if one input is diagonal, we can test to the other
		      // for all types but symmetric
		      //
		      || ((type1 == Integral::DIAGONAL) && (type3 == type2) &&
			  (type3 != Integral::SYMMETRIC))
		      || ((type2 == Integral::DIAGONAL) && (type3 == type1) &&
			  (type3 != Integral::SYMMETRIC))

		      // or if both are upper and the output is upper
		      //
		      || ((type1 == Integral::UPPER_TRIANGULAR)
			  && (type1 == type2) && (type1 == type3))

		      // or if both are lower and the output is lower
		      //
		      || ((type1 == Integral::LOWER_TRIANGULAR)
			  && (type1 == type2) && (type1 == type3))) {

		    // we use a transpose of arg_mat2 so that the result is
		    // the same as for multiplication:
		    //  transpose(transpose(mat)) = mat
		    //
		    tmp_mat.clear();
		    tmp_mat2.transpose(arg_mat2);
		    tmp_mat.changeType((Integral::MTYPE)type3);
		    tmp_mat.outerProduct(arg_mat1, tmp_mat2);
		    res_mat.assignComplexDiagnose((int32)MMAT_MULT_MAT_RES_COMPLEX[mat1 - MMAT_NUM_MATS_REAL][mat2 - MMAT_NUM_MATS_REAL]
				   [MMAT_NROW_LOC], 
				   (int32)MMAT_MULT_MAT_RES_COMPLEX[mat1 - MMAT_NUM_MATS_REAL][mat2 - MMAT_NUM_MATS_REAL]
				   [MMAT_NCOL_LOC], 
				   (float64*)&MMAT_MULT_MAT_RES_COMPLEX[mat1 - MMAT_NUM_MATS_REAL][mat2 - MMAT_NUM_MATS_REAL]
				   [MMAT_DATA_LOC]);

		    if (tmp_mat.getType() != type3) {
		      Console::put(arg3_str);
		      return Error::handle(name(), L"outerProduct", Error::TEST,
					   __FILE__, __LINE__);
		    }
		    if (!res_mat.almostEqual(tmp_mat)) {
		      arg_mat1.debug(L"arg_mat1");
		      arg_mat2.debug(L"arg_mat2");
		      tmp_mat2.debug(L"tmp_mat2");
		      res_mat.debug(L"res_mat");
		      tmp_mat.debug(L"tmp_mat");
		      Error::handle(name(), L"outerProduct", Error::TEST, 
				    __FILE__, __LINE__);

		    }
		  }
		}

		// test the matrix quadratic methods
		//
		if (arg_mat1.getNumColumns() == arg_mat2.getNumRows()) {
		  
		  // the central matrix must be square
		  //
		  if (arg_mat2.isSquare()) {

		    // create the transpose matrix
		    //
		    tmp_mat.transpose(arg_mat1);
		      
		    // create a temporary matrix to store the expected
		    // results
		    //
		    MMatrix<TScalar, TIntegral> res_mat;
		    res_mat.mult(arg_mat1, arg_mat2);
		    res_mat.mult(res_mat, tmp_mat);

		    // compute the quadratic form
		    //
		    MMatrix<TScalar, TIntegral> out_mat;
		    arg_mat2.quadratic(out_mat, arg_mat1);

		    // verify the results
		    //
		    if (!res_mat.almostEqual(out_mat)) {
		      Console::put(arg3_str);
		      arg_mat1.debug(L"arg_mat1");
		      arg_mat2.debug(L"arg_mat2");
		      res_mat.debug(L"res_mat");
		      out_mat.debug(L"out_mat");
		      Error::handle(name(), L"outerProduct", Error::TEST, 
				    __FILE__, __LINE__);
		    }
		  }
		}
	      }
	    }
	  }
	}
      } 
    }
  }

  // reset indentation
  //
  if (level_a > Integral::NONE) {
    Console::decreaseIndention();
  }

  // exit gracefully
  //
  return true;
}
#endif

// explicit instantiations. note that the sub-diagnose methods don't need
// there own instantiations since they are private and nothing but the
// primary diagnose method (also in this file) call them.
//
template bool8
MMatrixMethods::diagnose<MMatrix<ISIP_TEMPLATE_TARGET>, ISIP_TEMPLATE_TARGET>
(Integral::DEBUG level);
