// file: $isip/class/shell/Filename/fn_03.cc
// version: $Id: fn_03.cc 6807 2001-04-24 15:28:14Z peng $
//

// isip include files
//
#include "Filename.h"
#include <Sof.h>
#include <String.h>

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
bool8 Filename::read(Sof& sof_a, int32 tag_a, const String& name_a) {

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
bool8 Filename::write(Sof& sof_a, int32 tag_a, const String& name_a) const {

  // declare local variables
  //
  int32 obj_size;

  // get the size of the object
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
