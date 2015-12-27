// file: $isip/class/system/Random/Random.h
// version: $Id: Random.h 10636 2007-01-26 22:18:09Z tm334 $
//
// 07/06/2013 (amir harati): added a gamma random number generator
//
// make sure definitions are only made once
//
#ifndef ISIP_RANDOM
#define ISIP_RANDOM

// isip include files:
//
#ifndef ISIP_SYS_STRING
#include <SysString.h>
#endif

#ifndef ISIP_MEMORY_MANAGER
#include <MemoryManager.h>
#endif

// Random: a class that implements some standard random number generation
// algorithms. this class is introduced at this level because it is used by
// many classes to produce random valued objects. it is implemented in
// a way that allows the flexibility of parallel random generators
// or a single global generator.
//
class Random {

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
  enum ALGORITHM { UNIFORM = 0, GAUSSIAN, GAMMA,
		   DEF_ALGORITHM = UNIFORM };

  // define implementations:
  //  note that ACCREJ stands for "ACCEPTANCE-REJECTION" implementation
  //  for a gamma distribution
  //
  enum IMPLEMENTATION { SUBTRACTIVE = 0, CONGRUENTIAL, TRANSFORMATION, ACCREJ,
			DEF_IMPLEMENTATION = SUBTRACTIVE };
  
  //----------------------------------------
  //
  // other important constants
  //
  //----------------------------------------

  // define global random number generators
  //
  static Random GLOBAL_UNIFORM;
  static Random GLOBAL_GAUSSIAN;
  static Random GLOBAL_GAMMA;

  // define default values to seed random number generators and the
  // size of the generator's array
  //
  static const int32 US_MBIG = 1000000000;
  static const int32 US_MSEED = 161803398;
  static const int32 US_MZ = 0;
  static const int32 US_MDIM = 56;
  static const int32 US_CONST = 30;
  static const float64 US_FAC = (1.0 / 1000000000);

  // define default values to scale random numbers
  //
  static const float64 INV_RAND_MAX = 1.0 / RAND_MAX;

  // define constants for gamma generation algorithm
  //
  static const float64 ACCREJ_THRESHOLD = 0.0331;

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

  // define default values for the generic set method
  //
  static const float64 DEF_VALUE = 1.0;

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

  // algorithm: UNIFORM*
  // implementation: SUBTRACTIVE
  //
  // define some registers to maintain history
  //
  int32 us_inext_d;
  int32 us_inextp_d;
  int32 us_ma_d[US_MDIM];

  // algorithm: GAUSSIAN
  // implementation: TRANSFORMATION
  //
  // define two registers to maintain previously computed values
  //
  bool8 gt_iset_d;
  float64 gt_gset_d;
  
  // algorithm: GAMMA
  // implementation: ACCREJ
  //
  // define alpha, the shape parameter
  //
  float64 gacc_alpha_d;
  
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
  Random(const Random& arg) {
    assign(arg);
  }

  // method: destructor
  //
  ~Random() {}

  // other constructor(s)
  //
  Random(int32 seed = DEF_SEED);

  // assign methods:
  //
  bool8 assign(const Random& arg);

  // method: operator=
  //
  Random& operator=(const Random& arg) {
    assign(arg);
    return *this;
  }
    
  // i/o methods:
  //  these methods are omitted
  //
  
  // equality methods:
  //
  bool8 eq(const Random& arg) const;
  
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
  //
  //  we need a constructor with configuration information to make it easy
  //  for math scalar classes to use this class.
  //
  Random(ALGORITHM alg, IMPLEMENTATION impl, int32 seed = DEF_SEED) {
    setAlgorithm(alg);
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
  bool8 setAlgorithm(ALGORITHM algorithm) {
    algorithm_d = algorithm;
    return (!(is_valid_d = false));
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

  // method: setParameters
  //  note that these parameters are interpreted in an algorithm-specific
  //  manner.
  //
  bool8 setParameters(float64 value = DEF_VALUE);
  
  // method: getParameters
  //  note that these parameters are interpreted in an algorithm-specific
  //  manner.
  //
  float64 getParameters();

  // method: seed
  //
  bool8 seed(int32 value = DEF_SEED) {
    seed_d = value;
    is_valid_d = false;
    return true;
  }

  // method: get
  //
  float64 get() {
    return compute();
  }

  // method: cast (float64) conversion operator
  //  a simple way to get a random number
  //
  operator float64() {
    return compute();
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
  float64 compute();

  //---------------------------------------------------------------------------
  //
  // private methods
  //
  //---------------------------------------------------------------------------
private:

  // algorithm-specific computation methods:
  //  uniform random numbers using a subtractive method
  //
  bool8 initUniformSubtractive();
  float64 computeUniformSubtractive();

  // algorithm-specific computation methods:
  //  uniform random numbers using a multiplicative congruential method
  //
  bool8 initUniformCongruential();
  float64 computeUniformCongruential();

  // algorithm-specific computation methods:
  //  Gaussian random numbers using a transformation method
  //
  bool8 initGaussianTransform();
  float64 computeGaussianTransform();

  // algorithm-specific computation methods:
  //  Gamma random numbers using the acceptance-rejection method
  //
  bool8 initGammaAccrej();
  float64 computeGammaAccrej();
};

// end of include file
//
#endif
