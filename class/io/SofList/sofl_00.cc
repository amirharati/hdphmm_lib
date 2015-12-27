// file: $isip/class/io/SofList/sofl_00.cc
// version: $Id: sofl_00.cc 5013 2000-09-26 15:38:58Z zhao $
//

// isip include files
//
#include "SofList.h"

// method: destructor
//
// arguments: none
//
// return: none
//
// this is the default destructor for the SofList class
//
SofList::~SofList() {

  // clear the list entries
  //
  clear();
  
  // delete the stack
  //
  if (stack_d != (SofNode**)NULL) {
    mgr_d.releaseBlock(stack_d);
  }
  
  // exit gracefully
  //
}

// method: copy constructor
//
// arguments:
//  const SofList& arg: (input) SofList object
//
// return: none
//
// this is the copy constructor for the SofList class
//
SofList::SofList(const SofList& arg_a) {

  // set pointers to null and initialize data
  //
  root_d = (SofNode*)NULL;
  current_d = root_d;
  table_d = (SofSymbolTable*)NULL;

  // initialize stack
  //
  stack_d = (SofNode**)NULL;
  stack_size_d = DEF_STACK_SIZE;
  stack_ptr_d  = DEF_STACK_PTR;
  stack_frame_d  = DEF_STACK_FRAME;
  
  // debugging parameters
  //
  debug_level_d = Integral::NONE;

  // assign the data
  //
  assign(arg_a);

  // exit gracefully
  //
}

// method: default constructor
//
// arguments: none
//
// return: none
//
// this is the default constructor for the SofList class
//
SofList::SofList() {

  // set pointers to null and initialize data
  //
  root_d = (SofNode*)NULL;
  current_d = root_d;
  table_d = (SofSymbolTable*)NULL;

  // initialize stack
  //
  stack_d = (SofNode**)NULL;
  stack_size_d = DEF_STACK_SIZE;
  stack_ptr_d  = DEF_STACK_PTR;
  stack_frame_d  = DEF_STACK_FRAME;
  
  // debugging parameters
  //
  debug_level_d = Integral::NONE;

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
const SysString SofList::CLASS_NAME(L"SofList");

// static instantiations: memory manager
//
MemoryManager SofList::mgr_d(sizeof(SofList), SofList::name());
