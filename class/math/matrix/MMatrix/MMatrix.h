// file: $isip/class/math/matrix/MMatrix/MMatrix.h
// version: $Id: MMatrix.h 10636 2007-01-26 22:18:09Z tm334 $
//

// make sure definitions are only made once
//
#ifndef ISIP_MMATRIX
#define ISIP_MMATRIX

// isip include files
//
#ifndef ISIP_MMATRIX_METHODS
#include "MMatrixMethods.h"
#endif

#ifndef ISIP_VECTOR_LONG
#include <VectorLong.h>
#endif

#ifndef ISIP_NAME_MAP
#include <NameMap.h>
#endif

// MMatrix: this is a matrix template class which is inherited by
// other matrix classes. TScalar is a Scalar class, TIntegral is an
// Integral type.
//
// this class supports 6 types of matrices:
//   FULL: a rectangular matrix.
//   DIAGONAL: a diagonal matrix 
//   SYMMETRIC: a symmetric matrix.
//   LOWER_TRIANGULAR: a lower triangular matrix. 
//   UPPER_TRIANGULAR: an upper triangular matrix. 
//   SPARSE: a sparse matrix (has very few non-zero elements).
//
// these are defined by the constant Integral::MTYPE. this important
// constant is located in Integral.h so that the notion of a matrix
// storage type is available to both MMatrix.h and MMatrixMethods.h,
// as well as the specific instantiations of this template.
//
template <class TScalar, class TIntegral>
class MMatrix {

  //---------------------------------------------------------------------------
  //
  // public constants
  //
  //---------------------------------------------------------------------------
public:

  // define the class name
  //
  static const String CLASS_NAME;

  //----------------------------------------
  //
  // i/o related constants
  //
  //----------------------------------------  
  
  static const String DEF_PARAM;
  static const String PARAM_DATA;
  static const String PARAM_TYPE;
  static const String PARAM_NROWS;
  static const String PARAM_NCOLS;
  static const String PARAM_ROW_IND;
  static const String PARAM_COL_IND;

  //----------------------------------------
  //
  // matrix type-related constants
  //
  //----------------------------------------  
  
  static const NameMap TYPE_MAP;
  
  //----------------------------------------
  //
  // other numeric constants
  //
  //----------------------------------------  

  // define a conditioning factor to be used to determine singularity
  //
  static const float64 THRESH_SINGULAR = 1e-10;

  // define a conditioning factor to be used to determine threshhold
  //  for rank method
  //
  static const float64 THRESH_SINGULAR_DOUBLE = 2.22e-16; // for float64 type
  static const float64 THRESH_SINGULAR_FLOAT = 1.49e-08; // for float type
  
  // define a threshold used to determine sparseness
  //
  static const float64 THRESH_SPARSE = 0.9;

  // define a threshold used to determine balance
  //
  static const float64 THRESH_BALANCE = 0.95;

  // define a threshold used to stabilize matrices
  //
  static const float64 THRESH_STABLE = 1e-20;

  //----------------------------------------
  //
  // default values and arguments
  //
  //----------------------------------------  

  // default arguments to methods
  //
  static const unichar DEF_ROW_DELIM = L',';
  static const unichar DEF_DELIM = DEF_ROW_DELIM;
  
  // default value(s) of the class data
  //
  static const TIntegral DEF_VALUE;
  static const int32 DEF_SIZE = 0;

  //----------------------------------------
  //
  // error codes
  //
  //----------------------------------------
  
  static const int32 ERR = 24000;
  static const int32 ERR_OPTYPE = 24001;
  static const int32 ERR_DIM = 24002;
  static const int32 ERR_UNKTYP = 24003;
  static const int32 ERR_SINGLR = 24004;
  static const int32 ERR_POSDEF = 24005;    
  
  //---------------------------------------------------------------------------
  //
  // protected data
  //
  //---------------------------------------------------------------------------
protected:

  typedef MVector<TScalar, TIntegral> TVector;

  // define the type
  //
  Integral::MTYPE type_d;

  // number of rows and columns in the matrix
  //
  Long nrows_d;
  Long ncols_d;
  
  // the values of this matrix are stored in a vector for two reasons.
  // first, we want to make use of all the math operations supported
  // in the vector classes. second, we want to make access and manipulation
  // of the matrix fast.
  //
  TVector m_d;

  // for the sparse matrix implementation, in addition to the values,
  // we need two vectors to hold row and column indices.
  //
  MVector<Long, int32> row_index_d;
  MVector<Long, int32> col_index_d;
  
  // declare a static debug level
  //
  static Integral::DEBUG debug_level_d;

  //---------------------------------------------------------------------------
  //
  // required public methods
  //
  //---------------------------------------------------------------------------
public:

  // method: name
  //
  static const String& name() {
    return CLASS_NAME;
  }

  // method: diagnose
  //  
  static bool8 diagnose(Integral::DEBUG debug_level) {
    return MMatrixMethods::diagnose<MMatrix<TScalar,TIntegral>,
      TScalar, TIntegral>(debug_level);
  }

  // method: setDebug
  //
  bool8 setDebug(Integral::DEBUG level) {
    debug_level_d = level;
    return true;
  }
    
  // method: debug
  //
  bool8 debug(const unichar* message) const {
    return debug(name(), message);
  }
  
  // method: destructor
  //  note that since there are no pointers in the protected data,
  //  we don't need to clean up anything.
  //
  ~MMatrix() {}

  // method: default constructor
  //
  MMatrix();

  // method: copy constructor
  //
  MMatrix(const MMatrix& arg);

  // method: assign
  //  this method is templatized so it can also do conversions without
  //  generating class-specific code.
  //
  template <class TAScalar, class TAIntegral>
  bool8 assign(const MMatrix<TAScalar, TAIntegral>& arg) {
    return MMatrixMethods::assign(*this, arg);
  }

  // operator= methods:
  //  these methods are omitted because they are defined in the
  //  classes that instantiate this template
  //
  
  // i/o methods
  //
  int32 sofSize() const {
    return MMatrixMethods::sofSize<TScalar,TIntegral>(*this);
  }
  
