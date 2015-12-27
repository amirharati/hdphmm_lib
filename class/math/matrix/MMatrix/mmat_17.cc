// file: $isip/class/math/matrix/MMatrix/mmat_17.cc
// version: $Id: mmat_17.cc 10636 2007-01-26 22:18:09Z tm334 $
//

// isip include files
//
#include "MMatrixMethods.h"
#include "MMatrix.h"

// method: getDiagonal
//
// arguments:
//  const MMatrix<TScalar, TIntegral>& this: (input) class operand
//  MVector<TScalar, TIntegral>& vector: (output) diagonal values
//
// return: a bool8 value indicating status
//
template<class TScalar, class TIntegral>
bool8 MMatrixMethods::getDiagonal(const MMatrix<TScalar, TIntegral>& this_a,
				    MVector<TScalar, TIntegral>& vector_a) {

  // the matrix must be square
  //
  if (!this_a.isSquare()) {
    this_a.debug(L"this_a");
    return Error::handle(name(), L"getDiagonal", Error::ARG,
			 __FILE__, __LINE__);
  }
    
  // type: DIAGONAL
  //  simply copy the output matrix
  //
  if (this_a.type_d == Integral::DIAGONAL) {
    return vector_a.assign(this_a.m_d);
  }

  // type: non-DIAGONAL
  //
  else {

    // create output space
    //
    vector_a.setLength(this_a.nrows_d, false);

    // loop over all elements
    //
    for (int32 row = 0; row < this_a.nrows_d; row++) {
      vector_a(row) = this_a.getValue(row, row);
    }
  }
  
  // exit gracefully
  //
  return true;
}

// explicit instantiations
//
template bool8
MMatrixMethods::getDiagonal<ISIP_TEMPLATE_TARGET>
(const MMatrix<ISIP_TEMPLATE_TARGET>&, MVector<ISIP_TEMPLATE_TARGET>&);

// method: getLower
//
// arguments:
//  const MMatrix<TScalar, TIntegral>& this: (input) class operand
//  MMatrix<TScalar, TIntegral>& arg: (output) lower triangular values
//
// return: a bool8 value indicating status
//
// note that this method clears the output matrix
//
template<class TScalar, class TIntegral>
bool8 MMatrixMethods::getLower(const MMatrix<TScalar, TIntegral>& this_a,
				 MMatrix<TScalar, TIntegral>& arg_a) {

  // check for compatibility
  //
  if (((arg_a.type_d == Integral::DIAGONAL) && (!this_a.isDiagonal())) ||
      ((arg_a.type_d == Integral::UPPER_TRIANGULAR) &&
       (!this_a.isDiagonal())) ||
      ((arg_a.type_d == Integral::SYMMETRIC) && (!this_a.isDiagonal()))) {
    arg_a.debug(L"arg_a");    
    this_a.debug(L"this_a");    
    return Error::handle(name(), L"getLower", Error::ARG, __FILE__, __LINE__);
  }

  // check for both types being LOWER_TRIANGULAR (in which case this
  // method shouldn't even be called)
  //
  else if ((this_a.type_d == Integral::LOWER_TRIANGULAR) &&
	   (arg_a.type_d == Integral::LOWER_TRIANGULAR)) {
    arg_a.nrows_d = this_a.nrows_d;
    arg_a.ncols_d = this_a.ncols_d;
    return arg_a.m_d.assign(this_a.m_d);
  }

  // all other cases: loop over all elements and manually copy data
  //
  arg_a.setDimensions(this_a.nrows_d, this_a.ncols_d, false);
  arg_a.clear(Integral::RETAIN);

  for (int32 row = 0; row < this_a.nrows_d; row++) {
    for (int32 col = 0; col <= row; col++) {
      arg_a.setValue(row, col, this_a.getValue(row, col));
    }
  }
  
  // exit gracefully
  //
  return true;
}

