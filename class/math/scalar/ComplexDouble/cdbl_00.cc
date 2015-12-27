// file: $isip/class/math/scalar/ComplexDouble/cdbl_00.cc
// version: $Id: cdbl_00.cc 7030 2001-06-09 02:14:24Z picone $
//

// there is no source code in this file
//

// isip include files
//
#include "ComplexDouble.h"

//-----------------------------------------------------------------------------
//
// we define non-integral constants in the default constructor
//      
//-----------------------------------------------------------------------------

// constants: class name
//
const String ComplexDouble::CLASS_NAME(L"ComplexDouble");

// static instantiations: memory manager
//
MemoryManager ComplexDouble::mgr_d(sizeof(ComplexDouble), CLASS_NAME);
