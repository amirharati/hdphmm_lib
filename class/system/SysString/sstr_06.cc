// file: $isip/class/system/SysString/sstr_06.cc
// version: $Id: sstr_06.cc 9418 2004-03-10 17:11:33Z parihar $
//

// isip include files
//
#include "SysString.h"
// method: countTokens
//
// arguments:
//  unichar delim: (input) delimiter character
//
// return: the number of tokens seperated by delim
//
// find the number of tokens in the string
//
int32 SysString::countTokens(unichar delim_a) const {

  // create a string out of the delimiter character
  //
  static SysString temp(1);
  temp(0) = delim_a;
  temp(1) = (unichar)NULL;

  // call master function
  //
  return countTokens(temp);
}

// method: countTokens
//
// arguments:
//  const SysString& delims: (input) delimiter characters
//
// return: the number of tokens separated by delim
//
// find the number of tokens in the string
//
int32 SysString::countTokens(const SysString& delims_a) const {

  // initialize a counter
  //
  int32 i = 0;

  // declare local variable
  //
  int32 pos = 0;
  SysString sub;
  int32 len = length();
  
  // call tokenize method if length is greater than zero
  //
  if (len > 0) {

    // call tokenize method for the string and count tokens
    //
    while (tokenize(sub, pos, delims_a)) {
      
      // increment the counter
      //
      i++;
    }
  }
  
  // return number of tokens and exit
  //
  return i;
}

// method: countDelimiters
//
// arguments:
//  unichar delim: (input) delimiter character
//
// return: the number of delimiters seperated by delim
//
// find the number of delimiters in the string
//
int32 SysString::countDelimiters(unichar delim_a) const {

  // create a string out of the delimiter character
  //
  static SysString temp(1);
  temp(0) = delim_a;
  temp(1) = (unichar)NULL;

  // call master function
  //
  return countDelimiters(temp);
}

// method: countDelimiters
//
// arguments:
//  const SysString& delims: (input) delimiter characters
//
// return: the number of delimiters separated by delim
//
// find the number of delimiters in the string
//
int32 SysString::countDelimiters(const SysString& delims_a) const {

  // initialize a counter
  //
  int32 i = 0;

  // declare local variable
  //
  int32 len = length();
  
  // compute the no. of delimiters
  //
  for (int32 pos = 0; pos < len; pos++) {
    
    // find whether current element on string is a delimiter or not
    //
    int32 chr_pos = delims_a.firstChr(value_d[pos]);
    
    if (chr_pos != Integral::NO_POS) {
      
      // increment the counter
      //
      i++;
    }    
  }
  
  // return number of delimiters and exit
  //
  return i;
}

// method: tokenize
//
// arguments:
//  SysString& sub: (output) sub string
//  int32& pos: (output) position on string where next delimiter is
//  unichar delim: (input) delimiter 
//
// return: a bool8 value indicating status
//
// this method tokenizes the string using the delimiter (delim) and returns
// a sub string containing the string up to first delimiter position
//
// note that the delimiter position (pos) can be used recursively to tokenize
// the string into several substring depending on the number of delimiters
// present by using the output position (pos) from the first call to the
// tokenize method in subsequent calls to the method
//
bool8 SysString::tokenize(SysString& sub_a, int32& pos_a,
			    unichar delim_a) const {
    
  // create a string out of the delimiter character
  //
  static SysString temp(1);
  temp(0) = delim_a;
  temp(1) = (unichar)NULL;

  // call master function
  //
  return tokenize(sub_a, pos_a, temp);
}

// method: tokenize
//
// arguments:
//  SysString& sub: (output) sub string
//  int32& pos: (output) position on string where next delimiter is
//  const SysString delim: (input) delimiter 
//
// return: a bool8 value indicating status
//
// this method tokenizes the string using the delimiter (delim) and returns
// a sub string containing the string up to first delimiter position
//
// note that the delimiter position (pos) can be used recursively to tokenize
// the string into several substring depending on the number of delimiters
// present by using the output position (pos) from the first call to the
// tokenize method in subsequent calls to the method
//
bool8 SysString::tokenize(SysString& sub_a, int32& pos_a,
			    const SysString delim_a) const {

  // make sure the argument isn't the object
  //
  if (&sub_a == this) {
    return Error::handle(name(), L"tokenize", Error::ARG, __FILE__, __LINE__);
  }

  // clear the memory
  //
  if (!sub_a.clear(Integral::RESET)) {
    return Error::handle(name(), L"tokenize", ERR, __FILE__, __LINE__);
  }

  // make sure the initial poition is zero
  //
  if (pos_a < 0) {
    pos_a = 0;
  }
  
  // get the length of the string
  //
  int32 str_len = length();

  // check the arguments
  //
  if (pos_a >= str_len) {
    pos_a = str_len;
    return false;
  }

  // find whether current element on string is a delimiter or not
  //
  int32 chr_pos = delim_a.firstChr(value_d[pos_a]);
  
  // in case of a delimiter, skip till a non delimiter is found
  //
  if (chr_pos != Integral::NO_POS) {
    while ((chr_pos != Integral::NO_POS) && (pos_a < str_len)) {
      pos_a++;
      if (pos_a < str_len) {
	chr_pos = delim_a.firstChr(value_d[pos_a]);
      }
    }
  }

  // assign the values to output string if element on string is not a
  // delimiter
  //
  if (chr_pos == Integral::NO_POS) {
    sub_a.assign(value_d[pos_a]);
    pos_a++;

    // add elements on output string till next delimiter
    //
    if (pos_a < str_len) {
      chr_pos = delim_a.firstChr(value_d[pos_a]);
      if (chr_pos == Integral::NO_POS) {
	while ((chr_pos == Integral::NO_POS) && (pos_a < str_len)) {
	  sub_a.concat(value_d[pos_a]);
	  pos_a++;
	  chr_pos = delim_a.firstChr(value_d[pos_a]);
	}
      }
    }
  }

  // if there is no non-delimiter character on string
  //
  else {
    pos_a = str_len;
    return false;
  }

  // exit gracefully
  //
  return true;
}

