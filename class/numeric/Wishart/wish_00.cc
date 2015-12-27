// file: wish_00.cc
// version: $Id: wish_00.cc 2013-07-18  Amir Harati $
//

// isip include files
//
#include "Wishart.h"
 
// method: default constructor
//
// arguments:
//  int32 seed: (input) initial value of the seed
//
// return: none
//
Wishart::Wishart(int32 seed_a) {

  // initialize class data
  //
  algorithm_d = DEF_ALGORITHM;
  implementation_d = DEF_IMPLEMENTATION;

  // define a default initial seed
  //
  seed_d = seed_a;

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
const SysString Wishart::CLASS_NAME(L"Wishart");


// static instantiations: debug level and memory manager
//
Integral::DEBUG Wishart::debug_level_d = Integral::NONE;
MemoryManager Wishart::mgr_d(sizeof(Wishart), Wishart::name());

