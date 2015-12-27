// file: $isip/class/system/SysString/sstr_04.cc
// version: $Id: sstr_04.cc 8772 2002-11-05 04:07:20Z parihar $
//

// isip include files
//
#include "SysString.h"
// method: toUpper
//
// arguments: none
//
// return: a bool8 value indicating status
//
// this method converts all characters to uppercase
//
bool8 SysString::toUpper() {

  // create a temporary SysChar object
  //
  SysChar c;
  
  // loop over the elements and change to upper
  //  
  for (int32 i = 0; i < length(); i++) {
    c.assign(value_d[i]);
    c.toUpper();
    value_d[i] = c;
  }

  // exit gracefully
  //
  return true;
}

// method: toLower
//
// arguments: none
//
// return: a bool8 value indicating status
//
// this method converts all characters to lowercase
//
bool8 SysString::toLower() {

  // create a temporary SysChar object
  //
  SysChar c;

  // loop over the elements and change to lower
  //
  for (int32 i = 0; i < length(); i++) {
    c.assign(value_d[i]);
    c.toLower();
    value_d[i] = c;
  }

  // exit gracefully
  //
  return true;
}

// method: toMixed
//
// arguments: none
//
// return: a bool8 value indicating status
//
// this method converts all initial characters to lowercase. initial
// characters are defined as (1) the first non-whitespace character in
// the string, and (2) the first non-whitespace character following
// each whitespace character in the string
//
bool8 SysString::toMixed() {

  // create a temporary SysChar object
  //
  SysChar c;

  // find the first non-space character within the object
  //
  int32 i = firstNotSpace();
  
  while (i != Integral::NO_POS) {
    
    c.assign(value_d[i]);
    c.toUpper();
    value_d[i] = c;

    // jump to the next whitespace
    //
    i = firstSpace(i);

    // if there is whitespace, there may be a character following whitespace
    //
    if (i != Integral::NO_POS) {
      i = firstNotSpace(i);
    }
  }
  
  // exit gracefully
  //
  return true;
}

// method: toMixed
//
// arguments:
//  const SysString& sep_chrs: (input) separation characters
//
// return: a bool8 value indicating status
//
// this method converts all initial characters to lowercase. initial
// characters are defined as (1) the first character not in sep_chrs
// in the string, and (2) the first character not in sep_chrs
// following each character in sep_chrs in the string.
//
bool8 SysString::toMixed(const SysString& sep_chrs_a) {

  // create a temporary SysChar object
  //
  SysChar c;

  // find the first instance of a character in chrs_a within the
  // object
  //
  int32 i = firstNotChr(sep_chrs_a);

  while (i != Integral::NO_POS) {
    
    c.assign(value_d[i]);
    c.toUpper();
    value_d[i] = c;

    // jump to the next character within sep_chrs
    //
    i = firstChr(sep_chrs_a, i);

    // if there is a character in sep_chrs, there may be a character
    // following which isn't
    //
    if (i != Integral::NO_POS) {
      i = firstNotChr(sep_chrs_a, i);
    }
  }
  
  // exit gracefully
  //
  return true;
}

// method: compare
//
// arguments:
//  const unichar* arg: (input) input string
//
// return: int32 comparison result
//
// this method checks if the string is greater than, less than,
// or equal to the object
//
Integral::COMPARE SysString::compare(const unichar* arg_a) const {

  // declare a static string
  //    
  static SysString temp;

  // copy the input buffer to a temporary string
  //
  temp.assign(arg_a);

  // call the master function
  //
  return compare(*this, temp);
}

// method: compare
//
// arguments:
//  const SysString& arg1: (input) input string
//  const SysString& arg2: (input) input string
//
// return: int32 comparison result
//
// this method checks if arg1 is greater than, less than, or equal to arg2
//
Integral::COMPARE SysString::compare(const SysString& arg1_a,
				     const SysString& arg2_a) const {

  // call wcscmp function to compare
  //
  int32 cmp = isip_wcscmp(arg1_a.value_d, arg2_a.value_d);

  // branch on the return value of wcscmp
  //
  if (cmp > 0) {
    return Integral::GREATER;
  }
  else if (cmp < 0) {
    return Integral::LESSER;
  }

  // exit gracefully
  //
  return Integral::EQUAL;
}

