// file: $isip/class/system/SysHeap/sh_00.cc
// version: $Id: sh_00.cc 5014 2000-09-26 15:48:34Z hamaker $
//

// isip include files
//
#include "SysHeap.h"

// method: clear
//
// arguments:
//  Integral::CMODE ctype: (input) clear mode for the heap
//
// return: a bool8 value indicating status
//
// this method clears the heap
//
bool8 SysHeap::clear(Integral::CMODE ctype_a) {

  // if the ctype_a is RETAIN or RESET, clear structure but don't 
  // necessarily delete memory
  //
  if ((ctype_a == Integral::RETAIN) || (ctype_a == Integral::RESET)) {
    setLength(0);
  }

  // if the ctype_a is RELEASE, clear the structure and release memory
  //
  else if (ctype_a == Integral::RELEASE) {
    if (!setCapacity(0)) {
      return Error::handle(name(), L"clear", Error::ARG, __FILE__, __LINE__);
    }
  }

  // if the ctype_a is FREE, delete all memory held in structure
  //
  else if (ctype_a == Integral::FREE) {

    // loop through each element in the heap and deallocate memory
    //
    for (int32 i = 0; i < num_elements_d; i++) {
      if (data_d[i] != (void*)NULL) {
	free(data_d[i]);
      }
    }
    if (!setCapacity(0)) {
      return Error::handle(name(), L"clear", Error::ARG, __FILE__, __LINE__);
    }

    // reset the variables
    //
    num_elements_d = 0;
    capacity_d = 0;
  }

  // set configuration variables
  //
  grow_factor_d = DEF_GROW_FACTOR;
  
  // exit gracefully
  //
  return true;
}

// method: destructor
//
// arguments: none
//
// return: none
//
SysHeap::~SysHeap() {

  // clean up memory and reset
  //
  if (data_d != (void**)NULL) {
    free(data_d);
    data_d = (void**)NULL;
  }
    
  // exit gracefully
  //
}

// method: default constructor
//
// arguments: none
//
// return: none
//
SysHeap::SysHeap() {

  // initialize the class data
  //
  num_elements_d = DEF_NUM_ELEMENTS;
  capacity_d = DEF_CAPACITY;
  grow_factor_d = DEF_GROW_FACTOR;
  data_d = (void**)NULL;
  
  // exit gracefully
  //
}

//-----------------------------------------------------------------------------
//
// we define non-integral constants in the default constructor
//      
//-----------------------------------------------------------------------------

// constants: class name
//
const unichar SysHeap::CLASS_NAME[] = L"SysHeap";

// static instantiations: debug level
//
Integral::DEBUG SysHeap::debug_level_d = Integral::NONE;
