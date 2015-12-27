// file: $isip/class/system/MemoryManager/mmgr_01.cc
// version: $Id: mmgr_01.cc 5486 2000-11-12 21:27:35Z duncan $
//

// isip include files
//
#include "MemoryManager.h"
#include <Console.h>
#include <SysString.h>
#include <typeinfo>

#define ISIP_INTERNAL_USE_ONLY
#include "MemoryManagerOptimize.h"
#include "MemoryManagerTrack.h"
#undef ISIP_INTERNAL_USE_ONLY

// method: diagnose
//
// arguments:
//  Integral::DEBUG level: (input) debug level for diagnostics
//
// return: a bool8 value indicating status
//
bool8 MemoryManager::diagnose(Integral::DEBUG level_a) {

  //---------------------------------------------------------------------------
  //
  // 0. preliminaries
  //
  //---------------------------------------------------------------------------

  // output the class name
  //
  if (level_a > Integral::NONE) {
    SysString output(L"diagnosing class ");
    output.concat(CLASS_NAME);
    output.concat(L": ");
    Console::put(output);
    Console::increaseIndention();
  }

  //---------------------------------------------------------------------------
  //
  // 1. required public methods
  //
  //---------------------------------------------------------------------------

  // set indentation
  //
  if (level_a > Integral::NONE) {
    Console::put(L"testing required public methods...\n");
    Console::increaseIndention();
  }
  
  // do a test of constructors and destructors
  //
  MemoryManager* ptr = new MemoryManager(4);
  delete ptr;

  // test the debug methods
  //
  MemoryManager mgr(sizeof(float32), 1024, TRACK);
  
  mgr.setDebug(Integral::BRIEF);

  if (level_a > Integral::BRIEF) {
    mgr.debug(L"debug");
  }

#ifndef PURIFY
  
  // perform full diagnostic of tracking manager
  //
  if (level_a > Integral::BRIEF) {
    Console::put(L"starting diagnostic for tracking manager");
  }

  if (!MemoryManagerTrack::diagnose(level_a)) {
    return Error::handle(name(), L"diagnose", ERR, __FILE__, __LINE__);
  }

#endif

  // perform full diagnostic of optimized manager
  //
  if (level_a > Integral::BRIEF) {
    Console::put(L"starting diagnostic for optimized manager");
  }

  if (!MemoryManagerOptimize::diagnose(level_a)) {
    return Error::handle(name(), L"diagnose", ERR, __FILE__, __LINE__);
  }

  // reset indentation
  //
  if (level_a > Integral::NONE) {
    Console::decreaseIndention();
  }
  
  //---------------------------------------------------------------------------
  //
  // 2. class-specific public methods:
  //     extensions to required methods
  //
  //--------------------------------------------------------------------------

  // set indentation
  //
  if (level_a > Integral::NONE) {
    Console::put(L"testing class-specific public methods: extensions to required methods...\n");
    Console::increaseIndention();
  }
  
  // test class-specific constructors
  //
  MemoryManager mgr_t(sizeof(float32), 1024);
  mgr_t.setMode(TRACK, sizeof(float32), 1024);
  MemoryManager mgr_o(sizeof(float32), 1024);
  mgr_o.setMode(OPTIMIZE, sizeof(float32), 1024);
  
  // reset indentation
  //
  if (level_a > Integral::NONE) {
    Console::decreaseIndention();
  }
  
  //---------------------------------------------------------------------------
  //
  // 3. class-specific public methods:
  //     chunk memory-management methods
  //
  //---------------------------------------------------------------------------

  // set indentation
  //
  if (level_a > Integral::NONE) {
    Console::put(L"testing class-specific public methods: chunk memory-management methods...\n");
    Console::increaseIndention();
  }
    
  int32 size = 1000;
  float32** ptrs_t = (float32**)mgr_t.getBlock(size * sizeof(float32*));
  float32** ptrs_o = (float32**)mgr_o.getBlock(size * sizeof(float32*));

  for (int32 i = 0; i < size; i++) {
    ptrs_t[i] = (float32*)mgr_t.get();
    ptrs_o[i] = (float32*)mgr_o.get();
  }

  for (int32 i = 0; i < size; i++) {
    mgr_t.release(ptrs_t[i]);
    mgr_o.release(ptrs_o[i]);
  }

  mgr_t.releaseBlock(ptrs_t);
  mgr_o.releaseBlock(ptrs_o);

  // reset indentation
  //
  if (level_a > Integral::NONE) {
    Console::decreaseIndention();
  }

  //---------------------------------------------------------------------------
  //
  // 4. class-specific public methods:
  //     wrap operating system methods
  //
  //--------------------------------------------------------------------------

  // set indentation
  //
  if (level_a > Integral::NONE) {
    Console::put(L"testing class-specific public methods: wrap operating system methods...\n");
    Console::increaseIndention();
  }
  
  // test memset
  //
  byte8 buf[100];
  MemoryManager::memset(buf, 7, 100 * sizeof(byte8));
  MemoryManager::memset(buf, 4, 50 * sizeof(byte8));
  for (int32 i = 0; i < 50; i++) {
    if (buf[i] != (byte8)4) {
      return Error::handle(name(), L"memset", Error::TEST,
			   __FILE__, __LINE__);
    }
  }
  for (int32 i = 50; i < 100; i++) {
    if (buf[i] != (byte8)7) {
      return Error::handle(name(), L"memset", Error::TEST,
			   __FILE__, __LINE__);
    }
  }

  // test memcpy
  //
  MemoryManager::memcpy(&buf[75], &buf[0], 25);

  for (int32 i = 0; i < 50; i++) {
    if (buf[i] != (byte8)4) {
      return Error::handle(name(), L"memset", Error::TEST,
			   __FILE__, __LINE__);
    }
  }
  for (int32 i = 50; i < 75; i++) {
    if (buf[i] != (byte8)7) {
      return Error::handle(name(), L"memset", Error::TEST,
			   __FILE__, __LINE__);
    }
  }
  for (int32 i = 75; i < 100; i++) {
    if (buf[i] != (byte8)4) {
      return Error::handle(name(), L"memset", Error::TEST,
			   __FILE__, __LINE__);
    }
  }

  // reset indentation
  //
  if (level_a > Integral::NONE) {
    Console::decreaseIndention();
  }

  //---------------------------------------------------------------------------
  //
  // 5. class-specific public methods:
  //     static memory-management methods
  //
  //---------------------------------------------------------------------------
  
  // set indentation
  //
  if (level_a > Integral::NONE) {
    Console::put(L"testing class-specific public methods: static memory-management methods...\n");
    Console::increaseIndention();
  }
  
  // test newStatic
  //
  byte8 *stat_ptr = (byte8*)newStatic(100);
  if (stat_ptr == (byte8*)NULL) {
    return Error::handle(name(), L"newStatic", Error::TEST,
			 __FILE__, __LINE__);
  }
  
  // test deleteStatic
  //
  deleteStatic(stat_ptr);
  
  // test reallocate
  //
  int32 *lbuf = (int32*)MemoryManagerBase::isip_malloc(sizeof(int32) * 300);
  size = 300;
  for (int32 i = 0; i < 300; i++) {
    lbuf[i] = i * 3;
  }
  
  MemoryManagerBase::reallocate((void***)&lbuf, size);
  for (int32 i = 0; i < 300; i++) {
    if (lbuf[i] != (i * 3)) {
      return Error::handle(name(), L"reallocate", Error::TEST,
			   __FILE__, __LINE__);
    }
  }

  MemoryManagerBase::isip_free(lbuf);

  // reset indentation
  //
  if (level_a > Integral::NONE) {
    Console::decreaseIndention();
  }

  //---------------------------------------------------------------------------
  //
  // 6. print completion message
  //
  //---------------------------------------------------------------------------

  // reset indentation
  //
  if (level_a > Integral::NONE) {
    Console::decreaseIndention();
  }
  
  if (level_a > Integral::NONE) {
    SysString output(L"diagnostics passed for class ");
    output.concat(name());
    output.concat(L"\n");
    Console::put(output);
  }
  
  // exit gracefully
  //
  return true;
}

