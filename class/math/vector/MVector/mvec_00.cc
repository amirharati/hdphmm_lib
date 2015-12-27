// file: $isip/class/math/vector/MVector/mvec_00.cc
// version: $Id: mvec_00.cc 7826 2002-02-28 20:55:00Z alphonso $
//

// isip include files
//
#include "MVector.h"
#include <Console.h>
#include <SofParser.h>
#include <typeinfo>

//-----------------------------------------------------------------------------
//
// we define non-integral constants in the default constructor
//      
//-----------------------------------------------------------------------------

// constants: class name
//
template<class TScalar, class TIntegral>
const String MVector<TScalar, TIntegral>::CLASS_NAME(L"MVector");

// constants: i/o related constants
//
template<class TScalar, class TIntegral>
const String MVector<TScalar, TIntegral>::DEF_PARAM(L"value");

// constants: default value
//
template<class TScalar, class TIntegral>
const TIntegral MVector<TScalar, TIntegral>::DEF_VALUE(TScalar::DEF_VALUE);

template<class TScalar, class TIntegral>
const String MVector<TScalar, TIntegral>::DEF_DELIM_STR(L", ");

template<class TScalar, class TIntegral>
const TIntegral MVector<TScalar, TIntegral>::DEF_OFFSET((TIntegral)0);

template<class TScalar, class TIntegral>
const TIntegral MVector<TScalar, TIntegral>::DEF_INCR((TIntegral)1);

// static instantiations: memory manager
//
template<class TScalar, class TIntegral>
Integral::DEBUG MVector<TScalar, TIntegral>::debug_level_d = Integral::NONE;

//------------------------------------------------------------------------
//
// required public methods
//
//-----------------------------------------------------------------------

// method: destructor
//
// arguments: none
//
// return: none
//
// this is the default destructor for the vector template
//
template<class TScalar, class TIntegral>
MVector<TScalar, TIntegral>::~MVector() {
  
  // free memory
  // 
  if (v_d != (TScalar*)NULL) {
    delete [] v_d;
  }
  
  // reset pointers
  //
  length_d = (int32)0;
  capacity_d = (int32)0;
  v_d = (TScalar*)NULL;

  // exit gracefully
  //
}

// method: default constructor
//
// arguments: none
//
// return: none
//
// this is the default constructor for the vector template
//
template<class TScalar, class TIntegral>
MVector<TScalar, TIntegral>::MVector() {
  
  // initialize data
  // 
  length_d = (int32)0;
  capacity_d = (int32)0;
  v_d = (TScalar*)NULL;
  
  // exit gracefully
  //
}

// method: copy constructor
//
// arguments:
//  const MVector& arg: (input) vector to copy
//
// return: none
//
// this is the copy constructor
//
template<class TScalar, class TIntegral>
MVector<TScalar, TIntegral>::MVector(const MVector& arg_a) {
  
  // initialize data
  // 
  length_d = (int32)0;
  capacity_d = (int32)0;
  v_d = (TScalar*)NULL;
  
  // assign the value
  //
  assign(arg_a);
  
  // exit gracefully
  //
}

// method: eq
//
// arguments:
//  const MVector& vector: (input) operand
//
// return: a bool8 value indicating status
//
// this methods compares the elements of a vector with a scalar, return
// true if equal
//
template<class TScalar, class TIntegral>
bool8 MVector<TScalar, TIntegral>::eq(const MVector& vector_a) const {

  // if they are different lengths they are not equal
  //
  if (length_d != vector_a.length_d) {
    return false;
  }

  // if there is a difference, return false
  //
  for (int32 index = ((int32)(length_d) - 1); index >= 0; index--) {
    if (!v_d[index].eq(vector_a.v_d[index])) {
      return false;
    }
  }    

  // they must be equal
  //
  return true;
}

// method: clear
//
// arguments:
//  Integral::CMODE cmode: (input) clear mode
//
// return: a bool8 value indicating status
//
// based on the input mode, this method either resets the values of
// the class data, or releases each element, or releases memory
//
// in previous implementations, this method used to invoke setCapacity,
// since it was perceived to be a higher-level function. now, it
// sits at the bottom of the memory-management hierarchy. hence, it
// performs direct memory management for some modes.
//
template<class TScalar, class TIntegral>
bool8 MVector<TScalar, TIntegral>::clear(Integral::CMODE cmode_a) {

  // mode: RETAIN
  //  assign all elements to the default value
  //
  if (cmode_a == Integral::RETAIN) {
    return assign(TScalar::DEF_VALUE);
  }

  // mode: RESET
  //  set the length to zero, but do not alter memory
  //
  else if (cmode_a == Integral::RESET) {
    length_d = 0;
    return true;
  }

  // mode: RELEASE and FREE
  //  release memory
  //
  else {

    // free memory if the pointer is non-NULL
    //
    if (v_d != (TScalar*)NULL) {
      delete [] v_d;
      v_d = (TScalar*)NULL;
    }

    // be sure to reset length and capacity
    //
    length_d = 0;
    capacity_d = 0;

    // exit gracefully
    //
    return true;
  }
}

