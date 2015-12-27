// file: $isip/class/math/vector/VectorUshort/vust_00.cc
// version: $Id: vust_00.cc 5488 2000-11-13 00:07:22Z peng $
//

// there is no source code in this file
//

// isip include files
// 
#include "VectorUshort.h"

//-----------------------------------------------------------------------------
//
// we define non-integral constants in the default constructor
//      
//-----------------------------------------------------------------------------

// constants: class name
//
const String VectorUshort::CLASS_NAME(L"VectorUshort");

// static instantiations: memory manager
//
MemoryManager VectorUshort::mgr_d(sizeof(VectorUshort), CLASS_NAME);
