// file: $isip/class/math/vector/MVector/mvec_08.cc
// version: $Id: mvec_08.cc 5236 2000-10-09 01:02:03Z duncan $
//

// isip include files
//
#include "MVectorMethods.h"
#include "MVector.h"

// method: rand
//
// arguments:
//  MVector<TScalar, TIntegral>& this: (output) class operand
//  Random& generator: (input) random number generator
//
// return: a bool8 value indicating status
//
// this method initializes each element of the vector with a uniformly
// distributed random value
//
template<class TScalar, class TIntegral>
bool8 MVectorMethods::rand(MVector<TScalar, TIntegral>& this_a,
			     Random& generator_a) {

  // loop over all elements
  //
  int32 last_index = (int32)this_a.length_d;
    
  for (int32 index = 0; index < last_index; index++) {
    this_a.v_d[index].rand(generator_a);
  }
  
  // return the value
  //
  return true;
}

// explicit instantiations
//
template bool8
MVectorMethods::rand<ISIP_TEMPLATE_TARGET>
(MVector<ISIP_TEMPLATE_TARGET>&, Random&);

// method: rand
//
// arguments:
//  MVector<TScalar, TIntegral>& this: (output) class operand
//  TIntegral min: (input) min value
//  TIntegral max: (input) max value
//  Random& generator: (input) random number generator
//
// return: a bool8 value indicating status
//
// this method initializes each element of the vector with a uniformly
// distributed random value between min_a and max_a
//
template<class TScalar, class TIntegral>
bool8 MVectorMethods::rand(MVector<TScalar, TIntegral>& this_a,
			     TIntegral min_a, TIntegral max_a,
			     Random& generator_a) {

  int32 last_index = (int32)this_a.length_d;
  
  // process vector piecewise
  // 
  for (int32 index = 0; index < last_index; index++) {
    this_a.v_d[index].rand(min_a, max_a, generator_a);
  }
  
  // exit gracefully
  // 
  return true;
}

// explicit instantiations
//
template bool8 
MVectorMethods::rand<ISIP_TEMPLATE_TARGET>
(MVector<ISIP_TEMPLATE_TARGET>&, ISIP_TEMPLATE_T1, ISIP_TEMPLATE_T1, Random&);

// method: grand
//
// arguments:
//  MVector<TScalar, TIntegral>& this: (output) class operand
//  TIntegral mean: (input) mean value
//  TIntegral stdev: (input) standard deviation
//  Random& generator: (input) random number generator
//
// return: a bool8 value indicating status
//
// this method initializes each element of the vector with a uniformly
// distributed gaussian random value between min_a and max_a
//
template<class TScalar, class TIntegral>
bool8 MVectorMethods::grand(MVector<TScalar, TIntegral>& this_a,
			      TIntegral mean_a, TIntegral stdev_a,
			      Random& generator_a) {

  int32 last_index = (int32)this_a.length_d;
  
  // process vector piecewise
  // 
  for (int32 index = 0; index < last_index; index++) {
    this_a.v_d[index].grand(mean_a, stdev_a, generator_a);
  }
  
  // exit gracefully
  // 
  return true;
}

// explicit instantiations
//
template bool8 
MVectorMethods::grand<ISIP_TEMPLATE_TARGET>
(MVector<ISIP_TEMPLATE_TARGET>&, ISIP_TEMPLATE_T1, ISIP_TEMPLATE_T1, Random&);
