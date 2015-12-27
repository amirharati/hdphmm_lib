// file: $isip/class/math/matrix/MMatrix/mmat_12.cc
// version: $Id: mmat_12.cc 8944 2002-12-27 16:01:14Z parihar $
//

// isip include files
//
#include "MMatrixMethods.h"
#include "MMatrix.h"

// method: reorderColumns
//
// arguments:
//  MMatrix<TScalar, TIntegral>& this: (output) class operand
//  const MVector<Long, int32>& indices: (input) column assignments
//
// return: a bool8 value indicating status
//
// this method reorders the columns of the current matrix using the indices
// provided as an argument. for example:
//
//      [0 1 2]            [2]                     [2 0 1]
//  a = [3 4 5]  indices = [0]  reordered matrix = [5 3 4]
//      [6 7 8]		   [1]   	 	   [8 6 7]
//
// the result of this method is always a full matrix, except in the case
// of a SPARSE matrix. we could postprocess non-sparse matrices
// to see if we could shrink it, but that is probably not worth
// the trouble for most applications.
//
template<class TScalar, class TIntegral>
bool8 MMatrixMethods::reorderColumns(MMatrix<TScalar, TIntegral>& this_a, 
				       const MVector<Long, int32>& indices_a) {

  // transpose and call reorder rows
  //
  return (this_a.transpose() &&
	  this_a.reorderRows(indices_a) &&
	  this_a.transpose());
}

// explicit instantiations
//
template bool8
MMatrixMethods::reorderColumns<ISIP_TEMPLATE_TARGET>
(MMatrix<ISIP_TEMPLATE_TARGET>&, const MVector<Long, int32>&);

// method: reorderRows
//
// arguments:
//  MMatrix<TScalar, TIntegral>& this: (output) class operand
//  const MVector<Long, int32>& indices: (input) row assignments
//
// return: a bool8 value indicating status
//
// this method reorders the rows of the current matrix using the indices
// provided as an argument. for example:
//
//      [0 1 2]            [2]                     [6 7 8]
//  a = [3 4 5]  indices = [0]  reordered matrix = [0 1 2]
//      [6 7 8]		   [1]   	 	   [3 4 5]
//
// the result of this method is always a full matrix, except in the case
// of a SPARSE matrix. we could postprocess non-sparse matrices
// to see if we could shrink it, but that is probably not worth
// the trouble for most applications.
//
template<class TScalar, class TIntegral>
bool8 MMatrixMethods::reorderRows(MMatrix<TScalar, TIntegral>& this_a, 
				    const MVector<Long, int32>& indices_a) {

  // declare local variables
  //
  int32 nrows = indices_a.length();
  int32 ncols = this_a.getNumColumns();

  // check arguments:
  //  (1) the indices vector can't be larger than the number of rows (it
  //      can be smaller.
  //  (2) the elements of indices vector must be less than the number of rows
  //
  if ((nrows > (int32)this_a.nrows_d) ||
      (indices_a.min() < (int32)0) ||
      (indices_a.max() > (nrows - 1))) {    
    this_a.debug(L"this_a");
    indices_a.debug(L"indices_a");    
    return Error::handle(name(), L"reorderRows", Error::ARG,
			 __FILE__, __LINE__);
  }
    
  // type: non-SPARSE
  //  the general idea here is that we are going to build a vector
  //  containing the data as a FULL matrix, and then overwrite the
  //  data with this vector.
  //
  if ((this_a.type_d == Integral::FULL) ||
      (this_a.type_d == Integral::DIAGONAL) ||
      (this_a.type_d == Integral::SYMMETRIC) ||
      (this_a.type_d == Integral::LOWER_TRIANGULAR) ||
      (this_a.type_d == Integral::UPPER_TRIANGULAR)) {
  
    // create a temporary vector
    // 
    MVector<TScalar, TIntegral> tmp(nrows * ncols);
    
    // copy elements one by one to the temporary vector in the order
    // they will need to be in for a FULL matrix
    //
    for (int32 row = 0, index = 0; row < nrows; row++) {

      // grab the index of the permuted row
      //
      int32 new_row = indices_a(row);

      // copy each element in this new row
      //
      for (int32 col = 0; col < ncols; col++) {
	tmp(index++) = this_a.getValue(new_row, col);
      }
    }
    
    // now we can overwrite the original data
    //
    this_a.m_d.assign(tmp);

    // update the corresponding number of rows and columns
    //
    this_a.nrows_d.assign(nrows);
    this_a.ncols_d.assign(ncols);

    // set the type to full
    //
    this_a.type_d = Integral::FULL;
  }

  // type: SPARSE
  //  with a little bit work, we can preserve a sparse matrix. we just
  //  reorder the row indices according to the order specified in
  //  indices_a and then sort the elements row-wise.
  else {

    // compute the number of non-zero elements in the sparse matrix
    //
    int32 num_elements = this_a.row_index_d.length();

    // loop over number of elements of matrix
    //
    for (int32 i = 0; i < num_elements; i++) {
      
      // reorder the row indices according to the input vector of indices
      //
      this_a.row_index_d(i) = indices_a(this_a.row_index_d(i));
    }

    // sort the elements row-wise
    //
    return this_a.sortSparse();
  }

  // exit gracefully
  // 
  return true;
}

// explicit instantiations
//
template bool8
MMatrixMethods::reorderRows<ISIP_TEMPLATE_TARGET>
(MMatrix<ISIP_TEMPLATE_TARGET>&, const MVector<Long, int32>&);

