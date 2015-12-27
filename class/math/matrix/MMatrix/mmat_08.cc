// file: $isip/class/math/matrix/MMatrix/mmat_08.cc
// version: $Id: mmat_08.cc 8492 2002-07-29 14:53:18Z hamaker $
//

// isip include files
//
#include "MMatrixMethods.h"
#include "MMatrix.h"
#include <omp.h>
// method: multv
//
// arguments:
//  const MMatrix<TScalar, TIntegral>& this: (output) class operand
//  MVector<TScalar, TIntegral>& v_out: (output) output vector
//  const MVector<TScalar, TIntegral>& v_in: (input) input vector
//
// return: a bool8 value indicating status
//
// this method multiplies the current matrix with the input vector and
// assign result to the output vector, for example:
//
//           [0 1 2]         [2]          [0 1 2]   [2]   [2 ]
//  matrix = [3 4 5]  v_in = [0]  v_out = [3 4 5] * [0] = [11]
//           [6 7 8]	     [1]   	  [6 7 8]   [1]   [20]
//
// for this multiplication, the vector should be a column vector and
// the dimensions should agree
//
template<class TScalar, class TIntegral>
bool8 MMatrixMethods::multv(const MMatrix<TScalar, TIntegral>& this_a, 
			      MVector<TScalar, TIntegral>& v_out_a, 
			      const MVector<TScalar, TIntegral>& v_in_a) {

  // if the input and output are the same, then a temporary copy is needed
  //
  if (&v_in_a == &v_out_a) {
    MVector<TScalar, TIntegral> tmp(v_in_a);
    return multv(this_a, v_out_a, tmp);
  }
  
  // check the arguments:
  //  the columns of the matrix should be equal to the length of input vector
  //
  if (this_a.getNumColumns() != v_in_a.length()) {
    v_in_a.debug(L"v_in_a");    
    this_a.debug(L"this_a");    
    return Error::handle(name(), L"multv", Error::ARG, __FILE__, __LINE__);
  }

  // get the number of rows and columns of the current matrix
  //
  int32 nrows = (int32)this_a.nrows_d;
  int32 ncols = (int32)this_a.ncols_d;

  // create space in the output vector
  // 
  if (!v_out_a.setLength(nrows, false)) {
    v_out_a.debug(L"v_out_a");
    this_a.debug(L"this_a");    
    return Error::handle(name(), L"multv", Error::MEM, __FILE__, __LINE__);
  }

  // type: FULL
  //  the general idea is that we loop through each element of matrix and get
  //  the dot product
  //
  if (this_a.type_d == Integral::FULL) {

    // loop over all elements
    //
    for (int32 row = 0, index = 0; row < nrows; row++) {

      // initialize the accumulator for the dot product
      //
      TIntegral sum = 0;

      // compute the dot product
      //
      for (int32 col = 0; col < ncols; col++) {
	sum += this_a.m_d(index++) * v_in_a(col);
      }
      
      // save the result
      //
      v_out_a(row) = sum;
    }
  }
  
  // type: DIAGONAL
  //  the general idea here is that we just multiply corresponding elements of
  //  diagonal and input vector
  //
  else if (this_a.type_d == Integral::DIAGONAL) {

    // only multiply the diagonal values to the corresponding elements in the
    // input vector
    //
    for (int32 row = 0; row < nrows; row++) {
      v_out_a(row) = this_a.m_d(row) * v_in_a(row);
    }
  }

  // type: SYMMETRIC
  //  the general idea is that we loop through each row of the matrix.
  //  for elements in the upper triangular part, we use the values from
  //  the lower triangular part.
  //
  else if (this_a.type_d == Integral::SYMMETRIC) {

    // loop over rows of the matrix
    //
    for (int32 row = 0; row < nrows; row++) {

      // initialize the sum of dot products for current row
      //      
      TIntegral sum = 0;

      // loop over the lower triangular elements of the matrix
      //      
      for (int32 col = 0; col < row; col++) {
        sum += this_a.m_d(this_a.index(row, col)) * v_in_a(col);
      }

      // loop over the upper triangular elements of the matrix
      //            
      for (int32 col = row; col < nrows; col++) {
        sum += this_a.m_d(this_a.index(col, row)) * v_in_a(col);
      }

      // save the result
      //
      v_out_a(row) = sum;
    }
  }
  
  // type: LOWER_TRIANGULAR
  //  the general idea is that we only loop through the elements
  //  in the lower triangular part of the matrix
  //
  else if (this_a.type_d == Integral::LOWER_TRIANGULAR) {

    // loop over rows of the matrix
    //
    for (int32 row = 0; row < nrows; row++) {

      // initialize the sum of dot products for current row
      //      
      TIntegral sum = 0;

      // loop over the lower triangular elements of the matrix
      //      
      for (int32 col = 0; col <= row; col++) {
        sum += this_a.m_d(this_a.index(row, col)) * v_in_a(col);
      }

      // save the result
      //
      v_out_a(row) = sum;
    }
  }
  
  // type: UPPER_TRIANGULAR
  //
  else if (this_a.type_d == Integral::UPPER_TRIANGULAR) {

    // loop over rows of the matrix
    //
    for (int32 row = 0; row < nrows; row++) {

      // initialize the sum of dot products for current row
      //      
      TIntegral sum = 0;

      // loop over the lower triangular elements of the matrix
      //      
      for (int32 col = row; col < ncols; col++) {
        sum += this_a.m_d(this_a.index(row, col)) * v_in_a(col);
      }

      // save the result
      //
      v_out_a(row) = sum;
    }
  }
  
  // type: SPARSE
  //  only use the non-zero elements
  //
  else if (this_a.type_d == Integral::SPARSE) {

    // clear the output vector since we will use it as an accumulator
    //
    v_out_a.clear(Integral::RETAIN);
    
    // loop through non-zero elements of matrix, multiply and store in
    // output vector
    //
    int32 last_index = this_a.m_d.length();

    for (int32 index = 0; index < last_index; index++) {
      int32 row = this_a.row_index_d(index);
      int32 col = this_a.col_index_d(index);
      v_out_a(row) += this_a.m_d(index) * v_in_a(col);
    }
  }

  // exit gracefully
  //  
  return true;
}

// explicit instantiations
//
template bool8
MMatrixMethods::multv<ISIP_TEMPLATE_TARGET>
(const MMatrix<ISIP_TEMPLATE_TARGET>&, MVector<ISIP_TEMPLATE_TARGET>&,
 const MVector<ISIP_TEMPLATE_TARGET>&);

