// file: $isip/class/dstr/Node/Node.h
// version: $Id: Node.h 6494 2001-03-20 21:21:07Z duncan $
//

// make sure definitions are only made once
//
#ifndef ISIP_NODE
#define ISIP_NODE

// isip include files
//
#ifndef ISIP_STRING
#include <String.h>
#endif

#ifndef ISIP_DSTR_BASE
#include <DstrBase.h>
#endif

#ifndef ISIP_CHAR
#include <Char.h>
#endif

#ifndef ISIP_CONSOLE	
#include <Console.h>
#endif

// forward class definitions
//
template<class TObject> class NodeDiagnose;

// Node: a generic node template class. this is simply a container
// class for use by other classes. most likely, data structures such
// as linked-lists, queues, graphs, etc. will create their own node
// type which inherits this Node object.
//
template<class TObject>
class Node : public DstrBase {
  
  //---------------------------------------------------------------------------
  //
  // public constants
  //
  //---------------------------------------------------------------------------
public:
  
  // define the class name
  //
  static const String CLASS_NAME;

  //----------------------------------------
  //
  // i/o related constants
  //
  //----------------------------------------  
  
  static const String DEF_PARAM;
  
  //----------------------------------------
  //
  // default values and arguments
  //
  //----------------------------------------

  // default values
  //
    
  // default arguments to methods
  //
  
  //----------------------------------------
  //
  // error codes
  //
  //----------------------------------------  
  
  static const int32 ERR = 40000;
  static const int32 ERR_NOITEM = 40001;
  
  //---------------------------------------------------------------------------
  //
  // protected data
  //
  //---------------------------------------------------------------------------
protected:

  // a pointer to the item stored in this node:
  //  a NULL item is not valid and operations on a node containing a NULL
  //  item will typically result in an error
  //
  TObject* item_d;

  
  // debugging parameters and static memory manager
  //
  static Integral::DEBUG debug_level_d;
  static MemoryManager mgr_d;
  
  //---------------------------------------------------------------------------
  //
  // required public methods
  //
  //---------------------------------------------------------------------------
public:

  // static methods:
  //  diagnose method is moved outside the class header file and
  //  defined in the NodeDiagnose.h in order to avoid issues
  //  related to preprocessing of the diagnose code.
  //
  static const String& name();
  
  // method: setDebug
  //
  static bool8 setDebug(Integral::DEBUG debug_level) {
    debug_level_d = debug_level;
    return true;
  }

  // other debug methods
  //
  bool8 debug(const unichar* message) const;
    
  // method: destructor
  //
  ~Node() { }

  // method: default constructor
  //
  Node() {
    item_d = (TObject*)NULL;
  }

  // method: copy constructor
  //
  Node(const Node<TObject>& arg) {
    item_d = arg.item_d;
  }
  
  // method: assign
  //
  bool8 assign(const Node<TObject>& arg) {
    item_d = arg.item_d;
    return true;
  }

  // method: operator=
  //
  Node<TObject>& operator=(const Node<TObject>& arg) {
    assign(arg);
    return *this;
  }

  // equality methods:
  //  determines if the contents of the node are equivalent.
  //  this method calls the eq(TObject&) method for the items
  //  contained in the respective nodes to determine equivalence.
  //  only classes with an eq() method are available for use with
  //  this Node object
  //
  bool8 eq(const Node<TObject>& arg) const;
  
  // method: read
  //
  bool8 read(Sof& sof, int32 tag) {
    return read(sof, tag, name());
  }

  // method: write
  //
  bool8 write(Sof& sof, int32 tag) const {
    return write(sof, tag, name());
  }

  // other i/o methods:
  //  sofSize determines the amount of disk storage needed to store this object
  //  the read and write methods are for full object i/o. the readData and
  //  writeData methods handle i/o when this object is a component of another
  //  object
  //
  int32 sofSize() const;
  
  bool8 read(Sof& sof, int32 tag, const String& name);
  bool8 write(Sof& sof, int32 tag, const String& name) const;  
  
