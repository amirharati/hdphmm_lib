// file: $isip/class/shell/Sdb/sdb_00.cc
// version: $Id: sdb_00.cc 9236 2003-06-23 18:12:22Z gao $
//

// isip include files
// 
#include "Sdb.h"

// method: default constructor
//
// arguments: none
//
// return: none
//
Sdb::Sdb() {

  // initialize the data
  //
  output_basename_d.assign(String::NULL_STRING);  
  output_extension_d.assign(Filename::DEF_EXTENSION);
  output_suffix_d.assign(Filename::DEF_SUFFIX);
  lookahead_d = DEF_LOOKAHEAD;
  at_first_d = true;
  
  // initialize the internal stacks
  //
  fps_d.setAllocationMode(DstrBase::USER);
  tags_d.setAllocationMode(DstrBase::SYSTEM);
  nums_d.setAllocationMode(DstrBase::SYSTEM);
  
  // exit gracefully
  //
}

//-----------------------------------------------------------------------------
//
// we define non-integral constants in the default constructor
//      
//----------------------------------------------------------------------------

// constants: required constants such as the class name
//
const String Sdb::CLASS_NAME(L"Sdb");

// constants: default arguments
//
const String Sdb::DEF_OUT_DIR(L"");

// constants: required constants for i/o methods
//
const String Sdb::DEF_PARAM(L"files");

// constants: indicate file lists in the Sdb lists
//
const String Sdb::LIST_FILE_MARKER(L"(list) ");
const String Sdb::LIST_FILE_OPTION(L"list");

// static instantiations: debug level and memory manager
//
Integral::DEBUG Sdb::debug_level_d = Integral::NONE;
MemoryManager Sdb::mgr_d(sizeof(Sdb), Sdb::name());

