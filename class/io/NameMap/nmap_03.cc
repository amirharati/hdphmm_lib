// file: $isip/class/io/NameMap/nmap_03.cc
// version: $Id: nmap_03.cc 6918 2001-05-03 15:50:52Z duncan $
//

// isip include files
//
#include "NameMap.h"

// method: readElementData
//
// arguments:
//  int32& value: (output) value read
//  Sof& sof: (input) sof file object
//  const SysString& pname: (input) parameter name
//  int32 size: (input) number of bytes in file
//  bool8 param: (input) is the parameter specified?
//  bool8 nested: (input) is this nested?
//
// return: a bool8 value indicating status
//
// read this element to an sof file. this method is very useful
// inside other class's readData methods.
//
bool8 NameMap::readElementData(int32& value_a, Sof& sof_a,
				 const SysString& pname_a,int32 size_a,
				 bool8 param_a, bool8 nested_a) const {

  // clear the argument
  //
  value_a = -1;
  
  // if ascii, read in a line, else binary read
  //
  if (sof_a.isText()) {
    
    SofParser parser;
    SysString buffer;
    SysString pname;

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
      
      if (!parser.load(sof_a, size_a)) {
	return Error::handle(name(), L"readElementData", Error::READ,
			     __FILE__, __LINE__, Error::WARNING);
      }
      
      // if param is false, this means implicit parameter
      //
      if (!param_a) {
        parser.setImplicitParam();
      }

      // read the data from the default parameter
      //
      if (!parser.read(buffer, sof_a, parser.getEntry(sof_a, pname_a))) {
	return Error::handle(name(), L"readElementData", Error::READ,
			     __FILE__, __LINE__, Error::WARNING);
      }
    }
    else {

      // we are already positioned correctly, just read
      //
      if (!parser.read(buffer, sof_a, size_a)) {
	return Error::handle(name(), L"readElementData", Error::READ,
			     __FILE__, __LINE__, Error::WARNING);
      }
    }

    value_a = getIndex(buffer);

    if (value_a < 0) {
      displayChoices(buffer);
      return Error::handle(name(), L"readElementData", Error::READ,
			   __FILE__, __LINE__, Error::WARNING);
    }

  }
  
  // for binary read the index directly
  //
  else {

    // read the checksum
    //
    uint16 tmp;
    if (sof_a.read(&tmp, sizeof(uint16), 1) != 1) {
      return Error::handle(name(), L"readElementData", Error::READ,
			   __FILE__, __LINE__, Error::WARNING);
    }

    // check that the checksum matches the current checksum
    //
    if (tmp != checksum_d) {
      return Error::handle(name(), L"readElementData", ERR_CHKSUM,
			   __FILE__, __LINE__, Error::WARNING);
    }

    // read the index
    //
    uint16 val;
    if (sof_a.read(&val, sizeof(uint16), 1) != 1) {
      return Error::handle(name(), L"readElementData", Error::READ,
			   __FILE__, __LINE__, Error::WARNING);
    }
    value_a = val;

    // check the value
    //
    if ((value_a < 0) || (value_a >= size_d)) {
      return Error::handle(name(), L"readElementData", Error::READ,
			   __FILE__, __LINE__, Error::WARNING);
    }
  }
  
  // exit gracefully
  //
  return true;
}

// method: writeElementData
//
// arguments:
//  Sof& sof: (input) sof file
//  const SysString& pname: (input) parameter name
//  uint16 index: (input) value to write
//
// return: a bool8 value indicating status
//
// write this element to an sof file. this method is very useful
// inside other class's writeData methods.
//
bool8 NameMap::writeElementData(Sof& sof_a, const SysString& pname_a,
				  uint16 index_a) const {

  
  // for a text file write out the name
  //
  if (sof_a.isText()) {
    SysString output;
    
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
    output.concat(getName(index_a));

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

  // for binary write the index and the checksum directly
  //
  else {

    // write the checksum
    //
    uint16 cksm = checksum_d;
    if (sof_a.write(&cksm, sizeof(uint16), 1) != 1) {
      return false;
    }

    // write the index
    //
    uint16 val = index_a;
    if (sof_a.write(&val, sizeof(uint16), 1) != 1) {
      return false;
    }
  }

  // exit gracefully
  //
  return true;
}

// method: elementSofSize
//
// arguments: none
//
// return: the size of the object in an Sof file
//
// this method computes the size needed to write an element of the
// NameMap to a binary Sof file.
//
int32 NameMap::elementSofSize() const {

  static int32 nbytes = sizeof(uint16) + sizeof(uint16);
  return nbytes;
}

// method: displayChoices
//
// arguments:
//  const SysString& choice: (input) bad_choice
//
// return: logical error status
//
// display to the Console the available NameMap choices
//
bool8 NameMap::displayChoices(const SysString& choice_a) const {

  SysString out;

  if (size_d < 1) {
    return Error::handle(name(), L"displayChoices", ERR, __FILE__, __LINE__);
  }


  out.assign(L"value >");
  out.concat(choice_a);
  out.concat(L"< is not valid (");

  out.concat(names_d[0]);
  
  for (int32 i = 1; i < size_d; i++) {
    out.concat(L", ");
    out.concat(names_d[i]);
  }

  out.concat(L")\n");
  
  return Console::put(out);
}
	    
