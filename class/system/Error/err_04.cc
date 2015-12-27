// file: $isip/class/system/Error/err_04.cc
// version: $Id: err_04.cc 4883 2000-09-20 12:58:09Z hamaker $
//

// isip include files
//
#include "Error.h"

//--------------------------------------------------------------
// these methods have to be in the same file so they can use the same
// function pointer. this is a really nasty break in the C++
// hierarchy, but it results in a really nice feature in that all Sof
// files are cleanly closed on any fatal error (which gets reported.
// for seg-faults you are on your own).
//---------------------------------------------------------------
//

// the static pointer to the global function
//
static bool8 (*ISIPcloseSof)(void);

// a flag indicating if the sof has been set
//
static bool8 sof_initialized_d = false;

// method: setSofPointer
//
// arguments:
//  bool8 (*method) (void): (input) a static global function pointer
//
// return: a bool8 value indicating status
//
// Sof's constructor will call this method to set a static global
// function pointer to a global method in the i/o library which knows
// how to cleanly close all open sof files.
//
bool8 Error::setSofPointer(bool8 (*method_a) (void)) {

  // set the static function pointer
  //
  ISIPcloseSof = method_a;
  sof_initialized_d = true;

  // exit gracefully
  //
  return true;
}

// method: closeSof
//
// arguments: none
//
// return: a bool8 value indicating status
//
// call the statically defined method which closes all Sof files
//
bool8 Error::closeSof() {

  // if the function pointer has been set, call it
  //
  if (sof_initialized_d) {
    return (*ISIPcloseSof)();
  }

  // function pointer was never set, meaning no Sof objects have ever
  // been constructed. exit gracefully
  //
  return true;
}
