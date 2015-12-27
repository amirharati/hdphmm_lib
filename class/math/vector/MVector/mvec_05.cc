// file: $isip/class/math/vector/MVector/mvec_05.cc
// version: $Id: mvec_05.cc 8961 2003-01-02 20:14:26Z alphonso $
//

// isip include files
//
#include "MVectorMethods.h"
#include "MVector.h"

// method: assign
//
// arguments:
//  MVector<TScalar, TIntegral>& this: (output) class operand
//  int32 length: (input) length
//  const String* v: (input) Vector data
//
// return: a bool8 value indicating status
//
// this method creates a vector from a String vector
//
template<class TScalar, class TIntegral>
bool8 MVectorMethods::assign(MVector<TScalar, TIntegral>& this_a, 
			       int32 length_a, const String* v_a) {

  // check argument
  //
  if (length_a <= 0) {
    this_a.debug(L"this_a");    
    return Error::handle(name(), L"assign", Error::ARG, __FILE__, __LINE__);
  }
 
  // resize
  // 
  if (!this_a.setLength(length_a, false)) {
    this_a.debug(L"this_a");    
    return Error::handle(name(), L"assign", Error::NOMEM, __FILE__, __LINE__);
  }
 
  // copy the data
  //
  String obj;
  const String* ptr_cdata = v_a;

  for (int32 index = 0; index < length_a; index++) {
    if (((*ptr_cdata).length() == 0)
	|| (!this_a.v_d[index].assign((String&)*ptr_cdata++))) {
      this_a.setLength(index);
      break;
    }
  }

  if ((int32)(this_a.length_d) <= 0) {
    return false;
  }
 
  // exit gracefully
  // 
  return true;
}

// explicit instantiations
//
template bool8
MVectorMethods::assign<ISIP_TEMPLATE_TARGET>
(MVector<ISIP_TEMPLATE_TARGET>&, int32, const String*);

// method: assign
//
// arguments:
//  MVector<TScalar, TIntegral>& this: (output) class operand
//  const String& str: (input) string of data
//  unichar delim: (input) delimiter character
//
// return: a bool8 value indicating status
//
// this method creates a vector from a string using parsing
//
template<class TScalar, class TIntegral>
bool8 MVectorMethods::assign(MVector<TScalar, TIntegral>& this_a, 
			       const String& str_a, unichar delim_a) {

  // get the length of string
  //
  int32 len = str_a.length();

  if (len < 0) {
    this_a.debug(L"this_a");    
    return Error::handle(name(), L"assign", 
			 MVector<TScalar, TIntegral>::ERR_LEN, 
			 __FILE__, __LINE__);
  }

  SysChar sc(delim_a);
 
  if (!sc.isSpace()) {

    // create a string out of the delimiter character
    //
    SysString temp(3);
  
    temp(0) = delim_a;
    temp(1) = delim_a;    
    temp(2) = (unichar)NULL;

    // error in case of consequent non space delimiters
    //
    if (str_a.firstStr(temp) != Integral::NO_POS) {
      this_a.debug(L"this_a");      
      return Error::handle(name(), L"assign", Error::ARG, __FILE__, __LINE__);
    }

    // error in case of starting or end delimiters
    //
    if (len > (int32)0) {
      if ((str_a(0) == delim_a) || (str_a(len - 1) == delim_a)) {
	this_a.debug(L"this_a");
	str_a.debug(L"str");      
	return Error::handle(name(), L"assign", Error::ARG, 
			     __FILE__, __LINE__);
      }
    }
  }

  // declare a string to hold tokenized substrings
  //
  String tokens;

  // declare local variables
  //
  int32 pos = 0;
  int32 k = 0;
  int32 i = 1;

  TIntegral val;
 
  // call tokenize method if length is greater than zero
  //
  if (len > 0) {

    // call tokenize method and assign the substrings to vector
    //
    while (str_a.tokenize(tokens, pos, delim_a)) {

      tokens.trim();
      tokens.get(val);
      this_a.setLength(i);
      i++;
   
      // assign token to this_a
      //
      if (!this_a.v_d[k].assign(tokens)) {
	return false;
      }

      // increment the counter
      //
      k++;
    }
  }

  // else the string is empty
  //
  else {
    return this_a.setLength(0);
  }

  // exit gracefully
  //
  return true;
}

