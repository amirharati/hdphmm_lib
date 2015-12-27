// file: $isip/class/math/vector/MVector/mvec_07.cc
// version: $Id: mvec_07.cc 7816 2002-02-27 20:54:30Z alphonso $
//

// isip include files
//
#include "MVectorMethods.h"
#include "MVector.h"

#ifndef ISIP_TEMPLATE_complex

// method: limit
//
// arguments:
//  MVector<TScalar, TIntegral>& this: (output) class operand
//  TIntegral min: (input) min value
//  TIntegral max: (input) max value
//  const MVector<TScalar, TIntegral>& v: (input/output) Vector operand
//
// return: a bool8 value indicating status
//
// this method limits elements of a vector to the range [min_a, max_a]
//
template<class TScalar, class TIntegral>
bool8 MVectorMethods::limit(MVector<TScalar, TIntegral>& this_a,
			      TIntegral min_a, TIntegral max_a,
			      const MVector<TScalar, TIntegral>& v_a) {

  // create space
  // 
  int32 last_index = (int32)this_a.length_d;
  
  if (!this_a.setLength(last_index, false)) {
    this_a.debug(L"this_a");    
    return Error::handle(name(), L"limit", Error::NOMEM, __FILE__, __LINE__);
  }
  
  // process vector piecewise
  // 
  for (int32 index = 0; index < last_index; index++) {
    this_a.v_d[index].limit(min_a, max_a, v_a.v_d[index]);
  }
  
  // exit gracefully
  // 
  return true;
}

// explicit instantiations
//
template bool8 
MVectorMethods::limit<ISIP_TEMPLATE_TARGET>
(MVector<ISIP_TEMPLATE_TARGET>&, ISIP_TEMPLATE_T1, ISIP_TEMPLATE_T1,
 const MVector<ISIP_TEMPLATE_TARGET>&);

// method: limitMin
//
// arguments:
//  MVector<TScalar, TIntegral>& this: (output) class operand
//  TIntegral min: (input) min value
//  const MVector<TScalar, TIntegral>& v: (input/output) Vector operand
//
// return: a bool8 value indicating status
//
// this method limits elements of a vector to the range [min_a, infinity]
//
template<class TScalar, class TIntegral>
bool8 MVectorMethods::limitMin(MVector<TScalar, TIntegral>& this_a,
				 TIntegral min_a, 
				 const MVector<TScalar, TIntegral>& v_a) {

  // create space
  // 
  int32 last_index = (int32)this_a.length_d;
  
  if (!this_a.setLength(last_index, false)) {
    this_a.debug(L"this_a");    
    return Error::handle(name(), L"limitMin", Error::NOMEM, __FILE__,__LINE__);
  }
  
  // process vector piecewise
  // 
  for (int32 index = 0; index < last_index; index++) {
    this_a.v_d[index].max(min_a, v_a.v_d[index]);
  }
  
  // exit gracefully
  // 
  return true;
}

// explicit instantiations
//
template bool8 
MVectorMethods::limitMin<ISIP_TEMPLATE_TARGET>
(MVector<ISIP_TEMPLATE_TARGET>&, ISIP_TEMPLATE_T1,
 const MVector<ISIP_TEMPLATE_TARGET>&);

// method: limitMax
//
// arguments:
//  MVector<TScalar, TIntegral>& this: (output) class operand
//  TIntegral max: (input) max value
//  const MVector<TScalar, TIntegral>& v: (input/output) Vector operand
//
// return: a bool8 value indicating status
//
// this method limits elements of a vector to the range [max_a, infinity]
//
template<class TScalar, class TIntegral>
bool8 MVectorMethods::limitMax(MVector<TScalar, TIntegral>& this_a,
				 TIntegral max_a, 
				 const MVector<TScalar, TIntegral>& v_a) {

  // create space
  // 
  int32 last_index = (int32)this_a.length_d;
  
  if (!this_a.setLength(last_index, false)) {
    this_a.debug(L"this_a");    
    return Error::handle(name(), L"limitMax", Error::NOMEM, __FILE__,__LINE__);
  }
  
  // process vector piecewise
  // 
  for (int32 index = 0; index < last_index; index++) {
    this_a.v_d[index].min(max_a, v_a.v_d[index]);
  }
  
  // exit gracefully
  // 
  return true;
}

