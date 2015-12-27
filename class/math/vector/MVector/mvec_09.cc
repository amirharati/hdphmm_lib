// file: $isip/class/math/vector/MVector/mvec_09.cc
// version: $Id: mvec_09.cc 7816 2002-02-27 20:54:30Z alphonso $
//

// isip include files
//
#include "MVectorMethods.h"
#include "MVector.h"

// method: move
//
// arguments:
//  MVector<TScalar, TIntegral>& this: (output) class operand
//  const MVector<TScalar, TIntegral>& v: (input) input Vector
//  long n: (input) number of elements to be moved
//  long i_offset: (input) index of first element in input Vector
//  long o_offset: (input) index of first element in output Vector
//
// return: a bool8 value indicating status
//
// this method moves certain number of elements from input vector to the
// current vector
//
template<class TScalar, class TIntegral>
bool8 MVectorMethods::move(MVector<TScalar, TIntegral>& this_a,
			     const MVector<TScalar, TIntegral>& v_a, int32 n_a,
			     int32 i_offset_a, int32 o_offset_a) {

  // declare local variables
  // 
  int32 num_to_move = n_a;                       // counter for moving
  int32 ind_in = i_offset_a;                     // start index in input
  int32 ind_in_end = ind_in + num_to_move;       // end index in input
  int32 ind_out = o_offset_a;                    // start index in output
  int32 ind_out_end = ind_out + num_to_move;     // end index in output
  int32 last_index = (int32)v_a.length_d;
  
  // check input and output vectors
  // 
  if ((ind_in < 0) || (ind_out < 0) || (ind_out > (int32)this_a.length_d)) {
    v_a.debug(L"v_a");    
    this_a.debug(L"this_a");    
    return Error::handle(name(), L"move", Error::ARG, __FILE__, __LINE__);
  }
  else if ((ind_out_end > (int32)this_a.length_d)) {
    
    // resize this vector
    //
    this_a.setLength(ind_out_end);
  }
    
  // subtract amount to be zeroed at the end
  // 
  if (ind_in_end > last_index) {
    num_to_move -= ind_in_end - last_index;
  }
  
  // move the data
  // 
  while (num_to_move > 0) {
    this_a.v_d[ind_out++] = (TIntegral)v_a.v_d[ind_in++];
    num_to_move--;
  }
  
  // zero padding at end if necessary
  // 
  while (ind_out < ind_out_end) {
    this_a.v_d[ind_out++] = (TIntegral)0;
  }
  
  // exit gracefully
  // 
  return true;
}

// explicit instantiations
//
template bool8 
MVectorMethods::move<ISIP_TEMPLATE_TARGET>
(MVector<ISIP_TEMPLATE_TARGET>&, const MVector<ISIP_TEMPLATE_TARGET>&,
 int32, int32, int32);

// method: shift
//
// arguments:
//  MVector<TScalar, TIntegral>& this: (output) class operand
//  int32 delta: (input) shift factor
//
// return: a bool8 value indicating status
//
// this method shifts the data in the vector according to 
//  delta > 0: x[i] = x[i-delta]
//  delta < 0: x[i] = x[i+delta]
//
template<class TScalar, class TIntegral>
bool8 MVectorMethods::shift(MVector<TScalar, TIntegral>& this_a,
			      int32 delta_a) {

  // shift the data forward and fill in the rest 0
  // 
  if (delta_a > 0) {
    int32 i = (int32)(this_a.length_d) - 1;
    int32 j = i - delta_a;
    int32 i_end = delta_a - 1;
    while (i > i_end) {
      this_a.v_d[i--] = this_a.v_d[j--];
    }
    while (i >= 0) {
      this_a.v_d[i--] = (TIntegral)0;
    }
  }
  
  // shift the data backward and fill in the rest 0
  // 
  else {
    int32 i = 0;
    int32 j = i - delta_a;
    int32 i_end = (int32)(this_a.length_d) + delta_a;
    while (i < i_end) {
      this_a.v_d[i++] = this_a.v_d[j++];
    }
    
    while (i < this_a.length_d) {
      this_a.v_d[i++] = (TIntegral)0;
    } 
  }
  
  // exit gracefully
  // 
  return true;
}

// explicit instantiations
//
template bool8 
MVectorMethods::shift<ISIP_TEMPLATE_TARGET>
(MVector<ISIP_TEMPLATE_TARGET>&, int32);

