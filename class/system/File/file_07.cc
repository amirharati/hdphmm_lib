// file: $isip/class/system/File/file_07.cc
// version: $Id: file_07.cc 9314 2003-09-30 01:29:13Z parihar $
//

// system include files
//
#include "unistd.h"

// isip include files
//
#include "File.h"
#include <SysString.h>
#include <Console.h>
 
// method: truncate
//
// arguments:
//  int32 size: (input) size of file in bytes
//
// return: a bool8 value indicating status
//
// truncate the file to the given size
//
bool8 File::truncate(int32 size_a) {
  
  // check the file pointer
  //
  if (fp_d == (FILE*)NULL) {
    return Error::handle(name(), L"truncate", ERR_NOTOPN, __FILE__, __LINE__);
  }

  // check the mode
  //
  if (mode_d == READ_ONLY) {
    return Error::handle(name(), L"truncate", Error::MOD_READONLY,
			 __FILE__, __LINE__);
  }
  
  // call the system function
  //
  if (::ftruncate(fileno(fp_d), size_a) != 0) {
    return Error::handle(name(), L"truncate", ERR_TRUNCT, __FILE__, __LINE__);
  }
  
  // exit gracefully
  //
  return true;
}

// method: flush
//
// arguments: none
//
// return: a bool8 value indicating status
//
// flush the file stream
//
bool8 File::flush() {

  // check the file pointer
  //
  if (fp_d == (FILE*)NULL) {
    return Error::handle(name(), L"flush", ERR_NOTOPN, __FILE__,
			 __LINE__, Error::WARNING);
  }
  
  // check the mode
  //
  if (mode_d == READ_ONLY) {
    return Error::handle(name(), L"flush", Error::MOD_READONLY,
			 __FILE__, __LINE__, Error::WARNING);
  }
  
  // call the system function
  //
  if (::fflush(fp_d) == EOF) {
    return Error::handle(name(), L"flush", ERR_FLUSH, __FILE__,
			 __LINE__, Error::WARNING);
  }
  
  // exit gracefully
  //
  return true;
}

// method: lock
//
// arguments:
//  int32 retry: (input) number of times to try for the lock
//  int32 delay: (input) pause in seconds between attempts
//
// return: a bool8 value indicating status
//
// this method locks the file, if it fails, it keeps trying retry_a times
//
bool8 File::lock(int32 retry_a, int32 delay_a) {

  // make sure we have an acceptable mode
  //
  if (mode_d == READ_ONLY) {
    return Error::handle(name(), L"lock",
			 Error::FILE_LOCK_READONLY, __FILE__, __LINE__);
  }
  
  // make sure the file is not already locked
  //
  if (lock_d) {
    return true;
  }
  
  // if no lock_retry, just try once
  //
  if (retry_a < 0) {
    if (::lockf(fileno(fp_d), F_LOCK, 0) == 0) {
      lock_d = true;
    }
  }
  
  // try as many as the given times to lock the file
  //
  for (int32 n = 0; n <= retry_a; n++) {
    
    // lockf works on nfs files across systems
    //
    if (::lockf(fileno(fp_d), F_TLOCK, 0) == 0) {
      lock_d = true;
    }
    else {
      if ((n + 1) <= retry_a) {

	// delay some seconds before next retry
	//
	Console::put(L"<File::lock> waiting for file lock\n");
	Integral::sleep(delay_a);
      }
    }
  }
  
  // error if lock unsuccessfully
  //
  if (!lock_d) {
    Error::handle(name(), L"lock", Error::FILE_LOCK, __FILE__, __LINE__,
		  Error::WARNING);
    return false;
  }
  
  // exit gracefully
  //
  return true;
  
}

// method: unlock
//
// arguments: none
//
// return: a bool8 value indicating status
//
// this method unlocks the file
//
bool8 File::unlock() {

  // reset the lock
  //
  if (lock_d) {
    
    // lockf works on nfs files across systems
    //
    if (::lockf(fileno(fp_d), F_ULOCK, 0) != 0) {
      return Error::handle(name(), L"unlock", Error::FILE_UNLOCK,
			   __FILE__, __LINE__);
    }
    lock_d = false;
  }
  
  // exit gracefully
  //
  return true;
}

