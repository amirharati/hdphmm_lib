// file: $isip/class/shell/DebugLevel/dbgl_04.cc
// version: $Id: dbgl_04.cc 5454 2000-11-02 16:32:16Z picone $
//

// isip include files
//
#include "DebugLevel.h"

// method: write
//
// arguments:
//  Sof& sof: (input) sof file object
//  int32 tag: (input) sof object instance tag
//  String& name: (input) sof object instance name
//
// return: a bool8 value indicating status
//
// this method writes an object to an Sof file
//
bool8 DebugLevel::write(Sof& sof_a, int32 tag_a, const String& name_a) const {

  // declare local variables
  //
  int32 obj_size;

  // get the size of the object inside the Sof file
  //
  if (sof_a.isText()) {
    obj_size = Sof::ANY_SIZE;
  }
  else {
    obj_size = sofSize();
  }
  
  // put the object into the sof file's index
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
// return: a bool8 value indicating status
//
// this method writes an object to an Sof file. it assumes that the
// Sof file is already positioned correctly.
//
bool8 DebugLevel::writeData(Sof& sof_a, const String& pname_a) const {
  
  // call the NameMap write function so we get those cute little
  // double quotes surrounding the value.
  //
  return LEVEL_MAP.writeElementData(sof_a, pname_a, value_d);
}
