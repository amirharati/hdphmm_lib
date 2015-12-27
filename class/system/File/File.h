// file: $isip/class/system/File/File.h
// version: $Id: File.h 9314 2003-09-30 01:29:13Z parihar $
//
// note:
// AH (07/27/2010): In function new I  add a temp variable to get ride of warning related to size
//
// make sure definitions are only made once
//
#ifndef ISIP_FILE
#define ISIP_FILE

// isip include files
//
#ifndef ISIP_INTEGRAL
#include <Integral.h>
#endif

#ifndef ISIP_ERROR
#include <Error.h>
#endif

#ifndef ISIP_MEMORY_MANAGER
#include <MemoryManager.h>
#endif

// forward class definitions
//
class SysChar;
class SysString;

// File: a general purpose file pointer. this class abstracts file
//  manipulations, which are operating system specific, and provides
//  a general interface that all classes should use to access files.
//
//  an important feature of this class is that a polling strategy for
//  opening files is built into the class. when a file open fails, it is
//  possible that the file exists, but the network file system for the
//  computer is in error. this happens often in unix when dealing with
//  files using the network file system. an effective solution is simply
//  to wait a specified time, and try again. more often than not,
//  the next open will succeed. since all file I/O is centralized through
//  this class, this feature is automatically available to all isip classes.
//
class File {
  
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

  // define some maximum sizes
  //
  static const int32 MAX_FNAME_SIZE = PATH_MAX;
  static const int32 BUF_SIZE = 8192;
  static const int32 BAD_COUNT = -1;
    
  // standard file streams
  //
  enum STREAM { NO_STREAM = -1, OUT, IN, ERROR, DEF_STREAM = NO_STREAM };
  
  // seek positions
  //
  enum SEEK { POS = SEEK_SET, POS_PLUS_CUR = SEEK_CUR,
	      POS_PLUS_END = SEEK_END };
  
  // i/o modes
  //
  enum MODE { READ_ONLY = 0, READ_PLUS, WRITE_ONLY,
	      WRITE_PLUS, APPEND_ONLY, APPEND_PLUS, DEF_MODE = READ_ONLY };
  
  // i/o types
  //
  enum TYPE { TEXT = 0, BINARY, DEF_TYPE = TEXT };
  
  // byte-order modes
  //
  enum BMODE { NATIVE = 0, SWAP, BIG_ENDIAN, LITTLE_ENDIAN,
	       DEF_BMODE = NATIVE };
  
  // names for each of the enumerated file modes
  //
  static const char SYS_TEXT_READ_ONLY[];
  static const char SYS_TEXT_READ_PLUS[];
  static const char SYS_TEXT_WRITE_ONLY[];
  static const char SYS_TEXT_WRITE_PLUS[];
  static const char SYS_TEXT_APPEND_ONLY[];
  static const char SYS_TEXT_APPEND_PLUS[];
  
  static const char SYS_BINARY_READ_ONLY[];
  static const char SYS_BINARY_READ_PLUS[];
  static const char SYS_BINARY_WRITE_ONLY[];
  static const char SYS_BINARY_WRITE_PLUS[];
  static const char SYS_BINARY_APPEND_ONLY[];
  static const char SYS_BINARY_APPEND_PLUS[];
 
  // names for each of the enumerated file type
  //
  static const SysString TYPE_TEXT;
  static const SysString TYPE_BINARY;

  // indention and line wrapping
  //
  static const SysString INDENT_STR;
  static const SysString WRAP_TERM_STR;
  static const SysString WRAP_PRE_INDENT_STR;
  static const SysString WRAP_POST_INDENT_STR;

  // a string denoting a piped input/output
  //
  static const SysString STREAM_FILE;
  
  //----------------------------------------
  //
  // default values and arguments
  //  
  //----------------------------------------  
  
