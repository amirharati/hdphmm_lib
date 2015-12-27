// file: $isip/class/math/matrix/MatrixLong/mlng_00.cc
// version: $Id: mlng_00.cc 5544 2000-11-16 17:51:18Z peng $
//

// there is no source code in this file
//

// isip include files
// 
#include "MatrixLong.h"
 
//-----------------------------------------------------------------------------
//
// we define non-integral constants in the default constructor
//      
//-----------------------------------------------------------------------------

// constants: required constants such as the class name
//
const String MatrixLong::CLASS_NAME(L"MatrixLong");

// static instantiations: memory manager
//
MemoryManager MatrixLong::mgr_d(sizeof(MatrixLong), CLASS_NAME);
