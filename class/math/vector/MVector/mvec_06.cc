// file: $isip/class/math/vector/MVector/mvec_06.cc
// version: $Id: mvec_06.cc 7843 2002-03-05 15:12:48Z gao $
//

// isip include files
//
#include "MVectorMethods.h"
#include "MVector.h"

// method: ramp
//
// arguments:
//  MVector<TScalar, TIntegral>& this: (output) class operand
//  TIntegral offset: (input) offset to Start Ramp Function
//  TIntegral incr: (input) Increment
//
// return: a bool8 value indicating status
//
// this method uses the size of the vector and creates a ramp function
// of the form: y = incr*index + offset
//
template<class TScalar, class TIntegral>
bool8 MVectorMethods::ramp(MVector<TScalar, TIntegral>& this_a,
			     TIntegral offset_a, TIntegral incr_a) {

  // compute a ramp function
  //
  int32 last_index = (int32)this_a.length_d;
  for (int32 index = 0; index < last_index; index++) {
    this_a.v_d[index] = incr_a*(int32)index + offset_a;
  }

  // exit gracefully
  // 
  return true; 
}

// explicit instantiations
//
template bool8
MVectorMethods::ramp<ISIP_TEMPLATE_TARGET>
(MVector<ISIP_TEMPLATE_TARGET>&, ISIP_TEMPLATE_T1, ISIP_TEMPLATE_T1);

// method: ramp
//
// arguments:
//  MVector<TScalar, TIntegral>& this: (output) class operand
//  TIntegral offset: (input) offset to Start Ramp Function
//  TIntegral incr: (input) Increment
//  TIntegral end: (input) end point of function
//
// return: a bool8 value indicating status
//
// this method creates a ramp function of the form
//   y = [offset, offset+incr, ..., offset + (m * incr)] where
//   m = (end - offset) / incr;
// m is always rounded toward zero to stay inline with matlab "colon" notation.
// if m is negative (before rounding) then the output vector is emptied.
// if m == 0, the output vector will contain a single entry of [offset]
//
template<class TScalar, class TIntegral>
bool8 MVectorMethods::ramp(MVector<TScalar, TIntegral>& this_a,
			     TIntegral offset_a, TIntegral incr_a,
			     TIntegral end_a) {

#ifndef ISIP_TEMPLATE_complex
  float64 end = end_a;
  float64 offset = offset_a;
  float64 incr = incr_a;
#else
  float64 end = end_a.real();
  float64 offset = offset_a.real();
  float64 incr = incr_a.real();

  if ((end_a.imag() != 0) || (offset_a.imag() != 0) || (incr_a.imag() != 0)) {
    this_a.debug(L"this_a");    
    return Error::handle(name(), L"ramp", Error::ARG, __FILE__, __LINE__);
  }

#endif

  // verify arguments are in the range.
  //
  float64 m = (end - offset) / incr;
  if (m < 0) {
    return this_a.setLength(0);
  }
  
  // check for offset and end equal
  //
  if (m == 0) {
    this_a.setLength(1);
    this_a.v_d[0] = offset_a;
    return true;
  }
  
  // round off m toward zero
  //
  int32 m_rnd = (int32)Integral::floor(m);
  this_a.setLength(m_rnd + 1);
  
  // create sequence
  //
  for (int32 i = 0; i <= m_rnd; i++) {
    this_a.v_d[i] = (TIntegral)(incr*i + offset);
  }

  // exit gracefully
  // 
  return true; 
}

// explicit instantiations
//
template bool8
MVectorMethods::ramp<ISIP_TEMPLATE_TARGET>
(MVector<ISIP_TEMPLATE_TARGET>&, ISIP_TEMPLATE_T1, ISIP_TEMPLATE_T1,
 ISIP_TEMPLATE_T1);

