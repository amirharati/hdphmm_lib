// file: $isip/class/...
// version: $Id: database_03.cc 7/10/2013
//

// isip include files
//
#include "DPM.h"
#include <Sof.h>

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
bool8 DPM::read(Sof& sof_a, int32 tag_a, const String& name_a) {

     if (is_master_d == true){
    for(int32 i = 0;i < slaves_d->length();i++){
      (*slaves_d)(i).read(sof_a,i,L"emission_model");
    }
    return true;
  }
  else{
  

    // get the instance of the object from the Sof file
    //
    if (!sof_a.find(name_a, tag_a)) {
      return false;
    }

    // read the actual data from the sof file
    //
    return readData(sof_a);
  }
}

// method: readData
//
// arguments:
// Sof& sof: (input) sof file object
// const String& pname: (input) parameter name
// int32 size: (input) number of bytes in file
// bool8 param: (input) is the parameter specified?
// bool8 nested: (input) is this nested?
//
// return: logical error status
//
// this method has the object read itself from an Sof file. it assumes
// that the Sof file is already positioned correctly.
//
bool8 DPM::readData(Sof& sof_a, const String& pname_a,
				    int32 size_a,
				    bool8 param_a, bool8 nested_a) {

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
    return Error::handle(name(), L"readData", Error::READ,
			 __FILE__, __LINE__, Error::WARNING);
  }	    

  // get hyper_vec
  //
  if (!hyper_params_vec_d.readData(sof_a, L"hyper_params_vec",
		       parser.getEntry(sof_a, L"hyper_params_vec"),
		       false, false)) {
    return Error::handle(name(), L"readData", Error::READ,
			 __FILE__, __LINE__, Error::WARNING);
  }	  


 if (!iterations_d.readData(sof_a, L"iterations",parser.getEntry(sof_a, L"iterations"),false, false)) {
      return Error::handle(name(), L"readData", Error::READ,
			   __FILE__, __LINE__, Error::WARNING);
    }	  


     if (!burn_in_d.readData(sof_a, L"burn_in",parser.getEntry(sof_a, L"burn_in"),false, false)) {
      return Error::handle(name(), L"readData", Error::READ,
			   __FILE__, __LINE__, Error::WARNING);
    }	  
 

     if (!itr_acc_d.readData(sof_a, L"itr_acc",parser.getEntry(sof_a, L"itr_acc"),false, false)) {
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

  // get mu_acc
  //
  if (!theta_d.mu_acc.readData(sof_a, L"mu_acc",
		       parser.getEntry(sof_a, L"mu_acc"),
		       false, false)) {
    return Error::handle(name(), L"readData", Error::READ,
			 __FILE__, __LINE__, Error::WARNING);
  }	    

  // get invSigma_acc
  //
  if (!theta_d.invSigma_acc.readData(sof_a, L"invSigma_acc",
			     parser.getEntry(sof_a, L"invSigma_acc"),
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

   // get pi_s 
   //
   if (!dist_struct_d.pi_s_acc.readData(sof_a, L"pi_s_acc",
 			     parser.getEntry(sof_a, L"pi_s_acc"),
 			     false, false)) {
     return Error::handle(name(), L"readData", Error::READ,
 			 __FILE__, __LINE__, Error::WARNING);
   }


   // get Ns
   //
   if (!counts_d.Ns.readData(sof_a, L"Ns",
 			     parser.getEntry(sof_a, L"Ns"),
 			     false, false)) {
     return Error::handle(name(), L"readData", Error::READ,
 			 __FILE__, __LINE__, Error::WARNING);
   }

   // get cards
   //
   if (!sstats_d.cards.readData(sof_a, L"cards",
 			     parser.getEntry(sof_a, L"cards"),
 			     false, false)) {
     return Error::handle(name(), L"readData", Error::READ,
 			 __FILE__, __LINE__, Error::WARNING);
   }

   // get YY 
   //
   if (!sstats_d.YY.readData(sof_a, L"YY",
 			     parser.getEntry(sof_a, L"YY"),
 			     false, false)) {
     return Error::handle(name(), L"readData", Error::READ,
 			 __FILE__, __LINE__, Error::WARNING);
   }

   // get sumY 
   //
   if (!sstats_d.sumY.readData(sof_a, L"sumY",
 			     parser.getEntry(sof_a, L"sumY"),
 			     false, false)) {
     return Error::handle(name(), L"readData", Error::READ,
 			 __FILE__, __LINE__, Error::WARNING);
   }

   // get sigma 
   //
   if (!hyper_d.sigma.readData(sof_a, L"sigma",
 			     parser.getEntry(sof_a, L"sigma"),
 			     false, false)) {
     return Error::handle(name(), L"readData", Error::READ,
 			 __FILE__, __LINE__, Error::WARNING);
   }
   if (is_slave_d ==  true)
     (*master_d).hyper_d.sigma.assign(hyper_d.sigma);

   // get data_index 
   // code fixed : it allows for having new data 
   /*if (!mixture_index_d.readData(sof_a, L"data_index",
 			     parser.getEntry(sof_a, L"data_index"),
 			     false, false)) {
     return Error::handle(name(), L"readData", Error::READ,
 			 __FILE__, __LINE__, Error::WARNING);
			 }*/
   

  // exit gracefully
  //
  return true;

}

// method: write
//
// arguments:
//  Sof& sof: (input) sof file object
//  int32 tag: (input) sof object instance tag
//  const String& name: (input) sof object instance name
//
// return: bool8 value indicating status
//
// this method has the object write itself to an Sof file
//
bool8 DPM::write(Sof& sof_a, int32 tag_a,
			     const String& name_a) const {


  // for compact instances mu,invSigma,mu_acc and invSigma_acc are not stored
  
  if (is_master_d == true){
    for(int32 i = 0;i < slaves_d->length();i++){
      (*slaves_d)(i).write(sof_a,i,L"emission_model");
    }
    return true;
  }
  else{

    int32 obj_size = 0;
  
    // write the instance of the object into the Sof file
    //
    if (sof_a.isText()) {

      // set the size to by dynamic
      //
      obj_size = Sof::ANY_SIZE;
    }
    else {

      // the size index and the size of each element
      //
      obj_size = sofSize();
    }

    // write the object into the sof file's index
    //
    if (!sof_a.put(name_a, tag_a, obj_size)) {
      return false;
    }
    
    // exit gracefully
    //
    return writeData(sof_a);
  }
}

// method: writeData
//
// arguments:
//  Sof& sof: (input) sof file object
//  const String& pname: (input) parameter name
//
// return: bool8 value indicating status
//
// this method has the object write itself to an Sof file. it assumes
// that the Sof file is already positioned correctly.
//
bool8 DPM::writeData(Sof& sof_a, const String& pname_a) const {

  // write all params of the model
  //

  if(!hyper_params_vec_d.writeData(sof_a,L"hyper_params_vec"))
    return Error::handle(name(), L"writeData", Error::WRITE,
			 __FILE__, __LINE__, Error::WARNING);

  if(!iterations_d.writeData(sof_a,L"iterations"))
    return Error::handle(name(), L"writeData", Error::WRITE,
 			 __FILE__, __LINE__, Error::WARNING);
  
  if(!burn_in_d.writeData(sof_a,L"burn_in"))
    return Error::handle(name(), L"writeData", Error::WRITE,
 			 __FILE__, __LINE__, Error::WARNING);
  
  if(!itr_acc_d.writeData(sof_a,L"itr_acc"))
    return Error::handle(name(), L"writeData", Error::WRITE,
 			 __FILE__, __LINE__, Error::WARNING);

  if(!theta_d.mu.writeData(sof_a,L"mu"))
    return Error::handle(name(), L"writeData", Error::WRITE,
			 __FILE__, __LINE__, Error::WARNING);

  if(!theta_d.invSigma.writeData(sof_a,L"invSigma"))
    return Error::handle(name(), L"writeData", Error::WRITE,
			 __FILE__, __LINE__, Error::WARNING);
  
  if(!theta_d.mu_acc.writeData(sof_a,L"mu_acc"))
    return Error::handle(name(), L"writeData", Error::WRITE,
			 __FILE__, __LINE__, Error::WARNING);

  if(!theta_d.invSigma_acc.writeData(sof_a,L"invSigma_acc"))
    return Error::handle(name(), L"writeData", Error::WRITE,
			 __FILE__, __LINE__, Error::WARNING);
  

  if(!dist_struct_d.pi_s.writeData(sof_a,L"pi_s"))
    return Error::handle(name(), L"writeData", Error::WRITE,
			 __FILE__, __LINE__, Error::WARNING);

  if(!dist_struct_d.pi_s_acc.writeData(sof_a,L"pi_s_acc"))
    return Error::handle(name(), L"writeData", Error::WRITE,
			 __FILE__, __LINE__, Error::WARNING);

  if(!counts_d.Ns.writeData(sof_a,L"Ns"))
    return Error::handle(name(), L"writeData", Error::WRITE,
 			 __FILE__, __LINE__, Error::WARNING);

 if(!sstats_d.cards.writeData(sof_a,L"cards"))
    return Error::handle(name(), L"writeData", Error::WRITE,
 			 __FILE__, __LINE__, Error::WARNING);

 if(!sstats_d.YY.writeData(sof_a,L"YY"))
    return Error::handle(name(), L"writeData", Error::WRITE,
 			 __FILE__, __LINE__, Error::WARNING);

 if(!sstats_d.sumY.writeData(sof_a,L"sumY"))
   return Error::handle(name(), L"writeData", Error::WRITE,
			__FILE__, __LINE__, Error::WARNING);

if(!hyper_d.sigma.writeData(sof_a,L"sigma"))
    return Error::handle(name(), L"writeData", Error::WRITE,
 			 __FILE__, __LINE__, Error::WARNING);

if(! mixture_index_d.writeData(sof_a,L"data_index"))
     return Error::handle(name(), L"writeData", Error::WRITE,
 			 __FILE__, __LINE__, Error::WARNING);

  return true;
}
