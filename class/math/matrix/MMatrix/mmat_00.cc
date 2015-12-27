// file: $isip/class/math/matrix/MMatrix/mmat_00.cc
// version: $Id: mmat_00.cc 8478 2002-07-26 20:07:07Z hamaker $
//

// system include files
//
#include <typeinfo>

// isip include files
// 
#include "MMatrix.h"
#include <Console.h>
#include <VectorLong.h>

//-----------------------------------------------------------------------------
//
// we define non-integral constants in the default constructor
//      
//-----------------------------------------------------------------------------

// constants: required constants such as the class name
//
template<class TScalar, class TIntegral>
const String MMatrix<TScalar, TIntegral>::CLASS_NAME(L"MMatrix");

// constants: i/o related constants
//
template<class TScalar, class TIntegral>
const String MMatrix<TScalar, TIntegral>::DEF_PARAM(L"");

template<class TScalar, class TIntegral>
const String MMatrix<TScalar, TIntegral>::PARAM_DATA(L"values");

template<class TScalar, class TIntegral>
const String MMatrix<TScalar, TIntegral>::PARAM_NROWS(L"num_rows");

template<class TScalar, class TIntegral>
const String MMatrix<TScalar, TIntegral>::PARAM_NCOLS(L"num_cols");

template<class TScalar, class TIntegral>
const String MMatrix<TScalar, TIntegral>::PARAM_ROW_IND(L"row_indices");

template<class TScalar, class TIntegral>
const String MMatrix<TScalar, TIntegral>::PARAM_COL_IND(L"col_indices");

template<class TScalar, class TIntegral>
const String MMatrix<TScalar, TIntegral>::PARAM_TYPE(L"type");

// constants: default value
//
template<class TScalar, class TIntegral>
const TIntegral MMatrix<TScalar, TIntegral>::DEF_VALUE(TScalar::DEF_VALUE);

// constants: matrix type-related constants
//
// note that unchanged and unknown are not included, since they are
// not valid matrix types (and only useful as arguments).
//
template<class TScalar, class TIntegral>
const NameMap MMatrix<TScalar, TIntegral>::TYPE_MAP(L"FULL, DIAGONAL, SYMMETRIC, LOWER_TRIANGULAR, UPPER_TRIANGULAR, SPARSE");

// static instantiations: memory manager
//
template<class TScalar, class TIntegral>
Integral::DEBUG MMatrix<TScalar, TIntegral>::debug_level_d = Integral::NONE;

//---------------------------------------------------------------------------
//
// required public methods
//
//---------------------------------------------------------------------------

// method: debug
//
// arguments:
//  const String& name: (input) class name
//  const unichar* message: (input) message
//
// return: a bool8 value indicating status
//
template<class TScalar, class TIntegral>
bool8 MMatrix<TScalar, TIntegral>::debug(const String& name_a,
					   const unichar* message_a) const {
  
  // declare local strings to hold the class data
  //
  String output;
  String value;
  String param;

  // display the type
  //
  output.debugStr(name_a, message_a, L"type_d", TYPE_MAP((int32)type_d));
  Console::put(output);
  
  // display the number of rows
  //
  value.assign((int32)nrows_d);
  output.debugStr(name_a, message_a, L"nrows_d", value);
  Console::put(output);
  
  // display the number of columns
  //    
  value.assign((int32)ncols_d);
  output.debugStr(name_a, message_a, L"ncols_d", value);
  Console::put(output);

  // display the elements of the matrix
  //
  output.debugStr(name_a, message_a, L"m_d");
  Console::put(output);

  // loop over all rows
  //
  for (int32 i = 0; i < nrows_d; i++) {

    // output starting string
    //
    output.assign(L"[ ");

    // loop over columns and output each element
    //
    for (int32 j = 0; j < ncols_d; j++) {
      value.assign(getValue(i, j));
      output.concat(value);
      output.concat(L" ");
    }
    
    // output terminating string
    //
    output.concat(L"]\n");
    Console::put(output);
  }
  
  // for the really inquisitive user, display more detail about
  // the internal vectors
  //
  if (debug_level_d > Integral::DETAILED) {
    m_d.debug(L"m_d");
    row_index_d.debug(L"row_index_d");
    col_index_d.debug(L"col_index_d");
  }    

  // exit gracefully
  //
  return true;
}

// method: default constructor
//
// arguments: none
//
// return: none
//
// this method constructs a matrix object with default values
//
template<class TScalar, class TIntegral>
MMatrix<TScalar, TIntegral>::MMatrix() {
  
  // set the type
  //
  type_d = Integral::DEF_MTYPE;  

  // initialize the non-vector values just in case their default
  // initial values are non-zero. note that the other vector-valued
  // objects are initialized to zero.
  //
  nrows_d = 0;
  ncols_d = 0;
  
  // exit gracefully
  //
}

// method: copy constructor
//
// arguments:
//  const MMatrix& arg: (input) MMatrix
//
// return: none
//  
// this method constructs a matrix that is a copy of the input matrix.
// since it is a copy constructor that will ultimately call the assign
// method, we only need initialize integral types that are not
// initialized by default constructors.
//
template<class TScalar, class TIntegral>
MMatrix<TScalar, TIntegral>::MMatrix(const MMatrix& arg_a) {

  // set the type
  //
  type_d = Integral::DEF_MTYPE;  

  // copy the data from input matrix 
  //
  assign(arg_a);
  
  // exit gracefully
  // 
}

//---------------------------------------------------------------------------
//
// class-specific public methods:
//  extensions to required methods
//
//---------------------------------------------------------------------------

// method: eq
//
// argument(s):
//  const MMatrix& arg:  (input) operand
//
// return: a bool8 value indicating status
//
// this method checks if the current matrix is identical to the input matrix
//
template<class TScalar, class TIntegral>
bool8 MMatrix<TScalar, TIntegral>::eq(const MMatrix& arg_a) const {

  // check the Dimensions
  // 
  if (!checkDimensions(arg_a)) {
    return false;
  }
      
  // if the types of the matrices are equal, we can check their
  // internal data directly
  //
  if (type_d == arg_a.type_d) {

    // for full, symmetric, diagonal, lower, and upper triangular matrices,
    // check the internal data directly
    //
    if ((arg_a.type_d == Integral::FULL) ||
	(arg_a.type_d == Integral::DIAGONAL) ||
	(arg_a.type_d == Integral::LOWER_TRIANGULAR) ||
	(arg_a.type_d == Integral::UPPER_TRIANGULAR) ||
	(arg_a.type_d == Integral::SYMMETRIC)) {
      return m_d.eq(arg_a.m_d);
    }

    // for a sparse matrix, check the equality of each vector
    // that is part of the sparse matrix implementation
    //
    else if ((m_d.length() == arg_a.m_d.length()) &&
	     (m_d.eq(arg_a.m_d)) &&
	     (row_index_d.eq(arg_a.row_index_d)) &&
	     (col_index_d.eq(arg_a.col_index_d))) {
      return true;
    }

    // exit ungracefully: not equal
    //
    else {
      return false;
    }
  }

  // else: the matrices are different types, and we must check each matrix
  // element by element
  //
  else {

    // loop over all elements
    //
    int32 last_row_index = getNumRows();
    int32 last_col_index = getNumColumns();

    for (int32 row_index = 0; row_index < last_row_index; row_index++) {
      for (int32 col_index = 0; col_index < last_col_index; col_index++) {
	if (getValue(row_index, col_index) !=
	    arg_a.getValue(row_index, col_index)) {
	  return false;
	}
      }
    }
  }

  // exit gracefully: they must be equal
  //
  return true;
}

// method: clear
//
// arguments:
//  Integral::CMODE cmode: (input) clear mode
//
// return: a bool8 value indicating status
//
// based on the input mode, this method either resets the values of
// the class data, or releases each element, or releases memory
//
template<class TScalar, class TIntegral>
bool8 MMatrix<TScalar, TIntegral>::clear(Integral::CMODE cmode_a) {

  // mode: RETAIN
  //  set all elements to zero, but leave
  //  the dimensions and capacity unchanged
  //  
  if (cmode_a == Integral::RETAIN) {
    return assign((TIntegral)DEF_VALUE);
  }

  // mode: RESET
  //  set the dimensions to zero, but leave the capacity unchanged
  //  
  else if (cmode_a == Integral::RESET) {
    return setDimensions(0, 0, false, type_d);
  }

  // modes: RELEASE and FREE
  //  set the capacity to zero, but leave the type unchanged
  //
  else {
    
    return (setDimensions(0, 0, false, type_d) &&
	    setCapacity(0, 0, false, type_d));
  }
}