// method: symbolPad
//
// arguments:
//  const SysString& symbols: (input) symbol set that needs padding
//
// return: a bool8 value indicating status
//
// this method removes all instances of chars from the beginning and
// end of buffer. This method is designed to take a string like this:
//         "<grammar> = 1|2|3 | (5 6 | 7 8);"
// and parse (with delim = "|();") to:
//        "<grammar> = 1 | 2 | 3 | ( 5 6 | 7 8 ) ;"
// The idea is to allow the second pass to come through with tokenize
// so that each "token" is isolated, which makes parsing simpler. this
// method ensures that there is a pad character on either side of
// every "symbol" character.
//
bool8 SysString::symbolPad(const SysString& symbols_a) {

  // set temp to be the current string, allocate a new larger buffer
  // for the current string
  //
  SysString temp(2*length());
  swap(temp);

  // buff_p: the pointer to the original buffer that is read from
  // fixed_buff_p: the pointer that is written to
  //
  unichar* buff_p = temp.value_d;
  unichar* fixed_buff_p = value_d;
  int32 state = STATE_PAD_NOSPACE;

  // declare local variable
  //
  SysChar c;
  
  // enter the state machine
  //
  while (*buff_p != (unichar)NULL) {

    c.assign((unichar)*buff_p);
    
    // the no-space state means that the last character was not a space
    //
    if (state == STATE_PAD_NOSPACE) {

      // a symbol needs full padding
      //
      if (symbols_a.firstChr(c) != Integral::NO_POS) {

	*fixed_buff_p++ = (unichar)SysChar::SPACEC;
	*fixed_buff_p++ = *buff_p;
	*fixed_buff_p++ = (unichar)SysChar::SPACEC;
	state = STATE_PAD_SPACE;
      }

      // a space changes state
      //
      else if (c.isSpace()) {

	*fixed_buff_p++ = (unichar)SysChar::SPACEC;
	state = STATE_PAD_SPACE;
      }

      // copy character directly
      //
      else {
	*fixed_buff_p++ = *buff_p;
      }
    }

    // space means that last character was a space
    //
    else if (state == STATE_PAD_SPACE) {
      
      // symbols only need the trailing space
      //
      if (symbols_a.firstChr(c) != Integral::NO_POS) {
	*fixed_buff_p++ = *buff_p;
	*fixed_buff_p++ = (unichar)SysChar::SPACEC;
      }

      // eat up the whitespace
      //
      else if (c.isSpace()) {

	// do nothing
	//
      }
      else {
	
	// simple character, change state
	//
	*fixed_buff_p++ = *buff_p;
	state = STATE_PAD_NOSPACE;
      }
    }

    // increment the pointer
    //
    buff_p++;
  }

  // terminate the string
  //
  *fixed_buff_p = (unichar)NULL;

  // trim the outer spaces
  //
  trim();
  
  // exit gracefully
  //
  return true;
}

// method: trim
//
// arguments: none
//
// return: a bool8 value indicating status
//
// trim all whitespace away from the beginning and end of the object
//
bool8 SysString::trim() {

  // find the position of the first non-whitespace character
  //
  int32 start = firstNotSpace();

  // find the position of the last non-whitespace character
  //
  int32 end = lastNotSpace();

  // check the case of no good characters
  //
  if ((start == Integral::NO_POS) || ((end - start) < 0)) {

    // clear the current string
    //
    clear(Integral::RESET);
  }
  else {

    // copy over the "good" part of the string
    //
    for (int32 i = start; i <= end; i++) {
      value_d[i - start] = value_d[i];
    }

    // terminate the string
    //
    value_d[end - start + 1] = (unichar)NULL;
  }
  
  // exit gracefully
  //
  return true;
}

