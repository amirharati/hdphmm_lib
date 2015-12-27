// file: $isip/class/io/SofParser/sofp_05.cc
// version: $Id: sofp_05.cc 8921 2002-12-17 16:35:31Z parihar $
//
 
// isip include files
//
#include "SofParser.h"

// method: preParse
//
// arguments:
//  int32& out_len: (output) size of clean entry
//  unichar* buffer: (input/output) parameter file text
//  int32 in_len: (input) size of buffer
//  int32 offset: (input) where to set absolute positions from
//
// return: a bool8 value indicating status
//
// this method pre parses the buffer to remove comments, and excess
// whitespace, handle literal characters and quotation marks, and
// checks to make sure that there are no hanging quotation marks
//
// this function runs off of a state machine, see documentation
// for a diagram if interested.
//
bool8 SofParser::preParse(int32& out_len_a, unichar* buffer_a,
			    int32 in_len_a, int32 offset_a) {
  
  unichar* buff_p;
  unichar* fixed_buff_p;
  
  // buff_p: the pointer to the original buffer that is read from
  // fixed_buff_p: the pointer that is written to.
  //
  // note: we can both read at buff_p and write at fixed_buff_p
  //       since buff_p >= fixed_buff_p and we always read before
  //       we write
  //
  buff_p = buffer_a;
  fixed_buff_p = buffer_a;
  SysChar c;
  ///*
  int64 current_pos = 0;

  // go through the state machine
  //
  ///*   
  while (((int64)buff_p - (int64)buffer_a)/(int64)sizeof(unichar) < in_len_a) {
      ///*
       current_pos = ((int64)buff_p - (int64)buffer_a) / sizeof(unichar) + offset_a;


 
    c.assign((unichar)*buff_p);
    
    // give debug information for the state machine
    //
    if (debug_level_d > Integral::DETAILED) {

      SysChar fixed((unichar)*fixed_buff_p);
      SysString numeric(current_pos);
      
      SysString message(L"*buff=");
      numeric.assign(c);
      message.concat(numeric);
      message.concat(L", *fixed=");
      numeric.assign(fixed);
      message.concat(numeric);
      message.concat(L", pos=");
      message.concat(numeric);
      
      numeric.assign(out_len_a);
      message.concat(L", out_len=");
      message.concat(numeric);

      setString(numeric, state_d);
      message.concat(L", state=");
      message.concat(numeric);
      
      numeric.assign(statement_last_token_d);
      message.concat(L", last_tok=");
      message.concat(numeric);
      
      numeric.assign(token_count_d);
      message.concat(L", tok_cnt=");
      message.concat(numeric);
      
      Console::put(message);
    }
    
    // branch on state
    //
    //----------------------------------
    // state: no good previous input (initial state)
    //----------------------------------
    //
    if (state_d == NO_GPI) {
      
      // branch on input
      //
      
      // input is whitespace, no change of state, no output
      //
      if (c.isSpace()) {
	
	// nothing is done here
	//
      }

      // input is the terminal character, null valid statement
      //
      else if (c.eq(terminator_char_d)) {
	  return false;
      }
      
      // input is comment operator, go into ngpi comment state, no output
      //
      else if (c.eq(comment_char_d)) {
	state_d = COMMENT_OP_NO_GPI;
      }
      
      // input is quote operator, go into quote state, output
      //
      else if (c.eq(QUOTE_CHAR)) {
	state_d = QUOTE_OP;
      }
      
      // input is literal operator, go into literal state, no output
      //
      else if (c.eq(LITERAL_CHAR)) {
	state_d = LITERAL_OP;
      }

      // input is a block_start character, do nothing
      //
      else if (c.eq(blockstart_char_d)) {

	// if we are nested, the first block-start encountered
	// is not output, and we set the implicit_block flag
	//
	if (nest_d && (!implicit_block_d)) {
	  implicit_block_d = true;
	}

	// else we need to worry about this block-start char
	//
	else {

	  // if we are within the token range, output char
	  //
	  if ((token_count_d >= token_start_d)
	      && (token_count_d < token_stop_d)) {
	    *fixed_buff_p = *buff_p;
	    fixed_buff_p++;
	  }
	  
	  // everything within this block is left for the sub-object to parse
	  //
	  block_count_d++;
	  statement_last_token_d = current_pos;
	  state_d = BLOCK_GPI; 
	}
      }

      // input is a block_stop character, decrease block_count but
      // stay in nogpi state
      //
      else if (c.eq(blockstop_char_d)) {

	// if we dug through one level of brackets, then hitting a
	// blockstop means the data is null
	//
	if (nest_d && implicit_block_d) {
	  out_len_a = 0;
	  *fixed_buff_p =NULL_CHAR;  //I  delete  (int32)
	   // valid read
	  //
	  return true;
	}

	// any other time a blockstop char means error
	//
	else {
	  return false;
	}
      }
      
      // else copy character directly, go into gpi state
      //
      else {

	if ((token_count_d >= token_start_d)&&(token_count_d < token_stop_d)) {
	  *fixed_buff_p = *buff_p;
	  fixed_buff_p++;
	}
	
	if (c.eq(delimiter_char_d)) {
	  
	  // just increment the counter, never output the first or last
	  // delimiter character
	  //
	  token_count_d++;
	}

	// we wanted to break into a nest, we didn't
	//
	if (nest_d && (!implicit_block_d)) {

	  // let's figure we were tokenizing so we never hit the open
	  // brace
	  //
	  implicit_block_d = true;
	}
	
	// if this is an implicit parameter, the first character
	// parsed is the first character of data
	//
	if (implicit_object_d) {
	  
	  // good input received, go into GPI state and set last_token
	  //
	  statement_last_token_d = current_pos;
	  statement_asgn_d = current_pos;
	}
	 // go into GPI state
	//
	state_d = GPI;
      }
    }

  
    //----------------------------------
    // state: comment operator in ngpi state
    //----------------------------------
    //
    else if (state_d == COMMENT_OP_NO_GPI) {
      
      // go back to no gpi state on newline, stay in this state if
      // not, no output in either case
      //
      if (c.eq(NEWLINE_CHAR)) {
	state_d = NO_GPI;
      }
    }
    
    //----------------------------------
    // state: literal operator
    //----------------------------------
    //
    else if (state_d == LITERAL_OP) {

      // if tokenizing, only output if we have surpassed token_start_d
      //
      if ((token_count_d >= token_start_d) && (token_count_d < token_stop_d)) {
	
	// regardless of input, output the character and go to gpi
	// state,
	//
	*fixed_buff_p = *buff_p;
	fixed_buff_p++;
      }
      
      // if we are in a block, go back to BLOCK_GPI, else GPI
      //
      if (block_count_d == 0) {
	
	// in case the first good character is a literal
	//
	if (implicit_object_d && (statement_last_token_d < 0)) {
	  statement_last_token_d = current_pos;
	  statement_asgn_d = current_pos;
	}
	state_d = GPI;
      }
      else {
	state_d = BLOCK_GPI;
      }
    }

    //----------------------------------
    // state: gpi
    //----------------------------------
    //
    else if (state_d == GPI) {
      
      // make sure statement_asgn_d is set for implicit
      //
      if (implicit_object_d && (statement_asgn_d == -1)) {
	return Error::handle(name(), L"preParse - error parsing rvalue", ERR_RVALUE, __FILE__, __LINE__);
      }
      
      // branch on input
      //
      
      // literal character, go into literal state, no output
      //
      if (c.eq(LITERAL_CHAR)) {
	state_d = LITERAL_OP;
      }
      
      // quote character, go into quote state, no output
      //
      else if (c.eq(QUOTE_CHAR)) {
	state_d = QUOTE_OP;
      }

      // comment operator, go into gpi comment state, output space
      //
      else if (c.eq(comment_char_d)) {

	// only output if we are in the token range
	//
	if ((token_count_d >= token_start_d)&&(token_count_d < token_stop_d)) {
	  *fixed_buff_p = SPACE_CHAR;
	  fixed_buff_p++;
        	}
	state_d = COMMENT_OP_GPI;
      }

      // block start character, increment block start, output
      //
      else if (c.eq(blockstart_char_d)) {
	if ((token_count_d >= token_start_d)&&(token_count_d < token_stop_d)) {
	  *fixed_buff_p = *buff_p;
	  fixed_buff_p++;
	}

	block_count_d++;
	state_d = BLOCK_GPI;
      }

      // block stop character (but not in block_gpi state), only if
      // are nesting was set should this be valid
      //
      //
      else if (c.eq(blockstop_char_d)) {
	
	  if (nest_d && implicit_block_d && implicit_object_d) {///*
	  out_len_a = ((int64)fixed_buff_p - (int64)buffer_a) / sizeof(unichar);
	  state_d = NO_GPI;
	  *fixed_buff_p = NULL_CHAR;

	   // used to be token_count > 0
	  //
	  if (open_index_d && (statement_last_token_d > 0)) {

	    // add the last token
	    //
	    if (token_count_d > 2) {
	      if (!index_d.addQuick(param_d, token_count_d + 1,
				    statement_last_token_d,
				    current_pos - statement_last_token_d)) {
		reportIndexError(param_d, token_count_d + 1,
				 statement_last_token_d);
		return Error::handle(name(), L"preParse - error adding the last token", SofList::ERR, __FILE__, __LINE__, Error::WARNING);
	      }
	    }
	    else {
	      if (!index_d.add(param_d, token_count_d + 1,
			       statement_last_token_d,
			       current_pos - statement_last_token_d)) {
		reportIndexError(param_d, token_count_d + 1,
				 statement_last_token_d);
		return Error::handle(name(), L"preParse - error adding the last token", SofList::ERR, __FILE__, __LINE__, Error::WARNING);
	      }
	    }
	  }
	 
	  implicit_object_d = false;
	  implicit_block_d = false;
	  state_d = NO_GPI;
	  statement_term_d = current_pos;

	  // valid parse
	  //
	  return true;
	}
	
	// invalid parse
	//
	*fixed_buff_p++ = blockstop_char_d;

	return false;
      }

      // terminal character, output it, return the length of the buffer
      //
      else if (c.eq(terminator_char_d)) {

	// if we hit a terminal character, we better not be looking
	// for a nested block end
	//
	if (nest_d && implicit_block_d && implicit_object_d) {

	  // bad parse
	  //
	  *fixed_buff_p = NULL_CHAR;
	  return false;
	}
	
	// always output the terminal character, regardless of token
	//
	*fixed_buff_p = terminator_char_d;
	fixed_buff_p++;
         // add the last token if last char was not assignment char
	//
	if (open_index_d && (statement_last_token_d > 0)
	    && (*(fixed_buff_p - 2) != assignment_char_d)) {
	  
	  // add the last token
	  //
	  if (token_count_d > 2) {
	    if (!index_d.addQuick(param_d, token_count_d + 1,
				  statement_last_token_d,
				  current_pos - statement_last_token_d)) {
	      reportIndexError(param_d, token_count_d + 1,
			       statement_last_token_d);
	      return Error::handle(name(), L"preParse - error adding the last token", SofList::ERR, __FILE__, __LINE__, Error::WARNING);
	    }
	  }
	  else {
	    if (!index_d.add(param_d, token_count_d + 1,
			     statement_last_token_d,
			     current_pos - statement_last_token_d)) {
	      reportIndexError(param_d, token_count_d + 1,
			       statement_last_token_d);
	      return Error::handle(name(), L"preParse - error adding the last token", SofList::ERR, __FILE__, __LINE__, Error::WARNING);
	    }
	  }
	}
	
	statement_term_d = current_pos;
	///*
	out_len_a = ((int64)fixed_buff_p - (int64)buffer_a) / sizeof(unichar);
	state_d = NO_GPI;

	// strip the terminal character from the string
	//
	//Change by Amir: To fix Segmentation fault error
	if (fixed_buff_p>buffer_a)
	*(fixed_buff_p - 1) = NULL_CHAR;
        return true;
      }
      
      // first assignment character, set values, output
      //
      else if (c.eq(assignment_char_d)) {

	// possibly bad parse
	//
	if ((statement_asgn_d != -1) || implicit_object_d) {
	    *fixed_buff_p = NULL_CHAR;
		    
	  return false;
	}
	
	// assign the name of the parameter
	//
	statement_asgn_d = current_pos + 1;
	statement_last_token_d = statement_asgn_d;
	token_count_d = 0;
	///*
	int64 clen = ((int64)fixed_buff_p - (int64)buffer_a) / sizeof(unichar);
	*fixed_buff_p = *buff_p;
	if (!assignName(buffer_a, clen)) {
	  return Error::handle(name(), L"preParse - error parsing lvalue", ERR_LVALUE, __FILE__, __LINE__, Error::WARNING);
	}
	fixed_buff_p++;
      }
	
      // whitespace character, go to gpi/lws state, output space
      //
      else if (c.isSpace()) {
	
	// only output if in current token range
	//
	if ((token_count_d >= token_start_d)&&(token_count_d < token_stop_d)) {
	  *fixed_buff_p = SPACE_CHAR;
	  fixed_buff_p++;
		  
	  state_d = GPI_LWS;
	}
	
	if (delimiter_char_d.eq(SPACE_CHAR)) {
	  // do nothing
	  //
	}
      }
      
      // else copy character directly, no change in state
      //
      else {

	// only output within token limits
	//
	if ((token_count_d >= token_start_d)&&(token_count_d < token_stop_d)) {
	  *fixed_buff_p = *buff_p;
	  fixed_buff_p++;
	}
	
	// add a token
	//
	if (c.eq(delimiter_char_d)) {
	  token_count_d++;
	  if (open_index_d && (param_d >= 0) && (statement_last_token_d>=0)) {

	    if (token_count_d > 2) {
	      if (!index_d.addQuick(param_d, token_count_d,
				    statement_last_token_d,
				    current_pos - statement_last_token_d)) {
		reportIndexError(param_d, token_count_d,
				 statement_last_token_d);
		return Error::handle(name(), L"preParse - error adding the token", SofList::ERR, __FILE__, __LINE__, Error::WARNING);
	      }
	    }
	    else {
	      if (!index_d.add(param_d, token_count_d, statement_last_token_d,
			       current_pos - statement_last_token_d)) {
		reportIndexError(param_d, token_count_d,
				 statement_last_token_d);
		return Error::handle(name(), L"preParse - error adding the token", SofList::ERR, __FILE__, __LINE__, Error::WARNING);
	      }
	    }

	    statement_last_token_d = current_pos + 1;
	  }
	}
      }
    }                                          // end state_d == GPI
    
    //----------------------------------
    // state: quotation operator
    //----------------------------------
    //
    else if (state_d == QUOTE_OP) {
      
      // branch on input
      //
      
      // quote operator again, output it and go to gpi state
      //
      if (c.eq(QUOTE_CHAR)) {
	if (block_count_d == 0) {
	  state_d = GPI;	  
	}
	else {
	  state_d = BLOCK_GPI;	  
	}
      }
      
      // literal operator, go into quote literal state, no output
      //
      else if (c.eq(LITERAL_CHAR)) {
	state_d = LITERAL_OP_IN_QUOTE;
      }

      // else stay in this state copying characters over
      //
      else {

	if (statement_last_token_d < 0) {
	  statement_last_token_d = current_pos;
	}
	if ((token_count_d >= token_start_d)&&(token_count_d < token_stop_d)) {
	  *fixed_buff_p = *buff_p;
	  fixed_buff_p++;
	}
      }
    }
    
    //----------------------------------
    // state: literal operator for inside a quote
    //----------------------------------
    //
    else if (state_d == LITERAL_OP_IN_QUOTE) {

      if (statement_last_token_d < 0) {
	statement_last_token_d = current_pos;
      }
      if ((token_count_d >= token_start_d)&&(token_count_d < token_stop_d)) {
	
	// regardless of input, output the character and go back to
	// quote state
	//
	*fixed_buff_p = *buff_p;
	fixed_buff_p++;
      }
      state_d = QUOTE_OP;
    }

    //----------------------------------
    // state: good previous input, last input whitespace
    //----------------------------------
    //
    else if (state_d == GPI_LWS) {
      
      // branch on input
      //

      // terminal character, trim last whitespace and return buffer
      // no output
      //
      if (c.eq(terminator_char_d)) {
	
	// if we hit a terminal character, we better not be looking
	// for a nested block end
	//
	if (nest_d && implicit_block_d && implicit_object_d) {
	  
	  // bad parse
	  //
	    //changed by Amir: To fix Segmentation fault error
	    if(fixed_buff_p>buffer_a)
	  *(fixed_buff_p - 1) = terminator_char_d;
	  *fixed_buff_p = NULL_CHAR;
	  return false;
	}

	// always output the terminal character, regardless of token
	//
	//changed by Amir: To fix Segmentation fault error
	if(fixed_buff_p>buffer_a)
	    *(fixed_buff_p - 1) = terminator_char_d;
        	
	// add the last token if last char was not assignment char
	///*
	if (open_index_d && (statement_last_token_d > 0)
	    && (((int64)fixed_buff_p - 2) >= (int64)buffer_a)
	    && (*(fixed_buff_p - 2) != assignment_char_d)) {

	  if (token_count_d > 2) {
	    if (!index_d.addQuick(param_d, token_count_d + 1,
				  statement_last_token_d,
				  current_pos - statement_last_token_d)) {
	      reportIndexError(param_d, token_count_d + 1,
			       statement_last_token_d);
	      return Error::handle(name(), L"preParse - error adding the last token when last char was not assignment character", SofList::ERR, __FILE__, __LINE__, Error::WARNING);
	    }
	  }
	  else {
	    if (!index_d.add(param_d, token_count_d + 1,
			     statement_last_token_d,
			     current_pos - statement_last_token_d)) {
	      reportIndexError(param_d, token_count_d + 1,
			       statement_last_token_d);
	      return Error::handle(name(), L"prePars - error adding the last token when last char was not assignment character", SofList::ERR, __FILE__, __LINE__, Error::WARNING);
	    }
	  }
	}
	
	statement_term_d = current_pos;
	///*
	out_len_a = ((int64)fixed_buff_p - (int64)buffer_a) / sizeof(unichar);
	state_d = NO_GPI;

	// strip the terminal character from the string
	//
	//changed by Amir: To fix Segmentation fault error
	if(fixed_buff_p>buffer_a)
	     *(fixed_buff_p - 1) = NULL_CHAR;
        	
	return true;
      }
      
      // comment operator, go to comment state, no output
      //
      else if (c.eq(comment_char_d)) {
	state_d = COMMENT_OP_GPI;
      }
      
      // more whitespace, stay in this state, output nothing
      //
      else if (c.isSpace()) {
	// do nothing
	//
      }

      // quote character, go to quote state, output nothing
      //
      else if (c.eq(QUOTE_CHAR)) {
	state_d = QUOTE_OP;
      }

      // assignment character, set values, output
      //
      else if (c.eq(assignment_char_d)) {
	
	// possibly bad parse
	//
	if ((statement_asgn_d != -1) || implicit_object_d) {
	  *fixed_buff_p = NULL_CHAR;
		  
	  return false;
	}

	// assign the name of the parameter
	//
	statement_asgn_d = current_pos + 1;
	statement_last_token_d = statement_asgn_d;
	///*
	int64 clen = ((int64)fixed_buff_p - (int64)buffer_a) / sizeof(unichar);

	*fixed_buff_p = *buff_p;

	if (!assignName(buffer_a, clen)) {
	  return Error::handle(name(), L"preParse  - error parsing lvalue", ERR_LVALUE, __FILE__, __LINE__, Error::WARNING);
	}
	
	if ((token_count_d >= token_start_d)&&(token_count_d < token_stop_d)) {
	  *fixed_buff_p = *buff_p;
	  fixed_buff_p++;
	}
	state_d = GPI;
      }

      // literal operator, go to literal op state, no output
      //
      else if (c.eq(LITERAL_CHAR)) {
	state_d = LITERAL_OP;
      }

      // block start character, increment block start, output
      //
      else if (c.eq(blockstart_char_d)) {
	if ((token_count_d >= token_start_d)&&(token_count_d < token_stop_d)) {
	  *fixed_buff_p = *buff_p;
	  fixed_buff_p++;
	}
	block_count_d++;
	state_d = BLOCK_GPI;
      }

      // block stop character (but not in block_gpi state)
      //
      else if (c.eq(blockstop_char_d)) {

	// if we are nested and this is an implicit param, valid parse
	//
	if (nest_d && implicit_block_d && implicit_object_d) {

	    //changed by Amir: To fix Segmentation fault error
	    if(fixed_buff_p>buffer_a)
		  *(fixed_buff_p - 1) = NULL_CHAR;
	    ///*
	  out_len_a = ((int64)fixed_buff_p-(int64)buffer_a-1) / sizeof(unichar);
	  state_d = NO_GPI;

	  if (open_index_d && (statement_last_token_d > 0)) {

	    // add the last token
	    //
	    if (token_count_d > 2) {
	      if (!index_d.addQuick(param_d, token_count_d + 1,
				    statement_last_token_d,
				    current_pos -
				    statement_last_token_d - 1)) {
		reportIndexError(param_d, token_count_d + 1,
				 statement_last_token_d);
		return Error::handle(name(), L"preParse - error adding the last token", SofList::ERR, __FILE__, __LINE__, Error::WARNING);
	      }
	    }
	    else {
	      if (!index_d.add(param_d, token_count_d + 1,
			       statement_last_token_d,
			       current_pos - statement_last_token_d - 1)) {
		reportIndexError(param_d, token_count_d + 1,
				 statement_last_token_d);
		return Error::handle(name(), L"preParse - error adding the last token", SofList::ERR, __FILE__, __LINE__, Error::WARNING);
	      }
	    }
	  }
	  
	  implicit_object_d = false;
	  implicit_block_d = false;
	  state_d = NO_GPI;
	  statement_term_d = current_pos;
	  
	  // valid parse
	  //
	  return true;
	}
	
	// invalid parse
	//
	
	*fixed_buff_p++ = blockstop_char_d;
		
	return false;
      }
      
      // else output character, go back to gpi state
      //
      else {
	
	if ((token_count_d >= token_start_d)&&(token_count_d < token_stop_d)) {
	  *fixed_buff_p = *buff_p;
	  fixed_buff_p++;
	}
	if (c.eq(delimiter_char_d)) {
	  token_count_d++;
	  if (open_index_d && (param_d >= 0) && (statement_last_token_d>=0)) {

	    if (token_count_d > 2) {
	      if (!index_d.addQuick(param_d, token_count_d,
				    statement_last_token_d,
				    current_pos - statement_last_token_d)) {
		reportIndexError(param_d, token_count_d,
				 statement_last_token_d);
		return Error::handle(name(), L"preParse - error adding the token", SofList::ERR, __FILE__, __LINE__, Error::WARNING);
	      }
	    }
	    else {
	      if (!index_d.add(param_d, token_count_d,
			       statement_last_token_d,
			       current_pos - statement_last_token_d)) {
		reportIndexError(param_d, token_count_d,
				 statement_last_token_d);
		return Error::handle(name(), L"preParse - error adding the token", SofList::ERR, __FILE__, __LINE__, Error::WARNING);
	      }
	    }
	    statement_last_token_d = current_pos + 1;
	  } 
	}
	state_d = GPI;
      }
    }
    
    //----------------------------------
    // state: comment with good previous input
    //----------------------------------
    //
    else if (state_d == COMMENT_OP_GPI) {
      
      // go back to gpi lws state on newline, 
      // no output
      //
      if (c.eq(NEWLINE_CHAR)) {
	
	// either go back to GPI or block GPI, depending on block count
	//
	if (block_count_d == 0) {
	  state_d = GPI_LWS;
	}
	else {
	  state_d = BLOCK_GPI_LWS;
	}
      }
      
      // eat comment characters with no output and stay in this state
      //
      else {
	
	// do nothing
	//
      }
    }
    
    //----------------------------------
    // state: block with good previous input
    //----------------------------------
    //
    else if (state_d == BLOCK_GPI) {
      
      // if block stop character, output & decrease count, possibly enter gpi
      //
      if (c.eq(blockstop_char_d)) {
	block_count_d--;
	if ((token_count_d >= token_start_d)&&(token_count_d < token_stop_d)) {
	  *fixed_buff_p = *buff_p;
	  fixed_buff_p++;
	}
	if (block_count_d == 0) {
	  state_d = GPI;
	}
      }
      
      // if block start character, output & increase count
      //
      else if (c.eq(blockstart_char_d)) {
	block_count_d++;
	if ((token_count_d >= token_start_d)&&(token_count_d < token_stop_d)) {
	  *fixed_buff_p = *buff_p;
	  fixed_buff_p++;
	}
      }

      // literal character, go into literal state, no output
      //
      else if (c.eq(LITERAL_CHAR)) {
	state_d = LITERAL_OP;
      }

      // quote character, go into quote state, no output
      //
      else if (c.eq(QUOTE_CHAR)) {
	state_d = QUOTE_OP;
      }

      // whitespace character, go into block_gpi_lws state
      //
      else if (c.isSpace()) {

	if ((token_count_d >= token_start_d)&&(token_count_d < token_stop_d)) {
	  *fixed_buff_p = SPACE_CHAR;
	  fixed_buff_p++;
		}
	state_d = BLOCK_GPI_LWS;
      }

      // comment operator, go into gpi comment state, output space
      //
      else if (c.eq(comment_char_d)) {
	if ((token_count_d >= token_start_d)&&(token_count_d < token_stop_d)) {
	  *fixed_buff_p = SPACE_CHAR;
	  fixed_buff_p++;
		}
	state_d = COMMENT_OP_GPI;
      }

      // else copy character directly, no change in state
      //
      else {
	if ((token_count_d >= token_start_d)&&(token_count_d < token_stop_d)) {
	  *fixed_buff_p = *buff_p;
	  fixed_buff_p++;
	}
      }
    }
    
    //----------------------------------
    // state: block with good previous input, leading white space
    //----------------------------------
    //
    else if (state_d == BLOCK_GPI_LWS) {

      // block stop character, trim last whitespace and decrement count
      //
      if (c.eq(blockstop_char_d)) {

	// trim the last space
	//
	if ((token_count_d >= token_start_d)&&(token_count_d < token_stop_d)) {
	    //Change by Amir : To fix  Segmentation fault error
	    if (fixed_buff_p>buffer_a)
	     *(fixed_buff_p-1) = *buff_p;
	    
	 	}

	
	// decrement block_count. either go into GPI or BLOCK_GPI
	//
	block_count_d--;
	if (block_count_d == 0) {
	  state_d = GPI;
	}
	else {
	  state_d = BLOCK_GPI;
	}
      }

      // if block start character, output & increase count
      //
      else if (c.eq(blockstart_char_d)) {
	block_count_d++;
	if ((token_count_d >= token_start_d)&&(token_count_d < token_stop_d)) {
	  *fixed_buff_p = *buff_p;
	  fixed_buff_p++;
	}
	state_d = BLOCK_GPI;
      }
      
      // more whitespace, stay in this state, output nothing
      //
      else if (c.isSpace()) {
	// do nothing
	//
      }

      // literal character, go into literal state, no output
      //
      else if (c.eq(LITERAL_CHAR)) {
	state_d = LITERAL_OP;
      }

      // quote character, go into quote state, no output
      //
      else if (c.eq(QUOTE_CHAR)) {
	state_d = QUOTE_OP;
      }

      // comment operator, go into gpi comment state, no output
      //
      else if (c.eq(comment_char_d)) {
	state_d = COMMENT_OP_GPI;
      }

      // else copy character directly, go into BLOCK_GPI state
      //
      else {
	if ((token_count_d >= token_start_d)&&(token_count_d < token_stop_d)) {
	  *fixed_buff_p = *buff_p;
	  fixed_buff_p++;
	}
	state_d = BLOCK_GPI;
      }
    }

    //----------------------------------
    // end of state listings, do the things done each state
    //----------------------------------
    
    // increment the input buffer
    //
    buff_p++;
    
    // end of state loop
    //
  }
  
  // there may be some good output, let the user decide
  ///*
  out_len_a = ((int64)fixed_buff_p - (int64)buffer_a) / sizeof(unichar);

  // if we only want some tokens, we drop off in the middle of the parse
  //
  if ((is_token_d) && (state_d != NO_GPI) && (state_d != COMMENT_OP_NO_GPI)) {
    return true;
  }
  
  // the only successful ways to exit is through certain inputs
  // in certain terminal states, if the program exits this loop
  // gracefully. there is something wrong, return 0 length for the buffer
  //
   return false;
}

