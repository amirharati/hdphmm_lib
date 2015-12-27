// file: $isip/class/io/Sof/sof_03.cc
// version: $Id: sof_03.cc 6679 2001-04-16 15:23:32Z duncan $
//

// isip include files
//
#include "Sof.h"

// method: assign
//
// arguments:
//  const Sof& sof: (input) file object from which to copy
//
// return: a bool8 value indicating status
//
// this method assigns input object to this
//
bool8 Sof::assign(const Sof& sof_a) {

  // only assign if they are of the same type
  //
  if (file_type_d != sof_a.file_type_d) {
    return Error::handle(name(), L"assign", Error::ARG, __FILE__, __LINE__);
  }
  
  // copy the symbol table
  //
  if (!table_d.assign(sof_a.table_d)) {
    return Error::handle(name(), L"assign", SofList::ERR_SYMB,
			 __FILE__, __LINE__);
  }

  // copy the list of items
  //
  if (!index_d.assign(sof_a.index_d)) {
    return Error::handle(name(), L"assign", SofList::ERR, __FILE__, __LINE__);
  }
  
  // exit gracefully
  //
  return true;
}

// method: clear
//
// arguments:
//  Integral::CMODE ctype: (input) clear mode
//
// return: a bool8 value indicating status
//
// this method can be used only for writable Sof files. it deletes
// all items from the sof file for all CMODE's
//
bool8 Sof::clear(Integral::CMODE ctype_a) {
  
  // we can not clear read only sof
  //
  if (!fp_d.isWritable()) {
    return Error::handle(name(), L"clear", Error::MOD_READONLY,
			 __FILE__, __LINE__);
  }

  // if we are in partial read more, error
  //
  if (partial_read_d) {
    return Error::handle(name(), L"clear", ERR, __FILE__, __LINE__);
  }
  
  // if we are in partial write more, error
  //
  if (partial_write_d) {
    return Error::handle(name(), L"clear", ERR, __FILE__, __LINE__);
  }

  // delete the index
  //
  if (!index_d.clear()) {
    return Error::handle(name(), L"clear", SofList::ERR, __FILE__, __LINE__);
  }
  
  // delete the symbol table
  //
  if (!table_d.clear()) {
    return Error::handle(name(), L"clear", SofSymbolTable::ERR,
			 __FILE__, __LINE__);
  }
  
  // truncate the file to be the length of the header
  //
  if (!fp_d.truncate(end_of_header_d)) {
    return Error::handle(name(), L"clear", Error::IO, __FILE__, __LINE__);
  }
  
  // seek to the beginning of the file (truncate does not do this)
  //
  if (!fseek(0, File::POS)) {
    return Error::handle(name(), L"clear", Error::SEEK, __FILE__, __LINE__);
  }
  
  // exit gracefully
  //
  return true;
}

// method: memSize
//
// arguments: none
//
// return: int32 value
//
// find the memory size of the Sof object in bytes
//
int32 Sof::memSize() {
  
  int32 size = 0;
  
  // the scalar data
  //
  size += name_d.memSize();
  size += expanded_name_d.memSize();
  size += sizeof(file_type_d);
  size += fp_d.memSize();
  size += sizeof(delimiter_d);
  size += sizeof(end_of_header_d);
  size += sizeof(end_of_data_d);
  size += sizeof(implicit_count_d);
  size += sizeof(cur_data_d);
  size += sizeof(disable_lock_d);
  size += sizeof(lock_retry_d);
  size += sizeof(lock_delay_d);
  size += table_d.memSize();
  size += index_d.memSize();
  size += cname_d.memSize();
  size += version_d.memSize();
  size += magic_d.memSize();
  size += sizeof(debug_level_d);

  // exit gracefully
  //
  return (int32)size;
}

// method: clearSpace
//
// arguments:
//  int32 nbytes: (input) number of bytes to clear
//
// return: a bool8 value indicating status
//
// clear out this space by filling in with all 0's
//
bool8 Sof::clearSpace(int32 nbytes_a) {

  // use a static buffer of clear bytes
  //
  static byte8 clear_buffer[BUFFER_SIZE];
  static bool8 clear_flag = false;
  
  if (!clear_flag) {
    MemoryManager::memset(clear_buffer, (int32)DELETE_CHAR_BINARY, BUFFER_SIZE);
    clear_flag = true;
  }
  
  static byte8 space_buffer[BUFFER_SIZE];
  static bool8 space_flag = false;
  if (!space_flag) {
    MemoryManager::memset(space_buffer, (int32)DELETE_CHAR_TEXT, BUFFER_SIZE);
    space_flag = true;
  }
  
  // loop through the space
  //
  int32 pass_size;
  byte8* buf = clear_buffer;
  
  if (isText()) {
    nbytes_a -= NEWLINE_LENGTH;
    buf = space_buffer;
  }
  
  for (int32 i = nbytes_a; i > 0; i -= BUFFER_SIZE) { 

    if (i > BUFFER_SIZE) {
      pass_size = BUFFER_SIZE;
    }
    else {
      pass_size = i;
    }

    // call the system function, we don't want any range checking or
    // byte swapping
    //
    if (fp_d.write(buf, sizeof(byte8), pass_size) != pass_size) {
      return Error::handle(name(), L"clearSpace", Error::WRITE,
			   __FILE__, __LINE__);
    }

    // for binary files, update position
    //
    if (isBinary()) {
      cur_pos_d += pass_size * sizeof(byte8);
    }
  }      
  
  if (isText()) {
    if (fp_d.write(NEWLINE_BUFFER, sizeof(byte8), NEWLINE_LENGTH)
	!= NEWLINE_LENGTH) {
      return Error::handle(name(), L"clearSpace", Error::WRITE,
			   __FILE__, __LINE__);
    }
  }
    
  // exit gracefully
  //
  return true;
}

// method: cleanUp
//
// arguments: none
//
// return: a bool8 value indicating status
//
// this method frees memory space associated with an Sof object.
//
bool8 Sof::cleanUp() {

  // general information about a file
  //
  name_d.clear();
  expanded_name_d.clear();
  file_type_d = File::TEXT;
  
  // unix I/O related variables
  //
  if (fp_d.isOpen()) {
    fp_d.close();
    cur_pos_d = DEF_POS;
  }

  // auxiliary information
  //
  delimiter_d = DEF_DELIMITER;
  end_of_header_d = (int32)-1;
  end_of_data_d = (int32)-1;
  cur_data_d = (int32)-1;
  
  // linked lists used to process the object index
  //
  freeIndex();
  
  // magic number processing
  //
  cname_d.clear();
  version_d.clear();
  magic_d.clear();

  // debugging parameters
  //
  debug_level_d = Integral::NONE;
  
  // implicit tag count
  //
  implicit_count_d = IMPLICIT_START;
  
  // exit gracefully
  //
  return true;
}

// method: freeIndex
//
// arguments: none
//
// return: a bool8 value indicating status
//
// this method frees memory space associated with an Sof index.
//
bool8 Sof::freeIndex() {

  // clear the table and list
  //
  if (!table_d.clear()) {

    // only error if we aren't exiting
    //
    if (!Error::isExiting()) {
      return Error::handle(name(), L"freeIndex", SofSymbolTable::ERR,
			   __FILE__, __LINE__);
    }
  }

  if (!index_d.clear()) {

    // only error if we aren't exiting
    //
    if (!Error::isExiting()) {
      return Error::handle(name(), L"freeIndex", SofList::ERR,
			   __FILE__, __LINE__);
    }
  }

  // exit gracefully
  //
  return true;
}
