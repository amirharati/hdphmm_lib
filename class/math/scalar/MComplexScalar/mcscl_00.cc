// file: $isip/class/math/scalar/MComplexScalar/mcscl_00.cc
// version: $Id: mcscl_00.cc 10636 2007-01-26 22:18:09Z tm334 $
//

// this file contains those methods that are not inlined in the MComplexScalar
// template, but yet, not sufficiently complicated to be placed in
// MComplexScalarMethods.h. The functions implemented here must be in the same
// file, due to the intricacies of template support in C++.
//

// isip include files
//
#include "MComplexScalar.h"
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
bool8 MComplexScalar<TIntegral, TSize>::debug(const unichar* msg_a) const {

  // declare local variables
  //
  String output;
  String value;
  
  // dump the data
  //
  value.assign(this->value_d);
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
SysComplex<TIntegral>
MComplexScalar<TIntegral, TSize>::rand(Random& generator_a) {
  Error::handle(name(), L"rand", Error::TEMPLATE_TYPE, __FILE__, __LINE__);
  return 0;
}

#ifdef ISIP_TEMPLATE_int32_int32

// method: rand
//
// arguments:
//  Random& generator: (input) random number generator
//
// return: a random number represented as a complexlong
//
template<>
SysComplex<int32>
MComplexScalar<int32, int32>::rand(Random& generator_a) {

  float64 r = (generator_a.get() - 0.5) * 2.0 * RAND_LONG_MAX;
  float64 i = (generator_a.get() - 0.5) * 2.0 * RAND_LONG_MAX;
  return (this->value_d = presentValue(complexdouble(r, i)));
}

// ifdef so that the specializations will only be compiled
// for the given type.
//
#elif ISIP_TEMPLATE_float32_float32

// method: rand
//
// arguments:
//  Random& generator: (input) random number generator
//
// return: a random number represented as a complexfloat
//
template<>
SysComplex<float32>
MComplexScalar<float32, float32>::rand(Random& generator_a) {
  float32 r = (float32)generator_a.get();
  float32 i = (float32)generator_a.get();

  return (this->value_d = complexfloat(r, i));
}

#elif defined ISIP_TEMPLATE_float64_float64

// method: rand
//
// arguments:
//  Random& generator: (input) random number generator
//
// return: a random number represented as a complexdouble
//
template<>
SysComplex<float64>
MComplexScalar<float64, float64>::rand(Random& generator_a) {
  float64 r = (float64)generator_a.get();
  float64 i = (float64)generator_a.get();
  return (this->value_d = complexdouble(r, i));
}

#endif

// method: rand
//
// arguments:
//  SysComplex<TIntegral> min: (input) lower bound
//  SysComplex<TIntegral> max: (input) upper bound
//  Random& generator: (input) random number generator
//
// return: a random number
//
// this method finds a random number within the range defined by
// rectangle (min, max)
//
template<class TIntegral, class TSize>
SysComplex<TIntegral>
MComplexScalar<TIntegral, TSize>::rand(SysComplex<TIntegral> min_a,
				       SysComplex<TIntegral> max_a,
				       Random& generator_a) {

  // bounds checking
  //
  if ((min_a.real() > max_a.real()) ||
      (min_a.imag() > max_a.imag())) {
    return Error::handle(name(), L"rand", Error::ARG, __FILE__, __LINE__);
  }

  // scale by a double for real types, not for complex types
  //
  this->value_d.assign((TIntegral)(generator_a.get() * (max_a.real() - min_a.real())
			     + min_a.real()),
		 (TIntegral)(generator_a.get() * (max_a.imag() - min_a.imag())
			     + min_a.imag()));
  
  return this->value_d;
}

//-----------------------------------------------------------------------------
//
// gaussian random number generation
//      
//-----------------------------------------------------------------------------

// method: grand
//
// arguments:
//  SysComplex<TIntegral> mean: (input) mean of the distribution
//  SysComplex<TIntegral> stddev: (input) standard deviation
//  Random& generator: (input) random number generator
//
// return: a random number
//
// this method obtains a random complex number from a gaussian
// distribution. the mean is specified by a TIntegral vector, the
// variance by a TIntegral vector. for a true two-dimensional
// distribution the variance should be described by a matrix, but this
// version of the function is necessary for conformance to the
// template interface. it assumes that:
//
//   mean = [ mean_a.real() ]  covvar = [ stddev_a.real()     0 ]
//          [ mean_a.imag() ]           [   0   stddev_a.imag() ] 
//
// this creates a constraint that the distribution cannot be tilted
// away from the x or y axis. the grandComplex() function will allow
// for any covariance matrix to be specified (Varmint #334).
//

template<class TIntegral, class TSize>
SysComplex<TIntegral>
MComplexScalar<TIntegral, TSize>::grand(SysComplex<TIntegral> mean_a,
					SysComplex<TIntegral> stddev_a,
					Random& generator_a) {

  complexdouble tmp_complex(generator_a.get() *
			    stddev_a.real(),
			    generator_a.get() *
			    stddev_a.imag());
  // return a random number
  //
  return (this->value_d = this->presentValue(tmp_complex + (complexdouble)mean_a));
}

//-----------------------------------------------------------------------------
//
// we define non-integral constants in the default constructor
//      
//-----------------------------------------------------------------------------

// constants: class name
//
template<class TIntegral, class TSize>
const String MComplexScalar<TIntegral, TSize>::CLASS_NAME(L"MComplexScalar");


// constants: default value
//
template<class TIntegral, class TSize>
const MComplexScalar<TIntegral, TSize> MComplexScalar<TIntegral, TSize>::DEF_VALUE(SysComplex<TIntegral>(0,0));

// constants: default parameters
//
template<class TIntegral, class TSize>
const String MComplexScalar<TIntegral, TSize>::DEF_PARAM(L"value");

// static instantiations: debug level
//
template<class TIntegral, class TSize>
Integral::DEBUG MComplexScalar<TIntegral, TSize>::debug_level_d = Integral::NONE;

//-----------------------------------------------------------------------------
//
// explicit class template instantiations - must come at the end
//      
//-----------------------------------------------------------------------------

// define all pre-provided template instances
//
template class MComplexScalar<ISIP_TEMPLATE_TARGET>;

//
// end of file
