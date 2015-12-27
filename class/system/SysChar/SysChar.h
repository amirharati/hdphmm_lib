// file: $isip/class/system/SysChar/SysChar.h
// version: $Id: SysChar.h 7770 2002-02-20 20:41:47Z yuan $
//

// make sure definitions are only made once
//
#ifndef ISIP_SYSCHAR
#define ISIP_SYSCHAR

// isip include files
//
#ifndef ISIP_INTEGRAL
#include <Integral.h>
#endif

#ifndef ISIP_ERROR
#include <Error.h>
#endif

// forward class definition(s)
//
class SysString;

// SysChar: a class that manages unicode characters. this class is
// implemented as an index into the Unicode standard list of
// characters. the class supports automatic conversion to and from
// UTF8 (which includes standard 7-bit ASCII) and UTF16 encoded byte8
// streams.
//
class SysChar {

  //---------------------------------------------------------------------------
  //
  // public constants
  //
  //---------------------------------------------------------------------------
public:

  // define the class name
  //
  static const SysString CLASS_NAME;
  
  //---------------------------------------
  //
  // encoding constants
  //
  //---------------------------------------

  // bit masks to determine if this is a fixed character or not. right
  // now we don't deal with variable length characters, we just error off.
  //
  static const byte8 UTF8_FIXED = 0x80;
  static const uint16 UTF16_FIXED = 0x0000;

  // encoding flags that represent the character formats
  //
  enum ENCODE { ENCODE_ASCII = 0, ENCODE_UTF8, ENCODE_UTF16,
		DEF_ENCODE = ENCODE_ASCII };
  
  // define special characters
  //
  static const SysChar NULLC;
  static const SysChar SPACEC;
  static const SysChar TILDE;
  static const SysChar DOLLAR;
  static const SysChar NEWLINE;
  
  //----------------------------------------
  //
  // default values and arguments
  //
  //----------------------------------------  

  // define the default value(s) of the class data
  //
  static const unichar DEF_VALUE = (unichar)0;

  //----------------------------------------
  //
  // error codes
  //
  //----------------------------------------  

  static const int32 ERR = 1100;
  static const int32 ERR_NOTASC = 1101;
  static const int32 ERR_UNUTF8 = 1102;
  static const int32 ERR_UNUTF16 = 1103;
  static const int32 ERR_UNKENC = 1104;

  //---------------------------------------------------------------------------
  //
  // protected data
  //
  //---------------------------------------------------------------------------
protected:

  // internal data - be careful not add anything that isn't absolutely
  // necessary, so that higher level classes (e.g., vector) do not waste space
  //
  unichar value_d;

  // declare a static debug level for all class instantitations
  //
  static Integral::DEBUG debug_level_d;
  
  //---------------------------------------------------------------------------
  //
  // required public methods
  //
  //---------------------------------------------------------------------------
public:

  // method: name
  //
  static const SysString& name() {
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
  ~SysChar() {}

  // method: default constructor
  //
  SysChar(unichar arg = DEF_VALUE) {
    value_d = arg;
  }

  // method: copy constructor
  //
  SysChar(const SysChar& arg) {
    assign(arg);
  }

  // method: assign
  //
  bool8 assign(const SysChar& arg) {
    value_d = arg.value_d;
    return true;
  }
  
  // method: operator=
  //
  SysChar& operator=(const SysChar& arg) {
    assign(arg);
    return *this;
  }
    
  // i/o methods
  //  i/o methods are omitted because this class can not be written to
  //  an Sof file
  //

  // method: eq
  // 
  bool8 eq(const SysChar& arg) const {
    return (value_d == arg.value_d);
  }

  // memory management methods:
  //  the new and delete methods are omitted because only classes at the
  //  math library level and above are required to override new and delete
  //
  bool8 clear(Integral::CMODE ctype = Integral::DEF_CMODE);

  //---------------------------------------------------------------------------
  //
  // class-specific public methods:
  //  extensions to required methods
  //
  //---------------------------------------------------------------------------

  // method: constructor
  //  this constructor initializes a SysChar from a C character value
  //
  SysChar(byte8* data, ENCODE encoding = DEF_ENCODE) {
    int32 len;
    assign(len, data, encoding);
  }

  // method: assign
  //
  bool8 assign(byte8 arg) {
    value_d = (unichar)arg;
    return true;
  }

  // other assign methods
  //
  bool8 assign(unichar arg);
  bool8 assign(int32& len, const byte8* arg, ENCODE encoding = DEF_ENCODE);
  bool8 assign(const SysString& arg);

  // method: eq
  //
  bool8 eq(const unichar arg) const {
    SysChar temp(arg);
    return eq(temp);
  }

  // method: ne
  //
  bool8 ne(const SysChar& arg) const {
    return (value_d != arg.value_d);
  }

  // method: ne
  //
  bool8 ne(const unichar arg) const {
    return (value_d != arg);
  }
  
  // method: memSize
  //  get the size of object in memory 
  //
  int32 memSize() const {
    return sizeof(value_d);
  }
  
  //---------------------------------------------------------------------------
  //
  // class-specific public methods:
  //  casting and conversion methods
  //
  //---------------------------------------------------------------------------

  // method: operator()
  //
  operator unichar() const {
    return value_d;
  }

  // method: get
  //  convert to an ascii byte8 value
  //
  bool8 get(byte8& arg) const {
    arg = (byte8)value_d;
    return true;
  }

  // method: get
  //
  bool8 get(unichar& arg) const {
    if ((value_d & UTF16_FIXED) == 0) {
      arg = value_d;
    }
    else {
      return Error::handle(name(), L"get", ERR_UNUTF16,
			   __FILE__, __LINE__, Error::WARNING);
    }
    return true;
  }
  
  // other type conversion methods
  //
  bool8 get(int32& len, byte8* arg, ENCODE encoding = DEF_ENCODE) const;
  
  // method: toUpper
  //
  bool8 toUpper() {
    if (isAlpha()) {
      value_d = towupper(value_d);
      return true;
    }
    return false;
  }

  // method: toLower
  //
  bool8 toLower() {
    if (isAlpha()) {
      value_d = towlower(value_d);
      return true;
    }
    return false;
  }
  
  //---------------------------------------------------------------------------
  //
  // class-specific public methods:
  //  character classification methods
  //
  //--------------------------------------------------------------------------
  
  // method: isAlnum
  //  note: calls to wide character system level functions like iswalnum
  //  have been defined as macros under linux 6.2 and above, hence the
  //  global scoping operators like '::' cannot be used with them
  //
  bool8 isAlnum() const {
     return (iswalnum(value_d) != 0);
  }

  // method: isAlpha
  //
  bool8 isAlpha() const {
    return (iswalpha(value_d) != 0);
  }

  // method: isDigit
  //
  bool8 isDigit() const {
    return (iswdigit(value_d) != 0);
  }

  // method: isLower
  //
  bool8 isLower() const {
    return (iswlower(value_d) != 0);
  }

  // method: isPrint
  //
  bool8 isPrint() const {
    return (iswprint(value_d) != 0);
  }

  // method: isPunct
  //
  bool8 isPunct() const {
    return (iswpunct(value_d) != 0);
  }        

  // method: isSpace
  //
  bool8 isSpace() const {
    return (iswspace(value_d) != 0);
  }        

  // method: isUpper
  //
  bool8 isUpper() const {
    return (iswupper(value_d) != 0);
  }    
  
  //---------------------------------------------------------------------------
  //
  // class-specific public methods:
  //  relational and logical methods
  //
  //---------------------------------------------------------------------------

  // method: gt
  //
  bool8 gt(const SysChar& arg) const {
    return (value_d > arg.value_d);
  }

  // method: gt
  //
  bool8 gt(unichar arg) const {
    return (value_d > arg);
  }

  // method: lt
  //
  bool8 lt(const SysChar& arg) const {
    return (value_d < arg.value_d);
  }

  // method: lt
  //
  bool8 lt(unichar arg) const {
    return (value_d < arg);
  }        

  // method: ge
  //
  bool8 ge(const SysChar& arg) const {
    return (value_d >= arg.value_d);
  }

  // method: ge
  //
  bool8 ge(unichar arg) const {
    return (value_d >= arg);
  }    

  // method: le
  //
  bool8 le(const SysChar& arg) const {
    return (value_d <= arg.value_d);
  }

  // method: le
  //
  bool8 le(unichar arg) const {
    return (value_d <= arg);
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
