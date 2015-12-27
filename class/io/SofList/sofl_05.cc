// file: $isip/class/io/SofList/sofl_05.cc
// version: $Id: sofl_05.cc 6809 2001-04-24 16:33:22Z duncan $
//

// isip include files
//
#include "SofList.h"
#include <MemoryManager.h>
#include <Console.h>

// method: add
//
// arguments:
//  int32 name: (input) object name
//  int32 tag: (input) object tag
//  int32 pos: (input) object position
//  int32 size: (input) object size
//
// return: a bool8 value indicating status
//
// add a new node to the list
//
bool8 SofList::add(int32 name_a, int32 tag_a, int32 pos_a, int32 size_a) {

  // check argument
  //
  if (name_a == SofSymbolTable::NO_SYMB) {
    return Error::handle(name(), L"add", Error::ARG, __FILE__, __LINE__);
  }
  
  // we need a new node to hold this, declare and copy data
  //
  SofNode* tmp = newNode();
  tmp->name_d = name_a;
  tmp->tag_d = tag_a;
  tmp->pos_d = pos_a;
  tmp->size_d = size_a;

  // add the new node
  //
  return addNode(tmp);
}

// method: addQuick
//
// arguments:
//  int32 name: (input) object name
//  int32 tag: (input) object tag
//  int32 pos: (input) object position
//  int32 size: (input) object size
//
// return: a bool8 value indicating status
//
// add a new node to the list quickly. this method assumes that the
// previous call added a node that is less than the current node and
// will fall directly adjacent to the new node, hence no tree
// searching is necessary. this speeds up the common case of adding
// consecutive tokens for the same object in SofParser.
//
bool8 SofList::addQuick(int32 name_a, int32 tag_a, int32 pos_a, int32 size_a) {

  // we need a new node to hold this, declare and copy data
  //
  SofNode* tmp = newNode();
  tmp->name_d = name_a;
  tmp->tag_d = tag_a;
  tmp->pos_d = pos_a;
  tmp->size_d = size_a;

  // make sure the right branch is null
  //
  if ((current_d == (SofNode*)NULL) ||
      (current_d->right_d != (SofNode*)NULL)) {
    return Error::handle(name(), L"addQuick", ERR, __FILE__, __LINE__);
  }

  // add this directly to the right of the current node
  //
  current_d->right_d = tmp;
  tmp->parent_d = current_d;
  current_d = tmp;

  // exit gracefully
  //
  return true;
}


// method: addNode
//
// arguments:
//  SofNode* node: (input) node to add into tree
//
// return: a bool8 value indicating status
//
// add the new node to the tree
//
bool8 SofList::addNode(SofNode* node_a) {

  // check for special case of this being the first node
  //
  if (root_d == (SofNode*)NULL) {
    root_d = node_a;
    node_a->parent_d = (SofNode*)NULL;
    current_d = root_d;
    return true;
  }

  // now find a space in the tree
  //
  SofNode* node = root_d;

  // when we find the space, we reset the tmp pointer
  //
  while (node_a != (SofNode*)NULL) {
    
    // compare the new node against the current
    //

    // if lesser, move to the left
    //
    if (nodeLt(node_a, node)) {
      if (node->left_d != (SofNode*)NULL) {
	node = node->left_d;
      }
      else {
	node->left_d = node_a;
	node_a->parent_d = node;
	current_d = node_a;
	node_a = (SofNode*)NULL;
      }
    }

    // if greater, move to the right
    //
    else if (nodeGt(node_a, node)) {
      if (node->right_d != (SofNode*)NULL) {
	node = node->right_d;
      }
      else {
	node->right_d = node_a;
	node_a->parent_d = node;
	current_d = node_a;
	node_a = (SofNode*)NULL;
      }
    }

    // if equal, we error. note that placing the check here is more
    // efficient then calling the find() method outside of this
    // method.
    //
    else {
      SysString output(L"Object ");
      if (table_d != (SofSymbolTable*)NULL) {
	SysString n;
	table_d->getSymbol(n, node_a->name_d);
	output.concat(L"'");
	output.concat(n);
	output.concat(L"'");
      }
      else {
	output.concat(L"[#");
	output.concat(node_a->name_d);
	output.concat(L"]");
      }
      output.concat(L" has been defined multiple times.\n");
      Console::put(output);
      return Error::handle(name(), L"addNode", ERR_EXISTS, __FILE__, __LINE__,
			   Error::WARNING);
    }
  }

  // exit gracefully
  //
  return true;
}

// method: remove
//
// arguments: none
//
// return: a bool8 value indicating status
//
// delete the current node from the tree
//
bool8 SofList::remove() {

  // check the current node
  //
  if (current_d == (SofNode*)NULL) {
    return Error::handle(name(), L"remove", ERR_CURR, __FILE__, __LINE__);
  }

  SofNode** parent_ptr = (SofNode**)NULL;

  // if the parent is null, this is the root node
  //
  if (current_d->parent_d == (SofNode*)NULL) {
    parent_ptr = &root_d;
  }
  
  // determine if this is the left or right node
  //
  else if (current_d->parent_d->left_d == current_d) {
    parent_ptr = &(current_d->parent_d->left_d);
  }
  else if (current_d->parent_d->right_d == current_d) {
    parent_ptr = &(current_d->parent_d->right_d);
  } 
  
  // if either of the children are null, just pop the other child up
  // to take the place of the node which is leaving
  //
  if (current_d->left_d == (SofNode*)NULL) {
    *parent_ptr = current_d->right_d;
    if (current_d->right_d != (SofNode*)NULL) {
      current_d->right_d->parent_d = current_d->parent_d;
    }
    deleteNode(current_d);
  }
  else if (current_d->right_d == (SofNode*)NULL) {
    *parent_ptr = current_d->left_d;
    if (current_d->left_d != (SofNode*)NULL) {
      current_d->left_d->parent_d = current_d->parent_d;
    }
    deleteNode(current_d);
  }

  // both children exist. set the parent to point to the left and
  // re-insert the right.
  //
  else {
    SofNode* tmp = current_d->right_d;
    *parent_ptr = current_d->left_d;
    current_d->left_d->parent_d = current_d->parent_d;

    deleteNode(current_d);

    // tmp, the right leaf, is now unlinked, so re-insert it
    //
    tmp->parent_d = (SofNode*)NULL;
    addNode(tmp);
  }
  
  // exit gracefully
  //
  return true;
}

//-----------------------------------------------------------------------------
//
// the below methods have to be in the same file so they can utilize the
// same static MemoryManager
//
//-----------------------------------------------------------------------------

static MemoryManager mgr(sizeof(SofNode));

// method: newNode
//
// arguments: none
//
// return: a pointer to a new node
//
// get and initialize a new node
//
SofNode* SofList::newNode() {

  // grab a node from the memory manager
  //
  SofNode* tmp = (SofNode*)mgr.get();

  // leave the node data (name, tag, pos, size) undefined
  //

  // clear the pointers
  //
  tmp->left_d = (SofNode*)NULL;
  tmp->right_d = (SofNode*)NULL;
  tmp->parent_d = (SofNode*)NULL;

  // return the new node
  //
  return tmp;
}

// method: deleteNode
//
// arguments:
//  SofNode* node: (input) node to be deleted
//
// return: a bool8 value indicating status
//
// note: this node better be unlinked or we will have problems
//
bool8 SofList::deleteNode(SofNode* node_a) {

  // give the node back to the manager
  //
  mgr.release(node_a);

  // exit gracefully
  //
  return true;
}
