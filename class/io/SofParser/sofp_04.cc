// file: $isip/class/io/SofParser/sofp_04.cc
// version: $Id: sofp_04.cc 7815 2002-02-26 22:59:31Z alphonso $
//

// isip include files
//
#include "SofParser.h"

// method: getEntry
//
// arguments:
//  Sof& sof: (input) sof object from which to read
//  const SysString& param: (input) parameter to return
//  int32 tag: (input) instance of parameter to return
//
// return: size of entry
//
// this function gets ready to read a sub-parameter
//
int32 SofParser::getEntry(Sof& sof_a, const SysString& param_a, int32 tag) {
  
  // if it's not text, return
  //
  if (!sof_a.isText()) {
    return true;
  }
  
  // find the parameter
  //  
  int32 param = table_d.getIndex(param_a);
  if (param < 0) {
    param_a.debug(L"param_a");
    Error::handle(name(), L"getEntry - unable to find parameter", SofList::ERR, __FILE__,
		  __LINE__, Error::WARNING);
    return -1;
  }
  
  if ((param >= used_size_d) || (used_d == (bool8*)NULL)) {
    param_a.debug(L"param_a");
    Error::handle(name(), L"getEntry - unable to find parameter", SofList::ERR, __FILE__,
		  __LINE__, Error::WARNING);
    return -1;
  }

  used_d[param] = true;
  
  if (!index_d.find(param, tag)) {
    param_a.debug(L"param_a");    
    Error::handle(name(), L"getEntry - unable to find instance of parameter to return", SofList::ERR, __FILE__,
		  __LINE__, Error::WARNING);
    return -1;
  }
  
  // seek to the beginning of the parameter 
  //
  sof_a.seek(index_d.getPosition() + base_position_d, File::POS);
  
  // possibly set the implicit block flag for individual tokens
  //
  if (tag != BASE_TAG) {
    is_token_d = true;
  }
  else {
    is_token_d = false;
  }
  
  // return the length
  //
  return index_d.getSize();
}

// method: getEntry
//
// arguments:
//  Sof& sof: (input) sof object from which to read
//  const SysString& param: (input) parameter to return
//  int32 token_offset: (input) first token we want to read
//  int32 num_tokens: (input) maximum number of tokens to read
//
// return: size of entry
//
// this function gets ready to read a sub-parameter
//
int32 SofParser::getEntry(Sof& sof_a, const SysString& param_a,
			 int32 token_offset_a, int32 num_tokens_a) {
  
  // if it's not text, return
  //
  if (!sof_a.isText()) {
    return true;
  }
  
  // find the largest token given our constraints
  //
  int32 param = table_d.getIndex(param_a);
  int32 start_tag = index_d.first(param);
  int32 stop_tag = Sof::NO_TAG;
  int32 last_pos = -1;

  // error check the param, mark it as used
  //
  if (param < 0) {
    param_a.debug(L"param_a");        
    Error::handle(name(), L"getEntry - unable to find parameter", SofList::ERR, __FILE__, __LINE__, Error::WARNING);
    return -1;
  }
  
  if ((param >= used_size_d) || (used_d == (bool8*)NULL)) {
    param_a.debug(L"param_a");    
    Error::handle(name(), L"getEntry - unable to find parameter", SofList::ERR, __FILE__, __LINE__, Error::WARNING);
    return -1;
  }
  
  used_d[param] = true;
  
  // special case for a vector with one element
  //
  if ((token_offset_a == 0) && (num_tokens_a == 1)
      &&(index_d.getCount(param) == 1)) {
    start_tag = 1;
    stop_tag = 1;
  }

  else {

    // the zeroth tag is the full object
    //
    start_tag = index_d.next(param, token_offset_a);
    
    // this will return the actual last token to the constraint
    //
    stop_tag = index_d.prev(param, token_offset_a + num_tokens_a + 1);
  }
  
  // first find the last instance so we can get the size
  //
  if (!index_d.find(param, stop_tag)) {
    return Error::handle(name(), L"getEntry - unable to find last instance of parameter to return", SofList::ERR,
			 __FILE__, __LINE__, Error::WARNING);
  }
  last_pos = index_d.getPosition() + index_d.getSize();
  
  // first find the first instance so we can get the size
  //
  if (!index_d.find(param, start_tag)) {
    return Error::handle(name(), L"getEntry - unable to find first instance of parameter to return", SofList::ERR,
			 __FILE__, __LINE__, Error::WARNING);
  }
  
  sof_a.seek(index_d.getPosition() + base_position_d, File::POS);
  
  is_token_d = true;
  
  // return the size
  //
  return (last_pos - index_d.getPosition());
}

