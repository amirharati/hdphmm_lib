// file: $isip/class/shell/Filename/fn_04.cc
// version: $Id: fn_04.cc 9209 2003-06-15 03:41:40Z picone $
//

// isip include files
//
#include "Filename.h"
#include <String.h>

// method: getBase
//
// arguments:
//  String& base: (output) the basename component of the filename
//
// return: a bool8 value indicating status
//
bool8 Filename::getBase(String& base_a) const {
  if (os_d == UNIX) {
    return getBaseUnix(base_a);
  }
  else {
    return Error::handle(name(), L"getBase",
                         Error::ARG, __FILE__, __LINE__);
  }
}

// method: getExt
//
// arguments:
//  String& ext: (output) the extension component of the filename
//
// return: a bool8 value indicating status
//
bool8 Filename::getExt(String& ext_a) const {
  if (os_d == UNIX) {
    return getExtUnix(ext_a);
  }
  else {
    return Error::handle(name(), L"getExt",
                         Error::ARG, __FILE__, __LINE__);
  }
}

// method: getDir
//
// arguments:
//  String& dir: (output) the directory component of the filename
//
// return: a bool8 value indicating status
//
bool8 Filename::getDir(String& dir_a) const {
  if (os_d == UNIX) {
    return getDirUnix(dir_a);
  }
  else {
    return Error::handle(name(), L"getDir",
                         Error::ARG, __FILE__, __LINE__);
  }
}

// method: getName
//
// arguments:
//  String& filename: (output) the filename (stripped of the directory)
//
// return: a bool8 value indicating status
//
bool8 Filename::getName(String& filename_a) const {
  if (os_d == UNIX) {
    return getNameUnix(filename_a);
  }
  else {
    return Error::handle(name(), L"getName",
                         Error::ARG, __FILE__, __LINE__);
  }
}

// method: getDirDelim
//
// arguments:
//  String& arg: (output) the string used to delimit a directory
//
// return: a bool8 value indicating status
//
bool8 Filename::getDirDelim(String& arg_a) const {
  if (os_d == UNIX) {
    return getDirDelimUnix(arg_a);
  }
  else {
    return Error::handle(name(), L"getDirDelim",
                         Error::ARG, __FILE__, __LINE__);
  }
}

// method: getFileDelim
//
// arguments:
//  String& arg: (output) the string used to delimit a file extension
//
// return: a bool8 value indicating status
//
bool8 Filename::getFileDelim(String& arg_a) const {
  if (os_d == UNIX) {
    return getFileDelimUnix(arg_a);
  }
  else {
    return Error::handle(name(), L"getFileDelim",
                         Error::ARG, __FILE__, __LINE__);
  }
}

//-----------------------------------------------------------------------------
//
// operating system specific versions: UNIX
//
//-----------------------------------------------------------------------------

// method: getBaseUnix
//
// arguments:
//  String& base: (output) the basename component of the filename
//
// return: a bool8 value indicating status
//
// this method is essentially equivalent to basename(). a filename
// of the form "/home/picone/rje/foo.text" will return "foo".
//
bool8 Filename::getBaseUnix(String& base_a) const {

  // position from where we have to start trimming
  //
  int32 start = lastStr(SLASH);

  // position where we stop trimming
  //
  int32 end = lastStr(DOT);

  // return the substring of value_d
  //
  substr(base_a, (start + 1), (end - start - 1));

  // exit gracefully
  //
  // exit gracefully
  //
  return true;  
}

// method: getExtUnix
//
// arguments:
//  String& ext: (output) the extension component of the filename
//
// return: a bool8 value indicating status
//
// find the extension in the filename.
//
// this method returns the filename's extension. on Unix, this means
// for "/home/picone/rje/foo.text" we return "text".
//
bool8 Filename::getExtUnix(String& ext_a) const {

  // total length of the string
  //
  int32 total_length = length();

  // position of the string dot
  //
  int32 index = lastStr(DOT);

  // return the substring of value_d
  //
  substr(ext_a, (index + 1), (total_length - index - 1));

  // exit gracefully
  //
  return true;  
}

// method: getDirUnix
//
// arguments:
//  String& dir: (output) the directory component of the filename
//
// return: a bool8 value indicating status
//
// this method returns the directory. on Unix, this means
// for "/home/picone/rje/foo.text" we return "/home/picone/rje".
//
bool8 Filename::getDirUnix(String& dir_a) const {

  // position of the string
  //
  int32 index = lastStr(SLASH);

  // if index is negative then the directory is the current directory
  //
  if (index < 0 ) {
    dir_a.clear();
  }

  // else find the corresponding directory
  //
  else {
    substr(dir_a, 0, index);
  }

  // exit gracefully
  //
  return true;  
}

