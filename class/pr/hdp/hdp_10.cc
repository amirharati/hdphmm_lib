// file: hdp_10.cc
// version: $Id: hdp_10.cc  7/16/2013
//

// isip include files
//
#include "HDP.h"
#include <Console.h>

// method: store
//
// arguments: 
//  
// out_filename: file to store the model 
// type : text or binary
//
// return: bool8 value
//
// Store the model in Raw format
//

bool8 HDP::store(String out_filename,File::TYPE type){

  // local variables
  //
  Sof outfile;

  // open the file
  //
  if (!outfile.open(out_filename, File::WRITE_ONLY,type)) {
    Console::put(L"Error in open");
    exit(1);
  }


  header_info_d.write(outfile,0,L"info");

  if(is_master_d != true){
    if(! write(outfile,0))
      return Error::handle(name(), L"write", Error::WRITE,
			   __FILE__, __LINE__, Error::WARNING);
  }

  if(is_master_d == true){

    if(! write(outfile,0,L"master"))
      return Error::handle(name(), L"write", Error::WRITE,
			   __FILE__, __LINE__, Error::WARNING);
    for(int32 i = 0 ; i <(*slaves_d).length();i++){
      if(! (*slaves_d)(i).write(outfile,i,L"slave"))
	return Error::handle(name(), L"write", Error::WRITE,
			     __FILE__, __LINE__, Error::WARNING);
    }
  }
  // return gracefully
  //
  outfile.close();
  return true;
}



// method: load
//
// arguments: 
//  
// filename_a: file to load the model 
// 
//
// return: bool8 value
//
// Store the model in Raw format
//
bool8 HDP::load(VectorLong seeds,String filename_a){


  Sof sof_a;
  
  VectorDouble internal_itr;
  internal_itr.assign(L"50");

  // initilize
  //
  initilize(seeds,internal_itr);
 
  // open the Sof file
  //
  if (sof_a.open(filename_a, File::READ_ONLY) != true) {
    return Error::handle(filename_a, L"open", Error::TEST, __FILE__, __LINE__);
  }

  // read the frist record to determine the dimension
  //
  if(is_master_d != true){
    if(read(sof_a,0) != true)
      return Error::handle(filename_a, L"read", Error::TEST, __FILE__, __LINE__);
   

  }

  if(is_master_d == true){

    if(! read(sof_a,0,L"master"))
      return Error::handle(name(), L"write", Error::WRITE,
			   __FILE__, __LINE__, Error::WARNING);
    // set params from loaded  vec
    //
   
    for(int32 i = 0 ; i <(*slaves_d).length();i++){
      if(! (*slaves_d)(i).read(sof_a,i,L"slave"))
	return Error::handle(name(), L"write", Error::WRITE,
			     __FILE__, __LINE__, Error::WARNING);
    }
  }

  compute_cholesky();

  sample_data();
  sof_a.close();

  return true;  
}


