// file: $isip/class/math/matrix/MMatrix/mmat_09.cc
// version: $Id: mmat_09.cc 7924 2002-03-15 23:30:38Z zheng $
//

// isip include files
//
#include "MMatrixMethods.h"
#include "MMatrix.h"

// method: add
//
// arguments:
//  MMatrix<TScalar, TIntegral>& this: (output) class operand
//  TIntegral value: (input) scalar value
//
// return: a bool8 value indicating status
//
template<class TScalar, class TIntegral>
bool8 MMatrixMethods::add(MMatrix<TScalar, TIntegral>& this_a, 
			    TIntegral value_a) {

  // get the type of the matrix and branch on type
  //
  Integral::MTYPE type = this_a.getType();
  
  // if the current matrix is a sparse, change it to full for the
  // computation. this is admittedly inefficient, but there is really
  // no way for this computation to be efficient anyway.
  //
  if (type == Integral::SPARSE) {
    this_a.changeType(Integral::FULL);
  }

  //  now we simply need to add the value to the storage vector
  //
  if (!this_a.m_d.add(value_a)) {
    return false;
  }

  // for sparse we need to change the type back
  //
  if (type == Integral::SPARSE) {
    this_a.changeType(Integral::SPARSE);
  }

  // exit gracefully
  //
  return true;
}

// explicit instantiations
//
template bool8
MMatrixMethods::add<ISIP_TEMPLATE_TARGET>
(MMatrix<ISIP_TEMPLATE_TARGET>&, ISIP_TEMPLATE_T1);

// method: add
//
// arguments:
//  MMatrix<TScalar, TIntegral>& this: (output) class operand
//  const MMatrix<TAScalar, TAIntegral>& m2: (input) operand 1
//
// return: a bool8 value indicating status
//
// this method adds a matrix to "this". we use the following flowchart:
//
// (1) special cases:
//      types are equal: process internal data directly for all types
//      one of the types is sparse: process internal data directly
//      one of the types is full: the result is always a full matrix
//      
// (2) other cases:
//      this matrix describes the type of the output matrix as a function
//      of the input types. For the operation a += b,
//      type1 is the type of a; type 2 is the type of b.
//
//    TYPE2 --------> FULL  DIAG  SYMM  LTRI  UTRI  SPRS
//    TYPE1 ->  FULL: full  full  full  full  full  full
//              DIAG: full  diag  symm  ltri  utri  sprs
//              SYMM: full  symm  symm  full  full  full
//              LTRI: full  ltri  full  ltri  full  full
//              UTRI: full  utri  full  full  utri  full
//              SPRS: full  sprs  full  full  full  sprs
//
template<class TScalar, class TIntegral, class TAScalar, class TAIntegral>
bool8 MMatrixMethods::add(MMatrix<TScalar, TIntegral>& this_a, 
			    const MMatrix<TAScalar, TAIntegral>& m2_a) {

  // check if the two input matrices have the dimensions
  //
  if (!this_a.checkDimensions(m2_a))  {
    m2_a.debug(L"m2_a");    
    this_a.debug(L"this_a");    
    return Error::handle(name(), L"add", Error::ARG, __FILE__, __LINE__);
  }

  // declare local variables
  //
  int32 nrows = this_a.nrows_d;
  Integral::MTYPE type1 = this_a.type_d;
  Integral::MTYPE type2 = m2_a.type_d;
  
  //---------------------------------------------------------------------------
  // special cases:
  //  in this section, we deal with special cases that share the same
  //  code structure.
  //---------------------------------------------------------------------------

  // if the two types are the same, we can simply operate on the storage
  // vectors directly
  //
  if (type1 == type2) {

    // type: FULL, DIAGONAL, SYMMETRIC, LOWER_TRIANGULAR, UPPER_TRIANGULAR
    //
    if ((type1 == Integral::FULL) ||
	(type1 == Integral::SYMMETRIC) ||
	(type1 == Integral::DIAGONAL) ||
	(type1 == Integral::LOWER_TRIANGULAR) ||
	(type1 == Integral::UPPER_TRIANGULAR)) {
      return this_a.m_d.add(m2_a.m_d);
    }

    // type: SPARSE
    //
    else {

      // loop through each element of the second argument
      //
      for (int32 index = 0; index < m2_a.m_d.length(); index++) {
	int32 row = m2_a.row_index_d(index);
	int32 col = m2_a.col_index_d(index);
        this_a.setValue(row, col,(TIntegral)(this_a(row, col) + m2_a.m_d(index)));
      }
      return true;
    }
  }

  // if the first type is sparse, and the second type isn't sparse,
  // we assign the output type to FULL (except for DIAG), then
  // add elements of the second.
  //
  else if ((type1 == Integral::SPARSE) && (type2 != Integral::SPARSE)) {

    // create a FULL matrix for all types except DIAGONAL
    //
    if (type2 != Integral::DIAGONAL) {
      this_a.changeType(Integral::FULL);
    }

    // add elements of the second matrix
    //
    for (int32 row = 0; row < nrows; row++) {
      int32 start_col = m2_a.startColumn(row, this_a.type_d, type2);
      int32 stop_col = m2_a.stopColumn(row, this_a.type_d, type2);
      for (int32 col = start_col; col <= stop_col; col++) {
	this_a.setValue(row, col, (TIntegral)(this_a(row, col) + m2_a(row, col)));
      }
    }

    // restore the type
    //
    return this_a.changeType(type1);
  }

  // if the second type is sparse, and the first type isn't sparse,
  // we assign the output type to FULL (except for DIAGONAL), and
  // add the elements of the second.
  //
  else if ((type1 != Integral::SPARSE) && (type2 == Integral::SPARSE)) {

    // create a FULL matrix for all types except DIAGONAL
    //
    if (this_a.type_d == Integral::DIAGONAL) {
      this_a.changeType(Integral::SPARSE);
    }
    else {
      this_a.changeType(Integral::FULL);
    }
    
    // add elements of the second sparse matrix
    //
    for (int32 index = 0; index < m2_a.m_d.length(); index++) {
      int32 row = m2_a.row_index_d(index);
      int32 col = m2_a.col_index_d(index);
      this_a.setValue(row, col, (TIntegral)(this_a(row, col) + m2_a(row, col)));
    }

    // restore the type
    //
    return this_a.changeType(type1);
  }
    
  // if either type is FULL, we assign the output type to FULL,
  // then add elements of the second
  //
  else if ((type1 == Integral::FULL) || (type2 == Integral::FULL)) {
    this_a.changeType(Integral::FULL);
  }

  //---------------------------------------------------------------------------
  // in this section of the code, we deal with the remaining cases where
  // the matrices are of different types, and some intelligent conversion
  // must be done.
  //---------------------------------------------------------------------------
  
  // type1: DIAGONAL
  //  the remaining types are SYMMETRIC and *_TRIANGULAR. 
  //  the output types follow the type of the second operand.
  // 
  else if (type1 == Integral::DIAGONAL) {
    this_a.changeType(type2);
  }
    
  // type1: SYMMETRIC, *_TRIANGULAR
  //  the remaining types are DIAGONAL, SYMMETRIC, and *_TRIANGULAR. 
  //  the output types vary with the input.
  // 
  else {
    
    // set up the output matrix: a diagonal matrix preserves the type
    // of the input; all other types force a full matrix.
    //
    if (type2 != Integral::DIAGONAL) {
      this_a.changeType(Integral::FULL);
    }
  }

  // now, we can add elements of the second matrix to "this"
  //
  for (int32 row = 0; row < nrows; row++) {
    int32 start_col = m2_a.startColumn(row, this_a.type_d, type2);
    int32 stop_col = m2_a.stopColumn(row, this_a.type_d, type2);
    for (int32 col = start_col; col <= stop_col; col++) {
      this_a.m_d(this_a.index(row, col)) += 
	(TIntegral)m2_a.m_d(m2_a.index(row, col));
    }
  }

  // restore the type
  //
  return this_a.changeType(type1);
}

// explicit instantiations
//
#ifndef ISIP_TEMPLATE_complex
template bool8
MMatrixMethods::add<ISIP_TEMPLATE_TARGET, Byte, byte8>
(MMatrix<ISIP_TEMPLATE_TARGET>&, const MMatrix<Byte, byte8>&);

template bool8
MMatrixMethods::add<ISIP_TEMPLATE_TARGET, Ushort, uint16>
(MMatrix<ISIP_TEMPLATE_TARGET>&, const MMatrix<Ushort, uint16>&);

template bool8
MMatrixMethods::add<ISIP_TEMPLATE_TARGET, Ulong, uint32>
(MMatrix<ISIP_TEMPLATE_TARGET>&, const MMatrix<Ulong, uint32>&);

template bool8
MMatrixMethods::add<ISIP_TEMPLATE_TARGET, Ullong, uint64>
(MMatrix<ISIP_TEMPLATE_TARGET>&, const MMatrix<Ullong, uint64>&);

template bool8
MMatrixMethods::add<ISIP_TEMPLATE_TARGET, Short, int16>
(MMatrix<ISIP_TEMPLATE_TARGET>&, const MMatrix<Short, int16>&);

template bool8
MMatrixMethods::add<ISIP_TEMPLATE_TARGET, Long, int32>
(MMatrix<ISIP_TEMPLATE_TARGET>&, const MMatrix<Long, int32>&);

template bool8
MMatrixMethods::add<ISIP_TEMPLATE_TARGET, Llong, int64>
(MMatrix<ISIP_TEMPLATE_TARGET>&, const MMatrix<Llong, int64>&);

template bool8
MMatrixMethods::add<ISIP_TEMPLATE_TARGET, Float, float32>
(MMatrix<ISIP_TEMPLATE_TARGET>&, const MMatrix<Float, float32>&);

template bool8
MMatrixMethods::add<ISIP_TEMPLATE_TARGET, Double, float64>
(MMatrix<ISIP_TEMPLATE_TARGET>&, const MMatrix<Double, float64>&);
#endif

#ifdef ISIP_TEMPLATE_complex
template bool8
MMatrixMethods::add<ISIP_TEMPLATE_TARGET, ComplexLong, complexlong>
(MMatrix<ISIP_TEMPLATE_TARGET>&, const MMatrix<ComplexLong, complexlong>&);

template bool8
MMatrixMethods::add<ISIP_TEMPLATE_TARGET, ComplexFloat, complexfloat>
(MMatrix<ISIP_TEMPLATE_TARGET>&, const MMatrix<ComplexFloat, complexfloat>&);

template bool8
MMatrixMethods::add<ISIP_TEMPLATE_TARGET, ComplexDouble, complexdouble>
(MMatrix<ISIP_TEMPLATE_TARGET>&, const MMatrix<ComplexDouble, complexdouble>&);
#endif