  bool8 read(Sof& sof, int32 tag, const String& name) {
    return MMatrixMethods::read<TScalar,TIntegral>(*this, sof, tag, name);
  }
  
  bool8 write(Sof& sof, int32 tag, const String& name) const {
    return MMatrixMethods::write<TScalar,TIntegral>(*this, sof, tag, name);
  }
  
  bool8 readData(Sof& sof, const String& pname,
		   int32 size, bool8 param, bool8 nested) {
    return MMatrixMethods::readData<TScalar,TIntegral>(*this, sof, pname,
						       size, param, nested);
  }
  
  bool8 writeData(Sof& sof, const String& name) const {
    return MMatrixMethods::writeData<TScalar,TIntegral>(*this, sof, name);
  }
  
  // equality methods
  //
  bool8 eq(const MMatrix& arg) const;

  // memory management methods:
  //  the new and delete methods are omitted because they are defined in the
  //  classes that instantiate this template
  //
  bool8 clear(Integral::CMODE cmode = Integral::DEF_CMODE);

  //---------------------------------------------------------------------------
  //
  // class-specific public methods:
  //  extensions to required methods
  //
  //---------------------------------------------------------------------------

  // debug methods:
  //  this second debug method is used so that the template
  //  instantiations can use a common debug method.
  //
  bool8 debug(const String& name, const unichar* message) const;

  // constructor(s)
  //
  MMatrix(int32 nrows, int32 ncols = DEF_SIZE,
	  Integral::MTYPE type = Integral::DEF_MTYPE);

  // method: eq
  //
  bool8 eq(TIntegral value) const {
    return MMatrixMethods::eq<TScalar,TIntegral>(*this, value);
  }
  
  // method: assign
  //  this method is an overload of the required assign method that
  //  allows the user to set the type. note that we do not use a default
  //  value for the type argument so we avoid a conflict with the standard
  //  assign method. also 
  //
  template <class TAScalar, class TAIntegral>
  bool8 assign(const MMatrix<TAScalar, TAIntegral>& arg,
		 Integral::MTYPE type) {
    return ((((void*)&arg == (void*)this) && changeType(type)) ||
	    (setDimensions(0, 0, false, type) && copy(arg)));
  }

  // other scalar assign methods
  //
  bool8 assign(TIntegral value);

  // method: assign
  //  array conversion methods
  //
  template<class TAIntegral>
  bool8 assign(int32 num_rows, int32 num_cols, const TAIntegral* arg, 
		 Integral::MTYPE type = Integral::DEF_MTYPE) {
    return MMatrixMethods::assign<TScalar,TIntegral>(*this, num_rows,
						     num_cols, arg, type);
  }    

  // method: assign
  //
  bool8 assign(int32 num_rows, int32 num_cols, const String* arg, 
		 Integral::MTYPE type = Integral::DEF_MTYPE) {
    return MMatrixMethods::assign<TScalar,TIntegral>(*this, num_rows,
						     num_cols, arg, type);
  }
  
  // method: assign
  //  create a matrix from a string with given delimiter
  //
  bool8 assign(int32 nrows, int32 ncols, const String& arg,
		 Integral::MTYPE type = Integral::DEF_MTYPE,  
		 const Char delim = DEF_DELIM) {
    return MMatrixMethods::assign<TScalar,TIntegral>(*this, nrows, ncols,
						     arg, type, delim);
  }

  // method: assign
  //  create a matrix from an array of unichars with given delimiter
  //  
  bool8 assign(int32 nrows, int32 ncols, const unichar* arg,
		 Integral::MTYPE type = Integral::DEF_MTYPE,
		 const Char delim = DEF_DELIM) {
    String temp((unichar*)arg);
    return MMatrixMethods::assign<TScalar,TIntegral>(*this, nrows, ncols,
						     temp, type, delim);
  }  

  // method: copy
  //  copy the values from arg to "this" without changing the type of "this"
  //
  template <class TAScalar, class TAIntegral>
  bool8 copy(const MMatrix<TAScalar, TAIntegral>& arg) {
    return MMatrixMethods::copy(*this, arg);
  }

  // method: swap
  //
  bool8 swap(MMatrix& arg) {
    return MMatrixMethods::swap<TScalar,TIntegral>(*this, arg);
  }

  //---------------------------------------------------------------------------
  //
  // class-specific public methods:
  //  operator overloads, get, set, find, resize methods
  //
  //---------------------------------------------------------------------------

  // method: operator()
  //
  TIntegral operator()(int32 i, int32 j) const {
    return getValue(i, j);
  }

  // method: getType
  //
  Integral::MTYPE getType() const {
    return type_d;
  }  

  // method: getValue
  //
  TIntegral getValue(int32 row_index, int32 col_index) const {
    return MMatrixMethods::getValue<TScalar,TIntegral>(*this, row_index,
						       col_index);
  }

  // method: getValue
  //
  bool8 getValue(TScalar& value, int32 row_index, int32 col_index) const {
    return MMatrixMethods::getValue<TScalar,TIntegral>(*this, value,
						       row_index, col_index);
  }

  // method: getNumRows
  //
  int32 getNumRows() const {
    return nrows_d;
  }
  
  // method: getNumColumns
  //
  int32 getNumColumns() const {
    return ncols_d;
  }

  // method: getRow
  //
  bool8 getRow(TVector& vector, int32 row_index) const {
    return MMatrixMethods::getRow<TScalar,TIntegral>(*this, vector,
						     row_index);
  }

  // method: getColumn
  //
  bool8 getColumn(TVector& vector, int32 col_index) const {
    return MMatrixMethods::getColumn<TScalar,TIntegral>(*this, vector,
							col_index);
  }
  
  // method: getDiagonal
  //
  bool8 getDiagonal(TVector& vector) const {
    return MMatrixMethods::getDiagonal<TScalar,TIntegral>(*this, vector);
  }
  
  // method: getLower
  //
  bool8 getLower(MMatrix& arg) const {
    return MMatrixMethods::getLower<TScalar,TIntegral>(*this, arg);
  }
  
  // method: getUpper
  //
  bool8 getUpper(MMatrix& arg) const {
    return MMatrixMethods::getUpper<TScalar,TIntegral>(*this, arg);
  }
  