// method: open
//
// arguments:
//  const unichar* filename: (input) file to open
//  MODE mode: (input) open mode
//  TYPE type: (input) file type
//
// return: a bool8 value indicating status
//
// open the file, if it fails, it keeps trying open_retry_d times
//
bool8 File::open(const unichar* filename_a, MODE mode_a, TYPE type_a) {

  SysString temp(filename_a);

  // call the master function
  //
  return open(temp, mode_a, type_a);
}

// method: open
//
// arguments:
//  const SysString& filename: (input) file to open
//  MODE mode: (input) open mode
//  TYPE type: (input) file type
//
// return: a bool8 value indicating status
//
// open the file, if it fails, it keeps trying open_retry_d times
//
bool8 File::open(const SysString& filename_a, MODE mode_a, TYPE type_a) {

  // check the file pointer
  //
  if (fp_d != (FILE*)NULL) {
    Error::handle(name(), L"open", ERR_REOPEN, __FILE__, __LINE__,
		  Error::WARNING);
    
    if (!close()) {
      return Error::handle(name(), L"open", ERR_CLOSE, __FILE__, __LINE__,
			   Error::WARNING);
    }
  }

  // set the file type
  //
  if (type_d != type_a) {
    type_d = type_a;
  }
  
  // if the filename is a stream, set it to either read only or write only
  //
  if (filename_a.eq(STREAM_FILE)) {

    if (mode_a == READ_ONLY) {

      // set the file mode
      //
      if (mode_d != mode_a) {
	mode_d = mode_a;
      }

      // set the stream_d to IN so that the destructor will remove the
      // temporary file
      //
      setStreamType(IN);

      // set the file pointer to stdin
      //
      fp_d = stdin;
      
      // create Systring object for temporary file
      //
      SysString temp_file;
      
      // declare an output file pointer
      //
      FILE* o_fp;
      
      // create temporary file.
      //
      Integral::makeTemp(temp_file);
      
      // register this temporary file so that it can be deleted later
      // by the destructor
      //
      registerTemp(temp_file);
      
      // create an 8 bit buffer
      //
      byte8 buffer;
      
      // get a file pointer to the temp file
      //
      o_fp = fopen((char*)(byte8*)temp_file, SYS_BINARY_WRITE_PLUS);
      
      // read one unit (8 bits) from stdin and write it to the temp
      // file, until fread does not return 1
      //
      while(::fread(&buffer, sizeof(byte8), 1, fp_d) == 1) {
	
	// null file pointer, error
	//
	if (o_fp == (FILE*)NULL) { 
	  return Error::handle(name(), L"open", ERR_NOTOPN,
			       __FILE__, __LINE__);
	}
	
	// write the 8-bit buffer
	//
	if (::fwrite(&buffer, sizeof(byte8),1,o_fp) != 1) {
	  return Error::handle(name(), L"open", Error::WRITE,
			       __FILE__, __LINE__);
	}
      }
      
      // set file pointer back to start of file
      //
      Integral::fseek(o_fp,0,POS);
      
      // point the file pointer to the temp file
      //
      fp_d = o_fp;
      
      return true;
    }

    else if (mode_a == WRITE_ONLY) {

      // set the file mode
      //
      if (mode_d != mode_a) {
	mode_d = mode_a;
      }
      
      fp_d = stdout;
      return true;
    }

    else {
      return Error::handle(name(), L"open", Error::ARG, __FILE__, __LINE__);
    }
  }
  
  // see if we can expand the filename
  //
  SysString fn;
  if (!Integral::expandName(fn, filename_a)) {
    SysString output(L"File not found: ");
    output.concat(filename_a);
    output.concat(L"\n");
    return Error::handle(name(), L"open", Error::FILENAME_EXPAND,
			 __FILE__, __LINE__, Error::WARNING, output);
  }

  // loop the file is open or until the number of retries is exhausted
  //
  for (int32 count = 0; (count <= open_retry_d) && (fp_d == (FILE*)NULL);
       count++) {

    // branch on type
    //
    if (type_a == TEXT) {
      
      // branch on mode, open the file
      //
      if (mode_a == READ_ONLY) {
	fp_d = fopen((char*)(byte8*)fn, SYS_TEXT_READ_ONLY);
      }
      
      else if (mode_a == READ_PLUS) {
	fp_d = fopen((char*)(byte8*)fn, SYS_TEXT_READ_PLUS);
      }
      
      else if (mode_a == WRITE_ONLY) {
	fp_d = fopen((char*)(byte8*)fn, SYS_TEXT_WRITE_ONLY);
      }
      
      else if (mode_a == WRITE_PLUS) {
	fp_d = fopen((char*)(byte8*)fn, SYS_TEXT_WRITE_PLUS);
      }
      
      else if (mode_a == APPEND_ONLY) {
	fp_d = fopen((char*)(byte8*)fn, SYS_TEXT_APPEND_ONLY);
      }
      else if (mode_a == APPEND_PLUS) {
	fp_d = fopen((char*)(byte8*)fn, SYS_TEXT_APPEND_PLUS);
      }
    }
    
    else if (type_a == BINARY) {
      
      // branch on mode, open the file
      //
      if (mode_a == READ_ONLY) {
	fp_d = fopen((char*)(byte8*)fn, SYS_BINARY_READ_ONLY);
      }

      else if (mode_a == READ_PLUS) {
	fp_d = fopen((char*)(byte8*)fn, SYS_BINARY_READ_PLUS);
      }
      
      else if (mode_a == WRITE_ONLY) {
	fp_d = fopen((char*)(byte8*)fn, SYS_BINARY_WRITE_ONLY);
      }

      else if (mode_a == WRITE_PLUS) {
	fp_d = fopen((char*)(byte8*)fn, SYS_BINARY_WRITE_PLUS);
      }

      else if (mode_a == APPEND_ONLY) {
	fp_d = fopen((char*)(byte8*)fn, SYS_BINARY_APPEND_ONLY);
      }

      else if (mode_a == APPEND_PLUS) {
	fp_d = fopen((char*)(byte8*)fn, SYS_BINARY_APPEND_PLUS);
      }
    }
    
    // not a valid open mode
    //
    else {
      return Error::handle(name(), L"open", Error::ARG, __FILE__, __LINE__);
    }
    
    // if the file was not opened then delay if required
    //
    if (fp_d == (FILE*)NULL) {
      
      // sleep if we need to retry the open
      //
      if (count < open_retry_d) {
	SysString msg(L"<File::open> waiting for file open: ");
	msg.concat(fn);
	Console::put(msg);
	Integral::sleep(open_delay_d );
      }

      // return with a warning
      //
      else {
	SysString output(L"File: ");
	output.concat(filename_a);
	output.concat(L"\n");
	return Error::handle(name(), L"openRead", Error::FILE_NOTFND,
			     __FILE__, __LINE__, Error::WARNING, output);
      }
    }
  }

  // set other class data
  //
  mode_d = mode_a;
  type_d = type_a;
  lock_d = false;
    
  // exit gracefully
  //
  return true;
}

