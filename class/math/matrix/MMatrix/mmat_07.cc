// file: $isip/class/math/matrix/MMatrix/mmat_07.cc
// version: $Id: mmat_07.cc 7886 2002-03-12 22:29:02Z zheng $
//

// isip include files
//
#include "MMatrixMethods.h"
#include "MMatrix.h"
#include <typeinfo>

// method: inverse
//
// arguments:
//  MMatrix<TScalar, TIntegral>& this: (output) class operand
//  const MMatrix<TScalar, TIntegral>& m: (input) matrix operand
//
// return: a bool8 value indicating status
//
// this method gets the inverse of the input matrix and assign it to
// the current matrix
//
template<class TScalar, class TIntegral>
bool8 MMatrixMethods::inverse(MMatrix<TScalar, TIntegral>& this_a, 
				const MMatrix<TScalar, TIntegral>& m_a)  {

  // this variant uses float64 internally, it is defined only for float
  // and float64 matrices
  //
#ifdef ISIP_TEMPLATE_fp
  
  // declare local variables
  //
  int32 nrows = m_a.nrows_d;
  int32 ncols = m_a.ncols_d;
  
  // condition: the two input matrices are same
  //  if the current matrix is same as input matrix, assign the current
  //  matrix to a temporary matrix and call inverse
  //
  if (&this_a == &m_a) {
    MMatrix<TScalar, TIntegral> tmp(m_a);
    return this_a.inverse(tmp);
  }
  
  // condition: non-square matrix
  //
  if (!m_a.isSquare()) {
    m_a.debug(L"m_a");
    this_a.debug(L"this_a");    
    return Error::handle(name(), L"inverse", Error::ARG, __FILE__, __LINE__);
  }
  
  // get the type of the input matrix
  //
  int32 type = m_a.getType();

  // get the type of the output matrix
  //
  Integral::MTYPE out_type = this_a.getType();

  // create space in the current matrix
  //
  this_a.setDimensions(m_a, false, m_a.type_d);
    
  // if the determinant is zero then error as the matrix is a
  // singular matrix
  //  
  if (m_a.isSingular()) {
    m_a.debug(L"m_a");    
    this_a.debug(L"this_a");    
    return Error::handle(name(), L"inverse", 
			 MMatrix<TScalar, TIntegral>::ERR_SINGLR, 
			 __FILE__, __LINE__, Error::WARNING);
  }
  
  // type: DIAGONAL
  //
  if (type == Integral::DIAGONAL) {
    
    // compute the number of rows of the input matrix
    //
    int32 nrows = m_a.getNumRows();

    // create space in the current matrix
    //
    this_a.setDimensions(m_a, false, m_a.type_d);
    
    // compute inverse - this can be computed simply by taking the
    // inverse of the elements of the input matrix. these elements are
    // not zero, otherwise the matrix would be singular.
    //
    for (int32 row = 0; row < nrows; row++) {
      this_a.m_d(row) = 1 / (m_a.m_d(row));
    }
  }
  
  // type: FULL
  //
  else if (type == Integral::FULL) {
    
    // create a temporary float64 matrix to hold the input matrix
    //
    MMatrix<Double, float64> a;
    a.assign(m_a);
    
    // initially store the identity matrix in current matrix. after the last
    // pass this_a will be replaced by the inverse of a.
    //
    this_a.makeIdentity(nrows, Integral::FULL);
    
    // initialize the value of the determinant
    //
    float64 det = 1;
    
    // start computing inverse matrix - the current pivot row is
    // ipass, for each pass, first find the maximum element in the
    // pivot column
    //
    for (int32 ipass = 0; ipass < nrows; ipass++) {
      int32 imx = ipass;
      for (int32 irow = ipass; irow < nrows; irow++) {
	if (fabs(a.getValue(irow, ipass)) > fabs(a.getValue(imx, ipass))) {
	  imx = irow;
	}
      }
      
      // interchange the elements of row ipass and row imx in both a and this_a
      //
      if (imx != ipass) {
	for (int32 icol = 0; icol < nrows; icol++) {
	  
	  float64 temp = this_a.getValue(ipass, icol);
	  this_a.setValue(ipass, icol, this_a.getValue(imx, icol));
	  this_a.setValue(imx, icol, temp);
	  if (icol >= ipass) {
	    temp = a.getValue(ipass, icol);
	    a.setValue(ipass, icol, a.getValue(imx, icol));
	    a.setValue(imx, icol, temp);
	  }
	}
      }
      
      // the current pivot is now a.getValue(ipass, ipass) - the determinant
      // is the product of the pivot elements
      //
      float64 pivot = a.getValue(ipass, ipass);
      
      det = det * pivot;
      if (det == 0) {
	this_a.debug(L"this_a");	
	return Error::handle(name(), L"inverse", 
			     MMatrix<TScalar, TIntegral>::ERR_SINGLR, 
			     __FILE__, __LINE__, Error::WARNING);
      }

      // normalize the pivot row by dividing across by the pivot element
      //
      for (int32 icol = 0; icol < nrows; icol++) { 
	this_a.setValue(ipass, icol, this_a.getValue(ipass, icol) / pivot);
	if (icol >= ipass) {
	  a.setValue(ipass, icol, a.getValue(ipass, icol) / pivot);
	}
      }
      
      // now replace each row by the row plus a multiple of the
      // pivot row with a factor chosen so that the element of a on
      // the pivot column is 0
      //
      float64 factor = 0;
      for (int32 irow = 0; irow < nrows; irow++) {
	
	if (irow != ipass) {
	  factor = a.getValue(irow, ipass);
	}
	
	for (int32 icol = 0; icol < nrows; icol++) {
	  if (irow != ipass) {
	    this_a.setValue(irow, icol, this_a.getValue(irow, icol) -
			  factor * this_a.getValue(ipass, icol));
	    a.setValue(irow, icol, a.getValue(irow, icol) -
		       factor * a.getValue(ipass, icol));
	  }
	}
      }
    }
  }
  
  // type: SYMMETRIC, LOWER_TRIANGULAR, UPPER_TRIANGULAR
  //  for symmetric and triangular matrix, change them into a full matrix
  //  and get the inverse
  //
  else if ((type == Integral::SYMMETRIC) ||
	   (type == Integral::LOWER_TRIANGULAR) ||
	   (type == Integral::UPPER_TRIANGULAR)) {
    this_a.assign(m_a, Integral::FULL);
    this_a.inverse();
  }
  
  // type: SPARSE
  //
  else {
    
    // declare temporary sparse matrix to hold the minor, and use this_a
    // to perform cofactor matrix
    //
    MMatrix<TScalar, TIntegral> mat_minor(nrows - 1, ncols - 1,
					  Integral::SPARSE);
    this_a.clear(Integral::RETAIN);
    
    // declare local variable
    //
    int32 length = 0;
    
    // compute determinant of input matrix
    //
    float64 det_in = m_a.determinant();
      
    // compute matrix of co-factor for input matrix
    //
    // loop over all the elements of matrix
    //
    for (int32 i = 0; i < nrows; i++) {
      for (int32 j = 0; j < ncols; j++) {
	
	// call minor of the element at this (i, j) position
	//
	m_a.getMinor(mat_minor, i, j);
	
	// calculate the determinant of minor matrix
	//
	float64 det = mat_minor.determinant();

	// check if the matrix is non-singular, if it is then compute inverse
	//
	if (det != 0) {
	  
	  // increasing the number of elements
	  //
	  length++;
	  
	  // checking sign of the elements and assigning it to
	  // their determinant to get the cofactor matrix
	  //
	  if ((i + j) % 2 == 0) {
	    
	    // assign positive sign if sum of row index and column
	    // index is even
	    // 
	    this_a.setValue(i, j, det);
	  }
	  
	  else {
	    
	    // assign negative sign if sum of row index and column
	    // index is odd
	    // 
	    this_a.setValue(i, j, -det);
	  }
	}
      }
    }
    
    // gives adjoint matrix, which is, transpose of co-factor matrix
    //
    this_a.transpose();
    this_a.div(det_in);
  }

  // solve the round-off problem during inverse computation
  //  1. for symmtric, copy the lower triangular part to upper triangular
  //     part, making it completely symmetric
  //  2. for lower triangular, set zeros in complete upper part, in case
  //     some non-zero but very close to zero elements exist;
  //  3. for upper triangular, set zeros in complete lower part, in case
  //     some non-zero but very close to zero elements exist;
  //
  if (out_type == Integral::SYMMETRIC) {
    for (int32 row = 0; row < nrows; row++) {
      for (int32 col = row + 1; col < ncols; col++) {
	this_a.setValue(row, col, this_a(col, row));
      }
    }
  }
  else if (out_type == Integral::LOWER_TRIANGULAR) {
    for (int32 row = 0; row < nrows; row++) {
      for (int32 col = row + 1; col < ncols; col++) {
	this_a.setValue(row, col, 0);
      }
    }
  }
  else if (out_type == Integral::UPPER_TRIANGULAR) {
    for (int32 row = 0; row < nrows; row++) {
      for (int32 col = 0; col < row; col++) {
	this_a.setValue(row, col, 0);
      }
    }
  }
  
  // change back to the oringinal type
  //
  if (!this_a.changeType(out_type)) {
    this_a.debug(L"this_a");    
    return Error::handle(name(), L"inverse",
			 MMatrix<TScalar, TIntegral>::ERR_OPTYPE,
			 __FILE__, __LINE__);
  }
  
  // exit gracefully
  //
  return true;

#endif

  // this variant uses complexdouble internally, it is defined only
  // for complexfloat and complexdouble matrices
  //
#ifdef ISIP_TEMPLATE_complex
#ifndef ISIP_TEMPLATE_ComplexLong_complexlong

  // declare local variables
  //
  int32 nrows = m_a.nrows_d;
  int32 ncols = m_a.ncols_d;
  
  // condition: the two input matrices are same
  //  if the current matrix is same as input matrix, assign the current
  //  matrix to a temporary matrix and call inverse
  //
  if (&this_a == &m_a) {
    MMatrix<TScalar, TIntegral> tmp(m_a);
    return this_a.inverse(tmp);
  }
  
  // condition: non-square matrix
  //
  if (!m_a.isSquare()) {
    m_a.debug(L"m_a");    
    this_a.debug(L"this_a");    
    return Error::handle(name(), L"inverse", Error::ARG, __FILE__, __LINE__);
  }
  
  // get the type of the input matrix
  //
  int32 type = m_a.getType();

  // get the type of the output matrix
  //
  Integral::MTYPE out_type = this_a.getType();

  // create space in the current matrix
  //
  this_a.setDimensions(m_a, false, m_a.type_d);
    
  // if the determinant is zero then error as the matrix is a
  // singular matrix
  //  
  if (m_a.isSingular()) {
    m_a.debug(L"m_a");    
    this_a.debug(L"this_a");    
    return Error::handle(name(), L"inverse", 
			 MMatrix<TScalar, TIntegral>::ERR_SINGLR, 
			 __FILE__, __LINE__, Error::WARNING);
  }
  
  // type: DIAGONAL
  //
  if (type == Integral::DIAGONAL) {
    
    // compute the number of rows of the input matrix
    //
    int32 nrows = m_a.getNumRows();

    // create space in the current matrix
    //
    this_a.setDimensions(m_a, false, m_a.type_d);
    
    // compute inverse - this can be computed simply by taking the
    // inverse of the elements of the input matrix. these elements are
    // not zero, otherwise the matrix would be singular.
    //
    for (int32 row = 0; row < nrows; row++) {
      this_a.m_d(row) = (TIntegral)1 / (m_a.m_d(row));
    }
  }
  
  // type: FULL
  //
  else if (type == Integral::FULL) {
    
    // create a temporary float64 matrix to hold the input matrix
    //
    MMatrix<ComplexDouble, complexdouble> a;
    a.assign(m_a);
    
    // initially store the identity matrix in current matrix. after the last
    // pass this_a will be replaced by the inverse of a.
    //
    this_a.makeIdentity(nrows, Integral::FULL);
    
    // initialize the value of the determinant
    //
    complexdouble det = 1;
    
    // start computing inverse matrix - the current pivot row is
    // ipass, for each pass, first find the maximum element in the
    // pivot column
    //
    for (int32 ipass = 0; ipass < nrows; ipass++) {
      int32 imx = ipass;
      for (int32 irow = ipass; irow < nrows; irow++) {
	
	ComplexDouble abs_irow, abs_imx;
	ComplexDouble temp_irow, temp_imx;	

	temp_irow = a.getValue(irow, ipass);
	temp_imx = a.getValue(imx, ipass);
	abs_irow = temp_irow.abs();
	abs_imx = temp_imx.abs();
	
	if (abs_irow > abs_imx) {
	  imx = irow;
	}
      }
      
      // interchange the elements of row ipass and row imx in both a and this_a
      //
      if (imx != ipass) {
	for (int32 icol = 0; icol < nrows; icol++) {
	  
	  complexdouble temp = this_a.getValue(ipass, icol);
	  this_a.setValue(ipass, icol, this_a.getValue(imx, icol));
	  this_a.setValue(imx, icol, (TIntegral)temp);
	  if (icol >= ipass) {
	    temp = a.getValue(ipass, icol);
	    a.setValue(ipass, icol, a.getValue(imx, icol));
	    a.setValue(imx, icol, temp);
	  }
	}
      }
      
      // the current pivot is now a.getValue(ipass, ipass) - the determinant
      // is the product of the pivot elements
      //
      complexdouble pivot = a.getValue(ipass, ipass);
      
      det = det * pivot;
      if (det == 0) {
	this_a.debug(L"this_a");	
	return Error::handle(name(), L"inverse", 
			     MMatrix<TScalar, TIntegral>::ERR_SINGLR, 
			     __FILE__, __LINE__, Error::WARNING);
      }

      // normalize the pivot row by dividing across by the pivot element
      //
      for (int32 icol = 0; icol < nrows; icol++) { 
	this_a.setValue(ipass, icol, this_a.getValue(ipass, icol) / pivot);
	if (icol >= ipass) {
	  a.setValue(ipass, icol, a.getValue(ipass, icol) / pivot);
	}
      }
      
      // now replace each row by the row plus a multiple of the
      // pivot row with a factor chosen so that the element of a on
      // the pivot column is 0
      //
      complexdouble factor = 0;
      for (int32 irow = 0; irow < nrows; irow++) {
	
	if (irow != ipass) {
	  factor = a.getValue(irow, ipass);
	}
	
	for (int32 icol = 0; icol < nrows; icol++) {
	  if (irow != ipass) {
	    this_a.setValue(irow, icol, this_a.getValue(irow, icol) -
			  factor * this_a.getValue(ipass, icol));
	    a.setValue(irow, icol, a.getValue(irow, icol) -
		       factor * a.getValue(ipass, icol));
	  }
	}
      }
    }
  }
  
  // type: SYMMETRIC, LOWER_TRIANGULAR, UPPER_TRIANGULAR
  //  for symmetric and triangular matrix, change them into a full matrix
  //  and get the inverse
  //
  else if ((type == Integral::SYMMETRIC) ||
	   (type == Integral::LOWER_TRIANGULAR) ||
	   (type == Integral::UPPER_TRIANGULAR)) {
    this_a.assign(m_a, Integral::FULL);
    this_a.inverse();
  }
  
  // type: SPARSE
  //
  else {
    
    // declare temporary sparse matrix to hold the minor, and use this_a
    // to perform cofactor matrix
    //
    MMatrix<TScalar, TIntegral> mat_minor(nrows - 1, ncols - 1,
					  Integral::SPARSE);
    this_a.clear(Integral::RETAIN);
    
    // declare local variable
    //
    int32 length = 0;
    
    // compute determinant of input matrix
    //
    complexdouble det_in = m_a.determinant();
      
    // compute matrix of co-factor for input matrix
    //
    // loop over all the elements of matrix
    //
    for (int32 i = 0; i < nrows; i++) {
      for (int32 j = 0; j < ncols; j++) {
	
	// call minor of the element at this (i, j) position
	//
	m_a.getMinor(mat_minor, i, j);
	
	// calculate the determinant of minor matrix
	//
	complexdouble det = mat_minor.determinant();

	// check if the matrix is non-singular, if it is then compute inverse
	//
	if (det != 0) {
	  
	  // increasing the number of elements
	  //
	  length++;
	  
	  // checking sign of the elements and assigning it to
	  // their determinant to get the cofactor matrix
	  //
	  if ((i + j) % 2 == 0) {
	    
	    // assign positive sign if sum of row index and column
	    // index is even
	    // 
	    this_a.setValue(i, j, (TScalar)det);
	  }
	  
	  else {
	    
	    // assign negative sign if sum of row index and column
	    // index is odd
	    // 
	    this_a.setValue(i, j, (TScalar)-det);
	  }
	}
      }
    }
    
    // gives adjoint matrix, which is, transpose of co-factor matrix
    //
    this_a.transpose();
    this_a.div(det_in);
  }

  // solve the round-off problem during inverse computation
  //  1. for symmtric, copy the lower triangular part to upper triangular
  //     part, making it completely symmetric
  //  2. for lower triangular, set zeros in complete upper part, in case
  //     some non-zero but very close to zero elements exist;
  //  3. for upper triangular, set zeros in complete lower part, in case
  //     some non-zero but very close to zero elements exist;
  //
  if (out_type == Integral::SYMMETRIC) {
    for (int32 row = 0; row < nrows; row++) {
      for (int32 col = row + 1; col < ncols; col++) {
	this_a.setValue(row, col, this_a(col, row));
      }
    }
  }
  else if (out_type == Integral::LOWER_TRIANGULAR) {
    for (int32 row = 0; row < nrows; row++) {
      for (int32 col = row + 1; col < ncols; col++) {
	this_a.setValue(row, col, (float64)0);
      }
    }
  }
  else if (out_type == Integral::UPPER_TRIANGULAR) {
    for (int32 row = 0; row < nrows; row++) {
      for (int32 col = 0; col < row; col++) {
	this_a.setValue(row, col, (float64)0);
      }
    }
  }
  
  // change back to the oringinal type
  //
  if (!this_a.changeType(out_type)) {
    this_a.debug(L"this_a");    
    return Error::handle(name(), L"inverse",
			 MMatrix<TScalar, TIntegral>::ERR_OPTYPE,
			 __FILE__, __LINE__);
  }
  
  // exit gracefully
  //
  return true;
#endif
#endif
  
  // for matrices other than float, float64, complexfloat and
  // complexdouble this should error
  //
  return Error::handle(name(), L"inverse", Error::TEMPLATE_TYPE,
		       __FILE__, __LINE__);
}