// method: assignName
//
// arguments:
//  const unichar* buffer: (input) buffer of data from which to extract name
//  int32 clen: (input) number of characters of the string
//
// return: a bool8 value indicating status
//
// assign the parameter at the current position in the state machine
//
bool8 SofParser::assignName(const unichar* buffer_a, int32 clen_a) {

  // check argument
  //
  if (buffer_a == (unichar*)NULL) {
    return Error::handle(name(), L"assignName - buffer of data from which to extract name is null", Error::ARG, __FILE__, __LINE__);
  }

  // check string length
  //
  if (clen_a <= 0) {
    return Error::handle(name(), L"assignName -  number of characters of the string is less that or equal to zero", Error::ARG, __FILE__, __LINE__);
  }
  
  // prepare the name to be assigned
  //
  unichar temp = buffer_a[clen_a];
  const_cast<unichar&>(buffer_a[clen_a]) = (unichar)NULL;
  
  // assign the name to a string
  //
  SysString param(buffer_a);
  
  // restore the buffer
  //
  const_cast<unichar&>(buffer_a[clen_a]) = temp;

  // trim the string
  //
  param.trim();
  
  if (debug_level_d >= Integral::DETAILED) {
    param.debug(L"adding parameter");
  }
  
  // assign the name using the symbol table
  //
  param_d = table_d.add(param);
  
  if (param_d < 0) {
    param.debug(L"param");
    return Error::handle(name(), L"assignName - unable to add the parameter to the symbol table", SofSymbolTable::ERR, __FILE__, __LINE__, Error::WARNING);
  }
  
  // exit gracefully
  //
  return true;
}

// method: reportIndexError
//
// arguments:
//  int32 param: (input) parameter being added
//  int32 tag: (input) tag of parameter being added
//  int32 pos: (input) position of parameter being added
//
// return: logical error status
//
// display a descriptive message about the failed index add
//
bool8 SofParser::reportIndexError(int32 param_a, int32 tag_a, int32 pos_a) {

  SysString param;
  table_d.getSymbol(param, param_a);

  SysString output(L"An error occurred while adding parameter '");
  output.concat(param);
  output.concat(L"'\n");
  Console::put(output);
  
  load_error_d = true;
  
  // exit gracefully
  //
  return true;
}
