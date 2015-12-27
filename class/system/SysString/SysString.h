// file: $isip/class/system/SysString/SysString.h
// version: $Id: SysString.h 9418 2004-03-10 17:11:33Z parihar $
//
// notes:
//
// (1) AH (07/08/2010): for gcc 4.4.4 compatibility,
//     we changed:
//        return ::wcschr((wchar_t*)ws1, (wchar_t*)ws2);
//     to:
//        return ::wcschr(ws1, ws2);
//

// make sure definitions are only made once
//
#ifndef ISIP_SYS_STRING
#define ISIP_SYS_STRING

// include the configure output:
//  this has to be done here since wchar.h is possibly included before
//  File.h (which in turn includes Integral.h and IntegralConfigure.h)
//
#ifndef ISIP_INTEGRAL_CONFIGURE
#define ISIP_INTERNAL_USE_ONLY
#include <IntegralConfigure.h>
#undef ISIP_INTERNAL_USE_ONLY
#endif

// include definition for the SysComplex type
//
#ifndef ISIP_SYS_COMPLEX
#include <SysComplex.h>
#endif

// system include files needed for non Solaris systems
//
#if ISIP_WCHAR_MODE == ISIP_WCHAR_REDHAT
#include <wchar.h>
#endif

// isip include files:
//  though we could get by with a forward class definition, it is very
//  convenient to include SysChar here, since virtually all methods
//  use it. File is needed so we can convert the File::MODE
//  enumeration into a string. a benefit of having SysChar in the
//  header file is so we can convert the SysChar::ENCODING enumeration
//  into a string, as well
//
#ifndef ISIP_SYS_CHAR
#include <SysChar.h>
#endif

#ifndef ISIP_FILE
#include <File.h>
#endif

// SysString: a class that manages a string of unicode characters. this is
// needed at a low-level in the system so that other low-level classes,
// such as Sof, can operate on unicode characters. most users will
// interact with a higher-level version of this class in math/scalar
// called String.
//
class SysString {
    
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
  // other important constants
  //
  //---------------------------------------

  // miscellaneous constants
  //
  static const int32 MAX_LENGTH = 1024;
  static const int32 BIG_BUFFER_LENGTH = 8192;
  static const int32 STATIC_BUFFER_SIZE = 16;

  // define special strings
  //
  static const unichar NULL_STRING[];
  static const SysString NULL_PTR;
  
  // text corresponding to bool8 values
  //
  static const SysString BOOL_TRUE;
  static const SysString BOOL_FALSE;

  // text corresponding to debug values
  //
  static const SysString DBG_NONE;
  static const SysString DBG_BRIEF;
  static const SysString DBG_DETAILED;
  static const SysString DBG_ALL;
  
  // text corresponding to compare values
  //
  static const SysString CMP_EQUAL;
  static const SysString CMP_LESSER;
  static const SysString CMP_GREATER;

  // text corresponding to file mode values
  //
  static const SysString MODE_READ_ONLY;
  static const SysString MODE_READ_PLUS;
  static const SysString MODE_WRITE_ONLY;
  static const SysString MODE_WRITE_PLUS;
  static const SysString MODE_APPEND_ONLY;
  static const SysString MODE_APPEND_PLUS;

  // text corresponding to file type values
  //
  static const SysString TYPE_TEXT;
  static const SysString TYPE_BINARY;
  
  // text corresponding to file binary mode values
  //
  static const SysString BMODE_NATIVE;
  static const SysString BMODE_SWAP;
  static const SysString BMODE_BIG_ENDIAN;
  static const SysString BMODE_LITTLE_ENDIAN;
  
  // text corresponding to SysChar encode values
  //
  static const SysString ENCODE_ASCII;
  static const SysString ENCODE_UTF8;
  static const SysString ENCODE_UTF16;
  
  // text corresponding to MemoryManager modes
  //
  static const SysString MMGR_MODE_OPTIMIZE;
  static const SysString MMGR_MODE_TRACK;
  
  // small state machine for symbolPad
  //
  static const int32 STATE_PAD_NOSPACE = 0;
  static const int32 STATE_PAD_SPACE = 1;
  
  // format for the debug method output
  //
  static const SysString DBG_FORMAT_0;
  static const SysString DBG_FORMAT_1;
  static const SysString DBG_FORMAT_2;
  static const SysString DBG_FORMAT_3;

