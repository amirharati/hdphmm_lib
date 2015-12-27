// file: hdp_09.cc
// version: $Id: hdp_09.cc  7/16/2013
//

// isip include files
//
#include "HDP.h"
#include <Console.h>

// method: initilize
//
// arguments: 
//  
// seeds: seeds for initilizing random generators  
//
// return: bool8 value
//
// initilize variables
//
bool8 HDP::initilize(VectorLong seeds, VectorDouble other_params){

  // print a message based on verbosity level
  //
  if ( verbosity_d > Integral::NONE || debug_level_d > Integral::NONE){
    Console::increaseIndention();
    Console::put(L"initilize()");
    Console::decreaseIndention();
  }

  

  if (seeds.length() !=6){
    // error message
    //
    return Error::handle(name(), L"seeds vector for HDP should be of length 6.", Error::ARG, __FILE__, __LINE__);

  }
  if (other_params.length() != 1){

    // error message
    //
    return Error::handle(name(), L"other_params length should be 1.", Error::ARG, __FILE__, __LINE__);
  }

  if (is_master_d == true && one_database_d == true){
    
    // set dimension
    // 
    dim_d = db_d->dim_d;
  }
  else if (is_master_d == true && one_database_d == false){
    dim_d = (*slaves_d)(0).db_d->dim_d;
  }
  else if(is_slave_d == true){
    dim_d = (*master_d).dim_d;
  }
  
  // iteration 
  //
  iterations_d = 0;
  burn_in_d = 0;
  itr_acc_d = 0;


  // local variables
  //
  VectorDouble zero_vec1(dim_d);
  VectorDouble zero_vec2(dim_d*dim_d);
  MatrixDouble zero_matrix;
  
  zero_matrix.setDimensions(dim_d,dim_d,false);
  

  // number of iterations for IWN sampling
  //
  internal_itr_d = (int32)other_params(0);

  // set the size and initial values for theta members
  //
  theta_d.invSigma.setLength(Ks_d,false);
  theta_d.invSigma.assign(zero_matrix);
 
  // set  the size of mean matrix
  //
  theta_d.mu.setLength(Ks_d,false);
  theta_d.mu.assign(zero_vec1);

  // set the size and initial values for theta members
  //
  theta_d.invSigma_acc.setLength(Ks_d,false);
  theta_d.invSigma_acc.assign(zero_matrix);
 
  // set  the size of mean matrix
  //
  theta_d.mu_acc.setLength(Ks_d,false);
  theta_d.mu_acc.assign(zero_vec1);


  // cholinvSigma and dcholinvSigma
  //
  theta_d.cholinvSigma.setLength(Ks_d,false);
  theta_d.cholinvSigma.assign(zero_matrix);
  theta_d.dcholinvSigma.setLength(Ks_d,false);
  theta_d.mu.assign(zero_vec1);

  // set the size and initial values for sstats members
  //
  sstats_d.cards.setLength(Ks_d,false);
  sstats_d.YY.setLength(Ks_d,false);
  sstats_d.YY.assign(zero_matrix); 
  sstats_d.sumY.setLength(Ks_d,false);
  sstats_d.sumY.assign(zero_vec1);
  
  dist_struct_d.pi_s_acc.setLength(Ks_d,false);
  dist_struct_d.beta_vec_acc.setLength(Ks_d,false);

  // initilize cluster counts to zero
  //
  counts_d.Ns.setLength(Ks_d,false);

  // set M
  //
  counts_d.M.setDimensions(Kg_d,Ks_d,false);
 
  // initilize Random generators
  //

  // initilize Random Dirichlet generator
  //
  dir_dist_d.seed(seeds(0));
 
 // initilize Random multinominal generator (using Dirichlet)
 //
  multi_dist_d.seed(seeds(1));
 
  //  initilize inverse Wishart generator
  //
  iwishart_dist_d.setAlgorithm(Wishart::INVERSE);
  iwishart_dist_d.setImplementation(Wishart::TRANSFORMATION);
  iwishart_dist_d.seed(seeds(2));
 
  // initilize Normal vecotr generator
  //
  norm_gen_d.setAlgorithm(Random::GAUSSIAN);
  norm_gen_d.setImplementation(Random::TRANSFORMATION);
  norm_gen_d.seed(seeds(3));
 
  // initilize uniform vector generator
  //
  uniform_gen_d.setAlgorithm(Random::UNIFORM);
  uniform_gen_d.setImplementation(Random::SUBTRACTIVE);
  uniform_gen_d.seed(seeds(4));
  
  // initilize gamma random generator
  //
  gamma_rand_d.setAlgorithm(Random::GAMMA);
  gamma_rand_d.setImplementation(Random::ACCREJ);
  gamma_rand_d.seed(seeds(5));

  
  // a master object has no database attached to it necessarily so the following steps are just for slaves
  //
 
  if ( is_master_d == false){
    mixture_index_d.setLength(db_d->get_records_no(),false);
    mixture_index_d.setDebug(debug_level_d);
    
    VectorLong T(db_d->get_records_no());
    
    // loop over all data points
    //
    for (int32 data_records = 0; data_records < db_d->get_records_no(); data_records++){
      
      // read the data
      //
      db_d->get(); 
      
      // seqeuece length
      //
      T (data_records) = db_d->curr_data_d.getNumColumns();
      
      mixture_index_d(data_records).setLength(T(data_records),false);
      
      // initilize to -1
    //
      for (int32 i = 0; i < T(data_records);i++)
	mixture_index_d(data_records)(i) = -1;
 
    }
  }


  if (is_master_d == true && one_database_d == true){
    mixture_index_d.setLength(db_d->get_records_no(),false);
    VectorLong T(db_d->get_records_no());

    // loop over all data points
    //
    for (int32 data_records = 0; data_records < db_d->get_records_no(); data_records++){
      
      // read the data
      //
      db_d->get(); 
      
      // seqeuece length
      //
      T (data_records) = db_d->curr_data_d.getNumColumns();
      
      mixture_index_d(data_records).setLength(T(data_records),false);
      
      // initilize to -1
      //
      for (int32 i = 0; i < T(data_records);i++)
	mixture_index_d(data_records)(i) = -1;
    }

    
  }
  

  // intilize the params
  //
  params_d.nu_delta.assign(zero_matrix);
  params_d.M.assign(zero_vec1);
 
  if(init_params()!= true)
    return Error::handle(name(), L"initilize", Error::ARG, __FILE__, __LINE__);
 
  // call salves
  //
  if (is_master_d == true){

    for(int32 i = 0;i < slaves_d->length();i++){
      
       (*slaves_d)(i).initilize(seeds,other_params);
    }
  }


  header_info_d.assign(L"\n Emission_type : ");
  header_info_d.concat((*master_d).name());
  header_info_d.concat(L"\nKs = ");
  header_info_d.concat(Ks_d);
  header_info_d.concat(L"\n prior_type: ");
  switch(priorType_d){
  case NIW:
    header_info_d.concat(L"\nNIW");
    break;
  case IW_N:
    header_info_d.concat(L"\nIW_N");
    break;
  };


  // exit gracefully
  //
  return true;
}


