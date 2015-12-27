// file: $isip/class/math/scalar/Ushort/Ushort.h
// version: $Id: Ushort.h 10636 2007-01-26 22:18:09Z tm334 $
//

// make sure definitions are only made once
//
#ifndef ISIP_USHORT
#define ISIP_USHORT

// isip include files
//
#ifndef ISIP_SCALAR
#include <MScalar.h>
#endif

// Ushort: a class that manages a 16-bit unsigned integer. this class mainly
// inherits the MScalar template functionality. we only need to add Sof file
// support and memory management
//
class Ushort : public MScalar<uint16, uint16> {

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

  static const int32 ERR = 20400;

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
  ~Ushort() {}

  // method: default constructor
  //
  Ushort(uint16 arg = DEF_VALUE) {
    value_d = arg;
  }

  // method: copy constructor
  //
  Ushort(const Ushort& arg) {
    assign(arg.value_d);
  }

  // assign methods:
  //  these methods are inherited from the MScalar template class
  //

  // method: operator=
  //
  Ushort& operator= (const Ushort& arg) {
    assign(arg);
    return *this;
  }
  
  // i/o methods:
  //  the sofSize, readData and writeData are inherited from the MScalar
  //  template class
  //

  // method: read
  //
  bool8 read(Sof& sof, int32 tag, const String& name = CLASS_NAME) {
    return MScalar<uint16, uint16>::read(sof, tag, name);
  }

  // method: write
  //
  bool8 write(Sof& sof, int32 tag, const String& name = CLASS_NAME) const {
    return MScalar<uint16, uint16>::write(sof, tag, name);
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

  // other memory management:
  //  these methods are inherited from the MScalar template class
  //
  
  //---------------------------------------------------------------------------
  //
  // class-specific public methods
  //
  //---------------------------------------------------------------------------

  // method: operator=
  //
  Ushort& operator= (uint16 arg) {
    value_d = arg;
    return *this;
  }

  // method: operator %
  //
  uint16 operator% (uint16 arg) const {
    return value_d % arg;
  }

  // method: operator %=
  //
  Ushort& operator%= (uint16 arg) {
    value_d %= arg;
    return *this;
  }

  // method: mod
  //
  uint16 mod(uint16 arg2) {
    return mod(value_d, arg2);
  }

  // method: mod
  //
  uint16 mod(uint16 arg1, uint16 arg2) {
    return (value_d = arg1 % arg2);
  }

  // method: band
  //
  uint16 band(uint16 arg) {
    return band(value_d, arg);
  }

  // method: band
  //
  uint16 band(uint16 arg1, uint16 arg2) {
    return (value_d = (arg1 & arg2));
  }

  // method: bor
  //
  uint16 bor(uint16 arg) {
    return bor(value_d, arg);
  }

  // method: bor
  //
  uint16 bor(uint16 arg1, uint16 arg2) {
    return (value_d = (arg1 | arg2));
  }

  // method: bxor
  //
  uint16 bxor(uint16 arg) {
    return bxor(value_d, arg);
  }

  // method: bxor
  //
  uint16 bxor(uint16 arg1, uint16 arg2) {
     return (value_d = (arg1 ^ arg2));
  }

  // method: brs
  //
  uint16 brs(uint16 incr) {
    return brs(value_d, incr);
  }

  // method: brs
  //
  uint16 brs(uint16 arg, uint16 incr) {
    return (value_d = (arg >> incr));
  }

  // method: bls
  //
  uint16 bls(uint16 incr) {
    return bls(value_d, incr);
  }

  // method: bls
  //
  uint16 bls(uint16 arg, uint16 incr) {
    return (value_d = (arg << incr));
  }

  // method: bcmpl
  //
  uint16 bcmpl() {
    return bcmpl(value_d);
  }

  // method: bcmpl
  //
  uint16 bcmpl(uint16 arg) {
    return (value_d = (~arg));
  }

  uint16 acos(uint16 arg) {
    return (uint16) 0;
  }
  uint16 acosh(uint16 arg) {
    return (uint16) 0;
  }
  uint16 asin(uint16 arg) {
    return (uint16) 0;
  }
  uint16 asinh(uint16 arg) {
    return (uint16) 0;
  }
  uint16 atan(uint16 arg) {
    return (uint16) 0;
  }
  uint16 atanh(uint16 arg) {
    return (uint16) 0;
  }
  uint16 cos(uint16 arg) {
    return (uint16) 0;
  }
  uint16 cosh(uint16 arg) {
    return (uint16) 0;
  }
  uint16 sin(uint16 arg) {
    return (uint16) 0;
  }
  uint16 sinh(uint16 arg) {
    return (uint16) 0;
  }
  uint16 tan(uint16 arg) {
    return (uint16) 0;
  }
  uint16 tanh(uint16 arg) {
    return (uint16) 0;
  }
  uint16 abs(uint16 arg) {
    return (uint16) 0;
  }
  uint16 neg(uint16 arg) {
    return (uint16) 0;
  }
  uint16 sign(uint16 arg) {
    return (uint16) 0;
  }
  uint16 ceil(uint16 arg) {
    return (uint16) 0;
  }
  uint16 rceil(uint16 arg) {
    return (uint16) 0;
  }
  uint16 rfloor(uint16 arg) {
    return (uint16) 0;
  }
  uint16 round(uint16 arg) {
    return (uint16) 0;
  }
  uint16 floor(uint16 arg) {
    return (uint16) 0;
  }
  
  //---------------------------------------------------------------------------
  //
  // private methods
  //
  //---------------------------------------------------------------------------
private:

/*   //declare trigonometric methods as private because they cannot be */
/*   //defined for Ullong operations */
/*   // */

/*   uint16 acos(ushort); */
/*   ushort acosh(ushort); */
/*   ushort asin(ushort); */
/*   ushort asinh(ushort); */
/*   ushort atan(ushort); */
/*   ushort atanh(ushort); */
/*   ushort cos(ushort); */
/*   ushort cosh(ushort); */
/*   ushort sin(ushort); */
/*   ushort sinh(ushort); */
/*   ushort tan(ushort); */
/*   ushort tanh(ushort); */
  
/*   //declare those methods as private which cannot be defined for */
/*   //unsigned numbers */
/*   // */
/*   ushort abs(ushort); */
/*   ushort neg(ushort); */
/*   ushort sign(ushort); */

/*   //declare those methods as private which cannot be defined for */
/*   //integer numbers */
/*   //   */
/*   ushort ceil(ushort); */
/*   ushort rceil(ushort); */
/*   ushort rfloor(ushort); */
/*   ushort round(ushort); */
/*   ushort floor(ushort); */

};

// end of include file
//
#endif
