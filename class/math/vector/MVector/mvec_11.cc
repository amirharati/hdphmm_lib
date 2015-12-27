// file: $isip/class/math/vector/MVector/mvec_11.cc
// version: $Id: mvec_11.cc 7816 2002-02-27 20:54:30Z alphonso $
//

// isip include files
//
#include "MVectorMethods.h"
#include "MVector.h"

// method: pow
//
// arguments:
//  MVector<TScalar, TIntegral>& this: (output) class operand
//  const MVector<TScalar, TIntegral>& v: (input) operand
//  float64 value: (input) operand
//
// return: a bool8 value indicating status
//
// this method does a power operation of each input vector element with the
// input scalar and stores the result in this vector
//
template<class TScalar, class TIntegral>
bool8 MVectorMethods::pow(MVector<TScalar, TIntegral>& this_a,
			    const MVector<TScalar, TIntegral>& v_a,
			    float64 value_a) {

  if (!this_a.setLength((int32)v_a.length_d, false)) {
    v_a.debug(L"v_a");
    this_a.debug(L"this_a");
    return Error::handle(name(), L"pow", Error::NOMEM, __FILE__, __LINE__);
  }
  
  // loop through each element
  //
  int32 last_index = (int32)this_a.length_d;
  for (int32 index = 0; index < last_index; index++) {
    this_a.v_d[index].pow(v_a.v_d[index], (TIntegral)value_a);
  }

  // exit gracefully
  //
  return true;
}

// explicit instantiations
//
template bool8
MVectorMethods::pow<ISIP_TEMPLATE_TARGET>
(MVector<ISIP_TEMPLATE_TARGET>&, const MVector<ISIP_TEMPLATE_TARGET>&, float64);

// method: max
//
// arguments:
//  const MVector<TScalar, TIntegral>& this: (output) class operand
//  int32& max_pos: (output) position of maximum
//
// return: a TIntegral value containing the maximum value in the vector
//
// this method finds the maximum value in the vector
//
template<class TScalar, class TIntegral>
TIntegral MVectorMethods::max(const MVector<TScalar, TIntegral>& this_a,
			      int32& max_pos_a) {
  
  // check Vector dimension
  // 
  int32 last_index = (int32)this_a.length_d;
  if (last_index <= (int32)0) {
    this_a.debug(L"this_a");    
    return Error::handle(name(), L"max", Error::ARG, __FILE__, __LINE__);
  }
  
  // initialize
  // 
  max_pos_a = (int32)0;
  TIntegral max_val = (TIntegral)this_a.v_d[(int32)0];
  
  // loop over data
  // 
  for (int32 index = 0; index < last_index; index++) {
    if ((TIntegral)this_a.v_d[index] > max_val) {
      max_val = this_a.v_d[index];
      max_pos_a = index;
    }
  }
  
  // return the value
  // 
  return max_val;
}

// explicit instantiations
//
template ISIP_TEMPLATE_T1
MVectorMethods::max<ISIP_TEMPLATE_TARGET>
(const MVector<ISIP_TEMPLATE_TARGET>&, int32&);

// method: maxMag
//
// arguments:
//  const MVector<TScalar, TIntegral>& this: (output) class operand
//  int32& max_pos: (output) position of maximum
//
// return: a float64 value containing the maximum magnitude in the vector
//
// this method finds the element in the input vector whose magnitude is
// maximum amongst all elements in the vector
//
template<class TScalar, class TIntegral>
float64 MVectorMethods::maxMag(const MVector<TScalar, TIntegral>& this_a,
				 int32& max_pos_a) {
  
  // check Vector dimension
  // 
  int32 last_index = (int32)this_a.length_d;
  if (last_index <= (int32)0) {
    this_a.debug(L"this_a");
    return Error::handle(name(), L"maxMag", Error::ARG, __FILE__, __LINE__);
  }
  
  // initialize
  // 
  max_pos_a = (int32)0;
  float64 abs_val = Integral::abs((TIntegral)this_a.v_d[0]);
  float64 max_val = abs_val;
  
  // loop over data
  // 
  for (int32 index = 1; index < last_index; index++) {
    abs_val = Integral::abs((TIntegral)this_a.v_d[index]);
    if (abs_val > max_val) {
      max_val = abs_val;
      max_pos_a = index;
    }
  }
  
  // return the value
  // 
  return max_val; 
}