  // method: getMinor
  //
  bool8 getMinor(MMatrix& arg, int32 row_index, int32 col_index) const {
    return MMatrixMethods::getMinor<TScalar, TIntegral>(*this, arg, row_index,
							col_index);
  }

  // method: setValue
  //
  bool8 setValue(int32 row_index, int32 col_index,
		   const TScalar& value) {
    return MMatrixMethods::setValue<TScalar,TIntegral>(*this, row_index,
						       col_index,
						       (TIntegral)value);
  }

  // method: setRow
  //
  bool8 setRow(int32 row_index, const TVector& vector) {
    return MMatrixMethods::setRow<TScalar,TIntegral>(*this,
						     row_index, vector);
  }    

  // method: setColumn
  //
  bool8 setColumn(int32 col_index, const TVector& vector) {
    return MMatrixMethods::setColumn<TScalar,TIntegral>(*this,
							col_index, vector);
  }    
  
  // method: setDiagonal
  //
  bool8 setDiagonal(const TVector& values) {
    return MMatrixMethods::setDiagonal<TScalar,TIntegral>(*this, values);
  }    

  // method: setDiagonal
  //
  bool8 setDiagonal(const MMatrix& source) {
    TVector tmp;
    source.getDiagonal(tmp);
    return MMatrixMethods::setDiagonal<TScalar,TIntegral>(*this, tmp);
  }
  
  // method: setDiagonal
  //
  bool8 setDiagonal(TIntegral value) {
    TVector tmp(nrows_d);
    tmp.assign(value);
    return MMatrixMethods::setDiagonal<TScalar,TIntegral>(*this, tmp);
  }

  // method: setLower
  //
  bool8 setLower(const MMatrix& source) {
    return MMatrixMethods::setLower<TScalar,TIntegral>(*this, source);
  }    
 
  // method: setUpper
  //
  bool8 setUpper(const MMatrix& source) {
    return MMatrixMethods::setUpper<TScalar,TIntegral>(*this, source);
  }

  // method: setBlock
  //
  bool8 setBlock(int32 start_row, int32 start_col,
		   int32 num_rows, int32 num_cols, TIntegral value) {
    return MMatrixMethods::setBlock<TScalar, TIntegral>(*this,
							start_row, start_col,
							num_rows, num_cols,
							value);
  }

  // method: makeDiagonal
  //
  bool8 makeDiagonal(const TVector& values,
		       Integral::MTYPE type = Integral::DIAGONAL) {
    return MMatrixMethods::makeDiagonal<TScalar,TIntegral>(*this,
							   values, type);
  }    
  
  // method: makeDiagonal
  //
  bool8 makeDiagonal(TIntegral value, int32 dim,
		       Integral::MTYPE type = Integral::DIAGONAL) {
    TVector tmp(dim);
    tmp.assign(value);
    return MMatrixMethods::makeDiagonal<TScalar,TIntegral>(*this, tmp, type);
  }
  
  // method: makeIdentity
  //
  bool8 makeIdentity(int32 dim, Integral::MTYPE type = Integral::DIAGONAL) {
    TVector tmp(dim);
    tmp.assign((TIntegral)1.0);
    return MMatrixMethods::makeDiagonal<TScalar,TIntegral>(*this, tmp, type);
  }

  // method: makeLower
  //
  bool8 makeLower(const MMatrix& source,
		    Integral::MTYPE type = Integral::LOWER_TRIANGULAR) {
    return MMatrixMethods::makeLower<TScalar,TIntegral>(*this, source, type);
  }
  
  // method: makeUpper
  //
  bool8 makeUpper(const MMatrix& source,
		    Integral::MTYPE type = Integral::UPPER_TRIANGULAR) {
    return MMatrixMethods::makeUpper<TScalar,TIntegral>(*this, source, type);
  }
  
  // method: nextZero
  //
  bool8 nextZero(int32& row_index, int32& col_index,
		   int32 row_start, int32 col_start) const {
    return MMatrixMethods::nextZero(*this, row_index, col_index,
				    row_start, col_start);
  }

  // method: nextNonZero
  //
  bool8 nextNonZero(TIntegral& value,
		      int32& row_index, int32& col_index,
		      int32 row_start, int32 col_start) const {
    return MMatrixMethods::nextNonZero(*this, value, row_index, col_index,
				       row_start, col_start);
  }

  // method: findRow
  //
  int32 findRow(const TVector& vector) const {
    return MMatrixMethods::findRow<TScalar,TIntegral>(*this, vector);
  }
  
  // resize methods
  //
  bool8 setCapacity(int32 nrows, int32 ncols = DEF_SIZE,
		      bool8 preserve_values = true,
		      Integral::MTYPE type = Integral::UNCHANGED);
  bool8 setCapacity(const MMatrix& prototype_matrix,
		      bool8 preserve_values = true,
		      Integral::MTYPE type = Integral::UNCHANGED);

  bool8 setDimensions(int32 nrows, int32 ncols = DEF_SIZE,
			bool8 preserve_values = true,
			Integral::MTYPE type = Integral::UNCHANGED);
  bool8 setDimensions(const MMatrix& prototype_matrix,
			bool8 preserve_values = true,
			Integral::MTYPE type = Integral::UNCHANGED);

  //---------------------------------------------------------------------------
  //
  // class-specific public methods:
  //  property checking methods
  //
  //---------------------------------------------------------------------------
  
  // method: checkDimensions
  //  check if the current matrix has the same dimension as the input matrix
  //
  template <class TAScalar, class TAIntegral>
  bool8 checkDimensions(const MMatrix<TAScalar, TAIntegral>& matrix) const {
    return (getNumRows() == matrix.getNumRows() &&
	    getNumColumns() == matrix.getNumColumns());    
  }

  // method: changeType
  //  change the type of the current matrix
  //
  bool8 changeType(Integral::MTYPE type);

  // method: isTypePossible
  //  check if it is possible to change the current matrix into a
  //  matrix of the requested type
  //
  bool8 isTypePossible(Integral::MTYPE type) const {
    return MMatrixMethods::isTypePossible<TScalar,TIntegral>(*this, type);
  }