// explicit instantiations
//
template bool8   
MMatrixMethods::inverse<ISIP_TEMPLATE_TARGET>
(MMatrix<ISIP_TEMPLATE_TARGET>&, const MMatrix<ISIP_TEMPLATE_TARGET>&);

// method: determinant
//
// arguments:
//  const MMatrix<TScalar, TIntegral>& this: (output) class operand
//
// return: a TIntegral value containing the determinant
//
// this method calculates the determinant of the matrix, attempting to
// do this in an efficient way. a number of conditions are hardcoded,
// and the fallback algorithm is an LU decomposition.
//
template<class TScalar, class TIntegral>
TIntegral MMatrixMethods::determinant(const MMatrix<TScalar, TIntegral>& this_a) {

  // return error for unsigned matrices
  //
#ifdef ISIP_TEMPLATE_unsigned
  this_a.debug(L"this_a");  
  return Error::handle(name(), L"determinant", Error::TEMPLATE_TYPE, __FILE__, __LINE__);
#else
  
  // declare local variables
  //
  int32 nrows = this_a.nrows_d;
  TIntegral det = 1;

  // check arguments: the matrix must be square
  //
  if (!this_a.isSquare()) {
    this_a.debug(L"this_a");    
    Error::handle(name(), L"determinant()", Error::ARG, __FILE__, __LINE__);
  }

  // condition: nrows = 1 (one element), return its value
  //
  else if (nrows == 1) {
    det = this_a.getValue(0, 0);
  }

  // condition: (nrows == 2) and type is FULL
  //  do this efficiently using direct indexing
  //
  else if ((nrows == 2) && (this_a.type_d == Integral::FULL)) {
    det = this_a.m_d(3) * this_a.m_d(0) - this_a.m_d(1) * this_a.m_d(2);
  }

  // condition: (nrows == 2) and type is not FULL
  //  do this efficiently using indirect indexing
  //
  else if ((nrows == 2) && (this_a.type_d != Integral::FULL)) {
    // TIntegral v0 = this_a(0, 0);
    // TIntegral v1 = this_a(0, 1);
    // TIntegral v2 = this_a(1, 0);
    // TIntegral v3 = this_a(1, 1);    
    det = this_a(1, 1) * this_a(0, 0) - this_a(1, 0) * this_a(0, 1);
  }

  // condition: (nrows == 3) and type is FULL
  //  do this using direct indexing
  //
  else if ((nrows == 3) && (this_a.type_d == Integral::FULL)) {
    det =
      this_a.m_d(0) * this_a.m_d(4) * this_a.m_d(8) +
      this_a.m_d(1) * this_a.m_d(5) * this_a.m_d(6) +
      this_a.m_d(2) * this_a.m_d(3) * this_a.m_d(7) -
      this_a.m_d(6) * this_a.m_d(4) * this_a.m_d(2) -
      this_a.m_d(7) * this_a.m_d(5) * this_a.m_d(0) -
      this_a.m_d(8) * this_a.m_d(3) * this_a.m_d(1);
  }

  // condition: (nrows == 3) and type is not FULL
  //  do this efficiently using indirect indexing. this is still faster
  //  than LU decomposition.
  //
  else if ((nrows == 3) && (this_a.type_d != Integral::FULL)) {
    TIntegral val0 = this_a.getValue(0, 0);
    TIntegral val1 = this_a.getValue(0, 1);
    TIntegral val2 = this_a.getValue(0, 2);    
    TIntegral val3 = this_a.getValue(1, 0);
    TIntegral val4 = this_a.getValue(1, 1);
    TIntegral val5 = this_a.getValue(1, 2);
    TIntegral val6 = this_a.getValue(2, 0);
    TIntegral val7 = this_a.getValue(2, 1);
    TIntegral val8 = this_a.getValue(2, 2);

    TIntegral v0 = val0 * val4 * val8;
    TIntegral v1 = val1 * val5 * val6;
    TIntegral v2 = val2 * val3 * val7;
    TIntegral v3 = val6 * val4 * val2;
    TIntegral v4 = val7 * val5 * val0;
    TIntegral v5 = val8 * val3 * val1;

    det = v0 + v1 + v2 - v3 -v4 -v5;
  }

  // condition: type is DIAGONAL
  //  the determinant is equal to the product of the diagonal elements
  //
  else if (this_a.type_d == Integral::DIAGONAL) {
    for (int32 row = 0; row < nrows; row++) {
      det *= this_a.m_d(row);
    }
  }
  
  // type: LOWER_TRIANGULAR, UPPER_TRIANGULAR
  //  compute the products of all the diagonal elements. we can do this
  //  using direct indexing into the storage vector since the diagnonal
  //  elements are the same. the increment is initialized to a value
  //  of 2 for matrices of order 2 or greater.
  //
  else if (this_a.type_d == Integral::LOWER_TRIANGULAR ||
	   this_a.type_d == Integral::UPPER_TRIANGULAR) {
    for (int32 row = 0, index = 0; row < nrows; row++) {
      det *= this_a.m_d(index);
      index += 2 + row;
    }
  }

  // for floating point types, use LU decomposition to quickly arrive
  // at the determinant.
  //

  // type: (type is FULL or SYMMETRIC) and (nrows > 3)
  //
  else if (this_a.type_d == Integral::FULL ||
	   this_a.type_d == Integral::SYMMETRIC) {

    // for float and float64 matrices, we use LU decomposition to
    // compute determinant as it is much efficient
    //
#ifdef ISIP_TEMPLATE_fp

    // using LU decomposition method to compute determinant efficiently
    //
    det = this_a.determinantLU();

    // for other matrices, we use minor method as LU decomposition is
    // defined only for float and float64 matrices
#else
    
    det = this_a.determinantMinor();
#endif
  }

  // type: (type is SPARSE) and (nrows > 3)
  //
  else {

    // using getMinor method to compute determinant
    //
    det = this_a.determinantMinor();
  }

  // exit gracefully: return the value
  //
  return (TIntegral)det;
#endif
}

