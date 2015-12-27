// file: $isip/class/system/Random/rand_04.cc
// version: $Id: rand_04.cc 5660 2000-11-22 17:24:28Z picone $
//

// updated 7/6/2013 by Amir Harati
// isip include files
//
#include "Random.h"
#include <Console.h>
// method: init
//
// arguments: none
//
// return: a bool8 value indicating status
//
// this method pre-computes various constants used in this class
//
bool8 Random::init() {

  // check: algorithm = UNIFORM; implementation = SUBTRACTIVE
  // 
  if ((algorithm_d == UNIFORM) &&
      (implementation_d == SUBTRACTIVE)) {
    return initUniformSubtractive();
  }

  // check: algorithm = UNIFORM; implementation = CONGRUENTIAL
  // 
  if ((algorithm_d == UNIFORM) && (implementation_d == CONGRUENTIAL)) {
    return initUniformCongruential();
  }

  // check: algorithm = GAUSSIAN; implementation = TRANSFORMATION
  // 
  else if ((algorithm_d == GAUSSIAN) &&
	   (implementation_d == TRANSFORMATION)) {
    return initGaussianTransform();
  }

  // check: algorithm = GAMMA; implementation = TRANSFORMATION
  // 
  else if ((algorithm_d == GAMMA) &&
	   (implementation_d == ACCREJ)) {
    return initGammaAccrej();
  }

  // check algorithm: unknown
  //
  else {
    return Error::handle(name(), L"init",
			 Error::ARG, __FILE__, __LINE__);
  }  

  // exit gracefully
  //
  return true;
}

// method: initUniformSubtractive
//
// arguments: none
//
// return: a bool8 value indicating status
//
// this method seeds the random number generator. the seed should be
// a large positive number (which is converted to a large negative number).
//
bool8 Random::initUniformSubtractive() {

  // declare local temporary variables
  //
  int32 mj;
  int32 mk;
  int32 ii;
  int32 i;
  int32 k;
    
  // initialize the end of the seed array using a combination of
  // a predefined seed, MSEED, and the user-specific seed, seed_d.
  //
  mj = US_MSEED - seed_d;
  mj %= US_MBIG;
  us_ma_d[US_MDIM - 1] = mj;
  mk = 1;
  
  // initialize rest of the array in a slightly random order with numbers
  // that are not especially random.
  //
  for (i = 1; i <= US_MDIM - 1; i++) {
    
    // compute some arbitrary number
    //
    ii = (21 * i) % (US_MDIM - 1);
    us_ma_d[ii] = mk;
    mk = mj - mk;

    // make sure this number is positive by wrapping it around MBIG
    //
    if (mk < US_MZ) {
      mk += US_MBIG;
    }
    mj = us_ma_d[ii];
  }
  
  // "warm up" the random number generator by randomizing these numbers
  //
  for (k = 1; k <= 4; k++) {
    for (i = 1; i <= (US_MDIM - 1); i++) {

      // randomize the number via a modulus operation
      //
      us_ma_d[i] -= us_ma_d[1 + (i + US_CONST) % (US_MDIM - 1)];

      // make sure this number is positive by wrapping it around MBIG
      //
      if (us_ma_d[i] < US_MDIM) {
	us_ma_d[i] += US_MBIG;
      }
    }
  }
  
  // set values for next round
  //
  us_inext_d = 0;
  us_inextp_d = US_CONST + 1;
  
  // make the status valid
  //
  is_valid_d = true;

  // exit gracefully
  //
  return true;
}

// method: initUniformCongruential
//
// arguments: none
//
// return: a bool8 value indicating status
//
// this method seeds the random number generator.
//
bool8 Random::initUniformCongruential() {

  // seed the native random number generator
  //
  ::srand(seed_d);

  // make the status valid
  //
  is_valid_d = true;

  // exit gracefully
  //
  return true;
}

