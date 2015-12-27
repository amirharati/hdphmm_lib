// file: $isip/class/math/matrix/MMatrix/mmat_06.cc
// version: $Id: mmat_06.cc 7816 2002-02-27 20:54:30Z alphonso $
//

// isip include files
//
#include "MMatrixMethods.h"
#include "MMatrix.h"

// method: gt
//
// arguments:
//  const MMatrix<TScalar, TIntegral>& this: (output) class operand
//  TIntegral value: (input) operand
//
// return: a bool8 value of true if all elements in the matrix are
//         greater than value
//
// this method checks if all the elements in the current matrix are
// greater than the input value
//
template<class TScalar, class TIntegral>
bool8 MMatrixMethods::gt(const MMatrix<TScalar, TIntegral>& this_a, 
			   TIntegral value_a) {

  // type: FULL, SYMMETRIC
  //  call the vector gt method for all the elements
  //
  if ((this_a.type_d == Integral::FULL) ||
      (this_a.type_d == Integral::SYMMETRIC)) {
    return this_a.m_d.gt(value_a);
  }

  // type: DIAGONAL, LOWER_TRIANGULAR, UPPER_TRIANGULAR
  //  check if the value being compared is less than 0 and if the non-zero
  //  elements in the matrix are greater than the input value
  //
  else if ((this_a.type_d == Integral::DIAGONAL) ||
	   (this_a.type_d == Integral::LOWER_TRIANGULAR) ||
	   (this_a.type_d == Integral::UPPER_TRIANGULAR)) {

    // if the dimensions of one matrix are greater than 1, there must
    // be zero elements in this matrix because its type is diagonal or
    // triangular. the zero element(s) is obviously less than the input
    // value if the input value is greater than zero. Thus,
    // gt method should always return false in this situation
    //
    // note that the cast to float64 prevents a compiler warning.
    //
    if ((int32)(this_a.nrows_d) > 1) {

#ifndef ISIP_TEMPLATE_unsigned    
      if ((TIntegral)0 <= value_a) {
#endif

	return false;

#ifndef ISIP_TEMPLATE_unsigned
      }
#endif      
    }

    // call the vector gt method for all the valid (diagonal, for diagonal
    // matrix, or triangular, for triangular matrix) elements in the matrix
    //    
    return this_a.m_d.gt(value_a);
  }

  // type: SPARSE
  //  check if the value being compared is less than 0 and if the non-zero
  //  elements in the matrix are greater than the input value
  //
  else {

    // see if we have any zero elements
    //
    if (this_a.numEqual(0) > 0) {
      
#ifndef ISIP_TEMPLATE_unsigned    
      if ((TIntegral)0 <= value_a) {
#endif	

        return false;

#ifndef ISIP_TEMPLATE_unsigned    
      }
#endif
    }

    // make sure all of the non-zero elements pass
    //
    return this_a.m_d.gt(value_a);
  }
}

// explicit instantiations
//
template bool8
MMatrixMethods::gt<ISIP_TEMPLATE_TARGET>
(const MMatrix<ISIP_TEMPLATE_TARGET>&, ISIP_TEMPLATE_T1);

// method: lt
//
// arguments:
//  const MMatrix<TScalar, TIntegral>& this: (output) class operand
//  TIntegral value: (input) operand
//
// return: a bool8 value of true if all elements in the matrix are
//         less than value
//
// this method checks if all the elements in the current matrix are
// less than the input value
//
template<class TScalar, class TIntegral>
bool8 MMatrixMethods::lt(const MMatrix<TScalar, TIntegral>& this_a, 
			   TIntegral value_a) {

  // type: FULL, SYMMETRIC
  //  call the vector gt method for all the elements
  //
  if ((this_a.type_d == Integral::FULL) ||
      (this_a.type_d == Integral::SYMMETRIC)) {
    return this_a.m_d.lt(value_a);
  }

  // type: DIAGONAL, LOWER_TRIANGULAR, UPPER_TRIANGULAR
  //  check if the value being compared is greater than 0 and if the non-zero
  //  elements are less than the input value
  //
  else if ((this_a.type_d == Integral::DIAGONAL) ||
	   (this_a.type_d == Integral::LOWER_TRIANGULAR) ||
	   (this_a.type_d == Integral::UPPER_TRIANGULAR)) {

    // if the dimensions of one matrix are greater than 1, there must
    // be zero elements in this matrix because its type is diagonal or
    // triangular. the zero element(s) is obviously greater than or equal
    // to the input value if the input value is less than or equal to zero.
    // Thus, lt method should always return false in this situation
    //
    if ((TIntegral)(this_a.nrows_d) > 1) {
      if ((TIntegral)0 >= (TIntegral)value_a) {
	return false;
      }
    }

    // call the vector lt method for all the valid (diagonal, for diagonal
    // matrix, or triangular, for triangular matrix) elements in the matrix
    //        
    return this_a.m_d.lt(value_a);
  }

  // type: SPARSE
  //  for sparse matrix check if the value being compared is greater than 0
  //  and if the non-zero elements in the matrix are less than the input value
  //
  else {

    // see if we have any zero elements
    //
    if (this_a.numEqual(0) > 0) {
      if ((TIntegral)0 >= (TIntegral)value_a) {
        return false;
      }
    }

    // only check for non-zero elements
    //
    return this_a.m_d.lt(value_a);
  }
}

// explicit instantiations
//
template bool8
MMatrixMethods::lt<ISIP_TEMPLATE_TARGET>
(const MMatrix<ISIP_TEMPLATE_TARGET>&, ISIP_TEMPLATE_T1);