// method: sum
//
// arguments:
//  const MVector<TScalar, TIntegral>& this: (output) class operand
//
// return: a TIntegral value containing the sum of the elements of the vector
//
// this method sums all elements in the vector
//
template<class TScalar, class TIntegral>
TIntegral MVectorMethods::sum(const MVector<TScalar, TIntegral>& this_a) {

  int32 last_index = (int32)this_a.length_d;
  
  TIntegral acc = 0;
  
  for (int32 index = 0; index < last_index; index++) {
    acc += (TIntegral)this_a.v_d[index];
  }
  
  // return the value
  //
  return acc; 
}

// explicit instantiations
//
template ISIP_TEMPLATE_T1
MVectorMethods::sum<ISIP_TEMPLATE_TARGET>
(const MVector<ISIP_TEMPLATE_TARGET>&);

// method: sumSquare
//
// arguments:
//  const MVector<TScalar, TIntegral>& this: (output) class operand
//
// return: a TIntegral value containing the sumSquare of the elements
// of the vector
//
// this method sumSquares all elements in the vector
//
template<class TScalar, class TIntegral>
TIntegral MVectorMethods::sumSquare(const MVector<TScalar, TIntegral>& this_a) {

  int32 last_index = (int32)this_a.length_d;
  
  TIntegral acc = 0;
  TIntegral tmp;
  
  for (int32 index = 0; index < last_index; index++) {
    tmp = (TIntegral)this_a.v_d[index];
    acc += tmp * tmp;
  }
  
  // return the value
  //
  return acc;
}

// explicit instantiations
//
template ISIP_TEMPLATE_T1
MVectorMethods::sumSquare<ISIP_TEMPLATE_TARGET>
(const MVector<ISIP_TEMPLATE_TARGET>&);

// method: mean
//
// arguments:
//  const MVector<TScalar, TIntegral>& this: (output) class operand
//
// return: a TIntegral value containing the mean of the elements of
// the vector
//
// this method computes the mean of all elements in the vector
//
template<class TScalar, class TIntegral>
TIntegral MVectorMethods::mean(const MVector<TScalar, TIntegral>& this_a) {

  int32 size = (int32)this_a.length_d;
  
  if (size <= (int32)0) {
    this_a.debug(L"this_a");    
    return Error::handle(name(), L"mean",
			 MVector<TScalar, TIntegral>::ERR_LEN,
			 __FILE__, __LINE__);
  }
  
  // return the value
  //
  return (sum(this_a) / (TIntegral)size); 
}

// explicit instantiations
//
template ISIP_TEMPLATE_T1
MVectorMethods::mean<ISIP_TEMPLATE_TARGET>
(const MVector<ISIP_TEMPLATE_TARGET>&);

// method: median
//
// arguments:
//  const MVector<TScalar, TIntegral>& this: (output) class operand
//
// return: a TIntegral value containing the median of the elements of
// the vector
//
// this method computes the median of all elements in the vector
//
template<class TScalar, class TIntegral>
TIntegral MVectorMethods::median(const MVector<TScalar, TIntegral>& this_a) {

  // get the size of the vector
  //
  int32 size = (int32)this_a.length_d;

  if (size <= (int32)0) {
    this_a.debug(L"this_a");    
    return Error::handle(name(), L"median",
			 MVector<TScalar, TIntegral>::ERR_LEN,
			 __FILE__, __LINE__);
  }
  
  // sort the input vector
  //
  MVector<TScalar, TIntegral> val_sort;
  val_sort.sort(this_a, Integral::ASCENDING);
  
  // return the value
  //  
  if (size % 2  == 0) {
    return ((val_sort((size - 1) / 2) + val_sort((size + 1) / 2)) / 2);
  }
  else {
    return (val_sort((size - 1) / 2));
  }
}

// explicit instantiations
//
template ISIP_TEMPLATE_T1
MVectorMethods::median<ISIP_TEMPLATE_TARGET>
(const MVector<ISIP_TEMPLATE_TARGET>&);