// method: vmult
//
// arguments:
//  const MMatrix<TScalar, TIntegral>& this: (output) class operand
//  MVector<TScalar, TIntegral>& v_out: (output) output vector
//  const MVector<TScalar, TIntegral>& v_in: (input) input vector
//
// return: a bool8 value indicating status
//
// this method multiply the input vector with the current matrix and assign
// result to the output vector, for example:
//
//                           [0 1 2]                    [0 1 2]   
//  v_in = [2 0 1]  matrix = [3 4 5]  v_out = [2 0 1] * [3 4 5] = [6 9 12]
//                           [6 7 8]	        	[6 7 8]   
//
// for this multiplication, the vector should be a row vector and
// dimensions should agree
//
template<class TScalar, class TIntegral>
bool8 MMatrixMethods::vmult(const MMatrix<TScalar, TIntegral>& this_a, 
			      MVector<TScalar, TIntegral>& v_out_a, 
			      const MVector<TScalar, TIntegral>& v_in_a) {

  // if the input and output are the same, then a temporary copy is needed
  //
  if (&v_in_a == &v_out_a) {
    MVector<TScalar, TIntegral> tmp(v_in_a);
    return multv(this_a, v_out_a, tmp);
  }
  
  // get the number of rows and columns of the matrix
  //
  int32 nrows = this_a.getNumRows();
  int32 ncols = this_a.getNumColumns();
  
  // check the dimensions
  //  the row of matrix should be equal to the length of input vector
  //
  if (nrows != v_in_a.length()) {
    v_in_a.debug(L"v_in_a");    
    this_a.debug(L"this_a");    
    return Error::handle(name(), L"vmult()", Error::ARG, __FILE__, __LINE__);
  }

  // create space in the output vector
  //
  if (!v_out_a.setLength(ncols, false)) {
    v_out_a.debug(L"v_out_a");    
    this_a.debug(L"this_a");    
    return Error::handle(name(), L"vmult", Error::MEM, __FILE__, __LINE__);
  }

  // type: FULL
  //  compute the dot product directly
  //
  if (this_a.type_d == Integral::FULL) {

    // loop over the number of columns
    //
    for (int32 col = 0; col < ncols; col++) {

      // initialize the sum of dot products for current column
      //            
      TIntegral sum = 0;

      // calculate the dot product of the row
      //
      for (int32 row = 0; row < nrows; row++) {
	sum += this_a.m_d(this_a.index(row, col)) * v_in_a(row);
      }
      
      // save the result
      //
      v_out_a(col) = sum;
    }
  }

  // type: DIAGONAL
  //  multiply corresponding elements of diagonal and input vector
  //
  else if (this_a.type_d == Integral::DIAGONAL) {
    for (int32 row = 0; row < nrows; row++) {
      v_out_a(row) = v_in_a(row) * this_a.m_d(row);
    }
  }

  // type: SYMMETRIC
  //  loop through each column of the matrix and compute the dot product
  //  for elements in the upper triangle, we use the values from
  //  lower triangle 
  //
  else if (this_a.type_d == Integral::SYMMETRIC) {

    // loop over the rows of the matrix
    //          
    for (int32 col = 0; col < ncols; col++) {

      // loop over the upper triangular elements of the matrix
      //            
      TIntegral sum = 0;

      for (int32 row = 0; row < col; row++) {
        sum += v_in_a(row) * this_a.m_d(this_a.index(col, row));
      }

      // loop over the lower triangular elements of the matrix
      //
      for (int32 row = col; row < nrows; row++) {
        sum  += v_in_a(row) * this_a.m_d(this_a.index(row, col));
      }

      // output the results
      //
      v_out_a(col) = sum;
    }
  }

  // type: LOWER_TRIANGULAR
  //  same as SYMMETRIC, but only the lower triangular values are used
  //
  else if (this_a.type_d == Integral::LOWER_TRIANGULAR) {

    // loop over the rows of the matrix
    //          
    for (int32 col = 0; col < ncols; col++) {

      // loop over the upper triangular elements of the matrix
      //            
      TIntegral sum = 0;

      for (int32 row = col; row < nrows; row++) {
        sum  += v_in_a(row) * this_a.m_d(this_a.index(row, col));
      }

      // output the results
      //
      v_out_a(col) = sum;
    }
  }

  // type: UPPER_TRIANGULAR
  //  same as SYMMETRIC, but only the upper triangle values are used
  //
  else if (this_a.type_d == Integral::UPPER_TRIANGULAR) {

    // loop over the rows of the matrix
    //          
    for (int32 col = 0; col < ncols; col++) {

      // loop over the upper triangular elements of the matrix
      //            
      TIntegral sum = 0;

      for (int32 row = 0; row <= col; row++) {
        sum += v_in_a(row) * this_a.m_d(this_a.index(row, col));
      }

      // output the results
      //
      v_out_a(col) = sum;
    }
  }

  // type: SPARSE
  //  the general idea is that we loop through the non-zero elements only
  //  and get the dot product
  //
  else if (this_a.type_d == Integral::SPARSE) {

    // clear the contents of output vector
    //
    v_out_a.clear(Integral::RETAIN);
    
    // loop through non-zero elements of matrix, multiply and store in
    // output vector
    //
    int32 last_index = this_a.m_d.length();

    for (int32 index = 0; index < last_index; index++) {
      int32 row = this_a.row_index_d(index);
      int32 col = this_a.col_index_d(index);
      v_out_a(col) += this_a.m_d(index) * v_in_a(row);
    }
  }

  // exit gracefully
  //  
  return true;
}

// explicit instantiations
//
template bool8
MMatrixMethods::vmult<ISIP_TEMPLATE_TARGET>
(const MMatrix<ISIP_TEMPLATE_TARGET>&, MVector<ISIP_TEMPLATE_TARGET>&,
 const MVector<ISIP_TEMPLATE_TARGET>&);

// method: quadratic
//
// arguments:
//  TIntegral& output: (output) scalar return value
//  const MMatrix<TScalar, TIntegral>& this: (input) class operand
//  const MVector<TScalar, TIntegral>& v_in: (input) input vector
//
// return: a bool8 value indicating status
//   v_in * this_a * transpose(v_in)
//
// this method computes v_in * this_a * transpose(v_in) and returns a
// scalar value, for example:
//
//                           [0 1 2]                     [0 1 2]   [2]
//  v_in = [2 0 1]  matrix = [3 4 5]  output = [2 0 1] * [3 4 5] * [0] = 24
//                           [6 7 8]	          	 [6 7 8]   [1]
//
template<class TScalar, class TIntegral>
bool8
MMatrixMethods::quadratic(TIntegral& output_a,
			  const MMatrix<TScalar, TIntegral>& this_a, 
			  const MVector<TScalar, TIntegral>& v_in_a) {

  // initialize the output
  //
  output_a = 0;
  
  // get the number of rows and columns of the matrix
  //
  int32 nrows = this_a.getNumRows();
  int32 ncols = this_a.getNumColumns();

  // check dimensions:
  //  (1) the number of rows and number of columns of the matrix can't be
  //      less than 1
  //  (2) the rows and columns of matrix must be equal to the length of
  //      input vector
  //
  if ((nrows < 1) || (ncols < 1) ||
      (nrows != v_in_a.length()) || (ncols != v_in_a.length())) {
    v_in_a.debug(L"v_in_a");
    this_a.debug(L"this_a");    
    return Error::handle(name(), L"quadratic", this_a.ERR_DIM,
			 __FILE__, __LINE__);
  }
  
  // type: DIAGONAL
  //  the general idea is that we only loop through the elements of diagonal
  //
  if (this_a.type_d == Integral::DIAGONAL) {

    // loop over diagonal elements of the matrix and multiply
    //
    for (int32 i = 0; i < nrows; i++) {
      output_a += (v_in_a(i) * v_in_a(i)) * this_a.m_d(i);
    }
  }

  // type: NON-DIAGONAL
  //  the general idea here is that we are going to build a vector to do
  //  vector * matrix first, and then do dot product of vector
  //
  else if ((this_a.type_d == Integral::FULL) ||
	   (this_a.type_d == Integral::SYMMETRIC) ||
	   (this_a.type_d == Integral::LOWER_TRIANGULAR) ||
	   (this_a.type_d == Integral::UPPER_TRIANGULAR) ||
	   (this_a.type_d == Integral::SPARSE)) {

    // declare temporary vector
    //
    MVector<TScalar, TIntegral> temp;

    // do vector matrix multiplication and store the result into a
    // temporary vector
    //
    this_a.vmult(temp, v_in_a);

    // compute the dot product of the two vectors
    // note that dotProduct for complex numbers conjugates elements of
    // the second vector
    //
    output_a = v_in_a.dotProduct(temp);
  }

  // exit gracefully
  //  
  return true;
}

