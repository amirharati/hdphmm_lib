// file: $isip/class/math/scalar/ComplexDouble/ComplexDouble.h
// version: $Id: ComplexDouble.h 10675 2009-07-21 01:13:30Z tm334 $
//

// make sure definitions are only made once
//
#ifndef ISIP_COMPLEX_DOUBLE
#define ISIP_COMPLEX_DOUBLE

// isip include files
//
#ifndef ISIP_MCOMPLEX_SCALAR
#include <MComplexScalar.h>
#endif

// ComplexDouble: a class that manages a complex number for which
// each component is a 64-bit floating point number. this class largely
// inherits the MScalarComplex and MScalar template functionality.
//
class ComplexDouble : public MComplexScalar<float64, float64> {

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

  static const int32 ERR = 21400;

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
  ~ComplexDouble() {}
  
  // method: default constructor
  //
  ComplexDouble(complexdouble arg = DEF_VALUE) {
    value_d = arg;
  }

  // method: copy constructor
  //
  ComplexDouble(const ComplexDouble& arg) {
    assign(arg.value_d);
  }

  // assign methods:
  //  these methods are inherited from the MScalar template class
  //

  // method: operator=
  //
  ComplexDouble& operator= (const ComplexDouble& arg) {
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
    return MComplexScalar<float64, float64>::read(sof, tag, name);
  }

  // method: write
  //
  bool8 write(Sof& sof, int32 tag, const String& name = CLASS_NAME) const {
    return MComplexScalar<float64, float64>::write(sof, tag, name);
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
  ComplexDouble(float64 real, float64 imag = 0) {
    assign(complexdouble(real, imag));
  }

  // method: constructor
  //
  ComplexDouble(const unichar* arg) {
    assign(String(arg));
  }

  // method: operator complexfloat()
  //
  operator complexfloat() const {
    return (complexfloat)value_d;
  }

  // method: operator complexlong()
  //
  operator complexlong() const {
    return (complexlong)value_d;
  }

  complexdouble bor(complexdouble arg) {
    return (complexdouble) 0;
  }
  complexdouble bor(complexdouble arg0, complexdouble arg1) {
    return (complexdouble) 0;
  }

  complexdouble band(complexdouble arg) {
    return (complexdouble) 0;
  }
  complexdouble band(complexdouble arg0, complexdouble arg1) {
    return (complexdouble) 0;
  }

  complexdouble bxor(complexdouble arg) {
    return (complexdouble) 0;
  }
  complexdouble bxor(complexdouble arg0, complexdouble arg1) {
    return (complexdouble) 0;
  }

  complexdouble brs(complexdouble arg) {
    return (complexdouble) 0;
  }
  complexdouble brs(complexdouble arg0, complexdouble arg1) {
    return (complexdouble) 0;
  }

  complexdouble bls(complexdouble arg) {
    return (complexdouble) 0;
  }
  complexdouble bls(complexdouble arg0, complexdouble arg1) {
    return (complexdouble) 0;
  }

  complexdouble bcmpl(complexdouble arg) {
    return (complexdouble) 0;
  }
  complexdouble bcmpl(complexdouble arg0, complexdouble arg1) {
    return (complexdouble) 0;
  }

  complexdouble mod(complexdouble arg) {
    return (complexdouble) 0;
  }
  complexdouble mod(complexdouble arg0, complexdouble arg1) {
    return (complexdouble) 0;
  }

  complexdouble abs() {
    return (complexdouble) 0;
  }
  complexdouble abs(complexdouble arg0) {
    return (complexdouble) 0;
  }

  //---------------------------------------------------------------------------
  //
  // private methods
  //
  //---------------------------------------------------------------------------
private:

/*   // declare bitwise methods as private member functions because they */
/*   // are not defined for floating point operations */
/*   // */
/*   using MScalar<complexdouble, float64>::bor; */
/*   using MScalar<complexdouble, float64>::band; */
/*   using MScalar<complexdouble, float64>::bxor; */
/*   using MScalar<complexdouble, float64>::brs; */
/*   using MScalar<complexdouble, float64>::bls; */
/*   using MScalar<complexdouble, float64>::bcmpl; */

/*   // declare modulus methods as private member functions because they */
/*   // are not defined for floating point operations */
/*   // */
/*   using MScalar<complexdouble, float64>::operator%=; */
/*   using MScalar<complexdouble, float64>::mod; */

};

// end of include file
//
#endif
