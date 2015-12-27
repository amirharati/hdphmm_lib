// file: $isip/class/math/scalar/MScalar/mscl_04.cc
// version: $Id: mscl_04.cc 6807 2001-04-24 15:28:14Z peng $
//

// isip include files
//
#include "MScalarMethods.h"
#include "MScalar.h"
#include <typeinfo>

// method: write
//
// arguments:
//  const MScalar<TIntegral, TSize>& this: (output) class operand
//  Sof& sof: (input) sof file object
//  long tag: (input) sof object instance tag
//  const String& name: (input) sof object instance name
//
// return: a bool8 value indicating status
//
// this method has the object write itself to an Sof file
//
template<class TIntegral, class TSize>
bool8 MScalarMethods::write(const MScalar<TIntegral, TSize>& this_a,
			      Sof& sof_a, int32 tag_a, const String& name_a) {

  int32 obj_size;

  if (sof_a.isText()) {
    obj_size = Sof::ANY_SIZE;
  }
  else {
    obj_size = this_a.sofSize();
  }
  
  // put the object into the sof file's index
  //
  if (!sof_a.put(name_a, tag_a, obj_size)) {
    return false;
  }

  // exit gracefully
  //
  return this_a.writeData(sof_a);
}

// method: writeData
//
// arguments:
//  const MScalar<TIntegral, TSize>& this: (output) class operand
//  Sof& sof: (input) sof file object
//  const String& pname: (input) sof object instance name
//
// return: a bool8 value indicating status
//
// this method writes the object to the Sof file. it assumes that the
// Sof file is already positioned correctly.
//
template<class TIntegral, class TSize>
bool8 MScalarMethods::writeData(const MScalar<TIntegral, TSize>& this_a,
				  Sof& sof_a, const String& pname_a) {

  // if ascii, read in a line, else binary read
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
    numeric.assign(this_a.value_d);
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

    // make sure we write exactly 4 bytes
    //
    TSize val = (TSize)this_a.value_d;

    // range check the datatype
    //
    if (this_a.value_d != (TIntegral)val) {
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

// declare classes that need to inherit MScalar
//
template bool8
MScalarMethods::write<ISIP_TEMPLATE_TARGET> 
(const MScalar<ISIP_TEMPLATE_TARGET>&, Sof&, int32, const String&);

template bool8
MScalarMethods::writeData<ISIP_TEMPLATE_TARGET> 
(const MScalar<ISIP_TEMPLATE_TARGET>&, Sof&, const String&);
