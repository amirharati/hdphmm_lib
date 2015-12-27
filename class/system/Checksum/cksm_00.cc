// file: $isip/class/system/Checksum/cksm_00.cc
// version: $Id: cksm_00.cc 5556 2000-11-17 20:46:46Z peng $
//

// isip include files
//
#include "Checksum.h"

// method: default constructor
//
// arguments: none
//
// return: none
//
Checksum::Checksum() {

  // initialize class data
  //
  algorithm_d = DEF_ALGORITHM;
  implementation_d = DEF_IMPLEMENTATION;
  cksum_d = (uint32)0;
  
  // set the status to invalid
  //
  is_valid_d = false;

  // exit gracefully
  //
}

//-----------------------------------------------------------------------------
//
// we define non-integral constants in the default constructor
//      
//-----------------------------------------------------------------------------

// constants: class name
//
const SysString Checksum::CLASS_NAME(L"Checksum");


// static instantiations: debug level and memory manager
//
Integral::DEBUG Checksum::debug_level_d = Integral::NONE;
MemoryManager Checksum::mgr_d(sizeof(Checksum), Checksum::name());