// method: ge
//
// arguments:
//  const MMatrix<TScalar, TIntegral>& this: (output) class operand
//  TIntegral value: (input) operand
//
// return: a bool8 value of true if all elements in the matrix are
//         greater than or equal to value
//
// this method checks if all the elements in the current matrix are
// greater or equal in value to the input value
//
template<class TScalar, class TIntegral>
bool8 MMatrixMethods::ge(const MMatrix<TScalar, TIntegral>& this_a, 
			   TIntegral value_a) {

  // type: FULL, SYMMETRIC
  //  call the vector ge method for all the elements
  //
  if ((this_a.type_d == Integral::FULL) ||
      (this_a.type_d == Integral::SYMMETRIC)) {
    return this_a.m_d.ge(value_a);
  }

  // type: DIAGONAL, LOWER_TRIANGULAR, UPPER_TRIANGULAR
  //  check if the value being compared is greater than 0 and if the non-zero
  //  elements are greater than the input value
  //
  else if ((this_a.type_d == Integral::DIAGONAL) ||
	   (this_a.type_d == Integral::LOWER_TRIANGULAR) ||
	   (this_a.type_d == Integral::UPPER_TRIANGULAR)) {
    
    // if the dimensions of one matrix are greater than 1, there must
    // be zero elements in this matrix because its type is diagonal or
    // triangular. the zero element(s) is obviously less than the input
    // value if the input value is greater than zero. Thus, ge method
    // should always return false in this situation
    //
    if ((TIntegral)(this_a.nrows_d) > 1) {
      if ((TIntegral)0 < (TIntegral)value_a) {
	return false;
      }
    }

    // call the vector ge method for all the valid (diagonal, for diagonal
    // matrix, or triangular, for triangular matrix) elements in the matrix
    //            
    return this_a.m_d.ge(value_a);
  }

  // type: SPARSE
  //  for sparse matrix, check the non-zero values only
  //  
  else {

    // see if we have any zero elements
    //
    if (this_a.numEqual(0) > 0) {
      if ((TIntegral)0 < (TIntegral)value_a) {
        return false;
      }
    }

    // make sure all of the non-zero elements pass
    //
    return this_a.m_d.ge(value_a);
  }
}

// explicit instantiations
//
template bool8
MMatrixMethods::ge<ISIP_TEMPLATE_TARGET>
(const MMatrix<ISIP_TEMPLATE_TARGET>&, ISIP_TEMPLATE_T1);

// method: le
//
// arguments:
//  const MMatrix<TScalar, TIntegral>& this: (output) class operand
//  TIntegral value: (input) operand
//
// return: a bool8 value of true if all elements in the matrix are
//         less than or equal to value
//
// this method checks if all elements in the current matrix are less than
// or equal to the input value
//
template<class TScalar, class TIntegral>
bool8 MMatrixMethods::le(const MMatrix<TScalar, TIntegral>& this_a, 
			   TIntegral value_a) {

  // type: FULL, SYMMETRIC
  //  call the vector le method for all the elements
  //
  if ((this_a.type_d == Integral::FULL) ||
      (this_a.type_d == Integral::SYMMETRIC)) {
    return this_a.m_d.le(value_a);
  }

  // type: DIAGONAL, LOWER_TRIANGULAR, UPPER_TRIANGULAR
  //  check if the value is less than 0 and if the non-zero elements are
  //  less than the input value
  //
  else if ((this_a.type_d == Integral::DIAGONAL) ||
	   (this_a.type_d == Integral::LOWER_TRIANGULAR) ||
	   (this_a.type_d == Integral::UPPER_TRIANGULAR)) {

    // if the dimensions of one matrix are greater than 1, there must
    // be zero elements in this matrix because its type is diagonal or
    // triangular. the zero element(s) is obviously greater than the input
    // value if the input value is less than zero. Thus, le method
    // should always return false in this situation
    //
#ifndef ISIP_TEMPLATE_unsigned
    if ((TIntegral)(this_a.nrows_d) > 1) {
      if ((TIntegral)0 > value_a) {
	return false;
      }
    }
#endif

    // call the vector le method for all the valid (diagonal, for diagonal
    // matrix, or triangular, for triangular matrix) elements in the matrix
    //
    return this_a.m_d.le(value_a);
  }

  // type: SPARSE
  //  for sparse matrix only check the non-zero values
  //    
  else {

    // see if we have any zero elements
    //

#ifndef ISIP_TEMPLATE_unsigned    
    if (this_a.numEqual(0) > 0) {
      if ((TIntegral)0 > value_a) {
        return false;
      }
    }
#endif
    
    // make sure all of the non-zero elements pass
    //
    return this_a.m_d.le(value_a);
  }
}

// explicit instantiations
//
template bool8
MMatrixMethods::le<ISIP_TEMPLATE_TARGET>
(const MMatrix<ISIP_TEMPLATE_TARGET>&, ISIP_TEMPLATE_T1);

