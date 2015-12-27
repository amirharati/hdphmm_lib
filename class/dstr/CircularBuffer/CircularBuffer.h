// file: $isip/class/dstr/CircularBuffer/CircularBuffer.h
// version: $Id: CircularBuffer.h 7464 2001-11-12 19:30:32Z gao $
//

// make sure definitions are only made once
//
#ifndef ISIP_CIRCULAR_BUFFER
#define ISIP_CIRCULAR_BUFFER

// isip include files
//
#ifndef ISIP_VECTOR
#include <Vector.h>
#endif

#ifndef ISIP_FLOAT
#include <Float.h>
#endif

#ifndef ISIP_CONSOLE
#include <Console.h>
#endif

#ifndef ISIP_MEMORY_MANAGER
#include <MemoryManager.h>
#endif

// CircularBuffer: this is a generic circular buffer of objects. this
// class, unlike most other dstr classes, only supports the SYSTEM
// memory management mode (see DstrBase for a more detailed explanation).
// the class is implemented using read, write and
// current index pointers, so users can easily keep track of the amount of
// available data in the buffer.
//
template<class TObject>
class CircularBuffer {
  
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
  static const String PARAM_VALUES;
  static const String PARAM_CAPACITY;  
  static const String PARAM_READ;
  static const String PARAM_WRITE;
  static const String PARAM_CURR;
  
  //----------------------------------------
  //
  // default values and arguments
  //
  //----------------------------------------
  
  // default values
  //
  static const int32 DEF_BUF_CAPACITY = 8192;
  static const int32 DEF_READ_IDX = 0;
  static const int32 DEF_WRITE_IDX = -1;
  static const int32 DEF_CURR_IDX = 0;
  
  // default arguments to methods
  //
  static const int32 DEF_OFFSET = 0;
  static const int32 DEF_NUM_READ = 1;
  
  //----------------------------------------
  //
  // error codes
  //
  //----------------------------------------  
  
  static const int32 ERR = 41600;
  static const int32 ERR_FULL = 41601;
  
  //---------------------------------------------------------------------------
  //
  // protected data
  //
  //---------------------------------------------------------------------------
protected:
  
  // declare a vector of data objects
  //
  Vector<TObject> v_d;
  
  // declare the position indices
  //
  Long read_d;
  Long write_d;
  Long curr_d;
  
  // declare the debugging parameters
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
  //  diagnose method is moved outside the class header file and
  //  defined in CircularBufferDiagnose.h in order to avoid issues
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
  ~CircularBuffer() {}

  // default constructor
  //
  CircularBuffer(int32 capacity = DEF_BUF_CAPACITY);

  // method: copy constructor
  //
  CircularBuffer(const CircularBuffer<TObject>& copy_cbuf) {
    assign(copy_cbuf);
  }
  
  // assign methods
  //
  bool8 assign(const CircularBuffer<TObject>& copy_cbuf);