// method: add
//
// arguments:
//  MMatrix<TScalar, TIntegral>& this: (output) class operand
//  const MMatrix<TScalar, TIntegral>& m1: (input) operand 1
//  const MMatrix<TAScalar, TAIntegral>& m2: (input) operand 2
//
// return: a bool8 value indicating status
//
// add the two argument matrices and store result in the current matrix
// for example:
//
//       [1 2 3]       [2 0 4]                    [3  2  7]
//  m1 = [4 5 6]  m2 = [0 6 0]  m_out = m1 + m2 = [4  11 6]
//       [7 8 9]       [8 0 1]                    [15 8 10]
//
// this method has evolved somewhat as our ability to efficiently
// copy and assign matrices has improved. this version implements
// some complicated logic to do things as efficiently as possible.
// the approach can best be summarized by the following flowchart and matrix:
//
// (1) special cases:
//      types are equal: process internal data directly for all types
//      one of the types is sparse: process internal data directly
//      one of the types is full: the result is always a full matrix
//      
// (2) other cases:
//      this matrix describes the type of the output matrix as a function
//      of the input types. For the operation c = a + b,
//      type1 is the type of a; type 2 is the type of b.
//
//    TYPE2 --------> FULL  DIAG  SYMM  LTRI  UTRI  SPRS
//    TYPE1 ->  FULL: full  full  full  full  full  full
//              DIAG: full  diag  symm  ltri  utri  sprs
//              SYMM: full  symm  symm  full  full  full
//              LTRI: full  ltri  full  ltri  full  full
//              UTRI: full  utri  full  full  utri  full
//              SPRS: full  sprs  full  full  full  sprs
//
// addition has an advantage over subtraction in that we can interchange
// the matrices such that the least number of operations are performed.
//
template<class TScalar, class TIntegral, class TAScalar, class TAIntegral>
bool8 MMatrixMethods::add(MMatrix<TScalar, TIntegral>& this_a, 
			    const MMatrix<TScalar, TIntegral>& m1_a, 
			    const MMatrix<TAScalar, TAIntegral>& m2_a) {

  // check if the two input matrices have the dimensions
  //
  if (!m1_a.checkDimensions(m2_a))  {
    m1_a.debug(L"m1_a");
    m2_a.debug(L"m2_a");    
    return Error::handle(name(), L"add", Error::ARG, __FILE__, __LINE__);
  }

  // declare local variables
  //
  int32 nrows = m1_a.nrows_d;
  int32 ncols = m2_a.ncols_d;
  Integral::MTYPE old_type = this_a.type_d;
  Integral::MTYPE type1 = m1_a.type_d;
  Integral::MTYPE type2 = m2_a.type_d;
  
  //---------------------------------------------------------------------------
  // special cases:
  //  in this section, we deal with special cases that share the same
  //  code structure.
  //---------------------------------------------------------------------------

  // if the two types are the same, we can simply operate on the storage
  // vectors directly
  //
  if (type1 == type2) {

    // type: FULL, DIAGONAL, SYMMETRIC, LOWER_TRIANGULAR, UPPER_TRIANGULAR
    //
    if ((type1 == Integral::FULL) ||
	(type1 == Integral::DIAGONAL) ||
	(type1 == Integral::SYMMETRIC) ||
	(type1 == Integral::LOWER_TRIANGULAR) ||
	(type1 == Integral::UPPER_TRIANGULAR)) {
      this_a.setDimensions(nrows, ncols, false, m1_a.type_d);
      this_a.m_d.add(m1_a.m_d, m2_a.m_d);
    }

    // type: SPARSE
    //
    else {

      // set the output matrix to SPARSE
      //
      this_a.assign(m1_a, Integral::SPARSE);

      // loop through each element of the second argument
      //
      for (int32 index = 0; index < m2_a.m_d.length(); index++) {
	int32 row = m2_a.row_index_d(index);
	int32 col = m2_a.col_index_d(index);
        this_a.setValue(row, col, (TIntegral)(m1_a(row, col) + m2_a.m_d(index)));
      }
    }
    
    // restore the type and return
    //
    return this_a.changeType(old_type);
  }

  // if the first type is sparse, and the second type isn't sparse,
  // we assign the output type to FULL (except for DIAG), copy the elements
  // of the second (which has more elements), and then add elements of
  // the first.
  //
  else if ((type1 == Integral::SPARSE) && (type2 != Integral::SPARSE)) {

    // create a FULL matrix for all types except DIAGONAL, and zero it
    //
    if (type2 == Integral::DIAGONAL) {
      this_a.setDimensions(nrows, ncols, false, Integral::SPARSE);
    }
    else {
      this_a.setDimensions(nrows, ncols, false, Integral::FULL);
    }
    this_a.copy(m2_a);

    // add elements of the first matrix
    //
    for (int32 index = 0; index < m1_a.m_d.length(); index++) {
      int32 row = m1_a.row_index_d(index);
      int32 col = m1_a.col_index_d(index);
      this_a.setValue(row, col, this_a(row, col) + m1_a(row, col));
    }
  }

  // if the second type is sparse, and the first type isn't sparse,
  // we assign the output type to FULL (except for DIAGONAL), copy the
  // elements of the first, and then add elements of the second
  //
  else if ((type1 != Integral::SPARSE) && (type2 == Integral::SPARSE)) {

    // create a FULL matrix for all types except DIAGONAL, and zero it
    //
    if (m1_a.type_d == Integral::DIAGONAL) {
      this_a.assign(m1_a, Integral::SPARSE);
    }
    else {
      this_a.assign(m1_a, Integral::FULL);
    }
    
    // add elements of the second sparse matrix
    //
    for (int32 index = 0; index < m2_a.m_d.length(); index++) {
      int32 row = m2_a.row_index_d(index);
      int32 col = m2_a.col_index_d(index);
      this_a.setValue(row, col, (TIntegral)(this_a(row, col) + m2_a(row, col)));
    }
  }

  // if either type is FULL, we assign the output type to FULL,
  // copy the elements from the first, then add elements of the second
  //
  else if (type1 == Integral::FULL) {

    // create a FULL matrix through assignment
    //
    this_a.assign(m1_a, Integral::FULL);
    
    // add elements of the second matrix
    //
    for (int32 row = 0; row < nrows; row++) {

      // add the values
      //
      int32 start_col = m2_a.startColumn(row, this_a.type_d, type2);
      int32 stop_col = m2_a.stopColumn(row, this_a.type_d, type2);

      for (int32 col = start_col; col <= stop_col; col++) {
	this_a.setValue(row, col, (TIntegral)(this_a(row, col) + m2_a(row, col)));
      }
    }
  }

  // if either type is FULL, we assign the output type to FULL,
  // copy the elements from the first, then add elements of the second
  //
  else if (type2 == Integral::FULL) {

    // create a FULL matrix through assignment
    //
    this_a.assign(m2_a, Integral::FULL);
    
    // add elements of the second matrix
    //
    for (int32 row = 0; row < nrows; row++) {

      // add the values
      //
      int32 start_col = m1_a.startColumn(row, type1, this_a.type_d);
      int32 stop_col = m1_a.stopColumn(row, type1, this_a.type_d);

      for (int32 col = start_col; col <= stop_col; col++) {
	this_a.setValue(row, col, this_a(row, col) + m1_a(row, col));
      }
    }
  }
  
  //---------------------------------------------------------------------------
  // in this section of the code, we deal with the remaining cases where
  // the matrices are of different types, and some intelligent conversion
  // must be done.
  //---------------------------------------------------------------------------
  
  // type1: DIAGONAL
  //  the remaining types are SYMMETRIC and *_TRIANGULAR. 
  //  the output types follow the type of the second operand.
  //  the approach is to create a matrix, copy the second operand,
  //  and add the first operand.
  // 
  else if (type1 == Integral::DIAGONAL) {
    
    // set up the output matrix and assign values
    //
    this_a.assign(m2_a, type2);

    // add the diagonal
    //
    for (int32 row = 0; row < nrows; row++) {  
      this_a.m_d(this_a.index(row, row)) += (TIntegral)m1_a.m_d(row);
    }
  }

  else if (type2 == Integral::SYMMETRIC) {

    // set up the output matrix and assign values
    //
    this_a.assign(m2_a, Integral::FULL);

    // add elements of the first matrix
    //
    for (int32 row = 0; row < nrows; row++) {

      // add the values
      //
      int32 start_col = m1_a.startColumn(row, type1, this_a.type_d);
      int32 stop_col = m1_a.stopColumn(row, type1, this_a.type_d);

      for (int32 col = start_col; col <= stop_col; col++) {
	this_a.m_d(this_a.index(row, col)) += 
	  (TIntegral)m1_a.m_d(m1_a.index(row, col));
      }
    }
  }
    
  // type1: SYMMETRIC, *_TRIANGULAR
  //  the remaining types are DIAGONAL, SYMMETRIC, and *_TRIANGULAR. 
  //  the output types vary with the input.
  //  the approach is to copy the values of the first operand,
  //  and add the values of the second operand.
  // 
  else {
    
    // set up the output matrix: a diagonal matrix preserves the type
    // of the input; all other types force a full matrix.
    //
    if ((type1 == Integral::SYMMETRIC) &&
	(type2 == Integral::DIAGONAL)) {
      this_a.assign(m1_a, Integral::SYMMETRIC);
    }
    if ((type1 == Integral::LOWER_TRIANGULAR) &&
	(type2 == Integral::DIAGONAL)) {
      this_a.assign(m1_a, Integral::LOWER_TRIANGULAR);
    }
    else if ((type1 == Integral::UPPER_TRIANGULAR) &&
	     (type2 == Integral::DIAGONAL)) {
      this_a.assign(m1_a, Integral::UPPER_TRIANGULAR);
    }
    else {
      this_a.assign(m1_a, Integral::FULL);
    }

    // add elements of the second matrix
    //
    for (int32 row = 0; row < nrows; row++) {

      // add the values
      //
      int32 start_col = m2_a.startColumn(row, this_a.type_d, type2);
      int32 stop_col = m2_a.stopColumn(row, this_a.type_d, type2);

      for (int32 col = start_col; col <= stop_col; col++) {
	this_a.m_d(this_a.index(row, col)) += 
	  (TIntegral)m2_a.m_d(m2_a.index(row, col));
      }
    }
  }
  
  // exit gracefully
  //
  return this_a.changeType(old_type);
}

// explicit instantiations
//
#ifndef ISIP_TEMPLATE_complex
template bool8
MMatrixMethods::add<ISIP_TEMPLATE_TARGET, Byte, byte8>
(MMatrix<ISIP_TEMPLATE_TARGET>&, const MMatrix<ISIP_TEMPLATE_TARGET>&,
 const MMatrix<Byte, byte8>&);

template bool8
MMatrixMethods::add<ISIP_TEMPLATE_TARGET, Ushort, uint16>
(MMatrix<ISIP_TEMPLATE_TARGET>&, const MMatrix<ISIP_TEMPLATE_TARGET>&,
 const MMatrix<Ushort, uint16>&);

template bool8
MMatrixMethods::add<ISIP_TEMPLATE_TARGET, Ulong, uint32>
(MMatrix<ISIP_TEMPLATE_TARGET>&, const MMatrix<ISIP_TEMPLATE_TARGET>&,
 const MMatrix<Ulong, uint32>&);

template bool8
MMatrixMethods::add<ISIP_TEMPLATE_TARGET, Ullong, uint64>
(MMatrix<ISIP_TEMPLATE_TARGET>&, const MMatrix<ISIP_TEMPLATE_TARGET>&,
 const MMatrix<Ullong, uint64>&);

template bool8
MMatrixMethods::add<ISIP_TEMPLATE_TARGET, Short, int16>
(MMatrix<ISIP_TEMPLATE_TARGET>&, const MMatrix<ISIP_TEMPLATE_TARGET>&,
 const MMatrix<Short, int16>&);

template bool8
MMatrixMethods::add<ISIP_TEMPLATE_TARGET, Long, int32>
(MMatrix<ISIP_TEMPLATE_TARGET>&, const MMatrix<ISIP_TEMPLATE_TARGET>&,
 const MMatrix<Long, int32>&);

template bool8
MMatrixMethods::add<ISIP_TEMPLATE_TARGET, Llong, int64>
(MMatrix<ISIP_TEMPLATE_TARGET>&, const MMatrix<ISIP_TEMPLATE_TARGET>&,
 const MMatrix<Llong, int64>&);

template bool8
MMatrixMethods::add<ISIP_TEMPLATE_TARGET, Float, float32>
(MMatrix<ISIP_TEMPLATE_TARGET>&, const MMatrix<ISIP_TEMPLATE_TARGET>&,
 const MMatrix<Float, float32>&);

template bool8
MMatrixMethods::add<ISIP_TEMPLATE_TARGET, Double, float64>
(MMatrix<ISIP_TEMPLATE_TARGET>&, const MMatrix<ISIP_TEMPLATE_TARGET>&,
 const MMatrix<Double, float64>&);
#endif

#ifdef ISIP_TEMPLATE_complex
template bool8
MMatrixMethods::add<ISIP_TEMPLATE_TARGET, ComplexLong, complexlong>
(MMatrix<ISIP_TEMPLATE_TARGET>&, const MMatrix<ISIP_TEMPLATE_TARGET>&,
 const MMatrix<ComplexLong, complexlong>&);

template bool8
MMatrixMethods::add<ISIP_TEMPLATE_TARGET, ComplexFloat, complexfloat>
(MMatrix<ISIP_TEMPLATE_TARGET>&, const MMatrix<ISIP_TEMPLATE_TARGET>&,
 const MMatrix<ComplexFloat, complexfloat>&);

template bool8
MMatrixMethods::add<ISIP_TEMPLATE_TARGET, ComplexDouble, complexdouble>
(MMatrix<ISIP_TEMPLATE_TARGET>&, const MMatrix<ISIP_TEMPLATE_TARGET>&,
 const MMatrix<ComplexDouble, complexdouble>&);
#endif

// method: sub
//
// arguments:
//  MMatrix<TScalar, TIntegral>& this: (output) class operand
//  TIntegral value: (input) scalar value
//
// return: a bool8 value indicating status
//
template<class TScalar, class TIntegral>
bool8 MMatrixMethods::sub(MMatrix<TScalar, TIntegral>& this_a, 
			    TIntegral value_a) {

  // get the type of the matrix and branch on type
  //
  Integral::MTYPE type = this_a.getType();
  
  // if the current matrix is a sparse, change it to full for the
  // computation. this is admittedly inefficient, but there is really
  // no way for this computation to be efficient anyway.
  //
  if (type == Integral::SPARSE) {
    this_a.changeType(Integral::FULL);
  }

  //  now we simply need to subtract the value to the storage vector
  //
  if (!this_a.m_d.sub(value_a)) {
    return false;
  }

  // for sparse we need to change the type back
  //
  if (type == Integral::SPARSE) {
    this_a.changeType(Integral::SPARSE);
  }

  // exit gracefully
  //
  return true;
}

// explicit instantiations
//
template bool8
MMatrixMethods::sub<ISIP_TEMPLATE_TARGET>
(MMatrix<ISIP_TEMPLATE_TARGET>&, ISIP_TEMPLATE_T1);

