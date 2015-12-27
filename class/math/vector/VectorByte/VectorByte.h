// file: $isip/class/math/vector/VectorByte/VectorByte.h
// version: $Id: VectorByte.h 7446 2001-10-31 19:41:41Z gao $
//

// make sure definitions are only made once
//
#ifndef ISIP_VECTOR_BYTE
#define ISIP_VECTOR_BYTE

// isip include files
//
#ifndef ISIP_MVECTOR
#include <MVector.h>
#endif

// VectorByte: this is a vector of Byte objects, which inherits
// the MVector template class.
//
class VectorByte : public MVector<Byte, byte8> {

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
  // default values and arguments
  //
  //----------------------------------------  
  
  //----------------------------------------
  //
  // error codes
  //
  //----------------------------------------  
  
  static const int32 ERR = 22100;

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

  // method: setDebug
  //  these methods are inherited from the MVector template class
  //
  
  // method: debug
  //
  bool8 debug(const unichar* message) const {
    return MVector<Byte, byte8>::debug(name(), &message[0]);
  }
  
  // method: destructor
  //
  ~VectorByte() {}
    
  // method: default constructor
  //
  VectorByte(int32 length = DEF_LENGTH, byte8 value = DEF_VALUE) {
    assign(length, value);
  }

  // method: copy constructor
  //
  VectorByte(const VectorByte& vector) {
    assign(vector);
  }
  
  // assign methods:
  //  these methods are inherited from the MVector template class
  //

  // method: operator=
  //
  //  note that we need to have the overloaded operator '=' defined in the
  //  derived classes instead of the base template class. this is required
  //  since c++ predefines the operator '=' for any class by default
  //  and this hides any other definition of this operator in the base class
  //
  VectorByte& operator= (const VectorByte& vector) {
    assign(vector);
    return *this;
  }
  
  // i/o methods:
  //  the sofSize, readData and writeData are inherited from the MVector
  //  template class
  //

  // method: read
  //
  bool8 read(Sof& sof, int32 tag, const String& name = CLASS_NAME) {
    return MVector<Byte, byte8>::read(sof, tag, name);
  }
  
  // method: write
  //
  bool8 write(Sof& sof, int32 tag, const String& name = CLASS_NAME) {
    return MVector<Byte, byte8>::write(sof, tag, name);
  }    

  // equality methods:
  //  these methods are inherited from the MVector template class
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
  //  the clear method is inherited from the MVector template class
  // 

  //---------------------------------------------------------------------------
  //
  // class-specific public methods
  //
  //---------------------------------------------------------------------------
public:
  
  // method: constructor
  //  this method constructs a vector with a String* object
  //
  VectorByte(const String& arg, unichar delim = DEF_DELIM) {
    assign(arg, delim);
  }
  
  // method: constructor
  //  this method constructs a vector with a unichar* object
  //
  VectorByte(const unichar* arg, unichar delim = DEF_DELIM) {
    assign(arg, delim);
  }
  
  // method: operator=
  //  this method assigns a byte value to the vector
  //
  VectorByte& operator= (byte8 value) {
    assign(value);
    return *this;
  }

  //---------------------------------------------------------------------------
  //
  // private methods
  //
  //---------------------------------------------------------------------------
private:
  //declare trigonometric methods as private because they cannot be
  //defined for byte8 operations
  //
  byte8 acos(byte8);
  byte8 acosh(byte8);
  byte8 asin(byte8);
  byte8 asinh(byte8);
  byte8 atan(byte8);
  byte8 atanh(byte8);
  byte8 cos(byte8);
  byte8 cosh(byte8);
  byte8 sin(byte8);
  byte8 sinh(byte8);
  byte8 tan(byte8);
  byte8 tanh(byte8);
  
  //declare those methods as private which cannot be defined for
  //unsigned numbers
  //
  byte8 abs(byte8);
  byte8 neg(byte8);
  byte8 sign(byte8);

  //declare those methods as private which cannot be defined for
  //integer numbers
  //  
  byte8 ceil(byte8);
  byte8 rceil(byte8);
  byte8 rfloor(byte8);
  byte8 round(byte8);
  byte8 floor(byte8);

  
};

// end of include file
//
#endif