  // method: isFull
  //
  bool8 isFull() const {
    return MMatrixMethods::isTypePossible<TScalar,TIntegral>
      (*this, Integral::FULL);
  }

  // method: isDiagonal
  //
  bool8 isDiagonal() const {
    return MMatrixMethods::isTypePossible<TScalar,TIntegral>
      (*this, Integral::DIAGONAL);
  }

  // method: isSymmetric
  //
  bool8 isSymmetric() const {
    return MMatrixMethods::isTypePossible<TScalar,TIntegral>
      (*this, Integral::SYMMETRIC);
  }
  
  // method: isLowerTriangular
  //
  bool8 isLowerTriangular() const {
    return MMatrixMethods::isTypePossible<TScalar,TIntegral>
      (*this, Integral::LOWER_TRIANGULAR);
  }

  // method: isUpperTriangular
  //
  bool8 isUpperTriangular() const {
    return MMatrixMethods::isTypePossible<TScalar,TIntegral>
      (*this, Integral::UPPER_TRIANGULAR);
  }

  // method: isSparse
  //
  bool8 isSparse() const {
    return (numEqual((TIntegral)0) > (nrows_d * ncols_d * THRESH_SPARSE));
  }

  // method: isSquare
  //  check if the current matrix is a square matrix
  //
  bool8 isSquare() const {
    return isSquare(*this);
  }

  // method: isSquare
  //
  bool8 isSquare(const MMatrix& matrix) const {
    return (matrix.getNumRows() == matrix.getNumColumns());
  }

  // method: isSingular
  //  check if the current matrix is singular
  //
  bool8 isSingular(float64 thresh = 0) const {
    return isSingular(*this, thresh);
  }

  // method: isSingular
  //
  bool8 isSingular(const MMatrix& matrix, float64 thresh = 0) const;
  
  // method: isOrthogonal()
  //
  bool8 isOrthogonal() const {
    return MMatrixMethods::isOrthogonal<TScalar,TIntegral>(*this);
  }
    
  // method: isIdentity
  //
  bool8 isIdentity() const {
    return MMatrixMethods::isIdentity<TScalar,TIntegral>(*this);
  }
  
  //---------------------------------------------------------------------------
  //
  // class-specific public methods:
  //  relational and logical methods
  //
  //---------------------------------------------------------------------------

  // method: ne
  //
  bool8 ne(TIntegral value) const {
    return (!eq(value));
  }

  // method: ne
  //  
  bool8 ne(const MMatrix& matrix) const {
    return (!eq(matrix));
  } 

  // method: lt
  //
  bool8 lt(TIntegral value) const {
    return MMatrixMethods::lt<TScalar,TIntegral>(*this, value);
  }
  
  // method: le
  //
  bool8 le(TIntegral value) const {
    return MMatrixMethods::le<TScalar,TIntegral>(*this, value);
  }

  // method: gt
  //
  bool8 gt(TIntegral value) const {
    return MMatrixMethods::gt<TScalar,TIntegral>(*this, value);
  }
  
  // method: ge
  //
  bool8 ge(TIntegral value) const {
    return MMatrixMethods::ge<TScalar,TIntegral>(*this, value);
  }
  
  // method: operator ==
  //
  bool8 operator == (TIntegral arg) const {
    return eq(arg);
  }

  // method: operator !=
  //
  bool8 operator != (TIntegral arg) const {
    return ne(arg);
  }

  // method: operator <
  //
  bool8 operator < (TIntegral arg) const {
    return lt(arg);
  }

  // method: operator <=
  //
  bool8 operator <= (TIntegral arg) const {
    return le(arg);
  }

  // method: operator >
  //
  bool8 operator > (TIntegral arg) const {
    return gt(arg);
  }

  // method: operator >=
  //
  bool8 operator >= (TIntegral arg) const {
    return ge(arg);
  }
  
  // method: numEqual
  //
  int32 numEqual(TIntegral value) const {
    return MMatrixMethods::numEqual<TScalar,TIntegral>(*this, value);
  }

  // method: numNotEqual
  //
  int32 numNotEqual(TIntegral value) const {
    int32 nrows = getNumRows();
    int32 ncols = getNumColumns();
    return (nrows * ncols - numEqual(value));        
  }
  
  // almostEqual methods
  //
  bool8 almostEqual(TIntegral value,
		      float64 percent = Integral::DEF_PERCENTAGE,
		      float64 bound = Integral::DEF_BOUND) const;
  bool8 almostEqual(const MMatrix& matrix,
		      float64 percent = Integral::DEF_PERCENTAGE,
		      float64 bound = Integral::DEF_BOUND) const;

  //---------------------------------------------------------------------------
  //
  // class-specific public methods:
  //  concatenation methods 
  //
  //--------------------------------------------------------------------------
  
  // method: concatByRow
  //
  bool8 concatByRow(const MMatrix& additional_rows) {
    return MMatrixMethods::concatByRow<TScalar,TIntegral>(*this,
							  additional_rows);
  }

  // method: concatByRow
  //  
  bool8 concatByRow(const MMatrix& matrix1, const MMatrix& matrix2) {
    Integral::MTYPE old_type = type_d;
    return (assign(matrix1) && concatByRow(matrix2) && changeType(old_type));
  }
  
  // method: concatByColumn
  //
  bool8 concatByColumn(const MMatrix& additional_cols) {
    return MMatrixMethods::concatByColumn<TScalar,TIntegral>(*this,
							     additional_cols);
  }

  // method: concatByColumn
  //  
  bool8 concatByColumn(const MMatrix& matrix1,
			 const MMatrix& matrix2) {
    Integral::MTYPE old_type = type_d;
    return (assign(matrix1) && concatByColumn(matrix2) &&
	    changeType(old_type));
  }

  //---------------------------------------------------------------------------
  //
  // class-specific public methods:
  //  ordering methods 
  //
  //--------------------------------------------------------------------------

  // method: reorderRows
  //
  bool8 reorderRows(const MVector<Long,int32>& indexes) {
    return MMatrixMethods::reorderRows<TScalar,TIntegral>(*this, indexes);
  }
  