// method: init_params
//
// arguments: 
//  
//  
//
// return: bool8 value
//
// initilize hyper-parameters
//
bool8 HDP::init_params(){
  
  // print a message based on verbosity level
  //
  if ( verbosity_d > Integral::NONE || debug_level_d > Integral::NONE){
    Console::increaseIndention();
    Console::put(L"init_params()");
    Console::decreaseIndention();
  }

  // local varaibles
  //
  VectorDouble data_v;
  MatrixDouble u;
  MatrixDouble meanSigma;
  
  meanSigma.setDimensions(dim_d,dim_d,false);

  VectorDouble zero_vec1(dim_d);
  MatrixDouble zero_mat(dim_d,dim_d);

  
  // NIW params
  //
  params_d.K = prior_hyper_params_d(0);
  
  params_d.M.assign(zero_vec1);
    
  // IWN params
  //
  params_d.cholSigma.assign(zero_mat);
  params_d.Lambda.assign(zero_mat);
  params_d.theta.assign(zero_vec1);
  
  // total number of data points which is the total number
  // of frames of all sequences (sum(Ti))
  //
  int64 counts = 0;
 
  // if  the object is a master and each slave has its own database
  //
  if (is_master_d == true && one_database_d == false){
   

    // loop over slaves
    //
    for(int32 i = 0; i < (*slaves_d).length();i++){
      // loop over all data points
      //
      for (int32 data_records = 0; data_records < (*slaves_d)(i).db_d->get_records_no(); data_records++){
	
	// read data
	//
	(*slaves_d)(i).db_d->get();
	
	// loop over a sequence
	//
	// seq.  length
	//
	int32 T = (*slaves_d)(i).db_d->curr_data_d.getNumColumns();
	
	for (int32 seq_t = 0; seq_t < T; seq_t++){
	  
	  (*slaves_d)(i).db_d->curr_data_d.getColumn(data_v,seq_t);
	  
	  // add to params_d.M
	  //
	  params_d.M.add(data_v);
	  counts ++;
	}    
      }
    }

    // M  is the average of all data points
    //
    params_d.M.div(counts);
     
   
    for(int32 i = 0 ; i < (*slaves_d).length();i++){
      // loop over all data points
      //
      for (int32 data_records = 0; data_records < (*slaves_d)(i).db_d->get_records_no(); data_records++){
      
	// read data
	//
	(*slaves_d)(i).db_d->get();
      
	// loop over a sequence
	//
	// seq.  length
	//
	int32 T = (*slaves_d)(i).db_d->curr_data_d.getNumColumns();
      
	for (int32 seq_t = 0; seq_t < T; seq_t++){
	
	  (*slaves_d)(i).db_d->curr_data_d.getColumn(data_v,seq_t);
	
	  // subtract the mean
	  // 
	  data_v.sub(params_d.M);
	
	  // compute the covarince
	  //
	  u.outerProduct(data_v,data_v);
	  meanSigma.add(u);
	}
      }
    }

    // devide by the number of records
    //
    meanSigma.div(counts);
    

    // IWN params
    //
    meanSigma.decompositionCholesky(params_d.cholSigma); 
    params_d.cholSigma.transpose();
    params_d.Lambda.assign(params_d.cholSigma);
    params_d.Lambda.transpose();
    params_d.Lambda.changeType(Integral::FULL);
    params_d.Lambda.mult(params_d.cholSigma);
    params_d.Lambda.inverse();
    MatrixDouble tmp;
    tmp.transpose(params_d.Lambda);
    params_d.Lambda.setLower(tmp);
    
    params_d.Lambda.multv(params_d.theta,params_d.M);

    // nu
    //
    params_d.nu = prior_hyper_params_d(1);
    
    // nu_delta
    //
    params_d.nu_delta.assign(meanSigma);
    params_d.nu_delta.mult(((float32)params_d.nu-dim_d-1));



    // loop over slaves and copy
    //
    for (int32 slaves_i = 0; slaves_i < slaves_d->length(); slaves_i++){
      (*slaves_d)(slaves_i).params_d.M.assign(params_d.M);
      (*slaves_d)(slaves_i).params_d.nu = params_d.nu;
      (*slaves_d)(slaves_i).params_d.nu_delta.assign(params_d.nu_delta);
    }
    
  }

  // if the object is a master and there is just one database (like HDP-HMM)
  //
  if ( is_master_d == true && one_database_d == true){

// loop over all data points
    //
    for (int32 data_records = 0; data_records < db_d->get_records_no(); data_records++){
      
      // read data
      //
      db_d->get();
      
      // loop over a sequence
      //
      // seq.  length
    //
      int32 T = db_d->curr_data_d.getNumColumns();
      
      for (int32 seq_t = 0; seq_t < T; seq_t++){

	db_d->curr_data_d.getColumn(data_v,seq_t);
	
	// add to params_d.M
	//
	params_d.M.add(data_v);
	counts ++;
      }    
    }
    
    // M  is the average of all data points
    //
    params_d.M.div(counts);
    
    
    // loop over all data points
    //
    for (int32 data_records = 0; data_records < db_d->get_records_no(); data_records++){
      
      // read data
      //
      db_d->get();
      
      // loop over a sequence
      //
      // seq.  length
      //
      int32 T = db_d->curr_data_d.getNumColumns();
      
      for (int32 seq_t = 0; seq_t < T; seq_t++){
	
	db_d->curr_data_d.getColumn(data_v,seq_t);
	
	// subtract the mean
	// 
	data_v.sub(params_d.M);
	
	// compute the covarince
	//
	u.outerProduct(data_v,data_v);
	meanSigma.add(u);
      }
    }

    // devide by the number of records
    //
    meanSigma.div(counts);
    
    // IWN params
    //
    meanSigma.decompositionCholesky(params_d.cholSigma); 
    params_d.cholSigma.transpose();
    //params_d.cholSigma.debug(L"choligma");
    params_d.Lambda.assign(params_d.cholSigma);
    params_d.Lambda.transpose();
    params_d.Lambda.changeType(Integral::FULL);
    params_d.Lambda.mult(params_d.cholSigma);
    params_d.Lambda.inverse();
    MatrixDouble tmp;
    tmp.transpose(params_d.Lambda);
    params_d.Lambda.setLower(tmp);
    
    params_d.Lambda.multv(params_d.theta,params_d.M);

    // nu
    //
    params_d.nu = prior_hyper_params_d(1);
    
    // nu_delta
    //
    params_d.nu_delta.assign(meanSigma);
    params_d.nu_delta.mult(((float32)params_d.nu-dim_d-1));

    
    // loop over slaves and copy
    //
    for (int32 slaves_i = 0; slaves_i < slaves_d->length(); slaves_i++){
      (*slaves_d)(slaves_i).params_d.M.assign(params_d.M);
      (*slaves_d)(slaves_i).params_d.nu = params_d.nu;
      (*slaves_d)(slaves_i).params_d.nu_delta.assign(params_d.nu_delta);
    }

  }

 if (debug_level_d > Integral::NONE){
   Console::increaseIndention();
   params_d.K.debug(L"K");
   params_d.M.debug(L"M");
   params_d.nu.debug(L"nu");
   meanSigma.debug(L"meanSigma");
   params_d.nu_delta.debug(L"nu_delta");
   Console::decreaseIndention();
 }
  // exit gracefully
  //
  return true;
}


