// file: $isip/class/dstr/Queue/Queue.h
// version: $Id: Queue.h 6110 2000-12-28 22:31:11Z duncan $
//

// make sure definitions are made only once
//
#ifndef ISIP_QUEUE
#define ISIP_QUEUE

// isip include files
//
#ifndef ISIP_DSTR_BASE
#include <DstrBase.h>
#endif

#ifndef ISIP_DOUBLE_LINKED_LIST
#include <DoubleLinkedList.h>
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
template<class TObject> class DoubleLinkedList;

// Queue: this class implements a standard queue (first-in, first-out)
// using a float64 linked list. this class uses the double linked list
// class in USER mode since this list is used to store either
// the actual data or a pointer to it.
//
template<class TObject>
class Queue : public DstrBase {
  
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
  static const int32 REMOVE_ALL = -1;
  static const int32 REMOVE_TO_MARK = -2;
  
  // default arguments to methods
  //
  
  //----------------------------------------
  //
  // error codes
  //
  //----------------------------------------  
  
  static const int32 ERR = 40600;
  static const int32 ERR_EMPTY = 40601;
  
  //---------------------------------------------------------------------------
  //
  // protected data
  //
  //---------------------------------------------------------------------------
protected:
  
  // the internal structure of the queue is a DoubleLinkedList
  //
  DoubleLinkedList<TObject> queue_d;

  // the allocation mode
  //
  ALLOCATION alloc_d;
 
  // debugging parameters
  //
  static Integral::DEBUG debug_level_d;

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
  //  the diagnose method is moved outside the class header file and
  //  defined in the QueueDiagnose.h in order to avoid issues
  //  with preprocessing of the diagnose code.
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
  ~Queue() {
    clear(Integral::RESET);
  }

  // default constructor
  //
  Queue(ALLOCATION alloc = DEF_ALLOCATION);
  
  // method: copy constructor
  //
  Queue(const Queue<TObject>& copy_queue) {
    alloc_d = copy_queue.alloc_d;
    queue_d.setAllocationMode(USER);
    assign(copy_queue);
  }

  // assign method
  //
  bool8 assign(const Queue<TObject>& copy_stack);
  
  // method: operator=
  //
  Queue<TObject>& operator=(const Queue<TObject>& arg) {
    assign(arg);
    return *this;
  }

  // method: eq
  //
  bool8 eq(const Queue<TObject>& arg) const {
    return queue_d.eq(arg.queue_d);
  }

  // method: sofSize
  //
  int32 sofSize() const {
    return queue_d.sofSize();
  }

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

  // method: read
  //
  bool8 read(Sof& sof, int32 tag, const String& name) {
    return queue_d.read(sof, tag, name);
  }
  
  // method: write
  //
  bool8 write(Sof& sof, int32 tag, const String& name) const {
    return queue_d.write(sof, tag, name);
  }
  
  // method: readData
  //
  bool8 readData(Sof& sof, const String& pname = DEF_PARAM, int32 size =
		   SofParser::FULL_OBJECT, bool8 param = true,
		   bool8 nested = false) {
    return queue_d.readData(sof, pname, size, param, nested);
  }
  
  // method: writeData
  //
  bool8 writeData(Sof& sof, const String& pname = DEF_PARAM) const {
    return queue_d.writeData(sof, pname);
  }
    
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
    
  // method: clear
  //
  bool8 clear(Integral::CMODE cmode = Integral::DEF_CMODE) {
    queue_d.setAllocationMode(alloc_d);
    bool8 ret = queue_d.clear(cmode);
    queue_d.setAllocationMode(USER);
    return ret;
  }

  //---------------------------------------------------------------------------
  //
  // class-specific public methods:
  //  extensions to required methods
  //
  //---------------------------------------------------------------------------

  // method: ne
  //
  bool8 ne(const Queue<TObject>& compare_queue) const {
    return (!eq(compare_queue));
  }

  //---------------------------------------------------------------------------
  //
  // class-specific public methods:
  //  queue add and remove methods
  //
  //---------------------------------------------------------------------------

  // add methods:
  //  the add methods add items to the front of the queue
  //
  bool8 add(TObject* item);
  bool8 add(Queue<TObject>& item_queue);
  bool8 add(TObject** items, int32 num_items);

  // other queue manipulation methods
  //
  const TObject* peek() const; 
  TObject* peek(); 
  TObject* remove(TObject* item = (TObject*)NULL);
  int32 remove(Queue<TObject>& items, int32 num_items);

  // method: removeAll
  //
  bool8 removeAll(Queue<TObject>& item_queue) {
    if (remove(item_queue, REMOVE_ALL) <= 0) {
      return false;
    }
    return true;
  }
  
