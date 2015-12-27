// file: $isip/class/math/scalar/Boolean/bool_00.cc
// version: $Id: bool_00.cc 5488 2000-11-13 00:07:22Z peng $
//

// there is no source code in this file
//

// isip include files
//
#include "Boolean.h"

//-----------------------------------------------------------------------------
//
// we define non-integral constants in the default constructor
//      
//-----------------------------------------------------------------------------

// constants: class name
//
const String Boolean::CLASS_NAME(L"Boolean");

// constants: default parameters
//
const String Boolean::DEF_PARAM(L"value");

// static instantiations: debug level and memory manager
//
Integral::DEBUG Boolean::debug_level_d = Integral::NONE;
MemoryManager Boolean::mgr_d(sizeof(Boolean), CLASS_NAME);
