// file: $isip/class/io/SofParser/SofParser.h
// version: $Id: SofParser.h 6809 2001-04-24 16:33:22Z duncan $
//

// make sure definitions are only made once
//
#ifndef ISIP_SOF_PARSER
#define ISIP_SOF_PARSER

// isip include files
//
#ifndef ISIP_SOF
#include <Sof.h>
#endif

#ifndef ISIP_CONSOLE
#include <Console.h>
#endif

// SofParser: parse name=value pairs from ASCII Sof files. it is used to
// parse ASCII Sof files. 
//
class SofParser {

  //---------------------------------------------------------------------------
  //
  // public constants
  //
  //---------------------------------------------------------------------------
public:

  // define the class name
  //
  static const SysString CLASS_NAME;
  
  //----------------------------------------
  //
  // other important constants
  //
  //----------------------------------------  

  // buffer size used for the preparser.
  //
  static const int32 MAX_BUFFER_SIZE = SysString::MAX_LENGTH - 1;

  // define implicit parameter constants
  //
  static const int32 IMPLICIT_NAME = SofSymbolTable::NO_SYMB - 1;
  static const SysString IMPLICIT_PARAM;
  
  //----------------------------------------
  //
  // state machine related constants
  //
  //----------------------------------------  
  
  // define the states:
  //    GPI stands for good previous input
  //    LWS stands for last character whitespace
  //
  enum STATE { NO_GPI = 0, COMMENT_OP_NO_GPI, LITERAL_OP, GPI, QUOTE_OP,
	       LITERAL_OP_IN_QUOTE, GPI_LWS, COMMENT_OP_GPI,
	       TERMINAL_TRIM_LWS, BLOCK_GPI, BLOCK_GPI_LWS,
	       DEF_STATE = NO_GPI };

  // names for states in state machine
  //
  static const SysString STATE_NO_GPI;
  static const SysString STATE_COMMENT_OP_NO_GPI;
  static const SysString STATE_LITERAL_OP;
  static const SysString STATE_GPI;
  static const SysString STATE_QUOTE_OP;
  static const SysString STATE_LITERAL_OP_IN_QUOTE;
  static const SysString STATE_GPI_LWS;
  static const SysString STATE_COMMENT_OP_GPI;
  static const SysString STATE_TERMINAL_TRIM_LWS;
  static const SysString STATE_BLOCK_GPI;
  static const SysString STATE_BLOCK_GPI_LWS;
  
  // special characters to the state machine
  //
  static const unichar LITERAL_CHAR = L'\\';
  static const unichar QUOTE_CHAR = L'"';
  static const unichar NEWLINE_CHAR = L'\n';
  static const unichar NULL_CHAR = L'\0';
  static const unichar SPACE_CHAR = L' ';
  
  //----------------------------------------
  //
  // default values and arguments
  //
  //----------------------------------------  

  // define the default value(s) of the class data
  //
  static const unichar DEF_TERMINATOR_CHAR = L';';
  static const unichar DEF_ASSIGNMENT_CHAR = L'=';
  static const unichar DEF_COMMENT_CHAR = L'#';
  static const unichar DEF_BLOCKSTART_CHAR = L'{';
  static const unichar DEF_BLOCKSTOP_CHAR = L'}';
  static const unichar DEF_DELIMITER_CHAR = L',';
  
  // default arguments to methods
  //
  static const int32 NO_SYMB = -1;
  static const int32 ALL_TOKENS = -1;
  static const int32 FULL_OBJECT = -1;
  static const int32 BASE_TAG = 0;
  
  //----------------------------------------
  //
  // error codes
  //
  //----------------------------------------  

  // class general error
  //
  static const int32 ERR	= 10300;
  
  // error codes for parsing
  //
  static const int32 ERR_PARSE = 10302;
  static const int32 ERR_PASTAT = 10303;
  static const int32 ERR_LVALUE = 10304;
  static const int32 ERR_RVALUE = 10305;
  
  //---------------------------------------------------------------------------
  //
  // protected data
  //
  //---------------------------------------------------------------------------
protected:

  // storage for the parameters and values
  //
  SofSymbolTable table_d;
  SofList index_d;

  // keep track of what parameters are accessed
  //
  bool8* used_d;
  int32 used_size_d;
  
  // special characters
  //
  SysChar terminator_char_d;
  SysChar assignment_char_d;
  SysChar comment_char_d;
  SysChar blockstart_char_d;
  SysChar blockstop_char_d;
  SysChar delimiter_char_d;

  // states and variables in the preParse FSM
  //
  STATE state_d;
  int32 param_d;			// symbol table entry for current param
  int32 block_count_d;		// block level
  int32 token_count_d;		// token # for current param
  int32 token_start_d;
  int32 token_stop_d;
  
  // positions within the current statement
  //
  int32 statement_asgn_d;
  int32 statement_term_d;
  int32 statement_last_token_d;

  // the limits of our file space
  //
  int32 base_position_d;
  int32 full_size_d;
  
  // a few flags for the parser
  //
  bool8 open_index_d;
  bool8 nest_d;
  bool8 is_token_d;

  // flags for implicit parameters:
  //  since we sometimes have parameters without explicit parameters,
  //  like each vector in a matrix object, this facility exists to trick
  //  the parser into thinking it has already seen the assignment operator
  //
  bool8 implicit_object_d;
  bool8 implicit_block_d;

