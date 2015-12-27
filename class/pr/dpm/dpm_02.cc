// file: dpm_02.cc
// version: dpm_02.cc  2013-07-25 Amir Harati $
//

// isip include files
//
#include "DPM.h"
#include <Console.h>

// method: diagnose
//
// arguments:
//  Integral::DEBUG level: (input) debug level for diagnostics
//
// return: a bool8 value indicating status
//
// this is the diagnose method
//
bool8 DPM::diagnose(Integral::DEBUG level_a) {

  // a small usage example
  //

  DPM dpm1;
  VectorFloat params;
  Database db;
  
  params.setLength(6);
  params(0)=10; //Ks_d
  params(1)=IW_N; // prior
  params(2)=10; params(3)=1; // sigma (a,b)
  params(4)=.1; params(5)=5; // kappa, nu

  dpm1.set_hyper_parameters(params);
  dpm1.setDebug(Integral::NONE);
  db.init(L"dpm_test.sof");
  dpm1.set_db(db);

  // initilize
  //
  VectorLong seeds(6);
  VectorDouble  internal_itr;
  seeds.assign(L"3100,10100,10001,20000,61098,100023");
  internal_itr.assign(L"50");
 
  // inference
  // 
  dpm1.inference(seeds,100,50);  // burin 50, itr:100

  // store the model in raw format
  //
  dpm1.store(L"model_raw.text",File::TEXT);
  
  // load the model
  // 
  dpm1.load(seeds,L"model_raw.text");
   
  dpm1.extract_model(L"model_raw.text",L"model_extracted.text",File::TEXT);

  dpm1.load_final_model(L"model_extracted.text",db);

  // calculate the  log likelihoods
  dpm1.observation_likelihood();

  // exit gracefully
  //
  return true;

}

