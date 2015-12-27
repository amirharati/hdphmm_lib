// file: $isip/class/system/Integral/itgl_05.cc
// version: $Id: itgl_05.cc 10534 2006-03-30 16:15:57Z raghavan $
//

// isip include files
//
#include "Integral.h"
#include <SysString.h>


// method: makeTemp
//
// arguments:
//  SysString& tmp_file: (output) filename
//
// return: a bool8 value indicating status
//
// create a temporary filename
//
bool8 Integral::makeTemp(SysString& tmp_file_a) {

  // declare local variables
  //
  SysString name;
  SysString numeric;
  
  // create static String constants out of the constants
  //
  static SysString tmpdir((unichar*)TMPDIR);
  static SysString tmp_fmt_0((unichar*)TMP_FMT_0);
  static SysString tmp_fmt_1((unichar*)TMP_FMT_1);
  static SysString tmp_template((unichar*)TMP_TEMPLATE);
  static int32 tempFileCounter = 1;

  // start with /tmp/tmp_
  //
  name.concat(tmpdir, tmp_fmt_0);

  // add the process and host id:
  //  %7.7lu is the print format
  //
  numeric.assign((int32)Integral::getPid(), L"%6.6lu");
  name.concat(numeric);
  numeric.assign((int32)Integral::getHostid(), L"%6.6lu");
  name.concat(numeric);
  name.concat(tmp_fmt_1);
  
  // add time stamp
  // using current time 
  //
  numeric.assign((uint32)(time()), L"%10.10lu");
  name.concat(numeric);
  name.concat(tmp_fmt_1);
  
  // add the static variable
  //
  numeric.assign((int32)tempFileCounter++, L"%d");
  name.concat(numeric);

  // call the master function
  //
  return makeTemp(tmp_file_a, name);
}

// method: makeTemp
//
// arguments:
//  SysString& tmp_file: (output) filename
//  const SysString& basename: (input) base-name to call mktemp with
//
// return: a bool8 value indicating status
//
// create a temporary filename
//
bool8 Integral::makeTemp(SysString& tmp_file_a,
			   const SysString& basename_a) {

  // assign the file name
  //
  tmp_file_a.assign((byte8*)basename_a);  

  // register the temp file
  //
  File::registerTemp(tmp_file_a);
  
  // exit gracefully
  //
  return true;
}
