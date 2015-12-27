// file: $isip/class/math/scalar/ComplexLong/clong_00.cc
// version: $Id: clong_00.cc 7210 2001-07-22 15:25:31Z jelinek $
//

// there is no source code in this file
//

// isip include files
//
#include "ComplexLong.h"

//-----------------------------------------------------------------------------
//
// we define non-integral constants in the default constructor
//      
//-----------------------------------------------------------------------------

// constants: class name
//
const String ComplexLong::CLASS_NAME(L"ComplexLong");

// static instantiations: memory manager
//
MemoryManager ComplexLong::mgr_d(sizeof(ComplexLong), CLASS_NAME);
