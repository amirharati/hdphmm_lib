// file: $isip/class/io/Sof/sof_04.cc
// version: $Id: sof_04.cc 6679 2001-04-16 15:23:32Z duncan $
//

// isip include files
//
#include "Sof.h"
#include <Console.h>

// method: open
//
// arguments:
//  const SysString& fname: (input) filename
//  File::MODE mode: (input) access mode
//  File::TYPE type: (input) type of file (text, or binary)
//
// return: a bool8 value indicating status
//
// this method opens an sof file
//
bool8 Sof::open(const SysString& fname_a, File::MODE mode_a,
		  File::TYPE type_a) {

  // check if the file is already open
  //
  if (fp_d.isOpen()) {
    Error::handle(name(), L"open", Error::FILE_REOPEN,
		  __FILE__, __LINE__, Error::WARNING);
    return false;
  }
  
  // assign the filename
  //
  name_d.assign(fname_a);

  // expand the filename
  //
  if (!Integral::expandName(expanded_name_d, name_d)) {
    SysString output(L"File: ");
    output.concat(name_d);
    output.concat(L"\n");
    Error::handle(name(), L"open", Error::FILENAME_EXPAND, __FILE__, __LINE__,
		  Error::WARNING, output);
    name_d.clear();
    expanded_name_d.clear();
    return false;
  }
  
  if (debug_level_d > Integral::BRIEF) {
    name_d.debug(L"<Sof::open> name_d");
    expanded_name_d.debug(L"<Sof::open> expanded_name_d");
  }
  
  // save the type
  //
  file_type_d = type_a;
  
  // initialize the position
  //
  if (type_a == File::BINARY) {
    cur_pos_d = 0;
  }
  
  // if read only, call openRead
  //
  if (mode_a == File::READ_ONLY) {
    return openRead();
  }
  
  // call open write (which calls read if necessary)
  //
  return openWrite(mode_a);
}

// method: close
//
// arguments: none
//
// return: a bool8 value indicating status
//
// this method closes an sof file.
//
bool8 Sof::close() {

  // update the file if necessary
  //
  if (fp_d.isWritable()) {
    if (!update()) {
      
      // only error if we aren't exiting
      //
      if (!Error::isExiting()) {
	return Error::handle(name(), L"close", ERR_UPDATE, __FILE__, __LINE__);
      }
    }
  }

  // if we are in the middle of a partial write, warn and stop
  //
  if (partial_write_d) {

    // only error if we aren't exiting
    //
    if (!Error::isExiting()) {
      return Error::handle(name(), L"close", ERR, __FILE__, __LINE__);
    }
    stopPartialWrite();
  }

  // if we are in the middle of a partial read, warn and stop
  //
  if (partial_read_d) {

    // only error if we aren't exiting
    //
    if (!Error::isExiting()) {
      return Error::handle(name(), L"close", ERR, __FILE__, __LINE__);
    }
    stopPartialRead();
  }

  
  // free resources
  //
  if (!cleanUp()) {

    // no cleanup necessary, but only error if we aren't exiting
    //
    if (!Error::isExiting()) {
      return Error::handle(name(), L"close", Error::RELEASE, __FILE__,
			   __LINE__, Error::WARNING);
    }
  }
  
  // exit gracefully
  //
  return true;
}

