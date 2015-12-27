// file: $isip/class/io/SofSymbolTable/sofs_00.cc
// version: $Id: sofs_00.cc 5019 2000-09-26 18:47:33Z zhao $
//

// isip include files
//
#include "SofSymbolTable.h"

// method: destructor
//
// arguments: none
//
// return: none
//
SofSymbolTable::~SofSymbolTable() {

  // delete the memory
  //
  freeMem();
  
  // exit gracefully
  //
}

// method: copy constructor
//
// arguments:
//  const SofSymbolTable& sofs: (input) symbol table to be copied
//
// return: none
//
// this is the copy constructor for the SofSymbolTable class
//
SofSymbolTable::SofSymbolTable(const SofSymbolTable& sofs_a) {

  // setup a null index
  // 
  table_d = (SysString*)NULL;
  ref_count_d = (int32*)NULL;
  
  // initialize the number of symbols
  //
  num_syms_d = 0;
  table_size_d = NO_SYMB;
  table_capacity_d = 0;
  
  // by default we have no transform vector
  //
  transform_d = (int32*)NULL;
  transform_size_d = 0;

  // debugging parameters
  //
  debug_level_d = Integral::NONE;

  // assign the table
  //
  assign(sofs_a);
}

// method: freeMem
//
// arguments: none
//
// return: a bool8 value indicating status
//
// method releases all memory
//
bool8 SofSymbolTable::freeMem() {

  // clear out memory
  //
  clear();
  
  // delete memory
  //
  if (table_d != (SysString*)NULL) {
    delete [] table_d;
    table_d = (SysString*)NULL;
  }
  if (ref_count_d != (int32*)NULL) {
    delete [] ref_count_d;
    ref_count_d = (int32*)NULL;
  }
  if (transform_d != (int32*)NULL) {
    delete [] transform_d;
    transform_d = (int32*)NULL;
  }
  
  // set sizes to zero
  //
  table_capacity_d = 0;
  transform_size_d = 0;

  // initialize the number of symbols
  //
  num_syms_d = 0;
  table_size_d = NO_SYMB;

  // exit gracefully
  //
  return true;
}

// method: default constructor
//
// arguments: none
//
// return: none
//
// this is the default constructor for the SofSymbolTable class
//
SofSymbolTable::SofSymbolTable() {

  // setup a null index
  //  
  table_d = (SysString*)NULL;
  ref_count_d = (int32*)NULL;

  // initialize the number of symbols
  //
  num_syms_d = 0;
  table_size_d = NO_SYMB;
  table_capacity_d = 0;
  
  // by default we have no transform vector
  //
  transform_d = (int32*)NULL;
  transform_size_d = 0;
  
  // debugging parameters
  //
  debug_level_d = Integral::NONE;
  
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
const SysString SofSymbolTable::CLASS_NAME(L"SofSymbolTable");

// constants: invalid characters in a symbol name
//
const SysString SofSymbolTable::INVALID_CHARS(L" {}=\\;\"'/`:#");
