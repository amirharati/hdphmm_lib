// file: $isip/class/system/MemoryManager/MemoryNode.h
// version: $Id: MemoryNode.h 2589 2000-01-20 23:14:40Z duncan $
//

// this file is for internal use only
//
#ifdef ISIP_INTERNAL_USE_ONLY

// isip include files
//
#ifndef ISIP_INTEGRAL
#include <Integral.h>
#endif

// make sure definitions are only made once
//
#ifndef ISIP_MEMORY_NODE
#define ISIP_MEMORY_NODE

// MemoryNode: a node for the MemoryManager linked lists
//
typedef struct memory_manager_node MemoryNode;

struct memory_manager_node {

  // pointer to data
  //
  void* ptr_d;

  // pointer to next entry
  //
  MemoryNode* next_d;

};

// end of include file
// 
#endif
#endif
