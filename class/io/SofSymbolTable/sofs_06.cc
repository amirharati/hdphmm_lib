// file: $isip/class/io/SofSymbolTable/sofs_06.cc
// version: $Id: sofs_06.cc 4955 2000-09-22 20:48:39Z zhao $
//

// isip include files
//
#include "SofSymbolTable.h"

// method: getIndex
//
// arguments:
//  const SysString& name: (input) the name of the symbol
//
// return: a int32 index
//
// this method finds the index of name in the list
//
int32 SofSymbolTable::getIndex(const SysString& name_a) const {
  
  // make sure it is a valid name
  //
  if (!checkName(name_a)) {
    return NO_SYMB;
  }
					     
  // check for special cases
  //
  if (num_syms_d <= (int32)0) {
    return NO_SYMB;
  }

  // iterate through the list
  //
  for (int32 i = 0; i <= table_size_d; i++) {

    // this is a match if the strings are equal and the reference
    // count is greater than zero.
    //
    if ((ref_count_d[i] > 0) && (name_a.eq(table_d[i]))) {
      return i;
    }
  }
  
  // exit (un)gracefully - no match was found
  //
  return NO_SYMB;
}

// method: getSymbol
//
// arguments:
//  SysString& name: (output) name of this index
//  int32 index: (input) index into the symbol table
//
// return: a bool8 value indicating status
//
// this method finds the symbol of the given index in the list
//
bool8 SofSymbolTable::getSymbol(SysString& name_a, int32 index_a) const {
  
  // check for special cases
  //
  if ((index_a < 0) || (index_a > table_size_d)) {
    Error::handle(name(), L"getSymbol", ERR_SYMB, __FILE__, __LINE__);
    name_a.clear();
    return false;
  }
  
  if (ref_count_d[index_a] <= 0) {
    name_a.clear();
    return false;
  }
  
  // assign the string
  //
  name_a.assign(table_d[index_a]);
    
  // exit gracefully 
  //
  return true;
}

// method: getRefCount
//
// arguments:
//  const SysString& name: (input) object name
//
// return: a int32 count
// 
// find the number of symbols matching this name exist in the table
//
int32 SofSymbolTable::getRefCount(const SysString& name_a) const {

  // do a linear search on the index
  //
  int32 i = getIndex(name_a);

  // get the count
  //
  if (i >= 0) {
    return ref_count_d[i];
  }

  // exit (un)gracefully
  //
  return (int32)0;
}

// method: getRefCount
//
// arguments:
//  int32 index: (input) object index
//
// return: a int32 count
// 
// find the number of symbols matching this index exist in the table
//
int32 SofSymbolTable::getRefCount(int32 index_a) const {
  
  // get the count
  //
  if ((index_a >= 0) && (index_a <= table_size_d)) {
    return ref_count_d[index_a];
  }

  // exit (un)gracefully
  //
  return (int32)0;
}