  // format for the debugStr output
  //
  static const SysString DBGS_FORMAT_0;
  static const SysString DBGS_FORMAT_1;
  static const SysString DBGS_FORMAT_2;
  static const SysString DBGS_FORMAT_3;

  // 8-bit version of the default format strings (for efficiency)
  //
  static const char DEF_FMT_VOIDP_8BIT[];
  static const char DEF_FMT_ULONG_8BIT[];
  static const char DEF_FMT_ULLONG_8BIT[];
  static const char DEF_FMT_LONG_8BIT[];
  static const char DEF_FMT_LLONG_8BIT[];
  static const char DEF_RFMT_FLOAT_8BIT[];
  static const char DEF_WFMT_FLOAT_8BIT[];
  static const char DEF_RFMT_DOUBLE_8BIT[];
  static const char DEF_WFMT_DOUBLE_8BIT[];

  //----------------------------------------
  //
  // default values and arguments
  //
  //----------------------------------------  

  // define the default value(s) of the class data
  //
  static const int32 DEF_CAPACITY = 0;
  static const SysString DEF_VALUE;

  // default arguments to methods
  //
  static const unichar DEF_TERM = (unichar)NULL;
  static const byte8 DEF_TERM_BYTE8 = (byte8)NULL;
  static const int32 DEF_POS = Integral::NO_POS;

  //----------------------------------------
  //
  // error codes
  //
  //----------------------------------------  

  static const int32 ERR = 1300;
  
  //---------------------------------------------------------------------------
  //
  // protected data
  //
  //---------------------------------------------------------------------------
protected:

  // internal data - be careful not to add anything that isn't absolutely
  // necessary, so that higher level classes (e.g., vector) do not waste space
  //
  unichar* value_d;
  int32 capacity_d;

  // declare a static debug level for all class instantiations
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
  //  the setDebug method for this class is static because the debug_level is
  //  shared across all objects of this class type
  //
  static bool8 setDebug(Integral::DEBUG level) {
    debug_level_d = level;
    return true;
  }

  // other debug methods
  //
  bool8 debug(const unichar* msg) const;
  
  // destructor/constructor(s)
  //

  // method: destructor
  //
  ~SysString() {
    freeMem();
  }

  // method: default constructor
  //
  SysString(int32 capacity = DEF_CAPACITY);

  // method: copy constructor
  //
  SysString(const SysString& arg);
  
  // assign methods
  //
  bool8 assign(const SysString& arg);

  // method: operator=
  //
  SysString& operator=(const SysString& arg) {
    assign(arg);
    return *this;
  }

  // i/o methods:
  //  these methods are omitted because SysString can not write itself to an
  //  sof file
  //

  // equality methods
  //
  bool8 eq(const SysString& value, bool8 case_sensitive = true) const;

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

  // constructors
  //
  SysString(const unichar* data);
  SysString(const byte8* data, SysChar::ENCODE encoding = SysChar::DEF_ENCODE);

  // assign methods
  //
  bool8 assign(const unichar* data);
  bool8 assign(const byte8* data, int32 max_size = BIG_BUFFER_LENGTH,
		 SysChar::ENCODE encoding = SysChar::DEF_ENCODE);

  // numeric conversion assignment methods:
  //
  bool8 assign(const void* arg);
  bool8 assign(bool8 arg);
  bool8 assign(const byte8 arg);
  bool8 assign(unichar arg);
  bool8 assign(const uint16 arg);
  bool8 assign(const uint32 arg);
  bool8 assign(const uint64 arg);
  bool8 assign(const int16 arg);
  bool8 assign(const int32 arg);
  bool8 assign(const int64 arg);
  bool8 assign(const float32 arg);
  bool8 assign(const float64 arg);

  template <class TIntegral>
  bool8 assign(const SysComplex<TIntegral>& arg);

  // define versions of the assign methods that take format strings
  //
  bool8 assign(const SysString& arg, const unichar* fmt);
  bool8 assign(const unichar* data, const unichar* fmt);
  bool8 assign(const byte8* data, const unichar* fmt,
		 int32 max_size = BIG_BUFFER_LENGTH,
		 SysChar::ENCODE encoding = SysChar::DEF_ENCODE);

