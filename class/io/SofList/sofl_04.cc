// file: $isip/class/io/SofList/sofl_04.cc
// version: $Id: sofl_04.cc 6291 2001-02-06 20:39:43Z duncan $
//

// isip include files
//
#include "SofList.h"
#include <Console.h>

// method: find
//
// arguments:
//  int32 name: (input) class name
//  int32 tag: (input) class tag
//
// return: a bool8 value indicating status
//
// this method finds the name.tag in the list. if found, the current
// pointer is set to this node and subsequent operations will operate
// on this node
//
bool8 SofList::find(int32 name_a, int32 tag_a) {

  // find the node of the given name and tag
  //
  SofNode* tmp = findNode(name_a, tag_a);

  // if node not found, return
  //
  if (tmp == (SofNode*)NULL) {
    return false;
  }
  
  // set the node found to be current
  //
  current_d = tmp;
  
  // exit gracefully
  //
  return true;
}

// method: first
//
// arguments:
//  int32 name: (input) name of object to find
//
// return: int32 tag number
//
// this method finds the first object of the specified name
//
int32 SofList::first(int32 name_a) {
  
  // check for special case of empty tree
  //
  if (root_d == (SofNode*)NULL) {
    return NO_TAG;
  }
  
  // now find position in the tree of specified name
  //
  SofNode* node = findNode(name_a);
  
  // make sure it exists
  //
  if (node == (SofNode*)NULL) {
    return NO_TAG;
  }
  
  // set the node found to be the current node, it may not be the first
  //
  current_d = node;
  
  // now we are at the topmost node in the tree of the correct
  // name. we now want to find the leftmost leaf with the same name as
  // it will have the lowest tag.
  //
  while (node != (SofNode*)NULL) {

    if (nodeEq(node, name_a)) {

      // set the current node
      //
      current_d = node;

      // traverse to the left
      //
      node = node->left_d;
    }
    else {

      // names are not equal, go to the right
      //
      node = node->right_d;
    }
  }

  // exit gracefully
  //
  return current_d->tag_d;
}

// method: last
//
// arguments:
//  int32 name: (input) name of object to find
//
// return: int32 tag number
//
// this method finds the last object of the specified name
//
int32 SofList::last(int32 name_a) {

  // check for special case of empty tree
  //
  if (root_d == (SofNode*)NULL) {
    return NO_TAG;
  }
  
  // now find position in the tree
  //
  SofNode* node = findNode(name_a);

  // make sure it exists
  //
  if (node == (SofNode*)NULL) {
    return NO_TAG;
  }
  
  // set the node found to be the current node, it may not be the last
  //
  current_d = node;
  
  // now we are at the topmost node in the tree of the correct
  // name. We now want to find the rightmost leaf with the same name as
  // it will have the highest tag.
  //
  while (node != (SofNode*)NULL) {

    if (nodeEq(node, name_a)) {

      // set the current node
      //
      current_d = node;
      
      // traverse to the right
      //
      node = node->right_d;
    }
    else {

      // names are not equal, go to the left
      //
      node = node->left_d;
    }
  }

  // exit gracefully
  //
  return current_d->tag_d;
}

// method: next
//
// arguments:
//  int32 name: (input) name of object to find
//  int32 tag: (input) tag number we must exceed
//
// return: int32 tag
//
// this method finds an object of specified name with a tag exceeding
// the specified value
//
int32 SofList::next(int32 name_a, int32 tag_a) {

  // check for special case of empty tree
  //
  if (root_d == (SofNode*)NULL) {
    return NO_TAG;
  }
  
  // now find position in the tree
  //
  SofNode* node = findNode(name_a);
  
  // make sure it exists
  //
  if (node == (SofNode*)NULL) {
    return NO_TAG;
  }
  
  // now we are at the topmost node in the tree of the correct
  // name.  We now want to find the leftmost leaf with the same name as
  // it will have the lowest tag, but make sure it is greater than the
  // specified tag
  //
  bool8 flag = false;
  
  while (1) {

    // traverse to the left as far as possible
    //
    while (node != (SofNode*)NULL) {
      push(node);
      node = node->left_d;
    }

    // now pop to the right
    //
    if (pop(node)) {

      // this made perfect sense at the time :)
      //
      if (nodeEq(node, name_a) &&	
	  nodeGt(node, name_a, tag_a) &&
	  ((!flag) ||
	   (flag && (!nodeGt(node, current_d))))) {
	
	// set the current node
	//
	current_d = node;
	flag = true;
      }
      node = node->right_d;
    }
    else {
      break;
    }
  }

  // if not found
  //
  if (!flag) {
    return NO_TAG;
  }
  
  // exit gracefully
  //
  return current_d->tag_d;
}

// method: prev
//
// arguments:
//  int32 name: (input) name of object to find
//  int32 tag: (input) tag number we must precede
//
// return: int32 tag
//
// this method finds an object of specified name with a tag preceding
// the specified value
//
int32 SofList::prev(int32 name_a, int32 tag_a) {

  // check for special case of empty tree
  //
  if (root_d == (SofNode*)NULL) {
    return NO_TAG;
  }
  
  // now find position in the tree
  //
  SofNode* node = findNode(name_a);

  // make sure it exists
  //
  if (node == (SofNode*)NULL) {
    return NO_TAG;
  }
  
  // now we are at the topmost node in the tree of the correct
  // name. We now want to find the rightmost leaf with the same name as
  // it will have the highest tag, but make sure it is less than the
  // specified tag
  //
  bool8 flag = false;

  while (1) {

    // traverse to the right
    //
    while (node != (SofNode*)NULL) {
      push(node);
      node = node->right_d;
    }

    // pop to the left
    //
    if (pop(node)) {

      // this made perfect sense at the time :)
      //
      if (nodeEq(node, name_a) && nodeLt(node, name_a, tag_a) &&
	  ((!flag) || (flag && !(nodeLt(node, current_d))))) {
	
	// set the current node
	//
	current_d = node;
	flag = true;
      }
      node = node->left_d;
    }
    else {
      break;
    }
  }

  // if not found
  // 
  if (!flag) {
    return NO_TAG;
  }
  
  // exit gracefully
  //
  return current_d->tag_d;
}

