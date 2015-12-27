// file: $isip/class/dstr/Pair/Pair.h
// version: $Id: Pair.h 5965 2000-12-17 23:28:40Z picone $
//

// make sure definitions are only made once
//
#ifndef ISIP_PAIR
#define ISIP_PAIR

// isip include files
//
#ifndef ISIP_STRING
#include <String.h>
#endif

#ifndef ISIP_CHAR
#include <Char.h>
#endif

#ifndef ISIP_VECTOR
#include <Vector.h>
#endif

#ifndef ISIP_CONSOLE	
#include <Console.h>
#endif

// Pair: a generic pair template class. this is simply a container class
// that groups together two arbitrary objects.
//
template<class T1, class T2>
class Pair {

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
  static const String BLOCK_START_STR;
  static const String BLOCK_DELIM_STR;
  static const String BLOCK_END_STR;
  static const String BLOCK_TERM_STR;
  
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
  
  static const int32 ERR = 41800;
  
  //---------------------------------------------------------------------------
  //
  // protected data
  //
  //---------------------------------------------------------------------------
protected:

  // define an object of each type
  //
  T1 obj1_d;
  T2 obj2_d;

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
  //  defined in the PairDiagnose.h in order to avoid issues
  //  related to preprocessing of the diagnose code.
  //
  static const String& name();
  
  // method: setDebug
  //
  static bool8 setDebug(Integral::DEBUG debug_level) {
    T1::setDebug(debug_level);
    T2::setDebug(debug_level);
    return true;
  }

  // other debug methods
  //
  bool8 debug(const unichar* message) const;

  // method: destructor
  //
  ~Pair() {}

  // method: default constructor
  //
  Pair() {}

  // method: copy constructor
  //
  Pair(const Pair<T1,T2>& arg) {
    assign(arg);
  }
  
  // method: assign
  //
  bool8 assign(const Pair<T1,T2>& arg) {
    return (obj1_d.assign(arg.obj1_d) && obj2_d.assign(arg.obj2_d));
  }

  // method: operator=
  //
  Pair<T1,T2>& operator=(const Pair<T1,T2>& arg) {
    assign(arg);
    return *this;
  }

  // method: eq
  //  determines if the contents of the pair are equivalent.
  //  this method calls the eq(TObject&) method for the items
  //  contained in the respective nodes to determine equivalence.
  //  only classes with an eq() method are available for use with
  //  this Pair object
  //
  bool8 eq(const Pair<T1,T2>& arg) const {
    return (obj1_d.eq(arg.obj1_d) && obj2_d.eq(arg.obj2_d));
  }
  
