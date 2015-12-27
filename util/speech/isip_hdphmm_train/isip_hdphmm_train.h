// file: isip_hdphmm_train.h
//
// this is the header file for the isip_recognize utility
//
// make sure the file is included only once
//
#ifndef ISIP_UTIL_HDPHMM_TRAIN
#define ISIP_UTIL_HDPHMM_TRAIN

// isip include files
//
#include <HDPHMM.h>
#include <HDP.h>
#include <DPM.h>
#include <Sdb.h>
#include <CommandLine.h>



static const String PROG_NAME(L"isip_hdphmm_train");
static const String OPTION_PARAMS_FILE(L"params_file");
static const String OPTION_RAW_MODEL(L"raw_model");
static const String OPTION_OUTPUT_MODE(L"output_mode");
static const String OPTION_FINAL_MODEL(L"final_model");
static const String OPTION_TRAIN_FILE(L"train_file");
static const String OPTION_EMISSION_TYPE(L"emission_type");
static const String OPTION_STRUCTURE_TYPE(L"structure_type");
static const String OPTION_HMM_PARAMS(L"hmm_params");
static const String OPTION_KZ(L"kz");
static const String OPTION_EMISSION_PARAMS(L"emission_params");
static const String OPTION_ITR(L"itr");
static const String OPTION_INIT_ITR(L"init_itr");
static const String OPTION_BURNIN(L"burn_in");
static const String OPTION_SEEDS(L"seeds");
static const String OPTION_EXTRACT_MODEL_MODE(L"extract");
static const String OPTION_LOG_LIKELIHOOD(L"log_likelihood");


static const String OPTION_DEBUG_LEVEL(L"debug_level");
static const String OPTION_VERBOSITY_LEVEL(L"verbose");
static const String OPTION_LOG_FILE(L"log_file");


static const String OPTION_LOAD_MODEL(L"load_model");

static const String OPTION_UPDATE_EMISSIONS(L"update_only_emissions");

static const String OPTION_ALIGNMENT(L"alignment");

static const String  OPTION_ALIGNMENT_ALGORITHM(L"alignment_algorithm");

static const String OPTION_ALIGNMENT_MODE(L"alignment_mode");

static const String OPTION_ALIGNMENT_TIME(L"alignment_time");

static const String OPTION_ALIGNMENT_DIR(L"alignment_dir");


static const String OPTION_REDUCE_FINAL(L"reduce_final");

static const String EMPTY(String::NULL_STRING);
static const String LOG_FILE_DEFAULT(L"-");
static const String OUTPUT_MODE_DEFAULT(L"BINARY");
static const String EMISSION_TYPE_DEFAULT(L"DPM");
static const String STRUCTURE_TYPE_DEFAULT(L"ERGODIC");
static const String SEEDS_DEFAULT(L"113,101,1001,17,23,10001");

static const String ALIGNMENT_ALGORITHM_DEFAULT(L"viterbi");
static const String ALIGNMENT_MODE_DEFAULT(L"state");
static const String ALIGNMENT_TIME_DEFAULT(L"HTK");



static const Integral::DEBUG DEBUG_LEVEL_DEFAULT=Integral::NONE;
static const Integral::DEBUG VERBOSITY_LEVEL_DEFAULT=Integral::NONE;


extern DebugLevel verbosity_d;
extern DebugLevel debug_level_d;
extern Filename log_file_d;
extern Filename raw_model_d;
extern Filename final_model_d;
extern String output_mode_d;
extern Filename train_file_d;
extern String emission_type_d;
extern String structure_type_d;
extern String hmm_params_d;
extern Long Kz_d;
extern String emission_params_d;
extern String itr_d;
extern Long init_itr_d;
extern Long burnin_d;
extern String seeds_d;
extern Long extract_model_mode_d;
extern String log_likeliood_d;
extern String alignment_mode_d;
extern String alignment_algorithm_d;
extern String alignment_dir_d;
extern String alignment_time_d;




// functions to read parameters file
//
bool8 readData(Sof& sof, const String& pname = L"",
		   int32 size = SofParser::FULL_OBJECT,
		   bool8 param = true,
		   bool8 nested = false);
bool8  read(Sof& sof_a, int32 tag_a, const String& name_a);

// end of file
//
#endif
