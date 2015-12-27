// file: $isip/class/math/matrix/MatrixByte/mbyt_00.cc
// version: $Id: mbyt_00.cc 5544 2000-11-16 17:51:18Z peng $
//

// there is no source code in this file
//

// isip include files
// 
#include "MatrixByte.h"
 
//-----------------------------------------------------------------------------
//
// we define non-integral constants in the default constructor
//      
//-----------------------------------------------------------------------------

// constants: required constants such as the class name
//
const String MatrixByte::CLASS_NAME(L"MatrixByte");

// static instantiations: memory manager
//
MemoryManager MatrixByte::mgr_d(sizeof(MatrixByte), CLASS_NAME);
