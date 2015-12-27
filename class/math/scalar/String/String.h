// file: $isip/class/string/String/String.h
// version: $Id: String.h 6805 2001-04-23 22:57:41Z peng $
//

// make sure definitions are only made once
//
#ifndef ISIP_STRING
#define ISIP_STRING

// isip include files
//
#ifndef ISIP_SYS_STRING
#include <SysString.h>
#endif

#ifndef ISIP_SOF_PARSER
#include <SofParser.h>
#endif

#ifndef ISIP_MEMORY_MANAGER
#include <MemoryManager.h>
#endif

// String: a class that manages generalized character strings. this class
// inherits the SysString class functionality. we only need to add Sof file
// support and scalar type conversions for the full scalar object.
//
class String : public SysString {

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

  static const String EMPTY;
  
  //----------------------------------------
  //
  // default values and arguments
  //
  //----------------------------------------
  
  // define the default value(s) of the class data
  //  note we inherit DEF_CAPACITY and DEF_VALUE from SysString class
  //
  
  // default arguments to methods
  //
  static const String DEF_PARAM;
  
  //----------------------------------------
  //
  // error codes
  //
  //----------------------------------------  

  static const int32 ERR = 21200;

  //---------------------------------------------------------------------------
  //
  // protected data
  //
  //---------------------------------------------------------------------------
protected:

  // a static memory manager
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
  //  the setDebug method is inherited from the SysString class
  //
  bool8 debug(const unichar* message) const;

  // method: destructor
  //
  ~String() {}

  // method: default constructor
  //  
  String(int32 arg = DEF_CAPACITY) {
    setCapacity(arg);
  }

  // method: copy constructor
  //  
  String(const String& arg) {
    SysString::assign(arg);
  }
  
  // assign methods:
  //  these methods are inherited from the SysString class
  //

  // method: operator=
  //
  String& operator= (const String& arg) {
    assign(arg);
    return *this;
  }

  // method: sofSize
  //
  int32 sofSize() const {
    return (int32)(sizeof(unichar) * length() + sizeof(capacity_d));
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

  // equality methods:
  //  these methods are inherited from the SysString class
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

  // other memory management methods
  //  these methods are inherited from the SysString class
  //
  
  //---------------------------------------------------------------------------
  //
  // class-specific public methods
  //
  //---------------------------------------------------------------------------
public:

  // method: String
  //
  String(const unichar* arg) {
    SysString::assign(arg);
  }
  
  // random alphanumeric string generation methods
  //
  bool8 rand(int32 min_len = 0, int32 max_len = MAX_LENGTH);

  // method: getEmptyString
  //
  static const String& getEmptyString() {
    static String temp;
    return temp;
  }
  
  // hash method bounded by input capacity
  //
  int32 hash(int32 capacity_a) const;

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