// method: eq
//
// arguments:
//  const unichar* arg: (input) input string
//  bool8 case_sensitive: (input) if the comparison is case sensitive
//
// return: a bool8 value indicating status
//
// this method checks if the string is equal to the object
//
bool8 SysString::eq(const unichar* arg_a, bool8 case_sensitive_a) const {

  // declare a static string
  //  
  static SysString temp;

  // copy the input buffer to a temporary string
  //
  temp.assign(arg_a);
  
  // call the master function
  //
  return eq(temp, case_sensitive_a);
}

// method: eq
//
// arguments:
//  const SysString& arg: (input) input string
//  bool8 case_sensitive: (input) if the comparison is case sensitive
//
// return: a bool8 value indicating status
//
// this method checks if the string is equal to the object
//
bool8 SysString::eq(const SysString& arg_a, bool8 case_sensitive_a) const {

  // branch on bool8 case sensitive flag
  //
  if (case_sensitive_a) {
      
    if (compare(arg_a) == Integral::EQUAL) {
      return true;
    } 
  }

  // not case sensitive
  //
  else {
    static SysString cmp_str;
    static SysString this_str;

    // preserve the case of the input string
    //
    cmp_str.assign(arg_a);
    this_str.assign(*this);

    // change both to upper case
    //
    cmp_str.toLower();
    this_str.toLower();
    if (this_str.compare(cmp_str) == Integral::EQUAL) {
      return true;
    }
  }
    
  // exit gracefully
  //
  return false;
}

// method: gt
//
// arguments:
//  const unichar* arg: (input) input string
//
// return: a bool8 value indicating status
//
// this method checks if the string is greater than the object
//
bool8 SysString::gt(const unichar* arg_a) const {

  // declare a static string
  //  
  static SysString temp;

  // copy the input buffer to a temporary string
  //
  temp.assign(arg_a);
  
  // call the master function
  //
  return gt(temp);
}

// method: lt
//
// arguments:
//  const unichar* arg: (input) input string
//
// return: a bool8 value indicating status
//
// this method checks if the string is less than the object
//
bool8 SysString::lt(const unichar* arg_a) const {

  // declare a static string
  //  
  static SysString temp;

  // copy the input buffer to a temporary string
  //
  temp.assign(arg_a);

  // call the master function
  //
  return lt(temp);
}

// method: ne
//
// arguments:
//  const unichar* arg: (input) input string
//  bool8 case_sensitive: (input) if the comparison is case sensitive
//
// return: a bool8 value indicating status
//
// this method checks if the string is not equal to the object
//
bool8 SysString::ne(const unichar* arg_a, bool8 case_sensitive_a) const {

  // declare a static string
  //  
  static SysString temp;

  // copy the input buffer to a temporary string
  //
  temp.assign(arg_a);

  // call the master function
  //
  return ne(temp, case_sensitive_a);
}

// method: le
//
// arguments:
//  const unichar* arg: (input) input string
//
// return: a bool8 value indicating status
//
// this method checks if the string is less than or equal to the object
//
bool8 SysString::le(const unichar* arg_a) const {

  // declare a static string
  //
  static SysString temp;

  // copy the input buffer to a temporary string
  //
  temp.assign(arg_a);

  // call the master function
  //
  return le(temp);
}

// method: ge
//
// arguments:
//  const unichar* arg: (input) input string
//
// return: a bool8 value indicating status
//
// this method checks if the string is greater than or equal to the object
//
bool8 SysString::ge(const unichar* arg_a) const {

  // declare static string
  //
  static SysString temp;

  // assign the input buffer to a temporary string
  //
  temp.assign(arg_a);

  // call the master function
  //
  return ge(temp);
}

