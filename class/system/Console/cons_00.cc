// file: $isip/class/system/Console/cons_00.cc
// version: $Id: cons_00.cc 5124 2000-10-03 14:44:06Z picone $
//

// there is no source code in this file
//

// isip include files
//
#include "Console.h"
#include <SysString.h>

//-----------------------------------------------------------------------------
//
// we define non-integral constants in the default constructor
//      
//-----------------------------------------------------------------------------

// constants: class name
//
const SysString Console::CLASS_NAME(L"Console");

// static instantiations: consoles stack
//
File Console::cons_d(Console::DEF_STREAM);
File Console::stack_d[Console::MAX_STACK_SIZE];
int32 Console::size_d = 0;
int32 Console::stack_size_d = Console::MAX_STACK_SIZE;

// static instantiations: line-wrapping state
//
bool8 Console::initialized_wrap_d = false;

// static instantiations: debug level
//
Integral::DEBUG Console::debug_level_d = Integral::NONE;