// method: eq
//
// arguments:
//  const MMatrix<TScalar, TIntegral>& this: (output) class operand
//  TIntegral value: (input) operand
//
// return: a bool8 value of true if all elements in the matrix are
//         equal to value
//
// this method checks if all elements in the current matrix are equal to
// the input value
//
template<class TScalar, class TIntegral>
bool8 MMatrixMethods::eq(const MMatrix<TScalar, TIntegral>& this_a, 
			   TIntegral value_a) {

  // type: FULL, SYMMETRIC
  //  call the vector eq method for all the elements
  //
  if ((this_a.type_d == Integral::FULL) ||
      (this_a.type_d == Integral::SYMMETRIC)) {
    return this_a.m_d.eq(value_a);
  }

  // type: DIAGONAL, LOWER_TRIANGULAR, UPPER_TRIANGULAR
  //  test for diagonal, lower and upper triangular matrix
  //
  else if ((this_a.type_d == Integral::DIAGONAL) ||
	   (this_a.type_d == Integral::LOWER_TRIANGULAR) ||
	   (this_a.type_d == Integral::UPPER_TRIANGULAR)) {

    // if the dimensions of one matrix are greater than 1, there must
    // be zero elements in this matrix because its type is diagonal or
    // triangular. the zero element(s) is obviously not equal to the input
    // value if the input value is not zero. Thus, eq method should
    // always return false in this situation
    //
    if ((TIntegral)(this_a.nrows_d) > 1) {
      if ((TIntegral)0 != value_a) {
	return false;
      }
    }

    // call the vector eq method for all the valid (diagonal, for diagonal
    // matrix, or triangular, for triangular matrix) elements in the matrix
    //    
    return this_a.m_d.eq(value_a);
  }

  // type: SPARSE
  //  for sparse matrix only check the non-zero values
  //
  else {

    // if we have any zero elements, then the value_a must be 0
    //
    if (this_a.numEqual(0) > 0) {
      if ((TIntegral)0 != value_a) {
        return false;
      }
    }

    // make sure all of the non-zero elements pass
    //
    return this_a.m_d.eq(value_a);
  }
}

// explicit instantiations
//
template bool8
MMatrixMethods::eq<ISIP_TEMPLATE_TARGET>
(const MMatrix<ISIP_TEMPLATE_TARGET>&, ISIP_TEMPLATE_T1);

// method: numEqual
//
// arguments:
//  const MMatrix<TScalar, TIntegral>& this: (output) class operand
//  TIntegral value: (input) value to be tested
//
// return: a int32 value containing the number of elements equal to the
// input element
//
// this method counts the number of elements in the current matrix
// which are equal to the input value
//
template<class TScalar, class TIntegral>
int32 MMatrixMethods::numEqual(const MMatrix<TScalar, TIntegral>& this_a, 
			      TIntegral value_a) {
  
  // type: FULL
  //  count the number of elements equal to value_a
  //
  if (this_a.type_d == Integral::FULL) {
    return this_a.m_d.numEqual(value_a);
  }
  
  // type: DIAGONAL
  //
  else if (this_a.type_d == Integral::DIAGONAL) {
    
    // count the number of elements equal to value_a in the diagonal vector
    //
    int32 num_eq = this_a.m_d.numEqual(value_a);
    
    // if given value is 0, adding the number of 0 elements not in diagonal
    //
    if (value_a == 0) {
      num_eq += (int32)( this_a.nrows_d) * ((int32)(this_a.nrows_d) - 1);
    }
    
    // exit gracefully
    //
    return num_eq;
  }
  
  // type: SYMMETRIC
  //
  else if (this_a.type_d == Integral::SYMMETRIC) {

    // count the number of elements equal to value_a in the lower triangle
    // 
    int32 num_eq  = this_a.m_d.numEqual(value_a);
    num_eq += num_eq;

    // subtract the number of diagonal elements which is equal to value_a
    // from num_eq
    //
    for (int32 index = 0; index < this_a.nrows_d; index++) {
      if (this_a.m_d(this_a.index(index, index)) == value_a) {
        num_eq--;
      }
    }
    
    // exit gracefully
    // 
    return num_eq;
  } 
  
  // type: LOWER_TRIANGULAR, UPPER_TRIANGULAR
  //
  else if ((this_a.type_d == Integral::LOWER_TRIANGULAR) ||
	   (this_a.type_d == Integral::UPPER_TRIANGULAR)) {
    
    // count the number of elements equal to value_a in the vector
    //
    int32 num_eq = this_a.m_d.numEqual(value_a);
    
    // if value_a = 0, add the number of zero elements implied by the
    // other half of the matrix. this happens to be the length of
    // the data vector, m_d, minus the number of rows.
    //
    if (value_a == 0) {
      num_eq += this_a.m_d.length() - this_a.nrows_d;
    }
    
    // exit gracefully
    //
    return num_eq;
  }

  // type: SPARSE
  //
  else {

    // for non-zero value call the numEqual for value vector
    //
    if (value_a != 0) {
      return this_a.m_d.numEqual(value_a);
    }

    // else return the number of zeros in the matrix
    //
    int32 number = (this_a.nrows_d * this_a.ncols_d) - this_a.m_d.length();

    // exit gracefully
    //    
    return number;
  }
}

// explicit instantiations
//
template int32
MMatrixMethods::numEqual<ISIP_TEMPLATE_TARGET>
(const MMatrix<ISIP_TEMPLATE_TARGET>&, ISIP_TEMPLATE_T1);

// method: maxMag
//
// arguments:
//  const MMatrix<TScalar, TIntegral>& this: (output) class operand
//  int32& row_pos: (output) row position of maximum mag
//  int32& col_pos: (output) col position of maximum mag
//
// return: a float64 value containing the magnitude of the maximum
// magnitude element
//
// this method returns the magnitude, row index and column index of the
// maximum magnitude element of the matrix
//
template<class TScalar, class TIntegral>
float64 MMatrixMethods::maxMag(const MMatrix<TScalar, TIntegral>& this_a, 
				 int32& row_pos_a, int32& col_pos_a) {

  // condition: empty input matrix
  //
  if ((this_a.getNumRows() < 1) || (this_a.getNumColumns() < 1)) {
    this_a.debug(L"this_a");    
    return Error::handle(name(), L"maxMag", Error::ARG, __FILE__, __LINE__);
  }

  // declare local variables
  //
  int32 position;
  
  // get the element with maximum magnitude
  //
  float64 value = this_a.m_d.maxMag(position);

  // get the row and column indices of the maximum magnitude element
  //
  if ((float64)0 == value) {

    // find the first zero element
    //
    this_a.nextZero(row_pos_a, col_pos_a, -1, -1);
  }
  else {

    // get the row index and column index of the element
    //
    this_a.reverseIndex(row_pos_a, col_pos_a, position);
  }

  // exit gracefully
  //
  return value;
}