// method: comparePartial
//
// arguments:
//  const unichar* arg: (input) input string
//  int32 arg_offset: (input) starting position in "arg"
//  int32 num_elements: (input) number of elements to compare
//  int32 offset: (input) starting position in "this"
//
// return: int32 comparison result
//
// this method checks if a portion of this string greater than, less than,
// or equal to the object
//
Integral::COMPARE SysString::comparePartial(const unichar* arg_a,
					    int32 arg_offset_a,
					    int32 num_elements_a,
					    int32 offset_a) const {

  // declare local variables
  //
  static SysString temp;

  // assign the input buffer to a temporary string
  //
  temp.assign(arg_a);

  // call the master function
  //
  return comparePartial(temp, arg_offset_a, num_elements_a, offset_a);
}

// method: comparePartial
//
// arguments:
//  const SysString& arg: (input) input string
//  int32 arg_offset: (input) starting position in "arg"
//  int32 num_elements: (input) number of elements to compare
//  int32 offset: (input) starting position in "this"
//
// return: int32 comparison result
//
// this method checks if a portion of this string greater than, less
// than, or equal to the object
//
Integral::COMPARE SysString::comparePartial(const SysString& arg_a,
					    int32 arg_offset_a,
					    int32 num_elements_a,
					    int32 offset_a) const {

  // check if the source offset is greater than the length of the
  // current string
  //
  if (arg_offset_a > length())  {

    // check if the destination offset is greater than the length of
    // the input string
    //
    if (offset_a > arg_a.length()) {    
      return Integral::EQUAL;
    }
    else {
      return Integral::GREATER;
    }
  }
  else if (offset_a > arg_a.length()) {    
    return Integral::LESSER;
  }

  // check the number of elements
  //
  if (num_elements_a < 1) {
    Error::handle(name(), L"comparePartial", Error::ARG,
		  __FILE__, __LINE__);
    return Integral::EQUAL;
  }

  // call isip_wcsncmp to get comparison result
  //
  int32 cmp = isip_wcsncmp(&value_d[arg_offset_a],
			  &(arg_a.value_d[offset_a]),
			  num_elements_a);
  
  if (cmp > 0) {
    return Integral::GREATER;
  }
  else if (cmp < 0) {
    return Integral::LESSER;
  }

  // exit gracefully
  //
  return Integral::EQUAL;
}

// method: firstStr
//
// arguments:
//  const SysString& str: (output) the substring
//  int32 start: (input) where to start looking
//
// return: int32 index within the string
//
// this method finds the first instance of str_a within the object
//
int64 SysString::firstStr(const SysString& str_a, int32 start_a) const {

  // check the arguments
  //
  if (start_a > length()) {
    return Integral::NO_POS;
  }

  if (start_a == Integral::NO_POS) {
    start_a = 0;
  }
  
  // find the string
  //
  unichar* index = isip_wcsstr(&value_d[start_a], str_a.value_d);

  if (index == (unichar*)NULL) {
    return Integral::NO_POS;
  }

  // return the position
  //
  /*
    Because the retutn tpye is a pointer  we  should use int64
   */
  return (((int64)index - (int64)value_d) / sizeof(unichar));
}

// method: lastStr
//
// arguments:
//  const SysString& str: (output) the substring
//  int32 end: (input) where to start looking
//
// return: int32 index within the string
//
// this method finds the last instance of str_a within the object
//
int32 SysString::lastStr(const SysString& str_a, int32 end_a) const {

  // length can't be less than or equal to zero
  //
  if (length() < 1) {
    return Integral::NO_POS;
  }

  // check the arguments
  //
  if ((end_a == Integral::NO_POS) || end_a >= length()) {

    if (eq(str_a)) {
      return 0;
    }
    
    end_a = length() - 1;
  }
  
  if (str_a.length() >= end_a) {
    return Integral::NO_POS;
  }

  // we need a temporary placeholder
  //
  unichar c = value_d[end_a + 1];
  value_d[end_a + 1] = (unichar)NULL;

  // loop over the elements of string
  //
  for (int32 i = (end_a - str_a.length()); i >= 0; i--) {
  
    // find the string
    //
    if (isip_wcsstr(&value_d[i], str_a.value_d) != (unichar*)NULL) {
      value_d[end_a + 1] = c;
      return i;
    }
  }

  // restore the temporary null
  //
  value_d[end_a + 1] = c;
  
  // exit ungracefully
  //
  return Integral::NO_POS;
}

