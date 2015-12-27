// file: Wishart.h
// version: $Id: Wishart.h 2013-07-18 by Amir Harati$
//
//
// make sure definitions are only made once
//
#ifndef ISIP_Wishart
#define ISIP_Wishart

// isip include files:
//
#ifndef ISIP_SYS_STRING
#include <SysString.h>
#endif

#ifndef ISIP_MEMORY_MANAGER
#include <MemoryManager.h>
#endif

#ifndef ISIP_RANDOM
#include <Random.h>
#endif

#ifndef  ISIP_VECTOR_FLOAT
#include <VectorFloat.h>
#endif

#ifndef  ISIP_MATRIX_FLOAT
#include <MatrixFloat.h>
#endif

#ifndef ISIP_MATRIX_DOUBLE
#include <MatrixDouble.h>
#endif

#ifndef  ISIP_SCALAR_BOOLEAN
#include <Boolean.h>
#endif

// RandomDirichlet: a class that implements Dirichlet number generator
//
class Wishart {

  //---------------------------------------------------------------------------
  //
  // public constants
  //
  //---------------------------------------------------------------------------
public:
  
  // define the class name
  //
  static const SysString CLASS_NAME;
  
  // define algorithm choices
  //
  enum ALGORITHM { FORWARD = 0 , INVERSE, 
		   DEF_ALGORITHM = INVERSE };

  // define implementations
  //
  enum IMPLEMENTATION { TRANSFORMATION = 0,
			DEF_IMPLEMENTATION = TRANSFORMATION};
  
  //----------------------------------------
  //
  // other important constants
  //
  //----------------------------------------

  static const float64 SQRTH = 0.70710678118655; // sqrt(0.5)
  static const float64 SQRTT = 1.41421356237; // sqrt(2)

  //----------------------------------------
  //
  // default values and arguments
  //
  //----------------------------------------  

  // define the default value(s) of the class data
  //
  
  // default arguments to methods
  //
  
  // define a default value for the random number generator
  //
  static const int32 DEF_SEED = 27;

  //----------------------------------------
  //
  // error codes
  //
  //----------------------------------------  

  static const int32 ERR = 1900;

  //---------------------------------------------------------------------------
  //
  // protected data
  //
  //---------------------------------------------------------------------------
protected:

  // this section contains data common to all algorithms
  //

  // algorithm name
  //
  ALGORITHM algorithm_d;
  
  // implementation name
  //
  IMPLEMENTATION implementation_d;
  
  // define a seed:
  //  most random numbers use a concept of a seed. typically, this is a
  //  large, odd, positive integer value.
  //
  int32 seed_d;

  // declare a static debug level for all class instantiations
  //
  static Integral::DEBUG debug_level_d;

  // static memory manager
  //
  static MemoryManager mgr_d;

  // initialization flag
  //
  bool8 is_valid_d;

  // this section contains data for a specific algorithm
  //
  
  // algorithm: WISHART, INV_WISHART
  //
  // Sigma: Sigma parameter for inverese Wishart 
  // DF : degree of freedom for inverse Wishart
  // DI : Cholesky factor of inverse of Sigma
  //  Using_Sigma : true if  Sigma_DI == SIGMA
  //
  MatrixDouble Sigma_DI_d;
  Double DF_d;
  Boolean Using_Sigma_d;

  // matrix dimensions
  //
  int32 dim1_d;
  int32 dim2_d;


  // Random variable
  //
  Random rnd1_d;
  Random rnd2_d;

  
  
  
  // Result storage
  //
  MatrixDouble result_d;
  
  //  temp  storage
  //
  MatrixDouble temp_result_d;  

  //---------------------------------------------------------------------------
  //
  // required public methods
  //
  //---------------------------------------------------------------------------
public:

  // method: name
  //
  static const SysString& name() {
    return CLASS_NAME;
  }
  
  // other static methods
  //
  static bool8 diagnose(Integral::DEBUG debug_level);
  
  // method: setDebug
  //
  static bool8 setDebug(Integral::DEBUG level) {
    debug_level_d = level;
    return true;
  }
  
  // other debug methods
  //
  bool8 debug(const unichar* message) const;

  // method: copy constructor
  //
  Wishart(const Wishart& arg) {
    assign(arg);
  }

  // method: destructor
  //
  ~Wishart() {}

  // other constructor(s)
  //
  Wishart(int32 seed = DEF_SEED);

  // assign methods:
  //
  bool8 assign(const Wishart& arg);

