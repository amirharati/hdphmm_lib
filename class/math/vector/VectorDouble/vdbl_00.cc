// file: $isip/class/math/vector/VectorDouble/vdbl_00.cc
// version: $Id: vdbl_00.cc 5488 2000-11-13 00:07:22Z peng $
//

// there is no source code in this file
//

// isip include files
// 
#include "VectorDouble.h"

//-----------------------------------------------------------------------------
//
// we define non-integral constants in the default constructor
//      
//-----------------------------------------------------------------------------

// constants: class name
//
const String VectorDouble::CLASS_NAME(L"VectorDouble");

// static instantiations: memory manager
//
MemoryManager VectorDouble::mgr_d(sizeof(VectorDouble), CLASS_NAME);
