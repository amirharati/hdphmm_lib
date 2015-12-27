// file: $isip/util/speech/isip_hdphmm_train/isip_hdphmm_train.cc
//
// Amir Harati
//

// This program can by used for training HDPHMM/DHDPHMM models, also
// it can be used for decoding the model, finding the Viterbi Path,
// finding posterioirgram representation
//
// usage 1(train):
//
//isip_hdphmm_train -params_file params.sof -train_file train.db  -itr $itr -raw_model raw_model  -final_model final_model -burn_in $burnin
// where train.db is a database file (look at class/mmedia/Database.h)
// $burnin is the number of iterations to be discared
// if  we want to to continue from a saved model (should be saved in raw format)
//isip_hdphmm_train -params_file params.sof -train_file train.db  -itr $itr -raw_model raw_model  -final_model final_model -load old_raw_model -burn_in $burnin
// usage 2 (decode):
//
//  isip_hdphmm_train -final_model final_model -log_likelihood eval.db
//  this command  read a final model in final_model and compute likelihood of all data points in eval.db and print them in the screen
//
// usage 3 (Viterbi Path/State)
//
// isip_hdphmm_train -final_model final_model -alignment train.db  -alignment_algorithm viterbi -alignment_dir out_dir -alignment_time frame -alignment_mode state
//
//  where  we used viterbi algorith, and output in out_dir(one file per utterance in HTK format). We have also used state model
//
// usage 4 (forward algorithm path generate posteriorgram probablities over state)
//
// isip_hdphmm_train -final_model final_model -alignment train.db  -alignment_algorithm forward -alignment_dir out_dir -alignment_time frame -alignment_mode state 
//



// isip include files
//
#ifndef ISIP_UTIL_HDPHMM_TRAIN
#include "isip_hdphmm_train.h"
#endif


DebugLevel verbosity_d;
DebugLevel debug_level_d;
Filename log_file_d;
Filename raw_model_d;
Filename final_model_d;
String output_mode_d;
Filename train_file_d;
String emission_type_d;
String structure_type_d;
String hmm_params_d;
Long Kz_d = 0;
String emission_params_d;
String itr_d;
Long init_itr_d = -1;
Long burnin_d = -1;
String seeds_d;
Long extract_model_mode_d;
String log_likelihood_d;
String update_emission_option;
bool8 update_only_emissions_d;

// the aligment_s is either empty or contains the name of db to be aligned
// 
//
String alignment_d;
String alignment_mode_d;
String alignment_algorithm_d;
String alignment_dir_d;
String alignment_time_d;

// reduce the final model to min model (def. =true)
String reduce_final_option;
bool8 reduce_final_d;

