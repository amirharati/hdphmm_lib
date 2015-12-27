// file: $isip/class/...
// version: $Id: hdphmm_03.cc 7/10/2013
//

// isip include files
//
#include "HDPHMM.h"
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
template <class emission_type>
bool8 HDPHMM<emission_type>::read(Sof& sof_a, int32 tag_a, const String& name_a) {

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
template <class emission_type>
bool8 HDPHMM<emission_type>::readData(Sof& sof_a, const String& pname_a,
				    int32 size_a,
				    bool8 param_a, bool8 nested_a) {

  Integral::DEBUG debug_level = Integral::NONE;

  SofParser parser;

  parser.setDebug(debug_level);


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

  // read the  model file
  //
  if (pname_a.eq(PARAM_MODEL)){
    

    // get emission type
    //
    if (!emission_type_d.readData(sof_a, L"emission_type",
				     parser.getEntry(sof_a, L"emission_type"),
				     false, false)) {
      return Error::handle(name(), L"readData", Error::READ,
			   __FILE__, __LINE__, Error::WARNING);
    }	  
    
    if (emission_type_d.eq(master_emission_d.name())==false){

      Console::put(L"Emission types in the file to be loaded and the model specifications are not the same.");
      Integral::exit(); 
       
    }
    // get hyper_vec
    //
    if (!hyper_params_vec_d.readData(sof_a, L"hyper_params_vec",
				      parser.getEntry(sof_a, L"hyper_params_vec"),
				      false, false)) {
       return Error::handle(name(), L"readData", Error::READ,
			    __FILE__, __LINE__, Error::WARNING);
     }	  
     
     if (!iterations_d.readData(sof_a, L"iterations",
				parser.getEntry(sof_a, L"iterations"),
				false, false)) {
       return Error::handle(name(), L"readData", Error::READ,
			    __FILE__, __LINE__, Error::WARNING);
     }	  
     
     if (!burn_in_d.readData(sof_a, L"burn_in",
				     parser.getEntry(sof_a, L"burn_in"),
				     false, false)) {
      return Error::handle(name(), L"readData", Error::READ,
			   __FILE__, __LINE__, Error::WARNING);
     }	  
     
     if (!itr_acc_d.readData(sof_a, L"itr_acc",
				     parser.getEntry(sof_a, L"itr_acc"),
				     false, false)) {
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
        
    // get beta_vec
    //
    if (!dist_struct_d.beta_vec.readData(sof_a, L"beta_vec",
	       parser.getEntry(sof_a, L"beta_vec"),
		       false, false)) {
      return Error::handle(name(), L"readData", Error::READ,
			   __FILE__, __LINE__, Error::WARNING);
    }
 
    // get pi_z_acc
    //
    if (!dist_struct_d.pi_z_acc.readData(sof_a, L"pi_z_acc",
				     parser.getEntry(sof_a, L"pi_z_acc"),
				     false, true)) {
      return Error::handle(name(), L"readData", Error::READ,
			   __FILE__, __LINE__, Error::WARNING);
    }	    
    
    // get pi_init_acc
    //
    if (!dist_struct_d.pi_init_acc.readData(sof_a, L"pi_init_acc",
	parser.getEntry(sof_a, L"pi_init_acc"),false, false)) {
      return Error::handle(name(), L"readData", Error::READ,
			   __FILE__, __LINE__, Error::WARNING);
    }
       
    // get beta_vec_acc
    //
    if (!dist_struct_d.beta_vec_acc.readData(sof_a, L"beta_vec_acc",
	       parser.getEntry(sof_a, L"beta_vec_acc"),
		       false, false)) {
      return Error::handle(name(), L"readData", Error::READ,
			   __FILE__, __LINE__, Error::WARNING);
    }   
 
    // get N
    //
    if (!counts_d.N.readData(sof_a, L"N",
			     parser.getEntry(sof_a, L"N"),
			     false, true)) {
      return Error::handle(name(), L"readData", Error::READ,
			   __FILE__, __LINE__, Error::WARNING);
    }
    
    // get M
    //
    if (!counts_d.M.readData(sof_a, L"M",
			     parser.getEntry(sof_a, L"M"),
			     false, true)) {
      return Error::handle(name(), L"readData", Error::READ,
			   __FILE__, __LINE__, Error::WARNING);
    }
    
    // get barM
    //
    if (!counts_d.barM.readData(sof_a, L"barM",
		       parser.getEntry(sof_a, L"barM"),
				false, true)) {
      return Error::handle(name(), L"readData", Error::READ,
			   __FILE__, __LINE__, Error::WARNING);
    }
    
    // get sumW
    //
    if (!counts_d.sumW.readData(sof_a, L"sumW",
				parser.getEntry(sof_a, L"sumW"),
				false, false)) {
      return Error::handle(name(), L"readData", Error::READ,
			 __FILE__, __LINE__, Error::WARNING);
    }
    
    // get alpha_p_kappa
    //
    if (!hyper_d.alpha_p_kappa.readData(sof_a, L"alpha_p_kappa",
					parser.getEntry(sof_a, L"alpha_p_kappa"),
					false, false)) {
      return Error::handle(name(), L"readData", Error::READ,
			   __FILE__, __LINE__, Error::WARNING);
    }

    // get gamma
    //
    if (!hyper_d.gamma.readData(sof_a, L"gamma",
			     parser.getEntry(sof_a, L"gamma"),
 			     false, false)) {
      return Error::handle(name(), L"readData", Error::READ,
			   __FILE__, __LINE__, Error::WARNING);
    }
   
    // get rho 
    //
    if (!hyper_d.rho.readData(sof_a, L"rho",
			      parser.getEntry(sof_a, L"rho"),
			      false, false)) {
      return Error::handle(name(), L"readData", Error::READ,
			   __FILE__, __LINE__, Error::WARNING);
    }
  
    // get state index
    //
    /*    if (!state_index_d.readData(sof_a, L"state_index",
				parser.getEntry(sof_a, L"state_index"),
 			     false, false)) {
      return Error::handle(name(), L"readData", Error::READ,
			   __FILE__, __LINE__, Error::WARNING);
			   }*/
  }  

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
template <class emission_type>
bool8 HDPHMM<emission_type>::write(Sof& sof_a, int32 tag_a,
			     const String& name_a) const {

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
template <class emission_type>
bool8 HDPHMM<emission_type>::writeData(Sof& sof_a, const String& pname_a) const {

  // write all params of the model
  //

 
  if(!emission_type_d.writeData(sof_a,L"emission_type"))
    return Error::handle(name(), L"writeData", Error::WRITE,
 			 __FILE__, __LINE__, Error::WARNING);

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

  if(!dist_struct_d.pi_z.writeData(sof_a,L"pi_z"))
    return Error::handle(name(), L"writeData", Error::WRITE,
			 __FILE__, __LINE__, Error::WARNING);

  if(!dist_struct_d.pi_init.writeData(sof_a,L"pi_init"))
    return Error::handle(name(), L"writeData", Error::WRITE,
			 __FILE__, __LINE__, Error::WARNING);
  
  if(!dist_struct_d.beta_vec.writeData(sof_a,L"beta_vec"))
    return Error::handle(name(), L"writeData", Error::WRITE,
			 __FILE__, __LINE__, Error::WARNING);


 if(!dist_struct_d.pi_z_acc.writeData(sof_a,L"pi_z_acc"))
    return Error::handle(name(), L"writeData", Error::WRITE,
			 __FILE__, __LINE__, Error::WARNING);

  if(!dist_struct_d.pi_init_acc.writeData(sof_a,L"pi_init_acc"))
    return Error::handle(name(), L"writeData", Error::WRITE,
			 __FILE__, __LINE__, Error::WARNING);
  
  if(!dist_struct_d.beta_vec_acc.writeData(sof_a,L"beta_vec_acc"))
    return Error::handle(name(), L"writeData", Error::WRITE,
			 __FILE__, __LINE__, Error::WARNING);

  if(!counts_d.N.writeData(sof_a,L"N"))
    return Error::handle(name(), L"writeData", Error::WRITE,
 			 __FILE__, __LINE__, Error::WARNING);

 if(!counts_d.M.writeData(sof_a,L"M"))
    return Error::handle(name(), L"writeData", Error::WRITE,
 			 __FILE__, __LINE__, Error::WARNING);

 if(!counts_d.barM.writeData(sof_a,L"barM"))
    return Error::handle(name(), L"writeData", Error::WRITE,
 			 __FILE__, __LINE__, Error::WARNING);

 if(!counts_d.sumW.writeData(sof_a,L"sumW"))
   return Error::handle(name(), L"writeData", Error::WRITE,
			__FILE__, __LINE__, Error::WARNING);

if(!hyper_d.alpha_p_kappa.writeData(sof_a,L"alpha_p_kappa"))
    return Error::handle(name(), L"writeData", Error::WRITE,
 			 __FILE__, __LINE__, Error::WARNING);

if(!hyper_d.gamma.writeData(sof_a,L"gamma"))
    return Error::handle(name(), L"writeData", Error::WRITE,
 			 __FILE__, __LINE__, Error::WARNING);
if(!hyper_d.rho.writeData(sof_a,L"rho"))
    return Error::handle(name(), L"writeData", Error::WRITE,
 			 __FILE__, __LINE__, Error::WARNING);

if(! state_index_d.writeData(sof_a,L"state_index"))
     return Error::handle(name(), L"writeData", Error::WRITE,
 			 __FILE__, __LINE__, Error::WARNING);

  return true;
}