  // method: removeToMark
  //
  bool8 removeToMark(Queue<TObject>& item_queue) {
    if (remove(item_queue, REMOVE_TO_MARK) <= 0) {
      return false;
    }
    return true;
  }
  
  //---------------------------------------------------------------------------
  //
  // class-specific public methods:
  //  queue marker positioning methods
  //
  //---------------------------------------------------------------------------
  
  // method: setMark
  //  sets the end of the queue to be the marked position
  //
  bool8 setMark() {
    queue_d.gotoLast();
    return queue_d.setMark();
  }

  // method: clearMark
  //  unmarks the marked queue position
  //
  bool8 clearMark() {
    return queue_d.clearMark();
  }

  // method: markIsSet
  //
  bool8 markIsSet() const {
    return queue_d.markIsSet();
  }

  // method: getMark
  //
  const TObject* getMark() const {
    return queue_d.getMark();
  }

  // method: getMark
  //
  TObject* getMark() {
    return queue_d.getMark();
  }

  // method: isMarkedElement
  //  indicates if the marked element is on top of the queue
  //
  bool8 isMarkedElement() const {
    return (queue_d.getFirst() == queue_d.getMark());
  }

  //---------------------------------------------------------------------------
  //
  // class-specific public methods:
  //  queue property methods
  //
  //---------------------------------------------------------------------------
  
  // method: isEmpty
  //
  bool8 isEmpty() const {
    return queue_d.isEmpty();
  }

  // method: length
  //
  int32 length() const {
    return queue_d.length();
  }
  
  // method: find
  //
  bool8 find(TObject* item) {

    // since the position of the queue must be at the end of the
    // queue, we set the mark to the element if it is found
    //
    return (queue_d.find(item) && queue_d.setMark() &&
	    queue_d.gotoLast());
  }

  // method: contains
  //
  bool8 contains(TObject* item) const {
    return queue_d.contains(item);
  }

  //---------------------------------------------------------------------------
  //
  // class-specific public methods:
  //  queue computation methods
  //
  //---------------------------------------------------------------------------
  
  // method: apply
  //  applies the input method to each element in the queue
  //
  bool8 apply(bool8 (TObject::*method)()) {
    return (queue_d.apply(method) && queue_d.gotoLast());
  }

  // method: apply
  //  applies the input method to each element in the input queue
  //  and assigns the input queue to this queue
  //
  bool8 apply(bool8 (TObject::*method)(), Queue<TObject>& arg) {
    assign(arg);
    queue_d.gotoFirst();
    return apply(method);
  }  

  //---------------------------------------------------------------------------
  //
  // class-specific public methods:
  //  queue element ordering methods
  //
  //---------------------------------------------------------------------------
  
  // method: sort
  //  sorts the elements in the queue according to the given order with 
  //  ascending order, the item at the bottom of the queue will be the
  //  greatest in value.
  //
  bool8 sort(Integral::ORDER sort_order = Integral::ASCENDING,
               SORT_ALGO sort_algo = DEF_SORT_ALGO) {
    return (queue_d.sort(sort_order, sort_algo) && queue_d.gotoLast());
  }

  // method: reverse
  //  reverses the order of elements in the queue
  //
  bool8 reverse() {
    return (queue_d.reverse() && queue_d.gotoLast());
  }
  
  // method: getAllocationMode
  //
  ALLOCATION getAllocationMode() const {
    return alloc_d;
  }

  // method: setAllocationMode
  //
  bool8 setAllocationMode(ALLOCATION alloc) {
    alloc_d = alloc;
    return true;
  }

