// file: $isip/class/system/SysHeap/sh_04.cc
// version: $Id: sh_04.cc 5437 2000-10-29 20:47:05Z hamaker $
//

// isip include files
// 
#include "SysHeap.h"
 
// method: extractMax
//
// arguments:
//  void*& ptr: (output) largest pointer
//
// return: a bool8 value indicating status
//
// this method removes (and returns) the largest pointer from the heap
//
bool8 SysHeap::extractMax(void*& ptr_a) {

  // check whether the heap is empty or not?
  //
  if (isEmpty()) {

    // return error
    //
    return Error::handle(name(), L"extractMax", ERR_HEMPTY,
                         __FILE__, __LINE__, Error::WARNING);
  }

  // number of elements can't be negative
  //
  if (num_elements_d < 0) {
    return Error::handle(name(), L"extractMax", ERR,
                         __FILE__, __LINE__, Error::WARNING);
  }  

  // declare local variable
  //
  void* max;

  // element at index 0 is maximum
  //
  max = data_d[0];
  data_d[0] = data_d[num_elements_d - 1];

  // decrease the length of the heap by one
  //
  num_elements_d = num_elements_d - 1;

  // heapify the remaining heap
  //
  heapify(0);
  ptr_a = max;
  
  // exit gracefully
  //
  return true;
}

// method: extract
//
// arguments:
//  void* ptr: (input) pointer to extract
//
// return: a bool8 value indicating status
//
// this method removes a pointer from the heap
//
bool8 SysHeap::extract(void* ptr_a) {

  // check whether the heap is empty or not?
  //
  if (isEmpty()) {

    // return error
    //
    return Error::handle(name(), L"extract", ERR_HEMPTY,
                         __FILE__, __LINE__, Error::WARNING);
  }

  // number of elements can't be negative
  //
  if (num_elements_d < 0) {
    return Error::handle(name(), L"extract", ERR,
                         __FILE__, __LINE__, Error::WARNING);
  }  

  // find the index of the pointer on heap
  //
  int32 index = find(ptr_a);
  if (index < 0) {
    Error::handle(name(), L"extract", ERR_INVPTR,
		  __FILE__, __LINE__, Error::WARNING);
  }

  // reduce the number of elements by 1 after extracting it
  //
  if (!extract(ptr_a, index)) {
    return Error::handle(name(), L"extract", ERR, __FILE__, __LINE__,
			 Error::WARNING);
  }
    
  // exit gracefully
  //
  return true;
}

// method: extract
//
// arguments:
//  void* ptr: (input) pointer to extract
//  int32 pos: (input) index
//
// return: a bool8 value indicating status
//
// this method removes a pointer from the heap
//
bool8 SysHeap::extract(void* ptr_a, int32 pos_a) {

  // number of elements can't be negative
  //
  if (num_elements_d < 0) {
    return Error::handle(name(), L"extract", ERR,
                         __FILE__, __LINE__, Error::WARNING);
  }  

  if ((pos_a < 0) || (pos_a >= num_elements_d)) {
    return Error::handle(name(), L"extract", ERR,
                         __FILE__, __LINE__, Error::WARNING);
  }  

  // check whether the heap is empty or not?
  //
  if (isEmpty()) {

    // return error
    //
    return Error::handle(name(), L"extract", ERR_HEMPTY,
                         __FILE__, __LINE__, Error::WARNING);
  }

  // if the ptr is the last item in the array then we don't need to
  // restructure the heap
  //
  if (pos_a == num_elements_d - 1) {
    num_elements_d--;
    return true;
  }

  // move the last element in the place of the one to extract,
  //
  data_d[pos_a] = data_d[num_elements_d - 1];

  // decrease the size of the heap
  //
  num_elements_d--;

  // the element that was just moved is not guaranteed to be less than its
  // new parant so bubble it up
  //
  bubbleUp(pos_a);

  // if the element did not bubble up then there is no guarantee that it is
  // greater than its new children, so heapify this portion of the heap
  //
  heapify(pos_a);
  
  // exit gracefully
  //
  return true; 
}

// method: bubbleUp
//
// arguments:
//  int32 index: (input) index
//
// return: a bool8 value indicating status
//
// this method swaps the parent and child values until the value of the parent
// is greater than or equal to the value of it's child
//
bool8 SysHeap::bubbleUp(int32 index_a) {

  // if we are at the top of the heap, there is no bubbling to be done
  //
  if (index_a == 0) {
    return true;
  }
  
  // declare local variables
  //
  void* temp = NULL;
  int32 parent_index = parent(index_a);
  
  // swap the parent and child until parent becomes greater or equal
  // to the child
  //
  while ((index_a > 0) && (data_d[parent_index] < data_d[index_a])) {

    // swap the parent and child
    //
    temp = data_d[parent_index];
    data_d[parent_index] = data_d[index_a];
    data_d[index_a] = temp;

    // update the index
    //
    index_a = parent_index;
  }
  
  // exit gracefully
  //
  return true;  
}