// method: set_hyper_parameters
//
// arguments: 
//  
//  
//
// return: bool8 value
//
//set hyper-parameters
//
bool8 HDP::set_hyper_parameters(VectorFloat hyper_parameters){


  if(is_master_d == true){
    Kg_d = (*slaves_d).length();
  }
  else if(is_slave_d == true){
    Kg_d = (*master_d).Kg_d;
  }

  if(hyper_parameters.length () != 8 and hyper_parameters.length () != 9){
    return Error::handle(name(), L"set_hyper_parameters", Error::ARG, __FILE__, __LINE__);
  }
  else{

    if (hyper_parameters.length () == 8){
      hyper_params_vec_d.assign(hyper_parameters);
    
      Ks_d =(int32) hyper_parameters(0);
      Kc_d = Ks_d;
    
      switch((int32)hyper_parameters(1)){
      case 0:
	priorType_d = NIW;
	break;
      case 1:
	priorType_d = IW_N;
	break;
	
      default:
	// error message
	//
	return Error::handle(name(), L"The second entry (prior type) is not recognized.", Error::ARG, __FILE__, __LINE__);
	break;
      
      }

      HDP_hyper_params_d.setLength(4);
      prior_hyper_params_d.setLength(2);

      HDP_hyper_params_d(0) = hyper_parameters(2);
      HDP_hyper_params_d(1) = hyper_parameters(3);
      HDP_hyper_params_d(2) = hyper_parameters(4);
      HDP_hyper_params_d(3) = hyper_parameters(5);
      prior_hyper_params_d(0) = hyper_parameters(6);
      prior_hyper_params_d(1) = hyper_parameters(7);
    }
    if(hyper_parameters.length () == 9){
      
      hyper_params_vec_d.assign(hyper_parameters);
      
      Ks_d =(int32) hyper_parameters(0);
      Kc_d = (int32) hyper_parameters(1);
    
      switch((int32)hyper_parameters(2)){
      case 0:
	priorType_d = NIW;
	break;
      case 1:
	priorType_d = IW_N;
	break;
	
      default:
	// error message
	//
	return Error::handle(name(), L"The second entry (prior type) is not recognized.", Error::ARG, __FILE__, __LINE__);
	break;
      
      }

      HDP_hyper_params_d.setLength(4);
      prior_hyper_params_d.setLength(2);

      HDP_hyper_params_d(0) = hyper_parameters(3);
      HDP_hyper_params_d(1) = hyper_parameters(4);
      HDP_hyper_params_d(2) = hyper_parameters(5);
      HDP_hyper_params_d(3) = hyper_parameters(6);
      prior_hyper_params_d(0) = hyper_parameters(7);
      prior_hyper_params_d(1) = hyper_parameters(8);
    }
  }

  if ( is_master_d == true){
    
    // copy for slaves
    //
    for(int32 i = 0; i < (*slaves_d).length();i++){
      
      (*slaves_d)(i).set_hyper_parameters(hyper_parameters);
    }
  }

  // add header
  //
  header_info_d.assign(L"\n Emission_type : ");
  header_info_d.concat((*master_d).name());
  header_info_d.concat(L"\nKs = ");
  header_info_d.concat(Ks_d);
  header_info_d.concat(L"\n prior_type: ");

  switch(priorType_d){
  case NIW:
    header_info_d.concat(L"\nNIW");
    break;
  case IW_N:
    header_info_d.concat(L"\nIW_N");
    break;
  };

  
  return true;
}


// method: sample_hyper_init
//
// arguments: 
//  
//  
//
// return: bool8 value
//
// initilize hyper-parameters
//
bool8 HDP::sample_hyper_init(){

  // print a message based on verbosity level
  //
  if ( verbosity_d > Integral::NONE || debug_level_d > Integral::NONE){
    Console::increaseIndention();
    Console::put(L"sample_hyper_init()");
    Console::decreaseIndention();
  }
  
  // initilize sigma
  //
  hyper_d.sigma = HDP_hyper_params_d(0)/HDP_hyper_params_d(1);

  // initilize landa
  //
  hyper_d.landa = HDP_hyper_params_d(2)/HDP_hyper_params_d(3);


  if (is_master_d == true){
    for(int32 i = 0; i < (*slaves_d).length();i++){
      (*slaves_d)(i).sample_hyper_init();
    }
  }

  //exit gracefully
  //
  return true;
}

// method: sample_dist
//
// arguments: 
//  
//  
//
// return: bool8 value
//
// sample  pi_s  distribution
//
bool8 HDP::sample_dist(){

// print a message based on verbosity level
  //
  if ( verbosity_d > Integral::NONE || debug_level_d > Integral::NONE){
    Console::increaseIndention();
    Console::put(L"sample_dist()");
    Console::decreaseIndention();
  }

  if (is_master_d == true){
    
    // sample beta_vec
    //
    // local variable
    //
    
    
    VectorLong M_sum(Ks_d);
    VectorLong temp_row(Ks_d);
    for (int32 i = 0 ;i < Kg_d; i++){ 
      counts_d.M.getRow(temp_row,i);
      M_sum.add(temp_row);
    }

    dir_params_d.assign(M_sum);
    dir_params_d.add((float64)hyper_d.sigma/Ks_d); // or Ks_d ?? 
    dir_dist_d.setParameters(dir_params_d);
    dir_dist_d.get(dist_struct_d.beta_vec);
    
    // call  slaves
    //
    for(int32 i = 0; i < (*slaves_d).length();i++){
      (*slaves_d)(i).sample_dist();
    }
   
  }

  // if slave just copy the beta_vec
  //
  else{
    dist_struct_d.beta_vec.assign((*master_d).dist_struct_d.beta_vec);
  }


  if (is_slave_d == true){
    VectorFloat beta_vec_sigma;
    beta_vec_sigma.assign(dist_struct_d.beta_vec);
    beta_vec_sigma.mult(hyper_d.sigma); // needed ot  div by Ks_d?

    // sample pi_s for each slave 
    // pi_s=Dirichlet(Ns+sigma*beta_vec)
    //
   
    // calculate Dirichlet sampling
    //
   
    dir_params_d.assign(counts_d.Ns);
    dir_params_d.add(beta_vec_sigma);
    dir_dist_d.setParameters(dir_params_d);
    dir_dist_d.get(dist_struct_d.pi_s);
    if ( debug_level_d > Integral::NONE){
      dir_params_d.debug(L"dir_params");
      dist_struct_d.pi_s.debug(L"dir_dist");
    }
  }
  // exit gracefully
  //
  return true;
}

// method: sample_tables
//
// arguments: 
//  
//  
//
// return: bool8 value
//
// sample tables in the Chinese Resturant Franchise
//
bool8 HDP::sample_tables(){

  // local variables
  //
  Double landa = hyper_d.landa;
  Double sigma = hyper_d.sigma;
 
  MatrixDouble temp1(Kg_d,Ks_d);
  VectorDouble temp3;
  

  if ( is_master_d == true){
    temp3.mult(dist_struct_d.beta_vec,landa); // sigma or landa?
    for (int32 kg=0;kg<Kg_d;kg++)
      temp1.setRow(kg,temp3);
      

    // sample tables
    //
    randnumtable(temp1);

    // call  slaves
    //
    for(int32 i = 0; i < (*slaves_d).length(); i++){
      
      (*slaves_d)(i).sample_tables();
    
    }
  }
  // if this is a slave just copy
  //
  else{
    counts_d.M.assign((*master_d).counts_d.M);
  }

  // return gracefully
  //
  return true;
}

// method: randnumtable
//
// arguments: 
//  
//  
//
// return: bool8 value
//
// 
//
bool8 HDP::randnumtable(MatrixDouble alpha){
  
  // local variables
  //  
  VectorDouble temp;
  int32 temp2 = 0;
  
  for(int32 row = 0; row < (*slaves_d).length(); row++){

    
    for (int32 col = 0; col < (*slaves_d)(row).counts_d.Ns.length();col++){
      if ((*slaves_d)(row).counts_d.Ns(col) >= 2){
	uniform_rand_d.setLength((*slaves_d)(row).counts_d.Ns(col)-1);
	uniform_rand_d.rand(uniform_gen_d);
	temp.setLength((*slaves_d)(row).counts_d.Ns(col)-1);
        temp.setRange(0,(*slaves_d)(row).counts_d.Ns(col)-1,alpha.getValue(row,col));
	for (int32 i = 0; i < (*slaves_d)(row).counts_d.Ns(col)-1; i++){
     
	  temp(i) = temp(i) /(temp(i)+(double)i+1.0);
	  if(temp(i) > uniform_rand_d(i))
	    temp2++;
	}

	// set M
	//
	counts_d.M.setValue(row,col,temp2+1);
	temp2 = 0 ;
      }
      else if ((*slaves_d)(row).counts_d.Ns(col) == 1){

	// set M
	//
	counts_d.M.setValue(row,col,1);
      } 
      else if ((*slaves_d)(row).counts_d.Ns(col) == 0){

	// set M
	//
	counts_d.M.setValue(row,col,0);
      }
    }
  }     
      // return gracefully
      //
      return true;
}



