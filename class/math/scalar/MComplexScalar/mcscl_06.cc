// file: $isip/class/math/scalar/MComplexScalar/mcscl_06.cc
// version: $Id: mcscl_06.cc 7363 2001-09-07 03:10:57Z picone $
//

// isip include files
//
#include "MComplexScalarMethods.h"
#include "MComplexScalar.h"

// method: name
//
// arguments: none
//
// return: a static String& containing the class name
//
// this method returns the class name
//
const String& MComplexScalarMethods::name() {
  return MComplexScalar<float, float32>::CLASS_NAME;
}