// explicit instantiations
//
template ISIP_TEMPLATE_T1
MMatrixMethods::determinant<ISIP_TEMPLATE_TARGET>
(const MMatrix<ISIP_TEMPLATE_TARGET>&);

// method: transpose
//
// arguments:
//  MMatrix<TScalar, TIntegral>& this: (output) class operand
//  const MMatrix<TScalar, TIntegral>& m: (input) matrix operand
//
// return: a bool8 value indicating status
//
// this method computes the transpose of the input matrix and assigns
// it to the current matrix. note that this method will change the
// type of the matrix: an upper triangular matrix will become lower
// triangular, a lower will become upper. all other types remain
// unchanged.
//
template<class TScalar, class TIntegral>
bool8 MMatrixMethods::transpose(MMatrix<TScalar, TIntegral>& this_a, 
				  const MMatrix<TScalar, TIntegral>& m_a)  {

  // type: DIAGONAL, SYMMETRIC
  //  just assign the input matrix to the current matrix since the
  //  transpose is the same.
  //
  if (m_a.type_d == Integral::DIAGONAL ||
      m_a.type_d == Integral::SYMMETRIC)  {
    return this_a.assign(m_a);
  }

  // condition: the two input matrices are same
  //  if the current matrix is same as input matrix, assign the current
  //  matrix to a temporary matrix and call transpose
  //
  if (&this_a == &m_a) {
    MMatrix<TScalar, TIntegral> tmp(this_a);
    return this_a.transpose(tmp);
  }

  // change the row dimension and column dimension of the input matrix
  //
  int32 nrows = m_a.getNumColumns();
  int32 ncols = m_a.getNumRows();

  // type: FULL
  //  for a full matrix, create space in the output matrix,
  //  and manually copy the elements.
  //
  if (m_a.type_d == Integral::FULL) {
    this_a.setDimensions(nrows, ncols, false, m_a.type_d);
    for (int32 row = 0; row < nrows; row++) {
      for (int32 col = 0; col < ncols; col++) {
        this_a.m_d(this_a.index(row, col)) = m_a.m_d(m_a.index(col, row));
      }
    }
  }
  
  // type: LOWER_TRIANGULAR
  //  our storage mode for lower and triangle matrices guarantees that
  //  one is the transpose of the other.
  //
  else if (m_a.type_d == Integral::LOWER_TRIANGULAR) {
    this_a.setDimensions(nrows, ncols, false, Integral::UPPER_TRIANGULAR);
    this_a.m_d.assign(m_a.m_d);
  }

  // type: UPPER_TRIANGULAR
  //  our storage mode for lower and triangle matrices guarantees that
  //  one is the transpose of the other.
  //
  else if (m_a.type_d == Integral::UPPER_TRIANGULAR) {
    this_a.setDimensions(nrows, ncols, false, Integral::LOWER_TRIANGULAR);
    this_a.m_d.assign(m_a.m_d);
  }
  
  // type: SPARSE
  //  to reach this point for a sparse matrix, we must already have
  //  a copy of the matrix, so we simply have to swap rows and columns.
  //
  else {
    
    // set up a SPARSE matrix and copy the data. transform rows
    // and columns as needed.
    //
    this_a.setDimensions(nrows, ncols, false, Integral::SPARSE);
    this_a.m_d.assign(m_a.m_d);
    this_a.row_index_d.assign(m_a.col_index_d);
    this_a.col_index_d.assign(m_a.row_index_d);

    // sort the rows and columns
    //
    this_a.sortSparse();
  }

  // exit gracefully
  //
  return true;
}

