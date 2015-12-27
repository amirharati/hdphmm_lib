// file: $isip/class/math/matrix/MMatrix/mmat_10.cc
// version: $Id: mmat_10.cc 7816 2002-02-27 20:54:30Z alphonso $
//

// isip include files
//
#include "MMatrixMethods.h"
#include "MMatrix.h"
//#include <VectorLong.h>

// method: getValue
//
// arguments:
//  const MMatrix<TScalar, TIntegral>& this: (output) class operand
//  TScalar& value: (output) value at the given position
//  int32 row_index: (input) row_index
//  int32 col_index: (input) col_index
//
// return: a TIntegral value at the given position of the matrix
//
// this method gets the value at the specified position in the matrix
//
template<class TScalar, class TIntegral>
bool8 MMatrixMethods::getValue(const MMatrix<TScalar, TIntegral>& this_a, 
				 TScalar& value_a, int32 row_index_a,
				 int32 col_index_a) {

  // type: DIAGONAL
  //  the general idea is that we output the value of diagonal element for
  //  diagonal position, otherwise, we output zero.
  //
  if (this_a.type_d == Integral::DIAGONAL) {

    // return zero for non-diagonal elements
    //
    if (row_index_a != col_index_a) {
      value_a = TScalar((TIntegral)0);
    }

    // return diagonal element
    //
    else {
      value_a = TScalar(this_a.m_d(row_index_a));
    }
  }

  // type: FULL
  //  the general idea is that we simply output the value of corresponding
  //  position.
  //
  else if (this_a.type_d == Integral::FULL) {

    // return the value at specified row and column index
    //
    value_a = TScalar(this_a.m_d(this_a.index(row_index_a, col_index_a)));
  }

  // type: SYMMETRIC
  //  the general idea is that we simply output the value of lower triangular
  //  element, but for upper triangular element, we output the corresponding
  //  element in lower triangular part, that is a(i, j) = a(j, i).
  //
  else if (this_a.type_d == Integral::SYMMETRIC) {

    // return the element in lower triangle
    //
    if (row_index_a >= col_index_a) {
      value_a = TScalar(this_a.m_d(this_a.index(row_index_a,
						    col_index_a)));
    }

    // for upper triangular elements also output corresponding element
    // in lower triangle
    //
    else {
      value_a = TScalar(this_a.m_d(this_a.index(col_index_a,
						    row_index_a)));
    }
  }

  // type: LOWER_TRIANGULAR
  //  the general idea is that we output the value of lower triangular element,
  //  otherwise, output zero for upper triangular element.
  //
  else if (this_a.type_d == Integral::LOWER_TRIANGULAR) {

    // return the element in lower triangle
    //    
    if (row_index_a >= col_index_a) {
      value_a = TScalar(this_a.m_d(this_a.index(row_index_a,
						    col_index_a)));
    }

    // return zero for upper triangular values
    //
    else {
      value_a = TScalar((TIntegral)0);
    }
  }

  // type: UPPER_TRIANGULAR
  //  the general idea is that we output the value of upper triangular element
  //  and output zero for lower triangular element
  //
  else if (this_a.type_d == Integral::UPPER_TRIANGULAR) {

    // return the element in upper triangle
    //        
    if (row_index_a <= col_index_a) {
      value_a = TScalar(this_a.m_d(this_a.index(row_index_a,
						    col_index_a)));
    }

    // return zero for lower triangular values
    //    
    else {
      value_a = TScalar((TIntegral)0);
    }
  }

  // type: SPARSE
  //  the general idea is that we loop through all the elements on the storage
  //  vector.
  //
  else if (this_a.type_d == Integral::SPARSE) {

    // if the storage vector does not have the element corresponding
    // to that row and column index then it must be zero.
    //
    value_a = TScalar((TIntegral)0);
    
    // return the element on the storage vector if it is a non-zero element
    //
    for (int32 index = 0; index < this_a.m_d.length(); index++) {
      if ((row_index_a == this_a.row_index_d(index)) &&
	  (col_index_a == this_a.col_index_d(index))) {
	value_a = (TScalar)this_a.m_d(index);
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
MMatrixMethods::getValue<ISIP_TEMPLATE_TARGET>
(const MMatrix<ISIP_TEMPLATE_TARGET>&, ISIP_TEMPLATE_T0&, int32, int32);

// method: getValue
//
// arguments:
//  const MMatrix<TScalar, TIntegral>& this: (output) class operand
//  int32 row_index: (input) row_index
//  int32 col_index: (input) col_index
//
// return: a TIntegral value at the given position of the matrix
//
// this method gets the value at the specified position
//
template<class TScalar, class TIntegral>
TIntegral MMatrixMethods::getValue(const MMatrix<TScalar, TIntegral>& this_a, 
				   int32 row_index_a, int32 col_index_a) {

  // type: DIAGONAL
  //  the general idea is that we return the value of diagonal element for
  //  diagonal position, otherwise, we return zero.
  //
  if (this_a.type_d == Integral::DIAGONAL) {

    // return zero for non-diagonal elements
    //    
    if (row_index_a != col_index_a) {
      return (TIntegral)0;
    }

    // return diagonal element
    //    
    else {
      return (TIntegral)this_a.m_d(row_index_a);
    }
  }

  // type: FULL
  //  the general idea is that we simply return the value of corresponding
  //  position.  
  //
  else if (this_a.type_d == Integral::FULL) {

    // return the value at specified row and column index
    //    
    return (TIntegral)(this_a.m_d(this_a.index(row_index_a, col_index_a)));
  }

  // type: SYMMETRIC
  //  the general idea is that we simply return the value of lower triangular
  //  element, but for upper triangular element, we return the corresponding
  //  element in lower triangular part, that is a(i, j) = a(j, i).  
  //
  else if (this_a.type_d == Integral::SYMMETRIC) {

    // return the element in lower triangle
    //    
    if (row_index_a >= col_index_a) {
      return (TIntegral)(this_a.m_d(this_a.index(row_index_a,
						     col_index_a)));
    }

    // for upper triangular elements also return corresponding element
    // in lower triangle
    //    
    else {
      return (TIntegral)(this_a.m_d(this_a.index(col_index_a,
						     row_index_a)));
    }
  }

  // type: LOWER_TRIANGULAR
  //  the general idea is that we return the value of lower triangular element,
  //  otherwise, output zero for upper triangular element.
  //  
  else if (this_a.type_d == Integral::LOWER_TRIANGULAR) {

    // return the element in lower triangle
    //    
    if (row_index_a >= col_index_a) {
      return (TIntegral)(this_a.m_d(this_a.index(row_index_a,
						     col_index_a)));
    }

    // return zero for upper triangular values
    //    
    else {
      return (TIntegral)0;
    }
  }

  // type: UPPER_TRIANGULAR
  //  the general idea is that we return the value of upper triangular element
  //  and return zero for lower triangular element  
  //    
  else if (this_a.type_d == Integral::UPPER_TRIANGULAR) {

    // return the element in upper triangle
    //     
    if (row_index_a <= col_index_a) {
      return (TIntegral)(this_a.m_d(this_a.index(row_index_a,
						     col_index_a)));
    }

    // return zero for lower triangular values
    //     
    else {
      return (TIntegral)0;
    }
  }

  // type: SPARSE
  //  the general idea is that we loop through all the elements on the storage
  //  vector.
  //
  else if (this_a.type_d == Integral::SPARSE) {

    // return the element on the storage vector if it is a non-zero element
    //
    for (int32 index = 0; index < this_a.m_d.length(); index++) {
      if ((row_index_a == (int32)this_a.row_index_d(index)) &&
          (col_index_a == (int32)this_a.col_index_d(index))) {
        return (TIntegral)this_a.m_d(index);
      }
    }

    // if the storage vector does not have the element corresponding
    // to that row and column index then it must be zero.
    //
    return (TIntegral)0;
  }

  else {
    this_a.debug(L"this_a");    
    return Error::handle(name(), L"getValue", 
			 MMatrix<TScalar, TIntegral>::ERR_UNKTYP,
			 __FILE__, __LINE__);
  }
}

// explicit instantiations
//
template ISIP_TEMPLATE_T1
MMatrixMethods::getValue<ISIP_TEMPLATE_TARGET>
(const MMatrix<ISIP_TEMPLATE_TARGET>&, int32, int32);

// method: getRow
//
// arguments:
//  const MMatrix<TScalar, TIntegral>& this: (output) class operand
//  MVector<TScalar, TIntegral>& vector: (output) a row vector at the given row
//  int32 row_index: (input) row_index
//
// return: a bool8 value indicating status
//
// this method gets the row vector at the specified row
//
template<class TScalar, class TIntegral>
bool8 MMatrixMethods::getRow(const MMatrix<TScalar, TIntegral>& this_a, 
			       MVector<TScalar, TIntegral>& vector_a,
			       int32 row_index_a) {

  // check the argument
  //
  if ((row_index_a < 0) || (row_index_a > this_a.nrows_d)) {
    this_a.debug(L"this_a");
    vector_a.debug(L"vector_a");    
    return Error::handle(name(), L"getRow", Error::ARG, __FILE__, __LINE__);
  }

  // get the number of columns
  //
  int32 ncols = this_a.getNumColumns();
  
  // create space for the output vector
  //
  vector_a.setLength(ncols, false);

  // type: FULL
  //  the general idea is that we assign the row vector to the output vector
  //  which can be easily done by calling move method for the storage vector.
  //
  if (this_a.type_d == Integral::FULL) {
    vector_a.move(this_a.m_d, ncols, row_index_a * ncols, 0);
  }

  // type: DIAGONAL
  //  the general idea is that we copy the diagonal element for the row at
  //  appropriate index in the vector and put zeros at other places.
  //
  else if (this_a.type_d == Integral::DIAGONAL) {

    // zero the non-diagonal components
    //
    vector_a.clear(Integral::RETAIN);

    // copy the diagonal element at the appropriate row
    //
    vector_a(row_index_a) = this_a.m_d(row_index_a);
  }

  // type: SYMMETRIC
  //  the general idea is that we copy the elements in the lower triangular
  //  part of the row in sequence, and fetch the upper triangular part
  //  using the index function.
  //  
  else if (this_a.type_d == Integral::SYMMETRIC) {

    // copy the lower triangular part
    //
    int32 index = this_a.index(row_index_a, 0);

    for (int32 col = 0; col < row_index_a; col++) {
      vector_a(col) = this_a.m_d(index++);
    }

    // copy the diagonal part
    //
    vector_a(row_index_a) = this_a.m_d(index);

    // copy the upper triangular part
    //
    for (int32 col = row_index_a + 1; col < ncols; col++) {
      vector_a(col) = this_a.getValue(row_index_a, col);
    }
  }

  // type: LOWER_TRIANGULAR
  //  the general idea is that we copy the elements in lower triangular part
  //  of the row at appropriate indices in the vector and put zeros at
  //  upper triangular part of the row.
  //    
  else if (this_a.type_d == Integral::LOWER_TRIANGULAR) {

    // loop over all columns
    //
    int32 index = this_a.index(row_index_a, 0);

    for (int32 col = 0; col < row_index_a; col++) {
      vector_a(col) = this_a.m_d(index++);
      vector_a(ncols - 1 - col) = (TIntegral)0;
    }
    vector_a(row_index_a) = this_a.m_d(index);
  }

  // type: UPPER_TRIANGULAR
  //  the general idea is that we copy the elements in upper triangular part
  //  of the row at appropriate indices in the vector and put zeros at
  //  lower triangular part of the row. since upper triangular is stored
  //  in a column-oriented format, we must do this through the indexing
  //  function.
  //      
  else if (this_a.type_d == Integral::UPPER_TRIANGULAR) {

    // compute the start column of upper triangular part of the row
    //
    int32 start_column = this_a.startColumn(row_index_a, this_a.type_d);

    // for the lower triangular part, place zeroes
    //
    for (int32 col = 0; col < start_column; col++) {
      vector_a(col) = (TIntegral)0;
    }

    // for the upper triangular part, copy the corresponding elements
    //
    for (int32 col = start_column; col < ncols; col++) {
      vector_a(col) =  this_a.m_d(this_a.index(row_index_a, col));
    }
  }

  // type: SPARSE
  //  we only copy the non-zero elements in that row to the output vector,
  //  but if there is no non-zero element, we will output an all-zero vector.
  //  also, note that since elements in a sparse matrix are stored in
  //  sequential order, we can avoid looping over all elements.
  //
  else if (this_a.type_d == Integral::SPARSE) {

    // set all elements to zeros
    // 
    vector_a.clear(Integral::RETAIN);
    
    // find the start of the row
    //
    int32 num_elements = this_a.m_d.length();
    int32 index = 0;

    while ((index < num_elements) &&
	   (this_a.row_index_d(index) != row_index_a)) {
      index++;
    }

    // copy element by element
    //
    while ((index < num_elements) &&
	   (this_a.row_index_d(index) == row_index_a)) {
      vector_a(this_a.col_index_d(index)) = this_a.m_d(index);
      index++;
    }
  }
      
  // exit gracefully
  //
  return true;
}

// explicit instantiations
//
template bool8
MMatrixMethods::getRow<ISIP_TEMPLATE_TARGET>
(const MMatrix<ISIP_TEMPLATE_TARGET>&, MVector<ISIP_TEMPLATE_TARGET>&, int32);

// method: getColumn
//
// arguments:
//  const MMatrix<TScalar, TIntegral>& this: (output) class operand
//  MVector<TScalar, TIntegral>& vector: (output) a vector at the given column
//  int32 col_index: (input) column index
//
// return: a bool8 value indicating status
//
template<class TScalar, class TIntegral>
bool8 MMatrixMethods::getColumn(const MMatrix<TScalar, TIntegral>& this_a, 
				  MVector<TScalar, TIntegral>& vector_a,
				  int32 col_index_a) {

  // check the argument
  //
  if ((col_index_a < 0) || (col_index_a > this_a.ncols_d)) {
    this_a.debug(L"this_a");
    vector_a.debug(L"vector_a");    
    return Error::handle(name(), L"getColumn", Error::ARG, __FILE__, __LINE__);
  }

  // create space for the output vector
  //
  vector_a.setLength(this_a.nrows_d, false);

  // since most of our matrices are stored in a row-major format, the
  // easiest way to do this is to simply loop over the elements and
  // copy them one by one
  //
  for (int32 row = 0; row < this_a.nrows_d; row++) {
    vector_a(row) = this_a.getValue(row, col_index_a);
  }
  
  // exit gracefully
  //
  return true;
}

// explicit instantiations
//
template bool8
MMatrixMethods::getColumn<ISIP_TEMPLATE_TARGET>
(const MMatrix<ISIP_TEMPLATE_TARGET>&, MVector<ISIP_TEMPLATE_TARGET>&, int32);

// method: setValue
//
// arguments:
//  MMatrix<TScalar, TIntegral>& this: (output) class operand
//  int32 row_index: (input) row_index
//  int32 col_index: (input) col_index
//  TIntegral value: (input) input value
//
// return: a bool8 value indicating status
//
// this method sets the specified position of the matrix to the input value
//
template<class TScalar, class TIntegral>
bool8 MMatrixMethods::setValue(MMatrix<TScalar, TIntegral>& this_a, 
				 int32 row_index_a, int32 col_index_a, 
				 TIntegral value_a) {

  // check the arguments
  //
  if ((row_index_a >= this_a.getNumRows()) ||
      (col_index_a >= this_a.getNumColumns())) {
    this_a.debug(L"this_a");    
    return Error::handle(name(), L"setValue()", Error::ARG, 
                         __FILE__, __LINE__);
  }

  // type: DIAGONAL
  //  this general idea here is that it is only allowed to set non-zero value
  //  for diagonal element, and zero for any element.
  //
  if (this_a.type_d == Integral::DIAGONAL) {

    // setting the non-zero value for off-diagonal element will change
    // the type of the matrix, so error
    //
    if (row_index_a != col_index_a ) {
      if (value_a != 0) {
	this_a.debug(L"this_a");	
        return Error::handle(name(), L"setValue()", 
			     MMatrix<TScalar, TIntegral>::ERR_OPTYPE, 
                             __FILE__, __LINE__);
      }
    }

    // set the value
    //
    else {
      this_a.m_d(row_index_a) = value_a;
    }
  }
  
  // type: FULL
  //
  else if (this_a.type_d == Integral::FULL) {
    (this_a.m_d(this_a.index(row_index_a, col_index_a))) = value_a;
  }

  // type: SYMMETRIC
  //  as we only keep elements of symmetric matrix in lower triangular, for
  //  upper triangular elements, we have a(i, j) = a(j, i) if i < j. so the
  //  general idea here is that we first check whether this position is lower
  //  or upper triangular, and then set the corresponding value in lower
  //  triangle.
  //
  else if (this_a.type_d == Integral::SYMMETRIC) {

    // if the position is in lower triangular part of the matrix, set the value
    //
    if (row_index_a > col_index_a) {
      (this_a.m_d(this_a.index(row_index_a, col_index_a))) = value_a;      
    }

    // else set the corresponding value in lower triangle
    //
    else {
      (this_a.m_d(this_a.index(col_index_a, row_index_a))) = value_a;
    }
  }

  // type: LOWER_TRIANGULAR
  //  this general idea here is that it is only allowed to set non-zero value
  //  for lower_triangular element, and zero for any element.
  //
  else if (this_a.type_d == Integral::LOWER_TRIANGULAR) {

    // set the value if the position is in lower triangular portion of matrix
    //
    if (row_index_a >= col_index_a) {
      (this_a.m_d(this_a.index(row_index_a, col_index_a))) = value_a;      
    }

    // error if a non-zero value is to be set in upper triangular
    // portion of the matrix, as it will change the type of the matrix
    //
    else if (value_a != 0) {
      this_a.debug(L"this_a");      
      return Error::handle(name(), L"setValue()", 
			   MMatrix<TScalar, TIntegral>::ERR_OPTYPE, 
			   __FILE__, __LINE__);
    }
  }

  // type: UPPER_TRIANGULAR
  //  this general idea here is that it is only allowed to set non-zero value
  //  for upper_triangular element, and zero for any element.
  //  
  else if (this_a.type_d == Integral::UPPER_TRIANGULAR) {

    // set the value if the position is in upper triangular portion of matrix
    //    
    if (row_index_a <= col_index_a) {
      (this_a.m_d(this_a.index(row_index_a, col_index_a))) = value_a;      
      return true;
    }

    // error if a non-zero value is to be set in lower triangular
    // portion of the matrix, as it will change the type of the matrix
    //    
    else if (value_a != 0) {
      this_a.debug(L"this_a");      
      return Error::handle(name(), L"setValue", 
			   MMatrix<TScalar, TIntegral>::ERR_OPTYPE, 
			   __FILE__, __LINE__);
    }
  }
  
  // type: SPARSE
  //  first we need to check whether this element exists or not. the general
  //  idea is we replace an existing value or insert a new value.
  //
  else if (this_a.type_d == Integral::SPARSE) {

    // find the position in the matrix where we can insert the value:
    //  the matrix elements are ordered by row (all elements for the
    //  first row followed by all elements for the second row ...). the
    //  value returned by this code, index, is the place at which the
    //  value should replace an existing value or insert a new value.
    // 
    //
    int32 index = 0;
    int32 num_elements = this_a.m_d.length();

    while ((index < this_a.col_index_d.length()) &&
           ((row_index_a > this_a.row_index_d(index)) ||
	    ((row_index_a == this_a.row_index_d(index)) &&
	     (col_index_a > this_a.col_index_d(index))))) {
      index++;
    }
    
    // if the element doesn't exist, or the matrix is empty, add it
    //
    if ((index >= num_elements) ||
	(row_index_a != this_a.row_index_d(index)) ||
	(col_index_a != this_a.col_index_d(index))) {
      
      // no need to add zero into sparse matrix
      //
      if (value_a == 0) {

	// exit gracefully
	//
	return true;
      }

      // increase the length by one
      //
      int32 new_len = num_elements + 1;
      this_a.m_d.setLength(new_len);
      this_a.row_index_d.setLength(new_len);
      this_a.col_index_d.setLength(new_len);

      // shift the data up by one
      //
      for (int32 i = num_elements; i > index; i--) {
	this_a.m_d(i) = this_a.m_d(i - 1);
	this_a.row_index_d(i) = this_a.row_index_d(i - 1);
	this_a.col_index_d(i) = this_a.col_index_d(i - 1);
      }
    
      // assign the new value
      //
      this_a.m_d(index) = value_a;
      this_a.row_index_d(index) = row_index_a;
      this_a.col_index_d(index) = col_index_a;
    }

    // if this element already exists, modify it
    //
    else {
      
      // if the input value is set to zero, remove this value
      //
      if (value_a == 0) {

	// shift the data down by one
	//
        for (int32 i = index; i < num_elements - 1; i++) {
          this_a.m_d(i) = this_a.m_d(i + 1);
          this_a.row_index_d(i) = this_a.row_index_d(i + 1);
          this_a.col_index_d(i) = this_a.col_index_d(i + 1);
        }

	// decrease the length by one
	//
        int32 new_len = num_elements - 1;
        this_a.m_d.setLength(new_len);
        this_a.row_index_d.setLength(new_len);
        this_a.col_index_d.setLength(new_len);
      }
      
      // the value is not zero, and the element can be replaced
      //
      else {
        this_a.m_d(index) = value_a;
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
MMatrixMethods::setValue<ISIP_TEMPLATE_TARGET>
(MMatrix<ISIP_TEMPLATE_TARGET>&, int32, int32, ISIP_TEMPLATE_T1);

// method: setRow
//
// arguments:
//  MMatrix<TScalar, TIntegral>& this: (output) class operand
//  int32 row_index: (input) row index for the row which need to be set
//  const MVector<TScalar, TIntegral>& vector: (input) a row vector
//
// return: a bool8 value indicating status
//
// this method sets the values of the row specified by the row index
//
template<class TScalar, class TIntegral>
bool8 MMatrixMethods::setRow(MMatrix<TScalar, TIntegral>& this_a, 
			       int32 row_index_a,
			       const MVector<TScalar, TIntegral>& vector_a) { 

  // check the argument
  //
  if ((row_index_a < 0) || (row_index_a >= this_a.nrows_d) ||
      (this_a.ncols_d != vector_a.length())) {
    this_a.debug(L"this_a");
    vector_a.debug(L"vector_a");    
    return Error::handle(name(), L"setRow", Error::ARG, __FILE__, __LINE__);
  }
  
  // get the number of columns of the matrix
  //
  int32 ncols = this_a.getNumColumns();

  // type: FULL
  //  the general idea is that we loop through the elements of the specified
  //  row and assign the values.
  //
  if (this_a.type_d == Integral::FULL) {

    // get the starting index
    //
    int32 index = this_a.index(row_index_a, 0);

    // copy the elements
    //
    for (int32 col = 0; col < ncols; col++) {  
      this_a.m_d(index++) = vector_a(col);
    }
  }

  // type: DIAGONAL
  //  user shouldn't use setRow for diagonal matrix as it will probably
  //  break its diagonal property.
  //
  else if (this_a.type_d == Integral::DIAGONAL) {
    this_a.debug(L"this_a");    
    return Error::handle(name(), L"setRow", Error::ARG, __FILE__, __LINE__);
  }

  // type: SYMMETRIC or LOWER_TRIANGULAR
  //  note that we only need to set the lower triangular part of the row  
  //
  else if ((this_a.type_d == Integral::SYMMETRIC) ||
	   (this_a.type_d == Integral::LOWER_TRIANGULAR)) {

    // get the starting index
    //
    int32 index = this_a.index(row_index_a, 0);

    // copy the elements
    //
    for (int32 col = 0; col <= row_index_a; col++) {  
      this_a.m_d(index++) = vector_a(col);
    }
  }

  // type: UPPER_TRIANGULAR
  //  note that we only need to set the upper triangular part of the row  
  //  since this format is stored in a column-oriented order, we use
  //  the indexing function.
  //
  else if (this_a.type_d == Integral::UPPER_TRIANGULAR) {

    // copy each element
    //    
    for (int32 col = row_index_a; col < ncols; col++) {
      this_a.m_d(this_a.index(row_index_a, col)) = vector_a(col);
    }
  }

  // type: SPARSE
  //  we try to do this efficiently by copying moving the elements in blocks
  //
  else {

    // get the length of non-zero elements in sparse matrix
    //
    int32 num_elements = this_a.m_d.length();

    // loop through each element to search the start index to insert
    // the input vector. 
    // 
    int32 start_index = Integral::NO_POS;

    for (int32 index = 0; index < num_elements; index++) {
      if (this_a.row_index_d(index) >= row_index_a) {
	start_index = index;
	break;
      }
    }

    if (start_index == Integral::NO_POS) {

      // will insert the input vector at the end of storing vectors of matrix
      //
      start_index = num_elements;
    }

    // copy the existing data
    //
    MVector<TScalar, TIntegral> tmp_m(this_a.m_d);

    VectorLong tmp_ri;
    tmp_ri.assign(this_a.row_index_d);

    VectorLong tmp_ci;
    tmp_ci.assign(this_a.col_index_d);    

    // get the maximum length of the number of non-zero elements in the
    // new sparse matrix
    //
    int32 max_num_elem = num_elements + vector_a.numNotEqual(0);

    // increase the capacity in preparation for the data copies
    //
    this_a.m_d.setLength(max_num_elem);
    this_a.row_index_d.setLength(max_num_elem);
    this_a.col_index_d.setLength(max_num_elem);

    // loop over all elements in the new vector to copy the non-zero elements
    // to current matrix
    //
    int32 index = start_index;

    for (int32 col = 0; col < ncols; col++) {

      // increase the length and copy
      //
      if ((TIntegral)(vector_a(col)) != 0) {
	this_a.m_d(index) = vector_a(col);
	this_a.row_index_d(index) = row_index_a;
	this_a.col_index_d(index++) = col;
      }
    }

    // from start_index, search the starting index of the next row
    // 
    int32 next_index = Integral::NO_POS;
    int32 next_row = row_index_a + 1;

    for (int32 i = start_index; i < num_elements; i++) {
      if (tmp_ri(i) >= next_row) {
	next_index = i;
	break;
      }
    }

    // is there any elements remaining to be copied?
    //
    int32 num_remain;

    if (next_index != Integral::NO_POS) {

      // compute the number of the rest elements
      //
      num_remain = num_elements - next_index;
    
      // copy those elements from [next_index to num_elements]
      //
      this_a.m_d.move(tmp_m, num_remain, next_index, index);
      this_a.row_index_d.move(tmp_ri, num_remain, next_index, index);
      this_a.col_index_d.move(tmp_ci, num_remain, next_index, index);
    }

    // no elements remaining to be copied
    //
    else {
      num_remain = 0;
    }

    // set the appropriate length: this is calculated using the current index
    // index and the number of remaining elements
    //
    num_elements = index + num_remain;
    this_a.m_d.setLength(num_elements);
    this_a.row_index_d.setLength(num_elements);
    this_a.col_index_d.setLength(num_elements);
  }

  // exit gracefully
  //
  return true;
}

// explicit instantiations
//
template bool8
MMatrixMethods::setRow<ISIP_TEMPLATE_TARGET>
(MMatrix<ISIP_TEMPLATE_TARGET>&, int32, const MVector<ISIP_TEMPLATE_TARGET>&); 

// method: setColumn
//
// arguments:
//  MMatrix<TScalar, TIntegral>& this: (output) class operand
//  int32 col_index: (input) column index for the column which needs to be set
//  const MVector<TScalar, TIntegral>& vector: (input) a row vector
//
// return: a bool8 value indicating status
//
template<class TScalar, class TIntegral>
bool8
MMatrixMethods::setColumn(MMatrix<TScalar, TIntegral>& this_a, 
			  int32 col_index_a,
			  const MVector<TScalar, TIntegral>& vector_a) { 

  // check the argument
  //
  if ((col_index_a < 0) || (col_index_a >= this_a.ncols_d) ||
      (this_a.nrows_d != vector_a.length())) {    
    this_a.debug(L"this_a");
    vector_a.debug(L"vector_a");    
    return Error::handle(name(), L"setColumn", Error::ARG, __FILE__, __LINE__);
  }

  // since most of our matrices are stored in a row-major format, the
  // easiest way to do this is to simply loop over the elements and
  // copy them one by one
  //
  for (int32 row = 0; row < this_a.nrows_d; row++) {
    this_a.setValue(row, col_index_a, vector_a(row));
  }

  // exit gracefully
  //
  return true;
}

// explicit instantiations
//
template bool8
MMatrixMethods::setColumn<ISIP_TEMPLATE_TARGET>
(MMatrix<ISIP_TEMPLATE_TARGET>&, int32, const MVector<ISIP_TEMPLATE_TARGET>&); 

// method: findRow
//
// arguments:
//  const MMatrix<TScalar, TIntegral>& this: (output) class operand
//  const MVector<TScalar, TIntegral>& v: (input) vector to be matched
//
// return: int32 value containing the row index for the input row vector
//
// this method returns only the position of the first exact match of
// the specified row in the matrix
//
template<class TScalar, class TIntegral>
int32 MMatrixMethods::findRow(const MMatrix<TScalar, TIntegral>& this_a, 
			     const MVector<TScalar, TIntegral>& v_a) {
  
  // declare local variables
  //
  int32 pos;

  // get the number of rows of the current matrix
  //
  int32 last_pos = this_a.getNumRows();

  // declare a temporary vector
  //
  MVector<TScalar, TIntegral> vector;

  // check all row vectors in the matrix for exact match
  // 
  for (pos = 0; pos < last_pos; pos++) {
    this_a.getRow(vector, pos);
    if (v_a.eq(vector)) {
      return pos;
    }
  }

  // if no match found, then return -1
  //
  pos = -1;

  // return the value
  //
  return pos;
}

// explicit instantiations
//
template int32
MMatrixMethods::findRow<ISIP_TEMPLATE_TARGET>
(const MMatrix<ISIP_TEMPLATE_TARGET>&, const MVector<ISIP_TEMPLATE_TARGET>&); 

// method: nextZero
//
// arguments:
//  const MMatrix<TScalar, TIntegral>& this: (input) class operand
//  int32& row_index: (output) row index for the next zero value
//  int32& col_index: (output) column index for the next zero value
//  int32  row_start: (input) start row
//  int32  col_start: (input) start column 
//
// return: a bool8 value indicating status
//
// this method returns position of next zero element in the matrix, it
// starts searching the matrix from the specified row and column index
//
template<class TScalar, class TIntegral>
bool8 MMatrixMethods::nextZero(const MMatrix<TScalar, TIntegral>& this_a,
				 int32& row_index_a, int32& col_index_a,
				 int32 row_start_a, int32 col_start_a) {
    
  // declare local variables
  //
  int32 row_start;
  int32 col_start;
  
  // get dimensions of the input matrix
  //
  int32 nrows = this_a.getNumRows();
  int32 ncols = this_a.getNumColumns();
  
  // check the arguments
  //
  if ((col_start_a >= ncols) || (row_start_a < -1)) {
    this_a.debug(L"this_a");    
    return Error::handle(name(), L"nextZero", Error::ARG,
			 __FILE__, __LINE__);
  }
  
  // calculate start row and column index:
  //  if starting row index is negative, set the start row and column
  //  index to zero
  //
  if (row_start_a == -1) {
    row_start = 0;
    col_start = 0;
  }
  else {

    // find the next column number
    //
    col_start = col_start_a + 1;
    row_start = row_start_a;

    // if reaching the end of row, begin from the next row
    //
    if (col_start >= ncols) {
      col_start = 0;
      row_start++;
    }
  }
  
  // if row_start is out of range, there is no other zero in the matrix
  //
  if (row_start >= nrows) {
    
    // exit ungracefully
    //
    return false;
  }
  
  // search the starting row for zero value
  //
  for (int32 j = col_start; j < ncols; j++) {
    
    // if the element is zero
    //
    if (this_a.getValue(row_start, j) == 0) {
      
      // record the position
      //
      row_index_a = row_start;
      col_index_a = j;
      
      // exit gracefully
      //
      return true;
    }
  }
  
  // check the following rows for zero element
  //
  for (int32 i = row_start + 1; i < nrows; i++) {
    for (int32 j = 0; j < ncols; j++) {
      
      // if the element is zero
      //
      if (this_a.getValue(i, j) == 0) {
	
	// record the position
	//
	row_index_a = i;
	col_index_a = j;
	
	// exit gracefully
	//
	return true;
      }
    }
  }
  
  // no other zero can be found on the matrix
  //
  return false;
}

// explicit instantiations
//
template bool8
MMatrixMethods::nextZero<ISIP_TEMPLATE_TARGET>
(const MMatrix<ISIP_TEMPLATE_TARGET>&, int32&, int32&, int32, int32);

// method: nextNonZero
//
// arguments:
//  const MMatrix<TScalar, TIntegral>& this: (input) class operand
//  TIntegral& value: (output) returned non zero value
//  int32& row_index: (output) row index for the next non-zero value
//  int32& col_index: (output) column index for the next non-zero value
//  int32 row_start: (input) start row
//  int32 col_start: (input) start column
//
// return: a bool8 value indicating status
//
// this method returns position of next non-zero element in the matrix, it
// starts searching the matrix from the specified row and column index
//
template<class TScalar, class TIntegral>
bool8 MMatrixMethods::nextNonZero(const MMatrix<TScalar, TIntegral>& this_a,
				    TIntegral& value_a,
				    int32& row_index_a, int32& col_index_a,
				    int32 row_start_a, int32 col_start_a) {
  
  // declare local variables
  //
  int32 row_start;
  int32 col_start;

  // get dimensions of input matrix
  //
  int32 nrows = this_a.getNumRows();
  int32 ncols = this_a.getNumColumns();

  // check the arguments
  //
  if (col_start_a >= ncols) {
    this_a.debug(L"this_a");    
    return Error::handle(name(), L"nextNonZero", Error::ARG,
			 __FILE__, __LINE__);
  }

  // calculate the start position
  //
  if (row_start_a < 0) {
    row_start = 0;
    col_start = 0;
  }
  else {

    // find the next column number
    //
    col_start = col_start_a + 1;
    row_start = row_start_a;

    // if reaching the end of row, begin from the next row
    //
    if (col_start >= ncols) {
      col_start = 0;
      row_start++;
    }
  }

  // if row_start is out of range, there is no other non-zero element
  // on the matrix
  //
  if (row_start >= nrows) {

    // exit gracefully
    //
    return false;
  }

  // type: DIAGONAL
  //  only search the diagonal elements, as off-diagonal elements are all zeros
  //
  if (this_a.type_d == Integral::DIAGONAL) {

    // adjust start row
    //
    if (row_start < col_start) {
      row_start++;
    }
    
    // search through the diagonal elements
    //
    for (int32 i = row_start; i < nrows; i++) {

      // search for non-zero element on the diagonal
      //
      if ((TIntegral)(this_a.m_d(i)) != 0) {

	// record the position and value
	//
	row_index_a = i;
	col_index_a = i;
	value_a = this_a.m_d(i);

	// exit gracefully
	//
	return true;
      }
    }
  }

  // type: FULL, SYMMETRIC
  //  loop through each element from the start position to find the first
  //  non-zero element
  //
  else if ((this_a.type_d == Integral::FULL) ||
	   (this_a.type_d == Integral::SYMMETRIC)) {
    
    // search through the elements
    //
    for (int32 i = row_start; i < nrows; i++) {
      for (int32 j = col_start; j < ncols; j++) {

	// search for non-zero element in the matrix
	//
	if (this_a.getValue(i, j) != 0) {

	  // record the position and value
	  //
	  row_index_a = i;
	  col_index_a = j;
	  value_a = this_a.getValue(i, j);

	  // exit gracefully
	  //
	  return true;
	}
      }

      // reset the col_start to zero
      //
      col_start = 0;
    }
  }

  // type: LOWER_TRIANGULAR, UPPER_TRIANGULAR
  //  search lower triangular or upper triangular part, which is implemented
  //  by calling of stopColumn and startColumn methods.
  //
  else if ((this_a.type_d == Integral::LOWER_TRIANGULAR) ||
	   (this_a.type_d == Integral::UPPER_TRIANGULAR)) {
    
    // search through the elements
    //
    for (int32 i = row_start; i < nrows; i++) {

      // get the stop column index in the current row:
      //  for lower triangular, it will be the current row's index;
      //  for upper triangular, it will be the maximum column index;
      //
      int32 stop_col = this_a.stopColumn(i, this_a.type_d); 

      // loop over the columns from start column to the stop column
      //
      for (int32 j = col_start; j <= stop_col; j++) {

	// search for non-zero element
	//
	if (this_a.getValue(i, j) != 0) {

	  // record the position and value
	  //
	  row_index_a = i;
	  col_index_a = j;
	  value_a = (this_a.m_d(this_a.index(i, j)));

	  // exit gracefully
	  //
	  return true;
	}
      }

      // reset the col_start to zero
      //
      col_start = 0;
    }
  }

  // type: SPARSE
  //  search through each element, and find the first element whose position
  //  is greater than the start position, as the value of this element is
  //  sure to be non-zero for sparse matrix.
  //
  else if (this_a.type_d == Integral::SPARSE) {

    // get the length of the storage vector, which gives the number of
    // non-zero elements in the matrix
    //
    int32 value_len = this_a.m_d.length();

    // loop over the vector and find the element
    //
    for (int32 i = 0; i < value_len; i++) {
      if ((row_start < this_a.row_index_d(i)) ||
	  ((row_start == this_a.row_index_d(i)) &&
	   (col_start <= this_a.col_index_d(i)))) {

	  // record the position and value
	  //
	  row_index_a = this_a.row_index_d(i);
	  col_index_a = this_a.col_index_d(i);
	  value_a = this_a.m_d(i);

	  // exit gracefully
	  //
	  return true;
      }
    }
  }

  // only zeros are left in the matrix
  //
  return false;
}

// explicit instantiations
//
template bool8
MMatrixMethods::nextNonZero<ISIP_TEMPLATE_TARGET>
(const MMatrix<ISIP_TEMPLATE_TARGET>&, ISIP_TEMPLATE_T1&, int32&, int32&,
 int32, int32);
