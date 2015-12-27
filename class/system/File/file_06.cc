// file: $isip/class/system/File/file_06.cc
// version: $Id: file_06.cc 5293 2000-10-11 20:28:36Z duncan $
//

// system include files
//
#include <sys/stat.h>
#include <errno.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

// isip include files
//
#include "File.h"
#include <SysString.h>
#include <Console.h>

// method: remove
//
// arguments:
//  const unichar* filename: (input) file to delete
//
// return: a bool8 value indicating status
//
// delete the file from disk
//
bool8 File::remove(const unichar* filename_a) {
  
  SysString temp(filename_a);
  
  // call the master function
  //
  return remove(temp);
}

// method: remove
//
// arguments:
//  const SysString& filename: (input) file to delete
//
// return: a bool8 value indicating status
//
// delete the file from disk. note that the error handling calls are
// wrapped to not be executed if the error handler says we are already
// exiting. this is because the exit method attempts to delete
// temporary files and we don't want to get caught in an infinite
// loop.
//
bool8 File::remove(const SysString& filename_a) {
  
  SysString full_name;

  // see if we can expand the filename
  //
  if (!Integral::expandName(full_name, filename_a)) {
    if (!Error::isExiting()) {
      return Error::handle(name(), L"remove", Error::FILE_NOTFND,
			   __FILE__, __LINE__, Error::WARNING);
    }
  }

  // remove the file. we must use the :: here to override our
  // File::rename() to access the system libraries remove()
  //
  if (::remove((char*)(byte8*)full_name) != 0) {
    if (!Error::isExiting()) {
      return Error::handle(name(), L"remove", Error::SYS_CALL,
			   __FILE__, __LINE__, Error::WARNING);
    }
  }

  // exit gracefully
  //
  return true;
}

// method: rename
//
// arguments:
//  const unichar* old_filename: (input) file to delete
//  const unichar* new_filename: (input) move to this filename
//
// return: a bool8 value indicating status
//
// rename a file from old_filename to new_filename
//
bool8 File::rename(const unichar* old_filename_a,
		     const unichar* new_filename_a) {

  SysString temp0(old_filename_a);
  SysString temp1(new_filename_a);

  // call the master function
  //
  return rename(temp0, temp1);
}

// method: rename
//
// arguments:
//  const SysString& old_filename: (input) file to delete
//  const SysString& new_filename: (input) move to this filename
//
// return: a bool8 value indicating status
//
// rename a file from old_filename to new_filename
//
bool8 File::rename(const SysString& old_filename_a,
		     const SysString& new_filename_a) {

  SysString old_fn;
  SysString new_fn;
  
  // see if we can expand the filename
  //
  if (!Integral::expandName(old_fn, old_filename_a)) {
    return Error::handle(name(), L"rename", Error::FILE_NOTFND,
			 __FILE__, __LINE__, Error::WARNING);
  }
  
  if (!Integral::expandName(new_fn, new_filename_a)) {
    return Error::handle(name(), L"rename", Error::FILE_NOTFND,
			 __FILE__, __LINE__, Error::WARNING);
  }

  // rename the file. we must use the :: here to override our
  // File::rename() to access the system library's rename()
  //
  if (::rename((char*)(byte8*)old_fn, (char*)(byte8*)new_fn) != 0) {
    return Error::handle(name(), L"rename", Error::SYS_CALL,
			 __FILE__, __LINE__, Error::WARNING);
  }

  // exit gracefully
  //
  return true;
}

// method: exists
//
// arguments:
//  const unichar* filename: (input) filename on disk
//
// return: a bool8 value indicating status
//
// check if filename exists
//
bool8 File::exists(const unichar* filename_a) {
  
  SysString temp(filename_a);
  
  // call the master function
  //
  return exists(temp);
}

// method: exists
//
// arguments:
//  const SysString& filename: (input) filename on disk
//
// return: a bool8 value indicating status
//
// check if filename exists
//
bool8 File::exists(const SysString& filename_a) {
  
  // see if we can expand the filename
  //
  SysString fn;
  if (!Integral::expandName(fn, filename_a)) {
    return Error::handle(name(), L"exists", Error::FILE_NOTFND,
			 __FILE__, __LINE__, Error::WARNING);
  }
  
  // there are two ways we can do this. first, we can try to open the
  // file and see if it exists. secondly we can use the stat function
  // to find out information about the pathname. the latter is nice
  // since it also works on directories, but the former may be more
  // portable.
  //
#ifdef ISIP_FILE_OPEN_TEST

  // if we can open the file, then it exists. we have to do this by
  // hand instead of by calling the open method because we don't want
  // to error off.
  //
  file* fp;

  fp = ::fopen((char*)(byte8*)fn, sys_read_only);
  
  // if null file pointer, it doesn't exist
  //
  if (fp == (file*)null) {
    return false;
  }

  // close the file
  //
  ::fclose(fp);

#else

  // call the system function
  //
  struct stat buf;
  if (::stat((char*)(byte8*)fn, &buf) != 0) {

    // output debug message
    //
    if (debug_level_d > Integral::NONE) {
      SysString err_msg((byte8*)strerror(errno));
      SysString output(fn);
      output.concat(L": ");
      output.concat(err_msg);
      Console::put(output);
    }
    
    // return false
    //
    return false;
  }
  
#endif

  // exit gracefully
  //
  return true;
}

