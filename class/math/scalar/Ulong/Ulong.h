// file: $isip/class/math/scalar/Ulong/Ulong.h
// version: $Id: Ulong.h 10636 2007-01-26 22:18:09Z tm334 $
//

// make sure definitions are only made once
//
#ifndef ISIP_ULONG
#define ISIP_ULONG

// isip include files
//
#ifndef ISIP_SCALAR
#include <MScalar.h>
#endif

// Ulong: a class that manages a 32-bit unsigned integer. this class mainly
// inherits the MScalar template functionality. we only need to add Sof file
// support and memory management
//
class Ulong : public MScalar<uint32, uint32> {

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

  static const int32 ERR = 20500;

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
  ~Ulong() {}
  
  // method: default constructor
  //
  Ulong(uint32 arg = DEF_VALUE) {
    value_d = arg;
  }

  // method: copy constructor
  //
  Ulong(const Ulong& arg) {
    assign(arg.value_d);
  }

  // assign methods:
  //  these methods are inherited from the MScalar template class
  //

  // method: operator=
  //
  Ulong& operator= (const Ulong& arg) {
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
    return MScalar<uint32, uint32>::read(sof, tag, name);
  }

  // method: write
  //
  bool8 write(Sof& sof, int32 tag, const String& name = CLASS_NAME) const {
    return MScalar<uint32, uint32>::write(sof, tag, name);
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
public:
  
  // method: operator=
  //
  Ulong& operator= (uint32 arg) {
    value_d = arg;
    return *this;
  }

  // method: operator %
  //
  uint32 operator% (uint32 arg) const {
    return value_d % arg;
  }

  // method: operator %=
  //
  Ulong& operator%= (uint32 arg) {
    value_d %= arg;
    return *this;
  }

  // method: mod
  //
  uint32 mod(uint32 arg2) {
    return mod(value_d, arg2);
  }

  // method: mod
  //
  uint32 mod(uint32 arg1, uint32 arg2) {
    return (value_d = arg1 % arg2);
  }

  // method: band
  //
  uint32 band(uint32 arg) {
    return band(value_d, arg);
  }

  // method: band
  //
  uint32 band(uint32 arg1, uint32 arg2) {
    return (value_d = (arg1 & arg2));
  }

  // method: bor
  //
  uint32 bor(uint32 arg) {
    return bor(value_d, arg);
  }

  // method: bor
  //
  uint32 bor(uint32 arg1, uint32 arg2) {
    return (value_d = (arg1 | arg2));
  }

  // method: bxor
  //
  uint32 bxor(uint32 arg) {
    return bxor(value_d, arg);
  }

  // method: bxor
  //
  uint32 bxor(uint32 arg1, uint32 arg2) {
     return (value_d = (arg1 ^ arg2));
  }

  // method: brs
  //
  uint32 brs(uint32 incr) {
    return brs(value_d, incr);
  }

  // method: brs
  //
  uint32 brs(uint32 arg, uint32 incr) {
    return (value_d = (arg >> incr));
  }

  // method: bls
  //
  uint32 bls(uint32 incr) {
    return bls(value_d, incr);
  }

  // method: bls
  //
  uint32 bls(uint32 arg, uint32 incr) {
    return (value_d = (arg << incr));
  }

  // method: bcmpl
  //
  uint32 bcmpl() {
    return bcmpl(value_d);
  }

  // method: bcmpl
  //
  uint32 bcmpl(uint32 arg) {
    return (value_d = (~arg));
  }

  uint32 acos(uint32 arg) {
    return (uint32) 0;
  }
  uint32 acosh(uint32 arg) {
    return (uint32) 0;
  }
  uint32 asin(uint32 arg) {
    return (uint32) 0;
  }
  uint32 asinh(uint32 arg) {
    return (uint32) 0;
  }
  uint32 atan(uint32 arg) {
    return (uint32) 0;
  }
  uint32 atanh(uint32 arg) {
    return (uint32) 0;
  }
  uint32 cos(uint32 arg) {
    return (uint32) 0;
  }
  uint32 cosh(uint32 arg) {
    return (uint32) 0;
  }
  uint32 sin(uint32 arg) {
    return (uint32) 0;
  }
  uint32 sinh(uint32 arg) {
    return (uint32) 0;
  }
  uint32 tan(uint32 arg) {
    return (uint32) 0;
  }
  uint32 tanh(uint32 arg) {
    return (uint32) 0;
  }
  uint32 abs(uint32 arg) {
    return (uint32) 0;
  }
  uint32 neg(uint32 arg) {
    return (uint32) 0;
  }
  uint32 sign(uint32 arg) {
    return (uint32) 0;
  }
  uint32 ceil(uint32 arg) {
    return (uint32) 0;
  }
  uint32 rceil(uint32 arg) {
    return (uint32) 0;
  }
  uint32 rfloor(uint32 arg) {
    return (uint32) 0;
  }
  uint32 round(uint32 arg) {
    return (uint32) 0;
  }
  uint32 floor(uint32 arg) {
    return (uint32) 0;
  }

  //---------------------------------------------------------------------------
  //
  // private methods
  //
  //---------------------------------------------------------------------------
private:

/*   //declare trigonometric methods as private because they cannot be */
/*   //defined for Ulong operations */
/*   // */
/*   ulong acos(ulong); */
/*   ulong acosh(ulong); */
/*   ulong asin(ulong); */
/*   ulong asinh(ulong); */
/*   ulong atan(ulong); */
/*   ulong atanh(ulong); */
/*   ulong cos(ulong); */
/*   ulong cosh(ulong); */
/*   ulong sin(ulong); */
/*   ulong sinh(ulong); */
/*   ulong tan(ulong); */
/*   ulong tanh(ulong); */
  
/*   //declare those methods as private which cannot be defined for */
/*   //unsigned numbers */
/*   // */
/*   ulong abs(ulong); */
/*   ulong neg(ulong); */
/*   ulong sign(ulong); */

/*   //declare those methods as private which cannot be defined for */
/*   //integer numbers */
/*   //   */
/*   ulong ceil(ulong); */
/*   ulong rceil(ulong); */
/*   ulong rfloor(ulong); */
/*   ulong round(ulong); */
/*   ulong floor(ulong); */
 
};

// end of include file
//
#endif