// method: constructor
//
// arguments:
//  int32 nrows: (input) number of rows
//  int32 ncols: (input) number of columns
//  Integral::MTYPE type: (input) type of the matrix
//
// return: none
//
// this method constructs a matrix having a specified number of rows,
// number of columns and type
//
template<class TScalar, class TIntegral>
MMatrix<TScalar, TIntegral>::MMatrix(int32 nrows_a, int32 ncols_a,
				     Integral::MTYPE type_a) {

  // check the type
  //
  type_d = Integral::DEF_MTYPE;
  type_d = checkType(type_a);

  // initialize the non-vector values just in case their default
  // initial values are non-zero. note that the other vector-valued
  // objects are initialized to zero.
  //
  nrows_d = 0;
  ncols_d = 0;
  
  // check for square matrics
  //
  checkSquare(nrows_a, ncols_a, type_d);

  // set the dimensions of the matrix
  //
  setDimensions(nrows_a, ncols_a, false, type_d);

  // exit gracefully
  //
}

// method: assign
//
// arguments:
//  TIntegral value: (input) value to be assigned
//
// return: a bool8 value indicating status
//
// this method assigns the input value to every element in the matrix.
// in this version of assign, it was decided that the type of the
// matrix would not be changed. hence, only the vectors need to be
// assigned.
//
template<class TScalar, class TIntegral>
bool8 MMatrix<TScalar, TIntegral>::assign(TIntegral value_a) {

  // type: SPARSE
  //
  if (type_d == Integral::SPARSE) {

    //  if the current matrix is a sparse matrix, and the value is zero,
    //  then we essentially set the length to zero, because sparse matrices
    //  only need to store non-zero values.
    //
    if (value_a == (TIntegral)0) {
      row_index_d.setLength(0);
      col_index_d.setLength(0);
      m_d.setLength(0);
    }

    // else: assign new values. this is going to be really inefficient
    // because a sparse matrix doesn't work well when all the values
    // are non-zero. nevertheless, let the user's wish prevail.
    // 
    else {

      // increase the size of the vectors
      //
      int32 num_vals = nrows_d * ncols_d;
      row_index_d.setLength(num_vals);
      col_index_d.setLength(num_vals);
      m_d.setLength(num_vals);

      // create the indices
      //
      int32 index = 0;

      for (int32 row = 0; row < nrows_d; row++) {
	for (int32 col = 0; col < ncols_d; col++) {
	  row_index_d(index) = row;
	  col_index_d(index) = col;
	  m_d(index) = value_a;
	  index++;
	}
      }
    }

    // exit gracefully
    //
    return true;
  }

  // type: anything other than SPARSE
  //
  else {
    return m_d.assign(value_a);
  }
}

// method: setCapacity
//
// arguments:
//  const MMatrix& pmat: (input) prototype matrix
//  bool8 preserve_values: (input) save old values
//  Integral::MTYPE type: (input) type of the new matrix
//
// return: a bool8 value indicating status
//
// this method sets the capacity of the matrix to be the same as the
// capacity of the input matrix. it saves the values of the matrix if
// the bool8 flag is true else it just creates space in the current
// matrix.
//
template<class TScalar, class TIntegral>
bool8 MMatrix<TScalar, TIntegral>::setCapacity(const MMatrix& pmat_a,
						 bool8 preserve_values_a,
						 Integral::MTYPE type_a) {

  // call the master function
  //
  return setCapacity(pmat_a.getNumRows(), pmat_a.getNumColumns(),
		     preserve_values_a, type_a);
}

// method: setCapacity
//
// arguments:
//  int32 nrows: (input) new number of rows (for capacity)
//  int32 ncols: (input) new number of cols (for capacity)
//  bool8 preserve_values: (input) save old values
//  Integral::MTYPE type: (input) type of the new matrix
//
// return: a bool8 value indicating status
//
// this method sets the capacity of the matrix to the specified
// number of rows and columns. it preserves the values in the matrix
// only when the bool8 flag is set to true.
//
template<class TScalar, class TIntegral>
bool8 MMatrix<TScalar, TIntegral>::setCapacity(int32 nrows_a,
						 int32 ncols_a,
						 bool8 preserve_values_a,
						 Integral::MTYPE type_a) {
  
  // condition: bad arguments
  //
  if ((nrows_a < 0) || (ncols_a < 0)) {
    this->debug(L"this");
    return Error::handle(name(), L"setCapacity", Error::ARG,
			 __FILE__, __LINE__);
  }

  // capacity < length: error (capacity can't be less than the length)
  //   
  else if (vecLength(nrows_a , ncols_a, type_a) <
	   vecLength(nrows_d, ncols_d, type_d)) {
    this->debug(L"this");    
    return Error::handle(name(), L"setCapacity", Error::ARG,
			 __FILE__, __LINE__);
  }
	   
  // condition: type = UNCHANGED
  //
  else if (type_a == Integral::UNCHANGED) {
    return setCapacity(nrows_a, ncols_a, preserve_values_a, type_d);
  }

  // condition: preserve_values = false
  //  if we don't need to preserve values, this is really easy. simply
  //  convert the old space into the new space.
  //
  else if (!preserve_values_a) {
    return vecResetCapacity(nrows_a, ncols_a, type_a);
  }

  // condition: preserve values = true and the types are the same
  //
  else if (type_a == type_d) {

    // we need to simply resize the underlying data structures
    //
    return vecResizeCapacity(nrows_a, ncols_a);
  }

  // condition: preserve values = true and the types are different
  //
  // this is the hard one. the new matrix is a different type
  // than the old matrix. we must do this in two steps: (1) change
  // the type of the existing matrix; (2) change the capacity.
  //
  // fortunately, changeType copies the data for us, which makes this
  // operation much easier.
  //
  else {

    // copy the old data manually
    //
    changeType(type_a);

    // change the capacity
    //
    return setCapacity((int32)nrows_a, (int32)ncols_a, preserve_values_a, type_a);
  }
}

// method: setDimensions
//
// arguments:
//  const MMatrix& pmat: (input) prototype matrix
//  bool8 preserve_values: (input) should we save the memory
//  Integral::MTYPE type: (input) type of the new matrix
//
// return: a bool8 value indicating status
//
// this method sets the dimensions of the matrix to be the same as
// that of the input matrix. it preserves the values only when the
// bool8 flag is true.
//
template<class TScalar, class TIntegral>
bool8 MMatrix<TScalar, TIntegral>::setDimensions(const MMatrix& pmat_a,
						   bool8 preserve_values_a,
						   Integral::MTYPE type_a) {

  // call the master function
  //
  return setDimensions(pmat_a.getNumRows(), pmat_a.getNumColumns(),
		       preserve_values_a, type_a);
}

// method: setDimensions
//
// arguments:
//  int32 nrows: (input) new number of rows
//  int32 ncols: (input) new number of columns
//  bool8 preserve_values: (input) flag to save existing values
//  Integral::MTYPE type: (input) type of the new matrix
//
// return: a bool8 value indicating status
//
// this method sets the dimensions of the matrix. capacity is
// adjusted accordingly.
//
template<class TScalar, class TIntegral>
bool8 MMatrix<TScalar, TIntegral>::setDimensions(int32 nrows_a, int32 ncols_a,
						   bool8 preserve_values_a,
						   Integral::MTYPE type_a) {
  
  // condition: bad arguments
  //
  if ((nrows_a < 0) || (ncols_a < 0) ||
      (!checkSquare(nrows_a, ncols_a, type_a))) {
    this->debug(L"this");    
    return Error::handle(name(), L"setDimensions", Error::ARG,
			 __FILE__, __LINE__);
  }
  
  // condition: type = UNCHANGED
  //
  else if (type_a == Integral::UNCHANGED) {
    return setDimensions(nrows_a, ncols_a, preserve_values_a, type_d);
  }

  // condition: the types are the same
  //  whether we preserve values or not, we do essentially the same thing.
  //
  else if (type_a == type_d) {
    return vecDimensionLength(nrows_a, ncols_a, preserve_values_a);
  }

  // condition: preserve_values = false
  //  if we don't need to preserve values, this is really easy. simply
  //  convert the old space into the new space. because we have to
  //  change the type, we have to do a little more work deleting
  //  old space and creating new space.
  //
  else if (!preserve_values_a) {
    return vecCreateLength(nrows_a, ncols_a, type_a);
  }

  // condition: preserve_values = true and the types are different
  //
  // this is the hard one. the new matrix is a different type
  // than the old matrix. we must do this in two steps: (1) change
  // the type of the existing matrix; (2) change the capacity.
  //
  // fortunately, changeType copies the data for us, which makes this
  // operation much easier.
  //
  else {

    // change the type (which preserves the values)
    //
    changeType(type_a);

    // change the dimensions now that the types are the same
    //
    return setDimensions(nrows_a, ncols_a, true, type_d);
  }
}

