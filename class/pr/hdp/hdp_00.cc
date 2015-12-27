// file: hdp_00.cc
// version: $Id: hdp_00.cc 2013-1-25 Amir Harati $
//

// there is no source code in this file
//

// isip include files
//
#include "HDP.h"

// there is no source code in this file
//

//-----------------------------------------------------------------------------
//
// we define non-integral constants in the default constructor
//
//-----------------------------------------------------------------------------

// constants: required constants such as the class name
//
const String HDP::CLASS_NAME(L"HDP");

// constants: i/o related constants
//
const String HDP::DEF_PARAM(L"");
const String HDP::PARAM_MODEL(L"HDP");

// static instantiations: memory manager and a permanent scratch space
//
MemoryManager HDP::mgr_d(sizeof(HDP),HDP::CLASS_NAME);

// debug level and verbosity
//
Integral::DEBUG HDP::debug_level_d = Integral::NONE;
Integral::DEBUG HDP::verbosity_d = Integral::NONE;
