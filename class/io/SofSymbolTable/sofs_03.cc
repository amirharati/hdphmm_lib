// file: $isip/class/io/SofSymbolTable/sofs_03.cc
// version: $Id: sofs_03.cc 5120 2000-10-03 13:05:25Z picone $
//

// isip include files
//
#include "SofSymbolTable.h"
#include <MemoryManager.h>

// method: assign
//
// arguments:
//  const SofSymbolTable& arg: (input) symbol table to be assigned
//
// return: a bool8 value indicating status
//
// assign the arg to current symbol table 
//
bool8 SofSymbolTable::assign(const SofSymbolTable& arg_a) {

  // clear current memory
  //
  clear();
  
  // see if we have enough space for new list, allocate more space if not
  //
  if (table_capacity_d <= arg_a.table_size_d) {

    // delete current memory
    //
    freeMem();
    
    if ((table_d != (SysString*)NULL) || (ref_count_d != (int32*)NULL)) {
      return Error::handle(name(), L"assign", Error::MEM, __FILE__, __LINE__);
    }

    // allocate the memory
    //
    table_capacity_d = arg_a.table_capacity_d;
    table_d = new SysString[table_capacity_d];
    ref_count_d = new int32[table_capacity_d];
    MemoryManager::memset(ref_count_d, (int32)0, table_capacity_d * sizeof(int32));
  }

  // assign the data
  //
  num_syms_d = 0;
  table_size_d = arg_a.table_size_d;
  
  for (int32 i = 0; i <= arg_a.table_size_d; i++) {
    if (arg_a.ref_count_d[i] > 0) {
      add(i, arg_a.ref_count_d[i], arg_a.table_d[i]);
    }
  }
  
  // exit gracefully
  //
  return true;
}

// method: clear
//
// arguments:
//  Integral::CMODE ctype: (input) clear mode
//
// return: a bool8 value indicating status
//
// clear out the values of entire symbol table. this clear method does not
//  accept FREE mode, so the user is forced to use the destructor for
/// handling the SofSymbolTable. Sof files could easily be corrupted
//  if the memory of SofSymbolTable is improperly freed.
//
bool8 SofSymbolTable::clear(Integral::CMODE ctype_a) {
  
  // check the clear mode
  //
  if (ctype_a == Integral::FREE) {
    return Error::handle(name(), L"clear", Error::ARG, __FILE__, __LINE__);
  }
  
  // clear out every entry
  //
  for (int32 i = 0; i <= table_size_d; i++) {
    ref_count_d[i] = 0;
    table_d[i].clear();
  }

  // set the data to be an empty (but allocated) index
  //
  num_syms_d = 0;
  table_size_d = NO_SYMB;

  // exit gracefully
  //
  return true;
}

// method: assignCompact
//
// arguments:
//  const SofSymbolTable& sofs: (input) symbol table to be copied
//
// return: a bool8 value indicating status
//
// assign the symbol table in a compact form
//
bool8 SofSymbolTable::assignCompact(const SofSymbolTable& sofs_a) {
  
  // delete memory
  //
  freeMem();
  
  // array used to hold the index, make it just big enough
  //
  table_capacity_d = GROW_SIZE;
  while (table_capacity_d < sofs_a.num_syms_d) {
    table_capacity_d += GROW_SIZE;
  }

  table_d = new SysString[table_capacity_d];
  ref_count_d = new int32[table_capacity_d];

  // zero out array of longs
  //
  MemoryManager::memset(ref_count_d, (int32)0, table_capacity_d * sizeof(int32));
    
  // initialize the number of symbols
  //
  num_syms_d = sofs_a.num_syms_d;
  
  table_size_d = NO_SYMB;
  
  // debugging parameters
  //
  debug_level_d = Integral::NONE;

  // copy over the data itself
  //
  for (int32 i = 0; i <= sofs_a.table_size_d; i++) {

    // if there is symbol in this slot
    //
    if (sofs_a.ref_count_d[i] > 0) {
      table_size_d++;
      
      // copy over the data
      //
      table_d[table_size_d].assign(sofs_a.table_d[i]);
      ref_count_d[table_size_d] = sofs_a.ref_count_d[i];
    }
  }

  // create the transform vector
  //
  transformInit(sofs_a);

  // exit gracefully
  //
  return true;
}

// method: memSize
//
// arguments: none
//
// return: int32 value
//
// determine the memory size of the class in bytes
//
int32 SofSymbolTable::memSize() const {
  
  // define the return value
  //
  int32 size = 0;
  
  // add the size of each data member
  //
  for (int32 i = 0; i <= table_size_d; i++) {
    i += table_d[i].memSize();
  }
  
  size += table_capacity_d * (sizeof(int32));
  size += sizeof(table_d);
  size += sizeof(ref_count_d);
  size += sizeof(table_capacity_d);
  size += sizeof(num_syms_d);
  size += sizeof(table_size_d);
  size += sizeof(debug_level_d);
  size += sizeof(transform_size_d);
  size += sizeof(transform_d);

  if (transform_size_d > 0) {
    size += sizeof(int32) * transform_size_d;
  }
  
  // return the size
  //
  return size;
}
