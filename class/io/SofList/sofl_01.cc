// file: $isip/class/io/SofList/sofl_01.cc
// version: $Id: sofl_01.cc 5118 2000-10-03 12:59:38Z picone $
//

// isip include files
//
#include "SofList.h"
#include <Console.h>

// method: debug
//
// arguments:
//  const unichar* message: (input) debugging message
//
// return: a bool8 value indicating status
//
bool8 SofList::debug(const unichar* message_a) const {

  // dump general information
  //
  SysString output;
  SysString value;

  // display the current node
  //
  const_cast<SofList*>(this)->display(value, current_d);
  output.debugStr(name(), message_a, L"current_d", value);
  Console::put(output);

  // display the whole tree
  //
  if (root_d != (SofNode*)NULL) {
    value.clear();
    output.debugStr(name(), message_a, L"root_d", value);
    Console::put(output);
    const_cast<SofList*>(this)->displayTree();
  }
  else {
    value.assign(root_d);
    output.debugStr(name(), message_a, L"root_d", value);
    Console::put(output);
  }

  // debugging parameters
  //
  value.assign(debug_level_d);
  output.debugStr(name(), message_a, L"debug_level_d", value);
  Console::put(output);

  // exit gracefully
  //
  return true;
}


// method: display
//
// arguments: none
//
// return: a bool8 value indicating status
//
// this method dumps the object index
//
bool8 SofList::display() {

  // start from the root node
  //
  SysString output;
  SofNode* node = root_d;
  
  if (node == (SofNode*)NULL) {
    output.assign(L"empty tree");
    Console::put(output);
    return true;
  }

  // traverse the tree iteratively using the stack
  //
  int32 i = 0;
  while (1) {
    
    while (node != (SofNode*)NULL) {
      push(node);
      node = node->left_d;
    }
    
    if (pop(node)) {
      display(output, node);
      Console::put(output);
      i++;
      node = node->right_d;
    }
    else {
      break;
    }
  }

  output.assign(i);
  output.insert(L"----------------\ntotal of ", 0);
  output.concat(L" nodes");
  Console::put(output);

  // exit gracefully
  //
  return false;
}

// method: display
//
// arguments:
//  SysString& output: (output) string of node
//  SofNode* node: (input) node to be displayed
//
// return: a bool8 value indicating status
//
// this method dumps the object index into a string
//
bool8 SofList::display(SysString& output_a, SofNode* node_a) {

  output_a.clear();
  
  // check argument
  //
  if (node_a == (SofNode*)NULL) {
    return false;
  }

  // display a message
  //
  SysString number;
  
  // pull out the object's name, either in numeric or symbol form
  //
  if (table_d != (SofSymbolTable*)NULL) {
    table_d->getSymbol(output_a, node_a->name_d);
  }
  else {
    output_a.assign((int32)node_a->name_d);
    output_a.insert(L"#", 0);
  }

  // append the tag
  //
  output_a.concat(L".");
  number.assign((int32)node_a->tag_d);
  output_a.concat(number);

  // append the position
  //
  output_a.concat(L":\t(pos = ");
  number.assign((int32)node_a->pos_d);
  output_a.concat(number);

  // append the size
  //
  output_a.concat(L", size = ");
  number.assign((int32)node_a->size_d);
  output_a.concat(number);

  // finish off the string
  //
  output_a.concat(L")");
  
  // exit gracefully
  //
  return true;
}

// method: displayTree
//
// arguments:
//  SofNode* node: (input) node to be displayed
//  int32 level: (input) level within the tree
//
// return: a bool8 value indicating status
//
// this method dumps the object index as a tree
//
bool8 SofList::displayTree(SofNode* node_a, int32 level_a) {

  // check the node
  //
  if (node_a == (SofNode*)NULL) {
    Console::put(L"empty tree");
    return true;
  }
  
  // display the current node
  //
  SysString output(SysString::MAX_LENGTH);
  display(output, node_a);

  // insert leading spaces for level
  //
  if (level_a > 0) {
    unichar preface[level_a + 1];
    for (int32 i = 0; i < level_a; i++) {
      preface[i] = L' ';
    }
    preface[level_a] = (unichar)NULL;
    output.insert(preface, 0);
  }
  
  Console::put(output);

  // display left and right children trees
  //
  if (node_a->left_d != (SofNode*)NULL) {
    displayTree(node_a->left_d, level_a + 1);
  }
  if (node_a->right_d != (SofNode*)NULL) {
    displayTree(node_a->right_d, level_a + 1);
  }
  
  // exit gracefully
  //
  return false;
}
