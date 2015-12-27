// file: $isip/class/shell/Sdb/Sdb.h
// version: $Id: Sdb.h 10640 2007-01-27 02:36:04Z tm334 $
//

// make sure definitions are only made once
//
#ifndef ISIP_SDB
#define ISIP_SDB

// isip include files
//
#ifndef ISIP_FILENAME
#include <Filename.h>
#endif

#ifndef ISIP_LONG
#include <Long.h>
#endif

#ifndef ISIP_BOOLEAN
#include <Boolean.h>
#endif

#ifndef ISIP_PAIR
#include <Pair.h>
#endif

#ifndef ISIP_WRAPPER
#include <Wrapper.h>
#endif

#ifndef ISIP_STACK
#include <Stack.h>
#endif

#ifndef ISIP_QUEUE
#include <Queue.h>
#endif

// forward class definitions
//
class CommandLine;

// Sdb: (Signal data base) class provides means of managing signal files
// and Sdb files
//
class Sdb {

  //---------------------------------------------------------------------------
  //
  // public constants
  //
  //---------------------------------------------------------------------------
public:

  // define the class name
  //
  static const String CLASS_NAME;

  // define filename translation constants
  //
  static const String DEF_OUT_DIR;
  
  //----------------------------------------
  //
  // i/o related constants
  //
  //----------------------------------------  
  
  static const String DEF_PARAM;

  // the marker string indicates the entry is an Sdb file to be
  // expanded, not just a filename. the option string is the command
  // line switch to preceed sdb files.
  //
  static const String LIST_FILE_MARKER;
  static const String LIST_FILE_OPTION;
  
  //----------------------------------------
  //
  // default values and arguments
  //
  //----------------------------------------  

  // define values
  //
  static const int32 DEF_LOOKAHEAD = 10;
  
  // default arguments to methods
  //
  static const int32 DEF_DIR_PRES = Filename::DEF_DIR_PRES;
  
  //----------------------------------------
  //
  // error codes
  //
  //----------------------------------------  

  static const int32 ERR = 45300;
  static const int32 ERR_NOTSDB = 45301;

  //---------------------------------------------------------------------------
  //
  // protected data
  //
  //---------------------------------------------------------------------------
protected:

  // the files that the user directly set. the flag specifies whether
  // it is a list or not.
  //
  DoubleLinkedList< Pair<Filename, Boolean> > files_d;

  // these are files ahead in the lookahead. everything here is not a
  // list, i.e. things are expanded before placed on this list.
  //
  Queue<Filename> queue_d;

  // class WSof;
  //
  // subclass definition for a limited wrapper. since Sof objects
  // cannot be assigned (the copy constructor is intentionally
  // blocked), we need to prevent Sof assign from ever being called.
  //
  class WSof : public Wrapper<Sof> {
    
  public:
    
    // method: default constructor
    //
    WSof() { }
    
    // method: copy constructor
    //
    WSof(const WSof& arg) {
      Error::handle(name(), L"copy constructor", ERR_NOTDEF, __FILE__,
		    __LINE__);
    }
    
    // method: assign
    //
    bool8 assign(const WSof& arg) {
      return Error::handle(name(), L"assign", ERR_NOTDEF, __FILE__,
			   __LINE__);
    }
    
    // method: operator=
    //
    bool8 operator=(const WSof& arg) {
      return Error::handle(name(), L"operator=", ERR_NOTDEF, __FILE__,
			   __LINE__);
    }
  };

  // this stack represents the current position. it is a stack of Sof
  // file pointers and int32 sof tag objects. note that the Wrapper
  // class is used since Sof does not implement the required public
  // methods.
  //
  Stack<WSof> fps_d;

  // the tag stack is a parallel data structure to fps_d. each element
  // represents the object tag currently pointed to by the sof object
  //
  Stack<Long> tags_d;

  // for binary operation we need to keep track of the number of
  // elements left to read
  //
  Stack<Long> nums_d;

  // the lookahead parameter
  //
  int32 lookahead_d;

  // are we at the begining of processing?
  //
  bool8 at_first_d;

  // output directory specification
  //
  String output_directory_d;

  // number of directories to preserve
  //
  Long dir_pres_d;

  // new extension to use
  //
  String output_extension_d;

  // new basename to use
  //
  String output_basename_d;

  // new suffix to use
  //
  String output_suffix_d;

  // define a static debug level for all objects of this class
  //
  static Integral::DEBUG debug_level_d;
  
  // static memory manager
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
  //
  static bool8 setDebug(Integral::DEBUG debug_level) {
    debug_level_d = debug_level;
    return true;
  }

  // other debug methods
  //
  bool8 debug(const unichar* message) const;
  
  // method: destructor
  //
  ~Sdb() {}

  // default constructor
  //
  Sdb();
  
  // assign methods:
  //  these methods are omitted since there is no need to copy the Sdb
  //  object
  //

  // operator= methods:
  //  these methods are private
  //
  