// method: rms
//
// arguments:
//  const MVector<TScalar, TIntegral>& this: (output) class operand
//
// return: a TIntegral value containing the rms of the elements of the
// vector
//
// this method computes the root mean square of all elements in the vector
//
template<class TScalar, class TIntegral>
TIntegral MVectorMethods::rms(const MVector<TScalar, TIntegral>& this_a) {

  int32 sze = (int32)this_a.length_d;
  
  if (sze <= (int32)0) {
    this_a.debug(L"this_a");    
    return Error::handle(name(), L"rms",
			 MVector<TScalar, TIntegral>::ERR_LEN,
			 __FILE__, __LINE__);
  }
  
  // compute and return the value
  //
  TScalar value((TIntegral)sumSquare(this_a) / sze);
  return value.sqrt();
}

// explicit instantiations
//
template ISIP_TEMPLATE_T1
MVectorMethods::rms<ISIP_TEMPLATE_TARGET>
(const MVector<ISIP_TEMPLATE_TARGET>&);

// method: var
//
// arguments:
//  const MVector<TScalar, TIntegral>& this: (output) class operand
//
// return: a TIntegral value containing the var of the elements of the
// vector
//
// this method computes the variance among all elements in the vector
//
template<class TScalar, class TIntegral>
TIntegral MVectorMethods::var(const MVector<TScalar, TIntegral>& this_a) {

  int32 sze = (int32)this_a.length_d;
  
  if (sze <= (int32)0) {
    this_a.debug(L"this_a");    
    return Error::handle(name(), L"var",
			 MVector<TScalar, TIntegral>::ERR_LEN,
			 __FILE__, __LINE__);
  }
  
  TIntegral mean_value = this_a.mean();
  TIntegral acc = 0;
  TIntegral sum;
  
  for (int32 index = 0; index < sze; index++) {
    sum  = (TIntegral)this_a.v_d[index] - mean_value;
    acc += sum*sum;
  }
  
#ifndef ISIP_TEMPLATE_complex

  // return the value
  //
  return (TIntegral)((float64)acc / (float64)sze);

#else

  return (TIntegral)((complexdouble)acc / (complexdouble)sze);

#endif
}

// explicit instantiations
//
template ISIP_TEMPLATE_T1
MVectorMethods::var<ISIP_TEMPLATE_TARGET>
(const MVector<ISIP_TEMPLATE_TARGET>&);

// method: stdev
//
// arguments:
//  const MVector<TScalar, TIntegral>& this: (output) class operand
//
// return: a TIntegral value containing the standard deviation of the vector
//
// this method computes the standard deviation among all elements of the vector
//
template<class TScalar, class TIntegral>
TIntegral MVectorMethods::stdev(const MVector<TScalar, TIntegral>& this_a) {

  // compute and return the value
  //
  TScalar value((TIntegral)var(this_a));
  return value.sqrt();
}

// explicit instantiations
//
template ISIP_TEMPLATE_T1
MVectorMethods::stdev<ISIP_TEMPLATE_TARGET>
(const MVector<ISIP_TEMPLATE_TARGET>&);

// method: dotProduct
//
// arguments:
//  const MVector<TScalar, TIntegral>& this: (output) class operand
//  const MVector<TScalar, TIntegral>& v: (input) Vector operand
//
// return: a TIntegral value containing the dot product <this, arg>
//
// this method computes the dot product between two vectors
//
template<class TScalar, class TIntegral>
TIntegral MVectorMethods::dotProduct(const MVector<TScalar, TIntegral>& this_a,
				     const MVector<TScalar, TIntegral>& v_a) {

  // check limits
  // 
  int32 last_index = (int32)this_a.length_d;
  
  if (last_index != (int32)v_a.length_d) {
    v_a.debug(L"v_a");    
    this_a.debug(L"this_a");    
    return Error::handle(name(), L"dotProduct",
			 MVector<TScalar, TIntegral>::ERR_LEN,
			 __FILE__, __LINE__);
  }
  
  // compute
  // 
  TIntegral acc = 0;
  
  for (int32 index = 0; index < last_index; index++) {
#ifndef ISIP_TEMPLATE_complex
    acc += (TIntegral)this_a.v_d[index] * (TIntegral)v_a.v_d[index];
#else
    // the second argument have to be conjugated for complex numbers
    //
    // Reference:
    //  S. Axler, "Linear Algebra Done Right,"
    //  Spriger-Verlag New York, USA, pp. 94, 1996
    //
    acc += (TIntegral)this_a.v_d[index].conjugate() * (TIntegral)v_a.v_d[index];
#endif    
  }
  
  // return the value
  // 
  return acc; 
}

