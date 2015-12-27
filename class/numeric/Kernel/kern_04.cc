// file: $isip/class/algo/Kernel/kern_04.cc
// version: $Id: kern_04.cc 7197 2001-07-20 15:51:56Z hamaker $
//

// isip include files
//
#include "Kernel.h"

// method: sofSize
//
// arguments: none
//
// return: size of object
//
// this method returns the size of the object in the Sof file and is
// used for binary write
//
int32 Kernel::sofSize() const {

  // start with the space required for the algorithm name
  //
  int32 bytes = ALGO_MAP.elementSofSize();

  // add the space required for Kernel constant vector
  //
  bytes += constants_d.sofSize();

  // return the size
  //
  return bytes;
}

// method: write
//
// arguments:
//  Sof& sof: (input) sof file object
//  int32 tag: (input) sof object instance tag
//  const String& name: (input) sof object instance name
//
// return: a bool8 value indicating status
//
// this method has the object write itself to an Sof file
//
bool8 Kernel::write(Sof& sof_a, int32 tag_a, const String& name_a) const {

  // declare local variable
  //
  int32 obj_size;
  
  // write the instance of the object into the Sof file
  //
  if (sof_a.isText()) {

    // set the size to by dynamic
    //
    obj_size = Sof::ANY_SIZE;
  }
  else {

    // set the size to be the size of the object written to the Sof file
    //
    obj_size = sofSize();
  }

  // write the object into the sof file's index
  //
  if (!sof_a.put(name_a, tag_a, obj_size)) {
    return false;
  }
  
  // write data and exit gracefully
  //
  return writeData(sof_a);
}

// method: writeData
//
// arguments:
//  Sof& sof: (input) sof file object
//  const String& pname: (input) parameter name
//
// return: a bool8 value indicating status
//
// this method has the object write itself to an Sof file. it assumes
// that the Sof file is already positioned correctly
//
bool8 Kernel::writeData(Sof& sof_a, const String& pname_a) const {

  // write a start string if necessary
  //
  sof_a.writeLabelPrefix(pname_a);

  // write the algorithm name
  //
  ALGO_MAP.writeElementData(sof_a, PARAM_ALGORITHM, (int32)algorithm_d);
    
  // check known algorithms: read constants data
  //
  if ((algorithm_d == LINEAR) ||
      (algorithm_d == POLYNOMIAL) ||
      (algorithm_d == RBF) ||
      (algorithm_d == SIGMOID)) {

    constants_d.writeData(sof_a, PARAM_CONSTANTS);
  }
  // check unknown algorithms
  //
  else {
    return Error::handle(name(), L"writeData",
			 ERR_UNKALG, __FILE__, __LINE__);
  }


  // put an end string if necessary
  //
  sof_a.writeLabelSuffix(pname_a);
  
  // exit gracefully
  //
  return true;
}
