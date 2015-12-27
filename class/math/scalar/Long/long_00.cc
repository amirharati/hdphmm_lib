// file: $isip/class/math/scalar/Long/long_00.cc
// version: $Id: long_00.cc 5488 2000-11-13 00:07:22Z peng $
//

// there is no source code in this file
//

// isip include files
//
#include "Long.h"

//-----------------------------------------------------------------------------
//
// we define non-integral constants in the default constructor
//      
//-----------------------------------------------------------------------------

// constants: class name
//
const String Long::CLASS_NAME(L"Long");

// static instantiations: debug level and memory manager
//
MemoryManager Long::mgr_d(sizeof(Long), CLASS_NAME);
