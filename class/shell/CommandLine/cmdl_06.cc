// file: $isip/class/shell/CommandLine/cmdl_06.cc
// version: $Id: cmdl_06.cc 9240 2003-06-23 21:59:42Z parihar $
//

// isip include files
// 
#include "CommandLine.h"
#include "SingleLinkedList.h"

// method: parse
//
// arguments:
//  int argc: (input) number of parameters on the command line
//  const char** argv: (input) parameters on the command line
//
// return: a bool8 value indicating status
//
// this method parses the command line options
//
bool8 CommandLine::parse(int argc_a, const char** argv_a) {

  // access the program name from commandline
  //
  String prog_name;
  prog_name.assign((byte8*)argv_a[0]);
  prog_name_d.assign(prog_name);

  // copy the program name to the actual command line
  //  
  expanded_d.assign(prog_name);

  // if we are using Sdb, add the LIST option
  //
  if (sdb_d != (Sdb*)NULL) {
    options_d.concat(Sdb::LIST_FILE_OPTION);
  }
  
  // create space to save the values
  //
  values_d.setLength(options_d.length());

  // loop over all the commandline options
  //
  for (int32 i = 1; i < argc_a; i++) {
    
    // declare a string and assign commandline options to it
    //
    String token;
    token.assign((byte8*)argv_a[i]);

    if (debug_level_d >= Integral::DETAILED) {
      token.debug(L"parsing token");
    }

    if (token.firstStr(DEF_PARAM_PREFIX) == 0) {
      
      // declare a string to hold the value, and an integer for the index
      //
      String val;
      int32 obj_index = getOptionIndex(token, true);
      
      // bad index returned
      //
      if (obj_index < 0) {
	printUsage();
	return Error::handle(name(), L"parse", ERR_OPT,
			     __FILE__, __LINE__, Error::WARNING);
      }
      
      // user defined options
      //
      else {

	// append expanded option into new command line
	//
	expanded_d.concat(DEF_PARAM_SPACE);
	expanded_d.concat(DEF_PARAM_PREFIX);

	if (obj_index == OPT_INDEX_SDB) {
	  expanded_d.concat(Sdb::LIST_FILE_OPTION);
	}
	else {
	  expanded_d.concat((String)options_d(obj_index));
	  used_d(obj_index).assign(true);
	}

	// bool8 option
	//
	if ((obj_index != OPT_INDEX_SDB) &&
	    types_d(obj_index).eq(Boolean::name())) {
	  ((Boolean*)objects_d[obj_index])->assign(true);
	}
	
	// any option other than a flag requires an argument, so
	// error if this is the last token on the list
	//
	else if (i == (argc_a - 1)) {
	  printUsage();
	  Error::handle(name(), L"parse", ERR_OPTARG,
			__FILE__, __LINE__);
	}

	// other options requiring a value
	//
	else {
	  
	  // convert the next argument to a value and save it
	  //
	  val.assign((byte8*)argv_a[i + 1]);

	  // we only return an option value for non-Sdb options
	  //
	  if (obj_index != OPT_INDEX_SDB) {
	    values_d(obj_index).assign(val);
	  }

	  if (val.firstStr(DEF_PARAM_PREFIX) == 0) {
	    printUsage(); 
	    return Error::handle(name(), L"parse", ERR_OPTARG,
				 __FILE__, __LINE__);
	  }

	  // declare local variables
	  //
	  int32 j = i;

	  // is this the special Sdb list marker? if so, append it to
	  // the sdb object with the list flag set. note that the Sdb
	  // option will only be returned if sdb_d is not null
	  //
	  if (obj_index == OPT_INDEX_SDB) {
	    sdb_d->append(val, true);
	    i++;
	  }
	  
	  // file type option:
	  //  this option is a little different. since it is so low-level,
	  //  we don't have all the name map support for checking for
	  //  valid values. so we have to do it manually.
	  //
	  else if (types_d(obj_index).eq(L"File::TYPE")) {
	    if (val.eq(File::TYPE_TEXT, false)) {
	      *((File::TYPE*)objects_d[obj_index]) = File::TEXT;
	    }
	    else if (val.eq(File::TYPE_BINARY, false)) {
	      *((File::TYPE*)objects_d[obj_index]) = File::BINARY;
	    }
	    else {
	      printUsage(); 
	      return Error::handle(name(), L"parse",
				   ERR_OPTARG,  __FILE__, __LINE__);
	    }
	    i++;
	  }

	  // string option
	  //
	  else if (types_d(obj_index).eq(String::name())) {
	    ((String*)objects_d[obj_index])->assign(val);
	    i++;
	  }

	  // filename option
	  //
	  else if (types_d(obj_index).eq(Filename::name())) {
	    ((Filename*)objects_d[obj_index])->assign(val);
	    i++;
	  }

	  // debug-level option
	  //
	  else if (types_d(obj_index).eq(DebugLevel::name())) {
	    ((DebugLevel*)objects_d[obj_index])->assign(val);
	    i++;
	  }

	  // byte option
	  //
	  else if (types_d(obj_index).eq(Byte::name())) {
	    ((Byte*)objects_d[obj_index])->assign(val);
	    i++;
	  }
	  
	  // ushort option
	  //
	  else if (types_d(obj_index).eq(Ushort::name())) {
	    ((Ushort*)objects_d[obj_index])->assign(val);
	    i++;
	  }
	  
	  // ulong option
	  //
	  else if (types_d(obj_index).eq(Ulong::name())) {
	    ((Ulong*)objects_d[obj_index])->assign(val);
	    i++;
	  }
	  
	  // ullong option
	  //
	  else if (types_d(obj_index).eq(Ullong::name())) {
	    ((Ullong*)objects_d[obj_index])->assign(val);
	    i++;
	  }
	  
	  // short option
	  //
	  else if (types_d(obj_index).eq(Short::name())) {
	    ((Short*)objects_d[obj_index])->assign(val);
	    i++;
	  }

	  // int32 option
	  //
	  else if (types_d(obj_index).eq(Long::name())) {
	    ((Long*)objects_d[obj_index])->assign(val);
	    i++;
	  }
	  
	  // llong option
	  //
	  else if (types_d(obj_index).eq(Llong::name())) {
	    ((Llong*)objects_d[obj_index])->assign(val);
	    i++;
	  }
	  
	  // float option
	  //
	  else if (types_d(obj_index).eq(Float::name())) {
	    ((Float*)objects_d[obj_index])->assign(val);
	    i++;
	  }
	  
	  // double option
	  //
	  else if (types_d(obj_index).eq(Double::name())) {
	    ((Double*)objects_d[obj_index])->assign(val);
	    i++;
	  }

	  // single-linked list for string option
	  //
	  else if (types_d(obj_index).eq(SingleLinkedList<String>::name())) {
	    ((SingleLinkedList<String>*)objects_d[obj_index])->insert(&val);
	    i++;
	  }

	  // single-linked list for filename option
	  //
	  else if (types_d(obj_index).eq(SingleLinkedList<Filename>::name())) {
	    Filename temp;
	    temp.assign(val);
	    ((SingleLinkedList<Filename>*)objects_d[obj_index])->insert(&temp);
	    i++;
	  }

	  // single-linked list for byte option
	  //
	  else if (types_d(obj_index).eq(SingleLinkedList<Byte>::name())) {
	    Byte temp;
	    temp.assign(val);
	    ((SingleLinkedList<Byte>*)objects_d[obj_index])->insert(&temp);
	    i++;
	  }

	  // single-linked list for short option
	  //
	  else if (types_d(obj_index).eq(SingleLinkedList<Short>::name())) {
	    Short temp;
	    temp.assign(val);
	    ((SingleLinkedList<Short>*)objects_d[obj_index])->insert(&temp);
	    i++;
	  }

	  // single-linked list for int32 option
	  //
	  else if (types_d(obj_index).eq(SingleLinkedList<Long>::name())) {
	    Long temp;
	    temp.assign(val);
	    ((SingleLinkedList<Long>*)objects_d[obj_index])->insert(&temp);
	    i++;
	  }

	  // single-linked list for llong option
	  //
	  else if (types_d(obj_index).eq(SingleLinkedList<Llong>::name())) {
	    Llong temp;
	    temp.assign(val);
	    ((SingleLinkedList<Llong>*)objects_d[obj_index])->insert(&temp);
	    i++;
	  }

	  // single-linked list for ushort option
	  //
	  else if (types_d(obj_index).eq(SingleLinkedList<Ushort>::name())) {
	    Ushort temp;
	    temp.assign(val);
	    ((SingleLinkedList<Ushort>*)objects_d[obj_index])->insert(&temp);
	    i++;
	  }

	  // single-linked list for ulong option
	  //
	  else if (types_d(obj_index).eq(SingleLinkedList<Ulong>::name())) {
	    Ulong temp;
	    temp.assign(val);
	    ((SingleLinkedList<Ulong>*)objects_d[obj_index])->insert(&temp);
	    i++;
	  }

	  // single-linked list for ullong option
	  //
	  else if (types_d(obj_index).eq(SingleLinkedList<Ullong>::name())) {
	    Ullong temp;
	    temp.assign(val);
	    ((SingleLinkedList<Ullong>*)objects_d[obj_index])->insert(&temp);
	    i++;
	  }

	  // single-linked list for float option
	  //
	  else if (types_d(obj_index).eq(SingleLinkedList<Float>::name())) {
	    Float temp;
	    temp.assign(val);
	    ((SingleLinkedList<Float>*)objects_d[obj_index])->insert(&temp);
	    i++;
	  }

	  // single-linked list for double option
	  //
	  else if (types_d(obj_index).eq(SingleLinkedList<Double>::name())) {
	    Double temp;
	    temp.assign(val);
	    ((SingleLinkedList<Double>*)objects_d[obj_index])->insert(&temp);
	    i++;
	  }

	  // one option found above
	  //
	  if (j != i) {

	    // append option to new command line
	    //
	    expanded_d.concat(DEF_PARAM_SPACE);
	    expanded_d.concat(val);
	  }
	}
      }
    }

    // not an option, must be an argument
    //
    else {
      if (debug_level_d >= Integral::DETAILED) {
	token.debug(L"adding argument");
      }
      args_d.concat(token);

      if (sdb_d != (Sdb*)NULL) {
	sdb_d->append(token);
      }

      // append to the new command line
      //
      expanded_d.concat(DEF_PARAM_SPACE);
      expanded_d.concat(token);
    }
  }

  // there are three standard options across all utilities: help,
  // usage, and version
  //
  if (help_flag_d) {
    printHelp();
  }
  else if (usage_flag_d) {
    printUsage();
  }
  else if (version_flag_d) {
    printVersion();
  }
  else if (echoc_flag_d) {
    printCommandLine();
  }

  // exit gracefully
  //
  return true;
}
 
