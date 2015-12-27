// file: $isip/class/numeric/Sigmoid/sigm_03.cc
// version: $Id: sigm_03.cc 6254 2001-01-29 23:10:53Z hamaker $
//

// isip include files
//
#include "Sigmoid.h"

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
bool8 Sigmoid::read(Sof& sof_a, int32 tag_a, const String& name_a) {

  // read the instance of the object from the Sof file
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
//  int32 size: (input) size in bytes of object (or full_size)
//  bool8 param: (input) is the parameter name in the file?
//  bool8 nested: (input) are we nested?
//
// return: a bool8 value indicating status
//
// this method has the object read itself from an Sof file. it assumes
// that the Sof file is already positioned correctly.
//
bool8 Sigmoid::readData(Sof& sof_a, const String& pname_a,
			  int32 size_a, bool8 param_a,
			  bool8 nested_a) {

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

  // get the gain factor
  //
  if (!gain_d.readData(sof_a, PARAM_GAIN,
			parser.getEntry(sof_a, PARAM_GAIN),
			false, false)) {
    return Error::handle(name(), L"readData", Error::READ,
			 __FILE__, __LINE__, Error::WARNING);
  }	    

  // get the slope
  //
  if (!slope_d.readData(sof_a, PARAM_SLOPE,
			parser.getEntry(sof_a, PARAM_SLOPE),
			false, false)) {
    return Error::handle(name(), L"readData", Error::READ,
			 __FILE__, __LINE__, Error::WARNING);
  }	    

  // get the xoffset
  //
  if (!xoffset_d.readData(sof_a, PARAM_XOFFSET,
			  parser.getEntry(sof_a, PARAM_XOFFSET),
			  false, false)) {
    return Error::handle(name(), L"readData", Error::READ,
			 __FILE__, __LINE__, Error::WARNING);
  }	    

  // get the yoffset
  //
  if (!yoffset_d.readData(sof_a, PARAM_YOFFSET,
			  parser.getEntry(sof_a, PARAM_YOFFSET),
			  false, false)) {
    return Error::handle(name(), L"readData", Error::READ,
			 __FILE__, __LINE__, Error::WARNING);
  }	    

  // exit gracefully
  //
  return true;
}