// method: almostEqual
//
// arguments:
//  TIntegral value: (input) value to be compared with
//  float64 percent: (input) percentage of allowable difference
//  float64 bound: (input) a lower bound on the comparison
//
// return: a bool8 value indicating status
//
// note that this method is now very simple, because it only checks
// values actually stored in the matrix (instead of checking all values
// including values that are zero by definition). so this simple
// function call works for all types of matrices.
//
template<class TScalar, class TIntegral>
bool8 MMatrix<TScalar, TIntegral>::almostEqual(TIntegral value_a,
						 float64 percent_a,
						 float64 bound_a) const {
  return m_d.almostEqual(value_a, percent_a, bound_a);
}

// method: almostEqual
//
// argument(s):
//  MMatrix& arg: (input) matrix to be compared
//  float64 percent: (input) percentage of allowable difference
//  float64 bound: (input) a lower bound on the comparison
//
// return: a bool8 value indicating status
//
// this methods checks if the current matrix is almost equal to the
// input matrix
//
template<class TScalar, class TIntegral>
bool8 MMatrix<TScalar, TIntegral>::almostEqual(const MMatrix& arg_a,
						 float64 percent_a,
						 float64 bound_a) const {

  // check the dimensions: the matrices must be the same size
  // 
  if (!checkDimensions(arg_a)) {
    return false;
  }

  // condition: both are SPARSE
  //  check all components of the matrix
  //
  if ((type_d == Integral::SPARSE) && (arg_a.type_d == Integral::SPARSE)) {
    return (m_d.almostEqual(arg_a.m_d, percent_a, bound_a) &&
	    row_index_d.eq(arg_a.row_index_d) &&
	    col_index_d.eq(arg_a.col_index_d));
  }

  // condition: both are the same type, and not SPARSE
  //  check data directly
  //
  else if ((type_d != Integral::SPARSE) && (type_d == arg_a.type_d)) {
    return m_d.almostEqual(arg_a.m_d, percent_a, bound_a);
  }

  // condition: different types
  //  must compare the matrices element by element
  //
  else {
    int32 nrows = getNumRows();
    int32 ncols = getNumColumns();
    for (int32 row = 0; row < nrows; row++) {
      for (int32 col = 0; col < ncols; col++) {
	if (!Integral::almostEqual(getValue(row, col),
				   arg_a.getValue(row, col),
				   percent_a, bound_a)) {
	  return false;
	}
      }
    }  
  }
  
  // exit gracefully: they must be equal
  //
  return true;
}

// method: checkType
//
// arguments:
//  Integral::MTYPE type: (input) the type of the matrix
//
// return: an MTYPE value that is the same as the input
//
// unfortunately, C++ lets you define a integer value outside the range
// of an enum. therefore, every time an enum is passed as an argument,
// we must check its validity. this method errors if the argument
// is not an allowable value.
// 
template<class TScalar, class TIntegral>
Integral::MTYPE
MMatrix<TScalar, TIntegral>::checkType(Integral::MTYPE type_a) const {

  // UNCHANGED: pass the existing type
  //
  if (type_a == Integral::UNCHANGED) {
    return type_d;
  }

  // check against all known valid storage types.
  //
  else if ((type_a == Integral::FULL) ||
	   (type_a == Integral::DIAGONAL) ||
	   (type_a == Integral::SYMMETRIC) ||
	   (type_a == Integral::LOWER_TRIANGULAR) ||
	   (type_a == Integral::UPPER_TRIANGULAR) ||
	   (type_a == Integral::SPARSE)) {
    return type_a;
  }

  // else: error
  //
  else {
    this->debug(L"this");    
    Error::handle(name(), L"checkType", Error::ARG, __FILE__, __LINE__);
    return Integral::UNKNOWN;
  }
}

// method: checkSquare
//
// arguments:
//  int32 nrows: (input) the number of rows
//  int32 ncols: (input) the number of cols
//  Integral::MTYPE type: (input) the type of the matrix
//
// return: a bool8 value indicating status
//
// several matrix types require the matrix to be square.
// this method performs this check and errors accordingly.
//
template<class TScalar, class TIntegral>
bool8
MMatrix<TScalar, TIntegral>::checkSquare(int32 nrows_a, int32 ncols_a,
					 Integral::MTYPE type_a) const {
  
  // UNCHANGED: pass the existing type
  //
  if (type_a == Integral::UNCHANGED) {
    return checkSquare(nrows_a, ncols_a, type_d);
  }

  // check against all known valid storage types that require a
  //  square matrix
  //
  else if ((type_a == Integral::SYMMETRIC) ||
	   (type_a == Integral::LOWER_TRIANGULAR) ||
	   (type_a == Integral::UPPER_TRIANGULAR)) {

    // check for a square matrix
    //
    if (nrows_a == ncols_a) {
      return true;
    }
    else {
      this->debug(L"this");      
      return Error::handle(name(), L"checkSquare", Error::ARG, __FILE__,
			   __LINE__);
    }
  }

  // else: other types don't require a square matrix
  //
  else {
    return true;
  }
}

// method: changeType
//
// arguments:
//  Integral::MTYPE type: (input) new matrix type 
//
// return: a bool8 value indicating status
//
// this method changes the type of a matrix from the
// current type (type_d) to the new type (type_a). data is preserved
// by copying it to a local vector.
// 
template<class TScalar, class TIntegral>
bool8 MMatrix<TScalar, TIntegral>::changeType(Integral::MTYPE type_a) {
  
  // condition: check the arguments
  //  (1) old and new matrices are the same type; we are done
  //  (2) type_a is UNCHANGED; we are done
  //
  if ((type_d == type_a) || (type_a == Integral::UNCHANGED)) {
    return true;
  }

  // condition: check if the conversion is possible
  //
  else if (!isTypePossible(type_a)) {
    String output(L"cannot change this matrix to type ");
    output.concat(TYPE_MAP(type_a));
    Console::put(output);
    this->debug(L"this");
    return Error::handle(name(), L"changeType", 
			 MMatrix<TScalar, TIntegral>::ERR_OPTYPE,
			 __FILE__, __LINE__);
  }

  // condition: non-SPARSE => non-SPARSE
  //  the technique for copying data from non-SPARSE matrices is to loop over
  //  all elements in the output matrix, and retrieve the corresponding
  //  values from the input.
  //
  if ((type_d != Integral::SPARSE) && (type_a != Integral::SPARSE)) {
      
    // create a temporary vector for the output values
    //
    TVector tmp(vecLength(nrows_d, ncols_d, type_a));

    // assign elements - loop over rows
    //
    for (int32 row = 0; row < nrows_d; row++) {

      // loop over *only* the necessary columns
      //
      int32 first_col = startColumn(row, type_d, type_a);
      int32 last_col = stopColumn(row, type_d, type_a);

      for (int32 col = first_col; col <= last_col; col++) {
	tmp(index(row, col, nrows_d, ncols_d, type_a)) =
	  m_d(index(row, col, nrows_d, ncols_d, type_d));
      }
    }

    // now we can overwrite the input data
    //
    m_d.assign(tmp);
  }

  // condition: non-SPARSE => SPARSE
  //  the technique for filling SPARSE is to only assign non-zero elements
  //
  else if ((type_d != Integral::SPARSE) && (type_a == Integral::SPARSE)) {

    // find the number of non-zero elements in the matrix
    // and allocate temporary space
    //
    int32 count = numNotEqual(0);
    TVector tmp(count);
    row_index_d.setLength(count);
    col_index_d.setLength(count);
      
    // assign elements
    //
    for (int32 row = 0, index = 0; row < nrows_d; row++) {

      // loop over *only* the necessary columns:
      //
      int32 first_col = startColumn(row, type_d, Integral::FULL);
      int32 last_col = stopColumn(row, type_d, Integral::FULL);

      for (int32 col = first_col; col <= last_col; col++) {

	// get the value at current position and save it if it is non-zero
	//
	TIntegral value = getValue(row, col);
	  
	if (value != (TIntegral)0) {
	  tmp(index) = value;
	  row_index_d(index) = row;
	  col_index_d(index++) = col;
	}
      }
    }

    // now we can overwrite the input data
    //
    m_d.assign(tmp);
  }

  // condition: SPARSE => non-SPARSE
  //  the technique for converting SPARSE is fairly easy: only assign
  //  the specified non-zero elements.
  //
  else if ((type_d == Integral::SPARSE) && (type_a != Integral::SPARSE)) {

    // allocate temporary space and make sure it is zero'ed
    //
    TVector tmp(vecLength(nrows_d, ncols_d, type_a));

    // assign elements
    //
    int32 num_elements = row_index_d.length();
    
    for (int32 ind = 0; ind < num_elements; ind++) {
      tmp(index(row_index_d(ind), col_index_d(ind),
		nrows_d, ncols_d, type_a)) = m_d(ind);
    }

    // now we can overwrite the input data
    //
    m_d.assign(tmp);
    row_index_d.clear(Integral::RETAIN);
    col_index_d.clear(Integral::RETAIN);
  }
  
  // condition: error
  //  we never should hit this point
  else {
    this->debug(L"this");    
    return Error::handle(name(), L"changeType", 
			 MMatrix<TScalar, TIntegral>::ERR_UNKTYP, 
			 __FILE__, __LINE__);
  }

  // finally, set the type equal to the new type
  //
  type_d = type_a;

  // exit ungracefully
  //
  return true;
}

