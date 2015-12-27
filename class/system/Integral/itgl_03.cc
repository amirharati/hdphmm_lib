// file: $isip/class/system/Integral/itgl_03.cc
// version: $Id: itgl_03.cc 5070 2000-09-29 20:36:36Z picone $
//

// isip include files
//
#include "Integral.h"
#include <Error.h>

// uncomment this line to debug almost equal
//
//#define ISIP_DEBUG_EQUALITY

// method: almostEqual
//
// arguments:
//  double x: (input) first value to be compared
//  double y: (input) second value to be compared
//  double percent: (input) *percentage* of difference allowable
//  double bound: (input) a lower bound on the comparison
//
// return: a boolean value indicating status
//
// this method compares two floating point numbers and determines if they
// are equal to within a specified precision. this method is vital to
// our diagnose methods, which require a comparison of computations to some
// known result.
//
// this method implements a comparison as:
//
//   x == y if  abs(x-y) < (percent/100.0) * (abs(x) + bound)
//
// hence, this method essentially provides a means of comparing numbers
// in a user-specified precision, since the user controls percent and bound.
//
bool8 Integral::almostEqual(float64 x_a, float64 y_a,
			    float64 percent_a, float64 bound_a) {
  
  // compare values to a threshold
  // with them a bit fields.
  //
  if (abs(x_a - y_a) < ((0.01 * percent_a) * (abs(x_a) + bound_a))) {
    return true;
  }
  else {
    return false;
  }
}