//-------------------------------------------------------------------------
//
// class-specific public methods:
//  extensions to required methods
//
//-------------------------------------------------------------------------

// method: debug
//
// arguments:
//  const String& name: (input) class name
//  const unichar* message: (input) information message
//
// return: a bool8 value indicating status
//
template<class TScalar, class TIntegral>
bool8 MVector<TScalar, TIntegral>::debug(const String& name_a,
					   const unichar* message_a) const {
  
  // declare local strings to hold the class data
  //
  String output;
  String value;
  String param;
  String numeric;
  
  // dump the length
  //
  value.assign((int32)length_d);
  output.debugStr(name_a, message_a, L"length_d", value);
  Console::put(output);
  
  // dump the capacity
  //
  value.assign((int32)capacity_d);
  output.debugStr(name_a, message_a, L"capacity_d", value);
  Console::put(output);
  
  // dump the values of the vector
  //
  param.assign(L"v_d");
  value.clear();
  
  output.debugStr(name_a, message_a, param, value);
  output.trimRight(L'\n');
  
  for (int32 i = 0; i < (int32)length_d; i++) {

    // get the next value as a string
    //
    numeric.assign((TIntegral)v_d[i]);

    // add the next value to this line
    //
    output.concat(numeric);

    if (i != (int32)length_d - 1) {
      output.concat(L", ");
    }
  }

  Console::put(output);

  // exit gracefully
  // 
  return true;
}

// method: constructor
//
// arguments:
//  int32 len: (input) length of new vector
//
// return: none
//
// this method constructs a vector with specified length
//
template<class TScalar, class TIntegral>
MVector<TScalar, TIntegral>::MVector(int32 len_a) {
  
  // initialize data
  // 
  length_d = (int32)0;
  capacity_d = (int32)0;
  v_d = (TScalar*)NULL;

  // set the length
  //
  if (!setLength(len_a, false)) {
    this->debug(L"this");
    Error::handle(name(), L"constructor", Error::NOMEM, __FILE__, __LINE__);
  }
  
  // exit gracefully
  //
}

// method: assign
//
// arguments:
//  TIntegral value: (input) sets all elements equal to value_a
//
// return: a bool8 value indicating status
//
// this method sets each element of the vector to the specified value
// 
template<class TScalar, class TIntegral>
bool8 MVector<TScalar, TIntegral>::assign(TIntegral value_a) {
  
  // assign each element
  // 
  int32 last_index = (int32)length_d;
  if (last_index < (int32)0) {
    return false;
  }
  
  for (int32 index = 0; index < last_index; index++) {
    v_d[index] = value_a;
  }
  
  // exit gracefully
  // 
  return true;
}

// method: assign
//
// arguments:
//  int32 length: (input) length of vector
//  TIntegral value: (input) sets all elements equal to value_a
//
// return: a bool8 value indicating status
//
// this method sets the length of the vector and then initializes each element
// to the given value
// 
template<class TScalar, class TIntegral>
bool8 MVector<TScalar, TIntegral>::assign(int32 length_a, TIntegral value_a) {
  
  // check argument
  //
  if (length_a < 0) {
    this->debug(L"this");    
    return Error::handle(name(), L"assign", Error::ARG, __FILE__, __LINE__);
  }
  
  // resize
  // 
  if (!setLength(length_a, false)) {
    this->debug(L"this");    
    return Error::handle(name(), L"assign", Error::NOMEM, __FILE__, __LINE__);
  }
  
  // assign the data
  // 
  int32 last_index = (int32)length_d;
  for (int32 index = 0; index < last_index; index++) {
    v_d[index].assign(value_a);
  }
  
  // exit gracefully
  // 
  return true;
}

// method: almostEqual
//
// arguments:
//  const MVector& vector: (input) operand
//  float64 percent: (input) *percentage* of difference allowable
//  float64 bound: (input) a lower bound on the comparison
//
// return: a bool8 value indicating status
//
template<class TScalar, class TIntegral>
bool8 MVector<TScalar, TIntegral>::almostEqual(const MVector& vector_a,
						 float64 percent_a,
						 float64 bound_a) const {
  
  // if lengths are not equal, they can't be equivalent vectors
  //
  if (vector_a.length_d != length_d) {
    return false;
  }

  for (int32 i = (int32)length_d - 1; i >= 0; i--) {
    if (!v_d[i].almostEqual(vector_a.v_d[i], percent_a, bound_a)) {
      return false;
    }
  }

  // everything checked out, return true
  //
  return true;
}