// explicit instantiations
//
template bool8   
MMatrixMethods::transpose<ISIP_TEMPLATE_TARGET>
(MMatrix<ISIP_TEMPLATE_TARGET>&, const MMatrix<ISIP_TEMPLATE_TARGET>&);

// method: trace
//
// arguments:
//  const MMatrix<TScalar, TIntegral>& this: (input) class operand
//
// return: a TIntegral value containing the value of the trace
//
template<class TScalar, class TIntegral>
TIntegral MMatrixMethods::trace(const MMatrix<TScalar, TIntegral>& this_a) {

  // condition: non-square matrix
  //
  if (!this_a.isSquare()) {
    this_a.debug(L"this_a");    
    return Error::handle(name(), L"trace", Error::ARG, __FILE__, __LINE__);
  }

  // declare local variables
  //
  int32 nrows = this_a.nrows_d;
  int32 ncols = this_a.ncols_d;  
  TIntegral sum = 0;

  // type: FULL
  //  do this efficiently using direct indexing
  //
  if (this_a.type_d == Integral::FULL) {
    for (int32 row = 0, index = 0; row < nrows; row++) {
      sum += this_a.m_d(index);
      index += ncols + 1;
    }
  }

  // type: DIAGONAL
  //  do this efficiently using a vector function
  //
  else if (this_a.type_d == Integral::DIAGONAL) {
    sum = this_a.sum();
  }

  // type: SYMMETRIC, LOWER_TRIANGULAR, UPPER_TRIANGULAR
  //  do this efficiently using direct indexing
  //
  else if ((this_a.type_d == Integral::SYMMETRIC) ||
	   (this_a.type_d == Integral::LOWER_TRIANGULAR) ||
	   (this_a.type_d == Integral::UPPER_TRIANGULAR)) {
    for (int32 row = 0, index = 0; row < nrows; row++) {
      sum += this_a.m_d(index);
      index += 2 + row;
    }
  }

  // type: SPARSE
  //  use indirect addressing through the index function
  //  
  else {
    
    // loop over rows and add the diagonal elements
    //
    for (int32 row = 0; row < this_a.nrows_d; row++) {
      sum += this_a.getValue(row, row);
    }
  }

  // exit gracefully
  //
  return sum;
}