// method: checkParams
//
// arguments:
//  const SysString* param_list: (input) acceptable parameters
//  int32 num: (input) number of acceptable parameters
//
// return: a bool8 value indicating status
//
// this method checks to see if there are any extraneous parameters set
//
bool8 SofParser::checkParams(const SysString* param_list_a, int32 num_a) {
  
  int32 count = table_d.getCount();
  
  // if there are more parameters present than listed, error
  //
  if (num_a < count) {
    return false;
  }
  
  // loop through all the given parameter names, subtracting present
  // names from the count
  //
  for (int32 i = 0; i < num_a; i++) {
    if (table_d.getIndex(param_list_a[i]) != SofSymbolTable::NO_SYMB) {
      count--;
    }
  }

  // if count is greater than zero, there is a parameter unaccounted for.
  //
  if (count > 0) {
    return false;
  }

  // exit gracefully
  //
  return true;
}

// method: checkParams
//
// arguments:
//  Sof& sof: (input) sof object
//
// return: a bool8 value indicating status
//
// this function checks to see if there are any extraneous parameters set
//
bool8 SofParser::checkParams(Sof& sof_a) {

  // if binary file, just return
  //
  if (sof_a.isBinary()) {
    return true;
  }
  
  // get the total number of parameters
  //
  int32 count = table_d.getCount();

  // run two sanity tests: (a) the number of elements specified does
  // not exceed the number of valid parameters, and (b) if the number
  // of specified parameters is not 0, the used_d array is not null.
  //
  if ((count > used_size_d) ||
      ((count > 0) && (used_d == (bool8*)NULL))) {
    return Error::handle(name(), L"checkParams - the number of elements specified exceeds the number of valid parameters or the number of specified parameters is not zero", ERR, __FILE__, __LINE__);
  }
  
  // loop through all parameters and make sure they have been used
  //
  SysString output(L"unrecognized symbol(s): ");
  bool8 first = true;
  bool8 problem = false;
  for (int32 i = 0; i < count; i++) {
    if (!used_d[i]) {
      problem = true;
      SysString pname;
      table_d.getSymbol(pname, i);
      if (first) {
	output.concat(pname);
	first = false;
      }
      else {
	output.concat(L", ");
	output.concat(pname);
      }
    }
  }

  // possibly print the problem message
  //
  if (problem) {
    Console::put(output);
  }

  // exit gracefully
  //
  return (!problem);
}

// method: getParams
//
// arguments:
//  SysString* param_list: (output) list of parameters
//  int32 max_num: (input) maximum number of parameters
//
// return: number of parameters
//
// this function returns a list of the defined parameters
//
int32 SofParser::getParams(SysString* param_list_a, int32 max_num_a) {
  
  // check arguments
  //
  if ((param_list_a == (SysString*)NULL) || (max_num_a < 1)) {
    Error::handle(name(), L"getParams - list of parameters is null or maximum number of parameters is less that one", Error::ARG, __FILE__, __LINE__);
    return (int32)-1;
  }
  
  // range check the number to return
  //
  if (table_d.getCount() < max_num_a) {
    max_num_a = table_d.getCount();
  }

  // initialize count
  //
  int32 count = 0;
  
  // loop through the parameter list
  //
  for (int32 i = 0; count < max_num_a; i++) {
    
    // if this index is in use, copy it over
    //
    if (table_d.getRefCount(i) > 0) {

      // copy the name
      //
      table_d.getSymbol(param_list_a[count], i);
      count++;
    }
  }
  
  // exit gracefully
  //
  return count;
}
