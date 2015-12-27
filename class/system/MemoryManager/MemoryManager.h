// file: $isip/class/system/MemoryManager/MemoryManager.h
// version: $Id: MemoryManager.h 5554 2000-11-17 19:25:57Z duncan $
//

// make sure definitions are only made once
//
#ifndef ISIP_MEMORY_MANAGER
#define ISIP_MEMORY_MANAGER

// isip include files
//
#ifndef ISIP_INTEGRAL
#include <Integral.h>
#endif

#define ISIP_INTERNAL_USE_ONLY
#ifndef ISIP_MEMORY_NODE
#include <MemoryNode.h>
#endif

#ifndef ISIP_MEMORY_MANAGER_BASE
#include <MemoryManagerBase.h>
#endif
#undef ISIP_INTERNAL_USE_ONLY

#ifndef ISIP_ERROR
#include <Error.h>
#endif

// MemoryManager: a class to preserve identically sized blocks of
// memory. this class increases memory efficiency when we need to
// allocate a large number of identically sized objects, such as a
// linked list.
//
class MemoryManager {
  
  //---------------------------------------------------------------------------
  //
  // public constants
  //
  //---------------------------------------------------------------------------
public:

  // define the class name
  //
 static const SysString CLASS_NAME;

  //---------------------------------------
  //
  // other important constants
  //
  //---------------------------------------
  
  // define the size of the allocation array
  //
  static const unichar ALLOC_SIZE = 32;

  // define enumerations for mode. note that the mode has to be set
  // through a compilation switch, see the documentation for details.
  //
  enum MODE {  OPTIMIZE=0,TRACK, DEF_MODE = OPTIMIZE };

  //----------------------------------------
  //
  // default values and arguments
  //
  //----------------------------------------  

  // define the default value(s) of the class data
  //
  static const int32 DEF_GROW_SIZE = MemoryManagerBase::DEF_GROW_SIZE;

  //----------------------------------------
  //
  // error codes
  //
  //----------------------------------------  

  static const int32 ERR = 1200;
  
  //---------------------------------------------------------------------------
  //
  // protected data
  //
  //---------------------------------------------------------------------------
protected:

  // a virtual pointer to either an optimized or tracking MemoryManager
  //
  MemoryManagerBase* virtual_mgr_d;
  
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
    return MemoryManagerBase::setDebug(level);
  }
   
  // method: debug
  //
  bool8 debug(const unichar* msg) const {
    return virtual_mgr_d->debug(msg);
    return true;
  }

  // destructor/constructor(s):
  //  the default and copy constructors are private
  //

  // method: destructor
  //
  ~MemoryManager() {
    delete virtual_mgr_d;
  }
  
  // assign methods:
  //  these methods are omitted because moving memory between
  //  MemoryManager objects is nonsensical
  //

  // operator= methods:
  //  these methods are omitted because moving memory between
  //  MemoryManager objects is nonsensical
  //
  
  // i/o methods:
  //  these methods are omitted because MemoryManager can not write itself to
  //  an sof file
  //

  // equality methods:
  //  these methods are omitted because they do not make sense for
  //  MemoryManager objects
  //

  // memory management methods:
  //  new and delete are omitted because memory for MemoryManager
  //  objects is not managed by the MemoryManager class. clear methods
  //  are omitted so the user is not allowed to be careless with
  //  memory.
  //

  //---------------------------------------------------------------------------
  //
  // class-specific public methods:
  //  extensions to required methods
  //
  //---------------------------------------------------------------------------

  // constructors:
  //  these two are the most commonly used constructor - you must specify
  //  element size before using the memory manager.
  //
  MemoryManager(int32 elem_size,	int32 grow_size = DEF_GROW_SIZE);

  MemoryManager(int32 elem_size, const SysString& name,
		int32 grow_size = DEF_GROW_SIZE);

  //---------------------------------------------------------------------------
  //
  // class-specific public methods:
  //  chunk memory-management methods
  //
  //---------------------------------------------------------------------------

  // method: get
  //
  void* get() {
    return virtual_mgr_d->get();
  }
  
  // method: release
  //
  bool8 release(void* ptr) {
    return virtual_mgr_d->release(ptr);
  }

  // method: getBlock
  //
  void* getBlock(int32 size) {
    return virtual_mgr_d->getBlock(size);
  }

  // method: releaseBlock
  //
  bool8 releaseBlock(void* ptr) {
    return virtual_mgr_d->releaseBlock(ptr);
  }
  
  // method: reallocateBlock
  //
  bool8 reallocateBlock(void*** ptr, int32& current_size,
				 int32 grow_size = DEF_GROW_SIZE) {
    return virtual_mgr_d->reallocateBlock(ptr, current_size,
					  grow_size);
  }

  // method: setGrow
  //
  bool8 setGrow(int32 size) {
    return virtual_mgr_d->setGrow(size);
  }

  // method: setAllocGrow
  //
  bool8 setAllocGrow(int32 size) {
    return virtual_mgr_d->setAllocGrow(size);
  }
  
  //---------------------------------------------------------------------------
  //
  // class-specific public methods:
  //  wrap operating system methods
  //
  //---------------------------------------------------------------------------

  // method: memset
  //
  static bool8 memset(void* ptr, int32 val, int32 size) {
    return MemoryManagerBase::memset(ptr, val, size);
  }

  // method: memcpy
  //
  static bool8 memcpy(void* dst, const void* src, int32  size) {
    return MemoryManagerBase::memcpy(dst, src, size);
  }

  // method: memcmp
  //
  static int32 memcmp(const void* s1, const void* s2, int32 size) {
    return ::memcmp(s1, s2, (size_t)size);
  }

  //---------------------------------------------------------------------------
  //
  // class-specific public methods:
  //  static memory-management methods
  //
  //---------------------------------------------------------------------------

  // static memory-management methods
  //
  static void* newStatic(int32 nbytes);
  static bool8 deleteStatic(void* ptr);
  static bool8 releaseStatics();

  // the cleanup method for MemoryManagers called before exiting
  //
  static bool8 releaseMgrs();
  
  //---------------------------------------------------------------------------
  //
  // private methods
  //
  //---------------------------------------------------------------------------
private:

  // constructor(s):
  //  the default and copy constructors are not needed, so they are
  //  declared as private
  //
  MemoryManager();
  MemoryManager(const MemoryManager& arg);  

  // grow methods:
  //  increase the number of free nodes
  //
  bool8 grow();

  // for diagnostic purposes we might need to change the mode,
  // but users should not be allowed to do this
  //
  bool8 setMode(MODE mode, int32 elem_size, int32 grow_size);
  
  // count node methods:
  //  count the nodes in the two lists. possibly useful for debugging
  //
  bool8 countNodes(int32& used, int32& free) const;
};

// end of include file
// 
#endif
