// file: $isip/class/dstr/Wrapper/Wrapper.h
// version: $Id: Wrapper.h 10636 2007-01-26 22:18:09Z tm334 $
//

// make sure definitions are only made once
//
#ifndef ISIP_WRAPPER
#define ISIP_WRAPPER

// isip include files
//
#ifndef ISIP_STRING
#include <String.h>
#endif

// forward class definitions
//
template<class TObject> class WrapperDiagnose;

// Wrapper: a class to wrap around any class that will provide a
// minimal implementation of the IFC required public methods. through
// this class any object can be placed on an IFC data structure.
//
template<class TObject>
class Wrapper : public TObject {
  
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
  
  static const int32 ERR = 42100;
  static const int32 ERR_NOTDEF = 42101;
  
  //---------------------------------------------------------------------------
  //
  // protected data
  //
  //---------------------------------------------------------------------------
protected:

  // note that there is no non-static data, this class must be as
  // close to its parent class as possible.
  //
  
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
  //  defined in the WrapperDiagnose.h in order to avoid issues
  //  related to preprocessing of the diagnose code.
  //
  static const String& name();
  
  // method: setDebug
  //
  static bool8 setDebug(Integral::DEBUG debug_level) {
    debug_level_d = debug_level;
    return true;
  }

  // method: debug
  //
  bool8 debug(const unichar* message) const {
    return true;
  }
    
  // method: destructor
  //
  ~Wrapper() {}

  // method: default constructor
  //
  Wrapper() {}

  // method: copy constructor
  //
  Wrapper(const Wrapper& arg) {
    (*(TObject*)this) = (TObject)arg;
  }
  
  // method: assign
  //
  bool8 assign(const Wrapper<TObject>& arg) {
    (*(TObject*)this) = (TObject)arg;
    return true;
  }

  // method: operator=
  //
  Wrapper<TObject>& operator=(const Wrapper<TObject>& arg) {
    (*(TObject*)this) = (TObject)arg;
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

  // method: sofSize
  //
  int32 sofSize() const {
    return 0;
  }

  // method: read
  //
  bool8 read(Sof& sof, int32 tag, const String& name) {
    return Error::handle(this->name(), L"read", ERR_NOTDEF, __FILE__, __LINE__);
  }

  // method: write
  //
  bool8 write(Sof& sof, int32 tag, const String& name) const {
    return Error::handle(this->name(), L"write", ERR_NOTDEF, __FILE__, __LINE__);
  }


  // method: readData
  //
  bool8 readData(Sof& sof, const String& pname = DEF_PARAM, int32 size =
                   SofParser::FULL_OBJECT, bool8 param = true,
                   bool8 nested = false) {
    return Error::handle(name(), L"readData", ERR_NOTDEF, __FILE__, __LINE__);
  }

  // method: writeData
  //
  bool8 writeData(Sof& sof, const String& pname = DEF_PARAM) const {
    return Error::handle(name(), L"writeData", ERR_NOTDEF, __FILE__, __LINE__);
  }
  
  // method: eq
  //
  bool8 eq(const Wrapper<TObject>& arg) const {
    return Error::handle(name(), L"eq", Error::ARG, __FILE__, __LINE__);
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
    return Error::handle(name(), L"clear", ERR_NOTDEF, __FILE__, __LINE__);
  }
  
  //---------------------------------------------------------------------------
  //
  // class-specific public methods:
  //  extensions to required methods
  //
  //---------------------------------------------------------------------------

  // method: constructor
  //
  Wrapper(const TObject& arg) {
    (*(TObject*)this) = arg;
  }

  // method: assign
  //
  bool8 assign(const TObject& arg) {
    (*(TObject*)this) = arg;
    return true;
  }

  // method: operator=
  //
  Wrapper<TObject>& operator=(const TObject& arg) {
    (*(TObject*)this) = arg;
    return *this;
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
  friend class WrapperDiagnose;  
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
const String Wrapper<TObject>::CLASS_NAME(L"Wrapper");

// constants: required constants for i/o methods
//
template <class TObject>
const String Wrapper<TObject>::DEF_PARAM(L"item");

// static instantiations: debug level and memory manager
//
template <class TObject>
Integral::DEBUG Wrapper<TObject>::debug_level_d = Integral::NONE;

template <class TObject>
MemoryManager Wrapper<TObject>::mgr_d(sizeof(Wrapper<TObject>), CLASS_NAME);

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
const String& Wrapper<TObject>::name() {

  // create the static name string for this class and return it
  //
  static String cname(CLASS_NAME);
  cname.clear();
  cname.concat(CLASS_NAME);

  // return the name
  //
  return cname;
}

// end of include file
//
#endif

