// file: $isip/class/io/SofSymbolTable/sofs_02.cc
// version: $Id: sofs_02.cc 5120 2000-10-03 13:05:25Z picone $
//

// isip include files
//
#include "SofSymbolTable.h"
#include <Console.h>

// method: diagnose
//
// arguments:
//  Integral::DEBUG level: (input) debug level for diagnostics
//
// return: a bool8 value indicating status
//
bool8 SofSymbolTable::diagnose(Integral::DEBUG level_a) {

  //---------------------------------------------------------------------------
  //
  // 0. preliminaries
  //
  //---------------------------------------------------------------------------

  // output the class name
  //
  if (level_a > Integral::NONE) {
    SysString output(L"diagnosing class ");
    output.concat(CLASS_NAME);
    output.concat(L": ");
    Console::put(output);
    Console::increaseIndention();
  }
  
  //--------------------------------------------------------------------------
  //
  // 1. required public methods
  //
  //--------------------------------------------------------------------------
  
  // set indentation
  //
  if (level_a > Integral::NONE) {
    Console::put(L"testing required public methods...\n");
    Console::increaseIndention();
  }

  // test default constructor
  //
  SofSymbolTable table_0;
  
  // add some symbols to the table
  //
  SysString sym(L"Int32");
  for (int32 i = 0; i < 1; i++) {
    table_0.add(sym);
  }
  
  // test the copy constructor and copy assign method
  //
  SofSymbolTable table_1(table_0);

  // test the debug methods
  //
  table_1.setDebug(Integral::NONE);
  
  if (level_a > Integral::BRIEF) {
    table_1.debug(L"debug");
  }

  // test clear methods
  //
  table_1.clear();
  if (table_1.getCount() != 0) {
    return Error::handle(name(), L"clear", Error::TEST, __FILE__, __LINE__);
  }
   
  // reset indentation
  //
  if (level_a > Integral::NONE) {
    Console::decreaseIndention();
  }
  
  //--------------------------------------------------------------------------
  //
  // 2. class-specific public methods:
  //     extensions to required public methods
  //
  //--------------------------------------------------------------------------

  // set indentation
  //
  if (level_a > Integral::NONE) {
    Console::put(L"testing class-specific public methods: extensions to required methods...\n");
    Console::increaseIndention();
  }

  // test assignCompact method
  //
  SofSymbolTable table_2;
  table_2.assignCompact(table_0);
  
  // get the memsize
  //
  int32 mem_size = table_2.memSize();
  
  if (level_a > Integral::BRIEF) {
    SysString numeric;
    numeric.assign(mem_size);
    SysString output(L"memSize of table_2: ");
    output.concat(numeric);
    Console::put(output);
  }
    
  // reset indentation
  //
  if (level_a > Integral::NONE) {
    Console::decreaseIndention();
  }
  
  //--------------------------------------------------------------------------
  //
  // 3. class-specific public methods:
  //     symbol table manipulation methods
  //
  //--------------------------------------------------------------------------

  // set indentation
  //
  if (level_a > Integral::NONE) {
    Console::put(L"testing class-specific public methods: table manipulation methods...\n");
    Console::increaseIndention();
  }
  
  SofSymbolTable table0;
  SofSymbolTable table1;
  SofSymbolTable table2;
  
  // start adding to the table
  //
  SysString n1(L"Int32");
  SysString n2(L"Int16");
  SysString n3(L"Float32");
  SysString n4(L"Int32");
  SysString n5(L"Char");
  SysString n6(L"Decoder");

  // add symbols
  //
  table0.add(n1);
  table0.add(n2);
  table0.add(n3);
  table0.add(n4);
  table0.add(n2);
  table0.add(n5);
  table0.add(n6);
  table0.add(n1);

  // check the counts
  //
  SysString symbol;
  if (!table0.getSymbol(symbol, 0) || symbol.ne(n1)) {
    symbol.debug(L"symbol");
    return Error::handle(name(), L"add/getSymbol", Error::TEST, __FILE__,
			 __LINE__);
  } 

  if (!table0.getSymbol(symbol, 1) || symbol.ne(n2)) {
    return Error::handle(name(), L"add/getSymbol", Error::TEST, __FILE__,
			 __LINE__);
  }
  
  if (table0.getCount() != 5) {
    return Error::handle(name(), L"add/getCount", Error::TEST, __FILE__,
			 __LINE__);
  }
  
  // test getIndex
  //
  int32 ind = table0.getIndex(n1);
  
  if (ind == SofSymbolTable::NO_SYMB) {
    return Error::handle(name(), L"getIndex", Error::TEST, __FILE__, __LINE__);
  }
  
  // n1 and n4 are the same symbol "Int32", their indices should be the same
  //
  if (table0.getIndex(n4) != ind) {
    return Error::handle(name(), L"getIndex", Error::TEST, __FILE__, __LINE__);
  }

  // test remove methods
  //
  table0.remove(n1);
  table0.remove(n5);

  if (level_a > Integral::BRIEF) {
    table0.debug(L"table0 after remove");
  }
 
  // check the counts
  //
  if (table0.getRefCount(n1) != 2) {
    return Error::handle(name(), L"remove/getCount", Error::TEST,
			 __FILE__, __LINE__);
  }
  
  if (table0.getRefCount(n3) != 1) {
    return Error::handle(name(), L"remove/getCount", Error::TEST,
			 __FILE__, __LINE__);
  }
  
  if (table0.getRefCount(n5) != 0) {
    return Error::handle(name(), L"remove/getCount", Error::TEST,
			 __FILE__, __LINE__);
  }
    
  if (table0.getCount() != 4) {
    return Error::handle(name(), L"getCount", Error::TEST, __FILE__, __LINE__);
  }

  // test manual add method
  //
  table1.clear();
    
  table1.add(6, 3, n5);
  
  if (table1.getCount() != 1) {
    return Error::handle(name(), L"manual add", Error::TEST, __FILE__,
			 __LINE__);
  }

  table1.clear();

  // test checking methods
  //
  SysString bad_name(L"oscar had");
  if (table0.checkName(bad_name)) {
    return Error::handle(name(), L"checkName", Error::TEST,
			 __FILE__, __LINE__);
  }
  
  if (!table0.isEfficient() && level_a > Integral::BRIEF) {
    Console::put(L"table0 not efficient");
  }
  
  // let's try to push out the length of the index greatly so
  // growIndex will be used.
  //
  if (level_a > Integral::BRIEF) {
    Console::put(L"testing larger table...");
  }
    
  SysString numeric;
  
  // insert 300 unique names
  //
  for (int32 i = 0; i < 300; i++) {
    numeric.assign((int32)i);
    numeric.insert(L"test", 0);
    table2.add(numeric);
  }

  // let's check a few entries (random choices)
  //
  numeric.assign(L"test5");
  if (table2.getIndex(numeric) != 5) {
    return Error::handle(name(), L"growCapacity", Error::TEST, __FILE__,
			 __LINE__);
  }
  
  // out of the first group
  //
  numeric.assign(L"test25");
  if (table2.getIndex(numeric) != 25) {
    return Error::handle(name(), L"growCapacity", Error::TEST, __FILE__,
			 __LINE__);
  }
  
  // out of the second group
  //
  numeric.assign(L"test270");
  if (table2.getIndex(numeric) != 270) {
    return Error::handle(name(), L"growCapacity", Error::TEST, __FILE__,
			 __LINE__);
  }
  
  // reset indentation
  //
  if (level_a > Integral::NONE) {
    Console::decreaseIndention();
  }
  
  //---------------------------------------------------------------------------
  //
  // 3. class-specific public methods:
  //     symbol table conversion methods
  //
  //---------------------------------------------------------------------------
  
  // set indentation
  //
  if (level_a > Integral::NONE) {
    Console::put(L"testing class-specific public methods: table conversion methods...\n");
    Console::increaseIndention();
  }
  
  SofSymbolTable old_table;
  SofSymbolTable new_table;

  SysString those(L"those");
  SysString that(L"that");
  SysString these(L"these");

  // add them into two tables in different order
  // 
  old_table.add(those);
  old_table.add(these);
  old_table.add(those);
  old_table.add(that);           // [those 2] [these 1 ] [that 1]
  
  new_table.add(that);
  new_table.add(these);
  new_table.add(those);
  new_table.add(that);          // [that 2 ] [these 1] [those 1]

  // test convert method 
  //
  int32 old_ind = old_table.getIndex(those);
  int32 new_ind = new_table.getIndex(those);

  if (new_ind != new_table.convert(old_table, old_ind)) {
    return Error::handle(name(), L"convert", Error::TEST, __FILE__,
			 __LINE__);
  }

  // generate the transform vector
  //
  new_table.transformInit(old_table);

  // call the other convert method
  //
  if (new_ind != new_table.convert(old_ind)) {
    return Error::handle(name(), L"convert", Error::TEST, __FILE__,
			 __LINE__);
  }
  new_table.transformDelete();
    
  // reset indentation
  //
  if (level_a > Integral::NONE) {
    Console::decreaseIndention();
  }
  
  //---------------------------------------------------------------------------
  //
  // 4. print completion message
  //
  //---------------------------------------------------------------------------
  
  // reset indentation
  //
  if (level_a > Integral::NONE) {
    Console::decreaseIndention();
  }
  
  if (level_a > Integral::NONE) {
    SysString output(L"diagnostics passed for class ");
    output.concat(name());
    output.concat(L"\n");
    Console::put(output);
  }
  
  // exit gracefully
  //
  return true;
  
  // exit gracefully
  //
  return true;
}