  // method: operator=
  //
  CircularBuffer<TObject>& operator=(const CircularBuffer<TObject>& arg) {
    assign(arg);
    return *this;
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
  
  // other i/o methods:
  //  sofSize determines the amount of disk storage needed to store this
  //  object the read and write methods are for full object i/o. the
  //  readData and writeData methods handle i/o when this object is a
  //  component of another object
  //
  int32 sofSize() const;

  bool8 read(Sof& sof, int32 tag, const String& name);
  bool8 write(Sof& sof, int32 tag, const String& name) const;

  bool8 readData(Sof& sof, const String& pname = DEF_PARAM,
		   int32 size = SofParser::FULL_OBJECT,
                   bool8 param = true,
		   bool8 nested = true);
  bool8 writeData(Sof& sof, const String& pname = DEF_PARAM) const;
  
  // equality methods
  //
  bool8 eq(const CircularBuffer<TObject>& compare_cbuf) const;
  
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

  // other memory management methods
  //  
  bool8 clear(Integral::CMODE cmode = Integral::DEF_CMODE);

  //---------------------------------------------------------------------------
  //
  // class-specific public methods:
  //  operator overload methods
  //
  //---------------------------------------------------------------------------

  // operator overload methods
  //
  TObject& operator() (int32 offset);
  const TObject& operator() (int32 offset) const;

  //---------------------------------------------------------------------------
  //
  // class-specific public methods:
  //  get methods
  //
  //---------------------------------------------------------------------------
  
  // get element methods
  //
  bool8 getElement(TObject& out, int32 offset = DEF_OFFSET) const;
  bool8 getElement(Vector<TObject>& out, int32 num_elem,
		     int32 offset = DEF_OFFSET) const; 

  // get number of element methods
  //
  int32 getNumElements() const;
  int32 getNumForward() const;
  int32 getNumBackward() const;

  //---------------------------------------------------------------------------
  //
  // class-specific public methods:
  //  class property methods
  //
  //---------------------------------------------------------------------------

  // status checking methods 
  //
  bool8 isFull() const;
  bool8 isEmpty() const;
  
  // method: getCapacity
  //
  int32 getCapacity() const {
    return v_d.getCapacity();
  }

  // method: setCapacity
  //  note that for a circular buffer, we don't distiguish between the
  //  capacity and the length, since the class is designed to manage
  //  how much of the capacity is in use.
  //
  bool8 setCapacity(int32 capacity, bool8 preserve_values = true) {
    v_d.setLength(capacity, preserve_values);
    v_d.setCapacity(capacity, preserve_values);
    return true;
  }

  //---------------------------------------------------------------------------
  //
  // class-specific public methods:
  //  data manipulation methods
  //
  //---------------------------------------------------------------------------

  // data manipulation methods
  //
  bool8 append(const TObject& in);  
  bool8 append(const Vector<TObject>& in);
  bool8 append(const Vector<TObject>& in, int32 num_elem,
		 int32 invec_offset = DEF_OFFSET);

  bool8 prepend(const TObject& in);  
  bool8 prepend(const Vector<TObject>& in);
  bool8 prepend(const Vector<TObject>& in, int32 num_elem,
		  int32 invec_offset = DEF_OFFSET);
  
  //---------------------------------------------------------------------------
  //
  // class-specific public methods:
  //  positioning methods
  //
  //---------------------------------------------------------------------------

  // method: resetCurr
  //
  bool8 resetCurr() {
    curr_d = read_d;
    return true;
  }

  // other positioning methods
  //  
  bool8 seekCurr(int32 offset);
  bool8 setRead(int32 num_read = DEF_NUM_READ);    
  
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
const String CircularBuffer<TObject>::CLASS_NAME(L"CircularBuffer");

template <class TObject>
const String CircularBuffer<TObject>::DEF_PARAM(L"");

template <class TObject>
const String CircularBuffer<TObject>::PARAM_VALUES(L"values");

template <class TObject>
const String CircularBuffer<TObject>::PARAM_CAPACITY(L"capacity");

template <class TObject>
const String CircularBuffer<TObject>::PARAM_READ(L"read");

template <class TObject>
const String CircularBuffer<TObject>::PARAM_WRITE(L"write");

template <class TObject>
const String CircularBuffer<TObject>::PARAM_CURR(L"curr");

// static instantiations: debug level and memory manager
//
template <class TObject>
Integral::DEBUG CircularBuffer<TObject>::debug_level_d = Integral::NONE;

template <class TObject>
MemoryManager CircularBuffer<TObject>::mgr_d(sizeof(CircularBuffer<TObject>),
					     CLASS_NAME);

// below are all the methods for the CircularBuffer template class
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
const String& CircularBuffer<TObject>::name() {
  
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
bool8 CircularBuffer<TObject>::debug(const unichar* message_a) const {
  
  // local variables
  //
  String output;
  String value;
  String param;
  
  // output the debug level
  //
  value.assign(debug_level_d);
  output.debugStr(name(), message_a, L"debug_level_d", value);
  Console::put(output);

  // output the number of valid elements
  //
  int32 num_elem = getNumElements();
  value.assign(num_elem);
  output.debugStr(name(), message_a, L"number of elements", value);
  Console::put(output);

  // output number of elements before and after
  //
  num_elem = getNumForward();
  value.assign(num_elem);
  output.debugStr(name(), message_a, L"number forward", value);
  Console::put(output);

  num_elem = getNumBackward();
  value.assign(num_elem);
  output.debugStr(name(), message_a, L"number backward", value);
  Console::put(output);

  num_elem = getCapacity();
  value.assign(num_elem);
  output.debugStr(name(), message_a, L"capacity", value);
  Console::put(output);

  num_elem = getNumElements();
  if (num_elem == 0) {
    return true;
  }
  
  // increment the indentation level in the console
  //
  Console::increaseIndention();
  
  // find the start number for the loop
  //
  int32 j = read_d;
  int32 capacity = getCapacity();
  
  if (write_d < read_d) {
    j -= capacity;
  }
  
  // loop all the valid elements
  //
  for (; j <= (int32)write_d; j++) {

    // get the physical index
    //
    int32 i = j;
    if (i < 0) {
      i += capacity;
    }
    
    // dump the values out
    //
    param.assign(L"v_d[");
    value.assign(i);
    
    param.concat(value);
    param.concat(L"]");
    
    String extras;
    
    // also output the position information
    //
    if (i == read_d) {
      extras.concat(L", ");
      extras.concat(L"read_d");
    }
    if (i == curr_d) {
      extras.concat(L", ");
      extras.concat(L"curr_d");
    }
    if (i == write_d) {
      extras.concat(L", ");
      extras.concat(L"write_d");
    }
    
    param.concat(extras);
    
    output.debugStr(name(), message_a, param);
    Console::put(output);
    
    // increase indention
    //
    Console::increaseIndention();
    
    // call the debug method of the element
    //
    v_d(i).debug(L"");
    
    Console::decreaseIndention();
  }
  
  // decrement the indention level in the console
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
//  int32 capacity: (input) the capacity of the CircularBuffer
//
// return: none
//
template<class TObject>
CircularBuffer<TObject>::CircularBuffer(int32 capacity_a) {
  
  // initialize the stored item
  //
  v_d.setLength(capacity_a);
  v_d.setCapacity(capacity_a);
  
  // initialize the position indices
  //
  read_d = DEF_READ_IDX;
  write_d = DEF_WRITE_IDX;
  curr_d = DEF_CURR_IDX;
  
  // exit gracefully
  //
}

//------------------------------------------------------------------------
//
// required assign methods
//
//-------------------------------------------------------------------------

// method: assign
//
// arguments:
//  const CircularBuffer<TObject>& copy_cbuf: (input) CircularBuffer to copy
//
// return: a bool8 value indicating status
//
// this method copies the contents of the input to this CircularBuffer
//
template<class TObject>
bool8 CircularBuffer<TObject>::assign(const CircularBuffer<TObject>&
					copy_cbuf_a) {
  
  // if the input CircularBuffer contains a null item, error and return without
  // changing this CircularBuffer
  //
  int32 in_capacity = copy_cbuf_a.getCapacity();
  if (in_capacity == 0) {
    return Error::handle(name(), L"assign", Error::NOMEM, __FILE__, __LINE__);
  }
  
  // it may be necessary to clear the CircularBuffer and reset the capacity
  //
  if (getCapacity() != in_capacity) {
    setCapacity(in_capacity, false);
  }
  
  // copy the position indices
  //
  read_d = copy_cbuf_a.read_d;
  curr_d = copy_cbuf_a.curr_d;
  write_d = copy_cbuf_a.write_d;
  
  // copy the valid data
  //
  
  // find the start index for the loop
  //
  int32 j = read_d;
  int32 capacity = getCapacity();
  
  if (write_d < read_d) {
    j -= capacity;
  }
  
  // loop all the valid elements
  //
  for (; j <= (int32)write_d; j++) {
    
    // get the physical index
    //
    int32 i = j;
    if (i < 0) {
      i += capacity;
    }
    
    v_d(i).assign(copy_cbuf_a.v_d(i));
  }
      
  // exit gracefully
  //
  return true;
}

//------------------------------------------------------------------------
//
// required i/o methods
//
//------------------------------------------------------------------------

// method: sofSize
//
// arguments: none
//
// return: size of object as written to disk via the i/o methods
//
// this method determines the size of the object on disk
//
template<class TObject>
int32 CircularBuffer<TObject>::sofSize() const {

  // get the size of the storage vector
  //
  int32 byte = v_d.sofSize();

  // add the sizes of other internal data
  //
  Long capacity = getCapacity();  
  byte += capacity.sofSize();
  
  byte += read_d.sofSize();
  byte += write_d.sofSize();
  byte += curr_d.sofSize();  

  // exit gracefully
  //
  return byte;
}

// method: read
//
// arguments:
//  Sof& sof: (input) sof file object
//  const String& name: (input) sof object instance name
//  int32 tag: (input) sof object instance tag
//
// return: a bool8 value indicating status
//
// this method has the object read itself from an Sof file
//
template<class TObject>
bool8 CircularBuffer<TObject>::read(Sof& sof_a, int32 tag_a,
				      const String& name_a) {

  // get the instance of the object from an Sof file
  //
  if (!sof_a.find(name_a, tag_a)) {
    return false;
  }
  
  // read the actual data from an Sof file
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
//  const String& name: (input) sof object instance name
//
// return: a bool8 value indicating status
//
// this method has the object write itself to an Sof file
//
template<class TObject>
bool8 CircularBuffer<TObject>::write(Sof& sof_a, int32 tag_a,
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
bool8 CircularBuffer<TObject>::readData(Sof& sof_a, const String& pname_a,
                                  int32 size_a,
                                  bool8 param_a, bool8 nested_a) {
  
  // first clear the buffer
  //
  if (!clear()) {
    return Error::handle(name(), L"readData", Error::READ,
                         __FILE__, __LINE__, Error::WARNING);
  }
  
  SofParser parser;
  parser.setDebug(debug_level_d);
    
  // ignore implicit parameter setting
  //
  
  // are we nested?
  //
  if (nested_a) {
    parser.setNest();
  }
  
  // load the parse
  //
  if (!parser.load(sof_a, size_a)) {
    return Error::handle(name(), L"readData", Error::READ,
			 __FILE__, __LINE__, Error::WARNING);
  }

  // read the capacity of the CircularBuffer
  //
  Long capacity;
  
  if (!capacity.readData(sof_a, PARAM_CAPACITY,
			 parser.getEntry(sof_a, PARAM_CAPACITY),
			 false, false)) {
    return Error::handle(name(), L"readData", Error::READ,
                         __FILE__, __LINE__, Error::WARNING);
  }

  // set the capacity
  //
  setCapacity(capacity);

  // read the pointers
  //
  Long read;
  
  if (!read.readData(sof_a, PARAM_READ,
		     parser.getEntry(sof_a, PARAM_READ),
		     false, false)) {
    return Error::handle(name(), L"readData", Error::READ,
                         __FILE__, __LINE__, Error::WARNING);
  }

  Long write;
  
  if (!write.readData(sof_a, PARAM_WRITE,
		      parser.getEntry(sof_a, PARAM_WRITE),
		      false, false)) {
    return Error::handle(name(), L"readData", Error::READ,
                         __FILE__, __LINE__, Error::WARNING);
  }

  Long curr;
  
  if (!curr.readData(sof_a, PARAM_CURR,
		     parser.getEntry(sof_a, PARAM_CURR),
		     false, false)) {
    return Error::handle(name(), L"readData", Error::READ,
                         __FILE__, __LINE__, Error::WARNING);
  }
  
  // read Vector in a temporary object
  //
  Vector<TObject> temp_vec;
  if (!temp_vec.readData(sof_a, PARAM_VALUES,
			 parser.getEntry(sof_a, PARAM_VALUES),
			 false, false)) {
    return Error::handle(name(), L"readData", Error::READ,
                         __FILE__, __LINE__, Error::WARNING);
  }

  v_d.setLength(capacity);	
  v_d.setCapacity(capacity);

  for (int32 i = 0; i < temp_vec.length(); i++) {
    v_d(i + read) = temp_vec(i);
  }
  
  read_d = read;
  write_d = write;
  curr_d = curr;
  
  // append to CircularBuffer
  //
  // append(temp_vec);
  
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
bool8 CircularBuffer<TObject>::writeData(Sof& sof_a,
					   const String& pname_a) const {
  
  // write a start string if necessary
  //
  sof_a.writeLabelPrefix(pname_a);

  // write the capacity
  //
  Long capacity = getCapacity();
  capacity.writeData(sof_a, PARAM_CAPACITY);

  read_d.writeData(sof_a, PARAM_READ);
  write_d.writeData(sof_a, PARAM_WRITE);
  curr_d.writeData(sof_a, PARAM_CURR);
    
  // get the valid number of elements in the buffer
  //
  int32 num_valid_element = write_d - read_d + 1;

  v_d.writeStart(sof_a);
  v_d.writePartialData(sof_a, read_d, num_valid_element);
  v_d.writeTerminate(sof_a);
  
  // put an end string if necessary
  //
  sof_a.writeLabelSuffix(pname_a);
  
  // exit gracefully
  //
  return true;  
}

// ----------------------------------------------------------------------
//
// required equality methods
//
//------------------------------------------------------------------------

// method: eq
//
// arguments:
//  const CircularBuffer<TObject>& compare_cbuf: (input) the CircularBuffer
//                                                       to compare
//
// return: a bool8 value indicating status
//
// this method compares two CircularBuffers for equivalence. two
// CircularBuffers are equivalent if all corresponding valid items are
// equivalent
//
template<class TObject>
bool8 CircularBuffer<TObject>::eq(const CircularBuffer<TObject>&
				    compare_cbuf_a) const {
  
  // remember the old curr_d
  //
  int32 old_curr = curr_d;
  int32 compare_old_curr = compare_cbuf_a.curr_d;

  // two circular buffers can not be equivalent if they have different
  // number of elements
  //
  int32 num_elements = getNumElements();
  
  if (num_elements != compare_cbuf_a.getNumElements()) {

    // exit ungracefully
    //
    return false;
  }

  // temporarily set the curr_d to be same as read_d
  //
  const_cast<CircularBuffer<TObject>*>(this)->curr_d = read_d;
  const_cast<CircularBuffer<TObject>&>(compare_cbuf_a).curr_d =
    compare_cbuf_a.read_d;
  
  // loop over each valid element and see if each is equivalent
  //
  for (int32 i = 0; i < num_elements; i++) {
    
    // see if the current items are equal
    //
    TObject value;
    getElement(value, i);
    if (!value.eq(compare_cbuf_a(i))) {
      
      // resume the curr_d and exit
      //
      const_cast<CircularBuffer<TObject>*>(this)->curr_d = old_curr;
      const_cast<CircularBuffer<TObject>&>(compare_cbuf_a).curr_d =
	compare_old_curr;
      return false;
    }
  }
  
  // resume the curr_d
  //
  const_cast<CircularBuffer<TObject>*>(this)->curr_d = old_curr;
  const_cast<CircularBuffer<TObject>&>(compare_cbuf_a).curr_d =
    compare_old_curr;

  // number of forward and backward should also be equal
  //
  if ((getNumForward() != compare_cbuf_a.getNumForward()) ||
      (getNumBackward() != compare_cbuf_a.getNumBackward())) {
    
    // exit ungracefully
    //
    return false;
  }
  
  // equal, exit gracefully
  //
  return true;
}

//-------------------------------------------------------------------------
//
//  required clear methods
//
//-------------------------------------------------------------------------

// method: clear
//
// arguments:
//  Integral::CMODE cmode_a: (input) clear mode
//
// return: a bool8 value indicating status
//
// set the class variables to default values and call the clear method
// for the vector.
// 
template<class TObject>
bool8 CircularBuffer<TObject>::clear(Integral::CMODE cmode_a) {

  // cmode_a: RESET, RELEASE or FREE
  //
  if (cmode_a != Integral::RETAIN) {

    // reset the position indices
    //
    read_d = DEF_READ_IDX;
    write_d = DEF_WRITE_IDX;
    curr_d = DEF_CURR_IDX;
  }

  // cmode_a: RETAIN, RELEASE or FREE
  //
  if (cmode_a != Integral::RESET) {
    
    // pass the release mode along to the vector and let it take care
    // of clearing
    //
    return v_d.clear(cmode_a);
  }

  // cmode_a: RESET
  //
  else {

    // exit gracefully
    //
    return true;
  }
}

// ----------------------------------------------------------------------
//
// class-specific public methods:
//  operator overload methods
//
//------------------------------------------------------------------------

// method: operator()
//
// arguments:
//  int32 offset: (input) the offset with respect to the curr_d
//
// return: the TObect element
//
// this method gets an element of the circular buffer
//
template<class TObject>
TObject& CircularBuffer<TObject>::operator() (int32 offset_a) {

  if ((offset_a > 0 && offset_a > getNumForward()) ||
      (offset_a < 0 && offset_a < (-1 * getNumBackward()))) {
    
    Error::handle(name(), L"operator()", Error::ARG, __FILE__, __LINE__);
  }

  // get the element
  //
  int32 index = curr_d + offset_a;
  int32 capacity = getCapacity();
  
  while (index > capacity -1) {
    index -= capacity;
  }
  while (index < 0) {
    index += capacity;
  }
  
  // return the value
  //
  return v_d(index);
}

// method: operator()
//
// arguments:
//  int32 offset: (input) the offset with respect to the curr_d
//
// return: the TObect element
//
// this method gets an element of the circular buffer
//
template<class TObject>
const TObject& CircularBuffer<TObject>::operator() (int32 offset_a) const {

  if ((offset_a > 0 && offset_a > getNumForward()) ||
      (offset_a < 0 && offset_a < (-1 * getNumBackward()))) {
    
    Error::handle(name(), L"operator()", Error::ARG, __FILE__, __LINE__);
  }
 
  // get the element
  //
  int32 index = curr_d + offset_a;
  int32 capacity = getCapacity();
  
  while (index > (capacity - 1)) {
    index -= capacity;
  }
  while (index < 0) {
    index += capacity;
  }
  
  // return the value
  //
  return v_d(index);
}

//---------------------------------------------------------------------------
//
// class-specific public methods:
//  get methods
//
//---------------------------------------------------------------------------
  
// method: getElement
// 
// arguments:
//  TObject& out: (output) the output data
//  int32 offset: (input) the offset with respect to curr_d in circular buffer
//
// return: a bool8 value indicating status
//
// this method gets data at certain position from the circular buffer
//
template<class TObject>
bool8 CircularBuffer<TObject>::getElement(TObject& out_a, int32 offset_a)
  const {

  if ((offset_a > 0 && offset_a > getNumForward()) ||
      (offset_a < 0 && offset_a < (-1 * getNumBackward()))) {
    
    return Error::handle(name(), L"getElement", Error::ARG, __FILE__,
			 __LINE__);
  }
  
  // get the element
  //
  int32 index = curr_d + offset_a;
  int32 capacity = getCapacity();
  
  while (index > capacity -1) {
    index -= capacity;
  }
  while (index < 0) {
    index += capacity;
  }

  // assign the value
  //
  out_a.assign(v_d(index));
  
  // exit gracefully
  //
  return true;
}

// method: getElement
// 
// arguments:
//  Vector<TObject>& out: (output) the output data
//  int32 num_elem: (input) the number of elements to get
//  int32 offset: (input) the offset with respect to curr_d in circular buffer
//
// return: a bool8 value indicating status
//
// this method gets data at certain position from the circular buffer
//
template<class TObject>
bool8 CircularBuffer<TObject>::getElement(Vector<TObject>& out_a,
					    int32 num_elem_a,
					    int32 offset_a) const {

  // local variables
  //
  TObject obj;
  
  // set the length of vector
  //
  out_a.setLength(num_elem_a);
  
  // get each element and assign it to the output vector
  //
  for (int32 i = 0; i < num_elem_a; i++) {
    getElement(out_a(i), offset_a);
    offset_a++;
  }
  
  // exit gracefully
  //
  return true;
}

// method: getNumElements
// 
// arguments: none
//   
// return: a int32 number 
//
// this method gets the number of valid elements of the circular buffer
//
template<class TObject>
int32 CircularBuffer<TObject>::getNumElements() const {
  
  // local variables
  //
  int32 capacity = getCapacity();
  
  // check the position of the read_d and write_d
  //
  if (isEmpty()) {
    return 0;
  }

  int32 dist = (write_d - read_d + capacity + 1) % capacity;
  
  if (dist == 0) {
    return capacity;
  }
  
  // return the number
  //
  return dist;
}

// method: getNumForward
// 
// arguments: none
//   
// return: a int32 number 
//
// this method gets the number of valid elements in front of curr_d (not
// including itself) 
//
template<class TObject>
int32 CircularBuffer<TObject>::getNumForward() const {

  // local variables
  //
  int32 num = 0;
  
  if (isEmpty()) {
    num = 0;
  }
  else if (curr_d == read_d) {
    num = getNumElements() - 1;
  }
  else {
    int32 capacity = getCapacity();
    num = (write_d - curr_d + capacity) % capacity;
  }
  
  // return the number
  //
  return num;
}

// method: getNumBackward
// 
// arguments: none
//   
// return: a int32 number 
//
// this method gets the number of valid elements lag of curr_d (not including
// itself) 
//
template<class TObject>
int32 CircularBuffer<TObject>::getNumBackward() const {
  
  // local variables
  //
  int32 num = 0;
  
  if (isEmpty()) {
    num = 0;
  }
  else if (curr_d == write_d) {
    num = getNumElements() - 1;
  }
  else {
    int32 capacity = getCapacity();
    num = (curr_d - read_d + capacity) % capacity;
  }
  
  // return the number
  //
  return num;
}

//---------------------------------------------------------------------------
//
// class-specific public methods:
//  class property methods
//
//---------------------------------------------------------------------------

// method: isFull
// 
// arguments: none
//
// return: a bool8 value indicating status
//
// this method check if the circular buffer is full
//
template<class TObject>
bool8 CircularBuffer<TObject>::isFull() const {
  
  // check if it's empty
  //
  if (isEmpty()) {
   return false;
  }
  
  // check the position of the read_d and write_d
  //
  int32 capacity = getCapacity();
  return (((write_d - read_d + capacity + 1) % capacity) == 0);
}

// method: isEmpty
// 
// arguments: none
//
// return: a bool8 value indicating status
//
// this method check if the circular buffer is empty
//
template<class TObject>
bool8 CircularBuffer<TObject>::isEmpty() const {
  
  // check if it's empty
  //
  bool8 ret = (write_d == DEF_WRITE_IDX);
  ret &= (read_d == DEF_READ_IDX);

  return ret;
}

//---------------------------------------------------------------------------
//
// class-specific public methods:
//  data manipulation methods
//
//---------------------------------------------------------------------------

// method: append
// 
// arguments:
//  TObject& in: (input) the data to add
//
// return: a bool8 value indicating status
//
// this method appends new data to the circular buffer
//
template<class TObject>
bool8 CircularBuffer<TObject>::append(const TObject& in_a) {
  
  // check now if the buffer is writable
  //
  if (isFull()) {
    return Error::handle(name(), L"append", ERR_FULL, __FILE__, __LINE__);
  }
  
  // advance the write_d and add the data
  //
  write_d = ((int32)write_d + 1) % getCapacity();
  
  v_d(write_d).assign(in_a);
  
  // exit gracefully
  //
  return true;
}

// method: prepend
// 
// arguments:
//  TObject& in: (input) the data to add
//
// return: a bool8 value indicating status
//
// this method appends new data to the circular buffer
//
template<class TObject>
bool8 CircularBuffer<TObject>::prepend(const TObject& in_a) {

  // check if number of elements to be appended are equal to the capacity
  //
  int32 cap = getCapacity();
  int32 numele = getNumElements();
  if (numele == (cap - 1)) {
     return Error::handle(name(), L"prepend-> no. of elements to be prepend equals to the capacity", ERR_FULL, __FILE__, __LINE__);
  }
  
  // check now if the buffer is writable
  //
  if (isFull()) {
    return Error::handle(name(), L"prepend", ERR_FULL, __FILE__, __LINE__);
  }
  
  // decrement read_d and add the data
  //
  read_d = (int32)read_d - 1;

  if ((int32)read_d < 0) {
    read_d += getCapacity();
  }
  
  v_d(read_d).assign(in_a);
  
  // exit gracefully
  //
  return true;
}

// method: append
// 
// arguments:
//  Vector<TObject> in: (input) the data to add
//
// return: a bool8 value indicating status
//
// this method appends new data to the circular buffer
//
template<class TObject>
bool8 CircularBuffer<TObject>::append(const Vector<TObject>& in_a) {
  
  // get the number of elements of the input vector
  //
  int32 num_elem = in_a.length();
  
  // append each element
  //
  append(in_a, num_elem, (int32)0);
  
  // exit gracefully
  //
  return true;
}

// method: prepend
// 
// arguments:
//  Vector<TObject> in: (input) the data to add
//
// return: a bool8 value indicating status
//
// this method prepends new data to the circular buffer
//
template<class TObject>
bool8 CircularBuffer<TObject>::prepend(const Vector<TObject>& in_a) {
  
  // get the number of elements of the input vector
  //
  int32 num_elem = in_a.length();
  
  // append each element
  //
  prepend(in_a, num_elem, (int32)0);
  
  // exit gracefully
  //
  return true;
}


// method: append
// 
// arguments:
//  Vector<TObject> in: (input) the data to add
//  int32 num: (input) the number of element to add
//  int32 invec_offset: (input) the start index in the input vector
//
// return: a bool8 value indicating status
//
// this method appends new data to the circular buffer
//
template<class TObject>
bool8 CircularBuffer<TObject>::append(const Vector<TObject>& in_a,
					int32 num_a, int32 invec_offset_a) {
  
  // get the number of elements of the input vector
  //
  int32 num_elem = in_a.length();
  
  if (num_a + invec_offset_a > num_elem) {
    num_a = num_elem - invec_offset_a;
  }
  
  // append each element
  //
  for (int32 i = 0; i < num_a; i++) {
    append(in_a(invec_offset_a + i));
  }
  
  // exit gracefully
  //
  return true;
}

// method: prepend
// 
// arguments:
//  Vector<TObject> in: (input) the data to add
//  int32 num: (input) the number of element to add
//  int32 invec_offset: (input) the start index in the input vector
//
// return: a bool8 value indicating status
//
// this method prepends new data to the circular buffer
//
template<class TObject>
bool8 CircularBuffer<TObject>::prepend(const Vector<TObject>& in_a,
					int32 num_a, int32 invec_offset_a) {
  
  // get the number of elements of the input vector
  //
  int32 num_elem = in_a.length();
  
  if (num_a + invec_offset_a > num_elem) {
    num_a = num_elem - invec_offset_a;
  }
  
  // append each element
  //
  for (int32 i = 0; i < num_a; i++) {
    prepend(in_a(invec_offset_a + i));
  }
  
  // exit gracefully
  //
  return true;
}

//---------------------------------------------------------------------------
//
// class-specific public methods:
//  positioning methods
//
//---------------------------------------------------------------------------

// method: seekCurr
// 
// arguments:
//  int32 offset: (input) the offset with respect to curr_d in circular buffer
//
// return: a bool8 value indicating status
//
// this method moves the curr_d 
//
template<class TObject>
bool8 CircularBuffer<TObject>::seekCurr(int32 offset_a) {
  
  int32 capacity = getCapacity();
  
  // curr_d should reside between read_d and write_d
  //
  if ((offset_a > 0 && offset_a > getNumForward()) ||
      (offset_a < 0 && offset_a < (-1* getNumBackward()))) {
    return Error::handle(name(), L"seekCurr", Error::ARG, __FILE__, __LINE__);
  }
  
  // compute
  //
  curr_d += offset_a;
  
  if (curr_d > capacity - 1) {
    curr_d -= capacity;
  }
  else if ((int32)curr_d < 0) {
    curr_d += capacity;
  }
  
  // exit gracefully
  //
  return true;
}

// method: setRead
// 
// arguments:
//  int32 num_read: (input) the numbers to move the read_d forward
//
// return: a bool8 value indicating status
//
// this method moves the read_d
//
template<class TObject>
bool8 CircularBuffer<TObject>::setRead(int32 num_read_a) {
  
  // read_d can't move backward
  //
  if (num_read_a < 0) {
    return Error::handle(name(), L"setRead", Error::ARG, __FILE__, __LINE__);
  }

  if (getNumElements() == num_read_a) {

    // reset the circular buffer to be empty
    //
    clear(Integral::RESET);
  }
  
  else {
    
    // get capacity
    //
    int32 capacity = getCapacity();
  
    // compute
    //
    int32 tmp_read_idx = read_d + num_read_a;
  
    if (tmp_read_idx > capacity - 1) {
      tmp_read_idx -= capacity;
    }
  
    // move curr_d if necessary to make sure it is still in the proper range
    //
    if (getNumBackward() < num_read_a) {
      curr_d = tmp_read_idx;
    }
  
    // move the read_d
    //
    read_d = tmp_read_idx;
  }
  
  // exit gracefully
  //
  return true;
}

// end of include file
//
#endif
