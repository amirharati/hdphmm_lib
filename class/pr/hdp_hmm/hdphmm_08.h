// file: hdphmm_08.cc
// version: $Id: hdphmm_08.cc  7/16/2013
//

// isip include files
//
#include "HDPHMM.h"

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
template <class emission_type>
bool8 HDPHMM<emission_type>::inference(VectorLong seeds,int32 max_itr,int32 init_itr,int32 burn_in,bool8 init,bool8 sample_emission_only){
  
  // loccal vars
  //
  VectorDouble internal_itr;
  internal_itr.assign(L"50");
  int32 itr_a = 0;

  burn_in_d = burn_in;
  
  // if true initilize; otherwise it is assumed that model is loaded 
  //
  if (init == true){
    sample_emissions_only_d=false;
    if (structure_type_d == HDPHMM::ERGODIC){
   
      // initilize
      //
      initilize(seeds,internal_itr);    
      
        
      // initilize hyper parameters
      //
      sample_hyper_init();
      
      // sample mixture parameters
      //
      sample_dist();

      //  store(L"init_dist",File::TEXT);
      
      // sample distribution parameters
      //
      sample_theta();

      //store(L"init_theta",File::TEXT);
     
    }
    else{

      // initilize
      //
      initilize_lr(seeds,internal_itr,init_itr);
      itr_a = init_itr;
    }
  }

  // just initilize the emissions
  //
  if (init == false and sample_emission_only == true ){
    sample_emissions_only_d=true;
    init_emissions(seeds,internal_itr);
      
    // sample mixture parameters
    //
    sample_dist();

      
    // sample distribution parameters
    //
    sample_theta();
  }
  
  //store(L"init",File::TEXT);
  // sample in a loop
  //
  for(int i = itr_a;i<max_itr;i++){

    //printf("itr %d \n",i);
    // sample data points
    //
    sample_data();
    //store(L"debug_sample_data",File::TEXT);
       
    // update sufficient stats
    //
    update_sstats();
    //store(L"debug_sstats",File::TEXT);
    
    
    // sample tables
    //
    sample_tables();
      //store(L"debug_tables",File::TEXT);
    
    // sample mixture parameters
    //
    sample_dist();
    
    // sample distribution parameters
    //
    sample_theta();
    //store(L"debug_theta2",File::TEXT);
    
    // sample hyper-parameters with 50 iteration
    //
    sample_hyper(50);
    //store(L"debug_hyper",File::TEXT);
    //printf("end ofloop %d %d %d \n",ix_d,iy_d,iz_d);
    // String DEBUG_FILE;
    //DEBUG_FILE.assign(L"debug_");
    //DEBUG_FILE.concat(i);
    //  store(DEBUG_FILE,File::TEXT);
	  
    // accumulate if we passed the burn in 
    //
    if ((i+iterations_d) > burn_in_d){
      accumulate();
    }
  }

  // total number of iterations
  //
  iterations_d += max_itr;
  
  // exit gacefully
  //
  return true;
}
