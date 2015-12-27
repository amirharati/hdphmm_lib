// file: $isip/class/pr/HDPHMM/HDPHMM.h
// version: $Id: HDPHMM.h 2013-6-30 $
// 
// Amir Harati
//
// HDPHMM class can use both DPM and HDP emissions
// The first case is HDPHMM<DPM> and is discussed in  (A sticky HDP-HMM with application to speaker diarization, Fox et al. ,2011) ,
// later case is HDPHMM<HDP> and is also known as DHDPHMM and is discusses
// in my dissertation (NONPARAMETRIC BAYESIAN APPROACHES FOR ACOUSTIC MODELING, Harati, 2015) and also some papers that I published.
// The inference algorithm is adpoted from Emily Fox code for HDPHMM in Matlab but we have add some ohter features like supporting DHDPHMM,  non-Ergodic structures, non-emitting states, using openMP, computing Viterbi or FOrward-BAckward Path among other things.
//

// make sure definitions are only made once
//
#ifndef ISIP_HDPHMM
#define ISIP_HDPHMM

#ifndef OMP_H
#include <omp.h>
#endif

#ifndef ISIP_DOUBLE
#include <Double.h>
#endif


#ifndef ISIP_ULONG
#include <Ulong.h>
#endif

#ifndef ISIP_VECTOR_BYTE
#include <VectorByte.h>
#endif

#ifndef ISIP_MATRIX_FLOAT
#include <MatrixFloat.h>
#endif

#ifndef ISIP_VECTOR_DOUBLE
#include <VectorDouble.h>
#endif

#ifndef ISIP_VECTOR_FLOAT
#include <VectorFloat.h>
#endif

#ifndef ISIP_MATRIX_DOUBLE
#include <MatrixDouble.h>
#endif

#ifndef ISIP_MATRIX_LONG
#include <MatrixLong.h>
#endif


#ifndef ISIP_DPM
#include <DPM.h>
#endif

#ifndef ISIP_DATABASE
#include "Database.h"
#endif

#ifndef ISIP_RANDOM
#include <Random.h>
#endif

#ifndef ISIP_DIRICHLET
#include <Dirichlet.h>
#endif

#ifndef ISIP_VECTOR
#include <Vector.h>
#endif

