// file: $isip/class/math/scalar/Short/shrt_00.cc
// version: $Id: shrt_00.cc 5488 2000-11-13 00:07:22Z peng $
//

// there is no source code in this file
//

// isip include files
//
#include "Short.h"

//-----------------------------------------------------------------------------
//
// we define non-integral constants in the default constructor
//      
//-----------------------------------------------------------------------------

// constants: class name
//
const String Short::CLASS_NAME(L"Short");

// static instantiations: debug level and memory manager
//
MemoryManager Short::mgr_d(sizeof(Short), CLASS_NAME);
