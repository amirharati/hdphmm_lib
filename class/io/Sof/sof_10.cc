// file: $isip/class/io/Sof/sof_10.cc
// version: $Id: sof_10.cc 6679 2001-04-16 15:23:32Z duncan $
//

// isip include files
//
#include "Sof.h"
#include <Console.h>
#include <MemoryManager.h>
#include <SofParser.h>

//-----------------------------------------------------------------------
// these methods have to be in the same file so they can use the same
// static pointers to the stack of Sof objects
//-----------------------------------------------------------------------

// an array of pointers
//
static Sof** allocated_d = (Sof**)NULL;
static int32 alloc_size_d = 0;
static int32 num_alloc_d = 0;

// method: registerPtr
//
// arguments: none
//
// return: a bool8 value indicating status
//
// this method adds the current sof pointer to the static array
//
bool8 Sof::registerPtr() {

  // possibly increase the size of the allocated array
  //
  if (num_alloc_d + 1 >= alloc_size_d) {
    mgr_d.reallocateBlock((void***)&allocated_d, alloc_size_d);
  }

  // add the new object to the array
  //
  allocated_d[num_alloc_d++] = this;
  
  // exit gracefully
  //
  return true;
}

// method: unRegisterPtr
//
// arguments: none
//
// return: a bool8 value indicating status
//
// this method pulls the current sof pointer from the static array
//
bool8 Sof::unRegisterPtr() {

  // we have already called Sof::closeAll(), no need to unregister pointers
  //
  if (allocated_d == (Sof**)NULL) {
    return true;
  }
  
  // find the pointer
  //
  bool8 found = false;
  int32 i = -1;
  for (i = 0; i < num_alloc_d; i++) {
    if (this == allocated_d[i]) {
      found = true;
      break;
    }
  }
  
  // make sure we found it
  //
  if (!found) {
    if (!Error::isExiting()) {
      Error::handle(name(), L"unRegisterPtr", Error::MEM, __FILE__, __LINE__);
    }
    return false;
  }

  // pull it out of array, decrement count
  //
  for (int32 j = i + 1; j < num_alloc_d; j++) {
    allocated_d[j - 1] = allocated_d[j];
  }
  allocated_d[--num_alloc_d] = (Sof*)NULL;
  
  // exit gracefully
  //
  return true;
}

// method: closeAll
//
// arguments: none
//
// return: a bool8 value indicating status
//
// this method closes every open Sof file
//
bool8 Sof::closeAll() {

  // count the open sof files
  //
  int32 num_open = 0;
  
  // loop through all allocated objects, counting only open ones
  //
  for (int32 i = 0; i < num_alloc_d; i++) {
    if (allocated_d[i]->isOpen()) {
      num_open++;
    }
  }
  
  // broadcast a message
  //
  if (num_open > 0) {
    static SysString close_msg(L"\nClosing all Sof files.");
    Console::broadcast(close_msg);

    // loop through all allocated objects
    //
    for (int32 i = 0; i < num_alloc_d; i++) {
      
      if (allocated_d[i]->isOpen()) {
	
	// print message for this file
	//
	SysString output(L"\n\tclosing ");
	output.concat(allocated_d[i]->expanded_name_d);
	output.concat(L".\n");
	Console::broadcast(output);
	
	// close the file
	//
	allocated_d[i]->close();
      }
    }
    
    // broadcast termination message
    //
    if (num_alloc_d > 0) {
      static SysString term_msg(L"\nAll Sof files are closed.\n");
      Console::broadcast(term_msg);
    }
  }
  
  // delete allocation array
  //
  mgr_d.releaseBlock(allocated_d);
  allocated_d = (Sof**)NULL;
  
  // exit gracefully
  //
  return true;
}

//-----------------------------------------------------------------------
// the below methods have to be in the same file so the class method can
// reference the address of the global method
//------------------------------------------------------------------------

