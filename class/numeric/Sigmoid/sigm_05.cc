// file: $isip/class/numeric/Sigmoid/sigm_05.cc
// version: $Id: sigm_05.cc 7473 2001-11-13 15:30:23Z gao $
//

// isip include files
//
#include "Sigmoid.h"

// method: computeScalar
//
// arguments:
//  TIntegral& y: (output) computed sigmoid result
//  const TIntegral x: (input) value to evaluate the sigmoid at
//
// return: bool8 value indicating status
//
// this method computes the sigmoid function:
//                      gain_d
//      y(x)  =   ----------------------------------  + yoffset_d
//                1 + e^(-slope_d * (x - xoffset_d))
//
template <class TIntegral>
bool8 Sigmoid::computeScalar(TIntegral& y_a, const TIntegral x_a) const {

  // compute the sigmoid function
  //
  y_a = (TIntegral)gain_d / (TIntegral)(1.0 + Integral::exp(-slope_d * (x_a - xoffset_d))) +
    yoffset_d;

  // exit gracefully
  //
  return true;
}

// explicit instantiations
//
template bool8
Sigmoid::computeScalar<float32>(float32&, float32) const;

template bool8
Sigmoid::computeScalar<float64>(float64&, const float64) const;

// method: computeVector
//
// arguments:
//  TVector& y: (output) computed sigmoid result
//  const TVector& x: (input) values to evaluate the sigmoid at
//
// return: bool8 value indicating status
//
// this method computes y[i] = sigmoid(x[i]):
//                            gain_d
//      y[i](x[i])  =   -------------------------------------  + yoffset_d
//                      1 + e^(-slope_d * (x[i] - xoffset_d))
//
template <class TVector, class TIntegral>
bool8 Sigmoid::computeVector(TVector& y_a, const TVector& x_a) const {

  // declare local variables
  //
  int32 length = x_a.length();
  TIntegral tmp = 0;
  
  // compute the sigmoid function for each element. it is much less efficient
  // to perform many vector operations (which loop over the vector many times)
  // than to loop over the vector once and do the calculations on each element
  // of the vector
  //
  y_a.setLength(length, false);
  for (int32 i = 0; i < length; i++) {
    compute(tmp, (TIntegral)x_a(i));
    y_a(i) = tmp;
  }

  // exit gracefully
  //
  return true;
}

// explicit instantiations
//
template bool8
Sigmoid::computeVector<VectorFloat, float32>(VectorFloat&,
					   const VectorFloat&) const;

template bool8
Sigmoid::computeVector<VectorDouble, float64>(VectorDouble&,
					     const VectorDouble&) const;