// explicit instantiations
//
template float64
MVectorMethods::maxMag<ISIP_TEMPLATE_TARGET>
(const MVector<ISIP_TEMPLATE_TARGET>&, int32&);

// method: min
//
// arguments:
//  const MVector<TScalar, TIntegral>& this: (output) class operand
//  int32& min_pos: (output) position of minimum
//
// return: a TIntegral value containing the minimum value in the vector
//
// this method finds the minimum value in the vector
//
template<class TScalar, class TIntegral>
TIntegral MVectorMethods::min(const MVector<TScalar, TIntegral>& this_a,
			      int32& min_pos_a) {
  
  // check Vector dimension
  // 
  int32 last_index = (int32)this_a.length_d;
  if (last_index <= (int32)0) {
    this_a.debug(L"this_a");    
    return Error::handle(name(), L"min", Error::ARG, __FILE__, __LINE__);
  }
  
  // initialize
  // 
  min_pos_a = (int32)0;
  TIntegral min_val = (TIntegral)this_a.v_d[(int32)0];
  
  // loop over data
  // 
  for (int32 index = 0; index < last_index; index++) {
    if ((TIntegral)this_a.v_d[index] < min_val) {
      min_val = this_a.v_d[index];
      min_pos_a = index;
    }
  }
  
  // return the value
  // 
  return min_val;
}

// explicit instantiations
//
template ISIP_TEMPLATE_T1
MVectorMethods::min<ISIP_TEMPLATE_TARGET>
(const MVector<ISIP_TEMPLATE_TARGET>&, int32&);

// method: minMag
//
// arguments:
//  const MVector<TScalar, TIntegral>& this: (output) class operand
//  int32& min_pos: (output) position of minimum
//
// return: a float64 value containing the minimum magnitude in the vector
//
// this method finds the element in the input vector whose magnitude is
// minimum amongst all elements in the vector
//
template<class TScalar, class TIntegral>
float64 MVectorMethods::minMag(const MVector<TScalar, TIntegral>& this_a,
				 int32& min_pos_a) {
  
  // check Vector dimension
  // 
  int32 last_index = (int32)this_a.length_d;
  if (last_index <= (int32)0) {
    this_a.debug(L"this_a");    
    return Error::handle(name(), L"minMag", Error::ARG, __FILE__, __LINE__);
  }
  
  // initialize
  // 
  min_pos_a = (int32)0;
  float64 abs_val = Integral::abs((TIntegral)this_a.v_d[0]);
  float64 min_val = abs_val;
  
  // loop over data
  // 
  for (int32 index = 1; index < last_index; index++) {
    abs_val = Integral::abs((TIntegral)this_a.v_d[index]);
    if (abs_val < min_val) {
      min_val = abs_val;
      min_pos_a = index;
    }
  }
  
  // return the value
  // 
  return min_val; 
}

// explicit instantiations
//
template float64
MVectorMethods::minMag<ISIP_TEMPLATE_TARGET>
(const MVector<ISIP_TEMPLATE_TARGET>&, int32&);

// method: memSize
//
// arguments:
//  const MVector<TScalar, TIntegral>& this: (output) class operand
//
// return: size of object
//
// this method returns the size of the object in memory
//
template<class TScalar, class TIntegral>
int32 MVectorMethods::memSize(const MVector<TScalar, TIntegral>& this_a) {

  // start with the length & capacity
  //
  int32 bytes = this_a.length_d.memSize() + this_a.capacity_d.memSize();
  
  // add each element
  //
  for (int32 i = 0; i < this_a.capacity_d; i++) {
    bytes += this_a.v_d[i].memSize();
  }
  
  // return the number
  //
  return bytes;
}

// explicit instantiations
//
template int32
MVectorMethods::memSize<ISIP_TEMPLATE_TARGET>
(const MVector<ISIP_TEMPLATE_TARGET>&);