  // method: reorderRows
  //
  bool8 reorderRows(const MMatrix& matrix,
		      const MVector<Long,int32>& indices) {
    Integral::MTYPE old_type =
      (type_d == Integral::SPARSE) ? Integral::SPARSE : Integral::FULL;
    return (assign(matrix) && reorderRows(indices) && changeType(old_type));
  }

  // method: reorderColumns
  //
  bool8 reorderColumns(const MVector<Long,int32>& indexes) {
    return MMatrixMethods::reorderColumns<TScalar,TIntegral>(*this, indexes);
  }
  
  // method: reorderColumns
  //
  bool8 reorderColumns(const MMatrix& matrix,
			 const MVector<Long,int32>& indices) {
    Integral::MTYPE old_type =
      (type_d == Integral::SPARSE) ? Integral::SPARSE : Integral::FULL;
    return (assign(matrix) && reorderColumns(indices) && changeType(old_type));
  }

  // method: swapRows
  //
  bool8 swapRows(const MMatrix& arg, int32 row1, int32 row2) {
    return MMatrixMethods::swapRows<TScalar, TIntegral>(*this, arg,
							row1, row2);
  }

  // method: swapRows
  //
  bool8 swapRows(int32 row1, int32 row2) {
    return MMatrixMethods::swapRows<TScalar, TIntegral>(*this, *this,
							row1, row2);
  }

  // method: swapColumns
  //
  bool8 swapColumns(const MMatrix& arg, int32 col1, int32 col2) {
    return MMatrixMethods::swapColumns<TScalar, TIntegral>(*this, arg,
							   col1, col2);
  }

  // method: swapColumns
  //
  bool8 swapColumns(int32 col1, int32 col2) {
    return MMatrixMethods::swapColumns<TScalar, TIntegral>(*this, *this,
							   col1, col2);
  }

  //---------------------------------------------------------------------------
  //
  // class-specific public methods:
  //  basic mathematical methods
  //
  //---------------------------------------------------------------------------

  // method: add
  //
  template<class TAScalar, class TAIntegral>  
  bool8 add(const MMatrix<TAScalar, TAIntegral>& m1) {
    return MMatrixMethods::add<TScalar,TIntegral>(*this, m1);
  }
  
  // method: add
  //
  template<class TAScalar, class TAIntegral>
  bool8 add(const MMatrix& m1, const MMatrix<TAScalar, TAIntegral>& m2) {
    return MMatrixMethods::add<TScalar,TIntegral>(*this, m1, m2);
  }
  
  // method: add
  //
  bool8 add(TIntegral value) {
    return MMatrixMethods::add<TScalar,TIntegral>(*this, value);
  }
  
  // method: add
  //
  bool8 add(const MMatrix& m1, TIntegral value) {
    Integral::MTYPE old_type = type_d;
    return (assign(m1) && add(value) && changeType(old_type));
  }

  // method: sub
  //
  template<class TAScalar, class TAIntegral>  
  bool8 sub(const MMatrix<TAScalar, TAIntegral>& m1) {
    return MMatrixMethods::sub<TScalar,TIntegral>(*this, m1);
  }
   
  // method: sub
  //
  template<class TAScalar, class TAIntegral>  
  bool8 sub(const MMatrix& m1, const MMatrix<TAScalar, TAIntegral>& m2) {
    return MMatrixMethods::sub<TScalar,TIntegral>(*this, m1, m2);
  }
  
  // method: sub
  //
  bool8 sub(TIntegral value) {
    return MMatrixMethods::sub<TScalar,TIntegral>(*this, value);
  }
  
  // method: sub
  //
  bool8 sub(const MMatrix& m1, TIntegral value) {
    Integral::MTYPE old_type = type_d;
    return (assign(m1) && sub(value) && changeType(old_type));
  }

  // method: mult
  //
  template<class TAScalar, class TAIntegral>    
  bool8 mult(const MMatrix<TAScalar, TAIntegral>& m1) {
    return MMatrixMethods::mult<TScalar,TIntegral>(*this, *this, m1);
  }
  
  // method: mult
  //
  template<class TAScalar, class TAIntegral>    
  bool8 mult(const MMatrix& m1, const MMatrix<TAScalar, TAIntegral>& m2) {
    return MMatrixMethods::mult<TScalar,TIntegral>(*this, m1, m2);
  }
  
  // method: mult
  //
  bool8 mult(TIntegral value) {
    return m_d.mult(value);
  }

  // method: div
  //
  bool8 div(TIntegral value) {
    return m_d.div(value);
  }
  
  // method: neg
  //
  bool8 neg() {
    return m_d.neg();
  }
  
  // method: neg
  //
  bool8 neg(const MMatrix& m1) {
    Integral::MTYPE old_type = type_d;
    return (assign(m1) && neg() && changeType(old_type));
  }

  //---------------------------------------------------------------------------
  //
  // class-specific public methods:
  //  other mathematical methods
  //
  //--------------------------------------------------------------------------
  
  // method: min
  //  find the minimum value
  //
  TIntegral min() const {
    static int32 row_pos;
    static int32 col_pos;
    return MMatrixMethods::min<TScalar,TIntegral>(*this, row_pos, col_pos);
  }
  
  // method: min
  //  find the element with the minimum value
  //
  TIntegral min(int32& row_index, int32& col_index) const {
    return MMatrixMethods::min<TScalar,TIntegral>(*this, row_index, col_index);
  } 

  // method: max
  //  find the maximum value
  //  
  TIntegral max() const {
    static int32 row_pos;
    static int32 col_pos;
    return MMatrixMethods::max<TScalar,TIntegral>(*this, row_pos, col_pos);
  }
  
  // method: max
  //  find the element with the maximum value
  //  
  TIntegral max(int32& row_index, int32& col_index) const {
    return MMatrixMethods::max<TScalar,TIntegral>(*this, row_index, col_index);
  }

  // method: minMag
  //  find the minimum magnitude
  //
  float64 minMag() const {
    static int32 row_pos;
    static int32 col_pos;
    return MMatrixMethods::minMag<TScalar,TIntegral>(*this, row_pos, col_pos);
  }
  