// method: almostEqual
//
// arguments:
//  TIntegral value: (input) operand
//  float64 percent: (input) *percentage* of difference allowable
//  float64 bound: (input) a lower bound on the comparison
//
// return: a bool8 value indicating status
//
// this methods checks if all the elements of the current vector are
// almostEqual the input value
//
template<class TScalar, class TIntegral>
bool8 MVector<TScalar, TIntegral>::almostEqual(TIntegral value_a,
						 float64 percent_a,
						 float64 bound_a) const {
  if ((int32)length_d == 0)
    return false;
  
  for (int32 i = (int32)length_d - 1; i >= 0; i--) {
    if (!v_d[i].almostEqual(value_a, percent_a, bound_a)) {
      return false;
    }
  }

  // everything checked out, return true
  //
  return true;
}

// method: setLength
// 
// arguments:
//  int32 length: (input) new length
//  bool8 preserve_values: (input) should we save the memory
//   
// return: a bool8 value indicating status
//
// this method sets the length, or number of valid elements
//
template<class TScalar, class TIntegral>
bool8 MVector<TScalar, TIntegral>::setLength(int32 length_a,
					       bool8 preserve_values_a) {
  
  // if length_a < 0, error
  // 
  if (length_a < 0) {
    this->debug(L"this");
    return Error::handle(name(), L"setLength", Error::ARG, __FILE__, __LINE__);
  }
  
  // if length_a <= length_d, just change length
  // 
  if (length_a <= (int32)length_d) {
    length_d = length_a;
    return true;
  }
  
  // else new length is greater than current length
  //
  else {
    
    // if new length is greater than capacity, call setCapacity
    //
    if (length_a > capacity_d) {
      if (!setCapacity(length_a, preserve_values_a)) {
	this->debug(L"this");	
	return Error::handle(name(), L"setLength", Error::NOMEM,
			     __FILE__, __LINE__);
      }
    }
    
    // for every new element clear the value
    //
    for (int32 i = (int32)length_d; i < length_a; i++) {
      v_d[i].assign(TScalar::DEF_VALUE);
    }
    
    // set new length
    // 
    length_d = length_a;
    
    // exit gracefully
    // 
    return true;
  }
}

// method: setCapacity
// 
// arguments:
//  int32 capacity: (input) new capacity
//  bool8 preserve_values: (input) flag to save memory
//   
// return: a bool8 value indicating status
//
// this method sets the length, or number of valid elements. note that
// the new capacity must always be greater than or equal to the length.
//
template<class TScalar, class TIntegral>
bool8 MVector<TScalar, TIntegral>::setCapacity(int32 capacity_a,
						 bool8 preserve_values_a) {
  
  // capacity_a < 0: error
  // 
  if (capacity_a < 0) {
    this->debug(L"this");    
    return Error::handle(name(), L"setCapacity", Error::ARG,
			 __FILE__, __LINE__);
  }
  
  // capacity_a is equal to the capacity: done
  //
  else if (capacity_a == capacity_d) {
    return true;
  }
  
  // capacity_a < length_d: error (capacity can't be less than the length)
  // 
  else if (capacity_a < (int32)length_d) {
    this->debug(L"this");    
    return Error::handle(name(), L"setCapacity", Error::ARG,
			 __FILE__, __LINE__);
  }
  
  // capacity_a == 0 (and length_d == 0): just delete memory
  //
  else if (capacity_a == 0) {
    
    // delete the old memory
    //
    if (v_d != (TScalar*)NULL) {
      delete [] v_d;
      v_d = (TScalar*)NULL;
    }
  }
    
  // capacity_a >= length_d: we will need to allocate memory and/or
  //  transfer data.
  //
  else {
    
    // allocate a new chunk of memory
    //
    TScalar* new_mem = new TScalar[capacity_a];
    if (new_mem == (TScalar*)NULL) {
      this->debug(L"this");      
      return Error::handle(name(), L"setCapacity", Error::NOMEM,
			   __FILE__, __LINE__);
    }

    // if there are valid elements and we need to preserve them
    //
    if (((int32)length_d > 0) && preserve_values_a) {
      for (int32 i = 0; i < length_d; i++) {
	new_mem[i] = v_d[i];
      }
    }
    
    // delete the old memory
    //
    if (v_d != (TScalar*)NULL) {
      delete [] v_d;
      v_d = (TScalar*)NULL;
    }
    
    // assign the pointer to the new memory
    //
    v_d = new_mem;
  }
  
  // set the new capacity
  //
  capacity_d = capacity_a;

  // exit gracefully
  //
  return true;
}

// declare classes that need to inherit MVector
//
template class MVector<ISIP_TEMPLATE_TARGET>;
