// file: $isip/class/io/SofParser/sofp_02.cc
// version: $Id: sofp_02.cc 7062 2001-06-11 03:42:08Z hamaker $
//

// isip include files
//
#include "SofParser.h"

// method: diagnose
//
// arguments:
//  Integral::DEBUG level: (input) debug level for diagnostics
//
// return: a bool8 value indicating status
//
bool8 SofParser::diagnose(Integral::DEBUG level_a) {
  
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

  // test constructors
  //
  SofParser parser0;
  SofParser parser1(parser0);
  
  // test the debug methods
  //
  parser0.setDebug(Integral::NONE);
  
  if (level_a > Integral::BRIEF) {
    parser0.debug(L"debug");
  }
  
  // reset indentation
  //
  if (level_a > Integral::NONE) {
    Console::decreaseIndention();
  }

  //--------------------------------------------------------------------------
  //
  // 2. class-specific public methods:
  //     extensions to required methods
  //
  //--------------------------------------------------------------------------
  
  // set indentation
  //
  if (level_a > Integral::NONE) {
    Console::put(L"testing class-specific public methods: extensions to required methods...\n");
    Console::increaseIndention();
  }
  
  SysChar terminator_char(L'.');
  SysChar assignment_char(DEF_ASSIGNMENT_CHAR);
  SysChar comment_char(DEF_COMMENT_CHAR);
  SysChar blockstart_char(DEF_BLOCKSTART_CHAR);
  SysChar blockstop_char(DEF_BLOCKSTOP_CHAR);
  SysChar delimiter_char(DEF_DELIMITER_CHAR);
  
  // test constructor 
  //
  SofParser parser2(terminator_char, assignment_char, comment_char,
		    blockstart_char, blockstop_char, delimiter_char);
  // get the memsize
  //
  int32 mem_size = parser2.memSize();
  
  if (level_a > Integral::BRIEF) {
    SysString numeric;
    numeric.assign(mem_size);
    SysString output(L"memSize of parser2: ");
    output.concat(numeric);
    Console::put(output);
  }

  // reset indentation
  //
  if (level_a > Integral::NONE) {
    Console::decreaseIndention();
  }

  //---------------------------------------------------------------------------
  //
  // 3. class-specific public methods:
  //     parser operation methods
  //
  //---------------------------------------------------------------------------
  
  // set indentation
  //
  if (level_a > Integral::NONE) {
    Console::put(L"testing class-specific public methods: parser operation methods...\n");
    Console::increaseIndention();
  }
  
  // let's try to overflow the buffer with a vector.
  //
  
  // first create a big vector
  //
  int32 test_size = 2000;
  int32 test_vec[test_size];
  int32 ref_vec[test_size];
  
  // make a simple linear function for the values
  //
  for (int32 i = 0; i < test_size; i++) {
    ref_vec[i] = i * 3 + 7;
  }
  
  // create an sof file
  //
  Sof sof0;
  SysString temp_file;
  SysString cvname(L"TestVector");
  SysString clname(L"TestList");
  SysString pname(L"values");
  Integral::makeTemp(temp_file);
  
  // open the new text file and add an entry into it
  //
  if (!sof0.open(temp_file, File::WRITE_ONLY, File::TEXT)) {
    Error::handle(name(), L"open", Error::TEST, __FILE__, __LINE__);
  }
  
  sof0.put(cvname, 12, Sof::ANY_SIZE);
  
  // write the values
  //
  SysString output;
  SysString numeric;
  SysString delim_str(L", # quick comment\n");
  
  output.assign(pname);
  output.concat(L" = ");
  numeric.assign(ref_vec[0]);
  output.concat(numeric);
  sof0.puts(output);

  for (int32 i = 1; i < test_size; i++) {
    numeric.assign(ref_vec[i]);
    output.assign(delim_str);
    output.concat(numeric);
    sof0.puts(output);
  }

  // write the terminator and a newline
  //
  output.assign(L";\n");
  sof0.puts(output);

  // add an entry to the sof file (for a single element vector)
  //
  sof0.put(cvname, 14, Sof::ANY_SIZE);
  output.assign(pname);
  output.concat(L" = 137;\n");
  sof0.puts(output);
  
  // add an entry to the sof file (for a zero element vector)
  //
  sof0.put(cvname, 17, Sof::ANY_SIZE);
  output.assign(pname);
  output.concat(L" = ;\n");
  sof0.puts(output);
  
  sof0.put(cvname, 18, Sof::ANY_SIZE);
  output.assign(pname);
  output.concat(L"=;\n");
  sof0.puts(output);
  
  sof0.close();
  sof0.setDebug(Integral::NONE);
  
  // open the file in read mode
  //
  sof0.open(temp_file);

  // find the parameter cvname with tag 12, this will position sof to cvname.12
  //
  int32 tag = 12;
  if (!sof0.find(cvname, tag)) {
    Error::handle(name(), L"find", Error::TEST, __FILE__, __LINE__);
  }
  
  // declare a parser
  //
  SofParser parser;
  parser.setDebug(Integral::NONE);

  // load into the parser
  //
  parser.load(sof0, SofParser::FULL_OBJECT);
  
  // test parameter name retrieval
  //
  int32 num_params = parser.countParams();
  SysString names[num_params];
  if (parser.getParams(names, num_params) != num_params) {
    return Error::handle(name(), L"getParams", Error::TEST,__FILE__, __LINE__);
  }
    
  if (!parser.checkParams(names, num_params)) {
    return Error::handle(name(), L"checkParams", Error::TEST,
			 __FILE__, __LINE__);
  }
  
  // open an sof file in write text
  //
  SysString file;
  Integral::makeTemp(file);
  
  Sof sof_present;
  sof_present.open(file, File::WRITE_ONLY, File::TEXT);
  
  SysString n1(L"Int32");
  SysString n2(L"Int16");
  SysString n3(L"Float32");
  SysString n4(L"Error");
  parser.table_d.add(n1);
  parser.table_d.add(n2);
  parser.table_d.add(n3);

  if (!parser.isPresent(sof_present, n1)) {
    return Error::handle(name(), L"isPresent", Error::TEST,
			 __FILE__, __LINE__);
  }

  sof_present.close();
  
  // open an sof file in write binary
  //
  sof_present.open(file, File::WRITE_ONLY, File::BINARY);
  
  if (!parser.isPresent(sof_present, n4)) {
    return Error::handle(name(), L"isPresent", Error::TEST,
			 __FILE__, __LINE__);
  }
  
  // close and delete the temporary file
  //
  sof_present.close();
  File::remove(file);
  
  // count tokens
  //
  int32 nelem = parser.countTokens(pname);
  
  // debugging statement
  //
  if (level_a > Integral::BRIEF) {
    output.assign(nelem);
    output.insert(L"setting VectorLong::size_d = ", 0);
    output.concat(L": ");
    output.concat(pname);
    Console::put(output);
  }
  
  // local variable
  //
  int32 TEXT_READ_SIZE = 33;
  
  SysString input;
  int32 val;
  int32 pos = 0;
  
  // read a block of data at a time
  //
  int32 read_size;
  int32 offset = 0;
  SysString tokens;
  
  if (nelem > TEXT_READ_SIZE) {
    read_size = TEXT_READ_SIZE;
    nelem -= TEXT_READ_SIZE;
  }
  else {
    read_size = nelem;
    nelem = 0;
  }

  while (read_size > 0) {
    
    // read elements (offset, offset + read_size)
    //
    if (!parser.read(input, sof0, parser.getEntry(sof0, pname, offset,
						  read_size))) {
      Error::handle(name(), L"read", Error::TEST, __FILE__, __LINE__);
    }
    
    // tokenize the input string into substrings, get the integer
    // value from the substring and assign it to test vector. 
    //

    // initialize "pos" to be 0 before every call of tokenize for one
    // input string
    //
    pos = 0;
    for (int32 k = 0; k < read_size; k++) {
      if (input.tokenize(tokens, pos, DEF_DELIMITER_CHAR)) {
	tokens.trim();
	tokens.get(val);
	test_vec[k + offset] = val;
      }
    }
    
    // debugging statement
    //
    if (level_a > Integral::DETAILED) {
      output.assign(L"read values ");
      numeric.assign(test_vec[0 + offset]);
      output.concat(numeric);
      output.concat(L" through ");
      numeric.assign(test_vec[offset + read_size - 1]);
      output.concat(numeric);
      Console::put(output);
    }
    
    offset += read_size;
    if (nelem > TEXT_READ_SIZE) {
      read_size = TEXT_READ_SIZE;
      nelem -= TEXT_READ_SIZE;
    }
    else {
      read_size = nelem;
      nelem = 0;
    }	
  }

  // check the read results
  //
  for (int32 i = 0; i < test_size; i++) {
    if (test_vec[i] != ref_vec[i]) {
      output.assign(i);
      output.insert(L"element ", 0);
      output.concat(L" inconsistent: ref = ");
      numeric.assign((int32)ref_vec[i]);
      output.concat(numeric);
      output.concat(L", hyp = ");
      numeric.assign((int32)test_vec[i]);
      output.concat(numeric);
      Console::put(output);

      Error::handle(name(), L"read", Error::TEST, __FILE__, __LINE__);
    }
  }

  // position sof0 to the parameter cvname with tag 14
  //
  tag = 14;
  if (!sof0.find(cvname, tag)) {
    Error::handle(name(), L"find", Error::TEST, __FILE__, __LINE__);
  }
  
  // reset
  //
  parser.reset();
  parser.setDebug(Integral::NONE);
  
  // load the parser
  //
  parser.load(sof0, SofParser::FULL_OBJECT);
  
  nelem = parser.countTokens(pname);
  
  // debugging statement
  //
  if (level_a > Integral::BRIEF) {
    output.assign(nelem);
    output.insert(L"setting VectorLong::size_d = ", 0);
    output.concat(L": ");
    output.concat(pname);
    Console::put(output);
  }

  // test getEntry methods
  //
  SysString sval;
  if (!parser.read(sval, sof0, parser.getEntry(sof0, pname, 0, 1))) {
    Error::handle(name(), L"read", Error::TEST, __FILE__, __LINE__);
  }
  
  int32 lval;
  sval.get(lval);
  
  if (lval != 137) {
    Error::handle(name(), L"read", Error::TEST, __FILE__, __LINE__);
  }
  
  if (level_a > Integral::BRIEF) {
    Console::put(L"testing zero length vectors");
  }

  // position the sof0 to the parameter cvname with tag 17
  //
  tag = 17;
  if (!sof0.find(cvname, tag)) {
    Error::handle(name(), L"find", Error::TEST, __FILE__, __LINE__);
  }
  
  parser.reset();
  parser.setDebug(Integral::NONE);
  
  // load the parser
  //
  parser.load(sof0, SofParser::FULL_OBJECT);
  
  if (parser.countTokens(pname) != 0) {
    return Error::handle(name(), L"countTokens",Error::TEST,__FILE__,__LINE__);
  }
  
  // position the sof0 to the parameter cvname with tag 18
  //
  tag = 18;
  if (!sof0.find(cvname, tag)) {
    Error::handle(name(), L"find", Error::TEST, __FILE__, __LINE__);
  }

  parser.reset();
  parser.setDebug(Integral::NONE);
  
  // load the parser
  //
  parser.load(sof0, SofParser::FULL_OBJECT);
  
  if (parser.countTokens(pname) != 0) {
    return Error::handle(name(), L"countTokens",Error::TEST,__FILE__,__LINE__);
  }

  // now test some implicit parameter stuff
  //

  // close and delete the temporary file
  //
  sof0.close();
  File::remove(temp_file);
  
  // test setImplicitParam and setNest
  //
  parser.setImplicitParam();
  parser.setNest();
  
  // try to read a complex nested file: the Features class
  //
  SysString nest_file(L"diagnose_test00.sof");
  sof0.open(nest_file);
  SysString features(L"Features");

  // position sof0 to features with tag 0
  //
  if (!sof0.find(features, 0)) {
    return Error::handle(name(), L"open", Error::TEST, __FILE__, __LINE__);
  }
  parser.reset();
  parser.setDebug(Integral::NONE);
  parser.load(sof0, FULL_OBJECT);
  
  SysString front_end(L"front_end");
  int32 size = parser.getEntry(sof0, front_end);
  
  if (size < 1) {
    return Error::handle(name(), L"getEntry", Error::TEST, __FILE__, __LINE__);
  }

  // declare a sub parser
  //
  SofParser sub_parser;
  sub_parser.setNest();
  sub_parser.load(sof0, size);
  if (level_a > Integral::DETAILED) {
    sub_parser.debug(L"sub object");
  }
  
  SysString window_duration(L"window_duration");
  size = sub_parser.getEntry(sof0, window_duration);
  if (size != 25) {
    return Error::handle(name(), L"getEntry", Error::TEST, __FILE__, __LINE__);
  }
  
  SysString buf;
  if (!sub_parser.read(buf, sof0, size)) {
    return Error::handle(name(), L"read", Error::TEST, __FILE__, __LINE__);
  }
  if (!buf.eq(L"2.50000000000000014e-02")) {
    return Error::handle(name(), L"read", Error::TEST, __FILE__, __LINE__);
  }
  
  // now try to read the other test object to test the checking of params
  //
  {
    SysString test_obj(L"TestObject");

    // position the sof0 to TestObject with tag 0
    //
    if (!sof0.find(test_obj, 0)) {
      return Error::handle(name(), L"open", Error::TEST, __FILE__, __LINE__);
    }
    parser.reset();
    parser.setDebug(Integral::NONE);
    parser.load(sof0, FULL_OBJECT);

    // check its parameters
    //
    if (level_a > Integral::BRIEF) {
      SysString good_param(L"good_param");
      int32 size = parser.getEntry(sof0, good_param);
      
      // the second parameter of TestObject 0 is extra
      //
      if (parser.checkParams(sof0)) {
	return Error::handle(name(), L"diagnose", Error::TEST,
			     __FILE__, __LINE__);
      }
      
      SysString bad_param(L"bad_param");
      size = parser.getEntry(sof0, bad_param);
      if (!parser.checkParams(sof0)) {
	return Error::handle(name(), L"diagnose", Error::TEST,
			     __FILE__, __LINE__);
      }
    }
  }
  
  sof0.close();

  {
    Sof sof1;
    sof1.open(L"diagnose_test01.sof");
    SysString cname(L"Features");
    sof1.find(cname, 0);
    SofParser parser1;
    parser1.load(sof1);

    SysString pname(L"values");

  
    if (parser1.getEntry(sof1, pname) != 35745) {
      return Error::handle(name(), L"getEntry", Error::TEST, __FILE__,
			   __LINE__);
    }

    pname.assign(L"data_mode");
    if (parser1.getEntry(sof1, pname) != 16) {
      return Error::handle(name(), L"getEntry", Error::TEST, __FILE__,
			   __LINE__);
    }

    sof1.close();
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
