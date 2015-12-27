// file: $isip/class/io/SofParser/sofp_03.cc
// version: $Id: sofp_03.cc 8921 2002-12-17 16:35:31Z parihar $
//


// isip include files
//
#include "SofParser.h"
#include <MemoryManager.h>

// method: load
//
// arguments:
//  Sof& sof: (input) an Sof file
//  int32 size: (input) number of bytes to parse within Sof object
//
// return: a bool8 value indicating status
//
// this method loads the parameters from the Sof object. it assumes
// that the Sof file is already positioned correctly to read the
// object in question.
//
bool8 SofParser::load(Sof& sof_a, int32 size_a) {
  
  // check argument
  //
  if (!sof_a.isOpen()) {
    return Error::handle(name(), L"load - sof file is not open", Error::READ_CLOSED, __FILE__, __LINE__, Error::WARNING);
  }

  // if it's not text, return
  //
  if (!sof_a.isText()) {
    return true;
  }

  // initialize the flag to keep track of load errors. note that this
  // flag will be reset to false before we exit this method.
  //
  load_error_d = false;

  // FULL_OBJECT is a flag to read the whole object
  //
  if (size_a == FULL_OBJECT) {
    
    // position the Sof object to the beginning of the current object
    //
    if (!sof_a.rewind()) {
      return Error::handle(name(), L"load - cannot position the sof object to the beginning of the current object", Error::SEEK, __FILE__, __LINE__, Error::WARNING);
    }

    // get the object size
    //
    size_a = sof_a.getObjectSize();
  }

 
  // now error check the size argument
  //
  if (size_a <= 0) {
    return Error::handle(name(), L"load - number of bytes to parse within Sof object is less than or equal to zero", Error::ARG, __FILE__, __LINE__);
  }
  
  // save the position & size of our file space
  //
  base_position_d = sof_a.tell();
  full_size_d = size_a;
  
  // initialize FSM
  //
  state_d = NO_GPI;
  open_index_d = true;
  implicit_block_d = false;
  statement_term_d = -1;
  block_count_d = 0;
  is_token_d = false;
  
  if (!implicit_object_d) {
    param_d = SofSymbolTable::NO_SYMB;
    statement_asgn_d = -1;
  }

  int32 parsed_length = 0;
  
  // initialize memory
  //
  byte8 buffer[MAX_BUFFER_SIZE+1];
  MemoryManager::memset(buffer, 0,MAX_BUFFER_SIZE+1*sizeof(byte8));
  unichar ubuf[MAX_BUFFER_SIZE+1];
  MemoryManager::memset(ubuf, 0, MAX_BUFFER_SIZE+1*sizeof(unichar));
  
  int32 read_size = 0;
  int32 nchars_pass = 0;
  


  // all positions are with respect to the beginning of the entry
  ///*
  int64 base_pos = 0;

  // in case there is a partial statement from the last read, use this
  // as an offset into the current buffer. So available new data
  // should be read starting at this point into the buffer
  //
  int32 size_left = 0;
  // compute the number of bytes to read in this pass
  //
  
  if (size_a > (MAX_BUFFER_SIZE - size_left)) {
    read_size = (MAX_BUFFER_SIZE - size_left);
    size_a -= read_size;
  }
  else {
    read_size = size_a;
    size_a = 0;
  }


    while (read_size > 0) {
	
    // clear out the buffer. note that characters 0-size_left are
    // preserved from the previous loop run.
    //
    MemoryManager::memset(&buffer[size_left], 0, MAX_BUFFER_SIZE - size_left);
    
    // read in a buffer of data
    //
    nchars_pass = sof_a.read(&buffer[size_left],sizeof(byte8),read_size);

    // make sure we read as many characters as we think we should. we
    // are in the middle of an Sof file, so we should not hit an EOF.
    //
    if (nchars_pass != read_size) {
      load_error_d = false;
      return Error::handle(name(), L"load - number of characters read so far is not equal to the amount that must be read", Error::READ, __FILE__, __LINE__, Error::WARNING);
    }
    buffer[size_left + read_size] = (byte8)NULL;
    
    // convert the buffer into unicode characters
    //
    SysString str;
    str.assign(buffer);
    if (debug_level_d > Integral::DETAILED) {
      str.debug(L"buffer string");
    }

    str.getBuffer(ubuf, read_size + size_left + 1);
    // parse this buffer of data
    //
    unichar* buffer_pos =(unichar*) ubuf;
    // increase the number of characters to parse by the number we just read in
    //
    size_left += nchars_pass;
    nchars_pass = size_left;    
    // after calling preParse,
    //
    //  o parsed_length will return the number of "output" characters
    //  o the buffer pointed to by buffer_pos will be updated in place
    //    with the parser output, characters 0-parsed_length are valid output
    //  o note a maximum of size_left characters will be examined by the parser
    //  o the final argument is an integer index used to obtain
    //    absolute file positions in the indeces
    //
    ///*
    while ((preParse(parsed_length, buffer_pos, size_left,(int64) (base_pos +((int64)buffer_pos - (int64)ubuf) /sizeof(unichar))))) {
	if (debug_level_d >= Integral::DETAILED) {

	// save the last char
	//
	unichar tchar = buffer_pos[parsed_length];
	buffer_pos[parsed_length] = (unichar)NULL;
	SysString temp((unichar*)buffer_pos);
	temp.debug(L"this was parsed");
	buffer_pos[parsed_length] = tchar;
      }


	
      // if we hit a param, add it to the table
      //
      if (param_d >= 0) {
	if (!index_d.add(param_d, BASE_TAG, statement_asgn_d,
			 statement_term_d - statement_asgn_d + 1)) {
	  load_error_d = false;
	  return Error::handle(name(), L"load - unable to add the parameter to the table", SofList::ERR, __FILE__, __LINE__, Error::WARNING);
	}
      }
      else {
	break;
      }
      
      // increment the counters
      //
      ///*      
      buffer_pos += (statement_term_d + sizeof(byte8) - base_pos
		     - ((int64)buffer_pos - (int64)ubuf) / sizeof(unichar));
      ///*      
      size_left = nchars_pass - ((int64)buffer_pos-(int64)ubuf)/sizeof(unichar);

      // reset the state machs
      //
      statement_asgn_d = -1;
      statement_term_d = -1;
      token_count_d = 0;
      param_d = -1;
      state_d = NO_GPI;
      parsed_length = 0;
      str.assign(buffer_pos);
      if (debug_level_d >= Integral::DETAILED) {
	str.debug(L"remaining buffer string");
      }

    }
    //end of while loop
    
    // check for symbol table error
    //
    if ((statement_asgn_d != -1) && (param_d < 0)) {
      load_error_d = false;
      return Error::handle(name(), L"load - symbol table error", SofSymbolTable::ERR, __FILE__, __LINE__, Error::WARNING);
    }
    
    // check for a partial parse
    //
    if (param_d != SofSymbolTable::NO_SYMB) {

      // if the param_d is set, then it hit an assignment operator. we
      // just need to throw more data at it until it hits a terminal.
      //
	//        statement_asgn_d += base_pos
	//	+ ((int32)buffer_pos - (int32)ubuf) / sizeof(unichar);
      size_left = 0;
    }
    else {

      // the name might be split across the end of the buffer, so
      // shift it back to the beginning and reset state machine. note
      // that we need to place the "output" back onto the char*
      // buffer, not ubuf.
      //
      size_left = parsed_length;
      SysString leftover;
      leftover.assign(buffer_pos);
      leftover.getBuffer(buffer, size_left+1);
      state_d = NO_GPI;
    }
    // compute the size of the next pass
    //
    if (size_a > (MAX_BUFFER_SIZE - size_left)) {
      read_size = (MAX_BUFFER_SIZE - size_left);
      size_a-=read_size;
    }
    else {
      read_size = size_a;
      size_a = 0;
    }
    // the nchars_pass variable is not corrupted in the loop
    //
    base_pos += (nchars_pass - size_left);

    }

  // initialize used array
  //
  if (table_d.getCount() > used_size_d) {
    if (used_d != (bool8*)NULL) {
      delete [] used_d;
    }
    used_size_d = table_d.getCount();
    used_d = new bool8[used_size_d];
    memset(used_d, 0, used_size_d * sizeof(bool8));
  }

  if (debug_level_d >= Integral::DETAILED) {
    debug(L"after loading");
  }

  if (load_error_d) {
    load_error_d = false;
    return Error::handle(name(), L"load", ERR, __FILE__, __LINE__, Error::WARNING);
  }

  // exit gracefully
  
  //
  return true;
}

