// file: $isip/class/io/SofList/sofl_02.cc
// version: $Id: sofl_02.cc 4927 2000-09-20 20:38:53Z zhao $
//

// isip include files
//
#include "SofList.h"
#include <Console.h>

// method: diagnose
//
// arguments:
//  Integral::DEBUG level: (input) debug level for diagnostics
//
// return: a bool8 value indicating status
//
bool8 SofList::diagnose(Integral::DEBUG level_a) {

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
  
  // set up a symbol table for use
  //
  //
  SofSymbolTable table;

  SysString n1(L"Int32"); 
  SysString n2(L"Int16");
  SysString n3(L"Float32");
  SysString n4(L"Char");
  SysString n5(L"Decoder");

  int32 i1 = table.add(n1);
  int32 i2 = table.add(n2);
  int32 i3 = table.add(n3);
  int32 i4 = table.add(n4);
  int32 i5 = table.add(n5);
  
  // test default constructor
  //
  SofList list_0;

  // test debug methods
  //
  list_0.setDebug(Integral::NONE);

  // add some nodes into the list
  //
  list_0.setTable(table);
  list_0.add(i1, 0, -1, sizeof(int32));
  list_0.add(i2, 0, -1, sizeof(int16));
  list_0.add(i3, 0, -1, sizeof(float32));
  
  if (level_a > Integral::BRIEF) {
    list_0.debug(L"debug");
  }
  
  // test the copy constructor and copy assign method
  //
  SofList list_1(list_0);

  if (list_1.getCount() != list_0.getCount()) {
    list_1.debug(L"list_1");
    return Error::handle(name(), L"copy constructor", Error::TEST,
			 __FILE__, __LINE__);
  }
  
  // test clear methods
  //
  list_1.clear();
  if (list_1.getCount() != 0) {
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
  
  // get the memsize
  //
  int32 mem_size = list_0.memSize();
  
  if (level_a > Integral::BRIEF) {
    SysString numeric;
    numeric.assign(mem_size);
    SysString output(L"memSize of list_0: ");
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
  //     soflist manipulation methods
  //
  //--------------------------------------------------------------------------

  // set indentation
  //
  if (level_a > Integral::NONE) {
    Console::put(L"testing class-specific public methods: soflist manipulation methods...\n");
    Console::increaseIndention();
  }


  SofList list;  
  SysString output;
        
  // set the symbol table
  //
  list.setTable(table);
  
  // add the nodes to list
  //
  list.add(i1, 0, -1, sizeof(int32));
  list.add(i2, 0, -1, sizeof(int16));
  list.add(i3, 0, -1, sizeof(float32));
  list.add(i4, 0, -1, sizeof(char));
  list.add(i5, 0, -1, 137);

  list.add(i2, 1, -1, sizeof(int16));
  list.add(i1, -1, -1, sizeof(int32));
  list.add(i4, 3, -1, sizeof(char));
  list.add(i4, 2, -1, sizeof(char));
  
  if (level_a > Integral::BRIEF) {
    list.debug(L"added nodes");
  }

  // check nodes
  //
  int32 tag = list.first(i4);
  if (tag != 0) {
    return Error::handle(name(), L"first", Error::TEST, __FILE__, __LINE__);
  }

  tag = list.next(i4, tag);
  if (tag != 2) {
    return Error::handle(name(), L"next", Error::TEST, __FILE__, __LINE__);
  }

  tag = list.next(i2, -100);
  if (tag != 0) {
    return Error::handle(name(), L"next", Error::TEST, __FILE__, __LINE__);
  }

  tag = list.prev(i1, 1000);
  if (tag != 0) {
    return Error::handle(name(), L"prev", Error::TEST, __FILE__, __LINE__);
  }

  tag = list.next(i4, 2);
  if (tag != 3) {
    return Error::handle(name(), L"next", Error::TEST, __FILE__, __LINE__);
  }

  tag = list.last(i5);
  if (tag != 0) {
    return Error::handle(name(), L"last", Error::TEST, __FILE__, __LINE__);
  }

  // test remove methods
  //
  if (!list.find(i3, 0)) {
    return Error::handle(name(), L"remove", Error::TEST, __FILE__, __LINE__);
  }
  if (!list.remove()) {
    return Error::handle(name(), L"remove", Error::TEST, __FILE__, __LINE__);
  }
  if (list.find(i3, 0)) {
    return Error::handle(name(), L"remove", Error::TEST, __FILE__, __LINE__);
  }

  // reinsert the node
  //
  list.add(i3, 0, -1, sizeof(float32));
  
  // reset indentation
  //
  if (level_a > Integral::NONE) {
    Console::decreaseIndention();
  }

  //---------------------------------------------------------------------------
  //
  // 3. class-specific public methods:
  //     set/get methods
  //
  //---------------------------------------------------------------------------
  
  // set indentation
  //
  if (level_a > Integral::NONE) {
    Console::put(L"testing class-specific public methods: set/get methods...\n");
    Console::increaseIndention();
  }
    
  // add lots of nodes
  //
  for (int32 i = 10; i < 2000; i++) {
    list.add(i3, i, i * 37, sizeof(float32));
  }
  
  // check the nodes by testing position
  //
  for (int32 i = 10; i < 2000; i++) {
    if (!list.find(i3, i)) {
      return Error::handle(name(), L"find", Error::TEST, __FILE__, __LINE__);
    }

    if (list.getSize() != sizeof(float32)) {
      return Error::handle(name(), L"getSize", Error::TEST,
			   __FILE__, __LINE__);
    }

    list.setSize(16);

    if (list.getSize() != 16) {
      return Error::handle(name(), L"getSize", Error::TEST, __FILE__,
			   __LINE__);
    }
    
    if (list.getPosition() != i * 37) {
      return Error::handle(name(), L"getPosition", Error::TEST, __FILE__,
			   __LINE__);
    }
    
    list.setPosition(i*36);
    if (list.getPosition() != i * 36) {
      return Error::handle(name(), L"setPosition", Error::TEST, __FILE__,
			   __LINE__);
    }
    
    if (list.getTag() != i) {
      return Error::handle(name(), L"getTag", Error::TEST, __FILE__, __LINE__);
    }

    if (list.getName() != i3) {
      return Error::handle(name(), L"getName", Error::TEST,
			   __FILE__, __LINE__);
    }
  }

  // check the number of classes
  //
  if (list.getNameCount() != 5) {
    return Error::handle(name(), L"getNameCount", Error::TEST,
			 __FILE__, __LINE__);
  }

  // count the nodes in the tree
  //
  if (list.getCount() != 1999) {
    return Error::handle(name(), L"getCount", Error::TEST, __FILE__, __LINE__);
  }

  if (list.getCount(i4) != 3) {
    return Error::handle(name(), L"getCount(Char's)", Error::TEST,
			 __FILE__, __LINE__);
  }

  // delete every other char node
  //
  for (int32 i = 10; i < 2000; i += 2) {
    if (!list.find(i3, i)) {
      return Error::handle(name(), L"find", Error::TEST, __FILE__, __LINE__);
    }
    if (!list.remove()) {
      return Error::handle(name(), L"find", Error::TEST, __FILE__, __LINE__);
    }
  }

  if (list.getCount(i3) != 996) {
    return Error::handle(name(), L"re-getCount", Error::TEST,
			 __FILE__, __LINE__);
  }

  // re-insert every other char node
  //
  for (int32 i = 10; i < 2000; i += 2) {
    if (!list.add(i3, i, -1, 5)) {
      return Error::handle(name(), L"remove", Error::TEST, __FILE__, __LINE__);
    }
  }
  
  if (list.getCount(i3) != 1991) {
    return Error::handle(name(), L"re-re-getCount", Error::TEST, __FILE__,
			 __LINE__);
  }
   
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
}
