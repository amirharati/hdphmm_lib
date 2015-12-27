// file: $isip/class/shell/Sdb/sdb_05.cc
// version: $Id: sdb_05.cc 9236 2003-06-23 18:12:22Z gao $
//

// isip include files
//
#include "Sdb.h"

// method: eq
//
// arguments:
//  const Sdb& arg: (input) input object to test
//
// return: a bool8 value indicating status
//
// this method checks if two Sdb objects are the same
//
bool8 Sdb::eq(const Sdb& arg_a) const {

  // check the equality of class data 
  //
  if (!output_basename_d.eq(arg_a.output_basename_d)) {
    return false;
  }  
  if (!output_extension_d.eq(arg_a.output_extension_d)) {
    return false;
  }
  if (!output_suffix_d.eq(arg_a.output_suffix_d)) {
    return false;
  }
  if (!output_directory_d.eq(arg_a.output_directory_d)) {
    return false;
  }
  if (!dir_pres_d.eq(arg_a.dir_pres_d)) {
    return false;
  }
  if (lookahead_d != arg_a.lookahead_d) {
    return false;
  }
  if (!files_d.eq(arg_a.files_d)) {
    return false;
  }

  // exit gracefully
  //
  return true;  
}

// method: clear
//
// arguments:
//  Integral::CMODE cmode: (input) clear type
//
// return: a bool8 value indicating status
//
// this method clears the contents of the Sdb object
//
bool8 Sdb::clear(Integral::CMODE cmode_a) {

  // regardless of mode, close out and clear the stack
  //
  Sof* sof;
  while ((sof = fps_d.pop()) != (Sof*)NULL) {
    Long tag;
    if (tags_d.pop(&tag) == (Long*)NULL) {
      return Error::handle(name(), L"clear", ERR, __FILE__, __LINE__);
    }
    if (nums_d.pop(&tag) == (Long*)NULL) {
      return Error::handle(name(), L"clear", ERR, __FILE__, __LINE__);
    }
    sof->close();
    delete sof;
  }
  at_first_d = true;

  // if the mode is RETAIN, just clear the files but leave the
  // settings. note that we can't clear the list with cmode_a = RETAIN
  // mode because we want it emptied.
  //
  if (cmode_a == Integral::RETAIN) {

    queue_d.clear();
    files_d.clear();
  }
  
  // if the mode is not RETAIN, clear settings and the lists
  //
  else {
  
    // clear the file lists
    //
    queue_d.clear(cmode_a);
    files_d.clear(cmode_a);
  
    // release resources
    //
    output_directory_d.clear(cmode_a);
    dir_pres_d.clear(cmode_a);

    output_basename_d.assign(String::NULL_STRING);    
    output_extension_d.assign(Filename::DEF_EXTENSION);
    output_suffix_d.assign(Filename::DEF_SUFFIX);
  }

  // exit gracefully
  //
  return true;
}

// method: isSdb
//
// arguments:
//  const Filename& arg: (input) filename to test
//
// return: bool8 value indicating if this file is an Sdb file or not
//
// test to see if this file is an Sdb list or not
//
bool8 Sdb::isSdb(const Filename& arg_a, const String& object_name_a) {

  Sof sof;

  // if this is not an Sof file then it cannot be an Sdb file
  //
  if (!sof.open(arg_a)) {
    return false;
  }

  // is there at least one Sdb object in the file?
  //
  bool8 ret = isSdb(sof, object_name_a);

  // close the file
  //
  sof.close();

  // return the value
  //
  return ret;
}

// method: isSdb
//
// arguments:
//  const Sof& arg: (input) sof object to test
//
// return: bool8 value indicating if this file is an Sdb file or not
//
// test to see if this file is an Sdb list or not
//
bool8 Sdb::isSdb(Sof& arg_a, const String& object_name_a) {

  // is there at least one Sdb object in the file?
  //
  return (arg_a.first(object_name_a) != Sof::NO_TAG);
}
