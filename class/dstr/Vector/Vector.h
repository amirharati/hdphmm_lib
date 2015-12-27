// file: $isip/class/dstr/Vector/Vector.h
// version: $Id: Vector.h 10675 2009-07-21 01:13:30Z tm334 $
//

// make sure definitions are made only once
//
#ifndef ISIP_VECTOR
#define ISIP_VECTOR

// isip include files
//
#ifndef ISIP_DSTR_BASE
#include <DstrBase.h>
#endif

#ifndef ISIP_DOUBLE_LINKED_LIST
#include <DoubleLinkedList.h>
#endif

#ifndef ISIP_LONG
#include <Long.h>
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

#ifndef ISIP_STACK
#include <Stack.h>
#endif

// forward class definitions
//
template<class TObject> class VectorDiagnose;

// Vector: a generic vector template class. it is simply a container
// class to hold an array of objects, such as Char, String, etc.
//
template<class TObject>
class Vector : public DstrBase {
  
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
  static const String BLOCK_START_STR;      // L"{\n";
  static const String BLOCK_DELIM_STR;      // L"}, {\n";
  static const String BLOCK_END_STR;        // L"}";
  static const String BLOCK_TERM_STR;       // L";\n";

  // define how the skip table will be written in binary mode
  //
  static const int32 SKIP_TABLE_GROUP = Sof::SKIP_TABLE_GROUP;
  static const int32 SKIP_TABLE_SKIP = 100;
  static const int32 SKIP_TABLE_LENGTH = SKIP_TABLE_GROUP * sizeof(int32);
  
  // i/o data buffering lengths
  //
  static const int32 TEXT_WRITE_SIZE = 512;
  
  //----------------------------------------
  //
  // default values and arguments
  //
  //----------------------------------------

  // default values
  //
  static const int32 DEF_LENGTH = 0;
  static const int32 DEF_END_POS = -1;
  
  // default arguments to methods
  //
  
  //----------------------------------------
  //
  // error codes
  //
  //----------------------------------------  
  
  static const int32 ERR = 40900;
  static const int32 ERR_WMODE = 40901;
  
  //---------------------------------------------------------------------------
  //
  // protected data
  //
  //---------------------------------------------------------------------------
protected:

  // vector elements 
  //
  TObject* v_d;

  // number of elements of this vector
  //
  Long length_d;

  // the maximum number of elements
  //
  Long capacity_d;
  
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
  //  diagnose method is moved outside the class header file and
  //  defined in VectorDiagnose.h in order to avoid issues
  //  related to preprocessing of the diagnose code.
  //
  static const String& name();

  // method: setDebug
  //
  static bool8 setDebug(Integral::DEBUG level) {
    debug_level_d = level;
    return true;
  }

  // other debug methods
  //
  bool8 debug(const unichar* message) const;

  // destructor/constructor(s)
  //
  ~Vector();
  Vector(int32 length = DEF_LENGTH);
  Vector(const Vector<TObject>& copy_vector);
  
  // assign methods
  //
  bool8 assign(const Vector<TObject>& copy_vector);

  // method: operator=
  //
  Vector<TObject>& operator=(const Vector<TObject>& arg) {
    assign(arg);
    return *this;
  }

  // equality methods
  //
  bool8 eq(const Vector<TObject>& compare_vector) const;
      
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
  //  sofSize determines the amount of disk storage needed for this object;
  //  the read and write methods are for full object i/o;
  //  the readData and writeData methods handle i/o when this object is
  //  a component of another object.
  //
  int32 sofSize() const;

  bool8 read(Sof& sof, int32 tag, const String& name);
  bool8 write(Sof& sof, int32 tag, const String& name) const;

  bool8 readData(Sof& sof, const String& pname = DEF_PARAM,
		   int32 size = SofParser::FULL_OBJECT,
                   bool8 param = true,
		   bool8 nested = true);
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
  
  // assign methods:
  //
  bool8 assign(TObject& arg);    

  // method: ne
  //
  bool8 ne(const Vector<TObject>& arg) const {
    return (!eq(arg));
  }
  
  // partial read methods:
  //  these methods must work together to complete the read
  //
  bool8 readStart(Sof& sof, const String& pname = DEF_PARAM,
		    int32 size = SofParser::FULL_OBJECT,
		    bool8 param = true,
		    bool8 nested = true);
  
  int32 readPartialData(Sof& sof, int32 start_pos, int32 num_elem,
		       const String& pname = DEF_PARAM,
		       int32 size = SofParser::FULL_OBJECT,
                       bool8 param = true,
                       bool8 nested = false);

  // method: readTerminate
  //
  bool8 readTerminate(Sof& sof) {
    return sof.stopPartialRead();
  }

  // partial write methods:
  //  these methods must work together to complete the write
  //  
  bool8 writeStart(Sof& sof, const String& pname = DEF_PARAM) const;

  int32 writePartialData(Sof& sof, int32 start_pos, int32 num_elem) const;

  bool8 writeTerminate(Sof& sof, const String& pname = DEF_PARAM) const;

  //---------------------------------------------------------------------------
  //
  // class-specific public methods:
  //  item access methods
  //
  //--------------------------------------------------------------------------
  
  // method: operator()
  //
  TObject& operator()(int32 index) {

    // do range checking in this construct so it will be optimized out
    //
    ISIP_FULL_CHECK(if ((index < 0) || (index >= (int32)length_d)) {
      Error::handle(name(), L"operator()", Error::BOUNDS, __FILE__, __LINE__);
      static TObject ptr;
      return ptr;
    })
      
      return v_d[index];
  }
  
  // method: operator()
  //
  const TObject& operator()(int32 index) const {

    // do range checking in this construct so it will be optimized out
    //
    ISIP_FULL_CHECK(if ((index < 0) || (index >= (int32)length_d)) {
      Error::handle(name(), L"operator()", Error::BOUNDS, __FILE__, __LINE__);
      static TObject ptr;
      return ptr;
    })
      
      return v_d[index];
  }

  //---------------------------------------------------------------------------
  //
  // class-specific public methods:
  //  size-related methods
  //
  //--------------------------------------------------------------------------
  
  // method: length
  //
  int32 length() const {
    return (int32)length_d;
  }

  // method: getCapacity
  //
  int32 getCapacity() const {
    return (int32)capacity_d;
  }

  // method to get vector size
  //
  int32 getVectorSize(int32 offset_a, Sof& sof_a);
  
  int32 getVectorSize(Sof& sof, int32 tag,
		     const String& name = name(),
		     const String& pname = DEF_PARAM,
		     int32 size = SofParser::FULL_OBJECT,
		     bool8 param = true,
		     bool8 nested = true);
  
  
  
  // resize methods
  //
  bool8 setLength(int32 length, bool8 preserve_values = true);
  bool8 setCapacity(int32 capacity, bool8 preserve_values = true);

  //---------------------------------------------------------------------------
  //
  // class-specific public methods:
  //  data manipulation methods
  //
  //--------------------------------------------------------------------------
  
  // positioning methods
  //
  bool8 move(const Vector<TObject>& source_vector, int32 num_elements,
	       int32 source_offset, int32 dest_offset);
  
  bool8 shift(const Vector<TObject>& source_vector, int32 delta);
  bool8 shift(int32 delta);

  // concatenation methods
  //
  bool8 concat(const Vector<TObject>& v2);
  bool8 concat(const Vector<TObject>& v1, const Vector<TObject>& v2);
  bool8 concat(const TObject& obj);

  // range operation methods
  //
  bool8 deleteRange(const Vector<TObject>& arg, int32 offset,
		      int32 num_elements);
  bool8 deleteRange(int32 offset, int32 num_elements);
  bool8 setRange(int32 offset, int32 num_elements, const TObject& value);
  
  // sort methods
  //
  bool8 sort(Integral::ORDER sort_order = Integral::ASCENDING,
	       SORT_ALGO = DEF_SORT_ALGO);

  //---------------------------------------------------------------------------
  //
  // class-specific public methods:
  //  item location and containment methods
  //
  //--------------------------------------------------------------------------
  
  // element location methods
  //
  int32 first(const TObject& value, int32 start_pos = Integral::NO_POS) const;
  int32 last(const TObject& value, int32 end_pos = Integral::NO_POS) const;

  // method: contains
  //
  bool8 contains(int32& index, const TObject* value) const {
    index = Integral::NO_POS;
    return ((value != (TObject*)NULL) &&
	    ((index = first(*value)) != Integral::NO_POS));
  }

  // method: contains
  //
  bool8 contains(const TObject* value) const {
    int32 index;
    return contains(index, value);
  }

  //---------------------------------------------------------------------------
  //
  // class-specific public methods:
  //  apply methods
  //
  //--------------------------------------------------------------------------
  
