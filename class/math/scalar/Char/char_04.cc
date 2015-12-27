// file: $isip/class/math/scalar/Char/char_04.cc
// version: $Id: char_04.cc 5167 2000-10-04 23:37:36Z picone $
//

// isip include files
//
#include "Char.h"
#include <Sof.h>
#include <SofParser.h>

// method: write
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
bool8 Char::write(Sof& sof_a, int32 tag_a, const String& name_a) const {

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
bool8 Char::writeData(Sof& sof_a, const String& pname_a) const {
  
  // if ascii, read in a line, else binary read
  //
  if (sof_a.isText()) {
    
    String output;
    
    // start with the assignment string
    //
    if (pname_a.length() > 0) {
      output.assign(pname_a);
      output.concat(L" = ");
    }

    // concatenate the value
    //
    String numeric;
    numeric.assign(L"\\ ");
    numeric(1) = value_d;
    output.concat(numeric);
    
    // if a parameter name was set, add a terminator and a newline
    //
    if (pname_a.length() > 0) {
      output.concat(L";\n");
    }

    // write the text string
    //
    if (!sof_a.puts(output)) {
      return false;
    }
  }

  // binary write, very simple
  //
  else {
    
    unichar val = (unichar)value_d;
    if (sof_a.write(&val, sizeof(unichar), 1) != 1) {
      return false;
    }
  }
  
  // exit gracefully
  //
  return true;
}