// explicit instantiations
//
template ISIP_TEMPLATE_T1   
MMatrixMethods::trace<ISIP_TEMPLATE_TARGET>
(const MMatrix<ISIP_TEMPLATE_TARGET>&);

// method: rank
//
// arguments:
//  const MMatrix<TScalar, TIntegral>& this: (input) class operand
//
// return: a value containing the rank of the matrix
//
// this method calculates the rank of a matrix (someday soon...)
//
template<class TScalar, class TIntegral>
int32 MMatrixMethods::rank(const MMatrix<TScalar, TIntegral>& this_a) {

  // this method is defined only for float and float64 matrices 
  //
#ifdef ISIP_TEMPLATE_fp
  
  MMatrix<TScalar, TIntegral> u;  // row orthonormal
  MMatrix<TScalar, TIntegral> w;  // singular value matrix
  MMatrix<TScalar, TIntegral> v;  // column orthonormal

  this_a.decompositionSVD(u, w, v);
  
  int32 m = w.getNumRows(); // w has same row and column 
  int32 i;

  // set up near-singular values.
  //
  TIntegral wmin = 0.0;
  TIntegral wmax = this_a.max();

  if (typeid(TIntegral) == typeid(float64)) {
    wmin = wmax * m * w.THRESH_SINGULAR_DOUBLE;
  }
  else if (typeid(TIntegral) == typeid(float32)) {
    wmin = wmax * m * w.THRESH_SINGULAR_FLOAT;
  }

  // check the data in w matrix
  //
  for (i = 0; i < m; i++) {
    if (w.getValue(i, i) < wmin) break;
  }

  return i;
  
#else
  return Error::handle(name(), L"rank", Error::TEMPLATE_TYPE,
		       __FILE__, __LINE__);
#endif

  this_a.debug(L"this_a");

  return Error::handle(name(), L"rank", Error::NOT_IMPLEM, __FILE__, __LINE__);

}

