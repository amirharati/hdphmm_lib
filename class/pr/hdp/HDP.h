// file: HDP.h
// version: HDP.h 2013-07-13 by Amir Harati
// 
// Amir Harati
//

// This code  implements an HDP calss that can be used independetly
// or  as a part of HDPHMM<HDP>  (AKA  DHDPHMM).
// In both case it use block-sampler inference algorithm similar to
// block sampler proposed by Fox(A sticky HDP-HMM with application to speaker diarization,2011)
//


// when called by hdp_hmm class we use master object that own some slaves (for each state one slave). Most function can only be called by master and slaves will automatically updated by master.
//


// make sure definitions are only made once
//
#ifndef ISIP_HDP
#define ISIP_HDP

#ifndef  OMP_H
#include <omp.h>
#endif

#ifndef ISIP_DOUBLE
#include <Double.h>
#endif

#ifndef ISIP_LONG
#include <Long.h>
#endif

#ifndef ISIP_VECTOR_BYTE
#include <VectorByte.h>
#endif

#ifndef ISIP_MATRIX_FLOAT
#include <MatrixDouble.h>
#endif

#ifndef ISIP_VECTOR_FLOAT
#include <VectorDouble.h>
#endif

#ifndef ISIP_MATRIX_DOUBLE
#include <MatrixDouble.h>
#endif

#ifndef ISIP_MATRIX_LONG
#include <MatrixLong.h>
#endif


#ifndef ISIP_RANDOM
#include <Random.h>
#endif

#ifndef ISIP_DIRICHLET
#include <Dirichlet.h>
#endif

#ifndef ISIP_WISHART
#include <Wishart.h>
#endif

#ifndef ISIP_Vector
#include <Vector.h>
#endif

#ifndef ISIP_DATABASE
#include <Database.h>
#endif

#include <VectorLlong.h>

#include <iostream>
#include <fstream>
#include <time.h>


// HDP: an intermediate class providing base code
//         for defining and training Dirichlet Process Mixtures. 
//                    
//
class HDP{
 private:
  //---------------------------------------------------------------------------
  //
  // container classes
  //
  //---------------------------------------------------------------------------
  
  // hyper paramters :Sigma
  //
  class hyperparams{
  public:

    // Sigma
    //
    Double sigma;

    // Landa
    //
    Double landa;
  };

  // sufficient stats 
  // this class used for saving statistics about each distribution.
  // names of each variable is the same as Matlab (Fox) code.
  //
  class sufficientstats{
  public:

    // sufficient stats for number of data point in each component of the mixture.
    //
    VectorDouble cards;

    // sufficient stats for covariances
    //
    Vector<MatrixDouble> YY;

    // sufficient stats for means
    //
    Vector<VectorDouble> sumY;
  };

  // theta
  // parameters of each distribution
  //
  class theta{
  public:

    // inverse of Sigma (covariance)
    //
    Vector<MatrixDouble> invSigma;

    // mean
    //
    Vector<VectorDouble> mu;

    // cholinvSigma
    //
    Vector<MatrixDouble> cholinvSigma;

    // dcholinvSigma
    //
    Vector<VectorDouble> dcholinvSigma;


    // inverse of Sigma (covariance)
    //
    Vector<MatrixDouble> invSigma_acc;

    // mean
    //
    Vector<VectorDouble> mu_acc;
  };

  // dist_struct
  // contains paramteres of the mixture.
  //
  class dist_struct{
  public:

    // weights of components
    //
    VectorDouble pi_s;

    VectorDouble pi_s_acc;

    // beta vec
    //
    VectorDouble beta_vec;
    VectorDouble beta_vec_acc;

  };

  // counts
  // contains number of datapoints in each components
  //
  class counts{
  public:
    VectorLong Ns;

    MatrixLong M;

  };

  // params
  // parameters related to priors
  //
  class params{
  public:

    // nu determines the degree of freedom for the sigma
    //
    Double nu;
 
    MatrixDouble nu_delta;

    // parameters for Normal-Inverse-Wishart (NIW) priors
    // 

    // kappa :acts as a pseudo count
    //
    Double K;

    // prior on mean : usually ensable mean
    //
    VectorDouble M;

    // cholesky of sigma (for IW-N priors)
    //
    MatrixDouble cholSigma;

    // Lambda
    //
    MatrixDouble Lambda;

    // theta
    //
    VectorDouble theta;

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


