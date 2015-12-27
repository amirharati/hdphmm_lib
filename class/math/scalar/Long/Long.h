// file: $isip/class/math/scalar/Long/Long.h
// version: $Id: Long.h 10636 2007-01-26 22:18:09Z tm334 $
//

// make sure definitions are only made once
//
#ifndef ISIP_LONG
#define ISIP_LONG

// isip include files
//
#ifndef ISIP_SCALAR
#include <MScalar.h>
#endif

// Long: a class that manages a 32-bit signed integer. this class mainly
// inherits the MScalar template functionality. we only need to add Sof file
// support and memory management
//
class Long : public MScalar<int32, int32> {

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

  static const int32 ERR = 20800;

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
  ~Long() {}

  // method: default constructor
  //
  Long(int32 arg = DEF_VALUE) {
    value_d = arg;
  }

  // method: copy constructor
  //
  Long(const Long& arg) {
    assign(arg.value_d);
  }
  
  // assign methods:
  //  these methods are inherited from the MScalar template class
  //

  // method: operator=
  //
  Long& operator= (const Long& arg) {
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
    return MScalar<int32, int32>::read(sof, tag, name);
  }

  // method: write
  //
  bool8 write(Sof& sof, int32 tag, const String& name = CLASS_NAME) const {
    return MScalar<int32, int32>::write(sof, tag, name);
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
  Long& operator= (int32 arg) {
    value_d = arg;
    return *this;
  }

  // method: operator %
  //
  long operator% (int32 arg) const {
    return value_d % arg;
  }

  // method: operator %=
  //
  Long& operator%= (int32 arg) {
    value_d %= arg;
    return *this;
  }

  // method: mod
  //
  long mod(int32 arg2) {
    return mod(value_d, arg2);
  }

  // method: mod
  //
  int32 mod(int32 arg1, int32 arg2) {
    return (value_d = arg1 % arg2);
  }

  // method: band
  //
  int32 band(int32 arg) {
    return band(value_d, arg);
  }

  // method: band
  //
  int32 band(int32 arg1, int32 arg2) {
    return (value_d = (arg1 & arg2));
  }

  // method: bor
  //
  int32 bor(int32 arg) {
    return bor(value_d, arg);
  }

  // method: bor
  //
  int32 bor(int32 arg1, int32 arg2) {
    return (value_d = (arg1 | arg2));
  }

  // method: bxor
  //
  int32 bxor(int32 arg) {
    return bxor(value_d, arg);
  }

  // method: bxor
  //
  int32 bxor(int32 arg1, int32 arg2) {
     return (value_d = (arg1 ^ arg2));
  }

  // method: brs
  //
  int32 brs(int32 incr) {
    return brs(value_d, incr);
  }

  // method: brs
  //
  int32 brs(int32 arg, int32 incr) {
    return (value_d = (arg >> incr));
  }

  // method: bls
  //
  int32 bls(int32 incr) {
    return bls(value_d, incr);
  }

  // method: bls
  //
  int32 bls(int32 arg, int32 incr) {
    return (value_d = (arg << incr));
  }

  // method: bcmpl
  //
  int32 bcmpl() {
    return bcmpl(value_d);
  }

  // method: bcmpl
  //
  int32 bcmpl(int32 arg) {
    return (value_d = (~arg));
  }
  
  int32 acos(int32 arg) {
    return (int32) 0;
  }
  int32 acosh(int32 arg) {
    return (int32) 0;
  }
  int32 asin(int32 arg) {
    return (int32) 0;
  }
  int32 asinh(int32 arg) {
    return (int32) 0;
  }
  int32 atan(int32 arg) {
    return (int32) 0;
  }
  int32 atanh(int32 arg) {
    return (int32) 0;
  }
  int32 cos(int32 arg) {
    return (int32) 0;
  }
  int32 cosh(int32 arg) {
    return (int32) 0;
  }
  int32 sin(int32 arg) {
    return (int32) 0;
  }
  int32 sinh(int32 arg) {
    return (int32) 0;
  }
  int32 tan(int32 arg) {
    return (int32) 0;
  }
  int32 tanh(int32 arg) {
    return (int32) 0;
  }
  int32 ceil(int32 arg) {
    return (int32) 0;
  }
  int32 rceil(int32 arg) {
    return (int32) 0;
  }
  int32 rfloor(int32 arg) {
    return (int32) 0;
  }
  int32 round(int32 arg) {
    return (int32) 0;
  }
  int32 floor(int32 arg) {
    return (int32) 0;
  }

  //---------------------------------------------------------------------------
  //
  // private methods
  //
  //---------------------------------------------------------------------------
private:

/*   //declare trigonometric methods as private because they cannot be */
/*   //defined for long  operations */
/*   // */
/*   long acos(long); */
/*   long acosh(long); */
/*   long asin(long); */
/*   long asinh(long); */
/*   long atan(long); */
/*   long atanh(long); */
/*   long cos(long); */
/*   long cosh(long); */
/*   long sin(long); */
/*   long sinh(long); */
/*   long tan(long); */
/*   long tanh(long); */

/*   //declare those methods as private which cannot be defined for */
/*   //integer numbers */
/*   //   */
/*   long ceil(long); */
/*   long rceil(long); */
/*   long rfloor(long); */
/*   long round(long); */
/*   long floor(long); */

};

// end of include file
//
#endif