// method: close
//
// arguments: none
//
// return: a bool8 value indicating status
//
// close the file
//
bool8 File::close() {

  // check the file pointer
  //
  if (fp_d == (FILE*)NULL) {
    return Error::handle(name(), L"close", ERR_NOTOPN, __FILE__, __LINE__,
			 Error::WARNING);
  }
  
  // if the file isn't a standard stream, close it
  //
  if ((fp_d != stdout) && (fp_d != stdin) && (fp_d != stderr)) {
    ::fclose(fp_d);
  }

  // reset
  //
  fp_d = (FILE*)NULL;
  mode_d = DEF_MODE;
  type_d = DEF_TYPE;
  
  // exit gracefully
  //
  return true;
}

// method: seek
//
// arguments:
//  int32 offset: (input) byte offset
//  SEEK mode: (input) where to seek from
//
// return: a bool8 value indicating status
//
// seek to the specified location within the open file
//
bool8 File::seek(int32 offset_a, SEEK mode_a) {

  // check the file pointer
  //
  if (fp_d == (FILE*)NULL) {
    return Error::handle(name(), L"seek", ERR_NOTOPN, __FILE__, __LINE__,
			 Error::WARNING);
  }
  
  // call the system function
  //
  if (::fseek(fp_d, offset_a, (int32)mode_a) != 0) {
    return Error::handle(name(), L"seek", Error::SEEK, __FILE__, __LINE__,
			 Error::WARNING);
  }
  
  // exit gracefully
  //
  return true;
}

// method: tell
//
// arguments: none
//
// return: a int32 number
//
// determine the file position
//
int32 File::tell() const {

  // check the file pointer
  //
  if (fp_d == (FILE*)NULL) {
    Error::handle(name(), L"tell", ERR_NOTOPN, __FILE__, __LINE__,
		  Error::WARNING);
    return BAD_COUNT;
  }
  
  // call the system function
  //
  int32 pos = ::ftell(fp_d);
  
  // error check system call
  //
  if (pos < 0) {
    return Error::handle(name(), L"tell", Error::SYS_CALL, __FILE__,
			 __LINE__, Error::WARNING);
  }
  
  // exit gracefully
  //
  return pos;
}

