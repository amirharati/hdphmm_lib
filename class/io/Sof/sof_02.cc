// file: $isip/class/io/Sof/sof_02.cc
// version: $Id: sof_02.cc 8121 2002-04-17 20:22:34Z huang $
//

// isip include files
//
#include "Sof.h"
#include <Console.h>

// method: diagnose
//
// arguments:
//  Integral::DEBUG level: (input) debug level for diagnostics
//
// return: a bool8 value indicating status
//
bool8 Sof::diagnose(Integral::DEBUG level_a) {

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
  
  // test constructor
  //
  Sof sof_0;
  
  // test debug methods
  //
  sof_0.setDebug(Integral::BRIEF);
  
  if (level_a > Integral::BRIEF) {
    sof_0.debug(L"debug");
  }

  // open a file in write mode
  //
  SysString file0;
 
  Integral::makeTemp(file0);
  File::registerTemp(file0);
  
  if (!sof_0.open(file0, File::WRITE_ONLY, File::BINARY)) {
    return Error::handle(name(), L"open", Error::TEST, __FILE__, __LINE__);
  }
  
  // test clear methods, note clear is only used for writable Sof
  //
  sof_0.clear();

  if (sof_0.getNameCount() != 0) {
    return Error::handle(name(), L"clear", Error::TEST, __FILE__, __LINE__);
  }       

  // close file
  //
  sof_0.close();
  File::remove(file0);
    
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
  int32 mem_size = sof_0.memSize();
  
  if (level_a > Integral::BRIEF) {
    SysString numeric;
    numeric.assign(mem_size);
    SysString output(L"memSize of sof_0: ");
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
  //     file operation methods
  //
  //--------------------------------------------------------------------------

  // set indentation
  //
  if (level_a > Integral::NONE) {
    Console::put(L"testing class-specific public methods: file operation methods...\n");
    Console::increaseIndention();
  }
  
  Sof sof0;
  Sof sof1;
  Sof sof2;
  Sof sof3;
  
  // create some temporary filenames
  //
  SysString file1;
  SysString file2;
  SysString file3;
  
  SysString long_cname(L"Int32");
  SysString short_cname(L"Int16");
  SysString string_cname(L"String");
  
  Integral::makeTemp(file0);
  File::registerTemp(file0);
  
  // test a bin file
  Integral::makeTemp(file1);
  File::registerTemp(file1);
  

  // test a ascii file
  Integral::makeTemp(file2);
  File::registerTemp(file2);
    
  Integral::makeTemp(file3);
  File::registerTemp(file3);
  
  // open files for write (text & binary)
  //
  if (!sof0.open(file0, File::WRITE_ONLY)) {
    return Error::handle(name(), L"open", Error::TEST, __FILE__, __LINE__);
  }
  if (!sof1.open(file1, File::WRITE_ONLY, File::BINARY)) {
    return Error::handle(name(), L"open", Error::TEST, __FILE__, __LINE__);
  }

  if (sof0.getName().ne(file0)) {
    return Error::handle(name(), L"getName", Error::TEST, __FILE__, __LINE__);
  }

  if (sof0.getExpandedName().ne(file0)) {
    return Error::handle(name(), L"getExpandedName", Error::TEST, __FILE__,
			 __LINE__);
  }

  // add a int32 entry to the files
  //
  int32 j = 27;
  sof0.put(long_cname, Sof::ANY_SIZE);
  sof1.put(long_cname, 0, sizeof(int32));
  
  // write the text value
  //
  sof0.increaseIndention();
  sof0.setLineWrap(100);
  sof0.decreaseIndention();
  
  SysString output;
  output.assign((int32)j);
  output.insert(L"value = ", 0);
  output.concat(L"\n");
  sof0.puts(output);

  // write the binary value
  //
  sof1.write(&j, sizeof(j), 1);
  
  // add another int32 entry to the files
  //
  j = 277;
  sof0.put(long_cname, Sof::ANY_SIZE);
  sof1.put(long_cname, 1, sizeof(int32));
  
  // write the text value
  //
  output.assign((int32)j);
  output.insert(L"value = ", 0);
  output.concat(L"\n");
  sof0.puts(output);

  // write the binary value
  //
  sof1.write(&j, sizeof(j), 1);
  
  // print out debug information
  //
  if (level_a > Integral::DETAILED) {
    sof1.setDebug(Integral::NONE);
    sof1.debug(L"sof1");
  }

  // test set and get methods
  //
  sof0.setLockRetry((int32)1);
  sof0.setDelimiter(DEF_DELIMITER);

  if (sof0.getDelimiter() != DEF_DELIMITER) {
    return Error::handle(name(), L"set/getDelimiter", Error::TEST, __FILE__,
			 __LINE__);
  }
  
  // test file queries
  //
  if (!sof0.isSof() || !isSof(file0)) {
    return Error::handle(name(), L"isSof", Error::TEST, __FILE__, __LINE__);
  }
  
  if (!sof0.isText() || !sof1.isBinary()) {
    return Error::handle(name(), L"isText / isBinary", Error::TEST, __FILE__,
			 __LINE__);
  }

  if (!sof0.isOpen() || !sof1.isOpen()) {
    return Error::handle(name(), L"isOpen", Error::TEST, __FILE__, __LINE__);
  }
  
  if (sof0.isSameFile(sof1)) {
    return Error::handle(name(), L"isSameFile", Error::TEST, __FILE__,
			 __LINE__);
  }
  
  // test clear the file
  //                    
  sof1.clear();

  if (sof1.getNameCount() != 0) {
    return Error::handle(name(), L"clear", Error::TEST, __FILE__, __LINE__);
  }       
  
  // close the files
  //
  sof0.close();
  sof1.close();
  
  if (sof0.isOpen() || sof1.isOpen()) {
    return Error::handle(name(), L"isOpen", Error::TEST, __FILE__, __LINE__);
  }
  
  // reset indentation
  //
  if (level_a > Integral::NONE) {
    Console::decreaseIndention();
  }

  //--------------------------------------------------------------------------
  //
  // 4. class-specific public methods:
  //     object operation methods
  //
  //--------------------------------------------------------------------------

  // set indentation
  //
  if (level_a > Integral::NONE) {
    Console::put(L"testing class-specific public methods: object operation methods...\n");
    Console::increaseIndention();
  }
  
  // open files again in read plus
  //
  if (!sof2.open(file0, File::READ_PLUS)) {
    return Error::handle(name(), L"diagnose", Error::ARG, __FILE__, __LINE__);
  }
  
  if (!sof3.open(file1, File::READ_PLUS, File::BINARY)) {
    return Error::handle(name(), L"diagnose", Error::ARG, __FILE__, __LINE__);
  }
  
  // read all the text values
  //
  int32 tag;
  for (tag = sof2.first(long_cname); tag != Sof::NO_TAG;
       tag = sof2.next(long_cname, tag)) {
    
    // find the node
    //
    sof2.find(long_cname, tag);
    
    SysString input;

    // this gets should work
    //
    if (!sof2.gets(input)) {
      return Error::handle(name(), L"gets", Error::TEST, __FILE__, __LINE__);
    }
    
    if (input.firstStr(L"value = ") != 0) {
      return Error::handle(name(), L"gets", Error::TEST, __FILE__, __LINE__);
    }
    SysString numeric;
    input.substr(numeric, 8);
    if (!numeric.get(j)) {
      return Error::handle(name(), L"gets", Error::TEST, __FILE__, __LINE__);
    }
    
    // we have read all the data on the line, so this gets should fail
    //
    if (sof2.gets(input)) {
      return Error::handle(name(), L"gets", Error::TEST, __FILE__, __LINE__);
    }

    if (level_a > Integral::BRIEF) {
      output.assign((int32)j);
      output.insert(L"reading from text: ", 0);
      Console::put(output);
    }
  }
  
  // read all the binary values
  //
  for (tag = sof3.last(long_cname); tag != Sof::NO_TAG;
       tag = sof3.prev(long_cname, tag)) {

    // find the node
    //
    sof3.find(long_cname, tag);

    if (sof3.read(&j, sizeof(j), 1) != 1) {
      return Error::handle(name(), L"read", Error::TEST, __FILE__, __LINE__);
    }
    
    if (level_a > Integral::BRIEF) {
      output.assign((int32)j);
      output.insert(L"reading from Binary: ", 0);
      Console::put(output);
    }
  }
  
  int32 NUM_CLASSES = 10;               
  int32 NUM_TAGS = 3;
  
  // sof3.setDebug(Integral::DETAILED);
  // sof0.setDebug(Integral::DETAILED);
  
  // add a whole bunch of names to the binary file
  //
  for (int32 i = 0; i < NUM_CLASSES; i++) {

    // create a name
    //
    SysString cname;
    cname.assign((int32)i);
    cname.insert(L"LongerNamedEntity", 0);

    // add multiple nodes
    //
    for (int32 j = 0; j < NUM_TAGS; j++) {

      // add the node
      //
      sof3.put(cname, j, sizeof(int32));

      // create and write a value
      //
      int32 val = i * 10277 + j * 13;
      sof3.write(&val, sizeof(val), 1);
    }
  }
  
  // test copy methods
  //
  if (level_a > Integral::BRIEF) {
    Console::put(L"testing copy (text)");
  }

  SysString foo_copy;
  Integral::makeTemp(foo_copy);
  File::registerTemp(foo_copy);
  
  sof1.open(foo_copy, File::WRITE_ONLY, File::TEXT);
  tag = sof2.first(long_cname);
  
  if (tag != Sof::NO_TAG) {
    
    // copy the first Int32 number from sof2
    //
    sof1.copy(0, sof2, long_cname, tag);
    
    if (sof1.getCount(long_cname) != 1) {
      return Error::handle(name(), L"copy", Error::TEST, __FILE__, __LINE__);
    } 
    
    // remove this tag
    //
    sof1.remove(long_cname, 0);
    
    // copy all the Long numbers from sof2
    //
    sof1.copy(sof2, long_cname);
    if (sof1.getCount(long_cname) != sof2.getCount(long_cname)) {
      return Error::handle(name(), L"copy", Error::TEST, __FILE__, __LINE__);
    }
  }
  
  // close the files
  //
  sof1.close();
  sof2.close();
  sof3.close();

  // open the binary file again
  //
  sof0.open(file1, File::READ_PLUS, File::BINARY);

  int32 count = 0;
  
  // read all the dynamically named nodes
  //
  for (int32 i = 0; i < NUM_CLASSES; i++) {
    
    // create a name
    //
    SysString cname;
    cname.assign((int32)i);
    cname.insert(L"LongerNamedEntity", 0);

    // read all the nodes of this name
    //
    for (tag = sof0.first(cname); tag != Sof::NO_TAG;
	 tag = sof0.next(cname, tag)) {
      
      // find the node
      //
      if (!sof0.find(cname, tag)) {
	return Error::handle(name(), L"find", Error::TEST, __FILE__, __LINE__);
      }
      
      int32 val = i * 10277 + tag * 13;
      int32 j;
      count++;
      
      if (sof0.read(&j, sizeof(j), 1) != 1) {
	return Error::handle(name(), L"read", Error::TEST, __FILE__, __LINE__);
      }

      if (j != val) {
	return Error::handle(name(), L"mismatch", Error::TEST, __FILE__,
			     __LINE__);
      }
    }
  }

  // check count
  //
  if (count != NUM_CLASSES * NUM_TAGS) {
    return Error::handle(name(), L"not enough", Error::TEST, __FILE__,
			 __LINE__);
  }

  // test delete
  //
  if (level_a > Integral::BRIEF) {
    Console::put(L"testing remove (binary)");
  }
  
  // go back through, delete every other entry
  //
  for (int32 i = 0; i < NUM_CLASSES; i += 2) {
    
    // create a name
    //
    SysString cname;
    cname.assign((int32)i);
    cname.insert(L"LongerNamedEntity", 0);
    
    if ((i % 4) == 0) {
      // read all the nodes of this name
      //
      for (tag = sof0.first(cname); tag != Sof::NO_TAG;
	   tag = sof0.next(cname, tag)) {
	
	// remove node
	//
	if (!sof0.remove(cname, tag)) {
	  return Error::handle(name(), L"remove1", Error::TEST,
			       __FILE__, __LINE__);
	}
      }
    }
    
    // delete all instances of this name
    //
    else if (!sof0.remove(cname)) {
      return Error::handle(name(),L"remove2",Error::TEST,__FILE__,__LINE__);
    }
    
    if (sof0.getCount(cname) != 0) {
      return Error::handle(name(), L"remove", Error::TEST, __FILE__, __LINE__);
    }
  }
  
  sof0.cleanUp();
  
  if (sof0.getCount() != 0) {
    return Error::handle(name(), L"remove", Error::TEST, __FILE__, __LINE__);
  }
  
  sof0.close();

  // testing read after delete
  //
  if (level_a > Integral::BRIEF) {
    SysString output(L"testing read after delete (binary)");
    Console::put(output);
  }

  // open the file again
  //
  sof0.open(file1);
  
  count = 0;
  
  // read all the dynamically named nodes
  //
  for (int32 i = 1; i < NUM_CLASSES; i += 2) {

    // create a name
    //
    SysString cname;
    cname.assign((int32)i);
    cname.insert(L"LongerNamedEntity", 0);
    
    // read all the nodes of this name
    //
    for (tag = sof0.first(cname); tag != Sof::NO_TAG;
	 tag = sof0.next(cname, tag)) {
      
      // find the node
      //
      if (!sof0.find(cname, tag)) {
	return Error::handle(name(), L"find", Error::TEST, __FILE__, __LINE__);
      }
      
      int32 val = i * 10277 + tag * 13;
      int32 j;
      count++;
      
      if (sof0.read(&j, sizeof(j), 1) != 1) {
	return Error::handle(name(), L"read", Error::TEST, __FILE__, __LINE__);
      }

      if (j != val) {
	return Error::handle(name(),L"mismatch",Error::TEST,__FILE__,__LINE__);
      }
    }
  }

  if (count != NUM_CLASSES * NUM_TAGS / 2) {
    return Error::handle(name(),L"not enough 2",Error::TEST,__FILE__,__LINE__);
  }
  
  // close the file
  //
  sof0.close();
  
  // add a whole bunch of names to the text file
  //
  NUM_CLASSES = 20;
  
  sof2.open(file2, File::WRITE_PLUS);
  
  for (int32 i = 0; i < NUM_CLASSES; i++) {
    
    // create a name
    //
    SysString cname;
    cname.assign((int32)i);
    cname.insert(L"LongerNamedEntity", 0);
    
    // add multiple nodes
    //
    for (int32 j = 0; j < NUM_TAGS; j++) {

      // add the node
      //
      sof2.put(cname, j, ANY_SIZE);

      // create and write a value
      //
      int32 val = i * 10277 + j * 13;
      
      // write the text value
      //
      output.assign((int32)val);
      output.insert(L"value = ", 0);
      output.concat(L"\n");
      sof2.puts(output);
    }
  }

  // close the files
  //
  sof2.close();
  
  // reset indentation
  //
  if (level_a > Integral::NONE) {
    Console::decreaseIndention();
  }
  
  //--------------------------------------------------------------------------
  //
  // 5. class-specific public methods:
  //     input and output methods
  //
  //--------------------------------------------------------------------------

  // set indentation
  //
  if (level_a > Integral::NONE) {
    Console::put(L"testing class-specific public methods: i/o methods...\n");
    Console::increaseIndention();
  }
  
  // open the text file again
  //
  sof0.open(file2, File::READ_PLUS);

  count = 0;

  SysString input;
  
  // read all the dynamically named nodes
  //
  for (int32 i = 0; i < NUM_CLASSES; i++) {

    // create a name
    //
    SysString cname;
    cname.assign((int32)i);
    cname.insert(L"LongerNamedEntity", 0);
    
    // read all the nodes of this name
    //
    for (tag = sof0.first(cname); tag != Sof::NO_TAG;
	 tag = sof0.next(cname, tag)) {
      
      // find the node
      //
      if (!sof0.find(cname, tag)) {
	return Error::handle(name(), L"find", Error::TEST, __FILE__, __LINE__);
      }

      int32 val = i * 10277 + tag * 13;
      int32 j;
      count++;
      
      if ((!sof0.gets(input)) || (input.firstStr(L"value = ") != 0)) {
	return Error::handle(name(), L"gets", Error::TEST, __FILE__, __LINE__);
      }
      SysString numeric;
      input.substr(numeric, 8);

      if (!numeric.get(j)) {
	return Error::handle(name(), L"gets", Error::TEST, __FILE__, __LINE__);
      }
      
      if (j != val) {
	return Error::handle(name(),L"mismatch",Error::TEST,__FILE__,__LINE__);
      }
    }
  }

  // check count
  //
  if (count != NUM_CLASSES * NUM_TAGS) {
    return Error::handle(name(), L"not enough",Error::TEST,__FILE__,__LINE__);
  }

  // test delete
  //
  if (level_a > Integral::BRIEF) {
    SysString output(L"testing remove (text)");
    Console::put(output);
  }
  
  // go back through, delete every other entry
  //
  for (int32 i = 0; i < NUM_CLASSES; i += 2) {
    
    // create a name
    //
    SysString cname;
    cname.assign((int32)i);
    cname.insert(L"LongerNamedEntity", 0);
    
    if ((i % 4) == 0) {
      // read all the nodes of this name
      //
      for (tag = sof0.first(cname); tag != Sof::NO_TAG;
	   tag = sof0.next(cname, tag)) {
	
	// remove node
	//
	if (!sof0.remove(cname, tag)) {
	  return Error::handle(name(), L"remove1", Error::TEST,
			       __FILE__, __LINE__);
	}
      }
    }
    
    // delete all instances of this name
    //
    else if (!sof0.remove(cname)) {
      return Error::handle(name(), L"remove2", Error::TEST, __FILE__,
			   __LINE__);
    }
  }
  
  sof0.close();
  
  // testing read after delete
  //
  if (level_a > Integral::BRIEF) {
    Console::put(L"testing read after delete (text)");
  }
  
  // open the file again
  //
  sof0.open(file2);

  count = 0;
  
  // read all the dynamically named nodes
  //
  for (int32 i = 1; i < NUM_CLASSES; i += 2) {
    
    // create a name
    //
    SysString cname;
    cname.assign((int32)i);
    cname.insert(L"LongerNamedEntity", 0);
    
    // read all the nodes of this name
    //
    for (tag = sof0.first(cname); tag != Sof::NO_TAG;
	 tag = sof0.next(cname, tag)) {
      
      // find the node
      //
      if (!sof0.find(cname, tag)) {
	return Error::handle(name(), L"find", Error::TEST, __FILE__, __LINE__);
      }
      
      int32 val = i * 10277 + tag * 13;
      int32 j;
      count++;

            
      if ((!sof0.gets(input)) || (input.firstStr(L"value = ") != 0)) {
	return Error::handle(name(), L"gets", Error::TEST, __FILE__, __LINE__);
      }
      SysString numeric;
      input.substr(numeric, 8);

      if (!numeric.get(j)) {
	return Error::handle(name(), L"gets", Error::TEST, __FILE__, __LINE__);
      }
      
      if (j != val) {
	return Error::handle(name(), L"mismatch", Error::TEST,
			     __FILE__, __LINE__);
      }
    }
  }
  
  if (count != NUM_CLASSES * NUM_TAGS / 2) {
    return Error::handle(name(), L"not enough 2", Error::TEST, __FILE__,
			 __LINE__);
  }

  // test enumerate method
  //
  SofList sof0_index;
  SofSymbolTable sof0_table;
  if (!sof0.enumerate(sof0_index, sof0_table)) {
    return Error::handle(name(), L"enumerate", Error::TEST, __FILE__,
			 __LINE__);
  }
  
  // close the file
  //
  sof0.close();

  // test overwriting in binary w/resize
  //
  {
    SysString temp;
    Integral::makeTemp(temp);
    Sof sof;
    sof.open(temp, File::WRITE_ONLY, File::BINARY);
    SysString obj_name(L"MyObject");
    sof.put(obj_name, 0, sizeof(int32));
    int32 a = 5;
    sof.write(&a, sizeof(int32), 1);
    sof.close();

    
    sof.open(temp, File::READ_PLUS, File::BINARY);
    int32 pos = sof.end_of_data_d;
    sof.put(obj_name, 0, sizeof(int32)*2);
    sof.write(&a, sizeof(int32), 1);
    sof.write(&a, sizeof(int32), 1);
    if (sof.end_of_data_d != (pos + (int32)sizeof(int32))) {
      return Error::handle(name(), L"diagnose", Error::TEST,
			   __FILE__, __LINE__);
    }
    sof.close();
  }

  // reset indentation
  //
  if (level_a > Integral::NONE) {
    Console::decreaseIndention();
  }
  
  //--------------------------------------------------------------------------
  //
  // 6. class-specific public methods:
  //     formatting methods
  //
  //--------------------------------------------------------------------------

  // set indentation
  //
  if (level_a > Integral::NONE) {
    Console::put(L"testing class-specific public methods: formatting methods...\n");
    Console::increaseIndention();
  }
  
  // open the file again
  //
  sof0.open(file0, File::WRITE_ONLY);
    
  // increase indentation
  //
  sof0.increaseIndention();
  sof0.setLineWrap(100);
  
  if (sof0.getLineWrap() != 100) {
    return Error::handle(name(), L"set/getLineWrap", Error::TEST,
			 __FILE__, __LINE__);
  }
  if (sof0.getLineLength() != 100 - (File::INDENT_STR).length()) {
    return Error::handle(name(), L"set/getLineLength", Error::TEST,
			 __FILE__, __LINE__);
  }
  
  // decrease indentation
  //
  sof0.decreaseIndention();
  
  if (sof0.getLineLength() != 100) {
    return Error::handle(name(), L"set/getLineLength", Error::TEST,
			 __FILE__, __LINE__);
  }
  
  sof0.close();
  
  // delete temporary files
  //
  //File::remove(file0);
  //File::remove(file1);
  //File::remove(L"/tmp/foo_asc.sof");
  //File::remove(L"/tmp/foo_copy.sof");

  // reset indentation
  //
  if (level_a > Integral::NONE) {
    Console::decreaseIndention();
  }
  
  //---------------------------------------------------------------------------
  //
  // 7. print completion message
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
