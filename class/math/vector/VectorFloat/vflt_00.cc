// file: $isip/class/math/vector/VectorFloat/vflt_00.cc
// version: $Id: vflt_00.cc 5488 2000-11-13 00:07:22Z peng $
//

// there is no source code in this file
//

// isip include files
// 
#include "VectorFloat.h"

//-----------------------------------------------------------------------------
//
// we define non-integral constants in the default constructor
//      
//-----------------------------------------------------------------------------

// constants: class name
//
const String VectorFloat::CLASS_NAME(L"VectorFloat");

// static instantiations: memory manager
//
MemoryManager VectorFloat::mgr_d(sizeof(VectorFloat), CLASS_NAME);
