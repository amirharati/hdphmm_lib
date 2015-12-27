#include <Console.h>
#include <time.h>
#include <float.h>

// method : init_emissions
//
// initilize emission distibutions
//
template <class emission_type>
bool8 HDPHMM<emission_type>::init_emissions(VectorLong seeds, VectorDouble other_params){

  Random rand_seed;
  rand_seed.seed(seeds(2));
  VectorLong rand_seeds(6);
  int32 count = 0;
  time_t t1;
  

  // set emissions_d as slaves
  //
  master_emission_d.setMaster(emissions_d);
  master_emission_d.set_db(*db_d);
 
  // set params for  emission
  //
  master_emission_d.set_hyper_parameters(emission_params_d);
  
  // set  debug and verbosity
  //
  if (debug_level_d > Integral::BRIEF) 
    master_emission_d.setDebug(debug_level_d);
  if (verbosity_d >= Integral::ALL) 
    master_emission_d.setVerbosity(verbosity_d);
  
  // set the db 
  //
  master_emission_d.set_db(*db_d);
  
  // initilize the master 
  //this will calculate stuff common for all slaves
  //
  master_emission_d.initilize(seeds,other_params);
 
  // call  the init function for emmission distributions
  //
  for (int32 i = 0; i< Kz_d; i++){
    if (count >T_d.length())
      count = 0;
    time(&t1);
    rand_seeds(0) = seeds(0)+T_d(count)+0*(int32)difftime(t1,NULL)%(10000+i)+(int32)10*rand_seed.get();
    rand_seeds(1) = seeds(1)+T_d(count)+0*(int32) difftime(t1,NULL)%(10000+i+1)+(int32)10*rand_seed.get();
    rand_seeds(2) = seeds(2)+T_d(count)+ 0*(int32)difftime(t1,NULL)%(10000+i+2)+(int32)10*rand_seed.get();
    rand_seeds(3) = seeds(3)+T_d(count)+ 0*(int32)difftime(t1,NULL)%(10000+i+3)+(int32)10*rand_seed.get();
    rand_seeds(4) = seeds(4)+T_d(count)+ 0*(int32)difftime(t1,NULL)%(10000+i+4)+(int32)10*rand_seed.get();
    rand_seeds(5) = seeds(5)+T_d(count)+ 0*(int32)difftime(t1,NULL)%(10000+i+5)+(int32)10*rand_seed.get();
    
    count++;
    
   
    // call initilize function
    // need to generate random seeds for each call using rand and time (perhaps need a delay)
    //
    emissions_d(i).initilize(rand_seeds, other_params);
    if (debug_level_d > Integral::BRIEF) 
      emissions_d(i).setDebug(debug_level_d);
    if (verbosity_d >= Integral::ALL) 
      emissions_d(i).setVerbosity(verbosity_d);  
  }
}



