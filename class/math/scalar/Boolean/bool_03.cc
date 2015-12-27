// file: $isip/class/math/scalar/Boolean/bool_03.cc
// version: $Id: bool_03.cc 4895 2000-09-20 16:09:11Z duncan $
//

// isip include files
//
#include "Boolean.h"

// method: read
//
// arguments:
//  Sof& sof: (input) sof file object
//  int32 tag: (input) sof object instance tag
//  const String& name: (input) sof object instance name
//
// return: a boolean value indicating status
//
// this method has the object read itself from an Sof file
//
bool8 Boolean::read(Sof& sof_a, int32 tag_a, const String& name_a) {

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
bool8 Boolean::readData(Sof& sof_a, const String& pname_a, int32 size_a,
			  bool8 param_a, bool8 nested_a) {

  // if ascii, read in a line, else binary read
  //
  if (sof_a.isText()) {
    
    SofParser parser;
    String buffer;
    String pname;

    // set the parser debug level
    //
    parser.setDebug(debug_level_d);
    
    // if param is false, this means implicit parameter
    //
    if (!param_a) {
      parser.setImplicitParam();
      pname.assign(parser.implicitPname());
    }
    else {
      pname.assign(pname_a);
    }
    
    // are we nested?
    //
    if (nested_a) {
      parser.setNest();
    }

    // size = -1 means this is the root object, load the parse
    //
    if (size_a < 0) {
      parser.load(sof_a, size_a);

      // if param is false, this means implicit parameter
      //
      if (!param_a) {
        parser.setImplicitParam();
      }

      // read the data from the default parameter
      //
      if (!parser.read(buffer, sof_a, parser.getEntry(sof_a, pname))) {
	return false;
      }
    }
    else {

      // we are already positioned correctly, just read
      //
      if (!parser.read(buffer, sof_a, size_a)) {
	return false;
      }
    }

    // assign the value
    //
    buffer.trim();
    assign(buffer);
  }

  // binary read, very simple
  //
  else {

    // make sure we read data properly
    //
    byte8 val;
    if (sof_a.read(&val, sizeof(val), 1) != 1) {
      return false;
    }
    value_d = (bool8)val;
  }
  
  // exit gracefully
  //
  return true;
}