  // method: minMag
  //  find the element with the minimum magnitude
  //
  float64 minMag(int32& row_index, int32& col_index) const {
    return MMatrixMethods::minMag<TScalar,TIntegral>(*this, row_index,
						     col_index);
  }

  // method: maxMag
  //  find the maximum magnitude
  //  
  float64 maxMag() const {
    static int32 row_pos;
    static int32 col_pos;
    return MMatrixMethods::maxMag<TScalar,TIntegral>(*this, row_pos, col_pos);
  }
 
  // method: maxMag
  //  find the element with the maximum magnitude
  //
  float64 maxMag(int32& row_index, int32& col_index) const {
    return MMatrixMethods::maxMag<TScalar,TIntegral>(*this, row_index,
						     col_index);
  }

  // random number generation methods  
  //
  bool8 rand(Random& generator = Random::GLOBAL_UNIFORM) {
    return MMatrixMethods::rand<TScalar, TIntegral>(*this, generator);
  }
  
  bool8 rand(TIntegral min_val, TIntegral max_val,
	       Random& generator = Random::GLOBAL_UNIFORM) {
    return MMatrixMethods::rand<TScalar, TIntegral>(*this, min_val,
						   max_val, generator);
  }
  
  bool8 grand(TIntegral mean, TIntegral stdev,
		Random& generator = Random::GLOBAL_GAUSSIAN) {
    return MMatrixMethods::grand<TScalar, TIntegral>(*this, mean,
						    stdev, generator);
  }
  
  //---------------------------------------------------------------------------
  //
  // class-specific public methods:
  //  linear algebra related methods 
  //
  //--------------------------------------------------------------------------
  
  // method: determinant
  //
  TIntegral determinant() const {
    return MMatrixMethods::determinant<TScalar,TIntegral>(*this);
  }
  
  // method: inverse
  //
  bool8 inverse() {
    return MMatrixMethods::inverse<TScalar,TIntegral>(*this, *this);
  }
  
  // method: inverse
  //
  bool8 inverse(const MMatrix& matrix) {
    return MMatrixMethods::inverse<TScalar,TIntegral>(*this, matrix);
  }

  // method: transpose
  //
  bool8 transpose() {
    return MMatrixMethods::transpose<TScalar,TIntegral>(*this, *this);
  }
  
  // method: transpose
  //
  bool8 transpose(const MMatrix& matrix) {
    return MMatrixMethods::transpose<TScalar,TIntegral>(*this, matrix);
  }

  // method: rank
  //
  int32 rank() const {
    return MMatrixMethods::rank<TScalar,TIntegral>(*this);
  }

  // method: trace
  //
  TIntegral trace() const {
    return MMatrixMethods::trace<TScalar,TIntegral>(*this);
  }

  // method: decompositionLU
  //
  bool8 decompositionLU(MMatrix& lower_trig, MMatrix& upper_trig) const {
    MVector<Long, int32> vec;
    int32 sign;
    return MMatrixMethods::decompositionLU<TScalar, TIntegral>(*this,
							       lower_trig,
							       upper_trig,
							       vec, sign,
							       THRESH_STABLE);
  }

  // method: decompositionLU
  //
  bool8 decompositionLU(MMatrix& lower_trig, MMatrix& upper_trig,
			  MVector<Long, int32>& index, int32& sign,
			  float64 stabilize = THRESH_STABLE) const {
    return MMatrixMethods::decompositionLU(*this, lower_trig, upper_trig,
					   index, sign, stabilize);
  }

  // method: decompositionCholesky
  //
  bool8 decompositionCholesky(MMatrix& ltri) const {
    return MMatrixMethods::decompositionCholesky(*this, ltri);
  }

  // method: decompositionSVD
  //
  bool8 decompositionSVD(MMatrix& u, MMatrix& w, MMatrix& v, bool8 economy_mode = true) const {
    return MMatrixMethods::decompositionSVD(*this, u, w, v, economy_mode);
  }

    //method decompositionQR
  //
  bool8 decompositionQR(MMatrix& q, MMatrix& r) const {
    return MMatrixMethods::decompositionQR(*this, q, r);
  }

  // method: eigen
  //  find the eigenvalues and vectors for a matrix 
  //
  #ifdef ISIP_TEMPLATE_unsigned
    bool8 eigen(TVector& eigvals, MMatrix& eigvects) const {
      return false;
    }
  #else
    bool8 eigen(TVector& eigvals, MMatrix& eigvects) const {
      return MMatrixMethods::eigen(*this, eigvals, eigvects);
    }
  #endif

  // method: luSolve
  //
  bool8 luSolve(MVector<TScalar, TIntegral>& out_vec,
		  const MMatrix& l,
		  const MMatrix& u,
		  const MVector<TScalar, TIntegral>& in_vec) const {
    VectorLong index(l.getNumRows());
    index.ramp(0, 1);
    return MMatrixMethods::luSolve(out_vec, l, u, index, in_vec);
  }

  // method: luSolve
  //
  bool8 luSolve(MVector<TScalar, TIntegral>& out_vec,
		  const MMatrix& l,
		  const MMatrix& u,
		  const VectorLong& index,
		  const MVector<TScalar, TIntegral>& in_vec) const {
    return MMatrixMethods::luSolve(out_vec, l, u, index, in_vec);
  }

  // method: choleskySolve
  //
  bool8 choleskySolve(MVector<TScalar, TIntegral>& out_vec,
			const MMatrix& l,
			const MVector<TScalar, TIntegral>& in_vec) const {
    return MMatrixMethods::choleskySolve(out_vec, l, in_vec);
  }

  // method: svdSolve
  //
  bool8 svdSolve(MVector<TScalar, TIntegral>& out_vec,
		   const MMatrix& u,
		   const MMatrix& w,
		   const MMatrix& v,
		   const MVector<TScalar, TIntegral>& in_vec,
		   bool8 zero_singulars = false) const {
    return MMatrixMethods::svdSolve(out_vec, u, w, v, in_vec, zero_singulars);
  }

  // method: matrix-vector multiplication
  //
  bool8 multv(TVector& output_vector, const TVector& input_vector) const {
    return MMatrixMethods::multv<TScalar,TIntegral>(*this, output_vector,
						    input_vector);
  }

