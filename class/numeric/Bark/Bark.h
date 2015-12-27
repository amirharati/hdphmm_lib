// file: $isip/class/numeric/Bark/Bark.h
// version: $Id: Bark.h 8338 2002-07-11 03:35:34Z picone $
//

// make sure definitions are only made once
//
#ifndef ISIP_BARK
#define ISIP_BARK

// isip include files
//
#ifndef ISIP_VECTOR_FLOAT
#include <VectorFloat.h>
#endif

#ifndef ISIP_MEMORY_MANAGER
#include <MemoryManager.h>
#endif

// Bark: this class implements a function that is commonly used
// to map frequency in Hz to a scale that is more perceptually-meaningful.
// the units of this scale are referred to as critical band rate, or Bark.
// the approximation for the Bark scale that is implemented 
// in this class is given by:
//
//  Bark = 13 atan(0.76 * freq / 1000) + 3.5 atan(freq ^ 2 / 7500 ^ 2)
//
// for more details about this transformation, see:
//
//  J. Picone, "Signal Modeling Techniques in Speech Recognition,"
//  IEEE Proceedings, vol. 81, no. 9, pp. 1215-1247, September 1993. 
//
// see the Mel class for an alternate way to approximate this scale.
//
class Bark {

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
  // other important constants
  //
  //----------------------------------------

  // function constants
  //
  static const float32 A1 = 13.0;
  static const float32 A2 = 0.76 / 1000.0;
  static const float32 B1 = 3.5;
  static const float32 B2 = 1.0 / 7500.0;

  //----------------------------------------
  //
  // i/o related constants
  //
  //----------------------------------------

  static const String DEF_PARAM;
  
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
  
  static const int32 ERR = 35300;
  
  //---------------------------------------------------------------------------
  //
  // protected data
  //
  //---------------------------------------------------------------------------
protected:
  
  // a static debug level
  //
  static Integral::DEBUG debug_level_d;
  
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
  //
  bool8 setDebug(Integral::DEBUG debug_level) {
    debug_level_d = debug_level;
    return true;
  }

  // other debug methods
  //
  bool8 debug(const unichar* msg) const;

  // method: destructor
  //
  ~Bark() {}

  // method: default constructor
  //
  Bark() {}
  
  // method: copy constructor
  //
  Bark(const Bark& arg) {
    assign(arg);
  }

  // method: assign
  //
  bool8 assign(const Bark& arg) {
    return true;
  }
  
  // method: operator=
  //
  Bark& operator= (const Bark& copy_node) {
    assign(copy_node);
    return *this;
  }
  
  // method: sofSize
  //
  int32 sofSize() const {
    return 0;
  }

  // method: read
  //
  bool8 read(Sof& sof, int32 tag, const String& name = CLASS_NAME) {
    return true;
  }

  // method: write
  //
  bool8 write(Sof& sof, int32 tag, const String& name = CLASS_NAME) const {
    return true;
  }

  // method: readData
  //
  bool8 readData(Sof& sof, const String& pname = DEF_PARAM,
                   int32 size = SofParser::FULL_OBJECT,
                   bool8 param = true,
                   bool8 nested = false) {
    return true;
  }

  // method: writeData
  //
  bool8 writeData(Sof& sof, const String& pname = DEF_PARAM) const {
    return true;
  }

  // method: eq
  //
  bool8 eq(const Bark& arg) const {
    return true;
  }
  
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

  // method: clear
  //
  bool8 clear(Integral::CMODE ctype = Integral::DEF_CMODE) {
    return true;
  }
  
  //---------------------------------------------------------------------------
  //
  // class-specific public methods:
  //  computational methods
  //
  //---------------------------------------------------------------------------
  
  // compute methods
  //
  static bool8 compute(float32& bark, float32 freq);
  static bool8 compute(VectorFloat& bark, const VectorFloat& freq);
  
  //---------------------------------------------------------------------------
  //
  // private methods
  //
  //---------------------------------------------------------------------------
private:

};

// end of include file
// 
#endif