  bool8 readData(Sof& sof, const String& pname = DEF_PARAM, int32 size =
                   SofParser::FULL_OBJECT, bool8 param = true,
                   bool8 nested = false);
  bool8 writeData(Sof& sof, const String& pname = DEF_PARAM) const;

  // method: new
  //
  static void* operator new(size_t size) {
    return mgr_d.get();
  }

  // method: new[]
  //
  static void* operator new[](size_t size) {
    return mgr_d.getBlock(size);
  }

  // method: delete
  //
  static void operator delete(void* ptr) {
    mgr_d.release(ptr);
  }

  // method: delete[]
  //
  static void operator delete[](void* ptr) {
    mgr_d.releaseBlock(ptr);
  }

  // method: setGrowSize
  //
  static bool8 setGrowSize(int32 grow_size) {
    return mgr_d.setGrow(grow_size);
  }

  // other memory-management methods
  //
  bool8 clear(Integral::CMODE cmode = Integral::DEF_CMODE);
  
  //---------------------------------------------------------------------------
  //
  // class-specific public methods:
  //  extensions to required methods
  //
  //---------------------------------------------------------------------------

  // method: constructor
  //
  Node(TObject* item) {
    item_d = item;
  }

  // method: assign
  //
  bool8 assign(TObject* item) {
    item_d = item;
    return true;
  }

  // method: ne
  //
  bool8 ne(const Node<TObject>& arg) const {
    return (!eq(arg));
  }

  // method: lt
  //
  bool8 lt(const Node<TObject>& arg) const {
    return item_d->lt(*(arg.item_d));
  }

  // method: gt
  //
  bool8 gt(const Node<TObject>& arg) const {
    return item_d->gt(*(arg.item_d));
  }

  //---------------------------------------------------------------------------
  //
  // class-specific public methods:
  //  item manipulation methods
  //
  //---------------------------------------------------------------------------  
  // method: getItem
  //
  const TObject* getItem() const {
    return item_d;
  }

  // method: getItem
  //
  TObject* getItem() {
    return item_d;
  }

  // method: setItem
  //
  bool8 setItem(TObject* item) {
    return ((item_d = item) != (TObject*)NULL);
  }

  // method: accessByMode
  //
  TObject* accessByMode(TObject* ptr, ALLOCATION mode) const {
    
    if (!((mode == SYSTEM) ^ (ptr == (TObject*)NULL))) {
      Error::handle(name(), L"accessByMode", ERR, __FILE__, __LINE__);
    }
    else if (mode == USER) {
      return item_d;
    }
    else if ((mode == SYSTEM) && (item_d == (TObject*)NULL)) {
      ptr->clear();
      return (TObject*)NULL;
    }
    ptr->assign(*item_d);
    return ptr;
  }

  // method: assignByMode
  //
  bool8 assignByMode(TObject* ptr, ALLOCATION mode) {
    
    if (ptr == (TObject*)NULL) {
      return Error::handle(name(), L"assignByMode", ERR, __FILE__, __LINE__);
    }

    if (mode == SYSTEM) {
      item_d = new TObject(*ptr);
    }
    else {
      item_d = ptr;
    }

    return true;
  }

  //---------------------------------------------------------------------------
  //
  // class-specific public methods:
  //  hashing function
  //
  //---------------------------------------------------------------------------  
  // method: hash
  //
  // note that this will hash the pointer, not the value of the object
  //
  int32 hash(int32 capacity) const {
    
    // interpret the pointer as a ulong*
    //
    return Integral::hash((uint64)item_d, capacity);
  }
    
  //---------------------------------------------------------------------------
  //
  // private methods
  //
  //---------------------------------------------------------------------------
private:

  // friend class
  //
  template <class TObject_diagnose> 
  friend class NodeDiagnose;  
}; 

//-----------------------------------------------------------------------------
//
// we define non-integral constants at the end of class definition for
// templates (for non-templates these are defined in the default constructor)
//      
//-----------------------------------------------------------------------------

