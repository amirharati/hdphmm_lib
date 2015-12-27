// file: $isip/class/system/SysChar/schr_00.cc
// version: $Id: schr_00.cc 5495 2000-11-13 02:21:43Z picone $
//

// there is no source code in this file
//

// isip include files
//
#include "SysChar.h"
#include <SysString.h>

//-----------------------------------------------------------------------------
//
// we define non-integral constants in the default constructor
//      
//-----------------------------------------------------------------------------

// constants: required constants such as the class name
//
const SysString SysChar::CLASS_NAME(L"SysChar");

// constants: define special characters
//
const SysChar SysChar::NULLC((unichar)0);
const SysChar SysChar::SPACEC(L' ');
const SysChar SysChar::TILDE(L'~');
const SysChar SysChar::DOLLAR(L'$');
const SysChar SysChar::NEWLINE(L'\n');

// static instantiations: debug level
//
Integral::DEBUG SysChar::debug_level_d = Integral::NONE;
