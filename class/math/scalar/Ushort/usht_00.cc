// file: $isip/class/math/scalar/Ushort/usht_00.cc
// version: $Id: usht_00.cc 5488 2000-11-13 00:07:22Z peng $
//

// there is no source code in this file
//

// isip include files
//
#include "Ushort.h"

//-----------------------------------------------------------------------------
//
// we define non-integral constants in the default constructor
//      
//-----------------------------------------------------------------------------

// constants: class name
//
const String Ushort::CLASS_NAME(L"Ushort");

// static instantiations: debug level and memory manager
//
MemoryManager Ushort::mgr_d(sizeof(Ushort), CLASS_NAME);