// explicit instantiations
//
template bool8 
MMatrixMethods::quadratic<ISIP_TEMPLATE_TARGET>
(ISIP_TEMPLATE_T1&, const MMatrix<ISIP_TEMPLATE_TARGET>&, const MVector<ISIP_TEMPLATE_TARGET>&);


// method: quadratic
//
// arguments:
//  MMatrix<TScalar, TIntegral>& output: (output) matrix output
//  const MMatrix<TScalar, TIntegral>& mat1: (input) input matrix
//  const MMatrix<TScalar, TIntegral>& mat2: (input) input matrix
//
// return: a bool8 value indicating status
//
// this method computes mat2 * mat1 * transpose(mat2)
// the result is stored in the output matrix. Note that mat1
// must be square.
//
//         [2 0 1]        [0 1 2] 
//  mat2 = [4 5 7] mat1 = [3 4 5] 
//                        [6 7 8]
//
//                         [0 1 2]   [2 4]             
//      output = [2 0 1] * [3 4 5] * [0 5] = [ 24  153]
//               [4 5 7]   [6 7 8]   [1 7]   [203 1216]
//
template<class TScalar, class TIntegral>
bool8
MMatrixMethods::quadratic(MMatrix<TScalar, TIntegral>& output_a,
			  const MMatrix<TScalar, TIntegral>& mat1_a,
			  const MMatrix<TScalar, TIntegral>& mat2_a) {

  // sanity checks
  //
  if (!mat1_a.isSquare() || (mat2_a.getNumColumns() != mat1_a.getNumRows())) {
    mat1_a.debug(L"mat1_a");
    mat2_a.debug(L"mat2_a");    
    return Error::handle(name(), L"quadratic", output_a.ERR_DIM,
			 __FILE__, __LINE__);
  }

  // make sure that none of the inputs is equal to the output
  //
  if (&mat1_a == &output_a) {
    MMatrix<TScalar, TIntegral> tmp(mat1_a);
    return quadratic(output_a, tmp, mat2_a) ;
  }
  else if (&output_a == &mat2_a) {
    MMatrix<TScalar, TIntegral> tmp(mat2_a);
    return quadratic(output_a, mat1_a, tmp);
  }
  
  // for the moment, unless the center matrix is diagonal, we do a simple
  // (but resource-intensive for larger matrices) temporary matrix computation
  //
  if (mat1_a.getType() != Integral::DIAGONAL) {

    MMatrix<TScalar, TIntegral> tmp_matrix;

    // compute the first multiplication: mat1 * mat2
    // and then the second: (mat1 * mat2) * transpose(mat1)
    //
    return (tmp_matrix.mult(mat2_a, mat1_a) &&
	    output_a.outerProduct(tmp_matrix, mat2_a));
  }

  // if the center matrix is diagonal then the output will be
  // symmetric and we need only calculate half of the output.
  // Further, there is a simple loop structure to the calculation
  //
  else {

    Integral::MTYPE old_type  = output_a.getType();
    int32 nrows = mat2_a.getNumRows();
    int32 ncols = mat2_a.getNumColumns();

    // if the output matrix is symmetric then we need not make any
    // change to the type. otherwise we will set it to be full temporarily
    // and determine later if the type can be changed back. Only
    // a symmetric, full, sparse, or (perhaps) diagonal are appropriate
    //
    if (output_a.getType() != Integral::SYMMETRIC) {
      output_a.setDimensions(nrows, nrows, false, Integral::FULL);
    }
    else {
      output_a.setDimensions(nrows, nrows, false);
    }
    
    // now loop and compute the output
    //
    for (int32 row = 0; row < nrows; row++) {
      for (int32 col = 0; col <= row; col++) {
	TIntegral sum = (TIntegral)0;
	for (int32 row2 = 0; row2 < ncols; row2++) {
	  sum += mat2_a(row,row2) * mat2_a(col,row2) * mat1_a.m_d(row2);
	}
	output_a.setValue(row,col,sum);
	output_a.setValue(col,row,sum);
      }
    }

    // try to change the output type to the desired type
    // restore the type if possible
    //
    if (output_a.isTypePossible(old_type)) {
      return output_a.changeType(old_type);
    }
    else {
      return output_a.changeType(Integral::FULL);
    }
  }
}

// explicit instantiations
//
template bool8 
MMatrixMethods::quadratic<ISIP_TEMPLATE_TARGET>
(MMatrix<ISIP_TEMPLATE_TARGET>&, const MMatrix<ISIP_TEMPLATE_TARGET>&,
 const MMatrix<ISIP_TEMPLATE_TARGET>&);


