// file: $isip/class/system/MemoryManager/mmgr_02.cc
// version: $Id: mmgr_02.cc 4923 2000-09-20 20:04:15Z hamaker $
//

// isip include files
//
#include "MemoryManager.h"
#include <Error.h>
#include <Console.h>

//--------------------------------------------------------------
// these methods have to be in the same file so they can use the same
// static exiting pointer.
//--------------------------------------------------------------
//
static void** static_d = (void**)NULL;
static int32 static_size_d = 0;
static int32 num_static_d = 0;

// method: newStatic
//
// arguments:
//  int32 size: (input) number of required bytes
//
// return: a bool8 value indicating status
//
// register a pointer with the exit handler
//
void* MemoryManager::newStatic(int32 size_a) {

  // check the arguments
  //
  if (size_a < 1) {
    Error::handle(name(), L"newStatic", Error::ARG, __FILE__, __LINE__);
    return (void*)NULL;
  }
  
  // possibly increase the size of the allocated array
  //
  if (num_static_d + 1 >= static_size_d) {
    MemoryManagerBase::reallocate(&static_d, static_size_d, ALLOC_SIZE);
  }

  // add the buffer to the allocated array. the allocated array points
  // to the handles with which we called new (and will later have to
  // call delete).
  //
  static_d[num_static_d] = MemoryManagerBase::isip_malloc(size_a);

  // exit gracefully
  //
  return static_d[num_static_d++];
}

// method: deleteStatic
//
// arguments:
//  void* ptr: (input) pointer that is about to be freed
//
// return: a bool8 value indicating status
//
// if you are about to free a registered pointer, unregister it first
//
bool8 MemoryManager::deleteStatic(void* ptr_a) {

  // check the arguments
  //
  if (ptr_a == (void*)NULL) {
    return Error::handle(name(), L"deleteStatic", Error::NULL_ARG,
			 __FILE__, __LINE__);
  }
  
  // find the pointer
  //
  bool8 found = false;
  int32 i = -1;
  for (i = 0; i < num_static_d; i++) {
    if (ptr_a == static_d[i]) {
      found = true;
      break;
    }
  }

  // make sure we found it
  //
  if (!found) {
    if (!Error::isExiting()) {
      Error::handle(name(), L"deleteStatic", Error::MEM, __FILE__, __LINE__);
    }
    return false;
  }

  // pull it out of array, decrement count
  //
  for (int32 j = i + 1; j < num_static_d; j++) {
    static_d[j - 1] = static_d[j];
  }
  static_d[--num_static_d] = (void*)NULL;

  // delete the ptr
  //
  MemoryManagerBase::isip_free(ptr_a);
  
  // exit gracefully
  //
  return true;
}

// method: releaseStatics
//
// arguments: none
//
// return: a bool8 value indicating status
//
// free all registered static memory
//
bool8 MemoryManager::releaseStatics() {

  // delete everything in the allocated list
  //
  for (int32 i = 0; i < num_static_d; i++) {
    MemoryManagerBase::isip_free((void*)static_d[i]);
  }

  // delete the allocated array
  //
  if (static_d != (void**)NULL) {
    MemoryManagerBase::isip_free((void*)static_d);
  }

  // re-initialize all pointers
  //
  static_d = (void**)NULL;
  static_size_d = 0;
  num_static_d = 0;
  
  // exit gracefully
  //
  return true;
}
