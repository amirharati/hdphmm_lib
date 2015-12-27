// file: $isip/class/math/matrix/MMatrix/MMatrixMethods.h
// version: $Id: MMatrixMethods.h 10304 2005-12-14 06:25:15Z srinivas $
//

// make sure definitions are only made once
//
#ifndef ISIP_MMATRIX_METHODS
#define ISIP_MMATRIX_METHODS

// isip include files
//
#ifndef ISIP_MVECTOR
#include <MVector.h>
#endif

#ifndef ISIP_MSCALAR
#include <MScalar.h>
#endif

#ifndef ISIP_LONG
#include <Long.h>
#endif

#ifndef ISIP_CHAR
#include <Char.h>
#endif

// forward class definitions
//
template<class TScalar, class TIntegral> class MMatrix;
class VectorLong;

// MMatrixMethods: a friend class to the MMatrix template.
// its purpose is mainly to provide a mechanism to get source code
// out of the header file and into implementation files.
//
class MMatrixMethods {
  
  //---------------------------------------------------------------------------
  //
  // required public methods
  //
  //---------------------------------------------------------------------------
public:

  // static methods
  //
  template <class TMatrix, class TScalar, class TIntegral>
  static bool8 diagnose(Integral::DEBUG debug_level);

  // assign methods
  //
  template <class TScalar, class TIntegral, class TAScalar, class TAIntegral>
  static bool8 assign(MMatrix<TScalar, TIntegral>& obj,
			const MMatrix<TAScalar, TAIntegral>& arg);
  
  // i/o methods
  //
  template <class TScalar, class TIntegral>
  static int32 sofSize(const MMatrix<TScalar, TIntegral>& obj);

  template <class TScalar, class TIntegral>
  static bool8 read(MMatrix<TScalar, TIntegral>& obj, Sof& sof, int32 tag, 
		      const String& name);

  template <class TScalar, class TIntegral>
  static bool8 write(const MMatrix<TScalar, TIntegral>& obj, 
		       Sof& sof, int32 tag, const String& name);

  template <class TScalar, class TIntegral>
  static bool8 readData(MMatrix<TScalar, TIntegral>& obj, 
			  Sof& sof, const String& pname, 
			  int32 size = SofParser::FULL_OBJECT, 
			  bool8 param = true, bool8 nested = false);

  template <class TScalar, class TIntegral>
  static bool8 writeData(const MMatrix<TScalar, TIntegral>& obj, 
			   Sof& sof, const String& name);
  
  //---------------------------------------------------------------------------
  //
  // class-specific public methods:
  //  extensions to required methods
  //
  //---------------------------------------------------------------------------

  // method: eq
  //
  template <class TScalar, class TIntegral>
  static bool8 eq(const MMatrix<TScalar, TIntegral>& obj, TIntegral value);

  // array conversion methods
  //
  template <class TScalar, class TIntegral, class TAIntegral>
  static bool8 assign(MMatrix<TScalar, TIntegral>& obj, 
			int32 nrows, int32 ncols, const TAIntegral* arg, 
			Integral::MTYPE type);
  
  template <class TScalar, class TIntegral>  
  static bool8 assignComplexDiagnose(MMatrix<TScalar, TIntegral>& obj, 
			int32 nrows, int32 ncols, const float64* arg, 
			Integral::MTYPE type);
  
  // conversion from string methods
  //
  template <class TScalar, class TIntegral>
  static bool8 assign(MMatrix<TScalar, TIntegral>& obj,
			int32 nrows, int32 ncols, const String* arg,
			Integral::MTYPE type);
    
  template <class TScalar, class TIntegral>
  static bool8 assign(MMatrix<TScalar, TIntegral>& obj,
			int32 nrows, int32 ncols, const String& arg, 
			Integral::MTYPE type, const Char delim);

  // copy methods
  //
  template <class TScalar, class TIntegral, class TAScalar, class TAIntegral>
  static bool8 copy(MMatrix<TScalar, TIntegral>& obj,
		      const MMatrix<TAScalar, TAIntegral>& arg);
      
  // swap methods
  //
  template <class TScalar, class TIntegral>
  static bool8 swap(MMatrix<TScalar, TIntegral>& obj, 
		      MMatrix<TScalar, TIntegral>& matrix);

  //---------------------------------------------------------------------------
  //
  // class-specific public methods:
  //  operator overloads, get, find, and set methods
  //
  //---------------------------------------------------------------------------