// method: extract_model
//
// arguments: 
//  
// 
// mode_a: 0 use sample valued directly (default) 1 calculate the parameters 
//         using segmented data.
//
// return: bool8 value
//
// Extract a HMM model from raw HDPHMM model file
//
bool8 HDP::extract_model(Sof &outfile,Vector<VectorLong> state_index,int32 this_state_index,int32 out_index,bool8 reduce_a){

  if (is_slave_d == true){

    
    
    // local variable
    //
    VectorLlong unique_comps(Ks_d);
    unique_comps.setRange(0,Ks_d,-1);
    int32 count = -1;
    int32 comps_no= 0;
    int32 is_existed;

    if (reduce_a == true){
      // find all states that actually visted by the data points
      //
      for (int32 i = 0 ; i< state_index.length(); i++){
	for (int32 j = 0 ; j < state_index(i).length(); j++){
	
	  is_existed = 0;
	  
	  // if this data point is in this state
	  //
	  if(state_index(i)(j) == this_state_index){
	    for (int32 k = 0 ; k <= count ; k++){
	      if(mixture_index_d(i)(j) == unique_comps(k)){
		is_existed = 1;
		break;    
	      }	  
	    }	
	  }
	  else 
	    is_existed = 1;
	
	  if(is_existed == 0){
	    count++;
	    comps_no++;
	    unique_comps(count) = mixture_index_d(i)(j);
	  }
	  
	}
      }
    
      unique_comps.setLength(comps_no,true);
      unique_comps.sort(); //??
    
    
      for (int32 i = 0 ; i< state_index.length(); i++){
	for (int32 j = 0 ; j < state_index(i).length(); j++){
	
	  // if this data point is in this state
	  //
	  if(state_index(i)(j) == this_state_index){
	    for (int32 k = 0 ; k <= count ; k++){
	      if(mixture_index_d(i)(j) == unique_comps(k)){
		
		(*master_d).mixture_index_d(i)(j) = k;
		break;    
	      }	  
	    }	
	  }
	}
      }
    }
    else{
      //mixture_index.assign(mixture_index_d);
      for (int32 i=0;i<Ks_d;i++)
	unique_comps(i)=i;
      comps_no=Ks_d;
    }

      
    Vector<MatrixDouble> invSigma_tmp;
    Vector<VectorDouble> mu_tmp;
    invSigma_tmp.assign(theta_d.invSigma_acc);
    mu_tmp.assign(theta_d.mu_acc);
    for (int32 i = 0;i<Ks_d;i++){
      invSigma_tmp(i).div(itr_acc_d);

      
      //
      mu_tmp(i).div(itr_acc_d);
    }
    
    VectorDouble zero_vec(dim_d);
    MatrixDouble zero_matrix;
    zero_matrix.setDimensions(dim_d,dim_d,false);
    
    Vector<MatrixDouble> invSigma;
    Vector<VectorDouble> mu;
    invSigma.setLength(comps_no);
    mu.setLength(comps_no);
    invSigma.assign(zero_matrix);
    mu.assign(zero_vec);
    
    VectorDouble pis;
    pis.setLength(comps_no);
    for (int32 i = 0; i < comps_no ; i++){
      invSigma(i).assign(invSigma_tmp(unique_comps(i)));
      mu(i).assign(mu_tmp(unique_comps(i)));
      pis(i) = dist_struct_d.pi_s_acc(unique_comps(i));
    }
    pis.div(pis.sum());
    
    int32 obj_size;
  
    // write the instance of the object into the Sof file
    //
    if (outfile.isText()) {
    
      // set the size to by dynamic
      //
      obj_size = Sof::ANY_SIZE;
    }
    else {

      // the size index and the size of each element
      //
      obj_size = pis.sofSize() + mu.sofSize() + invSigma.sofSize();
    }
    
    // write the object into the sof file's index
    //
    if (!outfile.put(L"emission_model", out_index, obj_size)) {
      return false;
    }
    if(!pis.writeData(outfile,L"pi_s"))
      return Error::handle(name(), L"writeData", Error::WRITE,
			   __FILE__, __LINE__, Error::WARNING);
    
    if(!mu.writeData(outfile,L"mu"))
      return Error::handle(name(), L"writeData", Error::WRITE,
			   __FILE__, __LINE__, Error::WARNING);
    if(!invSigma.writeData(outfile,L"invSigma"))
      return Error::handle(name(), L"writeData", Error::WRITE,
			   __FILE__, __LINE__, Error::WARNING);
  } 
  if(is_master_d == true){
    int32 obj_size;
    if (outfile.isText()) {
      
      // set the size to by dynamic
      //
      obj_size = Sof::ANY_SIZE;
    }
    else {
	
      // the size index and the size of each element
      //
      obj_size = (*master_d).mixture_index_d.sofSize();
    }
    
    // write the object into the sof file's index
    //
    if (!outfile.put(L"mixture_index", 0, obj_size)) {
      return false;
    }
    if(!mixture_index_d.writeData(outfile,L"mixture_index"))
      return Error::handle(name(), L"writeData", Error::WRITE,
			   __FILE__, __LINE__, Error::WARNING);
    
    
  }
  
  return true;
}

