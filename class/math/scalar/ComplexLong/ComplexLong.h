// file: $isip/class/math/scalar/ComplexLong/ComplexLong.h
// version: $Id: ComplexLong.h 10675 2009-07-21 01:13:30Z tm334 $
//

// make sure definitions are only made once
//
#ifndef ISIP_COMPLEX_LONG
#define ISIP_COMPLEX_LONG

// isip include files
//
#ifndef ISIP_MCOMPLEX_SCALAR
#include <MComplexScalar.h>
#endif

// ComplexLong: a class that manages a complex number for which
// each component is a 32-bit integer number. this class largely
// inherits the MScalar template functionality.
//
class ComplexLong : public MComplexScalar<int32, int32> {

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
  ~ComplexLong() {}
  
  // method: default constructor
  //
  ComplexLong(complexlong arg = DEF_VALUE) {
    value_d = arg;
  }

  // method: copy constructor
  //
  ComplexLong(const ComplexLong& arg) {
    assign(arg.value_d);
  }

  // assign methods:
  //  these methods are inherited from the MComplexScalar template class
  //

  // method: operator=
  //
  ComplexLong& operator= (const ComplexLong& arg) {
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
    return MComplexScalar<int32, int32>::read(sof, tag, name);
  }

  // method: write
  //
  bool8 write(Sof& sof, int32 tag, const String& name = CLASS_NAME) const {
    return MComplexScalar<int32, int32>::write(sof, tag, name);
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
  ComplexLong(int32 real, int32 imag = 0) {
    assign(complexlong(real, imag));
  }

  // method: constructor
  //
  ComplexLong(const unichar* arg) {
    assign(String(arg));
  }

  // method: operator complexdouble()
  //
  operator complexdouble() const {
    return (complexdouble)value_d;
  }

  // method: operator complexfloat()
  //
  operator complexfloat() const {
    return (complexfloat)value_d;
  }

  complexlong bor(complexlong arg) {
    return (complexlong) 0;
  }
  complexlong bor(complexlong arg0, complexlong arg1) {
    return (complexlong) 0;
  }

  complexlong band(complexlong arg) {
    return (complexlong) 0;
  }
  complexlong band(complexlong arg0, complexlong arg1) {
    return (complexlong) 0;
  }

  complexlong bxor(complexlong arg) {
    return (complexlong) 0;
  }
  complexlong bxor(complexlong arg0, complexlong arg1) {
    return (complexlong) 0;
  }

  complexlong brs(complexlong arg) {
    return (complexlong) 0;
  }
  complexlong brs(complexlong arg0, complexlong arg1) {
    return (complexlong) 0;
  }

  complexlong bls(complexlong arg) {
    return (complexlong) 0;
  }
  complexlong bls(complexlong arg0, complexlong arg1) {
    return (complexlong) 0;
  }

  complexlong bcmpl(complexlong arg) {
    return (complexlong) 0;
  }
  complexlong bcmpl(complexlong arg0, complexlong arg1) {
    return (complexlong) 0;
  }

  complexlong mod(complexlong arg) {
    return (complexlong) 0;
  }
  complexlong mod(complexlong arg0, complexlong arg1) {
    return (complexlong) 0;
  }

  complexlong abs() {
    return (complexlong) 0;
  }
  complexlong abs(complexlong arg0) {
    return (complexlong) 0;
  }

  //---------------------------------------------------------------------------
  //
  // private methods
  //
  //---------------------------------------------------------------------------
private:

/*   // declare bitwise methods as private member functions because they */
/*   // are not defined for complex type operations */
/*   // */
/*   using MScalar<complexlong, int32>::bor; */
/*   using MScalar<complexlong, int32>::band; */
/*   using MScalar<complexlong, int32>::bxor; */
/*   using MScalar<complexlong, int32>::brs; */
/*   using MScalar<complexlong, int32>::bls; */
/*   using MScalar<complexlong, int32>::bcmpl; */

/*   // declare modulus methods as private member functions because they */
/*   // are not defined for complex type operations */
/*   // */
/*   using MScalar<complexlong, int32>::operator%=; */
/*   using MScalar<complexlong, int32>::mod; */

};

// end of include file
//
#endif