// HDPHMM: an intermediate class providing base code
//         for defining and training Hierarchical Dirichlet Process-HMMs. 
//                    
//
template <class emission_type> class HDPHMM {

 private:
  //---------------------------------------------------------------------------
  //
  // container classes
  //
  //---------------------------------------------------------------------------
  
  // hyper paramters 
  //
  class hyperparams{
  public:

    // alpha_p_kappa
    //
    Double alpha_p_kappa;

    // gamma
    //
    Double gamma;

    // rho
    //
    Double rho;

  };

  // counts
  //
  class counts{
  public:
    MatrixLong N;
    MatrixLong M;
    MatrixDouble barM;
    VectorFloat sumW;
  };

  // dist_struct
  //
  class dist_struct{
  public:

    // transition distributions
    //
    MatrixDouble pi_z;
    
    // beta vector : expected  value of transitions to different states
    //
    VectorDouble beta_vec;
    
    // intial probablity of being in a state
    // 
    VectorDouble  pi_init;

    // accumulator variables
    //
    MatrixDouble pi_z_acc;
    VectorDouble  beta_vec_acc;
    VectorDouble pi_init_acc;

  };



  
  //--------------------------------------------------------------------------
  //
  // public constants
  //
  //--------------------------------------------------------------------------
public:
  
  // define the class name
  //
  static const String CLASS_NAME;

  //----------------------------------------
  //
  // i/o related constants
  //
  //----------------------------------------  
  
 
  //----------------------------------------
  //
  // other important constants
  //
  //----------------------------------------


  // define the algorithm choices
  //
  enum ALGORITHM { DECODE = 0, INFERENCE = 1,
		   DEF_ALGORITHM = DECODE };
  
  // define the implementation choices
  //
  enum IMPLEMENTATION { BLOCK_SAMPLER = 0, DEF_IMPLEMENTATION = BLOCK_SAMPLER};



  // define output types
  //
  enum TYPE { TEXT = 0, BINARY, DEF_TYPE = BINARY };  

  // define HDPHMM Parameters
  //
  
  //Structure type
  //
  enum STRUCTURE_TYPE {ERGODIC = 0, LEFT_TO_RIGHT, STRICTLY_LEFT_TO_RIGHT,LEFT_TO_RIGHT_WITH_LOOP,LEFT_TO_RIGHT_WITH_LOOP_TO_FIRST, DEF_STRUCTURE = ERGODIC};

  
  //----------------------------------------
  //
  // i/o related constants
  //
  //----------------------------------------

  static const String DEF_PARAM;
  static const String PARAM_MODEL;
  static const String PARAM_FILE;

  //----------------------------------------
  //
  // default values and arguments
  //
  //----------------------------------------
  
  // default values
  //
  static const bool8 DEF_VERIFY = false;
 
  
  //----------------------------------------
  //
  // error codes
  //
  //----------------------------------------  

  static const int32 ERR = (int32)100000;
  static const int32 ERR_ADAPT_NO_GAUSSIAN = (int32)100050;
  
  //---------------------------------------------------------------------------
  //
  // protected data
  //
  //---------------------------------------------------------------------------
 protected:
 
  // algorithm name
  //
  ALGORITHM algorithm_d;
  
  // implementation name
  //
  IMPLEMENTATION implementation_d;
  
  // sturcture type
  //
  STRUCTURE_TYPE structure_type_d;

  bool8 sample_emissions_only_d;
  // maximum number of states
  //
  Long Kz_d;

  // emission type
  //
  String emission_type_d;

  // iteration so far
  //
  Long iterations_d;

  // burn-in : when start to accumulate
  // 
  Long burn_in_d;

  // accumlation itr
  //
  Long itr_acc_d;
  
  // emission parameters
  // This vecotr contains all paramters for the emission distribution
  // it can be different for different type of emissions
  //
  VectorFloat emission_params_d;
 
  // dimension of data
  //
  long dim_d;

  // hyper_params
  //
  hyperparams hyper_d;

  //state counts
  //
  counts counts_d;
  
  //dist_struct
  //
  dist_struct dist_struct_d;
  

  // header info
  //
  String  header_info_d;


  // hyper_params_vec
  //
  VectorFloat hyper_params_vec_d;

  // HMM_hyper_params_d  vector: {a_alpha,b_alpha,a_gamma,b_gamma,c,d}
  // alpha : 
  // gamma : 
  // c,d : 
  //
  VectorFloat HMM_hyper_params_d;

  
  // master object to control/link emissions_d objects
  //
  emission_type master_emission_d;

  // number of iterations
  //
  int32  num_iterations_d;

  // Dirichlet distribution
  //
  Dirichlet dir_dist_d;

  // Parameter Vector for Dirichlet distribution
  //
  VectorFloat dir_params_d;

  // normal distribution
  //
  VectorDouble norm_dist_d;
  Random norm_gen_d;

  // parameter for normal dist.
  //
  VectorDouble norm_param_d;

  // multinomial using Dirichlet
  //
  Dirichlet multi_dist_d;

  // uniform random generator
  //
  VectorDouble uniform_rand_d;
  Random uniform_gen_d;

  // gamma random generator
  //
  Random gamma_rand_d; 

  // seq. length
  //
  VectorLong T_d;
  
  // state index 
  //
  Vector<VectorLong> state_index_d;

  // Database
  //
  Database *db_d;


  // debug level
  //
  static Integral::DEBUG debug_level_d;
  
  // verbosity
  //
  static Integral::DEBUG verbosity_d;

  // static memory manager
  //
  static MemoryManager mgr_d;

 //---------------------------------------------------------------------------
  //
  // public data
  //
  //---------------------------------------------------------------------------

 public:

  // Vector of emission distributions
  // DPM --->  emissionBase
  //
  Vector<emission_type> emissions_d;

  
  // partial likelihood * backward messages
  //
  Vector<VectorDouble> partial_marg_d;

  // log_normalizer
  //
  VectorDouble log_normalize_d;

  //  observation log_likelihood
  //
  VectorDouble observed_log_likelihood_d;

  // viterbi (or sampled) path for observations
  //
  Vector<VectorLong> observed_path_d; 

  Vector<VectorLong> observed_mix_d;

  // posteroir probablity (for states)
  //
  Vector<MatrixDouble> post_prob_d;
  
  //---------------------------------------------------------------------------
  //
  // required public methods
  //
  //---------------------------------------------------------------------------

public:
  
  // method: name
  //
  static const String& name() {
    return CLASS_NAME;
  }

  // other static methods
  //   
  static bool8 diagnose(Integral::DEBUG debug_level);

  // method: setDebug
  //
  bool8 setDebug(Integral::DEBUG debug_level) {
    debug_level_d = debug_level;
        
    return true;
  }

  // method: setVerbosity
  //
  bool8 setVerbosity(Integral::DEBUG verbosity) {
    verbosity_d = verbosity;
    return true;
  }


  
  // constructor(s)/destructor(s)
  //
  ~HDPHMM(){}
  HDPHMM(){
 }
  HDPHMM(const HDPHMM & arg){}

  // method: assign
  //
  bool8 assign(const HDPHMM & arg) {
    return Error::handle(name(), L"assign", Error::ARG, __FILE__, __LINE__);
  }
  

  // i/o methods
  //
  int32 sofSize() const{ 
    return(hyper_params_vec_d.sofSize() + iterations_d.sofSize() + burn_in_d.sofSize()+ itr_acc_d.sofSize() + dist_struct_d.pi_z.sofSize() + dist_struct_d.pi_init.sofSize()+ dist_struct_d.beta_vec.sofSize()+ dist_struct_d.pi_z_acc.sofSize() + dist_struct_d.pi_init_acc.sofSize()+ dist_struct_d.beta_vec_acc.sofSize() + counts_d.N.sofSize() + counts_d.M.sofSize() + counts_d.barM.sofSize() + counts_d.sumW.sofSize() + hyper_d.alpha_p_kappa.sofSize() + hyper_d.gamma.sofSize() + hyper_d.rho.sofSize() + state_index_d.sofSize()+emission_type_d.sofSize());
}
  bool8 read(Sof& sof, int32 tag, const String& name = PARAM_MODEL);
  bool8 write(Sof& sof, int32 tag, const String& name = PARAM_MODEL) const;
  
  bool8 readData(Sof& sof, const String& pname = DEF_PARAM,
		 int32 size = SofParser::FULL_OBJECT,
		 bool8 param = true,
		 bool8 nested = false);
  bool8 writeData(Sof& sof, const String& param = DEF_PARAM) const;
  
  // method: new
  //
  static void* operator new(size_t size) {
    return mgr_d.get();
  }

  // method: new[]
  //
  static void* operator new[](size_t size) {
    return mgr_d.getBlock(size);
  }

  // method: delete
  //
  static void operator delete(void* ptr) {
    mgr_d.release(ptr);
  }

  // method: delete[]
  //
  static void operator delete[](void* ptr) {
    mgr_d.releaseBlock(ptr);
  }

  // method: setGrowSize
  //
  static bool8 setGrowSize(int32 grow_size) {
    return mgr_d.setGrow(grow_size);
  }

  //---------------------------------------------------------------------------
  //
  // class-specific public methods
  //  set methods
  //
  //---------------------------------------------------------------------------
  
  // method: getAlgorithm
  //
  ALGORITHM getAlgorithm() {
    return algorithm_d;
  }

  // method: setAlgorithm
  //
  bool8 setAlgorithm(ALGORITHM arg) {
    return (algorithm_d = arg);
  }

  // method: getImplementation
  //
  IMPLEMENTATION getImplementation() {
    return implementation_d;
  }

  // method: setImplementation
  //
  bool8 setImplementation(IMPLEMENTATION arg) {
    return (implementation_d = arg);
  }

  // method: setStructureType
  //
  bool8 set_structureType(STRUCTURE_TYPE st_a){

    structure_type_d = st_a;

    return true;
  }
	   
  // method: set_Kz
  //
  bool8 set_Kz(int32 kz){
    Kz_d = kz;

    // return
    //
    return true;

  }

  // method : get_iterations
  // return the number of  iterations so far
  int32 get_iterations(){

    return iterations_d;
  }

  // method : get_burnin
  // return the number of  iterations so far
  int32 get_burnin(){

    return burn_in_d;
  }
  

  // method: set_emission_hyper_params
  //
  bool8 set_emission_params(VectorDouble emission_params){
    
    emission_params_d.assign(emission_params);
    
    // exit gracefully
    return true;
  }

  // method: set_HMM_params
  //
  bool8 set_HMM_params(VectorDouble hmm_params){

    if (hmm_params.length() != 6)
      return Error::handle(name(), L"set_HMM_params", Error::ARG, __FILE__, __LINE__);
    else
      HMM_hyper_params_d.assign(hmm_params);

    // exit gracefully
    return true;
  }

  // method: set_db
  //
  bool8 set_db(String db_file){

    // initilize the db
    //
    db_d->init(db_file);

    // return
    //
    return true;
  }

  // method: set_db
  //
  bool8 set_db(Database &db_a){

    db_d = &db_a;
    
    // return
    //
    return true;
  }

  // method: rest_accumulate  pi_z,beta_vec, pi_init and call accumulator
  // for emission distribution
  //
  bool8 reset_accumulate(){

    VectorDouble zero_vec(Kz_d);
    MatrixDouble zero_mat(Kz_d,Kz_d);
    
    dist_struct_d.beta_vec_acc.assign(zero_vec);
    dist_struct_d.pi_z_acc.assign(zero_mat);
    dist_struct_d.pi_init_acc.assign(zero_vec);
    
    
    itr_acc_d = 0;
    for(int32 i = 0; i < emissions_d.length(); i++){
      emissions_d(i).reset_accumulate();
    }
    return  true;
  }
  
  // method: accumulate  pi_z,beta_vec, pi_init and call accumulator
  // for emission distribution
  //
  bool8 accumulate(){

    dist_struct_d.pi_z_acc.add(dist_struct_d.pi_z);
    dist_struct_d.beta_vec_acc.add(dist_struct_d.beta_vec);
    dist_struct_d.pi_init_acc.add(dist_struct_d.pi_init);
    itr_acc_d++;
    for(int32 i = 0; i < emissions_d.length(); i++){
      emissions_d(i).accumulate();
    }
    return true;
  }

  //---------------------------------------------------------------------------
  //
  // class-specific public methods:
  //  computational methods
  //
  //---------------------------------------------------------------------------

  // run inference algorithm
  //  
  bool8 inference(VectorLong seeds,int32 max_itr,int32 init_itr,int32 burn_in,bool8 init = true,bool8 sample_emission_only = false);
   
  
  // load and store methods
  //
  bool8 load(VectorLong seeds,String filename_a);

  bool8 store(String out_filename,File::TYPE type);

  // initilize: intilize various variables for inference algorithm  
  //
 
  bool8 initilize(VectorLong seeds, VectorDouble other_params);

  // just initilize emissions
  //
  bool8 init_emissions(VectorLong seeds, VectorDouble other_params);
    
  // initilize a left_to_right structure
  //  
  bool8 initilize_lr(VectorLong seeds, VectorDouble other_params,int32 init_itr);

  // sample distributions
  //
  bool8 sample_dist();

  bool8 sample_data2();
  // initilize hyper_parameters
  //
  bool8 sample_hyper_init();

  // sample hyper_parameters
  //
  bool8 sample_hyper(int32 gibbs_itr);

  // sample states (z) and mixture components (s)
  //
  bool8 sample_data();
  

  // update suffcient statistics for observations
  //
  bool8 update_sstats();

  // sample theta
  //
  bool8 sample_theta();

  // sample tables
  //
  bool8 sample_tables();

  // compute the backward messages
  //
  bool8 backward_message_compute(int32 T);

  // sample_barM
  // 
  bool8 sample_barM();

  // Gibbs sampler for concentration parameter
  //
  double gibbs_conparam(Long itr_num,double a,double b,VectorFloat numdata,VectorFloat num_components,double alpha_in);


  bool8 randnumtable(MatrixDouble alpha);

  int32 randbinom(double p,int n);


  
  // extarct the model from  raw model file. This includes to use accumulated variables to compute pi_z, pi_init and emission params. It also do the necessary computation for adding non-emitting states and relabel the state seq. Save the result in final model.
  //
  bool8 extract_model(String input_raw_model_a, String output_model_a, File::TYPE type,bool8 reduce_a=true);

  // calculate the log-likelihood of the data currently in db_d
  //
  bool8 observation_likelihood();

  // load the  final model
  //
  bool8 load_final_model(String model_a,Database &db_a);

  // read the final model
  //
  bool8 read_final_model(Sof& sof_a, int32 tag_a, const String& name_a = PARAM_MODEL);

  // compute forward messages ( backward-forward algo.)
  // it is used in calcualting the likelihoods for an observation
  //
  bool8 forward_message_compute(int32 T,VectorDouble& neglog_c);

  bool8 find_path(const String& algorithm_a=L"viterbi");
};

//end of include file
//
#include "hdphmm_09.h"

#include "hdphmm_08.h"
#include "hdphmm_03.h"
#include "hdphmm_10.h"
#include "hdphmm_00.h"

#endif