// method: firstChr
//
// arguments:
//  const SysString& chrs: (input) a set of characters
//  int32 start: (input) where to start looking
//
// return: int32 index within the string
//
// this method finds the first instance of a character in chrs_a
// within the object
//
int32 SysString::firstChr(const SysString& chrs_a, int32 start_a) const {

  // check the arguments
  //
  if (start_a > length()) {
    return Integral::NO_POS;
  }
  if (start_a == Integral::NO_POS) {
    start_a = 0;
  }
  
  // find the index
  //
  for (int32 i = start_a; i < length(); i++) {
    if (isip_wcschr(chrs_a.value_d, value_d[i]) != (unichar*)NULL) {
      return i;
    }
  }

  // exit ungracefully
  //
  return Integral::NO_POS;
}

// method: lastChr
//
// arguments:
//  const SysString& chrs: (input) a set of characters
//  int32 end: (input) where to stop looking
//
// return: int32 index within the string
//
// this method finds the last instance of a character in chrs_a
// within the object
//
int32 SysString::lastChr(const SysString& chrs_a, int32 end_a) const {

  // length can't be less than or equal to zero
  //
  if (length() < 1) {
    return Integral::NO_POS;
  }

  // check the arguments
  //
  if ((end_a == Integral::NO_POS) || (end_a >= length())) {
    end_a = length() - 1;
  }

  // find the index
  //
  for (int32 i = end_a; i >= 0; i--) {
    if (isip_wcschr(chrs_a.value_d, value_d[i]) != (unichar*)NULL) {
      return i;
    }
  }

  // exit ungracefully
  //
  return Integral::NO_POS;
}

// method: firstChr
//
// arguments:
//  unichar chr: (input) a character
//  int32 start: (input) where to start looking
//
// return: int32 index within the string
//
// this method finds the first instance of a character chr_a within the object
//
int32 SysString::firstChr(unichar chr_a, int32 start_a) const {

  // length can't be less than or equal to zero
  //
  if (start_a > length()) {
    return Integral::NO_POS;
  }

  // check the arguments
  //
  if (start_a == Integral::NO_POS) {
    start_a = 0;
  }
  
  // find the index
  //
  for (int32 i = start_a; i < length(); i++) {
    if (chr_a == (unichar)value_d[i]) {
      return i;
    }
  }

  // exit ungracefully
  //
  return Integral::NO_POS;
}

// method: lastChr
//
// arguments:
//  unichar chr: (input) a character
//  int32 end: (input) where to stop looking
//
// return: int32 index within the string
//
// this method finds the last instance of a character chr_a within the object
//
int32 SysString::lastChr(unichar chr_a, int32 end_a) const {

  // length can't be less than or equal to zero
  //
  if (length() < 1) {
    return Integral::NO_POS;
  }

  // check the arguments
  //
  if ((end_a == Integral::NO_POS) || (end_a >= length())) {
    end_a = length() - 1;
  }

  // find the index
  //
  for (int32 i = end_a; i >= 0; i--) {
    if (chr_a == value_d[i]) {
      return i;
    }
  }

  // exit ungracefully
  //
  return Integral::NO_POS;
}

// method: firstNotChr
//
// arguments:
//  const SysString& chrs: (input) a set of characters
//  int32 start: (input) where to start looking
//
// return: int32 index within the string
//
// this method finds the first instance of a character not equal to a character
// within chrs_a within the object
//
int32 SysString::firstNotChr(const SysString& chrs_a, int32 start_a) const {

  // length can't be less than or equal to zero
  //
  if (start_a > length()) {
    return Integral::NO_POS;
  }

  // check the arguments
  //
  if (start_a == Integral::NO_POS) {
    start_a = 0;
  }
  
  // find the index
  //
  for (int32 i = start_a; i < length(); i++) {
    if (isip_wcschr(chrs_a.value_d, value_d[i]) == (unichar*)NULL) {
      return i;
    }
  }

  // exit ungracefully
  //
  return Integral::NO_POS;
}

