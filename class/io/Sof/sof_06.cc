// file: $isip/class/io/Sof/sof_06.cc
// version: $Id: sof_06.cc 6728 2001-04-20 19:11:20Z duncan $
//

// isip include files
//
#include "Sof.h"

// method: find
//
// arguments:
//  int32 name: (input) class name
//  int32 tag: (input) class tag
//
// return: an int32 value containing the position of the object in the index
//
// find an object in the index, making this the current object
//
bool8 Sof::find(int32 name_a, int32 tag_a) {
  
  // make sure we are not in partial write mode
  //
  if (partial_write_d || partial_read_d) {
    return Error::handle(name(), L"find", ERR_PARTIAL, __FILE__, __LINE__);
  }

  // find the object in the index
  //
  if (!index_d.find(name_a, tag_a)) {
    return false;
  }

  // position us at the beginning of the object's data
  //
  if (!seekData()) {
    return Error::handle(name(), L"find", Error::SEEK, __FILE__, __LINE__);
  }

  // exit gracefully
  //
  return true;
}

// method: first
//
// arguments:
//  const SysString& name: (input) object name
//
// return: int32 value indicating tag
//
// this method finds the first object of the specified name
//
int32 Sof::first(const SysString& name_a) {
  
  // make sure we are not in partial write mode
  //
  if (partial_write_d) {
    return Error::handle(name(), L"first", ERR_PARTIAL, __FILE__, __LINE__);
  }
  
  // find the index for the name
  //
  int32 index = table_d.getIndex(name_a);

  if (index == SofSymbolTable::NO_SYMB) {
    return SofList::NO_TAG;
  }

  // return the first tag for this name in the list
  //
  return index_d.first(index);
}

// method: last
//
// arguments:
//  const SysString& name: (input) object name
//
// return: int32 value indicating tag
//
// this method finds the last object of the specified name
//
int32 Sof::last(const SysString& name_a) {
  
  // make sure we are not in partial write mode
  //
  if (partial_write_d) {
    return Error::handle(name(), L"last", ERR_PARTIAL, __FILE__, __LINE__);
  }
  
  // find the index for the name
  //
  int32 index = table_d.getIndex(name_a);

  if (index == SofSymbolTable::NO_SYMB) {
    return SofList::NO_TAG;
  }

  // return the last tag for this name in the list
  //
  return index_d.last(index);
}

// method: seek
//
// arguments:
//  int32 offset: (input) byte offset
//  File::SEEK mode: (input) code for starting position
//
// return: a bool8 value indicating status
//
// seek to the specified location within the current object
//
bool8 Sof::seek(int32 offset_a, File::SEEK mode_a) {
  
  // make sure the current object pointer is set
  //
  if (cur_data_d < 0) {
    return Error::handle(name(), L"seek", SofList::ERR, __FILE__, __LINE__);
  }

  int32 seek_pos = 0;

  // figure out the end of this object
  //
  int32 obj_end = cur_data_d + index_d.getSize();
  if (obj_end < cur_data_d) {
    obj_end = -1;
  }

  // branch on modes
  //
  if (mode_a == File::POS) {
    seek_pos = cur_data_d + offset_a;
  }
  else if (mode_a == File::POS_PLUS_CUR) {
    seek_pos = ftell() + offset_a;
  }
  else if (mode_a == File::POS_PLUS_END) {
    
    // if size is unspecified, only restrict lower bound
    //
    if (obj_end < 0) {

      // if you try to seek before the start of the object's data,
      // restrict to the beginning of object's data
      //
      if ((ftell() + offset_a) > cur_data_d) {
	return fseek(offset_a, File::POS_PLUS_CUR);
      }
      else {
	return fseek(cur_data_d, File::POS);
      }
    }

    // size is specified, normal behavior
    //
    else {
      seek_pos = obj_end + offset_a;
    }
  }

  // invalid seek mode
  //
  else {
    return Error::handle(name(), L"seek", Error::ARG, __FILE__, __LINE__);
  }

  // restrict range
  //
  if (seek_pos > obj_end) {
    seek_pos = obj_end;
  }
  else if (seek_pos < cur_data_d) {
    seek_pos = cur_data_d;
  }

  // the actual system call
  //
  return fseek(seek_pos, File::POS);
}