  // method: vector-matrix multiplication
  //  
  bool8 vmult(TVector& output_vector, const TVector& input_vector) const {
    return MMatrixMethods::vmult<TScalar,TIntegral>(*this, output_vector,
						    input_vector);
  } 

  // method: quadratic
  //  compute (input) * (*this) * (transpose(input))
  //
  bool8 quadratic(MMatrix& output, const MMatrix& input) const {
    return MMatrixMethods::quadratic<TScalar,TIntegral>(output, *this, input);
  }

  // method: quadratic
  //  compute (in_vec) * (*this) * (transpose(in_vec))
  //
  bool8 quadratic(TIntegral& output, const TVector& in_vec) const {
    return MMatrixMethods::quadratic<TScalar,TIntegral>(output, *this, in_vec);
  }

  // method: outerProduct
  //  compute (*this) * transpose(*this)
  //
  bool8 outerProduct() {
    return MMatrixMethods::outerProduct<TScalar,TIntegral>(*this, *this,
							   *this);
  }

  // method: outerProduct
  //  compute (in_mat) * transpose(in_mat)
  //
  template<class TAScalar, class TAIntegral>    
  bool8 outerProduct(const MMatrix<TAScalar, TAIntegral>& in_mat) {
    return MMatrixMethods::outerProduct<TScalar,TIntegral>(*this, in_mat,
							   in_mat);
  }

  // method: outerProduct
  //  compute (in_mat1) * transpose(in_mat2)
  //
  template<class TAScalar, class TAIntegral>    
  bool8 outerProduct(const MMatrix& in_mat1,
		       const MMatrix<TAScalar, TAIntegral>& in_mat2) {
    return MMatrixMethods::outerProduct<TScalar,TIntegral>(*this, in_mat1,
							   in_mat2);
  }

  // method: outerProduct
  //  compute (in_vec) * transpose(in_vec)
  //
  bool8 outerProduct(const TVector& in_vec) {
    return MMatrixMethods::outerProduct<TScalar,TIntegral>(*this, in_vec,
							   in_vec);
  }

  // method: outerProduct
  //  compute (in_vec1) * transpose(in_vec2)
  //
  template<class TAScalar, class TAIntegral>    
  bool8 outerProduct(const TVector& in_vec1,
		       const MVector<TAScalar, TAIntegral>& in_vec2) {
    return MMatrixMethods::outerProduct<TScalar,TIntegral>(*this, in_vec1,
							   in_vec2);
  }

  //---------------------------------------------------------------------------
  //
  // class-specific public methods:
  //  other matrix to scalar mathematical methods 
  //
  //--------------------------------------------------------------------------

  // method: sum
  //  calculate the sum of all the elements in the matrix
  //
  TIntegral sum() const {
    return MMatrixMethods::sum<TScalar,TIntegral>(*this);
  }

  // method: sum of square
  //  calculate the sum of squares of all the elements in the matrix
  //  
  TIntegral sumSquare() const {
    return MMatrixMethods::sumSquare<TScalar,TIntegral>(*this);
  }

  // method: sumColumn
  //  calculate the sum of all elements in the given column
  //
  TIntegral sumColumn(int32 col_index) const {
    return MMatrixMethods::sumColumn<TScalar,TIntegral>(*this, col_index);
  }
  
  // method: sumRow
  //  calculate the sum of all elements in the given row
  //  
  TIntegral sumRow(int32 row_index) const {
    return MMatrixMethods::sumRow<TScalar,TIntegral>(*this, row_index);
  }
  
  // method: mean
  //  calculate the mean of all the elements in the matrix
  //  
  TIntegral mean() const {
    return sum() / (nrows_d * ncols_d);
  }

  // method: rms
  //  calculate the rms of all the elements in the matrix
  //  
  TIntegral rms() const {
    return (TIntegral)Integral::sqrt(var());
  }

  // method: variance
  //  calculate the variance of all elements as a 1-D array
  //
  TIntegral var() const {
    return MMatrixMethods::var<TScalar,TIntegral>(*this);
  }

  //---------------------------------------------------------------------------
  //
  // private methods
  //
  //---------------------------------------------------------------------------
private:

  //---------------------------------------------------------------------------
  //
  // private methods:
  //  indexing methods
  //
  //--------------------------------------------------------------------------

  // method: index
  //  this method gives the index of an element in the vector for storage
  //
  int32 index(int32 row_index, int32 col_index) const {
    return index(row_index, col_index, nrows_d, ncols_d);
  }

  // method: index
  //
  int32 index(int32 row_index, int32 col_index, int32 num_rows, int32 num_cols,
	     Integral::MTYPE type = Integral::UNCHANGED) const;  
  
  // method: reverseIndex
  //  get the row index and column index of the element in the matrix
  //  from the vector index
  //
  bool8 reverseIndex(int32& row_index, int32& col_index,
		       int32 vec_index) const {
    return MMatrixMethods::reverseIndex(*this, row_index, col_index,
					vec_index);
  }
  
  // method: startRow
  //  get the row index of first available element of a particular column
  //
  int32 startRow(int32 row_index,	Integral::MTYPE type_1,
		Integral::MTYPE type_2 = Integral::UNCHANGED) const;
  
  // method: stopRow
  //  get the row index of last available element of a particular column
  //
  int32 stopRow(int32 row_index,
	       Integral::MTYPE type_1,
	       Integral::MTYPE type_2 = Integral::UNCHANGED) const;
  
  // method: startColumn
  //  get the column index of first available element of a particular row
  //
  int32 startColumn(int32 row_index, Integral::MTYPE type_1,
		   Integral::MTYPE type_2 = Integral::UNCHANGED) const;
  
  // method: stopColumn
  //  get the column index of last available element of a particular row
  //
  int32 stopColumn(int32 row_index, Integral::MTYPE type_1,
		  Integral::MTYPE type_2 = Integral::UNCHANGED) const;
  
  // method: vecLength
  //  this method gives the length of the storage vector for a given
  //  dimension and type of the matrix
  //
  int32 vecLength() const {
    return vecLength(nrows_d, ncols_d, type_d);
  }
  