// method: sub
//
// arguments:
//  MMatrix<TScalar, TIntegral>& this: (output) class operand
//  const MMatrix<TAScalar, TAIntegral>& m2: (input) operand 2
//
// return: a bool8 value indicating status
//
// the approach can best be summarized by the following flowchart and matrix:
//
// (1) special cases:
//      types are equal: process internal data directly for all types
//      one of the types is sparse: process internal data directly
//      one of the types is full: the result is always a full matrix
//      
// (2) other cases:
//      this matrix describes the type of the output matrix as a function
//      of the input types. For the operation a -= b,
//      type1 is the type of a; type 2 is the type of b.
//
//    TYPE2 --------> FULL  DIAG  SYMM  LTRI  UTRI  SPRS
//    TYPE1 ->  FULL: full  full  full  full  full  full
//              DIAG: full  diag  symm  ltri  utri  sprs
//              SYMM: full  symm  symm  full  full  full
//              LTRI: full  ltri  full  ltri  full  full
//              UTRI: full  utri  full  full  utri  full
//              SPRS: full  sprs  full  full  full  sprs
//
// the code that implements each combination attempts to exploit the
// properties of the matrices as much as possible.
//
template<class TScalar, class TIntegral, class TAScalar, class TAIntegral>
bool8 MMatrixMethods::sub(MMatrix<TScalar, TIntegral>& this_a, 
			    const MMatrix<TAScalar, TAIntegral>& m2_a) {

  // check if the two input matrices have the dimensions
  //
  if (!this_a.checkDimensions(m2_a))  {
    m2_a.debug(L"m2_a");    
    this_a.debug(L"this_a");    
    return Error::handle(name(), L"sub", Error::ARG, __FILE__, __LINE__);
  }

  // declare local variables
  //
  int32 nrows = this_a.nrows_d;
  Integral::MTYPE type1 = this_a.type_d;
  Integral::MTYPE type2 = m2_a.type_d;
  
  //---------------------------------------------------------------------------
  // special cases:
  //  in this section, we deal with special cases that share the same
  //  code structure.
  //---------------------------------------------------------------------------

  // if the two types are the same, we can simply operate on the storage
  // vectors directly
  //
  if (type1 == type2) {

    // type: FULL, DIAGONAL, SYMMETRIC, LOWER_TRIANGULAR, UPPER_TRIANGULAR
    //
    if ((type1 == Integral::FULL) ||
	(type1 == Integral::SYMMETRIC) ||
	(type1 == Integral::DIAGONAL) ||
	(type1 == Integral::LOWER_TRIANGULAR) ||
	(type1 == Integral::UPPER_TRIANGULAR)) {
      return this_a.m_d.sub(m2_a.m_d);
    }

    // type: SPARSE
    //
    else {

      // loop through each element of the second argument
      //
      for (int32 index = 0; index < m2_a.m_d.length(); index++) {
	int32 row = m2_a.row_index_d(index);
	int32 col = m2_a.col_index_d(index);
        this_a.setValue(row, col, (TIntegral)(this_a(row, col) - m2_a.m_d(index)));
      }
      return true;
    }
  }

  // if the first type is sparse, and the second type isn't sparse,
  // we assign the output type to FULL (except for DIAG),
  // and then subtract elements of the second.
  //
  else if ((type1 == Integral::SPARSE) && (type2 != Integral::SPARSE)) {

    // create a FULL matrix for all types except DIAGONAL
    //
    if (type2 != Integral::DIAGONAL) {
      this_a.changeType(Integral::FULL);
    }

    // add elements of the second matrix
    //
    for (int32 row = 0; row < nrows; row++) {
      int32 start_col = m2_a.startColumn(row, this_a.type_d, type2);
      int32 stop_col = m2_a.stopColumn(row, this_a.type_d, type2);
      for (int32 col = start_col; col <= stop_col; col++) {
	this_a.setValue(row, col, (TIntegral)(this_a(row, col) - m2_a(row, col)));
      }
    }

    // restore the type
    //
    return this_a.changeType(type1);
  }

  // if the second type is sparse, and the first type isn't sparse,
  // we assign the output type to FULL (except for DIAGONAL), and
  // subtract the elements of the second.
  //
  else if ((type1 != Integral::SPARSE) && (type2 == Integral::SPARSE)) {

    // create a FULL matrix for all types except DIAGONAL
    //
    if (this_a.type_d == Integral::DIAGONAL) {
      this_a.changeType(Integral::SPARSE);
    }
    else {
      this_a.changeType(Integral::FULL);
    }
    
    // add elements of the second sparse matrix
    //
    for (int32 index = 0; index < m2_a.m_d.length(); index++) {
      int32 row = m2_a.row_index_d(index);
      int32 col = m2_a.col_index_d(index);
      this_a.setValue(row, col, (TIntegral)(this_a(row, col) - m2_a.m_d(index)));
    }

    // restore the type
    //
    return this_a.changeType(type1);
  }
    
  // if either type is FULL, we assign the output type to FULL,
  // then add elements of the second
  //
  else if ((type1 == Integral::FULL) || (type2 == Integral::FULL)) {
    this_a.changeType(Integral::FULL);
  }

  //---------------------------------------------------------------------------
  // in this section of the code, we deal with the remaining cases where
  // the matrices are of different types, and some intelligent conversion
  // must be done.
  //---------------------------------------------------------------------------
  
  // type1: DIAGONAL
  //  the remaining types are SYMMETRIC and *_TRIANGULAR. 
  //  the output types follow the type of the second operand.
  // 
  else if (type1 == Integral::DIAGONAL) {
    this_a.changeType(type2);
  }
    
  // type1: SYMMETRIC, *_TRIANGULAR
  //  the remaining types are DIAGONAL, SYMMETRIC, and *_TRIANGULAR. 
  //  the output types vary with the input.
  // 
  else {
    
    // set up the output matrix: a diagonal matrix preserves the type
    // of the input; all other types force a full matrix.
    //
    if (type2 != Integral::DIAGONAL) {
      this_a.changeType(Integral::FULL);
    }
  }

  // now, we can add elements of the second matrix to "this"
  //
  for (int32 row = 0; row < nrows; row++) {
    int32 start_col = m2_a.startColumn(row, this_a.type_d, type2);
    int32 stop_col = m2_a.stopColumn(row, this_a.type_d, type2);
    for (int32 col = start_col; col <= stop_col; col++) {
      this_a.m_d(this_a.index(row, col)) -= 
	(TIntegral)m2_a.m_d(m2_a.index(row, col));
    }
  }

  // restore the type
  //
  return this_a.changeType(type1);
}

// explicit instantiations
//
#ifndef ISIP_TEMPLATE_complex
template bool8
MMatrixMethods::sub<ISIP_TEMPLATE_TARGET, Byte, byte8>
(MMatrix<ISIP_TEMPLATE_TARGET>&, const MMatrix<Byte, byte8>&);

template bool8
MMatrixMethods::sub<ISIP_TEMPLATE_TARGET, Ushort, uint16>
(MMatrix<ISIP_TEMPLATE_TARGET>&, const MMatrix<Ushort, uint16>&);

template bool8
MMatrixMethods::sub<ISIP_TEMPLATE_TARGET, Ulong, uint32>
(MMatrix<ISIP_TEMPLATE_TARGET>&, const MMatrix<Ulong, uint32>&);

template bool8
MMatrixMethods::sub<ISIP_TEMPLATE_TARGET, Ullong, uint64>
(MMatrix<ISIP_TEMPLATE_TARGET>&, const MMatrix<Ullong, uint64>&);

template bool8
MMatrixMethods::sub<ISIP_TEMPLATE_TARGET, Short, int16>
(MMatrix<ISIP_TEMPLATE_TARGET>&, const MMatrix<Short, int16>&);

template bool8
MMatrixMethods::sub<ISIP_TEMPLATE_TARGET, Long, int32>
(MMatrix<ISIP_TEMPLATE_TARGET>&, const MMatrix<Long, int32>&);

template bool8
MMatrixMethods::sub<ISIP_TEMPLATE_TARGET, Llong, int64>
(MMatrix<ISIP_TEMPLATE_TARGET>&, const MMatrix<Llong, int64>&);

template bool8
MMatrixMethods::sub<ISIP_TEMPLATE_TARGET, Float, float32>
(MMatrix<ISIP_TEMPLATE_TARGET>&, const MMatrix<Float, float32>&);

template bool8
MMatrixMethods::sub<ISIP_TEMPLATE_TARGET, Double, float64>
(MMatrix<ISIP_TEMPLATE_TARGET>&, const MMatrix<Double, float64>&);
#endif

#ifdef ISIP_TEMPLATE_complex
template bool8
MMatrixMethods::sub<ISIP_TEMPLATE_TARGET, ComplexLong, complexlong>
(MMatrix<ISIP_TEMPLATE_TARGET>&, const MMatrix<ComplexLong, complexlong>&);

template bool8
MMatrixMethods::sub<ISIP_TEMPLATE_TARGET, ComplexFloat, complexfloat>
(MMatrix<ISIP_TEMPLATE_TARGET>&, const MMatrix<ComplexFloat, complexfloat>&);

template bool8
MMatrixMethods::sub<ISIP_TEMPLATE_TARGET, ComplexDouble, complexdouble>
(MMatrix<ISIP_TEMPLATE_TARGET>&, const MMatrix<ComplexDouble, complexdouble>&);
#endif

