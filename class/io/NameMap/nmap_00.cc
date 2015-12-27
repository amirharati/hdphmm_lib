// file: $isip/class/shell/NameMap/nmap_00.cc
// version: $Id: nmap_00.cc 6110 2000-12-28 22:31:11Z duncan $
//

// isip include files
// 
#include "NameMap.h"

// method: destructor
//
// arguments: none
//
// return: none
//
NameMap::~NameMap() {

  // delete the name list
  //
  if (names_d != (SysString*)NULL) {
    delete [] names_d;
  }

  // exit gracefully
  //
}

// method: assign
//
// arguments:
//  const SysString& str: (input) string to assign from
//  unichar delim: (input) delimiter character
//
// return: a bool8 value indicating status
//
bool8 NameMap::assign(const SysString& str_a, unichar delim_a) {

  // declare local variables
  //
  int32 pos = 0;
  int32 count = 0;

  SysString token;

  // count the tokens and allocate the space. note that this method is
  // only called by the constructors, so we don't need to check the
  // values of these variables before assigning them.
  //
  size_d = str_a.countTokens(delim_a);
  names_d = new SysString[size_d];
  
  while (str_a.tokenize(token, pos, delim_a)) {
    token.trim();
    names_d[count].assign(token);
    count++;
  }

  // exit gracefully
  //
  return computeChecksum();
}

// method: getName
//
// arguments:
//  uint16 index: (input) index of name
//
// return: String of the name
//
// this method returns the name for the given index. note that we
// return an object that points to internal data. however, the return
// value is const, so the user cannot alter this value. further, this
// is not a memory leak because when the class is destroyed, the
// memory will be deleted, and all objects pointing to that memory
// will lose that memory.
//
// now, namemaps are typically static and hence global to the program.
// this means their memory won't be deleted until the end of the
// program.  if the namemap object is destroyed before the end of
// program, all references to names returned by this method would be
// lost.  typically, users grab a copy of the value:
//
//  String str = NMP.getName(0);
//
// so even when the class is destroyed, the copy will be retained.
//
const SysString& NameMap::getName(uint16 index_a) const {

  // check the arguments
  //
  if (index_a >= size_d) {
    Error::handle(name(), L"getName", ERR_RANGE, __FILE__, __LINE__);
    return SysString::getEmptyString();
  }
  
  // return the string
  //
  return names_d[index_a];
}

// method: getIndex
//
// arguments:
//  const SysString& name: (input) name to search for
//
// return: index of the name
//
// this method returns the index for the given name. this method
// does a case-insensitive match.
//
// note that the index is restricted to a 16-bit unsigned integer; a
// value of -1 indicates the name was not found in the map. it will
// also throw a warning message if the string is not found in the map.
//
int32 NameMap::getIndex(const SysString& name_a) const {

  // declare local variables
  //
  int32 index = -1;

  // search for the name
  //
  SysString tmp_name(name_a);
  tmp_name.toLower();

  for (int32 i = 0; i < size_d; i++) {

    // convert each entry to lower case
    //
    SysString entry(names_d[i]);
    entry.toLower();

    // check for a match
    //
    if (entry.eq(tmp_name)) {
      index = i;
      break;
    }
  }

  // make sure the name was found
  //
  if (index == -1) {
    Error::handle(name(), L"getIndex", ERR_NOTFND,
		  __FILE__, __LINE__, Error::WARNING);
    return index;
  }
  
  // return the value
  //
  return index;
}

// method: computeChecksum
//
// arguments: none
//
// return: a bool8 value indicating status
//
// this method computes a checksum for the namemap map.
//
bool8 NameMap::computeChecksum() {

  // clear the checksum
  //
  cksm_d.clear(Integral::RETAIN);
  
  // loop over all vectors and update the checksum
  //

  for (int32 i = 0; i < size_d; i++) {
    if (!cksm_d.compute(names_d[i])) {
      return false;
    }
  }

  // save the checksum
  //
  checksum_d = (uint16)cksm_d.get();

  // exit gracefully
  //
  return true;
}

//-----------------------------------------------------------------------------
//
// we define non-integral constants in the default constructor
//
//-----------------------------------------------------------------------------

// constants: required constants such as the class name
//
const SysString NameMap::CLASS_NAME(L"NameMap");

// static instantiations: debug level and memory manager
//
Checksum NameMap::cksm_d;
Integral::DEBUG NameMap::debug_level_d = Integral::NONE;

// constants: namemaps for general enums
//
const NameMap NameMap::COLOR_MAP(L"WHITE, GREY, BLACK, BLUE, GREEN");
const NameMap NameMap::ALLOCATION_MAP(L"SYSTEM, USER");
