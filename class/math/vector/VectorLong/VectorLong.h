// file: $isip/class/math/vector/VectorLong/VectorLong.h
// version: $Id: VectorLong.h 7447 2001-10-31 19:44:04Z gao $
//

// make sure definitions are only made once
//
#ifndef ISIP_VECTOR_LONG
#define ISIP_VECTOR_LONG

// isip include files
//
#ifndef ISIP_MVECTOR
#include <MVector.h>
#endif

// VectorLong: this is a vector of Long objects, which inherits
// the MVector template class.
//
class VectorLong : public MVector<Long, int32> {

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
  
  static const int32 ERR = 22600;

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
    return MVector<Long, int32>::debug(name(), &message[0]);
  }
  
  // method: destructor
  //
  ~VectorLong() {}
    
  // method: default constructor
  //
  VectorLong(int32 length = DEF_LENGTH, int32 value = DEF_VALUE) {
    assign(length, value);
  }

  // method: copy constructor
  //
  VectorLong(const VectorLong& vector) {
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
  VectorLong& operator= (const VectorLong& vector) {
    assign(vector);
    return *this;
  }
  
  // i/o methods:
  //  the sofSize, readData and writeData are inherited from the MVector
  //  template class
  //

  // method: read
  //
  bool8 read(Sof& sof, int32 tag, const String& name = CLASS_NAME) {return MVector<Long, int32>::read(sof, tag, name);
  }
  
  // method: write
  //
  bool8 write(Sof& sof, int32 tag, const String& name = CLASS_NAME) {
    return MVector<Long, int32>::write(sof, tag, name);
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
  VectorLong(const String& arg, unichar delim = DEF_DELIM) {
    assign(arg, delim);
  }
  
  // method: constructor
  //  this method constructs a vector with a unichar* object
  //
  VectorLong(const unichar* arg, unichar delim = DEF_DELIM) {
    assign(arg, delim);
  }
  
  // method: operator=
  //  this method assigns a int32 value to the vector
  //
  VectorLong& operator= (int32 value) {
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
  //defined for int32  operations
  //
  int32 acos(int32);
  int32 acosh(int32);
  int32 asin(int32);
  int32 asinh(int32);
  int32 atan(int32);
  int32 atanh(int32);
  int32 cos(int32);
  int32 cosh(int32);
  int32 sin(int32);
  int32 sinh(int32);
  int32 tan(int32);
  int32 tanh(int32);

  //declare those methods as private which cannot be defined for
  //integer numbers
  //  
  int32 ceil(int32);
  int32 rceil(int32);
  int32 rfloor(int32);
  int32 round(int32);
  int32 floor(int32);
  
};

// end of include file
//
#endif