  // methods to get values from a matrix
  //
  template <class TScalar, class TIntegral>
  static TIntegral getValue(const MMatrix<TScalar, TIntegral>& obj, 
			    int32 row_index, int32 col_index);

  template <class TScalar, class TIntegral>
  static bool8 getValue(const MMatrix<TScalar, TIntegral>& obj, 
			  TScalar& value, int32 row_index, int32 col_index);

  template <class TScalar, class TIntegral>
  static bool8 getRow(const MMatrix<TScalar, TIntegral>& obj, 
			MVector<TScalar, TIntegral>& vector,
			int32 row_index);
  
  template <class TScalar, class TIntegral>
  static bool8 getColumn(const MMatrix<TScalar, TIntegral>& obj, 
			   MVector<TScalar, TIntegral>& vector,
			   int32 col_index);
  
  template <class TScalar, class TIntegral>
  static bool8 getDiagonal(const MMatrix<TScalar, TIntegral>& obj, 
			     MVector<TScalar, TIntegral>& vector);
  
  template <class TScalar, class TIntegral>
  static bool8 getLower(const MMatrix<TScalar, TIntegral>& obj, 
			  MMatrix<TScalar, TIntegral>& arg);
  
  template <class TScalar, class TIntegral>
  static bool8 getUpper(const MMatrix<TScalar, TIntegral>& obj, 
			  MMatrix<TScalar, TIntegral>& arg);
  
  template <class TScalar, class TIntegral>
  static bool8 getMinor(const MMatrix<TScalar, TIntegral>& obj, 
			  MMatrix<TScalar, TIntegral>& arg, 
			  int32 row_index, int32 col_index);

  // methods to set values
  //
  template <class TScalar, class TIntegral>
  static bool8 setValue(MMatrix<TScalar, TIntegral>& obj, 
			  int32 row_index, int32 col_index, TIntegral value);

  template <class TScalar, class TIntegral>
  static bool8 setRow(MMatrix<TScalar, TIntegral>& obj, int32 row_index,
			const MVector<TScalar, TIntegral>& vector);

  template <class TScalar, class TIntegral>
  static bool8 setColumn(MMatrix<TScalar, TIntegral>& obj, int32 col_index,
			   const MVector<TScalar, TIntegral>& vector);

  template <class TScalar, class TIntegral>
  static bool8 setDiagonal(MMatrix<TScalar, TIntegral>& obj, 
			     const MVector<TScalar, TIntegral>& values);
  
  template <class TScalar, class TIntegral>
  static bool8 setLower(MMatrix<TScalar, TIntegral>& obj,
			  const MMatrix<TScalar, TIntegral>& source);

  template <class TScalar, class TIntegral>
  static bool8 setUpper(MMatrix<TScalar, TIntegral>& obj,
			  const MMatrix<TScalar, TIntegral>& source);

  template <class TScalar, class TIntegral>
  static bool8 setBlock(MMatrix<TScalar, TIntegral>& obj,
			  int32 start_row, int32 start_col,
			  int32 num_rows, int32 num_cols, TIntegral value);

  // methods to make matrices
  //
  template <class TScalar, class TIntegral>
  static bool8 makeDiagonal(MMatrix<TScalar, TIntegral>& obj,
			      const MVector<TScalar, TIntegral>& values,
			      Integral::MTYPE type);

  template <class TScalar, class TIntegral>
  static bool8 makeLower(MMatrix<TScalar, TIntegral>& obj,
			   const MMatrix<TScalar, TIntegral>& source,
			   Integral::MTYPE type);
  
  template <class TScalar, class TIntegral>
  static bool8 makeUpper(MMatrix<TScalar, TIntegral>& obj,
			   const MMatrix<TScalar, TIntegral>& source,
			   Integral::MTYPE type);
  
  // methods to find values
  //
  template <class TScalar, class TIntegral>
  static bool8 nextZero(const MMatrix<TScalar, TIntegral>& obj,
			  int32& row_index, int32& col_index,
			  int32 row_start, int32 col_start);
     
  template <class TScalar, class TIntegral>
  static bool8 nextNonZero(const MMatrix<TScalar, TIntegral>& obj,
			     TIntegral& value,
			     int32& row_index, int32& col_index,
			     int32 row_start, int32 col_start);

  template <class TScalar, class TIntegral>
  static int32 findRow(const MMatrix<TScalar, TIntegral>& obj, 
		      const MVector<TScalar, TIntegral>& vector);
    