// explicit instantiations
//
template bool8
MMatrixMethods::getLower<ISIP_TEMPLATE_TARGET>
(const MMatrix<ISIP_TEMPLATE_TARGET>&, MMatrix<ISIP_TEMPLATE_TARGET>&);

// method: getUpper
//
// arguments:
//  const MMatrix<TScalar, TIntegral>& this: (input) class operand
//  MMatrix<TScalar, TIntegral>& arg: (output) upper triangular values
//
// return: a bool8 value indicating status
//
// note that this method clears the output matrix
//
template<class TScalar, class TIntegral>
bool8 MMatrixMethods::getUpper(const MMatrix<TScalar, TIntegral>& this_a,
				 MMatrix<TScalar, TIntegral>& arg_a) {

  // check for compatibility:
  //  there are some constraints on when this method can be invoked.
  //  the destination matrix must be square,
  //  and not be the wrong type (UPPER_TRIANGULAR).
  //
  if (((arg_a.type_d == Integral::DIAGONAL) && (!this_a.isDiagonal())) ||
      ((arg_a.type_d == Integral::LOWER_TRIANGULAR) &&
       (!this_a.isDiagonal())) ||
      ((arg_a.type_d == Integral::SYMMETRIC) && (!this_a.isDiagonal()))) {
    arg_a.debug(L"arg_a");    
    this_a.debug(L"this_a");    
    return Error::handle(name(), L"getUpper", Error::ARG, __FILE__, __LINE__);
  }

  // check for both types being UPPER_TRIANGULAR (in which case this
  // method shouldn't even be called)
  //
  else if ((this_a.type_d == Integral::UPPER_TRIANGULAR) &&
	   (arg_a.type_d == Integral::UPPER_TRIANGULAR)) {
    arg_a.nrows_d = this_a.nrows_d;
    arg_a.ncols_d = this_a.ncols_d;
    return arg_a.m_d.assign(this_a.m_d);
  }

  // all other cases: loop over all elements and manually copy data
  //
  arg_a.setDimensions(this_a.nrows_d, this_a.ncols_d, false);
  arg_a.clear(Integral::RETAIN);

  for (int32 row = 0; row < this_a.nrows_d; row++) {
    for (int32 col = row; col < this_a.ncols_d; col++) {
      arg_a.setValue(row, col, this_a.getValue(row, col));
    }
  }
  
  // exit gracefully
  //
  return true;
}

// explicit instantiations
//
template bool8
MMatrixMethods::getUpper<ISIP_TEMPLATE_TARGET>
(const MMatrix<ISIP_TEMPLATE_TARGET>&, MMatrix<ISIP_TEMPLATE_TARGET>&);

