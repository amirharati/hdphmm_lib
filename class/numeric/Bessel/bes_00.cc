// file: $isip/class/numeric/Bessel/bes_00.cc
// version: $Id: bes_00.cc 7146 2001-07-04 22:57:40Z picone $
//

// isip include files
//
#include "Bessel.h"

//-----------------------------------------------------------------------------
//
// we define non-integral constants in the default constructor
//      
//-----------------------------------------------------------------------------

// constants: class name
//
const String Bessel::CLASS_NAME(L"Bessel");

// constants: i/o related constants
//
const String Bessel::DEF_PARAM(L"");

// static instantiations: debug level and memory manager
//
Integral::DEBUG Bessel::debug_level_d = Integral::NONE;
MemoryManager Bessel::mgr_d(sizeof(Bessel), Bessel::name());

