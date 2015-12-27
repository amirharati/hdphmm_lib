// file: $isip/class/shell/DebugLevel/DebugLevel.h
// version: $Id: DebugLevel.h 9210 2003-06-15 14:48:40Z picone $
//

// make sure definitions are only made once
//
#ifndef ISIP_DEBUG_LEVEL
#define ISIP_DEBUG_LEVEL

// isip include files
//
#ifndef ISIP_LONG
#include <Long.h>
#endif

#ifndef ISIP_NAME_MAP
#include <NameMap.h>
#endif

// DebugLevel: an integer valued object that encapsulates our
// predefined debug levels defined in Integral.h
//
class DebugLevel : public Long {

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
  // other important constants
  //
  //----------------------------------------
  
  // define the names for the enumerated values
  //
  static const NameMap LEVEL_MAP;

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

  // define the default value(s) of the class data
  //
  
  // default arguments to methods
  //
  
  //----------------------------------------
  //
  // error codes
  //
  //----------------------------------------  

  static const int32 ERR = 45500;

  //---------------------------------------------------------------------------
  //
  // protected data
  //
  //---------------------------------------------------------------------------
protected:

  // static memory manager
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
  static const String& name() {
    return CLASS_NAME;
  }

  // other static methods
  //
  static bool8 diagnose(Integral::DEBUG debug_level);

  // debug methods:
  //  the setDebug method is inherited from the Long class
  //
  bool8 debug(const unichar* message) const;
  
  // method: destructor
  //
  ~DebugLevel() {}

  // method: default constructor
  //
  DebugLevel(Integral::DEBUG arg = Integral::DEF_DEBUG):
    Long((int32)arg) {}

  // method: copy constructor
  //
  DebugLevel(const DebugLevel& arg): Long((int32)arg) {}
  
  // method: constructor (from a string)
  //
  DebugLevel(const String& arg) {
    assign(arg);
  }
  
  // method: assign
  //  these methods are inherited from the Long class
  //
  
  // method: operator=
  //
  DebugLevel& operator= (const DebugLevel& arg) {
    Long::assign(arg);
    return *this;
  }
  
  // i/o methods:
  //  the sofSize method is inherited from the Long class
  //
  bool8 read(Sof& sof, int32 tag, const String& name = CLASS_NAME); 
  bool8 write(Sof& sof, int32 tag, const String& name = CLASS_NAME) const;
  
  bool8 readData(Sof& sof, const String& pname = DEF_PARAM,
		   int32 size = SofParser::FULL_OBJECT, bool8 param = true,
		   bool8 nested = false);
 
  bool8 writeData(Sof& sof, const String& pname = DEF_PARAM) const;
 
  // equality methods:
  //  these are inherited from the scalar class Long
  //
  
  // memory management methods:
  //  the clear method is inherited from the Long class
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
  // class-specific public methods:
  //  extensions to the required public methods      
  //
  //---------------------------------------------------------------------------

  // method: operator=
  //
  DebugLevel& operator= (Integral::DEBUG arg) {
    value_d = (int32)arg;
    return *this;
  }

  // method: operator >
  //
  bool8 operator> (Integral::DEBUG arg) {
    return (value_d > (int32)arg);
  }
  
  // method: operator >=
  //
  bool8 operator>= (Integral::DEBUG arg) {
    return (value_d >= (int32)arg);
  }
  
  // method: operator !=
  //
  bool8 operator!= (Integral::DEBUG arg) {
    return (value_d != (int32)arg);
  }

  // method: operator <
  //
  bool8 operator< (Integral::DEBUG arg) {
    return (value_d < (int32)arg);
  }
  
  // method: operator <=
  //
  bool8 operator<= (Integral::DEBUG arg) {
    return (value_d <= (int32)arg);
  }
  
  // method: operator ==
  //
  bool8 operator== (Integral::DEBUG arg) {
    return (value_d == (int32)arg);
  }
  
  // method: assign
  //
  bool8 assign(Integral::DEBUG arg) {
    value_d = arg;
    return true;
  }

  // method: assign
  //
  bool8 assign(const String& arg) {
    return ((value_d = LEVEL_MAP.getIndex(arg)) >= 0);
  }
  
  //---------------------------------------------------------------------------
  //
  // class-specific public methods:
  //  get methods
  //
  //---------------------------------------------------------------------------

  // method: getIndex
  //
  Integral::DEBUG getIndex(const String& arg) const {
    return (Integral::DEBUG)LEVEL_MAP.getIndex(arg);
  }
  
  // method: getIndex
  //
  Integral::DEBUG getIndex() const {
    return (Integral::DEBUG)(int32)value_d;
  }

  // method: getName
  //
  const String& getName() const {
    return (String&)LEVEL_MAP.getName((int32)value_d);
  }

  // method: operator Integral::DEBUG()
  //
  operator Integral::DEBUG() const {
    return getIndex();
  }

  // method: operator String&()
  //
  operator const String&() const {
    return getName();
  }

  //---------------------------------------------------------------------------
  //
  // private methods
  //
  //---------------------------------------------------------------------------
private:

};

// end of include file
//
#endif