  // i/o methods
  //
  int32 sofSize() const;
  
  bool8 read(Sof& sof, int32 tag, const String& name = CLASS_NAME);
  bool8 write(Sof& sof, int32 tag, const String& name = CLASS_NAME) const;

  bool8 readData(Sof& sof, const String& pname = DEF_PARAM,
		   int32 size = SofParser::FULL_OBJECT, bool8 param = true,
		   bool8 nested = false);
  bool8 writeData(Sof& sof, const String& pname = DEF_PARAM) const;

  // equality methods
  //
  bool8 eq(const Sdb& arg) const;
  
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

  // other memory management methods
  //
  bool8 clear(Integral::CMODE ctype = Integral::DEF_CMODE);
  
  //---------------------------------------------------------------------------
  //
  // class-specific public methods:
  //  append methods
  //
  //---------------------------------------------------------------------------

  // append methods
  //
  bool8 append(const Filename& arg, bool8 is_list = false);
  bool8 append(const String& arg, bool8 is_list = false);
  bool8 append(const unichar* arg, bool8 is_list = false);

  //---------------------------------------------------------------------------
  //
  // class-specific public methods:
  //  file list positioning and transformation methods
  //
  //--------------------------------------------------------------------------

  // position to the first/next file
  //
  bool8 gotoFirst();
  bool8 gotoNext();

  // transformation methods 
  //
  bool8 transformName(Filename& output_file, const Filename& input_file);

  //---------------------------------------------------------------------------
  //
  // class-specific public methods:
  //  get and set methods
  //
  //---------------------------------------------------------------------------
  
  // get name methods
  //
  bool8 getName(Filename& arg);

  // method: length
  //
  int32 length() {

    int32 list_length = 0;
    for (bool8 more = gotoFirst(); more; more = gotoNext()) {
      list_length++;
    }
    return list_length;
  }

  // method: setOutputDirectory
  //
  bool8 setOutputDirectory(const String& new_dir) {
    return output_directory_d.assign(new_dir);
  }

  // method: getOutputDirectory
  //
  const String& getOutputDirectory() const {
    return output_directory_d;
  }
  
  // method: setDirPresLevel
  //
  bool8 setDirPresLevel(int32 new_pres_level) {
    return dir_pres_d.assign(new_pres_level);
  }

  // method: getDirPresLevel
  //
  int32 getDirPresLevel() const {
    return (int32)dir_pres_d;
  }
  
  // method: setOutputExtension
  //
  bool8 setOutputExtension(const String& new_ext) {
    return output_extension_d.assign(new_ext);
  }

  // method: getOutputExtension
  //
  const String& getOutputExtension() const {
    return output_extension_d;
  }

  // method: setOutputBasename
  //
  bool8 setOutputBasename(const String& new_basename) {
    return output_basename_d.assign(new_basename);
  }  

  // method: getOutputBasename
  //
  const String& getOutputBasename() const {
    return output_basename_d;
  }
  
  // method: setOutputSuffix
  //
  bool8 setOutputSuffix(const String& new_ext) {
    return output_suffix_d.assign(new_ext);
  }

  // method: getOutputSuffix
  //
  const String& getOutputSuffix() const {
    return output_suffix_d;
  }
  
  //---------------------------------------------------------------------------
  //
  // class-specific public methods:
  //  query methods
  //
  //---------------------------------------------------------------------------

  // does this file contain an Sdb object
  //
  static bool8 isSdb(const Filename& arg,
		       const String& obj_name = CLASS_NAME);
  static bool8 isSdb(Sof& arg, const String& obj_name = CLASS_NAME);
    
  //---------------------------------------------------------------------------
  //
  // private methods
  //
  //---------------------------------------------------------------------------
private:

  // constructors:
  //  the copy constructor is private since there is no need to copy
  //  the Sdb object
  //
  Sdb(const Sdb& arg);

  // operator= methods:
  //  this method is private since there is no need to copy
  //  the Sdb object
  //
  Sdb& operator=(const Sdb& arg);

  // iterate methods:
  //  for the filename currently at the mark, this function will test
  //  to see if the file is an Sof file containing an Sdb object. if it
  //  is, then the data will be read and each entry in this list will
  //  be inserted in place of the given filename. if it is not such a
  //  file list, the file itself will be inserted in the list. while
  //  this may sound inefficient, this will actually pre-fetch all data
  //  files to be processed.
  //
  int32 iterate();

  // parse methods:
  //  Sdb objects do not follow the name = value language handled by
  //  SofParser, so a customized parser is required. the input to this
  //  method is a single line of text from a file, the output is a
  //  filename.
  //
  bool8 parse(Filename& output, bool8& list, const String& input);

  // method useful for diagnostics: iterate over two Sdb objects
  // and determine if they contain the same files.
  //
  bool8 sameFiles(Sdb& arg);

  // friend class
  //
  friend class CommandLine;  

};

// end of include file
//
#endif
