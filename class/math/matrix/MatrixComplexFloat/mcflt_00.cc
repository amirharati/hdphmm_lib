// file: $isip/class/math/matrix/MatrixComplexFloat/mcflt_00.cc
// version: $Id
//

// there is no source code in this file
//

// isip include files
// 
#include "MatrixComplexFloat.h"

//-----------------------------------------------------------------------------
//
// we define non-integral constants in the default constructor
//      
//-----------------------------------------------------------------------------

// constants: class name
//
const String MatrixComplexFloat::CLASS_NAME(L"MatrixComplexFloat");

// static instantiations: memory manager
//
MemoryManager MatrixComplexFloat::mgr_d(sizeof(MatrixComplexFloat), CLASS_NAME);
