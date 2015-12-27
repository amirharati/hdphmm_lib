// file: $isip/class/system/SysString/sstr_05.cc
// version: $Id: sstr_05.cc 4889 2000-09-20 13:49:58Z hamaker $
//

// isip include files
//
#include "SysString.h"
#include <MemoryManager.h>
// --------------------------------------------------------------
// these two methods have to be in the same file so they get the
// static constant NULL_STRING with the exact same address
// --------------------------------------------------------------

// method: allocateMem
//
// arguments: none
//
// return: a boolean value indicating status
//
// this method allocates memory for the string
//

bool8 SysString::allocateMem() {

  // either allocate the memory or assign it to the static null string
  //
  if (capacity_d > 0) {
    if (value_d != (unichar*)NULL) {
      return Error::handle(name(), L"allocateMem", Error::MEM,
			   __FILE__, __LINE__);
    }

    // allocate and initialize the memory
    //
    value_d = new unichar[capacity_d + 1];
    value_d[0] = (unichar)NULL;
  }
  else {
    if (value_d != (unichar*)NULL) {
      return Error::handle(name(), L"allocateMem", Error::MEM,
			   __FILE__, __LINE__);
    }

    // reset the capacity 
    //
    capacity_d = 0;

    // assign null string to class data
    //
      value_d = (unichar*)NULL_STRING;
  }

  // exit gracefully
  //
  return true;
}

// method: freeMem
//
// arguments: none
//
// return: a bool8 value indicating status
//
// this method deletes memory for the string
//
bool8 SysString::freeMem() {

  // possibly free memory associated with this string
  //
  if (capacity_d > 0) {
    if (value_d != (unichar*)NULL) {

      // release and initialize the pointer
      //
      delete [] value_d;
      value_d = (unichar*)NULL;
    }
    else {
      return Error::handle(name(), L"freeMem", Error::MEM, __FILE__, __LINE__);
    }
  }

  // if capacity is less than or equal to 0
  //
  else {
    if (value_d == (unichar*)NULL_STRING) {

      // initialize the ptr
      //
      value_d = (unichar*)NULL;
    }
    else {
      return Error::handle(name(), L"freeMem", Error::MEM, __FILE__, __LINE__);
    }

  }

  // reset the capacity
  //
  capacity_d = 0;

  // exit gracefully
  //
  return true;
}

// method: growMem
//
// arguments:
//  int32 new_size: (input) new size of memory required
//
// return: a bool8 value indicating status
//
// allocate more memory for the string, nondestructively
//
bool8 SysString::growMem(int32 new_size_a) {

  // see if we have to do anything
  //
  if (new_size_a <= capacity_d) {
    return true;
  }

  // if there is nothing in the old memory block, we don't have to
  // save any memory, just delete and reallocate
  //
  if (length() == 0) {
    freeMem();
    capacity_d = new_size_a;
    allocateMem();
  }
  else {

    // this is the only nontrivial case, we need to increase the size
    // of the memory without destroying existing contents. we do this
    // by creating a new string of the specified size, assigning this
    // new string to have our current value, and swapping the memory
    // pointers (so that the old buffer is deleted with the new
    // SysString)
    //
    SysString* tmp_str = new SysString(new_size_a);

    // assign tmp_str to have current values
    //
    tmp_str->assign(*this);

    // swap the memory pointers
    //
    swap(*tmp_str);

    delete tmp_str; 
  }
  
  // exit gracefully
  //
  return true;
}