  // numeric conversion assignment methods:
  //  these methods are similar to sprintf() in C
  //
  bool8 assign(const void* arg, const unichar* fmt);
  bool8 assign(const bool8 arg, const unichar* fmt);
  bool8 assign(const byte8 arg, const unichar* fmt);
  bool8 assign(const unichar arg, const unichar* fmt);
  bool8 assign(const uint16 arg, const unichar* fmt);
  bool8 assign(const uint32 arg, const unichar* fmt);
  bool8 assign(const uint64 arg, const unichar* fmt);
  bool8 assign(const int16 arg, const unichar* fmt);
  bool8 assign(const int32 arg, const unichar* fmt);
  bool8 assign(const int64 arg, const unichar* fmt);
  bool8 assign(const float32 arg, const unichar* fmt);
  bool8 assign(const float64 arg, const unichar* fmt);

  template <class TIntegral>
  bool8 assign(const SysComplex<TIntegral>& arg, const unichar* fmt);

  // enum assignment methods
  //
  bool8 assign(Integral::DEBUG arg);
  bool8 assign(Integral::COMPARE arg);
  bool8 assign(File::MODE arg);
  bool8 assign(File::BMODE arg);
  bool8 assign(File::TYPE arg);
  bool8 assign(SysChar::ENCODE arg);
  bool8 assign(MemoryManager::MODE arg);
  
  // special assignment methods:
  //  swaps pointers and is meant to be very fast
  //
  bool8 swap(SysString& arg);

  //---------------------------------------------------------------------------
  //
  // class-specific public methods:
  //  relational and logical methods
  //
  //---------------------------------------------------------------------------
  
  // method: compare
  //
  Integral::COMPARE compare(const SysString& str) const {
    return compare(*this, str);
  }
  
  // other generic compare methods
  //
  Integral::COMPARE compare(const SysString& arg1,
			    const SysString& arg2) const;
  Integral::COMPARE compare(const unichar* str) const;
  Integral::COMPARE comparePartial(const SysString& arg,
				   int32 arg_offset,
				   int32 num_elements, int32 offset) const;
  Integral::COMPARE comparePartial(const unichar* arg,
				   int32 arg_offset,
				   int32 num_elements, int32 offset) const;

  // method: ne
  //
  bool8 ne(const SysString& vector, bool8 case_sensitive = true) const {
    return !eq(vector, case_sensitive);
  }

  // other equality methods:
  //
  bool8 eq(const unichar* value, bool8 case_sensitive = true) const;
  bool8 ne(const unichar* value, bool8 case_sensitive = true) const;

  // method: gt
  //
  bool8 gt(const SysString& vector) const {
    return (compare(vector) == Integral::GREATER);
  }

  // other greater than methods
  //
  bool8 gt(const unichar* value) const;

  // method: lt
  //
  bool8 lt(const SysString& vector) const {
    return (compare(vector) == Integral::LESSER);
  }

  // other less than methods
  //
  bool8 lt(const unichar* value) const;

  // method: ge
  //
  bool8 ge(const SysString& vector) const {
    return (compare(vector) != Integral::LESSER);
  }

  // other greater than or equal to methods
  //
  bool8 ge(const unichar* value) const;

  // method: le
  //
  bool8 le(const SysString& vector) const {
    return (compare(vector) != Integral::GREATER);
  }

  // other less than or equal to methods
  //
  bool8 le(const unichar* value) const;

  // unichar comapre methods:
  //  these methods give the number of characters equal or not equal
  //  to the argument
  //
  int32 numEqual(unichar test_value) const;

  // method: numNotEqual
  //
  int32 numNotEqual(unichar test_value) const {
    return (length() - numEqual(test_value));
  }
  
  //---------------------------------------------------------------------------
  //
  // class-specific public methods:
  //  indexing methods
  //
  //---------------------------------------------------------------------------
  
  // method: operator()
  //
  unichar& operator()(int32 index) {
    return value_d[index];
  }

  // method: operator()
  //
  const unichar& operator()(int32 index) const {
    return value_d[index];
  }

  //---------------------------------------------------------------------------
  //
  // class-specific public methods:
  //  conversion methods
  //
  //---------------------------------------------------------------------------
  
  // automatic type conversion methods
  //
  operator byte8*() const;
  operator unichar*() const;
  
