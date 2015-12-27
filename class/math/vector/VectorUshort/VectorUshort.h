// file: $isip/class/math/vector/VectorUshort/VectorUshort.h
// version: $Id: VectorUshort.h 7447 2001-10-31 19:44:04Z gao $
//

// make sure definitions are only made once
//
#ifndef ISIP_VECTOR_USHORT
#define ISIP_VECTOR_USHORT

// isip include files
//
#ifndef ISIP_MVECTOR
#include <MVector.h>
#endif

// VectorUshort: this is a vector of Ushort objects, which inherits
// the MVector template class.
//
class VectorUshort : public MVector<Ushort, uint16> {

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
  
  static const int32 ERR = 22200;

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
    return MVector<Ushort, uint16>::debug(name(), &message[0]);
  }
  
  // method: destructor
  //
  ~VectorUshort() {}
    
  // method: default constructor
  //
  VectorUshort(int32 length = DEF_LENGTH, uint16 value = DEF_VALUE) {
    assign(length, value);
  }

  // method: copy constructor
  //
  VectorUshort(const VectorUshort& vector) {
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
  VectorUshort& operator= (const VectorUshort& vector) {
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
    return MVector<Ushort, uint16>::read(sof, tag, name);
  }
  
  // method: write
  //
  bool8 write(Sof& sof, int32 tag, const String& name = CLASS_NAME) {
    return MVector<Ushort, uint16>::write(sof, tag, name);
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
  VectorUshort(const String& arg, unichar delim = DEF_DELIM) {
    assign(arg, delim);
  }
  
  // method: constructor
  //  this method constructs a vector with a unichar* object
  //
  VectorUshort(const unichar* arg, unichar delim = DEF_DELIM) {
    assign(arg, delim);
  }
  
  // method: operator=
  //  this method assigns a uint16 value to the vector
  //
  VectorUshort& operator= (uint16 value) {
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
  //defined for Ushort
  //

  uint16 acos(uint16);
  uint16 acosh(uint16);
  uint16 asin(uint16);
  uint16 asinh(uint16);
  uint16 atan(uint16);
  uint16 atanh(uint16);
  uint16 cos(uint16);
  uint16 cosh(uint16);
  uint16 sin(uint16);
  uint16 sinh(uint16);
  uint16 tan(uint16);
  uint16 tanh(uint16);
  
  //declare those methods as private which cannot be defined for
  //unsigned numbers
  //
  uint16 abs(uint16);
  uint16 neg(uint16);
  uint16 sign(uint16);

  //declare those methods as private which cannot be defined for
  //integer numbers
  //  
  uint16 ceil(uint16);
  uint16 rceil(uint16);
  uint16 rfloor(uint16);
  uint16 round(uint16);
  uint16 floor(uint16); 
  
};

// end of include file
//
#endif
