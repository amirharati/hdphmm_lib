// file: $isip/class/algo/Kernel/kern_05.cc
// version: $Id: kern_05.cc 8475 2002-07-26 16:36:47Z hamaker $
//

// isip include files
//
#include "Kernel.h"

// method: compute
//
// arguments:
//  float32& value: (output) return value of the kernel evaluation
//  const VectorFloat& x: (input) first operand
//  const VectorFloat& y: (input) second operand
//
// return: a bool8 value indicating status
//
// this method applies the specified kernel on the input vectors
//
bool8 Kernel::compute(float32& value_a, const VectorFloat& x_a,
			const VectorFloat& y_a) {

  // check whether we need to initialize
  //
  if (!is_valid_d) {
    init();
  }

  // branch on the algorithm
  //
  if (algorithm_d == LINEAR) {
    return computeLinear(value_a, x_a, y_a);
  }

  else if (algorithm_d == POLYNOMIAL) {
    return computePolynomial(value_a, x_a, y_a);
  }  

  else if (algorithm_d == RBF) {
    return computeRBF(value_a, x_a, y_a);
  }  

  else if (algorithm_d == SIGMOID) {
    return computeSigmoid(value_a, x_a, y_a);
  }  
  
  // error: unknown algorithm
  //
  else {
    return Error::handle(name(), L"compute", ERR_UNKALG, __FILE__, __LINE__);
  }
}

// method: compute
//
// arguments:
//  float64& value: (output) return value of the kernel evaluation
//  const VectorDouble& x: (input) first operand
//  const VectorDouble& y: (input) second operand
//
// return: a bool8 value indicating status
//
// this method applies the specified kernel on the input vectors
//
bool8 Kernel::compute(float64& value_a, const VectorDouble& x_a,
			const VectorDouble& y_a) {

  // check whether we need to initialize
  //
  if (!is_valid_d) {
    init();
  }

  // branch on the algorithm
  //
  if (algorithm_d == LINEAR) {
    return computeLinear(value_a, x_a, y_a);
  }

  else if (algorithm_d == POLYNOMIAL) {
    return computePolynomial(value_a, x_a, y_a);
  }  

  else if (algorithm_d == RBF) {
    return computeRBF(value_a, x_a, y_a);
  }  

  else if (algorithm_d == SIGMOID) {
    return computeSigmoid(value_a, x_a, y_a);
  }  
  
  // error: unknown algorithm
  //
  else {
    return Error::handle(name(), L"compute", ERR_UNKALG, __FILE__, __LINE__);
  }
}

// method: computeLinear
//
// arguments:
//  float32& value: (output) return value of the kernel evaluation
//  const VectorFloat& x: (input) first operand
//  const VectorFloat& y: (input) second operand
//
// return: a bool8 value indicating status
//
// this method applies the linear kernel on the input vectors
//    value = (x . y)
//
bool8 Kernel::computeLinear(float32& value_a, const VectorFloat& x_a,
			      const VectorFloat& y_a) {

  // compute the final result
  //
  value_a = x_a.dotProduct(y_a);

  // exit gracefully
  //
  return true;
}

// method: computeLinear
//
// arguments:
//  float64& value: (output) return value of the kernel evaluation
//  const VectorDouble& x: (input) first operand
//  const VectorDouble& y: (input) second operand
//
// return: a bool8 value indicating status
//
// this method applies the linear kernel on the input vectors
//    value = (x . y)
//
bool8 Kernel::computeLinear(float64& value_a, const VectorDouble& x_a,
			      const VectorDouble& y_a) {

  // compute the final result
  //
  value_a = x_a.dotProduct(y_a);

  // exit gracefully
  //
  return true;
}

// method: computePolynomial
//
// arguments:
//  float32& value: (output) return value of the kernel evaluation
//  const VectorFloat& x: (input) first operand
//  const VectorFloat& y: (input) second operand
//
// return: a bool8 value indicating status
//
// this method applies the polynomial kernel on the input vectors
//    value = (x . y + 1) ^ p
// where 'p' is constants_d[0] in this class.
//
bool8 Kernel::computePolynomial(float32& value_a, const VectorFloat& x_a,
				  const VectorFloat& y_a) {

  // set the scale parameter
  //
  float32 p = constants_d(0);
  
  // compute the polynomial kernel
  //
  value_a = Integral::pow((x_a.dotProduct(y_a) + 1.0), p);

  // exit gracefully
  //
  return true;
}

