// file: $isip/class/math/scalar/String/str_00.cc
// version: $Id: str_00.cc 6026 2000-12-20 16:54:37Z hamaker $
//

// there is no source code in this file
//

// isip include files
//
#include "String.h"

//-----------------------------------------------------------------------------
//
// we define non-integral constants in the default constructor
//      
//-----------------------------------------------------------------------------

// constants: class name
//
const String String::CLASS_NAME(L"String");

// constants: default parameters
//
const String String::DEF_PARAM(L"value");

// constants: other constants
//
const String String::EMPTY(L"");

// static instantiations: debug level and memory manager
//
MemoryManager String::mgr_d(sizeof(String), CLASS_NAME);
