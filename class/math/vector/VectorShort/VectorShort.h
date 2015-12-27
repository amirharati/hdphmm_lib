// file: $isip/class/math/vector/VectorShort/VectorShort.h
// version: $Id: VectorShort.h 7447 2001-10-31 19:44:04Z gao $
//

// make sure definitions are only made once
//
#ifndef ISIP_VECTOR_SHORT
#define ISIP_VECTOR_SHORT

// isip include files
//
#ifndef ISIP_MVECTOR
#include <MVector.h>
#endif

// VectorShort: this is a vector of Short objects, which inherits
// the MVector template class.
//
class VectorShort : public MVector<Short, int16> {

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
  
  static const int32 ERR = 22500;

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
    return MVector<Short, int16>::debug(name(), &message[0]);
  }
  
  // method: destructor
  //
  ~VectorShort() {}
    
  // method: default constructor
  //
  VectorShort(int32 length = DEF_LENGTH, int16 value = DEF_VALUE) {
    assign(length, value);
  }

  // method: copy constructor
  //
  VectorShort(const VectorShort& vector) {
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
  VectorShort& operator= (const VectorShort& vector) {
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
    return MVector<Short, int16>::read(sof, tag, name);
  }
  
  // method: write
  //
  bool8 write(Sof& sof, int32 tag, const String& name = CLASS_NAME) {
    return MVector<Short, int16>::write(sof, tag, name);
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
  VectorShort(const String& arg, unichar delim = DEF_DELIM) {
    assign(arg, delim);
  }
  
  // method: constructor
  //  this method constructs a vector with a unichar* object
  //
  VectorShort(const unichar* arg, unichar delim = DEF_DELIM) {
    assign(arg, delim);
  }
  
  // method: operator=
  //  this method assigns a int16 value to the vector
  //
  VectorShort& operator= (int16 value) {
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
  //defined for Short operations
  //
  int16 acos(int16);
  int16 acosh(int16);
  int16 asin(int16);
  int16 asinh(int16);
  int16 atan(int16);
  int16 atanh(int16);
  int16 cos(int16);
  int16 cosh(int16);
  int16 sin(int16);
  int16 sinh(int16);
  int16 tan(int16);
  int16 tanh(int16);
  
  //declare those methods as private which cannot be defined for
  //integer numbers
  //  
  int16 ceil(int16);
  int16 rceil(int16);
  int16 rfloor(int16);
  int16 round(int16);
  int16 floor(int16);

  
};

// end of include file
//
#endif
