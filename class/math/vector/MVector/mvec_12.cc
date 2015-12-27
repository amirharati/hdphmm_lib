// file: $isip/class/math/vector/MVector/mvec_12.cc
// version: $Id: mvec_12.cc 5215 2000-10-06 20:08:25Z picone $
//

// isip include files
//
#include "MVector.h"
#include "MVectorMethods.h"

// method: name
//
// arguments: none
//
// return: a static String& containing the class name
//
// this method returns the class name
//
const String& MVectorMethods::name() {
  return MVector<Long, int32>::CLASS_NAME;
}