// method: tell
//
// arguments: none
//
// return: int32 offset
//
// find the position within the current object
//
int32 Sof::tell() const {
    
  // make sure current object is set
  //
  if (cur_data_d < 0) {
    Error::handle(name(), L"tell", SofList::ERR, __FILE__, __LINE__);
    return (int32)-1;
  }
  int32 size = index_d.getSize();
  
  // find the absolute position
  //
  int32 pos = ftell();

  // subtract the range for the current object
  //
  pos -= cur_data_d;

  // check range
  //
  if ((pos < 0) || ((size > 0) && (pos > size))) {
    Error::handle(name(), L"tell", ERR_RANGE, __FILE__, __LINE__);
    return (int32)-1;
  }

  // return the value
  //
  return pos;
}

// method: ftell
//
// arguments: none
//
// return: int32 offset
//
// find the position in the file
//
int32 Sof::ftell() const {

  // for text mode, just make the system call
  //
  if (isText()) {
    return fp_d.tell();
  }

  // for binary mode, be more intelligent
  //
  if (cur_pos_d < 0) {
    return Error::handle(name(), L"ftell", Sof::ERR, __FILE__, __LINE__);
  }
  
  return cur_pos_d;
}

// method: fseek
//
// arguments:
//  int32 offset: (input) offset in bytes
//  File::SEEK whence: (input) where to seek from
//
// return: bool8 error status
//
// seek to the specified location in the file
//
bool8 Sof::fseek(int32 offset_a, File::SEEK whence_a) {

  // make the system call
  //
  if (!fp_d.seek(offset_a, whence_a)) {
    return Error::handle(name(), L"fseek", Error::SEEK, __FILE__, __LINE__);
  }
    
  // for text mode, that's it
  //
  if (file_type_d == File::TEXT) {
    return true;
  }

  // for testing purposes, remove for efficiency later
  //
  if (cur_pos_d < 0) {
    return Error::handle(name(), L"fseek", Error::INTERNAL_DATA, __FILE__,
			 __LINE__, Error::WARNING);
  }

  // just set current to offset_a
  //
  if (whence_a == File::POS) {
    cur_pos_d = offset_a;
  }

  // just increment current by offset_a
  //
  else if (whence_a == File::POS_PLUS_CUR) {
    cur_pos_d += offset_a;
  }

  // if we search from the end of file, no telling where we end up
  //
  else {
    cur_pos_d = fp_d.tell();
  }

  // exit gracefully
  //
  return true;
}

// method: seekDataText
//
// arguments: none
//
// return: a bool8 value indicating status
//
// seek to the data of the current object in an text file
//
bool8 Sof::seekDataText() {

  // for text, first seek to the position, then skip the label and flush
  //
  if ((!fseek(index_d.getPosition(), File::POS)) ||
      (!skipLabel())) {
    return Error::handle(name(), L"seekDataText", Error::SEEK,
			 __FILE__, __LINE__);
  }
  
  // set the current data pointer
  //
  cur_data_d = ftell();

  // exit gracefully
  //
  return true;
}

// method: seekDataBinary
//
// arguments: none
//
// return: a bool8 value indicating status
//
// seek to the data of the current object in a binary file
//
bool8 Sof::seekDataBinary() {

  // binary files are simple, just seek to position
  //
  if (!fseek(index_d.getPosition(), File::POS)) {
    return Error::handle(name(), L"seekDataBinary", Error::SEEK,
			 __FILE__, __LINE__);
  }

  // set the current data pointer
  //
  cur_data_d = ftell();
  
  // exit gracefully
  //
  return true;
}
