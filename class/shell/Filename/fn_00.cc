// file: $isip/class/shell/Filename/fn_00.cc
// version: $Id: fn_00.cc 9209 2003-06-15 03:41:40Z picone $
//

// isip include files
//
#include "Filename.h"

// there is no source code in this file
//

//-----------------------------------------------------------------------------
//
// we define non-integral constants in the default constructor
//
//-----------------------------------------------------------------------------

// constants: required constants such as the class name
//
const String Filename::CLASS_NAME(L"Filename");

// constants: Unix delimiters
//
const String Filename::SLASH(L"/");
const String Filename::DOT(L".");
const String Filename::UNDERSCORE(L"_");

// constants: default arguments to methods
//
const String Filename::DEF_EXTENSION(L"sof");
const String Filename::DEF_SUFFIX(L"");

// static instantiations: memory manager
//
MemoryManager Filename::mgr_d(sizeof(Filename), Filename::name());