  //define HDP Parameters
  //
 
  //Prior Type
  //
  enum PRIOR_TYPE {NIW = 0, IW_N = 1, DEF_PRIOR = 0};
    
  //----------------------------------------
  //
  // i/o related constants
  //
  //----------------------------------------
  
  static const String DEF_PARAM;
  static  const String PARAM_MODEL;

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
  
  //---------------------------------------------------------------------------
  //
  // protected data
  //
  //---------------------------------------------------------------------------
 protected:
  
  // is this object master? (default false)
  //
  bool8 is_master_d;

  // is this obejct slave (default false)
  //
  bool8 is_slave_d;

  // pointer to the master object
  //
  HDP *master_d;

  // do we have one database for the whole HDP or one for each DPM
  //
  bool8 one_database_d;

  // pointer to slaves
  //
  Vector<HDP> *slaves_d;
 
  // algorithm name
  //
  ALGORITHM algorithm_d;
  
  // implementation name
  //
  IMPLEMENTATION implementation_d;

  // Proir type
  //
  PRIOR_TYPE priorType_d;
     
  // Database 
  // Temporary: should be replaced
  // 
  Database *db_d;

  // maximum number of mixture components
  //
  Long Ks_d;
  Long Kc_d; // limit on each state

  
  // number of groups
  //
  Long Kg_d;

  // iteration so far
  //
  Long iterations_d;

  // burn-in
  // 
  Long burn_in_d;

  // accumlation itr
  //
  Long itr_acc_d;

  // observation likelihood
  //
  VectorDouble observed_log_likelihood_d;

  
  // dimension of data
  //
  long dim_d;

  // hyper_params
  //
  hyperparams hyper_d;

  //sufficient stats
  //
  sufficientstats sstats_d;

  // theta
  //
  theta theta_d;

  // dist_struct
  //
  dist_struct dist_struct_d;
  
  // counts
  //
  counts  counts_d;

  // params
  //
  params params_d;


  // header info
  //
  String header_info_d;


  // hyper params vector : A vector of length 8 that sets the value
  // of different parameters & hyper parameters
  // 0: Ks_d
  // 1: prioir type (NIW=0,IWN=1,IWN-tied=2)
  // 2,3: a_sigma & b_sigma
  // 4,5: a_landa & b_landa
  // 6: kappa
  // 7: nu
  //
  VectorFloat hyper_params_vec_d;

  // HDP_hyper_params  vector: {a_sigma,b_sigma)
  // 
  VectorDouble HDP_hyper_params_d;

  // prior_hyper_params  vector: {kappa, nu}
  //
  VectorDouble prior_hyper_params_d;


  // internal iteraltions
  //
  int32 internal_itr_d;

  // number of iterations
  //
  int32  num_iterations_d;


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
  // class special variables :  
  //       These variables are used to preform different tasks within the class.
  //
  //---------------------------------------------------------------------------

  // Dirichlet distribution
  //
  Dirichlet dir_dist_d;

  // Parameter Vector for Dirichlet distribution
  //
  VectorFloat dir_params_d;

  // inverse Wishart
  //
  Wishart iwishart_dist_d;

  // parameter for inverse Wishart
  //
  MatrixFloat sigma_iwishart_d;

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

  //---------------------------------------------------------------------------
  //
  // public data
  //
  //---------------------------------------------------------------------------
 public:

  // mixture index (each data point belongs to which component)
  //
  Vector<VectorLlong> mixture_index_d;

  bool8 compact_d;
  // log_likelihood (updated after calling compute_likelihood)
  //
  Vector<VectorDouble> log_likelihood_d;

  // marginal log_likelihoods
  //
  VectorDouble marg_like_d;

  // mixture probability
  //
  Vector<VectorDouble> mix_prob_d;
  
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
  

  // method : debug
  //
  bool8 debug(const unichar* msg_a) const;

  // constructor(s)/destructor(s)
  //
  ~HDP(){}
  HDP(){

    // by default the object is not master or slave
    //
    is_master_d = false;
    is_slave_d = false;
    one_database_d = true;
  
  }


  // method: assign
  //
  bool8 assign(const HDP & arg);
  
