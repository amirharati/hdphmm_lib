// file: $isip/class/math/vector/VectorUlong/VectorUlong.h
// version: $Id: VectorUlong.h 7447 2001-10-31 19:44:04Z gao $
//

// make sure definitions are only made once
//
#ifndef ISIP_VECTOR_ULONG
#define ISIP_VECTOR_ULONG

// isip include files
//
#ifndef ISIP_MVECTOR
#include <MVector.h>
#endif

// VectorUlong: this is a vector of Ulong objects, which inherits
// the MVector template class.
//
class VectorUlong : public MVector<Ulong, uint32> {

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
  
  static const int32 ERR = 22300;

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
    return MVector<Ulong, uint32>::debug(name(), &message[0]);
  }
  
  // method: destructor
  //
  ~VectorUlong() {}
    
  // method: default constructor
  //
  VectorUlong(int32 length = DEF_LENGTH, uint32 value = DEF_VALUE) {
    assign(length, value);
  }

  // method: copy constructor
  //
  VectorUlong(const VectorUlong& vector) {
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
  VectorUlong& operator= (const VectorUlong& vector) {
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
    return MVector<Ulong, uint32>::read(sof, tag, name);
  }
  
  // method: write
  //
  bool8 write(Sof& sof, int32 tag, const String& name = CLASS_NAME) {
    return MVector<Ulong, uint32>::write(sof, tag, name);
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
  static bool8 setGrowSize(long grow_size) {
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
  VectorUlong(const String& arg, unichar delim = DEF_DELIM) {
    assign(arg, delim);
  }
  
  // method: constructor
  //  this method constructs a vector with a unichar* object
  //
  VectorUlong(const unichar* arg, unichar delim = DEF_DELIM) {
    assign(arg, delim);
  }
  
  // method: operator=
  //  this method assigns a uint32 value to the vector
  //
  VectorUlong& operator= (uint32 value) {
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
  //defined for Ulong operations
  //
  uint32 acos(uint32);
  uint32 acosh(uint32);
  uint32 asin(uint32);
  uint32 asinh(uint32);
  uint32 atan(uint32);
  uint32 atanh(uint32);
  uint32 cos(uint32);
  uint32 cosh(uint32);
  uint32 sin(uint32);
  uint32 sinh(uint32);
  uint32 tan(uint32);
  uint32 tanh(uint32);
  
  //declare those methods as private which cannot be defined for
  //unsigned numbers
  //
  uint32 abs(uint32);
  uint32 neg(uint32);
  uint32 sign(uint32);

  //declare those methods as private which cannot be defined for
  //integer numbers
  //  
  uint32 ceil(uint32);
  uint32 rceil(uint32);
  uint32 rfloor(uint32);
  uint32 round(uint32);
  uint32 floor(uint32);
  
};

// end of include file
//
#endif
