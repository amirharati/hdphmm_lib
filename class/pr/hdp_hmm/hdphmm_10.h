// file: hdphmm_10.cc
// version: $Id: dpm_09.cc  7/16/2013
//

// isip include files
//
#include "HDPHMM.h"
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
template <class emission_type>
bool8 HDPHMM<emission_type>::store(String out_filename,File::TYPE type){

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
  
  if(! write(outfile,0))
    return Error::handle(name(), L"write", Error::WRITE,
			 __FILE__, __LINE__, Error::WARNING);


  // for(int i=0;i<(emissions_d).length();i++)
  //  (emissions_d)(i).write(outfile,i,L"emission_model");
  master_emission_d.write(outfile,0,L"emission_model");
  
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
template <class emission_type>
bool8 HDPHMM<emission_type>::load(VectorLong seeds,String filename_a){


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
  if(read(sof_a,0) != true)
      return Error::handle(filename_a, L"read", Error::TEST, __FILE__, __LINE__);
  
  master_emission_d.read(sof_a,0,L"emission_model");
  for(int i=0;i<(emissions_d).length();i++){
    //(emissions_d)(i).read(sof_a,i,L"emission_model");
     (emissions_d)(i).compute_cholesky();
  }

  // now  resample  the state_index_d and mixture_index_d
  //
  // This allows us to replace the data after loading
  //
  //state_index_d.setLength(db_d->get_records_no(),false);
  //for (int32 data_records = 0; data_records < db_d->get_records_no(); data_records++){
  //  state_index_d(data_records).setLength(T_d(data_records),false);
    
  // }
    
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
template <class emission_type>
bool8 HDPHMM<emission_type>::extract_model(String input_raw_model_a, String output_model_a,File::TYPE type, bool8 reduce_a){

  
  Sof outfile;

  VectorLong seeds(6);
  load(seeds,input_raw_model_a);


  // final_model always in TEXT
  //
  type = File::TEXT;
  
  // open the file
  //
  if (!outfile.open(output_model_a, File::WRITE_ONLY,type)) {
    Console::put(L"Error in open");
    exit(1);
  }

  // local variables
  //
 
  VectorLong unique_states(Kz_d);
  unique_states.setRange(0,Kz_d,-1);
  int32 count = -1;
  int32 state_no= 0;
  int32 is_existed;
  MatrixDouble pi_z,pi_z_tmp,pi_z_ne;
  VectorDouble pi_init,pi_init_tmp,pi_init_ne;


  pi_z_tmp.assign(dist_struct_d.pi_z_acc);
  pi_init_tmp.assign(dist_struct_d.pi_init_acc);
  pi_z_tmp.div(itr_acc_d);
  pi_init_tmp.div(itr_acc_d);
  
  Vector<VectorLong> state_index;
  state_index.setLength(state_index_d.length());
  for (int32 i = 0 ; i< state_index.length(); i++){
    state_index(i).setLength(state_index_d(i).length());
  }

  if (reduce_a == true){
    // find all states that actually visted by the data points
    //
    for (int32 i = 0 ; i< state_index_d.length(); i++){
      for (int32 j = 0 ; j < state_index_d(i).length(); j++){
	is_existed = 0;
	for (int32 k = 0 ; k <= count; k++){
	  if(state_index_d(i)(j) == unique_states(k)){
	    is_existed = 1;
	    break;
	  }
	}
	if(is_existed == 0){
	  count++;
	  state_no++;
	  unique_states(count) = state_index_d(i)(j);
	}

	
      }
    }
    unique_states.setLength(state_no,true);
    unique_states.sort(); //??
 
    for (int32 i = 0 ; i< state_index_d.length(); i++){
      for (int32 j = 0 ; j < state_index_d(i).length(); j++){

	for (int32 k = 0 ; k <= count; k++){
	  if(state_index_d(i)(j) == unique_states(k)){
	    state_index(i)(j) = k;
	    break;
	  }
	}
      }
    }

  }
  else{
    state_index.assign(state_index_d);
    for (int32 i=0;i<Kz_d;i++)
      unique_states(i)=i;
    state_no=Kz_d;
  }
  MatrixDouble mat_tmp;
  mat_tmp.setDimensions(state_no,Kz_d);
  pi_z.setDimensions(state_no,state_no);
  pi_init.setLength(state_no);
  pi_z_ne.setDimensions(state_no+2,state_no+2);
  pi_init_ne.setLength(state_no+2);
  
  VectorDouble vec_tmp;
  for(int32 i = 0 ; i < state_no ; i++){
    pi_z_tmp.getRow(vec_tmp,unique_states(i));
    mat_tmp.setRow(i,vec_tmp);  
  }
  for(int32 i = 0 ; i < state_no ; i++){
    mat_tmp.getColumn(vec_tmp,unique_states(i));
    pi_z.setColumn(i,vec_tmp);  
  }
  for(int32 i = 0 ; i < state_no ; i++){
    pi_z.getRow(vec_tmp,i);
    vec_tmp.div(vec_tmp.sum());   
    pi_z.setRow(i,vec_tmp);  
  }
  for (int32 i = 0; i < state_no ; i++){
    pi_init(i) = pi_init_tmp(unique_states(i));
  }
  pi_init.div(pi_init.sum());

  
  // calculate non-emitting final state probablities
  //
  VectorFloat M(unique_states.length());
  VectorFloat self_trans(unique_states.length());
  VectorFloat rho(unique_states.length());
  MatrixDouble temp_piz;
  temp_piz.setDimensions(state_no+2,state_no+2);

  
  for (int32 i = 0 ; i< state_index_d.length(); i++){
    
    int32 end_state = state_index_d(i)(state_index_d(i).length()-1);
    int32 curr_state = end_state;
    int32 counter = 1;
    int32 pos = state_index_d(i).length()-2;
    do{
      
      curr_state = state_index_d(i)(pos);
      pos--;
      if(end_state == curr_state)
	counter++;
    } while( end_state == curr_state && pos >= 0);
    
    for(int32 k = 0; k < unique_states.length();k++){
      
      if(unique_states(k) == end_state){
	M(k)++;
	self_trans(k) += counter;
	
      }
    }
    
  }
  for(int32 k = 0; k < unique_states.length();k++){
    if (self_trans(k) > (float)0.0)
      rho(k) = M(k)/self_trans(k);
  }
  vec_tmp.assign(pi_init);
  vec_tmp.setLength(pi_init.length()+2);
  vec_tmp.shift(1);
  temp_piz.setRow(0,vec_tmp);
  for (int32 k=0; k < pi_init.length(); k++){
    pi_z.getRow(vec_tmp,k);
    vec_tmp.setLength(pi_init.length()+2);
    vec_tmp(pi_init.length()) = (double)rho(k)*(double)vec_tmp(k);
    vec_tmp(k)= (1-rho(k))*(vec_tmp(k));
    vec_tmp.shift(1);
    temp_piz.setRow(k+1,vec_tmp);
  }
  temp_piz.setValue((pi_init.length()+1),(pi_init.length()+1),1);
  
 
  // assign the new values
  //
  pi_init_ne.setRange(0,state_no+2,0);
  pi_init_ne(0)=1;
  pi_z_ne.assign(temp_piz);
  

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
    obj_size = pi_init.sofSize() + pi_z.sofSize() +  pi_init_ne.sofSize() +  pi_z_ne.sofSize();
  }

  // write the object into the sof file's index
  //
  if (!outfile.put(L"HDPHMM", 0, obj_size)) {
    return false;
  }
  
  if(!pi_init.writeData(outfile,L"pi_init"))
    return Error::handle(name(), L"writeData", Error::WRITE,
 			 __FILE__, __LINE__, Error::WARNING);
 if(!pi_z.writeData(outfile,L"pi_z"))
    return Error::handle(name(), L"writeData", Error::WRITE,
 			 __FILE__, __LINE__, Error::WARNING);


 if(!pi_init_ne.writeData(outfile,L"pi_init_with_none_emitting"))
   return Error::handle(name(), L"writeData", Error::WRITE,
			__FILE__, __LINE__, Error::WARNING);
 if(!pi_z_ne.writeData(outfile,L"pi_z_with_none_emitting"))
   return Error::handle(name(), L"writeData", Error::WRITE,
			__FILE__, __LINE__, Error::WARNING);


 // extarct emissions
 //
 for(int32 i = 0; i < state_no ; i++){
   emissions_d(unique_states(i)).extract_model(outfile,state_index_d,unique_states(i),i,reduce_a);

 }
 

 if (outfile.isText()) {
   
   // set the size to by dynamic
   //
   obj_size = Sof::ANY_SIZE;
 }
 else {
   
   // the size index and the size of each element
   //
   obj_size = state_index_d.sofSize();
 }
 

 if (!outfile.put(L"state_index", 0, obj_size)) {
   return false;
 }

 if(! state_index.writeData(outfile,L"state_index"))
   return Error::handle(name(), L"writeData", Error::WRITE,
			__FILE__, __LINE__, Error::WARNING);

 master_emission_d.extract_model(outfile,state_index_d,unique_states(0),0);

  outfile.close();
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
// load the minmum  model (HMM without  other parameters)
//
template <class emission_type>
bool8 HDPHMM<emission_type>::load_final_model(String model_a,Database &db_a) {


  Sof sof_a;
  VectorLong seeds(6);
  VectorDouble tmp1(6),tmp2(8);

  
  db_d = &db_a;

  // open the Sof file
  //
  if (sof_a.open(model_a, File::READ_ONLY) != true) {
    return Error::handle(model_a, L"open", Error::TEST, __FILE__, __LINE__);
  }

  // read the frist  HMM model
  //
  if(read_final_model(sof_a,0) != true)
      return Error::handle(model_a, L"read", Error::TEST, __FILE__, __LINE__);
  
  // read the emissions
  //  
   for(int i=0;i<(emissions_d).length();i++)
     (emissions_d)(i).read_final_model(sof_a,i,L"emission_model");


  sof_a.close();


  // exist garcefully
  //
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
template <class emission_type>
bool8 HDPHMM<emission_type>::read_final_model(Sof& sof_a, int32 tag_a, const String& name_a) {

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
  
  // get pi_z
  //
  if (!dist_struct_d.pi_z.readData(sof_a, L"pi_z",
				   parser.getEntry(sof_a, L"pi_z"),
				   false, true)) {
    return Error::handle(name(), L"readData", Error::READ,
			 __FILE__, __LINE__, Error::WARNING);
    }	    
  
  // get pi_init
  //
  if (!dist_struct_d.pi_init.readData(sof_a, L"pi_init",
				      parser.getEntry(sof_a, L"pi_init"),false, false)) {
    return Error::handle(name(), L"readData", Error::READ,
			 __FILE__, __LINE__, Error::WARNING);
  }
    
  Kz_d = dist_struct_d.pi_init.length();
 
  emissions_d.setLength(Kz_d,false);
  master_emission_d.setMaster(emissions_d);
  master_emission_d.set_db(*db_d);

  
  // exit gracefully
  //
  return true;
  
}
