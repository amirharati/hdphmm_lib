// file: $isip/class/shell/Filename/fn_05.cc
// version: $Id: fn_05.cc 9209 2003-06-15 03:41:40Z picone $
//

// isip include files
//
#include "Filename.h"

// method: transform
//
// arguments:
//  const String& new_dir: (input) new directory
//  const String& new_ext: (input) new extension for the filename
//  const String& new_suffix: (input) new suffix for the filename 
//  int32 dir_preserve: (input) number of subdirectories to preserve
//
// return: a bool8 value indicating status
//
// this method places the old file in a new directory with a new extension.
// a bit of complication is added with dir_pres. consider:
//
//  /home/picone/rje/foo.text
//
// if dir_pres == 0, new_directory="isip", new_ext="dat", then the
// result will be "/isip/foo.dat".
//
// if dir_pres == 1, new_directory="isip", new_ext="dat", then the
// result will be "/isip/rje/foo.dat".
//

bool8 Filename::transform(const String& new_dir_a, 
			    const String& new_ext_a,
			    const String& new_suffix_a,
			    int32 dir_preserve_a) {

  // fetch the OS-specific constants
  //
  String dir_delim;
  getDirDelim(dir_delim);

  String file_delim;
  getFileDelim(file_delim);

  // parse the existing name into pieces
  //
  String old_dir;
  getDir(old_dir);

  String old_base_name;
  getBase(old_base_name);

  String old_ext;
  getExt(old_ext);
    
  // operate on the new directory name if necessary
  //
  String mod_dir;
  preserveDirName(mod_dir, new_dir_a, old_dir, dir_preserve_a);

  // assign the new directory if the argument is not empty
  //
  if (mod_dir.length() > 0) {
    assign(mod_dir);
  }
  else {
    assign(old_dir);
  }

  // concat the new name
  //
  if (length() > 0) {
    concat(dir_delim);
  }
  concat(old_base_name);    

  // concat the new suffix if it is not empty
  //
  if (new_suffix_a.length() > 0) {
    concat(new_suffix_a);
  }

  // concat the new extension if it is not empty.
  // remember to insert a file delimiter
  //
  concat(file_delim);
  
  if (new_ext_a.length() > 0) {
    concat(new_ext_a);
  }
  else {
    concat(old_ext);
  }

  // exit gracefully
  //
  return true;  
}

// method: transformUniquely
//
// arguments: none
//
// return: a bool8 value indicating status
//
// this method replace the filename with a number at the end. (image_01.jpg)
//
bool8 Filename::transformUniquely() {

  // if the original file doesn't exist, return immediately
  //
  if (!File::exists(*this)) {
    return true;
  }

  // define the required strings
  //
  String filename;
  String extension;
  String directory;
  String number;

  // define a persistent scratch space
  //
  String tmp;

  // fetch the OS-specific constants
  //
  String dir_delim;
  getDirDelim(dir_delim);

  String file_delim;
  getFileDelim(file_delim);

  // get the directory, filename and extension of the current object
  //
  getDir(directory);
  getBase(filename);
  getExt(extension);

  // define a consistent permutation and concatenate it to the name:
  //  the name is of the form "...jjj/iii/foo_123.sof". we will build
  //  the first part in "this" and permute the last part.
  //
  assign(directory);

  if (directory.length() > 0) {
    concat(dir_delim);
  }

  concat(filename);
  concat(UNDERSCORE);

  // check if the filename already exists
  //
  bool8 flag_exists = false;
  int32 index = 0;

  while (!flag_exists) {

    // build a unique string
    //
    number.assign(index);

    // build a new filename
    //
    tmp.assign(*this);
    tmp.concat(number);
    tmp.concat(file_delim);
    tmp.concat(extension);

    // check if this exists
    //
    if (!File::exists(tmp)) {
      break;
    }
    else {
      index++;
    }
  }

  // build the final name
  //
  concat(number);
  concat(file_delim);
  concat(extension);
  
  // exit gracefully
  //
  return true;
}

// method: preserveDirName
//
// arguments:
//  String& mod_dir: (output) modified directory name
//  const String& new_dir: (input) proposed new directoy name
//  const String& old_dir: (input) existing directoy name
//  int32 dir_preserve: (input) number of subdirectories to preserve
//
// return: a bool8 value indicating status
//
// this method merges two directory names based on the value of dir_preserve.
//
bool8 Filename::preserveDirName(String& mod_dir_a,
				  const String& new_dir_a,
				  const String& old_dir_a,
				  int32 dir_preserve_a) {

  // fetch the OS-specific constants
  //
  String dir_delim;
  getDirDelim(dir_delim);

  // trim any trailing delimiters from old_dir and new_dir
  //
  SysString new_dir(new_dir_a);
  SysString old_dir(old_dir_a);

  new_dir.trimRight(dir_delim);
  old_dir.trimRight(dir_delim);

  // if the old_dir is empty, this is easy - just swap in the new dir
  //
  if (old_dir.length() == 0) {
    return mod_dir_a.assign(new_dir);
  }

  // if we don't need to preserve any part of the directory name,
  // this is easy
  //
  if (dir_preserve_a <= 0) {
    if (new_dir.length() > 0) {
      return mod_dir_a.assign(new_dir);
    }
    else {
      return mod_dir_a.assign(old_dir);      
    }      
  }

  // else, we must find the portion of the name that needs to be preserved.
  // we do this in several steps:
  //
  //  (1) count tokens in the directory name and make sure there are
  //      enough. if not, copy the old_name.
  //  (2) reverse index into the name and find the start point
  //  (3) copy it
  //

  // (1) make sure there are enough tokens
  //
  int32 num_tokens = old_dir.countTokens(dir_delim);  

  if (num_tokens < dir_preserve_a) {
    return mod_dir_a.assign(old_dir);
  }

  // (2) reverse index into the old name and find the start of the chunk
  //     to be preserved.
  //
  int32 pos = old_dir.length();

  for (int32 i = dir_preserve_a; i > 0; i--) {
    pos = old_dir.lastChr(dir_delim, pos - 1);
  }
  pos++;

  // (3) grab a substring
  //
  String preserve_path;
  int32 num_elem = old_dir.length() - pos;
  old_dir.substr(preserve_path, pos, num_elem);

  // (4) merge
  //
  mod_dir_a.assign(new_dir);
  mod_dir_a.concat(dir_delim);
  mod_dir_a.concat(preserve_path);  

  // exit gracefully
  //
  return true;
}

// method: buildPath
//
// arguments:
//  const String& path: (input) pathname to create
//
// return: a bool8 value indicating status
//
// this method builds all necessary subdirectories for specified path
//
bool8 Filename::buildPath(const String& path_a) {

  // if it already exists, we are done
  //
  if (File::exists(path_a)) {
    return true;
  }

  // get the directory name
  //
  Filename fn(path_a);
  String dir;
  fn.getDir(dir);

  // if the directory name is same as input path name, return error
  //
  if (dir.eq(path_a)) {
    return Error::handle(name(), L"buildPath", Error::ARG, __FILE__, __LINE__);
  }
  
  // recursively call buildPath to create parent
  //
  if (!buildPath(dir)) {
    return Error::handle(name(), L"buildPath", Error::ARG, __FILE__, __LINE__);
  }

  // now build this entry
  //
  File::mkdir(path_a);

  // exit gracefully
  //
  return true;
}