  //---------------------------------------------------------------------------
  //
  // class-specific public methods:
  //  property checking methods
  //
  //---------------------------------------------------------------------------
  
  // change/get type methods
  //
  template <class TScalar, class TIntegral>
  static bool8 isTypePossible(const MMatrix<TScalar, TIntegral>& obj, 
				Integral::MTYPE type);

  template <class TScalar, class TIntegral>
  static bool8 isSquare(const MMatrix<TScalar, TIntegral>& obj, 
			  const MMatrix<TScalar, TIntegral>& matrix);

  template <class TScalar, class TIntegral>
  static bool8 isOrthogonal(const MMatrix<TScalar, TIntegral>& obj);

  template <class TScalar, class TIntegral>
  static bool8 isIdentity(const MMatrix<TScalar, TIntegral>& obj);

  //---------------------------------------------------------------------------
  //
  // class-specific public methods:
  //  relational and logical methods
  //
  //---------------------------------------------------------------------------

  // relational and bool8 methods
  //
  template <class TScalar, class TIntegral>
  static bool8 gt(const MMatrix<TScalar, TIntegral>& obj, TIntegral value);

  template <class TScalar, class TIntegral>
  static bool8 lt(const MMatrix<TScalar, TIntegral>& obj, TIntegral value);

  template <class TScalar, class TIntegral>
  static bool8 ge(const MMatrix<TScalar, TIntegral>& obj, TIntegral value);

  template <class TScalar, class TIntegral>
  static bool8 le(const MMatrix<TScalar, TIntegral>& obj, TIntegral value);

  template <class TScalar, class TIntegral>
  static int32 numEqual(const MMatrix<TScalar, TIntegral>& obj,
		       TIntegral value);
  
  //---------------------------------------------------------------------------
  //
  // class-specific public methods:
  //  concatenation methods 
  //
  //--------------------------------------------------------------------------
  
  // concatenation methods
  //
  template <class TScalar, class TIntegral>
  static bool8 concatByRow(MMatrix<TScalar, TIntegral>& obj, const
			     MMatrix<TScalar, TIntegral>& additional_rows);

  template <class TScalar, class TIntegral>	
  static bool8 concatByColumn(MMatrix<TScalar, TIntegral>& obj, const
				MMatrix<TScalar, TIntegral>& additional_cols);

  //---------------------------------------------------------------------------
  //
  // class-specific public methods:
  //  ordering methods 
  //
  //--------------------------------------------------------------------------

  // ordering methods
  //
  template <class TScalar, class TIntegral>
  static bool8 reorderRows(MMatrix<TScalar, TIntegral>& obj, 
			     const MVector<Long, int32>& indexes);

  template <class TScalar, class TIntegral>
  static bool8 reorderColumns(MMatrix<TScalar, TIntegral>& obj, 
				const MVector<Long, int32>& indexes);

  template <class TScalar, class TIntegral>
  static bool8 swapRows(MMatrix<TScalar, TIntegral>& obj, 
			  const MMatrix<TScalar, TIntegral>& arg, 
			  int32 row1, int32 row2);

  template <class TScalar, class TIntegral>
  static bool8 swapColumns(MMatrix<TScalar, TIntegral>& obj, 
			     const MMatrix<TScalar, TIntegral>& arg, 
			     int32 col1, int32 col2);

  //---------------------------------------------------------------------------
  //
  // class-specific public methods:
  //  basic mathematical methods
  //
  //---------------------------------------------------------------------------

  template <class TScalar, class TIntegral>
  static bool8 add(MMatrix<TScalar, TIntegral>& obj,
		     TIntegral value);

  template <class TScalar, class TIntegral, class TAScalar, class TAIntegral>
  static bool8 add(MMatrix<TScalar, TIntegral>& obj,
		     const MMatrix<TAScalar, TAIntegral>& m1);

  template <class TScalar, class TIntegral, class TAScalar, class TAIntegral>
  static bool8 add(MMatrix<TScalar, TIntegral>& obj,
		     const MMatrix<TScalar, TIntegral>& m1, 
		     const MMatrix<TAScalar, TAIntegral>& m2);

  template <class TScalar, class TIntegral>
  static bool8 add(MMatrix<TScalar, TIntegral>& obj,
		     const MMatrix<TScalar, TIntegral>& source_matrix, 
		     TIntegral value);