  //---------------------------------------------------------------------------
  //
  // private methods
  //
  //---------------------------------------------------------------------------
private:

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
const String Queue<TObject>::CLASS_NAME(L"Queue");

template <class TObject>
const String Queue<TObject>::DEF_PARAM(L"values");

// static instantiations: debug level
//
template <class TObject>
Integral::DEBUG Queue<TObject>::debug_level_d = Integral::NONE;

// static instantiations: the memory manager
//
template <class TObject>
MemoryManager Queue<TObject>::mgr_d(sizeof(Queue<TObject>), CLASS_NAME);

// below are all the methods for the Queue template class
//      

// ---------------------------------------------------------------------
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
const String& Queue<TObject>::name() {
  
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

// ---------------------------------------------------------------------
//
// required debug methods
//
//----------------------------------------------------------------------

// method: debug
//
// arguments:
//  unichar* message: (input) information message
//
// return: a bool8 value indicating status
//
// this method dumps the contents of an object to the console
// 
template<class TObject>
bool8 Queue<TObject>::debug(const unichar* message_a) const {
  
  // declare local variables
  //
  String output;
  String value;

  // print out the memory allocation mode
  //
  output.debugStr(name(), message_a, L"alloc_d",
		  NameMap::ALLOCATION_MAP((int32)alloc_d));
  Console::put(output);
  
  // print out the debug level
  //
  value.assign(debug_level_d);
  output.debugStr(name(), message_a, L"debug_level_d", value);
  Console::put(output);
  
  // print out the top of queue message
  //
  value.assign(L"front of queue");
  Console::put(value);
  
  // increment the indention level
  //
  Console::increaseIndention();
  
  // call the list debug method
  //
  queue_d.debug(message_a);
  
  // decrement the indention level
  //
  Console::decreaseIndention();
  
  // exit gracefully
  // 
  return true;
}

//------------------------------------------------------------------------
//
// required destructor/constructor(s)
//
//-----------------------------------------------------------------------

// method: default constructor
//
// arguments:
//  ALLOCATION alloc: (input) the flag to specify whether or not the item
//                     memory is allocated by the node itself
//
// return: none
//
template<class TObject>
Queue<TObject>::Queue(ALLOCATION alloc_a) {

  // set the allocation flag
  //
  alloc_d = alloc_a;

  // the list object must be in USER mode
  //
  queue_d.setAllocationMode(USER);
}

//----------------------------------------------------------------------
//
// required assign methods
//
//----------------------------------------------------------------------

// method: assign
//
// arguments:
//  const Queue<TObject>& copy_queue: (input) queue to be copied
//
// return: a bool8 value indicating status
//
// this method copies the elements in queue passed in to the current queue
// 
template<class TObject>
bool8 Queue<TObject>::assign(const Queue<TObject>& arg_a) {

  // when the current queue is in USER mode and the queue to be copied
  // is in SYSTEM mode error
  //
  if ((alloc_d == USER) && (arg_a.getAllocationMode() == SYSTEM)) {
    return Error::handle(name(), L"assign", Error::ARG, __FILE__, __LINE__);
  }

  // if this queue is in system mode then temporarily set the list
  // to system mode and assign. this has the side-effect of copying the
  // data to this list
  //
  alloc_d = arg_a.alloc_d;
  queue_d.setAllocationMode(alloc_d);
  queue_d.assign(arg_a.queue_d);
  queue_d.setAllocationMode(USER);
  
  // reposition the Queue
  //
  queue_d.gotoLast();

  // exit gracefully
  //
  return true;
}

//---------------------------------------------------------------------------
//
// class-specific public methods:
//  queue add and remove methods
//
//---------------------------------------------------------------------------

// method: add
//
// arguments:
//  TObject* item: (input) the item added
//  
// return: a bool8 value indicating status
//
// this method adds a item to the front of the queue
//
template<class TObject>
bool8 Queue<TObject>::add(TObject* item_a) {

  // declare local variables
  //
  TObject* new_obj = (TObject*)NULL;

  // mode: SYSTEM
  //  make a copy of the element
  //
  if (alloc_d == SYSTEM) {
    new_obj = new TObject(*item_a);
  }

  // mode: USER
  //  make a copy of the pointer to the item
  //
  else {
    new_obj = item_a;
  }

  // add the object to the top of the queue
  //
  return queue_d.insertLast(new_obj);
}

// method: add
//
// arguments:
//  Queue<TObject>& item_queue: (input) queue to be added
//  
// return: a bool8 value indicating status
//
// this method adds a queue to the front of another queue
//
template<class TObject>
bool8 Queue<TObject>::add(Queue<TObject>& item_queue_a) {

  // if the queue is empty exit
  //
  if (item_queue_a.isEmpty()) {
    return false;
  }

  // loop over the queue and add elements
  //
  else {
    for (bool8 more = item_queue_a.queue_d.gotoFirst();
	 more; more = item_queue_a.queue_d.gotoNext()) {
    
      // add the element on the queue
      //
      if (!add(item_queue_a.queue_d.getCurr())) {
	return false;
      }
    }
    item_queue_a.queue_d.gotoLast();
  }
  
  // exit gracefully
  //
  return true;
}

// method: add
//
// arguments:
//  TObject** items: (input) list of items to be added
//  int32 num_items: (input) number of items in the list
//  
// return: a bool8 value indicating status
//
// this method adds num_items from the items list to the front of the queue
//
template<class TObject>
bool8 Queue<TObject>::add(TObject** items_a, int32 num_items_a) {

  // loop over all elements in the queue and add each one
  //
  for (int32 i = 0; i < num_items_a; i++) {
    if (!add(items_a[i])) {
      return false;
    }
  }
  
  // exit gracefully
  //
  return true;
}

// method: peek
//
// arguments: none
//  
// return: TObject* of the item on top of the queue
//
// this method lets the user manipulate the item on top of the queue without
// removing the item from the queue
//
template<class TObject>
const TObject* Queue<TObject>::peek() const {
  
  // if the queue is empty then return an error
  //
  if (isEmpty()) {
    Error::handle(name(), L"peek", Queue::ERR_EMPTY, __FILE__, __LINE__);
    return (TObject*)NULL;
  }

  // return the pointer
  //
  return queue_d.getFirst();
}

// method: peek
//
// arguments: none
//  
// return: TObject* of the item on top of the queue
//
// this method lets the user manipulate the item on top of the queue without
// removing the item from the queue
//
template<class TObject>
TObject* Queue<TObject>::peek() {
  
  // if the queue is empty then return an error
  //
  if (isEmpty()) {
    Error::handle(name(), L"peek", Queue::ERR_EMPTY, __FILE__, __LINE__);
    return (TObject*)NULL;
  }

  // return the pointer
  //
  return queue_d.getFirst();
}

// method: remove
//
// arguments:
//  TObject* item: (input) memory space for the object
//  
// return: a TObject* pointer to the object removed
//
// this method removes the front item in the queue and returns it to the user
//
template<class TObject>
TObject* Queue<TObject>::remove(TObject* item_a) {

  // declare local variables
  //
  bool8 result = false;
  TObject* ptr = (TObject*)NULL;

  // when in SYSTEM mode the item passed in should not be
  // null, if we are in reference mode the item should be null
  //
  if (((alloc_d == SYSTEM) && (item_a == (TObject*)NULL)) ||
      ((alloc_d == USER) && (item_a != (TObject*)NULL))) {
    Error::handle(name(), L"remove", ERR, __FILE__, __LINE__);
    return (TObject*)NULL;
  }

  // when in USER mode the item should be null
  //
  if ((alloc_d == USER) && (item_a != (TObject*)NULL)) {
    Error::handle(name(), L"remove", ERR, __FILE__, __LINE__);
    return (TObject*)NULL;
  }
  
  // if the queue is empty exit
  //
  if (!isEmpty()) {

    // the returned item is valid so remove the item and make sure we are
    // positioned at the front of the queue
    //
    result = queue_d.removeFirst(ptr);
    queue_d.gotoLast();
    
    // mode: SYSTEM
    //
    if (alloc_d == SYSTEM) {

      // make a copy of the object
      //
      item_a->assign(*ptr);

      // delete the reference to the object      
      //
      delete ptr;

      // return a pointer to the object (so that the return value can
      // be compared)
      //
      return item_a;
    }

    // mode: USER
    //
    else {
      return ptr;
    }
  }

  // nothing in queue, return null
  //
  return (TObject*)NULL;
}

// method: remove
//
// arguments:
//  Queue& item_a: (output) the items to be removed
//  int32 num_items_a: (input) the number of items
//  
// return: a bool8 value indicating status
//
// this method removes the first num_items off of the queue and places them
// in the input queue passed as an argument.
//
template<class TObject>
int32 Queue<TObject>::remove(Queue<TObject>& items_a, int32 num_items_a) {

  // check that the modes are compatible
  //
  if (items_a.getAllocationMode() != alloc_d) {
    return Error::handle(name(), L"remove", Queue::ERR,
			 __FILE__, __LINE__);
  }

  // declare local variables
  //
  int32 count = 0;
  int32 queue_len = 0;  
  TObject* ptr = NULL;

  // get the initial queue length
  //
  queue_len = queue_d.length();
  
  // the remove method was called with REMOVE_ALL
  //
  if (num_items_a == REMOVE_ALL) {
    while ((count < queue_len) && queue_d.removeFirst(ptr)) {
      items_a.queue_d.insertLast(ptr);
      count++;    
    }
  }
  
  // the remove method was called with REMOVE_TO_MARK
  //  
  else if (num_items_a == REMOVE_TO_MARK) {

    // position the queue
    //
    queue_d.gotoFirst();

    // remove element by element
    //
    while (!queue_d.isMarkedElement() && queue_d.removeFirst(ptr)) {
      items_a.queue_d.insertLast(ptr);
      count++;
    }
  }

  // the remove method was called with num_items_a
  //
  else if (num_items_a >= 0) {
    while ((count < num_items_a) && queue_d.removeFirst(ptr)) {
      items_a.queue_d.insertLast(ptr);
      count++;    
    }
  }

  // none of the valid options to remove were found
  //
  else {
    return Error::handle(name(), L"remove", Queue::ERR,
			 __FILE__, __LINE__);
  }
  
  // return the current pointer to the end of the list
  //
  queue_d.gotoLast();

  // return the number of items removed
  //
  return count;
}

// end of include file
//
#endif

