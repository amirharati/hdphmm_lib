// file: hdp_08.cc
// version: $Id: dpm_08.cc  7/16/2013
//

// isip include files
//
#include "HDP.h"

// method: inference
//
// arguments:
//  
//  
//
// return: bool8 value
//
// run inference algorithm
//
bool8 HDP::inference(VectorLong seeds,int32 max_itr,int32 burn_in,bool8 init){

  VectorDouble internal_itr;
  internal_itr.assign(L"50");


  // if true initilize; otherwise it is assumed that model is loaded 
  //
  if (init == true){
    
    initilize(seeds,internal_itr);    
    

    // initilize hyper parameters
    //
    sample_hyper_init();
    
    // sample mixture parameters
    //
    sample_dist();
       
    // sample distribution parameters
    //
    sample_theta();
  }

  burn_in_d = burn_in;
  if(is_master_d == true){
	for(int32 j = 0; j < (*slaves_d).length(); j++)
	  (*slaves_d)(j).burn_in_d = burn_in;
  }
  
  // sample in a loop
  //
  for(int i=0;i<max_itr;i++){

    // sample data points
    //
    sample_data();
     
    // update sufficient stats
    //
    update_sstats();
   
    // sample tables
    //
    sample_tables();
     
    // sample mixture parameters
    //
    sample_dist();
    
    // sample distribution parameters
    //
    sample_theta();
    
    // sample hyper-parameters with 50 iteration
    //
    sample_hyper(50);

    // accumulate if we passed the burn in 
    //
    if ((i+iterations_d) > burn_in_d){
      accumulate();
      if(is_master_d == true){
	for(int32 j = 0; j < (*slaves_d).length(); j++)
	  (*slaves_d)(j).accumulate();
      }
    }
  }

  // total number of iterations
  //
  iterations_d += max_itr;
  if(is_master_d == true){
	for(int32 j = 0; j < (*slaves_d).length(); j++)
	  (*slaves_d)(j).iterations_d = iterations_d;
  }
  // exit gacefully
  //
  return true;
}