// method: read_final_model
//
// arguments:
//  
// 
//  
//
// return: a bool8 indicating status
//
// read the minmum  model (HMM without  other parameters)
//
bool8 HDP::read_final_model(Sof& sof_a, int32 tag_a, const String& name_a) {

  // get the instance of the object from the Sof file
  //
  if (!sof_a.find(name_a, tag_a)) {
    return false;
  }
  
  
  int32 size_a = SofParser::FULL_OBJECT;

  
  Integral::DEBUG debug_level = Integral::NONE;
  
  SofParser parser;
  
  parser.setDebug(debug_level);
  
  
  // load the parse
  //
  if (!parser.load(sof_a, size_a)) {
    return Error::handle(name(), L"readData", Error::READ,
			 __FILE__, __LINE__, Error::WARNING);
  }	    
  

  // get mu
  //
  if (!theta_d.mu.readData(sof_a, L"mu",
		       parser.getEntry(sof_a, L"mu"),
		       false, false)) {
    return Error::handle(name(), L"readData", Error::READ,
			 __FILE__, __LINE__, Error::WARNING);
  }	    
  
  // get invSigma
  //
  if (!theta_d.invSigma.readData(sof_a, L"invSigma",
			     parser.getEntry(sof_a, L"invSigma"),
 			     false, false)) {
     return Error::handle(name(), L"readData", Error::READ,
 			 __FILE__, __LINE__, Error::WARNING);
   }
    
   // get pi_s 
   //
   if (!dist_struct_d.pi_s.readData(sof_a, L"pi_s",
 			     parser.getEntry(sof_a, L"pi_s"),
 			     false, false)) {
     return Error::handle(name(), L"readData", Error::READ,
 			 __FILE__, __LINE__, Error::WARNING);
   }
  
  
   Ks_d = dist_struct_d.pi_s.length();
 
   theta_d.cholinvSigma.setLength(Ks_d);
   theta_d.dcholinvSigma.setLength(Ks_d);
   compute_cholesky();
 
  // exit gracefully
  //
  return true;
  
}



