// file: $isip/class/math/scalar/ComplexFloat/cflt_00.cc
// version: $Id: cflt_00.cc 7030 2001-06-09 02:14:24Z picone $
//

// there is no source code in this file
//

// isip include files
//
#include "ComplexFloat.h"

//-----------------------------------------------------------------------------
//
// we define non-integral constants in the default constructor
//      
//-----------------------------------------------------------------------------

// constants: class name
//
const String ComplexFloat::CLASS_NAME(L"ComplexFloat");

// static instantiations: memory manager
//
MemoryManager ComplexFloat::mgr_d(sizeof(ComplexFloat), CLASS_NAME);
