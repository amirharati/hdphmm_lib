// file: $isip/class/system/Random/rand_00.cc
// version: $Id: rand_00.cc 5060 2000-09-29 16:00:10Z picone $
//

// updated 7/6/13  by Amir Harati
//

// isip include files
//
#include "Random.h"
 
// method: default constructor
//
// arguments:
//  int32 seed: (input) initial value of the seed
//
// return: none
//
Random::Random(int32 seed_a) {

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
const SysString Random::CLASS_NAME(L"Random");

// static instantiations: global generators
//
Random Random::GLOBAL_UNIFORM(UNIFORM, SUBTRACTIVE);
Random Random::GLOBAL_GAUSSIAN(GAUSSIAN, TRANSFORMATION);
Random Random::GLOBAL_GAMMA(GAMMA,ACCREJ);

// static instantiations: debug level and memory manager
//
Integral::DEBUG Random::debug_level_d = Integral::NONE;
MemoryManager Random::mgr_d(sizeof(Random), Random::name());

