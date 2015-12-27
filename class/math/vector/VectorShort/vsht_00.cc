// file: $isip/class/math/vector/VectorShort/vsht_00.cc
// version: $Id: vsht_00.cc 5488 2000-11-13 00:07:22Z peng $
//

// there is no source code in this file
//

// isip include files
// 
#include "VectorShort.h"

//-----------------------------------------------------------------------------
//
// we define non-integral constants in the default constructor
//      
//-----------------------------------------------------------------------------

// constants: class name
//
const String VectorShort::CLASS_NAME(L"VectorShort");

// static instantiations: memory manager
//
MemoryManager VectorShort::mgr_d(sizeof(VectorShort), CLASS_NAME);