// explicit instantiations
//
template bool8
MVectorMethods::assign<ISIP_TEMPLATE_TARGET>
(MVector<ISIP_TEMPLATE_TARGET>&, const String&, unichar);

// method: assign
//
// arguments:
//  MVector<TScalar, TIntegral>& this: (output) class operand
//  const unichar* str: (input) string of data
//  unichar delim: (input) delimiter character
//
// return: a bool8 value indicating status
//
// this method creates a vector from a unichar string using parsing
//
template<class TScalar, class TIntegral>
bool8 MVectorMethods::assign(MVector<TScalar, TIntegral>& this_a, 
			       const unichar* str_a, unichar delim_a) {

  String temp((unichar*)str_a);
  return this_a.assign(temp, delim_a);
 
}

// explicit instantiations
//
template bool8
MVectorMethods::assign<ISIP_TEMPLATE_TARGET>
(MVector<ISIP_TEMPLATE_TARGET>&, const unichar*, unichar);

// method: get
//
// arguments:
//  const MVector<TScalar, TIntegral>& this: (input) class operand
//  String& output: (output) string of data
//  const String& delim: (input) delimiter string
//
// return: a bool8 value indicating status
//
// this method creates a string from a vector
//
template<class TScalar, class TIntegral>
bool8 MVectorMethods::get(const MVector<TScalar, TIntegral>& this_a, 
			    String& output_a, const String& delim_a) {

  // get the length of the vector
  //
  int32 last = this_a.length();

  // handle the case of a zero-length vector
  //
  if (last == 0) {
    output_a.clear();
    return true;
  }
  
  // start with the first element
  //
  this_a.v_d[0].get(output_a);

  // loop over all successive elements
  //
  for (int32 i = 1; i < last; i++) {
    output_a.concat(delim_a);
    String num;
    this_a.v_d[i].get(num);
    output_a.concat(num);
  }

  // exit gracefully
  //
  return true;
}

// explicit instantiations
//
template bool8
MVectorMethods::get<ISIP_TEMPLATE_TARGET>
(const MVector<ISIP_TEMPLATE_TARGET>&, String&, const String&);

// method: swap
//
// arguments:
//  MVector<TScalar, TIntegral>& this: (output) class operand
//  MVector<TScalar, TIntegral>& arg: (input) class operand
//
// return: a bool8 value indicating status
//
// swap out data of *this & arg in a very memory efficient manner
//
template<class TScalar, class TIntegral>
bool8 MVectorMethods::swap(MVector<TScalar, TIntegral>& this_a, 
			     MVector<TScalar, TIntegral>& arg_a) {

  // we need temporary placeholders to hold arg
  //
  int32 temp_cap = arg_a.capacity_d;
  int32 temp_len = arg_a.length_d;
  TScalar* temp_vals = arg_a.v_d;
  
  // make arg be a memory-copy of *this
  //
  arg_a.capacity_d = this_a.capacity_d;
  arg_a.length_d = this_a.length_d;
  arg_a.v_d = this_a.v_d;
  
  // make *this be a memory copy of temp (was arg)
  //
  this_a.capacity_d = temp_cap;
  this_a.length_d = temp_len;
  this_a.v_d = temp_vals;
  
  // exit gracefully
  //
  return true; 
}

// explicit instantiations
//
template bool8
MVectorMethods::swap<ISIP_TEMPLATE_TARGET>
(MVector<ISIP_TEMPLATE_TARGET>&, MVector<ISIP_TEMPLATE_TARGET>&);
