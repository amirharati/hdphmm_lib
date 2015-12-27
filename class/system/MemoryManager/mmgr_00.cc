// file: $isip/class/system/MemoryManager/mmgr_00.cc
// version: $Id: mmgr_00.cc 5990 2000-12-18 17:50:58Z duncan $
//

// isip include files
//
#include "MemoryManager.h"
#include "MemoryManagerOptimize.h"
#include "MemoryManagerTrack.h"
#include <SysString.h>

// special isip include files
//
#define ISIP_INTERNAL_USE_ONLY
#include "MemoryManagerOptimize.h"
#include "MemoryManagerTrack.h"
#undef ISIP_INTERNAL_USE_ONLY

// method: constructor
//
// arguments:
//  int32 elem_size: (input) size of each entry
//  int32 grow_size: (input) size of each new chunk of memory
//
// return: none
//
// this is one of the most commonly used constructors for the
// MemoryManager class
//
MemoryManager::MemoryManager(int32 elem_size_a, int32 grow_size_a) {

#ifndef MEM_MGR_MODE
#error You must specify a MEM_MGR_MODE to compile this class
#endif

  // include an ident string according to mode
  //
#if defined MEM_MGR_MODE_TRACK
  static const char MemoryManager__MODE[] =
    "$MemoryManager: TRACK $";
#elif defined MEM_MGR_MODE_OPTIMIZE
  static const char MemoryManager__MODE[] =
    "$MemoryManager: OPTIMIZE $";
#else
#error bad MEM_MGR_MODE 
#endif

  MODE mode_set = MEM_MGR_MODE;

  // decide on which mode to use
  //
  if (mode_set == OPTIMIZE) {
    virtual_mgr_d = new MemoryManagerOptimize(elem_size_a, grow_size_a);
  }
  else if (mode_set == TRACK) {
    virtual_mgr_d = new MemoryManagerTrack(elem_size_a, grow_size_a);
  }

  // this test should never be true, but we have to somehow use the
  // ident string or we will get a compilation error. the efficiency
  // hit is negligible.
  //
  if (virtual_mgr_d == (MemoryManagerBase*)NULL) {
    SysString output((byte8*)MemoryManager__MODE);
    Error::handle(name(), (unichar*)output, Error::VIRTUAL_PTR,
		  __FILE__, __LINE__);
  }

  // exit gracefully
  //
}

// method: constructor
//
// arguments:
//  int32 elem_size: (input) size of each entry
//  const SysString& name: (input) name to associate with manager
//  int32 grow_size: (input) size of each new chunk of memory
//
// return: none
//
// this is one of the most commonly used constructors for the
// MemoryManager class
//
MemoryManager::MemoryManager(int32 elem_size_a, const SysString& name_a,
			     int32 grow_size_a) {

#ifndef MEM_MGR_MODE
#error You must specify a MEM_MGR_MODE to compile this class
#endif
  
  MODE mode_set = MEM_MGR_MODE;

  // decide on which mode to use
  //
  if (mode_set == OPTIMIZE) {
    virtual_mgr_d = new MemoryManagerOptimize(elem_size_a, grow_size_a);
  }
  else if (mode_set == TRACK) {
    virtual_mgr_d = new MemoryManagerTrack(elem_size_a, name_a, grow_size_a);
  }

  // exit gracefully
  //
}

// method: releaseMgrs
//
// arguments: none
//
// return: none
//
// this method calls the releaseMgrs method of the tracking memory
// manager, which will release (in a controlled way) all registered
// memory. this method is not implemented in the header file since the
// MemoryManagerTrack class is not in scope inside the header file.
//
bool8 MemoryManager::releaseMgrs() {
  return MemoryManagerTrack::releaseMgrs();
}

//-----------------------------------------------------------------------------
//
// we define non-integral constants in the default constructor
//
//-----------------------------------------------------------------------------

// constants: class name
//
const SysString MemoryManager::CLASS_NAME(L"MemoryManager");