// explicit instantiations
//
template int32
MMatrixMethods::rank<ISIP_TEMPLATE_TARGET>
(const MMatrix<ISIP_TEMPLATE_TARGET>&);

// method: swapRows
//
// arguments:
//  MMatrix<TScalar, TIntegral>& this: (output) class operand
//  const MMatrix<TScalar, TIntegral>& matrix: (input) source matrix
//  int32 row1: (input) first row for swap
//  int32 row2: (input) second row for swap
//
// return: a bool8 value indicating status
//
// this method swaps two rows of the input matrix. the input matrix can only
// be full or sparse, since this operation will change the type of
// a diagonal, symmetric, or triangular matrix.
//
template<class TScalar, class TIntegral>
bool8 MMatrixMethods::swapRows(MMatrix<TScalar, TIntegral>& this_a, 
				 const MMatrix<TScalar, TIntegral>& matrix_a, 
				 int32 row1_a, int32 row2_a) {

  // check the arguments
  //
  if (row1_a == row2_a) {
    return true;
  }
  else if ((row1_a < 0) || (row2_a < 0) ||
	   (row1_a >= matrix_a.nrows_d) || (row2_a >= matrix_a.nrows_d)) {
    this_a.debug(L"this_a");
    matrix_a.debug(L"matrix_a");    
    return Error::handle(name(), L"swapRows", Error::ARG, __FILE__, __LINE__);
  }

  // copy input matrix to output matrix
  //
  Integral::MTYPE old_type = this_a.type_d;
  if (&this_a != &matrix_a) {
    this_a.assign(matrix_a);
  }
  
  // implement this using getRow:
  //  create copies of the rows
  //
  MVector<TScalar, TIntegral> row1;
  MVector<TScalar, TIntegral> row2;
  this_a.getRow(row1, row1_a);
  this_a.getRow(row2, row2_a);

  // swap them
  //
  this_a.setRow(row1_a, row2);
  this_a.setRow(row2_a, row1);

  // restore the type
  //
  return this_a.changeType(old_type);
}