  // i/o methods
  //
int32 sofSize() const{
  if (compact_d==false){
    return (hyper_params_vec_d.sofSize() + iterations_d.sofSize() + burn_in_d.sofSize() + itr_acc_d.sofSize() + theta_d.mu.sofSize() + theta_d.invSigma.sofSize() + theta_d.mu_acc.sofSize() + theta_d.invSigma_acc.sofSize()  +  dist_struct_d.pi_s.sofSize() + dist_struct_d.beta_vec.sofSize() + dist_struct_d.pi_s_acc.sofSize() + dist_struct_d.beta_vec_acc.sofSize() + counts_d.Ns.sofSize() + counts_d.M.sofSize() + sstats_d.cards.sofSize() + sstats_d.YY.sofSize() + sstats_d.sumY.sofSize() + hyper_d.sigma.sofSize() + hyper_d.landa.sofSize() + mixture_index_d.sofSize());
  }
  else{
    return (hyper_params_vec_d.sofSize() + iterations_d.sofSize() + burn_in_d.sofSize() + itr_acc_d.sofSize() +  dist_struct_d.pi_s.sofSize() + dist_struct_d.beta_vec.sofSize() + dist_struct_d.pi_s_acc.sofSize() + dist_struct_d.beta_vec_acc.sofSize() + counts_d.Ns.sofSize() + counts_d.M.sofSize() + sstats_d.cards.sofSize() + sstats_d.YY.sofSize() + sstats_d.sumY.sofSize() + hyper_d.sigma.sofSize() + hyper_d.landa.sofSize() + mixture_index_d.sofSize());
  }
}

  bool8 read(Sof& sof, int32 tag, const String& name = PARAM_MODEL,bool8 compact=false);
  bool8 write(Sof& sof, int32 tag, const String& name = PARAM_MODEL,bool8 compact=false);
  
  bool8 readData(Sof& sof, const String& pname = DEF_PARAM, 
		 int32 size = SofParser::FULL_OBJECT, 
		 bool8 param = true, 
		 bool8 nested = false,
		 bool8 compact = false); 
  bool8 writeData(Sof& sof, const String& param = DEF_PARAM,bool8 compact=false) const;
    
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

 // other memory management methods
  // 
  bool8 clear(Integral::CMODE ctype_a = Integral::DEF_CMODE);

  //---------------------------------------------------------------------------
  //
  // class-specific public methods
  //  set methods
  //
  //---------------------------------------------------------------------------
  
  // method: setMaster
  //
  bool8 setMaster(Vector<HDP> &slaves){

    is_master_d = true;
    is_slave_d = false;
    slaves_d = &slaves;
    master_d = NULL;

    // make all "slaves" the slave of this object
    //
    for(int32 i = 0; i < slaves_d->length(); i++)
      (*slaves_d)(i).setSlave(*this);

    return true; 
  }

  // method: setSlave
  //
  bool8 setSlave(HDP &master){
    
    is_master_d = false;
    is_slave_d = true;
    master_d = &master;
    slaves_d = NULL;

    return true;
  }


  // method: use_one_database 
  // Are we using one database or
  // each group(slave) has its own database. The first case 
  // is usefull when called from other classes (HDp-HMM)
  //
  bool8 use_one_database(bool8 s1){
    one_database_d = s1;
    if(is_master_d == true){
      for(int32 i = 0; i < (*slaves_d).length();i++)
	(*slaves_d)(i).use_one_database(s1); 
    }
    return  true;
  }

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
  
  // method: getPriorType 
  //

  PRIOR_TYPE getPriorType(){
    return(priorType_d);
  }

  // mehtod: setPriorType
  //
  bool8 setPriorType(PRIOR_TYPE  pt){
    priorType_d = pt;
    if (is_master_d == true){
      for(int32 i = 0 ; i< (*slaves_d).length();i++)
	(*slaves_d)(i).setPriorType(pt);
    }

    return true;
  }

  // method: setVerbosity
  //
  bool8 setVerbosity(Integral::DEBUG verbosity) {
    verbosity_d = verbosity;
    return true;
  }


   // method: getKs
  //
  Long getKs(){
    return Ks_d;
  }

  
  //---------------------------------------------------------------------------
  //
  // class-specific public methods:
  //  computational methods
  //
  //--------------------------------------------------------------------------- 

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
   