// method: trim
//
// arguments:
//  const SysString& trim_chars: (input) set of characters to trim away
//
// return: a bool8 value indicating status
//
// trim specified characters away from the beginning and end of the object
//
bool8 SysString::trim(const SysString& trim_chars_a) {

  // find the position of the first keep-able character
  //
  int32 start = firstNotChr(trim_chars_a);

  // find the position of the last keep-able character
  //
  int32 end = lastNotChr(trim_chars_a);

  // check the case of no good characters
  //
  if ((start == Integral::NO_POS) || ((end - start) < 0)) {
    clear(Integral::RESET);
  }
  else {

    // copy over the "good" part of the string
    //
    for (int32 i = start; i <= end; i++) {
      value_d[i - start] = value_d[i];
    }

    // terminate the string
    //
    value_d[end - start + 1] = (unichar)NULL;
  }
  
  // exit gracefully
  //
  return true;
}

// method: trim
//
// arguments:
//  const unichar* trim_chars: (input) set of characters to trim away
//
// return: a bool8 value indicating status
//
// trim specified characters away from the beginning and end of the object
//
bool8 SysString::trim(const unichar* trim_chars_a) {

  // declare local variable
  //
  static SysString temp;

  // assign the trim characters
  //
  temp.assign(trim_chars_a);

  // call the master function
  //
  return trim(temp);
}

// method: trimLeft
//
// arguments: none
//
// return: a bool8 value indicating status
//
// trim all whitespace away from the begining of the object
//
bool8 SysString::trimLeft() {

  // find the position of the first non-whitespace character
  //
  int32 start = firstNotSpace();
  int32 end = length() - 1;

  // check the case of no good characters
  //
  if ((start == Integral::NO_POS) || ((end - start) < 0)) {
    clear(Integral::RESET);
  }
  else {

    // copy over the "good" part of the string
    //
    for (int32 i = start; i <= end; i++) {
      value_d[i - start] = value_d[i];
    }

    // terminate the string
    //
    value_d[end - start + 1] = (unichar)NULL;
  }
  
  // exit gracefully
  //
  return true;
}

// method: trimLeft
//
// arguments:
//  const SysString& trim_chars: (input) set of characters to trim away
//
// return: a bool8 value indicating status
//
// trim specified characters away from the begining of the object
//
bool8 SysString::trimLeft(const SysString& trim_chars_a) {

  // find the position of the last keepable character
  //
  int32 start = firstNotChr(trim_chars_a);
  int32 end = length() - 1;

  // check the case of no good characters
  //
  if ((start == Integral::NO_POS) || ((end - start) < 0)) {
    clear(Integral::RESET);
  }
  else {

    // copy over the "good" part of the string
    //
    for (int32 i = start; i <= end; i++) {
      value_d[i - start] = value_d[i];
    }

    // terminate the string
    //
    value_d[end - start + 1] = (unichar)NULL;
  }
  
  // exit gracefully
  //
  return true;
}

// method: trimLeft
//
// arguments:
//  const unichar* trim_chars: (input) set of characters to trim away
//
// return: a bool8 value indicating status
//
// trim specified characters away from the beginning of the object
//
bool8 SysString::trimLeft(const unichar* trim_chars_a) {

  // declare local variables
  //
  static SysString temp;

  // assign the trim characters
  //
  temp.assign(trim_chars_a);
  
  // call the master function
  //
  return trimLeft(temp);
}

// method: trimRight
//
// arguments: none
//
// return: a bool8 value indicating status
//
// trim all whitespace away from the end of the object
//
bool8 SysString::trimRight() {

  // declare local variables
  //
  int32 start = 0;

  // find the position of the last non-whitespace character
  //
  int32 end = lastNotSpace();

  // check the case of no good characters
  //
  if ((start == Integral::NO_POS) || ((end - start) < 0)) {
    clear(Integral::RESET);
  }
  else {

    // copy over the "good" part of the string
    //
    for (int32 i = start; i <= end; i++) {
      value_d[i - start] = value_d[i];
    }

    // terminate the string
    //
    value_d[end - start + 1] = (unichar)NULL;
  }
  
  // exit gracefully
  //
  return true;
}

// method: trimRight
//
// arguments:
//  const SysString& trim_chars: (input) set of characters to trim away
//
// return: a bool8 value indicating status
//
// trim specified characters away from the end of the object
//
bool8 SysString::trimRight(const SysString& trim_chars_a) {

  // declare local variables
  //
  int32 start = 0;

  // find the position of the last non-whitespace character
  //
  int32 end = lastNotChr(trim_chars_a);

  // check the case of no good characters
  //
  if ((start == Integral::NO_POS) || ((end - start) < 0)) {
    clear(Integral::RESET);
  }
  else {

    // copy over the "good" part of the string
    //
    for (int32 i = start; i <= end; i++) {
      value_d[i - start] = value_d[i];
    }

    // terminate the string
    //
    value_d[end - start + 1] = (unichar)NULL;
  }
  
  // exit gracefully
  //
  return true;
}

// method: trimRight
//
// arguments:
//  const unichar* trim_chars: (input) set of characters to trim away
//
// return: a bool8 value indicating status
//
// trim specified characters away from the end of the object
//
bool8 SysString::trimRight(const unichar* trim_chars_a) {

  // declare local variables
  //
  static SysString temp;

  // assign the input trim characters
  //
  temp.assign(trim_chars_a);

  // call the master function
  //
  return trimRight(temp);
}
