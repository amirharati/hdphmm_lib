// file: $isip/class/math/vector/VectorUllong/vull_00.cc
// version: $Id: vull_00.cc 5488 2000-11-13 00:07:22Z peng $
//

// there is no source code in this file
//

// isip include files
// 
#include "VectorUllong.h"

//-----------------------------------------------------------------------------
//
// we define non-integral constants in the default constructor
//      
//-----------------------------------------------------------------------------

// constants: class name
//
const String VectorUllong::CLASS_NAME(L"VectorUllong");

// static instantiations: memory manager
//
MemoryManager VectorUllong::mgr_d(sizeof(VectorUllong), CLASS_NAME);
