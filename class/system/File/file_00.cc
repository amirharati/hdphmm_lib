// file: $isip/class/system/File/file_00.cc
// version: $Id: file_00.cc 9078 2003-04-09 19:46:31Z duncan $
//

// isip include files
//
#include "File.h"
#include <SysString.h>

// method: destructor
//
// arguments: none
//
// return: none
//
// this is the destructor for the File class
//
File::~File() {

  // release resources
  //
  // we allow stdout and stderr to be deleted without closing. this is
  // necessary for the static File object's used in Console.
  //
  if ((fp_d == (FILE*)stdout) || (fp_d == (FILE*)stderr)) {
    close();
  }
  
  // close the file if it is still open
  //
  if (fp_d != (FILE*)NULL) {

    // warn the user that the file wasn't closed
    //
    Error::handle(name(), L"destructor", ERR_NOTCLS, __FILE__,
		  __LINE__, Error::WARNING);

    // close the file
    //
    close();
  }
  
  // if the stream type is IN, destroy the temporary files that were
  // used to buffer the input
  //
  if (stream_d == IN) {
    cleanTemps();
  }
  
  // exit gracefully
  //
}

// method: default constructor
//
// arguments:
//  STREAM stream: (input) file stream
//
// return: none
//
// this is the default constructor for the File class
//
File::File(STREAM stream_a) {

  // stream type
  //
  stream_d = stream_a;
  
  // initialize class data
  //
  fp_d = (FILE*)NULL;
  mode_d = DEF_MODE;
  type_d = DEF_TYPE;
  
  lock_d = DEF_LOCK;
  indent_level_d = DEF_INDENT;
  line_wrap_d = DEF_LINE_WRAP;
  column_position_d = 0;
  open_retry_d = DEF_OPEN_RETRY;
  open_delay_d = DEF_OPEN_DELAY;

  // byte-order mode
  //
  byte_mode_d = DEF_BMODE;
  byte_swap_d = false;
    
  // check argument: stdout
  //
  if (stream_a == OUT) {
    fp_d = stdout;
    mode_d = WRITE_ONLY;
    type_d = TEXT;
  }
  
  // check for stdin
  //
  else if (stream_a == IN) {
    open(STREAM_FILE, READ_ONLY, TEXT);
  }
  
  // check for stderr
  //
  else if (stream_a == ERROR) {
    fp_d = stderr;
    mode_d = WRITE_ONLY;
    type_d = TEXT;
  }

  // bad stream descriptor was specified
  //
  else if (stream_a != NO_STREAM) {
    Error::handle(name(), L"default constructor",
		  Error::ARG, __FILE__, __LINE__);
  }
  
  // exit gracefully
  //
}

//-----------------------------------------------------------------------------
//
// we define non-integral constants in the default constructor
//
//-----------------------------------------------------------------------------

// constants: class name
//
const SysString File::CLASS_NAME(L"File");

// constants: names for each of the enumerated file modes
//
const char File::SYS_TEXT_READ_ONLY[] = "r";
const char File::SYS_TEXT_READ_PLUS[] = "r+";
const char File::SYS_TEXT_WRITE_ONLY[] = "w";
const char File::SYS_TEXT_WRITE_PLUS[] = "w+";
const char File::SYS_TEXT_APPEND_ONLY[] = "a";
const char File::SYS_TEXT_APPEND_PLUS[] = "a+";
const char File::SYS_BINARY_READ_ONLY[] = "rb";
const char File::SYS_BINARY_READ_PLUS[] = "rb+";
const char File::SYS_BINARY_WRITE_ONLY[] = "wb";
const char File::SYS_BINARY_WRITE_PLUS[] = "wb+";
const char File::SYS_BINARY_APPEND_ONLY[] = "ab";
const char File::SYS_BINARY_APPEND_PLUS[] = "ab+";

// constants: names for each of the enumerated file types
//
const SysString File::TYPE_TEXT(L"text");
const SysString File::TYPE_BINARY(L"binary");

// constants: indention and line wrapping
//
const SysString File::INDENT_STR(L"  ");
const SysString File::WRAP_TERM_STR(L"\n");
const SysString File::WRAP_PRE_INDENT_STR(L"");
const SysString File::WRAP_POST_INDENT_STR(L">");

// constants: denoting a piped input/output
//
const SysString File::STREAM_FILE(L"-");

// static instantiations: debug level and memory manager
//
Integral::DEBUG File::debug_level_d = Integral::NONE;
MemoryManager File::mgr_d(sizeof(File), File::name());

// static instantiations: open sof file stack
//
SysString** File::temp_files_d = (SysString**)NULL;
int32 File::temp_size_d = 0;
int32 File::temp_num_d = 0;

