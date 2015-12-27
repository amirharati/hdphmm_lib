// file: $isip/class/numeric/Bark/bark_05.cc
// version: $Id: bark_05.cc 7042 2001-06-09 03:19:15Z picone $
//

// isip include files
//
#include "Bark.h"

// method: compute
//
// arguments:
//  float32& bark: (output) equivalent bark scaled value
//  float32 freq: (input) frequency value in Hz
//
// return: a bool8 value indicating status
//
// this method maps the input data from one scale to another via a
// nonlinear transformation.
//
bool8 Bark::compute(float32& bark_a, float32 freq_a) {

  // declare local variables
  //
  float32 tmp1 = A2 * freq_a;
  float32 tmp2 = B2 * freq_a;

  // assign the value
  //
  bark_a = A1 * Integral::atan(tmp1) + B1 * Integral::atan(tmp2 * tmp2);

  // exit gracefully
  //
  return true;
}

// method: compute
//
// arguments:
//  VectorFloat& bark: (output) bark-scaled data
//  const VectorFloat& freq: (input) frequency data in Hz
//
// return: a bool8 value indicating status
//
// this method maps the freq data to the Bark scale using a nonlinear
// transformation.
//
bool8 Bark::compute(VectorFloat& bark_a, const VectorFloat& freq_a) {

  // declare local variables
  //
  int32 length = freq_a.length();
  float32 tmp;
  bool8 status = true;

  // allocate space
  //
  bark_a.setLength(length, false);

  // loop over all the data
  //
  for (int32 k = 0; k < length; k++) {
    status = compute(tmp, (float32)freq_a(k));
    bark_a(k) = tmp;
  }

  // exit gracefully
  //
  return status;
}