  template <class TScalar, class TIntegral>
  static bool8 sub(MMatrix<TScalar, TIntegral>& obj,
		     TIntegral value);

  template <class TScalar, class TIntegral, class TAScalar, class TAIntegral>
  static bool8 sub(MMatrix<TScalar, TIntegral>& obj,
		     const MMatrix<TAScalar, TAIntegral>& m1);

  template <class TScalar, class TIntegral, class TAScalar, class TAIntegral>
  static bool8 sub(MMatrix<TScalar, TIntegral>& obj,
		     const MMatrix<TScalar, TIntegral>& m1, 
		     const MMatrix<TAScalar, TAIntegral>& m2);

  template <class TScalar, class TIntegral>
  static bool8 sub(MMatrix<TScalar, TIntegral>& obj,
		     const MMatrix<TScalar, TIntegral>& source_matrix, 
		     TIntegral value);

  template <class TScalar, class TIntegral, class TAScalar, class TAIntegral>
  static bool8 mult(MMatrix<TScalar, TIntegral>& obj,
		      const MMatrix<TScalar, TIntegral>& m1, 
		      const MMatrix<TAScalar, TAIntegral>& m2);

  //---------------------------------------------------------------------------
  //
  // class-specific public methods:
  //  other mathematical methods
  //
  //--------------------------------------------------------------------------
  
  template <class TScalar, class TIntegral>
  static TIntegral min(const MMatrix<TScalar, TIntegral>& obj);

  template <class TScalar, class TIntegral>
  static TIntegral min(const MMatrix<TScalar, TIntegral>& obj, 
		       int32& row_index, int32& col_index);

  template <class TScalar, class TIntegral>
  static TIntegral max(const MMatrix<TScalar, TIntegral>& obj); 

  template <class TScalar, class TIntegral>
  static TIntegral max(const MMatrix<TScalar, TIntegral>& obj,
		       int32& row_index, int32& col_index);

  template <class TScalar, class TIntegral>
  static float64 minMag(const MMatrix<TScalar, TIntegral>& obj); 

  template <class TScalar, class TIntegral>
  static float64 minMag(const MMatrix<TScalar, TIntegral>& obj, 
			  int32& row_index, int32& col_index);
  
  template <class TScalar, class TIntegral>
  static float64 maxMag(const MMatrix<TScalar, TIntegral>& obj); 

  template <class TScalar, class TIntegral>
  static float64 maxMag(const MMatrix<TScalar, TIntegral>& obj, 
			  int32& row_index, int32& col_index);

  // random number generation methods
  //
  template <class TScalar, class TIntegral>
  static bool8 rand(MMatrix<TScalar, TIntegral>& obj,
		      Random& generator);
  
  template <class TScalar, class TIntegral>
  static bool8 rand(MMatrix<TScalar, TIntegral>& obj,
		      TIntegral min_val, TIntegral max_val,
		      Random& generator);
  
  template <class TScalar, class TIntegral>
  static bool8 grand(MMatrix<TScalar,TIntegral>& obj,
		       TIntegral mean, TIntegral stdev, Random& generator);
  
  template <class TScalar, class TIntegral>
  static bool8 randIndicesSparse(MMatrix<TScalar,TIntegral>& obj,
				   Random& generator);
  
  //---------------------------------------------------------------------------
  //
  // class-specific public methods:
  //  linear algebra related methods 
  //
  //--------------------------------------------------------------------------
  
  // determinant and inverse methods
  //
  template <class TScalar, class TIntegral>
  static TIntegral determinant(const MMatrix<TScalar, TIntegral>& obj); 

  template <class TScalar, class TIntegral>
  static TIntegral determinantLU(const MMatrix<TScalar, TIntegral>& obj); 

  template <class TScalar, class TIntegral>
  static TIntegral determinantMinor(const MMatrix<TScalar, TIntegral>& obj); 

  template <class TScalar, class TIntegral>
  static bool8 inverse(MMatrix<TScalar, TIntegral>& obj, 
			 const MMatrix<TScalar, TIntegral>& matrix);

  template <class TScalar, class TIntegral>
  static bool8 transpose(MMatrix<TScalar, TIntegral>& obj, 
			   const MMatrix<TScalar, TIntegral>& matrix);

  template <class TScalar, class TIntegral>
  static int32 rank(const MMatrix<TScalar, TIntegral>& obj);