// explicit instantiations
//
template bool8
MMatrixMethods::swapRows<ISIP_TEMPLATE_TARGET>
(MMatrix<ISIP_TEMPLATE_TARGET>&, const MMatrix<ISIP_TEMPLATE_TARGET>&, int32, int32);

// method: swapColumns
//
// arguments:
//  MMatrix<TScalar, TIntegral>& this: (output) class operand
//  const MMatrix<TScalar, TIntegral>& matrix: (input) class operand
//  int32 col1: (input) first column for swap
//  int32 col2: (input) second column for swap
//
// return: a bool8 value indicating status
//
// this method swaps two columns of the input matrix and stores it
// into the output matrix. the input matrix can only be full or sparse,
// since this operation will change the type of a diagonal, symmetric,
// or triangular matrix.
//
template<class TScalar, class TIntegral>
bool8
MMatrixMethods::swapColumns(MMatrix<TScalar, TIntegral>& this_a, 
			    const MMatrix<TScalar, TIntegral>& matrix_a, 
			    int32 col1_a, int32 col2_a) {

  // check the arguments
  //
  if (col1_a == col2_a) {
    return true;
  }
  else if ((col1_a < 0) || (col2_a < 0) ||
	   (col1_a >= matrix_a.ncols_d) || (col2_a >= matrix_a.ncols_d)) {
    this_a.debug(L"this_a");
    matrix_a.debug(L"matrix_a");  
    return Error::handle(name(), L"swapColumns",
			 Error::ARG, __FILE__, __LINE__);
  }
  
  // copy input matrix to output matrix, save the type
  //
  Integral::MTYPE old_type = this_a.type_d;
  this_a.assign(matrix_a);
  
  // implement this using getColumn: create copies of the columns
  //
  MVector<TScalar, TIntegral> col1;
  MVector<TScalar, TIntegral> col2;
  this_a.getColumn(col1, col1_a);
  this_a.getColumn(col2, col2_a);

  // swap them
  //
  this_a.setColumn(col1_a, col2);
  this_a.setColumn(col2_a, col1);

  // exit gracefully
  //
  return this_a.changeType(old_type);
}

// explicit instantiations
//
template bool8
MMatrixMethods::swapColumns<ISIP_TEMPLATE_TARGET>
(MMatrix<ISIP_TEMPLATE_TARGET>&, const MMatrix<ISIP_TEMPLATE_TARGET>&, int32, int32);

