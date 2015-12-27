// file: $isip/class/math/vector/VectorFloat/VectorFloat.h
// version: $Id: VectorFloat.h 7447 2001-10-31 19:44:04Z gao $
//

// make sure definitions are only made once
//
#ifndef ISIP_VECTOR_FLOAT
#define ISIP_VECTOR_FLOAT

// isip include files
//
#ifndef ISIP_MVECTOR
#include <MVector.h>
#endif

// VectorFloat: this is a vector of Float objects, which inherits
// the MVector template class.
//
class VectorFloat : public MVector<Float, float32> {

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
  
  static const int32 ERR = 22800;

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
    return MVector<Float, float32>::debug(name(), &message[0]);
  }
  
  // method: destructor
  //
  ~VectorFloat() {}
    
  // method: default constructor
  //
  VectorFloat(int32 length = DEF_LENGTH, float32 value = DEF_VALUE) {
    assign(length, value);
  }

  // method: copy constructor
  //
  VectorFloat(const VectorFloat& vector) {
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
  VectorFloat& operator= (const VectorFloat& vector) {
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
    return MVector<Float, float32>::read(sof, tag, name);
  }
  
  // method: write
  //
  bool8 write(Sof& sof, int32 tag, const String& name = CLASS_NAME) {
    return MVector<Float, float32>::write(sof, tag, name);
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
  VectorFloat(const String& arg, unichar delim = DEF_DELIM) {
    assign(arg, delim);
  }
  
  // method: constructor
  //  this method constructs a vector with a unichar* object
  //
  VectorFloat(const unichar* arg, unichar delim = DEF_DELIM) {
    assign(arg, delim);
  }
  
  // method: operator=
  //  this method assigns a float32 value to the vector
  //
  VectorFloat& operator= (float32 value) {
    assign(value);
    return *this;
  }

  //---------------------------------------------------------------------------
  //
  // private methods
  //
  //---------------------------------------------------------------------------
private:
  // declare bitwise methods as private member functions because they
  // are not defined for floating point operations
  //
  float32 bor(float32, float32);
  float32 band(float32, float32);
  float32 bxor(float32, float32);
  float32 brs(float32, float32);
  float32 bls(float32, float32);
  float32 bcmpl(float32);

  // declare modulus methods as private member functions because they
  // are not defined for floating point operations
  //
  float32 mod(float32, float32);
  float32& operator%= (float32);
  float32 operator% (float32);
  
};

// end of include file
//
#endif
