// file: $isip/class/system/Integral/itgl_00.cc
// version: $Id: itgl_00.cc 5637 2000-11-21 03:52:58Z duncan $
//

// isip include files
//
#include "Integral.h"

#include <Error.h>
#include <Console.h>
#include <SysString.h>
#include <File.h>

// method: exit
//
// arguments: none
//
// return: a boolean value indicating status
//
// this method cleans up everything before the end of the program
//
int32 Integral::exit() {


  // close all Sof files (if applicable)
  //
  Error::closeSof();
  
  // remove all temporary files
  //
  File::cleanTemps();

  // close any open console's
  //
  Console::closeStack();

  // release any registered static memory
  //
  MemoryManager::releaseStatics();

  // exit gracefully
  //
  return Integral::SYS_RETURN_NOERROR;
}

//-----------------------------------------------------------------------------
//
// we define non-integral constants in the default constructor
//      
//-----------------------------------------------------------------------------

// constants: class name
//
const SysString Integral::CLASS_NAME(L"Integral");

// constants: environmental variables
//
const SysString Integral::ENV_ISIP(L"isip");
const SysString Integral::ENV_HOME(L"HOME");

// constants: for parsing environment variables and file pathnames under unix
//
const SysChar Integral::ENV_MARKER(L'$');
const SysChar Integral::DIR_DELIM(L'/');
const SysChar Integral::DIR_HOME(L'~');

// constants: unix commands
//
const SysString Integral::UNIX_CMD_COPY(L"cp");
const SysString Integral::UNIX_CMD_MOVE(L"mv");
const SysString Integral::UNIX_CMD_REDIR(L"2>&1");

// constants: temporary filename creation
//
const SysString Integral::TMPDIR(L"/tmp");
const SysString Integral::TMP_FMT_0(L"/tmp_");
const SysString Integral::TMP_FMT_1(L"_");
const SysString Integral::TMP_TEMPLATE(L"XXXXXX");

// constants: related to help message generation
//
const SysString Integral::HELP_FORMAT(L"more %s");
const SysString Integral::HELP_OPTION(L"-help");

// static instantiations: debug level
//
Integral::DEBUG Integral::debug_level_d = Integral::NONE;
