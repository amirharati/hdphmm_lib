// file: $isip/class/math/scalar/Double/Double.h
// version: $Id: Double.h 10636 2007-01-26 22:18:09Z tm334 $
//
// notes:
// (1) AH(07/28/2010) mod , % and %=  has been added

// make sure definitions are only made once
//
#ifndef ISIP_DOUBLE
#define ISIP_DOUBLE

// isip include files
//
#ifndef ISIP_SCALAR
#include <MScalar.h>
#endif

// Double: this is a class that manages a 64-bit float. this class mainly
//  inherits the MScalar template class functionality. we only need to add
//  Sof file support and memory management
//
class Double : public MScalar<float64, float64> {

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

  static const int32 ERR = 21100;

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
  ~Double() {}
  
  // method: default constructor
  //
  Double(float64 arg = DEF_VALUE) {
    value_d = arg;
  }
  
  // method: copy constructor
  //
  Double(const Double& arg) {
    assign(arg.value_d);
  }
    
  // assign methods:
  //  these methods are inherited from the MScalar template class
  //
  
  // method: operator=
  //
  Double& operator= (const Double& arg) {
    assign(arg);
    return *this;
  }
  
  // i/o methods:
  //  the sofSize, readData, and writeData methods are inherited from
  //  the MScalar template class
  //

  // method: read
  //
  bool8 read(Sof& sof, int32 tag, const String& name = CLASS_NAME) {
    return MScalar<float64, float64>::read(sof, tag, name);
  }

  // method: write
  //
  bool8 write(Sof& sof, int32 tag, const String& name = CLASS_NAME) const {
    return MScalar<float64, float64>::write(sof, tag, name);
  }
  
  // equality methods:
  //  these methods are inherited from the MScalar template class
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
  //  this clear is inherited from the MScalar template class
  //
    
  //---------------------------------------------------------------------------
  //
  // class-specific public methods:
  //  extentions to required methods
  //
  //---------------------------------------------------------------------------
public:

  // method: operator=
  //  this method assigns a float64 value to the scalar
  //
  Double& operator= (float64 arg) {
    value_d = arg;
    return *this;
  }

  // method: presentValue
  //
  float64 presentValue(float64 arg) const {
    return (float64)arg;
  }
    Double& operator%= (float64 arg){
	value_d =operator%(arg);
	return *this;
    }
    float64 operator% (float64 arg) {
	float64 value_d_temp=value_d;
	int64 temp=floor(value_d/arg);
	value_d=value_d_temp;
	return (value_d-temp*arg);
    }

    float64 mod(float64 arg0,float64 arg1)
	{
	    Double tmp1;
	    float64 tmp2;
	    tmp1=arg0;
	    tmp2=tmp1.operator%(arg1);
	    return (value_d = tmp2);
	}
    
  // method: fraction
  //
  float64 fraction(float64 arg) {
    return (value_d = Integral::fraction(arg));
  }

  float64 bor(float64 arg0, float64 arg1) {
    return (float64) 0;
  }
  float64 band(float64 arg0, float64 arg1) {
    return (float64) 0;
  }
  float64 bxor(float64 arg0, float64 arg1) {
    return (float64) 0;
  }
  float64 brs(float64 arg0, float64 arg1) {
    return (float64) 0;
  }
  float64 bls(float64 arg0, float64 arg1) {
    return (float64) 0;
  }
  float64 bcmpl(float64 arg) {
    return (float64) 0;
  }
  /*   
  float64 mod(float64 arg0, float64 arg1) {
    return (float64) 0;
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
/*   double bor(double, double); */
/*   double band(double, double); */
/*   double bxor(double, double); */
/*   double brs(double, double); */
/*   double bls(double, double); */
/*   double bcmpl(double); */

/*   // declare modulus methods as private member functions because they */
/*   // are not defined for floating point operations */
/*   // */
/*   double mod(double, double); */
/*   double& operator%= (double); */
/*   double& operator% (double); */

};

// end of include file
//
#endif
