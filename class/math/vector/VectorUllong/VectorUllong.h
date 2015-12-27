// file: $isip/class/math/vector/VectorUllong/VectorUllong.h
// version: $Id: VectorUllong.h 7447 2001-10-31 19:44:04Z gao $
//

// make sure definitions are only made once
//
#ifndef ISIP_VECTOR_ULLONG
#define ISIP_VECTOR_ULLONG

// isip include files
//
#ifndef ISIP_MVECTOR
#include <MVector.h>
#endif

// VectorUllong: this is a vector of Ullong objects, which inherits
// the MVector template class.
//
class VectorUllong : public MVector<Ullong, uint64> {

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
  
  static const int32 ERR = 22400;

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
    return MVector<Ullong, uint64>::debug(name(), &message[0]);
  }
  
  // method: destructor
  //
  ~VectorUllong() {}
    
  // method: default constructor
  //
  VectorUllong(int32 length = DEF_LENGTH, uint64 value = DEF_VALUE) {
    assign(length, value);
  }

  // method: copy constructor
  //
  VectorUllong(const VectorUllong& vector) {
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
  VectorUllong& operator= (const VectorUllong& vector) {
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
    return MVector<Ullong, uint64>::read(sof, tag, name);
  }
  
  // method: write
  //
  bool8 write(Sof& sof, int32 tag, const String& name = CLASS_NAME) {
    return MVector<Ullong, uint64>::write(sof, tag, name);
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
  VectorUllong(const String& arg, unichar delim = DEF_DELIM) {
    assign(arg, delim);
  }
  
  // method: constructor
  //  this method constructs a vector with a unichar* object
  //
  VectorUllong(const unichar* arg, unichar delim = DEF_DELIM) {
    assign(arg, delim);
  }
  
  // method: operator=
  //  this method assigns a uint64 value to the vector
  //
  VectorUllong& operator= (uint64 value) {
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
  //defined for Ullong operations
  //
  uint64 acos(uint64);
  uint64 acosh(uint64);
  uint64 asin(uint64);
  uint64 asinh(uint64);
  uint64 atan(uint64);
  uint64 atanh(uint64);
  uint64 cos(uint64);
  uint64 cosh(uint64);
  uint64 sin(uint64);
  uint64 sinh(uint64);
  uint64 tan(uint64);
  uint64 tanh(uint64);
  
  //declare those methods as private which cannot be defined for
  //unsigned numbers
  //
  uint64 abs(uint64);
  uint64 neg(uint64);
  uint64 sign(uint64);

  //declare those methods as private which cannot be defined for
  //integer numbers
  //  
  uint64 ceil(uint64);
  uint64 rceil(uint64);
  uint64 rfloor(uint64);
  uint64 round(uint64);
  uint64 floor(uint64);
  
  
};

// end of include file
//
#endif