    if ( is_master_d == true){
      for(int32 i = 0; i < (*slaves_d).length();i++){
	(*slaves_d)(i).set_db(db_a);
      }
    } 
    // return
    //
    return true;
  }

// method: reset_accumulate the theta and pi_s
  //
  bool8 reset_accumulate(){
  
    VectorDouble zero_vec1(dim_d);
    VectorDouble zero_vec2(Ks_d);
    MatrixDouble zero_matrix;
    zero_matrix.setDimensions(dim_d,dim_d,false);
   
    // set the size and initial values for theta members
    //
  theta_d.invSigma_acc.setLength(Ks_d,false);
  theta_d.invSigma_acc.assign(zero_matrix);
 
  // set  the size of mean matrix
  //
  theta_d.mu_acc.setLength(Ks_d,false);
  theta_d.mu_acc.assign(zero_vec1);

  dist_struct_d.pi_s_acc.assign(zero_vec2);
  dist_struct_d.beta_vec_acc.assign(zero_vec2);

  itr_acc_d = 0;
  
  return true;
    
  }
  

  // method: accumulate theta, pi_s and beta_vec
  //
  bool8 accumulate(){
    
    
    for (int32 i = 0 ;i < Ks_d ; i++){
      theta_d.mu_acc(i).add(theta_d.mu(i));
      theta_d.invSigma_acc(i).add(theta_d.invSigma(i));
    }
    if(is_master_d == false)
      dist_struct_d.pi_s_acc.add(dist_struct_d.pi_s);
    dist_struct_d.beta_vec_acc.add(dist_struct_d.beta_vec);

    itr_acc_d++;

    return true;
    
  }

 
  // run inference algorithm
  // 
  bool8 inference(VectorLong seeds,int32 max_itr,int32 burn_in,bool8 init = true);
 
  
  // load and store methods
  //
  bool8 store(String out_filename,File::TYPE type); 
  bool8 load(VectorLong seeds,String filename_a);

  //---------------------------------------------------------------------------
  //
  // other public methods
  //
  //---------------------------------------------------------------------------
  
 public:
 
  // initilize: intilize various variables for inference algorithm  
  //
  bool8 initilize(VectorLong seeds, VectorDouble other_params);

  // intitilze prior and other params
  //
  bool8 init_params();

  // sample distributions
  //
  bool8 sample_dist();

  // set_hyper_paramters
  //
  bool8 set_hyper_parameters(VectorFloat hyper_parameters);

  // initilize hyper_parameters
  //
  bool8 sample_hyper_init();

  // gibbs sampler for hyper parameters
  //
  double gibbs_conparam(Long itr_num,double a,double b,VectorFloat numdata,VectorFloat num_components,double alpha_in);

  // sample hyper_parameters
  //
  bool8 sample_hyper(long gibbs_itr);

  // compute Cholesky decomposition
  //
  bool8 compute_cholesky();

  // compute log-likelihood
  //
  bool8 compute_loglikelihood(int32 T,bool8 normalize = true);

  // sample data : each data belongs to which  component?
  //
  bool8 sample_data();
  bool8 sample_data(int32 data_records, int32 seq_t);
  bool8 init_sample_data();

  // update suffcient statistics for observations
  //
  bool8 update_sstats();
  bool8 init_update_sstats();
  bool8 update_sstats(int32 data_records, int32 seq_t);

  // sample theta
  //
  bool8 sample_theta();

  // compute marginal likelihoods
  //
  bool8 compute_marginal_ll();

  // normaliaze the likelihhods
  //
  bool8 normalize(int32 t,Double normalize_a);

  // sample tabels
  //
  bool8 sample_tables();

  // randnumtable
  //
  bool8 randnumtable(MatrixDouble alpha);


  // extarct the model from  raw model file. This includes to use accumulated variables to compute the theta and pi_s. The final model is the 
  // minimal model to represnt a DPM.
  // This version is  supposed to call by  other classes (HDP-HMM)
  //
  bool8 extract_model(Sof &outputfile,Vector<VectorLong> states_index,int32 this_state_index,int32 out_index,bool8 reduce_a=true);  

  // stand-alone version
  //
  bool8 extract_model(String input_raw_model_a, String output_model_a,File::TYPE type);

  // This function can read Sof file that contain the final model
  // extarct  using extract_model
  //
  bool8 read_final_model(Sof& sof_a, int32 tag_a, const String& name_a);
  // load the final model
  // 
  bool8 load_final_model(String model_a,Database &db_a);

  // calculate the log-likelihood of the data currently in db_d
  //
  bool8 observation_likelihood();

};


//end of include file
//
#endif
