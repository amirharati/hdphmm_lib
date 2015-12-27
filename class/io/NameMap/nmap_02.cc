// file: $isip/class/io/NameMap/nmap_02.cc
// version: $Id: nmap_02.cc 5871 2000-12-13 23:36:00Z duncan $
//

// isip include files
//
#include "NameMap.h"
#include <Console.h>

// method: diagnose
//
// arguments:
//  Integral::DEBUG level: (input) debug level for diagnostics
//
// return: a bool8 value indicating status
//
bool8 NameMap::diagnose(Integral::DEBUG level_a) {

  //---------------------------------------------------------------------
  //
  // 0. preliminaries
  //
  //---------------------------------------------------------------------

  // output the class name
  //
  if (level_a > Integral::NONE) {
    SysString output(L"diagnosing class ");
    output.concat(CLASS_NAME);
    output.concat(L": ");
    Console::put(output);
    Console::increaseIndention();
  }

  //---------------------------------------------------------------------
  //
  // 1. required public methods
  //
  //---------------------------------------------------------------------

  // set indentation
  //
  if (level_a > Integral::NONE) {
    Console::put(L"testing required public methods...\n");
    Console::increaseIndention();
  }

  // test the setDebug method
  //  set it to full
  //
  setDebug(Integral::ALL);

  if (debug_level_d != Integral::ALL) {
    return Error::handle(name(), L"setDebug", Error::TEST, __FILE__, __LINE__);
  }

  // again set it to null
  //
  setDebug(Integral::NONE);
  if (debug_level_d != Integral::NONE) {
    return Error::handle(name(), L"setDebug", Error::TEST, __FILE__, __LINE__);
  }

  // test destructor/constructor(s):
  //
  SysString temp(L"shivali");
  NameMap nmap_1(temp);

  if (level_a > Integral::BRIEF) {
    nmap_1.debug(L"namemap");
  }
    
  // reset indentation
  //
  if (level_a > Integral::NONE) {
    Console::decreaseIndention();
  }

  //--------------------------------------------------------------------------
  //
  // 3. class-specific public methods:
  //     get methods
  //
  //--------------------------------------------------------------------------

  // set indentation
  //
  if (level_a > Integral::NONE) {
    Console::put(L"testing class-specific public methods: get methods...\n");
    Console::increaseIndention();
  }

  // create a name map object
  //
  NameMap nmap(L"name0, name1, name2, name3, name4, name5, name6");

  // test the getName methods
  //
  if (nmap.getName(0).ne(L"name0") 
      || nmap.getName(1).ne(L"name1")
      || nmap.getName(2).ne(L"name2")
      || nmap.getName(3).ne(L"name3")
      || nmap.getName(4).ne(L"name4")
      || nmap.getName(5).ne(L"name5")
      || nmap.getName(6).ne(L"name6")) {
    nmap.debug(L"nmap");
    return Error::handle(name(), L"getName", Error::TEST, __FILE__, __LINE__);
  }

  // test getIndex
  //
  SysString name0(L"name0");
  SysString name1(L"name1");
  SysString name2(L"name2");
  SysString name3(L"name3");
  SysString name4(L"name4");
  SysString name5(L"name5");
  SysString name6(L"name6");

  if ((nmap.getIndex(name0) != 0)
      || (nmap.getIndex(name1) != 1)
      || (nmap.getIndex(name2) != 2)
      || (nmap.getIndex(name3) != 3)
      || (nmap.getIndex(name4) != 4)
      || (nmap.getIndex(name5) != 5)
      || (nmap.getIndex(name6) != 6)) {
    return Error::handle(name(), L"getIndex", Error::TEST, __FILE__, __LINE__);
  }
  
  // test operator() overloads
  //
  if (nmap(0).ne(L"name0")
      || nmap(1).ne(L"name1")
      || nmap(2).ne(L"name2")
      || nmap(3).ne(L"name3")
      || nmap(4).ne(L"name4")
      || nmap(5).ne(L"name5")
      || nmap(6).ne(L"name6")) {
    return Error::handle(name(), L"getName", Error::TEST, __FILE__, __LINE__);
  }
  
  if ((nmap(name0) != 0)
      || (nmap(name1) != 1)
      || (nmap(name2) != 2)
      || (nmap(name3) != 3)
      || (nmap(name4) != 4)
      || (nmap(name5) != 5)
      || (nmap(name6) != 6)) {
    return Error::handle(name(), L"getIndex", Error::TEST, __FILE__, __LINE__);
  }
  
  // reset indentation
  //
  if (level_a > Integral::NONE) {
    Console::decreaseIndention();
  }
  
  //--------------------------------------------------------------------------
  //
  // 4. class-specific public methods:
  //     special i/o methods
  //
  //--------------------------------------------------------------------------

  // set indentation
  //
  if (level_a > Integral::NONE) {
    Console::put(L"testing class-specific public methods: special i/o methods...\n");
    Console::increaseIndention();
  }
  
  // test i/o methods
  //
  NameMap io_nmap(L"type0, type1, type2");

  int32 byte = io_nmap.elementSofSize();

  if (byte != 4) {
    return Error::handle(name(), L"elementSofSize", Error::TEST,
			 __FILE__, __LINE__);
  }

  // we need binary and text sof files
  //
  SysString tmp_filename0;
  Integral::makeTemp(tmp_filename0);
  SysString tmp_filename1;
  Integral::makeTemp(tmp_filename1);

  // open files in write mode
  //
  Sof tmp_file0;
  tmp_file0.open(tmp_filename0, File::WRITE_ONLY, File::TEXT);
  Sof tmp_file1;
  tmp_file1.open(tmp_filename1, File::WRITE_ONLY, File::BINARY);

  SysString myobj(L"MyObject");

  if (!tmp_file0.put(myobj, 0, -1)) {
    return Error::handle(name(), L"put", Error::TEST, __FILE__, __LINE__);
  }
  if (!tmp_file1.put(myobj, 0, 7 * nmap.elementSofSize())) {
    return Error::handle(name(), L"put", Error::TEST, __FILE__, __LINE__);
  }

  NameMap pnames(L"val0,val1,val2,val3,val4,val5,val6");
  
  // write the values
  //
  for (int32 i = 0; i <= 6; i++) {
    nmap.writeElementData(tmp_file0, pnames(i), i);
    nmap.writeElementData(tmp_file1, pnames(i), i);
  }

  // close the files
  //
  tmp_file0.close();
  tmp_file1.close();

  // open the files in read mode
  //
  tmp_file0.open(tmp_filename0);
  tmp_file1.open(tmp_filename1);

  // read the value back
  //
  if (!tmp_file0.find(myobj, 0) || !tmp_file1.find(myobj, 0)) {
    return Error::handle(name(), L"find", Error::TEST, __FILE__, __LINE__);
  }
   
  for (int32 i = 0; i <= 6; i++) {
    int32 read_0;
    int32 read_1;
    nmap.readElementData(read_0, tmp_file0, pnames(i));
    nmap.readElementData(read_1, tmp_file1, pnames(i));

    if ((read_0 != i) || (read_1 != i)) {
      return Error::handle(name(), L"read", Error::TEST, __FILE__, __LINE__);
    }
  }
  
  // close and  delete the temporary files
  //
  tmp_file0.close();
  tmp_file1.close();

  File::remove(tmp_filename0);
  File::remove(tmp_filename1);

  // reset indentation
  //
  if (level_a > Integral::NONE) {
    Console::decreaseIndention();
  }
  //--------------------------------------------------------------------------
  //
  // 5. print completion message
  //
  //--------------------------------------------------------------------------
  
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
