// file: $isip/class/shell/Filename/Filename.h
// version: $Id: Filename.h 9209 2003-06-15 03:41:40Z picone $
//

// make sure definitions are only made once
//
#ifndef ISIP_FILENAME
#define ISIP_FILENAME

// isip include files
//
#ifndef ISIP_STRING
#include <String.h>
#endif

// Filename: hold and manipulate the name of a file. note that since this
// class actually holds a filename, we don't want to overload this class
// with a lot of internal data. hence, we implement the operating system
// specific methods as private methods.
//
class Filename : public String {

  //---------------------------------------------------------------------------
  //
  // public constants
  //
  //---------------------------------------------------------------------------
public:

  // define the class name
  //
  static const String CLASS_NAME;

  // define operating system choices
  //
  enum OS { UNIX = 0, WINDOWS, MACINTOSH,
	    DEF_OS = UNIX };

  // delimiters for a Unix filename
  //
  static const String SLASH;
  static const String DOT;
  static const String UNDERSCORE;
  
  //----------------------------------------
  //
  // default values and arguments
  //
  //----------------------------------------
  
  // define the default value(s) of the class data:
  //  note we inherit DEF_CAPACITY and DEF_VALUE from SysString class
  //
  
  // default arguments to methods:
  //  note we inherit DEF_PARAM from the String class
  //
  static const String DEF_EXTENSION;
  static const String DEF_SUFFIX;
  static const int32 DEF_DIR_PRES = 0;
  
  //----------------------------------------
  //
  // error codes
  //
  //----------------------------------------  

  static const int32 ERR = 45200;

  //---------------------------------------------------------------------------
  //
  // protected data
  //
  //---------------------------------------------------------------------------
protected:

  // this section contains data common to all operating systems
  //

  // operating system name
  //
  OS os_d;
  
  // a static memory manager
  //
  static MemoryManager mgr_d;
  
  //---------------------------------------------------------------------------
  //
  // required public methods
  //
  //---------------------------------------------------------------------------
public:
  
  // method: name
  //
  static const String& name() {
    return CLASS_NAME;
  }

  // other static methods
  //
  static bool8 diagnose(Integral::DEBUG debug_level);

  // method: setDebug
  //  this method is inherited from the SysString class
  //

  // other debug methods
  //
  bool8 debug(const unichar* message) const;

  // method: destructor
  //
  ~Filename() {}

  // method: default constructor
  //
  Filename(int32 arg = DEF_CAPACITY) {
    setOS(DEF_OS);
    setCapacity(arg);
  }

  // method: copy constructor
  //
  Filename(const Filename& arg) {
    assign(arg);
  }
  
  // method: assign
  //
  bool8 assign(const Filename& arg) {
    setOS(arg.os_d);
    return String::assign(arg);
  }

  // method: operator=
  //
   Filename& operator=(const Filename& arg) {
     assign(arg);
     return *this;
  }
  
  // i/o methods:
  //  the sofSize, readData, and writeData methods are inherited from String
  //
  bool8 read(Sof& sof, int32 tag, const String& name = CLASS_NAME);
  bool8 write(Sof& sof, int32 tag, const String& name = CLASS_NAME) const;

  // equality methods:
  //  this method is inherited from the SysString class
  //
  
  // memory management methods:
  //  clear method is inherited from the SysString class
  //

  // method: new
  //
  static void* operator new(size_t size) {
    return mgr_d.get();
  }

  // method: new[]
  //
  static void* operator new[](size_t size) {
    return mgr_d.getBlock(size);
  }

  // method: delete
  //
  static void operator delete(void* ptr) {
    mgr_d.release(ptr);
  }

  // method: delete[]
  //
  static void operator delete[](void* ptr) {
    mgr_d.releaseBlock(ptr);
  }

  // method: setGrowSize
  //
  static bool8 setGrowSize(int32 grow_size) {
    return mgr_d.setGrow(grow_size);
  }

  //---------------------------------------------------------------------------
  //
  // class-specific public methods:
  //  extensions to required methods
  //
  //---------------------------------------------------------------------------

  // method: constructor
  //
  Filename(const unichar* arg, OS os = DEF_OS) {
    setOS(os);
    String temp(arg);
    assign(temp);
  }

  // method: constructor
  //
  Filename(const String& arg, OS os = DEF_OS) {
    setOS(os);
    assign(arg);
  }
  