// method: sample_theta
//
// arguments: 
//  
//  
//
// return: bool8 value
//
// sample theta
//
bool8 HDP::sample_theta(){

  // print a message based on verbosity level
  //
  if ( verbosity_d > Integral::NONE || debug_level_d > Integral::NONE){
    Console::increaseIndention();
    Console::put(L"sample_theta()");
    Console::decreaseIndention();
  }

  // if this is a master object then sample
  //
  if ( is_master_d == true){
    
    
    // Normal-Inverse-Wishart priors
    //
    if ( priorType_d == NIW){
      
       // MK=params.M*params.K
      //
      VectorDouble MK(params_d.M);
      MK.mult(params_d.K);
      
      // MKM= params.M*params.K*params.M'
      //
      MatrixDouble  MKM;
      MKM.outerProduct(MK,params_d.M);
      
      if (debug_level_d > Integral::NONE){
	params_d.M.debug(L"params_d.M");
	MK.debug(L"MK");
	MKM.debug(L"MKM");
      }

      
      // Local variables
      //
      Double Sxx;
      VectorDouble Syx;
      MatrixDouble Syy;
      VectorDouble SyxSxxInv;
      MatrixDouble Sygx_t;
      MatrixDouble Sygx;
      MatrixDouble sqrtInvSigma;
      MatrixDouble  sqrtSigma,tmp_matrix;
      VectorDouble temp_v;
      int32 n;
      
      // loop over all compoenents and sample theta
      // by using sufficient stats
      // refer to Suderes ??? and Fox ??? for details
      //
      for(int32 ks=0;ks<Ks_d;ks++){
	Sxx = params_d.K;
	Syx = MK;
	Syy = MKM;
	n = 0;
	
	// loop over all slaves
	//
	for (int32 kg = 0; kg < Kg_d;kg++){

	  n = n + (*slaves_d)(kg).sstats_d.cards(ks);
	  if ( (*slaves_d)(kg).sstats_d.cards(ks) > 0.0 ){
	    Sxx = (*slaves_d)(kg).sstats_d.cards(ks)+Sxx;
	    Syx.add((*slaves_d)(kg).sstats_d.sumY(ks),Syx);
	    Syy.add((*slaves_d)(kg).sstats_d.YY(ks),Syy);
	  }
	  else{
	  }
	}
	
	SyxSxxInv.div(Syx,Sxx);
	Sygx_t.outerProduct(SyxSxxInv,Syx);
	Sygx_t.mult(-1);
	Sygx_t.add(Syy);
	Sygx.transpose(Sygx_t);
	Sygx.add(Sygx_t);
	Sygx.div(2);
	Sygx.add(params_d.nu_delta);	
	
	
	// sampling 
	// Moving this part into the "if" statement can improves the performace slightly by pre-computing the Chol of delta_nu 
	//

	
	// sample the inverse Wishart distribution
	//
	iwishart_dist_d.setParameters(Sygx,n+params_d.nu,true);
	iwishart_dist_d.get(sqrtInvSigma);
	sqrtInvSigma.transpose(); // added in debug
	
	// compute the invSigma using the sample from above line
	//
	tmp_matrix.outerProduct(sqrtInvSigma,sqrtInvSigma);
	
	theta_d.invSigma(ks).copy(tmp_matrix);
	
	// compute sqrtSigma
	//
	sqrtSigma.inverse(sqrtInvSigma);
	
	// debug info
	//
	if (debug_level_d >= Integral::DETAILED){
	  Console::increaseIndention();
	  Long _ks_=ks;
	  _ks_.debug(L"ks");
	  Sxx.debug(L"Sxx");
	  Syx.debug(L"Syx");
	  Syy.debug(L"Syy");
	  SyxSxxInv.debug(L"SyxSxxInv");
	  Sygx.debug(L"Sygx");
	  sqrtInvSigma.debug(L"sqrtInvSigma");
	  sqrtSigma.debug(L"sqrtSigma");
	  theta_d.invSigma(ks).debug(L"theta.invSigma");
	}
	
	// sample mu
	//
	//sqrtSigma.debug(L"sqrtSigma1");
	sqrtSigma.mult(sqrt(1/Sxx));

	
	norm_dist_d.setLength(dim_d);
	norm_dist_d.grand(0.0 ,1.0 ,norm_gen_d);
	sqrtSigma.transpose();
	sqrtSigma.multv(temp_v,norm_dist_d);
	theta_d.mu(ks).assign(SyxSxxInv);
	theta_d.mu(ks).add(temp_v);

	
       
	// debug info
	//
	if (debug_level_d >= Integral::DETAILED){
	  norm_dist_d.debug(L"norm_dist_d");
	  theta_d.mu(ks).debug(L"theta_d.mu");
	  Console::decreaseIndention();
	}

      }
     
    }
    // Inverse-Wishar-Normal
    else if( priorType_d == IW_N){
      
      // local variables
      //
      MatrixDouble sqrtInvSigma,Syy,Syy0,Sygx,zero_mat;
      MatrixDouble  sqrtSigma,temp_mat,Sigma_n, Sigma_n_chol;
      VectorDouble temp_vec,mu_n;
      MatrixDouble YY0;
      VectorDouble sum_sumY,zero_vec;
      Double total_N;
      

      int32 numItr = internal_itr_d;

      zero_mat.setDimensions(dim_d,dim_d);
      zero_vec.setLength(dim_d);
      
      MatrixDouble chol0;
      chol0.assign(params_d.cholSigma);
      chol0.transpose();  
	  
      //#pragma omp parallel for private (Syy,YY0,sum_sumY,total_N,Sigma_n,temp_vec,Sygx,Sigma_n_chol) not works
      for (int32 ks = 0; ks < Ks_d; ks++){
	//	if ( sstats_d.cards(ks) > 0.0 ){

	// set Syy , sum_sumY and total_N to zero
	//
	//
	//#pragma omp critical
	{
	    Syy.assign(zero_mat);
	    YY0.assign(zero_mat);
	    sum_sumY.assign(zero_vec);
	    total_N = 0;
      
	    //
	    for (int32 kg = 0; kg < Kg_d;kg++){

	      // if the cluster is not empty
	      //
	      if((*slaves_d)(kg).sstats_d.cards(ks) > 0.0){

		
		//Syy0.assign(zero_mat);
		/*Syy0.assign((*slaves_d)(kg).sstats_d.YY(ks));
		temp_mat.outerProduct(theta_d.mu(ks),(*slaves_d)(kg).sstats_d.sumY(ks));
		Syy0.sub(temp_mat);
		temp_mat.transpose();
		Syy0.sub(temp_mat);
		temp_mat.outerProduct(theta_d.mu(ks),theta_d.mu(ks));
		temp_mat.mult((*slaves_d)(kg).sstats_d.cards(ks));
		Syy0.add(temp_mat);
                */
		total_N = total_N + (*slaves_d)(kg).sstats_d.cards(ks);
		sum_sumY.add((*slaves_d)(kg).sstats_d.sumY(ks));
                YY0.add((*slaves_d)(kg).sstats_d.YY(ks));
	      }
	    }
	}//critical	
	    if(total_N > 0.0){
	      //printf("ks %d \n",ks);
	      //YY0.debug(L"YY0");
	      for (int32 n = 0; n < numItr; n++){

	    
		Syy.assign(YY0);
		temp_mat.outerProduct(theta_d.mu(ks),sum_sumY);
		Syy.sub(temp_mat);
		temp_mat.transpose();
		Syy.sub(temp_mat);
		temp_mat.outerProduct(theta_d.mu(ks),theta_d.mu(ks));
		temp_mat.mult(total_N);
		Syy.add(temp_mat);
	   
		Sygx.transpose(Syy);
		Sygx.add(Syy);
		Sygx.div(2);
		Sygx.add(params_d.nu_delta);

		
		// sample the inverse Wishart distribution
		//
		iwishart_dist_d.setParameters(Sygx,total_N+params_d.nu,true);
		iwishart_dist_d.get(sqrtInvSigma);
		sqrtInvSigma.transpose(); // added in debug
	    
		// compute the invSigma using the sample from above line
		//
		theta_d.invSigma(ks).outerProduct(sqrtInvSigma,sqrtInvSigma);
	  
	    
		// compute sqrtSigma
		//
		//sqrtSigma.inverse((MatrixDouble)sqrtInvSigma);
		
		// sample mu
		//
		Sigma_n.assign(theta_d.invSigma(ks));
		Sigma_n.mult(total_N);
		Sigma_n.add(params_d.Lambda);
		Sigma_n.inverse();
		theta_d.invSigma(ks).multv(temp_vec,sum_sumY);
		temp_vec.add(params_d.theta);
		Sigma_n.multv(mu_n,temp_vec);
		
		MatrixDouble tmp;
		tmp.transpose(Sigma_n);
		Sigma_n.setLower(tmp);
  

		Sigma_n.decompositionCholesky(Sigma_n_chol);
	    
		norm_dist_d.setLength(dim_d);
		norm_dist_d.grand(0.0 ,1.0 ,norm_gen_d);
		
		Sigma_n_chol.multv(theta_d.mu(ks),norm_dist_d);
		theta_d.mu(ks).add(mu_n);

		
	      }
	    }

	  //}
	  else{
        
	  // sample the inverse Wishart distribution
	  //
	  iwishart_dist_d.setParameters(params_d.nu_delta,params_d.nu,true);
	  iwishart_dist_d.get(sqrtInvSigma);
          sqrtInvSigma.transpose();
	  
	  // compute the invSigma using the sample from above line
	  //
	  theta_d.invSigma(ks).outerProduct(sqrtInvSigma,sqrtInvSigma);
	  
	  // sample mu
	  //
	  norm_dist_d.setLength(dim_d);
	  norm_dist_d.grand(0.0 ,1.0 ,norm_gen_d);
	  chol0.multv(theta_d.mu(ks),norm_dist_d);
	  theta_d.mu(ks).add(params_d.M);
	  	  
	  }
       
      }

      
    }
    
    else{
  
      // print error message
      //
      return Error::handle(name(), L"Prior_type is not known.", Error::ARG, __FILE__, __LINE__);
      
    }

    // call slaves
    //
    for(int32 i = 0; i < (*slaves_d).length(); i++){
      (*slaves_d)(i).sample_theta();
    }

  }

  // if is a slave object then just copy
  //
  if(is_slave_d == true){
    theta_d.mu.assign((*master_d).theta_d.mu);
    theta_d.invSigma.assign((*master_d).theta_d.invSigma);
  }

  // exit gracefully
  //
  return true;
}

