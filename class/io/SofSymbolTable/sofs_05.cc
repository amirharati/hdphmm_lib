// file: $isip/class/io/SofSymbolTable/sofs_05.cc
// version: 
//

// isip include files
//
#include "SofSymbolTable.h"

// method: convert
//
// arguments:
//  const SofSymbolTable& old_table: (input) symbol table to reference
//  int32 old_index: (input) reference of symbol in old table
//
// return: a int32 index
//
// this method finds the index in the current symbol table based on an index
// in an old symbol table
//
int32 SofSymbolTable::convert(const SofSymbolTable& old_table_a,
			     int32 old_index_a) const {
  
  // get the symbol name corresponding to the index
  //
  SysString old_name;
  
  if (!old_table_a.getSymbol(old_name, old_index_a)) {
    return NO_SYMB;
  }
  
  // get the index in the current table
  //
  return getIndex(old_name);
}

// method: convert
//
// arguments:
//  int32 old_index: (input) index of symbol in the old table
//
// return: a int32 index
//
// this method finds the index in the current object based on an index in
// the transform vector. this works only when the transform vector has
// been set up
//
int32 SofSymbolTable::convert(int32 old_index_a) const {

  // make sure the transform vector has been set up
  //  
  if (transform_d == (int32*)NULL) {
    Error::handle(name(), L"convert", ERR_NOVECT, __FILE__, __LINE__);
    return NO_SYMB;
  }

  // check the range of the index
  //
  if ((old_index_a >= transform_size_d) || (old_index_a < 0)) {
    Error::handle(name(), L"convert", ERR_SYMB, __FILE__, __LINE__);
    return NO_SYMB;
  }

  // return the new index according to the transform vector
  //
  return transform_d[old_index_a];
}

// method: transformInit
//
// arguments:
//  const SofSymbolTable& old_table: (input) symbol table to reference
//
// return: a bool8 value indicating status
//
// this method creates a transform vector between the old indexing scheme
// and the new (current) object such that:
//  new_index = transform_d[old_index]
//
// this facilitates a fast conversion between the two schemes
//
bool8 SofSymbolTable::transformInit(const SofSymbolTable& old_table_a) {

  // setup the memory for the transform
  //
  transformDelete();
  transform_size_d = old_table_a.table_size_d + 1;
  transform_d = new int32[transform_size_d];
  MemoryManager::memset(transform_d, 0, transform_size_d * sizeof(int32));
  
  // find the conversion for each index
  //
  for (int32 i = 0; i < transform_size_d; i++) {
    transform_d[i] = convert(old_table_a, i);
  }
  
  // exit gracefully
  //
  return true;
}

// method: transformDelete
//
// arguments: none
//
// return: a bool8 value indicating status
//
// this method deletes the transform vector
//
bool8 SofSymbolTable::transformDelete() {

  // delete the memory
  //
  if (transform_d != (int32*)NULL) {
    delete [] transform_d;
    transform_d = (int32*)NULL;
  }

  // reset the size
  //
  transform_size_d = (int32)0;
  
  // exit gracefully
  //
  return true;
}