// method: findNode
//
// arguments:
//  int32 name: (input) class name
//  int32 tag: (input) class tag
//
// return: an SofNode* pointer
//
// if the specified node is in the list, return a pointer to it.
//
SofNode* SofList::findNode(int32 name_a, int32 tag_a) {
  
  // check for special case of empty tree
  //
  if (root_d == (SofNode*)NULL) {
    return root_d;
  }

  // start from the root node
  //
  SofNode* node = root_d;

  // initialize while loop
  //
  bool8 found = false;
  
  // loop until found
  //
  while (!found) {

    // if greater, move to the left
    //
    if (nodeGt(node, name_a, tag_a)) {
      if (node->left_d != (SofNode*)NULL) {
	node = node->left_d;
      }
      else {
	return (SofNode*)NULL;
      }
    }

    // if lesser, move to the right
    //
    else if (nodeLt(node, name_a, tag_a)) {
      if (node->right_d != (SofNode*)NULL) {
	node = node->right_d;
      }
      else {
	return (SofNode*)NULL;
      }
    }
    else {
      found = true;
    }
  } 
  
  // exit gracefully
  //
  return node;
}

// method: findNode
//
// arguments:
//  int32 name: (input) class name
//
// return: an SofNode* pointer
// 
// find the topmost node with specified name in the tree
//
SofNode* SofList::findNode(int32 name_a) {
  
  // check for special case of empty tree
  //
  if (root_d == (SofNode*)NULL) {
    return root_d;
  }

  // start from the root node
  //
  SofNode* node = root_d;

  // initialize loop
  //
  bool8 found = false;

  // loop until found
  //
  while (!found) {

    // move to the left if greater
    //
    if (nodeGt(node, name_a)) {
      if (node->left_d != (SofNode*)NULL) {
	node = node->left_d;
      }
      else {
	return (SofNode*)NULL;
      }
    }

    // move to the right if lesser
    //
    else if (nodeLt(node, name_a)) {
      if (node->right_d != (SofNode*)NULL) {
	node = node->right_d;
      }
      else {
	return (SofNode*)NULL;
      }
    }
    else {
      found = true;
    }
  } 

  // give debug output
  //
  if (debug_level_d == Integral::ALL) {
    SysString output;
    display(output, node);
    output.insert(L"starting at node:", 0);
    Console::put(output);
  }
  
  // exit gracefully
  //
  return node;
}

// method: getCount
//
// arguments:
//  SofNode* node: (input) node at which to start count
//
// return: int32 count
//
// count the number of nodes below specified node
//
int32 SofList::getCount(SofNode* node_a) {

  if (node_a == (SofNode*)NULL) {
    return (int32)0;
  }
  
  int32 i = 0;

  // traverse the tree iteratively using the stack
  //
  while (1) {

    while (node_a != (SofNode*)NULL) {
      push(node_a);
      node_a = node_a->left_d;
    }

    if (pop(node_a)) {
      i++;
      node_a = node_a->right_d;
    }
    else {
      break;
    }
  }
  
  // exit gracefully
  //
  return i;
}

// method: getCount
//
// arguments:
//  SofNode* node: (input) node at which to start count
//  int32 name: (input) symbol to count matches of
//
// return: int32 count
//
// this method counts the number of classes that match the specified
// name under and including the specified node.
//
int32 SofList::getCount(SofNode* node_a, int32 name_a) {

  if (node_a == (SofNode*)NULL) {
    return (int32)0;
  }
  
  int32 i = 0;

  // traverse the tree iteratively using the stack
  //
  while (1) {

    while (node_a != (SofNode*)NULL) {
      push(node_a);
      node_a = node_a->left_d;
    }

    if (pop(node_a)) {
      if (nodeEq(node_a, name_a)) {
	i++;
      }
      node_a = node_a->right_d;
    }
    else {
      break;
    }
  }
  
  // exit gracefully
  //
  return i;
}

// method: pushFrame
//
// arguments: none
//
// return: a bool8 value indicating status
//
// this method pushes an integer index for the previous stack frame on
// the list and resets the value of the stack frame index to the
// current frame.
//
bool8 SofList::pushFrame() {

  // push the integer onto the stack
  //
  push((SofNode*)stack_frame_d);

  // set a new stack frame pointer
  //
  stack_frame_d = stack_ptr_d;
  
  // exit gracefully
  //
  return true;
}

// method: popFrame
//
// arguments: none
//
// return: a bool8 value indicating status
//
// this method pops the current frame off the stack and sets the frame
// pointer to the previous frame.
//
bool8 SofList::popFrame() {

  // set stack pointer to frame pointer
  //
  stack_ptr_d = stack_frame_d;
  if (stack_ptr_d < 1) {
    stack_frame_d = (int32)0;
  }
  else {

    // pop the old frame pointer off the stack
    //
      /* pointer need to  use int64  */
    stack_frame_d = (int64)stack_d[--stack_ptr_d];
  }
  
  // exit gracefully
  //
  return true;
}
