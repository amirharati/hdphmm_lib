// file: $isip/class/system/Checksum/Checksum.h
// version: $Id: Checksum.h 10642 2007-01-27 06:29:07Z tm334 $
//

// make sure definitions are only made once
//
#ifndef ISIP_CHECKSUM
#define ISIP_CHECKSUM

// isip include files:
//  note that we include SysString.h mainly for convenience
//
#ifndef ISIP_SYS_STRING
#include <SysString.h>
#endif

#ifndef ISIP_MEMORY_MANAGER
#include <MemoryManager.h>
#endif

// Checksum: a class that implements some standard checksum algorithms.
// this class is introduced at this level because it is used by Sof,
// NameMap, and other higher-level classes.
//
class Checksum {

  //---------------------------------------------------------------------------
  //
  // public constants
  //
  //---------------------------------------------------------------------------
public:
  
  // define the class name
  //
  static const SysString CLASS_NAME;
  
  // define algorithm choices
  //
  enum ALGORITHM { CRC_16_CCITT = 0, CRC_16, CRC_12, MD5,
		   DEF_ALGORITHM = CRC_16_CCITT };

  // define implementations
  //
  enum IMPLEMENTATION { FAST = 0, SLOW,
			DEF_IMPLEMENTATION = FAST };
  
  //----------------------------------------
  //
  // other important constants
  //
  //----------------------------------------

  // define an initial value for CRC
  //
  static const uint32 CRC_INITIAL_VALUE = 0;

  // define CRC polynomials
  //
  static const uint32 CRC_12_POLYNOMIAL = 05401;
  static const uint32 CRC_16_POLYNOMIAL = 0120001;
  static const uint32 CRC_16_CCITT_POLYNOMIAL = 0102010;

  // CRC checksums use a 256 length table
  //
  static const int32 CRC_TABLE_LENGTH = 256;

  //----------------------------------------
  //
  // default values and arguments
  //
  //----------------------------------------  

  // define the default value(s) of the class data
  //
  
  // default arguments to methods
  //
  
  //----------------------------------------
  //
  // error codes
  //
  //----------------------------------------  

  static const int32 ERR = 1600;
  static const int32 ERR_POLY = 1601;

  //---------------------------------------------------------------------------
  //
  // protected data
  //
  //---------------------------------------------------------------------------
protected:

  // this section contains data common to all algorithms
  //

  // algorithm name
  //
  ALGORITHM algorithm_d;
  
  // implementation name
  //
  IMPLEMENTATION implementation_d;
  
  // declare a register to hold the current checksum
  //
  uint32 cksum_d;

  // declare a static debug level for all class instantiations
  //
  static Integral::DEBUG debug_level_d;

  // static memory manager
  //
  static MemoryManager mgr_d;

  // initialization flag
  //
  bool8 is_valid_d;

  // this section contains data for a specific algorithm
  //

  // algorithm: CRC*
  // implementation: fast
  //
  // these implementations use a table lookup
  //
  uint32 crc_table_d[CRC_TABLE_LENGTH];

  //---------------------------------------------------------------------------
  //
  // required public methods
  //
  //---------------------------------------------------------------------------
public:

  // method: name
  //
  static const SysString& name() {
    return CLASS_NAME;
  }
  
  // other static methods
  //
  static bool8 diagnose(Integral::DEBUG debug_level);
  
  // method: setDebug
  //
  static bool8 setDebug(Integral::DEBUG level) {
    debug_level_d = level;
    return true;
  }
  
  // other debug methods
  //
  bool8 debug(const unichar* message) const;

  // method: destructor
  //
  ~Checksum() {}

  // method: copy constructor
  //
  Checksum(const Checksum& arg) {
    assign(arg);
  }

  // other constructor(s)
  //
  Checksum();

  // assign methods:
  //
  bool8 assign(const Checksum& arg);

  // method: operator=
  //
  Checksum& operator=(const Checksum& arg) {
    assign(arg);
    return *this;
  }
    
  // i/o methods:
  //  these methods are omitted
  //
  
  // equality methods:
  //
  bool8 eq(const Checksum& arg) const;
  
  // method: new
  //
  static void* operator new(size_t size) {
    //Added to get rid of the warning
    size_t temp;
    temp=size;
    
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

  // other memory management methods
  // 
  bool8 clear(Integral::CMODE ctype = Integral::DEF_CMODE);

  //---------------------------------------------------------------------------
  //
  // class-specific public methods:
  //  set and get methods
  //
  //---------------------------------------------------------------------------
  
  // method: setAlgorithm
  //
  bool8 setAlgorithm(ALGORITHM algorithm) {
    algorithm_d = algorithm;
    return (!(is_valid_d = false));
  }
  
  // method: setImplementation
  //
  bool8 setImplementation(IMPLEMENTATION implementation) {
    implementation_d = implementation;
    return (!(is_valid_d = false));
  }

  // method: getAlgorithm
  //
  ALGORITHM getAlgorithm() const {
    return algorithm_d;
  }

  // method: getImplementation
  //
  IMPLEMENTATION getImplementation() const {
    return implementation_d;
  }

  // method: get CRC value
  //
  uint32 get() const {
    return cksum_d;
  }

  // method: cast (uint32) conversion operator
  //  a simple way to get the checksum
  //
  operator uint32() const {
    return cksum_d;
  }

  //---------------------------------------------------------------------------
  //
  // class-specific public methods:
  //  initialization and computation methods
  //
  //---------------------------------------------------------------------------
  
  // initialization methods:
  //  these methods initialize the various class constants and reset the 
  //  internal checksum registers
  //
  bool8 init();
  
  // computational methods:
  //  these methods compute a new checksum
  //
  bool8 compute(const SysString& input);
  bool8 compute(const byte8* input, int32 nbytes);

  //---------------------------------------------------------------------------
  //
  // private methods
  //
  //---------------------------------------------------------------------------
private:

  // zero-out data in an algorithm dependent manner
  //
  bool8 reset();
  
  // algorithm-specific computation methods:
  //  these methods are shared by all CRC methods
  //
  bool8 initCrc(uint32 poly);
  bool8 computeCrcFast(const SysString& arg);
  bool8 computeCrcFast(const byte8* input, int32 nbytes);
};

// end of include file
//
#endif

