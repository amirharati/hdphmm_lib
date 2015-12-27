// file: $isip/class/math/matrix/MMatrix/mmat_11.cc
// version: $Id: mmat_11.cc 5669 2000-11-26 14:46:51Z picone $
//

// isip include files
//
#include "MMatrix.h"
#include "MMatrixMethods.h"

// method: name
//
// arguments: none
//
// return: a static String& containing the class name
//
// this method returns the class name
//
const String& MMatrixMethods::name() {
  return MMatrix<Long, int32>::CLASS_NAME;
}
