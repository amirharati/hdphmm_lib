// file: $isip/class/shell/CommandLine/cmdl_04.cc
// version: $Id: cmdl_04.cc 9236 2003-06-23 18:12:22Z gao $
//

// isip include files
// 
#include "CommandLine.h"
#include <Console.h>
 
// method: setSdb
//
// arguments:
//  Sdb& sdb: (input) Sdb object to link to commandline
//
// return: a bool8 value indicating status
//
// this function links the given Sdb object to this commandline object
//
bool8 CommandLine::setSdb(Sdb& sdb_a) {

  // copy the argument and clear the input argument
  //
  sdb_d = &sdb_a;
  sdb_a.clear(Integral::RESET);

  // make sure the Sdb list file option was not included
  //
  int32 first = options_d.first(Sdb::LIST_FILE_OPTION);

  if (first >= 0) {
    Console::put(L"this parameter is reserved by Sdb\n");
    options_d(first).debug(L"this parameter");
    types_d(first).debug(L"this class name");
    return Error::handle(name(), L"setSdb", ERR_OPTMULT,
			 __FILE__, __LINE__);
  }
  
  // specify the output directory option
  //
  addOptionParam(sdb_d->output_directory_d,
		 DEF_PARAM_DIRECTORY,
		 Sdb::DEF_OUT_DIR);

  // specify the output basename
  //
  addOptionParam(sdb_d->output_basename_d,
		 DEF_PARAM_BASENAME,
		 String::NULL_STRING);

  // specify the output extension
  //
  addOptionParam(sdb_d->output_extension_d,
		 DEF_PARAM_EXTENSION,
		 Filename::DEF_EXTENSION);

  // specify the directory preservation level
  //
  addOptionParam(sdb_d->dir_pres_d,
		 DEF_PARAM_PRESERVE,
		 Sdb::DEF_DIR_PRES);

  // specify the output suffix
  //
  addOptionParam(sdb_d->output_suffix_d,
		 DEF_PARAM_SUFFIX,
		 Filename::DEF_SUFFIX);
  
  // exit gracefully
  //
  return true;
}

// method: setIdent
//
// arguments:
//  const char* rev_str: (input) rcs "Revision" ident tag
//  const char* name_str: (input) rcs "Name" ident tag
//  const char* date_str: (input) rcs "Date" ident tag
//
// return: a bool8 value indicating status
//
// this method builds a version string from the input rcs ident tags
//
// the input should be the ident tags Revision, Name, and Date
//
bool8 CommandLine::setIdent(const char* rev_str_a,
			      const char* name_str_a,
			      const char* date_str_a) {

  // local variables
  //
  String rev_str;
  String name_str;
  String date_str;

  // assign the inputs to string objects
  //
  rev_str.assign((byte8*)rev_str_a);
  name_str.assign((byte8*)name_str_a);
  date_str.assign((byte8*)date_str_a);

  // strip the ident delimiters from the ident strings
  //
  if (rev_str.firstStr(L"$Revision: ") < 0) {
    return Error::handle(name(), L"setIdent", Error::ARG, __FILE__, __LINE__);
  }

  if (name_str.firstStr(L"$Name: ") < 0) {
    return Error::handle(name(), L"setIdent", Error::ARG, __FILE__, __LINE__);
  }

  if (date_str.firstStr(L"$Date: ") < 0) {
    return Error::handle(name(), L"setIdent", Error::ARG, __FILE__, __LINE__);
  }

  rev_str.deleteRange(0, 11);
  name_str.deleteRange(0, 7);
  date_str.deleteRange(0, 7);

  rev_str.trimRight(L" $");
  name_str.trimRight(L" $");
  date_str.trimRight(L" $");

  if (name_str.length() == 0) {
    name_str.assign(NO_VERSION_NAME);
  }
  
  version_msg_d.assign(VERSION_STR);
  version_msg_d.concat(rev_str);
  
  version_msg_d.concat(L" (");
  version_msg_d.concat(name_str);
  version_msg_d.concat(L") ");
  version_msg_d.concat(date_str);

  // exit gracefully
  //
  return true;
}

// method: printUsage
//
// arguments: none
//
// return: a bool8 value indicating status
//
// method to print a usage message
//
bool8 CommandLine::printUsage() {

  // print the usage message only once
  //
  if (!usage_printed_d) {

    // turn off line-wrapping
    //
    int32 line_wrap = Console::getLineWrap();
    Console::setLineWrap(-1);

    // print the usage message
    //
    Console::put(usage_msg_d);
    Console::put(L"\tspecify the -help option for more information\n\n");
    usage_printed_d = true;

    // reset the line-wrapping
    //
    Console::setLineWrap(line_wrap);
  }

  // exit gracefully by terminating program
  //
  if (!test_mode_d) {
      Error::exit();
  };

  // exit gracefully
  //
  return true;
}
 
// method: printHelp
//
// arguments: none
//
// return: a bool8 value indicating status
//
// method to print a help message
//
bool8 CommandLine::printHelp() const {

  // turn off line-wrapping
  //
  int32 line_wrap = Console::getLineWrap();
  Console::setLineWrap(-1);

  // print the help message
  //
  Console::put(help_msg_d);

  // reset the line-wrapping
  //
  Console::setLineWrap(line_wrap);

  // exit gracefully by terminating the calling program
  //
  if (!test_mode_d) {
    Error::exit();
  };

  // exit gracefully
  //
  return true;
}
 
// method: printVersion
//
// arguments: none
//
// return: a bool8 value indicating status
//
// method to print a version message
//
bool8 CommandLine::printVersion() const {

  // turn off line-wrapping
  //
  int32 line_wrap = Console::getLineWrap();
  Console::setLineWrap(-1);

  // print the version message
  //
  Console::put(version_msg_d);

  // reset the line-wrapping
  //
  Console::setLineWrap(line_wrap);

  // exit gracefully
  //
  return true;
}

// method: printFinalReport
//
// arguments:
//  const String& pname: (input) program name
//  int32 ncmpl: (input) number of files completed
//  int32 natt: (input) number of files attempted
//
// return: a bool8 value indicating status
//
// method to print a final report for a utility
//
bool8 CommandLine::printFinalReport(const String& pname_a,
				      int32 ncmpl_a, int32 natt_a) {

  // build the output string
  //
  String output;
  output.assign(pname_a);
  output.concat(REPORT_STR_00);
  output.concat(ncmpl_a);
  output.concat(REPORT_STR_01);
  output.concat(natt_a);
  output.concat(REPORT_STR_02);

  // write it to the console
  //
  Console::put(output);
  
  // exit gracefully
  //
  return true;
}

// method: printCommandLine
//
// arguments: none
//
// return: a bool8 value indicating status
//
// method to print a expanded command line
//
bool8 CommandLine::printCommandLine() const {

  // turn off line-wrapping
  //
  int32 line_wrap = Console::getLineWrap();
  Console::setLineWrap(File::NO_WRAP);

  // print the expanded command line message
  //
  String running_msg(COMMAND_STR);
  running_msg.concat(expanded_d);
  Console::put(running_msg);

  // reset the line-wrapping
  //
  Console::setLineWrap(line_wrap);

  // exit gracefully
  //
  return true;
}