// method: concat
//
// arguments:
//  MVector<TScalar, TIntegral>& this: (output) class operand
//  const MVector<TScalar, TIntegral>& v: (input) input Vector
//
// return: a bool8 value indicating status
//
// this method concatenates v_a to the end of "this"
//
template<class TScalar, class TIntegral>
bool8 MVectorMethods::concat(MVector<TScalar, TIntegral>& this_a,
			       const MVector<TScalar, TIntegral>& v_a) {
  
  // declare local variables
  // 
  int32 output_index = (int32)this_a.length_d;
  int32 last_index = (int32)v_a.length_d;
  int32 index;
  
  // resize (we must preserve elements)
  // 
  if (!this_a.setLength(this_a.length_d + v_a.length_d)) {
    v_a.debug(L"v_a");
    this_a.debug(L"this_a");    
    return Error::handle(name(), L"concat", Error::NOMEM, __FILE__, __LINE__);
  }
  
  // copy the data
  // 
  for (index = 0; index < last_index; index++) {
    this_a.v_d[output_index++] = v_a.v_d[index];
  }
  
  // exit gracefully
  // 
  return true;
}

// explicit instantiations
//
template bool8 
MVectorMethods::concat<ISIP_TEMPLATE_TARGET>
(MVector<ISIP_TEMPLATE_TARGET>&, const MVector<ISIP_TEMPLATE_TARGET>&);

// method: concat
//
// arguments:
//  MVector<TScalar, TIntegral>& this: (output) class operand
//  const MVector<TScalar, TIntegral>& v1: (input) input Vector
//  const MVector<TScalar, TIntegral>& v2: (input) operand
//
// return: a bool8 value indicating status
//
// this method concatenates v2 to v1 and stored the result in "this".
//
template<class TScalar, class TIntegral>
bool8 MVectorMethods::concat(MVector<TScalar, TIntegral>& this_a,
			       const MVector<TScalar, TIntegral>& v1_a,
			       const MVector<TScalar, TIntegral>& v2_a) {
  
  // make sure the length is great enough for both
  //
  if (!this_a.setLength(v1_a.length_d + v2_a.length_d, false)) {
    v1_a.debug(L"v1_a");
    v2_a.debug(L"v2_a");        
    this_a.debug(L"this_a");
    return Error::handle(name(), L"concat", Error::NOMEM, __FILE__, __LINE__);
  }
  this_a.setLength(0);
  
  // assign the first vector
  //
  if (!this_a.assign(v1_a)) {
    v1_a.debug(L"v1_a");
    v2_a.debug(L"v2_a");    
    this_a.debug(L"this_a");    
    return Error::handle(name(), L"concat", MVector<TScalar,TIntegral>::ERR,
			 __FILE__, __LINE__);
  }
  
  // call the master function to concatenate
  // 
  return this_a.concat(v2_a);
}

// explicit instantiations
//
template bool8 
MVectorMethods::concat<ISIP_TEMPLATE_TARGET>
(MVector<ISIP_TEMPLATE_TARGET>&, const MVector<ISIP_TEMPLATE_TARGET>&,
 const MVector<ISIP_TEMPLATE_TARGET>&);

// method: shift
//
// arguments:
//  MVector<TScalar, TIntegral>& this: (output) class operand
//  const MVector<TScalar, TIntegral>& v: (input) source vector
//  int32 delta: (input) shift factor
//
// return: a bool8 value indicating status
//
// this methods shifts the position of the elements of the vector
// if delta_a > 0: x[i] = x[i-delta], if delta_a < 0: x[i] = x[i+delta]
//
template<class TScalar, class TIntegral>
bool8 MVectorMethods::shift(MVector<TScalar, TIntegral>& this_a,
			      const MVector<TScalar, TIntegral>& v_a,
			      int32 delta_a) {

  // create new space
  // 
  if (!this_a.setLength((int32)v_a.length_d, false)) {
    return false;
  }
  
  // shift the data forward and fill in the rest 0
  // 
  if (delta_a > 0) {
    int32 i = (int32)this_a.length_d - 1;
    int32 j = i - delta_a;
    int32 i_end = delta_a - 1;
    while (i > i_end) {
      this_a.v_d[i--] = v_a.v_d[j--];
    }

    while (i >= 0) {
      this_a.v_d[i--] = (TIntegral)0;
    }
  }
  
  // shift the data backward and fill in the rest 0
  // 
  else {
    int32 i = 0;
    int32 j = i - delta_a;
    int32 i_end = (int32)this_a.length_d + delta_a;
    while (i < i_end) {
      this_a.v_d[i++] = v_a.v_d[j++];
    }
    
    while (i < this_a.length_d) {
      this_a.v_d[i++] = (TIntegral)0;
    }
  }
  
  // exit gracefully
  // 
  return true;
}