// method: sub
//
// arguments:
//  MMatrix<TScalar, TIntegral>& this: (output) class operand
//  const MMatrix<TScalar, TIntegral>& m1: (input) operand 1
//  const MMatrix<TAScalar, TAIntegral>& m2: (input) operand 2
//
// return: a bool8 value indicating status
//
// subtract the two argument matrices and store result in the current matrix
// for example:
//
//       [1 2 3]       [2 0 4]                    [-1  2 -1]
//  m1 = [4 5 6]  m2 = [0 6 0]  m_out = m1 - m2 = [ 4 -1  6]
//       [7 8 9]       [8 0 1]                    [-1  8  8]
//
// this method has evolved somewhat as our ability to efficiently
// copy and assign matrices has improved. this version implements
// some complicated logic to do things as efficiently as possible.
// the approach can best be summarized by the following flowchart and matrix:
//
// (1) special cases:
//      types are equal: process internal data directly for all types
//      one of the types is sparse: process internal data directly
//      one of the types is full: the result is always a full matrix
//      
// (2) other cases:
//      this matrix describes the type of the output matrix as a function
//      of the input types. For the operation c = a - b,
//      type1 is the type of a; type 2 is the type of b.
//
//    TYPE2 --------> FULL  DIAG  SYMM  LTRI  UTRI  SPRS
//    TYPE1 ->  FULL: full  full  full  full  full  full
//              DIAG: full  diag  symm  ltri  utri  sprs
//              SYMM: full  symm  symm  full  full  full
//              LTRI: full  ltri  full  ltri  full  full
//              UTRI: full  utri  full  full  utri  full
//              SPRS: full  sprs  full  full  full  sprs
//
// the code that implements each combination attempts to exploit the
// properties of the matrices as much as possible.
//
template<class TScalar, class TIntegral, class TAScalar, class TAIntegral>
bool8 MMatrixMethods::sub(MMatrix<TScalar, TIntegral>& this_a, 
			    const MMatrix<TScalar, TIntegral>& m1_a, 
			    const MMatrix<TAScalar, TAIntegral>& m2_a) {

  // check if the two input matrices have the dimensions
  //
  if (!m1_a.checkDimensions(m2_a))  {
    m1_a.debug(L"m1_a");
    m2_a.debug(L"m2_a");    
    return Error::handle(name(), L"sub", Error::ARG, __FILE__, __LINE__);
  }

  // declare local variables
  //
  int32 nrows = m1_a.nrows_d;
  int32 ncols = m2_a.ncols_d;
  Integral::MTYPE old_type = this_a.type_d;
  Integral::MTYPE type1 = m1_a.type_d;
  Integral::MTYPE type2 = m2_a.type_d;
  
  //---------------------------------------------------------------------------
  // special cases:
  //  in this section, we deal with special cases that share the same
  //  code structure.
  //---------------------------------------------------------------------------

  // if the two types are the same, we can simply operate on the storage
  // vectors directly
  //
  if (type1 == type2) {

    // type: FULL, DIAGONAL, SYMMETRIC, LOWER_TRIANGULAR, UPPER_TRIANGULAR
    //
    if ((type1 == Integral::FULL) ||
	(type1 == Integral::DIAGONAL) ||
	(type1 == Integral::SYMMETRIC) ||
	(type1 == Integral::LOWER_TRIANGULAR) ||
	(type1 == Integral::UPPER_TRIANGULAR)) {
      this_a.setDimensions(nrows, ncols, false, m1_a.type_d);
      this_a.m_d.sub(m1_a.m_d, m2_a.m_d);
    }

    // type: SPARSE
    //
    else {

      // set the output matrix to SPARSE
      //
      this_a.assign(m1_a, Integral::SPARSE);

      // loop through each element of the second argument
      //
      for (int32 index = 0; index < m2_a.m_d.length(); index++) {
	int32 row = m2_a.row_index_d(index);
	int32 col = m2_a.col_index_d(index);
        this_a.setValue(row, col, (TScalar)((TIntegral)(this_a.getValue(row, col) - m2_a.m_d(index))));
      }
    }
  }

  // if the first type is sparse, and the second type isn't sparse,
  // we assign the output type to FULL (except for DIAG), copy the elements
  // of the first, and then subtract elements of the second
  //
  else if ((type1 == Integral::SPARSE) && (type2 != Integral::SPARSE)) {

    // create a FULL matrix for all types except DIAGONAL, and zero it
    //
    if (type2 == Integral::DIAGONAL) {
      this_a.setDimensions(nrows, ncols, false, Integral::SPARSE);
    }
    else {
      this_a.setDimensions(nrows, ncols, false, Integral::FULL);
    }
    this_a.clear(Integral::RETAIN);
    
    // assign elements of the first sparse matrix
    //
    for (int32 index = 0; index < m1_a.m_d.length(); index++) {
	int32 row = m1_a.row_index_d(index);
	int32 col = m1_a.col_index_d(index);
	this_a.setValue(row, col, m1_a.m_d(index));
    }

    // subtract elements of the second matrix
    //
    for (int32 row = 0; row < nrows; row++) {

      // subtract the values
      //
      int32 start_col = m2_a.startColumn(row, this_a.type_d, type2);
      int32 stop_col = m2_a.stopColumn(row, this_a.type_d, type2);

      for (int32 col = start_col; col <= stop_col; col++) {
	this_a.setValue(row, col, (TScalar)((TIntegral)(this_a(row, col) - m2_a(row, col))));
      }
    }
  }

  // if the second type is sparse, and the first type isn't sparse,
  // we assign the output type to FULL (except for DIAGONAL), copy the
  // elements of the first, and then subtract elements of the second
  //
  else if ((type1 != Integral::SPARSE) && (type2 == Integral::SPARSE)) {

    // create a FULL matrix for all types except DIAGONAL, and zero it
    //
    if (m1_a.type_d == Integral::DIAGONAL) {
      this_a.assign(m1_a, Integral::SPARSE);
    }
    else {
      this_a.assign(m1_a, Integral::FULL);
    }
    
    // subtract elements of the second sparse matrix
    //
    for (int32 index = 0; index < m2_a.m_d.length(); index++) {
      int32 row = m2_a.row_index_d(index);
      int32 col = m2_a.col_index_d(index);
      this_a.setValue(row, col, (TScalar)((TIntegral)(this_a(row, col) - m2_a(row, col))));
    }
  }
    
  // if either type is FULL, we assign the output type to FULL,
  // copy the elements from the first, then subtract elements of the second
  //
  else if (type1 == Integral::FULL) {

    // create a FULL matrix through assignment
    //
    this_a.assign(m1_a, Integral::FULL);
    
    // subtract elements of the second matrix
    //
    for (int32 row = 0; row < nrows; row++) {

      // subtract the values
      //
      int32 start_col = m2_a.startColumn(row, this_a.type_d, type2);
      int32 stop_col = m2_a.stopColumn(row, this_a.type_d, type2);

      for (int32 col = start_col; col <= stop_col; col++) {
	this_a.setValue(row, col, (TScalar)(TIntegral)((this_a(row, col) - m2_a(row, col))));
      }
    }
  }

  else if (type2 == Integral::FULL) {

    // create a FULL matrix through assignment
    //
    this_a.assign(m1_a, Integral::FULL);
    
    // subtract elements of the second matrix
    //
    for (int32 row = 0; row < nrows; row++) {
      for (int32 col = 0; col < ncols; col++) {
	this_a.setValue(row, col, (TScalar)((TIntegral)(this_a(row, col) - m2_a(row, col))));
      }
    }
  }  

  //---------------------------------------------------------------------------
  // in this section of the code, we deal with the remaining cases where
  // the matrices are of different types, and some intelligent conversion
  // must be done.
  //---------------------------------------------------------------------------
  
  // type1: DIAGONAL
  //  the remaining types are SYMMETRIC and *_TRIANGULAR. 
  //  the output types follow the type of the second operand.
  //  the approach is to create a matrix, copy the diagonal values,
  //  and subtract the second operand.
  // 
  else if (type1 == Integral::DIAGONAL) {
    
    // set up the output matrix and assign the diagonal elements
    //
    this_a.setDimensions(nrows, ncols, false, type2);
    this_a.clear(Integral::RETAIN);
    this_a.setDiagonal(m1_a);

    // (1) subtract the diagonal for all
    //
    for (int32 row = 0; row < nrows; row++) {  
      this_a.m_d(this_a.index(row, row)) -= 
	(TIntegral)m2_a.m_d(m2_a.index(row, row));
    }        

    // (2) subtract the lower part for SYMMETRIC and LOWER
    //
    if ((type2 == Integral::SYMMETRIC) ||
	(type2 == Integral::LOWER_TRIANGULAR)) {
      for (int32 row = 0; row < nrows; row++) {  
	for (int32 col = 0; col < row; col++) {  
	  this_a.m_d(this_a.index(row, col)) -= 
	    (TIntegral)m2_a.m_d(m2_a.index(row, col));
	}
      }        
    }

    // (3) subtract the upper part for SYMMETRIC and UPPER
    //
    if (type2 == Integral::UPPER_TRIANGULAR) {
      for (int32 row = 0; row < nrows; row++) {  
	for (int32 col = row + 1; col < ncols; col++) {  
	  this_a.m_d(this_a.index(row, col)) -= 
	    (TIntegral)m2_a.m_d(m2_a.index(row, col));
	}        
      }
    }
  }
    
  // type2: SYMMETRIC, *_TRIANGULAR
  //  the remaining types are DIAGONAL, SYMMETRIC, and *_TRIANGULAR. 
  //  the output types vary with the input.
  //  the approach is to copy the values of the first operand,
  //  and subtract the values of the second operand.
  // 
  else {
    
    // set up the output matrix: a diagonal matrix preserves the type
    // of the input; all other types force a full matrix.
    //
    if ((type1 == Integral::SYMMETRIC) &&
	(type2 == Integral::DIAGONAL)) {
      this_a.assign(m1_a, Integral::SYMMETRIC);
    }
    if ((type1 == Integral::LOWER_TRIANGULAR) &&
	(type2 == Integral::DIAGONAL)) {
      this_a.assign(m1_a, Integral::LOWER_TRIANGULAR);
    }
    else if ((type1 == Integral::UPPER_TRIANGULAR) &&
	     (type2 == Integral::DIAGONAL)) {
      this_a.assign(m1_a, Integral::UPPER_TRIANGULAR);
    }
    else {
      this_a.assign(m1_a, Integral::FULL);
    }

    // subtract elements of the second matrix
    //
    for (int32 row = 0; row < nrows; row++) {

      // subtract the values
      //
      int32 start_col = m2_a.startColumn(row, this_a.type_d, type2);
      int32 stop_col = m2_a.stopColumn(row, this_a.type_d, type2);

      for (int32 col = start_col; col <= stop_col; col++) {
	this_a.m_d(this_a.index(row, col)) -= 
	  (TIntegral)m2_a.m_d(m2_a.index(row, col));
      }
    }
  }

  // restore the type
  //
  return this_a.changeType(old_type);
}

// explicit instantiations
//
#ifndef ISIP_TEMPLATE_complex
template bool8
MMatrixMethods::sub<ISIP_TEMPLATE_TARGET, Byte, byte8>
(MMatrix<ISIP_TEMPLATE_TARGET>&, const MMatrix<ISIP_TEMPLATE_TARGET>&,
 const MMatrix<Byte, byte8>&);

template bool8
MMatrixMethods::sub<ISIP_TEMPLATE_TARGET, Ushort, uint16>
(MMatrix<ISIP_TEMPLATE_TARGET>&, const MMatrix<ISIP_TEMPLATE_TARGET>&,
 const MMatrix<Ushort, uint16>&);

template bool8
MMatrixMethods::sub<ISIP_TEMPLATE_TARGET, Ulong, uint32>
(MMatrix<ISIP_TEMPLATE_TARGET>&, const MMatrix<ISIP_TEMPLATE_TARGET>&,
 const MMatrix<Ulong, uint32>&);

template bool8
MMatrixMethods::sub<ISIP_TEMPLATE_TARGET, Ullong, uint64>
(MMatrix<ISIP_TEMPLATE_TARGET>&, const MMatrix<ISIP_TEMPLATE_TARGET>&,
 const MMatrix<Ullong, uint64>&);

template bool8
MMatrixMethods::sub<ISIP_TEMPLATE_TARGET, Short, int16>
(MMatrix<ISIP_TEMPLATE_TARGET>&, const MMatrix<ISIP_TEMPLATE_TARGET>&,
 const MMatrix<Short, int16>&);

template bool8
MMatrixMethods::sub<ISIP_TEMPLATE_TARGET, Long, int32>
(MMatrix<ISIP_TEMPLATE_TARGET>&, const MMatrix<ISIP_TEMPLATE_TARGET>&,
 const MMatrix<Long, int32>&);

template bool8
MMatrixMethods::sub<ISIP_TEMPLATE_TARGET, Llong, int64>
(MMatrix<ISIP_TEMPLATE_TARGET>&, const MMatrix<ISIP_TEMPLATE_TARGET>&,
 const MMatrix<Llong, int64>&);

template bool8
MMatrixMethods::sub<ISIP_TEMPLATE_TARGET, Float, float32>
(MMatrix<ISIP_TEMPLATE_TARGET>&, const MMatrix<ISIP_TEMPLATE_TARGET>&,
 const MMatrix<Float, float32>&);

template bool8
MMatrixMethods::sub<ISIP_TEMPLATE_TARGET, Double, float64>
(MMatrix<ISIP_TEMPLATE_TARGET>&, const MMatrix<ISIP_TEMPLATE_TARGET>&,
 const MMatrix<Double, float64>&);
#endif

#ifdef ISIP_TEMPLATE_complex
template bool8
MMatrixMethods::sub<ISIP_TEMPLATE_TARGET, ComplexLong, complexlong>
(MMatrix<ISIP_TEMPLATE_TARGET>&, const MMatrix<ISIP_TEMPLATE_TARGET>&,
 const MMatrix<ComplexLong, complexlong>&);

template bool8
MMatrixMethods::sub<ISIP_TEMPLATE_TARGET, ComplexFloat, complexfloat>
(MMatrix<ISIP_TEMPLATE_TARGET>&, const MMatrix<ISIP_TEMPLATE_TARGET>&,
 const MMatrix<ComplexFloat, complexfloat>&);

template bool8
MMatrixMethods::sub<ISIP_TEMPLATE_TARGET, ComplexDouble, complexdouble>
(MMatrix<ISIP_TEMPLATE_TARGET>&, const MMatrix<ISIP_TEMPLATE_TARGET>&,
 const MMatrix<ComplexDouble, complexdouble>&);
#endif