// global method which Error can call
//
bool8 errCloseAll() {

  // call the class method
  //
  return Sof::closeAll();
}

// method: setErrorPointer
//
// arguments: none
//
// return: a bool8 value indicating status
//
// set Error's dynamic function pointer
//
bool8 Sof::setErrorPointer() {
  
  // set Error's pointer to the global function
  //
  return Error::setSofPointer(errCloseAll);
}

// method: startPartialWrite
//
// arguments: none
//
// return: logical error status
//
// configure the object (allocate objects, etc.) to enable partial
// writes.
//
bool8 Sof::startPartialWrite() {

  partial_write_d = true;

  if (partial_read_d) {
    return Error::handle(name(), L"startPartialWrite", ERR,
			 __FILE__, __LINE__);
  }

  skip_table_d = new int32[SKIP_TABLE_GROUP];
  skip_table_incr_d = 0;
  last_skip_table_pos_d = 0;
  vec_start_pos_d = 0;
  vec_size_d = 0;
  
  return true;
}

// method: startPartialRead
//
// arguments: none
//
// return: logical error status
//
// configure the object (allocate objects, etc.) to enable partial
// reads.
//
bool8 Sof::startPartialRead() {

  partial_read_d = true;

  if (partial_write_d) {
    return Error::handle(name(), L"startPartialWrite", ERR,
			 __FILE__, __LINE__);
  }

  skip_table_d = new int32[SKIP_TABLE_GROUP];
  skip_table_incr_d = 0;
  last_skip_table_pos_d = 0;
  vec_start_pos_d = 0;
  vec_size_d = 0;
  vec_curr_elem_d = 0;

  vec_parser_d = new SofParser();
  
  return true;
}

// method: stopPartialWrite
//
// arguments: none
//
// return: logical error status
//
// cleanup the object (delete objects, etc.) to disable partial
// writes.
//
bool8 Sof::stopPartialWrite() {

  if (!partial_write_d) {
    if (!Error::isExiting()) {
      return Error::handle(name(), L"stopPartialWrite", ERR,
			   __FILE__, __LINE__);
    }
  }
  partial_write_d = false;

  delete [] skip_table_d;
  skip_table_d = (int32*)NULL;
  skip_table_incr_d = 0;
  last_skip_table_pos_d = 0;
  vec_start_pos_d = 0;
  vec_size_d = 0;
  
  return true;
}

// method: stopPartialRead
//
// arguments: none
//
// return: logical error status
//
// cleanup the object (delete objects, etc.) to disable partial
// reads.
//
bool8 Sof::stopPartialRead() {

  if (!partial_read_d) {
    if (!Error::isExiting()) {
      return Error::handle(name(), L"stopPartialRead", Error::ARG,
			   __FILE__, __LINE__);
    }
  }
  
  partial_read_d = false;

  delete [] skip_table_d;
  skip_table_d = (int32*)NULL;
  skip_table_incr_d = 0;
  last_skip_table_pos_d = 0;
  vec_start_pos_d = 0;
  vec_size_d = 0;
  vec_curr_elem_d = 0;

  delete vec_parser_d;
  vec_parser_d = (SofParser*)NULL;
  
  return true;
}

// method: getVecParser
//
// arguments: none
//
// return: SofParser object
//
// return the internal parser object for use in partial reads
//
SofParser& Sof::getVecParser() {

  if (vec_parser_d == (SofParser*)NULL) {
    Error::handle(name(), L"getVecParser", Error::MEM,
			 __FILE__, __LINE__);
  }
  return *vec_parser_d;
}

// method: getVecParser
//
// arguments: none
//
// return: SofParser object
//
// return the internal parser object for use in partial reads
//
const SofParser& Sof::getVecParser() const {

  if (vec_parser_d == (SofParser*)NULL) {
    Error::handle(name(), L"getVecParser", Error::MEM,
			 __FILE__, __LINE__);
  }
  return *vec_parser_d;
}