  // lock constants:
  //  def_lock_retry is the default number of times we try to lock a file
  //  before reporting fails, the def_lock_delay is the time in seconds before 
  //  each retry
  //
  static const int32 DEF_LOCK = false;
  static const int32 DEF_LOCK_RETRY = 5;
  static const int32 DEF_LOCK_DELAY = 2;

  // formatting constants
  //
  static const int32 DEF_INDENT = 0;
  static const int32 NO_WRAP = -1;
  static const int32 DEF_LINE_WRAP = NO_WRAP;

  // open related constants:
  //  def_open_retry is the default number of times we try to open a file
  //  before reporting fails, the def_open_delay is the time in seconds before 
  //  each retry
  //
  static const int32 DEF_OPEN_RETRY = 5;
  static const int32 DEF_OPEN_DELAY = 2;
  
  //----------------------------------------
  //
  // error codes
  //
  //----------------------------------------  

  static const int32 ERR = 1000;
  static const int32 ERR_NOTCLS = 1001;
  static const int32 ERR_NOTOPN = 1002;
  static const int32 ERR_REOPEN = 1003;
  static const int32 ERR_CLOSE = 1004;
  static const int32 ERR_FLUSH = 1005;
  static const int32 ERR_TRUNCT = 1006;
  static const int32 ERR_WRAP = 1007;
  static const int32 ERR_DECODE = 1008;
  
  //---------------------------------------------------------------------------
  //
  // protected data
  //
  //---------------------------------------------------------------------------
protected:
  
  // the stream type
  //
  STREAM stream_d;
  
  // the file pointer
  //
  FILE* fp_d;
  
  // open mode and type
  //
  MODE mode_d;
  TYPE type_d;
  
  // lock flag
  //
  bool8 lock_d;
  
  // byte-order modes:
  //  it can be an absolute byte-order (LITTLE_ENDIAN or BIG_ENDIAN) or
  //  a relative order to the machine (NATIVE or SWAP)
  //
  BMODE byte_mode_d;

  // byte-swap flag:
  //  this is relative to the machine's byte-order
  //
  bool8 byte_swap_d;
  
  // indention level
  //
  int32 indent_level_d;
  
  // line wrapping limit
  //
  int32 line_wrap_d;
  
  // current column position
  //
  int32 column_position_d;
  
  // file polling:
  //  open_retry_d is the number of times that the file will be polled for
  //  opening before an error is returned. open_delay_d is the delay in
  //  seconds between attempts to open the file.
  //
  int32 open_retry_d;
  int32 open_delay_d;

  // declare an array of SysString objects to keep track of temporary filenames
  //
  static SysString** temp_files_d;
  static int32 temp_size_d;
  static int32 temp_num_d;

  // declare a static debug level for all class instantiations
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
  bool8 debug(const unichar* message) const;
  
  // destructor/constructor(s):
  //  the copy constructor is private
  //
  ~File();
  File(STREAM stream = DEF_STREAM);

  // assign methods:
  //  these methods are omitted because we do not ever want multiple file
  //  pointers on the same file. see the File::swap method
  //

  // operator= methods:
  //  these methods are omitted because we do not ever want multiple file
  //  pointers on the same file. 
  //

  // i/o methods:
  //  these methods are omitted because File can not write itself
  //  to an sof file
  //
  
  // equality methods:
  //  these methods are omitted because they are not useful for File objects
  //
  
  // memory management methods:
  //  the clear method is omitted so the user is forced to open and close
  //  files in a disciplined manner
  //
  
