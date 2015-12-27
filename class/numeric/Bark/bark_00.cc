// file: $isip/class/numeric/Bark/bark_00.cc
// version: $Id: bark_00.cc 7023 2001-06-08 23:46:48Z picone $
//

// isip include files
//
#include "Bark.h"

//-----------------------------------------------------------------------------
//
// we define non-integral constants in the default constructor
//      
//-----------------------------------------------------------------------------

// constants: class name
//
const String Bark::CLASS_NAME(L"Bark");

// constants: i/o related constants
//
const String Bark::DEF_PARAM(L"");

// static instantiations: debug level and memory manager
//
Integral::DEBUG Bark::debug_level_d = Integral::NONE;
MemoryManager Bark::mgr_d(sizeof(Bark), Bark::name());
