// file: $isip/class/dstr/Stack/Stack.h
// version: $Id: Stack.h 10636 2007-01-26 22:18:09Z tm334 $
//

// make sure definitions are made only once
//
#ifndef ISIP_STACK
#define ISIP_STACK

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

// forward class declaration
//
template<class TObject> class DoubleLinkedList;

// Stack: this class implements a standard stack (last-in, first-out)
// using a double linked list. this class uses the double linked list
// class in USER mode since this list is used to store either
// the actual data or a pointer to it.
//
template<class TObject>
class Stack : public DstrBase {
  
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
  static const int32 POP_ALL = -1;
  static const int32 POP_TO_MARK = -2;
  
  // default arguments to methods
  //
  
  //----------------------------------------
  //
  // error codes
  //
  //----------------------------------------  
  
  static const int32 ERR = 40500;
  static const int32 ERR_EMPTY = 40501;
  
  //---------------------------------------------------------------------------
  //
  // protected data
  //
  //---------------------------------------------------------------------------
protected:
  
  // the internal structure of the stack is a DoubleLinkedList
  //
  DoubleLinkedList<TObject> stack_d;

  // the allocation mode
  //
  ALLOCATION alloc_d;

  // define the memory manager
  //
  static MemoryManager mgr_d;
  
  // debugging parameters
  //
  static Integral::DEBUG debug_level_d;
  
  //---------------------------------------------------------------------------
  //
  // required public methods
  //
  //---------------------------------------------------------------------------
public:

