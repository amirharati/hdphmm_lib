// file: $isip/class/math/scalar/Float/flt_00.cc
// version: $Id: flt_00.cc 5488 2000-11-13 00:07:22Z peng $
//

// there is no source code in this file
//

// isip include files
//
#include "Float.h"

//-----------------------------------------------------------------------------
//
// we define non-integral constants in the default constructor
//      
//-----------------------------------------------------------------------------

// constants: class name
//
const String Float::CLASS_NAME(L"Float");

// static instantiations: debug level and memory manager
//
MemoryManager Float::mgr_d(sizeof(Float), CLASS_NAME);