  template <class TScalar, class TIntegral>
  static TIntegral trace(const MMatrix<TScalar, TIntegral>& obj);
  
  // decomposition methods
  //
  template <class TScalar, class TIntegral>
  static bool8 decompositionLU(const MMatrix<TScalar,TIntegral>& input,
				 MMatrix<TScalar, TIntegral>& l,
				 MMatrix<TScalar, TIntegral>& u,
				 MVector<Long, int32>& index,
				 int32& sign,
				 float64 stabilize);

  template <class TScalar, class TIntegral>
  static bool8 decompositionCholesky(const MMatrix<TScalar,TIntegral>& input,
				       MMatrix<TScalar, TIntegral>& l);
    
  template <class TScalar, class TIntegral>
  static bool8 decompositionSVD(const MMatrix<TScalar,TIntegral>& input,
  				  MMatrix<TScalar, TIntegral>& u,
  				  MMatrix<TScalar, TIntegral>& w,
  				  MMatrix<TScalar, TIntegral>& v,
				  bool8);

  template <class TScalar, class TIntegral>
  static bool8 decompositionQR(const MMatrix<TScalar, TIntegral>& input,
				 MMatrix<TScalar, TIntegral>& q,
				 MMatrix<TScalar, TIntegral>& r);

  // methods to compute eigenvalues and eigenvectors
  //
  template <class TScalar, class TIntegral>
  static bool8 eigen(const MMatrix<TScalar,TIntegral>& obj,
		       MVector<TScalar, TIntegral>& eigvals,
		       MMatrix<TScalar, TIntegral>& eigvects);

  template <class TScalar, class TIntegral>  
  static bool8 eigenComputeVector(MMatrix<TScalar, TIntegral>& obj,
				    MVector<TScalar, TIntegral>& eigvect,
				    TIntegral eigval);

  template <class TScalar, class TIntegral>    
  static bool8 eigenBalance(MMatrix<TScalar, TIntegral>& obj);

  template <class TScalar, class TIntegral>    
  static bool8 eigenEliminateHessenberg(MMatrix<TScalar, TIntegral>& obj);

  template <class TScalar, class TIntegral>    
  static bool8 eigenHessenbergQR(MMatrix<TScalar, TIntegral>& obj,
				   MVector<TScalar, TIntegral>& eig_val_real,
				   MVector<TScalar, TIntegral>& eig_val_imag);

  template<class TScalar, class TIntegral>
  static bool8 luSolve(MVector<TScalar, TIntegral>& out_vec,
			 const MMatrix<TScalar, TIntegral>& l,
			 const MMatrix<TScalar, TIntegral>& u,
			 const VectorLong& index,
			 const MVector<TScalar, TIntegral>& in_vec);
 
  template<class TScalar, class TIntegral>
  static bool8 choleskySolve(MVector<TScalar, TIntegral>& out_vec,
			       const MMatrix<TScalar, TIntegral>& l,
			       const MVector<TScalar, TIntegral>& in_vec);
 
  template<class TScalar, class TIntegral>
  static bool8 svdSolve(MVector<TScalar, TIntegral>& out_vec,
			  const MMatrix<TScalar, TIntegral>& u,
			  const MMatrix<TScalar, TIntegral>& w,
			  const MMatrix<TScalar, TIntegral>& v,
			  const MVector<TScalar, TIntegral>& in_vec,
			  bool8 zero_singulars);
 
  template <class TScalar, class TIntegral>
  static bool8 multv(const MMatrix<TScalar, TIntegral>& obj, 
		       MVector<TScalar, TIntegral>& output_vector,
		       const MVector<TScalar, TIntegral>& input_vector);

  template <class TScalar, class TIntegral>
  static bool8 vmult(const MMatrix<TScalar, TIntegral>& obj, 
		       MVector<TScalar, TIntegral>& output_vector,
		       const MVector<TScalar, TIntegral>& input_vector);

  template <class TScalar, class TIntegral>
  static bool8 quadratic(TIntegral& output, 
			   const MMatrix<TScalar, TIntegral>& obj, 
			   const MVector<TScalar, TIntegral>& input_vector);

  template <class TScalar, class TIntegral>
  static bool8 quadratic(MMatrix<TScalar, TIntegral>& output,
			   const MMatrix<TScalar, TIntegral>& input_mat1, 
			   const MMatrix<TScalar, TIntegral>& input_mat2);

