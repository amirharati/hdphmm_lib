// file: $isip/class/math/vector/VectorComplexDouble/vcdbl_00.cc
// version: $Id: vcdbl_00.cc 6803 2001-04-23 22:04:15Z peng $
//

// there is no source code in this file
//

// isip include files
// 
#include "VectorComplexDouble.h"

//-----------------------------------------------------------------------------
//
// we define non-integral constants in the default constructor
//      
//-----------------------------------------------------------------------------

// constants: class name
//
const String VectorComplexDouble::CLASS_NAME(L"VectorComplexDouble");

// static instantiations: memory manager
//
MemoryManager VectorComplexDouble::mgr_d(sizeof(VectorComplexDouble), CLASS_NAME);
