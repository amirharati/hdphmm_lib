// file: $isip/class/system/SysHeap/sh_05.cc
// version: $Id: sh_05.cc 4941 2000-09-21 22:53:01Z duncan $
//

// isip include files
//
#include "SysHeap.h"

// method: eq
//
// arguments:
//  const SysHeap& arg: (input) string to copy
//
// return: a bool8 value indicating status
//
// this method check to see if the object equal to arg_a
//
bool8 SysHeap::eq(const SysHeap& arg_a) {

  // check the equality of class data members
  //
  if (data_d != arg_a.data_d) {
    return false;
  }
  if (capacity_d != arg_a.capacity_d) {
    return false;
  }
  if (num_elements_d != arg_a.num_elements_d) {
    return false;
  }
  if (grow_factor_d != arg_a.grow_factor_d) {
    return false;
  }
  
  // exit gracefully
  //
  return true;
}

// method: setCapacity
//
// arguments:
//  int32 length: (input) capacity
//
// return: a bool8 value indicating status
//
// this method sets the capacity of the heap
//
bool8 SysHeap::setCapacity(int32 length_a) {

  // if length_a < 0, error
  // 
  if (length_a < 0) {
    return Error::handle(name(), L"setCapacity", Error::ARG,
                         __FILE__, __LINE__);
  }
  
  // if the length is equal to the current capacity, we're done
  //
  if (length_a == capacity_d) {
    return true;
  }

  // if length_a <= num_elements_d, we loose valid elements
  // 
  if (length_a <= (int32)num_elements_d) {
    num_elements_d = length_a;
  }

  // if the new capacity is greater than zero, we will need memory
  //
  if (length_a > 0) {
    
    // allocate a new chunk of memory
    //
    void** new_mem = (void**)malloc(sizeof(void*) * length_a);

    if (new_mem == (void**)NULL) {
      return Error::handle(name(), L"setCapacity", Error::NOMEM,
                           __FILE__, __LINE__);
    }

    // set capacity equal to length
    //
    capacity_d = length_a;

    // if there are valid elements and we need to preserve them
    //
    if (num_elements_d > 0) {
      
      for (int32 i = 0; i < num_elements_d; i++) {
        new_mem[i] = data_d[i];
      }
    }
    else {
      num_elements_d = 0;
    }

    // delete the old memory
    //
    if (data_d != (void**)NULL) {
      free(data_d);
      data_d = (void**)NULL;
    }
    
    // assign the pointer to the new memory
    //
    data_d = new_mem;
  }

  // new capacity is zero, just delete memory
  //
  else {
    
    // delete the old memory
    //
    if (data_d != (void**)NULL) {
      free(data_d);
      data_d = (void**)NULL;
    }

    // reset the capacity, number of elements and growth factor
    //
    capacity_d = 0;
    num_elements_d = 0;
    grow_factor_d = DEF_GROW_FACTOR;
  }
  
  // exit gracefully
  //
  return true;  
}

// method: setLength
//
// arguments:
//  int32 length: (input) length of heap
//
// return: a bool8 value indicating status
//
// this method sets the length of the heap
//
bool8 SysHeap::setLength(int32 length_a) {

  // declare local variables
  //
  int32 opt = 0;
  int32 new_cap = 0;
      
  // if length_a < 0, error
  // 
  if (length_a < 0) {
    return Error::handle(name(), L"setLength", Error::ARG,
                         __FILE__, __LINE__);
  }
  
  // if length_a <= num_elements_d change length
  // 
  if (length_a <= (int32)num_elements_d) {

    opt = capacity_d / (2 * grow_factor_d);

    // shrink by growth factor if the length is less than quarter of the
    // capacity, in order to make optimal use of memory
    //
    if (length_a <= opt) {
      if (!setCapacity(capacity_d / grow_factor_d)) {
        return Error::handle(name(), L"setLength", Error::NOMEM,
                             __FILE__, __LINE__);
      }
      
      // set the length
      //
      num_elements_d = length_a;

      // exit gracefully
      //
      return true;
    }

    // change the length without attempting shrinking the heap since we
    // know that the length_a is greater than the num_elements_d
    //
    else {

      // change num_elements_d 
      //
      num_elements_d = length_a;

      // exit gracefully
      //
      return true;
    }
  }

  // the new length is greater than the current length
  //
  else {
    
    // if new length is greater than the capacity, call setCapacity
    //
    while (length_a > capacity_d) {

      // check the growth factor
      //
      if (grow_factor_d < 2) {
	return Error::handle(name(), L"setLength", ERR, __FILE__, __LINE__);
      }
      
      // for the first increase we set the heap size to 10 which comes
      // from the amortized analysis of a growing table:
      //
      // T.H. Cormen, C.E. Leiserson and R.L. Rivest, "Introduction to
      // algorithms," McGraw-Hill, New York, New York, USA, pp. 356-367, 1997. 
      //
      if (capacity_d == 0) {
	new_cap = 10;
      }

      // increase the capacity of the heap by a set growth factor
      //
      else {
	new_cap = grow_factor_d * capacity_d;
      }
      
      // throw an error if heap capacity cannot be increased
      //
      if (!setCapacity(new_cap)) {
        return Error::handle(name(), L"setLength", Error::NOMEM,
                             __FILE__, __LINE__);
      }
    }
    
    // for every new element clear the value
    //
    for (int32 i = num_elements_d; i < length_a; i++) {
      data_d[i] = (void*)NULL;
    }
    
    // set the new length
    // 
    num_elements_d = length_a;

    // exit gracefully
    //
    return true;
  }
}