// explicit instantiations
//
template ISIP_TEMPLATE_T1
MVectorMethods::dotProduct<ISIP_TEMPLATE_TARGET>
(const MVector<ISIP_TEMPLATE_TARGET>&, const MVector<ISIP_TEMPLATE_TARGET>&);

// method: distanceSquare
//
// arguments:
//  const MVector<TScalar, TIntegral>& this: (output) class operand
//  const MVector<TScalar, TIntegral>& v: (input) Vector operand
//
// return: a TIntegral value containing the result
//
// this method computes the square of the euclidean distance
// between two vectors.
//
template<class TScalar, class TIntegral>
TIntegral
MVectorMethods::distanceSquare(const MVector<TScalar, TIntegral>& this_a,
			       const MVector<TScalar, TIntegral>& v_a) {

  int32 last_index = (int32)this_a.length_d;
  
  if (last_index != (int32)v_a.length_d) {
    v_a.debug(L"v_a");    
    this_a.debug(L"this_a");    
    return Error::handle(name(), L"distanceSquare", Error::ARG,
                         __FILE__, __LINE__);
  }
  
  TIntegral acc = 0;
  TIntegral value;
  for (int32 index = 0; index < last_index; index++) {
    value  = (TIntegral)this_a.v_d[index] - (TIntegral)v_a.v_d[index];
    acc += value*value;
  }
  return acc;
}

// explicit instantiations
//
template ISIP_TEMPLATE_T1
MVectorMethods::distanceSquare<ISIP_TEMPLATE_TARGET>
(const MVector<ISIP_TEMPLATE_TARGET>&, const MVector<ISIP_TEMPLATE_TARGET>&);

// method: numEqual
//
// arguments:
//  const MVector<TScalar, TIntegral>& this: (output) class operand
//  TIntegral value: (input) value to check each element against
//
// return: a int32 value - the number of elements equal to value_a
//
// this method finds the number of items equal to the input item
//
template<class TScalar, class TIntegral>
int32 MVectorMethods::numEqual(const MVector<TScalar, TIntegral>& this_a,
			      TIntegral value_a) {

  // exit gracefully
  //
  return (this_a.length_d - this_a.numNotEqual(value_a)); 
}

// explicit instantiations
//
template int32
MVectorMethods::numEqual<ISIP_TEMPLATE_TARGET>
(const MVector<ISIP_TEMPLATE_TARGET>&, ISIP_TEMPLATE_T1);

// method: numNotEqual
//
// arguments:
//  const MVector<TScalar, TIntegral>& this: (input) class operand
//  TIntegral value: (input) value to check each element against
//
// return: a int32 value - the number of elements equal to value_a
//
// this method finds the number of items equal to the input item
//
template<class TScalar, class TIntegral>
int32 MVectorMethods::numNotEqual(const MVector<TScalar, TIntegral>& this_a,
				 TIntegral value_a) {

  // check each element
  // 
  int32 num_nne = (int32)0;
  int32 last_index = (int32)this_a.length_d;
  
  for (int32 index = 0; index < last_index; index++) {
    if ((TIntegral)this_a.v_d[index] != value_a) {
      num_nne++;
    }
  }
  
  // exit gracefully
  // 
  return num_nne;
}

// explicit instantiations
//
template int32
MVectorMethods::numNotEqual<ISIP_TEMPLATE_TARGET>
(const MVector<ISIP_TEMPLATE_TARGET>&, ISIP_TEMPLATE_T1);

