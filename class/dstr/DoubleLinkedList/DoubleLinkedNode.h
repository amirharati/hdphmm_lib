// file: $isip/class/dstr/DoubleLinkedList/DoubleLinkedNode.h
// version: $Id: DoubleLinkedNode.h 10640 2007-01-27 02:36:04Z tm334 $
//

// make sure definitions are only made once
//
#ifndef ISIP_DOUBLE_LINKED_NODE
#define ISIP_DOUBLE_LINKED_NODE

// isip include files
//
#ifndef ISIP_NODE
#include <Node.h>
#endif

#ifndef ISIP_STRING
#include <String.h>
#endif

#ifndef ISIP_CHAR
#include <Char.h>
#endif

#ifndef ISIP_CONSOLE	
#include <Console.h>
#endif

// forward class definitions
//
template<class TObject> class DoubleLinkedNodeDiagnose;

// DoubleLinkedNode: a generic node template class which has a forward and a
// backward link to an object of the same type. this class inherits the
// Node template class and adds a pointer to the "next" and "previous"
// DoubleLinkedNode
//
template<class TObject>
class DoubleLinkedNode : public Node<TObject> {

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
  
  static const int32 ERR = 40200;
   
  //---------------------------------------------------------------------------
  //
  // protected data
  //
  //---------------------------------------------------------------------------
protected:

  // define pointers to the next and previous nodes:
  //  the item pointer and the debug level are inherited from the Node
  //  template class
  //
  DoubleLinkedNode<TObject>* next_d;
  DoubleLinkedNode<TObject>* prev_d;

  // define the memory manager
  //
  static MemoryManager mgr_d;
  
  //---------------------------------------------------------------------------
  //
  // required public methods
  //
  //---------------------------------------------------------------------------
public:

  // static methods:
  // diagnose method is moved outside the class header file and
  // defined in the DoubleLinkedNodeDiagnose.h in order to avoid issues
  // related to preprocessing of the diagnose code.
  //
  static const String& name();

  // debug methods
  //
  bool8 debug(const unichar* message) const;

  // method: destructor
  //
  ~DoubleLinkedNode() {
    this->clear(Integral::RESET);
  }

  // method: default constructor
  //
  DoubleLinkedNode(TObject* item = (TObject*)NULL) {
    this->item_d = item;
    next_d = (DoubleLinkedNode<TObject>*)NULL;
    prev_d = (DoubleLinkedNode<TObject>*)NULL;
  }

  // method: copy constructor
  //  
  DoubleLinkedNode(const DoubleLinkedNode<TObject>& arg) {
    next_d = (DoubleLinkedNode<TObject>*)NULL;
    prev_d = (DoubleLinkedNode<TObject>*)NULL;
    assign(arg);
  }
  
  // assign methods
  //
  bool8 assign(const DoubleLinkedNode<TObject>& arg);

  // method: operator=
  //
  DoubleLinkedNode<TObject>& operator=(const DoubleLinkedNode<TObject>& arg) {
    assign(arg);
    return *this;
  }

  // i/o methods:
  //  unlike other classes, we have two read and write methods in dstr
  //  classes. the interface is still the same as that in other
  //  classes. the reason behind this is that we can not use
  //  "CLASS_NAME" as default argument in the read and write methods
  //  here because the data structures build the class name on the fly
  //
  
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
  //  the sofSize, readData and writeData are inherited from the Node class
  //
  bool8 read(Sof& sof, int32 tag, const String& name);
  bool8 write(Sof& sof, int32 tag, const String& name) const;    

  // equality methods:
  //  the eq method is inherited from the Node template class
  //

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

  //---------------------------------------------------------------------------
  //
  // class-specific public methods
  //  get methods
  //
  //---------------------------------------------------------------------------

  // method: getNext
  //
  DoubleLinkedNode<TObject>* getNext() const {
    return next_d;
  }

  // method: getPrev
  //
  DoubleLinkedNode<TObject>* getPrev() const {
    return prev_d;
  }

  //---------------------------------------------------------------------------
  //
  // class-specific public methods
  //  set methods
  //
  //---------------------------------------------------------------------------
  
  // method: setNext
  //
  bool8 setNext(DoubleLinkedNode<TObject>* next_node) {
    next_d = next_node;
    return true;
  }
  
  // method: setPrev
  //
  bool8 setPrev(DoubleLinkedNode<TObject>* prev_node) {
    prev_d = prev_node;
    return true;
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
  friend class DoubleLinkedNodeDiagnose;
  
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
const String DoubleLinkedNode<TObject>::CLASS_NAME(L"DoubleLinkedNode");

template <class TObject>
const String DoubleLinkedNode<TObject>::DEF_PARAM(L"item");

// static instantiations: memory manager
//
template <class TObject>
MemoryManager DoubleLinkedNode<TObject>::mgr_d(sizeof(DoubleLinkedNode<TObject>), CLASS_NAME);

// below are all the methods for the DoubleLinkedNode template class
//

//----------------------------------------------------------------------
//
// required static methods
//
//----------------------------------------------------------------------

// method: name
//
// arguments: none
//
// return: a static String& containing the class name
//
template<class TObject>
const String& DoubleLinkedNode<TObject>::name() {

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

//----------------------------------------------------------------------
//
// required debug methods
//
//----------------------------------------------------------------------

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
bool8 DoubleLinkedNode<TObject>::debug(const unichar* message_a) const {

  // call the parent debug method since we add no new data
  //
  Node<TObject>::debug(message_a);
  
  // exit gracefully
  // 
  return true;
}

//------------------------------------------------------------------------
//
// required assign methods
//
//-------------------------------------------------------------------------

// method: assign
//
// arguments:
//  const DoubleLinkedNode<TObject>& arg: (input) the node to copy
//
// return: a bool8 value indicating status
//
// this method copies the contents of the input to this node
//
template<class TObject>
bool8
DoubleLinkedNode<TObject>::assign(const DoubleLinkedNode<TObject>& arg_a) {
  
  // copy the previous and next pointers
  //
  prev_d = arg_a.prev_d;
  next_d = arg_a.next_d;
  
  // call the assign in the base class which is responsible for
  // assigning the item pointer.
  //
  return Node<TObject>::assign(arg_a);
}

//------------------------------------------------------------------------
//
// required i/o methods
//
//------------------------------------------------------------------------

// method: read
//
// arguments:
//  Sof& sof: (input) sof file object
//  int32 tag: (input) sof object instance tag
//  const String& name: (input) sof object instance name
//
// return: a bool8 value indicating status
//
// this method has the object read itself from an Sof file
//
template<class TObject>
bool8 DoubleLinkedNode<TObject>::read(Sof& sof_a, int32 tag_a,
					const String& name_a) {
  
  // get the instance of the object from the Sof file
  //
  if (!sof_a.find(name_a, tag_a)) {
    return false;
  }

  // read the actual data from the sof file
  //
  if (!this->readData(sof_a)) {
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
//  const String& name: (input) sof object instance name
//
// return: a bool8 value indicating status
//
// this method has the object write itself to an Sof file
//
template<class TObject>
bool8 DoubleLinkedNode<TObject>::write(Sof& sof_a, int32 tag_a,
					 const String& name_a) const {

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
    obj_size = this->sofSize();
  }
  
  // put the object into the sof file's index
  //
  if (!sof_a.put(name_a, tag_a, obj_size)) {
    return false;
  }
  
  // exit gracefully
  //
  return this->writeData(sof_a);
}

// end of include file
//
#endif
