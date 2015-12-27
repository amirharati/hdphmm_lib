// file: $isip/class/io/SofSymbolTable/sofs_01.cc
// version: $Id: sofs_01.cc 4893 2000-09-20 15:45:04Z duncan $
//

// isip include files
//
#include "SofSymbolTable.h"
#include <Console.h>

// method: debug
//
// arguments:
//  const unichar* msg: (input) debug message
//
// return: a bool8 value indicating status
//
// this method displays the values of all internal data
//
bool8 SofSymbolTable::debug(const unichar* msg_a) const {

  SysString output;
  SysString value;
  SysString vec_name;
			
  // output the table size and capacity
  //
  value.assign((int32)table_size_d);
  output.debugStr(name(), msg_a, L"table_size_d", value);
  Console::put(output);
  
  value.assign((int32)table_capacity_d);
  output.debugStr(name(), msg_a, L"table_capacity_d", value);
  Console::put(output);

  // output the number of symbols
  //
  value.assign((int32)num_syms_d);
  output.debugStr(name(), msg_a, L"num_syms_d", value);
  Console::put(output);
  
  // output the symbols
  //
  for (int32 i = 0; i <= table_size_d; i++) {
    
    // if this entry is referenced
    //
    if (ref_count_d[i] > 0) {
      
      // build the variable name for this entry
      //
      vec_name.assign((int32)i);
      vec_name.insert(L"table_d[", 0);
      vec_name.concat(L"]");
      
      // build a value string which contains the symbol & ref_count
      //
      value.assign((int32)ref_count_d[i]);
      value.insert(L"(", (int32)0);
      value.concat(L") ");
      value.concat(table_d[i]);
      
      // output the ith element of the symbol table
      //
      output.debugStr(name(), msg_a, vec_name, value);
      Console::put(output);
    }
  }
  
  // output the transform size
  //
  value.assign((int32)transform_size_d);
  output.debugStr(name(), msg_a, L"transform_size_d", value);
  Console::put(output);

  // output the transform, if it exists
  //
  for (int32 i = 0; i < transform_size_d; i++) {

    // build the variable name for this transform vector entry
    //
    vec_name.assign((int32)i);
    vec_name.insert(L"transform_d[", 0);
    vec_name.concat(L"]");

    // output the ith element of the transform vector
    //
    value.assign((int32)transform_d[i]);
    output.debugStr(name(), msg_a, vec_name, value);
    Console::put(output);
  }

  // output the debug level
  //
  value.assign(debug_level_d);
  output.debugStr(name(), msg_a, L"debug_level_d", value);
  Console::put(output);

  // exit gracefully
  //
  return true;
}