// method: getMinor
//
// arguments:
//  const MMatrix<TScalar, TIntegral>& this: (output) class operand
//  MMatrix<TScalar, TIntegral>& arg: (output) contains result
//  int32 row_index: (input) row for which minor is to be calculated
//  int32 col_index: (input) column for which minor is to be calculated
//
// return: a bool8 value indicating status
//
// this method computes the minor matrix for a particular element of
// the input matrix. the output will be stored in the current matrix
//
template<class TScalar, class TIntegral>
bool8 MMatrixMethods::getMinor(const MMatrix<TScalar, TIntegral>& this_a, 
				 MMatrix<TScalar, TIntegral>& arg_a, 
				 int32 row_index_a, int32 col_index_a) {

  // calculate the dimensions for the output
  //
  int32 nrows_new = (int32)(this_a.nrows_d) - 1;
  int32 ncols_new = (int32)(this_a.ncols_d) - 1;

  // check the arguments and dimensions
  //
  if ((nrows_new <= 0) || (ncols_new <= 0) ||
      (row_index_a < 0) || (col_index_a < 0) ||
      (row_index_a >= this_a.nrows_d) || (col_index_a >= this_a.ncols_d)) {
    this_a.debug(L"this_a");    
    return Error::handle(name(), L"getMinor", Error::ARG,
			 __FILE__, __LINE__);
  }
  else if ((nrows_new == 0) && (ncols_new == 0)) {
    return arg_a.clear(Integral::RESET);
  }

  // create the space in the output matrix
  //
  arg_a.setDimensions(nrows_new, ncols_new, false, Integral::UNCHANGED);

  // type: non-SPARSE input; non-SPARSE output
  //
  if ((this_a.type_d != Integral::SPARSE) &&
      (arg_a.type_d != Integral::SPARSE)) {
  
    // loop over the rows of the current matrix and copy elements:
    //  be sure to skip the excluded row
    //
    for (int32 row = 0, orow = 0; row < this_a.nrows_d; row++) {
      
      // exclude the specified row
      //
      if (row != row_index_a) {

	// loop over columns in this row
	//
	for (int32 col = 0, ocol = 0; col < this_a.ncols_d; col++) {
	  
	  // exclude the specified column
	  //
	  if (col != col_index_a) {
	    arg_a.setValue(orow, ocol++, this_a.getValue(row, col));
	  }
	}

	// increment the output row counter
	//
	orow++;
      }
    }
  }  
  
  // type: non-SPARSE input; SPARSE output
  //  
  else if ((this_a.type_d != Integral::SPARSE) &&
	   (arg_a.type_d == Integral::SPARSE)) {
  
    // compute the number of non-zero elements and make (extra) space
    //
    int32 num_elements = this_a.numNotEqual(0);
    arg_a.m_d.setCapacity(num_elements);
    arg_a.row_index_d.setCapacity(num_elements);
    arg_a.col_index_d.setCapacity(num_elements);

    // loop over the rows of the current matrix and copy elements:
    //  be sure to skip the excluded row
    //
    for (int32 row = 0, index = 0; row < this_a.nrows_d; row++) {
      
      // exclude the specified row
      //
      if (row != row_index_a) {

	// loop over columns in this row
	//
	for (int32 col = 0; col < this_a.ncols_d; col++) {
	  
	  // exclude the specified column
	  //
	  if (col != col_index_a) {

	    // get the current value
	    //
	    TIntegral tmp = this_a.getValue(row, col);

	    // add this value if it is not zero
	    //
	    int32 new_row = row;
	    int32 new_col = col;
	    
	    if (tmp != 0) {

	      // compute the output row and column index: we must subtract one
	      // if this element occurs after the row and column to be deleted
	      //
	      if (new_row > row_index_a) {
		new_row--;
	      }
	      if (new_col > col_index_a) {
		new_col--;
	      }

	      // create space
	      //
	      arg_a.m_d.setLength(index + 1);
	      arg_a.row_index_d.setLength(index + 1);
	      arg_a.col_index_d.setLength(index + 1);
	    
	      // add this to the matrix
	      //
	      arg_a.m_d(index) = tmp;
	      arg_a.row_index_d(index) = new_row;
	      arg_a.col_index_d(index) = new_col;

	      // increment the counter
	      //
	      index++;
	    }
	  }
	}
      }
    }
  }

  // type: SPARSE input; SPARSE output
  //  
  else {
  
    // compute the number of non-zero elements and make space
    //
    int32 num_elements = this_a.m_d.length();
    arg_a.m_d.setCapacity(num_elements);
    arg_a.row_index_d.setCapacity(num_elements);
    arg_a.col_index_d.setCapacity(num_elements);

    // loop over the rows of the current matrix and copy elements:
    //  be sure to skip the excluded row
    //
    for (int32 index = 0, oindex = 0; index < num_elements; index++) {
      
      // exclude the specified row
      //
      int32 new_row = this_a.row_index_d(index);
      int32 new_col = this_a.col_index_d(index);

      if ((new_row != row_index_a) &&
	  (new_col != col_index_a)) {

	// get the current value
	//
	TIntegral tmp = this_a.m_d(index);

	// add this value if it is not zero
	//
	if (tmp != 0) {

	  // compute the output row and column index: we must subtract one
	  // if this element occurs after the row and column to be deleted
	  //
	  if (new_row > row_index_a) {
	    new_row--;
	  }
	  if (new_col > col_index_a) {
	    new_col--;
	  }

	  // create space
	  //
	  arg_a.m_d.setLength(oindex + 1);
	  arg_a.row_index_d.setLength(oindex + 1);
	  arg_a.col_index_d.setLength(oindex + 1);
	    
	  // add this to the matrix
	  //
	  arg_a.m_d(oindex) = tmp;
	  arg_a.row_index_d(oindex) = new_row;
	  arg_a.col_index_d(oindex) = new_col;

	  // increment the counter
	  //
	  oindex++;
	}
      }
    }
  }

  // exit gracefully
  //
  return true;
}

