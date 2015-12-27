// file: $isip/class/math/scalar/Double/dbl_00.cc
// version: $Id: dbl_00.cc 5488 2000-11-13 00:07:22Z peng $
//

// there is no source code in this file
//

// isip include files
//
#include "Double.h"

//-----------------------------------------------------------------------------
//
// we define non-integral constants in the default constructor
//
//-----------------------------------------------------------------------------

// constants: class name
//
const String Double::CLASS_NAME(L"Double");

// static instantiations: debug level and memory manager
//
MemoryManager Double::mgr_d(sizeof(Double), CLASS_NAME);
