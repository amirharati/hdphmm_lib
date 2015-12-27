// file: $isip/class/math/scalar/Byte/Byte.h
// version: $Id: Byte.h 10636 2007-01-26 22:18:09Z tm334 $
//

// make sure definitions are only made once
//
#ifndef ISIP_BYTE
#define ISIP_BYTE

// isip include files
//
#ifndef ISIP_SCALAR
#include <MScalar.h>
#endif

// Byte: a class that manages an 8-bit unsigned integer. this class mainly
// inherits the MScalar template functionality. we only need to add Sof file
// support and memory management
//
class Byte : public MScalar<byte8, byte8> {

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

  static const int32 ERR = 20200;
  
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
  ~Byte() {}

  // method: default constructor
  //
  Byte(byte8 arg = DEF_VALUE) {
    value_d = arg;
  }

  // method: copy constructor
  //
  Byte(const Byte& arg) {
    assign(arg.value_d);
  }

  // assign methods:
  //  these methods are inherited from the MScalar template class
  //
  
  // method: operator=
  //
  Byte& operator= (const Byte& arg) {
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
    return MScalar<byte8, byte8>::read(sof, tag, name);
  }

  // method: write
  //
  bool8 write(Sof& sof, int32 tag, const String& name = CLASS_NAME) const {
    return MScalar<byte8, byte8>::write(sof, tag, name);
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

  // other memory allocation methods:
  //  the clear method is inherited from the MScalar template class
  //
  
  //---------------------------------------------------------------------------
  //
  // class-specific public methods
  //
  //---------------------------------------------------------------------------
public:

  // method: operator=
  //
  Byte& operator= (byte8 arg) {
    value_d = arg;
    return *this;
  }

  // method: operator %
  //
  byte8 operator% (byte8 arg) const {
    return value_d % arg;
  }

  // method: operator %=
  //
  Byte& operator%= (byte8 arg) {
    value_d %= arg;
    return *this;
  }

  // method: mod
  //
  byte8 mod(byte8 arg2) {
    return mod(value_d, arg2);
  }

  // method: mod
  //
  byte8 mod(byte8 arg1, byte8 arg2) {
    return (value_d = arg1 % arg2);
  }

  // method: band
  //
  byte8 band(byte8 arg) {
    return band(value_d, arg);
  }

  // method: band
  //
  byte8 band(byte8 arg1, byte8 arg2) {
    return (value_d = (arg1 & arg2));
  }

  // method: bor
  //
  byte8 bor(byte8 arg) {
    return bor(value_d, arg);
  }

  // method: bor
  //
  byte8 bor(byte8 arg1, byte8 arg2) {
    return (value_d = (arg1 | arg2));
  }

  // method: bxor
  //
  byte8 bxor(byte8 arg) {
    return bxor(value_d, arg);
  }

  // method: bxor
  //
  byte8 bxor(byte8 arg1, byte8 arg2) {
     return (value_d = (arg1 ^ arg2));
  }

  // method: brs
  //
  byte8 brs(byte8 incr) {
    return brs(value_d, incr);
  }

  // method: brs
  //
  byte8 brs(byte8 arg, byte8 incr) {
    return (value_d = (arg >> incr));
  }

  // method: bls
  //
  byte8 bls(byte8 incr) {
    return bls(value_d, incr);
  }

  // method: bls
  //
  byte8 bls(byte8 arg, byte8 incr) {
    return (value_d = (arg << incr));
  }

  // method: bcmpl
  //
  byte8 bcmpl() {
    return bcmpl(value_d);
  }

  // method: bcmpl
  //
  byte8 bcmpl(byte8 arg) {
    return (value_d = (~arg));
  }

  byte8 acos(byte8 arg) {
    return (byte8) 0;
  }
  byte8 acosh(byte8 arg) {
    return (byte8) 0;
  }
  byte8 asin(byte8 arg) {
    return (byte8) 0;
  }
  byte8 asinh(byte8 arg) {
    return (byte8) 0;
  }
  byte8 atan(byte8 arg) {
    return (byte8) 0;
  }
  byte8 atanh(byte8 arg) {
    return (byte8) 0;
  }
  byte8 cos(byte8 arg) {
    return (byte8) 0;
  }
  byte8 cosh(byte8 arg) {
    return (byte8) 0;
  }
  byte8 sin(byte8 arg) {
    return (byte8) 0;
  }
  byte8 sinh(byte8 arg) {
    return (byte8) 0;
  }
  byte8 tan(byte8 arg) {
    return (byte8) 0;
  }
  byte8 tanh(byte8 arg) {
    return (byte8) 0;
  }
  byte8 abs(byte8 arg) {
    return (byte8) 0;
  }
  byte8 neg(byte8 arg) {
    return (byte8) 0;
  }
  byte8 sign(byte8 arg) {
    return (byte8) 0;
  }
  byte8 ceil(byte8 arg) {
    return (byte8) 0;
  }
  byte8 rceil(byte8 arg) {
    return (byte8) 0;
  }
  byte8 rfloor(byte8 arg) {
    return (byte8) 0;
  }
  byte8 round(byte8 arg) {
    return (byte8) 0;
  }
  byte8 floor(byte8 arg) {
    return (byte8) 0;
  }
  
  //---------------------------------------------------------------------------
  //
  // private methods
  //
  //---------------------------------------------------------------------------
private:

/*   //declare trigonometric methods as private because they cannot be */
/*   //defined for byte operations */
/*   // */
/*   byte acos(byte); */
/*   byte acosh(byte); */
/*   byte asin(byte); */
/*   byte asinh(byte); */
/*   byte atan(byte); */
/*   byte atanh(byte); */
/*   byte cos(byte); */
/*   byte cosh(byte); */
/*   byte sin(byte); */
/*   byte sinh(byte); */
/*   byte tan(byte); */
/*   byte tanh(byte); */
  
/*   //declare those methods as private which cannot be defined for */
/*   //unsigned numbers */
/*   // */

/*   byte abs(byte); */
/*   byte neg(byte); */
/*   byte sign(byte); */

/*   //declare those methods as private which cannot be defined for */
/*   //integer numbers */
/*   //   */
/*   byte ceil(byte); */
/*   byte rceil(byte); */
/*   byte rfloor(byte); */
/*   byte round(byte); */
/*   byte floor(byte); */

};

// end of include file
//
#endif