// explicit instantiations
//
template bool8
MMatrixMethods::getMinor<ISIP_TEMPLATE_TARGET>
(const MMatrix<ISIP_TEMPLATE_TARGET>&, MMatrix<ISIP_TEMPLATE_TARGET>&, int32, int32);

// method: setDiagonal
//
// arguments:
//  MMatrix<TScalar, TIntegral>& this: (output) class operand
//  const MVector<TScalar, TIntegral>& arg: (input) new values
//
// return: a bool8 value indicating status
//
// this method sets the diagonal elements of the current matrix to be
// the same as the elements of the input vector
//
template<class TScalar, class TIntegral>
bool8 MMatrixMethods::setDiagonal(MMatrix<TScalar, TIntegral>& this_a,
				    const MVector<TScalar, TIntegral>& arg_a) {

  // declare local variables
  //
  int32 nrows = arg_a.length();

  // check if the current matrix is square and the dimension of the
  // vector and matrix match
  //
  if ((!this_a.isSquare()) || (this_a.nrows_d != nrows)) {
    this_a.debug(L"this_a");    
    return Error::handle(name(), L"setDiagonal", Error::ARG, 
			 __FILE__, __LINE__);
  }

  // type: non-SPARSE
  //
  if ((this_a.type_d == Integral::FULL) ||
      (this_a.type_d == Integral::DIAGONAL) ||
      (this_a.type_d == Integral::SYMMETRIC) ||
      (this_a.type_d == Integral::LOWER_TRIANGULAR) ||
      (this_a.type_d == Integral::UPPER_TRIANGULAR)) {

    // only copy the diagonal elements from this matrix
    //
    for (int32 row = 0; row < nrows; row++) {
      this_a.setValue(row, row, arg_a(row));
    }
  }

  // type: SPARSE
  //
  else {

    // the only really clean way to do this is to manually copy all
    // the non-zero elements. for a truly sparse matrix, this won't be
    // prohibitively expensive.
    //
    for (int32 row = 0; row < nrows; row++) {

      // since looking up this value is expensive, we want to save it
      //
      TIntegral tmp = arg_a(row);
      
      // add the value if it is non-zero
      //
      if (tmp != 0) {
	this_a.setValue(row, row, tmp);
      }
    }
  }

  // exit gracefully
  //
  return true;
}

// explicit instantiations
//
template bool8
MMatrixMethods::setDiagonal<ISIP_TEMPLATE_TARGET>
(MMatrix<ISIP_TEMPLATE_TARGET>&, const MVector<ISIP_TEMPLATE_TARGET>&);

