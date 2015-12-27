// file: $isip/class/math/vector/VectorLong/vlng_00.cc
// version: $Id: vlng_00.cc 5488 2000-11-13 00:07:22Z peng $
//

// there is no source code in this file
//

// isip include files
// 
#include "VectorLong.h"

//-----------------------------------------------------------------------------
//
// we define non-integral constants in the default constructor
//      
//-----------------------------------------------------------------------------

// constants: class name
//
const String VectorLong::CLASS_NAME(L"VectorLong");

// static instantiations: memory manager
//
MemoryManager VectorLong::mgr_d(sizeof(VectorLong), CLASS_NAME);
