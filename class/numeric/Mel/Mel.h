// file: $isip/class/numeric/Mel/Mel.h
// version: $Id: Mel.h 8338 2002-07-11 03:35:34Z picone $
//

// make sure definitions are only made once
//
#ifndef ISIP_MEL
#define ISIP_MEL

// isip include files
//
#ifndef ISIP_VECTOR_FLOAT
#include <VectorFloat.h>
#endif

#ifndef ISIP_MEMORY_MANAGER
#include <MemoryManager.h>
#endif

// Mel: this class implements a function that is commonly used to map
// frequency in Hz to a scale that is more perceptually-meaningful.
// the units of this scale are referred to as mel (short for melody),
// a unit used to measure pitch.  the approximation for the Mel scale
// that is implemented in this class is given by:
//
//  mel = 2595 log10 (1 + freq / 700.0)
//
// see the Bark class for an alternate way to approximate this scale.
//
class Mel {

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

  // define constants used to approximate the mel scale
  //
  static const float32 A = 2595.0;
  static const float32 B = 1.0 / 700.0;

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
  
  static const int32 ERR = 35400;
  
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
  ~Mel() {}

  // method: default constructor
  //
  Mel() {}
  
  // method: copy constructor
  //
  Mel(const Mel& arg) {
    assign(arg);
  }

  // method: assign
  //
  bool8 assign(const Mel& arg) {
    return true;
  }
  
  // method: operator=
  //
  Mel& operator= (const Mel& copy_node) {
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
  bool8 eq(const Mel& arg) const {
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
  static bool8 compute(float32& mel, float32 freq);
  static bool8 compute(VectorFloat& mel, const VectorFloat& freq);
  
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
