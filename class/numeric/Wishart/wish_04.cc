// file: wish_04.cc
// version: $Id: wish_04.cc 2013-07-18  Amir Harati $
//

// isip include files
//
#include "Wishart.h"
#include <Console.h>


// method: init
//
// arguments: none
//
// return: a bool8 value indicating status
//
// this method pre-computes various constants used in this class
//
bool8 Wishart::init() {

  if ((algorithm_d == FORWARD) &&
	   (implementation_d == TRANSFORMATION)) {
    rnd1_d.setAlgorithm(Random::GAUSSIAN);
    rnd1_d.setImplementation(Random::TRANSFORMATION);
    rnd1_d.seed(seed_d);
    rnd2_d.setAlgorithm(Random::GAMMA);
    rnd2_d.setImplementation(Random::ACCREJ);
    rnd2_d.seed(seed_d);
  }
  else if ((algorithm_d == INVERSE) &&
	   (implementation_d == TRANSFORMATION)) {
    rnd1_d.setAlgorithm(Random::GAUSSIAN);
    rnd1_d.setImplementation(Random::TRANSFORMATION);
    rnd1_d.seed(seed_d);
    rnd2_d.setAlgorithm(Random::GAMMA);
    rnd2_d.setImplementation(Random::ACCREJ);
    rnd2_d.seed(seed_d);
  }

  // check algorithm: unknown
  //
  else {
    return Error::handle(name(), L"init",
			 Error::ARG, __FILE__, __LINE__);
  }  

  // exit gracefully
  //
  result_d.setDimensions(dim1_d,dim2_d);
  temp_result_d.setDimensions(dim1_d,dim2_d);
  is_valid_d=true;
  return true;
}


// method: compute
//
// arguments: none
//
// return: a VectorFloat value containing a random vector
//
// this method selects the appropriate computational method
//
bool8 Wishart::compute() {

  // check valid flag
  //
  if (!is_valid_d) {
    init();
  }
  
  
  // check algorithm: WISHART
  //
  if (algorithm_d == FORWARD) {
    
    // check implementations
    //
    if (implementation_d == TRANSFORMATION) {
      computeWishart();
    }
    else {
      return Error::handle(name(), L"compute",
			   Error::ARG, __FILE__, __LINE__);
    }
  }
  else if (algorithm_d == INVERSE){
    // check implementations
    //
    if (implementation_d == TRANSFORMATION) {
      computeiWishart();
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
      
      for (int i = 0; i< result_d.getNumRows();i++){
	for(int j=0; j< result_d.getNumColumns();j++){
	  value.concat((float64)result_d(i,j));
	  value.concat(L",");
	}
	value.concat("\n");
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

// method: computeWishart
//
// arguments: none
//
// return: result will contail sqrt of sigma
//     
// this method finds a random number within the default range
// using an algorithm modeled from:
//
// 
//
bool8 Wishart::computeWishart() {
  
  // first compute the inverse Wishart
  //
  computeiWishart();

  // invert the result
  //
  result_d.inverse();
  result_d.transpose();
  
  // exit gracefully: return a scaled value
  //
  return(true);
  
}


// method: computeiWishart
//
// arguments: none
//
// return: result will contain sqrt of inv-sigma 
//
// this method finds a random number within the default range
// using an algorithm modeled from:
//
// 
//
bool8 Wishart::computeiWishart() {
  
  // if  Sigma_DI is equal to Sigma then calculate CHolesky decomposition
  //
  if (Using_Sigma_d == true){
    Sigma_DI_d.decompositionCholesky(Sigma_DI_d);
    Sigma_DI_d.inverse();
    
    Using_Sigma_d = false;
  }
  genWishart(DF_d/2.0);
  
  result_d.mult(temp_result_d,Sigma_DI_d);
  result_d.mult(Wishart::SQRTT); // multiply with sqrt(2) 

  // exit gracefully: return a scaled value
  //
  return true;
  
}

// method: genWishart
//
// arguments: none
//
// return: helping function for computeiWishart
//
//p(X) = |X|^(a-(d+1)/2)*exp(-tr(X))/Gamma_d(a)
//
// this method finds a random number within the default range
// using an algorithm modeled from:
//
// 

bool8 Wishart::genWishart(double a) {

  MatrixDouble temp_result(dim1_d,dim2_d);
  for (int i= 0; i< dim1_d; i++)
    for (int j=0; j < dim2_d; j++)
      temp_result.setValue(i,j,rnd1_d.get()*Wishart::SQRTH);
  temp_result_d.makeUpper(temp_result);

  for (int i= 0; i< dim1_d; i++){
    
    rnd2_d.setParameters(a-(i*.5));
    temp_result_d.setValue(i,i,sqrt(rnd2_d.get()));
  }
  temp_result_d.changeType(Integral::UPPER_TRIANGULAR);

  // exit gracefully: return a scaled value
  //
  return true;
  
}

