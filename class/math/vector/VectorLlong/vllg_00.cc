// file: $isip/class/math/vector/VectorLlong/vllg_00.cc
// version: $Id: vllg_00.cc 5488 2000-11-13 00:07:22Z peng $
//

// there is no source code in this file
//

// isip include files
// 
#include "VectorLlong.h"

//-----------------------------------------------------------------------------
//
// we define non-integral constants in the default constructor
//      
//-----------------------------------------------------------------------------

// constants: class name
//
const String VectorLlong::CLASS_NAME(L"VectorLlong");

// static instantiations: memory manager
//
MemoryManager VectorLlong::mgr_d(sizeof(VectorLlong), CLASS_NAME);
