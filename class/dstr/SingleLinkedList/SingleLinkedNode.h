// file: $isip/class/dstr/SingleLinkedList/SingleLinkedNode.h
// version: $Id: SingleLinkedNode.h 10636 2007-01-26 22:18:09Z tm334 $
//

// make sure definitions are only made once
//
#ifndef ISIP_SINGLE_LINKED_NODE
#define ISIP_SINGLE_LINKED_NODE

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
template<class TObject> class SingleLinkedNodeDiagnose;

// SingleLinkedNode: a generic node template class which has a forward link
// to an object of the same type. this class inherits the Node template class
// and adds a pointer to a "next" SingleLinkedNode
//
template<class TObject>
class SingleLinkedNode : public Node<TObject> {

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
  
  static const int32 ERR = 40100;
  
  //---------------------------------------------------------------------------
  //
  // protected data
  //
  //---------------------------------------------------------------------------
protected:

  // define a pointer to the next node:
  //  the item pointer, the allocation flag and the debug level are
  //  inherited from the Node template class
  //
  SingleLinkedNode<TObject>* next_d;

  // define the memory manager
  //
  static MemoryManager mgr_d;
  
  //---------------------------------------------------------------------------
  //
  // required public methods
  //
  //---------------------------------------------------------------------------
public:

  // static methods
  //  diagnose method is moved outside the class header file and
  //  defined in the SingleLinkedNodeDiagnose.h in order to avoid issues
  //  related to preprocessing of the diagnose code.
  //
  static const String& name();

  // setdebug methods:
  //  this method is inherited from the Node template class
  //

  // method: debug
  //
  bool8 debug(const unichar* message) const {
    Node<TObject>::debug(message);
    return true;
  }

  // method: destructor
  //
  ~SingleLinkedNode() {
    this->clear(Integral::RESET);
  }

  // method: default constructor
  //
  SingleLinkedNode(TObject* item = (TObject*)NULL) {
    this->item_d = item;
    next_d = (SingleLinkedNode<TObject>*)NULL;
  }

  // method: copy constructor
  //  
  SingleLinkedNode(const SingleLinkedNode<TObject>& arg) {
    next_d = (SingleLinkedNode<TObject>*)NULL;
    assign(arg);
  }

  // assign methods
  //
  bool8 assign(const SingleLinkedNode<TObject>& arg);

  // method: operator=
  //
  SingleLinkedNode<TObject>& operator=(const SingleLinkedNode<TObject>& arg) {
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
  //  the sofSize method is inherited from the Node class
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
    return (mgr_d.setGrow(grow_size));
  }

  //---------------------------------------------------------------------------
  //
  // class-specific public methods:
  //  get methods
  //
  //---------------------------------------------------------------------------

  // method: getNext
  //
  SingleLinkedNode<TObject>* getNext() const {
    return next_d;
  }

  //---------------------------------------------------------------------------
  //
  // class-specific public methods:
  //  set methods
  //
  //---------------------------------------------------------------------------

  // method: setNext
  //
  bool8 setNext(SingleLinkedNode<TObject>* next_node) {
    next_d = next_node;
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
  friend class SingleLinkedNodeDiagnose;
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
const String SingleLinkedNode<TObject>::CLASS_NAME(L"SingleLinkedNode");

// constants: required constants for i/o methods
//
template <class TObject>
const String SingleLinkedNode<TObject>::DEF_PARAM(L"item");

// static instantiations: the memory manager
//
template <class TObject>
MemoryManager SingleLinkedNode<TObject>::mgr_d(sizeof(SingleLinkedNode<TObject>), CLASS_NAME);

// below are all the methods for the SingleLinkedNode template class
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
// this method returns the class name
//
template<class TObject>
const String& SingleLinkedNode<TObject>::name() {

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

//------------------------------------------------------------------------
//
// required assign methods
//
//-------------------------------------------------------------------------

// method: assign
//
// arguments:
//  const SingleLinkedNode<TObject>& arg: (input) the node to copy
//
// return: a bool8 value indicating status
//
// this method copies the contents of the input to this node
//
template<class TObject>
bool8
SingleLinkedNode<TObject>::assign(const SingleLinkedNode<TObject>& arg_a) {
  
  // copy the previous and next pointers
  //
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
bool8 SingleLinkedNode<TObject>::read(Sof& sof_a, int32 tag_a,
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
bool8 SingleLinkedNode<TObject>::write(Sof& sof_a, int32 tag_a,
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
