// file: $isip/class/system/MemoryManager/mmgrb_00.cc
// version: $Id: mmgrb_00.cc 4966 2000-09-22 22:46:24Z duncan $
//

// isip include files
//
#include <Error.h>

// special isip include files
//
#define ISIP_INTERNAL_USE_ONLY
#include "MemoryManagerBase.h"

// method: reallocate
//
// arguments:
//  void*** ptr: (input) pointer to pointer to array
//  long& current_size: (input/output) size of the array
//  long grow_size: (input) increment with which to grow the array
//
// return: a bool8 value indicating status
//
// increase the size of this array of pointers
//
bool8 MemoryManagerBase::reallocate(void*** ptr_a, int32& current_size_a,
				      int32 grow_size_a) {

  // declare the new array space
  //
  void** new_ptr = (void**)isip_malloc(sizeof(void*) * (current_size_a +
							grow_size_a));

  // possibly copy over and delete old space
  //
  if (*ptr_a != (void*)NULL) {
    
    // copy over the old entries
    //
    memcpy(new_ptr, *ptr_a, current_size_a * sizeof(void*));

    // delete the old space
    //
    isip_free(*ptr_a);
  }
  
  // set the pointer to the new space
  //
  *ptr_a = new_ptr;

  // increase the size
  //
  current_size_a += grow_size_a;
  
  // exit gracefully
  //
  return true;
}

//-----------------------------------------------------------------------------
//
// we define non-integral constants in the default constructor
//      
//-----------------------------------------------------------------------------

// instantiations of static class data
//
Integral::DEBUG MemoryManagerBase::debug_level_d = Integral::NONE;

