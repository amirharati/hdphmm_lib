// file: $isip/class/dstr/Wrapper/WrapperDiagnose.h
// version: $Id: WrapperDiagnose.h 10636 2007-01-26 22:18:09Z tm334 $
//

// make sure definitions are only made once
//
#ifndef ISIP_WRAPPER_DIAGNOSE
#define ISIP_WRAPPER_DIAGNOSE

// isip include files
//
#ifndef ISIP_WRAPPER
#include "Wrapper.h"
#endif

#ifndef ISIP_STACK
#include "Stack.h"
#endif

// WrapperDiagnose: a class that contains the diagnose method of Wrapper class.
//
template<class TObject>
class WrapperDiagnose : public Wrapper<TObject> {

  //---------------------------------------------------------------------------
  //
  // public constants
  //
  //---------------------------------------------------------------------------
public:
  
  // define the class name
  //

  //----------------------------------------
  //
  // i/o related constants
  //
  //----------------------------------------  
  
  //----------------------------------------
  //
  // default values and arguments
  //
  //----------------------------------------

  // default values
  //
    
  // default arguments to methods
  //
  
  //----------------------------------------
  //
  // error codes
  //
  //----------------------------------------  
  
  //---------------------------------------------------------------------------
  //
  // protected data
  //
  //---------------------------------------------------------------------------
protected:

  //---------------------------------------------------------------------------
  //
  // required public methods
  //
  //---------------------------------------------------------------------------
public:

  // methods: name
  //
  static const String& name() {
    return Wrapper<TObject>::name();
  }

  // other static methods
  //
  static bool8 diagnose(Integral::DEBUG debug_level);

  // debug methods
  //  these methods are omitted since this class does not have data
  //  members and operations  
  //
  
  // destructor/constructor(s):
  //  these methods are omitted since this class does not have data
  //  members and operations
  //

  // assign methods:
  //  these methods are omitted since this class does not have data
  //  members and operations
  //

  // operator= methods:
  //  these methods are omitted since this class does not have data
  //  members and operations
  //  

  // i/o methods:
  //  these methods are omitted since this class does not have data
  //  members and operations
  //

  // equality methods:
  //  these methods are omitted since this class does not have data
  //  members and operations
  //

  // memory-management methods:
  //  these methods are omitted since this class does not have data
  //  members and operations
  //
  
  //---------------------------------------------------------------------------
  //
  // class-specific public methods
  //
  //---------------------------------------------------------------------------

  //  these methods are omitted since this class does not have data
  //  members and operations
  //
  
  //---------------------------------------------------------------------------
  //
  // private methods
  //
  //---------------------------------------------------------------------------
private:

}; 

// below are all the methods for the WrapperDiagnose template class
//

//-----------------------------------------------------------------------------
//
// required static methods
//
//-----------------------------------------------------------------------------

// method: diagnose
//
// arguments:
//  Integral::DEBUG level: (input) debug level for diagnostics
//
// return: a bool8 value indicating status
//
template<class TObject>
bool8 WrapperDiagnose<TObject>::diagnose(Integral::DEBUG level_a) {
    
  //---------------------------------------------------------------------------
  //
  // 0. preliminaries
  //
  //---------------------------------------------------------------------------

  // output the class name
  //
  if (level_a > Integral::NONE) {
    SysString output(L"diagnosing class ");
    output.concat(name());
    output.concat(L": ");
    Console::put(output);
    Console::increaseIndention();
  }
  
  //--------------------------------------------------------------------------
  //
  // 1. required public methods
  //
  //--------------------------------------------------------------------------

  // set indentation
  //
  if (level_a > Integral::NONE) {
    Console::put(L"testing required public methods...\n");
    Console::increaseIndention();
  }

  // test destructor/constructor(s):
  //
  Wrapper<SysChar> wchr;
  SysChar c(L'c');
  SysChar d(L'd');
  wchr.assign(c); // assign (from TObject)
  Wrapper<SysChar> wchr2(wchr); // copy constructor (from Wrapper)
  Wrapper<SysChar> wchr3(c); // copy constructor (from TObject)

  if (wchr.SysChar::ne(c) || wchr2.SysChar::ne(c) || wchr3.SysChar::ne(c)) {
    return Error::handle(name(), L"constructors", Error::TEST, __FILE__,
			 __LINE__);
  }

  wchr = d;  // operator = (from TObject)
  wchr2 = wchr; // operator = (from Wrapper)
  
  if (wchr.SysChar::ne(d) || wchr2.SysChar::ne(d)) {
    return Error::handle(name(), L"constructors", Error::TEST, __FILE__,
			 __LINE__);
  }

  // test that the scope operator works
  //
  Wrapper<SysString> def_wrapper;
  def_wrapper.SysString::assign(Wrapper<TObject>::CLASS_NAME);
  if (def_wrapper.SysString::ne(Wrapper<TObject>::CLASS_NAME)) {
    return Error::handle(name(), L"diagnose", Error::TEST, __FILE__, __LINE__);
  }

  // test memory-management methods:
  //  set the memory to a strange block size so we can hopefully catch any
  //  frame overrun errors
  //
  Wrapper<TObject>::setGrowSize((int32)31);
  
  // loop for a large number of times creating and deleting a large number
  // of wrappers at each loop.
  //
  for (int32 j = 1; j <= 20; j++) {
    Wrapper<TObject>** wrappers = new Wrapper<TObject>*[j * 53];
    
    // create the wrappers
    //
    for (int32 i = 0; i < j * 53; i++) {
      wrappers[i] = new Wrapper<TObject>;
    }
    
    // delete wrappers
    //
    for (int32 i = (j * 53) - 1; i >= 0; i--) {
      delete wrappers[i];
    }
    
    delete [] wrappers;
  }
  
  // perform the same test using the new[] and delete [] operators
  //
  for (int32 j = 1; j <= 20; j++) {
    
    // allocate a large number of wrappers
    //
    Wrapper<TObject>* wrappers = new Wrapper<TObject>[j * 53];
    
    // clean up memory
    //
    delete [] wrappers;
  }

  // reset indentation
  //
  if (level_a > Integral::NONE) {
    Console::decreaseIndention();
  }

  //---------------------------------------------------------------------------
  //
  // 2. print completion message
  //
  //---------------------------------------------------------------------------

  // reset indentation
  //
  if (level_a > Integral::NONE) {
    Console::decreaseIndention();
  }
  
  if (level_a > Integral::NONE) {
    SysString output(L"diagnostics passed for class ");
    output.concat(name());
    output.concat(L"\n");
    Console::put(output);
  }  

  // exit gracefully
  //
  return true;
}

// end of include file
//
#endif
