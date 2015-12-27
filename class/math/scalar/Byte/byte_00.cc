// file: $isip/class/math/scalar/Byte/byte_00.cc
// version: $Id: byte_00.cc 5488 2000-11-13 00:07:22Z peng $
//

// there is no source code in this file
//

// isip include files
//
#include "Byte.h"

//-----------------------------------------------------------------------------
//
// we define non-integral constants in the default constructor
//      
//-----------------------------------------------------------------------------

// constants: class name
//
const String Byte::CLASS_NAME(L"Byte");

// static instantiations: debug level and memory manager
//
MemoryManager Byte::mgr_d(sizeof(Byte), CLASS_NAME);
