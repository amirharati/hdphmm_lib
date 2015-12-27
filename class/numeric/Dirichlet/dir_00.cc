// file: randgd_00.cc
// version: $Id: randv_00.cc 2013-07-18  Amir Harati $
//

// isip include files
//
#include "Dirichlet.h"
 
// method: default constructor
//
// arguments:
//  int32 seed: (input) initial value of the seed
//
// return: none
//
Dirichlet::Dirichlet(int32 seed_a) {

  
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
const SysString Dirichlet::CLASS_NAME(L"Dirichlet");


// static instantiations: debug level and memory manager
//
Integral::DEBUG Dirichlet::debug_level_d = Integral::NONE;
MemoryManager Dirichlet::mgr_d(sizeof(Dirichlet), Dirichlet::name());

