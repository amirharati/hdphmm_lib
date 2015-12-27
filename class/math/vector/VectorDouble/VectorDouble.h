// file: $isip/class/math/vector/VectorDouble/VectorDouble.h
// version: $Id: VectorDouble.h 7446 2001-10-31 19:41:41Z gao $
//

// make sure definitions are only made once
//
#ifndef ISIP_VECTOR_DOUBLE
#define ISIP_VECTOR_DOUBLE

// isip include files
//
#ifndef ISIP_MVECTOR
#include <MVector.h>
#endif

// VectorDouble: this is a vector of Double objects, which inherits
// the MVector template class.
//
class VectorDouble : public MVector<Double, float64> {

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
  
  static const int32 ERR = 22900;

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
    return MVector<Double, float64>::debug(name(), &message[0]);
  }
  
  // method: destructor
  //
  ~VectorDouble() {}
    
  // method: default constructor
  //
  VectorDouble(int32 length = DEF_LENGTH, float64 value = DEF_VALUE) {
    assign(length, value);
  }

  // method: copy constructor
  //
  VectorDouble(const VectorDouble& vector) {
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
  VectorDouble& operator= (const VectorDouble& vector) {
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
    return MVector<Double, float64>::read(sof, tag, name);
  }
  
  // method: write
  //
  bool8 write(Sof& sof, int32 tag, const String& name = CLASS_NAME) {
    return MVector<Double, float64>::write(sof, tag, name);
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
  VectorDouble(const String& arg, unichar delim = DEF_DELIM) {
    assign(arg, delim);
  }
  
  // method: constructor
  //  this method constructs a vector with a unichar* object
  //
  VectorDouble(const unichar* arg, unichar delim = DEF_DELIM) {
    assign(arg, delim);
  }
  
  // method: operator=
  //  this method assigns a float64 value to the vector
  //
  VectorDouble& operator= (float64 value) {
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
  float64 bor(float64, float64);
  float64 band(float64, float64);
  float64 bxor(float64, float64);
  float64 brs(float64, float64);
  float64 bls(float64, float64);
  float64 bcmpl(float64);

  // declare modulus methods as private member functions because they
  // are not defined for floating point operations
  //
  float64 mod(float64, float64);
  float64& operator%= (float64);
  float64& operator% (float64);

};

// end of include file
//
#endif