// method: parse
//
// arguments:
//  const String& str: (input) input string to match
//
// return: a bool8 value indicating status
//
// this method parses the commandline options
//
bool8 CommandLine::parse(const String& str_a) {

  // declare local variables
  //
  int32 pos = 0;
  int32 count = 0;
  int32 len = str_a.length();
  String token;
  Vector<String> vec_token;
  
  // call tokenize method if length is greater than zero
  //
  if (len > 0) {

    // call tokenize method and assign the substrings to vector
    //
    while (str_a.tokenize(token, pos)) {
  
      // set the length of the vector of options
      //
      vec_token.setLength(count + 1);
      
      // assign token to options_d
      //
      if (!vec_token(count).assign(token)) {
	return false;
      }

      // increment the counter
      //
      count++;

      if (debug_level_d >= Integral::DETAILED) {
	token.debug(L"translating token");
      }
    }
  }
      
  // declare an array to hold the tokens of the string
  //
  char* c_tokens[count];

  for (int32 i = 0; i < count; i++) {
    c_tokens[i] = new char[vec_token(i).length() + 1];
    vec_token(i).getBuffer((byte8*)c_tokens[i], SysString::MAX_LENGTH);
  }

  // call the master function
  //
  bool8 status = parse(count, (const char**)c_tokens);

  if (!status) {

    // exit ungracefully
    //
    return false;
  }

  // delete the memory
  //
  for (int32 i = 0; i < count; i++) {
    delete [] c_tokens[i];
  }

  // exit gracefully
  //
  return status;
}