// method: initGaussianTransform
//
// arguments: none
//
// return: a bool8 value indicating status
//
// this method seeds the random number generator and prepares the registers.
//
bool8 Random::initGaussianTransform() {

  // seed a uniform random number generator
  //
  initUniformSubtractive();

  // clear the save status register
  //
  gt_iset_d = false;

  // make the status valid
  //
  is_valid_d = true;

  // exit gracefully
  //
  return true;
}

// method: initGammaAccrej
//
// arguments: none
//
// return: a bool8 value indicating status
//
// this method seeds the random number generator and prepares the registers.
//
bool8 Random::initGammaAccrej() {

  // seed a normal &  uniform random number generator
  //
  initGaussianTransform();
  
  initUniformSubtractive();

  // clear the save status register
  //
  gt_iset_d = false;

  // make the status valid
  //
  is_valid_d = true;

  // exit gracefully
  //
  return true;
}

// method: compute
//
// arguments: none
//
// return: a float64 value containing a random number
//
// this method selects the appropriate computational method
//
float64 Random::compute() {

  // declare local variables
  //
  float64 sum;

  // check valid flag
  //
  if (!is_valid_d) {
    init();
  }

  // check algorithm: UNIFORM
  //
  if (algorithm_d == UNIFORM) {
    
    // check implementations
    //
    if (implementation_d == SUBTRACTIVE) {
      sum = computeUniformSubtractive();
    }
    else if (implementation_d == CONGRUENTIAL) {
      sum = computeUniformCongruential();
    }
    else {
      return Error::handle(name(), L"compute",
			   Error::ARG, __FILE__, __LINE__);
    }
  }

  // check algorithm: GAUSSIAN
  //
  else if (algorithm_d == GAUSSIAN) {
    
    // check implementations
    //
    if (implementation_d == TRANSFORMATION) {
      sum = computeGaussianTransform();
    }
    else {
      return Error::handle(name(), L"compute",
			   Error::ARG, __FILE__, __LINE__);
    }
  }
  
  // check algorithm: GAMMA
  //
  else if (algorithm_d == GAMMA) {
    
    // check implementations
    //
    if (implementation_d == ACCREJ) {
      sum = computeGammaAccrej();
    }
    else {
      return Error::handle(name(), L"compute",
			   Error::ARG, __FILE__, __LINE__);
    }
  }

  // check algorithm: unknown
  //
  else {
    return Error::handle(name(), L"compute",
			 Error::ARG, __FILE__, __LINE__);
  }  

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
      value.assign((float64)sum);
      output.debugStr(name(), CLASS_NAME, L"output", value);
      Console::put(output);
    }
    if (debug_level_d >= Integral::ALL) {
      Console::decreaseIndention();
    }    
  }

  // exit gracefully
  //
  return sum;
}

// method: computeUniformSubtractive
//
// arguments: none
//
// return: a float64 value containing a random number uniformly
//         distributed on the range [0,1]
//
// this method finds a random number within the default range
// using an algorithm modeled from:
//
//  W. Press, S. Teukolsky, W. Vetterling, B. Flannery,
//  Numerical Recipes in C, Second Edition, Cambridge University Press,
//  New York, New York, USA, p. 283.
//
float64 Random::computeUniformSubtractive () {
  
  // increment the registers, limiting them to the range [1,US_MDIM]
  //
  if (++us_inext_d == US_MDIM) {
    us_inext_d = 1;
  }
  if (++us_inextp_d == US_MDIM) {
    us_inextp_d = 1;
  }

  // Generate a new random number using subtraction (this is why the
  // method is called a subtractive method.
  //
  int32 mj = us_ma_d[us_inext_d] - us_ma_d[us_inextp_d];

  // make sure it is a positive number by wrapping it around MBIG
  //
  if (mj < 0) {
    mj += US_MBIG;
  }

  // save this number
  //
  us_ma_d[us_inext_d] = mj;
  
  // return the suitably scaled random number
  //
  return ((float64)mj * US_FAC);
}