// method: extract_model
//
// arguments: 
//  
// 
// mode_a: 0 use sample valued directly (default) 1 calculate the parameters 
//         using segmented data.
//
// return: bool8 value
//
// Extract a HMM model from raw HDPHMM model file
//
bool8 HDP::extract_model(String input_raw_model_a, String output_model_a,File::TYPE type){

Sof outfile;
  // open the file
  //
  if (!outfile.open(output_model_a, File::WRITE_ONLY,type)) {
    Console::put(L"Error in open");
    exit(1);
  }

  if(is_master_d == false){
    // local variables
    //
    VectorLong seeds(6);
    
    VectorLlong unique_comps(Ks_d);
    unique_comps.setRange(0,Ks_d,-1);
    int32 count = -1;
    int32 comps_no= 0;
    int32 is_existed;
    
    // load the input  model
    //
    load(seeds,input_raw_model_a);
    
    // find all states that actually visted by the data points
    //
    for (int32 i = 0 ; i< mixture_index_d.length(); i++){
      for (int32 j = 0 ; j < mixture_index_d(i).length(); j++){
	
	is_existed = 0;
	
	// if this data point is in this state
	//
	
	for (int32 k = 0 ; k <= count ; k++){
	  if(mixture_index_d(i)(j) == unique_comps(k)){
	    is_existed = 1;
	    break;    
	  }	  	  
	}
	if(is_existed == 0){
	  count++;
	  comps_no++;
	  unique_comps(count) = mixture_index_d(i)(j);
	}
	
      }
    }
    
    unique_comps.setLength(comps_no,true);
    unique_comps.sort(); //??
    
    
    Vector<VectorLlong> mixture_index;
    mixture_index.setLength(mixture_index_d.length());
    for (int32 i = 0 ; i< mixture_index.length(); i++){
      mixture_index(i).setLength(mixture_index_d(i).length());
    }
    
    
    for (int32 i = 0 ; i< mixture_index_d.length(); i++){
      for (int32 j = 0 ; j < mixture_index_d(i).length(); j++){
	
	// if this data point is in this state
	//
	for (int32 k = 0 ; k <= count ; k++){
	  if(mixture_index_d(i)(j) == unique_comps(k)){
	    mixture_index(i)(j) = k;
	    break;    
	  }	  
	}	
      }
    }
    
    
    Vector<MatrixDouble> invSigma_tmp;
    Vector<VectorDouble> mu_tmp;
    invSigma_tmp.assign(theta_d.invSigma_acc);
    mu_tmp.assign(theta_d.mu_acc);
    for (int32 i = 0;i<Ks_d;i++){
      invSigma_tmp(i).div(itr_acc_d);
      mu_tmp(i).div(itr_acc_d);
    }
    
    VectorDouble zero_vec(dim_d);
    MatrixDouble zero_matrix;
    zero_matrix.setDimensions(dim_d,dim_d,false);
    
    Vector<MatrixDouble> invSigma;
    Vector<VectorDouble> mu;
    invSigma.setLength(comps_no);
    mu.setLength(comps_no);
    invSigma.assign(zero_matrix);
    mu.assign(zero_vec);
    
    VectorDouble pis;
    
    pis.setLength(comps_no);
    for (int32 i = 0; i < comps_no ; i++){
      invSigma(i).assign(invSigma_tmp(unique_comps(i)));
      mu(i).assign(mu_tmp(unique_comps(i)));
      pis(i) = dist_struct_d.pi_s_acc(unique_comps(i));
    }
    pis.div(pis.sum());
    
    
    
    
    int32 obj_size;
    // write the instance of the object into the Sof file
    //
    if (outfile.isText()) {
      
      // set the size to by dynamic
      //
      obj_size = Sof::ANY_SIZE;
    }
    else {
      
      // the size index and the size of each element
      //
      obj_size = pis.sofSize() + mu.sofSize() + invSigma.sofSize();
    }
    
    // write the object into the sof file's index
    //
    if (!outfile.put(L"MODEL", 0, obj_size)) {
      return false;
    }
    if(!pis.writeData(outfile,L"pi_s"))
      return Error::handle(name(), L"writeData", Error::WRITE,
			   __FILE__, __LINE__, Error::WARNING);
    
    if(!mu.writeData(outfile,L"mu"))
      return Error::handle(name(), L"writeData", Error::WRITE,
			   __FILE__, __LINE__, Error::WARNING);
    if(!invSigma.writeData(outfile,L"invSigma"))
      return Error::handle(name(), L"writeData", Error::WRITE,
			   __FILE__, __LINE__, Error::WARNING);
    
    
    
    if (outfile.isText()) {
      
      // set the size to by dynamic
      //
      obj_size = Sof::ANY_SIZE;
    }
    else {
      
      // the size index and the size of each element
      //
      obj_size = mixture_index.sofSize();
    }
    
    // write the object into the sof file's index
    //
    if (!outfile.put(L"mixture_index", 0, obj_size)) {
      return false;
    }
    if(!mixture_index.writeData(outfile,L"mixture_index"))
      return Error::handle(name(), L"writeData", Error::WRITE,
			   __FILE__, __LINE__, Error::WARNING);
    
    
    
    outfile.close();
    
  }

  else if (is_master_d == true){

    //  error message
    //

  }
    // return gracefully
    //
    return true;
}



// method: load_final_model
//
// arguments:
//  
// 
//  
//
// return: a bool8 indicating status
//
// load the minmum  model (DPM without  other parameters)
//
bool8 HDP::load_final_model(String model_a,Database &db_a) {


  Sof sof_a;
  VectorLong seeds(6);
  VectorDouble tmp1(6),tmp2(8);

  db_d = &db_a;

  // open the Sof file
  //
  if (sof_a.open(model_a, File::READ_ONLY) != true) {
    return Error::handle(model_a, L"open", Error::TEST, __FILE__, __LINE__);
  }

  // read the model
  //
  if(read_final_model(sof_a,0,L"MODEL") != true)
      return Error::handle(model_a, L"read", Error::TEST, __FILE__, __LINE__);
  

  sof_a.close();


  // exist garcefully
  //
  return true;

}