// method: mult
//
// arguments:
//  MMatrix<TScalar, TIntegral>& this: (output) class operand
//  const MMatrix<TScalar, TIntegral>& m1: (input) operand 1
//  const MMatrix<TAScalar, TAIntegral>& m2: (input) operand 2
//
// return: a bool8 value indicating status
//
// this method multiplies two matrices, then assign result to the
// current matrix
// for example:
//
//       [1 2 3]       [2 0 4]                    [11 12  7]
//  m1 = [4 5 6]  m2 = [0 6 0]  m_out = m1 * m2 = [26 30 22]
//       [7 8 9]       [3 0 1]                    [41 48 37]
//
template<class TScalar, class TIntegral, class TAScalar, class TAIntegral>
bool8 MMatrixMethods::mult(MMatrix<TScalar, TIntegral>& this_a, 
			     const MMatrix<TScalar, TIntegral>& m1_a, 
			     const MMatrix<TAScalar, TAIntegral>& m2_a) {

  // if the current matrix is same as one operand, a copy to temporary matrix
  // of that operand is needed
  //
  if (&this_a == &m1_a) {
    MMatrix<TScalar, TIntegral> tmp(this_a);
    return this_a.mult(tmp, m2_a) ;
  }
  else if ((void*)&this_a == (void*)&m2_a) {
    MMatrix<TScalar, TIntegral> tmp(this_a);
    return this_a.mult(m1_a, tmp);
  }

  // check dimensions
  //
  if (m1_a.getNumColumns() != m2_a.getNumRows()) {
    m1_a.debug(L"m1_a");    
    m2_a.debug(L"m2_a");    
    return Error::handle(name(), L"mult", m2_a.ERR_DIM, __FILE__, __LINE__);
  }

  // get the type of two matrices and branch on type
  //
  Integral::MTYPE old_type = this_a.type_d;
  int32 nrows = m1_a.getNumRows();
  int32 ncols = m2_a.getNumColumns();
  Integral::MTYPE type1 = m1_a.getType();
  Integral::MTYPE type2 = m2_a.getType();

  // type1: FULL
  //
  if (type1 == Integral::FULL) {

    // type2: DIAGONAL
    //  set the type of output matrix as full, and multiply the elements in
    //  the first matrix with the diagonal elements in the second matrix which
    //  has the same column index
    //
    if (type2 == Integral::DIAGONAL) {
      
      // create space in the output matrix
      //
      this_a.setDimensions(nrows, ncols, false, Integral::FULL);
      
      // loop over elements and multiply
      //
      for (int32 row = 0; row < nrows; row++) {
        for (int32 col = 0; col < ncols; col++) {
          this_a.m_d(this_a.index(row, col)) =
	    (TIntegral)m1_a.m_d(m1_a.index(row, col)) *
            (TIntegral)m2_a.m_d(col);
        }
      }
    }

    // type2: FULL, SYMMETRIC, LOWER_TRIAGULAR, UPPER_TRIANGULAR
    //  set the type of output matrix as full, and multiply row of first
    //  matrix by the column of the second matrix - multiply elements in
    //  the given row of the first matrix with the elements in the given
    //  column of the second matrix
    //
    else if ((type2 == Integral::FULL) ||
	     (type2 == Integral::SYMMETRIC) ||
	     (type2 == Integral::LOWER_TRIANGULAR) ||
	     (type2 == Integral::UPPER_TRIANGULAR)) {

      // create space in the output matrix
      //
      this_a.setDimensions(nrows, ncols, false, Integral::FULL);
      
      // loop over all elements
      //
      for (int32 row = 0; row < nrows; row++) {
        for (int32 col = 0; col < ncols; col++) {  
          this_a.m_d(this_a.index(row, col)) = 
            this_a.multiplyRowByColumn(m1_a, m2_a, row, col);
        }
      }
    }

    // type2: SPARSE
    //  set the type of output matrix as full. 
    //
    else if (type2 == Integral::SPARSE) {

      // create space in the output matrix
      //
      this_a.setDimensions(nrows, ncols, false, Integral::FULL);
      this_a.clear(Integral::RETAIN);
       
      // declare local variables
      //
      int32 b_row;
      int32 b_col;
      TIntegral b_val;
      TIntegral c_val = 0;
      TIntegral sub_val = 0;
      int32 length = m2_a.m_d.length();

      // loop over the length of the vector of sparse matrix
      //
      for (int32 b_index = 0; b_index < length; b_index++) {

	// get row index, column index and value from sparse matrix
	//
        b_row = m2_a.row_index_d(b_index);
        b_col = m2_a.col_index_d(b_index);
        b_val = m2_a.m_d(b_index);

	// get the number of rows
	//
        int32 a_rows = m1_a.getNumRows();

	// loop through the number of rows and multiply
	//
        for (int32 a_index = 0; a_index < a_rows; a_index++) {
          c_val = this_a.getValue(a_index, b_col);
          sub_val = b_val * m1_a.getValue(a_index, b_row);
          this_a.setValue(a_index, b_col, c_val + sub_val);
        }
      }
    }
  }

  // type1: DIAGONAL
  //
  else if (type1 == Integral::DIAGONAL) {

    // type2: DIAGONAL
    //  if both matrices are diagonal ones, return a diagonal matrix and
    //  assign the products of the diagonal elements of the two input matrices
    //  to the output
    //
    if (type2 == Integral::DIAGONAL) {

      // create space in the output matrix
      //
      this_a.setDimensions(nrows, nrows, false, Integral::DIAGONAL);

      // loop over each diagonal element and multiply
      //
      for (int32 row = 0; row < nrows; row++) {
        this_a.m_d(row) = (TIntegral)m1_a.m_d(row) * (TIntegral)m2_a.m_d(row);
      }
    }

    // type2: FULL
    //  set the output matrix as full, and multiply the diagonal elements
    //  of the first matrix with the elements which has the same row index.
    //
    else if (type2 == Integral::FULL) {

      // create space in the output matrix
      //
      this_a.setDimensions(nrows, ncols, false, Integral::FULL);

      // loop over the elements and multiply
      //
      for (int32 row = 0; row < nrows; row++) {
        for (int32 col = 0; col < ncols; col++) {
          this_a.m_d(this_a.index(row, col)) =
	    (TIntegral)(m1_a.m_d(row)) *
	    (TIntegral)(m2_a.m_d(m2_a.index(row, col)));
        }
      }
    }

    // type2: SYMMETRIC
    //  set output matrix as symmetric, and multiply the diagonal elements
    //  of the first matrix to the symmetric matrix, for elements in the
    //  upper triangle of the symmetric matrix, use its symmetric value.
    //
    else if (type2 == Integral::SYMMETRIC) {

      // create space in the output matrix
      //
      this_a.setDimensions(nrows, ncols, false, Integral::FULL);
      
      // loop over the elements and multiply
      //      
      for (int32 row = 0; row < nrows; row++) {
	for (int32 col = 0; col < row; col++) {
          this_a.m_d(this_a.index(row, col)) =
	    (TIntegral)(m1_a.m_d(row)) *
	    (TIntegral)(m2_a.m_d(m2_a.index(row, col)));
        }
        for (int32 col = row; col < ncols; col++) {
          this_a.m_d(this_a.index(row, col)) =
	    (TIntegral)(m1_a.m_d(row)) *
	    (TIntegral)(m2_a.m_d(m2_a.index(col, row)));
        }
      }
    }

    // type2: LOWER_TRIANGULAR
    //  set the type of output matrix as lower triangular, and then 
    //  multiply the diagonal elements with the corresponding elements in
    //  the lower triangle.
    //
    else if (type2 == Integral::LOWER_TRIANGULAR) {

      // create space in the output matrix
      //
      this_a.setDimensions(nrows, nrows, false, Integral::LOWER_TRIANGULAR);
      
      // loop over the elements and multiply
      //      
      for (int32 row = 0; row < nrows; row++) {
        for (int32 col = 0; col <= row; col++) {
          this_a.m_d(this_a.index(row, col)) =
	    (TIntegral)(m1_a.m_d(row)) *
            (TIntegral)(m2_a.m_d(m2_a.index(row, col)));
        }
      }
    }

    // type2: UPPER_TRIANGULAR
    //  set the type of matrix as upper triangular, and multiply the diagonal
    //  elements with the corresponding elements in the upper triangle
    //
    else if (type2 == Integral::UPPER_TRIANGULAR) {

      // create space in the output matrix
      //
      this_a.setDimensions(nrows, nrows, false, Integral::UPPER_TRIANGULAR);
      
      // loop over the elements and multiply
      //      
      for (int32 row = 0; row < nrows; row++) {
        for (int32 col = row; col < nrows; col++) {
          this_a.m_d(this_a.index(row, col)) =
	    (TIntegral)(m1_a.m_d(row))*
            (TIntegral)(m2_a.m_d(m2_a.index(row, col)));
        }
      }
    }

    // type2: SPARSE
    //  set the type of output matrix as sparse. the general idea here is
    //  that we change sparse to full matrix, after finishing computation,
    //  we will change it to sparse matrix.
    //
    else if (type2 == Integral::SPARSE) {

      // create space in the output matrix
      //
      this_a.setDimensions(nrows, ncols, false, Integral::FULL);
      this_a.clear(Integral::RETAIN);
      
      // get the number of rows of diagonal matrix and the length of the
      // vector for sparse matrix
      //
      int32 len1 = m1_a.getNumRows();
      int32 len2 = m2_a.m_d.length();

      // declare local variables
      //
      int32 row2 = 0;
      int32 col2 = 0;
      TAIntegral val2 = 0;
      TIntegral val1 = 0;

      // loop over rows of the diagonal matrix
      //
      for (int32 row1 = 0; row1 < len1; row1++) {

	// get the element on the diagonal vector
	//
        val1 = m1_a.m_d(row1);

	// loop over the vector of sparse matrix
	//
        for (int32 index = 0; index < len2; index++) {

	  // get the row index, column index and value
	  //
          row2 = m2_a.row_index_d(index);
          col2 = m2_a.col_index_d(index);
          val2 = m2_a.m_d(index);
          
          // if the row index matches with position of diag vector
          // elements, multiply them
          //
          if (row2 == row1) {
            this_a.setValue(row1, col2, (TIntegral)(val1 * val2));
          }
        }
      }

      // now change type to sparse
      //
      this_a.changeType(Integral::SPARSE);
    }
  }

  // type1: SYMMETRIC
  //
  else if (type1 == Integral::SYMMETRIC) {

    // type2: DIAGONAL
    //  set the type of output matrix as full.
    //
    if (type2 ==  Integral::DIAGONAL) {

      // create space in the output matrix
      //
      this_a.setDimensions(nrows, ncols, false, Integral::FULL);
      
      // loop through the elements and multiply
      //
      for (int32 row = 0; row < nrows; row++) {
        for (int32 col = 0; col < row; col++) {
          this_a.m_d(this_a.index(row, col)) =
	    (TIntegral)(m2_a.m_d(col)) *
            (TIntegral)(m1_a.m_d(m1_a.index(row, col)));
        }
        for (int32 col = row; col < ncols; col++) {
          this_a.m_d(this_a.index(row, col)) =
	    (TIntegral)(m2_a.m_d(col)) *
            (TIntegral)(m1_a.m_d(m1_a.index(col, row)));
        }
      }
    }

    // type2: FULL, SYMMETRIC, LOWER_TRIANGULAR, UPPER_TRIANGULAR
    //  set the type of output matrix as full, and multiply elements in the
    //  given row of the first matrix with the elements in the given column
    //  of the second matrix.
    //
    else if ((type2 == Integral::FULL) ||
	     (type2 == Integral::SYMMETRIC) ||
	     (type2 == Integral::LOWER_TRIANGULAR) ||
	     (type2 == Integral::UPPER_TRIANGULAR)) {

      // create space in the output matrix
      //
      this_a.setDimensions(nrows, ncols, false, Integral::FULL);
      
      // loop through over elements
      //      
      for (int32 row = 0; row < nrows; row++) {
        for (int32 col = 0; col < ncols; col++) {  
          this_a.m_d(this_a.index(row, col)) = 
            this_a.multiplyRowByColumn(m1_a, m2_a, row, col);
        }
      }      
    }

    // type2: SPARSE
    //  set the type of output matrix as full. 
    //
    else if (type2 == Integral::SPARSE) {

      // create space in the output matrix
      //
      this_a.setDimensions(nrows, ncols, false, Integral::FULL);
      this_a.clear(Integral::RETAIN);
       
      // declare local variables
      //
      int32 b_row;
      int32 b_col;
      TIntegral b_val;
      TIntegral c_val = 0;
      TIntegral sub_val = 0;
      int32 length = m2_a.m_d.length();

      // loop over the values of the sparse matrix and multiply
      //
      for (int32 b_index = 0; b_index < length; b_index++) {
        b_row = m2_a.row_index_d(b_index);
        b_col = m2_a.col_index_d(b_index);
        b_val = m2_a.m_d(b_index);

        // get the number of rows of the first operand
	//
        int32 a_rows = m1_a.getNumRows();
        
        for (int32 a_index = 0; a_index < a_rows; a_index++) {
          c_val = this_a.getValue(a_index, b_col);
          sub_val = b_val * m1_a.getValue(a_index, b_row);
          this_a.setValue(a_index, b_col, c_val + sub_val);
        }
      }
    }
  }

  // type1: LOWER_TRIANGULAR
  //
  else if (type1 == Integral::LOWER_TRIANGULAR) {

    // type2: DIAGONAL
    //  set the type of output matrix as full.
    //
    if (type2 ==  Integral::DIAGONAL) {

      // create space in the output matrix
      //
      this_a.setDimensions(m1_a, false, m1_a.type_d);
      
      // loop over each element
      //
      for (int32 row = 0; row < nrows; row++) {
        for (int32 col = 0; col <= row; col++) {
          this_a.m_d(this_a.index(row, col)) =
	    (TIntegral)(m2_a.m_d(col)) *
            (TIntegral)(m1_a.m_d(m1_a.index(row, col)));
        }
      }
    }

    // type2: FULL, SYMMETRIC, LOWER_TRIANGULAR, UPPER_TRIANGULAR
    //  set the type of output matrix as full, and multiply elements in the
    //  given row of the first matrix with the elements in the given column
    //  of the second matrix.
    //
    else if ((type2 == Integral::FULL) ||
	     (type2 == Integral::SYMMETRIC) ||
	     (type2 == Integral::LOWER_TRIANGULAR) ||
      	     (type2 == Integral::UPPER_TRIANGULAR)) {

      // create space in the output matrix
      //
      this_a.setDimensions(nrows, ncols, false, Integral::FULL);
      
      // loop over all elements
      //
      for (int32 row = 0; row < nrows; row++) {
        for (int32 col = 0; col < ncols; col++) {  
          this_a.m_d(this_a.index(row, col)) = 
            this_a.multiplyRowByColumn(m1_a, m2_a, row, col);
        }
      }      
    }

    // type2: SPARSE
    //  set the type of output matrix as full.
    //
    else if (type2 == Integral::SPARSE) {

      // create space in the output matrix
      //      
      this_a.setDimensions(nrows, ncols, false, Integral::FULL);
      this_a.clear(Integral::RETAIN);
       
      // declare local variables
      //
      int32 b_row;
      int32 b_col;
      TIntegral b_val;
      TIntegral c_val = 0;
      TIntegral sub_val = 0;
      int32 length = m2_a.m_d.length();

      // loop over the elements of sparse matrix, get the row index,
      // column index and value of the element, then multiply it with
      // corresponding element in the first matrix
      //
      for (int32 b_index = 0; b_index < length; b_index++) {
        b_row = m2_a.row_index_d(b_index);
        b_col = m2_a.col_index_d(b_index);
        b_val = m2_a.m_d(b_index);
        int32 a_rows = m1_a.getNumRows();
        for (int32 a_index = 0; a_index < a_rows; a_index++) {
          c_val = this_a.getValue(a_index, b_col);
          sub_val = b_val * m1_a.getValue(a_index, b_row);
          this_a.setValue(a_index, b_col, c_val + sub_val);
        }
      }
    }    
  }

  // type1: UPPER_TRIANGULAR
  //
  else if (type1 == Integral::UPPER_TRIANGULAR) {

    // type2: DIAGONAL
    //  set the type of output matrix as full.
    //
    if (type2 ==  Integral::DIAGONAL) {

      // create space in the output matrix
      //
      this_a.setDimensions(m1_a, false, m1_a.type_d);
      
      // loop over each element
      //
      for (int32 row = 0; row < nrows; row++) {
        for (int32 col = row; col < nrows; col++) {
          this_a.m_d(this_a.index(row, col)) =
	    (TIntegral)(m2_a.m_d(col))*
            (TIntegral)(m1_a.m_d(m1_a.index(row, col)));
        }
      }
    }

    // type2: FULL, SYMMETRIC, LOWER_TRIANGULAR, UPPER_TRIANGULAR
    //  set the type of output matrix as full.
    //
    else if ((type2 == Integral::FULL) ||
	     (type2 == Integral::SYMMETRIC) ||
	     (type2 == Integral::LOWER_TRIANGULAR) ||
      	     (type2 == Integral::UPPER_TRIANGULAR)) {

      // create space in the output matrix
      //
      this_a.setDimensions(nrows, ncols, false, Integral::FULL);
      
      // multiply elements in the given row of the first matrix with the
      // elements in the given column of the second matrix
      //
      for (int32 row = 0; row < nrows; row++) {
        for (int32 col = 0; col < ncols; col++) {  
          this_a.m_d(this_a.index(row, col)) = 
            this_a.multiplyRowByColumn(m1_a, m2_a, row, col);
        }
      }      
    }

    // type2: SPARSE
    //  set the type of output matrix as full.
    //
    else if (type2 == Integral::SPARSE) {

      // create space in the output matrix
      //      
      this_a.setDimensions(nrows, ncols, false, Integral::FULL);
      
      // clear the contents of the current matrix
      //
      this_a.clear(Integral::RETAIN);
       
      // declare local variables
      //
      int32 b_row;
      int32 b_col;
      TIntegral b_val;
      TIntegral c_val = 0;
      TIntegral sub_val = 0;
      int32 length = m2_a.m_d.length();

      // loop over the elements of sparse matrix, get the row index,
      // column index and value of the element, then multiply it with
      // corresponding element in the first matrix
      //
      for (int32 b_index = 0; b_index < length; b_index++) {
        b_row = m2_a.row_index_d(b_index);
        b_col = m2_a.col_index_d(b_index);
        b_val = m2_a.m_d(b_index);
        int32 a_rows = m1_a.getNumRows();
        for (int32 a_index = 0; a_index < a_rows; a_index++) {
          c_val = this_a.getValue(a_index, b_col);
          sub_val = b_val * m1_a.getValue(a_index, b_row);
          this_a.setValue(a_index, b_col, c_val + sub_val);
        }
      }
    }    
  }

  // type1: SPARSE
  //
  else if (type1 == Integral::SPARSE) {

    // type2: DIAGONAL
    //  set the type of output matrix as sparse
    //
    if (type2 == Integral::DIAGONAL) {

      // create space in the output matrix
      //      
      this_a.setDimensions(nrows, ncols, false, Integral::FULL);
      this_a.clear(Integral::RETAIN);

      // declare local variables
      //
      int32 row1 = 0;
      int32 col1 = 0;
      TIntegral val2 = 0;
      TAIntegral val1 = 0;
      
      // get the number of rows of the second matrix and the length of
      // vector of sparse matrix
      //
      int32 len2 = m2_a.getNumRows();
      int32 len1 = m1_a.m_d.length();

      // loop over the number of rows of second matrix
      //
      for (int32 row2 = 0; row2 < len2; row2++) {
        val2 = m2_a.m_d(row2);
        for (int32 index = 0; index < len1; index++) {
          row1 = m1_a.row_index_d(index);
          col1 = m1_a.col_index_d(index);
          val1 = m1_a.m_d(index);

          // if the row index matches with position of diag vector
          // elements, multiply them
          //
          if (row2 == col1) {
            this_a.setValue(row1, row2, (TIntegral)val1 * val2);
          }
        }
      }

      // result should be sparse matrix
      //
      this_a.changeType(Integral::SPARSE);
    }

    // type2: FULL, SYMMETRIC, LOWER_TRIANGULAR, UPPER_TRIANGULAR
    //  set the type of output matrix as full
    //
    else if ((type2 == Integral::FULL) ||
	     (type2 == Integral::SYMMETRIC) ||
	     (type2 == Integral::LOWER_TRIANGULAR) ||
      	     (type2 == Integral::UPPER_TRIANGULAR)) {


      // create space in the output matrix
      //
      this_a.setDimensions(nrows, ncols, false, Integral::FULL);
      this_a.clear(Integral::RETAIN);
       
      // declare local variables
      //
      int32 a_row;
      int32 a_col;
      TIntegral a_val;
      TIntegral c_val = 0;
      TIntegral sub_val = 0;
      int32 length = m1_a.m_d.length();

      // loop over the values of the sparse matrix
      //
      for (int32 a_index = 0; a_index < length; a_index++) {

	// get the row index, column index and value
	//
        a_row = m1_a.row_index_d(a_index);
        a_col = m1_a.col_index_d(a_index);
        a_val = m1_a.m_d(a_index);

	// rows of second matrix should be the same as the columns in
	// the second matrix
	//
        int32 b_row = a_col;
        int32 b_cols = m2_a.getNumColumns();

        // loop over the columns of the second matrix
	//
        for (int32 b_index = 0; b_index < b_cols; b_index++) {
          c_val = this_a.getValue(a_row, b_index);
          sub_val = (TIntegral)a_val *
	    (TIntegral)m2_a.getValue(b_row, b_index);
          this_a.setValue(a_row, b_index, c_val + sub_val);
        }
      }
    }

    // type2: SPARSE
    //  set the type of output matrix as sparse
    //
    else if (type2 == Integral::SPARSE) {

      // temporary matrix is required
      //
      MMatrix<TScalar, TIntegral> temp(nrows, ncols);
      temp.clear(Integral::RETAIN);

      // temporary variables
      //
      int32 row;
      int32 col;
      TIntegral value;
      
      // loop over elements of the first matrix
      //
      for (int32 i = 0; i < m1_a.m_d.length(); i++) {
        
        // loop over elements of second matrix
        //
        for (int32 j = 0; j < m2_a.m_d.length(); j++) {
          
          // compare the respective column and row indices
          //
          if (m1_a.col_index_d(i) == m2_a.row_index_d(j)) {
            
            // multiply the elements and store them in a temporary matrix
            //
            row = m1_a.row_index_d(i);
            col = m2_a.col_index_d(j);
            value = temp.getValue(row, col) +
              (TIntegral)m1_a.m_d(i) * (TIntegral)m2_a.m_d(j);
            temp.setValue(row, col, value);
          }
        }
      }

      // copy the result to the current matrix
      //
      this_a.assign(temp, Integral::SPARSE);
    }
  }

  // restore the type
  //
  return this_a.changeType(old_type);
}

