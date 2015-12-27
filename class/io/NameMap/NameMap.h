// file: $isip/class/io/NameMap/NameMap.h
// version: $Id: NameMap.h 10640 2007-01-27 02:36:04Z tm334 $
//

// make sure definitions are only made once
//
#ifndef ISIP_NAME_MAP
#define ISIP_NAME_MAP

// isip include files
//
#ifndef ISIP_CHECKSUM
#include <Checksum.h>
#endif

#ifndef ISIP_SOF_PARSER
#include <SofParser.h>
#endif

// NameMap: a mapping from integers to SysString objects. this class is
// used to give SysString names to enumerated values. this class limits
// the size of the list to be less than an unsigned short int (65536).
//
class NameMap {

  //---------------------------------------------------------------------------
  //
  // public constants
  //
  //---------------------------------------------------------------------------
public:
  
  // define the class name
  //
  static const SysString CLASS_NAME;

  // define constraints on the size of the map
  //
  static const uint32 MAX_LENGTH = ((uint32)1 << 16);
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
  static const unichar DELIM_CHR = L',';
  
  //----------------------------------------
  //
  // declare some globally useful NameMaps
  //
  //----------------------------------------  

  // a NameMap for colors (Integral::COLOR)
  //
  static const NameMap COLOR_MAP;

  // a NameMap for allocation modes (DstrBase::ALLOCATION)
  //
  static const NameMap ALLOCATION_MAP;

  //----------------------------------------
  //
  // error codes
  //
  //----------------------------------------  
  
  static const int32 ERR = 10400;
  static const int32 ERR_RANGE = 10401;
  static const int32 ERR_NOTFND = 10402;
  static const int32 ERR_CHKSUM = 10403;
  
  //---------------------------------------------------------------------------
  //
  // protected data
  //
  //---------------------------------------------------------------------------
protected:

  // hold all names as elements in a vector of SysStrings.
  // the forward lookup will be very fast, backwards will be slower.
  //
  SysString* names_d;
  int32 size_d;
  
  // use a checksum to represent the name map when writing an index
  //
  uint16 checksum_d;

  // static checksum object
  //
  static Checksum cksm_d;
  
  // the debug level
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
  static bool8 setDebug(Integral::DEBUG debug_level) {
    debug_level_d = debug_level;
    return true;
  }

  // other debug methods
  //  
  bool8 debug(const unichar* message) const;
  
  // constructor(s)/destructor
  //
  ~NameMap();

  // the default and copy constructors are private since you must
  // supply a value string when you construct the object. 
  //

  // the assign and operator= methods are ommitted since they are not
  // useful for this object
  //

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
  //  not managed by the MemoryManager class. the clear method is ommited
  //  since it is not useful for the class.

  //---------------------------------------------------------------------------
  //
  // class-specific public methods:
  //  extensions to required methods
  //
  //---------------------------------------------------------------------------

  // method: constructor
  //
  NameMap(const SysString& arg, const unichar delim = DELIM_CHR) {
    assign(arg, delim);
  }

  // method: constructor
  //
  NameMap(const unichar* arg, const unichar delim = DELIM_CHR) {
    SysString str(arg);
    assign(str, delim);
  }
  
  //---------------------------------------------------------------------------
  //
  // class-specific public methods:
  //  get methods
  //
  //---------------------------------------------------------------------------

  // get methods:
  //  getName returns the name corresponding to the specified index
  //  getIndex returns the index cooresponding to the specified name
  //
  const SysString& getName(uint16  index) const;
  int32 getIndex(const SysString& name) const;

  // method: operator()
  //  (SysString&) conversion operator
  //
  const SysString& operator()(ushort index) const {
    return getName(index);
  }

  // method: operator()
  //  (ushort) conversion operator
  //
  int32 operator()(const SysString& name) const {
    return getIndex(name);
  }

  //---------------------------------------------------------------------------
  //
  // class-specific public methods:
  //  special i/o methods (used inside the i/o methods of other classes)
  //
  //---------------------------------------------------------------------------

  // determine the sofSize of an element in this NameMap
  //
  int32 elementSofSize() const;
  
  // direct access to Sof files
  //
  bool8 readElementData(int32& value, Sof& sof, const SysString& pname,
			  int32 size = SofParser::FULL_OBJECT,
			  bool8 param = true,
			  bool8 nested = false) const;

  bool8 writeElementData(Sof& sof, const SysString& pname,
			   ushort index) const;

  // method to display all possible enumeration choices
  //
  bool8 displayChoices(const SysString& bad_param) const;

  //---------------------------------------------------------------------------
  //
  // private methods
  //
  //---------------------------------------------------------------------------
private:

  // the default and copy constructors are private since you must
  // supply a value string when you construct the object. 
  //
  NameMap();
  NameMap(const NameMap& arg);
  NameMap& operator=(const NameMap& arg);

  // this method tokenizes the input string into the NameMap values
  //
  bool8 assign(const SysString& arg, unichar delim = DELIM_CHR);

  // checksum methods
  //
  bool8 computeChecksum();
};

// end of include file
//
#endif
