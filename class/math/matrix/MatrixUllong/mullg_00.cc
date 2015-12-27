// file: $isip/class/math/matrix/MatrixUllong/mullg_00.cc
// version: $Id: mullg_00.cc 5544 2000-11-16 17:51:18Z peng $
//

// there is no source code in this file
//

// isip include files
// 
#include "MatrixUllong.h"
 
//-----------------------------------------------------------------------------
//
// we define non-integral constants in the default constructor
//      
//-----------------------------------------------------------------------------

// constants: required constants such as the class name
//
const String MatrixUllong::CLASS_NAME(L"MatrixUllong");

// static instantiations: memory manager
//
MemoryManager MatrixUllong::mgr_d(sizeof(MatrixUllong), CLASS_NAME);