// method: setLower
//
// arguments:
//  MMatrix<TScalar, TIntegral>& this: (output) class operand
//  const MMatrix<TScalar, TIntegral>& arg: (input) new values
//
// return: a bool8 value indicating status
//
// this method sets the lower triangular elements of the matrix to be
// the same as the lower triangular elements of the source matrix
//
template<class TScalar, class TIntegral>
bool8 MMatrixMethods::setLower(MMatrix<TScalar, TIntegral>& this_a,
				 const MMatrix<TScalar, TIntegral>& arg_a) {

  // check arguments
  //
  if ((!arg_a.isSquare()) ||
      (!this_a.checkDimensions(arg_a)) ||
      ((this_a.type_d == Integral::DIAGONAL) && (!arg_a.isDiagonal())) ||
      ((this_a.type_d == Integral::UPPER_TRIANGULAR) &&
       (!arg_a.isDiagonal())) ||
      ((this_a.type_d == Integral::SYMMETRIC) && (!arg_a.isDiagonal()))) {
    arg_a.debug(L"arg_a");    
    this_a.debug(L"this_a");    
    return Error::handle(name(), L"setLower", Error::ARG, __FILE__, __LINE__);
  }

  // type: FULL, SYMMETRIC, or LOWER_TRIANGULAR
  //
  if ((this_a.type_d == Integral::FULL) ||
      (this_a.type_d == Integral::LOWER_TRIANGULAR)) {
    
    // copy the lower triangular elements
    //
    for (int32 row = 0; row < this_a.nrows_d; row++) {
      for (int32 col = 0; col <= row; col++) {
	this_a.m_d(this_a.index(row, col)) = arg_a.getValue(row, col);
      }
    }
  }

  // type: DIAGONAL or UPPER_TRIANGULAR
  //
  else if ((this_a.type_d == Integral::DIAGONAL) ||
	   (this_a.type_d == Integral::SYMMETRIC) ||
	   (this_a.type_d == Integral::UPPER_TRIANGULAR)) {

    // copy the diagonal elements
    //
    for (int32 row = 0; row < this_a.nrows_d; row++) {
      this_a.m_d(this_a.index(row, row)) = arg_a.getValue(row, row);
    }
  }

  // type: SPARSE
  //
  else {

    // the only really clean way to do this is to manually copy all
    // the non-zero elements. for a truly sparse matrix, this won't be
    // prohibitively expensive.
    //
    for (int32 row = 0; row < this_a.nrows_d; row++) {
      for (int32 col = 0; col <= row; col++) {

	// since looking up this value is expensive, we want to save it
	//
	TIntegral tmp = arg_a.getValue(row, col);

	// add the value if it is non-zero
	//
	if (tmp != 0) {
	  this_a.setValue(row, col, tmp);
	}
      }
    }
  }
  
  // exit gracefully
  //
  return true;
}

// explicit instantiations
//
template bool8
MMatrixMethods::setLower<ISIP_TEMPLATE_TARGET>
(MMatrix<ISIP_TEMPLATE_TARGET>&, const MMatrix<ISIP_TEMPLATE_TARGET>&);

// method: setUpper
//
// arguments:
//  MMatrix<TScalar, TIntegral>& this: (output) class operand
//  const MMatrix<TScalar, TIntegral>& arg: (input) new values
//
// return: a bool8 value indicating status
//
// this method sets the lower triangular elements of the matrix to be
// the same as the lower triangular elements of the source matrix
//
template<class TScalar, class TIntegral>
bool8 MMatrixMethods::setUpper(MMatrix<TScalar, TIntegral>& this_a,
				 const MMatrix<TScalar, TIntegral>& arg_a) {
  
  // check arguments
  //
  if ((!arg_a.isSquare()) ||
      (!this_a.checkDimensions(arg_a)) ||
      ((this_a.type_d == Integral::DIAGONAL) && (!arg_a.isDiagonal())) ||
      ((this_a.type_d == Integral::LOWER_TRIANGULAR) &&
       (!arg_a.isDiagonal())) ||
      ((this_a.type_d == Integral::SYMMETRIC) && (!arg_a.isDiagonal()))) {
    arg_a.debug(L"arg_a");    
    this_a.debug(L"this_a");    
    return Error::handle(name(), L"setUpper", Error::ARG, __FILE__, __LINE__);
  }

  // type: FULL, SYMMETRIC, or UPPER_TRIANGULAR
  //
  if ((this_a.type_d == Integral::FULL) ||
      (this_a.type_d == Integral::UPPER_TRIANGULAR)) {
    
    // copy the upper triangular elements
    //
    for (int32 row = 0; row < this_a.nrows_d; row++) {
      for (int32 col = row; col < this_a.nrows_d; col++) {
	this_a.m_d(this_a.index(row, col)) = arg_a.getValue(row, col);
      }
    }
  }

  // type: DIAGONAL, SYMMETRIC or LOWER_TRIANGULAR
  //
  else if ((this_a.type_d == Integral::DIAGONAL) ||
	   (this_a.type_d == Integral::SYMMETRIC) ||	   
	   (this_a.type_d == Integral::LOWER_TRIANGULAR)) {

    // copy the diagonal elements
    //
    for (int32 row = 0; row < this_a.nrows_d; row++) {
      this_a.m_d(this_a.index(row, row)) = arg_a.getValue(row, row);
    }
  }

  // type: SPARSE
  //
  else {

    // the only really clean way to do this is to manually copy all
    // the non-zero elements. for a truly sparse matrix, this won't be
    // prohibitively expensive.
    //
    for (int32 row = 0; row < this_a.nrows_d; row++) {
      for (int32 col = row; col < this_a.ncols_d; col++) {

	// since looking up this value is expensive, we want to save it
	//
	TIntegral tmp = arg_a.getValue(row, col);

	// add the value if it is non-zero
	//
	if (tmp != 0) {
	  this_a.setValue(row, col, tmp);
	}
      }
    }
  }
  
  // exit gracefully
  //
  return true;
}