// method: index
//
// arguments:
//  int32 row: (input) first index
//  int32 col: (input) second index
//  int32 nrows: (input) number of rows
//  int32 ncols: (input) number of cols
//  Integral::MTYPE type: (input) the matrix type
//
// return: a int32 value containing storage index of an element of matrix
//  
// since most of the matrix types are stored in a standard vector,
// we need a method to facilitate indexing computations - converting from
// row and column indices to an array index.
//
// for efficiency reasons, we do not check whether the requested index
// is out of bounds. other methods will catch this (eventually).
//
// finally, note that for SPARSE, an index will be returned only if
// the requested element is explicitly stored in the matrix. if not,
// an error handler is called.
//
template<class TScalar, class TIntegral>
int32 MMatrix<TScalar, TIntegral>::index(int32 row_a, int32 col_a,
					int32 nrows_a, int32 ncols_a,
					Integral::MTYPE type_a) const {

  // type: UNCHANGED
  //
  if (type_a == Integral::UNCHANGED) {
    return index(row_a, col_a, nrows_a, ncols_a, type_d);
  }

  // type: FULL
  //
  else if (type_a == Integral::FULL) {
    return (row_a * ncols_a + col_a);
  }

  // type: DIAGONAL
  //  the address must be on the diagonal
  //
  else if (type_a == Integral::DIAGONAL) {
    if (row_a == col_a) {
      return row_a;
    }
  }

  // type: SYMMETRIC
  //
  else if (type_a == Integral::SYMMETRIC) {

    // check the dimensions: the matrix must be square
    //
    if (nrows_a == ncols_a) {

      // swap the indices if necessary: remember that the lower half of the
      // symmetric matrix is stored.
      //
      int32 tmp;

      if (row_a < col_a) {
	tmp = row_a;
	row_a = col_a;
	col_a = tmp;
      }

      // now do the typical calculation
      //
      return ((row_a * (row_a + 1) / 2) + col_a);
    }
  }

  // type: LOWER_TRIANGULAR
  //  the address must be in the lower part of the matrix, and the matrix
  //  must be square
  //
  else if (type_a == Integral::LOWER_TRIANGULAR) {
    if ((nrows_a == ncols_a) && (row_a >= col_a)) {
      return ((row_a * (row_a + 1) / 2) + col_a);
    }
  }

  // type: UPPER_TRIANGULAR
  //  the address must be in the upper part of the matrix, and the matrix
  //  must be square
  //
  else if (type_a == Integral::UPPER_TRIANGULAR) {
    if ((nrows_a == ncols_a) && (col_a >= row_a)) {
      return ((col_a * (col_a + 1) / 2) + row_a);
    }
  }

  // type: SPARSE
  //  find the matching index
  //
  else if (type_a == Integral::SPARSE) {

    // loop over all non-zero elements
    //
    int32 last_index = row_index_d.length();

    for (int32 index = 0; index < last_index; index++) {
      if ((row_index_d(index) == row_a) &&
	  (col_index_d(index) == col_a)) {
	return index;
      }
    }
  }

  // exit ungracefully: 
  //  if we got this far, there was an indexing error. this can happen
  //  for three reasons: the matrix was a SPARSE matrix; a matrix
  //  required to be square wasn't; or an index was out of range for
  //  the type of matrix given.
  //
  this->debug(L"this");  
  return Error::handle(name(), L"index", Error::ARG, __FILE__, __LINE__);
}

// method: startRow
//
// arguments:
//  int32 col: (input) col index
//  Integral::MTYPE type_1: (input) matrix type
//  Integral::MTYPE type_2: (input) matrix type
//
// return: a int32 value containing the column index of the first
//  available element in a column
//  
// this method is typically used when copying data from one matrix to
// the other. it determines the first non-zero value in a given
// column that needs to be copied into the destination matrix.
// the rules implemented below can be summarized with the following table:
//
//  TYPE1                TYPE2
//         full  diag  symm  ltri  utri  sprs
//  full    0     col   0     col   0     0
//  diag    col   col   col   col   col   col
//  symm    0     col   col   col   0     0
//  ltri    col   col   col   col   col   col
//  utri    0     col   0     col   0     0
//  sprs    0     col   0     col   0     0
//
// this matrix should always be symmetric.
//
template<class TScalar, class TIntegral>
int32 MMatrix<TScalar, TIntegral>::startRow(int32 col_a,
					   Integral::MTYPE type_1_a,
					   Integral::MTYPE type_2_a) const {

  // check the arguments
  //
  if (type_2_a == Integral::UNCHANGED) {
    type_2_a = type_1_a;
  }

  // type1: FULL
  //
  if (type_1_a == Integral::FULL) {
    if (type_2_a == Integral::FULL) {
      return 0;
    }
    else if (type_2_a == Integral::DIAGONAL) {
      return col_a;
    }
    else if (type_2_a == Integral::SYMMETRIC) {
      return 0;
    }
    else if (type_2_a == Integral::LOWER_TRIANGULAR) {
      return col_a;
    }
    else if (type_2_a == Integral::UPPER_TRIANGULAR) {
      return 0;
    }
    else if (type_2_a == Integral::SPARSE) {
      return 0;
    }
  }

  // type_1: DIAGONAL
  //
  else if (type_1_a == Integral::DIAGONAL) {
    if (type_2_a == Integral::FULL) {
      return col_a;
    }
    else if (type_2_a == Integral::DIAGONAL) {
      return col_a;
    }
    else if (type_2_a == Integral::SYMMETRIC) {
      return col_a;
    }
    else if (type_2_a == Integral::LOWER_TRIANGULAR) {
      return col_a;
    }
    else if (type_2_a == Integral::UPPER_TRIANGULAR) {
      return col_a;
    }
    else if (type_2_a == Integral::SPARSE) {
      return col_a;
    }
  }

  // type_1: SYMMETRIC
  //
  else if (type_1_a == Integral::SYMMETRIC) {
    if (type_2_a == Integral::FULL) {
      return 0;
    }
    else if (type_2_a == Integral::DIAGONAL) {
      return col_a;
    }
    else if (type_2_a == Integral::SYMMETRIC) {
      return col_a;
    }
    else if (type_2_a == Integral::LOWER_TRIANGULAR) {
      return col_a;
    }
    else if (type_2_a == Integral::UPPER_TRIANGULAR) {
      return 0;
    }
    else if (type_2_a == Integral::SPARSE) {
      return 0;
    }
  }

  // type_1: LOWER_TRIANGULAR
  //
  else if (type_1_a == Integral::LOWER_TRIANGULAR) {
    if (type_2_a == Integral::FULL) {
      return col_a;
    }
    else if (type_2_a == Integral::DIAGONAL) {
      return col_a;
    }
    else if (type_2_a == Integral::SYMMETRIC) {
      return col_a;
    }
    else if (type_2_a == Integral::LOWER_TRIANGULAR) {
      return col_a;
    }
    else if (type_2_a == Integral::UPPER_TRIANGULAR) {
      return col_a;
    }
    else if (type_2_a == Integral::SPARSE) {
      return col_a;
    }
  }

  // type_1: UPPER_TRIANGULAR
  //
  else if (type_1_a == Integral::UPPER_TRIANGULAR) {
    if (type_2_a == Integral::FULL) {
      return 0;
    }
    else if (type_2_a == Integral::DIAGONAL) {
      return col_a;
    }
    else if (type_2_a == Integral::SYMMETRIC) {
      return 0;
    }
    else if (type_2_a == Integral::LOWER_TRIANGULAR) {
      return col_a;
    }
    else if (type_2_a == Integral::UPPER_TRIANGULAR) {
      return 0;
    }
    else if (type_2_a == Integral::SPARSE) {
      return 0;
    }
  }

  // type_1: SPARSE
  //
  else if (type_1_a == Integral::SPARSE) {
    if (type_2_a == Integral::FULL) {
      return 0;
    }
    else if (type_2_a == Integral::DIAGONAL) {
      return col_a;
    }
    else if (type_2_a == Integral::SYMMETRIC) {
      return 0;
    }
    else if (type_2_a == Integral::LOWER_TRIANGULAR) {
      return col_a;
    }
    else if (type_2_a == Integral::UPPER_TRIANGULAR) {
      return 0;
    }
    else if (type_2_a == Integral::SPARSE) {
      return 0;
    }
  }

  // type: UNKNOWN
  //
  this->debug(L"this");  
  return Error::handle(name(), L"startRow", Error::ARG,
		       __FILE__, __LINE__);
}

