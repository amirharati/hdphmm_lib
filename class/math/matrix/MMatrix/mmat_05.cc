// file: $isip/class/math/matrix/MMatrix/mmat_05.cc
// version: $Id: mmat_05.cc 7924 2002-03-15 23:30:38Z zheng $
//

// isip include files
//
#include "MMatrixMethods.h"
#include "MMatrix.h"

template<class TScalar, class TIntegral>
////template<class TScalar, class TIntegral, class TAIntegral>
bool8 MMatrixMethods::assignComplexDiagnose(
			       MMatrix<TScalar, TIntegral>& this_a,
			       int32 nrows_a, int32 ncols_a,
			       const float64* mdata_a,
			       Integral::MTYPE type_a) {

  // create a vector from the input data
  //
  MVector<TScalar, TIntegral> vec;

  if (!vec.assign(this_a.vecLength(nrows_a, ncols_a, type_a), mdata_a)) {
  this_a.debug(L"this_a");    
    return Error::handle(name(), L"assign", Error::ARG, __FILE__, __LINE__);
  }

  MVector<TScalar, TIntegral> vec_imag;

  if (!vec_imag.assign(this_a.vecLength(nrows_a, ncols_a, type_a),
		       this_a.vecLength(nrows_a, ncols_a, type_a) + mdata_a)) {
    this_a.debug(L"this_a");    
    return Error::handle(name(), L"assign", Error::ARG, __FILE__, __LINE__);
  }
  
#ifdef ISIP_TEMPLATE_complex
  vec_imag.mult(TIntegral(0, 1));

  vec.add(vec_imag);
#endif
  
  // call the assign stream method to actually do the matrix assign
  //
  return this_a.assignStream(nrows_a, ncols_a, vec, (Integral::MTYPE)type_a);
}

// explicit instantiations
//
template bool8
MMatrixMethods::assignComplexDiagnose<ISIP_TEMPLATE_TARGET>
(MMatrix<ISIP_TEMPLATE_TARGET>&, int32, int32,
 const float64*, Integral::MTYPE);


