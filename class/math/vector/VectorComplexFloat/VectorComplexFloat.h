// file: $isip/class/math/vector/VectorComplexFloat/VectorComplexFloat.h
// version: $Id: VectorComplexFloat.h 10636 2007-01-26 22:18:09Z tm334 $
//

// make sure definitions are only made once
//
#ifndef ISIP_VECTOR_COMPLEX_FLOAT
#define ISIP_VECTOR_COMPLEX_FLOAT

#ifndef ISIP_MVECTOR
#include <MVector.h>
#endif

#ifndef ISIP_VECTOR_FLOAT
#include <VectorFloat.h>
#endif

// VectorComplexFloat: this is a vector of ComplexFloat objects, which
// inherits the MVector template class.
//
class VectorComplexFloat : public MVector<ComplexFloat, complexfloat> {

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
  
  static const int32 ERR = 23000;

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
    return MVector<ComplexFloat, complexfloat>::debug(name(), message);
  }
  
  // method: destructor
  //
  ~VectorComplexFloat() {}
    
  // method: default constructor
  //
  VectorComplexFloat(int32 length = DEF_LENGTH,
		     complexfloat value = DEF_VALUE) {
    assign(length, value);
  }

  // method: copy constructor
  //
  VectorComplexFloat(const VectorComplexFloat& vector) {
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
  VectorComplexFloat& operator= (const VectorComplexFloat& vector) {
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
    return MVector<ComplexFloat, complexfloat>::read(sof, tag, name);
  }
  
  // method: write
  //
  bool8 write(Sof& sof, int32 tag, const String& name = CLASS_NAME) {
    return MVector<ComplexFloat, complexfloat>::write(sof, tag, name);
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
  VectorComplexFloat(const String& arg, unichar delim = DEF_DELIM) {
    assign(arg, delim);
  }
  
  // method: constructor
  //  this method constructs a vector with a unichar* object
  //
  VectorComplexFloat(const unichar* arg, unichar delim = DEF_DELIM) {
    assign(arg, delim);
  }
  
  // method: operator=
  //  this method assigns a float value to the vector
  //
  VectorComplexFloat& operator= (complexfloat value) {
    assign(value);
    return *this;
  }

  //---------------------------------------------------------------------------
  //
  // class-specific public methods: complex functionality
  //
  //---------------------------------------------------------------------------
public:

  // method: real
  //
  bool8 real(VectorFloat& arg) const {
    arg.setLength(length_d);
    for (int32 i = (int32)length_d - 1; i >= 0; i--) {
      arg(i) = v_d[i].real();
    }
    return true;
  }

  // method: imag
  //
  bool8 imag(VectorFloat& arg) const {
    arg.setLength(length_d);
    for (int32 i = (int32)length_d - 1; i >= 0; i--) {
      arg(i) = v_d[i].imag();
    }
    return true;
  }

  // method: abs
  //
  bool8 abs(VectorFloat& arg) const {
    arg.setLength(length_d);
    for (int32 i = (int32)length_d - 1; i >= 0; i--) {
      arg(i) = v_d[i].mag();
    }
    return true;
  }

  // method: mag
  //
  bool8 mag(VectorFloat& arg) const {
    arg.setLength(length_d);
    for (int32 i = (int32)length_d - 1; i >= 0; i--) {
      arg(i) = v_d[i].mag();
    }
    return true;
  }
  
  // method: angle
  //
  bool8 angle(VectorFloat& arg) const {
    arg.setLength(length_d);
    for (int32 i = (int32)length_d - 1; i >= 0; i--) {
      arg(i) = v_d[i].angle();
    }
    return true;
  }
  
  // method: conjugate
  //
  bool8 conjugate(const VectorComplexFloat& arg) {
    setLength(arg.length_d);
    for (int32 i = (int32)(arg.length_d) - 1; i >= 0; i--) {
      v_d[i] = arg(i).conjugate();
    }
    return true;
  }

  // method: conjugate
  //
  bool8 conjugate() {
    return conjugate(*this);
  }

  // method: limitMin
  //
  template<class TIntegral>
  bool8 limitMin(TIntegral min_val) {
    return false;
  }
  
  template<class TScalar, class TIntegral>
    bool8 limitMin(TIntegral min_val, const MVector<TScalar, TIntegral>& vector) {
    return false;
  }

  //---------------------------------------------------------------------------
  //
  // private methods
  //
  //---------------------------------------------------------------------------
private:

  //declare those methods as private because they cannot be
  //defined for Complex value
  //  
  bool8 operator %(const VectorComplexFloat& vector);
  bool8 operator %=(const VectorComplexFloat& vector);
  bool8 band();
  bool8 bor();
  bool8 bxor();
  bool8 brs();
  bool8 bls();
  bool8 bcmpl();

  bool8 mod();

  bool8 centerClip();
  bool8 fraction();
  bool8 limit();
  bool8 limitMag();
  
};

// end of include file
//
#endif
