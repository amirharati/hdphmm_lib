// file: $isip/class/math/scalar/MScalar/mscl_05.cc
// version: $Id: mscl_05.cc 7886 2002-03-12 22:29:02Z zheng $
//

// isip include files
//
#include "MScalarMethods.h"
#include "MScalar.h"

// method: centerClip
//
// arguments:
//  MScalar<TIntegral, TSize>& this: (output) class operand
//  TIntegral min: (input) minimum number in range
//  TIntegral max: (input) maximum number in range
//  TIntegral val: (input) operand
//
// return: a TIntegral value containing the result
//
// this method center clips the value. This means:
// 
//      input:                        output:
//        val < min                     val
//        max < val                     val
//        otherwise                     closest value of {min, max}
//
// it has traditionally been used for noise reduction.
//
template<class TIntegral, class TSize>
TIntegral MScalarMethods::centerClip(MScalar<TIntegral, TSize>& this_a,
				     TIntegral min_a, TIntegral max_a,
				     TIntegral val_a) {

  // bound checking
  //
  if (min_a > max_a) {
    return Error::handle(name(), L"centerClip", Error::ARG,__FILE__,__LINE__);
  }

  // check outside region
  //
  if ((val_a >= max_a) || (val_a <= min_a)) {
    return (this_a.value_d = val_a);
  }

  // return the lower clip value if we are closer to it
  //
  else if (val_a < ((min_a + max_a) / 2)) {
    return (this_a.value_d = min_a);
  }

  // return the upper clip value
  //
  return (this_a.value_d = max_a);
}

// method: limit
//
// arguments:
//  MScalar<TIntegral, TSize>& this: (output) class operand
//  TIntegral min: (input) minimum number in range
//  TIntegral max: (input) maximum number in range
//  TIntegral val: (input) operand
//
// return: a TIntegral value containing the result
//
// this method implements a two-sided limiter:
//
//      input:                          output:
//        val < min                       min
//        val > max                       max
//        otherwise                       val
//
template<class TIntegral, class TSize>
TIntegral MScalarMethods::limit(MScalar<TIntegral, TSize>& this_a,
				TIntegral min_a, TIntegral max_a,
				TIntegral val_a) {

  // check upper bound
  //
  if (val_a > max_a) {
    return (this_a.value_d = max_a);
  }

  // check lower bound
  //
  else if (val_a < min_a) {
    return (this_a.value_d = min_a);
  }

  // return value
  //
  return (this_a.value_d = val_a);
}

// method: limitMag
//
//  arguments:
//  MScalar<TIntegral, TSize>& this: (output) class operand
//  TIntegral thresh: (input) comparison value
//  TIntegral output: (input) value to be output when the threshold is exceeded
//  TIntegral val: (input) operand
//
// return: a TIntegral value containing the result
//
// this method returns the following value:
//    
//      input:                          output:
//      -thresh < value < thresh        value
//      otherwise                       output
//
// it is useful for some signal processing applications.
//
template<class TIntegral, class TSize>
TIntegral MScalarMethods::limitMag(MScalar<TIntegral, TSize>& this_a,
				   TIntegral thresh_a, TIntegral output_a,
				   TIntegral val_a) {

  // check positive bound
  //
  if ((val_a > 0) && (val_a >= thresh_a)) {
    return (this_a.value_d = output_a);
  }

  // check negative bound
  //
  if ((val_a < 0) && (val_a <= -thresh_a)) {
    return (this_a.value_d = output_a);
  }

  // return the value
  //
  return (this_a.value_d = val_a);
}

// template specializations for unsigned types
//
#ifdef ISIP_TEMPLATE_unsigned

template<> ISIP_TEMPLATE_T0 MScalarMethods::limitMag<ISIP_TEMPLATE_TARGET>
(MScalar<ISIP_TEMPLATE_TARGET>& this_a, ISIP_TEMPLATE_T0 thresh_a,
 ISIP_TEMPLATE_T0 output_a, ISIP_TEMPLATE_T0 val_a) {

  // check positive bound
  //
  if (val_a >= thresh_a) {

    // return the value
    //
    return (this_a.value_d = output_a);
  }
  else {
    
    // return the value
    //
    return (this_a.value_d = val_a);
  }  
}

#else

// define explicit template instantations for types that aren't specialized
//
template ISIP_TEMPLATE_T0
MScalarMethods::limitMag<ISIP_TEMPLATE_TARGET> 
(MScalar<ISIP_TEMPLATE_TARGET>&, ISIP_TEMPLATE_T0, ISIP_TEMPLATE_T0, ISIP_TEMPLATE_T0);

#endif

// define explicit template instantations. note that the limitMag
// function is not placed in this list because it should only be
// instantiated for those types that are not specialized.
//
template ISIP_TEMPLATE_T0
MScalarMethods::centerClip<ISIP_TEMPLATE_TARGET> 
(MScalar<ISIP_TEMPLATE_TARGET>&, ISIP_TEMPLATE_T0, ISIP_TEMPLATE_T0,
 ISIP_TEMPLATE_T0);

template ISIP_TEMPLATE_T0
MScalarMethods::limit<ISIP_TEMPLATE_TARGET> 
(MScalar<ISIP_TEMPLATE_TARGET>&, ISIP_TEMPLATE_T0, ISIP_TEMPLATE_T0,
 ISIP_TEMPLATE_T0);