// explicit instantiations
//
#ifndef ISIP_TEMPLATE_complex
template bool8
MMatrixMethods::mult<ISIP_TEMPLATE_TARGET, Byte, byte8>
(MMatrix<ISIP_TEMPLATE_TARGET>&, const MMatrix<ISIP_TEMPLATE_TARGET>&,
 const MMatrix<Byte, byte8>&);

template bool8
MMatrixMethods::mult<ISIP_TEMPLATE_TARGET, Ushort, uint16>
(MMatrix<ISIP_TEMPLATE_TARGET>&, const MMatrix<ISIP_TEMPLATE_TARGET>&,
 const MMatrix<Ushort, uint16>&);

template bool8
MMatrixMethods::mult<ISIP_TEMPLATE_TARGET, Ulong, uint32>
(MMatrix<ISIP_TEMPLATE_TARGET>&, const MMatrix<ISIP_TEMPLATE_TARGET>&,
 const MMatrix<Ulong, uint32>&);

template bool8
MMatrixMethods::mult<ISIP_TEMPLATE_TARGET, Ullong, uint64>
(MMatrix<ISIP_TEMPLATE_TARGET>&, const MMatrix<ISIP_TEMPLATE_TARGET>&,
 const MMatrix<Ullong, uint64>&);

template bool8
MMatrixMethods::mult<ISIP_TEMPLATE_TARGET, Short, int16>
(MMatrix<ISIP_TEMPLATE_TARGET>&, const MMatrix<ISIP_TEMPLATE_TARGET>&,
 const MMatrix<Short, int16>&);

template bool8
MMatrixMethods::mult<ISIP_TEMPLATE_TARGET, Long, int32>
(MMatrix<ISIP_TEMPLATE_TARGET>&, const MMatrix<ISIP_TEMPLATE_TARGET>&,
 const MMatrix<Long, int32>&);

template bool8
MMatrixMethods::mult<ISIP_TEMPLATE_TARGET, Llong, int64>
(MMatrix<ISIP_TEMPLATE_TARGET>&, const MMatrix<ISIP_TEMPLATE_TARGET>&,
 const MMatrix<Llong, int64>&);

template bool8
MMatrixMethods::mult<ISIP_TEMPLATE_TARGET, Float, float32>
(MMatrix<ISIP_TEMPLATE_TARGET>&, const MMatrix<ISIP_TEMPLATE_TARGET>&,
 const MMatrix<Float, float32>&);

template bool8
MMatrixMethods::mult<ISIP_TEMPLATE_TARGET, Double, float64>
(MMatrix<ISIP_TEMPLATE_TARGET>&, const MMatrix<ISIP_TEMPLATE_TARGET>&,
 const MMatrix<Double, float64>&);
#endif

#ifdef ISIP_TEMPLATE_complex
template bool8
MMatrixMethods::mult<ISIP_TEMPLATE_TARGET, ComplexLong, complexlong>
(MMatrix<ISIP_TEMPLATE_TARGET>&, const MMatrix<ISIP_TEMPLATE_TARGET>&,
 const MMatrix<ComplexLong, complexlong>&);

template bool8
MMatrixMethods::mult<ISIP_TEMPLATE_TARGET, ComplexFloat, complexfloat>
(MMatrix<ISIP_TEMPLATE_TARGET>&, const MMatrix<ISIP_TEMPLATE_TARGET>&,
 const MMatrix<ComplexFloat, complexfloat>&);

template bool8
MMatrixMethods::mult<ISIP_TEMPLATE_TARGET, ComplexDouble, complexdouble>
(MMatrix<ISIP_TEMPLATE_TARGET>&, const MMatrix<ISIP_TEMPLATE_TARGET>&,
 const MMatrix<ComplexDouble, complexdouble>&);
#endif