  // method: sofSize
  //
  int32 sofSize() const {
    return obj1_d.sofSize() + obj2_d.sofSize();
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

  // other i/o methods
  //
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

  // method: clear
  //   
  bool8 clear(Integral::CMODE cmode = Integral::DEF_CMODE) {
    return (obj1_d.clear(cmode) && obj2_d.clear(cmode));
  }
  
  //---------------------------------------------------------------------------
  //
  // class-specific public methods:
  //  extensions to required methods
  //
  //---------------------------------------------------------------------------

  // method: constructor
  //
  Pair(const T1& obj1, const T2& obj2) {
    assign(obj1, obj2);
  }

  // method: assign
  //
  bool8 assign(const T1& obj1, const T2& obj2) {
    return (obj1_d.assign(obj1) && obj2_d.assign(obj2));
  }

  //---------------------------------------------------------------------------
  //
  // class-specific public methods:
  //  item access methods
  //
  //---------------------------------------------------------------------------

  // method: first
  //
  T1& first() {
    return obj1_d;
  }

  // method: first
  //
  const T1& first() const {
    return obj1_d;
  }

  // method: second
  //
  T2& second() {
    return obj2_d;
  }

  // method: second
  //
  const T2& second() const {
    return obj2_d;
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
template <class T1, class T2>
const String Pair<T1, T2>::CLASS_NAME(L"Pair");

// constants: required constants for i/o methods
//
template <class T1, class T2>
const String Pair<T1, T2>::DEF_PARAM(L"pair");

template <class T1, class T2>
const String Pair<T1, T2>::BLOCK_START_STR(L"{");

template <class T1, class T2>
const String Pair<T1, T2>::BLOCK_DELIM_STR(L"}, {");

template <class T1, class T2>
const String Pair<T1, T2>::BLOCK_END_STR(L"}");

template <class T1, class T2>
const String Pair<T1, T2>::BLOCK_TERM_STR(L";\n");

// static instantiations: the memory manager
//
template <class T1, class T2>
MemoryManager Pair<T1, T2>::mgr_d(sizeof(Pair<T1, T2>), CLASS_NAME);

// below are all the methods for the Pair template class
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
template<class T1, class T2>
const String& Pair<T1,T2>::name() {

  // create the static name string for this class and return it
  //
  static String cname(CLASS_NAME);
  cname.clear();
  cname.concat(CLASS_NAME);
  cname.concat(L"<");
  cname.concat(T1::name());
  cname.concat(L",");
  cname.concat(T2::name());
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
template<class T1, class T2>
bool8 Pair<T1,T2>::debug(const unichar* message_a) const {

  // local variables
  //
  String output;

  // output the user's message
  //
  output.debugStr(name(), message_a, L"");
  Console::put(output);
  
  // increment the indention level in the console
  //
  Console::increaseIndention();
  
  // call the debug method of the item
  //
  obj1_d.debug(L"first");
  obj2_d.debug(L"second");
  
  // decrement the indention level in the console
  //
  Console::decreaseIndention();
  
  // exit gracefully
  // 
  return true;
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
template<class T1, class T2>
bool8 Pair<T1,T2>::read(Sof& sof_a, int32 tag_a, const String& name_a) {
  
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
template<class T1, class T2>
bool8 Pair<T1,T2>::write(Sof& sof_a, int32 tag_a, const String& name_a)
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
template<class T1, class T2>
bool8 Pair<T1,T2>::readData(Sof& sof_a, const String& pname_a, int32 size_a,
				bool8 param_a, bool8 nested_a) {
  
  // declare local variables
  //
  SofParser parser;
  String pname;
  
  // if param is false, this means implicit parameter
  //
  if (!param_a) {
    parser.setImplicitParam();
    pname.assign(parser.implicitPname());
  }
  else {
    pname.assign(pname_a);
  }
  
  // configure the parser to read a nested object
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
  
  // read the length first: this differs for text or binary
  //
  if (sof_a.isText()) {
    int32 new_size = parser.countTokens(pname);
    if (new_size != 2) {
      return Error::handle(name(), L"readData", Error::READ, __FILE__,
			   __LINE__, Error::WARNING);
    }
  }

  // read both objects
  //
  if (!obj1_d.readData(sof_a, pname, parser.getEntry(sof_a, pname, 0, 1),
		       false, true)) {
    return Error::handle(name(), L"readData", Error::READ, __FILE__,
			 __LINE__, Error::WARNING);
  }

  if (!obj2_d.readData(sof_a, pname, parser.getEntry(sof_a, pname, 1, 1),
		       false, true)) {
    return Error::handle(name(), L"readData", Error::READ, __FILE__,
			 __LINE__, Error::WARNING);
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
template<class T1, class T2>
bool8 Pair<T1,T2>::writeData(Sof& sof_a, const String& pname_a) const {

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

    sof_a.puts(BLOCK_START_STR);
  }

  // write the first element
  //
  if (!obj1_d.writeData(sof_a, String::getEmptyString())) {
    return Error::handle(name(), L"writeData",Error::IO, __FILE__, __LINE__);
  }

  if (sof_a.isText()) {
    sof_a.puts(BLOCK_DELIM_STR);
  }
  
  // write the second element
  //
  if (!obj2_d.writeData(sof_a, String::getEmptyString())) {
    return Error::handle(name(), L"writeData",Error::IO, __FILE__, __LINE__);
  }

  if (sof_a.isText()) {
    
    sof_a.puts(BLOCK_END_STR);
    
    // possibly terminate the statement
    //
    if (pname_a.length() > 0) {
      sof_a.puts(BLOCK_TERM_STR);
    }
  }

  // exit gracefully
  //
  return true;
}

// end of include file
//
#endif
