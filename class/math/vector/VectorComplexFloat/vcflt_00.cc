// file: $isip/class/math/vector/VectorComplexFloat/vcflt_00.cc
// version: $Id: vcflt_00.cc 6803 2001-04-23 22:04:15Z peng $
//

// there is no source code in this file
//

// isip include files
// 
#include "VectorComplexFloat.h"

//-----------------------------------------------------------------------------
//
// we define non-integral constants in the default constructor
//      
//-----------------------------------------------------------------------------

// constants: class name
//
const String VectorComplexFloat::CLASS_NAME(L"VectorComplexFloat");

// static instantiations: memory manager
//
MemoryManager VectorComplexFloat::mgr_d(sizeof(VectorComplexFloat), CLASS_NAME);