// method: stopRow
//
// arguments:
//  int32 col: (input) col index
//  Integral::MTYPE type_1: (input) matrix type
//  Integral::MTYPE type_2: (input) matrix type
//
// return: a int32 value containing the column index of the first
//  available element in a row
//  
// this method is typically used when copying data from one matrix to
// the other. it determines the last non-zero value in a given
// column that needs to be copied into the destination matrix.
// the rules implemented below can be summarized with the following table:
//
// see startColumn for a detailed description of what this method does.
// the rules implemented below can be summarized with the following table:
//
//  TYPE1                TYPE2
//         full  diag  symm  ltri  utri  sprs
//  full   nrows col   nrows nrows col   nrows
//  diag   col   col   col   col   col   col
//  symm   nrows col   nrows nrows col   nrows
//  ltri   nrows col   nrows nrows col   nrows
//  utri   col   col   col   col   col   col
//  sprs   nrows col   neows nrows col   nrows   
//
// this matrix should always be symmetric.
//
template<class TScalar, class TIntegral>
int32 MMatrix<TScalar, TIntegral>::stopRow(int32 col_a,
					  Integral::MTYPE type_1_a,
					  Integral::MTYPE type_2_a) const {

  // check the arguments
  //
  if (type_2_a == Integral::UNCHANGED) {
    type_2_a = type_1_a;
  }

  // type1: FULL
  //
  if (type_1_a == Integral::FULL) {
    if (type_2_a == Integral::FULL) {
      return (int32)nrows_d - 1;
    }
    else if (type_2_a == Integral::DIAGONAL) {
      return col_a;
    }
    else if (type_2_a == Integral::SYMMETRIC) {
      return (int32)nrows_d - 1;
    }
    else if (type_2_a == Integral::LOWER_TRIANGULAR) {
      return (int32)nrows_d - 1;
    }
    else if (type_2_a == Integral::UPPER_TRIANGULAR) {
      return col_a;
    }
    else if (type_2_a == Integral::SPARSE) {
      return (int32)nrows_d - 1;
    }
  }

  // type_1: DIAGONAL
  //
  else if (type_1_a == Integral::DIAGONAL) {
    if (type_2_a == Integral::FULL) {
      return col_a;
    }
    else if (type_2_a == Integral::DIAGONAL) {
      return col_a;
    }
    else if (type_2_a == Integral::SYMMETRIC) {
      return col_a;
    }
    else if (type_2_a == Integral::LOWER_TRIANGULAR) {
      return col_a;
    }
    else if (type_2_a == Integral::UPPER_TRIANGULAR) {
      return col_a;
    }
    else if (type_2_a == Integral::SPARSE) {
      return col_a;
    }
  }

  // type_1: SYMMETRIC
  //
  else if (type_1_a == Integral::SYMMETRIC) {
    if (type_2_a == Integral::FULL) {
      return (int32)nrows_d - 1;
    }
    else if (type_2_a == Integral::DIAGONAL) {
      return col_a;
    }
    else if (type_2_a == Integral::SYMMETRIC) {
      return (int32)nrows_d - 1;
    }
    else if (type_2_a == Integral::LOWER_TRIANGULAR) {
      return (int32)nrows_d - 1;
    }
    else if (type_2_a == Integral::UPPER_TRIANGULAR) {
      return col_a;
    }
    else if (type_2_a == Integral::SPARSE) {
      return (int32)nrows_d - 1;
    }
  }

  // type_1: LOWER_TRIANGULAR
  //
  else if (type_1_a == Integral::LOWER_TRIANGULAR) {
    if (type_2_a == Integral::FULL) {
      return (int32)nrows_d - 1;
    }
    else if (type_2_a == Integral::DIAGONAL) {
      return col_a;
    }
    else if (type_2_a == Integral::SYMMETRIC) {
      return (int32)nrows_d - 1;
    }
    else if (type_2_a == Integral::LOWER_TRIANGULAR) {
      return (int32)nrows_d - 1;
    }
    else if (type_2_a == Integral::UPPER_TRIANGULAR) {
      return col_a;
    }
    else if (type_2_a == Integral::SPARSE) {
      return (int32)nrows_d - 1;
    }
  }

  // type_1: UPPER_TRIANGULAR
  //
  else if (type_1_a == Integral::UPPER_TRIANGULAR) {
    if (type_2_a == Integral::FULL) {
      return col_a;
    }
    else if (type_2_a == Integral::DIAGONAL) {
      return col_a;
    }
    else if (type_2_a == Integral::SYMMETRIC) {
      return col_a;
    }
    else if (type_2_a == Integral::LOWER_TRIANGULAR) {
      return col_a;
    }
    else if (type_2_a == Integral::UPPER_TRIANGULAR) {
      return col_a;
    }
    else if (type_2_a == Integral::SPARSE) {
      return col_a;
    }
  }

  // type_1: SPARSE
  //
  else if (type_1_a == Integral::SPARSE) {
    if (type_2_a == Integral::FULL) {
      return (int32)nrows_d - 1;
    }
    else if (type_2_a == Integral::DIAGONAL) {
      return col_a;
    }
    else if (type_2_a == Integral::SYMMETRIC) {
      return (int32)nrows_d - 1;
    }
    else if (type_2_a == Integral::LOWER_TRIANGULAR) {
      return (int32)nrows_d - 1;
    }
    else if (type_2_a == Integral::UPPER_TRIANGULAR) {
      return col_a;
    }
    else if (type_2_a == Integral::SPARSE) {
      return (int32)nrows_d - 1;
    }
  }

  // type: UNKNOWN
  //
  this->debug(L"this");  
  return Error::handle(name(), L"stopRow", Error::ARG,
		       __FILE__, __LINE__);
}