// method: multiplyRowByColumn
//
// arguments:
//  const MMatrix<TScalar, TIntegral>& this: (output) class operand
//  const MMatrix<TScalar, TIntegral>& m1: (input) operand 1
//  const MMatrix<TAScalar, TAIntegral>& m2: (input) operand 2
//  int32 row: (input) row index in m1
//  int32 col: (input) column address in m2
//
// return: a TIntegral value that results from multiplying the specified row
// by the specified column
//
// this method is designed for the multiplication of full, symmetric,
// lower and upper triangular matrices
//
template<class TScalar, class TIntegral, class TAScalar, class TAIntegral>
TIntegral
MMatrixMethods::multiplyRowByColumn(const MMatrix<TScalar, TIntegral>& this_a, 
				    const MMatrix<TScalar, TIntegral>& m1_a, 
				    const MMatrix<TAScalar, TAIntegral>& m2_a,
				    int32 row_a, int32 col_a) {

  // declare local variables
  //
  TIntegral sum = 0;
  
  // get the number of columns of the first matrix
  // 
  int32 last_index = m1_a.getNumColumns();

  // get the type of the two matrices and branch on type
  //
  Integral::MTYPE type1 = m1_a.getType();
  Integral::MTYPE type2 = m2_a.getType();

  // type1: FULL
  //
  if (type1 == Integral::FULL) {

    // type2: FULL
    //
    if (type2 == Integral::FULL) {
      
      // compute the dot product
      //  
      for (int32 index = 0; index < last_index; index++) {
        sum += (TIntegral)m1_a.m_d(m1_a.index(row_a, index)) *
          (TIntegral)m2_a.m_d(m2_a.index(index, col_a));
      }      
    }

    // type2: SYMMETRIC
    //  multiply each element in the given row of the first matrix
    //  with the elements in the corresponding column of the second matrix
    //
    else if (type2 == Integral::SYMMETRIC) {
      
      // loop through the upper triangular elements of the second matrix
      //
      for (int32 index = 0; index < col_a; index++) {
        sum += (TIntegral)m1_a.m_d(m1_a.index(row_a, index)) *
          (TIntegral)m2_a.m_d(m2_a.index(col_a, index));
      }

      // loop through the lower triangular elements of the second matrix
      for (int32 index = col_a; index < last_index; index++) {
        sum += (TIntegral)m1_a.m_d(m1_a.index(row_a, index)) *
          (TIntegral)m2_a.m_d(m2_a.index(index, col_a));
      }
    }

    // type2: LOWER_TRIANGULAR
    //  multiply the lower triangular elements in the given column of
    //  the second matrix with the corresponding elements in the
    //  given row of the first matrix
    //
    else if (type2 == Integral::LOWER_TRIANGULAR) {
      for (int32 index = col_a; index < last_index; index++) {
        sum += (TIntegral)m1_a.m_d(m1_a.index(row_a, index)) *
          (TIntegral)m2_a.m_d(m2_a.index(index, col_a));
      }    
    }

    // type2: UPPER_TRIANGULAR
    //  multiply the upper triangular elements in the given column of
    //  the second matrix with the corresponding elements in the
    //  given row of the first matrix
    //      
    else if (type2 == Integral::UPPER_TRIANGULAR) {
      for (int32 index = 0; index <= col_a; index++) {
        sum += (TIntegral)m1_a.m_d(m1_a.index(row_a, index)) *
          (TIntegral)m2_a.m_d(m2_a.index(index, col_a));
      }    
    }
  }

  // type1: SYMMETRIC
  //
  else if (type1 == Integral::SYMMETRIC) {

    // type2: FULL
    //  multiply each elements in the given row of the first matrix with
    //  the elements in the corresponding column of the second matrix
    // 
    if (type2 == Integral::FULL) {  
      for (int32 index = 0; index < row_a; index++) {
        sum += (TIntegral)m1_a.m_d(m1_a.index(row_a, index)) *
          (TIntegral)m2_a.m_d(m2_a.index(index, col_a));
      }      
      for (int32 index = row_a; index < last_index; index++) {
        sum += (TIntegral)m1_a.m_d(m1_a.index(index, row_a)) *
          (TIntegral)m2_a.m_d(m2_a.index(index, col_a));
      }    
    }

    // type2: SYMMETRIC
    //  multiply each elements in the given row of the first matrix with
    //  the elements in the corresponding column of the second matrix.
    //  the code needs to be separated into several loops to make sure when
    //  a upper triangle element is needed, its symmetric value will be used
    // 
    else if (type2 == Integral::SYMMETRIC) {

      if (row_a > col_a) {
	for (int32 index = 0; index < col_a; index++) {
          sum += (TIntegral)m1_a.m_d(m1_a.index(row_a, index)) *
            (TIntegral)m2_a.m_d(m2_a.index(col_a, index));
        }
        for (int32 index = col_a; index < row_a; index++) {
          sum += (TIntegral)m1_a.m_d(m1_a.index(row_a, index)) *
            (TIntegral)m2_a.m_d(m2_a.index(index, col_a));
        }       
        for (int32 index = row_a; index < last_index; index++) {
          sum += (TIntegral)m1_a.m_d(m1_a.index(index, row_a)) *
            (TIntegral)m2_a.m_d(m2_a.index(index, col_a));
        }
      }

      else {
        for (int32 index = 0; index < row_a; index++) {
          sum += (TIntegral)m1_a.m_d(m1_a.index(row_a, index)) *
            (TIntegral)m2_a.m_d(m2_a.index(col_a, index));
        }
        for (int32 index = row_a; index < col_a; index++) {
          sum += (TIntegral)m1_a.m_d(m1_a.index(index, row_a)) *
            (TIntegral)m2_a.m_d(m2_a.index(col_a, index));
        }               
        for (int32 index = col_a; index < last_index; index++) {
          sum += (TIntegral)m1_a.m_d(m1_a.index(index, row_a)) *
            (TIntegral)m2_a.m_d(m2_a.index(index, col_a));
        }
      }
    }

    // type2: LOWER_TRIANGULAR
    //  multiply the elements in the lower triangle of the second matrix with
    //  its corresponding elements in the first matrix
    //
    else if (type2 == Integral::LOWER_TRIANGULAR) {

      if (row_a > col_a) {      
        for (int32 index = col_a; index < row_a; index++) {
          sum += (TIntegral)m1_a.m_d(m1_a.index(row_a, index)) *
            (TIntegral)m2_a.m_d(m2_a.index(index, col_a));
        }       
        
        for (int32 index = row_a; index < last_index; index++) {
          sum += (TIntegral)m1_a.m_d(m1_a.index(index, row_a)) *
            (TIntegral)m2_a.m_d(m2_a.index(index, col_a));
        }
      }      

      else {
        for (int32 index = col_a; index < last_index; index++) {
          sum += (TIntegral)m1_a.m_d(m1_a.index(index, row_a)) *
            (TIntegral)m2_a.m_d(m2_a.index(index, col_a));
        }
      }
    }

    // type2: UPPER_TRIANGULAR
    //  multiply the elements in the upper triangle of the second matrix with
    //  its corresponding elements in the first matrix
    //
    else if (type2 == Integral::UPPER_TRIANGULAR) {

      if (row_a < col_a) {      
        for (int32 index = 0; index < row_a; index++) {
          sum += (TIntegral)m1_a.m_d(m1_a.index(row_a, index)) *
            (TIntegral)m2_a.m_d(m2_a.index(index, col_a));
        }       
        
        for (int32 index = row_a; index <= col_a; index++) {
          sum += (TIntegral)m1_a.m_d(m1_a.index(index, row_a)) *
            (TIntegral)m2_a.m_d(m2_a.index(index, col_a));
        }
      }

      else {
        for (int32 index = 0; index <= col_a; index++) {
          sum += (TIntegral)m1_a.m_d(m1_a.index(row_a, index)) *
            (TIntegral)m2_a.m_d(m2_a.index(index, col_a));
        }
      }
    }
  }

  // type1: LOWER_TRIANGULAR
  //
  else if (type1 == Integral::LOWER_TRIANGULAR) {

    // type2: FULL
    //  multiply each element in the given row (and in the lower
    //  triangle) of the first matrix with its corresponding one in
    //  the given column of the second matrix, return the summation
    //  of the products
    //        
    if (type2 == Integral::FULL) {
      for (int32 index = 0; index <= row_a; index++) {
        sum += (TIntegral)m1_a.m_d(m1_a.index(row_a, index)) *
          (TIntegral)m2_a.m_d(m2_a.index(index, col_a));
      }      
    }

    // type2: SYMMETRIC
    //  multiply each elements in the given row (and in the lower
    //  triangle) of the first matrix with its corresponding one (if
    //  it's in the upper triangle, use its symmetric value) in the
    //  given column of the second matrix, return the summation of
    //  the products
    //
    else if (type2 == Integral::SYMMETRIC) {

      if (row_a > col_a) {      
        for (int32 index = 0; index < col_a; index++) {
          sum += (TIntegral)m1_a.m_d(m1_a.index(row_a, index)) *
            (TIntegral)m2_a.m_d(m2_a.index(col_a, index));
        }
        
        for (int32 index = col_a; index <= row_a; index++) {
          sum += (TIntegral)m1_a.m_d(m1_a.index(row_a, index)) *
            (TIntegral)m2_a.m_d(m2_a.index(index, col_a));
        }
      }
      
      else {
        for (int32 index = 0; index <= row_a; index++) {
          sum += (TIntegral)m1_a.m_d(m1_a.index(row_a, index)) *
            (TIntegral)m2_a.m_d(m2_a.index(col_a, index));
        }
      }
    }

    // type2: LOWER_TRIANGULAR
    //  multiply the elements in lower triangle
    //
    else if (type2 == Integral::LOWER_TRIANGULAR) {

      if (row_a >= col_a) {     
        for (int32 index = col_a; index <= row_a; index++) {
          sum += (TIntegral)m1_a.m_d(m1_a.index(row_a, index)) *
            (TIntegral)m2_a.m_d(m2_a.index(index, col_a));
        }
      }

      // result will be zero for elements in the upper triangular part
      //
      else {
        sum = (TIntegral)(0);
      }      
    }

    // type: UPPER_TRIANGULAR
    //
    else if (type2 == Integral::UPPER_TRIANGULAR) {

      int32 end_index = (row_a < col_a) ? row_a : col_a;
      for (int32 index = 0; index <= end_index; index++) {
	sum += (TIntegral)m1_a.m_d(m1_a.index(row_a, index)) *
	  (TIntegral)m2_a.m_d(m2_a.index(index, col_a));
      }
    }
  }

  // type1: UPPER_TRIANGULAR
  //
  else if (type1 == Integral::UPPER_TRIANGULAR) {

    // type2: FULL
    //  multiply each element in the given row (and in the lower triangle)
    //  of the first matrix with its corresponding one in the given column
    //  of the second matrix, return the summation of the products
    //
    if (type2 == Integral::FULL) {  
      for (int32 index = row_a; index < last_index; index++) {
        sum += (TIntegral)m1_a.m_d(m1_a.index(row_a, index)) *
          (TIntegral)m2_a.m_d(m2_a.index(index, col_a));
      }      
    }

    // type2: SYMMETRIC
    //  multiply each element in the given row (and in the lower triangle)
    //  of the first matrix with its corresponding one (if it's in the upper
    //  triangle, use its symmetric value) in the given column
    //  of the second matrix, return the summation of the products
    // 
    else if (type2 == Integral::SYMMETRIC) {

      if (row_a < col_a) {      
        for (int32 index = row_a; index < col_a; index++) {
          sum += (TIntegral)m1_a.m_d(m1_a.index(row_a, index)) *
            (TIntegral)m2_a.m_d(m2_a.index(col_a, index));
        }
        
        for (int32 index = col_a; index < last_index; index++) {
          sum += (TIntegral)m1_a.m_d(m1_a.index(row_a, index)) *
            (TIntegral)m2_a.m_d(m2_a.index(index, col_a));
        }
      }

      else {
        for (int32 index = row_a; index < last_index; index++) {
          sum += (TIntegral)m1_a.m_d(m1_a.index(row_a, index)) *
            (TIntegral)m2_a.m_d(m2_a.index(col_a, index));
        }
      }
    }

    // type2: LOWER_TRIANGULAR
    //
    else if (type2 == Integral::LOWER_TRIANGULAR) {

      // find the start index
      //
      int32 start_index = (row_a > col_a) ? row_a : col_a;
      for (int32 index = start_index; index < last_index; index++) {
	sum += (TIntegral)m1_a.m_d(m1_a.index(row_a, index)) *
	  (TIntegral)m2_a.m_d(m2_a.index(index, col_a));
      }
    }

    // type2: UPPER_TRIANGULAR
    //
    else if (type2 == Integral::UPPER_TRIANGULAR) {

      // multiply upper triangular elements
      //
      if (row_a <= col_a) {     
        for (int32 index = row_a; index <= col_a; index++) {
          sum += (TIntegral)m1_a.m_d(m1_a.index(row_a, index)) *
            (TIntegral)m2_a.m_d(m2_a.index(index, col_a));
        }
      }

      // multiplication will be zero for lower triangular elements
      //
      else {
        sum = (TIntegral)(0);
      }      
    }
  }

  // exit gracefully
  //
  return sum;
}

// explicit instantiations
//
#ifndef ISIP_TEMPLATE_complex
template ISIP_TEMPLATE_T1
MMatrixMethods::multiplyRowByColumn<ISIP_TEMPLATE_TARGET, Byte, byte8>
(const MMatrix<ISIP_TEMPLATE_TARGET>&, const MMatrix<ISIP_TEMPLATE_TARGET>&,
 const MMatrix<Byte, byte8>&, int32, int32);

template ISIP_TEMPLATE_T1
MMatrixMethods::multiplyRowByColumn<ISIP_TEMPLATE_TARGET, Ushort, uint16>
(const MMatrix<ISIP_TEMPLATE_TARGET>&, const MMatrix<ISIP_TEMPLATE_TARGET>&,
 const MMatrix<Ushort, uint16>&, int32, int32);

template ISIP_TEMPLATE_T1
MMatrixMethods::multiplyRowByColumn<ISIP_TEMPLATE_TARGET, Ulong, uint32>
(const MMatrix<ISIP_TEMPLATE_TARGET>&, const MMatrix<ISIP_TEMPLATE_TARGET>&,
 const MMatrix<Ulong, uint32>&, int32, int32);

template ISIP_TEMPLATE_T1
MMatrixMethods::multiplyRowByColumn<ISIP_TEMPLATE_TARGET, Ullong, uint64>
(const MMatrix<ISIP_TEMPLATE_TARGET>&, const MMatrix<ISIP_TEMPLATE_TARGET>&,
 const MMatrix<Ullong, uint64>&, int32, int32);

template ISIP_TEMPLATE_T1
MMatrixMethods::multiplyRowByColumn<ISIP_TEMPLATE_TARGET, Short, int16>
(const MMatrix<ISIP_TEMPLATE_TARGET>&, const MMatrix<ISIP_TEMPLATE_TARGET>&,
 const MMatrix<Short, int16>&, int32, int32);

template ISIP_TEMPLATE_T1
MMatrixMethods::multiplyRowByColumn<ISIP_TEMPLATE_TARGET, Long, int32>
(const MMatrix<ISIP_TEMPLATE_TARGET>&, const MMatrix<ISIP_TEMPLATE_TARGET>&,
 const MMatrix<Long, int32>&, int32, int32);

template ISIP_TEMPLATE_T1
MMatrixMethods::multiplyRowByColumn<ISIP_TEMPLATE_TARGET, Llong, int64>
(const MMatrix<ISIP_TEMPLATE_TARGET>&, const MMatrix<ISIP_TEMPLATE_TARGET>&,
 const MMatrix<Llong, int64>&, int32, int32);

template ISIP_TEMPLATE_T1
MMatrixMethods::multiplyRowByColumn<ISIP_TEMPLATE_TARGET, Float, float32>
(const MMatrix<ISIP_TEMPLATE_TARGET>&, const MMatrix<ISIP_TEMPLATE_TARGET>&,
 const MMatrix<Float, float32>&, int32, int32);

template ISIP_TEMPLATE_T1
MMatrixMethods::multiplyRowByColumn<ISIP_TEMPLATE_TARGET, Double, float64>
(const MMatrix<ISIP_TEMPLATE_TARGET>&, const MMatrix<ISIP_TEMPLATE_TARGET>&,
 const MMatrix<Double, float64>&, int32, int32);
#endif

#ifdef ISIP_TEMPLATE_complex
template ISIP_TEMPLATE_T1
MMatrixMethods::multiplyRowByColumn<ISIP_TEMPLATE_TARGET, ComplexLong, complexlong>
(const MMatrix<ISIP_TEMPLATE_TARGET>&, const MMatrix<ISIP_TEMPLATE_TARGET>&,
 const MMatrix<ComplexLong, complexlong>&, int32, int32);