// explicit instantiations
//
template float64
MMatrixMethods::maxMag<ISIP_TEMPLATE_TARGET>
(const MMatrix<ISIP_TEMPLATE_TARGET>&, int32&, int32&);

// method: minMag
//
// arguments:
//  const MMatrix<TScalar, TIntegral>& this: (output) class operand
//  int32& row_pos: (output) row position of minimum Magnitude
//  int32& col_pos: (output) col position of minimum Magnitude
//
// return: a float64 value containing the value of the minimum
// magnitude element
//
// this method returns the magnitude, row index and column index of the
// minimum magnitude element of the matrix
//
template<class TScalar, class TIntegral>
float64 MMatrixMethods::minMag(const MMatrix<TScalar, TIntegral>& this_a, 
				 int32& row_pos_a, int32& col_pos_a) {

  // condition: empty input matrix
  //
  if ((this_a.getNumRows() < 1) || (this_a.getNumColumns() < 1)) {
    this_a.debug(L"this_a");    
    return Error::handle(name(), L"minMag", Error::ARG, __FILE__, __LINE__);
  }

  // type: DIAGONAL, LOWER_TRIANGULAR, UPPER_TRIANGULAR, SPARSE
  //  for diagonal, triangular and sparse matrices, if the maximum value is
  //  zero and dimensions are greater than 1, then find the position of
  //  first zero element of the matrix
  //
  if (((TIntegral)(this_a.nrows_d) > 1) &&
      ((this_a.type_d == Integral::DIAGONAL) ||
       (this_a.type_d == Integral::LOWER_TRIANGULAR) ||
       (this_a.type_d == Integral::UPPER_TRIANGULAR) ||
       (this_a.type_d == Integral::SPARSE))) {
    
    // get the row index and column index of the first zero element
    //
    if (this_a.nextZero(row_pos_a, col_pos_a, -1, -1)) {
      
      // exit gracefully
      //
      return (float64)0;
    }
  }
  
  // declare the local variables
  //
  int32 position;
  
  // get the element with minimum magnitude
  //
  float64 value = this_a.m_d.minMag(position);

  // get the row index and column index of the element
  //
  this_a.reverseIndex(row_pos_a, col_pos_a, position);

  // exit gracefully
  //
  return value;
}

// explicit instantiations
//
template float64
MMatrixMethods::minMag<ISIP_TEMPLATE_TARGET>
(const MMatrix<ISIP_TEMPLATE_TARGET>&, int32&, int32&);

// method: max
//
// arguments:
//  const MMatrix<TScalar, TIntegral>& this: (output) class operand
//  int32& row_pos: (output) row position of maximum
//  int32& col_pos: (output) col position of maximum
//
// return: a TIntegral value containing the value of the maximum element
//
// this method finds the maximum value and its position
//
template<class TScalar, class TIntegral>
TIntegral MMatrixMethods::max(const MMatrix<TScalar, TIntegral>& this_a, 
			      int32& row_pos_a, int32& col_pos_a) {

  // condition: empty input matrix
  //
  if ((this_a.getNumRows() < 1) || (this_a.getNumColumns() < 1)) {
    this_a.debug(L"this_a");    
    return Error::handle(name(), L"max", Error::ARG, __FILE__, __LINE__);
  }

  // declare local variables
  //
  int32 position;
  
  // get the element with maximum value
  //
  TIntegral value = this_a.m_d.max(position);

  // get the row and column indices of the maximum magnitude element
  //
  if ((TIntegral)0 >= value) {

    // type: DIAGONAL, LOWER_TRIANGULAR, UPPER_TRIANGULAR, SPARSE
    //  for diagonal, triangular and sparse matrices, if the maximum value is
    //  zero and dimensions are greater than 1, then find the position of
    //  first zero element of the matrix
    //
    if (((TIntegral)this_a.nrows_d > 1) &&
	((this_a.type_d == Integral::DIAGONAL) ||
	 (this_a.type_d == Integral::LOWER_TRIANGULAR) ||
	 (this_a.type_d == Integral::UPPER_TRIANGULAR) ||
	 (this_a.type_d == Integral::SPARSE))) {

      // get the row index and column index of the first zero element
      //
      if (this_a.nextZero(row_pos_a, col_pos_a, -1, -1)) {

	// exit gracefully
	//
	return (TIntegral)0;
      }
    }
  }

  // there is no zero element in this matrix get the row index and
  // column index of the element
  //
  this_a.reverseIndex(row_pos_a, col_pos_a, position);

  // exit gracefully
  //
  return value;
}

// explicit instantiations
//
template ISIP_TEMPLATE_T1
MMatrixMethods::max<ISIP_TEMPLATE_TARGET>
(const MMatrix<ISIP_TEMPLATE_TARGET>&, int32&, int32&);

