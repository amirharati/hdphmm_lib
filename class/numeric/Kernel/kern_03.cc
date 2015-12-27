// file: $isip/class/algo/Kernel/kern_03.cc
// version: $Id: kern_03.cc 7197 2001-07-20 15:51:56Z hamaker $
//

// isip include files
//
#include "Kernel.h"

// method: read
//
// arguments:
//  Sof& sof: (input) sof file object
//  int32 tag: (input) sof object instance tag
//  const String& name: (input) sof object instance name
//
// return: a bool8 value indicating status
//
// this method has the object read itself from an Sof file according
// to the specified name and tag
//
bool8 Kernel::read(Sof& sof_a, int32 tag_a, const String& name_a) {

  // get the instance of the object from the Sof file
  //
  if (!sof_a.find(name_a, tag_a)) {
    return false;
  }

  // read the actual data from the sof file
  //
  return readData(sof_a);
}

// method: readData
//
// arguments:
//  Sof& sof: (input) sof file object
//  const String& pname: (input) parameter name
//  int32 size: (input) size in bytes of object (or FULL_OBJECT)
//  bool8 param: (input) is the parameter name in the file?
//  bool8 nested: (input) are we nested?
//
// return: a bool8 value indicating status
//
// this method has the object read itself from an Sof file. it assumes
// that the Sof file is already positioned correctly
//
bool8 Kernel::readData(Sof& sof_a, const String& pname_a,
			 int32 size_a, bool8 param_a, bool8 nested_a) {

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

  // get the algorithm
  //
  if (parser.isPresent(sof_a, PARAM_ALGORITHM)) {
    if (!ALGO_MAP.readElementData((int32&)algorithm_d, sof_a, PARAM_ALGORITHM,
				  parser.getEntry(sof_a, PARAM_ALGORITHM))) {

      // return a warning message
      //
      return Error::handle(name(), L"readData", Error::READ,
			   __FILE__, __LINE__, Error::WARNING);
    }
  }
  else {
    algorithm_d = DEF_ALGORITHM;
  }
  setAlgorithm(algorithm_d);
  
  // check known algorithms: read constants data
  //
  if ((algorithm_d == LINEAR) ||
      (algorithm_d == POLYNOMIAL) ||
      (algorithm_d == RBF) ||
      (algorithm_d == SIGMOID)) {

    // read the constants
    //
    if (parser.isPresent(sof_a, PARAM_CONSTANTS)) {
      if (!constants_d.readData(sof_a, PARAM_CONSTANTS,
				parser.getEntry(sof_a, PARAM_CONSTANTS) ,
				false, false)) {
      
	// return a warning message
	//
	return Error::handle(name(), L"readData", Error::READ,
			     __FILE__, __LINE__, Error::WARNING);
	
      }
    }
  }
    
  // check unsupported algorithms
  //
  else {
    return Error::handle(name(), L"readData",
			 ERR_UNKALG, __FILE__, __LINE__);
  }

  // check that all parameters are accounted for
  //
  if (!parser.checkParams(sof_a)) {

    // return a warning message
    //
    return Error::handle(name(), L"readData", Error::IO,
			 __FILE__, __LINE__, Error::WARNING);
  }

  // set the status to invalid and initialize
  //
  is_valid_d = false;
  init();

  // exit gracefully
  //
  return true;
}