// method: normailze
//
// arguments: 
// normailize_a: to subtract from log_likelihoods
// 
//
//
// return: bool8 value
//
// normalize the likelihoods
//
bool8 HDP::normalize(int32 t,Double normalize_a){

  for(int32 ks = 0; ks < Ks_d; ks++){
    log_likelihood_d(t)(ks).sub(normalize_a);
  }
  

  return true;

}

// method: compute_marginal_ll
//
// arguments: 
// 
// 
//
//
// return: bool8 value
//
// compute marginal log_likelihoods
//
bool8 HDP::compute_marginal_ll(){

  marg_like_d.setLength(log_likelihood_d.length());
  mix_prob_d.setLength(log_likelihood_d.length());
  for(int32 t = 0; t < log_likelihood_d.length(); t++){
    mix_prob_d(t).setLength(Ks_d);
    marg_like_d(t) = 0;   
    for (int32 ks = 0; ks < Ks_d; ks++){
      marg_like_d(t) += log_likelihood_d(t)(ks)*dist_struct_d.pi_s(ks);
      mix_prob_d(t)(ks) =  log_likelihood_d(t)(ks)*dist_struct_d.pi_s(ks);
    }
  }

  return true;
}


// method: compute_loglikelihood
//
// arguments: 
// data_index :  index for data structure (db) 
// log_likelihood: VectorDouble (output)
//
//
// return: bool8 value
//
// update sufficent statistics
//
bool8 HDP::compute_loglikelihood(int32 T,bool8 normalize){

  // print a message based on verbosity level
  //
  if ( verbosity_d > Integral::NONE || debug_level_d > Integral::NONE){
    Console::increaseIndention();
    Console::put(L"compute_loglikelihood");
    Console::decreaseIndention();
  }

  // local variables
  //
  VectorDouble data_v,u;
  Double u_ss;
  Double normalizer;

  
  // set the length of vector to T
  //
  log_likelihood_d.setLength(T); 
 
  // loop over a sequence
  //
  for (int32 seq_t = 0; seq_t < T; seq_t++){
    log_likelihood_d(seq_t).setLength(Ks_d);
  }


  // loop over a sequence
  //
  // seq.  length
  //
  #pragma omp parallel for private(data_v,u,u_ss) schedule(auto) collapse(2) 
  for (int32 seq_t = 0; seq_t < T; seq_t++){

      // loop over all components
      //
      for( int32 ks=0;ks<Ks_d;ks++){

	// can we  save the chol_invSigma instead of invSigma? (seems  we just need to
	// not compute invSigma in theta sampling : check later
	//
	//theta.invSigma(ks).decompositionCholesky(cholinvSigma);
	//cholinvSigma.transpose();
	//cholinvSigma.getDiagonal(dcholinvSigma);
	
	// for HDP each data point is a vector so we convert it from Matrix format
    //
	
    
	#pragma  omp critical
	{
	db_d->curr_data_d.getColumn(data_v,seq_t);
	}
	//data_tmp.assign(data_v);
	
	data_v.sub(theta_d.mu(ks));
	
	// multiply by cholinvSigma and save the result in u
	//
	theta_d.cholinvSigma(ks).multv(u,data_v);
	u_ss=-0.5*u.sumSquare();
	u_ss+=theta_d.dcholinvSigma(ks).sum();
#pragma omp critical
	{	
	log_likelihood_d(seq_t)(ks)=u_ss;
	}

      // debug info
      //
      if (debug_level_d >= Integral::ALL){
	theta_d.cholinvSigma(ks).debug(L"cholinvSigma");
	u.debug(L"u");
      }
    }
  }


  if (normalize == true){

    // normalize the likelihood
    //
   
    // loop over a sequence
    //
    for (int32 seq_t = 0; seq_t < T; seq_t++){
      normalizer = log_likelihood_d(seq_t).max();
      log_likelihood_d(seq_t).sub(normalizer);
    }
  }


  // copy to slaves
  //
  if(is_master_d == true){
    #pragma omp parallel for
    for (int32 kg = 0; kg < (*slaves_d).length(); kg++){
      (*slaves_d)(kg).log_likelihood_d.assign(log_likelihood_d);
    }
  }

  if (debug_level_d >= Integral::DETAILED){
    Console::increaseIndention();
    theta_d.invSigma.debug(L"theta_d.invSigma");
    theta_d.mu.debug(L"theta_d.mu");
    log_likelihood_d.debug(L"loglikelihood_d");
    Console::decreaseIndention();
  }

  // exit gracefully
  //
  return true;
}