// constants: required constants such as the class name
//
template <class TObject>
const String Node<TObject>::CLASS_NAME(L"Node");

// constants: required constants for i/o methods
//
template <class TObject>
const String Node<TObject>::DEF_PARAM(L"item");

// static instantiations: debug level and memory manager
//
template <class TObject>
Integral::DEBUG Node<TObject>::debug_level_d = Integral::NONE;

template <class TObject>
MemoryManager Node<TObject>::mgr_d(sizeof(Node<TObject>), CLASS_NAME);

// below are all the methods for the Node template class
//

//-----------------------------------------------------------------------------
//
// required static methods
//
//-----------------------------------------------------------------------------

// method: name
//
// arguments: none
//
// return: a static String& containing the class name
//
// this method returns the class name
//
template<class TObject>
const String& Node<TObject>::name() {

  // create the static name string for this class and return it
  //
  static String cname(CLASS_NAME);
  cname.clear();
  cname.concat(CLASS_NAME);
  cname.concat(L"<");
  cname.concat(TObject::name());
  cname.concat(L">");

  // return the name
  //
  return cname;
}

//-----------------------------------------------------------------------------
//
// required debug methods
//
//-----------------------------------------------------------------------------

// method: debug
//
// arguments:
//  const unichar* message: (input) information message
//
// return: a bool8 value indicating status
//
// this method dumps the contents of an object to the console
// 
template<class TObject>
bool8 Node<TObject>::debug(const unichar* message_a) const {

  // declare local variables
  //
  String output;
  String value;

  // call the debug method of the item
  //
  if (item_d != (TObject*)NULL) {
    item_d->debug(message_a);
  }
  else {
    value.assign(item_d);
    output.debugStr(name(), message_a, L"item_d", value);
    Console::put(output);
  }
  
  // exit gracefully
  // 
  return true;
}

//-----------------------------------------------------------------------------
//
// required i/o methods
//
//-----------------------------------------------------------------------------

// method: sofSize
//
// arguments: none
//
// return: size of object as written to disk via the i/o methods
//
// this method determines the size of the object on disk
//
template<class TObject>
int32 Node<TObject>::sofSize() const {

  // temporary size variable
  //
  if (item_d != NULL) {
    return item_d->sofSize();
  }
  else {
    Error::handle(name(), L"sofSize", ERR_NOITEM, __FILE__, __LINE__);
    return (int32)0;
  }
}

// method: read
//
// arguments:
//  Sof& sof: (input) sof file object
//  int32 tag: (input) sof object instance tag
//  String& name: (input) sof object instance name
//
// return: a bool8 value indicating status
//
// this method has the object read itself from an Sof file
//
template<class TObject>
bool8 Node<TObject>::read(Sof& sof_a, int32 tag_a, const String& name_a) {
  
  // get the instance of the object from the Sof file
  //
  if (!sof_a.find(name_a, tag_a)) {
    return false;
  }

  // read the actual data from the sof file
  //
  if (!readData(sof_a)) {
    return false;
  }

  // exit gracefully
  //
  return true;
}

// method: write
//
// arguments:
//  Sof& sof: (input) sof file object
//  int32 tag: (input) sof object instance tag
//  String& name: (input) sof object instance name
//
// return: a bool8 value indicating status
//
// this method has the object write itself to an Sof file
//
template<class TObject>
bool8 Node<TObject>::write(Sof& sof_a, int32 tag_a, const String& name_a)
  const {

  // declare a temporary size variable
  //
  int32 obj_size = 0;

  // switch on ascii or binary mode
  //
  if (sof_a.isText()) {

    // set the size to be dynamic
    //
    obj_size = Sof::ANY_SIZE;
  }
  else {

    // the size of the binary data to write
    //
    obj_size = sofSize();
  }
  
  // put the object into the sof file's index
  //
  if (!sof_a.put(name_a, tag_a, obj_size)) {
    return false;
  }
  
  // exit gracefully
  //
  return writeData(sof_a);
}

