// file: $isip/class/math/vector/VectorLlong/VectorLlong.h
// version: $Id: VectorLlong.h 7447 2001-10-31 19:44:04Z gao $
//

// make sure definitions are only made once
//
#ifndef ISIP_VECTOR_LLONG
#define ISIP_VECTOR_LLONG

// isip include files
//
#ifndef ISIP_MVECTOR
#include <MVector.h>
#endif

// VectorLlong: this is a vector of Llong objects, which inherits
// the MVector template class.
//
class VectorLlong : public MVector<Llong, int64> {

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
  
  static const int32 ERR = 22700;

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
    return MVector<Llong, int64>::debug(name(), &message[0]);
  }
  
  // method: destructor
  //
  ~VectorLlong() {}
    
  // method: default constructor
  //
  VectorLlong(int32 length = DEF_LENGTH, int64 value = DEF_VALUE) {
    assign(length, value);
  }

  // method: copy constructor
  //
  VectorLlong(const VectorLlong& vector) {
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
  VectorLlong& operator= (const VectorLlong& vector) {
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
    return MVector<Llong, int64>::read(sof, tag, name);
  }
  
  // method: write
  //
  bool8 write(Sof& sof, int32 tag, const String& name = CLASS_NAME) {
    return MVector<Llong, int64>::write(sof, tag, name);
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
  VectorLlong(const String& arg, unichar delim = DEF_DELIM) {
    assign(arg, delim);
  }
  
  // method: constructor
  //  this method constructs a vector with a unichar* object
  //
  VectorLlong(const unichar* arg, unichar delim = DEF_DELIM) {
    assign(arg, delim);
  }
  
  // method: operator=
  //  this method assigns a int64 value to the vector
  //
  VectorLlong& operator= (int64 value) {
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
  //defined for Llong  operations
  //
  int64 acos(int64);
  int64 acosh(int64);
  int64 asin(int64);
  int64 asinh(int64);
  int64 atan(int64);
  int64 atanh(int64);
  int64 cos(int64);
  int64 cosh(int64);
  int64 sin(int64);
  int64 sinh(int64);
  int64 tan(int64);
  int64 tanh(int64);

  //declare those methods as private which cannot be defined for
  //integer numbers
  //  
  int64 ceil(int64);
  int64 rceil(int64);
  int64 rfloor(int64);
  int64 round(int64);
  int64 floor(int64);
  
};

// end of include file
//
#endif
