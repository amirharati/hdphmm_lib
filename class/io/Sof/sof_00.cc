// file: $isip/class/io/Sof/sof_00.cc
// version: $Id: sof_00.cc 7400 2001-10-07 03:38:20Z picone $
//

// system include files
//
#include <strings.h>

// isip include files
//
#include "Sof.h"

// method: destructor
//
// arguments: none
//
// return: none
//
Sof::~Sof() {

  // make sure the file was closed
  //
  if (isOpen()) {

    // issue a warning
    //
    Error::handle(name(), L"destructor", File::ERR_NOTCLS,
		  __FILE__, __LINE__, Error::WARNING);
    
    // close the file
    //
    if (!cleanUp()) {
      Error::handle(name(), L"destructor", File::ERR_CLOSE,
		    __FILE__, __LINE__);
    }
  }
  
  // remove the file from the stack of Sof objects
  //
  unRegisterPtr();
  
  // exit gracefully
  //
}

// method: default constructor
//
// arguments: none
//
// return: none
//
Sof::Sof() {

  // initialize the data
  //
  // general information about a file
  //
  name_d.clear();
  expanded_name_d.clear();
  file_type_d = File::DEF_TYPE;

  // auxiliary information
  //
  delimiter_d = DEF_DELIMITER;
  end_of_header_d = DEF_POS;
  end_of_data_d = DEF_POS;
  implicit_count_d = DEF_IMPLICIT;
  cur_data_d = DEF_POS;
  cur_pos_d = DEF_POS;
  
  disable_lock_d = DEF_DISABLE_LOCK;
  lock_retry_d = File::DEF_LOCK_RETRY;
  lock_delay_d = File::DEF_LOCK_DELAY;

  file_checksum_d = 0;

  // partial i/o information
  //
  partial_write_d = false;
  partial_read_d = false;
  vec_parser_d = (SofParser*)NULL;
  skip_table_d = (int32*)NULL;
  skip_table_incr_d = 0;
  last_skip_table_pos_d = 0;
  vec_start_pos_d = 0;
  vec_size_d = 0;
  vec_curr_elem_d = 0;

  // create the reference between the list and the symbol table
  //
  index_d.setTable(table_d);

  // debugging parameters
  //
  debug_level_d = Integral::NONE;
  
  // add object to stack of Sof objects
  //
  registerPtr();

  // possibly set dynamic pointer for Error handler
  //
  static bool8 set_error = false;
  if (!set_error) {
    setErrorPointer();
    set_error = true;
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
const SysString Sof::CLASS_NAME(L"Sof");

// constants: for file parsing 
//
const SysString Sof::VERSION(L"v1.0");
const char Sof::NEWLINE_BUFFER[] = "\n";
const int32 Sof::NEWLINE_LENGTH = strlen(NEWLINE_BUFFER);

// constants: byte-mode descriptor string
//
const SysString Sof::BSTR_NATIVE(L"abcd");
const SysString Sof::BSTR_SWAP(L"dcba");

// static instantiations: memory manager and checksum
//
MemoryManager Sof::mgr_d(sizeof(Sof), Sof::name());
Checksum Sof::cksm_d;
