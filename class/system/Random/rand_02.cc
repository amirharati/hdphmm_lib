// file: $isip/class/system/Random/rand_02.cc
// version: $Id: rand_02.cc 5492 2000-11-13 00:46:50Z picone $
//

// isip include files
//
#include "Random.h"
#include <Console.h>

// method: diagnose
//
// arguments:
//  Integral::DEBUG level: (input) debug level for diagnostics
//
// return: a bool8 value indicating status
//
bool8 Random::diagnose(Integral::DEBUG level_a) {

  // declare local variables:
  //  we need to generate several sets of random numbers, so let's consolidate
  //  these variables
  //
  int32 N = 10000;
  int32 NC = 100;

  double avg;
  double stdev;
  double entropy;
  double z[3];
  double vals[N];
  double counts[NC];

  //----------------------------------------------------------------------
  //
  // 0. preliminaries
  //
  //----------------------------------------------------------------------

  // output the class name
  //
  if (level_a > Integral::NONE) {
    SysString output(L"diagnosing class ");
    output.concat(CLASS_NAME);
    output.concat(L": ");
    Console::put(output);
    Console::increaseIndention();
  }

  //---------------------------------------------------------------------
  //
  // 1. required public methods
  //
  //---------------------------------------------------------------------

  // set indentation
  //
  if (level_a > Integral::NONE) {
    Console::put(L"testing required public methods...\n");
    Console::increaseIndention();
  }

  // test the debug methods
  //
  setDebug(debug_level_d);
  
  if (level_a > Integral::BRIEF) {
    Random tmp;
    tmp.debug(L"debug");
  }
  
  // testing class constructors
  //
  Random rand_1;
  Random rand_2(rand_1);
  Random rand_3;

  // testing the operator= operator and assign method
  //
  rand_3 = rand_1;

  // testing i/o methods 
  //

  // testing the equality method
  //
  if (!rand_3.eq(rand_1)) {
    return Error::handle(name(), L"assign method/eq", Error::TEST,
			 __FILE__, __LINE__);
  }  
  if (!rand_2.eq(rand_1)) {
    return Error::handle(name(), L"copy constructor/eq", Error::TEST,
			 __FILE__, __LINE__);
  }
  
  // testing memory management methods
  //
  Random::setGrowSize((int32)500);

  for (int32 j = 1; j <= 10; j++) {
    Random** dyn_cal = new Random*[j * 100];
    
    // create the objects
    //
    for (int32 i = 0; i < j * 100; i++) {
      dyn_cal[i] = new Random();
    }
    
    // delete objects
    //
    for (int32 i = (j * 100) - 1; i >= 0; i--) {
      delete dyn_cal[i];
    }
      
    delete [] dyn_cal;
  }

  // reset indentation
  //
  if (level_a > Integral::NONE) {
    Console::decreaseIndention();
  }

  //---------------------------------------------------------------------
  //
  // 2. class-specific public methods
  //     set and get methods
  //
  //---------------------------------------------------------------------

  // set indentation
  //
  if (level_a > Integral::NONE) {
    Console::put(L"testing class-specific public methods: set and get methods...\n");
    Console::increaseIndention(); 
  }

  // set the algorithm
  //
  Random rand_4;

  if (!rand_4.setAlgorithm(UNIFORM)) {
    return Error::handle(name(), L"set algorithm", Error::TEST,
			 __FILE__, __LINE__);
  }
  
  // set the implementation
  //
  if (!rand_4.setImplementation(SUBTRACTIVE)) {
    return Error::handle(name(), L"set implementation", Error::TEST,
			 __FILE__, __LINE__);
  }

  // get the algorithm
  //
  if (rand_4.getAlgorithm() != UNIFORM) {
    return Error::handle(name(), L"get algorithm", Error::TEST,
			 __FILE__, __LINE__);
  }
  
  // get the implementation
  //
  if (rand_4.getImplementation() != SUBTRACTIVE) {
    return Error::handle(name(), L"get implementation", Error::TEST,
			 __FILE__, __LINE__);
  }

  // seed a value
  //
  if (!rand_4.seed(27)) {
    return Error::handle(name(), L"seed", Error::TEST, __FILE__, __LINE__);
  }
  
  // get a value
  //
  float64 x = Random::GLOBAL_UNIFORM.get();
  if ((x < 0) || (x > 1.0)) {
    return Error::handle(name(), L"get", Error::TEST, __FILE__, __LINE__);
  }
  
  // get a value using a cast
  //
  float64 y = (float64)Random::GLOBAL_UNIFORM;
  if ((y < 0) || (y > 1.0)) {
    return Error::handle(name(), L"cast", Error::TEST, __FILE__, __LINE__);
  }

  // reset indentation
  //
  if (level_a > Integral::NONE) {
    Console::decreaseIndention();
  }

  //---------------------------------------------------------------------
  //
  // 3. class-specific public methods
  //     initialization and computational methods for Uniform
  //
  //---------------------------------------------------------------------
  
  // set indentation
  //
  if (level_a > Integral::NONE) {
    Console::put(L"testing class-specific public methods: uniform compute methods...\n");
    Console::increaseIndention(); 
  }

  // set the seed
  //
  if (!rand_4.seed(1)) {
    return Error::handle(name(), L"seed", Error::TEST, __FILE__, __LINE__);
  }

  // check the exact numbers being produced:
  //  for the default algorithm, and a seed = 1, the results should
  //  be as shown below.
  //
  z[0] = rand_4.compute();
  z[1] = rand_4.compute();
  z[2] = rand_4.compute();

  if ((!Integral::almostEqual((float64)0.298227, (float64)z[0])) ||
      (!Integral::almostEqual((float64)0.715119, (float64)z[1])) ||
      (!Integral::almostEqual((float64)0.033021, (float64)z[2]))) {
    return Error::handle(name(), L"compute", Error::TEST, __FILE__, __LINE__);
  }

  // compute some random numbers
  //
  for (int32 i = 0; i < N; i++) {
    vals[i] = rand_4.compute();
  }

  // compute and check the average
  //
  avg = 0;
  for (int32 i = 0; i < N; i++) {
    avg += vals[i];
  }
  avg /= (float64)N;

  if (!Integral::almostEqual((float64)avg, (float64)0.5, 1.0)) {
    return Error::handle(name(), L"compute", Error::TEST, __FILE__, __LINE__);
  }

  // histogram the data
  //
  MemoryManager::memset(counts, 0, sizeof(float64) * NC);

  for (int32 i = 0; i < N; i++) {
    int32 index = (int32)Integral::floor(vals[i] * NC);
    counts[index]++;
  }

  // check the overall statistics by computing the entropy
  //
  entropy = 0;
  for (int32 i = 0; i < NC; i++) {
    counts[i] /= (float64)N;
    if (counts[i] != 0) {
      entropy -= counts[i] * Integral::log2(counts[i]);
    }
    else {
      return Error::handle(name(), L"compute", Error::TEST,
			   __FILE__, __LINE__);
    }
  }      
  entropy = Integral::exp2(entropy);

  if (!Integral::almostEqual((float64)entropy, (float64)NC, 1.0)) {
    return Error::handle(name(), L"compute", Error::TEST, __FILE__, __LINE__);
  }

  // reset indentation
  //
  if (level_a > Integral::NONE) {
    Console::decreaseIndention();
  }
  
  //---------------------------------------------------------------------
  //
  // 4. class-specific public methods
  //     initialization and computational methods for Gaussian
  //
  //---------------------------------------------------------------------
  
  // set indentation
  //
  if (level_a > Integral::NONE) {
    Console::put(L"testing class-specific public methods: Gaussian compute methods...\n");
    Console::increaseIndention(); 
  }

  // set the generator: let the seed default
  //
  Random rand_5(GAUSSIAN, TRANSFORMATION);

  // set the seed
  //
  if (!rand_5.seed(1)) {
    return Error::handle(name(), L"seed", Error::TEST, __FILE__, __LINE__);
  }

  // check the exact numbers being produced:
  //  for the default algorithm, and a seed = 1, the results should
  //  be as shown below.
  //
  z[0] = rand_5.compute();
  z[1] = rand_5.compute();
  z[2] = rand_5.compute();

  if ((!Integral::almostEqual((float64) 1.059816, (float64)z[0])) ||
      (!Integral::almostEqual((float64)-0.994063, (float64)z[1])) ||
      (!Integral::almostEqual((float64) 2.208976, (float64)z[2]))) {
    return Error::handle(name(), L"compute", Error::TEST, __FILE__, __LINE__);
  }

  // check Gaussian
  //
  for (int32 i = 0; i < N; i++) {
    vals[i] = rand_5.compute();
  }

  // compute and check the average
  //
  avg = 0;
  for (int32 i = 0; i < N; i++) {
    avg += vals[i];
  }
  avg /= (float64)N;

  if (!Integral::almostEqual(avg, (float64)0.0, 1.0, 1.0)) {
    return Error::handle(name(), L"compute", Error::TEST, __FILE__, __LINE__);
  }

  // compute the stdev
  //
  stdev = 0;
  for (int32 i = 0; i < N; i++) {
    stdev += (vals[i] - avg) * (vals[i] - avg);
  }
  stdev = sqrt(stdev / (float64)N);

  if (!Integral::almostEqual(stdev, (float64)1.0, 1.0, 1.0)) {
    return Error::handle(name(), L"compute", Error::TEST, __FILE__, __LINE__);
  }

  // reset indentation
  //
  if (level_a > Integral::NONE) {
    Console::decreaseIndention();
  }

  //---------------------------------------------------------------------
  //
  // 5. class-specific public methods
  //     initialization and computational methods for Gamma
  //
  //---------------------------------------------------------------------
  
  // set indentation
  //
  if (level_a > Integral::NONE) {
    Console::put(L"testing class-specific public methods: Gamma compute methods...\n");
    Console::increaseIndention(); 
  }

  // set the generator: let the seed default
  //
  Random rand_6(GAMMA, ACCREJ);

  // set params
  //
  rand_6.setParameters(1);

  // set the seed
  //
  if (!rand_6.seed(1)) {
    return Error::handle(name(), L"seed", Error::TEST, __FILE__, __LINE__);
  }

  // check the exact numbers being produced:
  //  for the default algorithm, and a seed = 1, the results should
  //  be as shown below.
  //
  z[0] = rand_6.compute();
  z[1] = rand_6.compute();
  z[2] = rand_6.compute();
  
  if ((!Integral::almostEqual((float64) 1.960404, (float64)z[0])) ||
      (!Integral::almostEqual((float64) 0.139847, (float64)z[1])) ||
      (!Integral::almostEqual((float64) 1.253779, (float64)z[2]))) {
    return Error::handle(name(), L"compute", Error::TEST, __FILE__, __LINE__);
  }

  // check Gaussian
  //
  for (int32 i = 0; i < N; i++) {
    vals[i] = rand_6.compute();
  }

  // compute and check the average
  //
  avg = 0;
  for (int32 i = 0; i < N; i++) {
    avg += vals[i];
  }
  avg /= (float64)N;

  if (!Integral::almostEqual(avg, (float64)1.0089, 1.0, 1.0)) {
    return Error::handle(name(), L"compute", Error::TEST, __FILE__, __LINE__);
  }


  
  //---------------------------------------------------------------------
  //
  // 6. class-specific public methods:
  //     global generator manipulation methods
  //
  //---------------------------------------------------------------------
  
  // set indentation
  //
  if (level_a > Integral::NONE) {
    Console::put(L"testing class-specific public methods: global methods...\n");
    Console::increaseIndention(); 
  }

  // set the seed
  //
  Random::GLOBAL_UNIFORM.seed((int32)9);

  if (GLOBAL_UNIFORM.seed_d != 9) {
    return Error::handle(name(), L"seed", Error::TEST,
			 __FILE__, __LINE__);
  }

  // check the exact numbers being produced:
  //  for the default algorithm, and a seed = 9, the results should
  //  be as shown below.
  //
  z[0] = Random::GLOBAL_UNIFORM.get();
  z[1] = Random::GLOBAL_UNIFORM.get();
  z[2] = Random::GLOBAL_UNIFORM.get();
  
  if ((!Integral::almostEqual((float64)0.412655, (float64)z[0])) ||
      (!Integral::almostEqual((float64)0.852002, (float64)z[1])) ||
      (!Integral::almostEqual((float64)0.088358, (float64)z[2]))) {
    return Error::handle(name(), L"compute", Error::TEST, __FILE__, __LINE__);
  }

  // set the seed
  //
  Random::GLOBAL_GAUSSIAN.seed((int32)9);

  if (GLOBAL_GAUSSIAN.seed_d != 9) {
    return Error::handle(name(), L"seed", Error::TEST,
			 __FILE__, __LINE__);
  }

  // check the exact numbers being produced:
  //  for the default algorithm, and a seed = 9, the results should
  //  be as shown below.
  //
  z[0] = Random::GLOBAL_GAUSSIAN.get();
  z[1] = Random::GLOBAL_GAUSSIAN.get();
  z[2] = Random::GLOBAL_GAUSSIAN.get();

  if ((!Integral::almostEqual((float64)1.099949, (float64)z[0])) ||
      (!Integral::almostEqual((float64)-0.272938, (float64)z[1])) ||
      (!Integral::almostEqual((float64)-1.116281, (float64)z[2]))) {
    return Error::handle(name(), L"compute", Error::TEST, __FILE__, __LINE__);
  }

  // set the seed
  //
  Random::GLOBAL_GAMMA.seed((int32)1);

  // set shape parameter
  //
  Random::GLOBAL_GAMMA.setParameters(1);

  if (GLOBAL_GAMMA.seed_d != 1) {
    return Error::handle(name(), L"seed", Error::TEST,
			 __FILE__, __LINE__);
  }

  // check the exact numbers being produced:
  //  for the default algorithm, and a seed = 1, the results should
  //  be as shown below.
  //
  z[0] = Random::GLOBAL_GAMMA.get();
  z[1] = Random::GLOBAL_GAMMA.get();
  z[2] = Random::GLOBAL_GAMMA.get();

  if ((!Integral::almostEqual((float64) 1.960404, (float64)z[0])) ||
      (!Integral::almostEqual((float64) 0.139847, (float64)z[1])) ||
      (!Integral::almostEqual((float64) 1.253779, (float64)z[2]))) {
    return Error::handle(name(), L"compute", Error::TEST, __FILE__, __LINE__);
  }

  // reset indentation
  //
  if (level_a > Integral::NONE) {
    Console::decreaseIndention();
  }
  
  //---------------------------------------------------------------------
  //
  // 7. print completion message
  //
  //---------------------------------------------------------------------

  // reset indentation
  //
  if (level_a > Integral::NONE) {
    Console::decreaseIndention();
  }
  
  if (level_a > Integral::NONE) {
    SysString output(L"diagnostics passed for class ");
    output.concat(name());
    output.concat(L"\n");
    Console::put(output);
  }

  // exit gracefully
  //
  return true;
}