  template <class TScalar, class TIntegral, class TAScalar, class TAIntegral>
  static bool8 outerProduct(MMatrix<TScalar, TIntegral>& out_matrix,
			      const MMatrix<TScalar, TIntegral>& input_mat1, 
			      const MMatrix<TAScalar, TAIntegral>& input_mat2);

  template <class TScalar, class TIntegral, class TAScalar, class TAIntegral>
  static bool8 outerProduct(MMatrix<TScalar, TIntegral>& out_matrix,
			      const MVector<TScalar, TIntegral>& input_vec1, 
			      const MVector<TAScalar, TAIntegral>& input_vec2);

  //---------------------------------------------------------------------------
  //
  // class-specific public methods:
  //  summation methods
  //
  //--------------------------------------------------------------------------

  template <class TScalar, class TIntegral>
  static TIntegral sum(const MMatrix<TScalar, TIntegral>& obj);

  template <class TScalar, class TIntegral>
  static TIntegral sumSquare(const MMatrix<TScalar, TIntegral>& obj);

  template <class TScalar, class TIntegral>	
  static TIntegral sumColumn(const MMatrix<TScalar, TIntegral>& obj, 
			     int32 col_index);

  template <class TScalar, class TIntegral>	
  static TIntegral sumRow(const MMatrix<TScalar, TIntegral>& obj, 
			  int32 row_index);

  template <class TScalar, class TIntegral>
  static TIntegral var(const MMatrix<TScalar, TIntegral>& obj);

  //---------------------------------------------------------------------------
  //
  // class-specific public methods:
  //  methods that are private in MMatrix
  //
  //--------------------------------------------------------------------------

  template <class TScalar, class TIntegral>
  static bool8 reverseIndex(const MMatrix<TScalar, TIntegral>& obj,
			   int32& row, int32& col, int32 vec_index);
  
  template <class TScalar, class TIntegral, class TAScalar, class TAIntegral>
  static TIntegral multiplyRowByColumn(const MMatrix<TScalar, TIntegral>& obj, 
				       const MMatrix<TScalar, TIntegral>&
				       matrix_for_row, 
				       const MMatrix<TAScalar, TAIntegral>&
				       matrix_for_col, 
				       int32 row_index, int32 col_index);
  
  template<class TScalar, class TIntegral, class TAScalar, class TAIntegral>
  static TIntegral multiplyRowByRow(const MMatrix<TScalar, TIntegral>& obj, 
				    const MMatrix<TScalar, TIntegral>& m1, 
				    const MMatrix<TAScalar, TAIntegral>& m2,
				    int32 row_m1, int32 row_m2);

  template <class TScalar, class TIntegral>
  static bool8 assignStream(MMatrix<TScalar, TIntegral>& obj, 
			      int32 nrows, int32 ncols, 
			      const MVector<TScalar, TIntegral>& vec, 
			      Integral::MTYPE type);

  //---------------------------------------------------------------------------
  //
  // class-specific public methods:
  //  diagnostic methods
  //
  //--------------------------------------------------------------------------

  // test general methods

  template <class TScalar, class TIntegral>
  static bool8 diagnose0(Integral::DEBUG level);

  // test single matrix->scalar methods
  //
  template <class TScalar, class TIntegral>
  static bool8 diagnose1(Integral::DEBUG level);

  // test single matrix->vector methods
  //
  template <class TScalar, class TIntegral>
  static bool8 diagnose2(Integral::DEBUG level);

  // test single matrix->matrix methods
  //
  template <class TScalar, class TIntegral>
  static bool8 diagnose3(Integral::DEBUG level);

  // test (matrix, matrix)->matrix methods (real)
  //
  template <class TScalar, class TIntegral>
  static bool8 diagnose4(Integral::DEBUG level);

  // test (matrix, matrix)->matrix methods (complex)
  //
  template <class TScalar, class TIntegral>
  static bool8  diagnose5(Integral::DEBUG level);

  //---------------------------------------------------------------------------
  //
  // private methods
  //
  //---------------------------------------------------------------------------
private:
  
  // destructor/constructor(s):
  // the constructors and destructors are declared private so that a
  // compilation error will be generated if the user tries to construct an
  // object of this type
  //
  ~MMatrixMethods();
  MMatrixMethods();
  MMatrixMethods(const MMatrixMethods& arg);

  // method: name
  //  make this method private so it is never called outside this class
  //
  static const String& name();
};

// end of include file
//
#endif