// method: min
//
// arguments:
//  const MMatrix<TScalar, TIntegral>& this: (output) class operand
//  int32& row_pos: (output) row position of minimum
//  int32& col_pos: (output) col position of minimum
//
// return: a TIntegral value containing the value of the minimum element
//
// this method finds the minimum value and its position
//
template<class TScalar, class TIntegral>
TIntegral MMatrixMethods::min(const MMatrix<TScalar, TIntegral>& this_a, 
			      int32& row_pos_a, int32& col_pos_a) {

  // condition: empty input matrix
  //
  if ((this_a.getNumRows() < 1) || (this_a.getNumColumns() < 1)) {
    this_a.debug(L"this_a");    
    return Error::handle(name(), L"min", Error::ARG, __FILE__, __LINE__);
  }

  // declare local variables
  //
  int32 position;
  
  // get the element with minimum value
  //
  TIntegral value = this_a.m_d.min(position);

  // get the row and column indices of the minimum valued element
  //
#ifndef ISIP_TEMPLATE_unsigned    
  if ((TIntegral)0 <= value) {
#endif

    // type: DIAGONAL, LOWER_TRIANGULAR, UPPER_TRIANGULAR, SPARSE
    //  for diagonal, triangular and sparse matrices, if the maximum value is
    //  zero and dimensions are greater than 1, then find the position of
    //  first zero element of the matrix
    //
    if (((TIntegral)this_a.nrows_d > 1) &&
	((this_a.type_d == Integral::DIAGONAL) ||
	 (this_a.type_d == Integral::LOWER_TRIANGULAR) ||
	 (this_a.type_d == Integral::UPPER_TRIANGULAR) ||
	 (this_a.type_d == Integral::SPARSE))) {

      // get the row index and column index of the first zero element
      //
      if (this_a.nextZero(row_pos_a, col_pos_a, -1, -1)) {

	// exit gracefully
	//
	return (TIntegral)0;
      }
    }
    
#ifndef ISIP_TEMPLATE_unsigned    
  }
#endif
  
  // there is no zero element in this matrix, get the row and column
  // index of the element
  //
  this_a.reverseIndex(row_pos_a, col_pos_a, position);

  // exit gracefully
  //
  return value;
}

// explicit instantiations
//
template ISIP_TEMPLATE_T1
MMatrixMethods::min<ISIP_TEMPLATE_TARGET>
(const MMatrix<ISIP_TEMPLATE_TARGET>&, int32&, int32&);

// method: concatByColumn
//
// arguments:
//  MMatrix<TScalar, TIntegral>& this: (output) class operand
//  const MMatrix<TScalar, TIntegral>& m: (input) MMatrix
//
// return: a bool8 value indicating status
//
// this method concatenates the matrix "m_a" to "this" by adding
// elements of "m_a" to the rows of this. note that the output of this
// operation is ALWAYS either FULL or sparse, regardless of current
// type or input types.
//
template<class TScalar, class TIntegral>
bool8
MMatrixMethods::concatByColumn(MMatrix<TScalar, TIntegral>& this_a, 
			       const MMatrix<TScalar, TIntegral>& m_a) {

  // condition: the numbers of rows of two matrices are not equal
  //
  if (this_a.getNumRows() != m_a.getNumRows()) {
    m_a.debug(L"m_a");    
    this_a.debug(L"this_a");    
    return Error::handle(name(), L"concatByColumn", Error::ARG,
			 __FILE__, __LINE__);
  }

  // make a temporary copy of the matrix
  //
  MMatrix<TScalar, TIntegral> tmp(m_a);

  // type: SPARSE
  //  for sparse matrices we do not change type to full 
  //
  if (this_a.type_d == Integral::SPARSE) {

    // change types of input matrix to SPARSE. this way the output
    // type will be unchanged.
    //
    tmp.changeType(Integral::SPARSE);
    
    // get the length of the value vectors of the current and the
    // input matrix in order to get the length of the resultant matrix
    //
    int32 length = this_a.m_d.length() + tmp.m_d.length();
    
    // declare local variables
    //
    int32 count = 0;

    // get the lengths of the two matrices
    //
    int32 len = this_a.m_d.length();
    int32 last_j = tmp.m_d.length();
    MMatrix<TScalar, TIntegral> temp(0, 0, Integral::SPARSE);

    // set the length of the three sparse vectors
    //
    temp.m_d.setLength(length);
    temp.row_index_d.setLength(length);
    temp.col_index_d.setLength(length);

    // loop through the number of rows of the input matrix
    //
    for (int32 row = 0; row < tmp.nrows_d; row++) {

      // loop through the elements of current matrix
      //
      for (int32 i = 0; i < len; i++) {
        
        // check row indices of non-zero elements
        //
        if (row == this_a.row_index_d(i)) {

	  // add values to all the three vectors of the temporary matrix
	  //
          temp.m_d(count) = this_a.m_d(i);
          temp.row_index_d(count) = this_a.row_index_d(i);
          temp.col_index_d(count) = this_a.col_index_d(i);
          count++;
        }
      }
      
      // loop through the elements of the input matrix
      //
      for (int32 j = 0; j < last_j; j++) {
        
        // check row indices of non-zero elements
        //
        if (row == tmp.row_index_d(j)) {
	
	  // add values to all the three vectors of the temporary matrix
	  //
          temp.m_d(count) = tmp.m_d(j);
          temp.row_index_d(count) = tmp.row_index_d(j);
          temp.col_index_d(count) = tmp.col_index_d(j) + this_a.ncols_d;
          count++;
        }
      }
    }
    
    // assign resultant values to the current matrix
    //
    this_a.nrows_d = tmp.nrows_d;
    this_a.ncols_d += tmp.ncols_d;
    this_a.m_d.setLength(length);
    this_a.row_index_d.setLength(length);
    this_a.col_index_d.setLength(length);
    
    // store elements, row index and column index in the current matrix
    //
    for (int32 k = 0; k < length; k++) {
      this_a.m_d(k) = temp.m_d(k);
      this_a.row_index_d(k) = temp.row_index_d(k);
      this_a.col_index_d(k) = temp.col_index_d(k);
    }
    
    // exit gracefully
    //
    return true;
  }

  // type: DIAGONAL, FULL, SYMMETRIC, LOWER_TRIANGULAR, UPPER_TRIANGULAR
  //
  else {

    // get the dimensions of the current matrix
    //
    int32 old_ncols = this_a.getNumColumns();
    int32 new_nrows = this_a.getNumRows();

    // get the new dimensions of the matrix
    //
    int32 add_ncols = tmp.getNumColumns();
    int32 new_ncols = old_ncols + add_ncols;

    // declare local variables
    // 
    int32 src_pos = 0;
   
    // change the dimension and type of the input and current matrices
    //
    this_a.setDimensions(new_nrows, new_ncols, true, Integral::FULL);
    tmp.changeType(Integral::FULL);

    // loop over the number of rows
    //
    for (int32 row_index = 0; row_index < new_nrows; row_index++) {

      // get the position of start column
      //
      int32 start_pos = this_a.index(row_index, old_ncols);

      // loop over the number of columns
      //
      for (int32 col_index = old_ncols; col_index < new_ncols; col_index++) {

	// assign data
	//
	this_a.m_d(start_pos) = tmp.m_d(src_pos);

	// increment the position pointer
	//
	start_pos++;
	src_pos++;
      }
    }
    
    // exit gracefully
    // 
    return true;
  }
}

