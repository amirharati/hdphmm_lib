// file: $isip/class/system/MemoryManager/MemoryManagerTrack.h
// version: $Id: MemoryManagerTrack.h 6099 2000-12-28 16:25:04Z hamaker $
//

// this file is for internal use only
//
#ifdef ISIP_INTERNAL_USE_ONLY

// make sure definitions are only made once
//
#ifndef ISIP_MEMORY_MANAGER_TRACK
#define ISIP_MEMORY_MANAGER_TRACK

// isip include files
//
#ifndef ISIP_MEMORY_MANAGER_BASE
#include "MemoryManagerBase.h"
#endif

#ifndef ISIP_INTEGRAL
#include <Integral.h>
#endif

#ifndef ISIP_SYS_STRING
#include <SysString.h>
#endif

#ifndef ISIP_SYSHEAP
#include <SysHeap.h>
#endif

#ifndef ISIP_MEMORY_NODE
#include <MemoryNode.h>
#endif

#ifndef ISIP_ERROR
#include <Error.h>
#endif

// MemoryManagerTrack: this supports TRACK mode of MemoryManager and
// is designed for the internal use only. this class is used for
// debugging purposes when we need to track what happens to the memory
// as it is allocated and deleted. it is not time efficient.
//
class MemoryManagerTrack : public MemoryManagerBase {
  
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

  static const int32 ERR_NOTFND = 1201;
  static const int32 ERR_NOTEMP = 1202;

  //---------------------------------------------------------------------------
  //
  // protected data
  //
  //---------------------------------------------------------------------------
protected:

  // heap of used memory blocks
  //
  SysHeap used_d;

  // linked lists of memory blocks
  //
  MemoryNode free_d;
  MemoryNode used_nodes_d;
  
  // size of memory blocks
  //
  /* Could it be  a  problem? by amir*/  
  int32 size_d;

  // allocation parameter
  //
  int32 grow_size_d;
  
  // heap of actual memory handles allocated
  //
  SysHeap allocated_d;
  
  // heap of actual block memory handles allocated
  //
  SysHeap block_allocated_d;

  // a name used for reporting errors
  //
  SysString name_d;

  // a static list of all tracking memory managers. note that this is
  // a pointer instead of an object so that we can control when it is
  // allocated or deleted, if not some static objects may be created
  // before it.
  //
  static SysHeap* allocated_mgrs_d;
  
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

  // the setDebug is inherited from base class
  //
  
  // other debug methods
  //
  bool8 debug(const unichar* message) const;
   
  // destructor/constructor(s):
  //  the default and copy constructors are private
  //
  ~MemoryManagerTrack();
  
  // assign methods:
  //  these methods are omitted because moving memory between
  //  MemoryManagerTrack objects is nonsensical
  //

  // operator= methods:
  //  these methods are omitted because moving memory between
  //  MemoryManagerTrack objects is nonsensical
  //

  // i/o methods:
  //  these methods are omitted because MemoryManagerTrack can not write
  //  itself to an sof file
  //

  // equality methods:
  //  these methods are omitted because they do not make sense for
  //  MemoryManagerTrack objects
  //

  // memory management methods:
  //  new and delete are omitted because
  //  memory for MemoryManagerTrack objects is not managed by the
  //  MemoryManagerTrack class.

  // the clear method releases internal memory and carefully accounts
  // for all memory managed by this object, erroring if a problem is
  // found.
  //
  bool8 clear(Integral::CMODE mode = Integral::DEF_CMODE);

  //---------------------------------------------------------------------------
  //
  // class-specific public methods
  //  extensions to required methods  
  //
  //---------------------------------------------------------------------------
  
  // constructors:
  //  these are the most commonly used constructor - you must specify element
  //  size before using the memory manager.
  //
  MemoryManagerTrack(int32 elem_size, int32 grow_size = DEF_GROW_SIZE);
  MemoryManagerTrack(int32 elem_size, const SysString& name,
		     int32 grow_size = DEF_GROW_SIZE);

  //---------------------------------------------------------------------------
  //
  // class-specific public methods:
  //  chunk memory-management methods
  //
  //--------------------------------------------------------------------------
  
  // get and release methods:
  //  get method gives the user a new chunk of memory and release
  //  method releases a chunk of memory
  //
  void* get();
  bool8 release(void* ptr);
  
  void* getBlock(int32 size);
  bool8 releaseBlock(void* ptr);

  // reallocate methods
  //
  bool8 reallocateBlock(void*** ptr_a, int32& current_size_a,
			  int32 grow_size_a = DEF_GROW_SIZE);
  
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
    allocated_d.setGrow(size);
    return true;
  }
  
  // get methods
  //
  int32 getSize() {
    return size_d;
  }

  // method to clean up all tracking MemoryManagers
  //
  static bool8 releaseMgrs();
  
  //---------------------------------------------------------------------------
  //
  // private methods
  //
  //---------------------------------------------------------------------------
private:

  // constructor(s):
  //  the default and copy constructors are not needed, so they
  //  are declared private
  //
  MemoryManagerTrack();
  MemoryManagerTrack(const MemoryManagerTrack& arg);
  
  // grow methods:
  //  increases the number of free nodes  
  //  
  bool8 grow();

  // count node methods:
  //  count the nodes in the two lists. possibly useful for debugging
  //  
  bool8 countNodes(int32& used, int32& free) const;

  // used to display status for error conditions
  //
  bool8 display(bool8 block_mode = false);
  bool8 display(void* ptr, bool8 block_mode = false);

  // method: registerMgr
  //
  bool8 registerMgr() {
    if (allocated_mgrs_d == (SysHeap*)NULL) {
      allocated_mgrs_d = new SysHeap();
    }
    return allocated_mgrs_d->insert(this);
  }

  // method: unRegisterMgr
  //
  bool8 unRegisterMgr() {
    if (allocated_mgrs_d == (SysHeap*)NULL) {
      return Error::handle(name(), L"unRegisterMgr", Error::MEM,
			   __FILE__, __LINE__);
    }
    return allocated_mgrs_d->extract(this);
  }
};

// end of include file
// 
#endif
#endif
