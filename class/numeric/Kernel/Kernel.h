// file: $isip/class/algo/Kernel/Kernel.h
// version: $Id: Kernel.h 8793 2002-11-14 21:28:50Z jelinek $
//

// make sure definitions are only made once
//
#ifndef ISIP_KERNEL
#define ISIP_KERNEL

// isip include files
//
#include <NameMap.h>
#include <VectorFloat.h>
#include <VectorDouble.h>

// Kernel: a class for computing various kernel functions such as:
// RBF, polynomial, sigmoid and linear kernels. The kernels
// implemented here represent the most common kernels found in the
// kernel machine literature.
// 
class Kernel {

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
  
  // define kernel choices:
  //  a linear kernel is the default choice
  //
  enum ALGORITHM { LINEAR = 0,  POLYNOMIAL, RBF, SIGMOID,
		   DEF_ALGORITHM = LINEAR };

  // define static NameMap objects for the enumerated values
  //
  static const NameMap ALGO_MAP;

  //----------------------------------------
  //
  // i/o related constants
  //
  //----------------------------------------  
  
  static const String DEF_PARAM;
  static const String PARAM_ALGORITHM;
  static const String PARAM_CONSTANTS;

  //----------------------------------------
  //
  // default values and arguments
  //
  //----------------------------------------  

  // default constants for each Kernel algorithm
  //
  static const VectorFloat DEF_LIN_CONSTANTS;
  static const VectorFloat DEF_POLY_CONSTANTS;
  static const VectorFloat DEF_RBF_CONSTANTS;
  static const VectorFloat DEF_SIGM_CONSTANTS;

  //----------------------------------------
  //
  // error codes
  //
  //----------------------------------------  
  
  static const int32 ERR = 35700;
  static const int32 ERR_PRM = 35701;
  static const int32 ERR_UNKALG = 35702;

  //---------------------------------------------------------------------------
  //
  // protected data
  //
  //---------------------------------------------------------------------------
protected:
  
  // algorithm name
  //
  ALGORITHM algorithm_d;

  // parameters of the Kernel function:
  //  since different kernels require different numbers of parameters,
  //  by making this a vector we are able to collapse all algorithms into
  //  one set of function calls.
  //
  VectorFloat constants_d;

  // initialization flag
  //
  bool8 is_valid_d;
  
  // static memory manager
  //
  static MemoryManager mgr_d;

  // static debug level
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
  
  // other static methods
  //
  static bool8 diagnose(Integral::DEBUG debug_level);
  
  // method: setDebug
  //
  bool8 setDebug(Integral::DEBUG debug_level) {
    debug_level_d = debug_level;
    return true;
  }

  // other debug methods
  //
  bool8 debug(const unichar* msg) const;

  // method: destructor
  //
  ~Kernel() {}

  // method: default constructor
  //
  Kernel(ALGORITHM algorithm = DEF_ALGORITHM) {
    algorithm_d = algorithm;
    is_valid_d = false;
  }
    
  // method: copy constructor
  //
  Kernel(const Kernel& arg) {
    assign(arg);
  }

  // assign methods
  //
  bool8 assign(const Kernel& arg);
  
  // method: operator=
  //
  Kernel& operator= (const Kernel& arg) {
    assign(arg);
    return *this;
  }

  // i/o methods
  //
  int32 sofSize() const;
  
  bool8 read(Sof& sof, int32 tag, const String& name = CLASS_NAME);
  bool8 write(Sof& sof, int32 tag, const String& name = CLASS_NAME) const;

  bool8 readData(Sof& sof, const String& pname = DEF_PARAM,
		   int32 size = SofParser::FULL_OBJECT,
		   bool8 param = true,
                   bool8 nested = false);
  bool8 writeData(Sof& sof, const String& pname = DEF_PARAM) const;
  
  // equality methods
  //
  bool8 eq(const Kernel& arg) const;
  
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
  
  // other memory management methods
  //
  bool8 clear(Integral::CMODE ctype = Integral::DEF_CMODE);
  
  //---------------------------------------------------------------------------
  //
  // class-specific public methods
  //  set methods
  //
  //---------------------------------------------------------------------------

  // method: setAlgorithm
  //
  bool8 setAlgorithm(ALGORITHM algorithm) {
    algorithm_d = algorithm;
    constants_d.clear(Integral::RESET);
    is_valid_d = false;
    return true;  
  }  

  // other set methods
  //
  bool8 setConstants(const VectorFloat& constants);
  
  //---------------------------------------------------------------------------
  //
  // class-specific public methods
  //  get methods
  //
  //---------------------------------------------------------------------------

  // method: getAlgorithm
  //
  ALGORITHM getAlgorithm() const {
    return algorithm_d;
  }

  // method: getConstants
  //
  const VectorFloat& getConstants() const {
    return constants_d;
  }

  //---------------------------------------------------------------------------
  //
  // class-specific public methods:
  //  computational methods
  //
  //---------------------------------------------------------------------------

  // computes the kernel function K(x,y)
  //
  bool8 compute(float32& value, const VectorFloat& x, const VectorFloat& y);
  bool8 compute(float64& value, const VectorDouble& x, const VectorDouble& y);

  //---------------------------------------------------------------------------
  //
  // class-specific public methods:
  //  public methods required by the AlgorithmBase interface contract
  //
  //---------------------------------------------------------------------------

  // initialization method
  //
  bool8 init();

  //---------------------------------------------------------------------------
  //
  // private methods
  //
  //---------------------------------------------------------------------------
private:

  // these methods compute particular kernels
  //
  bool8 computeLinear(float32& value, const VectorFloat& x,
			const VectorFloat& y);
  bool8 computeLinear(float64& value, const VectorDouble& x,
			const VectorDouble& y);

  bool8 computePolynomial(float32& value, const VectorFloat& x,
			    const VectorFloat& y);
  bool8 computePolynomial(float64& value, const VectorDouble& x,
			    const VectorDouble& y);

  bool8 computeRBF(float32& value, const VectorFloat& x,
		     const VectorFloat& y);
  bool8 computeRBF(float64& value, const VectorDouble& x,
		     const VectorDouble& y);

  bool8 computeSigmoid(float32& value, const VectorFloat& x,
			 const VectorFloat& y);
  bool8 computeSigmoid(float64& value, const VectorDouble& x,
			 const VectorDouble& y);

};

// end of include file
// 
#endif
