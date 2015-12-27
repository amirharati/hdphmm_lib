// file: $isip/class/numeric/Sigmoid/sigm_06.cc
// version: $Id: sigm_06.cc 6925 2001-05-03 18:21:56Z srivasta $
//

// isip include files
//
#include "Sigmoid.h"

// method: derivativeScalar
//
// arguments:
//  TIntegral& dydx: (output) computed result
//  const TIntegral x: (input) value to evaluate the sigmoid derivative at
//
// return: bool8 value indicating status
//
// this method computes the derivative of the sigmoid w.r.t. x evaluated
// at the input value
//
//   dy        gain_d * slope_d * e^(-slope_d * (x - xoffset_d))
//   --(x)  = --------------------------------------------------
//   dx           (1 + e^(-slope_d * (x - xoffset_d)))^2
//
template <class TIntegral>
bool8 Sigmoid::derivativeScalar(TIntegral& dydx_a,
				  const TIntegral x_a) const {

  // compute the derivative function
  //
  float64 exponent = Integral::exp(-slope_d * (x_a - xoffset_d));
  float64 sum = 1.0 + exponent;

  // we use doubles here to try to maintain stability in the
  // numbers since exponentials can quickly grow large
  //
  dydx_a = (TIntegral)(exponent / sum * slope_d / sum * gain_d);

  // exit gracefully
  //
  return true;
}

// explicit instantiations
//
template bool8
Sigmoid::derivativeScalar<float32>(float32&, const float32) const;

template bool8
Sigmoid::derivativeScalar<float64>(float64&, const float64) const;

// method: derivativeVector
//
// arguments:
//  TVector& dydx: (output) computed result
//  const TVector& x: (input) value to evaluate the sigmoid derivative at
//
// return: bool8 value indicating status
//
// this method computes y[i] = dy/dx(x[i]):
//
//   dy           gain_d * slope_d * e^(-slope_d * (x[i] - xoffset_d))
//   --(x[i])  = -----------------------------------------------------
//   dx              (1 + e^(-slope_d * (x[i] - xoffset_d)))^2
//
template <class TVector, class TIntegral>
bool8 Sigmoid::derivativeVector(TVector& dydx_a, const TVector& x_a) const {

  // declare local variables
  //
  int32 length = x_a.length();
  TIntegral tmp = 0;
  
  // compute the sigmoid function for each element. it is much less efficient
  // to perform many vector operations (which loop over the vector many times)
  // than to loop over the vector once and do the calculations on each element
  // of the vector
  //
  dydx_a.setLength(length, false);
  for (int32 i = 0; i < length; i++) {
    derivative(tmp, (TIntegral)x_a(i));
    dydx_a(i) = tmp;
  }

  // exit gracefully
  //
  return true;
}

// explicit instantiations
//
template bool8
Sigmoid::derivativeVector<VectorFloat, float32>(VectorFloat&,
					      const VectorFloat&) const;

template bool8
Sigmoid::derivativeVector<VectorDouble, float64>(VectorDouble&,
						const VectorDouble&) const;

// method: derivativeGainScalar
//
// arguments:
//  TIntegral& dydgain: (output) computed result
//  const TIntegral x: (input) value to evaluate the sigmoid derivative at
//
// return: bool8 value indicating status
//
// this method computes the derivative of the sigmoid w.r.t. 'gain' evaluated
// at the input value
//
//     dy                        1
//     -- (x)  =  ---------------------------------
//   dgain       1 + e^(-slope_d * (x - xoffset_d))
//
template <class TIntegral>
bool8 Sigmoid::derivativeGainScalar(TIntegral& dydgain_a,
				      const TIntegral x_a) const {

  // compute the derivative function
  //
  dydgain_a = 1.0 / (1.0 + Integral::exp(-slope_d * (x_a - xoffset_d)));

  // exit gracefully
  //  
  return true;
}

// explicit instantiations
//
template bool8
Sigmoid::derivativeGainScalar<float32>(float32&, const float32) const;

template bool8
Sigmoid::derivativeGainScalar<float64>(float64&, const float64) const;

