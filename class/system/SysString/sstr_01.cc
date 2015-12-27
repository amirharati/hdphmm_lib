// file: $isip/class/system/SysString/sstr_01.cc
// version: $Id: sstr_01.cc 6098 2000-12-28 16:10:57Z hamaker $
//

// system include files
//
//#include <widec.h>

// isip include files
//
#include "SysString.h"
#include <Console.h>
// method: debug
//
// arguments:
//  const unichar* msg: (input) message to print
//
// return: a bool8 value indicating status
//
// this is the debug method
//
bool8 SysString::debug(const unichar* msg_a) const {
  
  // dump the data
  //
  SysString output(length() + 50);
  SysString value(length() + 50);

  // get the debug formats
  //
  value.assign(DBG_FORMAT_0);
  value.concat((int32)capacity_d);
  value.concat(DBG_FORMAT_1);
  value.concat((int32)length());
  value.concat(DBG_FORMAT_2);
  value.concat(*this);
  value.concat(DBG_FORMAT_3);

  // get the class data
  //  
  output.debugStr(name(), msg_a, L"value_d", value);

  Console::put(output);

  // exit gracefully
  //
  return true;
}

// method: debugStr
//
// arguments:
//  const SysString& cname: (input) the class name
//  const unichar* mname: (input) the method name
//  const unichar* variable: (input) the variable name
//  const SysString& value: (input) the variable's value
//
// return: a bool8 value indicating status
//
// this method creates a uniform string used by the debug methods
//
bool8 SysString::debugStr(const SysString& cname_a, const unichar* mname_a,
			    const unichar* variable_a,
			    const SysString& value_a) {
  
  // create the base string
  //
  debugStr(cname_a, mname_a, variable_a);

  // concat
  //
  concat(DBGS_FORMAT_3);
  concat(value_a);
  
  // exit gracefully
  //
  return true;
}

// method: debugStr
//
// arguments:
//  const SysString& cname: (input) the class name
//  const unichar* mname: (input) the method name
//  const unichar* variable: (input) the variable name
//
// return: a bool8 value indicating status
//
// this method creates a uniform string used by the debug methods
//
bool8 SysString::debugStr(const SysString& cname_a, const unichar* mname_a,
			    const unichar* variable_a) {
  
  // copy the variable name to a SysString
  //
  SysString var(variable_a);

  // more than likely, the output string will be at least this big
  //
  setCapacity(128);
  
  // set the prefix
  //
  debugStrPrefix(cname_a, mname_a);

  // concat
  //
  concat(var);
  
  // exit gracefully
  //
  return true;
}

// method: debugStrPrefix
//
// arguments:
//  const SysString& cname: (input) the class name
//  const unichar* mname: (input) the method name
//
// return: a bool8 value indicating status
//
// this method creates the prefix used in the standard debug string message.
//
bool8 SysString::debugStrPrefix(const SysString& cname_a,
				  const unichar* mname_a) {

  // more than likely, the output string will be at least this big
  //
  setCapacity(128);
  
  // copy method name to SysStrings
  //
  SysString method(mname_a);

  // concat
  //
  concat(DBGS_FORMAT_0, cname_a);
  concat(DBGS_FORMAT_1);
  concat(method);
  concat(DBGS_FORMAT_2);

  // exit gracefully
  //
  return true;
}
