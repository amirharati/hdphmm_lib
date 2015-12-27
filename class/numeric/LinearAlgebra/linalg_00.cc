// file: $isip/class/numeric/LinearAlgebra/linalg_00.cc
// version: $Id: linalg_00.cc 6851 2001-04-29 20:01:21Z srivasta $
//

// there is no source code in this file
//

// isip include files
//
#include "LinearAlgebra.h"

//-----------------------------------------------------------------------------
//
// we define non-integral constants in the default constructor
//
//-----------------------------------------------------------------------------

// constants: class name
//
const String LinearAlgebra::CLASS_NAME(L"LinearAlgebra");

// constants: i/o related constants
//
const String LinearAlgebra::DEF_PARAM(L"");

// static instantiations: memory manager and debug level
//
MemoryManager LinearAlgebra::mgr_d(sizeof(LinearAlgebra),
				   LinearAlgebra::CLASS_NAME);
Integral::DEBUG LinearAlgebra::debug_level_d = Integral::NONE;
