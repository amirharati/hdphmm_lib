// file: $isip/class/shell/Sdb/sdb_03.cc
// version: $Id: sdb_03.cc 5762 2000-12-06 20:39:45Z duncan $
//

// isip include files
//
#include "Sdb.h"

// method: read
//
// arguments:
//  Sof& sof: (input) sof file object
//  int32 tag: (input) sof object instance tag
//  const String& name: (input) sof object instance name
//
// return: a bool8 value indicating status
//
// this method has the object read itself from an Sof file
//
bool8 Sdb::read(Sof& sof_a, int32 tag_a, const String& name_a) {

  // get the instance of the object from the Sof file
  //
  if (!sof_a.find(name_a, tag_a)) {
    return false;
  }

  // read the actual data from the sof file
  //
  if (!readData(sof_a)) {
    return false;
  }

  // exit gracefully
  //
  return true;
}

// method: readData
//
// arguments:
//  Sof& sof: (input) sof file object
//  const String& pname: (input) parameter name
//  int32 size: (input) size of the object
//  bool8 param: (input) is the parameter specified?
//  bool8 nested: (input) is this nested?
//
// return: a bool8 value indicating status
//
// this method has the object read itself from an Sof file. it assumes
// that the Sof file is already positioned correctly.
//
bool8 Sdb::readData(Sof& sof_a, const String& pname_a,
		      int32 size_a, bool8 param_a,
		      bool8 nested_a) {

  // first clear the object
  //
  if (!clear(Integral::RETAIN)) {
    return Error::handle(name(), L"readData", Error::READ,
			 __FILE__, __LINE__, Error::WARNING);
  }

  // for text mode loop over the file and call parse
  //
  if (sof_a.isText()) {
    String line;
    Filename new_file;
    bool8 is_list = false;

    // read until this object is out of data
    //
    while (sof_a.gets(line)) {

      // if the line parses, append it to the list. note that the
      // parse method does NOT clear the output new_file, it just
      // appends valid characters to it. hence we must clear the
      // new_file variable after a valid parse.
      //
      if (parse(new_file, is_list, line)) {
	append(new_file, is_list);
	new_file.clear();
      }
    }
  }
  
  // binary mode -- use standard Sof
  //
  else {
    files_d.readData(sof_a, size_a);
  }

  // exit gracefully
  //
  return true;
}

// method: parse
//
// arguments:
//  Filename& fname: (output) parsed filename
//  bool8& list: (output) is this entry a list?
//  const String& buffer: (input) line of text from file
//
// return: a bool8 value indicating status
//
// this method parses a line of text and returns a filename.
//
bool8 Sdb::parse(Filename& fname_a, bool8& list_a, const String& buffer_a) {

  // initialize output
  //
  list_a = false;
  
  // enumerate the states:
  //  NO_GPI-> no good previous input
  //  GPI-> good previous input
  //  COMMENT_OP_NO_GPI-> comment operator, no good previous input
  //  COMMENT_OP_GPI-> comment operator, good previous input
  //  LITERAL_OP-> literal operator
  //
  enum STATE { NO_GPI, GPI, COMMENT_OP_NO_GPI, COMMENT_OP_GPI, LITERAL_OP };

  // initialize the state
  //
  STATE state = NO_GPI;

  // declare local variables
  //
  SysChar LITERAL_CHAR(SofParser::LITERAL_CHAR);
  SysChar COMMENT_CHAR(SofParser::DEF_COMMENT_CHAR);

  // get the length of the input buffer and filename to parse
  //
  int32 in_length = buffer_a.length();
  int32 o_ptr = fname_a.length();

  // create space in output filename
  //
  fname_a.setCapacity(o_ptr + in_length);

  // loop over the length of the input buffer
  //
  for (int32 i_ptr = 0; i_ptr < in_length; i_ptr++) {

    // declare local variables
    //
    Char c(buffer_a(i_ptr));
    
    // state 0: no good previous input
    //
    if (state == NO_GPI) {

      // in case of "space" just stay in state
      //
      if (c.isSpace()) {

	// stay in state
	//
      }

      // check for L'\''
      //
      else if (c.eq(COMMENT_CHAR)) {
	state = COMMENT_OP_NO_GPI;
      }

      // check for L'\\'
      //
      else if (c.eq(LITERAL_CHAR)) {
	state = LITERAL_OP;
      }

      // else go to "good previous input" state
      //
      else {
	fname_a(o_ptr++) = buffer_a(i_ptr);
	state = GPI;
      }
    }

    // state 1: good previous input
    //
    else if (state == GPI) {

      // check for L'\''
      //      
      if (c.eq(COMMENT_CHAR)) {
	state = COMMENT_OP_GPI;
      }

      // check for L'\\'
      //      
      else if (c.eq(LITERAL_CHAR)) {
	state = LITERAL_OP;
      }

      else {
	fname_a(o_ptr++) = buffer_a(i_ptr);
      }
    }
    
    // state 2: comment operator, no good previous input
    //
    else if (state == COMMENT_OP_NO_GPI) {

      // there is no way to end a comment block, so if we enter the
      // comment state without any good previous input, there is no
      // filename on the line.
      // 
      return false;
    }

    // state 3: comment operator, good previous input
    //
    else if (state == COMMENT_OP_GPI) {

      // there is no way to end a comment block, so if we enter the
      // comment state just return what we have
      // 
      fname_a(o_ptr) = L'\0';
      return true;
    }
    
    // state 4: literal operator
    //
    else if (state == LITERAL_OP) {

      // pass the character through unmodified.
      //
      fname_a(o_ptr++) = buffer_a(i_ptr);
      state = GPI;
    }

    // increment the input pointer
    //
  }

  // set the length of the filename
  //
  fname_a(o_ptr) = L'\0';

  // if we end in the GPI state, we're done
  //
  if (state == GPI) {

    // check if the first part of the string is the list indicator
    //
    static const int32 lfm_len = LIST_FILE_MARKER.length();
    if ((LIST_FILE_MARKER.comparePartial(fname_a, 0, lfm_len, 0))
	== Integral::EQUAL) {
      list_a = true;
      fname_a.deleteRange(0, lfm_len);
      fname_a.trimLeft();
    }

    return true;
  }

  // if we end in the literal op state, we need more
  // input.
  //
  else if (state == LITERAL_OP) {
    return false;
  }

  // exit (un)gracefully
  //
  return false;
}
