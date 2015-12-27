// file: $isip/class/math/scalar/Float/Float.h
// version: $Id: Float.h 10636 2007-01-26 22:18:09Z tm334 $
//
// notes:
// (1) AH(07/28/2010) mod , % and %=  has been added
// To Do:
// For undefined functions that return 0 we should throw an error instead
//
// make sure definitions are only made once
//
#ifndef ISIP_FLOAT
#define ISIP_FLOAT

// isip include files
//
#ifndef ISIP_SCALAR
#include <MScalar.h>
#endif

// Float: a class that manages a 32-bit float. this class mainly
// inherits the MScalar template functionality. we only need to add Sof file
// support and memory management
//
class Float : public MScalar<float32, float32> {

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
  
  //----------------------------------------
  //
  // default values and arguments
  //
  //----------------------------------------  

  // define the default value(s) of the class data
  //

  // default arguments to methods
  //
  
  //----------------------------------------
  //
  // error codes
  //
  //----------------------------------------  

  static const int32 ERR = 21000;

  //---------------------------------------------------------------------------
  //
  // protected data
  //
  //---------------------------------------------------------------------------
protected:

  // static memory manager
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

  // debug methods:
  //  the setDebug method is inherited from the MScalar template class
  //
  bool8 debug(const unichar* message) const;
  
  // method: destructor
  //
  ~Float() {}
  
  // method: default constructor
  //
  Float(float32 arg = DEF_VALUE) {
    value_d = arg;
  }

  // method: copy constructor
  //
  Float(const Float& arg) {
    assign(arg.value_d);
  }

  // assign methods:
  //  these methods are inherited from the MScalar template class
  //

  // method: operator=
  //
  Float& operator= (const Float& arg) {
    assign(arg);
    return *this;
  }
    
  // i/o methods:
  //  sofSize, readData and writeData are inherited from the MScalar
  //  template class
  //

  // method: read
  //
  bool8 read(Sof& sof, int32 tag, const String& name = CLASS_NAME) {
    return MScalar<float32, float32>::read(sof, tag, name);
  }

  // method: write
  //
  bool8 write(Sof& sof, int32 tag, const String& name = CLASS_NAME) const {
    return MScalar<float32, float32>::write(sof, tag, name);
  }
  
  // equality methods:
  //  the eq method is inherited from the MScalar template class
  //

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

  // other memory management methods:
  //  these methods are inherited from the MScalar template class
  //
  
  //-----------------------------------------------------------------------
  //
  // class-specific public methods
  //
  //-----------------------------------------------------------------------

  // method: operator=
  //
  Float& operator= (float32 arg) {
    value_d = arg;
    return *this;
  }

    //Add by amir
    Float& operator%= (float32 arg){
	value_d =operator%(arg);
	return *this;
	}
    float32 operator% (float32 arg) {
	    float32 value_d_temp=value_d;
	    int32 temp=floor(value_d/arg);
	    value_d=value_d_temp;
	    return (value_d-temp*arg);
	}

    float32 mod(float32 arg0,float32 arg1)
	{
	    Float tmp1;
	    float32 tmp2;
	    tmp1=arg0;
	    tmp2=tmp1.operator%(arg1);
	    return (value_d = tmp2);
	}
 
    //
  // method: fraction
  //
  float32 fraction(float32 arg) {
    return (value_d = Integral::fraction(arg));
  }

  float32 bor(float32 arg0, float32 arg1) {
    return (float32) 0;
  }
  float32 band(float32 arg0, float32 arg1) {
    return (float32) 0;
  }
  float32 bxor(float32 arg0, float32 arg1) {
    return (float32) 0;
  }
  float32 brs(float32 arg0, float32 arg1) {
    return (float32) 0;
  }
  float32 bls(float32 arg0, float32 arg1) {
    return (float32) 0;
  }
  float32 bcmpl(float32 arg) {
    return (float32) 0;
  }
    /*  
  float32 mod(float32 arg0, float32 arg1) {
    return (float32) 0;
  }
    */
  //---------------------------------------------------------------------------
  //
  // private methods
  //
  //---------------------------------------------------------------------------
private:

/*   // declare bitwise methods as private member functions because they */
/*   // are not defined for floating point operations */
/*   // */
//   float bor(float, float); 
//   float band(float, float); 
//   float bxor(float, float); 
//   float brs(float, float); 
//   float bls(float, float); 
//   float bcmpl(float); 

/*   // declare modulus methods as private member functions because they */
/*   // are not defined for floating point operations */
/*   // */
//   float mod(float, float); 
//   float& operator%= (float); 
    // float operator% (float); 

};

// end of include file
//
#endif