// method: lastNotChr
//
// arguments:
//  const SysString& chrs: (input) a set of characters
//  int32 end: (input) where to stop looking
//
// return: int32 index within the string
//
// this method finds the last instance of a character not equal to a character
// within chrs_a within the object
//
int32 SysString::lastNotChr(const SysString& chrs_a, int32 end_a) const {

  // length can't be less than or equal to zero
  //
  if (length() < 1) {
    return Integral::NO_POS;
  }

  // check the arguments
  //
  if ((end_a == Integral::NO_POS) || (end_a >= length())) {
    end_a = length() - 1;
  }

  // find the index
  //
  for (int32 i = end_a; i >= 0; i--) {
    if (isip_wcschr(chrs_a.value_d, value_d[i]) == (unichar*)NULL) {
      return i;
    }
  }

  // exit ungracefully
  //
  return Integral::NO_POS;
}

// method: firstNotChr
//
// arguments:
//  unichar chr: (input) a character
//  int32 start: (input) where to start looking
//
// return: int32 index within the string
//
// this method finds the first instance of a character not equal to a character
// within chr_a within the object
//
int32 SysString::firstNotChr(unichar chr_a, int32 start_a) const {

  // check the arguments
  //
  if (start_a > length()) {
    return Integral::NO_POS;
  }

  if (start_a == Integral::NO_POS) {
    start_a = 0;
  }
  
  // find the index
  //
  for (int32 i = start_a; i < length(); i++) {
    if (chr_a != (unichar)value_d[i]) {
      return i;
    }
  }

  // exit ungracefully
  //
  return Integral::NO_POS;
}

// method: lastNotChr
//
// arguments:
//  unichar chr: (input) a character
//  int32 end: (input) where to stop looking
//
// return: int32 index within the string
//
// this method finds the last instance of a character not equal to a character
// within chr_a within the object
//
int32 SysString::lastNotChr(unichar chr_a, int32 end_a) const {

  // length can't be less than or equal to zero
  //
  if (length() < 1) {
    return Integral::NO_POS;
  }

  // check the arguments
  //
  if ((end_a == Integral::NO_POS) || (end_a >= length())) {
    end_a = length() - 1;
  }

  // loop over elements and find the last instance
  //
  for (int32 i = end_a; i >= 0; i--) {
    if (chr_a != value_d[i]) {
      return i;
    }
  }

  // exit ungracefully
  //
  return Integral::NO_POS;
}

// method: firstChar
//
// arguments:
//  int32 start: (input) where to start looking
//  bool8 (SysChar::*method) (void) const: (input) a global function pointer
//
// return: int32 index within the string
//
// this method finds the first instance of character specified by
// method_a within the object. this is a special method which is used
// for all the methods of the type firstAlpha, firstAlnum etc. method_a
// is a function pointer for SysChar class, which can be of the type
// isAlpha, isAlnum etc.
//
int32 SysString::firstChar(int32 start_a,
			  bool8 (SysChar::*method_a) (void) const) const {

  // declare a SysChar object
  //
  SysChar c;
  
  // check the arguments
  //
  if (start_a > length()) {
    return Integral::NO_POS;
  }
  if (start_a == Integral::NO_POS) {
    start_a = 0;
  }

  // find the index
  //
  for (int32 i = start_a; i < length(); i++) {

    // assign unichar value to the SysChar object
    //
    c.assign(value_d[i]);

    // call the specified method of SysChar
    //
    if ((c.*method_a)()) {

      // return the index
      //
      return i;
    }
  }
  
  // exit ungracefully
  //
  return Integral::NO_POS;
}

