// file: $isip/class/io/Sof/sof_08.cc
// version: $Id: sof_08.cc 5745 2000-12-05 17:50:46Z duncan $
//

// isip include files
//
#include "Sof.h"
#include <Console.h>
#include <SofParser.h>

// method: read
//
// arguments:
//  void* ptr: (input) buffer of data to read into
//  int32 size: (input) size (in bytes) of data type
//  int32 nitems: (input) maximum number of elements to read
//
// return: the number of elements read
//
// this is the read method for the Sof class
//
int32 Sof::read(void* ptr_a, int32 size_a, int32 nitems_a) {

  // check args
  //
  if ((ptr_a == NULL) || (size_a < 1) || (nitems_a < 1)) {
    Error::handle(name(), L"read", Error::ARG, __FILE__, __LINE__);
    return (int32)-1;
  }

  // check range
  //
  int32 obj_size = index_d.getSize();

  if ((obj_size < 0) || (cur_data_d < 0)) {
    Error::handle(name(), L"read", SofList::ERR, __FILE__, __LINE__);
  }
  
  int32 cur_pos = ftell();
  
  if ((cur_pos < cur_data_d) || (cur_pos > (cur_data_d + obj_size))) {
    Error::handle(name(), L"read", ERR_RANGE, __FILE__, __LINE__);
  }
  
  // if the nitems is too large, truncate to end of object
  //
  if (((size_a * nitems_a) + cur_pos) > (cur_data_d + obj_size)) {
    
    nitems_a = (cur_data_d + obj_size - cur_pos) / size_a;
  }
  
  // call the private method
  //
  return fread(ptr_a, size_a, nitems_a);
}

// method: write
//
// arguments:
//  const void* ptr: (input) buffer of data to write
//  int32 size: (input) size (in bytes) of data type
//  int32 nitems: (input) number of elements to write
//
// return: the number of elements written
//
// this is the write method for the Sof class
//
int32 Sof::write(const void* ptr_a, int32 size_a, int32 nitems_a) {

  // check args
  //
  if ((ptr_a == NULL) || (size_a < 1) || (nitems_a < 1)) {
    Error::handle(name(), L"write", Error::ARG, __FILE__, __LINE__);
    return (int32)-1;
  }

  // check range
  //
  int32 obj_size = index_d.getSize();
  
  if ((obj_size < 0) || (cur_data_d < 0)) {
    Error::handle(name(), L"write", SofList::ERR, __FILE__, __LINE__);
  }
  
  int32 cur_pos = ftell();

  // check range lower bound
  //
  if (cur_pos < cur_data_d) {
    Error::handle(name(), L"write", ERR_RANGE, __FILE__, __LINE__);
  }

  // if the object size is specified, restrict it
  //
  if ((obj_size != ANY_SIZE) &&
      ((cur_pos + size_a * nitems_a) > (cur_data_d + obj_size))) {
    Error::handle(name(), L"write", ERR_RANGE, __FILE__, __LINE__);
  }

  // call the private function
  //
  return fwrite(ptr_a, size_a, nitems_a);
}

// method: gets
//
// arguments:
//  SysString& str: (output) string of data
//  int32 size: (input) maximum number of bytes to read
//
// return: a bool8 value indicating status
//
// this is the fgets method for the SOF class. arguments and return
// values are the same.
//
bool8 Sof::gets(SysString& str_a, int32 size_a) {

  // check file open and mode
  //
  if (!fp_d.isReadable()) {
    return Error::handle(name(), L"gets", Error::READ_CLOSED,
			 __FILE__, __LINE__);
  }
  
  // check args
  //
  if (size_a < 1) {
    return Error::handle(name(), L"gets", Error::ARG, __FILE__, __LINE__);
  }

  // check range
  //
  int32 obj_size = index_d.getSize();

  if ((obj_size < 0) || (cur_data_d < 0)) {
    return Error::handle(name(), L"gets", SofList::ERR, __FILE__, __LINE__);
  }
  
  int32 cur_pos = ftell();

  // make sure there are bytes left to read
  //
  if ((cur_data_d + obj_size) == cur_pos) {
    return false;
  }

  // make sure we are not out of range
  //
  if ((cur_pos < cur_data_d) || (cur_pos > (cur_data_d + obj_size))) {
    return Error::handle(name(), L"gets", ERR_RANGE, __FILE__, __LINE__);
  }
  
  // if the size is too large, truncate to end of object. the +1 is
  // there to allow space for the terminal null character that gets
  // will include in the count.
  //
  if ((size_a + cur_pos) > (cur_data_d + obj_size)) {
    size_a = cur_data_d + obj_size - cur_pos + 1;
  }
  
  // the actual system call
  //
  if (!fp_d.get(str_a, size_a)) {
    return false;
  }
  
  // no position should be saved for text mode
  //
  if (isText()) {
    return true;
  }

  // save the position
  //
  cur_pos_d = fp_d.tell();

  // exit gracefully
  //
  return true;
}