  // other resizing methods:
  //  these methods facilitate setDimensions, and other such methods,
  //  that require matrix type-specific operations and computations.
  //
  int32 vecLength(int32 nrows, int32 ncols, Integral::MTYPE type) const;
  bool8 vecResetCapacity(int32 nrows, int32 ncols, Integral::MTYPE type);
  bool8 vecResizeCapacity(int32 nrows, int32 ncols);
  bool8 vecCreateLength(int32 nrows, int32 ncols, Integral::MTYPE type);
  bool8 vecDimensionLength(int32 nrows, int32 ncols, bool8 preserve_values);

  // method: randIndicesSparse
  //  a method that generates random non-zero values in a sparse matrix.
  //
  bool8 randIndicesSparse(Random& generator = Random::GLOBAL_UNIFORM) {
    return MMatrixMethods::randIndicesSparse<TScalar, TIntegral>(*this,
								 generator);
  }

  // other type-specific indexing methods
  //
  bool8 sortSparse();
  
  //---------------------------------------------------------------------------
  //
  // private methods:
  //  linear algebra-related methods
  //
  //--------------------------------------------------------------------------

  // method: multiplyRowByColumn
  //  multiply the specified row of one matrix with the specified
  //  column of the other matrix. this is used in the multiply methods
  //
  template <class TAScalar, class TAIntegral>  
  TIntegral multiplyRowByColumn(const MMatrix& matrix_for_row, const
				MMatrix<TAScalar, TAIntegral>& matrix_for_col,
				int32 row_index, int32 col_index) const {
    return MMatrixMethods::multiplyRowByColumn<TScalar, TIntegral>
      (*this, matrix_for_row, matrix_for_col, row_index, col_index);
  }

  // method: multiplyRowByRow
  //  multiply the specified row of one matrix with the specified
  //  row of the other matrix. this is used in the outerProduct methods
  //
  template <class TAScalar, class TAIntegral>  
  TIntegral multiplyRowByRow(const MMatrix& m1,
			     const MMatrix<TAScalar, TAIntegral>& m2,
			     int32 row_m1, int32 row_m2) const {
    return MMatrixMethods::multiplyRowByRow<TScalar, TIntegral>
      (*this, m1, m2, row_m1, row_m2);
  }

  // method: determinantLU
  //
  TIntegral determinantLU() const {
    return MMatrixMethods::determinantLU<TScalar,TIntegral>(*this);
  }

  // method: determinantLU
  //
  TIntegral determinantLU(const MMatrix& matrix) const {
    return MMatrixMethods::determinantLU<TScalar,TIntegral>(matrix);
  }

  // method: determinantMinor
  //
  TIntegral determinantMinor() const {
    return MMatrixMethods::determinantMinor<TScalar,TIntegral>(*this);
  }

  // method: determinantMinor
  //
  TIntegral determinantMinor(const MMatrix& matrix) const {
    return MMatrixMethods::determinantMinor<TScalar,TIntegral>(matrix);
  }

  #ifdef ISIP_TEMPLATE_fp
    // method: eigenComputeVector
    //
    bool8 eigenComputeVector(MVector<TScalar, TIntegral>& eigvect,
			     TIntegral eigval) {
      return MMatrixMethods::eigenComputeVector(*this, eigvect, eigval);
    }

    // method: eigenBalance
    //
    bool8 eigenBalance() {
      return MMatrixMethods::eigenBalance(*this);
    }

    // method: eigenEliminateHessenberg
    //
    bool8 eigenEliminateHessenberg() {
      return MMatrixMethods::eigenEliminateHessenberg(*this);
    }

    // method: eigenHessenbergQR
    //
    bool8 eigenHessenbergQR(MVector<TScalar, TIntegral>& eigval_real,
  			    MVector<TScalar, TIntegral>& eigval_imag) {
      return MMatrixMethods::eigenHessenbergQR(*this, eigval_real, eigval_imag);;
    }
  #else
    // method: eigenComputeVector
    //
    bool8 eigenComputeVector(MVector<TScalar, TIntegral>& eigvect,
			     TIntegral eigval) {
      return false;
    }

    // method: eigenBalance
    //
    bool8 eigenBalance() {
      return false;
    }

    // method: eigenEliminateHessenberg
    //
    bool8 eigenEliminateHessenberg() {
      return false;
    }

    // method: eigenHessenbergQR
    //
    bool8 eigenHessenbergQR(MVector<TScalar, TIntegral>& eigval_real,
  			    MVector<TScalar, TIntegral>& eigval_imag) {
      return false;
    }
  #endif

  //---------------------------------------------------------------------------
  //
  // private methods:
  //  type conversion and streaming
  //
  //--------------------------------------------------------------------------

  // check methods: these methods check properties of the matrix
  //
  bool8 checkSquare(int32 nrows, int32 ncols, Integral::MTYPE type) const;
  Integral::MTYPE checkType(Integral::MTYPE type) const;
  
  // method: assignStream
  //  assign the matrix from a vector containing the stream of data
  //
  bool8 assignStream(int32 nrows, int32 ncols,
		       const TVector& vec, Integral::MTYPE type) {
    return MMatrixMethods::assignStream<TScalar, TIntegral>(*this, nrows,
							    ncols, vec, type);
  }

  // method: assign
  //  array conversion methods
  //  reads complex numbers from array of real numbers
  //    - imaginary components are at the end of the array
  //  this method is used only in diagnoese method.
  //
  bool8  assignComplexDiagnose(int32 num_rows, int32 num_cols,
				  const float64* arg,
				  Integral::MTYPE type = Integral::DEF_MTYPE) {

    return MMatrixMethods::assignComplexDiagnose<TScalar, TIntegral>
      (*this, num_rows, num_cols, arg, type);
  }    

  //---------------------------------------------------------------------------
  //
  // friend classes:
  //  while friend classes and functions are generally discouraged,
  //  they are used in the MMatrix class to circumvent the
  //  template delayed compilation problem. 
  //
  //--------------------------------------------------------------------------

  friend class MMatrixMethods;
};

// end of include file
//
#endif