// method: assignStream
//
// arguments:
//  MMatrix<TScalar, TIntegral>& this: (output) class operand
//  int32 nrows: (input) number of rows
//  int32 ncols: (input) number of columns
//  const MVector<TScalar, TIntegral>& vec: (input) vector containing the data
//  Integral::MTYPE type: (input) type of matrix
//
// return: a bool8 value indicating status
//
// this method assigns the matrix from a stream of data stored in a vector.
//
template<class TScalar, class TIntegral>
bool8 MMatrixMethods::assignStream(MMatrix<TScalar, TIntegral>& this_a, 
				     int32 nrows_a, int32 ncols_a, 
				     const MVector<TScalar, TIntegral>& vec_a, 
				     Integral::MTYPE type_a) {
  
  // set the dimensions of the current matrix to create space
  // 
  if (!this_a.setDimensions(nrows_a, ncols_a, false, type_a)) {
    return false;
  }

  // type: FULL, DIAGONAL, SYMMETRIC, or LOWER_TRIANGULAR
  //  just assign the vector directly
  //
  if ((this_a.type_d == Integral::DIAGONAL) ||
      (this_a.type_d == Integral::FULL) ||
      (this_a.type_d == Integral::SYMMETRIC) ||
      (this_a.type_d == Integral::LOWER_TRIANGULAR)) {
    this_a.m_d.assign(vec_a);
  }

  // type: UPPER_TRIANGULAR
  //  we input the elements of upper triangular matrix in row order, but we
  //  store them in column order.
  //
  else if (this_a.type_d == Integral::UPPER_TRIANGULAR) {
    for (int32 row = 0, index = 0; row < nrows_a; row++) {
      for (int32 col = row; col < ncols_a; col++) {
	this_a.m_d(this_a.index(row, col)) = vec_a(index++);
      }
    }
  }

  // type: SPARSE
  //  assign only non-zero elements to the vector
  //
  else if (this_a.type_d == Integral::SPARSE) {

    // get the number of non-zero elements in the input vector
    //
    int32 len = vec_a.length();
    int32 count = vec_a.numNotEqual(0);

    // create space to hold the values
    //
    this_a.m_d.setLength(count);
    this_a.row_index_d.setLength(count);
    this_a.col_index_d.setLength(count);

    // loop over length of sparse vectors and assign non-zero values
    // and corresponding row and column indices
    //
    for (int32 i = 0, index = 0; i < len; i++) {
      if ((TIntegral)vec_a(i) != 0) {
        this_a.m_d(index) = vec_a(i);
        this_a.row_index_d(index) = i / ncols_a;
        this_a.col_index_d(index) = i % ncols_a;
        index++;
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
MMatrixMethods::assignStream<ISIP_TEMPLATE_TARGET>
(MMatrix<ISIP_TEMPLATE_TARGET>&, int32, int32,
 const MVector<ISIP_TEMPLATE_TARGET>&, Integral::MTYPE);

// method: assign
//
// arguments:
//  MMatrix<TScalar, TIntegral>& this: (output) class operand
//  const MMatrix<TAScalar, TAIntegral>& arg: (input) matrix to copy
//
// return: a bool8 value indicating status
//
// this method assigns all the elements of the source matrix to the
// current matrix, including type of matrix.
//
template <class TScalar, class TIntegral, class TAScalar, class TAIntegral>
bool8 MMatrixMethods::assign(MMatrix<TScalar, TIntegral>& this_a,
			       const MMatrix<TAScalar, TAIntegral>& arg_a) {

  // if the matrices are the same object, we are done. note that the
  // comparison uses void* to get around the issue of comparing a
  // MatrixFloat to a MatrixDouble, assuming that if the *this pointer
  // is the same for the objects then the actual objects are the same.
  //
  if ((void*)&this_a == (void*)&arg_a) {
    return true;
  }

  // set the type of the current matrix to be same as that of the input matrix
  //
  this_a.type_d = arg_a.type_d;

  // assign each data element
  //
  return (this_a.m_d.assign(arg_a.m_d) &&
	  this_a.nrows_d.assign(arg_a.nrows_d) &&
	  this_a.ncols_d.assign(arg_a.ncols_d) &&
	  this_a.row_index_d.assign(arg_a.row_index_d) &&
	  this_a.col_index_d.assign(arg_a.col_index_d));
}

// explicit instantiations
//
template bool8
MMatrixMethods::assign<ISIP_TEMPLATE_TARGET, Byte, byte8>
(MMatrix<ISIP_TEMPLATE_TARGET>&, const MMatrix<Byte, byte8>&);

template bool8
MMatrixMethods::assign<ISIP_TEMPLATE_TARGET, Ushort, uint16>
(MMatrix<ISIP_TEMPLATE_TARGET>&, const MMatrix<Ushort, uint16>&);

template bool8
MMatrixMethods::assign<ISIP_TEMPLATE_TARGET, Ulong, uint32>
(MMatrix<ISIP_TEMPLATE_TARGET>&, const MMatrix<Ulong, uint32>&);

template bool8
MMatrixMethods::assign<ISIP_TEMPLATE_TARGET, Ullong, uint64>
(MMatrix<ISIP_TEMPLATE_TARGET>&, const MMatrix<Ullong, uint64>&);

template bool8
MMatrixMethods::assign<ISIP_TEMPLATE_TARGET, Short, int16>
(MMatrix<ISIP_TEMPLATE_TARGET>&, const MMatrix<Short, int16>&);

template bool8
MMatrixMethods::assign<ISIP_TEMPLATE_TARGET, Long, int32>
(MMatrix<ISIP_TEMPLATE_TARGET>&, const MMatrix<Long, int32>&);

template bool8
MMatrixMethods::assign<ISIP_TEMPLATE_TARGET, Llong, int64>
(MMatrix<ISIP_TEMPLATE_TARGET>&, const MMatrix<Llong, int64>&);

template bool8
MMatrixMethods::assign<ISIP_TEMPLATE_TARGET, Float, float32>
(MMatrix<ISIP_TEMPLATE_TARGET>&, const MMatrix<Float, float32>&);

template bool8
MMatrixMethods::assign<ISIP_TEMPLATE_TARGET, Double, float64>
(MMatrix<ISIP_TEMPLATE_TARGET>&, const MMatrix<Double, float64>&);

#ifdef ISIP_TEMPLATE_complex
template bool8
MMatrixMethods::assign<ISIP_TEMPLATE_TARGET, ComplexDouble, complexdouble>
(MMatrix<ISIP_TEMPLATE_TARGET>&, const MMatrix<ComplexDouble, complexdouble>&);

template bool8
MMatrixMethods::assign<ISIP_TEMPLATE_TARGET, ComplexFloat, complexfloat>
(MMatrix<ISIP_TEMPLATE_TARGET>&, const MMatrix<ComplexFloat, complexfloat>&);

template bool8
MMatrixMethods::assign<ISIP_TEMPLATE_TARGET, ComplexLong, complexlong>
(MMatrix<ISIP_TEMPLATE_TARGET>&, const MMatrix<ComplexLong, complexlong>&);
#endif

// method: assign
//
// arguments:
//  MMatrix<TScalar, TIntegral>& this: (output) class operand
//  int32 nrows: (input) number of rows
//  int32 ncols: (input) number of columns
//  const TAIntegral* mdata: (input) matrix data
//  Integral::MTYPE type: (input) matrix type
//
// return: a bool8 value indicating status
//
// this method assigns the matrix from a TAIntegral array
//
template<class TScalar, class TIntegral, class TAIntegral>
bool8 MMatrixMethods::assign(MMatrix<TScalar, TIntegral>& this_a,
			       int32 nrows_a, int32 ncols_a,
			       const TAIntegral* mdata_a,
			       Integral::MTYPE type_a) {

  // create a vector from the input data
  //
  MVector<TScalar, TIntegral> vec;

  if (!vec.assign(this_a.vecLength(nrows_a, ncols_a, type_a), mdata_a)) {
    this_a.debug(L"this_a");    
    return Error::handle(name(), L"assign", Error::ARG, __FILE__, __LINE__);
  }

  // call the assign stream method to actually do the matrix assign
  //
  return this_a.assignStream(nrows_a, ncols_a, vec, (Integral::MTYPE)type_a);
}

// explicit instantiations
//
template bool8
MMatrixMethods::assign<ISIP_TEMPLATE_TARGET>
(MMatrix<ISIP_TEMPLATE_TARGET>&, int32, int32, const byte8*, Integral::MTYPE);

template bool8
MMatrixMethods::assign<ISIP_TEMPLATE_TARGET>
(MMatrix<ISIP_TEMPLATE_TARGET>&, int32, int32, const uint16*, Integral::MTYPE);

template bool8
MMatrixMethods::assign<ISIP_TEMPLATE_TARGET>
(MMatrix<ISIP_TEMPLATE_TARGET>&, int32, int32, const uint32*, Integral::MTYPE);

template bool8
MMatrixMethods::assign<ISIP_TEMPLATE_TARGET>
(MMatrix<ISIP_TEMPLATE_TARGET>&, int32, int32, const uint64*, Integral::MTYPE);

template bool8
MMatrixMethods::assign<ISIP_TEMPLATE_TARGET>
(MMatrix<ISIP_TEMPLATE_TARGET>&, int32, int32, const int16*, Integral::MTYPE);

template bool8
MMatrixMethods::assign<ISIP_TEMPLATE_TARGET>
(MMatrix<ISIP_TEMPLATE_TARGET>&, int32, int32, const int32*, Integral::MTYPE);

template bool8
MMatrixMethods::assign<ISIP_TEMPLATE_TARGET>
(MMatrix<ISIP_TEMPLATE_TARGET>&, int32, int32, const int64*, Integral::MTYPE);

template bool8
MMatrixMethods::assign<ISIP_TEMPLATE_TARGET>
(MMatrix<ISIP_TEMPLATE_TARGET>&, int32, int32, const float32*, Integral::MTYPE);

template bool8
MMatrixMethods::assign<ISIP_TEMPLATE_TARGET>
(MMatrix<ISIP_TEMPLATE_TARGET>&, int32, int32, const float64*, Integral::MTYPE);

#ifdef ISIP_TEMPLATE_complex
template bool8
MMatrixMethods::assign<ISIP_TEMPLATE_TARGET>
(MMatrix<ISIP_TEMPLATE_TARGET>&, int32, int32, const complexlong*, Integral::MTYPE);
template bool8
MMatrixMethods::assign<ISIP_TEMPLATE_TARGET>
(MMatrix<ISIP_TEMPLATE_TARGET>&, int32, int32, const complexfloat*, Integral::MTYPE);
template bool8
MMatrixMethods::assign<ISIP_TEMPLATE_TARGET>
(MMatrix<ISIP_TEMPLATE_TARGET>&, int32, int32, const complexdouble*, Integral::MTYPE);
#endif

// method: assign
//
// arguments:
//  MMatrix<TScalar, TIntegral>& this: (output) class operand
//  int32 nrows: (input) number of rows
//  int32 ncols: (input) number of columns
//  const String* mdata: (input) matrix data
//  Integral::MTYPE type: (input) matrix type
//
// return: a bool8 value indicating status
//
// this method assigns the matrix from an array of String objects.
//
template<class TScalar, class TIntegral>
bool8 MMatrixMethods::assign(MMatrix<TScalar, TIntegral>& this_a,
			       int32 nrows_a, int32 ncols_a,
			       const String* mdata_a,
			       Integral::MTYPE type_a) {

  // create a temporary copy of the input
  //
  MVector<TScalar, TIntegral> vec;

  if (!vec.assign(this_a.vecLength(nrows_a, ncols_a, type_a), mdata_a)) {
    this_a.debug(L"this_a");    
    return Error::handle(name(), L"assign", Error::ARG, __FILE__, __LINE__);
  }

  // call the assign stream method to actually do the matrix assign
  //
  return this_a.assignStream(nrows_a, ncols_a, vec, (Integral::MTYPE)type_a);
}

// explicit instantiations
//
template bool8
MMatrixMethods::assign<ISIP_TEMPLATE_TARGET>
(MMatrix<ISIP_TEMPLATE_TARGET>&, int32, int32, const String*, Integral::MTYPE);

// method: assign
//
// arguments:
//  MMatrix<TScalar, TIntegral>& this: (output) class operand
//  int32 nrows: (input) number of rows
//  int32 ncols: (input) number of columns
//  const String& str: (input) string of data
//  Integral::MTYPE type: (input) matrix type
//  const Char delim: (input) delimiter character
//
// return: a bool8 value indicating status
//
// this method creates a matrix from a String object.
//
template<class TScalar, class TIntegral>
bool8 MMatrixMethods::assign(MMatrix<TScalar, TIntegral>& this_a,
			       int32 nrows_a, int32 ncols_a,
			       const String& str_a,
			       Integral::MTYPE type_a,
			       const Char delim_a) {

  // get the number of elements in the matrix and length of string
  //
  int32 len = this_a.vecLength(nrows_a, ncols_a, type_a);
  int32 str_len = str_a.length();

  // allow a matrix of zero dimension
  //
  if ((len == 0) || (str_len == 0)) {
    return this_a.clear(Integral::RETAIN);
  }
  
  // string to store tokens
  //
  int32 pos = 0;
  int32 num_tokens = 0;
  String sub_str;
  String tokens[len];
  
  // call tokenize method and assign the substrings to vector
  //
  while (str_a.tokenize(sub_str, pos, delim_a)) {
    
    // assign the tokens to array of Strings
    //
    if (!tokens[num_tokens++].assign(sub_str)) {
      this_a.debug(L"this_a");      
      return Error::handle(name(), L"assign", Error::ARG, __FILE__, __LINE__);
    }
  }

  // check the dimensions of matrix and input string
  //
  if (num_tokens != len) {
    str_a.debug(L"input string");
    ////Warning
    this_a.debug(L"this_a");    
    return Error::handle(name(), L"assign - wrong number of elements",
			 Error::ARG, __FILE__, __LINE__, Error::WARNING);
  }

  // set the dimension of the matrix without preserving the elements
  //
  if (!this_a.setDimensions(nrows_a, ncols_a, false, type_a)) {
    this_a.debug(L"this_a");    
    return Error::handle(name(), L"assign", MMatrix<TScalar, TIntegral>::ERR,
			 __FILE__, __LINE__);
  }

  // call the String array assign method
  //
  if (!this_a.assign(nrows_a, ncols_a, tokens, (Integral::MTYPE)type_a)) {
    this_a.debug(L"this_a");    
    return Error::handle(name(), L"assign",
			 MMatrix<TScalar, TIntegral>::ERR, __FILE__, __LINE__);
  }
  
  // exit gracefully
  //
  return true;
}

// explicit instantiations
//
template bool8
MMatrixMethods::assign<ISIP_TEMPLATE_TARGET>
(MMatrix<ISIP_TEMPLATE_TARGET>&, int32, int32, const String&,
 Integral::MTYPE, const Char);

// method: swap
//
// arguments:
//  MMatrix<TScalar, TIntegral>& this: (output) class operand
//  MMatrix<TScalar, TIntegral>& matrix: (input) input matrix
//
// return: a bool8 value indicating status
//
// this method swap all elements in the input matrix with the current matrix
//
template<class TScalar, class TIntegral>
bool8 MMatrixMethods::swap(MMatrix<TScalar, TIntegral>& this_a, 
			     MMatrix<TScalar, TIntegral>& matrix_a) {
  
  // swap out the element storage vector
  //
  this_a.m_d.swap(matrix_a.m_d);

  // swap out the other sparse vector
  //  
  this_a.row_index_d.swap(matrix_a.row_index_d);
  this_a.col_index_d.swap(matrix_a.col_index_d);
  
  // copy all other current values (number of rows, columns and type) to tmp
  //
  Integral::MTYPE type_d_tmp = this_a.type_d;
  Long nrows_d_tmp = this_a.nrows_d;
  Long ncols_d_tmp = this_a.ncols_d;
 
  // copy all other argument values (number of rows, columns and type)
  //
  this_a.type_d = matrix_a.type_d;
  this_a.nrows_d = matrix_a.nrows_d;
  this_a.ncols_d = matrix_a.ncols_d;
     
  // copy all current values (from tmp) to argument
  //
  matrix_a.type_d = type_d_tmp;
  matrix_a.nrows_d = nrows_d_tmp;
  matrix_a.ncols_d = ncols_d_tmp;
   
  // exit gracefully
  //
  return true;
}

// explicit instantiations
//
template bool8
MMatrixMethods::swap<ISIP_TEMPLATE_TARGET>
(MMatrix<ISIP_TEMPLATE_TARGET>&, MMatrix<ISIP_TEMPLATE_TARGET>&);

// method: copy
//
// arguments:
//  MMatrix<TScalar, TIntegral>& this: (output) class operand
//  const MMatrix<TAScalar, TAIntegral>& matrix: (input) input matrix
//
// return: a bool8 value indicating status
//
// this method assigns all the elements of the source matrix to the
// current matrix, this method is similar to the assign method but the
// difference is that the copy method just copies the elements of the
// matrix but doesn't modify the type of the destination matrix
//
template <class TScalar, class TIntegral, class TAScalar, class TAIntegral>
bool8 MMatrixMethods::copy(MMatrix<TScalar, TIntegral>& this_a,
			     const MMatrix<TAScalar, TAIntegral>& matrix_a) {

  // if both types are the same, simply call matrix assign method
  //
  if (this_a.type_d == matrix_a.type_d) {
    return this_a.assign(matrix_a);
  }
  
  // check if the copy is possible
  //
  if (!matrix_a.isTypePossible(this_a.type_d)) {
    this_a.debug(L"this_a");
    matrix_a.debug(L"matrix_a");    
    return Error::handle(name(), L"copy", Error::ARG, __FILE__, __LINE__);
  }

  // create space in the current matrix
  //
  if (!this_a.setDimensions(matrix_a.nrows_d, matrix_a.ncols_d)) {
    this_a.debug(L"this_a");
    matrix_a.debug(L"matrix_a");    
    return Error::handle(name(), L"copy",
			 MMatrix<TScalar, TIntegral>::ERR_DIM, 
			 __FILE__, __LINE__);
  }
    
  // type: FULL
  //  loop through each element of matrix.
  //
  if (this_a.type_d == Integral::FULL) {
    for (int32 row = 0; row < this_a.nrows_d; row++) {
      for (int32 col = 0; col < this_a.ncols_d; col++) {
	this_a.m_d(this_a.index(row, col)) = (TScalar)((TIntegral)(matrix_a.getValue(row, col)));
      }
    }
  }

  // type: DIAGONAL
  //  copy the diagonal elements only.
  //
  else if (this_a.type_d == Integral::DIAGONAL) {
    for (int32 row = 0; row < this_a.nrows_d; row++) {
      this_a.m_d(row) = (TScalar)((TIntegral)(matrix_a.getValue(row, row)));
    }
  }

  // type: SYMMETRIC, LOWER_TRIANGULAR
  //  copy the lower triangular elements only.
  //
  else if ((this_a.type_d == Integral::LOWER_TRIANGULAR) ||
      (this_a.type_d == Integral::SYMMETRIC)) {
    for (int32 row = 0; row < this_a.nrows_d; row++) {
      for (int32 col = 0; col <= row; col++) {
	this_a.m_d(this_a.index(row, col)) = (TScalar)((TIntegral)(matrix_a.getValue(row, col)));
      }
    }
  }

  // type: UPPER_TRIANGULAR
  //  copy the upper triangular elements only.
  //
  else if (this_a.type_d == Integral::UPPER_TRIANGULAR) {
    for (int32 row = 0; row < this_a.nrows_d; row++) {
      for (int32 col = row; col < this_a.ncols_d; col++) {
	this_a.m_d(this_a.index(row, col)) = (TScalar)((TIntegral)(matrix_a.getValue(row, col)));
      }
    }
  }

  // type: SPARSE
  //  copy the non-zero elements only.
  //
  else if (this_a.type_d == Integral::SPARSE) {
    
    // get the number of non-zero elements in the matrix
    //
    int32 num_elements = matrix_a.numNotEqual(0);    

    // create space for the vectors of the sparse matrix
    //
    this_a.m_d.setLength(num_elements);
    this_a.row_index_d.setLength(num_elements);
    this_a.col_index_d.setLength(num_elements);

    // type2: FULL
    //  loop over all elements
    //
    if (matrix_a.type_d == Integral::FULL) {
      for (int32 row = 0, index = 0; row < this_a.nrows_d; row++) {
	for (int32 col = 0; col < this_a.ncols_d; col++) {
	  TIntegral value = (TIntegral)matrix_a.m_d(matrix_a.index(row, col));
	  if (value != 0) {
	    this_a.m_d(index) = value;
	    this_a.row_index_d(index) = row;
	    this_a.col_index_d(index++) = col;
	  }
	}
      }
    }

    // type2: DIAGONAL
    //  loop over diagonal elements
    //
    else if (matrix_a.type_d == Integral::DIAGONAL) {
      for (int32 row = 0, index = 0; row < this_a.nrows_d; row++) {
	TIntegral value = (TIntegral)matrix_a.m_d(row);
	if (value != 0) {
	  this_a.m_d(index) = value;
	  this_a.row_index_d(index) = row;
	  this_a.col_index_d(index++) = row;
	}
      }
    }

    // type2: SYMMETRIC
    //  loop over the lower triangular part of elements, assign both lower
    //  and upper triangular part, and then sort the rows and columns
    //
    else if (matrix_a.type_d == Integral::SYMMETRIC) {
      for (int32 row = 0, index = 0; row < this_a.nrows_d; row++) {
	for (int32 col = 0; col <= row; col++) {

	  // only assign non-zero values
	  //
	  TIntegral value = (TIntegral)matrix_a.m_d(matrix_a.index(row, col));
	  if (value != 0) {

	    // assign the lower triangular part of elements
	    //
	    this_a.m_d(index) = value;
	    this_a.row_index_d(index) = row;
	    this_a.col_index_d(index++) = col;

	    // assign the symmetric elements in completely upper triangular
	    // part
	    //
	    if (row != col) {
	      this_a.m_d(index) = value;
	      this_a.row_index_d(index) = col;
	      this_a.col_index_d(index++) = row;
	    }
	  }
	}
      }

      // sort the rows and columns
      //
      this_a.sortSparse();
    }

    // type2: LOWER_TRIANGULAR
    //  loop over the lower triangular part of elements
    //
    else if (matrix_a.type_d == Integral::LOWER_TRIANGULAR) {
      for (int32 row = 0, index = 0; row < this_a.nrows_d; row++) {
	for (int32 col = 0; col <= row; col++) {
	  TIntegral value = (TIntegral)matrix_a.m_d(matrix_a.index(row, col));
	  if (value != 0) {
	    this_a.m_d(index) = value;
	    this_a.row_index_d(index) = row;
	    this_a.col_index_d(index++) = col;
	  }
	}
      }
    }

    // type2: UPPER_TRIANGULAR
    //  loop over the upper triangular part of elements
    //
    else if (matrix_a.type_d == Integral::UPPER_TRIANGULAR) {
      for (int32 row = 0, index = 0; row < this_a.nrows_d; row++) {
	for (int32 col = row; col < this_a.ncols_d; col++) {
	  TIntegral value = (TIntegral)matrix_a.m_d(matrix_a.index(row, col));
	  if (value != 0) {
	    this_a.m_d(index) = value;
	    this_a.row_index_d(index) = row;
	    this_a.col_index_d(index++) = col;
	  }
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
MMatrixMethods::copy<ISIP_TEMPLATE_TARGET, Byte, byte8>
(MMatrix<ISIP_TEMPLATE_TARGET>&, const MMatrix<Byte, byte8>&);

template bool8
MMatrixMethods::copy<ISIP_TEMPLATE_TARGET, Ushort, uint16>
(MMatrix<ISIP_TEMPLATE_TARGET>&, const MMatrix<Ushort, uint16>&);

template bool8
MMatrixMethods::copy<ISIP_TEMPLATE_TARGET, Ulong, uint32>
(MMatrix<ISIP_TEMPLATE_TARGET>&, const MMatrix<Ulong, uint32>&);

template bool8
MMatrixMethods::copy<ISIP_TEMPLATE_TARGET, Ullong, uint64>
(MMatrix<ISIP_TEMPLATE_TARGET>&, const MMatrix<Ullong, uint64>&);

template bool8
MMatrixMethods::copy<ISIP_TEMPLATE_TARGET, Short, int16>
(MMatrix<ISIP_TEMPLATE_TARGET>&, const MMatrix<Short, int16>&);

template bool8
MMatrixMethods::copy<ISIP_TEMPLATE_TARGET, Long, int32>
(MMatrix<ISIP_TEMPLATE_TARGET>&, const MMatrix<Long, int32>&);

template bool8
MMatrixMethods::copy<ISIP_TEMPLATE_TARGET, Llong, int64>
(MMatrix<ISIP_TEMPLATE_TARGET>&, const MMatrix<Llong, int64>&);

template bool8
MMatrixMethods::copy<ISIP_TEMPLATE_TARGET, Float, float32>
(MMatrix<ISIP_TEMPLATE_TARGET>&, const MMatrix<Float, float32>&);

template bool8
MMatrixMethods::copy<ISIP_TEMPLATE_TARGET, Double, float64>
(MMatrix<ISIP_TEMPLATE_TARGET>&, const MMatrix<Double, float64>&);

#ifdef ISIP_TEMPLATE_complex
template bool8
MMatrixMethods::copy<ISIP_TEMPLATE_TARGET, ComplexDouble, complexdouble>
(MMatrix<ISIP_TEMPLATE_TARGET>&, const MMatrix<ComplexDouble, complexdouble>&);

template bool8
MMatrixMethods::copy<ISIP_TEMPLATE_TARGET, ComplexFloat, complexfloat>
(MMatrix<ISIP_TEMPLATE_TARGET>&, const MMatrix<ComplexFloat, complexfloat>&);

template bool8
MMatrixMethods::copy<ISIP_TEMPLATE_TARGET, ComplexLong, complexlong>
(MMatrix<ISIP_TEMPLATE_TARGET>&, const MMatrix<ComplexLong, complexlong>&);
#endif
