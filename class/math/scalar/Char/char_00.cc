// file: $isip/class/math/scalar/Char/char_00.cc
// version: $Id: char_00.cc 5488 2000-11-13 00:07:22Z peng $
//

// there is no source code in this file
//

// isip include files
//
#include "Char.h"

//-----------------------------------------------------------------------------
//
// we define non-integral constants in the default constructor
//      
//-----------------------------------------------------------------------------

// constants: class name
//
const String Char::CLASS_NAME(L"Char");

// constants: default value
//
const String Char::DEF_PARAM(L"value");

// static instantiations: debug level and memory manager
//
MemoryManager Char::mgr_d(sizeof(Char), CLASS_NAME);
