// file: $isip/class/math/vector/VectorByte/vbyt_00.cc
// version: $Id: vbyt_00.cc 5488 2000-11-13 00:07:22Z peng $
//

// there is no source code in this file
//

// isip include files
// 
#include "VectorByte.h"

//-----------------------------------------------------------------------------
//
// we define non-integral constants in the default constructor
//      
//-----------------------------------------------------------------------------

// constants: class name
//
const String VectorByte::CLASS_NAME(L"VectorByte");

// static instantiations: memory manager
//
MemoryManager VectorByte::mgr_d(sizeof(VectorByte), CLASS_NAME);
