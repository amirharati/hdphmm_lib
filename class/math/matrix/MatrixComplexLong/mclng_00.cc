// file: $isip/class/math/matrix/MatrixComplexLong/mclng_00.cc
// version: $Id
//

// there is no source code in this file
//

// isip include files
// 
#include "MatrixComplexLong.h"

//-----------------------------------------------------------------------------
//
// we define non-integral constants in the default constructor
//      
//-----------------------------------------------------------------------------

// constants: class name
//
const String MatrixComplexLong::CLASS_NAME(L"MatrixComplexLong");

// static instantiations: memory manager
//
MemoryManager MatrixComplexLong::mgr_d(sizeof(MatrixComplexLong), CLASS_NAME);
