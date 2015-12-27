// file: $isip/class/math/scalar/MScalar/mscl_00.cc
// version: $Id: mscl_00.cc 10636 2007-01-26 22:18:09Z tm334 $
//

// this file contains those methods that are not inlined in the MScalar
// template, but yet, not sufficiently complicated to be placed in
// MScalarMethods.h. The functions implemented here must be in the same
// file, due to the intricacies of template support in C++.
//

// isip include files
//
#include "MScalar.h"
#include <Error.h>

//-----------------------------------------------------------------------------
//
// miscellaneous methods
//      
//-----------------------------------------------------------------------------

// method: debug
//
// arguments:
//  const unichar* msg: (input) message to print
//
// return: a bool8 value indicating status
//
template<class TIntegral, class TSize>
bool8 MScalar<TIntegral, TSize>::debug(const unichar* msg_a) const {

  // declare local variables
  //
  String output;
  String value;
  
  // dump the data
  //
  value.assign((TIntegral)value_d);
  output.debugStr(name(), msg_a, L"value_d", value);
  Console::put(output);

  // exit gracefully
  //
  return true;
}

//-----------------------------------------------------------------------------
//
// uniform random number generation
//      
//-----------------------------------------------------------------------------

// method: rand
//
// arguments:
//  Random& generator: (input) random number generator
//
// return: a random number
//
// this is the default method that should never be called.
//
template<class TIntegral, class TSize>
TIntegral MScalar<TIntegral, TSize>::rand(Random& generator_a) {
  Error::handle(name(), L"rand", Error::TEMPLATE_TYPE, __FILE__, __LINE__);
  return 0;
}

// ifdef so that the specializations will only be compiled
// for the given type.
//
#ifdef ISIP_TEMPLATE_byte8_byte8

// method: rand
//
// arguments:
//  Random& generator: (input) random number generator
//
// return: a random number represented as a byte8
//
template<>
byte8 MScalar<byte8, byte8>::rand(Random& generator_a) {
  return (value_d =
	  (byte8)(generator_a.get() * RAND_BYTE_MAX));
}

#elif defined ISIP_TEMPLATE_uint16_uint16

// method: rand
//
// arguments:
//  Random& generator: (input) random number generator
//
// return: a random number represented as a uint16
//
template<>
uint16 MScalar<uint16, uint16>::rand(Random& generator_a) {
  return (value_d =
	  (uint16)Integral::round((generator_a.get() * RAND_USHORT_MAX)));
}

#elif defined ISIP_TEMPLATE_uint32_uint32

// method: rand
//
// arguments:
//  Random& generator: (input) random number generator
//
// return: a random number represented as a uint32
//
template<>
uint32 MScalar<uint32, uint32>::rand(Random& generator_a) {
  return (value_d =
	  (uint32)Integral::round((generator_a.get() * RAND_ULONG_MAX)));
}

#elif defined ISIP_TEMPLATE_uint64_uint64

// method: rand
//
// arguments:
//  Random& generator: (input) random number generator
//
// return: a random number represented as a uint64
//
template<>
uint64 MScalar<uint64, uint64>::rand(Random& generator_a) {
  return (value_d =
	  (uint64)Integral::round((generator_a.get() * RAND_ULLONG_MAX)));
}

#elif defined ISIP_TEMPLATE_int16_int16

// method: rand
//
// arguments:
//  Random& generator: (input) random number generator
//
// return: a random number represented as a int16
//
template<>
int16 MScalar<int16, int16>::rand(Random& generator_a) {
  return (value_d =
	  (int16)Integral::round(((generator_a.get() - 0.5) *
				  2.0 * RAND_SHORT_MAX)));
}

#elif defined ISIP_TEMPLATE_int32_int32

// method: rand
//
// arguments:
//  Random& generator: (input) random number generator
//
// return: a random number represented as a int32
//
template<>
int32 MScalar<int32, int32>::rand(Random& generator_a) {
  return (value_d =
	  (int32)Integral::round(((generator_a.get() - 0.5) *
				2.0 * RAND_LONG_MAX)));
}

#elif defined ISIP_TEMPLATE_int64_int64

// method: rand
//
// arguments:
//  Random& generator: (input) random number generator
//
// return: a random number represented as a int64
//
template<>
int64 MScalar<int64, int64>::rand(Random& generator_a) {
  return (value_d =
	  (int64)Integral::round(((generator_a.get() - 0.5) *
				  2.0 * RAND_LLONG_MAX)));
}

#elif defined ISIP_TEMPLATE_float32_float32

// method: rand
//
// arguments:
//  Random& generator: (input) random number generator
//
// return: a random number represented as a float32
//
template<>
float32 MScalar<float32, float32>::rand(Random& generator_a) {
  return (value_d = (float32)(generator_a.get()));
}

#elif defined ISIP_TEMPLATE_float64_float64

// method: rand
//
// arguments:
//  Random& generator: (input) random number generator
//
// return: a random number represented as a float64
//
template<>
float64 MScalar<float64, float64>::rand(Random& generator_a) {
  return (value_d = generator_a.get());
}

#endif

