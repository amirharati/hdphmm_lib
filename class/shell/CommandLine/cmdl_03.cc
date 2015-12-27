// file: $isip/class/shell/CommandLine/cmdl_03.cc
// version: $Id: cmdl_03.cc 9211 2003-06-16 03:44:53Z picone $
//

// isip include files
// 
#include "CommandLine.h"
 
// method: assign
//
// arguments:
//  const CommandLine& arg: (input) input operand to copy
//
// return: a bool8 value indicating status
//
// this method assigns input commandline to current commandline
//
bool8 CommandLine::assign(const CommandLine& arg_a) {

  // assign the message-related variables
  //
  echoc_flag_d.assign(arg_a.echoc_flag_d);
  help_flag_d.assign(arg_a.help_flag_d);
  usage_flag_d.assign(arg_a.usage_flag_d);
  version_flag_d.assign(arg_a.version_flag_d);

  help_msg_d.assign(arg_a.help_msg_d);
  usage_msg_d.assign(arg_a.usage_msg_d);
  version_msg_d.assign(arg_a.version_msg_d);
  expanded_d.assign(arg_a.expanded_d);
  
  // assign the options-related variables
  //
  prog_name_d.assign(arg_a.prog_name_d);
  options_d.assign(arg_a.options_d);
  types_d.assign(arg_a.types_d);
  used_d.assign(arg_a.used_d);
  args_d.assign(arg_a.args_d);

  // assign the Sdb object
  //
  sdb_d = arg_a.sdb_d;

  // assign other integral data types
  //
  objects_size_d = arg_a.objects_size_d;
  if (objects_d != (void**)NULL) {
    mgr_d.releaseBlock(objects_d);
  }
  objects_d = (void**)mgr_d.getBlock(objects_size_d * sizeof(void*));
  MemoryManager::memcpy(objects_d, arg_a.objects_d,
			options_d.length() * sizeof(void*));

  // assign internal flags
  //
  usage_printed_d = false;
  
  // exit gracefully
  //
  return true;
}

// method: assign
//
// arguments:
//  const String& str: (input) string to copy
//
// return: a bool8 value indicating status
// 
// this method assigns a string as the command line
//
bool8 CommandLine::assign(const String& str_a) {

  // declare local variables
  //
  int32 count = 0;			// number of arguments used
  int32 pos = 0;				// current position for tokenization
  int32 str_len = str_a.length();	// length of the argument
  String token;				// hold tokenized substrings

  // call tokenize method if length is greater than zero
  //
  if (str_len > 0) {

    // tokenize by space
    //
    while (str_a.tokenize(token, pos)) {
      
      // set the length of the vector of options
      //
      options_d.setLength(count + 1);
      
      // assign token to options_d
      //
      if (!options_d(count).assign(token)) {
	return false;
      }

      // increment the counter
      //
      count++;
    }
  }
  
  // initialize length of the vector used
  //
  used_d.setLength(count);

  // initialize the length of vector types_d
  //
  types_d.setLength(count);

  // exit gracefully
  //
  return true;
}

// method: clear
//
// arguments:
//  Integral::CMODE cmode: (input) clearing mode
//
// return: a bool8 value indicating status
//
// this method clears the contents of the object
// the sdb_d pointer is not cleared since it may be shared across contexts
//
bool8 CommandLine::clear(Integral::CMODE cmode_a) {

  // retain mode makes no sense for command line, we must reset so that
  // the code below can reinitialize
  //
  if (cmode_a == Integral::RETAIN) {
    cmode_a = Integral::RESET;
  }
  
  // clear the parsing-related variables
  //
  prog_name_d.clear(cmode_a);
  options_d.clear(cmode_a);
  types_d.clear(cmode_a);
  used_d.clear(cmode_a);
  args_d.clear(cmode_a);

  // clear the message-related variables
  //
  help_flag_d.clear(cmode_a);
  usage_flag_d.clear(cmode_a);
  version_flag_d.clear(cmode_a);
  echoc_flag_d.clear(cmode_a);

  help_msg_d.clear(cmode_a);
  usage_msg_d.clear(cmode_a);
  version_msg_d.clear(cmode_a);
  expanded_d.clear(cmode_a);

  // reset the sdb pointer
  //
  sdb_d = (Sdb*)NULL;
  
  // clear the data
  //
  if (objects_d != (void**)NULL) {

    if (cmode_a == Integral::RESET) {
      MemoryManager::memset(objects_d, 0, objects_size_d * sizeof(void*));
    }
    else {
      delete [] objects_d;
      objects_d = (void**)NULL;
      objects_size_d = 0;
    }
  }
  
  // reinitialize values
  //
  usage_printed_d = false;
    
  // specify values for the standard flags
  //
  addFlagParam(help_flag_d, DEF_PARAM_HELP);
  addFlagParam(usage_flag_d, DEF_PARAM_USAGE);
  addFlagParam(version_flag_d, DEF_PARAM_VERSION);
  addFlagParam(echoc_flag_d, DEF_PARAM_ECHOC);
  
  // exit gracefully
  //
  return true;
}
