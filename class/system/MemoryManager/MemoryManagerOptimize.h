// file: $isip/class/system/MemoryManager/MemoryManagerOptimize.h
// version: $Id: MemoryManagerOptimize.h 6099 2000-12-28 16:25:04Z hamaker $
//

// this file is for internal use only
//
#ifdef ISIP_INTERNAL_USE_ONLY

// make sure definitions are only made once
//
#ifndef ISIP_MEMORY_MANAGER_OPTIMIZE
#define ISIP_MEMORY_MANAGER_OPTIMIZE

// isip include files
//
#ifndef ISIP_INTEGRAL
#include <Integral.h>
#endif

#ifndef ISIP_SYSHEAP
#include <SysHeap.h>
#endif

#ifndef ISIP_MEMORY_NODE
#define ISIP_INTERNAL_USE_ONLY
#include <MemoryNode.h>
#endif

#ifndef ISIP_MEMORY_MANAGER_BASE
#include <MemoryManagerBase.h>
#endif

#ifndef ISIP_ERROR
#include <Error.h>
#endif

// MemoryManagerOptimize: this supports OPTIMIZE mode of MemoryManager
// and is designed for the internal use only. it preserves
// identically-sized blocks of memory and increases efficiency when we
// need to allocate a large number of identically-sized blocks.
//
class MemoryManagerOptimize : public MemoryManagerBase {
  
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
  
  //----------------------------------------
  //
  // default values and arguments
  //
  //----------------------------------------
  
  // define the size of the allocation array
  //
  static const unichar ALLOC_SIZE = 32;

  //----------------------------------------
  //
  // error codes
  //
  //----------------------------------------  

  static const int32 ERR = 1207;
  
  //---------------------------------------------------------------------------
  //
  // protected data
  //
  //---------------------------------------------------------------------------
protected:

  // linked lists of memory blocks
  //
  MemoryNode free_d;
  MemoryNode used_nodes_d;

  // size of memory blocks
  //
  int32 size_d;

  // allocation parameter
  //
  int32 grow_size_d;

  // heap of actual memory handles allocated
  //
   SysHeap allocated_d;  
  
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
  static bool8 diagnose(Integral::DEBUG level_a);

  // method: setDebug
  //  setDebug is inherited from base class
  
  // other debug methods
  //
  bool8 debug(const unichar* message) const;
  
  // destructor/constructor(s):
  //  the default and copy constructors are private
  //
  ~MemoryManagerOptimize();

  // assign methods:
  //  these methods are omitted because moving memory between
  //  MemoryManagerOptimize objects is nonsensical
  //

  // operator= methods:
  //  these methods are omitted because moving memory between
  //  MemoryManagerOptimize objects is nonsensical
  //
  
  // i/o methods:
  //  these methods are omitted because MemoryManagerOptimize can not write
  //  itself to an sof file
  //

  // equality methods:
  //  these methods are omitted because they do not make sense for
  //  MemoryManagerOptimize objects
  //

  // memory management methods:
  //  new and delete are omitted because memory for
  //  MemoryManagerOptimize objects is not managed by the
  //  MemoryManager class. clear methods are omitted so the user is
  //  not allowed to be careless with memory.
  //

  //---------------------------------------------------------------------------
  //
  // class-specific public methods:
  //  extensions to required methods  
  //
  //---------------------------------------------------------------------------
  
  // constructors:
  //  this is the most commonly used constructor - you must specify element
  //  size before using the memory manager.
  //
  MemoryManagerOptimize(int32 elem_size,	int32 grow_size = DEF_GROW_SIZE);

  //---------------------------------------------------------------------------
  //
  // class-specific public methods:
  //  chunk memory-management methods
  //
  //---------------------------------------------------------------------------
  
  // get and release methods:
  //  get method gives the user a new chunk of memory and release
  //  method releases a chunk of memory
  //
  void* get();
  bool8 release(void* ptr);
  
  // method: getBlock
  //
  void* getBlock(int32 size) {
    return isip_malloc(size);
  }

  // method: releaseBlock
  //
  bool8 releaseBlock(void* ptr) {
    return isip_free(ptr);
  }

  // method: reallocateBlock
  //
  bool8 reallocateBlock(void*** ptr, int32& current_size,
				 int32 grow_size = DEF_GROW_SIZE) {
    return reallocate(ptr, current_size, grow_size);
  }

  // method: setGrow
  //
  bool8 setGrow(int32 size) {
    if (size > 0) {
      grow_size_d = size;
      return true;
    }
    return Error::handle(name(), L"setGrow", Error::ARG, __FILE__, __LINE__);
  }

  // method: setAllocGrow
  //
    
  bool8 setAllocGrow(int32 size) {
    return allocated_d.setGrow(size);
  }
    
  //---------------------------------------------------------------------------
  //
  // private methods
  //
  //---------------------------------------------------------------------------
private:

  // constructor(s):
  //  the default and copy constructors are not needed, so they are
  //  declared private
  //
  MemoryManagerOptimize();
  MemoryManagerOptimize(const MemoryManagerOptimize& arg);
  
  // grow methods:
  //  increase the number of free nodes  
  //
  bool8 grow();

  // count node methods:
  //  count the nodes in the two lists. possibly useful for debugging
  //  
  bool8 countNodes(int32& used, int32& free) const;
};

// end of include file
// 
#endif
#endif
