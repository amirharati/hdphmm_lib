// file: $isip/class/math/scalar/MScalar/mscl_03.cc
// version: $Id: mscl_03.cc 6239 2001-01-26 20:42:25Z duncan $
//

// isip include files
//
#include "MScalarMethods.h"
#include "MScalar.h"
#include <typeinfo>

// method: read
//
// arguments:
//  MScalar<TIntegral, TSize>& this: (output) class operand
//  Sof& sof: (input) sof file object
//  int32 tag: (input) sof object instance tag
//  const String& name: (input) sof object instance name
//
// return: a bool8 indicating status
//
// this method has the object read itself from an Sof file
//
template<class TIntegral, class TSize>
bool8 MScalarMethods::read(MScalar<TIntegral, TSize>& this_a,
			     Sof& sof_a, int32 tag_a, const String& name_a) {

  // get the instance of the object from the Sof file
  //
  if (!sof_a.find(name_a, tag_a)) {
    return false;
  }

  // read the actual data from the sof file
  //
  if (!this_a.readData(sof_a)) {
    return false;
  }

  // exit gracefully
  //
  return true;
}

// method: readData
//
// arguments:
//  MScalar<TIntegral, TSize>& this: (output) class operand
//  Sof& sof: (input) sof file object
//  const String& pname: (input) sof object instance name
//  int32 size: (input) size in bytes of object (or FULL_SIZE)
//  bool8 param: (input) is the parameter specified?
//  bool8 nested: (input) is this nested?
//
// return: a bool8 indicating status
//
// this method has the object read itself from an Sof file. it assumes
// that the Sof file is already positioned correctly.
//
template<class TIntegral, class TSize>
bool8 MScalarMethods::readData(MScalar<TIntegral, TSize>& this_a,
				 Sof& sof_a, const String& pname_a,
				 int32 size_a, bool8 param_a,
				 bool8 nested_a) {

  // if ascii, read in a line, else binary read
  //
  if (sof_a.isText()) {
    
    SofParser parser;
    String buffer;
    String pname;

    // set the parser debug level
    //
    parser.setDebug(this_a.debug_level_d);
    
    // if param is false, this means implicit parameter
    //
    if (!param_a) {
      if (!parser.setImplicitParam()) {
	return Error::handle(name(), L"readData", Error::READ,
			     __FILE__, __LINE__, Error::WARNING);
      }
      if (!pname.assign(parser.implicitPname())) {
	return Error::handle(name(), L"readData", Error::READ,
			     __FILE__, __LINE__, Error::WARNING);
      }
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
      if (!parser.load(sof_a, size_a)) {
	return Error::handle(name(), L"readData", Error::READ,
			     __FILE__, __LINE__, Error::WARNING);
      }

      // if param is false, this means implicit parameter
      //
      if (!param_a) {
        if (!parser.setImplicitParam()) {
	  return Error::handle(name(), L"readData", Error::READ,
			     __FILE__, __LINE__, Error::WARNING);
	}
      }

      // read the data from the default parameter
      //
      if (!parser.read(buffer, sof_a, parser.getEntry(sof_a, pname))) {
        return Error::handle(name(), L"readData", Error::READ,
			     __FILE__, __LINE__, Error::WARNING);
      }
      
    }
    else {

      // we are already positioned correctly, just read
      //
      if (!parser.read(buffer, sof_a, size_a)) {
        return Error::handle(name(), L"readData", Error::READ,
			     __FILE__, __LINE__, Error::WARNING);
      }
      
    }

    // assign the value
    //
    buffer.trim();
    this_a.assign(buffer);
  }

  // binary read, very simple
  //
  else {

    // make sure we read data properly
    //
    TSize val;
    if (sof_a.read(&val, sizeof(val), 1) != 1) {
      return Error::handle(name(), L"readData", Error::READ,
			     __FILE__, __LINE__, Error::WARNING);
    }

    this_a.value_d = (TIntegral)val;
  }
  
  // exit gracefully
  //
  return true;
}

// declare classes that need to inherit MScalar
//
template bool8
MScalarMethods::read<ISIP_TEMPLATE_TARGET> 
(MScalar<ISIP_TEMPLATE_TARGET>&, Sof&, int32, const String&);

template bool8
MScalarMethods::readData<ISIP_TEMPLATE_TARGET> 
(MScalar<ISIP_TEMPLATE_TARGET>&, Sof&, const String&, int32, bool8, bool8);