  // numeric conversion methods
  //
  bool8 get(void*& arg) const;
  bool8 get(bool8& arg) const;
  bool8 get(byte8& arg) const;
  bool8 get(unichar& arg) const;
  bool8 get(SysChar& arg) const;
  bool8 get(uint16& arg) const;
  bool8 get(uint32& arg) const;
  bool8 get(uint64& arg) const;
  bool8 get(int16& arg) const;
  bool8 get(int32& arg) const;
  bool8 get(int64& arg) const;
  bool8 get(float32& arg) const;
  bool8 get(float64& arg) const;

  template <class TIntegral>
  bool8 get(SysComplex<TIntegral>& arg) const;

  //---------------------------------------------------------------------------
  //
  // class-specific public methods:
  //  size-related methods
  //
  //---------------------------------------------------------------------------

  // method: length
  //
  int32 length() const {
    return isip_wcslen(value_d);
  }

  // size methods
  //
  int32 memSize() const;

  // capacity-related methods
  //
  bool8 setCapacity(int32 cap);
  
  //---------------------------------------------------------------------------
  //
  // class-specific public methods:
  //  string manipulation methods
  //
  //---------------------------------------------------------------------------

  // array-oriented methods
  //*
  int64 getBuffer(unichar* buffer, int32 max) const;
  int64 getBuffer(byte8* buffer, int32 max,
		 SysChar::ENCODE encoding = SysChar::DEF_ENCODE) const;
  bool8 substr(SysString& str, int32 offset,
		 int32 num_elements = Integral::NO_POS) const;

  // insert/replace a substring into the string methods
  //
  bool8 insert(const SysString& str, int32 index);
  bool8 insert(const unichar* str, int32 index);
  bool8 replace(const SysString& str, int32 index);
  bool8 replace(const unichar* str, int32 index);
  bool8 replace(const SysString& pattern, const SysString& new_stuff);
  bool8 replaceAll(const SysString& pattern, const SysString& new_stuff);
  bool8 deleteRange(int32 offset, int32 num_elements);

  // append to the end of the string methods
  //
  bool8 concat(const SysString& str);
  bool8 concat(const SysString& str1, const SysString& str2);

  // method: concat
  //
  bool8 concat(const unichar* arg) {
    SysString temp;
    temp.assign(arg);
    return concat(temp);
  }

  // method: concat
  //
  bool8 concat(unichar arg) {
    SysString temp;
    temp.assign(arg);
    return concat(temp);
  }

  // numeric concatenation methods:
  //  these methods are similar to sprintf() in C
  //

  // method: concat
  //
  bool8 concat(const void* arg) {
    SysString temp;
    temp.assign(arg);
    return concat(temp);
  }
  
  // method: concat
  //
  bool8 concat(bool8 arg) {
    SysString temp;
    temp.assign(arg);
    return concat(temp);
  }
  
  // method: concat
  //
  bool8 concat(const byte8 arg) {
    SysString temp;
    temp.assign(arg);
    return concat(temp);
  }
  
  // method: concat
  //
  bool8 concat(const uint16 arg) {
    SysString temp;
    temp.assign(arg);
    return concat(temp);
  }
  
  // method: concat
  //
  bool8 concat(const uint32 arg) {
    SysString temp;
    temp.assign(arg);
    return concat(temp);
  }
  
  // method: concat
  //
  bool8 concat(const uint64 arg) {
    SysString temp;
    temp.assign(arg);
    return concat(temp);
  }
  
  // method: concat
  //
  bool8 concat(const int16 arg) {
    SysString temp;
    temp.assign(arg);
    return concat(temp);
  }
  
  // method: concat
  //
  bool8 concat(const int32 arg) {
    SysString temp;
    temp.assign(arg);
    return concat(temp);
  }
  
  // method: concat
  //
  bool8 concat(const int64 arg) {
    SysString temp;
    temp.assign(arg);
    return concat(temp);
  }
  
  // method: concat
  //
  bool8 concat(const float32 arg) {
    SysString temp;
    temp.assign(arg);
    return concat(temp);
  }
  
  // method: concat
  //
  bool8 concat(const float64 arg) {
    SysString temp;
    temp.assign(arg);
    return concat(temp);
  }
  
  // method: concat
  //
    