// method: computePolynomial
//
// arguments:
//  float64& value: (output) return value of the kernel evaluation
//  const VectorDouble& x: (input) first operand
//  const VectorDouble& y: (input) second operand
//
// return: a bool8 value indicating status
//
// this method applies the polynomial kernel on the input vectors
//    value = (x . y + 1) ^ p
// where 'p' is constants_d[0] in this class.
//
bool8 Kernel::computePolynomial(float64& value_a, const VectorDouble& x_a,
				  const VectorDouble& y_a) {

  // set the scale parameter
  //
  float64 p = constants_d(0);
  
  // compute the polynomial kernel
  //
  value_a = Integral::pow((x_a.dotProduct(y_a) + 1.0), p);

  // exit gracefully
  //
  return true;
}

// method: computeRBF
//
// arguments:
//  float32& value: (output) return value of the kernel evaluation
//  const VectorFloat& x: (input) first operand
//  const VectorFloat& y: (input) second operand
//
// return: a bool8 value indicating status
//
// this method applies the radial basis function kernel on the input vectors
//    value = exp(-gamma * ((x . x) - 2 * (x . y) + (y . y))
// where 'gamma' is constants_d[0] in this class.
//
bool8 Kernel::computeRBF(float32& value_a, const VectorFloat& x_a,
			   const VectorFloat& y_a) {

  static VectorFloat tmp;
  tmp.sub(x_a, y_a);
  float32 value = tmp.sumSquare();
  
  // set the scale parameter
  //
  float32 gamma = constants_d(0);
  
  // compute the rbf kernel
  //
  //  value_a = Integral::exp(-gamma * (x_a.dotProduct(x_a) -
  //				    2 * x_a.dotProduct(y_a) +
  //				    y_a.dotProduct(y_a)));

  value_a = Integral::exp(-gamma * value);

  // exit gracefully
  //
  return true;
}

// method: computeRBF
//
// arguments:
//  float64& value: (output) return value of the kernel evaluation
//  const VectorDouble& x: (input) first operand
//  const VectorDouble& y: (input) second operand
//
// return: a bool8 value indicating status
//
// this method applies the radial basis function kernel on the input vectors
//    value = exp(-gamma * ((x . x) - 2 * (x . y) + (y . y))
// where 'gamma' is constants_d[0] in this class.
//
bool8 Kernel::computeRBF(float64& value_a, const VectorDouble& x_a,
			   const VectorDouble& y_a) {

  static VectorDouble tmp;
  tmp.sub(x_a, y_a);
  float64 value = tmp.sumSquare();
  
  // set the scale parameter
  //
  float64 gamma = constants_d(0);
  
  // compute the rbf kernel
  //
  //  value_a = Integral::exp(-gamma * (x_a.dotProduct(x_a) -
  //				    2 * x_a.dotProduct(y_a) +
  //				    y_a.dotProduct(y_a)));

  value_a = Integral::exp(-gamma * value);

  // exit gracefully
  //
  return true;
}

// method: computeSigmoid
//
// arguments:
//  float32& value: (output) return value of the kernel evaluation
//  const VectorFloat& x: (input) first operand
//  const VectorFloat& y: (input) second operand
//
// return: a bool8 value indicating status
//
// this method applies the sigmoid kernel on the input vectors
//    value = tanh(kappa * (x . y) + delta)
// where 'kappa' is constants_d[0] and 'delta' is constants_d[1] in this
// class.
//
bool8 Kernel::computeSigmoid(float32& value_a, const VectorFloat& x_a,
			       const VectorFloat& y_a) {

  // set the scale parameter
  //
  float32 kappa = constants_d(0);
  float32 delta = constants_d(1);
  
  // compute the sigmoid kernel
  //
  value_a = Integral::tanh(kappa * x_a.dotProduct(y_a) + delta);

  // exit gracefully
  //
  return true;
}

// method: computeSigmoid
//
// arguments:
//  float64& value: (output) return value of the kernel evaluation
//  const VectorDouble& x: (input) first operand
//  const VectorDouble& y: (input) second operand
//
// return: a bool8 value indicating status
//
// this method applies the sigmoid kernel on the input vectors
//    value = tanh(kappa * (x . y) + delta)
// where 'kappa' is constants_d[0] and 'delta' is constants_d[1] in this
// class.
//
bool8 Kernel::computeSigmoid(float64& value_a, const VectorDouble& x_a,
			       const VectorDouble& y_a) {

  // set the scale parameter
  //
  float64 kappa = constants_d(0);
  float64 delta = constants_d(1);
  
  // compute the sigmoid kernel
  //
  value_a = Integral::tanh(kappa * x_a.dotProduct(y_a) + delta);

  // exit gracefully
  //
  return true;
}