// explicit instantiations
//
template bool8
MMatrixMethods::setUpper<ISIP_TEMPLATE_TARGET>
(MMatrix<ISIP_TEMPLATE_TARGET>&, const MMatrix<ISIP_TEMPLATE_TARGET>&);

// method: setBlock
//
// arguments:
//  MMatrix<TScalar, TIntegral>& this_a: (input) operand
//  int32 start_row: (input) starting row
//  int32 start_col: (input) starting column
//  int32 nrows: (input) number of rows
//  int32 ncols: (input) number of columns
//  TIntegral value: (input) operand
//
// return: a bool8 value indicating status
//
// this method assigns the input value to a block of a matrix
// in the range:
//
//    [start_row, start_col] to 
//       [start_row + nrows - 1, start_col + ncols - 1]
//
// the type of the matrix is not changed.
//
template<class TScalar, class TIntegral>
bool8 MMatrixMethods::setBlock(MMatrix<TScalar, TIntegral>& this_a,
				 int32 start_row_a, int32 start_col_a,
				 int32 nrows_a, int32 ncols_a,
				 TIntegral value_a) {

  // declare local variables
  //
  int32 start_row = start_row_a;
  int32 start_col = start_col_a; 
  int32 end_row = start_row_a + nrows_a;
  int32 end_col = start_col_a + ncols_a;
  
  // check the dimensions against the overall dimensions of the matrix
  //
  if ((start_row < (int32)0) || (end_row > (int32)this_a.nrows_d) ||
      (start_col < (int32)0) || (end_col > (int32)this_a.ncols_d)) {
    this_a.debug(L"this_a");    
    return Error::handle(name(), L"setBlock", Error::ARG, __FILE__, __LINE__);
  }
  else if ((nrows_a == 0) || (ncols_a == 0)) {
    return true;
  }
	  
  // type: FULL
  //  assign the value manually to each element
  //
  if (this_a.type_d == Integral::FULL) {
    for (int32 row = start_row; row < end_row; row++) {
      for (int32 col = start_col; col < end_col; col++) {
	this_a.m_d(this_a.index(row, col)) = value_a;
      }
    }
  }

  // type: DIAGONAL
  //
  else if (this_a.type_d == Integral::DIAGONAL) {

    // as we assign values, check for zero.
    //
    for (int32 row = start_row; row < end_row; row++) {
      for (int32 col = start_col; col < end_col; col++) {

	if ((row != col) && (value_a != 0)) {
	  this_a.debug(L"this_a");	  
	  return Error::handle(name(), L"setBlock",
			       Error::ARG, __FILE__, __LINE__);
	}
	else if ((row = col)) {
	  this_a.m_d(this_a.index(row, col)) = value_a;
	}
      }
    }
  }

  // type: SYMMETRIC
  //
  else if (this_a.type_d == Integral::SYMMETRIC) {

    // the block must also be one of three things:
    //  - completely in the lower half (in which case, we allow it)
    //  - completely in the upper half (in which case, we allow it)
    //  - centered on the diagonal and square
    //
    if (((start_col > start_row) && (start_col < (end_row - 1))) ||
	((start_col < start_row) && (start_col > (end_row - 1))) ||
	((start_row == start_col) && (nrows_a != ncols_a))) {
      this_a.debug(L"this_a");      
      return Error::handle(name(), L"setBlock", Error::ARG, __FILE__, __LINE__);
    }

    // we can proceed with assigning values. we could be more efficient
    // about this, but it is not trivial to get the indexing correct.
    //
    for (int32 row = start_row; row < end_row; row++) {
      for (int32 col = start_col; col < end_col; col++) {
	this_a.m_d(this_a.index(row, col)) = value_a;
      }      
    }
  }
    
  // type: LOWER_TRIANGULAR
  //
  else if (this_a.type_d == Integral::LOWER_TRIANGULAR) {

    // as we assign values, check for zero.
    //
    for (int32 row = start_row; row < end_row; row++) {
      for (int32 col = start_col; col < end_col; col++) {

	if ((col > row) && (value_a != 0)) {
	  this_a.debug(L"this_a");	  
	  return Error::handle(name(), L"setBlock",
			       Error::ARG, __FILE__, __LINE__);
	}
	else if (row >= col) {
	  this_a.m_d(this_a.index(row, col)) = value_a;
	}
      }
    }
  }
    
  // type: UPPER_TRIANGULAR
  //
  else if (this_a.type_d == Integral::UPPER_TRIANGULAR) {

    // as we assign values, check for zero.
    //
    for (int32 row = start_row; row < end_row; row++) {
      for (int32 col = start_col; col < end_col; col++) {

	if ((row > col) && (value_a != 0)) {
	  this_a.debug(L"this_a");	  
	  return Error::handle(name(), L"setBlock",
			       Error::ARG, __FILE__, __LINE__);
	}
	else if (col >= row) {
	  this_a.m_d(this_a.index(row, col)) = value_a;
	}
      }
    }
  }
    
  // type: SPARSE
  //  essentially the same as FULL, but we use the setValue method
  //
  else {
    for (int32 row = start_row; row < end_row; row++) {
      for (int32 col = start_col; col < end_col; col++) {
	this_a.setValue(row, col, value_a);
      }
    }
  }

  // exit gracefully
  //
  return true;
}

