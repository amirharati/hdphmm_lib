// file: randgd_04.cc
// version: $Id: randgd_04.cc 2013-07-18  Amir Harati $
//

// isip include files
//
#include "Dirichlet.h"
#include <Console.h>


// method: init
//
// arguments: none
//
// return: a bool8 value indicating status
//
// this method pre-computes various constants used in this class
//
bool8 Dirichlet::init() {

    rnd_d.setAlgorithm(Random::GAMMA);
    rnd_d.setImplementation(Random::ACCREJ);
    rnd_d.seed(seed_d);  

  // exit gracefully
  //
  result_d.setLength(dist_len_d);
  is_valid_d=true;
  return true;
}


// method: compute
//
// arguments: none
//
// return: a Dirichlet value containing a random vector
//
// this method selects the appropriate computational method
//
bool8 Dirichlet::compute() {

  // check valid flag
  //
  if (!is_valid_d) {
    init();
  }
    
  // compute the random vector
  //
  computeDirichlet();
    
  // provide some useful debugging information
  //
  if (debug_level_d > Integral::NONE) {
    if (debug_level_d >= Integral::ALL) {
      debug(CLASS_NAME);
      Console::increaseIndention();
    }    
    if (debug_level_d >= Integral::DETAILED) {
      SysString value;
      SysString output;
      value.assign(seed_d);
      output.debugStr(name(), CLASS_NAME, L"seed", value);
      Console::put(output);
    }
    if (debug_level_d >= Integral::BRIEF) {
      SysString value;
      SysString output;
      value.assign((float64)result_d(0));
      for (int i = 1; i< result_d.length();i++){
	value.concat(L",");
	value.concat((float64)result_d(i));
      }
      output.debugStr(name(), CLASS_NAME, L"output", value);
      Console::put(output);
    }
    if (debug_level_d >= Integral::ALL) {
      Console::decreaseIndention();
    }    
  }

  // exit gracefully
  //
  return true;


}


// method: computeDirichlet
//
// arguments: none
//
// return: a Vecotrfloat  containing  Dirichlet random numbers with
//         shape parameter  Random::a_gamma.
//
// this method finds a random number within the default range
// using an algorithm modeled from:
//
// 
//
bool8 Dirichlet::computeDirichlet() {
  
  // declare local variables
  //
  double sum = 0;

  // compute Gamma and normalize it
  //

  // to make sure that we get a numeric results for small concentration
  // prameters
  //
  int32 a = 1;
  while (sum == 0){
    for (int32 i = 0; i<dist_len_d; i++){
      
      rnd_d.setParameters(a * concentration_d(i));
     
      result_d(i) = rnd_d.get();
     
    }
  
    a = a * 10;
    sum=result_d.sum();
  }
  
  result_d.div(sum);

  // exit gracefully: return a scaled value
  //
  return true;
  
}