// method: derivativeGainVector
//
// arguments:
//  TVector& dydgain: (output) computed result
//  const TVector& x: (input) value to evaluate the sigmoid derivative at
//
// return: bool8 value indicating status
//
// this method computes y[i] = dy/dgain(x[i]):
//
//     dy                             1
//     -- (x[i])  =   ----------------------------------
//   dgain            1 + e^(-slope_d * (x - xoffset_d))
//
template <class TVector, class TIntegral>
bool8 Sigmoid::derivativeGainVector(TVector& dydgain_a,
				      const TVector& x_a) const {
  
  // declare local variables
  //
  int32 length = x_a.length();
  TIntegral tmp = 0;
  
  // compute the sigmoid function for each element. it is much less efficient
  // to perform many vector operations (which loop over the vector many times)
  // than to loop over the vector once and do the calculations on each element
  // of the vector
  //
  dydgain_a.setLength(length, false);
  for (int32 i = 0; i < length; i++) {
    derivativeGain(tmp, (TIntegral)x_a(i));
    dydgain_a(i) = tmp;
  }

  // exit gracefully
  //
  return true;
}

// explicit instantiations
//
template bool8
Sigmoid::derivativeGainVector<VectorFloat, float32>(VectorFloat&,
						  const VectorFloat&) const;

template bool8
Sigmoid::derivativeGainVector<VectorDouble, float64>(VectorDouble&,
						    const VectorDouble&) const;

// method: derivativeSlopeScalar
//
// arguments:
//  TIntegral& dydslope: (output) computed result
//  const TIntegral x: (input) value to evaluate the sigmoid derivative at
//
// return: bool8 value indicating status
//
// this method computes the derivative of the sigmoid w.r.t. 'slope' evaluated
// at the input value
//
//     dy        gain_d * (x - xoffset_d) * e^(-slope_d * (x - xoffset_d))
//     -- (x)  = ---------------------------------------------------------
//   dslope               (1 + e^(-slope_d * (x - xoffset_d)))^2
//
template <class TIntegral>
bool8 Sigmoid::derivativeSlopeScalar(TIntegral& dydslope_a,
				       const TIntegral x_a) const {

  // compute the derivative function
  //
  float64 exponent = Integral::exp(-slope_d * (x_a - xoffset_d));
  float64 sum = 1.0 + exponent;

  // we use doubles here to try to maintain stability in the
  // numbers since exponentials can quickly grow large
  //
  dydslope_a = exponent / sum * (x_a - xoffset_d) / sum * gain_d;

  // exit gracefully
  //
  return true;
}

// explicit instantiations
//
template bool8
Sigmoid::derivativeSlopeScalar<float32>(float32&, const float32) const;

template bool8
Sigmoid::derivativeSlopeScalar<float64>(float64&, const float64) const;

// method: derivativeSlopeVector
//
// arguments:
//  TVector& dydslope: (output) computed result
//  const TVector& x: (input) value to evaluate the sigmoid derivative at
//
// return: bool8 value indicating status
//
// this method computes y[i] = dy/dslope(x[i]):
//
//     dy           gain_d * (x[i]-xoffset_d) * e^(-slope_d*(x[i]-xoffset_d))
//     -- (x[i])  = ---------------------------------------------------------
//   dslope               (1 + e^(-slope_d * (x[i] - xoffset_d)))^2
//
template <class TVector, class TIntegral>
bool8 Sigmoid::derivativeSlopeVector(TVector& dydslope_a,
				       const TVector& x_a) const {

  // declare local variables
  //
  int32 length = x_a.length();
  TIntegral tmp = 0;
  
  // compute the sigmoid function for each element. it is much less efficient
  // to perform many vector operations (which loop over the vector many times)
  // than to loop over the vector once and do the calculations on each element
  // of the vector
  //
  dydslope_a.setLength(length, false);
  for (int32 i = 0; i < length; i++) {
    derivativeSlope(tmp, (TIntegral)x_a(i));
    dydslope_a(i) = tmp;
  }

  // exit gracefully
  //
  return true;
}

// explicit instantiations
//
template bool8
Sigmoid::derivativeSlopeVector<VectorFloat, float32>(VectorFloat&,
						   const VectorFloat&) const;

template bool8
Sigmoid::derivativeSlopeVector<VectorDouble, float64>(VectorDouble&,
						     const VectorDouble&)const;

