// file: $isip/class/system/Error/Error.h
// version: $Id: Error.h 10675 2009-07-21 01:13:30Z tm334 $
//
// (1) AH (07/27/2010): I have  deleted  volatile   qualifier from exit definitin
//                      to fix a warning in gcc-4.4.4 with  -Wextra
//

// make sure definitions are only made once
//
#ifndef ISIP_ERROR
#define ISIP_ERROR

// isip include files
//
#ifndef ISIP_INTEGRAL
#include <Integral.h>
#endif

// macro for checks which can be optimized out
//
#ifdef ISIP_OPTIMIZE
#define ISIP_FULL_CHECK(s)
#else
#define ISIP_FULL_CHECK(s) s
#endif

// forward class definitions
//
class SysString;

// Error: define a class that is used for error handling. everything
// in this class is static, so there is only one way to handle errors
// per program. this class will never be instantiated.
//
class Error {
  
  //---------------------------------------------------------------------------
  //
  // public constants
  //
  //---------------------------------------------------------------------------
public:
  
  // define the class name
  //
  static const SysString CLASS_NAME;
  
  //---------------------------------------
  //
  // error message related constants
  //
  //---------------------------------------
    
  // format of the error codes
  //
  static const SysString CODE_FMT;

  // default value for the extras string that users can pass in
  // to handle()
  //
  static const SysString DEF_EXTRAS;

  // format and components of error messages
  //
  static const long ERROR_MESSAGE_SIZE = 256;
  static const SysString ERROR_MESSAGE_00;
  static const SysString ERROR_MESSAGE_01;
  static const SysString ERROR_MESSAGE_02;
  static const SysString ERROR_MESSAGE_03;
  static const SysString ERROR_MESSAGE_04;
  static const SysString ERROR_MESSAGE_05;
  static const SysString ERROR_MESSAGE_99;

  // error message for the undefined error code
  //
  static const SysString UNDEFINED_MESSAGE;
  
  // declare exit levels:
  //  these levels affect the behavior of error handling
  //  NONE - never exit; ERROR - exit on errors;
  //  WARNING - always exit, even if it is only a warning
  //
  enum EXIT { NONE = 0, ERROR, WARNING, DEF_EXIT = ERROR };

  //---------------------------------------
  //
  // error codes
  //
  //---------------------------------------
  
  // file errors
  //
  static const int32 FILE_NOTFND		=	0;
  static const int32 IO			=	1;
  static const int32 PERMISSION_DENIED	=	2;
  static const int32 SEEK		=	3;
  static const int32 WRITE_CLOSED	=	4;
  static const int32 READ_CLOSED		=	5;
  static const int32 WRITE		=	6;
  static const int32 READ		=	7;
  static const int32 MOD_READONLY	=	8;
  static const int32 FILE_LOCK_READONLY	=	11;
  static const int32 FILE_LOCK		=	12;
  static const int32 FILE_UNLOCK		=	13;
  static const int32 FILE_REOPEN		=	14;
  static const int32 FILENAME_EXPAND	=	15;  
  
  // coding errors
  //
  static const int32 ENV_VAR		=	21;
  static const int32 SYS_CALL		=	24;
  static const int32 TEST		=	25;
  static const int32 INTERNAL_DATA	=	41;
  static const int32 BAD_CSTR		=	45;
  static const int32 DESTRUCTOR		=	50;
  static const int32 UNK_CMODE		=	51;
  static const int32 ARG			=	52;
  static const int32 RELEASE		=	53;
  static const int32 MEM			=	54;
  static const int32 NOMEM		=	55;
  static const int32 MEM_OFLOW		=	56;
  static const int32 STATIC_CLASS	=	57;
  static const int32 TEMPLATE_TYPE	=	58;
  static const int32 ENUM		=	59;
  static const int32 NULL_ARG            =       60;
  static const int32 STACK_EXCEEDED      =	61;
  static const int32 DATATYPE_RANGE	=	62;
  static const int32 BOUNDS		=	65;
  static const int32 NOT_IMPLEM		=	66;
  static const int32 ALLOC_MODE          =       75;
  static const int32 VIRTUAL_PTR         =       80;
  
  // utility errors
  //
  static const int32 NO_PARAM_FILE	=	500;
  static const int32 NO_INPUT_FILE	=	501;
  
  // Error class general errors (only here for uniformity)
  //
  static const int32 ERR = 1800;
  
  //---------------------------------------------------------------------------
  //
  // protected data
  //
  //---------------------------------------------------------------------------
protected:

  // static flags to control behaviors upon exit
  //
  static bool8 initialized_d;
  static EXIT exit_level_d;
  
  // declare a static debug level
  //
  static Integral::DEBUG debug_level_d;
  
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
  static bool8 setDebug(Integral::DEBUG level) {
    debug_level_d = level;
    return true;
  }

  // other debug methods
  //
  static bool8 debug(const unichar* message);
  
  // destructor/constructor(s) are private
  //

  // assign methods:
  //  these methods are omitted because Error objects
  //  can not be instantiated
  //

  // operator= methods:
  //  these methods are omitted because Error objects
  //  can not be instantiated
  //

  // i/o methods:
  //  these methods are omitted because Error objects
  //  can not be instantiated
  //

  // equality methods:
  //  these methods are omitted because Error objects
  //  can not be instantiated
  //

  // memory management methods:
  //  these methods are omitted because Error objects
  //  can not be instantiated
  //

  //---------------------------------------------------------------------------
  //
  // class-specific public methods
  //  error handler methods
  //
  //---------------------------------------------------------------------------
  
  // method: set
  //  the exit_level affects the behavior or error handling
  //
  static bool8 set(EXIT exit_level) {
    if (!initialized_d) {
      exit_level_d = exit_level;
    }
    return (initialized_d = true);
  }

  // method: reset
  //  the level needs to be reset before being set again
  //
  static bool8 reset() {
      exit_level_d = DEF_EXIT;
      return (!(initialized_d = false));
  }

  // error handler methods
  //
  static bool8 handle(const SysString& cname, const unichar* mname,
			int32 ecode, const char* file, int32 line,
			EXIT level = DEF_EXIT,
			const SysString& extras = DEF_EXTRAS);
  
  static bool8 handle(const SysString& cname, const SysString& mname,
			int32 ecode, const char* file, int32 line,
			EXIT level = DEF_EXIT,
			const SysString& extras = DEF_EXTRAS);
  
  //---------------------------------------------------------------------------
  //
  // class-specific public methods
  //  exit related methods
  //
  //---------------------------------------------------------------------------
  
  // Sof closing methods:
  //  these methods setup cleanup functions called upon exit.
  //  they are part of an implementation that causes any fatal
  //  error from anywhere in the code structure (high or low) to close
  //  all open Sof files. users should never use these methods directly.
  //
  static bool8 setSofPointer(bool8 (*method)(void));
  static bool8 closeSof();
  
  // exit methods
  //
  static bool8 isExiting();
  static void exit();
  
  //---------------------------------------------------------------------------
  //
  // private methods
  //
  //---------------------------------------------------------------------------
private:

  // destructor/constructor(s):
  //  these methods are private so the class cannot be instantiated
  //
  ~Error();
  Error();
  Error(const Error& arg);
  
  // error message lookup methods
  //
  static bool8 getMessage(SysString& msg, int32  code);
};

// end of include file
// 
#endif