// explicit instantiations
//
template bool8
MMatrixMethods::setBlock<ISIP_TEMPLATE_TARGET>
(MMatrix<ISIP_TEMPLATE_TARGET>&, int32, int32, int32, int32, ISIP_TEMPLATE_T1);

// method: makeDiagonal
//
// arguments:
//  MMatrix<TScalar, TIntegral>& this: (output) class operand
//  const MVector<TScalar, TIntegral>& values: (input) new values
//  Integral::MTYPE type: (input) expected matrix type
//
// return: a bool8 value indicating status
//
// this method creates a diagonal matrix from an input vector
//
template<class TScalar, class TIntegral>
bool8
MMatrixMethods::makeDiagonal(MMatrix<TScalar, TIntegral>& this_a,
			     const MVector<TScalar, TIntegral>& values_a,
			     Integral::MTYPE type_a) {

  // get the required dimensions of the matrix
  //
  int32 dim = values_a.length();

  // set the dimensions of the matrix
  //
  this_a.setDimensions(dim, dim, false, type_a);

  // type: DIAGONAL
  //  simply assign the input vector to the storage vector
  //
  if (type_a == Integral::DIAGONAL) {
    this_a.m_d.assign(values_a);
  }

  // type: FULL, SYMMETRIC, or TRIANGULAR
  //
  else if ((this_a.type_d == Integral::FULL) ||
	   (this_a.type_d == Integral::SYMMETRIC) ||
	   (this_a.type_d == Integral::LOWER_TRIANGULAR) ||
	   (this_a.type_d == Integral::UPPER_TRIANGULAR)) {

    // clear the contents of the current matrix
    //
    this_a.clear(Integral::RETAIN);

    // assign values to the diagonal elements of the matrix
    //
    for (int32 row = 0; row < dim; row++) {
      this_a.m_d(this_a.index(row, row)) = values_a(row);
    }
  }

  // type: SPARSE
  //
  else if (this_a.type_d == Integral::SPARSE) {

    // find the number of non-zero diagonal elements
    //
    int32 dim_nonzero = values_a.numNotEqual(0);
    
    // create space in the sparse vectors
    //
    this_a.m_d.setLength(dim_nonzero);
    this_a.row_index_d.setLength(dim_nonzero);
    this_a.col_index_d.setLength(dim_nonzero);

    // loop over the diagonal elements
    //
    for (int32 row = 0, index = 0; row < dim; row++) {

      // only assign the non-zero values
      //
      TIntegral tmp = values_a(row);

      if (tmp != 0) {
	this_a.m_d(index) = tmp;
	this_a.row_index_d(index) = row;
	this_a.col_index_d(index++) = row;
      }
    }
  }
  
  // exit gracefully
  //
  return true;
}