// method: mkdir
//
// arguments:
//  const unichar* dir_name: (input) dir_name on disk
//
// return: a bool8 value indicating status
//
// make the specified directory
//
bool8 File::mkdir(const unichar* dir_name_a) {
  
  SysString temp(dir_name_a);
  
  // call the master function
  //
  return mkdir(temp);
}

// method: mkdir
//
// arguments:
//  const SysString& dir_name: (input) dir_name on disk
//
// return: a bool8 value indicating status
//
// make the specified directory
//
bool8 File::mkdir(const SysString& dir_name_a) {
  
  // see if we can expand the dir_name
  //
  SysString dir;
  if (!Integral::expandName(dir, dir_name_a)) {
    return Error::handle(name(), L"mkdir", Error::FILE_NOTFND,
			 __FILE__, __LINE__, Error::WARNING);
  }
  
  // always create new directories with full permissions. this will,
  // of course, be modified by the users umask if they desire privacy.
  //
  mode_t mode = S_IRWXU | S_IRWXG | S_IRWXO;

  // call the system function
  //
  if (::mkdir((char*)(byte8*)dir, mode) != 0) {
    return Error::handle(name(), L"mkdir", Error::SYS_CALL,
			 __FILE__, __LINE__, Error::WARNING);
  }
  
  // exit gracefully
  //
  return true;
}

// method: rmdir
//
// arguments:
//  const unichar* dir_name: (input) directory to remove
//
// return: a bool8 value indicating status
//
// remove the specified directory
//
bool8 File::rmdir(const unichar* dir_name_a) {

  SysString temp(dir_name_a);
  
  // call the master function
  //
  return rmdir(temp);
}

// method: rmdir
//
// arguments:
//  const SysString& dir_name: (input) directory to remove
//
// return: a bool8 value indicating status
//
// remove the specified directory
//
bool8 File::rmdir(const SysString& dir_name_a) {

  // see if we can expand the dir_name
  //
  SysString dir;  
  if (!Integral::expandName(dir, dir_name_a)) {
    return Error::handle(name(), L"rmdir", Error::FILE_NOTFND,
			 __FILE__, __LINE__, Error::WARNING);
  }
  
  // call the system function rmdir
  //
  if (::rmdir((char*)(byte8*)dir) != 0) {
    return Error::handle(name(), L"rmdir", Error::SYS_CALL,
			 __FILE__, __LINE__, Error::WARNING);
  }
  
  // exit gracefully
  //
  return true;
}

// method: compare
//
// arguments:
//  const unichar* file1: (input) first filename
//  const unichar* file2: (input) second filename
//
// return: bool8 value
//
// compare two files on disk and test for binary equivalence
//
bool8 File::compare(const unichar* file1_a, const unichar* file2_a) {

  // make strings
  //
  SysString file1(file1_a);
  SysString file2(file2_a);

  // compare them
  //
  return compare(file1, file2);
}

// method: compare
//
// arguments:
//  const SysString& file1: (input) first filename
//  const SysString& file2: (input) second filename
//
// return: bool8 value
//
// compare two files on disk and test for binary equivalence
//
bool8 File::compare(const SysString& file1_a, const SysString& file2_a) {

  // declare local variables
  //
  File fp1;
  File fp2;

  // open the files
  //
  if (!fp1.open(file1_a, READ_ONLY, BINARY)) {
    return Error::handle(name(), L"compare", Error::IO, __FILE__, __LINE__);
  }

  if (!fp2.open(file2_a, READ_ONLY, BINARY)) {
    fp1.close();
    return Error::handle(name(), L"compare", Error::IO, __FILE__, __LINE__);
  }

  // declare buffers
  //
  static byte8 buf1[BUF_SIZE];
  static byte8 buf2[BUF_SIZE];

  // initialize variable so as to enter loop
  //
  int32 nread1 = 1;
  int32 nread2 = 0;
  
  // loop over the entire file
  //
  while (nread1 > 0) {

    nread1 = fp1.read(buf1, sizeof(byte8), BUF_SIZE);
    nread2 = fp2.read(buf2, sizeof(byte8), BUF_SIZE);

    // compare lengths
    //
    if (nread1 != nread2) {
      fp1.close();
      fp2.close();
      return false;
    }

    // compare the buffer contents
    //
    if (MemoryManager::memcmp(buf1, buf2, sizeof(byte8) * nread1) != 0) {
      fp1.close();
      fp2.close();
      return false;
    }
  }

  // close the files
  //
  fp1.close();
  fp2.close();
  
  // exit gracefully: they must be equal
  //
  return true;
}

// method: size
//
// arguments:
//  const unichar* name: (input) filename
//
// return: size of the file in bytes
//
// determine the size of the given file
//
int32 File::size(const unichar* name_a) {

  SysString temp(name_a);
  
  // call the master function
  //
  return size(temp);
}

// method: size
//
// arguments:
//  const SysString& name: (input) filename
//
// return: size of the file in bytes
//
// determine the size of the given file
//
int32 File::size(const SysString& name_a) {

  // local variables
  //
  File fp;
  int32 tsize = -1;

  // we don't want this file to be opened with retry
  //
  fp.setOpenRetry(0, 1);
  
  // see if we can open the file
  //
  if (fp.open(name_a)) {
    tsize = fp.size();
  }

  // close the file
  //
  fp.close();
  
  // exit gracefully
  //
  return tsize;
}