// method: read
//
// arguments:
//  SysString& value: (output) data read from file
//  Sof& sof: (input) sof object from which to read
//  int32 size: (input) maximum amount of data to return
//
// return: a bool8 value indicating status
//
// this function reads text data from the file
//
bool8 SofParser::read(SysString& value_a, Sof& sof_a, int32 size_a) {
  
  // if it's not text, return
  //
  if (!sof_a.isText()) {
    return Error::handle(name(), L"read - attempting to read non-text data from file", Error::ARG, __FILE__, __LINE__);
  }

  // seek to the begining of the current objec  //
  // sof_a.seek(index_d.getPosition(), File::POS);

  // range check size
  //
  if (size_a == FULL_OBJECT) {
    size_a = full_size_d;
  }
      
  if (debug_level_d >= Integral::BRIEF) {
    SysString output;
    SysString numeric;
    output.assign(L"reading from ");
    numeric.assign(sof_a.tell());
    output.concat(numeric);
    output.concat(L" to ");
    numeric.assign((int32)(size_a + sof_a.tell()));
    output.concat(numeric);
    Console::put(output);
  }
  
  // read in the data
  //
  byte8 buffer[size_a + 1];
  
  if (sof_a.read(buffer, sizeof(byte8), size_a) != size_a) {
    return Error::handle(name(), L"read - unable to read buffer form sof object", Error::READ, __FILE__, __LINE__, Error::WARNING);
  }
  
  buffer[size_a] = (byte8)NULL;
  
  // we need to deal with the data as unichar characters
  //
  unichar ubuf[size_a + 1];
  MemoryManager::memset(ubuf, 0, sizeof(unichar) * (size_a + 1));
  SysString str;
  str.assign((byte8*)buffer, size_a + 1);
  if (debug_level_d >= Integral::BRIEF) {
    str.debug(L"reading this string");
  }
   str.getBuffer(ubuf, size_a + 1);
  
  int32 length = -1;
  
  // pre-parse the data
  //
  state_d = NO_GPI;		  // reset the state machine
  statement_asgn_d = 1;		  // prevent us picking up any more '=' chars
  open_index_d = false;           // don't add to the index
  
  if (!preParse(length, (unichar*)ubuf, size_a, 0)) {
    return Error::handle(name(), L"read - error parsing rvalue", ERR_RVALUE, __FILE__, __LINE__, Error::WARNING);
  }

  ubuf[length] = (unichar)NULL;
  
  // reset the machine
  //
  state_d = NO_GPI;
  statement_asgn_d = -1;
  statement_term_d = -1; 

  value_a.assign(ubuf);

  if (debug_level_d >= Integral::BRIEF) {
    value_a.debug(L"after read, parsed this string");
  }
  
  // make sure we are returning a valid string. the delimiter
  // character or the terminator character can be terminated in the
  // preParse function. so, both length and (length-1) are valid.
  //
  if ((value_a.length() < (length-1)) || (value_a.length() > length)) {
    return Error::handle(name(), L"read - error parsing rvalue", ERR_RVALUE, __FILE__, __LINE__, Error::WARNING);
  }
 
  if (debug_level_d >= Integral::BRIEF) {
    value_a.debug(L"returning this string");
  }
  
  // exit gracefully
  //
  return true;
}

// method: reset
//
// arguments: none
//
// return: a bool8 value indicating status
//
// this method resets the class for a new parse.
//
bool8 SofParser::reset() {
  
  // reset the list and symbol table
  //
  index_d.clear();
  table_d.clear();
  
  // initialize all variables
  //
  state_d = NO_GPI;
  param_d = SofSymbolTable::NO_SYMB;
  block_count_d = 0;
  token_count_d = 0;

  statement_asgn_d = -1;
  statement_term_d = -1;
  statement_last_token_d = -1;
  
  base_position_d = 0;
  full_size_d = FULL_OBJECT;
  
  open_index_d = false;
  implicit_object_d = false;
  implicit_block_d = false;
  is_token_d = false;
  
  // exit gracefully
  //
  return true;
}
