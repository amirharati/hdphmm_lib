// file: $isip/class/shell/DebugLevel/dbgl_03.cc
// version: $Id: dbgl_03.cc 5327 2000-10-18 17:03:15Z srivasta $
//

// isip include files
//
#include "DebugLevel.h"

// method: read
//
// arguments:
//  Sof& sof: (input) sof file object
//  int32 tag: (input) sof object instance tag
//  const String& name: (input) sof object instance name
//
// return: a bool8 value indicating status
//
// this method has the object read itself from an Sof file
//
bool8 DebugLevel::read(Sof& sof_a, int32 tag_a, const String& name_a) {

  // get the instance of the object from the Sof file
  //
  if (!sof_a.find(name_a, tag_a)) {
    return false;
  }

  // read the actual data from the sof file
  //
  if (!readData(sof_a)) {
    return false;
  }

  // exit gracefully
  //
  return true;
}

// method: readData
//
// arguments:
//  Sof& sof: (input) sof file object
//  const String& pname: (input) parameter name
//  int32 size: (input) size in bytes of object (or FULL_SIZE)
//  bool8 param: (input) is the parameter specified?
//  bool8 nested: (input) is this nested?
//
// return: a bool8 value indicating status
//
// this method has the object read itself from an Sof file. it assumes
// that the Sof file is already positioned correctly.
//
bool8 DebugLevel::readData(Sof& sof_a, const String& pname_a,
			     int32 size_a, bool8 param_a,
			     bool8 nested_a) {

  // use the NameMap special i/o methods
  //
  LEVEL_MAP.readElementData((int32&)value_d, sof_a, pname_a, size_a,
			    param_a, nested_a);

  // value_d can't be negative
  //
  if (value_d  < (int32)0) {
    return false;
  }
  else {
    return true;
  }
}
