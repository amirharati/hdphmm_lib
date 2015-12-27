// file: $isip/class/numeric/Chebyshev/cheb_05.cc
// version: $Id: cheb_05.cc 7150 2001-07-04 23:58:10Z picone $
//

// isip include files
//
#include "Chebyshev.h"

// method: compute
//
// arguments:
//  float32& output: (output) computed value
//  float32 input: (input) independent variable
//  int32 order: (input) order of the Chebyshev function
//
// return: a bool8 value indicating status
//
bool8 Chebyshev::compute(float32& output_a, float32 input_a, int32 order_a) {

  // check the order
  //
  if (order_a < 0) {
    return Error::handle(name(), L"compute", Error::ARG, __FILE__, __LINE__);
  }

  // branch on the input value
  //
  if (Integral::abs(input_a) <= 1.0) {
    output_a = Integral::cos((float32)order_a * Integral::acos(input_a));
  }
  else {
    output_a = Integral::cosh((float32)order_a * Integral::acosh(input_a));    
  }

  // exit gracefully
  //
  return true;
}

// method: compute
//
// arguments:
//  VectorFloat& output: (output) computed values
//  const VectorFloat& input: (input) independent variables
//  int32 order: (input) order of the Chebyshev function
//
// return: a bool8 value indicating status
//
bool8 Chebyshev::compute(VectorFloat& output_a,
			   const VectorFloat& input_a, int32 order_a) {

  // create space in the output vector
  //
  if (!output_a.setLength(input_a.length())) {
    return false;
  }

  // loop over all elements
  //
  int32 len = input_a.length();
  float32 tmp;
    
  for (int32 i = 0; i < len; i++) {
    if (!compute(tmp, input_a(i), order_a)) {
      return false;
    }
    output_a(i) = tmp;
  }

  // exit gracefully
  //
  return true;
}
