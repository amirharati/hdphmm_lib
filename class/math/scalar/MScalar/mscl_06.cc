// file: $isip/class/math/scalar/MScalar/mscl_06.cc
// version: $Id: mscl_06.cc 5155 2000-10-04 16:48:56Z picone $
//

// isip include files
//
#include "MScalarMethods.h"
#include "MScalar.h"

// method: name
//
// arguments: none
//
// return: a static String& containing the class name
//
// this method returns the class name
//
const String& MScalarMethods::name() {
  return MScalar<int32, int32>::CLASS_NAME;
}
