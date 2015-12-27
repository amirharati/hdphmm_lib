// file: dpm_00.cc
// version: $Id: dpm_00.cc 2013-1-25 Amir Harati $
//


// there is no source code in this file
//

// isip include files
//
#include "DPM.h"

// there is no source code in this file
//

//-----------------------------------------------------------------------------
//
// we define non-integral constants in the default constructor
//
//-----------------------------------------------------------------------------

// constants: required constants such as the class name
//
const String DPM::CLASS_NAME(L"DPM ");

// constants: i/o related constants
//
const String DPM::DEF_PARAM(L"");
const String DPM::PARAM_MODEL(L"MODEL");

// static instantiations: memory manager and a permanent scratch space
//
MemoryManager DPM::mgr_d(sizeof(DPM),DPM::CLASS_NAME);


// debug level and verbosity
//
Integral::DEBUG DPM::debug_level_d = Integral::NONE;
Integral::DEBUG DPM::verbosity_d = Integral::NONE;