// method: startColumn
//
// arguments:
//  int32 row: (input) row index
//  Integral::MTYPE type_1: (input) matrix type
//  Integral::MTYPE type_2: (input) matrix type
//
// return: a int32 value containing the column index of the first
//  available element in a row
//  
// this method is typically used when copying data from one matrix to
// the other. it determines the first non-zero value is a given
// row that needs to be copied into the destination matrix.
// the rules implemented below can be summarized with the following table:
//
// the rules implemented below can be summarized with the following table:
//
//  TYPE1                TYPE2
//         full  diag  symm  ltri  utri  sprs
//  full    0     row   0     0     row   0
//  diag    row   row   row   row   row   row
//  symm    0     row   0     0     row   0
//  ltri    0     row   0     0     row   0
//  utri    row   row   row   row   row   row
//  sprs    0     row   0     0     row   0   
//
// this matrix should always be symmetric.
//
template<class TScalar, class TIntegral>
int32 MMatrix<TScalar, TIntegral>::startColumn(int32 row_a,
					      Integral::MTYPE type_1_a,
					      Integral::MTYPE type_2_a) const {

  // check the arguments
  //
  if (type_2_a == Integral::UNCHANGED) {
    type_2_a = type_1_a;
  }

  // type1: FULL
  //
  if (type_1_a == Integral::FULL) {
    if (type_2_a == Integral::FULL) {
      return 0;
    }
    else if (type_2_a == Integral::DIAGONAL) {
      return row_a;
    }
    else if (type_2_a == Integral::SYMMETRIC) {
      return 0;
    }
    else if (type_2_a == Integral::LOWER_TRIANGULAR) {
      return 0;
    }
    else if (type_2_a == Integral::UPPER_TRIANGULAR) {
      return row_a;
    }
    else if (type_2_a == Integral::SPARSE) {
      return 0;
    }
  }

  // type_1: DIAGONAL
  //
  else if (type_1_a == Integral::DIAGONAL) {
    if (type_2_a == Integral::FULL) {
      return row_a;
    }
    else if (type_2_a == Integral::DIAGONAL) {
      return row_a;
    }
    else if (type_2_a == Integral::SYMMETRIC) {
      return row_a;
    }
    else if (type_2_a == Integral::LOWER_TRIANGULAR) {
      return row_a;
    }
    else if (type_2_a == Integral::UPPER_TRIANGULAR) {
      return row_a;
    }
    else if (type_2_a == Integral::SPARSE) {
      return row_a;
    }
  }

  // type_1: SYMMETRIC
  //
  else if (type_1_a == Integral::SYMMETRIC) {
    if (type_2_a == Integral::FULL) {
      return 0;
    }
    else if (type_2_a == Integral::DIAGONAL) {
      return row_a;
    }
    else if (type_2_a == Integral::SYMMETRIC) {
      return 0;
    }
    else if (type_2_a == Integral::LOWER_TRIANGULAR) {
      return 0;
    }
    else if (type_2_a == Integral::UPPER_TRIANGULAR) {
      return row_a;
    }
    else if (type_2_a == Integral::SPARSE) {
      return 0;
    }
  }

  // type_1: LOWER_TRIANGULAR
  //
  else if (type_1_a == Integral::LOWER_TRIANGULAR) {
    if (type_2_a == Integral::FULL) {
      return 0;
    }
    else if (type_2_a == Integral::DIAGONAL) {
      return row_a;
    }
    else if (type_2_a == Integral::SYMMETRIC) {
      return 0;
    }
    else if (type_2_a == Integral::LOWER_TRIANGULAR) {
      return 0;
    }
    else if (type_2_a == Integral::UPPER_TRIANGULAR) {
      return row_a;
    }
    else if (type_2_a == Integral::SPARSE) {
      return 0;
    }
  }

  // type_1: UPPER_TRIANGULAR
  //
  else if (type_1_a == Integral::UPPER_TRIANGULAR) {
    if (type_2_a == Integral::FULL) {
      return row_a;
    }
    else if (type_2_a == Integral::DIAGONAL) {
      return row_a;
    }
    else if (type_2_a == Integral::SYMMETRIC) {
      return row_a;
    }
    else if (type_2_a == Integral::LOWER_TRIANGULAR) {
      return row_a;
    }
    else if (type_2_a == Integral::UPPER_TRIANGULAR) {
      return row_a;
    }
    else if (type_2_a == Integral::SPARSE) {
      return row_a;
    }
  }

  // type_1: SPARSE
  //
  else if (type_1_a == Integral::SPARSE) {
    if (type_2_a == Integral::FULL) {
      return 0;
    }
    else if (type_2_a == Integral::DIAGONAL) {
      return row_a;
    }
    else if (type_2_a == Integral::SYMMETRIC) {
      return 0;
    }
    else if (type_2_a == Integral::LOWER_TRIANGULAR) {
      return 0;
    }
    else if (type_2_a == Integral::UPPER_TRIANGULAR) {
      return row_a;
    }
    else if (type_2_a == Integral::SPARSE) {
      return 0;
    }
  }

  // type: UNKNOWN
  //
  this->debug(L"this");  
  return Error::handle(name(), L"startColumn", Error::ARG,
		       __FILE__, __LINE__);
}

// method: stopColumn
//
// arguments:
//  int32 row: (input) row index
//  Integral::MTYPE type_1: (input) matrix type
//  Integral::MTYPE type_2: (input) matrix type
//
// return: a int32 value containing the column index of the first
//  available element in a row
//  
// this method is typically used when copying data from one matrix to
// the other. it determines the last non-zero value is a given
// column that needs to be copied into the destination matrix.
// the rules implemented below can be summarized with the following table:
//
// see startColumn for a general explanation of what this method does.
// the rules implemented below can be summarized with the following table:
//
//  TYPE1               TYPE2
//         full  diag  symm  ltri  utri  sprs
//  full   ncols row   ncols row   ncols ncols
//  diag   row   row   row   row   row   row
//  symm   ncols row   row   row   nols  ncols
//  ltri   row   row   row   row   row   row
//  utri   ncols row   ncols row   ncols ncols
//  sprs   ncols row   ncols row   ncols ncols 
//
// this matrix should always be symmetric.
//
template<class TScalar, class TIntegral>
int32 MMatrix<TScalar, TIntegral>::stopColumn(int32 row_a,
					     Integral::MTYPE type_1_a,
					     Integral::MTYPE type_2_a) const {

  // check the arguments
  //
  if (type_2_a == Integral::UNCHANGED) {
    type_2_a = type_1_a;
  }

  // type1: FULL
  //
  if (type_1_a == Integral::FULL) {
    if (type_2_a == Integral::FULL) {
      return (int32)ncols_d - 1;
    }
    else if (type_2_a == Integral::DIAGONAL) {
      return row_a;
    }
    else if (type_2_a == Integral::SYMMETRIC) {
      return (int32)ncols_d - 1;
    }
    else if (type_2_a == Integral::LOWER_TRIANGULAR) {
      return row_a;
    }
    else if (type_2_a == Integral::UPPER_TRIANGULAR) {
      return (int32)ncols_d - 1;
    }
    else if (type_2_a == Integral::SPARSE) {
      return (int32)ncols_d - 1;
    }
  }

  // type_1: DIAGONAL
  //
  else if (type_1_a == Integral::DIAGONAL) {
    if (type_2_a == Integral::FULL) {
      return row_a;
    }
    else if (type_2_a == Integral::DIAGONAL) {
      return row_a;
    }
    else if (type_2_a == Integral::SYMMETRIC) {
      return row_a;
    }
    else if (type_2_a == Integral::LOWER_TRIANGULAR) {
      return row_a;
    }
    else if (type_2_a == Integral::UPPER_TRIANGULAR) {
      return row_a;
    }
    else if (type_2_a == Integral::SPARSE) {
      return row_a;
    }
  }

  // type_1: SYMMETRIC
  //
  else if (type_1_a == Integral::SYMMETRIC) {
    if (type_2_a == Integral::FULL) {
      return (int32)ncols_d - 1;
    }
    else if (type_2_a == Integral::DIAGONAL) {
      return row_a;
    }
    else if (type_2_a == Integral::SYMMETRIC) {
      return row_a;
    }
    else if (type_2_a == Integral::LOWER_TRIANGULAR) {
      return row_a;
    }
    else if (type_2_a == Integral::UPPER_TRIANGULAR) {
      return (int32)ncols_d - 1;
    }
    else if (type_2_a == Integral::SPARSE) {
      return (int32)ncols_d - 1;
    }
  }

  // type_1: LOWER_TRIANGULAR
  //
  else if (type_1_a == Integral::LOWER_TRIANGULAR) {
    if (type_2_a == Integral::FULL) {
      return row_a;
    }
    else if (type_2_a == Integral::DIAGONAL) {
      return row_a;
    }
    else if (type_2_a == Integral::SYMMETRIC) {
      return row_a;
    }
    else if (type_2_a == Integral::LOWER_TRIANGULAR) {
      return row_a;
    }
    else if (type_2_a == Integral::UPPER_TRIANGULAR) {
      return row_a;
    }
    else if (type_2_a == Integral::SPARSE) {
      return row_a;
    }
  }

  // type_1: UPPER_TRIANGULAR
  //
  else if (type_1_a == Integral::UPPER_TRIANGULAR) {
    if (type_2_a == Integral::FULL) {
      return (int32)ncols_d - 1;
    }
    else if (type_2_a == Integral::DIAGONAL) {
      return row_a;
    }
    else if (type_2_a == Integral::SYMMETRIC) {
      return (int32)ncols_d - 1;
    }
    else if (type_2_a == Integral::LOWER_TRIANGULAR) {
      return row_a;
    }
    else if (type_2_a == Integral::UPPER_TRIANGULAR) {
      return (int32)ncols_d - 1;
    }
    else if (type_2_a == Integral::SPARSE) {
      return (int32)ncols_d - 1;
    }
  }

  // type_1: SPARSE
  //
  else if (type_1_a == Integral::SPARSE) {
    if (type_2_a == Integral::FULL) {
      return (int32)ncols_d - 1;
    }
    else if (type_2_a == Integral::DIAGONAL) {
      return row_a;
    }
    else if (type_2_a == Integral::SYMMETRIC) {
      return (int32)ncols_d - 1;
    }
    else if (type_2_a == Integral::LOWER_TRIANGULAR) {
      return row_a;
    }
    else if (type_2_a == Integral::UPPER_TRIANGULAR) {
      return (int32)ncols_d - 1;
    }
    else if (type_2_a == Integral::SPARSE) {
      return (int32)ncols_d - 1;
    }
  }

  // type: UNKNOWN
  //
  this->debug(L"this");  
  return Error::handle(name(), L"stopColumn", Error::ARG,
		       __FILE__, __LINE__);
}

