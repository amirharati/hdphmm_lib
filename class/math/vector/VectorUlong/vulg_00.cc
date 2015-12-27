// file: $isip/class/math/vector/VectorUlong/vulg_00.cc
// version: $Id: vulg_00.cc 5488 2000-11-13 00:07:22Z peng $
//

// there is no source code in this file
//

// isip include files
// 
#include "VectorUlong.h"

//-----------------------------------------------------------------------------
//
// we define non-integral constants in the default constructor
//      
//-----------------------------------------------------------------------------

// constants: class name
//
const String VectorUlong::CLASS_NAME(L"VectorUlong");

// static instantiations: memory manager
//
MemoryManager VectorUlong::mgr_d(sizeof(VectorUlong), CLASS_NAME);