// method: setMode
//
// arguments:
//  MODE mode: (input) new mode
//  int32 elem_size: (input) size of each element (in bytes)
//  int32 grow_size: (input) how much to grow by
//
// return: logical error status
//
// set the mode of the MemoryManager. this is a private methods since
// the primary interface is to set all managers one way or
// another. this method is only needed for diagnostics. note that this
// method does not preserve other configuration information.
//
bool8 MemoryManager::setMode(MODE mode_a, int32 elem_size_a,
			       int32 grow_size_a) {

  // determine the current type of manager
  //
  MODE cur_mode = OPTIMIZE;
  if (typeid(*virtual_mgr_d) == typeid(MemoryManagerOptimize)) {
    cur_mode = OPTIMIZE;
  } 
  else if (typeid(*virtual_mgr_d) == typeid(MemoryManagerTrack)) {
    cur_mode = TRACK;
  }
  
  // if the mode is correct, we are done
  //
  if (mode_a == cur_mode) {
    return true;
  }

  delete virtual_mgr_d;

  if (mode_a == OPTIMIZE) {
    virtual_mgr_d = new MemoryManagerOptimize(elem_size_a, grow_size_a);
  }
  else if (mode_a == TRACK) {
    virtual_mgr_d = new MemoryManagerTrack(elem_size_a, grow_size_a);
  }

  // exit gracefully
  //
  return true;
}