// method: initilize_lr
//
// arguments: 
//  
// seeds: seeds for initilizing random generators  
//
// return: bool8 value
//
// initilize variables for Left_Right models
//
template <class emission_type>
bool8 HDPHMM<emission_type>::initilize_lr(VectorLong seeds, VectorDouble other_params,int32 init_itr){
  
  int32 count = 0;
  do{
    count ++;

    initilize(seeds,other_params);
    
    // initilize hyper parameters
    //
    sample_hyper_init();

    // sample mixture parameters
    //
    sample_dist();
        
    // sample distribution parameters
    //
    sample_theta();
    
    // sample in a loop
    //
    for(int i=0;i<init_itr;i++){
      
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
    
    }
    
  }while ((int32)state_index_d(0)(0)==(int32)state_index_d(0)(state_index_d(0).length()-1) && count < 10);
  

  return true;
}

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
template <class emission_type>
bool8 HDPHMM<emission_type>::initilize(VectorLong seeds, VectorDouble other_params){
  
  // print a message based on verbosity level
  //
  if ( verbosity_d > Integral::NONE || debug_level_d > Integral::NONE){
    Console::increaseIndention();
    Console::put(L"initilize()");
    Console::decreaseIndention();
  }

  
  // initilize iterations
  //
  iterations_d = 0;
  itr_acc_d = 0;
 
  // set dimension
  // 
  dim_d = db_d->dim_d;
  
  // local variables
  //
  VectorDouble zero_vec1(dim_d);
  VectorDouble zero_vec2(dim_d*dim_d);
  MatrixDouble zero_matrix;
  
  
  zero_matrix.setDimensions(dim_d,dim_d,false);
  
  // initilize the length of emissions_d
  //
  emissions_d.setLength(Kz_d,false);
  
  // initilize cluster counts to zero
  //
  counts_d.N.setDimensions(Kz_d+1,Kz_d,false);
  counts_d.M.setDimensions(Kz_d+1,Kz_d,false);
  counts_d.barM.setDimensions(Kz_d+1,Kz_d,false);
  counts_d.sumW.setLength(Kz_d,false);
 
  // initilize  dist_struct
  //
  dist_struct_d.pi_z.setDimensions(Kz_d,Kz_d,false);
  dist_struct_d.beta_vec.setLength(Kz_d,false);
  dist_struct_d.pi_init.setLength(Kz_d,false);

  dist_struct_d.pi_z_acc.setDimensions(Kz_d,Kz_d,false);
  dist_struct_d.beta_vec_acc.setLength(Kz_d,false);
  dist_struct_d.pi_init_acc.setLength(Kz_d,false);

  // initilize Random generators
  //

  // initilize Random Dirichlet generator
  //
  dir_dist_d.seed(seeds(0));
 
 // initilize Random multinominal generator (using Dirichlet)
 //
  multi_dist_d.seed(seeds(1));
 
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
 
  
  state_index_d.setLength(db_d->get_records_no());
  state_index_d.setDebug(debug_level_d);
  
  T_d.setLength(db_d->get_records_no());

  // loop over all data points
  //
  for (int32 data_records = 0; data_records < db_d->get_records_no(); data_records++){
    
    // read the data
    //
    db_d->get(); 
    
    // seqeuece length
    //
    T_d(data_records) = db_d->curr_data_d.getNumColumns();
    state_index_d(data_records).setLength(T_d(data_records));

    //log_normalize_d(data_records).setLength(T(data_records));

    // initilize to -1
    //
    for (int32 i = 0; i < T_d(data_records);i++)
      state_index_d(data_records)(i) = -1;
 
  }
  
  Random rand_seed;
  rand_seed.seed(seeds(2));
  VectorLong rand_seeds(6);
  int32 count = 0;
  time_t t1;
 
  // set emissions_d as slaves
  //
  master_emission_d.setMaster(emissions_d);
  master_emission_d.set_db(*db_d);
 
  // set params for  emission
  //
  master_emission_d.set_hyper_parameters(emission_params_d);
  
  // set  debug and verbosity
  //
  if (debug_level_d > Integral::BRIEF) 
    master_emission_d.setDebug(debug_level_d);
  if (verbosity_d >= Integral::ALL) 
    master_emission_d.setVerbosity(verbosity_d);
  
  // set the db 
  //
  master_emission_d.set_db(*db_d);
  
  // initilize the master 
  //this will calculate stuff common for all slaves
  //
  master_emission_d.initilize(seeds,other_params);
 
  // call  the init function for emmission distributions
  //
  for (int32 i = 0; i< Kz_d; i++){
    if (count >T_d.length())
      count = 0;
    time(&t1);
    rand_seeds(0) = seeds(0)+T_d(count)+0*(int32)difftime(t1,NULL)%(10000+i)+(int32)10*rand_seed.get();
    rand_seeds(1) = seeds(1)+T_d(count)+0*(int32) difftime(t1,NULL)%(10000+i+1)+(int32)10*rand_seed.get();
    rand_seeds(2) = seeds(2)+T_d(count)+ 0*(int32)difftime(t1,NULL)%(10000+i+2)+(int32)10*rand_seed.get();
    rand_seeds(3) = seeds(3)+T_d(count)+ 0*(int32)difftime(t1,NULL)%(10000+i+3)+(int32)10*rand_seed.get();
    rand_seeds(4) = seeds(4)+T_d(count)+ 0*(int32)difftime(t1,NULL)%(10000+i+4)+(int32)10*rand_seed.get();
    rand_seeds(5) = seeds(5)+T_d(count)+ 0*(int32)difftime(t1,NULL)%(10000+i+5)+(int32)10*rand_seed.get();
    
    count++;
    
   
    // call initilize function
    // need to generate random seeds for each call using rand and time (perhaps need a delay)
    //
    emissions_d(i).initilize(rand_seeds, other_params);
    if (debug_level_d > Integral::BRIEF) 
      emissions_d(i).setDebug(debug_level_d);
    if (verbosity_d >= Integral::ALL) 
      emissions_d(i).setVerbosity(verbosity_d);  
  }

 
  emission_type_d.assign(master_emission_d.name());

  hyper_params_vec_d.setLength(2);
  hyper_params_vec_d(0) = Kz_d;
  header_info_d.assign(L"\nKz = ");
  header_info_d.concat(Kz_d);
  header_info_d.concat(L"\n Emission_type : ");
  header_info_d.concat(master_emission_d.name());
  switch(structure_type_d){
  case ERGODIC:
    header_info_d.concat(L"\nERGODIC");
    hyper_params_vec_d(1) = 0;
    break;
  case LEFT_TO_RIGHT:
    header_info_d.concat(L"\nLEFT_TO_RIGHT");
    hyper_params_vec_d(1) = 1;
    break;
  case STRICTLY_LEFT_TO_RIGHT:
    header_info_d.concat(L"\nSTRICTLY_LEFT_TO_RIGHT");
    hyper_params_vec_d(1) = 3;
    break;
  case LEFT_TO_RIGHT_WITH_LOOP:
    header_info_d.concat(L"\nLEFT_TO_RIGHT_WITH_LOOP");
    hyper_params_vec_d(1) = 4;
    break;
  case LEFT_TO_RIGHT_WITH_LOOP_TO_FIRST:
    header_info_d.concat(L"\nLEFT_TO_RIGHT_WITH_LOOP_TO_FIRST");
    hyper_params_vec_d(1) = 5;
    break;  

    
  };
  hyper_params_vec_d.concat(HMM_hyper_params_d);
 
  // exit gracefully
  //
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
template <class emission_type>
bool8 HDPHMM<emission_type>::sample_hyper_init(){

  // print a message based on verbosity level
  //
  if ( verbosity_d > Integral::NONE || debug_level_d > Integral::NONE){
    Console::increaseIndention();
    Console::put(L"sample_hyper_init()");
    Console::decreaseIndention();
  }
  
  // initilize alpha_p_kappa
  //
  hyper_d.alpha_p_kappa = HMM_hyper_params_d(0) / HMM_hyper_params_d(1);

  // initilize gamma
  //
  hyper_d.gamma = HMM_hyper_params_d(2) / HMM_hyper_params_d(3);

  // initilize rho
  //
  hyper_d.rho = HMM_hyper_params_d(4)/(HMM_hyper_params_d(4)+HMM_hyper_params_d(5));
  
  // call emission distribution sample_hype_init or similar function
  //
  // initilize emission hyper params
  //
  master_emission_d.sample_hyper_init();

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
// sample  pi_z & beta_vec  distribution
//
template <class emission_type>
bool8 HDPHMM<emission_type>::sample_dist(){

// print a message based on verbosity level
  //
  if ( verbosity_d > Integral::NONE || debug_level_d > Integral::NONE){
    Console::increaseIndention();
    Console::put(L"sample_dist()");
    Console::decreaseIndention();
  }

  // local variable
  //
  VectorFloat beta_vec_alpha; 

  // sample beta_vec
  // beta_vec = Dirichlet(gamma/Kz)
  //
  VectorDouble barM_sum(Kz_d);
  VectorDouble temp_row(Kz_d);
  for (int32 i = 0 ;i < Kz_d+1; i++){
    counts_d.barM.getRow(temp_row,i);
    barM_sum.add(temp_row);
  }

  if (sample_emissions_only_d==false){
    dir_params_d.assign(barM_sum);
    dir_params_d.add((float64)hyper_d.gamma/(float64)Kz_d);
  
    dir_dist_d.setParameters(dir_params_d);
    dir_dist_d.get(dist_struct_d.beta_vec);
  
    // multiply beta_vec by alpha
    //
    beta_vec_alpha.assign(dist_struct_d.beta_vec);
    beta_vec_alpha.mult(hyper_d.alpha_p_kappa*(1-hyper_d.rho));
 
    // to read rows counts_d.N
    //
    VectorLong temp1;
    
    // sample pi_z & emission related pi_s if needed
    //
    for (int32 i = 0;i < Kz_d;i++){


      //  for dev
      counts_d.N.getRow(temp1,i);
  
      VectorFloat kappa_vec(Kz_d);
      VectorFloat multi_a(Kz_d);
      multi_a.setRange(0,Kz_d,0);
      kappa_vec.setRange(0,Kz_d,0);

      if ( structure_type_d == LEFT_TO_RIGHT){
	if (i <Kz_d-1)
	  multi_a.setRange(i,Kz_d-i,1);
	else
	  multi_a.setRange(i,1,1);

	beta_vec_alpha.assign(dist_struct_d.beta_vec);
	beta_vec_alpha.mult(multi_a);
	if(beta_vec_alpha.sum() != 0)
	  beta_vec_alpha.div(beta_vec_alpha.sum());    
	beta_vec_alpha.mult(hyper_d.alpha_p_kappa*(1-hyper_d.rho));

	// make ure it is LR
	// if not  have this then we allow for loops (with low prob)
	//
	temp1.mult(multi_a);
      }
      else if ( structure_type_d == LEFT_TO_RIGHT_WITH_LOOP){
	if (i <Kz_d-1)
	  multi_a.setRange(i,Kz_d-i,1);
	else
	  multi_a.setRange(i,1,1);

	beta_vec_alpha.assign(dist_struct_d.beta_vec);
	beta_vec_alpha.mult(multi_a);
	if(beta_vec_alpha.sum() != 0)
	  beta_vec_alpha.div(beta_vec_alpha.sum());    
	beta_vec_alpha.mult(hyper_d.alpha_p_kappa*(1-hyper_d.rho));

	// note the difference with above
      }
      else if ( structure_type_d == LEFT_TO_RIGHT_WITH_LOOP_TO_FIRST){
	if (i <Kz_d-1)
	  multi_a.setRange(i,Kz_d-i,1);
	else
	  multi_a.setRange(i,1,1);
	multi_a(0)=1; //enforce to first state
	
	beta_vec_alpha.assign(dist_struct_d.beta_vec);
	beta_vec_alpha.mult(multi_a);
	if(beta_vec_alpha.sum() != 0)
	  beta_vec_alpha.div(beta_vec_alpha.sum());    
	beta_vec_alpha.mult(hyper_d.alpha_p_kappa*(1-hyper_d.rho));

	// make ure it is LR
	// if not  have this then we allow for loops (with low prob)
	//
	temp1.mult(multi_a);
      }
      else if ( structure_type_d ==  STRICTLY_LEFT_TO_RIGHT){
	if (i <Kz_d-1)
	  multi_a.setRange(i,2,1);
	else
	  multi_a.setRange(i,1,1);

	beta_vec_alpha.assign(dist_struct_d.beta_vec);
	beta_vec_alpha.mult(multi_a);
	if(beta_vec_alpha.sum() != 0)
	  beta_vec_alpha.div(beta_vec_alpha.sum());
	beta_vec_alpha.mult(hyper_d.alpha_p_kappa*(1-hyper_d.rho));
	
	// make ure it is LR
	temp1.mult(multi_a);
      }

      // make the current state presisitence 
      //
      kappa_vec(i) = hyper_d.alpha_p_kappa*hyper_d.rho;

      // sample pi_z
      //
      //counts_d.N.getRow(temp1,i);
      dir_params_d.assign(temp1);
      dir_params_d.add(kappa_vec);
      dir_params_d.add(beta_vec_alpha);

   
      dir_dist_d.setParameters(dir_params_d);
      dir_dist_d.get(temp_row);
      dist_struct_d.pi_z.setRow(i,temp_row);

      //temp_row.debug(L"temp_row");
      //temp1.debug(L"temp1**");
      //beta_vec_alpha.debug(L"beta_vec");
      
      
    }
  
  
    // sample pi_init
    //
    counts_d.N.getRow(temp1,Kz_d);
    dir_params_d.assign(temp1);
    
    dir_params_d.add(beta_vec_alpha);
    dir_dist_d.setParameters(dir_params_d);
    dir_dist_d.get(dist_struct_d.pi_init);

    // debug force  pi_init to be 1 0 0 ..
    if (structure_type_d == LEFT_TO_RIGHT || structure_type_d == STRICTLY_LEFT_TO_RIGHT || structure_type_d == LEFT_TO_RIGHT_WITH_LOOP || structure_type_d == LEFT_TO_RIGHT_WITH_LOOP_TO_FIRST){
      // dist_struct_d.pi_init(0)=1;
      //dist_struct_d.pi_init.setRange(1,Kz_d-1,0);
      Long L =(int32) Kz_d/2;
      dist_struct_d.pi_init.setRange(L+1,Kz_d-L-1,0);
      dist_struct_d.pi_init.div(dist_struct_d.pi_init.sum());
    }
  
    if ( debug_level_d > Integral::NONE){
      dir_params_d.debug(L"dir_params");
    }
  }
  
  // sample emission distributions
  //
  
  master_emission_d.sample_dist();

  // exit gracefully
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
template <class emission_type>
bool8 HDPHMM<emission_type>::sample_theta(){

// print a message based on verbosity level
  //
  if ( verbosity_d > Integral::NONE || debug_level_d > Integral::NONE){
    Console::increaseIndention();
    Console::put(L"sample_theta()");
    Console::decreaseIndention();
  }


  
  // sample emission distributions
  //
  

  master_emission_d.sample_theta();


  // exit gracefully
  //
  return true;
}


// method: backward_message_compute
//
// arguments: 
//  
//  
//
// return: bool8 value
//
// compute the backward messages
//
template <class emission_type>
bool8 HDPHMM<emission_type>::backward_message_compute(int32 T){

  // local  variables
  //
  Vector<VectorDouble> bwds_msg;
  bwds_msg.setLength(T);
  
  // it might be better to precompute T for all data points 
  // and do these stuff in initilize
  //
  partial_marg_d.clear();
  partial_marg_d.setLength(T);
  for (int32 i = 0; i < T; i++){
    bwds_msg(i).setLength(Kz_d);
    bwds_msg(i).setRange(0,Kz_d,1);
    partial_marg_d(i).setLength(Kz_d);
  }

  for(int32 t = T-2; t >= 0; t--){
    for (int32 kz = 0; kz < Kz_d; kz++){
    
      // multiplie likelihoods with incoming message
      //
      partial_marg_d(t+1)(kz) = emissions_d(kz).marg_like_d(t+1) * bwds_msg(t+1)(kz);    
    }

    dist_struct_d.pi_z.multv(bwds_msg(t),partial_marg_d(t+1));
    bwds_msg(t).div(bwds_msg(t).sum());    
  }
  

  for (int32 kz = 0; kz < Kz_d; kz++){    
 
    // multiplie likelihoods with incoming message
    //
    partial_marg_d(0)(kz) = emissions_d(kz).marg_like_d(0) * bwds_msg(0)(kz);    
  }
  
  // return gracefully
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
template <class emission_type>
bool8 HDPHMM<emission_type>::sample_data(){

  // print a message based on verbosity level
  //
  if ( verbosity_d > Integral::NONE || debug_level_d > Integral::NONE){
    Console::increaseIndention();
    Console::put(L"sample_data()");
    Console::decreaseIndention();
  }

  // local variables
  //
  VectorDouble Pz;
  VectorDouble temp1;
  int32 state_no;

  // set N to zero
  //
  counts_d.N.setBlock(0,0,Kz_d+1,Kz_d,0);
  
  // loop ove all states and initile sample_data for emission distributions
  //
  master_emission_d.init_sample_data();
  for (int32 kz = 0; kz< Kz_d;kz++){
    emissions_d(kz).init_sample_data();
  }

     
  int32 data_len = db_d->get_records_no();

  // loop over all data points
  //   
  for (int32 data_records = 0; data_records < data_len; data_records++){

    // read the data
    //
    db_d->get(data_records);
    
    // seqeuece length
    //
    int32 T = T_d(data_records);
   
    // compute the log likelihood
    // at each call "log_likelihood" variable will be updated by the likelihood 
    // the current point (points accessed successively)
    //     
   
    // compute the likelihood for each emission distribution
    // without normaliztion 
    //
    
    master_emission_d.compute_loglikelihood(T,false);

    //if(data_records == data_len - 1){
      // printf("data %d\n",data_records);
      //emissions_d(4).log_likelihood_d.debug(L"LL em4 befor norm");
      //}
    log_normalize_d.clear();
    log_normalize_d.setLength(T);

    Long Ks = master_emission_d.getKs();

    #pragma omp parallel
    {
      

      VectorDouble temp_log_vec(Ks); //debug Ks_d
  
      //***#pragma omp    for

      /*for(int32 i = 0; i < T; i++){
	  for(int32 kz = 0; kz < Kz_d; kz++){
	    temp_log_vec(kz) = emissions_d(kz).log_likelihood_d(i).max();
	  }
	  
	  log_normalize_d(i) = temp_log_vec.max(); 
	 
	}
      */
      #pragma omp for
      for(int32 i = 0; i < T; i++){
	for (int32 j = 0;j < Ks; j++){ //debug Ksd
	  VectorDouble tmp_vec(Kz_d);
	  for(int32 kz = 0; kz < Kz_d; kz++){

	    tmp_vec(kz) = emissions_d(kz).log_likelihood_d(i)(j);
	    //        temp_log_vec(kz) =emissions_d(kz).log_likelihood_d(i)(j);
	  }
	  temp_log_vec(j) = tmp_vec.max();
	}
	log_normalize_d(i) = temp_log_vec.max();
      }
      
       #pragma omp for 
	for(int32 kz = 0;kz < Kz_d; kz++){
   
      
	  // convert form log to linear scale
	  //    
	  for (int32 seq_t = 0; seq_t < T; seq_t++){
	    
	    // normalize
	    //
	    emissions_d(kz).normalize(seq_t, log_normalize_d(seq_t));
	  }
	  for (int32 seq_t = 0; seq_t < T; seq_t++){
	    for (int32 j = 0;j < Ks; j++){ //debug Ksd

	      emissions_d(kz).log_likelihood_d(seq_t)(j).exp();
	    }
	  }
	  
	  // compute marginal likelihoods
	  //
	  emissions_d(kz).compute_marginal_ll();
	}
    }
    
    // compute the backward messages
    //
    backward_message_compute(T);

    //printf("hdp_hmm::sample_data emission %d \n",kz);
    //emissions_d(kz).log_likelihood_d.debug(L"LL");
    
    
    // sample the state (Z) for the current sequence
    //
    for (int32 seq_t = 0; seq_t < T; seq_t++){
     
      //check    
      //partial_marg_d(seq_t).div(partial_marg_d(seq_t).sum());

      // sample Z for the the first frame
      //
      if (seq_t == 0){
	Pz.mult(dist_struct_d.pi_init,partial_marg_d(0));    
      }

      // sample Z for other frames
      //
      else{
	VectorDouble temp;
	dist_struct_d.pi_z.getRow(temp,state_index_d(data_records)(seq_t-1));
       
	//temp.debug(L"temp");
	Pz.mult(temp,partial_marg_d(seq_t));
      }
 
      // while(Pz.max()<0.0001 && !isnan(Pz(0)) && Pz.max()!=0)
      //Pz.mult(10);  
    
      // sample from the posterior
      // 
      multi_dist_d.setParameters(Pz);
      multi_dist_d.get(temp1);
      temp1.max(state_no);

      //Pz.debug(L"Pz");
      //temp1.debug(L"temp1");
      // printf("seq_t %d\n",seq_t);
      //emissions_d(4).log_likelihood_d.debug(L"LL em4");
      /* VectorDouble Pz2(Kz_d);
      Pz2(0)=Pz(0);
      for(int32 i = 1 ; i<Pz.length();i++){
	Pz2(i) = Pz2(i-1) + Pz(i);
      }
      
      // debug
      Double sum_tmp = 0;
      Double u_rand = Pz.sum()*uniform_gen_d.get();
      for (int32 i = 0 ; i < Pz2.length(); i++){
	if(u_rand > Pz2(i))
	  sum_tmp += 1;
      }
      state_no = sum_tmp;
      */

      if (sample_emissions_only_d==false){
	state_index_d(data_records)(seq_t) = state_no;
	// increase the counts
	//
	if (seq_t > 0){
	  int32 temp2 = state_index_d(data_records)(seq_t-1);
	  counts_d.N.setValue(temp2,state_no,counts_d.N(temp2,state_no) + 1);
	}else{
       
	  counts_d.N.setValue(Kz_d,state_no,counts_d.N(Kz_d,state_no)+1);
      
	}
      }

      
      
      // sample for  the emission distribution (component index for DPM case)
      //
      emissions_d(state_index_d(data_records)(seq_t)).sample_data(data_records,seq_t);

     

    }

    // debug info
    //
    if (debug_level_d >= Integral::ALL){
    Console::increaseIndention();
    Pz.debug(L"Pz");
    Console::decreaseIndention();
    }
 
  }

  if (debug_level_d >= Integral::DETAILED){
    Console::increaseIndention();
    state_index_d.debug(L"state index");
    Console::decreaseIndention();
  }

  // exit gracefully
  //
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
template <class emission_type>
bool8 HDPHMM<emission_type>::update_sstats(){

  // print a message based on verbosity level
  //
  if ( verbosity_d > Integral::NONE || debug_level_d > Integral::NONE){
    Console::increaseIndention();
    Console::put(L"update_sstats");
    Console::decreaseIndention();
  }

  // initilize update function
  //
  for(int32 kz = 0; kz < Kz_d; kz++){
    emissions_d(kz).init_update_sstats();
  }

  // loop over all data points
  //
  for (int32 data_records = 0; data_records < db_d->get_records_no(); data_records++){

    // read data record
    //
    db_d->get(data_records);
    
    // seq.  length
    //
    int32 T = T_d(data_records);
    
    for (int32 seq_t = 0; seq_t < T; seq_t++){
      emissions_d(state_index_d(data_records)(seq_t)).update_sstats(data_records,seq_t);
    }
  
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
//
// return: bool8 value
//
// Gibbs sampler for concentration parameter
//
template <class emission_type>
double HDPHMM<emission_type>::gibbs_conparam(Long itr_num,double a,double b,VectorFloat numdata,VectorFloat num_components,double alpha_in){
 
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
  VectorFloat  uniform_rands;

  

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
template <class emission_type>
bool8 HDPHMM<emission_type>::sample_hyper(int32 gibbs_itr){
  
  // print a message based on verbosity level
  //
  if ( verbosity_d > Integral::NONE || debug_level_d > Integral::NONE){
    Console::increaseIndention();
    Console::put(L"sample_hyper()");
    Console::decreaseIndention();
  }
  
  VectorFloat Nkdot_tmp,Nkdot;
  int32 count;

  count = 0;
  Nkdot_tmp.setLength(counts_d.N.getNumRows());
  for (int32 i = 0; i < counts_d.N.getNumRows(); i++){
    Nkdot_tmp(i) = counts_d.N.sumRow(i);
  }
  Nkdot.setLength(Nkdot_tmp.numNotEqual(0));
  for (int32 i = 0; i < Nkdot_tmp.length();i++){
    if ((float32) Nkdot_tmp(i) != 0.0){
      Nkdot(count) = Nkdot_tmp(i);
      count++;
    }
  }

  VectorFloat Mkdot_tmp,Mkdot;
  
  count = 0;
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
  VectorFloat barMsum;
  double barK = 0;
  barMsum.setLength(counts_d.barM.getNumColumns());
  for (int32 i = 0; i < counts_d.barM.getNumColumns();i++){
    barMsum(i) = counts_d.barM.sumColumn(i);
    if ((float32)barMsum(i) > 0.0)  barK += 1;
  }

  // if the sets are empty
  //
  if (Nkdot.length() == 0){

    
    gamma_rand_d.setParameters(HMM_hyper_params_d(0));
    hyper_d.alpha_p_kappa = gamma_rand_d.get()/HMM_hyper_params_d(1);
    
    gamma_rand_d.setParameters(HMM_hyper_params_d(2));
    hyper_d.gamma = gamma_rand_d.get()/HMM_hyper_params_d(3);

  }
  else{
    hyper_d.alpha_p_kappa = gibbs_conparam(gibbs_itr,HMM_hyper_params_d(0),HMM_hyper_params_d(1),Nkdot,Mkdot,hyper_d.alpha_p_kappa);

    VectorFloat tmp1,tmp2;
    tmp1.setLength(1);
    tmp1(0) = counts_d.barM.sum();
    tmp2.setLength(1);
    tmp2(0) = barK;

    hyper_d.gamma = gibbs_conparam(gibbs_itr,HMM_hyper_params_d(2),HMM_hyper_params_d(3),tmp1,tmp2,hyper_d.gamma); 
  }
  gamma_rand_d.setParameters((float32)HMM_hyper_params_d(4)+(float32)counts_d.sumW.sum());
  double rtmp=gamma_rand_d.get();
  gamma_rand_d.setParameters((float32)HMM_hyper_params_d(5)+((float32)counts_d.M.sum()-(float32)counts_d.sumW.sum()));
  hyper_d.rho = rtmp/(rtmp + gamma_rand_d.get());

  
  // sample hyperparameters of the emission dist
  //
  
  //  We can use a static function that takes some parameters
  // to compute the sigma also the current sample_hyper is buggy there and need to be fixed
  //

  
  master_emission_d.sample_hyper(gibbs_itr);
  
  if (debug_level_d >= Integral::BRIEF){
    Console::increaseIndention();
    Console::decreaseIndention();
  }
  
  // return grcefully
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
template <class emission_type>
bool8 HDPHMM<emission_type>::sample_tables(){

  // local variables
  //
  Double rho = hyper_d.rho;
  Double alpha = hyper_d.alpha_p_kappa*(1-rho);
  Double kappa = hyper_d.alpha_p_kappa*rho;
 
  MatrixDouble temp1(Kz_d,Kz_d);
  MatrixDouble temp2(Kz_d,Kz_d);
  VectorDouble temp3;

  // temp1 = [alpha * beta_vec(ones(1,Kz)+kappa*eye(Kz);alpha * beta_vec]
  // 
  temp3.mult(dist_struct_d.beta_vec,alpha);

  for (int32 kz=0;kz<Kz_d;kz++)
    temp1.setRow(kz,temp3);

  temp2.setDiagonal(kappa);
  temp1.add(temp2);
  
  temp1.setDimensions(Kz_d+1,Kz_d,true);
  temp1.setRow(Kz_d,temp3);


  // sample tables
  //
  randnumtable(temp1);

  // sample barM to compensate for state presistence (kappa)
  //
  sample_barM();


  
  master_emission_d.sample_tables();

  
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
template <class emission_type>
bool8 HDPHMM<emission_type>::randnumtable(MatrixDouble alpha){
  
  // local variables
  //  
  //VectorDouble temp;
  int32 temp2 = 0;

  for (int32 col = 0; col < counts_d.N.getNumColumns();col++){
    for (int32 row = 0 ;row < counts_d.N.getNumRows(); row++){
      
      if (counts_d.N.getValue(row,col) >= 2){
	uniform_rand_d.setLength(counts_d.N.getValue(row,col)-1);
	uniform_rand_d.rand(uniform_gen_d);
	VectorDouble temp;
	temp.setLength(counts_d.N.getValue(row,col)-1);
        temp.setRange(0,counts_d.N.getValue(row,col)-1,alpha.getValue(row,col));
	for (int32 i = 0; i < counts_d.N.getValue(row,col)-1; i++){
	  temp(i) = temp(i) /(temp(i)+(double)i+1.0);
	  if(temp(i) > uniform_rand_d(i))
	    temp2++;
	}

	// set M
	//
	counts_d.M.setValue(row,col,temp2+1);
	temp2 = 0 ;
      }
      else if (counts_d.N.getValue(row,col) == 1){

	// set M
	//
	counts_d.M.setValue(row,col,1);
      } 
      else if (counts_d.N.getValue(row,col) == 0){

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

// method: sample_barM
//
// arguments: 
//  
//  
//
// return: bool8 value
//
// 
//
template <class emission_type>
bool8 HDPHMM<emission_type>::sample_barM(){
  double p;
  if ((float32)hyper_d.rho > 0.0){
    counts_d.barM.assign(counts_d.M);
    for(int32 j = 0; j < counts_d.M.getNumColumns();j++){

      
	p = hyper_d.rho/(((dist_struct_d.beta_vec(j)*(1-hyper_d.rho))+hyper_d.rho));

	
      counts_d.sumW(j) = randbinom(p,counts_d.M.getValue(j,j));
      
      counts_d.barM.setValue(j,j,counts_d.M.getValue(j,j)-counts_d.sumW(j));
      
    }
  }
  else{
    counts_d.barM.assign(counts_d.M);
    for(int32 j = 0; j < counts_d.M.getNumColumns();j++)
      counts_d.sumW(j) = 0;
    
  }
   
  // return gracefully
  //
  return true;
}

// method: randbinom
//
// arguments: 
//  
//  
//
// return: bool8 value
//
// 
//
template <class emission_type>
 int32 HDPHMM<emission_type>::randbinom(double p,int n){
   
   double DEF_EPSILON = DBL_EPSILON;
   VectorDouble params(2),b_temp;
   int r = 0;

   if(isnan(p)) return 0;
   if(p < DEF_EPSILON) return 0;
   if(p >= 1-DEF_EPSILON) return n;

   if((p > 0.5) && (n < 15)) {
     
     /* Coin flip method. This takes O(n) time. */
     int i;
     for(i=0;i<n;i++) {
       if(uniform_gen_d.get()  < p) r++;
     }

     
     return r;
   }
   if(n*p < 10) {
     
     /* Waiting time method.  This takes O(np) time. */
     double q = -log(1-p), e = -log(uniform_gen_d.get()), s;
     r = n;
     for(s = e/r; s <= q; s += e/r) {
       r--;
       if(r == 0) break;
       e = -log(uniform_gen_d.get());
     }
     r = n-r;
     
     return r;
   }
    
   if(1) {

    // Recursive method.  This makes O(log(log(n))) recursive calls. 
    //
     int32  i = (int32)(p*(n+1));

    double  rtmp;
    gamma_rand_d.setParameters((float64)i);
    rtmp=gamma_rand_d.get();
    gamma_rand_d.setParameters((float64)(n+1-i));
    double b = rtmp/(rtmp + gamma_rand_d.get());

    if(b <= p) r = i + randbinom((p-b)/(1-b), n-i);
    else r = i - 1 - randbinom((b-p)/b, i-1);
    
    
   return r;
   }
}

// method forward_message_compute
//
// arguments: 
//  
//  
//
// return: bool8 value
//
// compute the forward messages
//
template <class emission_type>
bool8 HDPHMM<emission_type>::forward_message_compute(int32 T,VectorDouble& neg_log_c){

  // local  variables
  //
  VectorDouble partial_marg;
  
  Vector<VectorDouble> fwd_msg;
  fwd_msg.setLength(T);
  Double sum_fwd_msg;

  
  neg_log_c.assign(log_normalize_d);
  
  // it might be better to precompute T for all data points 
  // and do these stuff in initilize
  //
  partial_marg.setLength(Kz_d);
  
  for (int32 i = 0; i < T; i++){
    fwd_msg(i).setLength(Kz_d);
    fwd_msg(i).setRange(0,Kz_d,1);
 
  }

  for (int32 kz = 0; kz < Kz_d; kz++){  
    fwd_msg(0)(kz)= dist_struct_d.pi_init(kz)*emissions_d(kz).marg_like_d(0);
  }
  sum_fwd_msg=fwd_msg(0).sum();
  if(sum_fwd_msg != 0.0) 
    fwd_msg(0).div(sum_fwd_msg);
  neg_log_c(0) =neg_log_c(0) + log(sum_fwd_msg);
  MatrixDouble pi_z;
  pi_z.assign(dist_struct_d.pi_z);
  pi_z.transpose();
  for(int32 t = 0; t < T-1 ; t++){

 
    pi_z.multv(partial_marg,fwd_msg(t));
    
    for (int32 kz = 0; kz < Kz_d; kz++){    
      fwd_msg(t+1)(kz)=partial_marg(kz)*emissions_d(kz).marg_like_d(t+1);
    }

    sum_fwd_msg=fwd_msg(t+1).sum();
    if(sum_fwd_msg != 0.0)
      fwd_msg(t+1).div(sum_fwd_msg);
    neg_log_c(t+1) =  neg_log_c(t+1) + log(sum_fwd_msg);

   
  }

  // return
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
// compute the likelihood for an observation for model stored in model_d
//
template <class emission_type>
bool8 HDPHMM<emission_type>::observation_likelihood(){

  // print a message based on verbosity level
  //
  if ( verbosity_d > Integral::NONE || debug_level_d > Integral::NONE){
    Console::increaseIndention();
    Console::put(L"observation_lielihood()");
    Console::decreaseIndention();
  }

  
  for(int32 i = 0; i<Kz_d ;i++){
    emissions_d(i).compute_cholesky();
  }

  // local varables
  //
  VectorDouble neglog_c;

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
    Long T = db_d->curr_data_d.getNumColumns();
   
    
    
    // compute the log likelihood
    // at each call "log_likelihood" variable will be updated by the likelihood 
    // the current point (points accessed successively)
    //     
    for(int32 kz = 0;kz < Kz_d; kz++){

      //if (data_records == db_d->get_records_no()-1){
      // printf("kz %d/%d\n",kz,(int32)Kz_d);
       //emissions_d(kz).log_likelihood_d.debug(L"LL_before_norm");
       //    }
      // compute the likelihood for each emission distribution
      // without normaliztion
      //
     emissions_d(kz).compute_loglikelihood(T,false);

     //printf ("LL size %d %d %f\n",emissions_d(kz).log_likelihood_d.length(),emissions_d(kz).log_likelihood_d(0).length(),(double)emissions_d(kz).log_likelihood_d(0)(9));

     // emissions_d(kz).log_likelihood_d.debug(L"LL");
    
    }

    VectorLong KS(Kz_d);
    for(int32 kz=0;kz< Kz_d; kz++){
      KS(kz) = emissions_d(kz).getKs();  
    }
    
    //printf("master  %d\n",(int)KS.max());
    
     //debug 
    VectorDouble temp_log_vec(KS.max());

    log_normalize_d.clear();
    log_normalize_d.setLength(T);

    for(int32 i = 0; i < T; i++){
     
      for (int32 j = 0;j < KS.max() ; j++){
	  VectorDouble tmp_vec(Kz_d);
      for(int32 kz = 0; kz < Kz_d; kz++){
	//debug added
	if(j< KS(kz)){
	  tmp_vec(kz) = emissions_d(kz).log_likelihood_d(i)(j);
	}else
	  {
	    //printf("zero vlaue\n");
	    tmp_vec(kz)=-1.0/0.0;
            
	  }
	//	  temp_log_vec(kz) =emissions_d(kz).log_likelihood_d(i)(j);
	}
      temp_log_vec(j) = tmp_vec.max();
	}
      log_normalize_d(i) = temp_log_vec.max(); 
    }

    //log_normalize_d.debug(L"lnd");
   
    for(int32 kz = 0;kz < Kz_d; kz++){
   
  
      // convert form log to linear scale
      //    
      for (int32 seq_t = 0; seq_t < T; seq_t++){
	
	// normalize
	//
	emissions_d(kz).normalize(seq_t, log_normalize_d(seq_t));

	emissions_d(kz).log_likelihood_d(seq_t).exp();
	
      }

      // COMPUTE MARGINAL LIKELIHOODS
      //
      emissions_d(kz).compute_marginal_ll();
    }


    
    /*for(int32 kz = 0;kz <Kz_d; kz++){
   
 if (data_records == db_d->get_records_no()-1){
   printf("kz %d\n",kz);
   emissions_d(kz).log_likelihood_d.debug(L"LL_after_norm");
 }

 }
 
    
for(int32 kz = 0;kz < Kz_d; kz++){
   for (int32 seq_t = 0; seq_t < T; seq_t++){

     emissions_d(kz).log_likelihood_d(seq_t).exp();

   }
 }

 for(int32 kz = 0;kz <Kz_d; kz++){
   
 if (data_records == db_d->get_records_no()-1){
   printf("kz %d\n",kz);
   emissions_d(kz).log_likelihood_d.debug(L"LL_after_exp");
 }

 }
 
 for(int32 kz = 0;kz < Kz_d; kz++){
    emissions_d(kz).compute_marginal_ll();
 }
    */

    ///  fix  this   (debug?)
 for (int32 seq_t = 0; seq_t < T; seq_t++){
      
    log_normalize_d(seq_t) = log_normalize_d(seq_t) - (39/2*log(2*3.1416)); 
      
   }

 //if (data_records == db_d->get_records_no()-1)
 //   log_normalize_d.debug(L"lln");

  
    forward_message_compute(T,neglog_c);

    //T.debug(L"T");
    //    neglog_c.debug(L"netlog_c");
    // average log-likelihood for this  observation
    //
    observed_log_likelihood_d(data_records) = neglog_c.sum() / T;
    
  }  // end  of  loop over dataset

  /* Double LL = 0;
  Long  count1 = 0;
  for (int32 data_records = 0; data_records < db_d->get_records_no(); data_records++){

    db_d->get(data_records);
    
    int32 T = db_d->curr_data_d.getNumColumns();

    LL = LL + observed_log_likelihood_d(data_records) * (Double)T;
    count1 = count1 +T;
  }
  LL=LL/(Double)count1;
  LL.debug(L"LL");
  */
  // return gracefully
  //
  return true;

}





// method: find_path
//
// arguments: 
//  
// Algorithms :{Viterbi=0,Forward-Backward=1, Defualt : Viterbi}  
//
// return: bool8 value
//
// compute the find_path
//
//
template <class emission_type>
bool8 HDPHMM<emission_type>::find_path(const String& algorithm_a){
  
  // Kz_d.debug(L"kz_d");
  observed_log_likelihood_d.setLength(db_d->get_records_no());
  observed_path_d.setLength(db_d->get_records_no());
  observed_mix_d.setLength(db_d->get_records_no());

  post_prob_d.setLength(db_d->get_records_no());
  
  for(int32 i = 0; i<Kz_d ;i++){
    emissions_d(i).compute_cholesky();
  }

  int32 data_len = db_d->get_records_no();
  // loop over all data points
  //   
  for (int32 data_records = 0; data_records < data_len; data_records++){

    // read the data
    //
    db_d->get(data_records);
    
    // seqeuece length
    //
    int32 T = db_d->curr_data_d.getNumColumns();


    observed_path_d(data_records).setLength(T);
    observed_mix_d(data_records).setLength(T);

    post_prob_d(data_records).setDimensions(Kz_d,T);
    // compute the log likelihood
    // at each call "log_likelihood" variable will be updated by the likelihood 
    // the current point (points accessed successively)
    //     
   
    // compute the likelihood for each emission distribution
    // without normaliztion 
    //


       for(int32 kz = 0;kz < Kz_d; kz++){

	 emissions_d(kz).compute_loglikelihood(T,false);

	 
       }
       VectorLong KS(Kz_d);
       for(int32 kz=0;kz< Kz_d; kz++){
	 KS(kz) = emissions_d(kz).getKs();  
       }


    //    master_emission_d.compute_loglikelihood(T,false);

    log_normalize_d.clear();
    log_normalize_d.setLength(T);

    
    // Long Ks = master_emission_d.getKs();
    Long Ks=KS.max();

#pragma omp parallel
    {
      
      VectorDouble temp_log_vec(Ks); //debug Ks_d
  
      #pragma omp for
      for(int32 i = 0; i < T; i++){
	for (int32 j = 0;j < Ks; j++){ //debug Ksd
	  VectorDouble tmp_vec(Kz_d);
	  for(int32 kz = 0; kz < Kz_d; kz++){
	    
	    if(j< KS(kz)){
	      tmp_vec(kz) = emissions_d(kz).log_likelihood_d(i)(j);
	    }else
	      {
		//printf("zero vlaue\n");
		tmp_vec(kz)=-1.0/0.0;
		
	      }

	    //tmp_vec(kz) = emissions_d(kz).log_likelihood_d(i)(j);
	    //        temp_log_vec(kz) =emissions_d(kz).log_likelihood_d(i)(j);
	  }
	  temp_log_vec(j) = tmp_vec.max();
	}
	log_normalize_d(i) = temp_log_vec.max();
      }
      
       #pragma omp for 
	for(int32 kz = 0;kz < Kz_d; kz++){
   
      
	  // convert form log to linear scale
	  //    
	  for (int32 seq_t = 0; seq_t < T; seq_t++){
	    
	    // normalize
	    //
	    emissions_d(kz).normalize(seq_t, log_normalize_d(seq_t));
	    emissions_d(kz).log_likelihood_d(seq_t).exp();
	  }
	  /* for (int32 seq_t = 0; seq_t < T; seq_t++){
	    for (int32 j = 0;j < Ks; j++){ //debug Ksd      
	      emissions_d(kz).log_likelihood_d(seq_t)(j).exp();
	    }
	  }
	  */
	  
	  // compute marginal likelihoods  (for each state)
	  //
	  emissions_d(kz).compute_marginal_ll();
	  //emissions_d(kz).marg_like_d(0).debug(L"ml");
	}
    }

    if (algorithm_a.eq(L"viterbi",false)){
    
	partial_marg_d.clear();
	partial_marg_d.setLength(T);
	for (int32 i = 0; i < T; i++){
	  partial_marg_d(i).setLength(Kz_d);
	}
     
	//MatrixDouble delta(Kz_d,T);
	// track the state
	//
	MatrixLong psi(Kz_d,T);
	Double tmp_sum;
	for (int32 kz = 0; kz < Kz_d; kz++){    
	  
	  // multiplie likelihoods with incoming message
	  //
	  partial_marg_d(0)(kz) = emissions_d(kz).marg_like_d(0) * dist_struct_d.pi_init(kz);
      
      
	  psi.setValue(kz,0,(int)0); 
	}
    
	for(int32 t = 1; t < T; t++){
	  for (int32 kz = 0; kz < Kz_d; kz++){
	    VectorDouble tmp_prob(Kz_d);
	    for (int32 kz2 = 0; kz2 < Kz_d; kz2++){
	      tmp_prob(kz2) = partial_marg_d(t-1)(kz2)*dist_struct_d.pi_z(kz2,kz);
	    }
	    int32 pos_max;
	    partial_marg_d(t)(kz) = tmp_prob.max(pos_max);
	    partial_marg_d(t)(kz) = partial_marg_d(t)(kz) * emissions_d(kz).marg_like_d(t);
	    psi.setValue(kz,t,pos_max);
	  }
	}
	
	// back track
	//
	Double path_prob;
	int32 pos_max,pos_max2;
	VectorLong path(T);
	VectorLong path_mix(T);
	VectorDouble temp1;
	path_prob = partial_marg_d(T-1).max(pos_max);
	path(T-1) = pos_max;
	emissions_d(path(T-1)).mix_prob_d(T-1).max(pos_max2);
	path_mix(T-1) = pos_max2;
	for (int32 t=T-2;t>=0;t--){
	  path(t) = psi(path(t+1),t+1);
	  emissions_d(path(t)).mix_prob_d(t).max(pos_max2);
	  path_mix(t) = pos_max2;

	}
	observed_mix_d(data_records).assign(path_mix);
	observed_path_d(data_records).assign(path);
	observed_log_likelihood_d(data_records) = path_prob.log();

      
    }// end of viterbi
    else if (algorithm_a.eq(L"forward",false)){
      VectorDouble Pz(Kz_d);
      int32 pos_max,pos_max2;
      VectorLong path(T);
      VectorLong path_mix(T);
      // compute the backward messages
      //
      backward_message_compute(T);
      for (int32 seq_t = 0; seq_t < T; seq_t++){
     
      
      // sample Z for the the first frame
      //
      if (seq_t == 0){
	Pz.mult(dist_struct_d.pi_init,partial_marg_d(0));    
      }

      // sample Z for other frames
      //
      else{
	VectorDouble temp;
	dist_struct_d.pi_z.getRow(temp,path(seq_t-1));
       
	Pz.mult(temp,partial_marg_d(seq_t));
      }
      Pz.max(pos_max);
      path(seq_t) = pos_max;
      emissions_d(path(seq_t)).mix_prob_d(seq_t).max(pos_max2);
      path_mix(seq_t) = pos_max2;
      post_prob_d(data_records).setColumn(seq_t,Pz);
      }
      observed_mix_d(data_records).assign(path_mix);
      observed_path_d(data_records).assign(path);
    }
    else{
      printf("algorithm is not known in find_path\n");
      exit(2);
    }
    
	
  } // loop over all data

  return true;
}