// method: put
//
// arguments:
//  const SysChar chr: (input) character to write
//  
// return: a bool8 value indicating status
//
// output a char into the file
//
bool8 File::put(const SysChar chr_a) {

  // null file pointer, error
  //
  if (fp_d == (FILE*)NULL) { 
    return Error::handle(name(), L"put", Error::WRITE_CLOSED,
			 __FILE__, __LINE__);
  }

  // check the mode
  //
  if (mode_d == READ_ONLY) {
    return Error::handle(name(), L"put", Error::MOD_READONLY,
			 __FILE__, __LINE__);
  }

  // temporary variable
  //
  unichar chr = chr_a;
  
  // put the character
  //
  if (SysString::isip_fputwc(chr, fp_d) == (wint_t)WEOF) {
    
    // nothing has been put
    //
    return false;
  }
  
  // exit gracefully
  //
  return true;
}

// method: put
//
// arguments:
//  const SysString& str: (output) String of data to write
//  
// return: a bool8 value indicating status
//
// put a string into the file
//
bool8 File::put(const SysString& str_a) {
  
  // check the file pointer
  //
  if (fp_d == (FILE*)NULL) {
    return Error::handle(name(), L"put", Error::WRITE_CLOSED,
			 __FILE__, __LINE__);
  }
  
  // check the file mode
  //
  if (mode_d == READ_ONLY) {
    return Error::handle(name(), L"put", Error::MOD_READONLY,
			 __FILE__, __LINE__);
  }
  
  // a local flag indicating line-wrapping
  //
  bool8 wrapping = false;
  
  // if we aren't indenting or wrapping, easy
  //
  if ((indent_level_d <= 0) && (line_wrap_d <= 0)) {
    
    // write the string
    //
    if (SysString::isip_fputws((unichar*)str_a, fp_d) < 0) {
      
      // nothing has been written
      //
      return false;
    }

    // check column position
    //
    int32 l = str_a.length();
    if ((l > 0) && (str_a(l - 1) == L'\n')) {
      column_position_d = 0;
    }
    else {
      column_position_d = 1;
    }
  }

  // else we need to go through newline by newline
  //
  else {

    // build the indent string
    //
    SysString indent_str;
    for (int32 i = 0; i < indent_level_d; i++) {
      indent_str.concat(INDENT_STR);
    }
    
    SysString out_str;

    // we will deal with characters from start_pos to stop_pos,
    // inclusive, every iteration
    //
    int32 start_pos = 0;
    int32 stop_pos = -1;
    int32 next_newline = -1;
    
    do {
      
      // find the newline
      //
      if (next_newline < start_pos) {
	next_newline = str_a.firstChr(L'\n', start_pos);
      }
      stop_pos = next_newline;
      
      // terminal condition
      //
      if (stop_pos == Integral::NO_POS) {
	stop_pos = str_a.length() - 1;
      }
      
      int32 tot_len;

      // if we are at the beginning of a line
      //
      if (column_position_d == 0) {
	tot_len = stop_pos - start_pos + 1 + indent_str.length();
      
	// write out the pre-indent wrap string
	//
	if (wrapping) {
	  const int32 wpis_len = WRAP_PRE_INDENT_STR.length();
	  tot_len += wpis_len;
	  
	  if (SysString::isip_fputws((unichar*)WRAP_PRE_INDENT_STR, fp_d) < 0){
	    return false;
	  }
	}
	
	// write out the indentation string
	//
	if (indent_level_d > 0) {
	  if (SysString::isip_fputws((unichar*)indent_str, fp_d) < 0) {
	    return false;
	  }
	}
	
	// write out the post-indent wrap string
	//
	if (wrapping) {
	  const int32 wpi_len = WRAP_POST_INDENT_STR.length();
	  tot_len += wpi_len;
	  
	  if (SysString::isip_fputws((unichar*)WRAP_POST_INDENT_STR,fp_d) < 0){
	    return false;
	  }
	}
      }

      // else we are continuing a line
      //
      else {
	tot_len = stop_pos - start_pos + 1 + column_position_d;
      }
      
      // possibly wrap
      //
      if ((line_wrap_d > 0) && (tot_len > line_wrap_d)) {

	// make sure user settings are possible (that we can at least
	// print 1 character per line
	//
	if ((tot_len - (stop_pos - start_pos + 1)) > line_wrap_d) {
	  return Error::handle(name(), L"put", ERR_WRAP,
			       __FILE__, __LINE__, Error::WARNING);
	  line_wrap_d = DEF_LINE_WRAP;
	}
	    
	// set the flag
	//
	wrapping = true;
	
	// if we wrap, we need the wrap terminating string
	//
	const int32 wts_len = WRAP_TERM_STR.length();
	tot_len += wts_len - 1;
	
	// decrement stop_pos by how much we overlap
	//
	stop_pos = start_pos + (line_wrap_d -
				(tot_len - (stop_pos - start_pos + 1)));
	
	// keep decrementing until we hit a good break point
	//
	int32 good_stop_pos = stop_pos + 1;
	SysChar current_char;

	do {
	  good_stop_pos--;
	  if (good_stop_pos <= start_pos) {
	    break;
	  }
	  current_char.assign(str_a(good_stop_pos));
	} while ((current_char.isPrint()) &&
		 (!current_char.isSpace()));
	
	// if we found a good break point, modify stop_position to be
	// this new break point. If not, then we have to live with
	// breaking exactly at the specified location
	//
	if (good_stop_pos > start_pos) {
	  stop_pos = good_stop_pos;
	}

	// if there is no good breakpoint on this line but this line
	// already had stuff on it, then don't print anything on this
	// line and try again to tokenize the next line
	//
	else if (column_position_d != 0) {
	  stop_pos = start_pos - 1;
	}
	
	column_position_d = line_wrap_d;
      }
      else {

	// clear the flag
	//
	wrapping = false;
	column_position_d = tot_len;
      }
	
      // write out this portion of the string
      //
      str_a.substr(out_str, start_pos, stop_pos - start_pos + 1);
      if (SysString::isip_fputws((unichar*)out_str, fp_d) < 0) {
	return false;
      }

      int32 l = out_str.length();
      if ((l > 0) && (out_str(l - 1) == L'\n')) {
	column_position_d = 0;
      }
      
      // possibly add the terminator
      //
      if (wrapping) {
	if (SysString::isip_fputws((unichar*)WRAP_TERM_STR, fp_d) < 0) {
	  return false;
	}
	column_position_d = 0;
      }

      // get he next start_pos
      //
      start_pos = stop_pos + 1;

    } while (stop_pos < (str_a.length() -1));
  }
  
  // exit gracefully
  //
  return true;
}

