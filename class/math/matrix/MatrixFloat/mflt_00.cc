// file: $isip/class/math/matrix/MatrixFloat/mflt_00.cc
// version: $Id: mflt_00.cc 5544 2000-11-16 17:51:18Z peng $
//

// there is no source code in this file
//

// isip include files
// 
#include "MatrixFloat.h"
 
//-----------------------------------------------------------------------------
//
// we define non-integral constants in the default constructor
//      
//-----------------------------------------------------------------------------

// constants: required constants such as the class name
//
const String MatrixFloat::CLASS_NAME(L"MatrixFloat");

// static instantiations: memory manager
//
MemoryManager MatrixFloat::mgr_d(sizeof(MatrixFloat), CLASS_NAME);
