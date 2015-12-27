// file: $isip/class/system/File/file_01.cc
// version: $Id: file_01.cc 4884 2000-09-20 13:06:57Z hamaker $
//

// isip include files
//
#include <SysString.h>
#include <Console.h>
#include "File.h"

// method: debug
//
// arguments:
//  const unichar* msg: (input) debugging message
//  
// return: a bool8 value indicating status
//
bool8 File::debug(const unichar* msg_a) const {
  
  // build the debug string
  //
  SysString output;
  SysString value;

  // output the information of the fp_d
  //
  if (fp_d == (FILE*)NULL) {
    value.assign(fp_d);
  }
  else if (fp_d == (FILE*)stdout) {
    value.assign(L"stdout");
  }
  else if (fp_d == (FILE*)stdin) {
    value.assign(L"stdin");
  }
  else if (fp_d == (FILE*)stderr) {
    value.assign(L"stderr");
  }
  else {
    value.assign((int32)(fileno(fp_d)));
    value.insert(L"desc #", 0);
  }

  output.debugStr(name(), msg_a, L"fp_d", value);
  Console::put(output);

  // output the information of file mode
  //
  value.assign(mode_d);
  output.debugStr(name(), msg_a, L"mode_d", value);
  Console::put(output);

  // output the information of the file type
  //  
  value.assign(type_d);
  output.debugStr(name(), msg_a, L"type_d", value);
  Console::put(output);
  
  // output the information of byte-order mode
  //
  value.assign(byte_mode_d);
  output.debugStr(name(), msg_a, L"byte_mode_d", value);
  Console::put(output);
  
  value.assign(byte_swap_d);
  output.debugStr(name(), msg_a, L"byte_swap_d", value);
  Console::put(output);

  // output other properties
  //
  value.assign(lock_d);
  output.debugStr(name(), msg_a, L"lock_d", value);
  Console::put(output);
  
  value.assign(indent_level_d);
  output.debugStr(name(), msg_a, L"indent_level_d", value);
  Console::put(output);
  
  value.assign(line_wrap_d);
  output.debugStr(name(), msg_a, L"line_wrap_d", value);
  Console::put(output);
  
  value.assign(column_position_d);
  output.debugStr(name(), msg_a, L"column_position_d", value);
  Console::put(output);

  // exit gracefully
  //
  return true;
}