// method: vecLength
//
// arguments:
//  int32 nrows: (input) number of rows
//  int32 ncols: (input) number of columns
//  Integral::MTYPE type: (input) type of the matrix
//
// return: a int32 value containing the length of the vector for a
//  matrix of a particular type
//
template<class TScalar, class TIntegral>
int32 MMatrix<TScalar, TIntegral>::vecLength(int32 nrows_a, int32 ncols_a,
					    Integral::MTYPE type_a) const {

  // type: UNCHANGED
  //
  if (type_a == Integral::UNCHANGED) {
    return vecLength(nrows_a, ncols_a, type_d);  
  }
  
  // type: FULL
  //  we store all elements
  //
  else if (type_a == Integral::FULL) {
    return nrows_a * ncols_a;
  }

  // type: DIAGONAL
  //  we store only the diagonal elements
  //
  else if (type_a == Integral::DIAGONAL) {
    if (nrows_a == ncols_a) {
      return nrows_a;
    }
  }

  // type: SYMMETRIC, LOWER_TRIANGULAR, UPPER_TRIANGULAR
  //  symmetric storage mode - matrices must be square
  //
  else if ((type_a == Integral::SYMMETRIC) ||
	   (type_a == Integral::LOWER_TRIANGULAR) ||
	   (type_a == Integral::UPPER_TRIANGULAR)) {
    if (nrows_a == ncols_a) {
      return (nrows_a * (nrows_a + 1) / 2);
    }
  }

  // type: SPARSE
  //
  else if (type_a == Integral::SPARSE) {
    return nrows_a * ncols_a;
  }

  // exit gracefully:
  //  if we got this far, there was an error
  //
  this->debug(L"this");  
  Error::handle(name(), L"vecLength", Error::ARG, __FILE__, __LINE__);
  return -1;
}

// method: vecCreateLength
//
// arguments:
//  int32 nrows: (input) number of rows
//  int32 ncols: (input) number of columns
//  Integral::MTYPE type: (input) desired type
//
// return: a bool8 value containing the status
//  
// this method is a very specific method used to facilitate setDimensions.
// it sets the length according to the type. it is typically used
// when the type is changed, and old data needs to be destroyed.
// old data is, by definition, destroyed.
//
template<class TScalar, class TIntegral>
bool8
MMatrix<TScalar, TIntegral>::vecCreateLength(int32 nrows_a, int32 ncols_a,
					     Integral::MTYPE type_a) {

  // note that note that we only need to check for
  // a crossconnect between SPARSE and all other types, because
  // SPARSE uses a unique storage format. setLength will take care
  // of the rest.
  //
  // condition: new matrix is not SPARSE
  // action: delete space used by the SPARSE representation
  //
  if (type_a != Integral::SPARSE) {

    // free space
    //
    row_index_d.clear(Integral::RELEASE);
    col_index_d.clear(Integral::RELEASE);

    // allocate space
    //
    m_d.setLength(vecLength(nrows_a, ncols_a, type_a), false);
  }

  // condition: new matrix is SPARSE
  // action: delete space used by the non-SPARSE representation
  //
  // note that since the matrix is sparse, and values are not preserved,
  // we simply clear the SPARSE vectors.
  //
  else {

    // free space
    //
    m_d.clear(Integral::RELEASE);

    // allocate space
    //
    m_d.setLength(0);
    row_index_d.setLength(0);
    col_index_d.setLength(0);
  }

  // set the dimensions
  //
  nrows_d = nrows_a;
  ncols_d = ncols_a;

  // install the new type
  //
  type_d = type_a;

  // exit gracefully
  //
  return true;
}

// method: vecResetCapacity
//
// arguments:
//  int32 nrows: (input) number of rows
//  int32 ncols: (input) number of columns
//  Integral::MTYPE type: (input) desired type
//
// return: a bool8 value containing the status
//  
// this method is a very specific method used to facilitate setCapacity.
// it deletes resizes old data, creating new capacity according to the type.
// old data is, by definition, destroyed.
//
template<class TScalar, class TIntegral>
bool8
MMatrix<TScalar, TIntegral>::vecResetCapacity(int32 nrows_a, int32 ncols_a,
					      Integral::MTYPE type_a) {

  // note that note that we only need to check for
  // a crossconnect between SPARSE and all other types, because
  // SPARSE uses a unique storage format. setLength will take care
  // of the rest.
  //
  // condition: new matrix is not SPARSE
  // action: delete space used by the SPARSE representation
  //
  if (type_a != Integral::SPARSE) {
    
    // free space
    //
    row_index_d.clear(Integral::RELEASE);
    col_index_d.clear(Integral::RELEASE);
    
    // allocate space
    //
    int32 new_size = vecLength(nrows_a, ncols_a, type_a);
    if (m_d.length() > new_size) {
      m_d.setLength(new_size, false);
    }
    m_d.setCapacity(new_size, false);
  }
  
  // condition: new matrix is SPARSE
  // action: delete space used by the non-SPARSE representation
  //
  // note that since the matrix is sparse, and values are not preserved,
  // we simply clear the SPARSE vectors.
  //
  else {
    
    // free space
    //
    m_d.clear(Integral::RELEASE);
    
    // allocate space
    //
    int32 num_elements = nrows_a * ncols_a;

    if (m_d.length() > num_elements) {
      m_d.setLength(num_elements, false);
    }
    m_d.setCapacity(num_elements, false);
    if (row_index_d.length() > num_elements) {
      row_index_d.setLength(num_elements, false);
    }
    row_index_d.setCapacity(num_elements, false);
    if (col_index_d.length() > num_elements) {
      col_index_d.setLength(num_elements, false);
    }
    col_index_d.setCapacity(num_elements, false);
  }
  
  // install the new type: but we still have to set the dimensions
  //
  type_d = type_a;

  // exit gracefully
  //
  return true;
}

// method: vecResizeCapacity
//
// arguments:
//  int32 nrows: (input) number of rows
//  int32 ncols: (input) number of columns
//
// return: a bool8 value containing the status
//  
// this method is a very specific method used to facilitate setCapacity.
// it is only called when the type of the matrix need not be changed.
// it invokes setCapacity for the internal data.
// old data is, by definition, retained.
//
template<class TScalar, class TIntegral>
bool8 MMatrix<TScalar, TIntegral>::
vecResizeCapacity(int32 nrows_a, int32 ncols_a) {

  // note that note that we only need to check for
  // a crossconnect between SPARSE and all other types, because
  // SPARSE uses a unique storage format.
  //
  // condition: new matrix is not SPARSE
  //
  if (type_d != Integral::SPARSE) {
    int32 new_size = vecLength(nrows_a, ncols_a, type_d);
    if (m_d.length() > new_size) {
      m_d.setLength(new_size, true);
    }
    m_d.setCapacity(new_size, true);
  }

  // condition: new matrix is SPARSE
  //
  else {

    // allocate space
    //
    int32 num_elements = nrows_a * ncols_a;
    if (m_d.length() > num_elements) {
      m_d.setLength(num_elements, true);
    }
    m_d.setCapacity(num_elements, true);
    if (row_index_d.length() > num_elements) {
      row_index_d.setLength(num_elements, true);
    }
    row_index_d.setCapacity(num_elements, true);
    if (col_index_d.length() > num_elements) {
      col_index_d.setLength(num_elements, true);
    }
    col_index_d.setCapacity(num_elements, true);
  }

  // exit gracefully
  //
  return true;
}

