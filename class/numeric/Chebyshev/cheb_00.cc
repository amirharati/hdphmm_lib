// file: $isip/class/numeric/Chebyshev/cheb_00.cc
// version: $Id: cheb_00.cc 7145 2001-07-04 22:57:11Z picone $
//

// isip include files
//
#include "Chebyshev.h"

//-----------------------------------------------------------------------------
//
// we define non-integral constants in the default constructor
//      
//-----------------------------------------------------------------------------

// constants: class name
//
const String Chebyshev::CLASS_NAME(L"Chebyshev");

// constants: i/o related constants
//
const String Chebyshev::DEF_PARAM(L"");

// static instantiations: debug level and memory manager
//
Integral::DEBUG Chebyshev::debug_level_d = Integral::NONE;
MemoryManager Chebyshev::mgr_d(sizeof(Chebyshev), Chebyshev::name());