// method: derivativeXOffsetScalar
//
// arguments:
//  TIntegral& dydxoffset: (output) computed result
//  const TIntegral x: (input) value to evaluate the sigmoid derivative at
//
// return: bool8 value indicating status
//
// this method computes the derivative of the sigmoid w.r.t. 'xoffset'
// evaluated at the input value
//
//   dy        -gain_d * slope_d * e^(-slope_d * (x - xoffset_d))
//   --(x)  = --------------------------------------------------
//   dx           (1 + e^(-slope_d * (x - xoffset_d)))^2
//
template <class TIntegral>
bool8 Sigmoid::derivativeXOffsetScalar(TIntegral& dydxoffset_a,
					 const TIntegral x_a) const {

  // compute the derivative function
  //
  float64 exponent = Integral::exp(-slope_d * (x_a - xoffset_d));
  float64 sum = 1.0 + exponent;

  // we use doubles here to try to maintain stability in the
  // numbers since exponentials can quickly grow large
  //
  dydxoffset_a = (TIntegral)(-exponent / sum * slope_d / sum * gain_d);

  // exit gracefully
  //
  return true;
}

// explicit instantiations
//
template bool8
Sigmoid::derivativeXOffsetScalar<float32>(float32&, const float32) const;

template bool8
Sigmoid::derivativeXOffsetScalar<float64>(float64&, const float64) const;

// method: derivativeXOffsetVector
//
// arguments:
//  TVector& dydxoffset: (output) computed result
//  const TVector& x: (input) value to evaluate the sigmoid derivative at
//
// return: bool8 value indicating status
//
// this method computes y[i] = dy/dxoffset(x[i]):
//
//   dy           -gain_d * slope_d * e^(-slope_d * (x[i] - xoffset_d))
//   --(x[i])  = -----------------------------------------------------
//   dx              (1 + e^(-slope_d * (x[i] - xoffset_d)))^2
//
template <class TVector, class TIntegral>
bool8 Sigmoid::derivativeXOffsetVector(TVector& dydxoffset_a,
					 const TVector& x_a) const {

  // declare local variables
  //
  int32 length = x_a.length();
  TIntegral tmp = 0;
  
  // compute the sigmoid function for each element. it is much less efficient
  // to perform many vector operations (which loop over the vector many times)
  // than to loop over the vector once and do the calculations on each element
  // of the vector
  //
  dydxoffset_a.setLength(length, false);
  for (int32 i = 0; i < length; i++) {
    derivativeXOffset(tmp, (TIntegral)x_a(i));
    dydxoffset_a(i) = tmp;
  }

  // exit gracefully
  //
  return true;
}

// explicit instantiations
//
template bool8
Sigmoid::derivativeXOffsetVector<VectorFloat, float32>(VectorFloat&,
						     const VectorFloat&) const;

template bool8
Sigmoid::derivativeXOffsetVector<VectorDouble, float64>(VectorDouble&,
						    const VectorDouble&) const;

// method: derivativeYOffsetScalar
//
// arguments:
//  TIntegral& dydyoffset: (output) computed result
//  const TIntegral x: (input) value to evaluate the sigmoid derivative at
//
// return: bool8 value indicating status
//
// this method computes the derivative of the sigmoid w.r.t. 'yoffset'
// evaluated at the input value
//
//     dy        
//     -- (x)  = 1.0
//   dyoffset     
//
template <class TIntegral>
bool8 Sigmoid::derivativeYOffsetScalar(TIntegral& dydyoffset_a,
					 const TIntegral x_a) const {

  // compute the derivative function
  //
  dydyoffset_a = 1.0;

  // exit gracefully
  //
  return true;
}

// explicit instantiations
//
template bool8
Sigmoid::derivativeYOffsetScalar<float32>(float32&, const float32) const;

template bool8
Sigmoid::derivativeYOffsetScalar<float64>(float64&, const float64) const;

// method: derivativeYOffsetVector
//
// arguments:
//  TVector& dydyoffset: (output) computed result
//  const TVector& x: (input) value to evaluate the sigmoid derivative at
//
// return: bool8 value indicating status
//
// this method computes y[i] = dy/dyoffset(x[i]):
//
//     dy           
//     -- (x[i])  = 1.0
//   dyoffset        
//
template <class TVector, class TIntegral>
bool8 Sigmoid::derivativeYOffsetVector(TVector& dydyoffset_a,
					 const TVector& x_a) const {

  // simply set every element of the output to 1.0
  //
  dydyoffset_a.setLength(x_a.length(), false);
  dydyoffset_a.assign(1.0);

  // exit gracefully
  //
  return true;
}

// explicit instantiations
//
template bool8
Sigmoid::derivativeYOffsetVector<VectorFloat, float32>(VectorFloat&,
						     const VectorFloat&) const;

template bool8
Sigmoid::derivativeYOffsetVector<VectorDouble, float64>(VectorDouble&,
						   const VectorDouble&) const;


