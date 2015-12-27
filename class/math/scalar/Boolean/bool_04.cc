// file: $isip/class/math/scalar/Boolean/bool_04.cc
// version: $Id: bool_04.cc 6807 2001-04-24 15:28:14Z peng $
//

// isip include files
//
#include "Boolean.h"

// method: write
//
// arguments:
//  Sof& sof: (input) sof file object
//  long tag: (input) sof object instance tag
//  const String& name: (input) sof object instance name
//
// return: a bool8 value indicating status
//
// this method has the object write itself to an Sof file
//
bool8 Boolean::write(Sof& sof_a, int32 tag_a, const String& name_a) const {

  int32 obj_size;

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
// this method writes the object to the Sof file. it assumes that the
// Sof file is already positioned correctly.
//
bool8 Boolean::writeData(Sof& sof_a, const String& pname_a) const {

  // test whether the sof file is ascii
  //
  if (sof_a.isText()) {
    
    String output;
    
    // start with the assignment String
    //
    if (pname_a.length() > 0) {
      output.assign(pname_a);
      output.concat(L" = ");
    }

    // concatenate the value
    //
    String numeric;
    numeric.assign(value_d);
    output.concat(numeric);
    
    // if a parameter name was set, add a terminator and a newline
    //
    if (pname_a.length() > 0) {
      output.concat(L";\n");
    }

    // write the text String
    //
    if (!sof_a.puts(output)) {
      return false;
    }
  }

  // binary write, very simple
  //
  else {

    // make sure we write exactly 1 byte
    //
    byte8 val = (byte8)value_d;

    // range check the datatype
    //
    if (value_d != (bool8)val) {
      return Error::handle(name(), L"writeData", Error::DATATYPE_RANGE,
			   __FILE__, __LINE__, Error::WARNING);
    }
    
    if (sof_a.write(&val, sizeof(val), 1) != 1) {
      return false;
    }
  }
  
  // exit gracefully
  //
  return true;
}