  // method: assign
  //  because we need to have an overload of the assign method
  //  for a Filename object, and Filename inherits a SysString,
  //  we must define an overload for SysString as well (or you get
  //  a seg fault).
  //
  bool8 assign(const String& arg) {
    return String::assign(arg);
  }

  // method: assign
  //  we also need a String assignment for the same reason
  //
  bool8 assign(const unichar* arg) {
    return String::assign(arg);
  }

  //---------------------------------------------------------------------------
  //
  // class-specific public methods:
  //  set and get methods
  //
  //---------------------------------------------------------------------------
  
  // method: setOS
  //
  bool8 setOS(OS os) {
    os_d = os;
    return true;
  }
  
  // method: getOS
  //
  OS getOS() const {
    return os_d;
  }

  //---------------------------------------------------------------------------
  //
  // class-specific public methods:
  //  filename parsing methods
  //
  //---------------------------------------------------------------------------

  // define the basic transform command
  //
  bool8 transform(const String& new_dir, 
		    const String& new_ext,
		    const String& new_suffix,
		    int32 dir_preserve = DEF_DIR_PRES);
  
  // method: transform (without a directory)
  //
  bool8 transform(const String& new_ext,
		    const String& new_suffix) {
    String old_dir;
    getDir(old_dir);
    return transform(old_dir, new_ext, new_suffix);
  }

  // method: transform (with a filename argument)
  //
  bool8 transform(const String& old_name,
		    const String& new_dir, const String& new_ext,
		    const String& new_suffix,
		    int32 dir_preserve = DEF_DIR_PRES) {
    assign(old_name);
    return transform(new_dir, new_ext, new_suffix, dir_preserve);
  }

  // define a basic command to generate a new, unique filename
  // from an existing one
  //
  bool8 transformUniquely();  

  // method: transformUniquely (with the filename as an argument)
  //
  bool8 transformUniquely(const String& old_name) {
    assign(old_name);
    return transformUniquely();
  }

  //---------------------------------------------------------------------------
  //
  // class-specific public methods:
  //  get methods. note that there is not getSuffix because by definition
  //  a suffix is only added to a filename.
  //
  //---------------------------------------------------------------------------
  
  // method: getDir
  //
  bool8 getDir(String& dir) const;

  // method: getBase
  //
  bool8 getBase(String& base) const;

  // method: getExt
  //
  bool8 getExt(String& ext) const;

  // method: getName
  //
  bool8 getName(String& filename) const;
  
  //---------------------------------------------------------------------------
  //
  // class-specific public methods:
  //  temporary filename methods
  //
  //---------------------------------------------------------------------------
  
  // method: makeTemp
  //
  bool8 makeTemp() {
    return Integral::makeTemp(*this);
  }

  // method: makeTemp
  //
  bool8 makeTemp(const String& basename) {
    return Integral::makeTemp(*this, basename);
  }

  //---------------------------------------------------------------------------
  //
  // class-specific public methods:
  //  methods to build necessary subdirectories for the output file
  //
  //---------------------------------------------------------------------------
  
  // pathfinding method
  //
  static bool8 buildPath(const String& pathname);
  
  //---------------------------------------------------------------------------
  //
  // private methods
  //
  //---------------------------------------------------------------------------
private:

  // directory merging methods
  //
  bool8 preserveDirName(String& mod_dir, const String& new_dir,
			  const String& old_dir, int32 dir_preserve);

  // delimiter methods
  //
  bool8 getDirDelim(String& arg) const;
  bool8 getFileDelim(String& arg) const;

  // UNIX filename parsing methods
  //
  bool8 getDirUnix(String& dir) const;
  bool8 getBaseUnix(String& base) const;
  bool8 getExtUnix(String& ext) const;
  bool8 getNameUnix(String& filename) const;
  bool8 getDirDelimUnix(String& arg) const;
  bool8 getFileDelimUnix(String& arg) const;

  // WINDOWS filename parsing methods
  //
  bool8 getBaseWin(String& base) const;
  bool8 getExtWin(String& ext) const;
  bool8 getDirWin(String& dir) const;
  bool8 getNameWin(String& filename) const;
  bool8 getDirDelimWin(String& arg) const;
  bool8 getFileDelimWin(String& arg) const;

  // MACINTOSH filename parsing methods
  //
  bool8 getBaseMac(String& base) const;
  bool8 getExtMac(String& ext) const;
  bool8 getDirMac(String& dir) const;
  bool8 getNameMac(String& filename) const;
  bool8 getDirDelimMac(String& arg) const;
  bool8 getFileDelimMac(String& arg) const;
};

// end of include file
//
#endif