// explicit instantiations
//
template bool8
MMatrixMethods::concatByColumn<ISIP_TEMPLATE_TARGET>
(MMatrix<ISIP_TEMPLATE_TARGET>&, const MMatrix<ISIP_TEMPLATE_TARGET>&);

// method: concatByRow
//
// arguments:
//  MMatrix<TScalar, TIntegral>& this: (output) class operand
//  const MMatrix<TScalar, TIntegral>& m: (input) MMatrix
//
// return: a bool8 value indicating status
//
// this method concatenates the matrix "new_matrix" to "this" by
// enlarging "this" by new_matrix.getNumRows(), and by assigning
// "new_matrix" to the newly created rows in "this".  note that the
// output of this operation is ALWAYS either FULL or sparse,
// regardless of current type or input types.
//
template<class TScalar, class TIntegral>
bool8 MMatrixMethods::concatByRow(MMatrix<TScalar, TIntegral>& this_a, 
				    const MMatrix<TScalar, TIntegral>& m_a) {

  // condition: the numbers of columns of two matrices are not equal
  //
  if (this_a.getNumColumns() != m_a.getNumColumns()) {
    m_a.debug(L"m_a");    
    this_a.debug(L"this_a");    
    return Error::handle(name(), L"concatByRow", Error::ARG,
			 __FILE__, __LINE__);
  }

  // copy the matrix to a temporary matrix
  //
  MMatrix<TScalar, TIntegral> tmp(m_a);
  
  // for sparse matrix
  //
  if (this_a.type_d == Integral::SPARSE) {

    // change the type of the input matrices to SPARSE
    //
    tmp.changeType(Integral::SPARSE);
        
    // get the length of the value vectors of the current and the
    // input matrix in order to get the length of the resultant matrix
    //    
    int32 length = this_a.m_d.length() + tmp.m_d.length();
    
    // declare local variable
    //
    int32 count = 0;
    int32 last_j = tmp.m_d.length();
    MMatrix<TScalar, TIntegral> temp(0, 0, 
				     Integral::SPARSE);

    // set the lengths of the three sparse vector to hold the elements
    //
    temp.m_d.setLength(length);
    temp.row_index_d.setLength(length);
    temp.col_index_d.setLength(length);

    // loop through the elements of current matrix
    //
    for (int32 i = 0; i < this_a.m_d.length(); i++) {

      // copy the values, row index and column index
      //
      temp.m_d(count) = this_a.m_d(i);
      temp.row_index_d(count) = this_a.row_index_d(i);
      temp.col_index_d(count) = this_a.col_index_d(i);
      count++;
    }
   
    // loop through the elements of input matrix
    //
    for (int32 j = 0; j < last_j; j++) {
      
      // copy values and increment row indexes
      //
      temp.m_d(count) = tmp.m_d(j);
      temp.row_index_d(count) = tmp.row_index_d(j) + this_a.nrows_d;
      temp.col_index_d(count) = tmp.col_index_d(j);
      count++;
    }

    // set the number of rows and columns of the matrix and the length of the
    // vectors of the matrix
    //
    this_a.nrows_d += tmp.nrows_d;
    this_a.ncols_d = tmp.ncols_d;
    this_a.m_d.setLength(length);
    this_a.row_index_d.setLength(length);
    this_a.col_index_d.setLength(length);
    
    // assign the elements and their row and column indices from the
    // temporary matrix to the current matrix
    //
    for (int32 k = 0; k < length; k++) {
      this_a.m_d(k) = temp.m_d(k);
      this_a.row_index_d(k) = temp.row_index_d(k);
      this_a.col_index_d(k) = temp.col_index_d(k);
    }
    
    // exit gracefully
    //
    return true;
  }
  
  // for diagonal, symmetric, lower triangle or upper triangle matrices the
  // type will be changed to full as matrix will no longer retain its type
  //
  else {

    // get the dimensions of the current matrix
    //
    int32 old_nrows = this_a.getNumRows();
    int32 new_ncols = this_a.getNumColumns();
    
    // get new dimensions of the matrix
    //
    int32 add_nrows = tmp.getNumRows();
    int32 new_nrows = old_nrows + add_nrows;

    // create space in the current matrix
    //
    this_a.setDimensions(new_nrows, new_ncols, true, Integral::FULL);

    // change the type of the matrix to full
    //
    MMatrix<TScalar, TIntegral> tmp;
    tmp.assign(m_a, Integral::FULL);

    // get the start position
    //
    int32 start_pos = this_a.index(old_nrows, 0);

    for (int32 src_pos = 0; src_pos < tmp.m_d.length(); src_pos++) {

      // assign data
      //
      this_a.m_d(start_pos) = tmp.m_d(src_pos);

      // increment the position pointer
      //
      start_pos++;
    }
    
    // exit gracefully
    // 
    return true;
  }
}

