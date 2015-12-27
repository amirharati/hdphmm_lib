// file: $isip/class/system/Console/Console.h
// version: $Id: Console.h 7929 2002-03-18 19:31:49Z alphonso $
//

// make sure definitions are only made once
//
#ifndef ISIP_CONSOLE
#define ISIP_CONSOLE

// isip include files
//
#ifndef ISIP_FILE
#include <File.h>
#endif

// Console: a class that controls messages (errors and debugging information)
// which programmers might want to send to a console such as stdout.
//
class Console : public File {

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
  // other important constants
  //
  //---------------------------------------

  // upper limit on the stack of console file pointers
  //
  static const int32 MAX_STACK_SIZE = 32;
  
  // the number of characters used for automatic line wrapping
  //
  static const int32 NO_WRAP = -1;
  static const int32 DEF_LINE_WRAP = NO_WRAP;
  
  //----------------------------------------
  //
  // default values and arguments
  //
  //----------------------------------------  

  // default arguments to methods
  //
  static const STREAM DEF_STREAM = File::OUT;
  
  //----------------------------------------
  //
  // error codes
  //
  //----------------------------------------  
  
  static const int32 ERR = 1400;
  static const int32 ERR_OPENMAX = 1401;

  //---------------------------------------------------------------------------
  //
  // protected data
  //
  //---------------------------------------------------------------------------
protected:

  // this is the file used as the current console
  //
  static File cons_d;
  
  // stack of other consoles
  //
  static File stack_d[];
  static int32 size_d;
  static int32 stack_size_d;

  // declare a variable for initialization of line-wrapping
  //
  static bool8 initialized_wrap_d;
  
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
  static bool8 debug(const unichar* msg);

  // destructor/constructor(s) are private
  //

  // assign methods:
  //  assign methods are omitted because Console objects
  //  can not be instantiated
  //

  // operator= methods:
  //  operator= are omitted because Console objects
  //  can not be instantiated
  //
  
  // i/o methods:
  //  these methods are omitted because Console objects
  //  can not be instantiated
  //

  // equality methods:
  //  these methods are omitted because Console objects
  //  can not be instantiated
  //

  // memory management methods:
  //  these methods are omitted because Console objects
  //  can not be instantiated
  //

  //---------------------------------------------------------------------------
  //
  // class-specific public methods:
  //  open and close methods
  //
  //---------------------------------------------------------------------------

  // open methods:
  //  these methods automatically push the old console down the stack
  //
  static bool8 open(const unichar* filename, MODE mode = File::APPEND_ONLY);
  static bool8 open(const SysString& filename,
		      MODE mode = File::APPEND_ONLY);
  static bool8 open(STREAM stream = DEF_STREAM);
  
  // close methods:
  //  these methods close one or all consoles in the stack
  //
  static bool8 close();
  static bool8 closeStack();
  
  //---------------------------------------------------------------------------
  //
  // class-specific public methods:
  //  message display methods
  //
  //---------------------------------------------------------------------------
  
  // put methods:
  //  these methods display a message to the console
  //
  static bool8 put(const unichar* str);
  static bool8 put(const SysString& str);

  // put methods:
  //  these methods display a message to the console fully disabling
  //  line wrapping
  //
  static bool8 putNoWrap(const unichar* str);
  static bool8 putNoWrap(const SysString& str);
  
  // broadcast methods:
  //  these methods display a message to ALL open consoles under the
  //  control of the current running application
  //
  static bool8 broadcast(const unichar* str);
  static bool8 broadcast(const SysString& str);

  //---------------------------------------------------------------------------
  //
  // class-specific public methods:
  //  formatting methods
  //
  //---------------------------------------------------------------------------

  // method: increaseIndention
  //
  static bool8 increaseIndention() {
    return cons_d.increaseIndention();
  }
  
  // method: decreaseIndention
  //
  static bool8 decreaseIndention() {
    return cons_d.decreaseIndention();
  }

  // method: setLineWrap
  //
  static bool8 setLineWrap(int32 num_cols) {
    initialized_wrap_d = true;
    return cons_d.setLineWrap(num_cols);
  }

  // method: getLineLength
  //
  static int32 getLineLength() {
    return cons_d.getLineLength();
  }

  // method: getLineWrap
  //
  static int32 getLineWrap() {
    if ((size_d == 0) && (!initialized_wrap_d)) {
      cons_d.setLineWrap(DEF_LINE_WRAP);
      initialized_wrap_d = true;
    }
    return cons_d.getLineWrap();
  }
  
  //---------------------------------------------------------------------------
  //
  // private methods
  //
  //---------------------------------------------------------------------------
private:
  
  // destructor/constructor(s):
  //  these methods are private so the class cannot be instantiated.
  //
  ~Console();
  Console();
  Console(const Console& arg);

  // stack operation methods
  //
  static bool8 push(File& arg);
  static bool8 pop(File& arg);
};

// end of include file
//
#endif