// explicit instantiations
//
template bool8 
MVectorMethods::limitMax<ISIP_TEMPLATE_TARGET>
(MVector<ISIP_TEMPLATE_TARGET>&, ISIP_TEMPLATE_T1,
 const MVector<ISIP_TEMPLATE_TARGET>&);

// method: limitMag
//
// arguments:
//  MVector<TScalar, TIntegral>& this: (output) class operand
//  TIntegral thresh: (input) comparison threshold
//  TIntegral new: (input) output value
//  const MVector<TScalar, TIntegral>& v: (input/output) Vector operand
//
// return: a bool8 value indicating status
//
// this method limits the magnitude of elements of a vector to the
// range [min_a, max_a]
//
template<class TScalar, class TIntegral>
bool8 MVectorMethods::limitMag(MVector<TScalar, TIntegral>& this_a,
				 TIntegral thresh_a, TIntegral new_a,
				 const MVector<TScalar, TIntegral>& v_a) {

  // create space
  // 
  int32 last_index = (int32)this_a.length_d;
  
  if (!this_a.setLength(last_index, false)) {
    this_a.debug(L"this_a");    
    return Error::handle(name(), L"limitMag", Error::NOMEM, __FILE__, __LINE__);
  }
  
  // process vector piecewise
  // 
  for (int32 index = 0; index < last_index; index++) {
    this_a.v_d[index].limitMag(thresh_a, new_a, v_a.v_d[index]);
  }
  
  // exit gracefully
  // 
  return true;
}

// explicit instantiations
//
template bool8 
MVectorMethods::limitMag<ISIP_TEMPLATE_TARGET>
(MVector<ISIP_TEMPLATE_TARGET>&, ISIP_TEMPLATE_T1, ISIP_TEMPLATE_T1,
 const MVector<ISIP_TEMPLATE_TARGET>&);

// method: centerClip
//
// arguments:
//  MVector<TScalar, TIntegral>& this: (output) class operand
//  TIntegral min: (input) min value
//  TIntegral max: (input) max value
//  const MVector<TScalar, TIntegral>& v: (input/output) Vector operand
//
// return: a bool8 value indicating status
//
// this method center clips the vector, this means
// input:                           output:
// *this.v_d[index] > max           v_a[index]
// *this.v_d[index] < min           v_a[index]
// otherwise                        closest value of (min, max)
//
template<class TScalar, class TIntegral>
bool8 MVectorMethods::centerClip(MVector<TScalar, TIntegral>& this_a,
				   TIntegral min_a, TIntegral max_a,
				   const MVector<TScalar, TIntegral>& v_a) {

  // create space
  // 
  int32 last_index = (int32)this_a.length_d;
  
  if (!this_a.setLength(last_index, false)) {
    this_a.debug(L"this_a");    
    return Error::handle(name(), L"centerClip", Error::NOMEM, __FILE__, __LINE__);
  }
  
  // process vector piecewise
  // 
  for (int32 index = 0; index < last_index; index++) {
    this_a.v_d[index].centerClip(min_a, max_a, v_a.v_d[index]);
  }
  
  // exit gracefully
  // 
  return true;
}

// explicit instantiations
//

template bool8 
MVectorMethods::centerClip<ISIP_TEMPLATE_TARGET>
(MVector<ISIP_TEMPLATE_TARGET>&, ISIP_TEMPLATE_T1, ISIP_TEMPLATE_T1,
 const MVector<ISIP_TEMPLATE_TARGET>&);

#endif