// method: openWrite
//
// arguments:
//  File::MODE access_mode: (input) what mode to open
//
// return: a bool8 value indicating status
//
// this method opens a file for write access
//
bool8 Sof::openWrite(File::MODE access_mode_a) {
  
  bool8 new_file = false;
  
  // open the file as a standard Unix stream
  //
  if (access_mode_a == File::WRITE_ONLY) {

    // note: WRITE_PLUS is used for WRITE_ONLY to allow for index
    // manipulation. the user is kept from reading a write only file
    // through software.
    //
    if (!fp_d.open(expanded_name_d, File::WRITE_PLUS)) {
      Error::handle(name(), L"openWrite", Error::IO, __FILE__,
		    __LINE__, Error::WARNING);
      cleanUp();
      return false;
    }
    new_file = true;
    
  }
  else if (access_mode_a == File::WRITE_PLUS) {
    
    if (!fp_d.open(expanded_name_d, File::WRITE_PLUS)) {
      Error::handle(name(), L"openWrite", Error::IO, __FILE__, __LINE__,
		    Error::WARNING);
      cleanUp();
      return false;
    }
    new_file = true;
  }
  else if (access_mode_a == File::READ_PLUS) {
    
    if (!fp_d.open(expanded_name_d, File::READ_PLUS)) {
      Error::handle(name(), L"openWrite", Error::IO, __FILE__, __LINE__,
		    Error::WARNING);
      cleanUp();
      return false;
    }
  }
  else {

    // invalid mode
    //
    return Error::handle(name(), L"openWrite", Error::ARG, __FILE__, __LINE__);
  }
  
  // grab a lock
  //
  if (!disable_lock_d) {
    if (!fp_d.lock(lock_retry_d, lock_delay_d)) {
      Error::handle(name(), L"openWrite", Error::FILE_LOCK, __FILE__, __LINE__,
		    Error::WARNING);
      cleanUp();
      return false;
    }
  }
  
  // if the file exists, read it in
  //
  if (!new_file) {

    // make sure it is an Sof file
    //
    if (!isSof()) {
      Error::handle(name(), L"openWrite", ERR_NOTSOF, __FILE__, __LINE__,
		    Error::WARNING);
      cleanUp();
      return false;
    }
    
    // load the index
    //
    if (file_type_d == File::TEXT) {
      return openReadText();
    }
    else if (file_type_d == File::BINARY) {
      return openReadBinary();
    }
    else {
      Error::handle(name(), L"openWrite", ERR_NOTSOF, __FILE__, __LINE__,
		    Error::WARNING);
      cleanUp();
      return false;
    }
  }
  else {

    // set the class name and version strings to default values
    //
    cname_d.assign(CLASS_NAME);
    version_d.assign(VERSION);
    fp_d.setBMode(File::NATIVE);
    
    // update the header
    //
    if (!update()) {
      return Error::handle(name(), L"openWrite", ERR_UPDATE,
			   __FILE__, __LINE__);
    }
    
    // set the end_of_data pointer to the end_of_header_d, as we have no data.
    //
    end_of_data_d = end_of_header_d;
  }
  
  // exit gracefully
  //
  return true;
}

// method: openRead
//
// arguments: none
//
// return: a bool8 value indicating status
//
// this method opens a file for read only access.
//
bool8 Sof::openRead() {

  // open the file as a standard Unix stream
  //
  if (!fp_d.open(expanded_name_d, File::READ_ONLY)) {
    Error::handle(name(), L"openRead", Error::FILE_NOTFND,
		  __FILE__, __LINE__, Error::WARNING);
    cleanUp();
    return false;
  }

  // is it an Sof file
  //
  if (!isSof()) {
    Error::handle(name(), L"openRead", ERR_NOTSOF, __FILE__,
		  __LINE__, Error::WARNING);
    cleanUp();
    return false;
  }

  // load the index
  //
  if (file_type_d == File::TEXT) {
    return openReadText();
  }
  else if (file_type_d == File::BINARY) {
    return openReadBinary();
  }

  // exit ungracefully
  //
  Error::handle(name(), L"openRead", ERR_NOTSOF, __FILE__, __LINE__,
		Error::WARNING);
  cleanUp();
  return false;
}

