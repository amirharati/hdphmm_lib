// file: $isip/class/math/matrix/MatrixUshort/musht_00.cc
// version: $Id: musht_00.cc 5544 2000-11-16 17:51:18Z peng $
//

// there is no source code in this file
//

// isip include files
// 
#include "MatrixUshort.h"
 
//-----------------------------------------------------------------------------
//
// we define non-integral constants in the default constructor
//      
//-----------------------------------------------------------------------------

// constants: required constants such as the class name
//
const String MatrixUshort::CLASS_NAME(L"MatrixUshort");

// static instantiations: memory manager
//
MemoryManager MatrixUshort::mgr_d(sizeof(MatrixUshort), CLASS_NAME);