// method: puts
//
// arguments:
//  const SysString& str: (output) string of data
//
// return: a bool8 value indicating status
//
// this is the fputs method for the Sof class. 
//
bool8 Sof::puts(const SysString& str_a) {

  // check file open and mode
  //
  if (!fp_d.isWritable()) {
    return Error::handle(name(), L"puts", Error::WRITE_CLOSED,
			 __FILE__, __LINE__);
  }

  // check range
  //
  int32 obj_size = index_d.getSize();

  if (cur_data_d < 0) {
    return Error::handle(name(), L"puts", SofList::ERR, __FILE__, __LINE__);
  }
  
  int32 cur_pos = ftell();
  
  if ((cur_pos < cur_data_d) ||
      ((obj_size >= 0) && (cur_pos >= (cur_data_d + obj_size)))) {
    return Error::handle(name(), L"puts", ERR_RANGE, __FILE__, __LINE__);
  }
  
  // if the size is too large, truncate to end of object
  //
  if ((obj_size >= 0) &&
      ((cur_pos + str_a.length()) > (cur_data_d + obj_size))) {

    int32 size = cur_data_d + obj_size - cur_pos;

    unichar temp = str_a(size);
    const_cast<unichar&>(str_a(size)) = (unichar)NULL;

    // write the truncated string
    //
    if (!fp_d.put(str_a)) {
      return Error::handle(name(), L"puts", Error::WRITE, __FILE__, __LINE__,
			   Error::WARNING);
    }
    const_cast<unichar&>(str_a(size)) = temp;
  }
  else {

    // write the string
    //
    if (!fp_d.put(str_a)) {
      return Error::handle(name(), L"puts", Error::WRITE, __FILE__, __LINE__,
			   Error::WARNING);
    }
  }

  if (isText()) {
    return true;
  }

  // for binary mode, save the size
  //
  cur_pos_d = fp_d.tell();
  return true;
}

// method: fread
//
// arguments:
//  void* ptr: (input) buffer of data to read into
//  int32 size: (input) size (in bytes) of data type
//  int32 nitems: (input) maximum number of elements to read
//
// return: the number of elements read
//
// this is the private fread method. it performs byte swapping, but
// disables range checking. use this method within Sof, the main read
// & write methods are meant to be used for reading and writing objects.
//
int32 Sof::fread(void* ptr_a, int32 size_a, int32 nitems_a) {
  
  // check file open and mode
  //
  if (!fp_d.isReadable()) {
    Error::handle(name(), L"fread", Error::READ_CLOSED, __FILE__, __LINE__);
    return (int32)-1;
  }
  
  // check args
  //
  if ((ptr_a == NULL) || (size_a < 1) || (nitems_a < 1)) {
    Error::handle(name(), L"fread", Error::ARG, __FILE__, __LINE__);
    return (int32)-1;
  }

  // output the debug information
  //
  if (debug_level_d == Integral::ALL) {
    SysString numeric;
    SysString output(200);
    numeric.assign((int32)nitems_a);
    output.assign(L"freading ");
    output.concat(numeric);
    output.concat(L" ");
    numeric.assign((int32)size_a);
    output.concat(numeric);
    output.concat(L" byte blocks");
    Console::put(output);
  }
  
  // the actual system call
  //
  int32 n = fp_d.read(ptr_a, size_a, nitems_a);

  // increment position
  //
  cur_pos_d += (n * size_a);
  
  // exit gracefully
  //
  return n;
}

