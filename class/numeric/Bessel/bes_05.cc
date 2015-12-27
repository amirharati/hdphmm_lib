// file: $isip/class/numeric/Bessel/bes_05.cc
// version: $Id: bes_05.cc 7149 2001-07-04 23:44:38Z picone $
//

// isip include files
//
#include "Bessel.h"

// method: compute
//
// arguments:
//  float32& output: (output) computed value
//  float32 input: (input) independent variable
//  int32 order: (input) order of the Bessel function
//  int32 nterms: (input) number of terms in the approximation
//
// return: a bool8 value indicating status
//
bool8 Bessel::compute(float32& output_a, float32 input_a,
			int32 order_a, int32 nterms_a) {

  // check the order
  //
  if (order_a != 0) {
    return Error::handle(name(), L"compute", ERR_UNSUPA, __FILE__, __LINE__);
  }
  else if (nterms_a < 0) {
    return Error::handle(name(), L"compute", Error::ARG, __FILE__, __LINE__);
  }

  // loop over all terms
  //
  output_a = 1.0;
  Float flt;
  
  for (int32 r = 1; r <= nterms_a; r++) {
    output_a += pow(pow(0.5 * input_a, r) / flt.factorial(r), 2.0);
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
//  int32 order: (input) order of the Bessel function
//  int32 nterms: (input) number of terms in the approximation
//
// return: a bool8 value indicating status
//
bool8 Bessel::compute(VectorFloat& output_a,
			const VectorFloat& input_a,
			int32 order_a, int32 nterms_a) {

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
    if (!compute(tmp, input_a(i), order_a, nterms_a)) {
      return false;
    }
    output_a(i) = tmp;
  }

  // exit gracefully
  //
  return true;
}
