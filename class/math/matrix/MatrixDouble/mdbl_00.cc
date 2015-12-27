// file: $isip/class/math/matrix/MatrixDouble/mdbl_00.cc
// version: $Id: mdbl_00.cc 5544 2000-11-16 17:51:18Z peng $
//

// there is no source code in this file
//

// isip include files
// 
#include "MatrixDouble.h"
 
//-----------------------------------------------------------------------------
//
// we define non-integral constants in the default constructor
//      
//-----------------------------------------------------------------------------

// constants: required constants such as the class name
//
const String MatrixDouble::CLASS_NAME(L"MatrixDouble");

// static instantiations: memory manager
//
MemoryManager MatrixDouble::mgr_d(sizeof(MatrixDouble), CLASS_NAME);