  // method: new
  //
  static void* operator new(size_t size) {
      // Added to get ride of the warning
      size_t temp;
      temp=size;
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
  //  extensions to the required public methods
  //
  //---------------------------------------------------------------------------
  
  // memory size methods
  //
  int32 memSize() const;
  
  // swap methods:
  //  this method serves as File's assignment method. we don't
  //  ever want multiple file pointers on the same file, so if you
  //  assign a pointer to another, the source loses it's data.
  //
  bool8 swap(File& arg);

  //---------------------------------------------------------------------------
  //
  // class-specific public methods:
  //  get/set methods
  //
  //---------------------------------------------------------------------------
  
  // method: setStreamType
  //
  bool8 setStreamType(STREAM arg) {
    return (stream_d = arg);
  }
  
  // method: setFileMode
  //
  bool8 setFileMode(MODE arg) {
    return (mode_d = arg);
  }  

  // method: get temporary files
  //
  SysString** getTempFilename() {
    return temp_files_d;
  }
  
  // method: get number of temporary files
  //
  int32 getNumTempFiles() {
    return temp_num_d;
  }
  
  //---------------------------------------------------------------------------
  //
  // class-specific public methods:
  //  file operation methods
  //
  //---------------------------------------------------------------------------
  
  // standard file methods
  //
  bool8 open(const unichar* filename, MODE mode = DEF_MODE,
	       TYPE type = DEF_TYPE);
  bool8 open(const SysString& filename, MODE mode = DEF_MODE,
	       TYPE type = DEF_TYPE);
  
  bool8 close();
  bool8 flush();
  bool8 truncate(int32 size);
  
  // file polling methods:
  //  this method sets the retry times that a file will be polled for
  //  opening before an error is returned
  //
  bool8 setOpenRetry(int32 retry, int32 delay);

  // file locking methods
  //
  bool8 lock(int32 retry = DEF_LOCK_RETRY, int32 DELAY = DEF_LOCK_DELAY);
  bool8 unlock();
  
  // positioning methods
  //
  bool8 seek(int32 offset, SEEK mode);
  int32 tell() const;
  
  // method: eof
  //
  bool8 eof() const {
    if (fp_d == (FILE*)NULL) {
      return Error::handle(name(), L"eof", ERR_NOTOPN, __FILE__, __LINE__,
			   Error::WARNING);
    }
    return feof(fp_d);
  }

  // method: rewind
  //
  bool8 rewind() {
    return seek(0, POS);
  }
  
  // method: isOpen
  //
  bool8 isOpen() const {
    return (fp_d != (FILE*)NULL);
  }
  
  // method: isReadable
  //
  bool8 isReadable() const {
    return ((fp_d != (FILE*)NULL) && (mode_d != WRITE_ONLY)
	    && (mode_d != APPEND_ONLY));
  }
  
  // method: isWritable
  //
  bool8 isWritable() const {
    return ((fp_d != (FILE*)NULL) && (mode_d != READ_ONLY));
  }
  
  // method: isText
  //
  bool8 isText() const {
    return ((fp_d != (FILE*)NULL) && (type_d == TEXT));
  }
  
  // method: isBinary
  //
  bool8 isBinary() const {
    return ((fp_d != (FILE*)NULL) && (type_d == BINARY));
  }
  
  // method: isLocked
  //
  bool8 isLocked() const {
    return lock_d;
  }

  // return the size of the file in bytes
  //
  int32 size(bool8 keep_position = true) const;
  static int32 size(const unichar* filename);
  static int32 size(const SysString& filename);

  //---------------------------------------------------------------------------
  //
  // class-specific public methods:
  //  i/o methods
  //
  //---------------------------------------------------------------------------
  
  // single character i/o methods
  //
  bool8 get(SysChar& chr);
  bool8 put(const SysChar chr);

  // string i/o methods (recommended)
  //
  bool8 get(SysString& str, int32 len = BUF_SIZE);
  bool8 put(const SysString& str);
  
  // buffer-based i/o methods:
  //  for binary files (with byte swapping).
  //  note these are not the same as the required read/write methods in
  //  other classes which read/ write the object itself from /into sof file
  //
  int32 read(void* ptr, int32 size, int32 num);
  int32 write(const void* ptr, int32 size, int32 num);
  
  //---------------------------------------------------------------------------
  //
  // class-specific public methods:
  //  formatting methods
  //
  //---------------------------------------------------------------------------
  
  // indentation methods
  //
  bool8 increaseIndention();
  bool8 decreaseIndention();
  
  // method: setLineWrap
  //
  bool8 setLineWrap(int32 num_cols) {
    line_wrap_d = num_cols;
    return true;
  }

  // method: getLineWrap
  //
  int32 getLineWrap() const {
    return line_wrap_d;    
  }

  // get the line length
  //
  int32 getLineLength() const;

  // methods to register temporary files so they can be cleanly deleted
  //
  static bool8 registerTemp(SysString& name);
  static bool8 cleanTemps();
  
  //---------------------------------------------------------------------------
  //
  // class-specific public methods:
  //  disk file operation methods
  //
  //---------------------------------------------------------------------------
  
  // the methods which take unichar* as arguments are not inlined because
  // they need include SysString.h. however SysString requires to include
  // File.h. therefore we don't inline these methods to avoid the compilation
  // error resulted from two classes trying to include each other.
  //
  static bool8 remove(const unichar* filename);  
  static bool8 remove(const SysString& filename);
  
  static bool8 rename(const unichar* old_name, const unichar* new_name);
  static bool8 rename(const SysString& old_name, const SysString& new_name);
  
  static bool8 mkdir(const unichar* dir_name);  
  static bool8 mkdir(const SysString& dir_name);
  
  static bool8 rmdir(const unichar* dir_name);
  static bool8 rmdir(const SysString& dir_name);
  
  static bool8 exists(const unichar* filename);    
  static bool8 exists(const SysString& filename);

  static bool8 compare(const unichar* file1, const unichar* file2);
  static bool8 compare(const SysString& file1, const SysString& file2);

  //---------------------------------------------------------------------------
  //
  // class-specific public methods:
  //  byte-order related methods
  //
  //---------------------------------------------------------------------------
  
  // set/get the absolute byte-order mode methods
  //
  bool8 setBMode(BMODE mode);
  BMODE getBMode() const;
  
  // get the machine's byte order methods
  //
  BMODE getMachineByteOrder() const;
  
  // single value encode/decode methods
  //
  int16 encode(int16 value) const;
  int32 encode(int32 value) const;
  int64 encode(int64 value) const;
  
  int16 decode(int16 value) const;
  int32 decode(int32 value) const;
  int64 decode(int64 value) const;

  //---------------------------------------------------------------------------
  //
  // class-specific public methods:
  //  string manipulation methods
  //
  //---------------------------------------------------------------------------

  // array-oriented methods
  //
  bool8 substr(SysString& str, int32 offset,
		 int32 num_elements = Integral::NO_POS) const;
  
  //---------------------------------------------------------------------------
  //
  // class-specific public methods:
  //  string search methods
  //
  //---------------------------------------------------------------------------

  // method: firstStr
  //
  int32 firstStr(const unichar* str, int32 start = Integral::NO_POS) const;

  // other first string methods
  //
  int32 firstStr(const SysString& str, int32 start = Integral::NO_POS) const;
  
  //---------------------------------------------------------------------------
  //
  // private methods
  //
  //---------------------------------------------------------------------------
private:
    
  // method: copy constructor
  //   this method is private so we can't copy file objects.
  //
  File(const File& arg);

  // method: encode
  //
  bool8 encode(void* buf, int32 size, int32 nitems) const {
    return encode(buf, buf, size, nitems);
  }

  // other encode methods:
  //
  bool8 encode(void* obuf, const void* ibuf, int32 size, int32 nitems) const;
  
  // method: decode
  //
  bool8 decode(void* buf, int32 size, int32 nitems) const {
    return decode(buf, buf, size, nitems);
  }

  // other decode methods:
  //
  bool8 decode(void* obuf, const void* ibuf, int32 size, int32 nitems) const;
};

// end of include file
//
#endif