  // flag to indicate if there was a load error
  //
  bool8 load_error_d;
  
  // debugging parameters
  //
  Integral::DEBUG debug_level_d;
  
  //---------------------------------------------------------------------------
  //
  // required public methods
  //
  //---------------------------------------------------------------------------
public:

  // method: name
  //
  static const SysString& name() {
    return CLASS_NAME;
  }

  // other static methods
  //
  static bool8 diagnose(Integral::DEBUG debug_level);

  // method: setDebug
  //
  bool8 setDebug(Integral::DEBUG level) {
    debug_level_d = level;
    return true;
  }
  
  // other debug methods
  //
  bool8 debug(const unichar* msg) const;
  
  // destructor/constructor(s)
  //
  ~SofParser();
  SofParser();
  SofParser(const SofParser& arg);
  
  // assign methods:
  //  these methods are omitted because they are not useful for
  //  SofParser objects
  //
  
  // operator= methods:
  //  these methods are omitted because they are not useful for
  //  SofParser objects
  //
  
  // i/o methods:
  //  these methods are omitted because SofParser can not write itself
  //  to an sof file
  //
  
  // equality methods:
  //  these methods are omitted because they are not useful for
  //  SofParser objects
  //
  
  // memory management methods:
  //  new and delete are omitted because memory for SofParser objects is not
  //  managed by the MemoryManager class. the clear method is omitted so the
  //  user is forced to use the destructor for handling the SofParser
  //

  //---------------------------------------------------------------------------
  //
  // class-specific public methods
  //  extensions to the required public methods
  //
  //---------------------------------------------------------------------------
  
  // constructors
  //
  SofParser(const SysChar terminator, const SysChar assignment,
	    const SysChar comment, const SysChar block_start,
	    const SysChar block_stop, const SysChar delim);
  
  // memory size methods
  //
  int32 memSize();

  //---------------------------------------------------------------------------
  //
  // class-specific public methods
  //  parser operation methods
  //
  //---------------------------------------------------------------------------
  
  // load methods:
  //  these methods parse through and build index from current file space
  //
  bool8 load(Sof& sof_a, int32 size = FULL_OBJECT);
  
  // read methods
  //
  bool8 read(SysString& value, Sof& sof, int32 size = FULL_OBJECT);
  
  // getEntry methods:
  //  these  methods position the Sof file and return the size of the
  //  parameter. after calling this we are ready to read. return
  //  negative size if the parameter is not present. the second methods
  //  allows partial io.
  //
  int32 getEntry(Sof& sof, const SysString& param, int32 tag = BASE_TAG);
  int32 getEntry(Sof& sof, const SysString& param, int32 token_offset,
		int32 num_tokens);
  
  // method: countParams
  //
  int32 countParams() {
    return table_d.getCount();             // return the number of parameters
  }
  bool8 checkParams(const SysString* param_list, int32 num);
  bool8 checkParams(Sof& sof);
  int32 getParams(SysString* param_list, int32 max_num);

  // method: implicitPname
  //  set the implicit parameters name, implicit parameters always have
  //  the same parameter name
  //
  static const SysString& implicitPname() {
    return IMPLICIT_PARAM;
  }

  // method: setImplicitParam
  //  these methods are to interface for data-only objects (sometimes used in
  //  nested data types, like a matrix).
  //
  bool8 setImplicitParam() {
    implicit_object_d = true;
    param_d = table_d.add(IMPLICIT_PARAM);
    statement_asgn_d = 0;
    return true;
  }

  // method: setNest
  //  this allows a parameter to dig past brackets in the current object. it
  //  will always be used in conjunction with the setImplicitParam() method
  //
  bool8 setNest() {
    nest_d = true;
    return true;
  }
  
  // method: isPresent
  //  checks if a parameter name is present in the symbol table
  //
  bool8 isPresent(const Sof& sof, const SysString& param_name) {
    if (sof.isBinary()) {
      return true;              // for binary case, always return true
    }
    
    return (table_d.getIndex(param_name) != SofSymbolTable::NO_SYMB);
  }
 
  // method: countTokens
  //  count the number of tokens in our file space
  //
  int32 countTokens(const SysString& param) {
    int32 count = index_d.getCount(table_d.getIndex(param));
    if (count > 0) {
      count--;                     // the zeroth entry is the whole parameter
    }
    return count;
  }
  
  // reset methods
  //
  bool8 reset();
  
  //---------------------------------------------------------------------------
  //
  // private methods
  //
  //---------------------------------------------------------------------------
private:

  // preParse methods:
  //  this is an FSM which cleans the format of the input text for easier
  //  parsing. it destructively changes the input buffer
  //
  bool8 preParse(int32& olen, unichar* buffer, int32 ilen, int32 offset);
  
  // assignName methods:
  //  this method assigns the parameter at the current position in the
  //  state machine
  //
  bool8 assignName(const unichar* buffer, int32 clen);
  
  // get state name methods
  //
  bool8 setString(SysString& str, STATE state) const;

  // method to assist in error reporting
  //
  bool8 reportIndexError(int32 param, int32 tag, int32 pos);
};

// end of include file
// 
#endif
