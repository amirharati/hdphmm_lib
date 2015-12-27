// file: $isip/class/shell/CommandLine/cmdl_00.cc
// version: $Id: cmdl_00.cc 9248 2003-06-29 10:02:45Z picone $
//

// isip include files
// 
#include "CommandLine.h"

// method: default constructor
//
// arguments: none
//
// return: none
//
// this is the default constructor
//
CommandLine::CommandLine() {

  // initialize only those data members needing initialization
  //
  objects_size_d = DEF_OBJECTS_SIZE;
  objects_d = (void**)mgr_d.getBlock(objects_size_d * sizeof(void*));
  sdb_d = (Sdb*)NULL;

  // set some other objects' sizes based on the above values
  //
  options_d.setCapacity(objects_size_d, false);
  types_d.setCapacity(objects_size_d, false);
  used_d.setCapacity(objects_size_d, false);
  args_d.setCapacity(objects_size_d, false);
  values_d.setCapacity(objects_size_d, false);

  // set the internal flags: static's are not set
  //
  usage_printed_d = false;
  debug_level_d = Integral::NONE;
  
  // specify values for the message-related flags
  //
  addFlagParam(echoc_flag_d, DEF_PARAM_ECHOC);
  addFlagParam(help_flag_d, DEF_PARAM_HELP);
  addFlagParam(usage_flag_d, DEF_PARAM_USAGE);
  addFlagParam(version_flag_d, DEF_PARAM_VERSION);

  // exit gracefully
  //
}

// method: copy constructor
//
// arguments:
//  const CommandLine& arg: (input) list of commandline
//
// return: a bool8 value indicating status
//
// this method is the copy constructor for the CommandLine class
//
CommandLine::CommandLine(const CommandLine& arg_a) {

  // initialize those variables needing initialization
  //
  objects_size_d = DEF_OBJECTS_SIZE;
  objects_d = (void**)mgr_d.getBlock(objects_size_d * sizeof(void*));
  sdb_d = (Sdb*)NULL;

  // copy the rest
  //
  assign(arg_a);

  // the usage has not been printed
  //
  usage_printed_d = false;
  debug_level_d = Integral::NONE;

  // exit gracefully
  //
}

// method: constructor
//
// arguments:
//  Sdb& arg: (input) Sdb object to link in
//
// return: none
//
// this constrctor builds a CommandLine object and sets the Sdb pointer.
//
CommandLine::CommandLine(Sdb& arg_a) {

  // initialize only those variables needing initialization
  //
  objects_size_d = DEF_OBJECTS_SIZE;
  objects_d = (void**)mgr_d.getBlock(objects_size_d * sizeof(void*));

  sdb_d = (Sdb*)NULL;
  
  // set some other objects' sizes based on the above values
  //
  options_d.setCapacity(objects_size_d, false);
  types_d.setCapacity(objects_size_d, false);
  used_d.setCapacity(objects_size_d, false);
  args_d.setCapacity(objects_size_d, false);
  
  // set the internal flags: static's are not set
  //
  usage_printed_d = false;
  debug_level_d = Integral::NONE;
  
  // specify values for the standard flags
  //
  addFlagParam(echoc_flag_d, DEF_PARAM_ECHOC);
  addFlagParam(help_flag_d, DEF_PARAM_HELP);
  addFlagParam(usage_flag_d, DEF_PARAM_USAGE);
  addFlagParam(version_flag_d, DEF_PARAM_VERSION);

  // set the sdb argument
  //
  setSdb(arg_a);

  // exit gracefully
  //
}
  
// method: destructor
//
// arguments: none
//
// return: none
//
// this is the default destructor
//
CommandLine::~CommandLine() {

  // free memory
  //
  if (objects_d != (void**)NULL) {
    mgr_d.releaseBlock(objects_d);
  }
  objects_d = (void**)NULL;

  // exit gracefully
  //
}

//-----------------------------------------------------------------------------
//
// we define non-integral constants in the default constructor
//      
//-----------------------------------------------------------------------------

// constants: required constants such as class name
//
const String CommandLine::CLASS_NAME(L"CommandLine");

// constants: for command line parsing
//
const String CommandLine::DEF_PARAM_PREFIX(L"-");
const String CommandLine::DEF_PARAM_SPACE(L" ");

// constants: standard option name definitions
//
const String CommandLine::DEF_PARAM_DEBUG(L"debug_level");
const String CommandLine::DEF_PARAM_LFILE(L"log_file");
const String CommandLine::DEF_PARAM_PFILE(L"parameter_file");
const String CommandLine::DEF_PARAM_TYPE(L"type");
const String CommandLine::DEF_PARAM_VERBOSITY(L"verbosity");

// constants: for Sdb argument parsing
//
const String CommandLine::DEF_PARAM_DIRECTORY(L"directory");
const String CommandLine::DEF_PARAM_BASENAME(L"basename");
const String CommandLine::DEF_PARAM_EXTENSION(L"extension");
const String CommandLine::DEF_PARAM_PRESERVE(L"preserve");
const String CommandLine::DEF_PARAM_SUFFIX(L"suffix");

// constants: for message-related parameters
//
const String CommandLine::DEF_PARAM_ECHOC(L"echo_command_line");
const String CommandLine::DEF_PARAM_HELP(L"help");
const String CommandLine::DEF_PARAM_USAGE(L"usage");
const String CommandLine::DEF_PARAM_VERSION(L"version");

// constants: for messages and output strings
//
const String CommandLine::COMMAND_STR(L"Command: ");
const String CommandLine::NO_VERSION_NAME(L"not released");
const String CommandLine::VERSION_STR(L"Version: ");

const String CommandLine::REPORT_STR_00(L": processed ");
const String CommandLine::REPORT_STR_01(L" file(s), attempted ");
const String CommandLine::REPORT_STR_02(L" file(s).\n");

// constants: for default values for arguments
//
const Filename CommandLine::DEF_EMPTY(L"");
const Filename CommandLine::DEF_LFILE_NAME(L"-");

// static instantiations: test mode
//
bool8 CommandLine::test_mode_d = false;

// static instantiations: memory manager
//
Integral::DEBUG CommandLine::debug_level_d = Integral::NONE;
MemoryManager CommandLine::mgr_d(sizeof(CommandLine), CommandLine::name());
