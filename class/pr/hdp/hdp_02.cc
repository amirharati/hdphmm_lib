// file: hdp_02.cc
// version: hdp_02.cc  2013-07-25 Amir Harati $
//

// isip include files
//
#include "HDP.h"
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
bool8 HDP::diagnose(Integral::DEBUG level_a) {


  // an example program
  //
  HDP master;
  Vector<HDP> slaves;
  slaves.setLength(2);

  master.setMaster(slaves);
  master.use_one_database(false);


  Database db1,db2;
  VectorFloat params;
  params.assign(L"10,0,10,1,10,1,.1,5");
  master.set_hyper_parameters(params);  
  db1.init(L"hdp_test_g1.sof");
  slaves(0).set_db(db1);
  db2.init(L"hdp_test_g1.sof");
  slaves(1).set_db(db2);
 




  // initilize
  //
  VectorLong seeds(6);
  VectorDouble  internal_itr;
  seeds.assign(L"3100,10100,10001,20000,61098,100023");
  internal_itr.assign(L"50");
   
  master.inference(seeds,200,100);
   
  
  master.store(L"master_out.text",File::TEXT);

  slaves(0).store(L"slave0_out.text",File::TEXT);
  slaves(1).store(L"slave1_out.text",File::TEXT);
  
  master.load(seeds,L"master_out.text");
   
  // exit gracefully
  //
  return true;
}