template ISIP_TEMPLATE_T1
MMatrixMethods::multiplyRowByColumn<ISIP_TEMPLATE_TARGET, ComplexFloat, complexfloat>
(const MMatrix<ISIP_TEMPLATE_TARGET>&, const MMatrix<ISIP_TEMPLATE_TARGET>&,
 const MMatrix<ComplexFloat, complexfloat>&, int32, int32);

template ISIP_TEMPLATE_T1
MMatrixMethods::multiplyRowByColumn<ISIP_TEMPLATE_TARGET, ComplexDouble, complexdouble>
(const MMatrix<ISIP_TEMPLATE_TARGET>&, const MMatrix<ISIP_TEMPLATE_TARGET>&,
 const MMatrix<ComplexDouble, complexdouble>&, int32, int32);
#endif

// method: isTypePossible
//
// arguments:
//  const MMatrix<TScalar, TIntegral>& this: (output) class operand
//  Integral::MTYPE type: (input) new matrix type 
//
// return: a bool8 value indicating status
//
// this method is used to check if it is possible to change the current
// matrix into the given type
//
template<class TScalar, class TIntegral>
bool8 MMatrixMethods::isTypePossible(const MMatrix<TScalar, 
				       TIntegral>& this_a,
				       Integral::MTYPE type_a) {

  // declare local variables
  //
  int32 len;
  
  // if the current type is the same as input type, exit and return true
  //
  if (this_a.type_d == type_a) {
    return true;
  }

  // a diagonal matrix can be changed into anything, a sparse or full
  // matrix can accept anything.
  //
  if ((this_a.type_d == Integral::DIAGONAL) ||
      (type_a == Integral::SPARSE) ||
      (type_a == Integral::FULL)) {
    return true;
  }

  // type1: FULL
  // 
  else if (this_a.type_d == Integral::FULL) {

    // FULL -> type2: DIAGONAL
    //  it is allowed to change type when
    //  (1) matrix is square
    //  (2) non-diagonal elements are zeros
    //
    if (type_a == Integral::DIAGONAL) {

      // a diagonal matrix must be square
      //
      if (!this_a.isSquare()) {
        return false;
      }

      // loop through each element
      //
      for (int32 row = 0; row < this_a.nrows_d; row++) {
        for (int32 col = 0; col < this_a.nrows_d; col++) {

	  // check if a non-diagonal element is zero
	  //
	  if ((row != col) && (this_a.getValue(row, col) != 0)) {
            return false;
          }
        }
      }
    }

    // FULL -> type2: SYMMETRIC
    //  it is allowed to change type when
    //   (1) matrix is square;
    //   (2) matrix has symmetric characteristic
    //
    else if (type_a == Integral::SYMMETRIC) {      

      // a symmetric matrix must be square
      //
      if (!this_a.isSquare()) {
        return false;
      }

      // check for symmetry
      //
      for (int32 row = 0; row < this_a.nrows_d; row++) {
        for (int32 col = 0; col < row; col++) {
          if ((this_a.getValue(row, col)) != (this_a.getValue(col, row))) {
            return false;
          }
        }
      }
    }

    // FULL -> type2: LOWER_TRIANGULAR
    //  it is allowed to change type when
    //   (1) matrix is square
    //   (2) upper triangular elements are zeros
    //
    else if (type_a == Integral::LOWER_TRIANGULAR) {

      // a lower-triangular matrix must be square
      //
      if (!this_a.isSquare()) {
        return false;
      }

      // loop through the upper triangular elements
      //
      for (int32 row = 0; row < this_a.nrows_d; row++) {
        for (int32 col = row + 1; col < (int32)(this_a.nrows_d) - 1; col++) {
          if (this_a.getValue(row, col) != 0) {
            return false;
          }
        }
      }
    }

    // FULL -> type2: UPPER_TRIANGULAR
    //  it is allowed to change type when
    //   (1) matrix is square
    //   (2) lower triangular elements are zeros
    //
    else if (type_a == Integral::UPPER_TRIANGULAR) {

      // an upper-triangular matrix must be square
      //
      if (!this_a.isSquare()) {
        return false;
      }

      // loop through the lower triangular elements
      //
      for (int32 row = 1; row < this_a.nrows_d; row++) {
        for (int32 col = 0; col < row; col++) {
          if (this_a.getValue(row, col) != 0) {
            return false;
          }
        }
      }
    }
  }

  // type1: SYMMETRIC, LOWER_TRIANGULAR
  //  they are allowed to change to symmetric, triangular, diagonal only if
  //  they are diagonal matrix themselves. the general idea here is that we
  //  loop through all non-diagonal elements to determine if they are zeros
  //  or not.
  //
  else if ((this_a.type_d == Integral::SYMMETRIC) ||
	   (this_a.type_d == Integral::LOWER_TRIANGULAR)) {

    // check if all non-diagonal elements are zeros
    //
    if ((type_a == Integral::DIAGONAL) ||
	(type_a == Integral::LOWER_TRIANGULAR) ||
	(type_a == Integral::UPPER_TRIANGULAR) ||
	(type_a == Integral::SYMMETRIC)) {

      for (int32 row = 0; row < this_a.nrows_d; row++) {
        for (int32 col = 0; col < row; col++) {
          if (this_a.getValue(row, col) != 0) {
            return false;
          }
        }
      }
    }
  }

  // type1: UPPER_TRIANGULAR
  //  they are allowed to change to symmetric, lower triangular, diagonal
  //  only if they are diagonal matrix themselves. the general idea here
  //  is that we loop through all non-diagonal elements to determine if
  //  they are zeros or not.
  //  
  else if (this_a.type_d == Integral::UPPER_TRIANGULAR) {

    // check if all non-diagonal elements are zeros
    //
    if ((type_a == Integral::DIAGONAL) ||
	(type_a == Integral::LOWER_TRIANGULAR) ||
	(type_a == Integral::SYMMETRIC)) {

      for (int32 row = 0; row < this_a.nrows_d; row++) {
        for (int32 col = (int32)(this_a.ncols_d) - 1; col > row; col--) {
          if (this_a.getValue(row, col) != 0) {
            return false;
          }
        }
      }
    }
  }

  // type1: SPARSE
  //
  else if (this_a.type_d == Integral::SPARSE) {

    // SPARSE -> type2: DIAGONAL
    //  it is allowed only if
    //   (1) matrix is square
    //   (2) all non-diagonal elements are zeros
    //
    if (type_a == Integral::DIAGONAL) {
      if (!this_a.isSquare()) {
	return false;
      }

      // loop through each sparse element
      //
      len = this_a.m_d.length();
      for (int32 i = 0; i < len; i++) {
	if (this_a.row_index_d(i) != this_a.col_index_d(i)) {
	  return false;
	}
      }
    }

    // SPARSE -> type2: SYMMETRIC
    //  it is allowed only if
    //   (1) matrix is square
    //   (2) matrix is symmetric itself
    //
    else if (type_a == Integral::SYMMETRIC) {      
      if (!this_a.isSquare()) {
	return false;
      }

      // loop through each sparse element
      //
      len = this_a.m_d.length();	
      for (int32 i = 0; i < len; i++) {
	TIntegral value = this_a.m_d(i);
	int32 row = this_a.row_index_d(i);
	int32 col = this_a.col_index_d(i);
	
	if (value != this_a.getValue(col, row)) {
	  return false;
	}
      }
    }

    // SPARSE -> type2: LOWER_TRIANGULAR
    //  it is allowed only if
    //   (1) matrix is square
    //   (2) the upper triangle elements are all zeros
    //
    else if (type_a == Integral::LOWER_TRIANGULAR) {
      if (!this_a.isSquare()) {
	return false;
      }

      // loop through each sparse element
      //
      len = this_a.m_d.length();
      for (int32 i = 0; i < len; i++) {
	if (this_a.row_index_d(i) < this_a.col_index_d(i)) {
	  return false;
	}
      }
    }

    // SPARSE -> type2: UPPER_TRIANGULAR
    //  it is allowed only if
    //   (1) matrix is square
    //   (2) the lower triangle elements are all zeros
    //
    else if (type_a == Integral::UPPER_TRIANGULAR) {
      if (!this_a.isSquare()) {
	return false;
      }

      // loop through each sparse element
      //
      len = this_a.m_d.length();
      for (int32 i = 0; i < len; i++) {
	if (this_a.row_index_d(i) > this_a.col_index_d(i)) {
	  return false;
	}
      }
    }
  }
    
  // exit gracefully: it is possible to change the type
  //
  return true;
}

// explicit instantiations
//
template bool8
MMatrixMethods::isTypePossible<ISIP_TEMPLATE_TARGET>
(const MMatrix<ISIP_TEMPLATE_TARGET>&, Integral::MTYPE);

// method: isIdentity
//
// arguments:
//  const MMatrix<TScalar, TIntegral>& this: (output) class operand
//
// return: a bool8 value indicating status
//
// this method is used to check if the matrix is an identity matrix
//
template<class TScalar, class TIntegral>
bool8 MMatrixMethods::isIdentity(const MMatrix<TScalar, TIntegral>& this_a) {

  // check the dimension of the current matrix
  //
  if ((int32)(this_a.nrows_d) <= 0) {
    return false;
  }
     
  // type: DIAGONAL
  //  check whether all diagonal elements are equal to 1
  //
  if (this_a.type_d == Integral::DIAGONAL) {
    return this_a.m_d.eq((TIntegral)1);
  }

  // type: FULL
  //
  else if (this_a.type_d == Integral::FULL) {
    
    // check if the current matrix is square
    //
    if (this_a.nrows_d != this_a.ncols_d) {
      return false;
    }
    
    // check if every element of the current matrix matches the identity matrix
    //
    for (int32 i = 0; i < this_a.nrows_d; i++) {
      for (int32 j =  0; j < this_a.ncols_d; j++) {

	// non-diagonal elements should be zero
	//
	if (i != j) {
	  if (!(this_a.getValue(i, j) == 0)) {
	    return false;
	  }
	}

	// diagonal elements should be one
	//
	else {
	  if (!(this_a.getValue(i, j) == 1)) {
	    return false;
	  }
	}
      }
    }
  }

  // type: SYMMETRIC, LOWER_TRIANGULAR
  //  loop through each lower triangular element
  //
  else if ((this_a.type_d == Integral::SYMMETRIC) ||
	   (this_a.type_d == Integral::LOWER_TRIANGULAR)) {
    
    // check every elements of current matrix to match identity matrix
    //
    for (int32 i = 0; i < this_a.nrows_d; i++) {
      for (int32 j =  0; j <= i; j++) {

	// non-diagonal elements should be zero
	//	
	if (i != j) {
	  if (!(this_a.getValue(i, j) == 0)) {
	    return false;
	  }
	}

	// all the diagonal elements should be equal to one
	//
	else {
	  if (!(this_a.getValue(i, j) == 1)) {
	    return false;
	  }
	}
      }
    }
  }

  // type: UPPER_TRIANGULAR
  //
  else if (this_a.type_d == Integral::UPPER_TRIANGULAR) {
    
    // check if every element of current matrix matches the identity matrix
    //
    for (int32 i = 0; i < this_a.nrows_d; i++) {
      for (int32 j =  i; j < this_a.ncols_d; j++) {

	// non-diagonal elements should be zero
	//
	if (i != j) {
	  if (!(this_a.getValue(i, j) == 0)) {
	    return false;
	  }
	}
	
	// diagonal elements should be one
	//
	else {
	  if (!(this_a.getValue(i, j) == 1)) {
	    return false;
	  }
	}
      }
    }
  }
  
  // type: SPARSE
  //
  else if (this_a.type_d == Integral::SPARSE) {

    // check if the current matrix is square
    //
    if (this_a.nrows_d != this_a.ncols_d) {
      return false;
    }

    // check all the diagonal elements
    //
    for (int32 i = 0; i < this_a.ncols_d; i++) {

      // diagonal elements should be 1
      //
      if ((this_a.row_index_d(i) != i) || (this_a.col_index_d(i) != i) ||
	  (this_a.m_d(i) != (TIntegral)1)) {
	return false;
      }
    }
  }

  // exit gracefully: it is an identity matrix
  //
  return true;
}

// explicit instantiations
//
template bool8
MMatrixMethods::isIdentity<ISIP_TEMPLATE_TARGET>
(const MMatrix<ISIP_TEMPLATE_TARGET>&);

// method: isOrthogonal
//
// arguments:
//  const MMatrix<TScalar, TIntegral>& this: (output) class operand
//
// return: a bool8 value indicating status
//
// this method is used to check if the current matrix is orthogonal -
// for this AA' = A'A = I (where A' = transpose(A))
//
template<class TScalar, class TIntegral>
bool8 MMatrixMethods::isOrthogonal(const MMatrix<TScalar,
				     TIntegral>& this_a) {

  // an orthogonal matrix must be square
  //
  if (!this_a.isSquare()) {
    return false;
  }

  // create a temporary matrix
  //
  MMatrix<TScalar, TIntegral> tmp(this_a);

  // transpose the MMatrix
  //
  MMatrix<TScalar, TIntegral> transp(this_a);
  transp.transpose();

  // compute AA'
  //
  tmp.mult(transp);

  // check whether the result is an identity matrix
  //
  if (!tmp.isIdentity()) {
    return false;
  }

  // compute A'A
  //
  transp.mult(this_a);

  // check whether the result is an identity matrix
  //
  return transp.isIdentity();
}

// explicit instantiations
//
template bool8
MMatrixMethods::isOrthogonal<ISIP_TEMPLATE_TARGET>
(const MMatrix<ISIP_TEMPLATE_TARGET>&);
