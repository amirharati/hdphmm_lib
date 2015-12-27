// file: $isip/class/math/matrix/MMatrix/mmat_14.cc
// version: $Id: mmat_14.cc 7816 2002-02-27 20:54:30Z alphonso $
//

// isip include files
//
#include "MMatrixMethods.h"
#include "MMatrix.h"

// method: sum
//
// arguments:
//  const MMatrix<TScalar, TIntegral>& this: (input) class operand
//
// return: a value containing the sum of the elements
//
template<class TScalar, class TIntegral>
TIntegral MMatrixMethods::sum(const MMatrix<TScalar, TIntegral>& this_a) {

  // declare local variables
  //
  int32 nrows = this_a.nrows_d;
  int32 ncols = this_a.ncols_d;
  TIntegral sum = 0;

  // type: non-SYMMETRIC
  //
  if (this_a.type_d != Integral::SYMMETRIC) {
    sum = this_a.m_d.sum();
  }
  
  // type: SYMMETRIC
  //  
  else {

    // check the dimension
    //
    if ((nrows == 0) && (ncols == 0)) {
      return sum;
    }

    // compute the sum of the lower-triangular elements in two parts:
    // off-diagonal and diagonal values.
    //
    TIntegral sum_diag = this_a.m_d(0);

    for (int32 row = 1, index = 1; row < nrows; row++) {
      for (int32 col = 0; col < row; col++) {
	sum += this_a.m_d(index++);
      }
      sum_diag += this_a.m_d(index++);
    }

    // the correct sum can now be computed by adding these two pieces
    //
    sum = (TIntegral)2 * sum + sum_diag;
  }

  // exit gracefully
  //  
  return sum;
}

// explicit instantiations
//
template ISIP_TEMPLATE_T1   
MMatrixMethods::sum<ISIP_TEMPLATE_TARGET>
(const MMatrix<ISIP_TEMPLATE_TARGET>&);

// method: sumSquare
//
// arguments:
//  const MMatrix<TScalar, TIntegral>& this: (input) class operand
//
// return: a value containing the sum of the squares of the elements
//
template<class TScalar, class TIntegral>
TIntegral
MMatrixMethods::sumSquare(const MMatrix<TScalar, TIntegral>& this_a) {

  // declare local variables
  //
  int32 nrows = this_a.nrows_d;
  int32 ncols = this_a.ncols_d;
  TIntegral sum = 0;

  // type: non-SYMMETRIC
  //
  if (this_a.type_d != Integral::SYMMETRIC) {
    sum = this_a.m_d.sumSquare();
  }
  
  // type: SYMMETRIC
  //  
  else {

    // check the dimension
    //
    if ((nrows == 0) && (ncols == 0)) {
      return sum;
    }

    // compute the sum of the lower-triangular elements in two parts:
    // off-diagonal and diagonal values.
    //
    TIntegral sum_diag = this_a.m_d(0) * this_a.m_d(0);

    for (int32 row = 1, index = 1; row < nrows; row++) {
      for (int32 col = 0; col < row; col++) {
	sum += this_a.m_d(index) * this_a.m_d(index);
	index++;
      }
      sum_diag += this_a.m_d(index) * this_a.m_d(index);
      index++;
    }

    // the correct sum can now be computed by adding these two pieces
    //
    sum = (TIntegral)2 * sum + sum_diag;
  }

  // exit gracefully
  //  
  return sum;
}

// explicit instantiations
//
template ISIP_TEMPLATE_T1   
MMatrixMethods::sumSquare<ISIP_TEMPLATE_TARGET>
(const MMatrix<ISIP_TEMPLATE_TARGET>&);

// method: var
//
// arguments:
//  const MMatrix<TScalar, TIntegral>& this: (input) class operand
//
// return: a value containing the variance 
//
// this method calculates the variance of all elements in the matrix by
// considering it as a 1-D array.
//
template<class TScalar, class TIntegral>
TIntegral MMatrixMethods::var(const MMatrix<TScalar, TIntegral>& this_a) {

  // declare local variables for the number of elements and the mean
  //
  int32 num_elements = this_a.nrows_d * this_a.ncols_d;
  TIntegral mean = this_a.mean();
  
  // we can compute the variance by computing the sum of squares
  // and subtracting the squared mean.
  //
  TIntegral var =  (TIntegral)(this_a.sumSquare() / (TIntegral)num_elements - mean * mean);

  return var;
}

// explicit instantiations
//
template ISIP_TEMPLATE_T1
MMatrixMethods::var<ISIP_TEMPLATE_TARGET>
(const MMatrix<ISIP_TEMPLATE_TARGET>&);

