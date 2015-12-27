// file: $isip/class/shell/CommandLine/cmdl_05.cc
// version: $Id: cmdl_05.cc 9233 2003-06-20 21:43:09Z picone $
//

// isip include files
// 
#include "CommandLine.h"
 
// method: addOptionParam
//
// arguments:
//  void* var: (input) void variable
//  const String& name: (input) class name
//  const String& param: (input) parameter
//
// return: a bool8 value indicating status
//
// this method checks whether the option is unique and adds the input
// option to the internal lists
//
bool8 CommandLine::addOptionParam(void* var_a, const String& name_a,
				    const String& param_a) {

  // make sure this option isn't the Sdb list option
  //
  if ((sdb_d != (Sdb*)NULL) && param_a.eq(Sdb::LIST_FILE_OPTION)) {
    Console::put(L"this parameter is reserved by Sdb\n");
    param_a.debug(L"this parameter");
    name_a.debug(L"this parameter");
    return Error::handle(name(), L"addOptionParam",
			 ERR_OPTMULT, __FILE__, __LINE__);
  }

  // make sure the option is unique
  //
  if (options_d.first(param_a) >= 0) {
    param_a.debug(L"this parameter");
    name_a.debug(L"this class name");
    return Error::handle(name(), L"addOptionParam",
			 ERR_OPTMULT, __FILE__, __LINE__);
  }
  
  // check the size of objects_d[],
  //
  if ((options_d.length() + 1) >= objects_size_d) {
    mgr_d.reallocateBlock((void***)&objects_d, objects_size_d);
  }
  
  // add this option to the internal lists
  //
  objects_d[options_d.length()] = var_a;
  options_d.concat(param_a);
  types_d.concat(name_a);
  Boolean use(false);
  used_d.concat(use);
  
  // exit gracefully
  //
  return true;
}

// method: getOptionIndex
//
// arguments:
//  const String& opt_name: (input) input string
//  bool8 prefix: (input) does the option name contain a prefix (def = false)
//
// return: a int32 value containing the index of string
//
// this function does a partial match and gives an error in case of ambiguous
// or duplicate options on command line. in case of no such errors it
// returns the index of the string.
//
// the prefix option refers to whether the string contains the
// argument prefix (e.g., "-foo" vs. "foo"). the default is no prefix.
//
int32 CommandLine::getOptionIndex(const String& opt_name_a, bool8 prefix_a) {

  // declare a string
  //
  String match(opt_name_a);

  // this is a class error, not a user error
  //
  if ((prefix_a) && opt_name_a.firstStr(DEF_PARAM_PREFIX) != 0) {
    return Error::handle(name(), L"getOptionIndex",
			 Error::ARG, __FILE__, __LINE__);
  }

  // remove the prefix from the token to get the match string
  //
  if (prefix_a) {
    opt_name_a.substr(match, DEF_PARAM_PREFIX.length(),
		      opt_name_a.length() - DEF_PARAM_PREFIX.length());
  }
  
  // if we are using Sdb, test for the LIST option
  //
  if (sdb_d != (Sdb*)NULL) {
    if (match.eq(Sdb::LIST_FILE_OPTION)) {
      return OPT_INDEX_SDB;
    }
  }

  // declare and initialize initial variables
  //
  int32 num_found = 0;
  bool8 exact_found = false;
  int32 index = Integral::NO_POS;

  String mult_matches;
  
  // loop over all the command line options
  //
  for (int32 i = 0; i < options_d.length(); i++) {

    if (options_d(i).eq(match)) {

      // has there already been an exact match?
      //
      if (exact_found) {
	printUsage();
	Error::handle(name(), L"getOptionIndex",
		      ERR_OPTDUPL, __FILE__, __LINE__, Error::WARNING);
	return Integral::NO_POS;
      }

      exact_found = true;
      num_found = 1;
      index = i;
    }

    // the substring matches the start of the string
    //
    if ((!exact_found) && (options_d(i).firstStr(match) == 0)) {
      
      // has there already been a match?
      //
      if (num_found > 0) {
	if (mult_matches.length() == 0) {
	  mult_matches.assign(L"option name /");
	  mult_matches.concat(match);
	  
	  mult_matches.concat(L".*/ matches (");
	  mult_matches.concat(options_d(index));
	} 
	
	mult_matches.concat(L", ");
	mult_matches.concat(options_d(i));
      }
      
      num_found++;
      index = i;
    }
  }

  // has there already been a match?
  //
  if (num_found > 1) {
    mult_matches.concat(L")");
    Console::put(mult_matches);
    printUsage();
    Error::handle(name(), L"getOptionIndex", ERR_OPTAMB,
		  __FILE__, __LINE__, Error::WARNING);
    return Integral::NO_POS;
  }

  // if the option is found, mark it as used
  //
  //  if (index >= 0) {
  //    used_d(index).assign(true);
  //  }
  
  // return the index
  //
  return index;
}
 
// method: getArgument
//
// arguments:
//  String& arg: (output) string
//  int32 ordinal_number: (input) ordinal number
//
// return: a bool8 value indicating status
//
// this method gives the unused arguments after all good parameters
// have been passed
//
bool8 CommandLine::getArgument(String& arg_a, int32 ordinal_number_a) const {

  // loop through all the unused parameters
  //
  for (int32 i = 0; i < args_d.length(); i++) {

    // check the indices of args_d
    //
    if (i == ordinal_number_a) {
      return arg_a.assign(args_d(i));
    }
  }

  // exit ungracefully
  //
  return false;
}

// method: isPresent
//
// arguments:
//  const String& opt_name: (input) the full option name
//  bool8 prefix: (input) does the option name contain a prefix (def = false)
//
// return: a bool8 value that is true if there is a match
//
// this method checks if a specific option name is present
// in the command line. the argument should be the full
// name of the option (not the abbreviated name). partial
// matching is done so that if an abbreviated name was entered
// in the input command line, it will be matched.
//
// for example, if "-sample_frequency" is the full option name,
// and the user inputs "-sample", this function will return true.
//
// note that the parse method must be called before this method
// so that a command line has actually been expanded.
//
bool8 CommandLine::isPresent(const String& opt_name_a,
			       bool8 prefix_a) {

  // make sure the parse method has been called
  //
  if (expanded_d.length() == 0) {
    Error::handle(name(), L"isPresent", ERR_OPTPARS,
		  __FILE__, __LINE__, Error::WARNING);
    return false;
  }

  // check the options list
  //
  if (getOptionIndex(opt_name_a, prefix_a) >= 0) {
    return true;
  }

  // exit gracefully
  //
  else {
    return false;
  }
}

// method: getValue
//
// arguments:
//  String& value: (output) the value as a string
//  const String& opt_name: (input) the option name
//  bool8 prefix: (input) whether the option name include the prefix
//
// return: a bool8 which is true if the option has been set
//
// this function returns the value specified at the command line
// for a given option. if the option was not specified, it returns false.
//
bool8 CommandLine::getValue(String& value_a,
			      const String& opt_name_a,
			      bool8 prefix_a) {

  // find the option
  //
  int32 pos = getOptionIndex(opt_name_a, prefix_a);

  // check if the option was specified
  // 
  if (!used_d(pos)) {
    return false;
  }
  
  // fetch the string
  //
  else {
    return value_a.assign(values_d(pos));
  }
}
