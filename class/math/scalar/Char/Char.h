// file: $isip/class/char/Char/Char.h
// version: $Id: Char.h 6805 2001-04-23 22:57:41Z peng $
//

// make sure definitions are only made once
//
#ifndef ISIP_CHAR
#define ISIP_CHAR

// isip include files
//
#ifndef ISIP_SYS_CHAR
#include <SysChar.h>
#endif

#ifndef ISIP_STRING
#include <String.h>
#endif

#ifndef ISIP_MEMORY_MANAGER
#include <MemoryManager.h>
#endif

// Char: a class that implements a generic character capability by
// inheriting the SysChar class functionality. we only need to add Sof file
// support and scalar type conversions for the full scalar object.
//
class Char : public SysChar {

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
  
  //----------------------------------------
  //
  // default values and arguments
  //
  //----------------------------------------  

  // define the default value(s) of the class data
  //  note that DEF_VALUE is missing because we inherit SysChar's DEF_VALUE
  //
  
  // default arguments to methods
  //
  static const String DEF_PARAM;
  
  //----------------------------------------
  //
  // error codes
  //
  //----------------------------------------  
  
  static const int32 ERR = 20300;

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
  //  the setDebug method is inherited from the MScalar template class
  //
  bool8 debug(const unichar* message) const;
  
  // method: destructor
  //
  ~Char() {}

  // method: default constructor
  //
  Char(unichar arg = DEF_VALUE) {
    value_d = arg;
  }

  // method: copy constructor 
  //
  Char(const Char& arg) {
    value_d = (unichar)arg;
  }
  
  // assign methods:
  //  these methods are inherited from the MScalar template class
  //

  // method: operator=
  //
  Char& operator= (const Char& arg) {
    assign(arg);
    return *this;
  }

  // method: sofSize
  //
  int32 sofSize() const {
    return sizeof(value_d);
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
  //  these methods are inherited from the SysChar template class
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

  // other memory management methods:
  //  these methods are inherited from the SysChar template class
  //
  
  //---------------------------------------------------------------------------
  //
  // class-specific public methods
  //
  //---------------------------------------------------------------------------

  // method: Char
  //
  Char(const byte8* data, ENCODE encoding = DEF_ENCODE) {
    int32 len;
    assign(len, data, encoding);
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