// method: fwrite
//
// arguments:
//  const void* ptr: (input) buffer of data to write
//  int32 size: (input) size (in bytes) of data type
//  int32 nitems: (input) number of elements to write
//
// return: the number of elements written
//
// this is the private fwrite method. it performs byte swapping, but
// disables range checking. use this method within Sof, the main read
// & write methods are meant to be used for reading and writing objects.
//
int32 Sof::fwrite(const void* ptr_a, int32 size_a, int32 nitems_a) {

  // check file open and mode
  //
  if (!fp_d.isReadable()) {
    Error::handle(name(), L"fwrite", Error::WRITE_CLOSED,
		  __FILE__, __LINE__);
    return (int32)-1;
  }

  // check args
  //
  if ((ptr_a == NULL) || (size_a < 1) || (nitems_a < 1)) {
    Error::handle(name(), L"fwrite", Error::ARG, __FILE__, __LINE__);
    return (int32)-1;
  }

  // output debug information
  //
  if (debug_level_d == Integral::ALL) {
    SysString numeric;
    SysString output(200);
    numeric.assign((int32)nitems_a);
    output.assign(L"fwriting ");
    output.concat(numeric);
    output.concat(L" ");
    numeric.assign((int32)size_a);
    output.concat(numeric);
    output.concat(L" byte blocks");
    Console::put(output);
  }
  
  // exit gracefully
  //
  int32 n = fp_d.write(ptr_a, size_a, nitems_a);

  // increment position
  //
  cur_pos_d += (n * size_a);
  
  // exit gracefully
  //
  return n;
}

// method: parseLabel
//
// arguments:
//  SysString& name: (output) object name
//  int32& tag: (output) object tag
//  const SysString& buf: (input) string which (possibly) contains a label
//  
// return: a bool8 value indicating status
//
// parse a string which possibly contains a label
//
bool8 Sof::parseLabel(SysString& name_a, int32& tag_a,
			const SysString& buf_a) {

  // initialize arguments
  //
  name_a.clear();
  tag_a = NO_TAG;

  // try to get the first delimiter char
  //
  int32 index0 = buf_a.firstNotSpace();
  int32 index1 = -1;
  if ((index0 < 0) || (buf_a(index0) != delimiter_d)) {
    return false;
  }

  // try to get the class name
  //
  index0 = buf_a.firstNotSpace(index0 + 1);
  index1 = buf_a.firstSpace(index0);
  if ((index0 < 0) || (index1 < 0)) {
    return false;
  }
  buf_a.substr(name_a, index0, index1 - index0);

  // try to get either the delimiter or the tag
  //
  index0 = buf_a.firstNotSpace(index1 + 1);
  if (index0 < 0) {
    return false;
  }
  
  // if this index is the last character on the line, then no tag was
  // specified.
  //
  if ((buf_a.firstNotSpace(index0+1) < 0) && (buf_a(index0) == delimiter_d)) {
    tag_a = FREE_TAG;
    return true;
  }

  // else this better have a tag specified
  //

  // grab the tag
  //
  SysString numeric;
  index1 = buf_a.firstSpace(index0);
  if (index1 < 0) {
    return false;
  }
  buf_a.substr(numeric, index0, index1 - index0);
  
  if (!numeric.get(tag_a)) {
    return false;
  }
  
  // pull the final delimiter off the end of the line
  //
  index0 = buf_a.firstNotSpace(index1 + 1);
  if (index0 < 0) {
    return false;
  }
  
  // the delimiter should be the last character on the line
  //
  if ((buf_a.firstNotSpace(index0+1) >= 0) || (buf_a(index0) != delimiter_d)) {
    return false;
  }
  
  // exit gracefully
  //
  return true;
}

// method: writeLabel
//
// arguments:
//  int32 name: (input) name to write
//  int32 tag: (input) tag to write
//  
// return: a bool8 value indicating status
//
// this method creates and writes a label to the file at the current
// position. only used in text mode.
// 
bool8 Sof::writeLabel(int32 name_a, int32 tag_a) {

  // get the name for this index
  //
  SysString name_str;
  if (!table_d.getSymbol(name_str, name_a)) {
    return Error::handle(name(), L"writeLabel", SofSymbolTable::ERR,
			 __FILE__, __LINE__);
  }
  
  // call the master function
  //
  return writeLabel(name_str, tag_a);
}