  // method: apply
  //
  bool8 apply(bool8 (TObject::*method)(), Vector<TObject>& arg) {
    assign(arg);
    return apply(method);
  }
  
  // other apply methods:
  //  methods to apply an external function to each element in the vector
  //
  bool8 apply(bool8 (TObject::*method)());

  //---------------------------------------------------------------------------
  //
  // private methods
  //
  //---------------------------------------------------------------------------
private:
  
  // sort methods
  //
  bool8 randQuickSort(Integral::ORDER sort_order);
  bool8 insertionSort(Integral::ORDER sort_order);

  bool8 clearBinPos(int32* bin_pos) const;
  
  // friend class
  //
  template <class TObject_diagnose> 
  friend class VectorDiagnose;    
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
const String Vector<TObject>::CLASS_NAME(L"Vector");

// constants: required constants for i/o methods
//
template <class TObject>
const String Vector<TObject>::DEF_PARAM(L"values");

template <class TObject>
const String Vector<TObject>::BLOCK_START_STR(L"{\n");

template <class TObject>
const String Vector<TObject>::BLOCK_DELIM_STR(L"}, {\n");

template <class TObject>
const String Vector<TObject>::BLOCK_END_STR(L"}");

template <class TObject>
const String Vector<TObject>::BLOCK_TERM_STR(L";\n");

// static instantiations: debug level and memory manager
//
template <class TObject>
Integral::DEBUG Vector<TObject>::debug_level_d = Integral::NONE;

template <class TObject>
MemoryManager Vector<TObject>::mgr_d(sizeof(Vector<TObject>), CLASS_NAME);

// below are all the methods for the Vector template class
//

//-----------------------------------------------------------------------
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
const String& Vector<TObject>::name() {

  // create the static name string for this class and return it
  //
  static String cname;
  cname.clear();
  cname.concat(CLASS_NAME);
  cname.concat(L"<");
  cname.concat(TObject::name());
  cname.concat(L">");
  
  // return the name
  //
  return cname;
}

//---------------------------------------------------------------------
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
bool8 Vector<TObject>::debug(const unichar* message_a) const {

  // declare temporary strings to hold class data
  //
  String output;
  String value;
  String param;
  String numeric;
  
  // dump the length
  //
  value.assign((int32)length_d);
  output.debugStr(name(), message_a, L"length_d", value);
  Console::put(output);

  // dump the capacity
  //
  value.assign((int32)capacity_d);
  output.debugStr(name(), message_a, L"capacity_d", value);
  Console::put(output);

  // dump the values
  //
  for (int32 i = 0; i < (int32)length_d; i++) {

    param.assign(L"v_d[");
    value.assign(i);

    param.concat(value);
    param.concat(L"]");
    output.debugStr(name(), message_a, param);
    Console::put(output);

    // increase indention
    //
    Console::increaseIndention();
    
    // call the debug method of the element
    //
    v_d[i].debug(L"");

    Console::decreaseIndention();
  }
  
  // exit gracefully
  // 
  return true;
}

//------------------------------------------------------------------------
//
// required destructor/constructor(s)
//
//-----------------------------------------------------------------------

// method: destructor
//
// arguments: none
//
// return: none
//
// this is the default destructor for the Vector class
//
template<class TObject>
Vector<TObject>::~Vector() {

  // free memory
  //
  clear(Integral::RELEASE);
  
  // exit gracefully
  //
}

// method: default constructor
//
// arguments:
//  int32 length: (input) number of elements
//
// return: none
//
template<class TObject>
Vector<TObject>::Vector(int32 length_a) {

  // initialize data
  // 
  length_d = (int32)0;
  capacity_d = (int32)0;
  v_d = (TObject*)NULL;
  
  // set the length
  //
  if (!setLength(length_a)) {
    Error::handle(name(), L"default constructor", Error::NOMEM, __FILE__,
		  __LINE__);
  }
  
  // exit gracefully
  //
}

// method: copy constructor
//
// arguments:
//  const Vector<TObject>& copy_vector: (input) the vector to copy
//
// return: none
//
template<class TObject>
Vector<TObject>::Vector(const Vector<TObject>& copy_vector_a) {

  // initialize data
  // 
  length_d = (int32)0;
  capacity_d = (int32)0;
  v_d = (TObject*)NULL;
  
  // call the assign method to copy the vector
  //
  assign(copy_vector_a);
  
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
//  const Vector<TObject>& copy_vector: (input) the vector to copy
//
// return: a bool8 value indicating status
//
// this method copies the contents of the input to this vector
//
template<class TObject>
bool8 Vector<TObject>::assign(const Vector<TObject>& copy_vector_a) {

  // resize the vector
  // 
  if (!setLength(copy_vector_a.length(), false)) {
    return Error::handle(name(), L"assign", Error::NOMEM, __FILE__, __LINE__);
  }
  
  // copy the data
  // 
  for (int32 index = 0; index < (int32)length_d; index++) {
    v_d[index].assign(copy_vector_a.v_d[index]);
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
int32 Vector<TObject>::sofSize() const {
  
  // start with the length
  //
  int32 bytes = length_d.sofSize();

  // add each element
  //
  for (int32 i = 0; i < length_d; i++) {
    if ((i % (SKIP_TABLE_SKIP * SKIP_TABLE_GROUP)) == 0) {
      bytes += sizeof(int32) * SKIP_TABLE_GROUP;
    }
    bytes += v_d[i].sofSize();
  }

  // return the size
  //
  return bytes;
}

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
bool8 Vector<TObject>::read(Sof& sof_a, int32 tag_a, const String& name_a) {
  
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
//  const String& name: (input) sof object instance name
//
// return: a bool8 value indicating status
//
// this method has the object write itself to an Sof file
//
template<class TObject>
bool8 Vector<TObject>::write(Sof& sof_a, int32 tag_a, const String& name_a)
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
  
  // write the object into the sof file's index
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
//  const String& pname: (input) parameter name
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
bool8 Vector<TObject>::readData(Sof& sof_a, const String& pname_a,
				  int32 size_a, bool8 param_a,
				  bool8 nested_a) {
  
  // first cleanup the list
  //
  if (!clear(Integral::FREE)) {
    return Error::handle(name(), L"readData", Error::READ,
			 __FILE__, __LINE__, Error::WARNING);
  }

  // local variables
  //
  SofParser parser;
  String pname;
  
  // if param is false, this means implicit parameter
  //
  if (!param_a) {
    if (!parser.setImplicitParam()) {
      return Error::handle(name(), L"readData", Error::READ,
			   __FILE__, __LINE__, Error::WARNING);
    }
    if (!pname.assign(parser.implicitPname())) {
      return Error::handle(name(), L"readData", Error::READ,
			   __FILE__, __LINE__, Error::WARNING);
    }      
  }
  else {
    pname.assign(pname_a);
  }
  
  // are we nested?
  //
  if (nested_a) {
    parser.setNest();
  }
  
  // load the parse
  //
  parser.load(sof_a, size_a);

  Long new_size((int32)0);
  
  // read the length first: this differs for text or binary
  //
  if (sof_a.isText()) {
    new_size = parser.countTokens(pname);
  }

  // binary mode
  //
  else {
    if (!new_size.readData(sof_a, pname)) {
      return Error::handle(name(), L"readData", Error::READ,
			   __FILE__, __LINE__, Error::WARNING);
    }      
  }

  if (debug_level_d >= Integral::DETAILED) {
    new_size.debug(L"new_size");
  }
  
  // set length destructively
  //
  if (!setLength(new_size, false)) {
    return Error::handle(name(), L"readData", Error::ARG, __FILE__, __LINE__);
  }

  // we need to also read in the skip table. we verify the values in
  // the skip table as a sort of checksum
  //
  static int32 bin_pos[SKIP_TABLE_GROUP];
  int32 skip_pos = 0;
  int32 skip_incr = 0;
  
  // read a node at a time
  //
  for (int32 i = 0; i < new_size; i++) {

    if (sof_a.isBinary() &&
	((i % (SKIP_TABLE_SKIP * SKIP_TABLE_GROUP)) == 0)) {
      if (debug_level_d >= Integral::ALL) {
	String output(L"reading skip table from position ");
	output.concat(sof_a.tell());
	Console::put(output);
      }

      if (i > 0) {
	skip_pos = bin_pos[SKIP_TABLE_GROUP - 1] + SKIP_TABLE_LENGTH;
	skip_incr = 0;
      } 

      if (sof_a.read(bin_pos, sizeof(int32),
		     SKIP_TABLE_GROUP) != SKIP_TABLE_GROUP) {
	return Error::handle(name(), L"readData", Error::ARG,
			     __FILE__, __LINE__, Error::WARNING);
      }

      if (i == 0) {
	skip_pos = bin_pos[skip_incr++];
      }
    }

    if (sof_a.isBinary()) {

      // verify the values in the skip table
      //
      if ((i > 0) && ((i % SKIP_TABLE_SKIP) == 0)) {
	int32 cur_pos = sof_a.tell();
	
	if (skip_pos != cur_pos) {
	  String output(L"skip_pos = ");
	  output.concat(skip_pos);
	  output.concat(L", cur_pos = ");
	  output.concat(cur_pos);
	  output.concat(L", skip_incr = ");
	  output.concat(skip_incr);
	  output.concat(L", i = ");
	  output.concat(i);
	  Console::put(output);
	  return Error::handle(name(), L"readData", Error::READ,
			       __FILE__, __LINE__, Error::WARNING);
	}
	skip_pos = bin_pos[skip_incr++];
      }
    }
    
    // read the node
    //
    if (!v_d[i].readData(sof_a, pname, parser.getEntry(sof_a, pname, i, 1),
			 false, true)) {

      return Error::handle(name(), L"readData", Error::WARNING, __FILE__,
			   __LINE__, Error::WARNING);
    }
  }
  
  // exit gracefully
  //
  return true;
}

// method: writeData
//
// arguments:
//  Sof& sof: (input) sof file object
//  const String& pname: (input) parameter name
//
// return: a bool8 value indicating status
//
// this method writes the object to the Sof file. it assumes that the
// Sof file is already positioned correctly.
//
template<class TObject>
bool8 Vector<TObject>::writeData(Sof& sof_a, const String& pname_a) const {

  // make sure we are in write-in-full mode
  //
  if (sof_a.getPartialWrite()) {
    return Error::handle(name(), L"writeData", ERR_WMODE, __FILE__,
			 __LINE__);
  }
  
  // we need an empty string for the sub-parameter
  //
  String empty_str;

  // for binary writes we will need an array of positions
  //
  int32 bin_pos_incr = 0;
  int32 bin_pos[SKIP_TABLE_GROUP];
  int32 last_bin_pos = 0;

  for (int32 i = 0; i < SKIP_TABLE_GROUP; i++) {
    bin_pos[i] = -1;
  }
  
  // if text, write a parameter name. this can't be done with
  // writeLabelPrefix because an empty list gets no brackets
  //
  if (sof_a.isText()) {

    if (pname_a.length() > 0) {
      String output;
      output.assign(pname_a);
      output.concat(SofParser::SPACE_CHAR);
      output.concat(SofParser::DEF_ASSIGNMENT_CHAR);
      output.concat(SofParser::SPACE_CHAR);
      sof_a.puts(output);
    }
    if ((int32)length_d > 0) {
      sof_a.puts(BLOCK_START_STR);
    }
  }
  
  // for binary, write length and bin pos
  //
  else {
    
    if (!length_d.writeData(sof_a)) {
      return Error::handle(name(), L"writeData", Error::IO,__FILE__,__LINE__);
    }

    last_bin_pos = sof_a.tell();
    if ((int32)length_d > 0) {
      if (!sof_a.write(bin_pos, sizeof(int32), SKIP_TABLE_GROUP)) {
	return Error::handle(name(), L"writeData", Error::IO,
			     __FILE__, __LINE__);
      }
    }
  }
  
  bool8 is_first = true;
  
  // loop through the vector
  //
  for (int32 i = 0; i < length_d; i++) {

    if (sof_a.isText()) {
      if (!is_first) {
	sof_a.decreaseIndention();
	sof_a.puts(BLOCK_DELIM_STR);
      }
      sof_a.increaseIndention();
      is_first = false;
    }

    // do we need to update the skip table?
    //
    if (sof_a.isBinary() && (i > 0) && ((i % SKIP_TABLE_SKIP) == 0)) {

      // update the current table with this position
      //
      bin_pos[bin_pos_incr++] = (int32)sof_a.tell();

      if (bin_pos_incr == SKIP_TABLE_GROUP) {
	bin_pos_incr = 0;

	// seek back and write the last bin pos table
	//
	sof_a.seek(last_bin_pos, File::POS);
	if (!sof_a.write(bin_pos, sizeof(int32), SKIP_TABLE_GROUP)) {
	  return Error::handle(name(), L"writeData", Error::IO,__FILE__,__LINE__);
	}

	// seek back to the current one
	//
	last_bin_pos = bin_pos[SKIP_TABLE_GROUP - 1];
	sof_a.seek(last_bin_pos, File::POS);

	// write out the next dummy table
	//
	clearBinPos(bin_pos);
	if (!sof_a.write(bin_pos, sizeof(int32), SKIP_TABLE_GROUP)) {
	  return Error::handle(name(), L"writeData", Error::IO,__FILE__,__LINE__);
	}
      }
    }

    // write this element
    //
    if (!v_d[i].writeData(sof_a, empty_str)) {
      return Error::handle(name(), L"writeData",Error::IO, __FILE__, __LINE__);
    }
  }
  
  if (sof_a.isText()) {

    // write the close brace
    //
    if ((int32)length_d > 0) {
      sof_a.decreaseIndention();
      sof_a.puts(BLOCK_END_STR);
    }
    
    // possibly terminate the statement
    //
    if (pname_a.length() > 0) {
      sof_a.puts(BLOCK_TERM_STR);
    }
  }

  // for binary mode update the last bin_pos table
  //
  else {

    if (bin_pos_incr > 0) {

      int32 cur_pos = sof_a.tell();
      sof_a.seek(last_bin_pos, File::POS);

      if (!sof_a.write(bin_pos, sizeof(int32), SKIP_TABLE_GROUP)) {
	return Error::handle(name(), L"writeData", Error::IO,__FILE__,__LINE__);
      }

      sof_a.seek(cur_pos, File::POS);
    }
  }

  // exit gracefully
  //
  return true;
}

//------------------------------------------------------------------------
//
// required equality methods
//
//------------------------------------------------------------------------

// method: eq
//
// arguments:
//  const Vector<TObject>& compare_vector: (input) the vector to compare
//
// return: a bool8 value indicating status
//
// this method compares two vectors for equivalence. two vectors are equivalent
// if all corresponding items are equivalent
//
template<class TObject>
bool8 Vector<TObject>::eq(const Vector<TObject>& compare_vector_a) const {
  
  // declare the output variable
  //
  bool8 are_equal = true;

  // two vectors can not be equivalent if they are of differing lengths
  //
  if (length_d != compare_vector_a.length_d) {
    
    // set the break flag
    //
    are_equal = false;
  }

  // loop over each element and see if each is equivalent
  //
  for (int32 i = 0; are_equal && (i < (int32)length_d); i++) {
    
    // see if the current items are equal
    //
    are_equal = v_d[i].eq(compare_vector_a.v_d[i]);
  }
  
  // return a value representing if they are equivalent
  //
  return are_equal;
}

//-------------------------------------------------------------------------
//
// required memory management methods
//
//-------------------------------------------------------------------------

// method: clear
//
// arguments: 
//  Integral::CMODE cmode_a: (input) clear mode
//  
// return: a bool8 value indicating status
//
// this method clears the contents of the list by the setting of cmode_a
//
//  enum CMODE { RETAIN = 0, RESET, RELEASE, FREE, DEF_CMODE = RESET };
//
// RETAIN: call clear with RETAIN on each element in the vector
//
// RESET: clear the structure but don't necessarily delete memory
//
// RELEASE: clear the structure and release memory
//
// FREE: clear the structure and release memory
//
// Programming hint:
//
// use the clear() method to manage the memory of the objects going
// into the vector.
// particular useful when vector is in USER mode. Caution the object
// you place into vector must have a clear method that meets the
// requirements of the IFC clear method.
//
//
template<class TObject>
bool8 Vector<TObject>::clear(Integral::CMODE cmode_a) {

  // if the cmode_a is RETAIN or FREE, call clear(cmode_a) method for
  // each element
  //  
  if ((cmode_a == Integral::RETAIN) || (cmode_a == Integral::FREE)) {

    // loop over all elements
    //
    int32 i_end = length_d;

    for (int32 i = 0; i < i_end; i++) {
      v_d[i].clear(cmode_a);
    }
  }

  // if the cmode_a is RESET, clear the structure but don't 
  // necessarily delete memory
  //    
  if (cmode_a == Integral::RESET) {
    setLength(0);
  }
  
  // if the cmode_a is RELEASE or FREE, clear the structure and
  // release memory.
  //
  else if ((cmode_a == Integral::RELEASE) || (cmode_a == Integral::FREE)) {

    // free memory -- the setCapacity call will actually release it.
    //
    length_d = 0;
    setCapacity(0);
  }
  
  // exit gracefully
  //
  return true;
}

//-------------------------------------------------------------------------
//
// class-specific public methods:
//  extensions to required methods
//
//-------------------------------------------------------------------------

// method: assign
//
// arguments:
//  TObject& value: (input) sets all elements equal to value_a
//
// return: a bool8 value - true on successful completion
// 
template<class TObject>
bool8 Vector<TObject>::assign(TObject& value_a) {
  
  // assign each element
  // 
  int32 last_index = (int32)length_d;

  if (last_index < (int32)0) {
    return false;
  }
  
  for (int32 index = 0; index < last_index; index++) {
    v_d[index].assign(value_a);
  }
  
  // exit gracefully
  // 
  return true;
}

// method: readStart
//
// arguments:
//  Sof& sof: (input) sof file object
//  const String& pname: (input) parameter name
//  int32 size: (input) size of the object
//  bool8 param: (input) is the parameter specified?
//  bool8 nested: (input) is this nested?
//
// return: logical error status
//
// this method allocate an SofParser object and load the parse. it is
// used for partial read.
//
template<class TObject>
bool8 Vector<TObject>::readStart(Sof& sof_a, const String& pname_a,
				   int32 size_a, bool8 param_a,
				   bool8 nested_a) {
  
  // local variable
  //
  Long new_size((int32)0);
  
  // first cleanup the list
  //
  if (!clear(Integral::RELEASE)) {
    return Error::handle(name(), L"readStart", Error::MEM, __FILE__, __LINE__);
  }

  // start the partial read in Sof
  //
  sof_a.startPartialRead();
  
  // if text, read in a line, else binary read
  //
  if (sof_a.isText()) {
    
    String pname;

    // set the parser debug level
    //
    sof_a.getVecParser().setDebug(debug_level_d);
    
    // if param is false, this means implicit parameter
    //
    if (!param_a) {
      sof_a.getVecParser().setImplicitParam();
      pname.assign(SofParser::implicitPname());
    }
    else {
      pname.assign(pname_a);
    }
    
    // are we nested?
    //
    if (nested_a) {
      sof_a.getVecParser().setNest();
    }
    
    // load the parse
    //
    sof_a.getVecParser().load(sof_a, size_a);

    new_size = sof_a.getVecParser().countTokens(pname);
  }

  // binary mode
  //
  else {
    sof_a.setStartPos(sof_a.tell());
    if (!new_size.readData(sof_a, String::EMPTY)) {
      return false;
    }

    // go ahead and read the first skip table as well
    //
    if ((int32)new_size > 0) {
      if (!sof_a.readSkipTable()) {
	return Error::handle(name(), L"readStart", Error::IO,
			     __FILE__, __LINE__);
      }
    }
  }

  sof_a.setVecSize((int32)new_size);
  sof_a.setVecCurrentElement((int32)0);
  
  // exit gracefully
  //
  return true;
}

// method: readPartialData
//
// arguments:
//  Sof& sof: (input) sof file object
//  int32 start_pos: (input) first entry to read
//  int32 num_elem: (input) number of elements to read
//  const String& pname: (input) parameter name
//  int32 size: (input) size in bytes of object (or FULL_SIZE)
//  bool8 param: (input) is the parameter name in the file?
//  bool8 nested: (input) are we nested?
//
// return: the number of elements read
//
// this method has the object read itself from an Sof file. it assumes
// that the Sof file is already positioned correctly.
//
template<class TObject>
int32 Vector<TObject>::readPartialData(Sof& sof_a, int32 start_pos_a,
				      int32 num_elem_a, const String& pname_a,
				      int32 size_a, bool8 param_a,
				      bool8 nested_a) {

  // check the arguments
  //
  if (num_elem_a <= 0) {
    setLength(0);
    return (int32)0;
  }
  if (start_pos_a < 0) {
    return Error::handle(name(), L"readPartialData", Error::ARG,
                         __FILE__, __LINE__);
  }

  // declare local variable
  //
  String pname;
    
  // if param is false, this means implicit parameter
  //
  if (!param_a) {
    sof_a.getVecParser().setImplicitParam();
    pname.assign(SofParser::implicitPname());
  }
  else {
    pname.assign(pname_a);
  }

  if (start_pos_a > sof_a.getVecSize()) {
    return (int32)0;
  }
  else if ((start_pos_a + num_elem_a) > sof_a.getVecSize()) {
    num_elem_a = sof_a.getVecSize() - start_pos_a;
  }
  
  // set length destructively
  //
  setLength(num_elem_a, false);

  if (num_elem_a > 0) {

    if (sof_a.isText()) {
      
      // read a node at a time
      //
      for (int32 i = 0; i < num_elem_a; i++) {
      
	// read the node
	//
	int32 count = i + start_pos_a;
	if (!v_d[i].readData(sof_a, pname,
			     sof_a.getVecParser().getEntry(sof_a, pname,
							   count, 1),
			     false, true)) {
	  return Error::handle(name(), L"readPartialData", SofParser::ERR,
			       __FILE__, __LINE__, Error::WARNING);
	}
      }
      sof_a.setVecCurrentElement(start_pos_a + num_elem_a);
    }

    // binary read
    //
    else {

      // do we need to seek backwards?
      //
      int32 cur_elem = sof_a.getVecCurrentElement();

      // start back at zero: BUGBUG -- we may be able to seek back
      // to the begining of the current skip table
      //
      bool8 restart = false;
      if (start_pos_a < cur_elem) {
	restart = true;
      }

      // possibly jump ahead
      //
      int32 seek_pos = -1;
      int32 skip_table_incr = sof_a.getSkipTableIncr();

      // if incrementing will take us past a skip table boundary, take
      // the current element back to the previous skip table block
      // start. for instance, if cur = 70 and start = 20. without
      // reseting this would NOT cause a jump since it is only going
      // 50 elements (and the skip table size is 100. BUT, it would be
      // faster to jump to 100 first and then just walk through 20
      // elements rather than walking through all 50, so we will set
      // cur back to 0.
      //
      if (((start_pos_a % SKIP_TABLE_SKIP) < (cur_elem % SKIP_TABLE_SKIP)) ||
	  ((start_pos_a - cur_elem) > SKIP_TABLE_SKIP)) {

	cur_elem -= (cur_elem % SKIP_TABLE_SKIP);

	if (skip_table_incr > 0) {
	  seek_pos = sof_a.getSkipTable()[skip_table_incr - 1];
	}
	else {
	  seek_pos = sof_a.getLastSkipTablePos()
	    + (SKIP_TABLE_GROUP * sizeof(int32));
	}

	if (debug_level_d >= Integral::ALL) {
	  String output(L"going back to block start: cur_elem = ");
	  output.concat(cur_elem);
	  output.concat(L", skip_table_incr = ");
	  output.concat(skip_table_incr);
	  output.concat(L", seek_pos = ");
	  output.concat(seek_pos);
	  Console::put(output);
	}
	
      }

      if (restart) {
	sof_a.setVecCurrentElement((int32)0);
	sof_a.seek(sof_a.getStartPos() + length_d.sofSize(), File::POS);

	sof_a.readSkipTable();
	sof_a.setSkipTableIncr(0);
	return readPartialData(sof_a, start_pos_a, num_elem_a, pname_a);
      }
      
      while ((start_pos_a - cur_elem) >= SKIP_TABLE_SKIP) {
	cur_elem += SKIP_TABLE_SKIP;

	seek_pos = sof_a.getSkipTable()[skip_table_incr++];
	
	if (skip_table_incr == SKIP_TABLE_GROUP) {
	  sof_a.seek(seek_pos, File::POS);
	  skip_table_incr = 0;
	  sof_a.setLastSkipTablePos(sof_a.tell());

	  if (debug_level_d >= Integral::ALL) {
	    String output(L"reading skip table from position ");
	    output.concat(sof_a.tell());
	    Console::put(output);
	  }
	  
	  if (!sof_a.readSkipTable()) {
	    return Error::handle(name(), L"readPartialData", Error::READ,
				 __FILE__, __LINE__, Error::WARNING);
	  }
	  seek_pos += SKIP_TABLE_GROUP * sizeof(int32);
	}

	if (debug_level_d >= Integral::ALL) {
	  String output(L"jumping: cur_elem = ");
	  output.concat(cur_elem);
	  output.concat(L", skip_table_incr = ");
	  output.concat(skip_table_incr);
	  output.concat(L", seek_pos = ");
	  output.concat(seek_pos);
	  Console::put(output);
	}

      }

      if (seek_pos > 0) {
	sof_a.seek(seek_pos, File::POS);
      }

      // loop past the data before the section we are looking for
      //
      for (int32 i = cur_elem; i < start_pos_a; i++) {

	if ((i > cur_elem) && ((i % SKIP_TABLE_SKIP) == 0)) {
	  return Error::handle(name(), L"readPartialData", ERR,
			       __FILE__, __LINE__);
	}

	if (debug_level_d >= Integral::ALL) {
	  String output(L"skipping over object ");
	  output.concat(i);
	  output.concat(L", position = ");
	  output.concat(sof_a.tell());
	  Console::put(output);
	}
					       
	TObject v_tmp;
	v_tmp.readData(sof_a, pname_a,
		       sof_a.getVecParser().getEntry(sof_a, pname, i , 1),
		       false, true);
      }

      cur_elem = start_pos_a;
      
      // now read the useful data
      //
      for (int32 i = 0; i < num_elem_a; i++) {

	if (((i > 0) &&
	     (((i + start_pos_a) % SKIP_TABLE_SKIP) == 0))) {

	  skip_table_incr++;

	  // if (((i + start_pos_a) %
	  //   (SKIP_TABLE_SKIP * SKIP_TABLE_GROUP)) == 0)
	  {
	    if (skip_table_incr == SKIP_TABLE_GROUP) {
	      sof_a.setLastSkipTablePos(sof_a.tell());
	      if (!sof_a.readSkipTable()) {
		return Error::handle(name(), L"readPartialData", Error::READ,
				     __FILE__, __LINE__, Error::WARNING);
	      }
	      skip_table_incr = 0;
	    }
	  }
	}
	
        if (!v_d[i].readData(sof_a, pname_a,
			     sof_a.getVecParser().getEntry(sof_a, pname, i, 1),
			     false, true)) {
          return (int32)0;
        }
      }

      sof_a.setSkipTableIncr(skip_table_incr);
      sof_a.setVecCurrentElement(cur_elem + num_elem_a);

      if(((cur_elem+num_elem_a)%(SKIP_TABLE_SKIP * SKIP_TABLE_GROUP)) == 0)
	  {
	      {
	      sof_a.setLastSkipTablePos(sof_a.tell());
	      if (!sof_a.readSkipTable()) {
		return Error::handle(name(), L"readPartialData", Error::READ,
				     __FILE__, __LINE__, Error::WARNING);
	      }
	      skip_table_incr = 0;
	    }
	  }


      
    }
  }
  
  // exit gracefully
  //
  return num_elem_a;
}

// method: writeStart
//
// arguments:
//  Sof& sof: (input) sof file object
//  const String& pname: (input) parameter name
//
// return: logical error status
//
// this method is to write the start part for writing partial data
//
template<class TObject>
bool8 Vector<TObject>::writeStart(Sof& sof_a, const String& pname_a) const {

  // set sof into partial write mode
  //
  sof_a.startPartialWrite();

  // store the length position
  //
  sof_a.setStartPos(sof_a.tell());
  sof_a.setVecSize(0);
  
  // we need an empty string for the sub-parameter
  //
  String empty_str;
   
  // if text, write a parameter name. this can't be done with
  // writeLabelPrefix because an empty list gets no brackets
  //
  if (sof_a.isText()) {
    if (pname_a.length() > 0) {
      String output;
      output.assign(pname_a);
      output.concat(SofParser::SPACE_CHAR);
      output.concat(SofParser::DEF_ASSIGNMENT_CHAR);
      output.concat(SofParser::SPACE_CHAR);
      sof_a.puts(output);
    }
    if ((int32)length_d > 0) {
      sof_a.puts(BLOCK_START_STR);
    }
  }
  
  // for binary, write a temporary length
  //
  else {
    Long len((int32)0);
    if (!len.writeData(sof_a)) {
      return Error::handle(name(), L"writeStart", Error::IO,
			   __FILE__, __LINE__);
    }
  }

  // exit gracefully
  //
  return true;
}

// method: writePartialData
//
// arguments:
//  Sof& sof: (input) the Sof file to write
//  int32 start_pos: (input) the index of the Vector to start to write
//  int32 num_elem: (input) the number of elements to write
//
// return: a bool8 value indicating status
//
template<class TObject>
int32 Vector<TObject>::writePartialData(Sof& sof_a, int32 start_pos_a,
					  int32 num_elem_a) const {
  
  // make sure we are in partial write mode
  //
  if (!sof_a.getPartialWrite()) {
    return Error::handle(name(), L"writePartialData", ERR, __FILE__, __LINE__);
  }

  // is this the first write?
  //
  bool8 is_first = (sof_a.getVecSize() == 0);
  
  // for the first write, we need to write the initial skip table
  //
  if (is_first && sof_a.isBinary() && (num_elem_a > 0)) {
    sof_a.setLastSkipTablePos(sof_a.tell());
    sof_a.setSkipTableIncr(0);
    sof_a.clearSkipTable();

    sof_a.resize(sof_a.getObjectSize() + SKIP_TABLE_GROUP * sizeof(int32));
    
    if (!sof_a.writeSkipTable()) {
      Error::handle(name(), L"writePartialData", Error::IO,
		    __FILE__, __LINE__, Error::WARNING);
    }
  }
  
  if ((num_elem_a + start_pos_a) > length_d) {
    num_elem_a = length_d - start_pos_a;
  }
  
  // loop through the part of vector to write
  //
  for (int32 i = start_pos_a; i < (start_pos_a + num_elem_a); i++) {
    
    if (sof_a.isBinary()) {
      sof_a.resize(sof_a.getObjectSize() + v_d[i].sofSize());
    }

    if (sof_a.isText()) {
      if (!is_first) {
	sof_a.decreaseIndention();
	sof_a.puts(BLOCK_DELIM_STR);
      }
      sof_a.increaseIndention();
      is_first = false;
    }

    int32 real_index = sof_a.getVecSize() + i - start_pos_a;

    if (sof_a.isBinary() && (real_index > 0) &&
	((real_index % SKIP_TABLE_SKIP) == 0)) {

      // update the current table with this position
      //
      int32 incr = sof_a.getSkipTableIncr();
      sof_a.getSkipTable()[incr] = (int32)sof_a.tell();
      sof_a.setSkipTableIncr(incr + 1);

      if (sof_a.getSkipTableIncr() == SKIP_TABLE_GROUP) {
	sof_a.setSkipTableIncr(0);

	// seek back and write the last bin pos table
	//
	sof_a.seek(sof_a.getLastSkipTablePos(), File::POS);
	
	if (!sof_a.writeSkipTable()) {
	  Error::handle(name(), L"writePartialData", Error::IO,
			__FILE__, __LINE__);
	}

	// seek back to the current one and write out a dummy skip table
	//
	sof_a.setLastSkipTablePos(sof_a.getSkipTable()[SKIP_TABLE_GROUP - 1]);
	sof_a.seek(sof_a.getLastSkipTablePos(), File::POS);
	
	sof_a.clearSkipTable();
	sof_a.resize(sof_a.getObjectSize() + SKIP_TABLE_GROUP * sizeof(int32));
	if (!sof_a.writeSkipTable()) {
	  return Error::handle(name(), L"writePartialData", Error::IO,
			       __FILE__, __LINE__);
	}
      }
    }
    
    // write this element
    //
    if (!v_d[i].writeData(sof_a, String::EMPTY)) {
      return Error::handle(name(), L"writePartialData", Error::IO,
			   __FILE__, __LINE__);
    }
  }

  sof_a.setVecSize(sof_a.getVecSize() + num_elem_a);

  // exit gracefully
  //
  return num_elem_a;
}

// method: writeTerminate
//
// arguments:
//  Sof& sof: (input) sof file object to write
//  int32 length_pos: (input) sof file position for the length
//  int32* bin_pos: (input) binary position table
//  int32 bin_pos_incr: (input) binary position table increment
//  int32 last_bin_pos: (input) where the last table was written
//  int32 acc_num: (input) total number of items written
//  const String& pname: (input) the parameter name
//
// return: a bool8 value indicating status
//
// this method concludes the partial write and returns the write-in-full mode
//
template<class TObject>
bool8 Vector<TObject>::writeTerminate(Sof& sof_a,
					const String& pname_a) const {
  
  // check if we are in write partial mode
  //
  if (!sof_a.getPartialWrite()) {
    return Error::handle(name(), L"writeTerminate",
			 ERR_WMODE, __FILE__, __LINE__);
  }

  // write the terminal string
  //
  if (sof_a.isText()) {
    
    // write the close brace
    //
    if (sof_a.getVecSize() > 0) {
      sof_a.decreaseIndention();
      sof_a.puts(BLOCK_END_STR);
    }
    
    // possibly terminate the statement
    //
    if (pname_a.length() > 0) {
      sof_a.puts(BLOCK_TERM_STR);
    }
  }
  
  // for binary mode, go back and write the actual size
  //
  else {
    sof_a.seek(sof_a.getStartPos(), File::POS);
    
    Long size(sof_a.getVecSize());

    if (debug_level_d >= Integral::ALL) {
      String output(L"writing size = ");
      output.concat(size);
      output.concat(L" to position ");
      output.concat(sof_a.tell());
      Console::put(output);
    }

    size.writeData(sof_a);
    
    // now write the last skip table, if necessary
    //
    if (sof_a.getSkipTableIncr() > 0) {
      sof_a.seek(sof_a.getLastSkipTablePos(), File::POS);
      if (!sof_a.writeSkipTable()) {
	return Error::handle(name(), L"writeTerminate",
			     Error::IO, __FILE__, __LINE__);
      }
    }
    
    sof_a.seek(0, File::POS_PLUS_END);
  }
  
  // reset the write mode
  //
  sof_a.stopPartialWrite();
  
  // exit gracefully
  //
  return true;
}

//------------------------------------------------------------------------
//
// class-specific public methods:
//  get and set methods
//
//------------------------------------------------------------------------

// method: setLength
// 
// arguments:
//  int32 length: (input) new length
//  bool8 preserve_values: (input) should we save the memory
//   
// return: a bool8 value indicating status
//
// this method sets the length, or number of valid elements
//
template<class TObject>
bool8 Vector<TObject>::setLength(int32 length_a, bool8 preserve_values_a) {

  // check arguments
  // 
  if (length_a < 0) {
    return Error::handle(name(), L"setLength", Error::ARG, __FILE__, __LINE__);
  }
  
  // if new length is greater than capacity, call setCapacity
  //
  if (length_a > capacity_d) {
    if (!setCapacity(length_a, preserve_values_a)) {
      return Error::handle(name(), L"setLength", Error::NOMEM,
			   __FILE__, __LINE__);
    }
  }

  // set new length
  // 
  length_d = length_a;
    
  // exit gracefully
  // 
  return true;
}

// method: setCapacity
// 
// arguments:
//  int32 capacity: (input) new capacity
//  bool8 preserve_values: (input) should we save the memory
//   
// return: a bool8 value indicating status
//
// this method sets the capacity, which is the maximum number of elements
// this vector can hold.
//
template<class TObject>
bool8 Vector<TObject>::setCapacity(int32 capacity_a,
				     bool8 preserve_values_a) {

  // capacity_a < 0: error
  // 
  if (capacity_a < 0) {
    return Error::handle(name(), L"setCapacity",
			 Error::ARG, __FILE__, __LINE__);
  }

  // capacity_a = capacity_d: done
  //
  else if (capacity_a == capacity_d) {
    return true;
  }
  
  // if capacity_a < length_d: error (capacity can't be less than the length)
  // 
  else if ((uint32)capacity_a < (uint32)length_d) {
    return Error::handle(name(), L"setCapacity", Error::ARG,
			 __FILE__, __LINE__);
  }
  
  // capacity_a == 0 (and length_d == 0): just delete memory
  //
  else if (capacity_a == 0) {
    
    // delete the old memory
    //
    if (v_d != (TObject*)NULL) {
      delete [] v_d;
      v_d = (TObject*)NULL;
    }
  }
  
  // capacity_a >= length_d: we will need to allocate memory and/or
  // transfer data.
  //
  else {

    // allocate a new chunk of memory
    //
    TObject* new_mem = new TObject[capacity_a];
    if (new_mem == (TObject*)NULL) {
      return Error::handle(name(), L"setCapacity", Error::NOMEM,
			   __FILE__, __LINE__);
    }
    
    // if there are valid elements and we need to preserve them
    //
    if (((uint32)length_d > 0) && preserve_values_a) {
      for (int32 i = 0; i < (int32)length_d; i++) {
	new_mem[i].assign(v_d[i]);
      }
    }
    
    // delete the old memory
    //
    if (v_d != (TObject*)NULL) {
      delete [] v_d;
      v_d = (TObject*)NULL;
    }
    
    // assign the pointer to the new memory
    //
    v_d = new_mem;
  }
  
  // set the new capacity
  //
  capacity_d = capacity_a;

  // exit gracefully
  //
  return true;
}

// method: getVectorSize
// 
// arguments:
//  int32 offset: (input) the beginning point for vector
//  Sof& sof: (input) sof file
//   
// return: the vector size
//
// this method get the length of vector in a file
//
template<class TObject>
int32 Vector<TObject>::getVectorSize(int32 offset_a, Sof& sof_a) {

  if (sof_a.isText()) {
    return Error::handle(name(), L"getVectorSize", Error::IO,
                         __FILE__, __LINE__);
  }

  // for binary mode, get the actual size
  //

  // get current position
  //
  int32 cur_file_pos = sof_a.tell();
  
  // seek the data needed position
  //
  sof_a.seek(offset_a, File::POS);

  // get the length of the vector
  //
  Long len;
  len.readData(sof_a, String::EMPTY);

  // resume the file position
  //
  sof_a.seek(cur_file_pos, File::POS);
  
  if (debug_level_d >= Integral::ALL) {
    String output(L"readinging size = ");
    output.concat(len);
    output.concat(L" from position ");
    output.concat(sof_a.tell());
    Console::put(output);
  }
  
  // exit gracefully
  // 
  return len;
}



// method: getVectorSize
// 
// arguments:
//  Sof& sof: (input) sof file object
//  int32 tag: (input) object tag
//  const String& pname: (input) parameter name
//  int32 size: (input) size of the object
//  bool8 param: (input) is the parameter specified?
//  bool8 nested: (input) is this nested?
//
// return: the vector size
//
// this method get the length of vector in a file. It assumes that the
// Sof file is already positioned correctly.
//
template<class TObject>
int32 Vector<TObject>::getVectorSize(Sof& sof_a, int32 tag_a,
				    const String& name_a,
				    const String& pname_a,
				    int32 size_a,
				    bool8 param_a,
				    bool8 nested_a) {

  // get the instance of the object from the Sof file
  //
  if (!sof_a.find(name_a, tag_a)) {
    return false;
  }

  // local variables
  //
  SofParser parser;
  String pname;
  
  // if param is false, this means implicit parameter
  //
  if (!param_a) {
    if (!parser.setImplicitParam()) {
      return Error::handle(name(), L"getVectorSize", Error::READ,
			   __FILE__, __LINE__, Error::WARNING);
    }
    if (!pname.assign(parser.implicitPname())) {
      return Error::handle(name(), L"getVectorSize", Error::READ,
			   __FILE__, __LINE__, Error::WARNING);
    }      
  }
  else {
    pname.assign(pname_a);
  }
  
  // are we nested?
  //
  if (nested_a) {
    parser.setNest();
  }
  
  // load the parse
  //
  parser.load(sof_a, size_a);
  
  Long new_size((int32)0);
  
  // read the length first: this differs for text or binary
  //
  if (sof_a.isText()) {
    new_size = parser.countTokens(DEF_PARAM);
    new_size.debug(L"new_size");    
  }

  // for binary mode, get the actual size
  //
  else {
    if (!new_size.readData(sof_a, pname)) {
      return Error::handle(name(), L"getVectorSize", Error::READ,
			   __FILE__, __LINE__, Error::WARNING);
    }
  }

  // exit gracefully
  // 
  return (int32)new_size;
}



//---------------------------------------------------------------------------
//
// class-specific public methods:
//  item manipulation methods
//
//---------------------------------------------------------------------------

// method: move
//
// arguments:
//  const Vector& v: (input) input Vector
//  int32 n: (input) number of elements to be moved
//  int32 i_offset: (input) index of first element in input Vector
//  int32 o_offset: (input) index of first element in output Vector
//
// return: logical error status
//
// note that this method now does appropriate boundary checking/processing.
//
template<class TObject>
bool8 Vector<TObject>::move(const Vector& v_a, int32 n_a, int32 i_offset_a,
			      int32 o_offset_a) {
 
  // declare local variables
  // 
  int32 num_to_move = n_a;  			// counter for moving
  int32 ind_in = i_offset_a; 		        // start index in input
  int32 ind_in_end = ind_in + num_to_move;	// end index in input
  int32 ind_out = o_offset_a; 		        // start index in output
  int32 ind_out_end = ind_out + num_to_move;     // end index in output
  int32 last_index = (int32)v_a.length_d;		// last index in input
  
  // check output vector
  // 
  if ((ind_in < 0) || (ind_out < 0) || (ind_out > (int32)length_d)) {
    return Error::handle(name(), L"move", Error::ARG, __FILE__, __LINE__);
  }
  else if ((ind_out_end > (int32)length_d)) {
    
    // resize this vector
    //
    setLength(ind_out_end);
  }
   
  // subtract amount to be zeroed at the end
  // 
  if (ind_in_end > last_index) {
    num_to_move -= ind_in_end - last_index;
  }
  
  // move the data
  // 
  while (num_to_move > 0) {
    v_d[ind_out++].assign(v_a.v_d[ind_in++]);
    num_to_move--;
  }

  // reset the values at end if necessary
  // 
  while (ind_out < ind_out_end) {
    v_d[ind_out++].clear();
  }
  
  // exit gracefully
  // 
  return true;
}

// method: shift
//
// arguments:
//  const Vector& v: (input) source vector
//  int32 delta: (input) shift factor
//
// return: a bool8 value indicating status
//
// this methods shifts the position of the elements of the vector
// if delta_a > 0: x[i] = x[i-delta], if delta_a < 0: x[i] = x[i+delta]
//
template<class TObject>
bool8 Vector<TObject>::shift(const Vector& v_a, int32 delta_a) {
  
  // create new space
  // 
  if (!setLength((int32)v_a.length_d, false)) {
    return false;
  }

  // clear the space
  //
  clear(Integral::RETAIN);
  
  // shift the data forward
  // 
  if (delta_a > 0) {
    int32 i = (int32)length_d - 1;
    int32 j = i - delta_a;
    int32 i_end = delta_a - 1;
    while (i > i_end) {
      v_d[i--].assign(v_a.v_d[j--]);
    }
  }
  
  // shift the data backward
  // 
  else {
    int32 i = 0;
    int32 j = i - delta_a;
    int32 i_end = (int32)length_d + delta_a;
    while (i < i_end) {
      v_d[i++].assign(v_a.v_d[j++]);
    }
  }
 
  // exit gracefully
  // 
  return true;
}

// method: shift
//
// arguments:
//  int32 delta: (input) shift factor
//
// return: a bool8 value indicating status
//
// shift the specified amount
//       delta_a > 0: x[i] = x[i-delta]
//	 delta_a < 0: x[i] = x[i+delta]
//
template<class TObject>
bool8 Vector<TObject>::shift(int32 delta_a) {
 
  // shift the data forward
  // 
  if (delta_a > 0) {
    int32 i = (int32)length_d - 1;
    int32 j = i - delta_a;
    int32 i_end = delta_a - 1;
    while (i > i_end) {
      v_d[i--].assign(v_d[j--]);
    }

    while (i >= 0) {
      v_d[i--].clear();
    }
  }
  
  // shift the data backward
  // 
  else {
    int32 i = 0;
    int32 j = i - delta_a;
    int32 i_end = (int32)length_d + delta_a;
    while (i < i_end) {
      v_d[i++].assign(v_d[j++]);
    }

    while (i < length_d) {
      v_d[i++].clear();
    }
  }
   
  // exit gracefully
  // 
  return true;
}

// method: concat
//
// arguments:
//  const Vector& v: (input) Vector to be concatenated 
//
// return: a bool8 value indicating status
//
// this method concatenates v_a to the end of "this".
//
template<class TObject>
bool8 Vector<TObject>::concat(const Vector& v_a) {

  // declare local variables
  // 
  int32 output_index = (int32)length_d;
  int32 last_index = (int32)v_a.length_d;
  int32 index;
  
  // resize (we must preserve elements)
  // 
  if (!setLength(length_d + v_a.length_d)) {
    return Error::handle(name(), L"concat", Error::NOMEM, __FILE__, __LINE__);
  }
  
  // copy the data
  // 
  for (index = 0; index < last_index; index++) {
    v_d[output_index++].assign(v_a.v_d[index]);
  }
  
  // exit gracefully
  // 
  return true;
}

// method: concat
//
// arguments:
//  const Vector& v1: (input) operand
//  const Vector& v2: (input) operand
//
// return: a bool8 value indicating status
//
// concatenates v2 to v1 and stored the result in "this".
//
template<class TObject>
bool8 Vector<TObject>::concat(const Vector& v1_a, const Vector& v2_a) {
 
  // make sure the length is great enough for both
  //
  if (!setLength(v1_a.length_d + v2_a.length_d, false)) {
    return Error::handle(name(), L"concat", Error::NOMEM, __FILE__, __LINE__);
  }
  setLength(0);

  // assign the first vector
  //
  if (!assign(v1_a)) {
    return Error::handle(name(), L"concat", ERR, __FILE__, __LINE__);
  }

  // call the master function to concatenate
  // 
  return concat(v2_a);
}

// method: concat
//
// arguments:
//  const TObject& obj: (input) object to be concatenated 
//
// return: a bool8 value indicating status
//
// this method concatenates obj to the end of "this".
//
template<class TObject>
bool8 Vector<TObject>::concat(const TObject& obj_a) {

  // declare local variables
  // 
  int32 output_index = (int32)length_d;
  
  // resize (we must preserve elements)
  // 
  if (!setLength((int32)length_d + 1)) {
    return Error::handle(name(), L"concat", Error::NOMEM, __FILE__, __LINE__);
  }
  
  // copy the data
  // 
  v_d[output_index].assign(obj_a);
  
  // exit gracefully
  // 
  return true;
}

// method: deleteRange
//
// arguments:
//  const Vector& arg: (input) input vector
//  int32 offset: (input) first element to delete
//  int32 num_elem: (input) number of elements to delete
//
// return: a bool8 value indicating status
//
template<class TObject>
bool8 Vector<TObject>::deleteRange(const Vector& arg_a, int32 offset_a,
				     int32 num_elem_a) {

  // make sure this isn't the same object
  //
  if (&arg_a == this) {
    return deleteRange(offset_a, num_elem_a);
  }
  
  // local variables
  //
  int32 len_old = arg_a.length();
  int32 len_new = len_old - num_elem_a;

  // check arguments
  //
  if (num_elem_a == 0) {
    return assign(arg_a);
  }
  else if (((offset_a < 0) || (offset_a >= len_old)) ||
	   ((num_elem_a < 0) ||
	    ((offset_a + num_elem_a) > len_old))) {
    return Error::handle(name(), L"deleteRange", Error::ARG,
			 __FILE__, __LINE__);
  }

  setLength(len_new);
  
  // copy the first chunk
  //
  for (int32 i = 0; i < offset_a; i++) {
    v_d[i].assign(arg_a.v_d[i]);
  }

  // copy the second chunk
  //
  for (int32 i = offset_a; i < len_new; i++) {
    v_d[i].assign(v_d[i + num_elem_a]);
  }
  
  // exit gracefully
  //
  return true;
}

// method: deleteRange
//
// arguments:
//  int32 offset: (input) first element to delete
//  int32 num_elem: (input) number of elements to delete
//
// return: a bool8 value indicating status
//
template<class TObject>
bool8 Vector<TObject>::deleteRange(int32 offset_a, int32 num_elem_a) {

  // local variables
  //
  int32 len_old = length();
  int32 len_new = len_old - num_elem_a;

  // check arguments
  //
  if (num_elem_a == 0) {
    return true;
  }
  else if (((offset_a < 0) || (offset_a >= len_old)) ||
	   ((num_elem_a < 0) ||
	    ((offset_a + num_elem_a) > len_old))) {
    return Error::handle(name(), L"deleteRange", Error::ARG,
			 __FILE__, __LINE__);
  }

  // copy the second chunk
  //
  for (int32 i = offset_a; i < len_new; i++) {
    v_d[i].assign(v_d[i + num_elem_a]);
  }
  
  // resize
  //
  return setLength(len_new);
}

// method: setRange
//
// arguments:
//  int32 offset: (input) first element to delete
//  int32 num_elem: (input) number of elements to delete
//  const TObject& value: (input) value to set
//
// return: a bool8 value indicating status
//
template<class TObject>
bool8 Vector<TObject>::setRange(int32 offset_a, int32 num_elem_a,
				  const TObject& value_a) {

  // local variables
  //
  int32 len = length();

  // check arguments
  //
  if (num_elem_a == 0) {
    return true;
  }
  else if (((offset_a < 0) || (offset_a >= len)) ||
	   ((num_elem_a < 0) ||
	    ((offset_a + num_elem_a) > len))) {
    return Error::handle(name(), L"setRange", Error::ARG,
			 __FILE__, __LINE__);
  }

  // assign each element
  //
  for (int32 i = offset_a; i < (offset_a + num_elem_a); i++) {
    if (!v_d[i].assign(value_a)) {
      return false;
    }
  }

  // exit gracefully
  //
  return true;
}
  
// method: sort
//
// arguments:
//  Integral::ORDER sort_order: (input) the order to sort
//  SORT_ALGO sort_algo: (input) the algorithm to use
//
// return: a bool8 value indicating status
//
// this method sorts the elements in the vector according to the given order
//
template<class TObject>
bool8 Vector<TObject>::sort(Integral::ORDER sort_order_a,
			      SORT_ALGO sort_algo_a) {

  // branches on algorithms
  //
  if (sort_algo_a == RAND_QUICK) {
    return this->randQuickSort(sort_order_a);
  }
  else if (sort_algo_a == INSERTION) {
    return this->insertionSort(sort_order_a);
  }
  else {
    return Error::handle(name(), L"sort", Error::NOT_IMPLEM,
                         __FILE__, __LINE__, Error::WARNING);
  }
}

//---------------------------------------------------------------------------
//
// class-specific public methods:
//  item location and containment methods
//
//---------------------------------------------------------------------------

// method: first
//
// arguments:
//  const TObject& value: (input) value to be found
//  int32 start_pos: (input) position to start searching from
//
// return: a int32 value of the element index
//
// this method finds the index of the first element after the start_pos
// (count from 0) in "this" equal to value_a, if the value is not found,
// NO_POS is returned.
//
template<class TObject>
int32 Vector<TObject>::first(const TObject& value_a, int32 start_pos_a) const {
  
  int32 last_index = (int32)length_d;

  // make sure the range of start_pos is between [0, length_d-1]
  //
  if ((start_pos_a == Integral::NO_POS) || (start_pos_a >= length_d)) {
    start_pos_a = 0;                
  }

  // check all values
  //
  for (int32 index = start_pos_a; index < last_index; index++) {
    if (v_d[index].eq(value_a)) {
      return index;         
    }
  }
  
  // exit gracefully - no match found
  // 
  return Integral::NO_POS;
}

// method: last
//
// arguments:
//  const TObject& value: (input) value to be found
//  int32 end_pos: (input) position to start searching back from
//
// return: a int32 value of the element index
//
// this method finds the index of the first element after the start_pos
// in "this" equal to value_a, if the value is not found, NO_POS is
// returned. 
//
template<class TObject>
int32 Vector<TObject>::last(const TObject& value_a, int32 end_pos_a) const {
  
  // make sure the range of end_pos is between [0, length_d-1]
  //
  if (end_pos_a == Integral::NO_POS || end_pos_a >= length_d) {
    end_pos_a = (int32)length_d - 1;        
  }
  
  // check all values
  //
  for (int32 index = end_pos_a; index >= 0; index--) {
    if (v_d[index].eq(value_a)) {
      return index;
    }
  }
  
  // exit gracefully - no match found
  // 
  return Integral::NO_POS;
}

//------------------------------------------------------------------------
//
// class-specific public methods:
//  apply methods
//
//------------------------------------------------------------------------

// method: apply
//
// arguments:
//  bool8 (TObject::*method)(): (input) the method to apply to each element
//          this method must be a member of the TObject class
//
// return: a bool8 value indicating status
//
// this method applies the input method to each element in the vector
//
template<class TObject>
bool8 Vector<TObject>::apply(bool8 (TObject::*method_a)()) {

  // loop over each element in the vector and apply the method to it
  //
  for (int32 i = 0; i < length_d; i++) {
    
    // apply the method to all non-null elements
    //
    (v_d[i].*method_a)();
  }

  // exit gracefully
  //
  return true;
}

//---------------------------------------------------------------------------
//
// private methods
//
//---------------------------------------------------------------------------

// method: randQuickSort
//
// arguments:
//  Integral::ORDER sort_order: (input) ascending or descending
//
// return: a bool8 value indicating status
//
// this method sorts the input vector elements in the specified order and
// stores the result in this Vector
//
// a "randomized version of quicksort" using random pivot taken from:
//
//  T. Cormen, C. Leiserson, R. Rivest, Introduction to Algorithms,
//  MIT Press, Boston, Massachusetts, USA, pp. 161-162, 1998.
//
//  this reference method was modified to eliminate recursion.
//
template<class TObject>
bool8 Vector<TObject>::randQuickSort(Integral::ORDER sort_order_a) {

  // declare the temporary variables
  //
  int32 i, j;
  TObject x;
  
  // declare two stacks
  //
  Stack<Long> p_stack;
  Stack<Long> r_stack;

  // store the partition indices on the stacks
  //
  Long p = 0;
  p_stack.push(&p);
  
  Long r = length() - 1;
  r_stack.push(&r);

  // repeatedly sort the partition region
  //
  while ((!p_stack.isEmpty()) && (!r_stack.isEmpty())) {
    
    // use the p & r values at the top of the stacks, this is similar
    // to the top of the new function call
    //
    p_stack.pop(&p);
    r_stack.pop(&r);
    
    // this is the partition method
    //
    if (p < r) {

      // select a number at random between p and r
      //
      Long rand_pivot;
      rand_pivot.rand(p, r);

      // error if the value does not lie between p and r
      //
      if ((rand_pivot < p) || (rand_pivot > r)) {
	return Error::handle(name(), L"randQuickSort", ERR,
			     __FILE__, __LINE__);
      }

      x.assign(v_d[rand_pivot]); // pivot element

      // starting positions for sort
      //
      i = (int32)p - 1;
      j = (int32)r + 1;
      
      do {
	
	// decrement j, increment i, until
	//   v_d[i] >= x >= v_d[j] for ascending
	//   v_d[i] <= x <= v_d[j] for descending
	//
	if (sort_order_a == Integral::ASCENDING) {
	  do {
	    j--;
	  } while (v_d[j].gt(x));
	  
	  do {
	    i++;
	  } while (v_d[i].lt(x));
	}
	else { 
	  do {
	    j--;
	  } while (v_d[j].lt(x));
	  
	  do {
	    i++;
	  } while (v_d[i].gt(x));
	}

        if (i < j) {

	  // exchange v_d[i] and v_d[j]
	  //
	  TObject temp(v_d[j]);
          v_d[j].assign(v_d[i]);
          v_d[i].assign(temp);
        }
      } while (i < j);

      // now add p & r values to the vectors, similar to making new
      // function calls but with much less overhead
      //
      // randQuicksort2(A, p, j);
      //
      p_stack.push(&p);
      Long x = j; 
      r_stack.push(&x) ;
      
      // randQuicksort2(A, j+1, r);
      //
      Long sum = j + 1;
      p_stack.push(&sum);
      r_stack.push(&r);
      
    }
    
  }
  
  // exit gracefully
  //
  return true;  
  
}

// method: insertionSort
//
// arguments:
//  Integral::ORDER sort_order: (input) ascending or descending
//
//  return: a bool8 value indicating status
//
// this method sorts the vector using the insertion sort algorithm.
// a good reference for this algorithm is:
//
//  T. Cormen, C. Leiserson, R. Rivest, Introduction to Algorithms,
//  MIT Press, Boston, Massachusetts, USA, pp. 3-4, 1998.
//
// this implementation follows this reference closely.
//
template<class TObject>
bool8 Vector<TObject>::insertionSort(Integral::ORDER sort_order_a) {
  
  // if empty or only 1 item, no need to sort
  //
  if ((int32)length_d == 0 || (int32)length_d == 1) {
    return true;
  }

  // declare the sort order to be true if the order is ascending and
  // false if the order is descending - this will help us in deciding
  // that whether we want to go to right or left  
  //
  bool8 order = true;
  if (sort_order_a == Integral::DESCENDING) {
    order = false;
  }
  
  // declare local variables
  //
  TObject insert_item;
  bool8 cont = true;
  
  // insert starting from the second item
  //
  for (int32 j = 1; j < (int32)length_d; j++) {

    // insert the item into the sorted items [0, j-1]
    //
    for (int32 i = 0; ( i < j  ) && cont; i++) {

      // if v_d[j] should reside to the left of v_d[i], stop
      //
      if (v_d[j].gt(v_d[i]) ^ order) {

	cont = false;

	insert_item.assign(v_d[j]);
			  
	// insert v_d[j] in front of v_d[i], we need to move
	// v_d[i] to v_d[j-1] forward
	//
	for (int32 k = j - 1; k >= i; k--) {
	  v_d[k + 1].assign(v_d[k]);
	}
	v_d[i].assign(insert_item);
      }
      
      // continue to insert the next element
      //
      cont = true;
    }
  }

  // exit gracefully
  //
  return true;
}
  
// method: clearBinPos
//
// arguments:
//  int32* bin_pos: (input) binary position table
//
// return: logical error status
//
// initialize the binary position table to all -1 values
//
template<class TObject>
bool8 Vector<TObject>::clearBinPos(int32* bin_pos_a) const {

  // clear the table
  //
  for (int32 i = 0; i < SKIP_TABLE_GROUP; i++) {
    bin_pos_a[i] = -1;
  }

  // exit gracefully
  //
  return true;
}
 
// end of include file
//
#endif
