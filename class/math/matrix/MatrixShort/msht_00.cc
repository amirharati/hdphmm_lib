// file: $isip/class/math/matrix/MatrixShort/msht_00.cc
// version: $Id: msht_00.cc 5544 2000-11-16 17:51:18Z peng $
//

// there is no source code in this file
//

// isip include files
// 
#include "MatrixShort.h"
 
//-----------------------------------------------------------------------------
//
// we define non-integral constants in the default constructor
//      
//-----------------------------------------------------------------------------

// constants: required constants such as the class name
//
const String MatrixShort::CLASS_NAME(L"MatrixShort");

// static instantiations: memory manager
//
MemoryManager MatrixShort::mgr_d(sizeof(MatrixShort), CLASS_NAME);
