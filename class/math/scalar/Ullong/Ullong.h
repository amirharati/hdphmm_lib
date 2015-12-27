// file: $isip/class/math/scalar/Ullong/Ullong.h
// version: $Id: Ullong.h 10636 2007-01-26 22:18:09Z tm334 $
//

// make sure definitions are only made once
//
#ifndef ISIP_ULLONG
#define ISIP_ULLONG

// isip include files
//
#ifndef ISIP_SCALAR
#include <MScalar.h>
#endif

// Ullong: a class manages the a 64-bit unsigned integer. this class mainly
// inherits the MScalar template functionality. we only need to add Sof file
// support and memory management
//
class Ullong : public MScalar<uint64, uint64> {

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
  // default arguments and values
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

  static const int32 ERR = 20600;

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
  ~Ullong() {}

  // method: default constructor
  //
  Ullong(uint64 arg = DEF_VALUE) {
    value_d = arg;
  }

  // method: copy constructor
  //
  Ullong(const Ullong& arg) {
    assign(arg.value_d);
  }

  // assign methods:
  //  these methods are inherited from the MScalar template class
  //

  // method: operator=
  //
  Ullong& operator= (const Ullong& arg) {
    assign(arg);
    return *this;
  }
    
  // i/o methods:
  //  the sofSize, readData, and writeData are inherited from the MScalar
  //  template class
  //

  // method: read
  //
  bool8 read(Sof& sof, int32 tag, const String& name = CLASS_NAME) {
    return MScalar<uint64, uint64>::read(sof, tag, name);
  }

  // method: write
  //
  bool8 write(Sof& sof, int32 tag, const String& name = CLASS_NAME) const {
    return MScalar<uint64, uint64>::write(sof, tag, name);
  }  

  // equality methods:
  //  the equality methods are inherited from the MScalar template class
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
  Ullong& operator= (uint64 arg) {
    value_d = arg;
    return *this;
  }

  // method: operator %
  //
  uint64 operator% (uint64 arg) const {
    return value_d % arg;
  }

  // method: operator %=
  //
  Ullong& operator%= (uint64 arg) {
    value_d %= arg;
    return *this;
  }

  // method: mod
  //
  uint64 mod(uint64 arg2) {
    return mod(value_d, arg2);
  }

  // method: mod
  //
  uint64 mod(uint64 arg1, uint64 arg2) {
    return (value_d = arg1 % arg2);
  }

  // method: band
  //
  uint64 band(uint64 arg) {
    return band(value_d, arg);
  }

  // method: band
  //
  uint64 band(uint64 arg1, uint64 arg2) {
    return (value_d = (arg1 & arg2));
  }

  // method: bor
  //
  uint64 bor(uint64 arg) {
    return bor(value_d, arg);
  }

  // method: bor
  //
  uint64 bor(uint64 arg1, uint64 arg2) {
    return (value_d = (arg1 | arg2));
  }

  // method: bxor
  //
  uint64 bxor(uint64 arg) {
    return bxor(value_d, arg);
  }

  // method: bxor
  //
  uint64 bxor(uint64 arg1, uint64 arg2) {
     return (value_d = (arg1 ^ arg2));
  }

  // method: brs
  //
  uint64 brs(uint64 incr) {
    return brs(value_d, incr);
  }

  // method: brs
  //
  uint64 brs(uint64 arg, uint64 incr) {
    return (value_d = (arg >> incr));
  }

  // method: bls
  //
  uint64 bls(uint64 incr) {
    return bls(value_d, incr);
  }

  // method: bls
  //
  uint64 bls(uint64 arg, uint64 incr) {
    return (value_d = (arg << incr));
  }

  // method: bcmpl
  //
  uint64 bcmpl() {
    return bcmpl(value_d);
  }

  // method: bcmpl
  //
  uint64 bcmpl(uint64 arg) {
    return (value_d = (~arg));
  }

  uint64 acos(uint64 arg) {
    return (uint64) 0;
  }
  uint64 acosh(uint64 arg) {
    return (uint64) 0;
  }
  uint64 asin(uint64 arg) {
    return (uint64) 0;
  }
  uint64 asinh(uint64 arg) {
    return (uint64) 0;
  }
  uint64 atan(uint64 arg) {
    return (uint64) 0;
  }
  uint64 atanh(uint64 arg) {
    return (uint64) 0;
  }
  uint64 cos(uint64 arg) {
    return (uint64) 0;
  }
  uint64 cosh(uint64 arg) {
    return (uint64) 0;
  }
  uint64 sin(uint64 arg) {
    return (uint64) 0;
  }
  uint64 sinh(uint64 arg) {
    return (uint64) 0;
  }
  uint64 tan(uint64 arg) {
    return (uint64) 0;
  }
  uint64 tanh(uint64 arg) {
    return (uint64) 0;
  }
  uint64 abs(uint64 arg) {
    return (uint64) 0;
  }
  uint64 neg(uint64 arg) {
    return (uint64) 0;
  }
  uint64 sign(uint64 arg) {
    return (uint64) 0;
  }
  uint64 ceil(uint64 arg) {
    return (uint64) 0;
  }
  uint64 rceil(uint64 arg) {
    return (uint64) 0;
  }
  uint64 rfloor(uint64 arg) {
    return (uint64) 0;
  }
  uint64 round(uint64 arg) {
    return (uint64) 0;
  }
  uint64 floor(uint64 arg) {
    return (uint64) 0;
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
/*   ullong acos(ullong); */
/*   ullong acosh(ullong); */
/*   ullong asin(ullong); */
/*   ullong asinh(ullong); */
/*   ullong atan(ullong); */
/*   ullong atanh(ullong); */
/*   ullong cos(ullong); */
/*   ullong cosh(ullong); */
/*   ullong sin(ullong); */
/*   ullong sinh(ullong); */
/*   ullong tan(ullong); */
/*   ullong tanh(ullong); */
  
/*   //declare those methods as private which cannot be defined for */
/*   //unsigned numbers */
/*   // */
/*   ullong abs(ullong); */
/*   ullong neg(ullong); */
/*   ullong sign(ullong); */

/*   //declare those methods as private which cannot be defined for */
/*   //integer numbers */
/*   //   */
/*   ullong ceil(ullong); */
/*   ullong rceil(ullong); */
/*   ullong rfloor(ullong); */
/*   ullong round(ullong); */
/*   ullong floor(ullong); */

};

// end of include file
//
#endif
