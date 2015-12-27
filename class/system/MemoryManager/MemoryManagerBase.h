// file: $isip/class/system/MemoryManager/MemoryManagerBase.h
// version: $Id: MemoryManagerBase.h 5554 2000-11-17 19:25:57Z duncan $
//

// this file is for internal use only
//
#ifdef ISIP_INTERNAL_USE_ONLY

// make sure definitions are only made once
//
#ifndef ISIP_MEMORY_MANAGER_BASE
#define ISIP_MEMORY_MANAGER_BASE

// isip include files
//
#ifndef ISIP_INTEGRAL
#include <Integral.h>
#endif

// system include files
//
#include <memory.h>

// MemoryManagerBase: a class that defines the interface contract for
// the two MemoryManager classes, which are designed essentially to
// preserve identically sized blocks of memory.
//
class MemoryManagerBase {
  
  //---------------------------------------------------------------------------
  //
  // public constants
  //
  //---------------------------------------------------------------------------
public:

  //---------------------------------------
  //
  // other important constants
  //
  //---------------------------------------
  
  //----------------------------------------
  //
  // default values and arguments
  //
  //----------------------------------------  

  // define the default value(s) of the class data
  //
  static const int32 DEF_GROW_SIZE = 1024;

  //----------------------------------------
  //
  // error codes
  //
  //----------------------------------------
  
  //---------------------------------------------------------------------------
  //
  // protected data
  //
  //---------------------------------------------------------------------------
protected:

  // debugging parameters
  //
  static Integral::DEBUG debug_level_d;

public:
  //---------------------------------------------------------------------------
  //
  // required public methods
  //
  //---------------------------------------------------------------------------

  // method: name
  //  not required for this class
  //

  // other static methods:
  //  not required for this class
  //

  // method: setDebug
  //
  static bool8 setDebug(Integral::DEBUG level) {
    debug_level_d = level;
    return true;
  }

  // other debug methods
  //
  virtual bool8 debug(const unichar* msg) const = 0;
  
  // destructor/constructor(s)
  //
  virtual ~MemoryManagerBase() {}

  // assign methods:
  //  these methods are omitted because MemoryManagerBase objects
  //  can not be instantiated
  //

  // operator= methods:
  //  these methods are omitted because MemoryManagerBase objects
  //  can not be instantiated
  //
  
  // i/o methods:
  //  i/o methods are omitted because MemoryManagerBase can not write
  //  itself to an sof file
  //

  // equality methods:
  //  these methods are omitted because MemoryManagerBase objects
  //  can not be instantiated
  //

  // memory management methods:
  //  these methods are omitted because MemoryManagerBase objects
  //  can not be instantiated
  //

  //---------------------------------------------------------------------------
  //
  // class-specific public methods
  //  block-oriented memory-management methods
  //
  //---------------------------------------------------------------------------
  
  // get and release methods:
  //  get method gives the user a new chunk of memory and the release
  //  method releases a chunk of memory
  //
  virtual void* get() = 0;
  virtual bool8 release(void* ptr) = 0;

  virtual void* getBlock(int32 size) = 0;
  virtual bool8 releaseBlock(void* ptr) = 0;

  // reallocate methods
  //   
  virtual bool8 reallocateBlock(void*** ptr, int32& current_size,
				  int32 grow_size = DEF_GROW_SIZE) = 0;
  
  static bool8 reallocate(void*** ptr, int32& current_size,
                            int32 grow_size = DEF_GROW_SIZE);

  // set methods
  //  
  virtual bool8 setGrow(int32 size) = 0;
  virtual bool8 setAllocGrow(int32 size) = 0;

  //---------------------------------------------------------------------------
  //
  // class-specific public methods:
  //  wrap operating system methods
  //
  //---------------------------------------------------------------------------

  // method: memset
  //  
  static bool8 memset(void* ptr, int32 val, int32 size) {
    ::memset(ptr, val, size);
    return true;
  }

  // method: memcpy
  // 
  static bool8 memcpy(void* dst, const void* src, int32 size) {
    ::memcpy(dst, src, size);
    return true;
  }

  // method: isip_malloc
  //  
  static void* isip_malloc(int32 size) {
    return malloc(size);
  }

  // method: isip_free
  //  
  static bool8 isip_free(void* ptr) {
    free(ptr);
    return true;
  }
  
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
#endif
