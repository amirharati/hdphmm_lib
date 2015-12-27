// file: $isip/class/io/SofSymbolTable/SofSymbolTable.h
// version: $Id: SofSymbolTable.h 4788 2000-09-15 19:14:22Z zhao $
//

// make sure definitions are only made once
//
#ifndef ISIP_SOF_SYMBOL_TABLE
#define ISIP_SOF_SYMBOL_TABLE

// isip include files
//
#ifndef ISIP_SYS_STRING
#include <SysString.h>
#endif

// SofSymbolTable: a class to be used under Sof. the symbol table is an
//  array of SysStrings which are the symbol names. it is used to
//  keep track of a symbol table for Sof's use. 
//
class SofSymbolTable {
  
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
  
  // maximum length of a symbol
  //
  static const int32 MAX_SYM_LENGTH = 64;

  // the size to grow the symbol array by each time
  //
  static const int32 GROW_SIZE = 256;
  
  // invalid characters within symbol names
  //
  static const SysString INVALID_CHARS;

  // constants for efficiency measure
  //
  static const int32 MAX_WASTED_SPACE = 1024;
  
  //----------------------------------------
  //
  // default values and arguments
  //
  //----------------------------------------  
  
  // dummy index for a non-exist symbol in the table
  //
  static const int32 NO_SYMB = -1;

  //----------------------------------------
  //
  // error codes
  //
  //----------------------------------------  

  // class general error
  //
  static const int32 ERR = 10200;
  
  // error code indicating failure to add a symbol into the symbol table
  //
  static const int32 ERR_ADD = 10201;
  
  // error code indicating failure to find a symbol in the symbol table
  //
  static const int32 ERR_NOTFND = 10202;

  // error code indicating no transform vector
  //
  static const int32 ERR_NOVECT = 10203;
  
  // error code indicating symbol index out of range 
  //
  static const int32 ERR_SYMB = 10204;
  
  //---------------------------------------------------------------------------
  //
  // protected data
  //
  //---------------------------------------------------------------------------
protected:
  
  // an array of string symbols
  //
  SysString* table_d;
  
  // number of references to symbols
  //
  int32* ref_count_d;			
  
  // current length of the symbol table (some entries may be empty)
  //
  int32 table_size_d;
  
  // number of non-empty entries in the symbol table
  //
  int32 num_syms_d;
  
  // capacity of the symbol table, it can be grown dynamically
  //
  int32 table_capacity_d;
  
  // parameters used to transform between tables
  //
  int32* transform_d;		
  int32 transform_size_d;
  
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
  ~SofSymbolTable();
  SofSymbolTable();
  SofSymbolTable(const SofSymbolTable& arg);

  // assign methods
  //
  bool8 assign(const SofSymbolTable& arg);
  
  // method: operator=
  //
  SofSymbolTable& operator=(const SofSymbolTable& arg) {
    if (!assign(arg)) {
      Error::handle(name(), L"operator=", Error::ARG,
                    __FILE__, __LINE__);
    }      
    return *this;
  }
  
  // i/o methods:
  //  these methods are omitted because SofSymbolTable can not write itself
  //  to an sof file
  //

  // equality methods:
  //  these methods are omitted because they are not useful for
  //  SofSymbolTable objects
  //

  // memory management methods:
  //  new and delete are omitted because memory for SofSymbolTable objects is
  //  not managed by the MemoryManager class. the clear method does not
  //  accept FREE mode, so the user is forced to use the destructor for
  //  handling the SofSymbolTable. Sof files could easily be corrupted
  //  if the memory of SofSymbolTable is improperly freed.
  //
  bool8 clear(Integral::CMODE ctype_a = Integral::DEF_CMODE);

  //---------------------------------------------------------------------------
  //
  // class-specific public methods:
  //  extensions to the required public methods
  //
  //---------------------------------------------------------------------------

  // assign methods
  //
  bool8 assignCompact(const SofSymbolTable& arg);
  
  // memory size methods
  //
  int32 memSize() const;

  //---------------------------------------------------------------------------
  //
  // class-specific public methods:
  //  symbol table manipulation methods
  //
  //---------------------------------------------------------------------------
  
  // symbol retrieval methods
  //
  int32 getIndex(const SysString& name) const;
  bool8 getSymbol(SysString& name, int32 num) const;
  int32 getRefCount(const SysString& name) const;
  int32 getRefCount(int32 index) const;

  // method: getCount
  //
  int32 getCount() const {
    return num_syms_d;
  }
  
  // symbol entry manipulation methods
  //
  int32 add(const SysString& name);
  bool8 add(int32 index, int32 refs, const SysString& name);
  
  bool8 remove(const SysString& name);
  bool8 remove(int32 index);

  // checkName methods:
  //  this method checks if a symbol name is valid
  //
  bool8 checkName(const SysString& name) const;

  // method: isEfficient
  //  this method checks if the symbol table is used efficiently by checking
  //  the number of unused slots 
  //
  bool8 isEfficient() const {
    
    // if few spaces are wasted, it is efficient
    //
    return ((table_size_d - num_syms_d) < MAX_WASTED_SPACE);    
  }

  //---------------------------------------------------------------------------
  //
  // class-specific public methods:
  //  symbol table conversion methods
  //
  //---------------------------------------------------------------------------

  // convert methods:
  //  these methods get the index of a symbol in this table given its index
  //  in the old table
  //
  int32 convert(const SofSymbolTable& old, int32 index) const;
  int32 convert(int32 index) const;

  // transform methods:
  //  these methods are for manipulating the transform vector between the
  //  old symbol table and this symbol table
  //
  bool8 transformInit(const SofSymbolTable& old);
  bool8 transformDelete();

  //---------------------------------------------------------------------------
  //
  // private methods
  //
  //---------------------------------------------------------------------------
private:

  // add new symbol methods
  //
  int32 addNew(const SysString& name);
  
  // grow table capacity methods
  //
  bool8 growCapacity();
  
  // release memory methods
  //
  bool8 freeMem();
};

// end of include file
// 
#endif