// method: compute_cholesky
//
// arguments: 
//  
//  
//
// return: bool8 value
//
// compute and save Cholesky decomposition
//
bool8 HDP::compute_cholesky(){


  theta_d.cholinvSigma.setLength(Ks_d);
  theta_d.dcholinvSigma.setLength(Ks_d);
  
 // loop over all components
 //
  #pragma omp parallel for
  for( int32 ks=0;ks<Ks_d;ks++){

    // can we  save the chol_invSigma instead of invSigma? (seems  we just need to
    // not compute invSigma in theta sampling : check later
    //
    theta_d.invSigma(ks).decompositionCholesky(theta_d.cholinvSigma(ks));
    theta_d.cholinvSigma(ks).transpose();
    theta_d.cholinvSigma(ks).getDiagonal(theta_d.dcholinvSigma(ks));
    theta_d.dcholinvSigma(ks).log();
  }

  // exit  gracefully
  //
  return true;
}

// method: sample_data
//
// arguments: 
//  
//  
//
// return: bool8 value
//
// sample mixture components
//
bool8 HDP::sample_data(){

  // local variables
  //
  VectorDouble Ps;
  VectorDouble temp1;
  int32 temp2;

  Ps.setLength(Ks_d);
  temp1.setLength(Ks_d);

  // print a message based on verbosity level
  //
  if ( verbosity_d > Integral::NONE || debug_level_d > Integral::NONE){
    Console::increaseIndention();
    Console::put(L"sample_s()");
    Console::decreaseIndention();
  }

  // if this is a slave
  //
  if(is_slave_d == true){
    
    init_sample_data();
    
    // loop over all data points
    //
    for (int32 data_records = 0; data_records < db_d->get_records_no(); data_records++){
      
      // read the data
      //
      db_d->get(); 
      
      // seqeuece length
      //
      int32 T = db_d->curr_data_d.getNumColumns();
      
      
      // compute the log likelihood
      // at each call "log_likelihood" variable will be updated by the likelihood 
      // the current point (points accessed successively)
      //     
      compute_loglikelihood(T);
      

      // convert form log to linear scale
      // 
      
      // loop over a sequence
      //
      
      for (int32 seq_t = 0; seq_t < T; seq_t++){
	
	log_likelihood_d(seq_t).exp();
	
	
	// posetrior probablity
	//
	Ps.mult(dist_struct_d.pi_s,log_likelihood_d(seq_t));

	//  force each state to at most have Kc_d components
  //  This feature is experimental but might prove useful
  //


  // only run if Kc_d is less than Ks_d
  //
  
  if (Kc_d < Ks_d){

    VectorLong  sorted_inds;
    
    VectorDouble tmp1,tmp2;
    
    Ps.index(sorted_inds,Integral::DESCENDING);
    tmp1.assign(Ps);
    Ps.assign(0.0);
    tmp2.assign(dist_struct_d.pi_s);
    dist_struct_d.pi_s.assign(0.0);
    
    for (int i=0;i<Kc_d;i++){
      Ps(sorted_inds(i))= tmp1(sorted_inds(i));
      dist_struct_d.pi_s(sorted_inds(i))= tmp2(sorted_inds(i));
	
    }
    
    dist_struct_d.pi_s.div(dist_struct_d.pi_s.sum());
    
  }

	
	// sample from the posterior
	// 
	multi_dist_d.setParameters(Ps);
	multi_dist_d.get(temp1);
	temp1.max(temp2);
	mixture_index_d(data_records)(seq_t) = temp2;
      
	// increas the counts
	//
	counts_d.Ns(temp2) = counts_d.Ns(temp2)+1;
	
	// debug info
	//
	if (debug_level_d >= Integral::ALL){
	  Console::increaseIndention();
	  Ps.debug(L"Ps");
	  temp1.debug(L"temp1: mutinominal distribution");
	  Long _temp2_=temp2;
	  _temp2_.debug(L"mixture index for this data point");
	  Console::decreaseIndention();
	}
	
      }
      
      if (debug_level_d >= Integral::DETAILED){
	Console::increaseIndention();
      mixture_index_d.debug(L"mixture index");
      Console::decreaseIndention();
      }
      
    }
  }

  // call the slaves
  //
  if (is_master_d == true){
    for(int32 i = 0 ; i<(*slaves_d).length();i++){
      (*slaves_d)(i).sample_data();

    }

  }

  // exit gracefully
  //
  return true;
  }
  
// method: init_sample_data
//
// arguments: 
//  
//  
//
// return: bool8 value
//
// initilize sample_data()
//
bool8 HDP::init_sample_data(){

  // set Ns to zero
  //
  counts_d.Ns.setRange(0,Ks_d,0);

  // compute cholesky decompsitions
  //
  compute_cholesky();

  return true;
}

// method: sample_data
//
// arguments: 
//  
//  
//
// return: bool8 value
//
// sample mixture components
// init_sample_data should be called outside 
//
bool8 HDP::sample_data(int32 data_records,int32 seq_t){

  // local variables
  //
  VectorDouble Ps;
  VectorDouble temp1;
  int32 temp2;

  Ps.setLength(Ks_d);
  temp1.setLength(Ks_d);

  // print a message based on verbosity level
  //
  if ( verbosity_d > Integral::NONE || debug_level_d > Integral::NONE){
    Console::increaseIndention();
    Console::put(L"sample_s()");
    Console::decreaseIndention();
  }

  // init_sample_data should be called outside of this function
  //

  // read the data
  //
  //  db_d->get(data_records); 
             
  // posetrior probablity
  //
  Ps.mult(dist_struct_d.pi_s,log_likelihood_d(seq_t));


  // only run if Kc_d is less than Ks_d
  //
  
  if (Kc_d < Ks_d){

    VectorLong  sorted_inds;
    
    VectorDouble tmp1,tmp2;
    
    Ps.index(sorted_inds,Integral::DESCENDING);
    tmp1.assign(Ps);
    Ps.assign(0.0);
    tmp2.assign(dist_struct_d.pi_s);
    dist_struct_d.pi_s.assign(0.0);
    
    for (int i=0;i<Kc_d;i++){
      Ps(sorted_inds(i))= tmp1(sorted_inds(i));
      dist_struct_d.pi_s(sorted_inds(i))= tmp2(sorted_inds(i));
	
    }
    
    dist_struct_d.pi_s.div(dist_struct_d.pi_s.sum());
    
  }

  
  // sample from the posterior
  // 
  multi_dist_d.setParameters(Ps);
  multi_dist_d.get(temp1);
  temp1.max(temp2);
  mixture_index_d(data_records)(seq_t) = temp2;
  
  // increas the counts
  //
  counts_d.Ns(temp2) = counts_d.Ns(temp2)+1;
      
  // debug info
  //
  if (debug_level_d >= Integral::ALL){
    Console::increaseIndention();
    Ps.debug(L"Ps");
    temp1.debug(L"temp1: mutinominal distribution");
    Long _temp2_=temp2;
    _temp2_.debug(L"mixture index for this data point");
    Console::decreaseIndention();
  }
    
    
  
  if (debug_level_d >= Integral::DETAILED){
    Console::increaseIndention();
    mixture_index_d.debug(L"mixture index");
    Console::decreaseIndention();
  }
    
  
  // exit gracefully
  //
  return true;
}


