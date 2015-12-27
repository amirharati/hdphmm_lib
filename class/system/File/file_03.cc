// file: $isip/class/system/File/file_03.cc
// version: $Id: file_03.cc 6940 2001-05-07 18:53:36Z duncan $
//

// isip include files
//
#include "File.h"
#include <MemoryManager.h>
#include <SysChar.h>
#include <SysString.h>
 
// declare some static memory
//
static unichar* buf = (unichar*)NULL;
static int32 buf_len = 0;

// method: swap
//
// arguments:
//  File& arg: (input) source file pointer
//
// return: a bool8 value indicating status
//
// this swap method serves as File's assignment method. we don't
// ever want multiple file pointers on the same file, so if you
// assign a pointer to another the source loses it's data
//
bool8 File::swap(File& arg_a) {

  // save this object as temporary
  //
  FILE* tmp_fp = fp_d;
  MODE tmp_mode = mode_d;
  TYPE tmp_type = type_d;  
  bool8 tmp_lock = lock_d;
  BMODE tmp_byte_mode = byte_mode_d;
  bool8 tmp_byte_swap = byte_swap_d;
  int32 tmp_indent_level = indent_level_d;
  int32 tmp_line_wrap = line_wrap_d;
  int32 tmp_column_position = column_position_d;
  int32 tmp_open_retry = open_retry_d;
  int32 tmp_open_delay = open_delay_d;
  
  // copy over internal data from the other object into this object
  //
  fp_d = arg_a.fp_d;
  mode_d = arg_a.mode_d;
  type_d = arg_a.type_d;
  lock_d = arg_a.lock_d;
  byte_mode_d = arg_a.byte_mode_d;
  byte_swap_d = arg_a.byte_swap_d;
  indent_level_d = arg_a.indent_level_d;
  line_wrap_d = arg_a.line_wrap_d;
  column_position_d = arg_a.column_position_d;
  open_retry_d = arg_a.open_retry_d;
  open_delay_d = arg_a.open_delay_d;
  
  // copy temporary data into other object
  //
  arg_a.fp_d = tmp_fp;
  arg_a.mode_d = tmp_mode;
  arg_a.type_d = tmp_type;  
  arg_a.lock_d = tmp_lock;
  arg_a.byte_mode_d = tmp_byte_mode;
  arg_a.byte_swap_d = tmp_byte_swap;
  arg_a.indent_level_d = tmp_indent_level;
  arg_a.line_wrap_d = tmp_line_wrap;
  arg_a.column_position_d = tmp_column_position;
  arg_a.open_retry_d = tmp_open_retry;
  arg_a.open_delay_d = tmp_open_delay;
  
  // exit gracefully
  //
  return true;
}

// method: get
//
// arguments:
//  SysChar& chr: (output) a character being read
//  
// return: a bool8 value indicating status
//
// get a char from the file
//
bool8 File::get(SysChar& chr_a) {
  
  // null file pointer, error
  //
  if ((fp_d == (FILE*)NULL) || (mode_d == WRITE_ONLY)) {
    return Error::handle(name(), L"get", Error::READ_CLOSED,
			 __FILE__, __LINE__);
  }
  
  // read the character
  //
  unichar chr = SysString::isip_fgetwc(fp_d);
  
  // make sure this is not the WEOF
  //
  if ((wint_t)chr == (wint_t)WEOF) {
    
    // nothing has been read
    //
    return false;
  }
  
  // assign the value and return
  //
  return chr_a.assign(chr);
}

// method: get
//
// arguments:
//  SysString& str: (output) string of data read
//  int32 len: (input) maximum length to read
//  
// return: a bool8 value indicating status
//
// get a string from the file
//
bool8 File::get(SysString& str_a, int32 len_a) {
  
  // clear the output string
  //
  str_a.clear();

  // check the file pointer and the mode
  //
  if ((fp_d == (FILE*)NULL) || (mode_d == WRITE_ONLY)) {
    return Error::handle(name(), L"get", Error::READ_CLOSED,
			 __FILE__, __LINE__);
  }
  
  // increase buffer size if necessary
  //
  if (len_a > buf_len) {
    if (buf != (unichar*)NULL) {

      // unregister and delete the memory
      //
      MemoryManager::deleteStatic(buf);
    }
    buf_len = len_a;
    
    // allocate and register the memory
    //
    buf = (unichar*)MemoryManager::newStatic((buf_len + 1) * sizeof(unichar));
  }

  // clear out the buffer
  //
  MemoryManager::memset(buf, 0, (len_a + 1) * sizeof(unichar));
  
  // read the string
  //
  if (SysString::isip_fgetws(buf, len_a, fp_d) == (unichar*)NULL) {
    
    // nothing has been read
    //
    return false;
  }
  
  // assign the output buffer
  //
  str_a.assign(buf);

  // strip newlines from the end of the string
  //
  static SysString newline(L"\n");
  str_a.trimRight(newline);
  
  // exit gracefully
  //
  return true;
}

// method: memSize
//
// arguments: none
//  
// return: a int32 number
//
// return the memory size of the class in bytes
//
int32 File::memSize() const {

  // start with the file pointer size
  //
  int32 s = sizeof(fp_d);
  
  // add the size of each data member
  //
  s += sizeof(mode_d);
  s += sizeof(type_d);
  s += sizeof(lock_d);
  s += sizeof(byte_mode_d);
  s += sizeof(byte_swap_d);
  s += sizeof(indent_level_d);
  s += sizeof(line_wrap_d);
  s += sizeof(column_position_d);
  s += sizeof(open_retry_d);
  s += sizeof(open_delay_d);
    
  // return the size
  //
  return s;
}