// method: determinantLU
//
// arguments:
//  const MMatrix<TScalar, TIntegral>& this: (output) class operand
//
// return: a TIntegral value containing the determinant
//
// this method calculates the determinant of the matrix, attempting to
// do this by copying the matrix into a MMatrixDouble matrix and use
// LU decomposition as the fallback algorithm
//
// through the combination of division and subtraction in the LU
// decomposition method, we may potentially encounter precision problems
// in the LU calculations. elements on the diagonal that should be
// zero may be returned by the LU computation as very small (on the
// order of 1e-8 for floats and 1e-16 for doubles) non-zero numbers
// thus, we will floor these numbers.
//
// unfortunately, this means we will have to loop over the
// upper-triangular matrix's diagonal elements twice - once to find
// the dynamic range and once to zero out the elements which fall
// outside of an epsilon of the dynamic range. finding a way to move
// this flooring directly to the LU decomposition would be a better
// way to handle this.
//
template<class TScalar, class TIntegral>
TIntegral MMatrixMethods::determinantLU(const MMatrix<TScalar, TIntegral>& this_a) {

  // declare slack variables to control round-off error. The machine epsilon
  // for 32-bit floats is typically 3e-8. We back off of that by an order
  // of magnitude to give some breathing room.
  //
  static float64 det_slack_var = 0.0;

  if (typeid(TIntegral) == typeid(float32)) {
    det_slack_var = 3e-7;
  }
  else if (typeid(TIntegral) == typeid(float64)) {
    det_slack_var = 3e-15;
  }
  else {
    det_slack_var = 3e-7;
  }
  
  // declare local variables
  //
  MMatrix<TScalar, TIntegral> l;
  MMatrix<TScalar, TIntegral> u;
  MVector<Long, int32> index;
  int32 sign;

  this_a.decompositionLU(l, u, index, sign, 0);

  // get the mean of the elements on the diagonal of the upper-triangular
  //
  float64 mean = 0;
  for (int32 i = 0; i < this_a.nrows_d; i++) {
    mean += Integral::abs(u(i, i));
  }
  mean /= (float64)this_a.nrows_d;

  // get the minimum magnitude that we will accept - make sure that the
  // floor is reasonably close to zero
  //
  float64 floor = Integral::abs(mean) * det_slack_var;
  if (floor > det_slack_var) {
    floor = det_slack_var;
  }

  // loop over the diagonal elements again and zero out those that
  // are below the floor so int32 as the floor is reasonably close to zero
  //
  for (int32 i = 0; i < this_a.nrows_d; i++) {
    if (Integral::abs(u(i, i)) < floor) {
      return 0;
    }
  }
  
  // since the lower triangular component has 1's along the diagonal,
  // we can just calculate the determinant of the upper triangular
  // matrix. We have to make a special case for complex numbers so the
  // compiler does not complain
  //
#ifdef ISIP_TEMPLATE_complex
  return ((TIntegral)sign * u.determinant());
#else
  return (sign * u.determinant());
#endif
}

// explicit instantiations
//
template ISIP_TEMPLATE_T1
MMatrixMethods::determinantLU<ISIP_TEMPLATE_TARGET>
(const MMatrix<ISIP_TEMPLATE_TARGET>&);

// method: determinantMinor
//
// arguments:
//  const MMatrix<TScalar, TIntegral>& this: (output) class operand
//
// return: a TIntegral value containing the determinant
//
// this method calculates the determinant of a sparse matrix, attempting to
// do this using recursive getMinor method
//
template<class TScalar, class TIntegral>
TIntegral MMatrixMethods::determinantMinor(const MMatrix<TScalar, TIntegral>& this_a) {

  // declare local variables
  //
  TIntegral det = 0;

  // type: FULL
  //
  if (this_a.type_d == Integral::FULL) {

    // define full matrix to hold the minor matrix
    //
    MMatrix<TScalar, TIntegral> mat_minor(this_a.nrows_d, this_a.ncols_d, 
					  Integral::FULL);

    // get the minor matrix and use recursive method to compute determinant
    //    
    int32 sign = 1;
    for (int i = 0; i < this_a.ncols_d; i++) {
      
      // get the minor matrix
      //
      this_a.getMinor(mat_minor, 0, i);
      if (sign == 1) {
	det += this_a.m_d(i) * mat_minor.determinant();
      }
      else {
	det -= this_a.m_d(i) * mat_minor.determinant();
      }
      sign = -sign;
    }
  }

  // type: SYMMETRIC
  //  for symmetric matrix, change it into a full matrix before calculating
  //  the determinant
  //
  else if (this_a.type_d == Integral::SYMMETRIC) {
    MMatrix<TScalar, TIntegral> temp;
    temp.assign(this_a, Integral::FULL);
    return (TIntegral)temp.determinant(); 
  }

  // type: SPARSE
  //
  else {
    
    // define row and column vectors
    //
    MVector<Long, int32> rows(this_a.nrows_d);
    MVector<Long, int32> cols(this_a.ncols_d);
    
    // define sparse matrix to hold the minor matrix
    //
    MMatrix<TScalar, TIntegral> mat_minor(this_a.nrows_d, this_a.ncols_d, 
					  Integral::SPARSE);
    
    // assigning number to every row and column of the real matrix
    //
    for (int32 i = 0; i < this_a.m_d.length(); i++) {
      rows(this_a.row_index_d(i)) += 1;
      cols(this_a.col_index_d(i)) += 1;
    }
    
    // initializing row_to_use (the row having lowest number of
    // non-zero elements) to zero
    //
    int32 row_to_use = 0;
    
    // if any row has all zeros then determinant is zero
    //
    if (rows.min(row_to_use) == 0) {
      return 0;
    }
    
    // if all rows have at least one non-zero element
    //
    else {
      for (int32 i = 0; i < this_a.ncols_d; i++) {
	
	// calculate only if the value is non-zero
	//
	TIntegral tmp_val = this_a.getValue(row_to_use, i);
	if (tmp_val != 0) {
	  
	  // compute the minor of the matrix
	  //
	  this_a.getMinor(mat_minor, row_to_use, i);
	  
	  // get the sign for a particular value and multiply value by
	  // the determinant of the minor to get the determinant
	  //
	  if (((row_to_use + i) % 2) == 0) {
	    det += mat_minor.determinant() * tmp_val;
	  }
	  else {
	    det -= mat_minor.determinant() * tmp_val;
	  }
	}
      }
    }
  }

  // exit gracefully: return the value
  //
  return (TIntegral)det;
}

// explicit instantiations
//
template ISIP_TEMPLATE_T1
MMatrixMethods::determinantMinor<ISIP_TEMPLATE_TARGET>
(const MMatrix<ISIP_TEMPLATE_TARGET>&);
