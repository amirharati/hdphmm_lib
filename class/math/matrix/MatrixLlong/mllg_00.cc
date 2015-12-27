// file: $isip/class/math/matrix/MatrixLlong/mllg_00.cc
// version: $Id: mllg_00.cc 5544 2000-11-16 17:51:18Z peng $
//

// there is no source code in this file
//

// isip include files
// 
#include "MatrixLlong.h"
 
//-----------------------------------------------------------------------------
//
// we define non-integral constants in the default constructor
//      
//-----------------------------------------------------------------------------

// constants: required constants such as the class name
//
const String MatrixLlong::CLASS_NAME(L"MatrixLlong");

// static instantiations: memory manager
//
MemoryManager MatrixLlong::mgr_d(sizeof(MatrixLlong), CLASS_NAME);
