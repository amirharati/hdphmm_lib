// file: $isip/class/math/scalar/Llong/Llong.h
// version: $Id: Llong.h 10636 2007-01-26 22:18:09Z tm334 $
//

// make sure definitions are only made once
//
#ifndef ISIP_LLONG
#define ISIP_LLONG

// isip include files
//
#ifndef ISIP_SCALAR
#include <MScalar.h>
#endif

// Llong: a class that manages a 64-bit signed integer. this class mainly
// inherits the MScalar template functionality. we only need to add Sof file
// support and memory management
//
class Llong : public MScalar<int64, int64> {

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

  static const int32 ERR = 20900;

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
  //  the serDebug method is inherited from the MScalar template class
  //
  bool8 debug(const unichar* message) const;
  
  // method: destructor
  //
  ~Llong() {}

  // method: default constructor
  //
  Llong(int64 arg = DEF_VALUE) {
    value_d = arg;
  }

  // method: copy constructor 
  //
  Llong(const Llong& arg) {
    assign(arg.value_d);
  }
  
  // assign methods:
  //  these methods are inherited from the MScalar template class
  //

  // method: operator=
  //
  Llong& operator= (const Llong& arg) {
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
    return MScalar<int64, int64>::read(sof, tag, name);
  }

  // method: write
  //
  bool8 write(Sof& sof, int32 tag, const String& name = CLASS_NAME) const {
    return MScalar<int64, int64>::write(sof, tag, name);
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
  Llong& operator= (int64 arg) {
    value_d = arg;
    return *this;
  }

  // method: operator %
  //
  int64 operator% (int64 arg) const {
    return value_d % arg;
  }

  // method: operator %=
  //
  Llong& operator%= (int64 arg) {
    value_d %= arg;
    return *this;
  }

  // method: mod
  //
  int64 mod(int64 arg2) {
    return mod(value_d, arg2);
  }

  // method: mod
  //
  int64 mod(int64 arg1, int64 arg2) {
    return (value_d = arg1 % arg2);
  }

  // method: band
  //
  int64 band(int64 arg) {
    return band(value_d, arg);
  }

  // method: band
  //
  int64 band(int64 arg1, int64 arg2) {
    return (value_d = (arg1 & arg2));
  }

  // method: bor
  //
  int64 bor(int64 arg) {
    return bor(value_d, arg);
  }

  // method: bor
  //
  int64 bor(int64 arg1, int64 arg2) {
    return (value_d = (arg1 | arg2));
  }

  // method: bxor
  //
  int64 bxor(int64 arg) {
    return bxor(value_d, arg);
  }

  // method: bxor
  //
  int64 bxor(int64 arg1, int64 arg2) {
     return (value_d = (arg1 ^ arg2));
  }

  // method: brs
  //
  int64 brs(int64 incr) {
    return brs(value_d, incr);
  }

  // method: brs
  //
  int64 brs(int64 arg, int64 incr) {
    return (value_d = (arg >> incr));
  }

  // method: bls
  //
  int64 bls(int64 incr) {
    return bls(value_d, incr);
  }

  // method: bls
  //
  int64 bls(int64 arg, int64 incr) {
    return (value_d = (arg << incr));
  }

  // method: bcmpl
  //
  int64 bcmpl() {
    return bcmpl(value_d);
  }

  // method: bcmpl
  //
  int64 bcmpl(int64 arg) {
    return (value_d = (~arg));
  }

  int64 acos(int64 arg) {
    return (int64) 0;
  }
  int64 acosh(int64 arg) {
    return (int64) 0;
  }
  int64 asin(int64 arg) {
    return (int64) 0;
  }
  int64 asinh(int64 arg) {
    return (int64) 0;
  }
  int64 atan(int64 arg) {
    return (int64) 0;
  }
  int64 atanh(int64 arg) {
    return (int64) 0;
  }
  int64 cos(int64 arg) {
    return (int64) 0;
  }
  int64 cosh(int64 arg) {
    return (int64) 0;
  }
  int64 sin(int64 arg) {
    return (int64) 0;
  }
  int64 sinh(int64 arg) {
    return (int64) 0;
  }
  int64 tan(int64 arg) {
    return (int64) 0;
  }
  int64 tanh(int64 arg) {
    return (int64) 0;
  }
  int64 ceil(int64 arg) {
    return (int64) 0;
  }
  int64 rceil(int64 arg) {
    return (int64) 0;
  }
  int64 rfloor(int64 arg) {
    return (int64) 0;
  }
  int64 round(int64 arg) {
    return (int64) 0;
  }
  int64 floor(int64 arg) {
    return (int64) 0;
  }

  //---------------------------------------------------------------------------
  //
  // private methods
  //
  //---------------------------------------------------------------------------
private:

/*   //declare trigonometric methods as private because they cannot be */
/*   //defined for Llong  operations */
/*   // */
/*   llong acos(llong); */
/*   llong acosh(llong); */
/*   llong asin(llong); */
/*   llong asinh(llong); */
/*   llong atan(llong); */
/*   llong atanh(llong); */
/*   llong cos(llong); */
/*   llong cosh(llong); */
/*   llong sin(llong); */
/*   llong sinh(llong); */
/*   llong tan(llong); */
/*   llong tanh(llong); */

/*   //declare those methods as private which cannot be defined for */
/*   //integer numbers */
/*   //   */
/*   llong ceil(llong); */
/*   llong rceil(llong); */
/*   llong rfloor(llong); */
/*   llong round(llong); */
/*   llong floor(llong); */

};

// end of include file
//
#endif