// method: update_sstats  : should be changed
//
// arguments: 
//  
//  
//
// return: bool8 value
//
// update sufficent statistics
//

// this can be changed to speed up (we just  need to update one copy)
//
bool8 HDP::update_sstats(){

  // print a message based on verbosity level
  //
  if ( verbosity_d > Integral::NONE || debug_level_d > Integral::NONE){
    Console::increaseIndention();
    Console::put(L"update_sstats");
    Console::decreaseIndention();
  }

  // local variables : it might be better to move this outside
  //
  Vector<MatrixDouble> store_YY;
  Vector<VectorDouble> store_sumY;
  VectorDouble data_v;
  MatrixDouble  u;

  VectorDouble zero_vec1(dim_d);
  VectorDouble zero_vec2(dim_d*dim_d);
  MatrixDouble zero_matrix;
  zero_matrix.setDimensions(dim_d,dim_d,false);
  u.setDimensions(dim_d,dim_d,false);
 
  // initilize to zero
  //
  store_YY.setLength(Ks_d);
  store_YY.assign(zero_matrix);
  store_sumY.setLength(Ks_d);
  store_sumY.assign(zero_vec1);

  if (is_slave_d == true){
    // loop over all data points
    //
    for (int32 data_records = 0; data_records < db_d->get_records_no(); data_records++){
      
      // read data record
      //
      db_d->get(data_records);
      
      // loop over a sequence
      //
      // seq.  length
      //
      int32 T = db_d->curr_data_d.getNumColumns();
      
      for (int32 seq_t = 0; seq_t < T; seq_t++){
      
	
	// for HDP each data point is a vector so we convert it from Matrix format
	//
	db_d->curr_data_d.getColumn(data_v,seq_t);
	u.outerProduct(data_v,data_v);
	
	// add the  data point to correct YY & sumY indexed place
	//
	store_YY(mixture_index_d(data_records)(seq_t)).add(u);  
	store_sumY(mixture_index_d(data_records)(seq_t)).add(data_v);
	
	if (debug_level_d >= Integral::ALL){
	  Console::increaseIndention();
	  db_d->curr_data_d.debug(L"db_d->curr_data_d");
	  u.debug(L"u : outerProduct of db_d->curr_data_d");
	  Console::decreaseIndention();
	}
	
      }
    }
    
    // update sstats
    //
    sstats_d.YY.assign(store_YY);
    sstats_d.cards.assign(counts_d.Ns);
    sstats_d.sumY.assign(store_sumY);
    
    if (debug_level_d >= Integral::BRIEF){
      Console::increaseIndention();
      store_YY.debug(L"store_YY");
      counts_d.Ns.debug(L"counts_d.Ns");
      store_sumY.debug(L"store_sumY");
      Console::decreaseIndention();
    }
  }
  if (is_master_d == true){
    for(int32 i = 0 ; i<(*slaves_d).length();i++){
      (*slaves_d)(i).update_sstats();
    }
  }
  // exit gracefully
  //
  return true;
}

// method: init_update_sstats
//
// arguments: 
//  
//  
//
// return: bool8 value
//
// initilize the function  update_sstats with arguments
//
bool8 HDP::init_update_sstats(){

  VectorDouble zero_vec1(dim_d);
  MatrixDouble zero_matrix;
  zero_matrix.setDimensions(dim_d,dim_d,false);

  sstats_d.YY.assign(zero_matrix);
  sstats_d.cards.assign(counts_d.Ns);
  sstats_d.sumY.assign(zero_vec1);

  return true;
}

// method: update_sstats
//
// arguments: 
//  
//  
//
// return: bool8 value
//
// update sufficent statistics
//
bool8 HDP::update_sstats(int32 data_records, int32 seq_t){

  // print a message based on verbosity level
  //
  if ( verbosity_d > Integral::NONE || debug_level_d > Integral::NONE){
    Console::increaseIndention();
    Console::put(L"update_sstats");
    Console::decreaseIndention();
  }

  // local variables : it might be better to move this outside
  //
  VectorDouble data_v;
  MatrixDouble  u;
  u.setDimensions(dim_d,dim_d);
 
 // read data record
  //
  db_d->get(data_records);
      
      
  // for HDP each data point is a vector so we convert it from Matrix format
  //
  db_d->curr_data_d.getColumn(data_v,seq_t);
  u.outerProduct(data_v,data_v);
  
  // add the  data point to correct YY & sumY indexed place
  //
  sstats_d.YY(mixture_index_d(data_records)(seq_t)).add(u);  
  sstats_d.sumY(mixture_index_d(data_records)(seq_t)).add(data_v);
  sstats_d.cards.assign(counts_d.Ns);
  
  if (debug_level_d >= Integral::ALL){
    Console::increaseIndention();
    db_d->curr_data_d.debug(L"db_d->curr_data_d");
    u.debug(L"u : outerProduct of db_d->curr_data_d");
    Console::decreaseIndention();
  }


  // exit gracefully
  //
  return true;
}


// method: gibbs_conparam
//
// arguments: 
// itr_num : number of iteration for Gibbs sampler
// a,b :  paramters of the hyper-parameter
// numdata : number of data points        
// num_components : number of components of the mixture
// alpha_in : current value of the hyper-paramter 
//    
//
// return: bool8 value
//
// Gibbs sampler for concentration parameter
//
double HDP::gibbs_conparam(Long itr_num,double a,double b,VectorFloat numdata,VectorFloat num_components,double alpha_in){
 
  // print a message based on verbosity level
  //
  if ( verbosity_d > Integral::NONE || debug_level_d > Integral::NONE){
    Console::increaseIndention();
    Console::put(L"gibbs_conparam()");
    Console::decreaseIndention();
  }
  // local variables
  //
  
  double gammaa, gammab;
  VectorLong zz;
  double alpha = alpha_in;

  int32 numgroups = numdata.length();
  
  Vector<VectorFloat> dir_params;
  VectorFloat dir_var;
  VectorFloat dir0_collect;
  VectorFloat uniform_rands;

 
  dir_params.setLength(numgroups);
  for (int i = 0; i< numgroups ; i++){
    dir_params(i).setLength(2);
    dir_params(i)(0) = alpha + 1;
    dir_params(i)(1) = numdata(i);
  }
 
  // collect the first component of dir_var
  //
  
  dir0_collect.setLength(numgroups);

  
    zz.setLength(numgroups);
   
  // sample the hyper parameter
  //
  for(int32 i = 0;i<itr_num;i++){

    
    // generate random Dirichlet samples
    //
    for (int32 j = 0; j < numgroups; j++){
     
      dir_dist_d.setParameters(dir_params(j));
      dir_dist_d.get(dir_var);
      dir0_collect(j) = dir_var(0);
     
    }
    dir0_collect.log();

   


    // sample from uniform random generator
    //
    uniform_rands.setLength(numgroups);
    
    uniform_rand_d.setLength(1);
    for (int32 j = 0; j < numgroups; j++){
      uniform_rand_d.rand(uniform_gen_d);
      uniform_rands(j).assign(uniform_rand_d(0));
    }

  
    
    // binomial auxiliary variables
    //
    for (int32 j = 0; j < numgroups; j++){
      
      if (((double)uniform_rands(j)*(alpha+(double)numdata(j))) < (double)numdata(j))
	zz(j) = 1;
      else
	zz(j) = 0;
    }

    
    // gamma resampling of hyper parameter
    //
    gammaa = a + num_components.sum() - zz.sum();
    gammab = b - dir0_collect.sum();

    gamma_rand_d.setParameters(gammaa);
    alpha = gamma_rand_d.get()/gammab;

    
  }

  // return gracefully
  //
  return (alpha);
}



