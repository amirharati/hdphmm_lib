// file: $isip/class/math/scalar/Ulong/ulng_00.cc
// version: $Id: ulng_00.cc 5488 2000-11-13 00:07:22Z peng $
//

// there is no source code in this file
//

// isip include files
//
#include "Ulong.h"

//-----------------------------------------------------------------------------
//
// we define non-integral constants in the default constructor
//      
//-----------------------------------------------------------------------------

// constants: class name
//
const String Ulong::CLASS_NAME(L"Ulong");

// static instantiations: debug level and memory manager
//
MemoryManager Ulong::mgr_d(sizeof(Ulong), CLASS_NAME);
