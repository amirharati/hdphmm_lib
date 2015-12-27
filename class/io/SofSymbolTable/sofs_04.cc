// file: $isip/class/io/SofSymbolTable/sofs_04.cc
// version: $Id: sofs_04.cc 5502 2000-11-13 15:27:27Z picone $
//

// isip include files
//
#include "SofSymbolTable.h"
#include <MemoryManager.h>

// method: add
//
// arguments:
//  const SysString& name: (input) object name
//
// return: a int32  index
//
// add a name to the symbol table, and return its reference count
//
int32  SofSymbolTable::add(const SysString& name_a) {
  
  // make sure it is a valid name
  //
  if (!checkName(name_a)) {
    return NO_SYMB;
  }

  // see if the symbol already exists in the table
  //
  int32  num = getIndex(name_a);

  if (num != NO_SYMB) {
    
    // symbol already exists, increment reference count
    //
    ref_count_d[num]++;
    return num;
  }

  // new symbol, add to the end of the list
  //
  return addNew(name_a);
}

// method: addNew
//
// arguments:
//  const SysString& name: (input) object name
//
// return: a int32  index
//
// add a new name to the symbol table
//
int32  SofSymbolTable::addNew(const SysString& name_a) {
  
  // add the new symbol to the end of the list
  //
  int32  num = NO_SYMB;
  
  // check if we need to grow the table size
  //
  if (num_syms_d >= table_capacity_d - 1) {

    if (!growCapacity()) {
      Error::handle(name(), L"addNew", Error::NOMEM, __FILE__, __LINE__);
      return NO_SYMB;
    }
    num = num_syms_d;
    table_size_d = num;
  }
  
  else {
    
    num = NO_SYMB;
    
    // find a free space within the list
    //
    for (int32  i = 0; i < table_capacity_d; i++) {
      if (ref_count_d[i] == 0) {
	num = i;
	break;
      }
    }

    // check for memory error
    //
    if (num == NO_SYMB) {
      Error::handle(name(), L"addNew", Error::MEM, __FILE__, __LINE__);
      return NO_SYMB;
    }

    // incremement table_size_d
    //
    if (num > table_size_d) {
      table_size_d = num;
    }
  }
  
  // copy class data and initialize reference count
  //
  table_d[num].assign(name_a);
  ref_count_d[num] = 1;
  num_syms_d++;

  // exit gracefully
  //
  return num;
}

// method: add
//
// arguments:
//  int32  ind: (input) index for name
//  int32  ref: (input) reference count for name
//  const SysString& name: (input) symbol name
//
// return: a bool8 value indicating status
//
// manually add an entry. this is used when reconstructing a symbol
// table from a disk file.
//
bool8 SofSymbolTable::add(int32  ind_a, int32  ref_a, const SysString& name_a) {
  
  // make sure it is a valid name
  //
  if (!checkName(name_a)) {
    return false;
  }
  
  // check the bounds of the input
  //
  if (ind_a < 0) {
    return Error::handle(name(), L"add", ERR_SYMB,
                         __FILE__, __LINE__);
  }

  // increase the capacity of the table as necessary
  //
  while (ind_a >= table_capacity_d) {
    if (!growCapacity()) {
      return Error::handle(name(), L"add", Error::NOMEM,
                           __FILE__, __LINE__);
    }
  }

  // set the data
  //
  ref_count_d[ind_a] = ref_a;
  table_d[ind_a].assign(name_a);
  
  // set the counters
  //
  if (ind_a > table_size_d) {
    table_size_d = ind_a;
  }
  num_syms_d++;
  
  // exit gracefully
  //
  return true;
}

// method: remove
//
// arguments:
//  const SysString& name: (input) class name to remove
//
// return: a bool8 value indicating status
//
// remove one instance of name from the symbol table
//
bool8 SofSymbolTable::remove(const SysString& name_a) {

  int32  num = getIndex(name_a);

  if (num == NO_SYMB) {
    return Error::handle(name(), L"remove", ERR_NOTFND, __FILE__, __LINE__);
  }

  // if there are no more references to this symbol, delete it from
  // the list
  //
  if ((--ref_count_d[num]) == 0) {

    // clear the entry
    //
    table_d[num].clear();
    
    // decrease the actual table size if applicable
    //
    while (ref_count_d[table_size_d] == 0) {
      table_size_d--;
    }
    
    // decrease the number of objects
    //
    num_syms_d--;
  }
  
  // exit gracefully
  //
  return true;
}

// method: remove
//
// arguments:
//  int32  index: (input) index to delete
//
// return: a bool8 value indicating status
//
// remove one instance of a symbol of given index from the symbol table
//
bool8 SofSymbolTable::remove(int32  index_a) {
  
  if (index_a < 0) {
    return Error::handle(name(), L"remove", ERR_SYMB, __FILE__, __LINE__);
  }
  
  // if there are no more references to this symbol, delete it from
  // the list
  //
  if ((--ref_count_d[index_a]) == 0) {

    // clear the entry
    //
    table_d[index_a].clear();
    
    // decrease max if applicable
    //
    while ((table_size_d >= 0) && (ref_count_d[table_size_d] == 0)) {
      table_size_d--;
    }
    
    // decrease the number of objects
    //
    num_syms_d--;
  }

  // exit gracefully
  //
  return true;
}

// method: growCapacity
//
// arguments: none
//
// return: a bool8 value indicating status
//
// this method grows the symbol table array,  note that we always have
// contiguous memory
//
bool8 SofSymbolTable::growCapacity() {
  
  // increase capacity and create new space
  //
  table_capacity_d += GROW_SIZE;
  SysString* tmp_table = (SysString*)NULL;
  int32* tmp_ref = (int32*)NULL;
  
  tmp_table = new SysString[table_capacity_d];
  tmp_ref = new int32[table_capacity_d];
  
  // initialize the reference counts on the new data
  //
  MemoryManager::memset(tmp_ref, 0, table_capacity_d * sizeof(int32));
  
  if (table_size_d != NO_SYMB) {
    
    // copy the reference count data
    //
    MemoryManager::memcpy(tmp_ref, ref_count_d,
                          (table_size_d + 1) * sizeof(int32));
  
    // "swap" the new, zero length systrings with the old ones. This is
    // faster than copy because it doesn't need to allocate or
    // deallocate any memory.
    //
    for (int32 i = 0; i <= table_size_d; i++) {
      tmp_table[i].swap(table_d[i]);
    }
  }
  
  // delete the old space
  //
  if (table_d != (SysString*)NULL) {
    delete [] table_d;
  }
  if (ref_count_d != (int32*)NULL) {
    delete [] ref_count_d;
  }

  // install the new data
  //
  table_d = tmp_table;
  ref_count_d = tmp_ref;

  // exit gracefully
  //
  return true;
}

// method: checkName
//
// arguments:
//  const SysString& name: (input) symbol name
//
// return: a bool8 value indicating status
//
// this method checks if a symbol name is valid
//
bool8 SofSymbolTable::checkName(const SysString& name_a) const {

  // if a bad character was found, this is an invalid string
  //
  if (name_a.firstChr(INVALID_CHARS) != Integral::NO_POS) {
    return false;
  }
  
  // if the first character is a number, this is an invalid string
  //
  SysChar c(name_a(0));
  if (c.isDigit()) {
    return false;
  }
  
  // exit gracefully
  //
  return true;
}
