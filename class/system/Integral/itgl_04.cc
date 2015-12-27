// file: $isip/class/system/Integral/itgl_04.cc
// version: $Id: itgl_04.cc 7230 2001-07-24 00:44:30Z picone $
//

// system include files
//

#include <memory.h>
#include <unistd.h>
#include <pwd.h>

// isip include files
//
#include "Integral.h"
#include <SysString.h>


// method: getEnv
//
// arguments:
//  SysString& val: (output) expansion of the variable
//  const SysString& var: (input) environmental variable name
//
// return: a bool8 value indicating status
//
bool8 Integral::getEnv(SysString& val_a, const SysString& var_a) {


  // call system getenv function to get value of environment name
  //
  byte8* val = (byte8*)getenv((char*)(byte8*)var_a);

  // if it is not null then assign assign environment name to output
  // string
  //
  if (val != (byte8*)NULL) {
    val_a.assign((byte8*)val);
  }

  // if environment name is NULL then clear the output string
  //
  else {
    val_a.clear();
    return false;
  }

    // exit gracefully
  //
  return true;
}


// method: getLoginDir
//
// arguments:
//  SysString& dir: (output) the fully qualified directory
//  const SysString& login: (input) a login name
//
// return: a bool8 value indicating status
//
// this method returns the login directory for a username
//
bool8 Integral::getLoginDir(SysString& dir_a, const SysString& login_a) {

  // call getpwnam_r and getpwnam methods depending upon the operating
  // system, which returns a pointer to a struct passwd if they
  // successfully locate the requested entry
  //
#if ISIP_WCHAR_MODE == ISIP_WCHAR_SOLARIS
  char buffer[SysString::MAX_LENGTH];
  struct passwd pwd_buf;
  struct passwd* pwd = getpwnam_r((char*)(byte8*)login_a, &pwd_buf,
				  buffer, SysString::MAX_LENGTH);
#else
  struct passwd* pwd = getpwnam((char*)(byte8*)login_a);
#endif

  // if they successfully locate the requested, then assign it to
  // output directory
  //
  if (pwd != (passwd*)NULL) {
    dir_a.assign((byte8*)pwd->pw_dir);
  }

  // if they don't successfully locate the requested entry, then clear
  // the output directory and exit
  //
  else {
    dir_a.clear();
    return false;
  }

  // exit gracefully
  //
  return true;
}

// method: expandName
//
// arguments:
//  SysString& o_name: (output) expanded name
//  const SysString& i_name: (input) name needing expansion
//
// return: a bool8 value indicating status
//
// this method replaces all environment variables and other such
// things in a string with their equivalent expansions. for example:
// 
//  $HOME/foo.text		=> /u1/person/foo.text
//  foo.text/$HOME/data		=> foo.text//u1/person/data
//
// in other words, variables or aliases anywhere in the string will be
// replaced.
//
bool8 Integral::expandName(SysString& o_name_a, const SysString& i_name_a) {

  // declare local variables
  //
  int32 index = -1;
  SysString val;
  SysString var;

  // start with the input string
  //
  o_name_a.assign(i_name_a);
  bool8 valid = true;

  // remove preceding and trailing whitespace from the filename
  //
  o_name_a.trim();
  
  // expand all tilde's in the filename
  //
  while ((index = o_name_a.firstChr(DIR_HOME, index)) >= 0) {
    
    // increment the index
    //
    index++;
    
    // find the termination of the login name, probably a directory
    // separator
    //
    int32 last = o_name_a.firstChr(DIR_DELIM, index);
    
    if (last == NO_POS) {
      last = o_name_a.length();
    }
    
    // if position of delim is greater than the index, then get sub
    // string
    //
    if ((last - index) > 0) {
      o_name_a.substr(var, index, last - index);

      // call getLoginDir to get the login directory for a username
      //
      if (getLoginDir(val, var)) {
	o_name_a.deleteRange(index - 1, last - index + 1);
	o_name_a.insert(val, index - 1);
      }
      else {
	valid = false;
      }
    }

    // if position of delim is less than or equal to the index, then
    // call getEnv function to get value of environment name
    //
    else {
      var.assign((unichar*)ENV_HOME);
      getEnv(val, var);
      o_name_a.deleteRange(index - 1, 1);
      o_name_a.insert(val, index - 1);
    }
  }
  
  // expand all variables in the filename
  //
  while ((index = o_name_a.firstChr(ENV_MARKER, index)) != NO_POS) {

    // see if the ENV_MARKER is escaped
    //
    int32 index2 = NO_POS;
    if (index > 0) {
      index2 = o_name_a.firstChr(L"\\", index - 1);
    }

    // only expand if it was not escaped
    //
    if (index2 != NO_POS) {
      o_name_a.deleteRange(index - 1, 1);
    }
    else {

      // initialize a bool8 flag
      //
      bool8 found = false;
      
      // skip past the dollar character
      //
      index++;
      
      // loop through successively shorter string until we have a match
      //
      for (int32 last = o_name_a.length(); last > index; last--) {
	
	// select substring into var
	//
	o_name_a.substr(var, index, last - index);
	
	// if getEnv returns the value of environment name, then set the
	// bool8 flag to true
	//
	if (getEnv(val, var)) {
	  o_name_a.deleteRange(index - 1, last - index + 1);
	  found = true;
	  break;
	}
	
	// if match is not found, then clear the val string
	//
	else {
	  val.clear();
	}
      }
      
      // if no match is found, delete the output value and Error
      //
      if (!found) {
	valid = false;
      }
      
      // insert the value into the string
      //
      o_name_a.insert(val, index - 1);
    }
  }

  // look for instances with "//', throw to root directory like Emacs
  //
  static unichar two_delims[] = {
    DIR_DELIM, DIR_DELIM, (unichar)0
  };

  int32 i = o_name_a.lastStr((unichar*)two_delims);

  if (i != NO_POS) {

    // check to see if we cropped away the invalids
    //
    o_name_a.deleteRange(0, i + 1);
    if ((!valid) && (expandName(val, o_name_a))) {
      valid = true;
    }
  }

  // exit gracefully
  //
  return valid;
}
