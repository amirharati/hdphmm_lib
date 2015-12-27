// file: $isip/class/math/matrix/MatrixUlong/mulg_00.cc
// version: $Id: mulg_00.cc 5544 2000-11-16 17:51:18Z peng $
//

// there is no source code in this file
//

// isip include files
// 
#include "MatrixUlong.h"
 
//-----------------------------------------------------------------------------
//
// we define non-integral constants in the default constructor
//      
//-----------------------------------------------------------------------------

// constants: required constants such as the class name
//
const String MatrixUlong::CLASS_NAME(L"MatrixUlong");

// static instantiations: memory manager 
//
MemoryManager MatrixUlong::mgr_d(sizeof(MatrixUlong), CLASS_NAME);
