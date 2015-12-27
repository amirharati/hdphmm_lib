// file: $isip/class/numeric/Sigmoid/sigm_04.cc
// version: $Id: sigm_04.cc 6254 2001-01-29 23:10:53Z hamaker $
//

// isip include files
//
#include "Sigmoid.h"

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
bool8 Sigmoid::write(Sof& sof_a, int32 tag_a,
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
bool8 Sigmoid::writeData(Sof& sof_a, const String& pname_a) const {
  
  // write a start string if necessary
  //
  sof_a.writeLabelPrefix(pname_a);

  // write the parameters
  //
  gain_d.writeData(sof_a, PARAM_GAIN);
  slope_d.writeData(sof_a, PARAM_SLOPE);
  xoffset_d.writeData(sof_a, PARAM_XOFFSET);
  yoffset_d.writeData(sof_a, PARAM_YOFFSET);  

  // put an end string if necessary
  //
  sof_a.writeLabelSuffix(pname_a);
  
  // exit gracefully
  //
  return true;
}