// method: outerProduct
//
// arguments:
//  MMatrix<TScalar, TIntegral>& this: (output) class operand
//  const MMatrix<TScalar, TIntegral>& m1: (input) operand 1
//  const MMatrix<TAScalar, TAIntegral>& m2: (input) operand 2
//
// return: a bool8 value indicating status
//
// this method computes the outer product of two matrices. The
// column dimension of both matrices must agree.
// for example:
//
//       [1 4]       [2 0]                               [2 24  4 42]
//  m1 = [2 5]  m2 = [0 6]  m_out = m1 * transpose(m2) = [4 30  8 57]
//       [3 6]       [4 0]                               [6 36 12 72]
//                   [6 9]
//
template<class TScalar, class TIntegral, class TAScalar, class TAIntegral>
bool8 MMatrixMethods::outerProduct(MMatrix<TScalar, TIntegral>& this_a, 
			     const MMatrix<TScalar, TIntegral>& m1_a, 
			     const MMatrix<TAScalar, TAIntegral>& m2_a) {

  // if the current matrix is same as one operand, a copy to temporary matrix
  // of that operand is needed
  //
  if (&this_a == &m1_a) {
    MMatrix<TScalar, TIntegral> tmp(this_a);
    return this_a.outerProduct(tmp, m2_a) ;
  }
  else if ((void*)&this_a == (void*)&m2_a) {
    MMatrix<TScalar, TIntegral> tmp(this_a);
    return this_a.outerProduct(m1_a, tmp);
  }

  // check dimensions
  //
  if (m1_a.getNumColumns() != m2_a.getNumColumns()) {
    m1_a.debug(L"m1_a");
    m2_a.debug(L"m2_a");    
    return Error::handle(name(), L"outerProduct", m2_a.ERR_DIM, __FILE__,
			 __LINE__);
  }

  // get the type of two matrices and branch on type
  //
  Integral::MTYPE old_type = this_a.type_d;
  int32 nrows = m1_a.getNumRows();
  int32 ncols = m2_a.getNumRows();
  Integral::MTYPE type1 = m1_a.getType();
  Integral::MTYPE type2 = m2_a.getType();

  // type1: FULL
  //
  if (type1 == Integral::FULL) {

    // create space in the output matrix
    //
    this_a.setDimensions(nrows, ncols, false, Integral::FULL);
    
    // type2: DIAGONAL
    //  set the type of output matrix as full, and multiply the elements in
    //  the first matrix with the diagonal elements in the second matrix which
    //  has the same column index
    //
    if (type2 == Integral::DIAGONAL) {
      
      // loop over elements and multiply
      //      
      for (int32 row = 0; row < nrows; row++) {
        for (int32 col = 0; col < ncols; col++) {
          this_a.m_d(this_a.index(row, col)) =
	    (TIntegral)((TAIntegral)m1_a.m_d(m1_a.index(row, col)) *
	       (TAIntegral)m2_a.m_d(col));
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

      // loop over all elements
      //
#pragma omp parallel for collapse(2)
      for (int32 row = 0; row < nrows; row++) {
        for (int32 col = 0; col < ncols; col++) {  
          this_a.m_d(this_a.index(row, col)) = 
            (TIntegral)this_a.multiplyRowByRow(m1_a, m2_a, row, col);
        }
      }
    }

    // type2: SPARSE
    //  set the type of output matrix as full. 
    //
    else if (type2 == Integral::SPARSE) {

      // clear the output matrix
      //
      this_a.clear(Integral::RETAIN);
       
      // declare local variables
      //
      int32 b_row;
      int32 b_col;
      TAIntegral b_val;
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
          c_val = this_a.getValue(a_index, b_row);
          sub_val = (TIntegral)((TAIntegral)b_val *
				m1_a.getValue(a_index, b_col));
          this_a.setValue(a_index, b_row, c_val + sub_val);
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
        this_a.m_d(row) = (TIntegral)((TAIntegral)m1_a.m_d(row) * (TAIntegral)m2_a.m_d(row));
      }
    }

    // type2: FULL
    //  set the output matrix as full, and multiply the diagonal elements
    //  of the first matrix with the elements which has the same row index.
    //  since a diagonal matrix is equal to its transpose, we can do normal
    //  matrix multiplication here
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
	    (TIntegral)((TAIntegral)(m1_a.m_d(row)) *
	    (TAIntegral)(m2_a.m_d(m2_a.index(col, row))));
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
	    (TIntegral)((TIntegral)(m1_a.m_d(row)) *
			(TIntegral)(m2_a.m_d(m2_a.index(row, col))));
        }
        for (int32 col = row; col < ncols; col++) {
          this_a.m_d(this_a.index(row, col)) =
	    (TIntegral)((TIntegral)(m1_a.m_d(row)) *
			(TIntegral)(m2_a.m_d(m2_a.index(col, row))));
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
      this_a.setDimensions(nrows, nrows, false, Integral::UPPER_TRIANGULAR);
      
      // loop over the elements and multiply
      //      
      for (int32 row1 = 0; row1 < nrows; row1++) {
        for (int32 row2 = row1; row2 < nrows; row2++) {
          this_a.m_d(this_a.index(row1, row2)) =
	    (TIntegral)((TAIntegral)(m1_a.m_d(row1)) *
            (TAIntegral)(m2_a.m_d(m2_a.index(row2, row1))));
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
      this_a.setDimensions(nrows, nrows, false, Integral::LOWER_TRIANGULAR);
      
      // loop over the elements and multiply
      //
      for (int32 row1 = 0; row1 < nrows; row1++) {
        for (int32 row2 = 0; row2 <= row1; row2++) {
          this_a.m_d(this_a.index(row1, row2)) =
	    (TIntegral)((TAIntegral)(m1_a.m_d(row1))*
            (TAIntegral)(m2_a.m_d(m2_a.index(row2, row1))));
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
      int32 len1 = m1_a.getNumColumns();
      int32 len2 = m2_a.m_d.length();

      // declare local variables
      //
      int32 row2 = 0;
      int32 col2 = 0;
      TAIntegral val2 = 0;
      TIntegral val1 = 0;

      // loop over the columns of the diagonal matrix
      //
      for (int32 col1 = 0; col1 < len1; col1++) {

	// get the element on the diagonal vector
	//
        val1 = m1_a.m_d(col1);

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
          if (col2 == col1) {
            this_a.setValue(col1, row2, (TIntegral)(val1 * val2));
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
	    (TScalar)((TIntegral)(m2_a.m_d(col)) *
		      (TIntegral)(m1_a.m_d(m1_a.index(row, col))));
        }
        for (int32 col = row; col < ncols; col++) {
          this_a.m_d(this_a.index(row, col)) =
	    (TScalar)((TIntegral)(m2_a.m_d(col)) *
		      (TIntegral)(m1_a.m_d(m1_a.index(col, row))));
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
            this_a.multiplyRowByRow(m1_a, m2_a, row, col);
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
      TAIntegral b_val;
      TIntegral c_val = 0;
      TIntegral sub_val = 0;
      int32 length = m2_a.m_d.length();

      // loop over the values of the sparse matrix and multiply
      //
      for (int32 b_index = 0; b_index < length; b_index++) {
        b_row = m2_a.row_index_d(b_index);
        b_col = m2_a.col_index_d(b_index);
        b_val = m2_a.m_d(b_index);
        int32 a_rows = m1_a.getNumRows();
        for (int32 a_index = 0; a_index < a_rows; a_index++) {
          c_val = this_a.getValue(a_index, b_row);
          sub_val = (TIntegral)((TAIntegral)b_val *
				m1_a.getValue(a_index, b_col));
          this_a.setValue(a_index, b_row, c_val + sub_val);
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
      this_a.setDimensions(m1_a, false, Integral::LOWER_TRIANGULAR);
      
      // loop over each element
      //
      for (int32 row = 0; row < nrows; row++) {
        for (int32 col = 0; col <= row; col++) {
          this_a.m_d(this_a.index(row, col)) =
	    (TScalar)((TIntegral)((TIntegral)m2_a.m_d(col) *
		      (TIntegral)(m1_a.m_d(m1_a.index(row, col)))));
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
            this_a.multiplyRowByRow(m1_a, m2_a, row, col);
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
      TAIntegral b_val;
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
          c_val = this_a.getValue(a_index, b_row);
          sub_val = (TIntegral)((TAIntegral)b_val *
				m1_a.getValue(a_index, b_col));
          this_a.setValue(a_index, b_row, c_val + sub_val);
        }
      }
    }    
  }

  // type1: UPPER_TRIANGULAR
  //
  else if (type1 == Integral::UPPER_TRIANGULAR) {
    // type2: DIAGONAL
    //  set the type of output matrix as lower triangular.
    //
    if (type2 == Integral::DIAGONAL) {

      // create space in the output matrix
      //
      this_a.setDimensions(nrows, ncols, false, Integral::UPPER_TRIANGULAR);

      // loop over each element
      //
      for (int32 row = 0; row < nrows; row++) {
        for (int32 col = row; col < ncols; col++) {
          this_a.m_d(this_a.index(row, col)) =
	    (TScalar)((TIntegral)m2_a.m_d(col) *
		      (TIntegral)(m1_a.m_d(m1_a.index(row, col))));
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
            this_a.multiplyRowByRow(m1_a, m2_a, row, col);
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
      TAIntegral b_val;
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
          c_val = this_a.getValue(a_index, b_row);
          sub_val = (TIntegral)((TAIntegral)b_val *
				m1_a.getValue(a_index, b_col));
          this_a.setValue(a_index, b_row, c_val + sub_val);
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
      TAIntegral val2 = 0;
      TIntegral val1 = 0;
      
      // get the number of rows of the second matrix and the length of
      // vector of sparse matrix
      //
      int32 len2 = m2_a.getNumColumns();
      int32 len1 = m1_a.m_d.length();

      // loop over the number of rows of second matrix
      //
      for (int32 col2 = 0; col2 < len2; col2++) {
        val2 = m2_a.m_d(col2);
        for (int32 index = 0; index < len1; index++) {
          row1 = m1_a.row_index_d(index);
          col1 = m1_a.col_index_d(index);
          val1 = m1_a.m_d(index);

          // if the row index matches with position of diag vector
          // elements, multiply them
          //
          if (col2 == col1) {
            this_a.setValue(row1, col2, (TIntegral)(val1 * val2));
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

	// row of first matrix should be the same as the row in
	// the second matrix
	//
        int32 b_rows = m2_a.getNumRows();

        // loop over the columns of the second matrix
	//
        for (int32 b_index = 0; b_index < b_rows; b_index++) {
          c_val = this_a.getValue(a_row, b_index);
          sub_val = (TIntegral)((TIntegral)a_val *
				(TAIntegral)m2_a.getValue(b_index, a_col));
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
      int32 row1;
      int32 row2;
      int32 col1;
      int32 col2;
      TIntegral value;
      
      // loop over elements of the first matrix
      //
      for (int32 i = 0; i < m1_a.m_d.length(); i++) {
        
        // loop over elements of second matrix
        //
        for (int32 j = 0; j < m2_a.m_d.length(); j++) {
          
          // compare the respective column and row indices
          //
	  row1 = m1_a.row_index_d(i);
	  row2 = m2_a.row_index_d(j);
	  col1 = m1_a.col_index_d(i);
	  col2 = m2_a.col_index_d(j);
          if (col1 == col2) {
            
            // multiply the elements and store them in a temporary matrix
            //
            value = temp.getValue(row1, row2) +
              (TIntegral)((TIntegral)m1_a.m_d(i) * (TAIntegral)m2_a.m_d(j));
            temp.setValue(row1, row2, value);
          }
        }
      }

      // copy the result to the current matrix
      //
      this_a.assign(temp, Integral::SPARSE);
    }
  }

  // restore the type if possible
  //
  if (this_a.isTypePossible(old_type)) {
    return this_a.changeType(old_type);
  }
  else {
    return this_a.changeType(Integral::FULL);
  }
}

// explicit instantiations
//
#ifndef ISIP_TEMPLATE_complex
template bool8
MMatrixMethods::outerProduct<ISIP_TEMPLATE_TARGET, Byte, byte8>
(MMatrix<ISIP_TEMPLATE_TARGET>&, const MMatrix<ISIP_TEMPLATE_TARGET>&,
 const MMatrix<Byte, byte8>&);

template bool8
MMatrixMethods::outerProduct<ISIP_TEMPLATE_TARGET, Ushort, uint16>
(MMatrix<ISIP_TEMPLATE_TARGET>&, const MMatrix<ISIP_TEMPLATE_TARGET>&,
 const MMatrix<Ushort, uint16>&);

template bool8
MMatrixMethods::outerProduct<ISIP_TEMPLATE_TARGET, Ulong, uint32>
(MMatrix<ISIP_TEMPLATE_TARGET>&, const MMatrix<ISIP_TEMPLATE_TARGET>&,
 const MMatrix<Ulong, uint32>&);

template bool8
MMatrixMethods::outerProduct<ISIP_TEMPLATE_TARGET, Ullong, uint64>
(MMatrix<ISIP_TEMPLATE_TARGET>&, const MMatrix<ISIP_TEMPLATE_TARGET>&,
 const MMatrix<Ullong, uint64>&);

template bool8
MMatrixMethods::outerProduct<ISIP_TEMPLATE_TARGET, Short, int16>
(MMatrix<ISIP_TEMPLATE_TARGET>&, const MMatrix<ISIP_TEMPLATE_TARGET>&,
 const MMatrix<Short, int16>&);

template bool8
MMatrixMethods::outerProduct<ISIP_TEMPLATE_TARGET, Long, int32>
(MMatrix<ISIP_TEMPLATE_TARGET>&, const MMatrix<ISIP_TEMPLATE_TARGET>&,
 const MMatrix<Long, int32>&);

template bool8
MMatrixMethods::outerProduct<ISIP_TEMPLATE_TARGET, Llong, int64>
(MMatrix<ISIP_TEMPLATE_TARGET>&, const MMatrix<ISIP_TEMPLATE_TARGET>&,
 const MMatrix<Llong, int64>&);

template bool8
MMatrixMethods::outerProduct<ISIP_TEMPLATE_TARGET, Float, float32>
(MMatrix<ISIP_TEMPLATE_TARGET>&, const MMatrix<ISIP_TEMPLATE_TARGET>&,
 const MMatrix<Float, float32>&);

template bool8
MMatrixMethods::outerProduct<ISIP_TEMPLATE_TARGET, Double, float64>
(MMatrix<ISIP_TEMPLATE_TARGET>&, const MMatrix<ISIP_TEMPLATE_TARGET>&,
 const MMatrix<Double, float64>&);
#endif
#ifdef ISIP_TEMPLATE_complex
template bool8
MMatrixMethods::outerProduct<ISIP_TEMPLATE_TARGET, ComplexLong, complexlong>
(MMatrix<ISIP_TEMPLATE_TARGET>&, const MMatrix<ISIP_TEMPLATE_TARGET>&,
 const MMatrix<ComplexLong, complexlong>&);

template bool8
MMatrixMethods::outerProduct<ISIP_TEMPLATE_TARGET, ComplexFloat, complexfloat>
(MMatrix<ISIP_TEMPLATE_TARGET>&, const MMatrix<ISIP_TEMPLATE_TARGET>&,
 const MMatrix<ComplexFloat, complexfloat>&);
 
template bool8
MMatrixMethods::outerProduct<ISIP_TEMPLATE_TARGET, ComplexDouble, complexdouble>
(MMatrix<ISIP_TEMPLATE_TARGET>&, const MMatrix<ISIP_TEMPLATE_TARGET>&,
 const MMatrix<ComplexDouble, complexdouble>&);
#endif

// method: outerProduct
//
// arguments:
//  MMatrix<TScalar, TIntegral>& this: (output) class operand
//  const MVector<TScalar, TIntegral>& v1: (input) operand 1
//  const MVector<TAScalar, TAIntegral>& v2: (input) operand 2
//
// return: a bool8 value indicating status
//
// this method computes the outer product of two column vectors. because the
// outer product produces a full matrix, the output matrix type is
// normally set to FULL. if the matrix is input as a SPARSE matrix, its
// type is maintained however.
//
// example:
//                                                  [ 4  5  6  7]
//  m1 = [1] m2 = [4]  m_out = m1 * transpose(m2) = [ 8 10 12 14]
//       [2]      [5]                               [12 15 18 21]
//       [3]      [6]
//                [7]
//
// if length(m1) = r and length(m2) = c, then m_out will be a r by c matrix.
//
template<class TScalar, class TIntegral, class TAScalar, class TAIntegral>
bool8
MMatrixMethods::outerProduct(MMatrix<TScalar, TIntegral>& this_a, 
			     const MVector<TScalar, TIntegral>& v1_a, 
			     const MVector<TAScalar, TAIntegral>& v2_a) {
  
  // determine the new dimensions
  //
  int32 nrows = v1_a.length();
  int32 ncols = v2_a.length();

  // get the current type of the output matrix. if it is SPARSE then leave it
  // as SPARSE, otherwise change it to FULL
  //
  Integral::MTYPE output_type = this_a.type_d;

  if (output_type != Integral::SPARSE) {
    output_type = Integral::FULL;
  }

  // create space in the output matrix
  //
  this_a.setDimensions(nrows, ncols, false, Integral::FULL);

  // loop over all elements of both vectors and create the outer
  // product matrix
  //
  for (int32 i = 0; i < nrows; i++) {
    for (int32 j = 0; j < ncols; j++) {
      this_a.setValue(i, j, (TIntegral)(v1_a(i) * (TIntegral)v2_a(j)));
    }
  }

  // restore the output type
  //
  return this_a.changeType(output_type);
}

// explicit instantiations
//
#ifndef ISIP_TEMPLATE_complex
template bool8
MMatrixMethods::outerProduct<ISIP_TEMPLATE_TARGET, Byte, byte8>
(MMatrix<ISIP_TEMPLATE_TARGET>&, const MVector<ISIP_TEMPLATE_TARGET>&,
 const MVector<Byte, byte8>&);

template bool8
MMatrixMethods::outerProduct<ISIP_TEMPLATE_TARGET, Ushort, uint16>
(MMatrix<ISIP_TEMPLATE_TARGET>&, const MVector<ISIP_TEMPLATE_TARGET>&,
 const MVector<Ushort, uint16>&);

template bool8
MMatrixMethods::outerProduct<ISIP_TEMPLATE_TARGET, Ulong, uint32>
(MMatrix<ISIP_TEMPLATE_TARGET>&, const MVector<ISIP_TEMPLATE_TARGET>&,
 const MVector<Ulong, uint32>&);

template bool8
MMatrixMethods::outerProduct<ISIP_TEMPLATE_TARGET, Ullong, uint64>
(MMatrix<ISIP_TEMPLATE_TARGET>&, const MVector<ISIP_TEMPLATE_TARGET>&,
 const MVector<Ullong, uint64>&);

template bool8
MMatrixMethods::outerProduct<ISIP_TEMPLATE_TARGET, Short, int16>
(MMatrix<ISIP_TEMPLATE_TARGET>&, const MVector<ISIP_TEMPLATE_TARGET>&,
 const MVector<Short, int16>&);

template bool8
MMatrixMethods::outerProduct<ISIP_TEMPLATE_TARGET, Long, int32>
(MMatrix<ISIP_TEMPLATE_TARGET>&, const MVector<ISIP_TEMPLATE_TARGET>&,
 const MVector<Long, int32>&);

template bool8
MMatrixMethods::outerProduct<ISIP_TEMPLATE_TARGET, Llong, int64>
(MMatrix<ISIP_TEMPLATE_TARGET>&, const MVector<ISIP_TEMPLATE_TARGET>&,
 const MVector<Llong, int64>&);

template bool8
MMatrixMethods::outerProduct<ISIP_TEMPLATE_TARGET, Float, float32>
(MMatrix<ISIP_TEMPLATE_TARGET>&, const MVector<ISIP_TEMPLATE_TARGET>&,
 const MVector<Float, float32>&);

template bool8
MMatrixMethods::outerProduct<ISIP_TEMPLATE_TARGET, Double, float64>
(MMatrix<ISIP_TEMPLATE_TARGET>&, const MVector<ISIP_TEMPLATE_TARGET>&,
 const MVector<Double, float64>&);
#endif
#ifdef ISIP_TEMPLATE_complex
template bool8
MMatrixMethods::outerProduct<ISIP_TEMPLATE_TARGET, ComplexLong, complexlong>
(MMatrix<ISIP_TEMPLATE_TARGET>&, const MVector<ISIP_TEMPLATE_TARGET>&,
 const MVector<ComplexLong, complexlong>&);

template bool8
MMatrixMethods::outerProduct<ISIP_TEMPLATE_TARGET, ComplexFloat, complexfloat>
(MMatrix<ISIP_TEMPLATE_TARGET>&, const MVector<ISIP_TEMPLATE_TARGET>&,
 const MVector<ComplexFloat, complexfloat>&);
 
template bool8
MMatrixMethods::outerProduct<ISIP_TEMPLATE_TARGET, ComplexDouble, complexdouble>
(MMatrix<ISIP_TEMPLATE_TARGET>&, const MVector<ISIP_TEMPLATE_TARGET>&,
 const MVector<ComplexDouble, complexdouble>&);
#endif

// method: multiplyRowByRow
//
// arguments:
//  const MMatrix<TScalar, TIntegral>& this: (output) class operand
//  const MMatrix<TScalar, TIntegral>& m1: (input) operand 1
//  const MMatrix<TAScalar, TAIntegral>& m2: (input) operand 2
//  int32 row_m1: (input) row index in m1
//  int32 row_m2: (input) row index in m2
//
// return: a TIntegral value that results from multiplying the specified row
// in m1 by the specified row in m2
//
// this method is designed for the outer-product multiplication of full,
// symmetric, lower and upper triangular matrices
//
template<class TScalar, class TIntegral, class TAScalar, class TAIntegral>
TIntegral
MMatrixMethods::multiplyRowByRow(const MMatrix<TScalar, TIntegral>& this_a, 
				 const MMatrix<TScalar, TIntegral>& m1_a, 
				 const MMatrix<TAScalar, TAIntegral>& m2_a,
				 int32 row_m1_a, int32 row_m2_a) {

  // declare local variables
  //
  TIntegral sum = 0;
  
  // get the number of columns of the first matrix
  // 
  int32 last_index = m1_a.getNumRows();
  int32 ncols = m1_a.getNumColumns();

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
      for (int32 index = 0; index < ncols; index++) {
        sum += (TIntegral)((TIntegral)m1_a.m_d(m1_a.index(row_m1_a, index)) *
			  (TAIntegral)m2_a.m_d(m2_a.index(row_m2_a, index)));
      }      
    }

    // type2: SYMMETRIC
    //  multiply each element in the given column of the first matrix
    //  with the elements in the corresponding column of the second matrix
    //
    else if (type2 == Integral::SYMMETRIC) {
      
      // loop through the upper triangular elements of the second matrix
      //
      for (int32 index = 0; index < row_m2_a; index++) {
        sum += (TIntegral)((TIntegral)m1_a.m_d(m1_a.index(row_m1_a, index)) *
			   (TAIntegral)m2_a.m_d(m2_a.index(index, row_m2_a)));
      }

      // loop through the lower triangular elements of the second matrix
      //
      for (int32 index = row_m2_a; index < ncols; index++) {
        sum += (TIntegral)((TIntegral)m1_a.m_d(m1_a.index(row_m1_a, index)) *
			   (TAIntegral)m2_a.m_d(m2_a.index(row_m2_a, index)));
      }
    }

    // type2: LOWER_TRIANGULAR
    //  multiply the lower triangular elements in the given column of
    //  the second matrix with the corresponding elements in the
    //  given column of the first matrix
    //
    else if (type2 == Integral::LOWER_TRIANGULAR) {
      for (int32 index = 0; index <= row_m2_a; index++) {
        sum += (TIntegral)((TIntegral)m1_a.m_d(m1_a.index(row_m1_a, index)) *
			   (TAIntegral)m2_a.m_d(m2_a.index(row_m2_a, index)));
      }    
    }

    // type2: UPPER_TRIANGULAR
    //  multiply the upper triangular elements in the given column of
    //  the second matrix with the corresponding elements in the
    //  given column of the first matrix
    //      
    else if (type2 == Integral::UPPER_TRIANGULAR) {
      for (int32 index = row_m2_a; index < ncols; index++) {
        sum += (TIntegral)((TIntegral)m1_a.m_d(m1_a.index(row_m1_a, index)) *
			   (TAIntegral)m2_a.m_d(m2_a.index(row_m2_a, index)));
      }    
    }
  }

  // type1: SYMMETRIC
  //  a symmetric matrix is equal to its transpose so we can follow normal
  //  multiplication rules here
  //
  else if (type1 == Integral::SYMMETRIC) {

    // type2: FULL
    //  multiply each elements in the given row of the first matrix with
    //  the elements in the corresponding column of the second matrix
    // 
    if (type2 == Integral::FULL) {  
      for (int32 index = 0; index < row_m1_a; index++) {
        sum += (TIntegral)((TIntegral)m1_a.m_d(m1_a.index(index, row_m1_a)) *
			   (TAIntegral)m2_a.m_d(m2_a.index(row_m2_a, index)));
      }      
      for (int32 index = row_m1_a; index < last_index; index++) {
        sum += (TIntegral)((TIntegral)m1_a.m_d(m1_a.index(row_m1_a, index)) *
			   (TAIntegral)m2_a.m_d(m2_a.index(row_m2_a, index)));
      }    
    }

    // type2: SYMMETRIC
    //  multiply each elements in the given row of the first matrix with
    //  the elements in the corresponding column of the second matrix.
    //  the code needs to be separated into several loops to make sure when
    //  a upper triangle element is needed, its symmetric value will be used
    // 
    else if (type2 == Integral::SYMMETRIC) {

      if (row_m1_a > row_m2_a) {
	for (int32 index = 0; index < row_m2_a; index++) {
          sum += (TIntegral)((TIntegral)m1_a.m_d(m1_a.index(index, row_m1_a)) *
			     (TAIntegral)m2_a.m_d(m2_a.index(index, row_m2_a)));
        }
        for (int32 index = row_m2_a; index < row_m1_a; index++) {
          sum += (TIntegral)((TIntegral)m1_a.m_d(m1_a.index(index, row_m1_a)) *
			     (TAIntegral)m2_a.m_d(m2_a.index(row_m2_a, index)));
        }       
        for (int32 index = row_m1_a; index < last_index; index++) {
          sum += (TIntegral)((TIntegral)m1_a.m_d(m1_a.index(row_m1_a, index)) *
			     (TAIntegral)m2_a.m_d(m2_a.index(row_m2_a, index)));
        }
      }

      else {
        for (int32 index = 0; index < row_m1_a; index++) {
          sum += (TIntegral)((TIntegral)m1_a.m_d(m1_a.index(index, row_m1_a)) *
			     (TAIntegral)m2_a.m_d(m2_a.index(index, row_m2_a)));
        }
        for (int32 index = row_m1_a; index < row_m2_a; index++) {
          sum += (TIntegral)((TIntegral)m1_a.m_d(m1_a.index(row_m1_a, index)) *
			     (TAIntegral)m2_a.m_d(m2_a.index(index, row_m2_a)));
        }               
        for (int32 index = row_m2_a; index < last_index; index++) {
          sum += (TIntegral)((TIntegral)m1_a.m_d(m1_a.index(row_m1_a, index)) *
			     (TAIntegral)m2_a.m_d(m2_a.index(row_m2_a, index)));
        }
      }
    }

    // type2: LOWER_TRIANGULAR
    //  multiply the elements in the lower triangle of the second matrix with
    //  its corresponding elements in the first matrix
    //
    else if (type2 == Integral::LOWER_TRIANGULAR) {

      for (int32 index = 0; index <= row_m2_a; index++) {
	sum += (TIntegral)((TIntegral)m1_a.m_d(m1_a.index(row_m1_a, index)) *
			   (TAIntegral)m2_a.m_d(m2_a.index(row_m2_a, index)));
      }
    }

    // type2: UPPER_TRIANGULAR
    //  multiply the elements in the upper triangle of the second matrix with
    //  its corresponding elements in the first matrix
    //
    else if (type2 == Integral::UPPER_TRIANGULAR) {

      for (int32 index = row_m2_a; index < ncols; index++) {
	sum += (TIntegral)((TIntegral)m1_a.m_d(m1_a.index(row_m1_a, index)) *
			   (TAIntegral)m2_a.m_d(m2_a.index(row_m2_a, index)));
      }
    }
  }

  // type1: LOWER_TRIANGULAR
  //
  else if (type1 == Integral::LOWER_TRIANGULAR) {

    // type2: FULL
    //  multiply each element in the given column (and in the lower
    //  triangle) of the first matrix with its corresponding one in
    //  the given column of the second matrix, return the summation
    //  of the products
    //        
    if (type2 == Integral::FULL) {
      for (int32 index = 0; index <= row_m1_a; index++) {
        sum += (TIntegral)((TIntegral)m1_a.m_d(m1_a.index(row_m1_a, index)) *
			   (TAIntegral)m2_a.m_d(m2_a.index(row_m2_a, index)));
      }      
    }

    // type2: SYMMETRIC
    //  multiply each elements in the given column (and in the lower
    //  triangle) of the first matrix with its corresponding one (if
    //  it's in the upper triangle, use its symmetric value) in the
    //  given column of the second matrix, return the summation of
    //  the products
    //
    else if (type2 == Integral::SYMMETRIC) {

      for (int32 index = 0; index <= row_m1_a; index++) {
	sum += (TIntegral)((TIntegral)m1_a.m_d(m1_a.index(row_m1_a, index)) *
			   (TAIntegral)m2_a.m_d(m2_a.index(row_m2_a, index)));
      }
    }

    // type2: LOWER_TRIANGULAR
    //  multiply the elements in lower triangle
    //
    else if (type2 == Integral::LOWER_TRIANGULAR) {

      // find the start index
      //
      int32 last_index = (row_m1_a > row_m2_a) ? row_m2_a : row_m1_a;
      for (int32 index = 0; index <= last_index; index++) {
	sum += (TIntegral)((TIntegral)m1_a.m_d(m1_a.index(row_m1_a, index)) *
			   (TAIntegral)m2_a.m_d(m2_a.index(row_m2_a, index)));
      }
    }

    // type: UPPER_TRIANGULAR
    //
    else if (type2 == Integral::UPPER_TRIANGULAR) {

      int32 start_index = row_m2_a;
      last_index = row_m1_a;
      for (int32 index = start_index; index <= last_index; index++) {
	sum += (TIntegral)((TIntegral)m1_a.m_d(m1_a.index(row_m1_a, index)) *
			   (TAIntegral)m2_a.m_d(m2_a.index(row_m2_a, index)));
      }
    }
  }

  // type1: UPPER_TRIANGULAR
  //
  else if (type1 == Integral::UPPER_TRIANGULAR) {

    // type2: FULL
    //  multiply each element in the given column (and in the upper triangle)
    //  of the first matrix with its corresponding one in the given column
    //  of the second matrix, return the summation of the products
    //
    if (type2 == Integral::FULL) {
      for (int32 index = row_m1_a; index < ncols; index++) {
        sum += (TIntegral)((TIntegral)m1_a.m_d(m1_a.index(row_m1_a, index)) *
			   (TAIntegral)m2_a.m_d(m2_a.index(row_m2_a, index)));
      }      
    }

    // type2: SYMMETRIC
    //  multiply each element in the given column (and in the lower triangle)
    //  of the first matrix with its corresponding one (if it's in the upper
    //  triangle, use its symmetric value) in the given column
    //  of the second matrix, return the summation of the products
    // 
    else if (type2 == Integral::SYMMETRIC) {

      for (int32 index = row_m1_a; index < ncols; index++) {
	sum += (TIntegral)((TIntegral)m1_a.m_d(m1_a.index(row_m1_a, index)) *
			   (TAIntegral)m2_a.m_d(m2_a.index(row_m2_a, index)));
      }
    }

    // type2: LOWER_TRIANGULAR
    //
    else if (type2 == Integral::LOWER_TRIANGULAR) {

      // find the start index
      //
      int32 start_index = row_m1_a;
      last_index = row_m2_a;
      for (int32 index = start_index; index <= last_index; index++) {
	sum += (TIntegral)((TIntegral)m1_a.m_d(m1_a.index(row_m1_a, index)) *
			   (TAIntegral)m2_a.m_d(m2_a.index(row_m2_a, index)));
      }
    }

    // type2: UPPER_TRIANGULAR
    //
    else if (type2 == Integral::UPPER_TRIANGULAR) {

      // multiply upper triangular elements
      //
      int32 start_index = (row_m1_a < row_m2_a) ? row_m2_a : row_m1_a;
      for (int32 index = start_index; index < ncols; index++) {
	sum += (TIntegral)((TIntegral)m1_a.m_d(m1_a.index(row_m1_a, index)) *
			   (TAIntegral)m2_a.m_d(m2_a.index(row_m2_a, index)));
      }
    }
  }

  // exit gracefully
  //
  return sum;
}

// explicit instantiations
//
// we only allow complex matrices to operate with other complex matrices
//
#ifndef ISIP_TEMPLATE_complex
template ISIP_TEMPLATE_T1
MMatrixMethods::multiplyRowByRow<ISIP_TEMPLATE_TARGET, Byte, byte8>
(const MMatrix<ISIP_TEMPLATE_TARGET>&, const MMatrix<ISIP_TEMPLATE_TARGET>&,
 const MMatrix<Byte, byte8>&, int32, int32);

template ISIP_TEMPLATE_T1
MMatrixMethods::multiplyRowByRow<ISIP_TEMPLATE_TARGET, Ushort, uint16>
(const MMatrix<ISIP_TEMPLATE_TARGET>&, const MMatrix<ISIP_TEMPLATE_TARGET>&,
 const MMatrix<Ushort, uint16>&, int32, int32);

template ISIP_TEMPLATE_T1
MMatrixMethods::multiplyRowByRow<ISIP_TEMPLATE_TARGET, Ulong, uint32>
(const MMatrix<ISIP_TEMPLATE_TARGET>&, const MMatrix<ISIP_TEMPLATE_TARGET>&,
 const MMatrix<Ulong, uint32>&, int32, int32);

template ISIP_TEMPLATE_T1
MMatrixMethods::multiplyRowByRow<ISIP_TEMPLATE_TARGET, Ullong, uint64>
(const MMatrix<ISIP_TEMPLATE_TARGET>&, const MMatrix<ISIP_TEMPLATE_TARGET>&,
 const MMatrix<Ullong, uint64>&, int32, int32);

template ISIP_TEMPLATE_T1
MMatrixMethods::multiplyRowByRow<ISIP_TEMPLATE_TARGET, Short, int16>
(const MMatrix<ISIP_TEMPLATE_TARGET>&, const MMatrix<ISIP_TEMPLATE_TARGET>&,
 const MMatrix<Short, int16>&, int32, int32);

template ISIP_TEMPLATE_T1
MMatrixMethods::multiplyRowByRow<ISIP_TEMPLATE_TARGET, Long, int32>
(const MMatrix<ISIP_TEMPLATE_TARGET>&, const MMatrix<ISIP_TEMPLATE_TARGET>&,
 const MMatrix<Long, int32>&, int32, int32);

template ISIP_TEMPLATE_T1
MMatrixMethods::multiplyRowByRow<ISIP_TEMPLATE_TARGET, Llong, int64>
(const MMatrix<ISIP_TEMPLATE_TARGET>&, const MMatrix<ISIP_TEMPLATE_TARGET>&,
 const MMatrix<Llong, int64>&, int32, int32);

template ISIP_TEMPLATE_T1
MMatrixMethods::multiplyRowByRow<ISIP_TEMPLATE_TARGET, Float, float32>
(const MMatrix<ISIP_TEMPLATE_TARGET>&, const MMatrix<ISIP_TEMPLATE_TARGET>&,
 const MMatrix<Float, float32>&, int32, int32);

template ISIP_TEMPLATE_T1
MMatrixMethods::multiplyRowByRow<ISIP_TEMPLATE_TARGET, Double, float64>
(const MMatrix<ISIP_TEMPLATE_TARGET>&, const MMatrix<ISIP_TEMPLATE_TARGET>&,
 const MMatrix<Double, float64>&, int32, int32);
#endif

#ifdef ISIP_TEMPLATE_complex
template ISIP_TEMPLATE_T1
MMatrixMethods::multiplyRowByRow<ISIP_TEMPLATE_TARGET, ComplexLong, complexlong>
(const MMatrix<ISIP_TEMPLATE_TARGET>&, const MMatrix<ISIP_TEMPLATE_TARGET>&,
 const MMatrix<ComplexLong, complexlong>&, int32, int32);

template ISIP_TEMPLATE_T1
MMatrixMethods::multiplyRowByRow<ISIP_TEMPLATE_TARGET, ComplexFloat, complexfloat>
(const MMatrix<ISIP_TEMPLATE_TARGET>&, const MMatrix<ISIP_TEMPLATE_TARGET>&,
 const MMatrix<ComplexFloat, complexfloat>&, int32, int32);

template ISIP_TEMPLATE_T1
MMatrixMethods::multiplyRowByRow<ISIP_TEMPLATE_TARGET, ComplexDouble, complexdouble>
(const MMatrix<ISIP_TEMPLATE_TARGET>&, const MMatrix<ISIP_TEMPLATE_TARGET>&,
 const MMatrix<ComplexDouble, complexdouble>&, int32, int32);
#endif