  template <class TIntegral>
  bool8 concat(const SysComplex<TIntegral>& arg) {
    SysString temp;
    temp.assign(arg);
    return concat(temp);
  }
    
  // append to the end of the string methods with format
  //

  // method: concat
  //
  bool8 concat(const SysString& arg, const unichar* fmt) {
    SysString temp;
    temp.assign(arg, fmt);
    return concat(temp);
  }
  
  // method: concat
  //
  bool8 concat(const unichar* arg, const unichar* fmt) {
    SysString temp;
    temp.assign(arg, fmt);
    return concat(temp);
  }
  
  // method: concat
  //
  bool8 concat(unichar arg, const unichar* fmt) {
    SysString temp;
    temp.assign(arg, fmt);
    return concat(temp);
  }
  
  // numeric concatenation methods with format:
  //  these methods are similar to sprintf() in C
  //

  // method: concat
  //
  bool8 concat(const void* arg, const unichar* fmt) {
    SysString temp;
    temp.assign(arg, fmt);
    return concat(temp);
  }
  
  // method: concat
  //
  bool8 concat(bool8 arg, const unichar* fmt) {
    SysString temp;
    temp.assign(arg, fmt);
    return concat(temp);
  }
  
  // method: concat
  //
  bool8 concat(const byte8 arg, const unichar* fmt) {
    SysString temp;
    temp.assign(arg, fmt);
    return concat(temp);
  }
  
  // method: concat
  //
  bool8 concat(const uint16 arg, const unichar* fmt) {
    SysString temp;
    temp.assign(arg, fmt);
    return concat(temp);
  }
  
  // method: concat
  //
  bool8 concat(const uint32 arg, const unichar* fmt) {
    SysString temp;
    temp.assign(arg, fmt);
    return concat(temp);
  }
  
  // method: concat
  //
  bool8 concat(const uint64 arg, const unichar* fmt) {
    SysString temp;
    temp.assign(arg, fmt);
    return concat(temp);
  }
  
  // method: concat
  //
  bool8 concat(const int16 arg, const unichar* fmt) {
    SysString temp;
    temp.assign(arg, fmt);
    return concat(temp);
  }
  
  // method: concat
  //
  bool8 concat(const int32 arg, const unichar* fmt) {
    SysString temp;
    temp.assign(arg, fmt);
    return concat(temp);
  }
  
  // method: concat
  //
  bool8 concat(const int64 arg, const unichar* fmt) {
    SysString temp;
    temp.assign(arg, fmt);
    return concat(temp);
  }
  
  // method: concat
  //
  bool8 concat(const float32 arg, const unichar* fmt) {
    SysString temp;
    temp.assign(arg, fmt);
    return concat(temp);
  }
  
  // method: concat
  //
  bool8 concat(const float64 arg, const unichar* fmt) {
    SysString temp;
    temp.assign(arg, fmt);
    return concat(temp);
  }
  
  // method: concat
  //
    
  template <class TIntegral>
  bool8 concat(const SysComplex<TIntegral>& arg, const unichar* fmt) {
    SysString temp;
    temp.assign(arg, fmt);
    return concat(temp);
  }
    
  // trim away characters from string methods
  //
  bool8 trim();
  bool8 trim(const SysString& chars);
  bool8 trim(const unichar* chars);
  
  bool8 trimLeft();
  bool8 trimLeft(const SysString& chars);
  bool8 trimLeft(const unichar* chars);
  
  bool8 trimRight();
  bool8 trimRight(const SysString& chars);
  bool8 trimRight(const unichar* chars);
 
  // string case conversion methods
  //
  bool8 toUpper();
  bool8 toLower();
  bool8 toMixed();
  bool8 toMixed(const SysString& sep_chrs);

  //---------------------------------------------------------------------------
  //
  // class-specific public methods:
  //  string search methods
  //
  //---------------------------------------------------------------------------

  // method: firstStr
  /*
    Because The returning type is a pointer  it  should be int64
   */  
  int64 firstStr(const unichar* str, int32 start = Integral::NO_POS) const {
    SysString temp(str);
    return firstStr(temp, start);
  }
  
  // other first string methods
  //
  int64 firstStr(const SysString& str, int32 start = Integral::NO_POS) const;

