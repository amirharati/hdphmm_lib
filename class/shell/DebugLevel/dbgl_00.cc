// file: $isip/class/shall/DebugLevel/dbgl_00.cc
// version: $Id: dbgl_00.cc 6120 2000-12-29 23:10:04Z duncan $
//

// there is no source code in this file
//

// isip include files
//
#include "DebugLevel.h"

//-----------------------------------------------------------------------------
//
// we define non-integral constants in the default constructor
//
//-----------------------------------------------------------------------------

// constants: required constants such as the class name
//
const String DebugLevel::CLASS_NAME(L"DebugLevel");

// constants:  i/o related constants
//
const String DebugLevel::DEF_PARAM(L"debug_level");

// constants: names for the enumerated levels
//
const NameMap DebugLevel::LEVEL_MAP(L"NONE, BRIEF, DETAILED, ALL");

// static instantiations: memory manager
//
MemoryManager DebugLevel::mgr_d(sizeof(DebugLevel), DebugLevel::name());
