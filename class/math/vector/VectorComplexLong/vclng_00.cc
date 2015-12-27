// file: $isip/class/math/vector/VectorComplexLong/vclng_00.cc
// version: $Id: vclng_00.cc 7225 2001-07-23 20:08:46Z jelinek $
//

// there is no source code in this file
//

// isip include files
// 
#include "VectorComplexLong.h"

//-----------------------------------------------------------------------------
//
// we define non-integral constants in the default constructor
//      
//-----------------------------------------------------------------------------

// constants: class name
//
const String VectorComplexLong::CLASS_NAME(L"VectorComplexLong");

// static instantiations: memory manager
//
MemoryManager VectorComplexLong::mgr_d(sizeof(VectorComplexLong), CLASS_NAME);
