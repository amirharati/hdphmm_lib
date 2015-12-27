// file: $isip/class/dstr/DstrBase/DstrBase.h
// version: $Id: DstrBase.h 6110 2000-12-28 22:31:11Z duncan $
//

// make sure definitions are only made once:
//
#ifndef ISIP_DSTR_BASE
#define ISIP_DSTR_BASE

// isip include files
//
#ifndef ISIP_STRING
#include <String.h>
#endif

#ifndef ISIP_NAME_MAP
#include <NameMap.h>
#endif

// DstrBase: this class contains some constants, enums and methods
// common to all data structure classes.
//
//
class DstrBase {
  
  //---------------------------------------------------------------------------
  //
  // public constants
  //
  //---------------------------------------------------------------------------
public:

  //----------------------------------------
  //
  // other important constants
  //
  //----------------------------------------
  
  // enumerate the sort algorithms
  //
  enum SORT_ALGO { RAND_QUICK = 0, MERGE, QUICK, INSERTION,
		   DEF_SORT_ALGO = RAND_QUICK };

  // enumerate the linked lists
  //
  enum LIST_TYPE { SINGLE = 0, DOUBLE, DEF_LIST_TYPE = DOUBLE };
  
  // enumerate the allocation modes:
  //  is item memory allocated by the data structure class or must the
  //  user allocate memory before passing it in? in SYSTEM mode (the
  //  default), the classes handle allocation and deletion of the
  //  objects. when the user places an object in the class, a copy of
  //  the object is made and inserted into the node via local memory
  //  allocation - note that this requires a call to the copy
  //  constructor so it is not a fast operation. when the object is
  //  removed the object is automatically deleted.
  //
  //  in user mode, it is the user's responsibility for handling
  //  memory. the data structure classes will only handle pointers, so
  //  the user must ensure that all memory is allocated before placing
  //  objects onto the structure, no memory is deleted while it is
  //  still referenced by the classes, and all memory is deleted
  //  exactly once.
  //
  enum ALLOCATION { SYSTEM = 0, USER, DEF_ALLOCATION = SYSTEM };

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

  static const int32 ERR = 42000;
  
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
  
  // name and diagnose methods are omitted
  //
  
  // method: destructor
  //
  ~DstrBase() {}
  
  // method: default constructor
  //
  DstrBase() {}

  // other constructor(s):
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
  // class-specific public methods:
  //  extensions to required methods
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

// end of include file
// 
#endif
