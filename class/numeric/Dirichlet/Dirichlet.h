// file: Dirichlet.h
// version: $Id: Dirichlet.h 2013-07-18 by Amir Harati$
//
//
// make sure definitions are only made once
//
#ifndef ISIP_DIRICHLET
#define ISIP_DIRICHLET

// isip include files:
//
#ifndef ISIP_SYS_STRING
#include <SysString.h>
#endif

#ifndef ISIP_MEMORY_MANAGER
#include <MemoryManager.h>
#endif

#ifndef ISIP_RANDOM
#include "Random.h"
#endif

#ifndef  ISIP_VECTOR_FLOAT
#include <VectorFloat.h>
#endif

#ifndef  ISIP_VECTOR_DOUBLE
#include <VectorDouble.h>
#endif



// RandomDirichlet: a class that implements Dirichlet number generator
//
class Dirichlet {

  //---------------------------------------------------------------------------
  //
  // public constants
  //
  //---------------------------------------------------------------------------
public:
  
  // define the class name
  //
  static const SysString CLASS_NAME;
    
  //----------------------------------------
  //
  // other important constants
  //
  //----------------------------------------

  
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

  
  // algorithm: GAMMA, Dirichlet
  //
  //shape parameter for Gamma and Concentration for Dirichlet
  //
  VectorFloat concentration_d;
  
  // length of a_gamma (distribution lenght)
  //
  Long dist_len_d;

  // Random variable
  //
  Random rnd_d;

  // Result storage
  //
  VectorFloat result_d;
 
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
  Dirichlet(const Dirichlet& arg) {
    assign(arg);
  }

  // method: destructor
  //
  ~Dirichlet() {}

  // other constructor(s)
  //
  Dirichlet(int32 seed = DEF_SEED);

  // assign methods:
  //
  bool8 assign(const Dirichlet& arg);

  // method: operator=
  //
  Dirichlet& operator=(const Dirichlet& arg) {
    assign(arg);
    return *this;
  }
    
  // i/o methods:
  //  these methods are omitted
  //
  
  // equality methods:
  //
  bool8 eq(const Dirichlet& arg) const;
  
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
  Dirichlet(VectorFloat param, int32 seed = DEF_SEED) {
    setParameters(param);
    seed_d = seed;
  }

  //---------------------------------------------------------------------------
  //
  // class-specific public methods:
  //  set and get methods
  //
  //---------------------------------------------------------------------------
  
  
  // method: setParameters
  //
  bool8 setParameters(VectorFloat  param){

    concentration_d = param;
    dist_len_d = param.length();  
  
    // set result_d length
    //
    result_d.setLength(dist_len_d);
   
    // exit gracefully
    //
    return true;
  }

  // method: setParameters
  //
  bool8 setParameters(VectorDouble  param){

    concentration_d.assign(param);
    dist_len_d = param.length();  
  
    // set result_d length
    //
    result_d.setLength(dist_len_d);
   
    // exit gracefully
    //
    return true;
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
  bool8 get(VectorFloat &out) {
    if(compute() !=true)
       return Error::handle(name(), L"get",
			   Error::ARG, __FILE__, __LINE__);
    out.assign(result_d);
    return true;
  }


  // method: get
  //
  bool8 get(VectorDouble &out) {
    if(compute() !=true)
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

  
  // Dirichlet random number using Gamma distribution
  //  
  bool8 computeDirichlet();
  
};

// end of include file
//
#endif