// method: sample_hyper
//
// arguments: 
//  
//  
//
// return: bool8 value
//
// sample hyper parameters (sigma)
//
bool8 HDP::sample_hyper(long gibbs_itr){

  // print a message based on verbosity level
  //
  if ( verbosity_d > Integral::NONE || debug_level_d > Integral::NONE){
    Console::increaseIndention();
    Console::put(L"sample_hyper()");
    Console::decreaseIndention();
  }

  VectorFloat Nskdot,uniqueS;

  VectorFloat M_sum,M_gz,M_sum_row;
  VectorFloat barMsum;
  double barK = 0;
  barMsum.setLength(counts_d.M.getNumColumns());
  for (int32 i = 0; i < counts_d.M.getNumColumns();i++){
    barMsum(i) = counts_d.M.sumColumn(i);
    if ((float32)barMsum(i) > 0.0)  barK += 1;
  }

  M_sum.setLength(1);
  M_gz.setLength(1);
  M_sum(0) = counts_d.M.sum();
  M_gz(0) = barK;

  // if it is a master object compute the sigma using all slaves
  //
  if (is_master_d == true){

    VectorFloat Nskdot_tmp,uniqueS_tmp;

    VectorFloat Mkdot_tmp,Mkdot;
    int count = 0;
    
    Mkdot_tmp.setLength(counts_d.M.getNumRows());
    for (int32 i = 0; i < counts_d.M.getNumRows();i++){
      Mkdot_tmp(i) = counts_d.M.sumRow(i);
    }

    Mkdot.setLength(Mkdot_tmp.numNotEqual(0));
    for (int32 i = 0; i < Mkdot_tmp.length();i++){
      if ((float32)Mkdot_tmp(i) != 0.0){
	Mkdot(count) = Mkdot_tmp(i);
	count++;
      }
    }
    
    Nskdot_tmp.setLength(slaves_d->length());
    uniqueS_tmp.setLength(slaves_d->length());

    // landa
    //
    //hyper_d.landa = gibbs_conparam(gibbs_itr,HDP_hyper_params_d(2),HDP_hyper_params_d(3),M_sum,M_gz,hyper_d.landa);

    for(int32 i = 0; i < slaves_d->length();i++){
      Nskdot_tmp(i) = (*slaves_d)(i).counts_d.Ns.sum();
      uniqueS_tmp(i) = (*slaves_d)(i).counts_d.Ns.numNotEqual(0);
      
    }
    Nskdot.setLength(Nskdot_tmp.numNotEqual(0));
    uniqueS.setLength(Nskdot_tmp.numNotEqual(0));

    count = 0;
    for (int32 i = 0; i < Nskdot_tmp.length();i++){
      if ((float32)Nskdot_tmp(i) != 0.0){
	Nskdot(count) = Nskdot_tmp(i);
	uniqueS(count) = uniqueS_tmp(i);
	count++;
      }
    }
    if (Nskdot.length() == 0){
      gamma_rand_d.setParameters(HDP_hyper_params_d(0));
      hyper_d.sigma = gamma_rand_d.get()/HDP_hyper_params_d(1);

      gamma_rand_d.setParameters(HDP_hyper_params_d(2));
      hyper_d.landa = gamma_rand_d.get()/HDP_hyper_params_d(3);
    }
    else{
  
 hyper_d.sigma = gibbs_conparam(gibbs_itr,HDP_hyper_params_d(0),HDP_hyper_params_d(1),Nskdot,uniqueS,hyper_d.sigma);

 //hyper_d.landa = gibbs_conparam(gibbs_itr,HDP_hyper_params_d(2),HDP_hyper_params_d(3),Nskdot,uniqueS,hyper_d.sigma);
 
 // landa
 //
 hyper_d.landa = gibbs_conparam(gibbs_itr,HDP_hyper_params_d(2),HDP_hyper_params_d(3),Nskdot,Mkdot,hyper_d.landa);

    }
    /*
    if (hyper_d.landa < 0.0001)
      hyper_d.landa = 0.0001;
    if(hyper_d.sigma < 0.0001)
      hyper_d.sigma = 0.0001;
    */
    // broadcast it to all slaves
    //
    for(int32 i = 0; i < slaves_d->length();i++){
      (*slaves_d)(i).hyper_d.sigma = hyper_d.sigma;
      (*slaves_d)(i).hyper_d.landa = hyper_d.landa;
    }

  }
  else{

    VectorFloat Nskdot_tmp,uniqueS_tmp;

    Nskdot_tmp.setLength(1);
    uniqueS_tmp.setLength(1);

  
    Nskdot_tmp(0) = counts_d.Ns.sum();
    uniqueS_tmp(0) = counts_d.Ns.numNotEqual(0);
    
    Nskdot.setLength(Nskdot_tmp.numNotEqual(0));
    uniqueS.setLength(Nskdot_tmp.numNotEqual(0));

    int32 count = 0;
    for (int32 i = 0; i < Nskdot_tmp.length();i++){
      if ((float32)Nskdot_tmp(i) != 0.0){
	Nskdot(count) = Nskdot_tmp(i);
	uniqueS(count) = uniqueS_tmp(i);
	count++;
      }
    }
    if (Nskdot.length() == 0){
      gamma_rand_d.setParameters(HDP_hyper_params_d(0));
      hyper_d.sigma = gamma_rand_d.get()/HDP_hyper_params_d(1);
    }
    else{
      hyper_d.sigma = gibbs_conparam(gibbs_itr,HDP_hyper_params_d(0),HDP_hyper_params_d(1),Nskdot,uniqueS,hyper_d.sigma);
    }
    
  }
 

  if (debug_level_d >= Integral::BRIEF){
    Console::increaseIndention();
    hyper_d.sigma.debug(L"alpha");
    Console::decreaseIndention();
  }

  // return grcefully
  //
  return true;
}




// method: observation_likelihood
//
// arguments: 
//  
//  
//
// return: bool8 value
//
// compute the likelihood for an observation for model
//
bool8 HDP::observation_likelihood(){

  // print a message based on verbosity level
  //
  if ( verbosity_d > Integral::NONE || debug_level_d > Integral::NONE){
    Console::increaseIndention();
    Console::put(L"observation_lielihood()");
    Console::decreaseIndention();
  }


  compute_cholesky();

    
  // local varables
  //

  VectorDouble neglog_c,normalizer;

  
  // set the length ogf the vector
  //
  observed_log_likelihood_d.setLength(db_d->get_records_no());


  // loop over all data points
  //
  for (int32 data_records = 0; data_records < db_d->get_records_no(); data_records++){
    
    // read the data
    //
    db_d->get(data_records); 
    
    // seqeuece length
    //
    int32 T = db_d->curr_data_d.getNumColumns();
   
    normalizer.setLength(T);
    
  
    // compute the log likelihood
    // at each call "log_likelihood" variable will be updated by the likelihood 
    // the current point (points accessed successively)
    //     
    
    compute_loglikelihood(T,false);        
    
  

    // convert form log to linear scale
    //    
    for (int32 seq_t = 0; seq_t < T; seq_t++){
      
      normalizer(seq_t) = log_likelihood_d(seq_t).max();
      normalize(seq_t, normalizer(seq_t));
      log_likelihood_d(seq_t).exp();
    }
      
    // compute marginal likelihoods
    //
    compute_marginal_ll();
    
    neglog_c.assign(normalizer);

    for (int32 seq_t = 0; seq_t < T; seq_t++)
      neglog_c(seq_t) += log(marg_like_d(seq_t));

   
    // average log-likelihood for this  observation
    //
    observed_log_likelihood_d(data_records) = neglog_c.sum() / T;
    
  }  // end  of  loop over dataset

  // return gracefully
  //
  return true;

}
