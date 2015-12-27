// file: $isip/class/system/SysHeap/sh_03.cc
// version: $Id: sh_03.cc 5437 2000-10-29 20:47:05Z hamaker $
//

// isip include files
// 
#include "SysHeap.h"
 
// method: build
//
// arguments: none
//
// return: a bool8 value indicating status
//
// this method builds the heap
//
bool8 SysHeap::build() {

  // loop over the elements of the array
  //
  for (int32 i = (num_elements_d / 2) -1; i >= 0; i--) {

    // call heapify
    //
    heapify(i);
  }
  
  // exit gracefully
  //
  return true;
}

// method: find
//
// arguments:
//  void* ptr: (input) pointer
//  int32 start_index: (input) index from where searching is to start
//
// return: a int32 value containing the index corresponding to the
//         input pointer
//
// this method returns a int32 value containing the index corresponding
// to the input pointer
//
int32 SysHeap::find(void* ptr_a, int32 start_index_a) const {

  // check the arguments
  //
  if (start_index_a < 0) {
    Error::handle(name(), L"find", Error::ARG,
		  __FILE__, __LINE__);
  }
  
  // check whether the heap is empty or not?
  //
  if (isEmpty()) {

    // return error
    //
    Error::handle(name(), L"find", ERR_HEMPTY,
		  __FILE__, __LINE__);
  }

  // number of elements can't be negative
  //
  if (num_elements_d < 0) {
    Error::handle(name(), L"find", ERR, __FILE__, __LINE__);
  }  

  // if the data is found at the starting index, then return the starting
  // index
  //
  if (data_d[start_index_a] == ptr_a) {
    return start_index_a;
  }

  // else search the heap to find the data
  //
  else {

    int32 temp = -1;
    int32 left_ind = left(start_index_a);

    if (left_ind < num_elements_d) {
      temp = find(ptr_a, left_ind);
    }

    if (temp >= 0) {
      return temp;
    }
    else {

      int32 right_ind = right(start_index_a);

      if (right_ind < num_elements_d) {
	temp = find(ptr_a, right_ind);
      }

      // return the index
      //
      return temp;
    }
  }
}

// method: insert
//
// arguments:
//  void* ptr: (input) pointer to insert
//
// return: a bool8 value indicating status
//
// this method adds a pointer to the heap 
//
bool8 SysHeap::insert(void* ptr_a) {

  // declare local variables
  //
  int32 index = 0;
  
  // increase the heap size by one
  //
  setLength(num_elements_d + 1);

  // set the initial index
  //
  index = num_elements_d - 1;

  // find a place to insert the input pointer so as to satisfy the heap
  // property
  //
  while ((index > 0) && (data_d[parent(index)] < ptr_a)) {
    data_d[index] = data_d[parent(index)];
    index = parent(index);
  }

  // insert the pointer now
  //
  data_d[index] = ptr_a;
  
  // exit gracefully
  //
  return true;  
}

// method: heapify
//
// arguments:
//  int32 index: (input) index for which we need to maintain heap property
//
// return: a bool8 value indicating status
//
// this method maintains the heap property
//
bool8 SysHeap::heapify(int32 index_a) {

  // declare local variables
  //
  int32 l = left(index_a);
  int32 r = right(index_a);
  int32 largest = 0;
  
  // check whether the left child is less than the heap size and if the left
  // node value is greater than the value at the input index
  //
  if ((l < num_elements_d) && (data_d[l] > data_d[index_a])) {

    // l is the largest element
    //
    largest = l;
  }

  else {
    largest = index_a;
  }

  // check whether the right child is less than the heap size and if the right
  // node value is greater than the largest node
  //
  if ((r < num_elements_d) && (data_d[r] > data_d[largest])) {

    // r is the largest element
    //
    largest = r;
  }

  // exchange the largest element with the element at the input index, if
  // largest index is not same as that of at the input index
  //
  if (largest != index_a) {

    // declare a temporary variable and swap
    //
    void* temp;
    temp = data_d[largest];
    data_d[largest] = data_d[index_a];
    data_d[index_a] = temp;

    // heapify again
    //
    heapify(largest);
  }

  // exit gracefully
  //
  return true; 
}