// method: openReadIndexText
//
// arguments: none
//
// return: a bool8 value indicating status
//
// this method parses a text sof file, reading the index
//
bool8 Sof::openReadIndexText() {

  // declare buffers for parsing an object entry
  //
  SysString buf(SysString::MAX_LENGTH);
  SysString object_name(SofSymbolTable::MAX_SYM_LENGTH);

  int32 object_sym = SofSymbolTable::NO_SYMB;
  int32 object_tag = SofList::NO_TAG;

  int32 last_sym = SofSymbolTable::NO_SYMB;
  int32 last_tag = SofList::NO_TAG;
  
  bool8 previous = false;
  
  int32 cur_line_pos = ftell();

  int32 data_pos = -1;

  // loop over the entire file
  //
  while (fp_d.get(buf)) {

    // is this line a label?
    //
    if (parseLabel(object_name, object_tag, buf)) {
      
      if (object_tag == FREE_TAG) {
	
	// we have a tag with no explicitly set tag number. set the
	// number
	//
	object_tag = implicit_count_d++;
	
	// check for overflow
	//
	if (implicit_count_d > IMPLICIT_END) {
	  Error::handle(name(), L"openReadIndexText", ERR_IMPLIC, __FILE__,
			__LINE__, Error::WARNING);
	  cleanUp();
	  return false;
	}
      }
      else if (object_tag <= IMPLICIT_END) {
	Error::handle(name(), L"openReadIndexText", ERR_TAG, __FILE__,
		      __LINE__, Error::WARNING);
      }
    
      // grab the object position. this will probably need to be
      // extended if we have anything but text in the label.
      //
      int32 object_pos = ftell() - buf.length() - 1;

      // get the symbol table index for the name
      //
      object_sym = table_d.add(object_name);
      
      // add the object to the index
      //
      if (!index_d.add(object_sym, object_tag, object_pos, (int32)-1)) {
	Error::handle(name(), L"openReadIndexText", SofList::ERR_ADD,
		      __FILE__, __LINE__, Error::WARNING);
	cleanUp();
	return false;
      }
      
      // now we set the size of the previous entry
      //
      if (previous) {

	// find the previous entry
	//
	if (!index_d.find(last_sym, last_tag)) {
	  return Error::handle(name(), L"openReadIndexText", Error::MEM,
			       __FILE__, __LINE__);
	}

	// set the size
	//
	index_d.setSize(cur_line_pos - data_pos);
      }

      // set the last values for the next pass
      //
      last_sym = object_sym;
      last_tag = object_tag;
      previous = true;

      // data_pos will be used for size computation
      //
      data_pos = ftell();
    }
    
    // save the current line position for possible use in a size
    //
    cur_line_pos = ftell();
  }

  // set the size of the last object
  //
  if (previous) {

    // find the previous entry
    //
    if (!index_d.find(last_sym, last_tag)) {
      return Error::handle(name(), L"openReadIndexText", Error::MEM,
			   __FILE__, __LINE__);
    }

    // set the size
    //
    index_d.setSize(cur_line_pos - data_pos);
  }
    
  // exit gracefully
  //
  return true;
}

// method: openReadIndexBinary
//
// arguments: none
//
// return: a bool8 value indicating status
//
// this method open and reads the index from an sof file
//
bool8 Sof::openReadIndexBinary() {

  // seek to the end of data
  //
  if (!fseek(end_of_data_d, File::POS)) {
    return Error::handle(name(), L"openReadIndexBinary",
			 Error::SEEK, __FILE__, __LINE__);
  }
  
  // debug information
  //
  if (debug_level_d > Integral::BRIEF) {
    SysString output;
    output.assign((int32)ftell());
    output.insert(L"reading table from ", 0);
    Console::put(output);
  }

  // clear the checksum
  //
  cksm_d.clear(Integral::RETAIN);
  
  // read the symbol table
  //
  if (!readTable()) {
    Error::handle(name(), L"openReadIndexBinary", Error::IO,
		  __FILE__, __LINE__, Error::WARNING);
    cleanUp();
    return false;
  }
  
  // debug information
  //
  if (debug_level_d > Integral::BRIEF) {
    SysString output;
    output.assign((int32)ftell());
    output.insert(L"reading index from ", 0);
    Console::put(output);
  }
  
  // read the binary index
  //
  if (!readIndex()) {
    Error::handle(name(), L"openReadIndexBinary", Error::IO,
		  __FILE__, __LINE__, Error::WARNING);
    cleanUp();
    return false;
  }

  // make sure the checksum matches
  //
  uint16 checksum_computed = cksm_d.get();
  if (checksum_computed != file_checksum_d) {
    return Error::handle(name(), L"openReadIndexBinary", Checksum::ERR,
			 __FILE__, __LINE__, Error::WARNING);
    cleanUp();
    return false;
  }
  
  // exit gracefully
  //
  return true;
}
