// file: $isip/class/numeric/Sigmoid/sigm_00.cc
// version: $Id: sigm_00.cc 7027 2001-06-09 01:46:31Z picone $
//

// there is no source code in this file
//

// isip include files
//
#include "Sigmoid.h"

//-----------------------------------------------------------------------------
//
// we define non-integral constants in the default constructor
//
//-----------------------------------------------------------------------------

// constants: class name
//
const String Sigmoid::CLASS_NAME(L"Sigmoid");

// constants: i/o related constants
//
const String Sigmoid::DEF_PARAM(L"");
const String Sigmoid::PARAM_GAIN(L"gain");
const String Sigmoid::PARAM_SLOPE(L"slope");
const String Sigmoid::PARAM_XOFFSET(L"xoffset");
const String Sigmoid::PARAM_YOFFSET(L"yoffset");

// static instantiations: debug level and memory manager
//
Integral::DEBUG Sigmoid::debug_level_d = Integral::NONE;
MemoryManager Sigmoid::mgr_d(sizeof(Sigmoid), Sigmoid::CLASS_NAME);
