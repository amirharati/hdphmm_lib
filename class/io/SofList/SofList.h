// file: $isip/class/io/SofList/SofList.h
// version: $Id: SofList.h 6291 2001-02-06 20:39:43Z duncan $
//

// make sure definitions are only made once
//
#ifndef ISIP_SOF_LIST
#define ISIP_SOF_LIST

// isip include files
//
#ifndef ISIP_SYS_STRING
#include <SysString.h>
#endif

#define ISIP_INTERNAL_USE_ONLY
#include "SofNode.h"
#undef ISIP_INTERNAL_USE_ONLY

#ifndef ISIP_SOF_SYMBOL_TABLE
#include <SofSymbolTable.h>
#endif

// SofList: a binary search tree used to hold indices for Sof files.
// it is used to keep track of a sorted list of objects.
// 
// a binary search tree is a linked data structure in which each node is
// an object. each node has keys as well as pointers to its left, right
// and parent nodes. let x be a node in a binary search tree:
//   if y is a node in the left subtree of x, then key[y] <= key[x],
//   if y is a node in the right subtree of x, then key[x] <= key[y]
// 
// in this SofList, a name and a tag are used as the keys of a node.
// when comparing two nodes, the names are compared first, if the names
// are the same, the tags are compared. a good tutorial on heaps can be
// found at :
// 
//  T.H. Cormen, C.E. Leiserson and R.L. Rivest, "Introduction to
//  Algorithms," McGraw-Hill, New York, New York, USA, pp. 244-249, 1997.
//
class SofList {
  
  //---------------------------------------------------------------------------
  //
  // public constants
  //
  //---------------------------------------------------------------------------
public:

  // define the class name
  //
  static const SysString CLASS_NAME;

  //----------------------------------------
  //
  // other important constants
  //
  //----------------------------------------  

  // internal stack constants
  //
  static const int32 STACK_SIZE = 2048;
  static const int32 GROW_SIZE = 1024;
  
  //----------------------------------------
  //
  // default values and arguments
  //
  //----------------------------------------  

  // default values for stack
  //
  static const int32 DEF_STACK_SIZE = 0;
  static const int32 DEF_STACK_PTR = 0;
  static const int32 DEF_STACK_FRAME = 0;
  
  // a dummy tag for a name not in the soflist
  //
  static const int32 NO_TAG = -2147483647;
  
  //----------------------------------------
  //
  // error codes
  //
  //----------------------------------------  

  static const int32 ERR		   = 10100;
  static const int32 ERR_SYMB	   = 10102;
  static const int32 ERR_COPY	   = 10104;
  static const int32 ERR_DELETE	   = 10105;
  static const int32 ERR_ADD	   = 10106;
  static const int32 ERR_EXISTS	   = 10107;
  static const int32 ERR_CURR       = 10108;

  //---------------------------------------------------------------------------
  //
  // protected data
  //
  //---------------------------------------------------------------------------
protected:

  // the root node of the binary tree
  //
  SofNode* root_d;
  
  // the current node
  //
  SofNode* current_d;
  
  // a pointer to the symbol table
  //
  SofSymbolTable* table_d;
  
  // we need an internal stack to avoid recursion in the binary tree search
  //
  SofNode** stack_d;
  int32 stack_size_d;///*
  int64 stack_ptr_d;
  int64 stack_frame_d;

  // debugging parameters
  //
  Integral::DEBUG debug_level_d;

  // a memory manager
  //
  static MemoryManager mgr_d;
  
  //---------------------------------------------------------------------------
  //
  // required public methods
  //
  //---------------------------------------------------------------------------
public:

  // method: name
  //
  static const SysString& name() {
    return CLASS_NAME;
  }

  // other static methods
  //
  static bool8 diagnose(Integral::DEBUG debug_level);
  
  // method: setDebug
  //
  bool8 setDebug(Integral::DEBUG level) {
    debug_level_d = level;
    return true;
  }

  // other debug methods
  //
  bool8 debug(const unichar* msg) const;
  
  // destructor/constructor(s)
  //
  ~SofList();
  SofList();
  SofList(const SofList& arg);
  
  // assign methods
  //
  bool8 assign(const SofList& arg);

  // method: operator=
  //
  SofList& operator= (const SofList& arg) {
    if (!assign(arg)) {
      Error::handle(name(), L"operator=", Error::ARG, __FILE__, __LINE__);
    }      
    return *this;
  }
  
  // i/o methods:
  //  these methods are omitted because SofList can not write itself
  //   to an sof file
  //

  // equality methods:
  //  these methods are omitted because they are not useful for
  //  SofList objects
  //
  
  // memory management methods:
  //  new and delete are omitted because memory for SofList objects is not
  //  managed by the MemoryManager class
  //
  bool8 clear(Integral::CMODE ctype = Integral::DEF_CMODE);

  //---------------------------------------------------------------------------
  //
  // class-specific public methods:
  //  extensions to the required public methods
  //
  //---------------------------------------------------------------------------
  
  // memory size methods
  //
  int32 memSize();
  
  //---------------------------------------------------------------------------
  //
  // class-specific public methods:
  //  soflist manipulation methods
  //
  //---------------------------------------------------------------------------
  
  // add object methods
  //
  bool8 add(int32 name, int32 tag, int32 pos, int32 size);
  bool8 addQuick(int32 name, int32 tag, int32 pos, int32 size);
  
  // remove object methods
  //
  bool8 remove();
  
  // search objects methods
  //
  bool8 find(int32 name, int32 tag);
  int32 first(int32 name);
  int32 last(int32 name);
  int32 next(int32 name, int32 cur_tag);
  int32 prev(int32 name, int32 cur_tag);
  
