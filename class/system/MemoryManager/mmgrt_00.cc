// file: $isip/class/system/MemoryManager/mmgrt_00.cc
// version: $Id: mmgrt_00.cc 8650 2002-08-23 19:32:45Z jelinek $
//

// isip include files
//
#include <SysString.h>
#include <Console.h>

// special isip include files
//
#define ISIP_INTERNAL_USE_ONLY
#include "MemoryManagerTrack.h"
 
// method: destructor
//
// arguments: none
//
// return: none
//
// this is the destructor for the MemoryManagerTrack class
//
MemoryManagerTrack::~MemoryManagerTrack() {

  // if the registered list is not empty (ie, releaseMgrs has not been
  // called), then clear and unregister this manager
  //
  if ((allocated_mgrs_d != (SysHeap*)NULL) && !allocated_mgrs_d->isEmpty()) {

    // release all internal data
    //
    clear();
    unRegisterMgr();
  }
  
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
// this is one of the most commonly constructors for the
// MemoryManagerTrack class.
//
MemoryManagerTrack::MemoryManagerTrack(int32 elem_size_a,
				       int32 grow_size_a) {

  // initialize the data
  //
  free_d.next_d = (MemoryNode*)NULL;
  free_d.ptr_d = (void*)NULL;

  used_nodes_d.next_d = (MemoryNode*)NULL;
  used_nodes_d.ptr_d = (void*)NULL;
  
  size_d = -1;
  grow_size_d = DEF_GROW_SIZE;
  
  // check the arguments
  //
  if (grow_size_a < 1) {
    Error::handle(name(), L"constructor", Error::ARG, __FILE__, __LINE__);
  }
  if (elem_size_a < 1) {
    Error::handle(name(), L"constructor", Error::ARG, __FILE__, __LINE__);
  }
  
  // set the parameters from arguments
  //
  size_d = elem_size_a;
  grow_size_d = grow_size_a;

  // register the memory manager
  //
  registerMgr();
  
  // exit gracefully
  //
}

// method: constructor
//
// arguments:
//  int32 elem_size: (input) size of each entry
//  const SysString& name: (input) name to associate with manager
//  int32 grow_size: (input) size of each new chunk of memory
//
// return: none
//
// this is oneof the most commonly used constructors for the
// MemoryManagerTrack class
//
MemoryManagerTrack::MemoryManagerTrack(int32 elem_size_a,
				       const SysString& name_a,
				       int32 grow_size_a) {

  // initialize the data
  //
  free_d.next_d = (MemoryNode*)NULL;
  free_d.ptr_d = (void*)NULL;

  used_nodes_d.next_d = (MemoryNode*)NULL;
  used_nodes_d.ptr_d = (void*)NULL;

  size_d = -1;
  grow_size_d = DEF_GROW_SIZE;

  // check the arguments
  //
  if (grow_size_a < 1) {
    Error::handle(name(), L"constructor", Error::ARG, __FILE__,
		  __LINE__);
  }
  if (elem_size_a < 1) {
    Error::handle(name(), L"constructor", Error::ARG, __FILE__, __LINE__);
  }
  
  // set the parameters from arguments
  //
  size_d = elem_size_a;
  grow_size_d = grow_size_a;
  //  name_d.assign(name_a);
  
  // register the memory manager
  //
  registerMgr();

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
bool8 MemoryManagerTrack::debug(const unichar* msg_a) const {
  
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

  // get the allocated heap
  //
  allocated_d.debug(L"allocated_d");
  block_allocated_d.debug(L"block_allocated_d");
  used_d.debug(L"used_d");

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
void* MemoryManagerTrack::get() {

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

  // set the nodes
  //
  void* ptr = node->ptr_d;
  node->ptr_d = (MemoryNode*)NULL;
  
  // insert this node to used heap
  //
  used_d.insert(ptr);

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
bool8 MemoryManagerTrack::release(void* ptr_a) {

  // without purify, go from the pool of objects
  //
#ifndef PURIFY
  
  // check the arguments
  //
  if (ptr_a == (void*)NULL) {
    Error::handle(name(), L"release", Error::ARG, __FILE__, __LINE__);
  }

  // extract the pointer from used heap
  //
  if (!used_d.extract(ptr_a)) {
    display(ptr_a);
    return Error::handle(name(), L"release", ERR_NOTFND,
			 __FILE__, __LINE__);
  }

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
bool8 MemoryManagerTrack::grow() {

  // free list must be out of nodes before this is called
  //
  if (free_d.next_d != (MemoryNode*)NULL) {
    return Error::handle(name(), L"grow", ERR_NOTEMP, __FILE__, __LINE__);
  }

  // allocate new MemoryNodes for the new data
  //
  void* buffer = isip_malloc(grow_size_d * size_d);

  // register the new pointer onto the allocated heap
  //
  allocated_d.insert(buffer);

  // create nodes to hold the pointers
  //
  MemoryNode* nodes = (MemoryNode*)isip_malloc(sizeof(MemoryNode)
					       * grow_size_d);

  // insert nodes on allocated heap
  //
  allocated_d.insert(nodes);
  
  // configure the first node
  //
  free_d.next_d = &nodes[0];
  MemoryNode* node = free_d.next_d;
  
  // initialize the newly created memory
  //
  for (int32 i = 0; i < grow_size_d - 1; i++) {
       /*
	Casting to 64 bit pointer  should be done  with int64 
       */ 
    node->ptr_d = (void*)((int64)buffer + (int64)(i * size_d));
    node->next_d = &nodes[i + 1];
    node = node->next_d;
  }

  // configure the last node
  //
      /*
	Casting to 64 bit pointer  should be done  with int64 
       */
  node->ptr_d = (void*)((int64)buffer + (grow_size_d-1) * size_d);
  node->next_d = (MemoryNode*)NULL;

  // exit gracefully
  //
  return true;
}

// method: getBlock
//
// arguments:
//  int32 size: (input) size of memory in bytes
//
// return: memory pointer
//
// allocate a chunk of contiguous memory
//
void* MemoryManagerTrack::getBlock(int32 size_a) {

  // check the arguments
  //
  if (size_a < 1) {
    Error::handle(name(), L"getBlock", Error::ARG, __FILE__, __LINE__);
    return (void*)NULL;
  }

  // get the pointer to a block of at least size_a bytes suitably
  // aligned
  //
  void* ptr = isip_malloc(size_a);

  // if it is NULL then return error
  //
  if (ptr == (void*)NULL) {
    Error::handle(name(), L"getBlock", Error::NOMEM, __FILE__, __LINE__);
    return (void*)NULL;
  }
  
  // pull a node from the top of the free heap
  //
  block_allocated_d.insert(ptr);
  
  // return the pointer
  //
  return ptr;
}

// method: releaseBlock
//
// arguments:
//  void* ptr: (input) buffer of memory to release
//
// return: a bool8 value indicating status
//
// allocate a chunk of contiguous memory
//
bool8 MemoryManagerTrack::releaseBlock(void* ptr_a) {

  // check the arguments
  //
  if (ptr_a == (void*)NULL) {
    return Error::handle(name(), L"releaseBlock", Error::ARG,
			 __FILE__, __LINE__);
  }

  // extract the pointer from block allocated heap
  //
  if (!block_allocated_d.extract(ptr_a)) {
    display(ptr_a, true);
    return Error::handle(name(), L"releaseBlock", ERR_NOTFND,
			 __FILE__, __LINE__);
  }

  // delete the memory
  //
  isip_free(ptr_a);
  
  // exit gracefully
  //
  return true;
}

// method: reallocateBlock
//
// arguments:
//  void*** ptr: (input) pointer to pointer to array
//  int32& current_size: (input/output) size of the array
//  int32 size_increment: (input) increment with which to grow the array
//
// return: a bool8 value indicating status
//
// increase the size of this array of pointers
//
bool8 MemoryManagerTrack::reallocateBlock(void*** ptr_a,
					    int32& current_size_a,
					    int32 grow_size_a) {

  // check for memory errors. either the pointer should be null and
  // the size 0, or the pointer should not be null and the size > 0
  //
  if ((*ptr_a == (void*)NULL) ^ (current_size_a == 0)) {
    return Error::handle(name(), L"reallocateBlock", Error::MEM,
			 __FILE__, __LINE__);
  }

  // if the pointer is not null, unregister it
  //
  if (*ptr_a != (void*)NULL) {
    if (!block_allocated_d.extract(*ptr_a)) {
      display(*ptr_a, true);
      return Error::handle(name(), L"reallocateBlock", ERR_NOTFND,
			   __FILE__, __LINE__);
    }
  }
  
  // reallocate the memory
  //
  reallocate(ptr_a, current_size_a, grow_size_a);
  
  // register the pointer
  //
  if (!block_allocated_d.insert(*ptr_a)) {
    return Error::handle(name(), L"reallocateBlock", Error::ARG,
			 __FILE__, __LINE__);
  }
  
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
bool8 MemoryManagerTrack::countNodes(int32& num_used_a,
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

// method: display
//
// arguments:
//  void* ptr: (input) address to report
//  bool8 block_mode: (input) are we in block mode?
//
// return: a bool8 value indicating status
//
// display status before the error handler is called
//
bool8 MemoryManagerTrack::display(void* ptr_a, bool8 block_mode_a) {

  // initialize with the pointer value
  //
  SysString output;
  output.assign((void*)ptr_a);
  output.insert(L"\taddress = 0x", 0);
  output.concat(L", source = ");

  // either print the name or unknown
  //
  if (name_d.length() > 0) {
    output.concat(name_d);
  }
  else {
    output.concat(L"unknown");
  }

  // either print block or single
  //
  if (block_mode_a) {
    output.concat(L" (block)\n");
  }
  else {
    output.concat(L" (single)\n");
  }

  // print the string
  //
  Console::put(output);

  // exit gracefully
  //
  return true;
}

// method: display
//
// arguments:
//  bool8 block_mode: (input) are we in block mode?
//
// return: a bool8 value indicating status
//
// display status before the error handler is called
//
bool8 MemoryManagerTrack::display(bool8 block_mode_a) {

  // initialize with a label
  //
  SysString output(L"source = ");

  // either print the name or unknown
  //
  if (name_d.length() > 0) {
    output.concat(name_d);
  }
  else {
    output.concat(L"unknown");
  }

  // either print block or single
  //
  if (block_mode_a) {
    output.concat(L" (block)");
  }
  else {
    output.concat(L" (single)");
  }

  // print the string
  //
  Console::put(output);

  // exit gracefully
  //
  return true;
}

// method: clear
//
// arguments:
//  Integral::CMODE cmode: (input) clear mode (ignored)
//
// return: logical error status
//
// before clearing and releasing memory, this method this method
// checks the internal storage and ensures that no unreleased memory
// exists. if any violation is found it is reported. Note that the
// cmode flag is ignored.
//
bool8 MemoryManagerTrack::clear(Integral::CMODE cmode_a) {

  if (debug_level_d > Integral::BRIEF) {
    SysString var(L"class");
    SysString output;
    //output.debugStr(name(), L"clear", var, name_d);
    Console::put(output);
  }

  if ((!used_d.isEmpty()) || (!block_allocated_d.isEmpty())) {
    
    // only error if we are not already exiting
    //
    if (!Error::isExiting()) {
    
      // print out message that memory is still in use
      //
      static bool8 shown_header = false;
      
      if (!shown_header) {
	shown_header = true;
	Console::put(L"\nError: Dynamic memory not deleted\n");
      }

      // declare local variable
      //
      void* node;
      
      // check if used heap is empty or not
      //
      while (!used_d.isEmpty()) {
	if (!used_d.extractMax(node)) {
	  display();
	  Error::handle(name(), L"clear", ERR_NOTFND, __FILE__, __LINE__);
	}
	display(node);
      }

      // declare local variable
      //      
      void* ptr;
      
      // check if block allocated heap is empty or not
      //
      while (!block_allocated_d.isEmpty()) {
	if (!block_allocated_d.extractMax(ptr)) {
	  display(true);
	  Error::handle(name(), L"clear", ERR_NOTFND, __FILE__, __LINE__);
	}
	display(ptr, true);
      }
    }
  }
  
  // release memory
  //
  allocated_d.clear(Integral::FREE);
  used_d.clear(Integral::FREE);
  block_allocated_d.clear(Integral::FREE);

  // exit gracefully
  //
  return true;
}  

// method: releaseMgrs
//
// arguments: none
//
// return: logical error status
//
// this method checks cleans up all registered MemoryManager objects
// and checks for unreleased memory. it is called in the exit routines
// of Integral and Exit so that errors can be reported before the
// error reporting mechanisms are deleted.
//
bool8 MemoryManagerTrack::releaseMgrs() {

  // remove each registered manager and call its clear method
  //
  void* ptr = (void*)NULL;
  while ((allocated_mgrs_d != (SysHeap*)NULL)
	 && (!allocated_mgrs_d->isEmpty())) {
    allocated_mgrs_d->extractMax(ptr);
    ((MemoryManagerTrack*)ptr)->clear();
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
const SysString MemoryManagerTrack::CLASS_NAME(L"MemoryManagerTrack");

// static instantiations: SysHeap
//
SysHeap* MemoryManagerTrack::allocated_mgrs_d = (SysHeap*)NULL;