  // static methods:
  //  the diagnose method is moved outside the class header file and
  //  defined in the StackDiagnose.h in order to avoid issues
  //  with preprocessing of the diagnose code.
  //
  static const String& name() {

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

  // method: setDebug
  //
  static bool8 setDebug(Integral::DEBUG debug_level) {
    debug_level_d = debug_level;
    return true;
  }

  // other debug methods:
  //
  bool8 debug(const unichar* message_a) const {

  // declare local variables
  //
  String output;
  String value;

  // print out the memory allocation mode
  //
  output.debugStr(name(), message_a, L"alloc_d",
		  NameMap::ALLOCATION_MAP((int32)alloc_d));
  Console::put(output);

  // output the debug level
  //
  value.assign(debug_level_d);
  output.debugStr(name(), message_a, L"debug_level_d", value);
  Console::put(output);
  
  // print out the top of stack message
  //
  value.assign(L"top of stack");
  Console::put(value);

  // increment the indention level
  //
  Console::increaseIndention();

  // call the list debug method
  //
  stack_d.debug(message_a);
  
  // decrement the indention level
  //
  Console::decreaseIndention();

  // exit gracefully
  // 
  return true;
}

  // method: destructor
  //
  ~Stack() {
    clear(Integral::RESET);
  }
  
  // default constructor
  //
  Stack(ALLOCATION alloc_a = DEF_ALLOCATION) {

  // set the allocation flag
  //
  alloc_d = alloc_a;
  
  // the list object must be in USER mode
  //
  stack_d.setAllocationMode(USER);
}
  
  // method: copy constructor
  //
  Stack(const Stack<TObject>& copy_stack) {
    alloc_d = copy_stack.alloc_d;
    stack_d.setAllocationMode(USER);
    assign(copy_stack);
  }
  
  // assign method
  //
  bool8 assign(const Stack<TObject>& copy_stack_a) {

  // error when the current stack is in USER mode and the stack to be copied
  // is in SYSTEM mode
  //
  if ((alloc_d == USER) && (copy_stack_a.getAllocationMode() == SYSTEM)) {
    return Error::handle(name(), L"assign", Error::ARG, __FILE__, __LINE__);
  }

  // if this stack is in system mode then temporarily set the list
  // to system mode and assign. this has the side-effect of copying the
  // data to this list
  //
  alloc_d = copy_stack_a.alloc_d;
  stack_d.setAllocationMode(alloc_d);
  stack_d.assign(copy_stack_a.stack_d);
  stack_d.setAllocationMode(USER);
  
  // reposition the stack
  //
  stack_d.gotoFirst();

  // exit gracefully
  //
  return true;
}

  // method: operator=
  //
  Stack<TObject>& operator=(const Stack<TObject>& arg) {
    assign(arg);
    return *this;
  }

  // method: eq
  //
  bool8 eq(const Stack<TObject>& compare_stack) const {
    return stack_d.eq(compare_stack.stack_d);
  }
  
  // method: sofSize
  //
  int32 sofSize() const {
    return stack_d.sofSize();
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
    return stack_d.read(sof, tag, name);
  }
  
  // method: write
  //
  bool8 write(Sof& sof, int32 tag, const String& name) const {
    return stack_d.write(sof, tag, name);
  }

  // method: readData
  //
  bool8 readData(Sof& sof, const String& pname = DEF_PARAM, int32 size =
		   SofParser::FULL_OBJECT, bool8 param = true,
		   bool8 nested = false) {
    return stack_d.readData(sof, pname, size, param, nested);
  }

  // method: writeData
  //
  bool8 writeData(Sof& sof, const String& pname =  DEF_PARAM) const {
    return stack_d.writeData(sof, pname);
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
    stack_d.setAllocationMode(alloc_d);
    bool8 ret = stack_d.clear(cmode);
    stack_d.setAllocationMode(USER);
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
  bool8 ne(const Stack<TObject>& compare_stack) const {
    return (!eq(compare_stack));
  }
  
  //---------------------------------------------------------------------------
  //
  // class-specific public methods:
  //  stack push and pop methods
  //
  //---------------------------------------------------------------------------
  
  // push methods:
  //  the push methods add items to the top of the stack
  //
  bool8 push(TObject* item_a) {

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

  // push the object to the top of the stack
  //
  return stack_d.insertFirst(new_obj);
}


  bool8 push(Stack<TObject>& item_stack);
  bool8 push(TObject** items, int32 num_items);
  
  // other stack manipulation methods
  //
  const TObject* peek() const  {
      return stack_d.getCurr();
  }

  TObject* peek() {
      return stack_d.getCurr();
  }


  TObject* pop(TObject* item_a = (TObject*)NULL) {

  // declare local variables
  //
  bool8 result = false;
  TObject* ptr = (TObject*)NULL;

  // when in SYSTEM mode the item passed in should not be
  // null, if we are in reference mode the item should be null
  //
  if (((alloc_d == SYSTEM) && (item_a == (TObject*)NULL)) ||
      ((alloc_d == USER) && (item_a != (TObject*)NULL))) {
    Error::handle(name(), L"pop", ERR, __FILE__, __LINE__);
    return (TObject*)NULL;
  }

  // when in USER mode the item should be null
  //
  if ((alloc_d == USER) && (item_a != (TObject*)NULL)) {
    Error::handle(name(), L"pop", ERR, __FILE__, __LINE__);
    return (TObject*)NULL;
  }  
  
  // if the stack is empty exit
  //
  if (!isEmpty()) {

    // the returned item is valid so remove the item and make sure we are
    // positioned at the top of the stack
    //
    result = stack_d.removeFirst(ptr);
    stack_d.gotoFirst();
    
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
      // be compared).
      //
      return item_a;
    }

    // mode: USER
    //
    else {
      return ptr;
    }
  }

  // nothing in stack, return null
  //
  return (TObject*)NULL;
}

  int32 pop(Stack<TObject>& items, int32 num_items);

  // method: popAll
  //
  bool8 popAll(Stack<TObject>& item_stack) {
    if (pop(item_stack, POP_ALL) <= 0) {
      return false;
    }
    return true;
  }

  // method: popToMark
  //
  bool8 popToMark(Stack<TObject>& item_stack) {
    if (pop(item_stack, POP_TO_MARK) <= 0) {
      return false;
    }
    return true;
  }

  //---------------------------------------------------------------------------
  //
  // class-specific public methods:
  //  stack marker positioning methods
  //
  //---------------------------------------------------------------------------
  
  // method: setMark
  //  sets the top of the stack to be the marked position
  //
  bool8 setMark() {
    return stack_d.setMark();
  }

  // method: clearMark
  //  unmarks the marked stack position
  //
  bool8 clearMark() {
    return stack_d.clearMark();
  }

  // method: markIsSet
  //
  bool8 markIsSet() const {
    return stack_d.markIsSet();
  }

  // method: getMark
  //
  const TObject* getMark() const {
    return stack_d.getMark();
  }

  // method: getMark
  //
  TObject* getMark() {
    return stack_d.getMark();
  }

  // method: isMarkedElement
  //  indicates if the marked element is on top of the stack
  //
  bool8 isMarkedElement() const {
    return stack_d.isMarkedElement();
  }

  //---------------------------------------------------------------------------
  //
  // class-specific public methods:
  //  stack property methods
  //
  //---------------------------------------------------------------------------
  
  // method: isEmpty
  //
  bool8 isEmpty() const {
    return (stack_d.isEmpty());
  }

  // method: length
  //
  int32 length() const {
    return stack_d.length();
  }

  // method: find
  //
  bool8 find(TObject* item) {

    // since the position of the stack must be at the top of the
    // stack, we set the mark to the element if it is found
    //
    return (stack_d.find(item) && stack_d.setMark() &&
	    stack_d.gotoFirst());
  }

  // method: contains
  //
  bool8 contains(TObject* item) const {
    return stack_d.contains(item);
  }

  //---------------------------------------------------------------------------
  //
  // class-specific public methods:
  //  stack computation methods
  //
  //---------------------------------------------------------------------------
    
  // method: apply
  //  apply an external function to each element in the list
  //
  bool8 apply(bool8 (TObject::*method)()) {
    return (stack_d.apply(method));
  }

  // method: apply
  //  applies the input method to each element in the input stack
  //  and assigns the input stack to this stack
  //
  bool8 apply(bool8 (TObject::*method)(), Stack<TObject>& arg) {
    assign(arg);
    stack_d.gotoFirst();
    return apply(method);
  }

  //---------------------------------------------------------------------------
  //
  // class-specific public methods:
  //  stack element ordering methods
  //
  //---------------------------------------------------------------------------
  
  // method: sort
  //  sorts the elements in the stack according to the given order with
  //  ascending order, the item at the bottom of the stack will be the
  //  greatest in value.
  //
  bool8 sort(Integral::ORDER sort_order = Integral::ASCENDING,
               DstrBase::SORT_ALGO sort_algo =  DstrBase::DEF_SORT_ALGO) {
    return stack_d.sort(sort_order, sort_algo);
  }

  // method: reverse
  //  reverses the order of elements in the stack
  //
  bool8 reverse() {
    return stack_d.reverse();
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
  // class-specific public methods:
  //  stack container access methods
  //
  //---------------------------------------------------------------------------

  // method: gotoFirst
  //
  bool8 gotoFirst() {
    return stack_d.gotoFirst();
  }

  // method: gotoNext
  //  
  bool8 gotoNext() {
    return stack_d.gotoNext();    
  }

  // method: gotoPrev
  //    
  bool8 gotoPrev() {
    return stack_d.gotoPrev();
  }

  // method: gotoMark
  //    
  bool8 gotoMark() {
    return stack_d.gotoMark();
  }  

  // method: getFirst
  //
  TObject* getFirst() {
    return stack_d.getFirst();
  }

  // method: getNext
  //  
  TObject* getNext() {
    return stack_d.getNext();    
  }

  // method: getPrev
  //    
  TObject* getPrev() {
    return stack_d.getPrev();
  }

  // method: getCurr
  //    
  TObject* getCurr() {
    return stack_d.getCurr();
  }  

  // method: gotoPosition
  //      
  bool8 gotoPosition() {
    return stack_d.gotoPosition();
  }

  // method: getPosition
  //        
  int32 getPosition() {
    return stack_d.getPosition();
  }

  // method: isLast
  //
  bool8 isLast() {
    return stack_d.isLast();
  }

  // method: isEmpty
  //
  bool8 isEmpty() {
    return stack_d.isEmpty();
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
const String Stack<TObject>::CLASS_NAME(L"Stack");

template <class TObject>
const String Stack<TObject>::DEF_PARAM(L"values");

// static instantiations: debug level
//
template <class TObject>
Integral::DEBUG Stack<TObject>::debug_level_d = Integral::NONE;

// static instantiations: the memory manager
//
template <class TObject>
MemoryManager Stack<TObject>::mgr_d(sizeof(Stack<TObject>), CLASS_NAME);

// below are all the methods for the Stack template class
//      


// method: push
//
// arguments:
//  Stack<TObject>& item_stack: (input) stack to be pushed
//  
// return: a bool8 value indicating status
//
// this method pushes a stack to the top of another stack
//
template<class TObject>
bool8 Stack<TObject>::push(Stack<TObject>& item_stack_a) {

  // if the stack is empty exit
  //
  if (item_stack_a.isEmpty()) {
    return false;
  }

  // loop over the stack and add elements
  //
  else {
    
    // move to the last element in the stack
    //
    item_stack_a.stack_d.gotoLast();
    
    // add the last item to the stack
    //
    push(item_stack_a.stack_d.getCurr());
    
    // loop over all elements in the input stack
    //
    while (item_stack_a.stack_d.gotoPrev()) {
      
      // push the element on the stack
      //
      push(item_stack_a.stack_d.getCurr());
    }
  }
  
  // exit gracefully
  //
  return true;
}

// method: push
//
// arguments:
//  TObject** items: (input) list of items to be pushed
//  int32 num_items: (input) number of items in the list
//  
// return: a bool8 value indicating status
//
// this method pushes num_items from the items list to the top of the stack
//
template<class TObject>
bool8 Stack<TObject>::push(TObject** items_a, int32 num_items_a) {

  // loop over all elements in the list and push each one
  //
  for (int32 i = num_items_a - 1; i >= 0; i--) {
    if (!push(items_a[i])) {
      return false;
    }
  }
  
  // exit gracefully
  //
  return true;
}

// method: pop
//
// arguments:
//  Stack& item_a: (output) the items pop'd
//  int32 num_items_a: (input) multi-pop mode
//  
// return: a bool8 value indicating status
//
// this method pops the top items off of the stack and places them in the
// input stack passed as an argument
//
template<class TObject>
int32 Stack<TObject>::pop(Stack<TObject>& items_a, int32 num_items_a) {

  // check that the modes are compatible
  //
  if (items_a.alloc_d != alloc_d) {
    return (Error::handle(name(), L"pop", Stack::ERR, __FILE__, __LINE__));
  }

  // declare local variables
  //
  int32 count = 0;
  int32 stack_len = 0;  
  TObject* ptr = NULL;

  // get the initial stack length
  //
  stack_len = stack_d.length();
  
  // the pop method was called with POP_ALL
  //
  if (num_items_a == POP_ALL) {
    while ((count < stack_len) && stack_d.removeFirst(ptr)) {
      items_a.stack_d.insertLast(ptr);
      count++;    
    }
  }
  
  // the pop method was called with POP_TO_MARK
  //  
  else if (num_items_a == POP_TO_MARK) {
    while (!stack_d.isMarkedElement() && stack_d.removeFirst(ptr)) {
      items_a.stack_d.insertLast(ptr);
      count++;
    }
  }

  // the pop method was called with num_items_a
  //
  else if (num_items_a >= 0) {
    while ((count < num_items_a) && stack_d.removeFirst(ptr)) {
      items_a.stack_d.insertLast(ptr);
      count++;    
    }
  }

  // none of the valid options to pop were found
  //
  else {
    return (Error::handle(name(), L"pop", Stack::ERR, __FILE__, __LINE__));
  }
  
  // return the number of items popped
  //
  return count;
}

// end of include file
//
#endif