// method: computeUniformCongruential
//
// arguments: none
//
// return: a float64 value containing a random number uniformly
//         distributed on the range [0,1]
//
// this method finds a random number within the default range
// using the ANSI-standard algorithm.
//
float64 Random::computeUniformCongruential() {
  
  // return a scaled value
  //
  return ::rand() * INV_RAND_MAX;
}

// method: computeGaussianTransform
//
// arguments: none
//
// return: a float64 value containing a Gaussian random number with
//         a zero mean and unit variance (normal distribution)
//
// this method finds a random number within the default range
// using an algorithm modeled from:
//
//  W. Press, S. Teukolsky, W. Vetterling, B. Flannery,
//  Numerical Recipes in C, Second Edition, Cambridge University Press,
//  New York, New York, USA, p. 289.
//
// the main innovation of this method is that the computation requires
// two random numbers to be computed. the second number is saved
// and reused in the next call.
//
float64 Random::computeGaussianTransform() {
  
  // declare local variables
  //
  float64 v1, v2;
  float64 fac;
  float64 rsq;

  // check if we have a random number ready
  //
  if (gt_iset_d) {
    gt_iset_d = false;
    return gt_gset_d;
  }

  // otherwise, generate one
  //
  else {

    // ???
    //
    do {
      v1 = 2.0 * computeUniformSubtractive() - 1.0;
      v2 = 2.0 * computeUniformSubtractive() - 1.0;
      rsq = v1 * v1 + v2 * v2;
    } while ((rsq >= 1.0) || (rsq == 0.0));

    // ???
    //
    fac = sqrt(-2.0 * log(rsq) / rsq);

    // ???
    //
    gt_gset_d = v1 * fac;
    gt_iset_d = true;

    // exit gracefully: return a scaled value
    //
    return v2 * fac;
  }
}

// method: computeGammaAccrej
//
// arguments: none
//
// return: a float64 value containing a Gamma-distributed
//         random number.
//
// this method finds a random number on the range [0, inf]
// using the following algorithm:
//
//  Marsaglia, G., & Tsang, W. W. (2000). A simple method for generating
//  gamma variables. ACM Transactions on Mathematical Software, 26(3), 363-372.
//
// the acceptance-rejection method is used for the implementation.
//
float64 Random::computeGammaAccrej() {
  
  // declare local variables
  //
  float64 d, c, v = 0;
  float64 x,u;
  float64 result;
  
  // initialize the shape paramter (a):
  //  if the shape parameter is less than one, increase it?
  //
  float64 a = gacc_alpha_d;
  float64 boost = 1.0;
  
  if (a < (float64)1.0) {
    boost = exp(log(computeUniformSubtractive())/a);
    a++;
  }

  // compute the ????
  //
  d = a - 1.0/3;
  c = 1.0 / sqrt(9*d);
  
  
  // aaceptance- rejection: we use an infinite loop and generate samples
  // from a Gaussian distribution and reject them until a sample generated 
  // this way follow certain conditions that make it a Gamma sample and 
  // therefore become accepted and we break the loop. 
  //
  for(;;){

    // use rejection sampling to generate a v that is greater than zero
    //
    do{
      
      x = computeGaussianTransform();
      
      v = 1+c*x;	
    }while (v <= 0);
    
    v = v*v*v;
    x = x*x;

    // generate a uniform variable
    //
    u = computeUniformSubtractive();
    
    // if u pass certian conditions (in the below formula) then break the infinit loop 
    // and return (boost*d*v) as gamma random variable
    //
    if((u < 1-Random::ACCREJ_THRESHOLD*x*x) || 
       (log(u) < 0.5*x + d*(1-v+log(v))) ) break;
  }
  
  
  
  result = boost*d*v;
  

  
  // exit gracefully: return a scaled value
  //
  return(result);
  
}