  // method: operator=
  //
  Wishart& operator=(const Wishart& arg) {
    assign(arg);
    return *this;
  }
    
  // i/o methods:
  //  these methods are omitted
  //
  
  // equality methods:
  //
  bool8 eq(const Wishart& arg) const;
  
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
  bool8 clear(Integral::CMODE ctype_a = Integral::DEF_CMODE);

  //---------------------------------------------------------------------------
  //
  // class-specific public methods:
  //  extensions to required methods
  //
  //---------------------------------------------------------------------------
  

  // method: constructor
  // for Wishart and iWishart dist.
  // sigma_di : either  Sigma of DI
  // df :  degree of freedom
  // using_sigma : true if  sigma_di is  sigma
  // 
  //  we need a constructor with configuration information to make it easy
  //  for math scalar classes to use this class.
  //
  Wishart(ALGORITHM alg, IMPLEMENTATION impl, MatrixDouble sigma_di,int32 df,bool8 using_sigma = true, int32 seed = DEF_SEED) {
    setAlgorithm(alg,sigma_di,df,using_sigma);
    setImplementation(impl);
    seed_d = seed;
  }

  //---------------------------------------------------------------------------
  //
  // class-specific public methods:
  //  set and get methods
  //
  //---------------------------------------------------------------------------
  
 // method: setAlgorithm
  //
  bool8 setAlgorithm(ALGORITHM algorithm){
    algorithm_d=algorithm;
    
    return (!(is_valid_d = false));
  }

  // method: setAlgorithm
  //
  bool8 setAlgorithm(ALGORITHM algorithm,MatrixDouble sigma_di,int32 df,bool8 using_sigma ) {
    algorithm_d = algorithm;
    
    // set params
    //
    setParameters(sigma_di,df,using_sigma);
    
    return (!(is_valid_d = false));
  }

  // method: setParameters
  //
  bool8 setParameters(MatrixFloat sigma_di,double df,bool8 using_sigma){

   
    if (using_sigma == true)
      Using_Sigma_d = true;
    else
      Using_Sigma_d = false;
    
    Sigma_DI_d.assign(sigma_di);
    DF_d= df;
    dim1_d=sigma_di.getNumRows();
    dim2_d=sigma_di.getNumColumns();
     
    // exit gracefully
    //
    return true;   

  }


  // method: setParameters
  //
  bool8 setParameters(MatrixDouble sigma_di,double df,bool8 using_sigma){

   
    if (using_sigma == true)
      Using_Sigma_d = true;
    else
      Using_Sigma_d = false;
    
    Sigma_DI_d.assign(sigma_di);
    DF_d= df;
    dim1_d=sigma_di.getNumRows();
    dim2_d=sigma_di.getNumColumns();
     
    // exit gracefully
    //
    return true;   

  }

  
  // method: setImplementation
  //
  bool8 setImplementation(IMPLEMENTATION implementation) {
    implementation_d = implementation;
    return (!(is_valid_d = false));
  }

  // method: getAlgorithm
  //
  ALGORITHM getAlgorithm() const {
    return algorithm_d;
  }

  // method: getImplementation
  //
  IMPLEMENTATION getImplementation() const {
    return implementation_d;
  }

  // method: seed
  //
  bool8 seed(int32 value = DEF_SEED) {
    seed_d = value;
    is_valid_d = false;
    return true;
  }

  
  // method: get
  //
  bool8 get(MatrixFloat &out) {
    if (compute() != true)
      return Error::handle(name(), L"get",
			   Error::ARG, __FILE__, __LINE__);
    out.assign(result_d);
    return true; 
  }

  // method: get
  //
  bool8 get(MatrixDouble &out) {
    if (compute() != true)
      return Error::handle(name(), L"get",
			   Error::ARG, __FILE__, __LINE__);
    out.assign(result_d);
    return true; 
  }
 

  //---------------------------------------------------------------------------
  //
  // class-specific public methods:
  //  initialization and computation methods
  //
  //---------------------------------------------------------------------------
  
  // initialization methods:
  //  these methods initialize the various class constants
  //
  bool8 init();
  
  // computational methods:
  //  these methods compute a new random number
  //
  bool8 compute();

  //---------------------------------------------------------------------------
  //
  // private methods
  //
  //---------------------------------------------------------------------------
private:

  // algorithm-specific computation methods:
  //
  
  // Wishart random number
  //
  bool8 computeWishart();

  // Inverse Wishart
  //
  bool8 computeiWishart();
  bool8 genWishart(double a);

};

// end of include file
//
#endif
