// file: $isip/class/system/File/file_08.cc
// version: $Id: file_08.cc 9308 2003-09-26 15:47:59Z tang $
//

// isip include files
//
#include "File.h"
#include <SysString.h>

// method: substr
//
// arguments:
//  SysString& str: (output) the substring
//  int32 offset: (input) where to start copying from
//  int32 num_elements: (input) number of characters to copy
//
// return: a bool8 value indicating status
//
// return a substring of the current object
//
bool8 File::substr(SysString& str_a, int32 offset_a,
			  int32 num_elements_a) const {

  // make sure the file is open
  //
  if (!isOpen()) {
    Error::handle(name(), L"substr", ERR_NOTOPN, __FILE__, __LINE__);
    return Integral::NO_POS;
  }

  // check the mode
  //
  if (mode_d == WRITE_ONLY) {
    return Error::handle(name(), L"substr", Error::READ_CLOSED,
			 __FILE__, __LINE__);
  }

  // offset can't be negative
  //
  if (offset_a < 0) {
    offset_a = 0;
  }

  // get the number of bytes of a character
  //
  char mbchr_t[MB_CUR_MAX];
  int32 chr_bytes = wctomb(mbchr_t, str_a(0));

  // get the length (in characters) of the file
  //
  int32 file_size = size() / chr_bytes;
  
  // clear the string and exit ungracefully if offset is greater than
  // the length of the file or number of characters to copy is 0
  //
  if ((offset_a > file_size) || (num_elements_a == 0)) {
    str_a.clear(Integral::RESET);
    return false;
  }

  // number of characters to copy can't be negative
  //
  if (num_elements_a < 0) {
    num_elements_a = file_size - offset_a;
  }

  // seek to the offset and get the string
  //
  const_cast<File*>(this)->seek(offset_a * chr_bytes, POS);

  // the get() method reads only (num_elements_a - 1) characters
  // from the file, while the caller wants num_elements_a
  const_cast<File*>(this)->get(str_a, num_elements_a + 1);
  
  // exit gracefully
  //
  return true;
}

// method: firstStr
//
// arguments:
//  const unichar* str_a: (input) a pointer to the substring
//  int32 start: (input) where to start looking
//
// return: int32 index (in characters) within the file
//
// this method finds the first instance of str_a within the object
//
int32 File::firstStr(const unichar* str_a, int32 start_a) const {

  SysString temp(str_a);
  return firstStr(temp, start_a);
}

// method: firstStr
//
// arguments:
//  const SysString& str_a: (input) the substring
//  int32 start: (input) where to start looking
//
// return: int32 index (in characters) within the file
//
// this method finds the first instance of str_a within the object
//
int32 File::firstStr(const SysString& str_a, int32 start_a) const {

  // make sure the file is open
  //
  if (!isOpen()) {
    Error::handle(name(), L"firstStr", ERR_NOTOPN, __FILE__, __LINE__);
    return Integral::NO_POS;
  }

  // check the mode
  //
  if (mode_d == WRITE_ONLY) {
    return Error::handle(name(), L"firstStr", Error::READ_CLOSED,
			 __FILE__, __LINE__);
  }
  
  // check the arguments
  //
  if (!str_a.length()) {
    return Integral::NO_POS;
  }
  
  // get the number of bytes of a character
  //
  char mbchr_t[MB_CUR_MAX];
  int32 chr_bytes = wctomb(mbchr_t, str_a(0));
  
  // get the length (in characters) of the file
  //
  int32 file_size = size() / chr_bytes;

  // get the length (in characters) of the substring
  //
  int32 str_size = str_a.length();

  // compute the last position where the search should stop
  //
  int32 last_pos = file_size - str_size;

  // check the arguments
  //
  if (start_a > last_pos) {
    return Integral::NO_POS;
  }

  if (start_a == Integral::NO_POS) {
    start_a = 0;
  }

  // allocate a memory buffer to store a unichar string
  //
  unichar *chr_ptr = (unichar *)MemoryManager::newStatic((str_size + 1) * sizeof(unichar));
  if (!chr_ptr) {
    Error::handle(name(), L"firstStr", Error::NOMEM, __FILE__, __LINE__);
    return Integral::NO_POS;
  }
  
  // seek to the starting position
  //
  const_cast<File*>(this)->seek(start_a * chr_bytes, POS);

  // read str_size characters from file to the buffer
  //
  SysChar chr_t;
  for (int32 i = 0; i < str_size; i ++) {
    const_cast<File*>(this)->get(chr_t);
    chr_ptr[i] = unichar(chr_t);
  }
  chr_ptr[str_size] = (unichar)NULL;

  // assign the unichar buffer to a SysString object
  //
  SysString str_t;
  str_t.assign(chr_ptr);

  // compare two strings
  //
  while (!str_a.eq(str_t)) {
    if (eof()) {
      MemoryManager::deleteStatic(chr_ptr);
      return Integral::NO_POS;
    }

    // construct a new buffer of characters by shifting left for one
    // character int32 and reading the next character from file
    //
    MemoryManager:: memcpy(chr_ptr, chr_ptr + 1, (str_size - 1) * sizeof(unichar));
    const_cast<File*>(this)->get(chr_t);
    chr_ptr[str_size - 1] = unichar(chr_t);
    chr_ptr[str_size] = (unichar)NULL;
    str_t.assign(chr_ptr);
  }

  // release the memory buffer
  //
  MemoryManager::deleteStatic(chr_ptr);

  // return the position (in characters) where the first instance of the
  // substring is found within the file
  //
  return tell() / chr_bytes  - str_size;
}