// method: vecDimensionLength
//
// arguments:
//  int32 nrows: (input) number of rows
//  int32 ncols: (input) number of columns
//  bool8 preserve_values: (input) flag to save existing values
//
// return: a bool8 value containing the status
//  
// this method is a very specific method used to facilitate setDimensions.
// it is only called when the type of the matrix need not be changed.
// it invokes a change of length for the internal data.
// old data is, by definition, retained.
//
template<class TScalar, class TIntegral>
bool8 MMatrix<TScalar, TIntegral>::
vecDimensionLength(int32 nrows_a, int32 ncols_a,bool8 preserve_values_a) {

  // condition: SPARSE
  //  this is really easy since sparse only saves non-zero values element
  //  by element. there is one catch: we might need to delete elements if
  //  the new dimensions are smaller.
  //
  if (type_d == Integral::SPARSE) {

    // check for a request to set the lengths to zero: it is best to do
    // this efficiently
    //
    if ((nrows_a == 0) && (ncols_a == 0)) {
      row_index_d.clear(Integral::RESET);
      col_index_d.clear(Integral::RESET);
      m_d.clear(Integral::RESET);
    }

    // else: delete element by element
    //
    else {

      // loop over all elements
      //
      int32 num_elements = row_index_d.length();
      int32 i = 0;

      while (i < num_elements) {
	if ((row_index_d(i) >= nrows_a) || (col_index_d(i) >= ncols_a)) {
	  row_index_d.deleteRange(i, 1);
	  col_index_d.deleteRange(i, 1);
	  m_d.deleteRange(i, 1);
	  num_elements--;
	}
	else {
	  i++;
	}
      }
    }

    // set the dimensions
    //
    nrows_d = nrows_a;
    ncols_d = ncols_a;
    return true;
  }

  // condition: preserve_values = false
  //  this is also easy. we simply need to set the vector length.
  //  the vector length method is smart enough to figure out what it
  //  has to do with the capacity.
  //
  else if (!preserve_values_a) {

    // set the dimensions
    //
    nrows_d = nrows_a;
    ncols_d = ncols_a;

    // set the length
    //
    return m_d.setLength(vecLength(nrows_a, ncols_a, type_d), false);
  }

  // condition: preserve_values = true
  //  at this point in the code, we can only have a non-sparse matrix.
  //  that makes things a little easier. but we still have to do some
  //  type-specific grungy stuff.
  //
  else {

    // copy the data
    //
    TVector m_old(m_d);

    // increase/decrease the length of the data vector. be sure to
    // clear it, since the contents are unpredictable.
    //
    m_d.setLength(vecLength(nrows_a, ncols_a, type_d), false);    
    m_d.clear(Integral::RETAIN);

    // copy only the intersection of the old and new matrices
    //
    int32 nrows_new = (int32)Integral::min(nrows_a, nrows_d);
    int32 ncols_new = (int32)Integral::min(ncols_a, ncols_d);

    // type: FULL
    //  loop over all elements (not the most efficient way, but simple)
    //
    if (type_d == Integral::FULL) {
      for (int32 row = 0; row < nrows_new; row++) {
	for (int32 col = 0; col < ncols_new; col++) {
	  m_d(index(row, col, nrows_a, ncols_a)) =
	    m_old(index(row, col, nrows_d, ncols_d));
	}
      }
    }

    // type: DIAGONAL
    //  copy the vector directly
    //
    else if (type_d == Integral::DIAGONAL) {
      m_d.move(m_old, nrows_new, 0, 0);
    }

    // type: SYMMETRIC or LOWER_TRIANGULAR
    //  loop over all elements
    //
    else if ((type_d == Integral::SYMMETRIC) ||
	     (type_d == Integral::LOWER_TRIANGULAR)) {
      for (int32 row = 0; row < nrows_new; row++) {
	for (int32 col = 0; col <= row; col++) {
	  m_d(index(row, col, nrows_a, ncols_a)) =
	    m_old(index(row, col, nrows_d, ncols_d));
	}
      }
    }

    // type: UPPER_TRIANGULAR
    //  loop over all elements
    //
    else if ((type_d == Integral::SYMMETRIC) ||
	     (type_d == Integral::UPPER_TRIANGULAR)) {
      for (int32 row = 0; row < nrows_new; row++) {
	for (int32 col = row; col < ncols_new; col++) {
	  m_d(index(row, col, nrows_a, ncols_a)) =
	    m_old(index(row, col, nrows_d, ncols_d));
	}
      }
    }

    // update the dimensions
    //
    nrows_d = nrows_a;
    ncols_d = ncols_a;

    // exit gracefully
    //
    return true;
  }
}

// method: sortSparse
//
// arguments: none
//
// return: a bool8 value containing the status
//  
// this method is a very specific method used to facilitate sparse matrix
// manipulations. it takes an existing sparse matrix and sorts the row
// and column indices to make sure they are in the proper order.
//
// this code uses a radix sort. the first pass sorts the columns, the second
// sorts the rows using a stable approach. the algorithm is described in:
//
//  Thomas H. Cormen, Charles E. Leiserson, Ronald L. Rivest,
//  Introduction to Algorithms, The MIT Press, Cambridge, Massachusetts, USA,
//  McGraw-Hill Book Company, New York, USA, pp. 175-179, 1997.
//
template<class TScalar, class TIntegral>
bool8 MMatrix<TScalar, TIntegral>::sortSparse() {

  // check the type
  //
  if (type_d != Integral::SPARSE) {
    this->debug(L"this");    
    Error::handle(name(), L"sortSparse", Error::ARG, __FILE__, __LINE__);
  }
  
  // declare a buffer: a counting sort needs scratch space for counts
  //
  MVector<Long, int32> counts((int32)Integral::max(nrows_d, ncols_d));

  // this algorithm does not sort in place, so we need temporary
  // buffers for the three vectors that comprise a sparse matrix.
  //
  int32 nelem = m_d.length();
  TVector tmp_m(nelem);
  MVector<Long, int32> tmp_ri(nelem);
  MVector<Long, int32> tmp_ci(nelem);

  // first sort the columns with a counting sort:
  //   A: col_index_d
  //   B: tmp_ci (note that the other two vectors are reordered simultaneously)
  //   C: counts  
  // after this loop counts(i) will contain the number of elements equal to i
  //
  for (int32 i = 0; i < nelem; i++) {
    counts(col_index_d(i)) += 1;
  }
  
  // after this loop counts(i) will contain the number of elements
  // less than or equal to index
  //
  for (int32 i = 1; i < ncols_d; i++) {
    counts(i) += counts(i - 1);
  }

  // copy the data vectors into the locations specified by counts()
  //
  for (int32 j = nelem - 1; j >= 0; j--) {
    int32 k = (int32)counts(col_index_d(j)) - 1;
    tmp_ri(k) = row_index_d(j);
    tmp_ci(k) = col_index_d(j);
    tmp_m(k) = m_d(j);
    counts(col_index_d(j)) -= 1;
  }

  // we now have the three temporary vectors sorted by columns, so
  // perform the second pass of counting sort to sort by rows.
  //   A: tmp_ri
  //   B: row_index_d
  //   C: counts
  //
  counts.clear(Integral::RETAIN);
  
  // after this loop, counts(i) will contain the number of elements equal to i
  //
  for (int32 i = 0; i < nelem; i++) {
    counts(tmp_ri(i)) += 1;
  }

  // after this loop, counts(i) will contain the number of elements
  // less than or equal to i
  //
  for (int32 i = 1; i < nrows_d; i++) {
    counts(i) += counts(i - 1);
  }

  // now copy the data vectors into the locations specified by counts()
  //
  for (int32 j = nelem - 1; j >= 0; j--) {
    int32 k = (int32)counts(tmp_ri(j)) - 1;
    row_index_d(k) = tmp_ri(j);
    col_index_d(k) = tmp_ci(j);
    m_d(k) = tmp_m(j);
    counts(tmp_ri(j)) -= 1;
  }

  // exit gracefully
  //
  return true;
}

// method: isSingular
//
// arguments:
//  const MMatrix& matrix: (input) the matrix to compute singularity on
//  float64 thresh: (input) if the determinant is less than this value then the
//                         matrix is considered singular
//
// return: a bool8 value containing the status
//
// this method checks if the matrix is a singular matrix or not. this
// method doesn't work for unsigned matrices as the determinant for
// unsigned matrices is not defined
//
template<class TScalar, class TIntegral>
bool8 MMatrix<TScalar, TIntegral>::isSingular(const MMatrix& matrix_a, float64 thresh_a) const {

#ifdef ISIP_TEMPLATE_unsigned
  this->debug(L"this");  
  return Error::handle(name(), L"isSingular", Error::TEMPLATE_TYPE, __FILE__, __LINE__);
#else

  // for diagonal or triangular matrices, the matrix is non-singular
  // so int32 as there are no zero-entries on the diagonal and we are not
  // thresholding
  //
  if ((thresh_a == 0) && ((matrix_a.type_d == Integral::DIAGONAL) ||
			  (matrix_a.type_d == Integral::LOWER_TRIANGULAR) ||
			  (matrix_a.type_d == Integral::LOWER_TRIANGULAR))) { 
    int32 nrows = matrix_a.nrows_d;
    for (int32 row = 0; row < nrows; row++) {
      if (matrix_a.m_d(matrix_a.index(row, row)) == (TIntegral)0.0) {
	return true;
      }
    }
    return false;
  }
  else {
    return (((thresh_a == 0) && (matrix_a.determinant() == 0)) ||
	    ((thresh_a != 0) && (Integral::abs(matrix_a.determinant()) < thresh_a)));
  }
#endif
}

// explicit instantiations
//
template class MMatrix<ISIP_TEMPLATE_TARGET>;