  //---------------------------------------------------------------------------
  //
  // class-specific public methods:
  //  set and get methods
  //
  //---------------------------------------------------------------------------

  // note that there is no method for changing name or tag, as this would
  // alter the position of the object in the tree. to do this, delete
  // and re-insert the node with the new information.
  //
  
  // method: setTable
  //  this method sets the symbol table used by the names
  //  this table will only be used by the display methods, not internally
  //
  bool8 setTable(SofSymbolTable& table) {
    table_d = &table;
    return true;
  }
  
  // method: setPosition
  //
  bool8 setPosition(int32 pos) {
    if (current_d == (SofNode*)NULL) {
      return Error::handle(name(), L"setPosition", ERR_CURR, __FILE__,
			   __LINE__);
    }
    current_d->pos_d = pos;
    return true;
  }

  // method: setSize
  //
  bool8 setSize(int32 size) {
    if (current_d == (SofNode*)NULL) {
      return Error::handle(name(), L"setSize", ERR_CURR, __FILE__, __LINE__);
    }                  
    current_d->size_d = size;
    return true;
  }
  
  // method: getName
  //
  int32 getName() const {
    if (current_d == (SofNode*)NULL) {
      Error::handle(name(), L"getName", ERR_CURR, __FILE__, __LINE__);
      return (int32)SofSymbolTable::NO_SYMB;
    }                  
    return current_d->name_d;
  }
  
  // method: getTag
  //
  int32 getTag() const {
    if (current_d == (SofNode*)NULL) {
      Error::handle(name(), L"getTag", ERR_CURR, __FILE__, __LINE__);
      return (int32)NO_TAG;
    }                  
    return current_d->tag_d;
  }

  // method: getPosition
  //
  int32 getPosition() const {
    if (current_d == (SofNode*)NULL) {
      Error::handle(name(), L"getPosition", ERR_CURR, __FILE__, __LINE__);
      return (int32)-1;
    }                  
    return current_d->pos_d;
  }
  
  // method: getSize
  //
  int32 getSize() const {
    if (current_d == (SofNode*)NULL) {
      Error::handle(name(), L"getSize", ERR_CURR, __FILE__, __LINE__);
      return (int32)-1;
    }                  
    return current_d->size_d;
  }
  
  // method: getNameCount
  //  this method counts the number of different classes
  //
  int32 getNameCount() const {    
    if (table_d == (SofSymbolTable*)NULL) {
      return 0;
    }
    return table_d->getCount();
  }
  
  // method: getCount
  //   this method gets the total number of nodes in the tree
  //
  int32 getCount() {
    return getCount(root_d);
  }
  
  // method: getCount
  //  gets the number of nodes matching name
  //
  int32 getCount(int32 name) {
    return getCount(root_d, name);
  }
  
  //---------------------------------------------------------------------------
  //
  // private methods
  //
  //---------------------------------------------------------------------------
private:

  // memory management methods
  //
  SofNode* newNode();		
  bool8 deleteNode(SofNode* node);

  // add object methods
  //
  bool8 addNode(SofNode* node);
  
  // search objects methods
  //
  SofNode* findNode(int32 name, int32 tag);
  SofNode* findNode(int32 name);

  // methods to compare two SofNodes
  //

  // method: nodeGt
  //
  bool8 nodeGt(const SofNode* node, int32 name, int32 tag) const {
    return ((node->name_d > name) ||
	    ((node->name_d == name) && (node->tag_d > tag)));
  }
    
  // method: nodeLt
  //
  bool8 nodeLt(const SofNode* node, int32 name, int32 tag) const {
    return ((node->name_d < name) ||
	    ((node->name_d == name) && (node->tag_d < tag)));
  }

  // method: nodeGt
  //
  bool8 nodeGt(const SofNode* node, int32 name) const {
    return (node->name_d > name);
  }

  // method: nodeLt
  //
  bool8 nodeLt(const SofNode* node, int32 name) const {
    return (node->name_d < name);
  }

  // method: nodeGt
  //
  bool8 nodeGt(const SofNode* node_1, const SofNode* node_2) const {
    return nodeGt(node_1, node_2->name_d, node_2->tag_d);
  }

  // method: nodeLt
  //
  bool8 nodeLt(const SofNode* node_1, const SofNode* node_2) const {
    return nodeLt(node_1, node_2->name_d, node_2->tag_d);
  }

  // method: nodeEq
  //
  bool8 nodeEq(const SofNode* node, int32 name) const {
    return (node->name_d == name);
  }
  
  // count nodes methods
  //
  int32 getCount(SofNode* node);
  int32 getCount(SofNode* node, int32 name);
  
  // internal stack management methods
  //

  // method: push
  //
  bool8 push(SofNode* ptr) {
    if (stack_ptr_d == stack_size_d) {
      mgr_d.reallocateBlock((void***)&stack_d, stack_size_d, STACK_SIZE);
    }
    stack_d[stack_ptr_d++] = ptr;
    return true;
  }

  // method: pop
  //
  bool8 pop(SofNode*& ptr) {
    if (stack_ptr_d <= stack_frame_d) {
      ptr = (SofNode*)NULL;
      return false;
    }
    ptr = stack_d[--stack_ptr_d];
    return true;
  }
  
  bool8 pushFrame();
  bool8 popFrame();
  
  // low-level debugging methods
  //
  bool8 display();
  bool8 display(SysString& str, SofNode* node);

  // method: displayTree
  //
  bool8 displayTree() {
    return displayTree(root_d, 0);
  }
  bool8 displayTree(SofNode* node, int32 level);
};

// end of include file
//
#endif
