// file: $isip/class/numeric/Chebyshev/Chebyshev.h
// version: $Id: Chebyshev.h 8338 2002-07-11 03:35:34Z picone $
//

// make sure definitions are only made once
//
#ifndef ISIP_CHEBYSHEV
#define ISIP_CHEBYSHEV

// isip include files
//
#ifndef ISIP_VECTOR_FLOAT
#include <VectorFloat.h>
#endif

#ifndef ISIP_MEMORY_MANAGER
#include <MemoryManager.h>
#endif

// Chebyshev: this class implements Chebyshev functions that are commonly
// used in signal processing. See:
//
//  S.K. Mitra, Digital Signal Processing,
//  McGraw-Hill, Boston, Massuchessetts, USA, 2001, pp. 456.
//
// All orders are currently supported.
//
class Chebyshev {

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
  
  static const int32 DEF_ORDER = 0;

  //----------------------------------------
  //
  // error codes
  //
  //----------------------------------------  
  
  static const int32 ERR = 35600;
  
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
  ~Chebyshev() {}

  // method: default constructor
  //
  Chebyshev() {}
  
  // method: copy constructor
  //
  Chebyshev(const Chebyshev& arg) {
    assign(arg);
  }

  // method: assign
  //
  bool8 assign(const Chebyshev& arg) {
    return true;
  }
  
  // method: operator=
  //
  Chebyshev& operator= (const Chebyshev& copy_node) {
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
  bool8 eq(const Chebyshev& arg) const {
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
  static bool8 compute(float32& output, float32 input, int32 order = DEF_ORDER);
  static bool8 compute(VectorFloat& output, const VectorFloat& input,
			 int32 order = DEF_ORDER);
  
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