  // method: lastStr
  //
  int32 lastStr(const unichar* str, int32 end = Integral::NO_POS) const {
    SysString temp(str);
    return lastStr(temp, end);
  }    

  // other last string methods
  //
  int32 lastStr(const SysString& str, int32 end = Integral::NO_POS) const;

  // method: firstChr
  //
  int32 firstChr(const unichar* chrs, int32 start = Integral::NO_POS) const {
    SysString temp(chrs);
    return firstChr(temp, start);
  }
  
  // other first char methods
  //
  int32 firstChr(const SysString& chrs, int32 start = Integral::NO_POS) const;
  int32 firstChr(unichar chr, int32 start = Integral::NO_POS) const;
  
  // method: lastChr
  //
  int32 lastChr(const unichar* chrs, int32 end = Integral::NO_POS) const {
    SysString temp(chrs);
    return lastChr(temp, end);
  }
  
  // other last char methods
  //
  int32 lastChr(const SysString& chrs, int32 end = Integral::NO_POS) const;
  int32 lastChr(unichar chr, int32 end = Integral::NO_POS) const;

  // not char methods:
  //
  int32 firstNotChr(const SysString& chrs, int32 start = Integral::NO_POS) const;
  int32 firstNotChr(unichar chr, int32 start = Integral::NO_POS) const;
  
  int32 lastNotChr(const SysString& chrs, int32 end = Integral::NO_POS) const;
  int32 lastNotChr(unichar chr, int32 end = Integral::NO_POS) const;

  // method: firstAlnum
  //
  int32 firstAlnum(int32 start = Integral::NO_POS) const {
    return firstChar(start, &SysChar::isAlnum);
  }

  // method: firstAlpha
  //
  int32 firstAlpha(int32 start = Integral::NO_POS) const {
    return firstChar(start, &SysChar::isAlpha);
  }

  // method: firstDigit
  //
  int32 firstDigit(int32 start = Integral::NO_POS) const {
    return firstChar(start, &SysChar::isDigit);
  }

  // method: firstLower
  //
  int32 firstLower(int32 start = Integral::NO_POS) const {
    return firstChar(start, &SysChar::isLower);
  }

  // method: firstPrint
  //
  int32 firstPrint(int32 start = Integral::NO_POS) const {
    return firstChar(start, &SysChar::isPrint);
  }

  // method: firstPunct
  //
  int32 firstPunct(int32 start = Integral::NO_POS) const {
    return firstChar(start, &SysChar::isPunct);
  }

  // method: firstSpace
  //
  int32 firstSpace(int32 start = Integral::NO_POS) const {
    return firstChar(start, &SysChar::isSpace);
  }

  // method: firstUpper
  //
  int32 firstUpper(int32 start = Integral::NO_POS) const {
    return firstChar(start, &SysChar::isUpper);
  }

  // method: lastAlnum
  //
  int32 lastAlnum(int32 end = Integral::NO_POS) const {
    return lastChar(end, &SysChar::isAlnum);
  }

  // method: lastAlpha
  //
  int32 lastAlpha(int32 end = Integral::NO_POS) const {
    return lastChar(end, &SysChar::isAlpha);
  }

  // method: lastDigit
  //
  int32 lastDigit(int32 end = Integral::NO_POS) const {
    return lastChar(end, &SysChar::isDigit);
  }

  // method: lastLower
  //
  int32 lastLower(int32 end = Integral::NO_POS) const {
    return lastChar(end, &SysChar::isLower);
  }

  // method: lastPrint
  //
  int32 lastPrint(int32 end = Integral::NO_POS) const {
    return lastChar(end, &SysChar::isPrint);
  }

  // method: lastPunct
  //
  int32 lastPunct(int32 end = Integral::NO_POS) const {
    return lastChar(end, &SysChar::isPunct);
  }

  // method: lastSpace
  //
  int32 lastSpace(int32 end = Integral::NO_POS) const {
    return lastChar(end, &SysChar::isSpace);
  }

  // method: lastUpper
  int32 lastUpper(int32 end = Integral::NO_POS) const {
    return lastChar(end, &SysChar::isUpper);
  }

  // method: firstNotAlnum
  //
  int32 firstNotAlnum(int32 start = Integral::NO_POS) const {
    return firstNotChar(start, &SysChar::isAlnum);
  }

