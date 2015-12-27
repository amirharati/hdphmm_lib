// file: $isip/class/numeric/Mel/mel_00.cc
// version: $Id: mel_00.cc 7025 2001-06-09 00:57:35Z picone $
//

// isip include files
//
#include "Mel.h"

//-----------------------------------------------------------------------------
//
// we define non-integral constants in the default constructor
//      
//-----------------------------------------------------------------------------

// constants: class name
//
const String Mel::CLASS_NAME(L"Mel");

// constants: i/o related constants
//
const String Mel::DEF_PARAM(L"");

// static instantiations: debug level and memory manager
//
Integral::DEBUG Mel::debug_level_d = Integral::NONE;
MemoryManager Mel::mgr_d(sizeof(Mel), Mel::name());
