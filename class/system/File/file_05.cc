// file: $isip/class/system/File/file_05.cc
// version: $Id: file_05.cc 4884 2000-09-20 13:06:57Z hamaker $
//

// isip include files
//
#include "File.h"
#include <SysString.h>

// method: increaseIndention
//
// arguments: none
//
// return: a bool8 value indicating status
//
// increase the indention level
//
bool8 File::increaseIndention() {

  // increase the level
  //
  indent_level_d++;

  // check column position, possibly output newline
  //
  if (column_position_d != 0) {
    SysString newline(L"\n");
    put(newline);
  }
  
  // exit gracefully
  //
  return true;
}

// method: decreaseIndention
//
// arguments: none
//
// return: a bool8 value indicating status
//
// decrease the indention level
//
bool8 File::decreaseIndention() {

  // decrease the level
  //
  indent_level_d--;

  if (indent_level_d < 0) {
    return Error::handle(name(), L"decreaseIndention", ERR_WRAP,
			 __FILE__, __LINE__);
  }
  
  // check column position, possibly output newline
  //
  if (column_position_d != 0) {
    SysString newline(L"\n");
    put(newline);
  }
  
  // exit gracefully
  //
  return true;
}

// method: getLineLength
//
// arguments: none
//
// return: a int32 number
//
// get the maximum number of characters printed per line
//
int32 File::getLineLength() const {

  // if no line wrapping, we can't predict
  //
  if (line_wrap_d <= 0) {
    return -1;
  }
  
  // if no indention, the line length is equal to the line wrap
  //
  if (indent_level_d <= 0) {
    return line_wrap_d;
  }
  
  // compute & return the value
  //
  return (line_wrap_d - indent_level_d * INDENT_STR.length());
}

// method: registerTemp
//
// arguments:
//  SysString& fname: (input) temporary filename
//
// return: logical error status
//
// register a temporary filename so it can be deleted upon program
// termination
//
bool8 File::registerTemp(SysString& fname_a) {

  if ((temp_num_d + 1) >= temp_size_d) {
    mgr_d.reallocateBlock((void***)&temp_files_d, temp_size_d);
  }

  // add the new object to the array
  //
  temp_files_d[temp_num_d++] = new SysString(fname_a);

  // exit gracefully
  //
  return true;
}

// method: cleanTemps
//
// arguments: none
//
// return: logical error status
//
// remove all registered temporary filenames
//
bool8 File::cleanTemps() {

  // delete all files that still exist
  //
  for (int32 i = 0; i < temp_num_d; i++) {
    if (File::exists(*temp_files_d[i])) {
      remove(*temp_files_d[i]);
    }

    delete temp_files_d[i];
  }

  // clean up memory
  //
  if (temp_size_d > 0) {
    mgr_d.releaseBlock(temp_files_d);
    temp_files_d = (SysString**)NULL;
    temp_size_d = 0;
    temp_num_d = 0;
  }

  // exit gracefully
  //
  return true;
}