  // method: firstNotAlpha
  //
  int32 firstNotAlpha(int32 start = Integral::NO_POS) const {
    return firstNotChar(start, &SysChar::isAlpha);
  }

  // method: firstNotDigit
  //
  int32 firstNotDigit(int32 start = Integral::NO_POS) const {
    return firstNotChar(start, &SysChar::isDigit);
  }

  // method: firstNotLower
  //
  int32 firstNotLower(int32 start = Integral::NO_POS) const {
    return firstNotChar(start, &SysChar::isLower);
  }

  // method: firstNotPrint
  //
  int32 firstNotPrint(int32 start = Integral::NO_POS) const {
    return firstNotChar(start, &SysChar::isPrint);
  }

  // method: firstNotPunct
  //
  int32 firstNotPunct(int32 start = Integral::NO_POS) const {
    return firstNotChar(start, &SysChar::isPunct);
  }

  // method: firstNotSpace
  //
  int32 firstNotSpace(int32 start = Integral::NO_POS) const {
    return firstNotChar(start, &SysChar::isSpace);
  }

  // method: firstNotUpper
  //
  int32 firstNotUpper(int32 start = Integral::NO_POS) const {
    return firstNotChar(start, &SysChar::isUpper);
  }

  // method: lastNotAlnum
  //
  int32 lastNotAlnum(int32 end = Integral::NO_POS) const {
    return lastNotChar(end, &SysChar::isAlnum);
  }

  // method: lastNotAlpha
  //
  int32 lastNotAlpha(int32 end = Integral::NO_POS) const {
    return lastNotChar(end, &SysChar::isAlpha);
  }

  // method: lastNotDigit
  //
  int32 lastNotDigit(int32 end = Integral::NO_POS) const {
    return lastNotChar(end, &SysChar::isDigit);
  }

  // method: lastNotLower
  //
  int32 lastNotLower(int32 end = Integral::NO_POS) const {
    return lastNotChar(end, &SysChar::isLower);
  }

  // method: lastNotPrint
  //
  int32 lastNotPrint(int32 end = Integral::NO_POS) const {
    return lastNotChar(end, &SysChar::isPrint);
  }

  // method: lastNotPunct
  //
  int32 lastNotPunct(int32 end = Integral::NO_POS) const {
    return lastNotChar(end, &SysChar::isPunct);
  }

  // method: lastNotSpace
  //
  int32 lastNotSpace(int32 end = Integral::NO_POS) const {
    return lastNotChar(end, &SysChar::isSpace);
  }

  // method: lastNotUpper
  //
  int32 lastNotUpper(int32 end = Integral::NO_POS) const {
    return lastNotChar(end, &SysChar::isUpper);
  }
  
  //---------------------------------------------------------------------------
  //
  // class-specific public methods:
  //  tokenize methods
  //
  //---------------------------------------------------------------------------

  // method: countTokens
  //   count the tokens when delimiter is white space
  //
  int32 countTokens() const {
    static SysString temp(L" ");
    return countTokens(temp);
  }
  
  // other count tokens methods
  //
  int32 countTokens(unichar delimiter) const;
  int32 countTokens(const SysString& delimiters) const;

  // method: countDelimiters
  //   count the delimiters when delimiter is white space
  //
  int32 countDelimiters() const {
    static SysString temp(L" ");
    return countDelimiters(temp);
  }
  
  // other count delimiters methods
  //
  int32 countDelimiters(unichar delimiter) const;
  int32 countDelimiters(const SysString& delimiters) const;

  // method: tokenize
  //  tokenize the string when delimiter is white space
  //
  bool8 tokenize(SysString& sub, int32& pos) const {
    static SysString temp(L" ");
    return tokenize(sub, pos, temp);
  }

  // other string tokenize methods
  //
  bool8 tokenize(SysString& sub, int32& pos, unichar delim) const;
  bool8 tokenize(SysString& sub, int32& pos, const SysString delim) const;
  
  // pad symbols methods
  //  this aides in tokenization by ensuring the specified symbols are padded
  //
  bool8 symbolPad(const SysString& symbols);
  
  // debug string creation methods
  //
  bool8 debugStr(const SysString& class_name, const unichar* message_a,
		   const unichar* variable_name,
		   const SysString& variable_value);
  
