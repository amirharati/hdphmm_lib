// file: $isip/class/math/matrix/MatrixComplexDouble/mcdbl_00.cc
// version: $Id
//

// there is no source code in this file
//

// isip include files
// 
#include "MatrixComplexDouble.h"

//-----------------------------------------------------------------------------
//
// we define non-integral constants in the default constructor
//      
//-----------------------------------------------------------------------------

// constants: class name
//
const String MatrixComplexDouble::CLASS_NAME(L"MatrixComplexDouble");

// static instantiations: memory manager
//
MemoryManager MatrixComplexDouble::mgr_d(sizeof(MatrixComplexDouble), CLASS_NAME);