// explicit instantiations
//
template bool8
MMatrixMethods::concatByRow<ISIP_TEMPLATE_TARGET>
(MMatrix<ISIP_TEMPLATE_TARGET>&, const MMatrix<ISIP_TEMPLATE_TARGET>&);

// method: reverseIndex
//
// arguments:
//  const MMatrix<TScalar, TIntegral>& this: (input) class operand
//  int32& row_index: (output) converted row index
//  int32& col_index: (output) converted column index
//  int32 vec_index: (input) the index of vector in the matrix
//
// return: a bool8 value indicating status
//
// this method gets the row index and column index of the element in
// the matrix from the vector index
//
template<class TScalar, class TIntegral>
bool8 MMatrixMethods::reverseIndex(const MMatrix<TScalar, TIntegral>& this_a,
				     int32& row_index_a, int32& col_index_a,
				     int32 vec_index_a) {

  // condition: empty input matrix
  //
  if (((TIntegral)this_a.nrows_d < 1) || ((TIntegral)this_a.ncols_d < 1)) {
    this_a.debug(L"this_a");    
    return Error::handle(name(), L"reverseIndex", Error::ARG,
			 __FILE__, __LINE__);
  }

  // condition: invalid argument
  //
  if (vec_index_a > this_a.m_d.length()) {
    this_a.debug(L"this_a");    
    return Error::handle(name(), L"reverseIndex", Error::ARG,
			 __FILE__, __LINE__);
  }
  
  // type: FULL
  //
  if (this_a.type_d == Integral::FULL) {

    // calculate the row index and column index
    //
    row_index_a = vec_index_a / this_a.ncols_d;
    col_index_a = vec_index_a - row_index_a * this_a.ncols_d;

    // exit gracefully
    //
    return true;
  }

  // type: DIAGONAL
  //
  else if (this_a.type_d == Integral::DIAGONAL) {

    // in case of the diagonal matrix, row and column indices are the
    // same as vector index
    //
    row_index_a = vec_index_a;
    col_index_a = vec_index_a;

    // exit gracefully
    //
    return true;
  }

  // type: SYMMETRIC, LOWER_TRIANGULAR
  //
  else if ((this_a.type_d == Integral::SYMMETRIC) ||
	   (this_a.type_d == Integral::LOWER_TRIANGULAR)) {

    // loop through the matrix rows to calculate the row index and
    // column indices
    //
    for (int32 index = 1; index <= this_a.nrows_d; index++) {

      // whether the element is in this row
      //
      if (vec_index_a < index) {

	// in case of the symmetric matrix, we return the element which
	// occurs first while scanning the matrix row-wise. the element,
	// which is stored on the vector, is the second element so we swap
	// the row and column indices of this element to get the element
	// in the upper triangle.
	//
	if (this_a.type_d == Integral::SYMMETRIC) {

	  // get the row index and column index which are in upper triangle
	  //
	  row_index_a = vec_index_a;
	  col_index_a = index - 1;
	}

	// lower triangle matrix
	//
	else {
	  
	  // get the row index and column index
	  //
	  row_index_a = index - 1;
	  col_index_a = vec_index_a;
	}

	// exit gracefully
	//
	return true;
      }

      // subtract the row length from vector index
      //
      vec_index_a -= index;
    }

    // error: out of the range of matrix
    //
    this_a.debug(L"this_a");    
    return Error::handle(name(), L"reverseIndex", 
			 MMatrix<TScalar, TIntegral>::ERR,
			 __FILE__, __LINE__);
  }

  // type: UPPER_TRIANGULAR
  //
  else if (this_a.type_d == Integral::UPPER_TRIANGULAR) {

    // loop through the matrix columns to calculate the row index and
    // column indices
    //
    for (int32 index = 1; index <= this_a.ncols_d; index++) {

      // whether the element is in this column
      //
      if (vec_index_a < index) {

	// get the row index and column index which are in upper triangle
	//
	row_index_a = vec_index_a;
	col_index_a = index - 1;

	// exit gracefully
	//
	return true;
      }

      // subtract the column length from vector index
      //
      vec_index_a -= index;
    }

    // error: out of the range of matrix
    //
    this_a.debug(L"this_a");    
    return Error::handle(name(), L"reverseIndex", 
			 MMatrix<TScalar, TIntegral>::ERR,
			 __FILE__, __LINE__);
  }

  // type: SPARSE
  //  in case of sparse matrix, return the row and column index from the
  //  vectors containing row and column indices
  //
  else {

    // get row index and column index from row_index_d and col_index_d
    //
    row_index_a = this_a.row_index_d(vec_index_a);
    col_index_a = this_a.col_index_d(vec_index_a);

    // exit gracefully
    //
    return true;
  }
}
// explicit instantiations
//
template bool8
MMatrixMethods::reverseIndex<ISIP_TEMPLATE_TARGET>
(const MMatrix<ISIP_TEMPLATE_TARGET>&, int32&, int32&, int32);

// method: rand
//
// arguments:
//  MMatrix<TScalar, TIntegral>& this: (output) class operand
//  Random& generator: (input) random number generator
//
// return: a bool8 value indicating status
//
// this method initializes each element of the matrix with a uniformly
// distributed random value
//
template<class TScalar, class TIntegral>
bool8 MMatrixMethods::rand(MMatrix<TScalar, TIntegral>& this_a,
			     Random& generator_a) {

  // type: non-SPARSE
  //
  if (this_a.type_d != Integral::SPARSE) {
    this_a.m_d.rand(generator_a);
  }

  // type: SPARSE
  //
  else {

    // generate random locations of non-zero elements
    //
    this_a.randIndicesSparse();

    // generate non-zero random numbers
    //
    int32 num_elements = this_a.m_d.length();

    for (int32 index = 0; index < num_elements; index++) {
      TIntegral value;
      do {
	value = this_a.m_d(index).rand(generator_a);
      } while (value == 0);
    }
  }

  // exit gracefully
  //
  return true;
}