// method: getNameUnix
//
// arguments:
//  String& filename: (output) the filename (stripped of the directory)
//
// return: a bool8 value indicating status
//
// this method returns the basename plus extension.
// for "/home/picone/rje/foo.text" we return "foo.text".
//
bool8 Filename::getNameUnix(String& filename_a) const {

  // length of the string value_d
  //
  int32 total_length = length();
  
  // position of the string slash
  //
  int32 index = lastStr(SLASH);
  
  // return the substring of value_d
  //
  substr(filename_a, (index + 1), (total_length - index - 1));

  return true;
}

// method: getDirDelimUnix
//
// arguments:
//  String& arg: (output) the string used to delimit a directory
//
// return: a bool8 value indicating status
//
// in Unix, this is a SLASH ("/").
//
bool8 Filename::getDirDelimUnix(String& arg_a) const {
  return arg_a.assign(SLASH);
}

// method: getFileDelimUnix
//
// arguments:
//  String& arg: (output) the string used to delimit a file extension
//
// return: a bool8 value indicating status
//
// in Unix, this is a DOT (".").
//
bool8 Filename::getFileDelimUnix(String& arg_a) const {
  return arg_a.assign(DOT);
}

//-----------------------------------------------------------------------------
//
// operating system specific versions: WINDOWS
//
//-----------------------------------------------------------------------------

// method: getBaseWin
//
// arguments:
//  String& base: (output) the basename component of the filename
//
// return: a bool8 value indicating status
//
bool8 Filename::getBaseWin(String& base_a) const {
  return false;
}

// method: getExtWin
//
// arguments:
//  String& ext: (output) the extension component of the filename
//
// return: a bool8 value indicating status
//
bool8 Filename::getExtWin(String& ext_a) const {
  return false;
}

// method: getDirWin
//
// arguments:
//  String& dir: (output) the directory component of the filename
//
// return: a bool8 value indicating status
//
bool8 Filename::getDirWin(String& dir_a) const {
  return false;
}

// method: getNameWin
//
// arguments:
//  String& filename: (output) the filename (stripped of the directory)
//
// return: a bool8 value indicating status
//
bool8 Filename::getNameWin(String& filename_a) const {
  return false;
}

// method: getDirDelimWin
//
// arguments:
//  String& arg: (output) the string used to delimit a directory
//
// return: a bool8 value indicating status
//
bool8 Filename::getDirDelimWin(String& arg_a) const {
  return false;
}

// method: getFileDelimWin
//
// arguments:
//  String& arg: (output) the string used to delimit an extension
//
// return: a bool8 value indicating status
//
bool8 Filename::getFileDelimWin(String& arg_a) const {
  return false;
}

//-----------------------------------------------------------------------------
//
// operating system specific versions: MACINTOSH
//
//-----------------------------------------------------------------------------

// method: getBaseMac
//
// arguments:
//  String& base: (output) the basename component of the filename
//
// return: a bool8 value indicating status
//
bool8 Filename::getBaseMac(String& base_a) const {
  return false;
}

// method: getExtMac
//
// arguments:
//  String& ext: (output) the extension component of the filename
//
// return: a bool8 value indicating status
//
bool8 Filename::getExtMac(String& ext_a) const {
  return false;
}

// method: getDirMac
//
// arguments:
//  String& dir: (output) the directory component of the filename
//
// return: a bool8 value indicating status
//
bool8 Filename::getDirMac(String& dir_a) const {
  return false;
}

// method: getNameMac
//
// arguments:
//  String& filename: (output) the filename (stripped of the directory)
//
// return: a bool8 value indicating status
//
bool8 Filename::getNameMac(String& filename_a) const {
  return false;
}

// method: getDirDelimMac
//
// arguments:
//  String& arg: (output) the string used to delimit a directory
//
// return: a bool8 value indicating status
//
bool8 Filename::getDirDelimMac(String& arg_a) const {
  return false;
}

// method: getFileDelimMac
//
// arguments:
//  String& arg: (output) the string used to delimit a file extension
//
// return: a bool8 value indicating status
//
bool8 Filename::getFileDelimMac(String& arg_a) const {
  return false;
}