// explicit instantiations
//
template bool8 
MVectorMethods::shift<ISIP_TEMPLATE_TARGET>
(MVector<ISIP_TEMPLATE_TARGET>&, const MVector<ISIP_TEMPLATE_TARGET>&, int32);

// method: deleteRange
//
// arguments:
//  MVector<TScalar, TIntegral>& this: (output) class operand
//  const MVector<TScalar, TIntegral>& v: (input) input Vector
//  int32 offset: (input) index of first element in the input vector
//  int32 num_elements: (input) number of elements to be moved
//
// return: a bool8 value indicating status
//
// delete a range of elements from the current vector
//
template<class TScalar, class TIntegral>
bool8 MVectorMethods::deleteRange(MVector<TScalar, TIntegral>& this_a,
				    const MVector<TScalar, TIntegral>& v_a,
				    int32 offset_a,
				    int32 num_elements_a) {

  // declare local variables
  //
  int32 len_old = v_a.length();
  int32 len_new = len_old - num_elements_a;

  // check arguments
  //
  if (num_elements_a == 0) {
    return true;
  }
  else if (((offset_a < 0) || (offset_a >= len_old)) ||
	   ((num_elements_a < 0) ||
	    ((offset_a + num_elements_a) > len_old))) {
    v_a.debug(L"v_a");    
    this_a.debug(L"this_a");    
    return Error::handle(name(), L"deleteRange", Error::ARG, __FILE__, __LINE__);
  }

  if (&this_a != &v_a) {

    // resize "this"
    //
    this_a.setLength(len_new, false);

    // copy the first chunk
    //
    this_a.move(v_a, offset_a, 0, 0);

    // copy the second chunk
    //
    return this_a.move(v_a, len_old - offset_a - num_elements_a,
		     offset_a + num_elements_a, offset_a);
  }
  else {

    // copy the second chunk
    //
    if (!this_a.move(v_a, len_old - offset_a - num_elements_a,
		     offset_a + num_elements_a, offset_a)) {
      
      // exit gracefully
      //
      return false;
    }

    // resize "this"
    //
    return this_a.setLength(len_new, true);
  }
}

// explicit instantiations
//
template bool8 
MVectorMethods::deleteRange<ISIP_TEMPLATE_TARGET>
(MVector<ISIP_TEMPLATE_TARGET>&, const MVector<ISIP_TEMPLATE_TARGET>&,
 int32, int32);

// method: setRange
//
// arguments:
//  MVector<TScalar, TIntegral>& this: (output) class operand
//  int32 offset: (input) index of first element in the input vector
//  int32 num_elements: (input) number of elements to be moved
//  TIntegral value: (input) inserted value
//
// return: a bool8 value indicating status
//
// set a range of elements to the current vector
//
template<class TScalar, class TIntegral>
bool8 MVectorMethods::setRange(MVector<TScalar, TIntegral>& this_a,
				 int32 offset_a, int32 num_elements_a, 
				 TIntegral value_a) {

  // declare local variables
  //
  int32 len = this_a.length();

  // check arguments
  //
  if (num_elements_a == 0) {
    return true;
  }
  else if (((offset_a < 0) || (offset_a >= len)) ||
	   ((num_elements_a < 0) ||
	    ((offset_a + num_elements_a) > len))) {    
    this_a.debug(L"this_a");    
    return Error::handle(name(), L"setRange", Error::ARG, __FILE__, __LINE__);
  }

  // assign each element
  //
  for (int32 i = offset_a; i < (offset_a + num_elements_a); i++) {
    if (!this_a.v_d[i].assign(value_a)) {
      return false;
    }
  }

  // exit gracefully
  //
  return true;
}

// explicit instantiations
//
template bool8 
MVectorMethods::setRange<ISIP_TEMPLATE_TARGET>
(MVector<ISIP_TEMPLATE_TARGET>&, int32, int32, ISIP_TEMPLATE_T1);
