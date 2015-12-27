// file: $isip/class/math/scalar/Boolean/Boolean.h
// version: $Id: Boolean.h 6805 2001-04-23 22:57:41Z peng $
//

// make sure definitions are only made once
//
#ifndef ISIP_BOOLEAN
#define ISIP_BOOLEAN

// isip include files
//
#ifndef ISIP_SCALAR
#include <MScalar.h>
#endif

// Boolean: a binary boolean value (boolean true or boolean false)
//
class Boolean {

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
  
  // i/o related constants
  //
  static const String DEF_PARAM;

  //----------------------------------------
  //
  // default values and arguments
  //
  //----------------------------------------  

  // define the default value(s) of the class data
  //
  static const bool8 DEF_VALUE = false;

  // default arguments to methods
  //
  
  //----------------------------------------
  //
  // error codes
  //
  //----------------------------------------  

  static const int32 ERR = 20100;

  //---------------------------------------------------------------------------
  //
  // protected data
  //
  //---------------------------------------------------------------------------
protected:

  // bool8 value
  //
  bool8 value_d;

  // define a static debug level for all objects of this class
  //
  static Integral::DEBUG debug_level_d;
  
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

  // method: setDebug
  //
  static bool8 setDebug(Integral::DEBUG level) {
    debug_level_d = level;
    return true;
  }

  // other debug methods
  //
  bool8 debug(const unichar* message) const;

  // method: destructor
  //
  ~Boolean() {}

  // method: default constructor
  //
  Boolean(bool8 arg = DEF_VALUE) {
    value_d = arg;
  }

  // method: copy constructor
  //
  Boolean(const Boolean& arg) {
    assign(arg);
  }
  
  // method: assign
  //
  bool8 assign(const Boolean& arg) {
    value_d = arg;
    return true;
  }

  // method: operator=
  //
  Boolean& operator= (const Boolean& arg) {
    assign(arg);
    return *this;
  }

  // method: sofSize
  //
  int32 sofSize() const {
    return sizeof(byte8);
  }

  // other i/o methods
  //
  bool8 read(Sof& sof, int32 tag, const String& name = CLASS_NAME);
  bool8 write(Sof& sof, int32 tag, const String& name = CLASS_NAME) const;

  bool8 readData(Sof& sof, const String& pname = DEF_PARAM,
		   int32 size = SofParser::FULL_OBJECT,
		   bool8 param = true,
		   bool8 nested = false);
  bool8 writeData(Sof& sof, const String& pname = DEF_PARAM) const;

  // method: eq
  //
  bool8 eq(const Boolean& arg) const {
    return (value_d == arg.value_d);
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
  bool8 clear(Integral::CMODE ctype = Integral::DEF_CMODE) {
    value_d = DEF_VALUE;
    return true;
  }
  
  //---------------------------------------------------------------------------
  //
  // class-specific public methods
  //
  //---------------------------------------------------------------------------
public:

  // method: assign
  //
  bool8 assign(bool8 arg) {
    value_d = arg;
    return true;
  }

  // method: assign
  //
  bool8 assign(const String& arg) {
    arg.get(value_d);
    return true;
  }
  
  // method: almostEqual
  //  note that we need this method for higher-level templates
  //
  bool8 almostEqual(bool8 arg) const {
    return (value_d == arg);
  }

  // method: almostEqual
  //  note that we need this method for higher-level templates
  //  
  bool8 almostEqual(bool8 arg, float64, float64) const {
    return (value_d == arg);
  }

  // method: operator=
  //
  Boolean& operator= (bool8 arg) {
    value_d = arg;
    return *this;
  }

  // method: operator()
  //
  operator bool8() const {
    return value_d;
  }

  // method: get
  //
  bool8 get(String& arg) const {
    arg.assign(value_d);
    return true;
  }
  
  // method: rand
  //
  bool8 rand(Random& generator = Random::GLOBAL_UNIFORM) {
    return (generator.get() > 0.5);
  }

  // method: memSize
  //
  int32 memSize() const {
    return sizeof(bool8);
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
