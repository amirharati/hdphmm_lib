// file: $isip/class/math/scalar/Ullong/ullg_00.cc
// version: $Id: ullg_00.cc 5488 2000-11-13 00:07:22Z peng $
//

// there is no source code in this file
//

// isip include files
//
#include "Ullong.h"

//-----------------------------------------------------------------------------
//
// we define non-integral constants in the default constructor
//      
//-----------------------------------------------------------------------------

// constants: class name
//
const String Ullong::CLASS_NAME(L"Ullong");

// static instantiations: debug level and memory manager
//
MemoryManager Ullong::mgr_d(sizeof(Ullong), CLASS_NAME);