// method: readData
//
// arguments:
//  Sof& sof: (input) sof file object
//  String& pname: (input) parameter name
//  int32 size: (input) size of the object
//  bool8 param: (input) is the parameter specified?
//  bool8 nested: (input) is this nested?
//
// return: a bool8 value indicating status
//
// this method has the object read itself from an Sof file. it assumes
// that the Sof file is already positioned correctly.
//
template<class TObject>
bool8 Node<TObject>::readData(Sof& sof_a, const String& pname_a, int32 size_a,
				bool8 param_a, bool8 nested_a) {
  
  // if item_d is NULL then create a new one
  //
  if (item_d == (TObject*)NULL) {
    item_d = new TObject();
  }
  
  // read the item
  //
  if (!item_d->readData(sof_a, pname_a, size_a, param_a, nested_a)) {
    return Error::handle(name(), L"readData", Error::READ,
			 __FILE__, __LINE__, Error::WARNING);
  }

  // exit gracefully
  //
  return true;
}

// method: writeData
//
// arguments:
//  Sof& sof: (input) sof file object
//  String& pname: (input) parameter name
//
// return: a bool8 value indicating status
//
// this method writes the object to the Sof file. it assumes that the
// Sof file is already positioned correctly.
//
template<class TObject>
bool8 Node<TObject>::writeData(Sof& sof_a, const String& pname_a) const {

  // make sure the item is not NULL
  //
  if (item_d != (TObject*)NULL) {
    return item_d->writeData(sof_a, pname_a);
  }
  else {
    return Error::handle(name(), L"writeData", ERR_NOITEM, __FILE__,
			 __LINE__);
  }

  // exit gracefully
  //
  return true;
}

//-----------------------------------------------------------------------------
//
// required equality methods
//
//-----------------------------------------------------------------------------

// method: eq
//
// arguments:
//  const Node<TObject>& arg: (input) the node to compare
//
// return: bool8 value indicating test of equivalence
//
// this method compares two nodes for equivalence. two nodes are equivalent
// if their contents are equivalent.
//
template<class TObject>
bool8 Node<TObject>::eq(const Node<TObject>& arg_a) const {
  
  // check for the case where the item is NULL
  // 
  if ((item_d != (TObject*)NULL) && (arg_a.item_d != (TObject*)NULL)) {

    // compare the two pointers. they won't often be equivalent, but
    // if they are then this is probably faster than comparing the
    // underlying objects.  if the pointers are not equivalent then
    // call the item compare method
    //
    return ((item_d == arg_a.item_d) || item_d->eq(*(arg_a.item_d)));
  }
  else {

    // if either item is NULL then error and return
    //
    return Error::handle(name(), L"eq", ERR_NOITEM, __FILE__,
			 __LINE__);  
  }
}

//-----------------------------------------------------------------------------
//
//  required memory management methods
//
//-----------------------------------------------------------------------------

// method: clear
//
// arguments:
//  Integral::CMODE cmode_a: (input) clear mode
//
// return: a bool8 value indicating status
//
// this method clears the reference to the internal item.
// 
template<class TObject>
bool8 Node<TObject>::clear(Integral::CMODE cmode_a) {
  
  // if the cmode_a is RETAIN, RESET or RELEASE
  //
  if ((cmode_a == Integral::RETAIN) ||
      (cmode_a == Integral::RESET) || (cmode_a == Integral::RELEASE)) {

    // clear the reference to the item
    //
    item_d = (TObject*)NULL;
  }

  // if the cmode_a is FREE, then delete all memory held in the structure
  //
  else if (cmode_a == Integral::FREE) {
    
    // clear the internal item
    //
    if (item_d != (TObject*)NULL) {
      
      // clear the lower level memory
      //
      item_d->clear(Integral::FREE);
      delete item_d;
      item_d = (TObject*)NULL;
    }
  }
  
  // exit gracefully
  // 
  return true;
}

// end of include file
//
#endif
