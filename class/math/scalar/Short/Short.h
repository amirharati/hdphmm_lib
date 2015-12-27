// file: $isip/class/math/scalar/Short/Short.h
// version: $Id: Short.h 10636 2007-01-26 22:18:09Z tm334 $
//

// make sure definitions are only made once
//
#ifndef ISIP_SHORT
#define ISIP_SHORT

// isip include files
//
#ifndef ISIP_SCALAR
#include <MScalar.h>
#endif

// Short: a class that manages a 16-bit signed integer. this class mainly
// inherits the MScalar template functionality. we only need to add Sof file
// support and memory management
//
class Short : public MScalar<int16, int16> {

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

  static const long ERR = 20700;

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
  ~Short() {}

  // method: default constructor
  //
  Short(int16 arg = DEF_VALUE) {
    value_d = arg;
  }

  // method: copy constructor
  //
  Short(const Short& arg) {
    assign(arg.value_d);
  }

  // assign methods:
  //  these methods are inherited from the MScalar template class
  //

  // method: operator=
  //
  Short& operator= (const Short& arg) {
    assign(arg);
    return *this;
  }
    
  // i/o methods:
  //  the sofSize, readData and writeData are inherited from the MScalar
  //  template class
  //

  // method: read
  //
  bool8 read(Sof& sof, long tag, const String& name = CLASS_NAME) {
    return MScalar<int16, int16>::read(sof, tag, name);
  }

  // method: write
  //
  bool8 write(Sof& sof, long tag, const String& name = CLASS_NAME) const {
    return MScalar<int16, int16>::write(sof, tag, name);
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
  static bool8 setGrowSize(long grow_size) {
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
  Short& operator= (int16 arg) {
    value_d = arg;
    return *this;
  }

  // method: operator %
  //
  int16 operator% (int16 arg) const {
    return value_d % arg;
  }

  // method: operator %=
  //
  Short& operator%= (int16 arg) {
    value_d %= arg;
    return *this;
  }

  // method: mod
  //
  int16 mod(int16 arg2) {
    return mod(value_d, arg2);
  }

  // method: mod
  //
  int16 mod(int16 arg1, int16 arg2) {
    return (value_d = arg1 % arg2);
  }

  // method: band
  //
  int16 band(int16 arg) {
    return band(value_d, arg);
  }

  // method: band
  //
  int16 band(int16 arg1, int16 arg2) {
    return (value_d = (arg1 & arg2));
  }

  // method: bor
  //
  int16 bor(int16 arg) {
    return bor(value_d, arg);
  }

  // method: bor
  //
  int16 bor(int16 arg1, int16 arg2) {
    return (value_d = (arg1 | arg2));
  }

  // method: bxor
  //
  int16 bxor(int16 arg) {
    return bxor(value_d, arg);
  }

  // method: bxor
  //
  int16 bxor(int16 arg1, int16 arg2) {
     return (value_d = (arg1 ^ arg2));
  }

  // method: brs
  //
  int16 brs(int16 incr) {
    return brs(value_d, incr);
  }

  // method: brs
  //
  int16 brs(int16 arg, int16 incr) {
    return (value_d = (arg >> incr));
  }

  // method: bls
  //
  int16 bls(int16 incr) {
    return bls(value_d, incr);
  }

  // method: bls
  //
  int16 bls(int16 arg, int16 incr) {
    return (value_d = (arg << incr));
  }

  // method: bcmpl
  //
  int16 bcmpl() {
    return bcmpl(value_d);
  }

  // method: bcmpl
  //
  int16 bcmpl(int16 arg) {
    return (value_d = (~arg));
  }

  int16 acos(int16 arg) {
    return (int16) 0;
  }
  int16 acosh(int16 arg) {
    return (int16) 0;
  }
  int16 asin(int16 arg) {
    return (int16) 0;
  }
  int16 asinh(int16 arg) {
    return (int16) 0;
  }
  int16 atan(int16 arg) {
    return (int16) 0;
  }
  int16 atanh(int16 arg) {
    return (int16) 0;
  }
  int16 cos(int16 arg) {
    return (int16) 0;
  }
  int16 cosh(int16 arg) {
    return (int16) 0;
  }
  int16 sin(int16 arg) {
    return (int16) 0;
  }
  int16 sinh(int16 arg) {
    return (int16) 0;
  }
  int16 tan(int16 arg) {
    return (int16) 0;
  }
  int16 tanh(int16 arg) {
    return (int16) 0;
  }
  int16 ceil(int16 arg) {
    return (int16) 0;
  }
  int16 rceil(int16 arg) {
    return (int16) 0;
  }
  int16 rfloor(int16 arg) {
    return (int16) 0;
  }
  int16 round(int16 arg) {
    return (int16) 0;
  }
  int16 floor(int16 arg) {
    return (int16) 0;
  }
  
  //---------------------------------------------------------------------------
  //
  // private methods
  //
  //---------------------------------------------------------------------------
private:

/*   //declare trigonometric methods as private because they cannot be */
/*   //defined for Short operations */
/*   // */
/*   short acos(short); */
/*   short acosh(short); */
/*   short asin(short); */
/*   short asinh(short); */
/*   short atan(short); */
/*   short atanh(short); */
/*   short cos(short); */
/*   short cosh(short); */
/*   short sin(short); */
/*   short sinh(short); */
/*   short tan(short); */
/*   short tanh(short); */
  
/*   //declare those methods as private which cannot be defined for */
/*   //integer numbers */
/*   //   */
/*   short ceil(short); */
/*   short rceil(short); */
/*   short rfloor(short); */
/*   short round(short); */
/*   short floor(short); */

};

// end of include file
//
#endif