// isip_hdphmm_train: train hdphmm model
//
int main(int argc, const char** argv) {

  // local variables
  //
  String output;
 
  // setup the command line
  //
  Sdb sdb;
  CommandLine cmdl(sdb);
  cmdl.setUsage(
#include "usage_message.text"
                );
  cmdl.setHelp(
#include "help_message.text"
               );

  cmdl.setIdent("$Revision: 10625 $",
		"$Name: $",
		"$Date: 2013-11-06 11:05:28 -0500 $");
   
  
 
  // add a command line option for param file
  //
  Filename params_file;
  cmdl.addOptionParam(params_file,OPTION_PARAMS_FILE,(Filename)EMPTY);

  // add a command line option for loading a saved model
  //
  Filename load_model;
  cmdl.addOptionParam(load_model,OPTION_LOAD_MODEL,(Filename)EMPTY);


  // add a command line option for the debug level
  //
  cmdl.addOptionParam(debug_level_d, OPTION_DEBUG_LEVEL,-1);

  // add a command line option for the log verbosity_dlevel
  //
  cmdl.addOptionParam(verbosity_d, OPTION_VERBOSITY_LEVEL,-1);


  // add a command line option for the log file
  //
  cmdl.addOptionParam(log_file_d, OPTION_LOG_FILE, (Filename)LOG_FILE_DEFAULT);


  // add a command line option for the output file
  //
  cmdl.addOptionParam(raw_model_d, OPTION_RAW_MODEL, (Filename)EMPTY);

 // add a command line option for the output file
  //
  cmdl.addOptionParam(final_model_d, OPTION_FINAL_MODEL, (Filename)EMPTY);

  // add a command line option for output mode
  //
  cmdl.addOptionParam(output_mode_d, OPTION_OUTPUT_MODE,(String)EMPTY);
  
  // add a command line option for the training database
  //
  cmdl.addOptionParam(train_file_d, OPTION_TRAIN_FILE, (Filename)EMPTY);


  // add a command line option for emission type
  //
  cmdl.addOptionParam(emission_type_d, OPTION_EMISSION_TYPE,(String)EMPTY);


  // add a command line option for emission type
  //
  cmdl.addOptionParam(structure_type_d, OPTION_STRUCTURE_TYPE,(String)EMPTY);

  // add a command line option for  hmm hyper params
  //
  cmdl.addOptionParam(hmm_params_d, OPTION_HMM_PARAMS,(String)EMPTY);

  // add a command line option for Kz
  //
  cmdl.addOptionParam(Kz_d, OPTION_KZ,0);

  // add a command line option for  emission params
  //
  cmdl.addOptionParam(emission_params_d, OPTION_EMISSION_PARAMS,(String)EMPTY);


  // add a command line option for itr
  //
  cmdl.addOptionParam(itr_d, OPTION_ITR,L"");

 // add a command line option for init_itr
  //
  cmdl.addOptionParam(init_itr_d, OPTION_INIT_ITR,-1);

  // add a command line option for burn_in
  //
  cmdl.addOptionParam(burnin_d, OPTION_BURNIN,-1);

  // add a command line option for  emission params
  //
  cmdl.addOptionParam(seeds_d, OPTION_SEEDS,(String)EMPTY);

  // add a command line option for extract_model option
  //
  cmdl.addOptionParam(extract_model_mode_d,OPTION_EXTRACT_MODEL_MODE,0);

  cmdl.addOptionParam(log_likelihood_d,OPTION_LOG_LIKELIHOOD,(String)EMPTY);


  cmdl.addOptionParam(update_emission_option,OPTION_UPDATE_EMISSIONS,L"false");


  cmdl.addOptionParam(alignment_d,OPTION_ALIGNMENT,(String)EMPTY);
  cmdl.addOptionParam(alignment_mode_d,OPTION_ALIGNMENT_MODE,(String)ALIGNMENT_MODE_DEFAULT);
  cmdl.addOptionParam(alignment_algorithm_d,OPTION_ALIGNMENT_ALGORITHM,(String)ALIGNMENT_ALGORITHM_DEFAULT);
  cmdl.addOptionParam(alignment_time_d,OPTION_ALIGNMENT_TIME,(String)ALIGNMENT_TIME_DEFAULT);
  cmdl.addOptionParam(alignment_dir_d,OPTION_ALIGNMENT_DIR,(String)EMPTY);


  cmdl.addOptionParam(reduce_final_option,OPTION_REDUCE_FINAL,L"true");
  
  // parse the command line
  //
  if (!cmdl.parse(argc, argv)) {
    cmdl.printUsage();
  };
 

  if (reduce_final_option.eq(L"false",false)){
  
    reduce_final_d = false;
  }
  else if (reduce_final_option.eq(L"true",false)){
    
    reduce_final_d = true;
  }
  
  if (update_emission_option.eq(L"false",false)){
    
    update_only_emissions_d = false;
  }
  else if (update_emission_option.eq(L"true",false)){
    update_only_emissions_d = true;
  }
  // open the log file
  //
  if (log_file_d.ne(L"-")) {
    Console::open(log_file_d);
    Console::setLineWrap(File::NO_WRAP);
  }


  // if alignment mode is active
  //
  if (alignment_d.eq(L"")==false){
   
    if(final_model_d.eq(L"")){
      output.assign(L"-final_model should be specified.\n");
      Console::put(output);
      exit(-1);
    }
    HDPHMM<DPM> hdphmm1;
    Database db1;
    db1.init(alignment_d);
    hdphmm1.load_final_model(final_model_d,db1);
    hdphmm1.find_path(alignment_algorithm_d);

    
    //File::mkdir(alignment_dir_d);
    // loop over records
    //
    for(int32 rn=0;rn<db1.get_records_no();rn++){
      int32 len;
      File f1;
      db1.get(rn);
      String s1,s2,s3;
      int fpos;
      fpos = db1.curr_fname_d.lastStr(L"/");
      db1.curr_fname_d.substr(s3,fpos+1);
      //s1.assign(rn);
      //s1.concat(L"_");
      s1.assign(s3);
      fpos = s1.lastStr(L".");
      s1.substr(s3,0,fpos);
      s1.assign(s3);
      s1.concat(L".lab");
      s2.assign(alignment_dir_d);
      s2.concat(L"/");
      s2.concat(s1);
      if(!f1.open(s2,File::WRITE_ONLY)){
	Console::put(L"Error in open");
      }
      len = hdphmm1.observed_path_d(rn).length();

      int32 fr_start=0;
      int32 fr_end=0;
      Double fr_rate=db1.db_fr_d; // in msec
      Long mstate;
      Long cstate = hdphmm1.observed_path_d(rn)(0);
      Long cmix = hdphmm1.observed_mix_d(rn)(0);
      if (alignment_mode_d.eq(L"state",false)){
	mstate = cstate;
      }
      else if (alignment_mode_d.eq(L"state+mix",false)){
	mstate = cstate*1000+cmix;
      }
      else{
	printf("Error for the alignment mode.\n");
	exit(2);
      }
      
      for(int32 i=1;i<len;i++){
	int32 mstate2;
	if (alignment_mode_d.eq(L"state",false)){
	  mstate2 = hdphmm1.observed_path_d(rn)(i);
	}
	else if (alignment_mode_d.eq(L"state+mix",false)){
	  mstate2 = hdphmm1.observed_path_d(rn)(i)*1000+hdphmm1.observed_mix_d(rn)(i);
	}
	if (alignment_algorithm_d.eq(L"forward",false)){ // for forward output the postrior prob.
	  String out1;
	  int32 st_time;
	  int32 en_time;
	  int32 kz=hdphmm1.post_prob_d(rn).getNumRows();
	  VectorDouble tmp(kz);
	  hdphmm1.post_prob_d(rn).getColumn(tmp,i);
	  
	  if (alignment_time_d.eq(L"frame",false)){
	    st_time = (int32)fr_start;
	    en_time = (int32)fr_end;
	  }
	  else if (alignment_time_d.eq(L"HTK",false)){
	    st_time = (int32)fr_start * fr_rate * 10000;
	    en_time = (int32)fr_end * fr_rate * 10000;

	  }
	  out1.assign(st_time);
	  out1.concat(L" ");
	  out1.concat(en_time);
	  out1.concat(L" ");
	  for(int32 j=0;j<kz;j++){
	    out1.concat(tmp(j));
	    out1.concat(L" ");
	  }
	  out1.concat(L"\n");
	  f1.put(out1);
	  fr_start = i;
	  fr_end = i;
	}
	if (alignment_algorithm_d.eq(L"viterbi",false) and (mstate2 != mstate or i==len-1)){
	  String out1;
	  int32 st_time;
	  int32 en_time;
	  if (alignment_time_d.eq(L"frame",false)){
	    st_time = (int32)fr_start;
	    en_time = (int32)fr_end;
	  }
	  else if (alignment_time_d.eq(L"HTK",false)){
	    st_time = (int32)fr_start * fr_rate * 10000;
	    en_time = (int32)fr_end * fr_rate * 10000;

	  }
	  out1.assign(st_time);
	  out1.concat(L" ");
	  out1.concat(en_time);
	  out1.concat(L" ");
	  out1.concat(cstate);
	  if (alignment_mode_d.eq(L"state+mix",false)){
	    out1.concat(L" ");
	    out1.concat(cmix);
	  }
	  out1.concat(L"\n");
	  f1.put(out1);
	   
	  cstate = hdphmm1.observed_path_d(rn)(i);
	  cmix = hdphmm1.observed_mix_d(rn)(i);
	  if (alignment_mode_d.eq(L"state",false)){
	    mstate = cstate;
	  }
	  else if (alignment_mode_d.eq(L"state+mix",false)){
	    mstate = cstate*1000+cmix;
	  }
	  fr_start = i;
	  fr_end = i;
	}
	else{
	  fr_end++; 
	}
      }//len
      f1.close();
    } //files
  }
  // calculate the log likelihood
  //
  else if(log_likelihood_d.eq(L"")==false){

    HDPHMM<DPM> hdphmm1;
    Database db1;
   
   
    if(final_model_d.eq(L"")){
      output.assign(L"-final_model should be specified.\n");
      Console::put(output);
      exit(-1);
    }

    // load the database
    //
    db1.init(log_likelihood_d);
    hdphmm1.load_final_model(final_model_d,db1);
    hdphmm1.observation_likelihood();
    
    
    // print the output
    //

    for(int32 i = 0; i < hdphmm1.observed_log_likelihood_d.length()-1;i++){
      printf("%f,",(double)hdphmm1.observed_log_likelihood_d(i));
      
    }
    printf("%f\n",(double)hdphmm1.observed_log_likelihood_d(hdphmm1.observed_log_likelihood_d.length()-1));

  }

  else{
    // param file message
    //  
    if (verbosity_d >= Integral::BRIEF) {
      Console::increaseIndention();    
      output.assign(L"\n Reading the parameter file.");
      output.concat(params_file);
      Console::put(output);
      Console::decreaseIndention();    
    }
    
    // parse the params file
    //
    Sof param_sof;
    if (params_file.eq(L"")==false){
      if (!param_sof.open(params_file, File::READ_ONLY)) {
	output.assign(L"\ncannot open file: ");
	output.concat(params_file);
	output.concat(L", bailing out...");
	Console::put(output);
	exit(-1);
      }
      read(param_sof,0,L"HDPHMM_PARAMS");
      param_sof.close();
    }
    else{
      output.assign(L"\n-params_file is missing");
      Console::put(output);
      exit(-1);
    }
    
    // load the  default values
    //
    if(seeds_d.eq(L""))
      seeds_d.assign(SEEDS_DEFAULT);
    
    
    if(structure_type_d.eq(L""))
      structure_type_d.assign(STRUCTURE_TYPE_DEFAULT);
    if(output_mode_d.eq(L""))
      output_mode_d.assign(OUTPUT_MODE_DEFAULT);
    
    
    // print the command line
    //
    if (verbosity_d >= Integral::BRIEF) {
      cmdl.printCommandLine();
      cmdl.printVersion();
    }
    
    // check for errors
    //
    if(extract_model_mode_d == 0)
      {
	if (hmm_params_d.countTokens(L",") != 6){
	  output.assign(L"HMM hyper parameter is a vector with length 6.");
	  output.concat(L"a_alpha,b_alpha,a_gamma,b_gamma,c,d");
	  output.concat(L"Example: 10,1,10,1,100,1");
	  Console::put(output);
	  exit(-1); 
	}
 
	if (emission_type_d.eq(L"DPM")){
	  if (emission_params_d.countTokens(L",") != 6){
	    output.assign(L"emission params for DPM is a vector with length 6.\n");
	    output.concat(L"Ks,emission_type(0,1,2),a_sigma,b_sigma,kappa,DF");
	    output.concat(L"Example: 10,1,10,1,.1,5");
	    Console::put(output);
	    exit(-1); 
	  }
	}
    
    
	if (emission_type_d.eq(L"HDP")){
	  if (emission_params_d.countTokens(L",") != 8 and emission_params_d.countTokens(L",") != 9){
	    output.assign(L"emission params for HDP is a vector with length 8 or 9.\n");
	    output.concat(L"Example: Ks,[Kc(if not specified then it will be the same as Ks)],a_sigma,b_sigma,a_landa,b_landa,kappa,DF");
	    output.concat(L"Example: 10,1,10,1,10,1,.1,5");
	    Console::put(output);
	    exit(-1); 
	  }
	}
    

	if(structure_type_d.ne(L"ERGODIC") && structure_type_d.ne(L"LEFT_TO_RIGHT") && structure_type_d.ne(L"STRICTLY_LEFT_TO_RIGHT") && structure_type_d.ne(L"LEFT_TO_RIGHT_WITH_LOOP" ) && structure_type_d.ne(L"LEFT_TO_RIGHT_WITH_LOOP_TO_FIRST")){
	  
	  output.assign(L"Structure type should either be:\n");
	  output.concat(L"1) ERGODIC 2) LEFT_TO_RIGHT 3) STRICTLY_LEFT_TO_RIGHT 4) LEFT_TO_RIGHT_WITH_LOOP 5) LEFT_TO_RIGHT_WITH_LOOP_TO_FIRST ");
	  Console::put(output);
	  exit(-1); 
	}
    
	if(Kz_d <= 0){
	  
	  output.assign(L"Kz is not specifed or invalid (<=0).");
	  Console::put(output);
	  exit(-1); 
	}
    
    
    
	if ( train_file_d.eq(L"")){
	  output.assign(L"train file(input) is not specified.\n");
	  Console::put(output);
	  exit(-1);
	}
	
	if ( raw_model_d.eq(L"")){
	  output.assign(L"raw_model (output) is not specified.\n");
	  Console::put(output);
	  exit(-1);
	}
    
	if (itr_d.eq(L"") || init_itr_d == -1){
	  output.assign(L"itr or init_itr are not specified.\n");
	  Console::put(output);
	  exit(-1);
	}
      }
    
    // database
    //
    Database db;
    //if(extract_model_mode_d == 0)
    db.init(train_file_d);
    
    VectorLong itrs;
    itrs.assign(itr_d);
    itrs.sort();
    
    String sub1,sub2,raw_model,sub1_2,sub2_2,final_model;
    int32 pos,pos2;
    raw_model_d.tokenize(sub1,pos,L".");
    raw_model_d.tokenize(sub2,pos,L".");
    
    final_model_d.tokenize(sub1_2,pos2,L".");
    final_model_d.tokenize(sub2_2,pos2,L".");
    
    // inference  message
    //  
    if (verbosity_d >= Integral::BRIEF) {
      Console::increaseIndention();    
      output.assign(L"\n Inference statrs...");
      Console::put(output);
      Console::decreaseIndention();    
    }
    
    // DPM emission
    //
    if(emission_type_d.eq(L"DPM")){
      HDPHMM<DPM> hdphmm;
      VectorDouble hmm_params, emission_params;
      hmm_params.assign(hmm_params_d);
      emission_params.assign(emission_params_d);
      hdphmm.set_Kz(Kz_d);
      hdphmm.set_HMM_params(hmm_params);
      if (structure_type_d.eq(L"ERGODIC")){
	
	hdphmm.set_structureType(HDPHMM<DPM>::ERGODIC);
      }
      else if (structure_type_d.eq(L"LEFT_TO_RIGHT")){
	
	hdphmm.set_structureType(HDPHMM<DPM>::LEFT_TO_RIGHT);
      }
      else if (structure_type_d.eq(L"LEFT_TO_RIGHT_WITH_LOOP")){
	
	hdphmm.set_structureType(HDPHMM<DPM>::LEFT_TO_RIGHT_WITH_LOOP);
      }
      else if (structure_type_d.eq(L"LEFT_TO_RIGHT_WITH_LOOP_TO_FIRST")){
	
	hdphmm.set_structureType(HDPHMM<DPM>::LEFT_TO_RIGHT_WITH_LOOP_TO_FIRST);
      }
      else if (structure_type_d.eq(L"STRICTLY_LEFT_TO_RIGHT")){
	
	hdphmm.set_structureType(HDPHMM<DPM>::STRICTLY_LEFT_TO_RIGHT);
      }
      
      hdphmm.set_emission_params(emission_params);
      hdphmm.setDebug(debug_level_d);
      hdphmm.setVerbosity(verbosity_d);   
      hdphmm.set_db(db);
      VectorLong seeds;
      seeds.assign(seeds_d);
      
      int32 offset_itr = 0;
      
      if(extract_model_mode_d == 1){
	
	if(final_model_d.eq(L"")){
	  Console::put(L"-final_model  is not specified");
	  exit(-1);
	}
	
	VectorLong seeds(6);
       	hdphmm.load(seeds,raw_model_d);
	
	if(output_mode_d.eq(L"TEXT")){
	  if(final_model_d.eq(L"") == false){
	    hdphmm.extract_model(raw_model_d,final_model_d,File::TEXT,reduce_final_d);
	  }
	}
	else if(output_mode_d.eq(L"BINARY")){
	  if(final_model_d.eq(L"") == false){
	    hdphmm.extract_model(raw_model_d,final_model_d,File::BINARY,reduce_final_d);
	  }
	}
	
      }
      else{
	
	// load a model if specified
	//
	if(load_model.eq(L"") == false){
	  
	  // load message
	  //  
	  if (verbosity_d >= Integral::BRIEF) {
	    Console::increaseIndention();    
	    output.assign(L"\n loading the model file : ");
	    output.concat(load_model);
	    Console::put(output);
	    Console::decreaseIndention();    
	  }
	  
	  hdphmm.load(seeds,load_model);
	  
	  
	  // get the number of passed iterations for the model
	  //
	  offset_itr = hdphmm.get_iterations();

	  if (burnin_d > offset_itr || burnin_d > hdphmm.get_burnin()){

	    hdphmm.reset_accumulate();
	    
	  }
	  
	  // itr message
	  //  
	  if (verbosity_d >= Integral::BRIEF) {
	    Console::increaseIndention();    
	    output.assign(L"\n itr :");
	    output.concat(offset_itr+itrs(0));
	    Console::put(output);
	    Console::decreaseIndention();    
	  }
	  hdphmm.inference(seeds,itrs(0),init_itr_d,burnin_d,false,update_only_emissions_d);
	  
	}
	else{
	  offset_itr = 0;
	  
	  // itr message
	  //  
	  if (verbosity_d >= Integral::BRIEF) {
	  Console::increaseIndention();    
	  output.assign(L"\n itr :");
	  output.concat(offset_itr+itrs(0));
	  Console::put(output);
	  Console::decreaseIndention();    
	  }
	
	  hdphmm.inference(seeds,itrs(0),init_itr_d,burnin_d,true);
	}
	
	if (itrs.length() == 1){
	  raw_model.assign(raw_model_d);
	  final_model.assign(final_model_d);
	}
	else{ 
	  raw_model.assign(sub1);
	  raw_model.concat(L"_");
	  raw_model.concat(offset_itr+itrs(0));
	  if( sub2.eq(L"") == false)
	    raw_model.concat(L".");
	  raw_model.concat(sub2);
	  
	  final_model.assign(sub1_2);
	  final_model.concat(L"_");
	  final_model.concat(offset_itr+itrs(0));
	  if( sub2_2.eq(L"") == false)
	    final_model.concat(L".");
	  final_model.concat(sub2_2);
	
	}
	
	// store message
	//  
	if (verbosity_d >= Integral::BRIEF) {
	Console::increaseIndention();    
	output.assign(L"\n store in : ");
	output.concat(raw_model);
	Console::put(output);
	Console::decreaseIndention();    
	}
	
	// store  the model
	//
	if(output_mode_d.eq(L"TEXT")){
	  
	  hdphmm.store(raw_model,File::TEXT);
	  if(final_model_d.eq(L"") == false){
	    hdphmm.extract_model(raw_model,final_model,File::TEXT,reduce_final_d);
	  }
	}
	else if(output_mode_d.eq(L"BINARY")){
	  hdphmm.store(raw_model,File::BINARY);
	  if(final_model_d.eq(L"") == false){
	    hdphmm.extract_model(raw_model,final_model,File::BINARY,reduce_final_d);
	  }	
	}
	
	
	
	for (int32 i = 1 ; i < itrs.length(); i++){
	  
	  // itr message
	  //  
	if (verbosity_d >= Integral::BRIEF) {
	  Console::increaseIndention();    
	  output.assign(L"\n itr :");
	  output.concat(offset_itr+itrs(i));
	  Console::put(output);
	  Console::decreaseIndention();    
	}
	
	hdphmm.inference(seeds,itrs(i)-itrs(i-1),init_itr_d,burnin_d,false,update_only_emissions_d);
	
	raw_model.assign(sub1);
	raw_model.concat(L"_");
	raw_model.concat(offset_itr+itrs(i));
	if( sub2.eq(L"") == false)
	  raw_model.concat(L".");
	raw_model.concat(sub2);
	
	final_model.assign(sub1_2);
	final_model.concat(L"_");
	final_model.concat(offset_itr+itrs(i));
	if( sub2_2.eq(L"") == false)
	  final_model.concat(L".");
	final_model.concat(sub2_2);
	
      	
	// store message
	//  
	if (verbosity_d >= Integral::BRIEF) {
	  Console::increaseIndention();    
	  output.assign(L"\n store in : ");
	  output.concat(raw_model);
	  Console::put(output);
	  Console::decreaseIndention();    
	}
	
	// store  the model
	//
	if(output_mode_d.eq(L"TEXT")){
	  
	  hdphmm.store(raw_model,File::TEXT);
	  if(final_model_d.eq(L"") == false){
	    hdphmm.extract_model(raw_model,final_model,File::TEXT,reduce_final_d);
	  }
	}
	else if(output_mode_d.eq(L"BINARY")){
	  hdphmm.store(raw_model,File::BINARY);
	  if(final_model_d.eq(L"") == false){
	    hdphmm.extract_model(raw_model,final_model,File::BINARY,reduce_final_d);
	  }
	  
	}
	
	
	
	}
	
      }
    }
    
    // HDP emission
    //
    else if(emission_type_d.eq(L"HDP")){
      HDPHMM<HDP> hdphmm;
      
      VectorDouble hmm_params, emission_params;
      hmm_params.assign(hmm_params_d);
      emission_params.assign(emission_params_d);
      hdphmm.set_Kz(Kz_d);
      hdphmm.set_HMM_params(hmm_params);
      if (structure_type_d.eq(L"ERGODIC")){
	
	hdphmm.set_structureType(HDPHMM<HDP>::ERGODIC);
      }
      else if (structure_type_d.eq(L"LEFT_TO_RIGHT")){
	
	hdphmm.set_structureType(HDPHMM<HDP>::LEFT_TO_RIGHT);
	
      }
      else if (structure_type_d.eq(L"LEFT_TO_RIGHT_WITH_LOOP")){
	
	hdphmm.set_structureType(HDPHMM<HDP>::LEFT_TO_RIGHT_WITH_LOOP);
	
      }
      else if (structure_type_d.eq(L"LEFT_TO_RIGHT_WITH_LOOP_TO_FIRST")){
	
	hdphmm.set_structureType(HDPHMM<HDP>::LEFT_TO_RIGHT_WITH_LOOP_TO_FIRST);
	
      }
      else if (structure_type_d.eq(L"STRICTLY_LEFT_TO_RIGHT")){
	
	hdphmm.set_structureType(HDPHMM<HDP>::STRICTLY_LEFT_TO_RIGHT);
      }
      hdphmm.set_emission_params(emission_params);
      hdphmm.setDebug(debug_level_d);
      hdphmm.setVerbosity(verbosity_d);   
      hdphmm.set_db(db);
      VectorLong seeds;
      seeds.assign(seeds_d);
      
      int32 offset_itr;
      

      if(extract_model_mode_d == 1){
       
	if(final_model_d.eq(L"")){
	  Console::put(L"-final_model  is not specified");
	  exit(-1);
	}

	VectorLong seeds(6);
       	hdphmm.load(seeds,raw_model_d);
	
	if(output_mode_d.eq(L"TEXT")){
	  if(final_model_d.eq(L"") == false){
	    hdphmm.extract_model(raw_model_d,final_model_d,File::TEXT,reduce_final_d);
	  }
	}
	else if(output_mode_d.eq(L"BINARY")){
	  if(final_model_d.eq(L"") == false){
	    hdphmm.extract_model(raw_model_d,final_model_d,File::BINARY,reduce_final_d);
	  }
	}
	
      }
      else{
	// load a model if specified
	//
	if(load_model.eq(L"") == false){
	  
	  // load message
	  //  
	  if (verbosity_d >= Integral::BRIEF) {
	  Console::increaseIndention();    
	  output.assign(L"\n load model file : ");
	  output.concat(load_model);
	  Console::put(output);
	  Console::decreaseIndention();    
	  } 
	  
	  hdphmm.load(seeds,load_model);
	  
	  // get the number of passed iterations for the model
	  //
	  offset_itr = hdphmm.get_iterations();

	  if (burnin_d > offset_itr || burnin_d > hdphmm.get_burnin()){

	    hdphmm.reset_accumulate();
	    
	  }
	  
	  // itr message
	  //  
	  if (verbosity_d >= Integral::BRIEF) {
	    Console::increaseIndention();    
	    output.assign(L"\n itr : ");
	    output.concat(offset_itr+itrs(0));
	    Console::put(output);
	    Console::decreaseIndention();    
	}
	  
	  hdphmm.inference(seeds,itrs(0),init_itr_d,burnin_d,false,update_only_emissions_d);
	  
	}
	else{
	  offset_itr = 0;
	  
	  // itr message
	  //  
	  if (verbosity_d >= Integral::BRIEF) {
	    Console::increaseIndention();    
	    output.assign(L"\n itr : ");
	    output.concat(offset_itr+itrs(0));
	    Console::put(output);
	    Console::decreaseIndention();    
	  }
	  
	  hdphmm.inference(seeds,itrs(0),init_itr_d,burnin_d,true);
	  
	}
      
	
	if (itrs.length() == 1){
	  raw_model.assign(raw_model_d);
	  final_model.assign(final_model_d);
	}
	else{
	  raw_model.assign(sub1);
	  raw_model.concat(L"_");
	  raw_model.concat(offset_itr+itrs(0));
	  if( sub2.eq(L"") == false)
	    raw_model.concat(L".");
	  raw_model.concat(sub2);
	  
	  final_model.assign(sub1_2);
	  final_model.concat(L"_");
	  final_model.concat(offset_itr+itrs(0));
	  if( sub2_2.eq(L"") == false)
	    final_model.concat(L".");
	  final_model.concat(sub2_2);
	  
	}
      
	// store message
	//  
      if (verbosity_d >= Integral::BRIEF) {
	Console::increaseIndention();    
	output.assign(L"\n store in : ");
	output.concat(raw_model);
	Console::put(output);
	Console::decreaseIndention();    
      }
      
      // store  the model
      //
      if(output_mode_d.eq(L"TEXT")){
	
	hdphmm.store(raw_model,File::TEXT);
	if(final_model_d.eq(L"") == false){
	  hdphmm.extract_model(raw_model,final_model,File::TEXT,reduce_final_d);
	}
      }
      else if(output_mode_d.eq(L"BINARY")){
	hdphmm.store(raw_model,File::BINARY);
	if(final_model_d.eq(L"") == false){
	  hdphmm.extract_model(raw_model,final_model,File::BINARY,reduce_final_d);
	}
      }
      
      for (int32 i = 1 ; i < itrs.length(); i++){
	
	// store message
	//  
	if (verbosity_d >= Integral::BRIEF) {
	  Console::increaseIndention();    
	  output.assign(L"\n itr : ");
	  output.concat(offset_itr+itrs(i));
	  Console::put(output);
	  Console::decreaseIndention();    
	}
	
	hdphmm.inference(seeds,itrs(i)-itrs(i-1),init_itr_d,burnin_d,false,update_only_emissions_d);
	
	raw_model.assign(sub1);
	raw_model.concat(L"_");
	raw_model.concat(offset_itr+itrs(i));
	if( sub2.eq(L"") == false)
	  raw_model.concat(L".");
	raw_model.concat(sub2);
	
	final_model.assign(sub1_2);
	final_model.concat(L"_");
	final_model.concat(offset_itr+itrs(i));
	if( sub2_2.eq(L"") == false)
	  final_model.concat(L".");
	final_model.concat(sub2_2);
	
	// store message
	//  
	if (verbosity_d >= Integral::BRIEF) {
	  Console::increaseIndention();    
	  output.assign(L"\n store in : ");
	  output.concat(raw_model);
	  Console::put(output);
	  Console::decreaseIndention();    
	}

	// store  the model
	//
	if(output_mode_d.eq(L"TEXT")){
	  
	  hdphmm.store(raw_model,File::TEXT);
	  
	  if(final_model_d.eq(L"") == false){
	    hdphmm.extract_model(raw_model,final_model,File::TEXT,reduce_final_d);
	  }
	}
	else if(output_mode_d.eq(L"BINARY")){
	  hdphmm.store(raw_model,File::BINARY);
	  if(final_model_d.eq(L"") == false){
	    hdphmm.extract_model(raw_model,final_model,File::BINARY,reduce_final_d);
	  }
	  
	}
	
      }
      }
    }
    
    else{
      
      // error message
      //
      output.assign(L"Emission type is unknown.");
      Console::put(output);
      exit(-1); 
    }
    
    
  }
      
  
  // exit message
  //  
  if (verbosity_d >= Integral::BRIEF) {
    Console::increaseIndention();    
    output.assign(L"\n Exit the program.");
    Console::put(output);
    Console::decreaseIndention();    
  }
  
  

  // close the log file
  //
  if (log_file_d.ne(L"-")) {
    Console::close();
  }

  // exit gracefully
  //
  return Integral::exit();
}