// method: rand
//
// arguments:
//  TIntegral min: (input) lower bound
//  TIntegral max: (input) upper bound
//  Random& generator: (input) random number generator
//
// return: a random number
//
// this method finds a random number within the range (min, max)
//
template<class TIntegral, class TSize>
TIntegral MScalar<TIntegral, TSize>::rand(TIntegral min_a, TIntegral max_a,
					  Random& generator_a) {

  // bounds checking
  //
  if (min_a > max_a) {
    return Error::handle(name(), L"rand", Error::ARG, __FILE__, __LINE__);
  }

  // scale by a float64
  //
  return (value_d = (TIntegral)(generator_a.get() 
				* (float64)(max_a - min_a)) + min_a);
}

//-----------------------------------------------------------------------------
//
// gaussian random number generation
//      
//-----------------------------------------------------------------------------

// method: grand
//
// arguments:
//  TIntegral mean: (input) mean of the distribution
//  TIntegral stddev: (input) standard deviation
//  Random& generator: (input) random number generator
//
// return: a random number
//
// this is the default method.
//
template<class TIntegral, class TSize>
TIntegral MScalar<TIntegral, TSize>::grand(TIntegral mean_a,
					   TIntegral stddev_a,
					   Random& generator_a) {

  // return a random number
  //
  return (value_d = (TIntegral)(generator_a.get() * (float64)stddev_a +
				(float64)mean_a));
}

// ifdef so that the specializations will only be compiled
// for the given type.
//
#if defined ISIP_TEMPLATE_byte8_byte8

// method: grand
//
// arguments:
//  byte mean: (input) mean of the distribution
//  byte stddev: (input) standard deviation
//  Random& generator: (input) random number generator
//
// return: a random number represented as a byte8
//
template<>
byte8 MScalar<byte8, byte8>::grand(byte8 mean_a, byte8 stddev_a,
				 Random& generator_a) {
  // declare local variables
  //
  float64 value;

  // loop until we find a satisfactory random number
  //
  do {
    value = generator_a.get() * (float64)stddev_a + (float64)mean_a;
  } while ((value < 0) || (value > Integral::TWO_EXP8));

  // exit gracefully
  //
  return (value_d = (byte8)value);
}

#elif defined ISIP_TEMPLATE_uint16_uint16

// method: grand
//
// arguments:
//  uint16 mean: (input) mean of the distribution
//  uint16 stddev: (input) standard deviation
//  Random& generator: (input) random number generator
//
// return: a random number represented as a uint16
//
template<>
uint16 MScalar<uint16, uint16>::grand(uint16 mean_a, uint16 stddev_a,
				      Random& generator_a) {

  // declare local variables
  //
  float64 value;

  // loop until we find a satisfactory random number
  //
  do {
    value = generator_a.get() * (float64)stddev_a + (float64)mean_a;
  } while ((value < 0) || (value > Integral::TWO_EXP16));

  // exit gracefully
  //
  return (value_d = (uint16)value);
}

#elif defined ISIP_TEMPLATE_uint32_uint32

// method: grand
//
// arguments:
//  ulong mean: (input) mean of the distribution
//  uint32 stddev: (input) standard deviation
//  Random& generator: (input) random number generator
//
// return: a random number represented as a uint32
//
template<>
uint32 MScalar<uint32, uint32>::grand(uint32 mean_a, uint32 stddev_a,
				    Random& generator_a) {

  // declare local variables
  //
  float64 value;

  // loop until we find a satisfactory random number
  //
  do {
    value = generator_a.get() * (float64)stddev_a + (float64)mean_a;
  } while ((value < 0) || (value > Integral::TWO_EXP8));

  // exit gracefully
  //
  return value_d = ((uint32)value);
}

#elif defined ISIP_TEMPLATE_uint64_uint64

// method: grand
//
// arguments:
//  ullong mean: (input) mean of the distribution
//  ullong stddev: (input) standard deviation
//  Random& generator: (input) random number generator
//
// return: a random number represented as a uint64
//
template<>
uint64 MScalar<uint64, uint64>::grand(uint64 mean_a, uint64 stddev_a,
				      Random& generator_a) {

  // declare local variables
  //
  float64 value;

  // loop until we find a satisfactory random number
  //
  do {
    value = generator_a.get() * (float64)stddev_a + (float64)mean_a;
  } while ((value < 0) || (value > Integral::TWO_EXP32));

  // exit gracefully
  //
  return value_d = ((uint64)value);
}

#endif

//-----------------------------------------------------------------------------
//
// we define non-integral constants in the default constructor
//      
//-----------------------------------------------------------------------------

// constants: class name
//
template<class TIntegral, class TSize>
const String MScalar<TIntegral, TSize>::CLASS_NAME(L"MScalar");


// constants: default value
//
template<class TIntegral, class TSize>
const TIntegral MScalar<TIntegral, TSize>::DEF_VALUE(0);

// constants: default parameters
//
template<class TIntegral, class TSize>
const String MScalar<TIntegral, TSize>::DEF_PARAM(L"value");

// static instantiations: debug level
//
template<class TIntegral, class TSize>
Integral::DEBUG MScalar<TIntegral, TSize>::debug_level_d = Integral::NONE;

//-----------------------------------------------------------------------------
//
// explicit class template instantiations - must come at the end
//      
//-----------------------------------------------------------------------------

// define all pre-provided template instances
//
template class MScalar<ISIP_TEMPLATE_TARGET>;

//
// end of file