// method: writeLabel
//
// arguments:
//  const SysString& name: (input) name to write
//  int32 tag: (input) tag to write
//  
// return: a bool8 value indicating status
//
// this method creates and writes a label to the file at the current
// position. only used in text mode.
// 
bool8 Sof::writeLabel(const SysString& name_a, int32 tag_a) {
  
  // make sure we are not in partial write mode
  //
  if (partial_write_d) {
    return Error::handle(name(), L"writeLabel", ERR_PARTIAL, __FILE__,
			 __LINE__);
  }
  
  SysString output;

  // build the header string
  //
  output.assign(L"  ");
  output(0) = delimiter_d;
  
  // append the name
  //
  output.concat(name_a);

  // if the tag is not implicit, write it out
  //
  if (tag_a > IMPLICIT_END) {
    
    output.concat(L" ");
    SysString numeric;
    
    numeric.assign(tag_a);
    output.concat(numeric);
  }
  
  // append the final delimiter
  //
  output.concat(L"  \n");
  output(output.length() - 2) = delimiter_d;
  
  // write the label
  //
  if (!fp_d.put(output)) {
    return Error::handle(name(), L"writeLabel", Error::WRITE,
			 __FILE__, __LINE__);
  }

  // exit gracefully
  //
  return true;
}

// method: skipLabel
//
// arguments: none
//  
// return: a bool8 value indicating status
//
// skip over a label in a text Sof file.
//
bool8 Sof::skipLabel() {

  // the line will probably be less than this. if greater, no big
  // deal, it will grow automatically.
  //
  SysString dummy(128);

  // read in a line
  //
  if (!fp_d.get(dummy)) {
    return Error::handle(name(), L"skipLabel", Error::READ,
			 __FILE__, __LINE__);
  }
  
  // only test the string if debug level is set
  //
  if (debug_level_d < Integral::DETAILED) {
    return true;
  }
  
  // make sure the string read was a label
  //
  SysString temp_name;
  int32 temp_tag;
  
  if (!parseLabel(temp_name, temp_tag, dummy)) {
    return Error::handle(name(), L"skipLabel", ERR_READHD,
			 __FILE__, __LINE__);
  }
  
  // exit gracefully
  //
  return true;
}

// method: writeLabelPrefix
//
// arguments:
//  const SysString& param_name: (input) parameter name
//  
// return: a bool8 value indicating status
//
// if this is a text file and the parameter is not empty, write
// the parameter name and start bracket.
//
bool8 Sof::writeLabelPrefix(const SysString& param_name_a) {

  if (isText() && (param_name_a.length() > 0)) {

    // build a starting string
    //
    SysString start_str;
    start_str.assign(SofParser::DEF_BLOCKSTART_CHAR);
    start_str.concat(SofParser::NEWLINE_CHAR);

    // build a string with the parameter name
    //
    SysString output;
    output.assign(param_name_a);
    output.concat(SofParser::SPACE_CHAR);
    output.concat(SofParser::DEF_ASSIGNMENT_CHAR);
    output.concat(SofParser::SPACE_CHAR);

    // write the strings
    //
    puts(output);
    puts(start_str);
    
    increaseIndention();
  }
  
  // exit gracefully
  //
  return true;
}

// method: writeLabelSuffix
//
// arguments:
//  const SysString& param_name: (input) parameter name
//  
// return: a bool8 value indicating status
//
// if this is a text file and the parameter is not empty, write the parameter
// name and start bracket.
//
bool8 Sof::writeLabelSuffix(const SysString& param_name_a) {
  
  if (isText() && (param_name_a.length() > 0)) {
    
    // decrease indentation at the end of the object
    //
    decreaseIndention();

    // write the close brace and newline
    //
    SysString end_str;
    end_str.assign(SofParser::DEF_BLOCKSTOP_CHAR);          // L"}"
    SysString term;
    term.assign(SofParser::DEF_TERMINATOR_CHAR);
    term.concat(SofParser::NEWLINE_CHAR);                  // L";\n"
    end_str.concat(term);
    puts(end_str);
  }
  
  // exit gracefully
  //
  return true;
}
