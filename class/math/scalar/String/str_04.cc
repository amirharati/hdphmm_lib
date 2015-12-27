// file: $isip/class/math/scalar/String/str_04.cc
// version: $Id: str_04.cc 4918 2000-09-20 19:07:44Z duncan $
//

// isip include files
//
#include "String.h"
#include <Sof.h>
#include <SofParser.h>

// method: write
//
// arguments:
//  Sof& sof: (input) sof file object
//  long tag: (input) sof object instance tag
//  const String& name: (input) sof object instance name
//
// return: a bool8 indicating status
//
// this method has the object read itself from an Sof file
//
bool8 String::write(Sof& sof_a, int32 tag_a, const String& name_a) const {

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
bool8 String::writeData(Sof& sof_a, const String& pname_a) const {

  // if ascii, read in a line, else binary read
  //
  if (sof_a.isText()) {
    
    String output;
    
    // start with the assignment string
    //
    if (pname_a.length() > 0) {
      output.assign(pname_a);
      output.concat(L" = \"");
    }
    else {
      output.concat(L"\"");
    }

    // concatenate the value
    //
    output.concat(*this);

    // end with a double quote
    //
    output.concat(L"\"");
    
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

    // first write the size
    //
    int32 len = length();
    if (sof_a.write(&len, sizeof(int32), 1) != 1) {
      return false;
    }

    // now write the characters
    //
    if (len > 0) {
      if (!sof_a.puts((*this))) {
	return false;
      }
    }
  }
  
  // exit gracefully
  //
  return true;
} 
