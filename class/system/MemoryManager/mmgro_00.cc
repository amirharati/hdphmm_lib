// file: $isip/class/system/MemoryManager/mmgro_00.cc
// version: $Id: mmgro_00.cc 5556 2000-11-17 20:46:46Z peng $
//

// isip include files
//
#include <SysString.h>
#include <Console.h>

// special isip include files
//
#define ISIP_INTERNAL_USE_ONLY
#include "MemoryManagerOptimize.h"
 
// method: destructor
//
// arguments: none
//
// return: none
//
// this is the default destructor for the MemoryManager class
//
MemoryManagerOptimize::~MemoryManagerOptimize() {

  allocated_d.clear(Integral::FREE);
  
  // exit gracefully
  //
}

// method: constructor
//
// arguments:
//  int32 elem_size: (input) size of each entry
//  int32 grow_size: (input) size of each new chunk of memory
//
// return: none
//
// this is the only acceptable constructor for the
// MemoryManagerOptimize class
//
MemoryManagerOptimize::MemoryManagerOptimize(int32 elem_size_a,
					     int32 grow_size_a) {

  // initialize the data
  //
  free_d.next_d = (MemoryNode*)NULL;
  free_d.ptr_d = (void*)NULL;

  used_nodes_d.next_d = (MemoryNode*)NULL;
  used_nodes_d.ptr_d = (void*)NULL;
  
  // range check arguments
  //
  if ((grow_size_a < 1) || (elem_size_a < 1)) {
    Error::handle(name(), L"constructor", Error::ARG, __FILE__, __LINE__);
  }

  // set the parameters from arguments
  //
  size_d = elem_size_a;
  grow_size_d = grow_size_a;
  
  // exit gracefully
  //
}

// method: debug
//
// arguments:
//  const unichar* msg: (input) debugging message
//  
// return: a bool8 value indicating status
//
bool8 MemoryManagerOptimize::debug(const unichar* msg_a) const {
  
  // dump the data
  //
  SysString output;
  SysString value;

  // get the size
  //
  value.assign(size_d);
  output.debugStr(name(), msg_a, L"size_d", value);
  Console::put(output);

  // get the grow size
  //
  value.assign(grow_size_d);
  output.debugStr(name(), msg_a, L"grow_size_d", value);
  Console::put(output);

  // get the number of free and used lists
  //
  int32 num_free;
  int32 num_used;
  countNodes(num_used, num_free);
  
  value.assign(num_used);
  output.debugStr(name(), msg_a, L"num_used_d", value);
  Console::put(output);

  value.assign(num_free);
  output.debugStr(name(), msg_a, L"num_free_d", value);
  Console::put(output);
  
  // exit gracefully
  //
  return true;
}

// method: get
//
// arguments: none
//
// return: pointer to new memory
//
// give the user a new chunk of memory
//
void* MemoryManagerOptimize::get() {

  // without purify running, go from the pool of objects
  //
#ifndef PURIFY

  // possibly allocate more nodes
  //
  if (free_d.next_d == (MemoryNode*)NULL) {
    if (!grow()) {
      Error::handle(name(), L"get", Error::NOMEM, __FILE__, __LINE__);
      return (void*)NULL;
    }
  }

  // declare local variables
  //
  MemoryNode* node;

  // pull a node from the top of the free list
  //
  node = free_d.next_d;
  free_d.next_d = free_d.next_d->next_d;

  // push the node to the top of the used list
  //
  node->next_d = used_nodes_d.next_d;
  used_nodes_d.next_d = node;

  void* ptr = node->ptr_d;
  node->ptr_d = (MemoryNode*)NULL;
  
  // return the new node's memory
  //
  return ptr;

  // purify is running, just call malloc
  //
#else
  return isip_malloc(size_d);
#endif
}

// method: release
//
// arguments:
//  void* ptr: (input/output) pointer to free
//
// return: a bool8 value indicating status
//
// release a chunk of memory
//
bool8 MemoryManagerOptimize::release(void* ptr_a) {

  // without purify, go from the pool of objects
  //
#ifndef PURIFY
  
  // declare local variables
  //
  MemoryNode* node;
  
  // grab first node from used_nodes_d
  //
  node = used_nodes_d.next_d;

  // error off if the node is NULL
  //
  if (node == (MemoryNode*)NULL) {
    return Error::handle(name(), L"release", Error::MEM,
			 __FILE__, __LINE__);
  }

  // reset the nodes
  //
  used_nodes_d.next_d = used_nodes_d.next_d->next_d;
  node->ptr_d = ptr_a;
  
  // push the node onto the top of the free list
  //
  node->next_d = free_d.next_d;
  free_d.next_d = node;
  
  // exit gracefully
  //
  return true;

  // purify is running, just call free
  //
#else
  return isip_free(ptr_a);
#endif
  
}

// method: grow
//
// arguments: none
//
// return: a bool8 value indicating status
//
// add to the array of free pointers
//
bool8 MemoryManagerOptimize::grow() {

  // allocate new MemoryNodes for the new data
  //
  void* buffer = isip_malloc(grow_size_d * size_d);

  // register the new pointer onto the allocated heap
  //
  allocated_d.insert(buffer);

  // create nodes to hold the pointers
  //
  MemoryNode* nodes = (MemoryNode*)isip_malloc(sizeof(MemoryNode) *
					       grow_size_d);
  allocated_d.insert(nodes);
  
  // configure the first node
  //
  free_d.next_d = &nodes[0];
  MemoryNode* node = free_d.next_d;
  
  // initialize the newly created memory
  //
  for (int32 i = 0; i < grow_size_d - 1; i++) {
       /*
	casting to 64 bit pointers should be  done  with int64
       */
    node->ptr_d = (void*)((int64)buffer + (int64)(i * size_d));
    node->next_d = &nodes[i + 1];
    node = node->next_d;
  }

  // configure the last node
  //
      /*
	casting to 64 bit pointers should be  done  with int64
      */
  node->ptr_d = (void*)((int64)buffer + (grow_size_d-1) * size_d);
  node->next_d = (MemoryNode*)NULL;

  // exit gracefully
  //
  return true;
}

// method: countNodes
//
// arguments:
//  int32& num_used: (output) number of nodes currently used
//  int32& num_free: (output) number of nodes currently available
//
// return: a bool8 value indicating status
//
// count the nodes in the two linked lists. possibly useful for debugging.
//
bool8 MemoryManagerOptimize::countNodes(int32& num_used_a,
					  int32& num_free_a) const {

  // initialize the number of nodes currently used
  //
  num_used_a = 0;

  // loop over nodes and increment the number of nodes currently used
  //
  for (const MemoryNode* node = &used_nodes_d;
       node->next_d != (MemoryNode*)NULL;
       node = node->next_d) {
    num_used_a++;
  }

  // initialize the number of nodes currently available
  //
  num_free_a = 0;

  // loop over nodes and increment the number of nodes currently
  // available
  //
  for (const MemoryNode* node = &free_d;
       node->next_d != (MemoryNode*)NULL;
       node = node->next_d) {
    num_free_a++;
  }

  // exit gracefully
  //
  return true;
}

//-----------------------------------------------------------------------------
//
// we define non-integral constants in the default constructor
//      
//-----------------------------------------------------------------------------

// constants: class name
//
const SysString MemoryManagerOptimize::CLASS_NAME(L"MemoryManagerOptimize");