// method: setOpenRetry
//
// arguments:
//  int32 retry: (input) number of times to try to open the file
//  int32 delay: (input) pause in seconds between attempts
//
// return: a bool8 value indicating status
//
// this method sets the number of retry times that a file will be polled for
// opening before an error is returned. this is useful in the case
// when the file system says the file doesn't exist, but it really does
// (such as a file system error).
//
bool8 File::setOpenRetry(int32 retry_a, int32 delay_a) {
  
  // check arguments
  //
  if ((retry_a < 0) || (delay_a < 1)) {
    return Error::handle(name(), L"setOpenRetry", Error::ARG,
			 __FILE__, __LINE__);
  }

  // set the retry flags
  //
  open_retry_d = retry_a;
  open_delay_d = delay_a;

  // exit gracefully
  //
  return true;
}

// method: size
//
// arguments:
//  bool8 keep_position: (input) whether we should preserve the
//                                 current position
//
// return: size of the file in bytes
//
// determine the size of the given file
//
int32 File::size(bool8 keep_position_a) const {

  // make sure the file is open
  //
  if (!isOpen()) {
    Error::handle(name(), L"size", ERR_NOTOPN, __FILE__, __LINE__);
    return -1;
  }

  // possibly save the seek position
  //
  int32 cur_pos = -1;
  if (keep_position_a) {
    cur_pos = tell();
  }
  
  int32 tsize = -1;
  
  // seek to the end of the file
  //
  const_cast<File*>(this)->seek(0, POS_PLUS_END);

  // save the size
  //
  tsize = tell();

  // possibly seek back to the previous position
  //
  if (keep_position_a) {
    const_cast<File*>(this)->seek(cur_pos, POS);
  }

  // return the size
  //
  return tsize;
}
