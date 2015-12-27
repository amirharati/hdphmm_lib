// file: $isip/class/numeric/Mel/mel_05.cc
// version: $Id: mel_05.cc 7042 2001-06-09 03:19:15Z picone $
//

// isip include files
//
#include "Mel.h"

// method: compute
//
// arguments:
//  float& mel: (output) mel-scaled data 
//  float freq: (input) frequency in Hz
//
// return: a boolean value indicating status
//
// this method maps the input data from one scale to another via a
// nonlinear Mel transformation, given by following equation:
//
//  mel = A * log10(1 + freq * B)
//
bool8 Mel::compute(float32& mel_a, float32 freq_a) {

  // compute the value
  //
  mel_a = A * Integral::log10(1.0 + freq_a * B);

  // exit gracefully
  //
  return true;
}

// method: compute
//
// arguments:
//  VectorFloat& mel: (output) mel-scaled data
//  const VectorFloat& freq: (input) frequency data in Hz
//
// return: a boolean value indicating status
//
// this method maps the input data from one scale to another via a
// nonlinear mel transformation
//
bool8 Mel::compute(VectorFloat& mel_a, const VectorFloat& freq_a) {
  
  // declare local variables
  //
  int32 length = freq_a.length();
  float32 tmp;
  bool8 status = true;

  // allocate space
  //
  mel_a.setLength(length, false);

  // loop over elements and call the single input / single output
  // compute method
  //
  for (int32 k = 0; k < length ; k++) {
    status = compute(tmp, (float32)freq_a(k));
    mel_a(k) = tmp;
  }

  // exit gracefully
  //
  return status;
}

