// file: $isip/class/system/MemoryManager/mmgrt_01.cc
// version: $Id: mmgrt_01.cc 4886 2000-09-20 13:21:43Z hamaker $
//

// isip include files
//
#include <SysString.h>
#include <Console.h>

// special isip include files
//
#define ISIP_INTERNAL_USE_ONLY
#include "MemoryManagerTrack.h"
 
// method: diagnose
//
// arguments:
//  Integral::DEBUG level: (input) debug level for diagnostics
//
// return: a bool8 value indicating status
//
bool8 MemoryManagerTrack::diagnose(Integral::DEBUG level_a) {

  // if level_a is DEBUG_NONE, only do a quick test of constructors
  // and destructors
  //
  if (level_a == Integral::NONE) {

    MemoryManagerTrack* ptr = new MemoryManagerTrack(4);
    delete ptr;

    return true;
  }

  // perform full diagnostic
  //
  if (level_a > Integral::BRIEF) {
    Console::put(L"starting diagnostic");
  }

  // start a memory manager for doubles
  //
  MemoryManagerTrack mgr(sizeof(float64));
  
  // test the setDebug method
  //
  mgr.setDebug(level_a);
  
  if (level_a > Integral::DETAILED) {
    mgr.debug(L"after initialization");
  }

  // test the get methods
  //
  float64* ptr0 = (float64*)mgr.get();
  *ptr0 = 54.0;

  if (level_a > Integral::DETAILED) {
    mgr.debug(L"after allocation 0");
  }

  float64* ptr1 = (float64*)mgr.get();
  *ptr1 = 54.1;
  
  float64* ptr2 = (float64*)mgr.get();
  *ptr2 = 54.2;
  
  float64* ptr3 = (float64*)mgr.get();
  *ptr3 = 54.3;
  
  float64* ptr4 = (float64*)mgr.get();
  *ptr4 = 54.4;

  if (level_a > Integral::DETAILED) {
    mgr.debug(L"after allocations");
  }

  // test the release methods
  //
  mgr.release(ptr0); 
  if ((*ptr1 != 54.1)&&(*ptr2 != 54.2)&&(*ptr3 != 54.3)&&(*ptr4 != 54.4)) {
    return Error::handle(name(), L"release", Error::TEST, __FILE__, __LINE__);
  }
  float64 *xx = (float64*)mgr.free_d.next_d->ptr_d;
  if (*xx != 54.0) {
    return Error::handle(name(), L"release", Error::TEST, __FILE__, __LINE__);
  }
  
  mgr.release(ptr3);
  if ((*ptr1 != 54.1)&&(*ptr2 != 54.2)&&(*ptr4 != 54.4)) {
    return Error::handle(name(), L"release", Error::TEST, __FILE__, __LINE__);
  }

  mgr.release(ptr2);
  if ((*ptr1 != 54.1)&&(*ptr4 != 54.4)) {
    return Error::handle(name(), L"release", Error::TEST, __FILE__, __LINE__);
  }

  mgr.release(ptr4);
  if (*ptr1 != 54.1) {
    return Error::handle(name(), L"release", Error::TEST, __FILE__, __LINE__);
  }

  mgr.release(ptr1);

  // let's try to grow several times
  //
  mgr.setGrow(3);

  float64* ptr[8198];

  for (int32 i = 0; i < 8198; i++) {   
    ptr[i] = (float64*)mgr.get();
    *ptr[i] = (float64)i;
  }
  
  if (level_a > Integral::DETAILED) {
    mgr.debug(L"after lots of allocations");
  }

  for (int32 i = 0; i < 8198; i++) {  
    mgr.release(ptr[i]);
  }
  
  if (level_a > Integral::DETAILED) {
    mgr.debug(L"after lots of releases");
  }
  
  // create another memory manager
  //
  MemoryManagerTrack mgr2(sizeof(int32));

  int32* lptr0 = (int32*)mgr2.get();
  *lptr0 = 54;

  if (level_a > Integral::DETAILED) {
    mgr2.debug(L"after allocation 0");
  }

  int32* lptr1 = (int32*)mgr2.get();
  *lptr1 = 55;
  
  int32* lptr2 = (int32*)mgr2.get();
  *lptr2 = 56;
  
  int32* lptr3 = (int32*)mgr2.get();
  *lptr3 = 57;
  
  int32* lptr4 = (int32*)mgr2.get();
  *lptr4 = 58;

  if (level_a > Integral::DETAILED) {
    mgr2.debug(L"after allocations");
  }

  mgr2.release(lptr0);
  mgr2.release(lptr1);
  mgr2.release(lptr2);
  mgr2.release(lptr3);
  mgr2.release(lptr4);
  
  // create a block allocater
  //
  MemoryManagerTrack block_mgr(1);
  
  int32 block_size = 100;
  int32 num_blocks = 8192;
  
  int32** blk_ints = (int32**)block_mgr.getBlock(num_blocks * sizeof(int32*));
  byte8** blk_bytes = (byte8**)block_mgr.getBlock(num_blocks * sizeof(byte8*));
  
  if (level_a > Integral::DETAILED) {
    block_mgr.debug(L"before block-allocations");
  }

  // allocate a whole bunch of memory blocks
  //
  for (int32 i = 0; i < num_blocks; i++) {

    blk_ints[i] = (int32*)block_mgr.getBlock(block_size * sizeof(int32));
    blk_bytes[i] = (byte8*)block_mgr.getBlock(block_size * sizeof(byte8));
    
    for (int32 j = 0; j < block_size; j++) {
      blk_ints[i][j] = ((3 * i) | 1) % (j | 1);
      blk_bytes[i][j] = ((2 * i) |  1) % (j | 1);
    }
  }
  
  // check the values of the memory blocks
  //
  for (int32 i = 0; i < num_blocks; i++) {

    for (int32 j = 0; j < block_size; j++) {
      if (blk_ints[i][j] != (((3 * i) | 1) % (j | 1))) {
	return Error::handle(name(), L"block", Error::TEST,
			     __FILE__, __LINE__);
      }
      if (blk_bytes[i][j] != (((2 * i) + 1) % (j | 1))) {
	return Error::handle(name(), L"block", Error::TEST,
			     __FILE__, __LINE__);
      }
    }
  }
  
  if (level_a > Integral::DETAILED) {
    block_mgr.debug(L"after block-allocations");
  }

  // release all the memory blocks
  //
  for (int32 i = 0; i < num_blocks; i++) {
    block_mgr.releaseBlock(blk_bytes[i]);
    block_mgr.releaseBlock(blk_ints[i]);
  }

  // release the block holders
  //
  block_mgr.releaseBlock(blk_bytes);
  block_mgr.releaseBlock(blk_ints);

  if (level_a > Integral::DETAILED) {
    block_mgr.debug(L"after block-release");
  }
  
  // possibly print completion message
  //
  if (level_a > Integral::BRIEF) {
    SysString output(L"\ndiagnostics completed successfully for class ");
    output.concat(name());
    output.concat(L"\n");
    Console::put(output);
  }

  // exit gracefully
  //
  return true;
}