// explicit instantiations
//
template bool8
MMatrixMethods::makeDiagonal<ISIP_TEMPLATE_TARGET>
(MMatrix<ISIP_TEMPLATE_TARGET>&, const MVector<ISIP_TEMPLATE_TARGET>&,
 Integral::MTYPE);

// method: makeLower
//
// arguments:
//  MMatrix<TScalar, TIntegral>& this: (output) class operand
//  const MMatrix<TScalar, TIntegral>& arg: (input) new values
//  Integral::MTYPE type: (input) expected matrix type
//
// return: a bool8 value indicating status
//
template<class TScalar, class TIntegral>
bool8 MMatrixMethods::makeLower(MMatrix<TScalar, TIntegral>& this_a,
				  const MMatrix<TScalar, TIntegral>& arg_a,
				  Integral::MTYPE type_a) {

  // change the type
  //
  this_a.clear(Integral::RESET);
  this_a.changeType(type_a);

  // make the new matrix
  //
  return arg_a.getLower(this_a);
}

// explicit instantiations
//
template bool8
MMatrixMethods::makeLower<ISIP_TEMPLATE_TARGET>
(MMatrix<ISIP_TEMPLATE_TARGET>&, const MMatrix<ISIP_TEMPLATE_TARGET>&,
 Integral::MTYPE);

// method: makeUpper
//
// arguments:
//  MMatrix<TScalar, TIntegral>& this: (output) class operand
//  const MMatrix<TScalar, TIntegral>& arg: (input) new values
//  Integral::MTYPE type: (input) expected matrix type
//
// return: a bool8 value indicating status
//
template<class TScalar, class TIntegral>
bool8 MMatrixMethods::makeUpper(MMatrix<TScalar, TIntegral>& this_a,
				  const MMatrix<TScalar, TIntegral>& arg_a,
				  Integral::MTYPE type_a) {
  // change the type
  //
  this_a.clear(Integral::RESET);
  this_a.changeType(type_a);

  // make the new matrix
  //
  return arg_a.getUpper(this_a);
}

// explicit instantiations
//
template bool8
MMatrixMethods::makeUpper<ISIP_TEMPLATE_TARGET>
(MMatrix<ISIP_TEMPLATE_TARGET>&, const MMatrix<ISIP_TEMPLATE_TARGET>&,
 Integral::MTYPE);
