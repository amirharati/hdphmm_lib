// file: $isip/util/speech/isip_hdphmm_train/isip_hdphmm_train_00.cc
//
// isip include files
//
#ifndef ISIP_UTIL_HDPHMM_TRAIN
#include "isip_hdphmm_train.h"
#endif

// method: read
//
// arguments:
//  Sof& sof: (input) sof file object
//  int32 tag: (input) sof object instance tag
//  const String& name: (input) sof object instance name
//
// return: a bool8 indicating status
//
// this method has the object read itself from an Sof file
//
bool8  read(Sof& sof_a, int32 tag_a, const String& name_a) {

   // get the instance of the object from the Sof file
   //
   if (!sof_a.find(name_a, tag_a)) {
    return false;
  }

  // read the actual data from the sof file
  //
   return readData(sof_a,name_a);
}

//method: readData
//
//arguments:
//Sof& sof: (input) sof file object
//const String& pname: (input) parameter name
//int32 size: (input) number of bytes in file
//bool8 param: (input) is the parameter specified?
//bool8 nested: (input) is this nested?
//
//return: logical error status
//
//this method has the object read itself from an Sof file. it assumes
//that the Sof file is already positioned correctly.
//
bool8 readData(Sof& sof_a, const String& pname_a,int32 size_a,bool8 param_a, bool8 nested_a) {

  Integral::DEBUG debug_level = Integral::NONE;

  SofParser parser;

  parser.setDebug(debug_level);

  // ignore implicit parameter setting
  //
  
  // are we nested?
  //
  if (nested_a) {
    parser.setNest();
  }
  
  // load the parse
  //
  if (!parser.load(sof_a, size_a)) {
    return false;   
  }	    

  if(parser.isPresent(sof_a,OPTION_TRAIN_FILE) && train_file_d.eq(L"")){
    train_file_d.readData(sof_a,OPTION_TRAIN_FILE,parser.getEntry(sof_a, OPTION_TRAIN_FILE),false, false);  
  }
  
 if(parser.isPresent(sof_a,OPTION_EMISSION_TYPE) && emission_type_d.eq(L"")){
    emission_type_d.readData(sof_a,OPTION_EMISSION_TYPE,parser.getEntry(sof_a, OPTION_EMISSION_TYPE),false, false);  
  }

 if(parser.isPresent(sof_a,OPTION_HMM_PARAMS) && hmm_params_d.eq(L"")){
   hmm_params_d.readData(sof_a,OPTION_HMM_PARAMS,parser.getEntry(sof_a, OPTION_HMM_PARAMS),false, false);  
 }

 if(parser.isPresent(sof_a,OPTION_KZ) && Kz_d.eq(0)){
  Kz_d.readData(sof_a,OPTION_KZ,parser.getEntry(sof_a, OPTION_KZ),false, false);  
 }

 if(parser.isPresent(sof_a,OPTION_STRUCTURE_TYPE) && structure_type_d.eq(L"")){
   structure_type_d.readData(sof_a,OPTION_STRUCTURE_TYPE,parser.getEntry(sof_a, OPTION_STRUCTURE_TYPE),false, false);  
 }

 if(parser.isPresent(sof_a,OPTION_EMISSION_PARAMS) && emission_params_d.eq(L"")){
   emission_params_d.readData(sof_a,OPTION_EMISSION_PARAMS,parser.getEntry(sof_a, OPTION_EMISSION_PARAMS),false, false);  
 }

 if(parser.isPresent(sof_a,OPTION_SEEDS) && seeds_d.eq(L"")){
   seeds_d.readData(sof_a,OPTION_SEEDS,parser.getEntry(sof_a, OPTION_SEEDS),false, false);  
 }

 if(parser.isPresent(sof_a,OPTION_ITR) && itr_d.eq(L"")){
   itr_d.readData(sof_a,OPTION_ITR,parser.getEntry(sof_a, OPTION_ITR),false, false);  
 }

 if(parser.isPresent(sof_a,OPTION_INIT_ITR) && init_itr_d.eq(-1)){
   init_itr_d.readData(sof_a,OPTION_INIT_ITR,parser.getEntry(sof_a, OPTION_INIT_ITR),false, false);  
 }

 if(parser.isPresent(sof_a,OPTION_BURNIN) && burnin_d.eq(-1)){
   burnin_d.readData(sof_a,OPTION_BURNIN,parser.getEntry(sof_a, OPTION_BURNIN),false, false);  
 }


 if(parser.isPresent(sof_a,OPTION_RAW_MODEL) && raw_model_d.eq(L"")){
   raw_model_d.readData(sof_a,OPTION_RAW_MODEL,parser.getEntry(sof_a, OPTION_RAW_MODEL),false, false);  
 }

 if(parser.isPresent(sof_a,OPTION_FINAL_MODEL) && final_model_d.eq(L"")){
   final_model_d.readData(sof_a,OPTION_FINAL_MODEL,parser.getEntry(sof_a, OPTION_FINAL_MODEL),false, false);  
 }

 if(parser.isPresent(sof_a,OPTION_OUTPUT_MODE) && output_mode_d.eq(L"")){
   output_mode_d.readData(sof_a,OPTION_OUTPUT_MODE,parser.getEntry(sof_a, OPTION_OUTPUT_MODE),false, false);  
 }


 if(parser.isPresent(sof_a,OPTION_DEBUG_LEVEL) && debug_level_d.eq(-1)){
   debug_level_d.readData(sof_a,OPTION_DEBUG_LEVEL,parser.getEntry(sof_a, OPTION_DEBUG_LEVEL),false, false);  
 }

 if(parser.isPresent(sof_a,OPTION_VERBOSITY_LEVEL) && verbosity_d.eq(-1)){
   verbosity_d.readData(sof_a,OPTION_VERBOSITY_LEVEL,parser.getEntry(sof_a, OPTION_VERBOSITY_LEVEL),false, false);  
 }
  
 // exit gracefully
 //
 return true;
  
}