// method: sumRow
//
// arguments:
//  const MMatrix<TScalar, TIntegral>& this: (input) class operand
//  int32 row: (input) row index
//
// return: a TIntegral value containing the sum
//
// this method calculates the sum of all elements in a given row.
//
template<class TScalar, class TIntegral>
TIntegral MMatrixMethods::sumRow(const MMatrix<TScalar, TIntegral>& this_a, 
				 int32 row_a) {

  // check the arguments
  //
  if ((row_a < 0) || (row_a > this_a.nrows_d)) {
    this_a.debug(L"this_a");    
    return Error::handle(name(), L"sumRow", Error::ARG, __FILE__, __LINE__);
  }

  // declare local variable
  //
  TIntegral sum = 0;
  
  // type: DIAGONAL
  //  this is easy since we only need one element
  //
  if (this_a.type_d == Integral::DIAGONAL) {
    sum = this_a.m_d(row_a);
  }

  // type: FULL, SYMMETRIC, LOWER_TRIANGULAR, UPPER_TRIANGULAR
  //
  else if ((this_a.type_d == Integral::FULL) ||
	   (this_a.type_d == Integral::SYMMETRIC) ||
	   (this_a.type_d == Integral::LOWER_TRIANGULAR) ||
	   (this_a.type_d == Integral::UPPER_TRIANGULAR)) {

    // loop over the entire row
    //
    int32 first_col = this_a.startColumn(row_a, this_a.type_d);
    int32 last_col = this_a.stopColumn(row_a, this_a.type_d);

    for (int32 col = first_col; col <= last_col; col++) {
      sum += this_a.getValue(row_a, col);
    }

    // for symmetric matrix, we will also need to add the elements
    // after the diagonal element for specified row 
    //
    if (this_a.type_d == Integral::SYMMETRIC) {
      for (int32 col = last_col + 1; col < this_a.ncols_d; col++) {
	sum += this_a.getValue(row_a, col);
      }
    }
  }

  // type: SPARSE
  //  
  else {

    // loop over number of elements: only add elements in the given row
    //
    int32 num_elements = this_a.m_d.length();
    
    for (int32 elem = 0; elem < num_elements; elem++) {
      if (row_a == this_a.row_index_d(elem)) {
	sum += this_a.m_d(elem);
      }
    }
  }

  // exit gracefully
  //
  return sum;
}

// explicit instantiations
//
template ISIP_TEMPLATE_T1   
MMatrixMethods::sumRow<ISIP_TEMPLATE_TARGET>
(const MMatrix<ISIP_TEMPLATE_TARGET>&, int32);

// method: sumColumn
//
// arguments:
//  const MMatrix<TScalar, TIntegral>& this: (input) class operand
//  int32 col: (input) col index
//
// return: a TIntegral value containing the sum
//
// this method calculates the sum of all elements in a given col.
//
template<class TScalar, class TIntegral>
TIntegral MMatrixMethods::sumColumn(const MMatrix<TScalar, TIntegral>& this_a, 
				    int32 col_a) {

  // check the arguments
  //
  if ((col_a < 0) || (col_a > this_a.ncols_d)) {
    this_a.debug(L"this_a");    
    return Error::handle(name(), L"sumColumn", Error::ARG, __FILE__, __LINE__);
  }

  // declare local variable
  //
  TIntegral sum = 0;
  
  // type: DIAGONAL
  //  this is easy since we only need one element
  //
  if (this_a.type_d == Integral::DIAGONAL) {
    sum = this_a.m_d(col_a);
  }

  // type: FULL, SYMMETRIC, LOWER_TRIANGULAR, UPPER_TRIANGULAR
  //  the easiest way to do this is to fetch the entire col as a vector
  //
  else if ((this_a.type_d == Integral::FULL) ||
	   (this_a.type_d == Integral::SYMMETRIC) ||
	   (this_a.type_d == Integral::LOWER_TRIANGULAR) ||
	   (this_a.type_d == Integral::UPPER_TRIANGULAR)) {

    // loop over the entire column
    //
    int32 first_row = this_a.startRow(col_a, this_a.type_d);
    int32 last_row = this_a.stopRow(col_a, this_a.type_d);

    for (int32 row = first_row; row <= last_row; row++) {
      sum += this_a.getValue(row, col_a);
    }

    // for symmetric matrix, we also need to add the elements above
    // diagonal for the particular column
    //
    if (this_a.type_d == Integral::SYMMETRIC) {
      for (int32 row = 0; row < first_row; row++) {
	sum += this_a.getValue(row, col_a);
      }
    }
  }

  // type: SPARSE
  //  
  else {

    // loop over number of elements: only add elements in the given col
    //
    int32 num_elements = this_a.m_d.length();
    
    for (int32 elem = 0; elem < num_elements; elem++) {
      if (col_a == this_a.col_index_d(elem)) {
	sum += this_a.m_d(elem);
      }
    }
  }

  // exit gracefully
  //
  return sum;
}

// explicit instantiations
//
template ISIP_TEMPLATE_T1   
MMatrixMethods::sumColumn<ISIP_TEMPLATE_TARGET>
(const MMatrix<ISIP_TEMPLATE_TARGET>&, int32);