// method: firstNotChar
//
// arguments:
//  int32 start: (input) where to start looking
//  bool8 (SysChar::*method) (void) const: (input) a global function pointer
//
// return: int32 index within the string
//
// this method finds the first instance of character not specified by
// method_a within the object. this is a special method which is used
// for all the methods of the type firstNotAlpha, firstNotAlnum
// etc. method_a is a function pointer for SysChar class, which can be
// of the type isAlpha, isAlnum etc.
//
int32 SysString::firstNotChar(int32 start_a,
			     bool8 (SysChar::*method_a) (void) const) const {

  // declare a SysChar object
  //
  SysChar c;
  
  // check the arguments
  //
  if (start_a > length()) {
    return Integral::NO_POS;
  }
  if (start_a == Integral::NO_POS) {
    start_a = 0;
  }

  // find the index
  //
  for (int32 i = start_a; i < length(); i++) {

    // assign unichar value to the SysChar object
    //
    c.assign(value_d[i]);

    // call the specified method of SysChar
    //
    if (!(c.*method_a)()) {

      // return the index
      //
      return i;
    }
  }
  
  // exit ungracefully
  //
  return Integral::NO_POS;
}

// method: lastChar
//
// arguments:
//  int32 end: (input) where to stop looking
//  bool8 (SysChar::*method) (void) const: (input) a global function pointer
//
// return: int32 index within the string
//
// this method finds the last instance of character specified by
// method_a within the object. this is a special method which is used
// for all the methods of the type lastAlpha, lastAlnum etc. method_a
// is a function pointer for SysChar class, which can be of the type
// isAlpha, isAlnum etc.
//
int32 SysString::lastChar(int32 end_a,
			 bool8 (SysChar::*method_a) (void) const) const {

  // declare a SysChar object
  //
  SysChar c;

  // length can't be less than or equal to zero
  //
  if (length() < 1) {
    return Integral::NO_POS;
  }

  // check the arguments
  //  
  if ((end_a == Integral::NO_POS) || (end_a >= length())) {
    end_a = length() - 1;
  }

  // find the index
  //
  for (int32 i = end_a; i >= 0; i--) {

    // assign unichar value to the SysChar object
    //
    c.assign(value_d[i]);

    // call the specified method of SysChar
    //
    if ((c.*method_a)()) {

      // return the index
      //
      return i;
    }
  }
  
  // exit ungracefully
  //
  return Integral::NO_POS;
}

// method: lastNotChar
//
// arguments:
//  int32 end: (input) where to stop looking
//  bool8 (SysChar::*method) (void) const: (input) a global function pointer
//
// return: int32 index within the string
//
// this method finds the last instance of character not specified by
// method_a within the object. this is a special method which is used
// for all the methods of the type lastNotAlpha, lastNotAlnum etc. method_a
// is a function pointer for SysChar class, which can be of the type
// isAlpha, isAlnum etc.
//
int32 SysString::lastNotChar(int32 end_a,
			 bool8 (SysChar::*method_a) (void) const) const {

  // declare a SysChar object
  //
  SysChar c;

  // length can't be less than or equal to zero
  //
  if (length() < 1) {
    return Integral::NO_POS;
  }

  // check the arguments
  //  
  if ((end_a == Integral::NO_POS) || (end_a >= length())) {
    end_a = length() - 1;
  }

  // find the index
  //
  for (int32 i = end_a; i >= 0; i--) {

    // assign unichar value to the SysChar object
    //
    c.assign(value_d[i]);

    // call the specified method of SysChar
    //
    if (!(c.*method_a)()) {

      // return the index
      //
      return i;
    }
  }
  
  // exit ungracefully
  //
  return Integral::NO_POS;
}

// method: numEqual
//
// arguments:
//  unichar arg: (input) character to test for
//
// return: the number of characters equal to arg
//
// find the number of characters equal to arg
//
int32 SysString::numEqual(unichar arg_a) const {

  // initialize a counter
  //
  int32 i = 0;
  
  // loop through the string
  //
  for (int32 j = 0; j < length(); j++) {

    // if the character is equal, increment count
    //
    if (arg_a == value_d[j]) {
      i++;
    }
  }

  // return the number
  //
  return i;
}
