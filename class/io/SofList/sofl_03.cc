// file: $isip/class/io/SofList/sofl_03.cc
// version: $Id: sofl_03.cc 5659 2000-11-22 17:23:12Z picone $
//

// isip include files
//
#include "SofList.h"

// method: assign
//
// arguments:
//  const SofList& arg: (input) list to be copied
//
// return: a bool8 value indicating status
//
// this is the direct assignment method. it requires the SofSymbolTable
// has been set up
//
bool8 SofList::assign(const SofList& arg_a) {
  
  // save the current pointer so as to not modify the argument
  //
  SofNode* cur = arg_a.current_d;
  
  // loop through the classes
  //
  for (int32 name = arg_a.getNameCount(); name >= 0; name--) {
    
    // loop through the tags
    //
    for (int32 tag = const_cast<SofList&>(arg_a).first(name); tag != NO_TAG;
	 tag = const_cast<SofList&>(arg_a).next(name, tag)) {

      // add the tag
      //
      add(name, tag, arg_a.getPosition(), arg_a.getSize());
    }
  }

  // copy over the symbol table
  //
  if (arg_a.table_d != (SofSymbolTable*)NULL) {
    setTable(*arg_a.table_d);
  }
  
  // copy over the debug level
  //
  setDebug(arg_a.debug_level_d);

  // restore the current pointer
  //
  const_cast<SofList&>(arg_a).current_d = cur;
    
  // exit gracefully
  //
  return true;
}

// method: clear
//
// arguments:
//  Integral::CMODE ctype: (input) clear mode
//
// return: a bool8 value indicating status
//
// this method deletes the tree regardless of the clear mode
//
bool8 SofList::clear(Integral::CMODE ctype_a) {
  
  // iterate through and delete all nodes
  //
  SofNode* node = root_d;
  SofNode* right = (SofNode*)NULL;

  int32 i = 0;
  
  if (node != (SofNode*)NULL) {
    
    // traverse the tree iteratively using the stack
    //
    while (1) {
      
      // push the leftmost branch onto the stack
      //
      while (node != (SofNode*)NULL) {
	push(node);
	node = node->left_d;
      }

      // pop and clear the right branches
      //
      if (pop(node)) {
	right = node->right_d;
	deleteNode(node);
	i++;
	node = right;
      }
      else {
	break;
      }
    }
  }

  root_d = (SofNode*)NULL;
  current_d = root_d;

  // print debug information
  //
  if (debug_level_d == Integral::ALL) {
    fprintf(stdout, "SofList::clear deleted %d nodes\n", i);
  }

  // exit gracefully
  //
  return true;
}

// method: memSize
//
// arguments: none
//
// return: a int32 number
//
// this method determines the total amount of memory used by this object
//
int32 SofList::memSize() {

  int32 size = 0;

  // the size of the binary tree
  //
  size += getCount() * sizeof(SofNode);

  // pointers (root_d, current_d)
  //
  size += 3 * sizeof(SofNode*);

  // pointer to the symbol table (the symbol table itself will be
  // counted elsewhere).
  //
  size += sizeof(SofSymbolTable*);

  // the stack and its pointers
  //
  size += sizeof(SofNode**);
  size += sizeof(SofNode*) * stack_size_d;
  size += sizeof(stack_size_d);
  size += sizeof(stack_ptr_d);
  size += sizeof(stack_frame_d);

  size += sizeof(debug_level_d);

  // exit gracefully
  //
  return size;
}
