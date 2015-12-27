// file: $isip/class/math/scalar/ComplexFloat/ComplexFloat.h
// version: $Id: ComplexFloat.h 10675 2009-07-21 01:13:30Z tm334 $
//

// make sure definitions are only made once
//
#ifndef ISIP_COMPLEX_FLOAT
#define ISIP_COMPLEX_FLOAT

// isip include files
//
#ifndef ISIP_MCOMPLEX_SCALAR
#include <MComplexScalar.h>
#endif

// ComplexFloat: a class that manages a complex number for which
// each component is a 32-bit floating point number. this class largely
// inherits the MComplexScalar and MScalar template functionality.
//
class ComplexFloat : public MComplexScalar<float32, float32> {

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

  static const int32 ERR = 21300;

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
  ~ComplexFloat() {}
  
  // method: default constructor
  //
  ComplexFloat(complexfloat arg = DEF_VALUE) {
    value_d = arg;
  }

  // method: copy constructor
  //
  ComplexFloat(const ComplexFloat& arg) {
    assign(arg.value_d);
  }

  // assign methods:
  //  these methods are inherited from the MScalar template class
  //

  // method: operator=
  //
  ComplexFloat& operator= (const ComplexFloat& arg) {
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
    return MComplexScalar<float32, float32>::read(sof, tag, name);
  }

  // method: write
  //
  bool8 write(Sof& sof, int32 tag, const String& name = CLASS_NAME) const {
    return MComplexScalar<float32, float32>::write(sof, tag, name);
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

  // method: constructor
  //
  ComplexFloat(float32 real, float32 imag = 0) {
    assign(complexfloat(real, imag));
  }

  // method: constructor
  //
  ComplexFloat(const unichar* arg) {
    assign(String(arg));
  }

  // method: operator complexdouble()
  //
  operator complexdouble() const {
    return (complexdouble)value_d;
  }

  // method: operator complexlong()
  //
  operator complexlong() const {
    return (complexlong)value_d;
  }

  complexfloat bor(complexfloat arg) {
    return (complexfloat) 0;
  }
  complexfloat bor(complexfloat arg0, complexfloat arg1) {
    return (complexfloat) 0;
  }

  complexfloat band(complexfloat arg) {
    return (complexfloat) 0;
  }
  complexfloat band(complexfloat arg0, complexfloat arg1) {
    return (complexfloat) 0;
  }

  complexfloat bxor(complexfloat arg) {
    return (complexfloat) 0;
  }
  complexfloat bxor(complexfloat arg0, complexfloat arg1) {
    return (complexfloat) 0;
  }

  complexfloat brs(complexfloat arg) {
    return (complexfloat) 0;
  }
  complexfloat brs(complexfloat arg0, complexfloat arg1) {
    return (complexfloat) 0;
  }

  complexfloat bls(complexfloat arg) {
    return (complexfloat) 0;
  }
  complexfloat bls(complexfloat arg0, complexfloat arg1) {
    return (complexfloat) 0;
  }

  complexfloat bcmpl(complexfloat arg) {
    return (complexfloat) 0;
  }
  complexfloat bcmpl(complexfloat arg0, complexfloat arg1) {
    return (complexfloat) 0;
  }

  complexfloat mod(complexfloat arg) {
    return (complexfloat) 0;
  }
  complexfloat mod(complexfloat arg0, complexfloat arg1) {
    return (complexfloat) 0;
  }

  complexfloat abs() {
    return (complexfloat) 0;
  }
  complexfloat abs(complexfloat arg0) {
    return (complexfloat) 0;
  }

  //---------------------------------------------------------------------------
  //
  // private methods
  //
  //---------------------------------------------------------------------------
private:
};

// end of include file
//
#endif
