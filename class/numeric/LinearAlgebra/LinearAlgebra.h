// file: $isip/class/numeric/LinearAlgebra/LinearAlgebra.h
// version: $Id: LinearAlgebra.h 8338 2002-07-11 03:35:34Z picone $
//

// make sure definitions are only made once
//
#ifndef ISIP_LINEAR_ALGEBRA
#define ISIP_LINEAR_ALGEBRA

// isip include files
//
#ifndef ISIP_MATRIX_FLOAT
#include <MatrixFloat.h>
#endif

#ifndef ISIP_VECTOR_FLOAT
#include <VectorFloat.h>
#endif

#ifndef ISIP_MATRIX_DOUBLE
#include <MatrixDouble.h>
#endif

#ifndef ISIP_VECTOR_DOUBLE
#include <VectorDouble.h>
#endif

#ifndef ISIP_MEMORY_MANAGER
#include <MemoryManager.h>
#endif

// LinearAlgebra: a storehouse for linear algebra operations that don't need
// to be generalized to the math/matrix library
//
class LinearAlgebra {

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
  // other important constants
  //
  //----------------------------------------

  static const float64 SVD_SINGULAR_THRESH = 10e-6;
  
  //----------------------------------------
  //
  // i/o related constants
  //
  //----------------------------------------  
  
  static const String DEF_PARAM;
  
  //----------------------------------------
  //
  // default values and arguments
  //
  //----------------------------------------  

  //----------------------------------------
  //
  // error codes
  //
  //----------------------------------------  
  
  static const int32 ERR = 35100;
  static const int32 ERR_LSOLVE_SINGULAR = 35101;
  
  //---------------------------------------------------------------------------
  //
  // protected data
  //
  //---------------------------------------------------------------------------
protected:
  
  // a static debug level
  //
  static Integral::DEBUG debug_level_d;
  
  // a static memory manager
  //
  static MemoryManager mgr_d;
  
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

  // other static methods
  //
  static bool8 diagnose(Integral::DEBUG debug_level);
  
  // method: setDebug
  //
  static bool8 setDebug(Integral::DEBUG debug_level) {
    debug_level_d = debug_level;
    return true;
  }
  
  // method: debug
  //
  bool8 debug(const unichar* msg) const {
    String output;
    output.debugStr(name(), msg, L"");
    Console::put(output);
    return true;
  }

  // method: destructor
  //
  ~LinearAlgebra() {}
  
  // method: default constructor
  //
  LinearAlgebra() {}

  // method: copy constructor
  //
  LinearAlgebra(const LinearAlgebra& arg) {
    assign(arg);
  }
  
  // method: assign
  //
  bool8 assign(const LinearAlgebra& arg) {
    return true;
  }

  // method: operator=
  //
  LinearAlgebra& operator= (const LinearAlgebra& arg) {
    assign(arg);
    return *this;
  }

  // method: sofSize
  //
  int32 sofSize() const {
    return 0;
  }
  
  // method: read
  //
  bool8 read(Sof& sof, int32 tag, const String& name = CLASS_NAME) {
    return true;
  }

  // method: write
  //
  bool8 write(Sof& sof, int32 tag, const String& name = CLASS_NAME) const {
    return true;
  }

  // method: readData
  //
  bool8 readData(Sof& sof, const String& pname = DEF_PARAM,
                   int32 size = SofParser::FULL_OBJECT,
                   bool8 param = true,
                   bool8 nested = false) {
    return true;
  }

  // method: writeData
  //
  bool8 writeData(Sof& sof, const String& name = DEF_PARAM) const {
    return true;
  }

  // method: eq
  //
  bool8 eq(const LinearAlgebra& arg) const {
    return true;
  }

  // method: new
  //
  static void* operator new(size_t size) {
    return mgr_d.get();
  }

  // method: new[]
  //
  static void* operator new[](size_t size) {
    return mgr_d.getBlock(size);
  }

  // method: delete
  //
  static void operator delete(void* ptr) {
    mgr_d.release(ptr);
  }

  // method: delete[]
  //
  static void operator delete[](void* ptr) {
    mgr_d.releaseBlock(ptr);
  }
  
  // method: setGrowSize
  // 
  static bool8 setGrowSize(int32 grow_size) {
    return mgr_d.setGrow(grow_size);
  }

  // method: clear
  //
  bool8 clear(Integral::CMODE cmode = Integral::DEF_CMODE) {
    return true;
  }

  //---------------------------------------------------------------------------
  //
  // class-specific public methods:
  //  equation solvers
  //
  //---------------------------------------------------------------------------

  // method: linearSolve
  //  solves functions of the form A*x = b, for the unknown 'x' using
  //  LU decomposition
  //
  static bool8 linearSolve(VectorFloat& x, const MatrixFloat& A,
			     const VectorFloat& b) {
    return linearSolveTemplate<MatrixFloat, VectorFloat>(x, A, b);
  }

  // method: linearSolve
  //  solves functions of the form A*x = b, for the unknown 'x' using
  //  LU decomposition
  //
  static bool8 linearSolve(VectorDouble& x, const MatrixDouble& A,
			     const VectorDouble& b) {
    return linearSolveTemplate<MatrixDouble, VectorDouble>(x, A, b);
  }
  
  //---------------------------------------------------------------------------
  //
  // private methods
  //
  //---------------------------------------------------------------------------
private:

  // templatized linear solver methods
  //
  template <class TMatrix, class TVector>
  static bool8 linearSolveTemplate(TVector& x, const TMatrix& A,
				     const TVector& b);
};

// end of include file
// 
#endif