  bool8 debugStr(const SysString& class_name, const unichar* message_a,
		   const unichar* variable_name);

  bool8 debugStrPrefix(const SysString& class_name,
			 const unichar* message_a);

  // method: getEmptyString
  //  empty string creation methods
  //
  static const SysString& getEmptyString() {
    static SysString temp;
    return temp;
  }
  
  //---------------------------------------------------------------------------
  //
  // private methods
  //
  //---------------------------------------------------------------------------
private:

  // general string search methods:
  //  these are special methods used for class-specific string search
  //  methods. these methods have function pointer as an argument
  //  which allow us to specify any method of the type "bool8
  //  doWhatever() const" of SysChar class.
  //
  int32 firstChar(int32 start, bool8 (SysChar::*method) (void) const) const;
  int32 lastChar(int32 end, bool8 (SysChar::*method) (void) const) const;
  int32 firstNotChar(int32 start,
		    bool8 (SysChar::*method) (void) const) const;  
  int32 lastNotChar(int32 end,
		   bool8 (SysChar::*method) (void) const) const;
  
  // memory allocation methods
  //
  bool8 allocateMem();
  bool8 freeMem();
  bool8 growMem(int32 new_size);

  //---------------------------------------------------------------------------
  //
  // wrap the system wchar methods
  //
  //---------------------------------------------------------------------------

  //  the following private methods are to wrap wide character
  //  support. wide character support is in a great state of flux, so
  //  the "isip_" prefix is meant to clarify that our api is not
  //  dependent on the specific operating system.
  //

  // method: isip_wcslen
  //
  static uint32 isip_wcslen(const unichar* ws) {
    return wcslen(ws);
  }

  // method: isip_wcscmp
  //
  static int32 isip_wcscmp(const unichar* ws1, const unichar* ws2) {
    return wcscmp(ws1, ws2);
  }

  // method: isip_wcsncmp
  //
  static int32 isip_wcsncmp(const unichar* ws1, const unichar* ws2,
				  uint32 n) {
    return wcsncmp(ws1, ws2, n);
  }

  // method: isip_wcschr
  //
  static unichar* isip_wcschr(const unichar* ws1,
				     const unichar ws2) {
    return wcschr((wchar_t*)ws1,(wchar_t) ws2);
  }

  // method: isip_wcscat
  //
  static unichar* isip_wcscat(unichar* ws1, const unichar* ws2) {
    return wcscat(ws1, ws2);
  }

  // method: isip_wcscpy
  //  
  static unichar* isip_wcscpy(unichar* ws1, const unichar* ws2) {
    return wcscpy(ws1, ws2);
  }

  // method: isip_wcsncpy
  //  
  static unichar* isip_wcsncpy(unichar* ws1, const unichar* ws2,
				      uint32 n) {
    return wcsncpy(ws1, ws2, n);
  }

  // method: isip_wctomb
  //  
  static int isip_wctomb(char* s, const unichar wchar) {
    return wctomb(s, (wchar_t)wchar);
  }

  // other wrappers for wchar methods
  //
  static unichar* isip_wcsstr(const unichar* ws1, const unichar* ws2);
  static unichar* isip_wcstok(unichar* ws, const unichar* delim,
			      unichar** ptr);
  static unichar* isip_fgetws(unichar* s, int n, FILE* stream);
  static int32 isip_fputws(const unichar* s, FILE* stream);
  static wint_t isip_fgetwc(FILE* stream);
  static wint_t isip_fputwc(wint_t wc, FILE* stream);

  //---------------------------------------------------------------------------
  //
  // friend functions:
  //  while friend functions are generally discouraged in the ISIP
  //  environment, they are used in the SysString class to isolate
  //  implementation details. currently, wide character support varies
  //  greatly between different operating systems, so we abstract a
  //  core group of wide character functions in this class as private
  //  methods. the file class also needs to access these wrappers
  //  directly for I/O purposes, though, so the friend directive is
  //  used.
  //
  //---------------------------------------------------------------------------

  // put methods
  //
  friend bool8 File::put(const SysString& str);
  friend bool8 File::put(const SysChar chr);

  // get methods
  //
  friend bool8 File::get(SysString& str, int32 len);
  friend bool8 File::get(SysChar& chr);

};

// end of include file
//
#endif