// explicit instantiations
//
template bool8
MMatrixMethods::rand<ISIP_TEMPLATE_TARGET>
(MMatrix<ISIP_TEMPLATE_TARGET>&, Random&);

// method: rand
//
// arguments:
//  MMatrix<TScalar, TIntegral>& this: (output) class operand
//  TIntegral min: (input) min value
//  TIntegral max: (input) max value
//  Random& generator: (input) random number generator
//
// return: a bool8 value indicating status
//
// this method initializes each element of the matrix with a uniformly
// distributed random value between min_a and max_a
//
template<class TScalar, class TIntegral>
bool8 MMatrixMethods::rand(MMatrix<TScalar, TIntegral>& this_a,
			     TIntegral min_a, TIntegral max_a,
			     Random& generator_a) {

  // type: non-SPARSE
  //
  if (this_a.type_d != Integral::SPARSE) {
    this_a.m_d.rand(min_a, max_a, generator_a);
  }

  // type: SPARSE
  //
  else {

    // generate random locations of non-zero elements
    //
    this_a.randIndicesSparse();

    // generate non-zero random numbers
    //
    int32 num_elements = this_a.m_d.length();

    for (int32 index = 0; index < num_elements; index++) {
      TIntegral value;
      do {
	value = this_a.m_d(index).rand(min_a, max_a, generator_a);
      } while (value == 0);
    }
  }

  // exit gracefully
  //
  return true;
}

// explicit instantiations
//
template bool8 
MMatrixMethods::rand<ISIP_TEMPLATE_TARGET>
(MMatrix<ISIP_TEMPLATE_TARGET>&, ISIP_TEMPLATE_T1, ISIP_TEMPLATE_T1, Random&);

// method: grand
//
// arguments:
//  MMatrix<TScalar, TIntegral>& this: (output) class operand
//  TIntegral mean: (input) mean value
//  TIntegral stdev: (input) standard deviation
//  Random& generator: (input) random number generator
//
// return: a bool8 value indicating status
//
// this method initializes each element of the matrix with a uniformly
// distributed gaussian random value
//
template<class TScalar, class TIntegral>
bool8 MMatrixMethods::grand(MMatrix<TScalar, TIntegral>& this_a,
			      TIntegral mean_a, TIntegral stdev_a,
			      Random& generator_a) {

  // type: non-SPARSE
  //
  if (this_a.type_d != Integral::SPARSE) {
    return this_a.m_d.grand(mean_a, stdev_a, generator_a);
  }

  // type: SPARSE
  //
  else {

    // generate random locations of non-zero elements
    //
    this_a.randIndicesSparse();

    // generate non-zero random numbers
    //
    int32 num_elements = this_a.m_d.length();

    for (int32 index = 0; index < num_elements; index++) {
      TIntegral value;
      do {
	value = this_a.m_d(index).grand(mean_a, stdev_a, generator_a);
      } while (value == 0);
    }
  }

  // exit gracefully
  //
  return true;
}

// explicit instantiations
//
template bool8 
MMatrixMethods::grand<ISIP_TEMPLATE_TARGET>
(MMatrix<ISIP_TEMPLATE_TARGET>&, ISIP_TEMPLATE_T1, ISIP_TEMPLATE_T1, Random&);

// method: randIndicesSparse
//
// arguments:
//  MMatrix<TScalar, TIntegral>& this: (output) class operand
//  Random& generator: (input) random number generator
//
// return: a bool8 value containing the status
//  
// this method generates randomized locations for non-zero elements
// in a sparse matrix.
//
template<class TScalar, class TIntegral>
bool8 MMatrixMethods::randIndicesSparse(MMatrix<TScalar, TIntegral>& this_a,
					  Random& generator_a) {

  // generate a random length using the sparseness threshold: generate
  // a length that is, on the average, close to the sparseness threshold
  //
  Long val;
  int32 max_nelem = this_a.nrows_d * this_a.ncols_d;
  int32 spr_nelem = (int32)(2 * max_nelem *
			  (1 - MMatrix<TScalar, TIntegral>::THRESH_SPARSE));
  int32 nelem = val.rand(1, spr_nelem, generator_a);

  // set the dimensions
  //
  this_a.m_d.setLength(nelem);
  this_a.row_index_d.setLength(nelem);
  this_a.col_index_d.setLength(nelem);

  // generate some random indices by:
  //  (1) generating a pair of indices
  //  (2) checking if these already exist
  //  (3) if they do, try again; if not, continue
  //
  for (int32 index = 0; index < nelem; index++) {

    // keep generating a pair of random indices until we find a unique pair
    //
    while (1) {

      // generate values
      //
      int32 row = val.rand(0, (int32)this_a.nrows_d - 1);
      int32 col = val.rand(0, (int32)this_a.ncols_d - 1);

      // check if this pair is unique
      //
      bool8 found = false;

      for (int32 i = 0; i < index; i++) {
	if ((this_a.row_index_d(i) == row) &&
	    (this_a.col_index_d(i) == col)) {
	  found = true;
	  break;
	}
      }

      // if found is false, they are unique, and we can break
      //
      if (!found) {
	this_a.row_index_d(index) = row;
	this_a.col_index_d(index) = col;
	break;
      }
    }
  }

  // sort the indices
  //
  this_a.sortSparse();
     
  // exit gracefully
  //
  return true;
}

// explicit instantiations
//
template bool8 
MMatrixMethods::randIndicesSparse<ISIP_TEMPLATE_TARGET>
(MMatrix<ISIP_TEMPLATE_TARGET>&, Random&);
