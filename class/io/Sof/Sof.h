// file: $isip/class/io/Sof/Sof.h
// version: $Id: Sof.h 6805 2001-04-23 22:57:41Z peng $
//

// make sure definitions are only made once
//
#ifndef ISIP_SOF
#define ISIP_SOF

// isip include files
//
#ifndef ISIP_FILE
#include <File.h>
#endif

#ifndef ISIP_SOF_SYMBOL_TABLE
#include <SofSymbolTable.h>
#endif

#ifndef ISIP_SOF_LIST
#include <SofList.h>
#endif

#ifndef ISIP_CHECKSUM
#include <Checksum.h>
#endif

// forward class definitions
//
class SofParser;

// Sof: (s)ignal (o)bject (f)ile
//
// this file defines a class that is used to read and write isip objects
// to a file (binary or text). this class serves as an index, keeping
// track of all objects written to a file. note that multiple objects
// of the same class name can be written to a file.
//
class Sof {

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
  // Sof file parsing related constants
  //
  //----------------------------------------  

  // define magic sequences used to identify an Sof file
  //
  static const int32 MAX_MAGIC_LENGTH = 22;

  // define the version number and magic number
  //
  static const SysString VERSION;

  // define some sizes
  //
  static const int32 MESSAGE_SIZE = 1024;
  static const int32 CLASS_NAME_SIZE = 256;
  
  // define deletion characters
  //
  static const char DELETE_CHAR_TEXT = ' ';
  static const char DELETE_CHAR_BINARY = '\0';

  // define new line characters
  //
  static const char NEWLINE_BUFFER[];
  static const int32 NEWLINE_LENGTH;
  
  //----------------------------------------
  //
  // byte-mode related constants
  //
  //----------------------------------------  

  // define descriptor string related to these byte modes
  //
  static const SysString BSTR_NATIVE;
  static const SysString BSTR_SWAP;

  // define the numbers that these string should convert to
  //
  static const int32 BCODE_NATIVE = 1633837924;
  static const int32 BCODE_SWAP = 1684234849;
  
  // define the length of the byte-string for testing
  //
  static const int32 BSTR_LEN = 4;
  
  // determine if the machine supports IEEE floating point
  //
  static const float32 IEEE_FLOAT_NATIVE = 16777999408082104352768.000000;
  static const float32 IEEE_FLOAT_SWAP = 261007875622861537280.000000;

  //----------------------------------------
  //
  // tag related constants
  //
  //----------------------------------------  
  
  // define constants for the implicit tag number regions
  //
  // if you go over 1.07 billion implicitly numbered tags, it will error
  //
  static const int32 NO_TAG = SofList::NO_TAG;
  static const int32 ALL_TAGS = NO_TAG + 1;
  static const int32 FREE_TAG = NO_TAG + 2;
  static const int32 IMPLICIT_END = -1073741824;
  static const int32 IMPLICIT_START = (NO_TAG + 3);
    
  //----------------------------------------
  //
  // binary index i/o related constants
  //
  //----------------------------------------  
  
  // define the buffer size to be used. the sof binary index, when
  // written, is aligned at this buffer size to expedite i/o.
  //
  static const int32 BUFFER_SIZE = File::BUF_SIZE;
  
  // positions in the sequentially output symbol table
  //
  static const int32 SYMBOL_BASE	= (2 * sizeof(uint32) + sizeof(ubyte8));
  static const int32 SYMBOL_OFFSET_NEXT = 0;
  static const int32 SYMBOL_OFFSET_IND =	SYMBOL_OFFSET_NEXT + sizeof(ubyte8);
  static const int32 SYMBOL_OFFSET_REFS = SYMBOL_OFFSET_IND + sizeof(int32);
  static const int32 SYMBOL_OFFSET_NAME = SYMBOL_OFFSET_REFS + sizeof(int32);
  
  // positions in the sequentially output binary index
  //
  static const int32 INDEX_SIZE = (4 * sizeof(int32) + sizeof(byte8));
  static const int32 INDEX_OFFSET_NEXT = 0;
  static const int32 INDEX_OFFSET_POS = INDEX_OFFSET_NEXT + sizeof(byte8);
  static const int32 INDEX_OFFSET_TAG = INDEX_OFFSET_POS + sizeof(int32);
  static const int32 INDEX_OFFSET_SIZE = INDEX_OFFSET_TAG + sizeof(int32);
  static const int32 INDEX_OFFSET_NAME = INDEX_OFFSET_SIZE + sizeof(int32);

  // constant for the skip table size (partial i/o)
  //
  static const int32 SKIP_TABLE_GROUP = 10;
  
  //----------------------------------------
  //
  // default values and arguments
  //
  //----------------------------------------  

  // define the default value(s) of the class data
  //
  static const unichar DEF_DELIMITER = L'@';
  static const int32 DEF_POS = -1;
  static const int32 DEF_IMPLICIT = IMPLICIT_START;
  static const bool8 DEF_DISABLE_LOCK = true;
  
  // default arguments to methods
  //
  static const int32 ANY_SIZE = -1;
  
  //---------------------------------------
  //
  // error codes
  //
  //---------------------------------------
  
  static const int32 ERR				= 10000;
  static const int32 ERR_NOTSOF			= 10001;
  static const int32 ERR_NOOBJ			= 10002;
  static const int32 ERR_NOTAG			= 10003;
  static const int32 ERR_UPDATEH			= 10011;
  static const int32 ERR_UPDATE			= 10012;
  static const int32 ERR_CLOSE			= 10015;
  static const int32 ERR_RANGE			= 10020;
  static const int32 ERR_CURPOS			= 10021;
  static const int32 ERR_FLOAT			= 10042;
  static const int32 ERR_READHD			= 10043;
  static const int32 ERR_TYPE			= 10044;
  static const int32 ERR_STRUCT			= 10045;
  static const int32 ERR_LABEL			= 10051;
  static const int32 ERR_IMPLIC			= 10061;
  static const int32 ERR_TAG			= 10062;
  static const int32 ERR_BINARY			= 10063;
  static const int32 ERR_PARTIAL			= 10070;
  static const int32 ERR_RESIZE			= 10071;

  //---------------------------------------------------------------------------
  //
  // protected data
  //
  //---------------------------------------------------------------------------
protected:

  // general information about a file
  //
  SysString name_d;                         // current filename
  SysString expanded_name_d;                // expanded filename
  File::TYPE file_type_d;	            // type of file (text or binary)  

  // I/O related variables
  //
  File fp_d;				    // active file pointer
  
  // auxiliary information
  //
  unichar delimiter_d;                     // object tag delimiter
  int32 end_of_header_d;                    // end of header, start of data
  int32 end_of_data_d;                      // end of data, start of index 
  int32 cur_data_d;                         // start of current object data

  // current file position (global, what ftell() would return)
  //
  int32 cur_pos_d;
  
  // next free implicit tag number
  //
  int32 implicit_count_d;		
  
  // file locking
  //
  bool8 disable_lock_d;
  int32 lock_retry_d;
  int32 lock_delay_d;
  
  // symbol table used for names
  //
  SofSymbolTable table_d;
  
  // list used to process the object index
  //
  SofList index_d;

  // scratch space for magic number manipulations
  //
  SysString cname_d;                              // sof file tag 
  SysString version_d;                            // sof version
  SysString magic_d;			          // sof magic number

  // variables used in partial read and write
  //
  bool8 partial_write_d;
  bool8 partial_read_d;
  SofParser* vec_parser_d;
  int32* skip_table_d;
  int32 skip_table_incr_d;
  int32 last_skip_table_pos_d;
  int32 vec_start_pos_d;
  int32 vec_size_d;
  int32 vec_curr_elem_d;

  // the checksum read from the file
  //
  uint16 file_checksum_d;
  
  // static checksum object for binary files
  //
  static Checksum cksm_d;
  
  // debugging parameters
  //
  Integral::DEBUG debug_level_d;

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
  bool8 setDebug(Integral::DEBUG level) {
    debug_level_d = level;
    return true;
  }
  
  // other debug methods
  //
  bool8 debug(const unichar* msg) const;

  // destructor/constructor(s)
  //
  ~Sof();
  Sof();
  
  // assign methods
  //
  bool8 assign(const Sof& arg);
  
  // method: operator=
  //
  Sof& operator=(const Sof& arg) {
    if (!assign(arg)) {
      Error::handle(name(), L"operator=", Error::ARG, __FILE__, __LINE__);
    }      
    return *this;
  }
  
  // i/o methods:
  //  these methods are omitted because Sof can not write itself to an
  //  sof file
  //
  
  // equality methods:
  //  these methods are omitted because they are not useful for Sof objects
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
  
  // clear method
  //  this clear method is slightly different from the required clear
  //  method in that it can be used only for writable Sof files. it deletes
  //  all items from the sof file for all CMODE's.
  // 
  bool8 clear(Integral::CMODE ctype = Integral::DEF_CMODE);
  
  //---------------------------------------------------------------------------
  //
  // class-specific public methods:
  //  extensions to the required public methods
  //
  //---------------------------------------------------------------------------

  // memory size methods
  //
  int32 memSize();
  
  //---------------------------------------------------------------------------
  //
  // class-specific public methods:
  //  file operation methods
  //
  //---------------------------------------------------------------------------
    
  // method: open
  //
  bool8 open(const unichar* filename, File::MODE mode = File::READ_ONLY,
	       File::TYPE type = File::DEF_TYPE) {
    SysString temp(filename);
    return open(temp, mode, type);
  }

  bool8 open(const SysString& filename, File::MODE mode = File::READ_ONLY,
	       File::TYPE type = File::DEF_TYPE);

  // close methods
  //
  bool8 close();
  
  // close all open Sof files (part of Error's clean exit)
  //
  static bool8 closeAll();
  
  // method: setLockDisable
  //
  bool8 setLockDisable(bool8 disable) {
    disable_lock_d = disable;
    return true;
  }

  // method: setLockRetry
  //
  bool8 setLockRetry(int32 retry, int32 delay = File::DEF_LOCK_DELAY) {
    lock_retry_d = retry;
    lock_delay_d = delay;
    return true;
  }
      
  // method: setDelimiter
  //
  bool8 setDelimiter(unichar chr) {
    delimiter_d = chr;
    return true;
  }
  
  // method: getDelimiter
  //
  unichar getDelimiter() const {
    return delimiter_d;
  }
  
  // method: getName
  //
  const SysString& getName() const {
    if (!isOpen()) {
      Error::handle(name(), L"getName", Error::READ_CLOSED, __FILE__,
		    __LINE__);
    }
    return name_d;
  }

  // method: getExpandedName
  //
  const SysString& getExpandedName() const {
    if (!isOpen()) {
      Error::handle(name(), L"getName", Error::READ_CLOSED, __FILE__,
		    __LINE__);
    }
    return expanded_name_d;
  }

  // file queries methods
  //
  bool8 isSof();
  static bool8 isSof(const SysString& filename);
  
  // method: isText
  //
  bool8 isText() const{
    return (file_type_d == File::TEXT);
  }
  
  // method: isBinary
  //
  bool8 isBinary() const {
    return (file_type_d != File::TEXT);
  }
  
  // method: isOpen
  //
  bool8 isOpen() const {
    return fp_d.isOpen();
  }

  // method: isSameFile
  //
  bool8 isSameFile(Sof& sof_obj) {
    return (expanded_name_d.eq(sof_obj.expanded_name_d));
  }

  //---------------------------------------------------------------------------
  //
  // class-specific public methods:
  //  object operation methods
  //
  //---------------------------------------------------------------------------
  
  // method: find
  //
  bool8 find(const SysString& name, int32 tag) {
    return find(table_d.getIndex(name), tag);
  }
  int32 first(const SysString& name);
  int32 last(const SysString& name);

  // method: next
  //  this method finds the next instance of this object in the index
  //
  int32 next(const SysString& name, int32 cur_tag) {
    int32 name_ind = table_d.getIndex(name);    // find in symbol table
    return index_d.next(name_ind, cur_tag);    // return the tag
  }
  
  // method: prev
  //
  int32 prev(const SysString& name, int32 cur_tag) {
    int32 name_ind = table_d.getIndex(name);
    return index_d.prev(name_ind, cur_tag);
  }
  
  // object put methods
  //
  bool8 put(const SysString& name, int32 size);
  bool8 put(const SysString& name, int32 tag, int32 size);

  // object remove methods
  //
  bool8 remove(const SysString& name, int32 object_tag);
  bool8 remove(int32 name, int32 object_tag);
  bool8 remove(const SysString& name);
  bool8 remove(int32 name);
  
  // object copy methods
  //
  bool8 copy(int32 o_tag, Sof& i_sof, const SysString& i_cname, int32 i_tag);
  bool8 copy(int32 o_tag, Sof& i_sof, int32 i_cname, int32 i_tag);
  bool8 copy(Sof& i_sof, const SysString& i_cname);
  bool8 copy(Sof& i_sof, int32 i_cname);

  // object operations: get methods
  //
  int32 getObjectSize(const SysString& name, int32 tag);
  int32 getObjectSize();

  // index count methods
  //
  
  // method: getCount
  //  this method gets the number of objects with this class name
  //
  int32 getCount(const SysString& name) {
    return index_d.getCount(table_d.getIndex(name));
  }

  // method: getCount
  //
  int32 getCount() {
    return index_d.getCount();    
  }

  // method: getNameCount
  //  this method gets the number of classes in the file,
  //  note it only works because the index is sorted
  //
  int32 getNameCount() {
    return table_d.getCount();
  }

  // method: enumerate
  //  this method enumerates all objects in an sof file
  //
  bool8 enumerate(SofList& index, SofSymbolTable& table) const {
     index.assign(index_d);
     table.assign(table_d);
     return true;
  }

  // positioning methods (relative to current object)
  //
  bool8 seek(int32 offset, File::SEEK whence);
  int32 tell() const;

  // method: rewind
  //
  bool8 rewind() {
    if (cur_data_d < 0) {
      return Error::handle(name(), L"rewind", SofList::ERR, __FILE__,
			   __LINE__);
    }
    return fseek(cur_data_d, File::POS);
  }
  
  //---------------------------------------------------------------------------
  //
  // class-specific public methods:
  //  input and output methods
  //
  //---------------------------------------------------------------------------
  
  // wrap the base i/o functions with automatic byte-swapping and
  // range checking. imagine each object within an Sof file is it's
  // own file, so rewind brings you to the beginning of that object's
  // space, not the begining of the actual file.
  //

  // binary i/o methods
  //
  int32 read(void* ptr, int32 size, int32 nitems);
  int32 write(const void* ptr, int32 size, int32 nitems);

  // text i/o methods
  //
  bool8 gets(SysString& ptr, int32 size = BUFFER_SIZE);
  bool8 puts(const SysString& ptr);

  // write label methods
  //
  bool8 writeLabelPrefix(const SysString& param_name);
  bool8 writeLabelSuffix(const SysString& param_name);
  
  //---------------------------------------------------------------------------
  //
  // class-specific public methods:
  //  formatting methods
  //
  //---------------------------------------------------------------------------
  
  // these methods are for text sof file only. refer File class for
  // the meaning of these methods
  //
  
  // method: increaseIndention
  //
  bool8 increaseIndention() {
    if (isText()) {
      return fp_d.increaseIndention();
    }
    return false;
  }

  // method: decreaseIndention
  //
  bool8 decreaseIndention() {
    if (isText()) {
      return fp_d.decreaseIndention();
    }
    return false;
  }
  
  // method: setLineWrap
  //
  bool8 setLineWrap(int32 ncols) {
    if (isText()) {
      return fp_d.setLineWrap(ncols);
    }
    return false;
  }

  // method: getLineLength
  //
  int32 getLineLength() const {
    if (isText()) {
      return fp_d.getLineLength();            // only for text files
    }
    return -1;                                // exit ungracefully 
  }

  // method: getLineWrap
  //
  int32 getLineWrap() const {
    if (isText()) {
      return fp_d.getLineWrap();
    }
    return -1;
  }
  
  //---------------------------------------------------------------------------
  //
  // class-specific public methods:
  //  methods that facilitate partial i/o
  //
  //---------------------------------------------------------------------------

  // partial write configuration methods
  //
  
  // methods to facilitate partial i/o
  //
  bool8 startPartialWrite();
  bool8 stopPartialWrite();
  bool8 startPartialRead();
  bool8 stopPartialRead();

  // method: getSkipTable
  //
  int32* getSkipTable() {
    if ((!partial_write_d) && (!partial_read_d)) {
      Error::handle(name(), L"getSkipTable", ERR, __FILE__, __LINE__);
    }
    return skip_table_d;
  }

  // method: getSkipTable
  //
  const int32* getSkipTable() const {
    if ((!partial_write_d) && (!partial_read_d)) {
      Error::handle(name(), L"getSkipTable", ERR, __FILE__, __LINE__);
    }
    return skip_table_d;
  }

  // method: getSkipTableIncr
  //
  int32 getSkipTableIncr() const {
    if ((!partial_write_d) && (!partial_read_d)) {
      return Error::handle(name(), L"getSkipTableIncr", ERR,
			   __FILE__, __LINE__);
    }
    return skip_table_incr_d;
  }

  // method: getLastSkipTablePos
  //
  int32 getLastSkipTablePos() const {
    if ((!partial_write_d) && (!partial_read_d)) {
      return Error::handle(name(), L"getLastSkipTablePos", ERR,
			   __FILE__, __LINE__);
    }
    return last_skip_table_pos_d;
  }

  // method: getStartPos
  //
  int32 getStartPos() const {
    if ((!partial_write_d) && (!partial_read_d)) {
      return Error::handle(name(), L"getStartPos", ERR,
			   __FILE__, __LINE__);
    }
    return vec_start_pos_d;
  }

  // method: getVecSize
  //
  int32 getVecSize() const {
    if ((!partial_write_d) && (!partial_read_d)) {
      return Error::handle(name(), L"getVecSize", ERR,
			   __FILE__, __LINE__);
    }
    return vec_size_d;
  }
  
  // method: getVecCurrentElement
  //
  int32 getVecCurrentElement() const {
    if ((!partial_write_d) && (!partial_read_d)) {
      return Error::handle(name(), L"getVecCurrentElement", ERR,
			   __FILE__, __LINE__);
    }
    return vec_curr_elem_d;
  }

  // method: getVecParser
  //
  const SofParser& getVecParser() const;
  SofParser& getVecParser();
  
  // method: setSkipTableIncr
  //
  bool8 setSkipTableIncr(int32 pos) {
    if ((!partial_write_d) && (!partial_read_d)) {
      return Error::handle(name(), L"getSkipTableIncr", ERR,
			   __FILE__, __LINE__);
    }
    skip_table_incr_d = pos;
    return true;
  }

  // method: setLastSkipTablePos
  //
  bool8 setLastSkipTablePos(int32 pos) {
    if ((!partial_write_d) && (!partial_read_d)) {
      return Error::handle(name(), L"getLastSkipTablePos", ERR,
			   __FILE__, __LINE__);
    }
    last_skip_table_pos_d = pos;
    return true;
  }

  // method: setStartPos
  //
  bool8 setStartPos(int32 pos) {
    if ((!partial_write_d) && (!partial_read_d)) {
      return Error::handle(name(), L"setStartPos", ERR,
			   __FILE__, __LINE__);
    }
    vec_start_pos_d = pos;
    return true;
  }
  

  // method: setVecSize
  //
  bool8 setVecSize(int32 pos) {
    if ((!partial_write_d) && (!partial_read_d)) {
      return Error::handle(name(), L"setVecSize", ERR,
			   __FILE__, __LINE__);
    }
    vec_size_d = pos;
    return true;
  }
  
  // method: setVecCurrentElement
  //
  bool8 setVecCurrentElement(int32 pos) {
    if ((!partial_write_d) && (!partial_read_d)) {
      return Error::handle(name(), L"setVecCurrentElement", ERR,
			   __FILE__, __LINE__);
    }
    vec_curr_elem_d = pos;
    return true;
  }

  // method: getPartialWrite
  //
  bool8 getPartialWrite() const {
    return partial_write_d;
  }

  // method: getPartialRead
  //
  bool8 getPartialRead() const {
    return partial_read_d;
  }

  // method: clearSkipTable
  //
  bool8 clearSkipTable() {
    if (skip_table_d == (int32*)NULL) {
      return Error::handle(name(), L"clearSkipTable", Error::MEM,
			   __FILE__, __LINE__);
    }
    for (int32 i = 0; i < SKIP_TABLE_GROUP; i++) {
      skip_table_d[i] = -1;
    }
    return true;
  }

  // method: writeSkipTable
  //
  bool8 writeSkipTable() {
    if (skip_table_d == (int32*)NULL) {
      return Error::handle(name(), L"writeSkipTable", Error::MEM,
			   __FILE__, __LINE__);
    }
    int32 n = write(skip_table_d, sizeof(int32), SKIP_TABLE_GROUP);
    return (n == SKIP_TABLE_GROUP);
  }

  // method: readSkipTable
  //
  bool8 readSkipTable() {
    if (skip_table_d == (int32*)NULL) {
      return Error::handle(name(), L"writeSkipTable", Error::MEM,
			   __FILE__, __LINE__);
    }
    last_skip_table_pos_d = tell();
    int32 n = read(skip_table_d, sizeof(int32), SKIP_TABLE_GROUP);
    return (n == SKIP_TABLE_GROUP);
  }

  // resize entry methods (should only be called in partial write mode)
  //
  bool8 resize(int32 size);

  //---------------------------------------------------------------------------
  //
  // private methods
  //
  //---------------------------------------------------------------------------
private:

  // method: copy constructor
  //  the method is private so we can't copy Sof objects.
  //
  Sof(const Sof& arg) {
    Error::handle(name(), L"Sof Constructor",
		  Error::BAD_CSTR, __FILE__, __LINE__);
  }
  
  // free memory methods
  //
  bool8 cleanUp();
  bool8 freeIndex();

  // update methods:
  //  update index and header
  //
  bool8 update();	

  // binary index i/o methods
  //
  bool8 readIndex();			
  bool8 writeIndex();			

  // symbol table i/o methods
  //
  bool8 readTable();	
  bool8 writeTable();			
  
  // open read methods:
  //  these methods open an sof file for read access
  //
  bool8 openRead();
  
  // method: openReadText
  //
  bool8 openReadText() {
    return openReadIndexText();
  }
  
  // method: openReadBinary
  //
  bool8 openReadBinary() {
    return openReadIndexBinary();
  }

  // open read index methods:
  //  these methods open a sof file for reading the indices
  //
  bool8 openReadIndexText();
  bool8 openReadIndexBinary();
  
  // open write methods:
  //  these methods open an sof file for write access
  //
  bool8 openWrite(File::MODE access_mode);

  // text file label handling methods
  //
  bool8 writeLabel(int32 name, int32 tag);
  bool8 writeLabel(const SysString& name, int32 tag);
  bool8 parseLabel(SysString& name, int32& tag, const SysString& buf);
  bool8 skipLabel(); 
 
  // method: seekData
  //  these methods seek to the data of an object
  //
  bool8 seekData() {
    if (file_type_d == File::TEXT) {
      return seekDataText();
    }
    return seekDataBinary();
  }
  
  bool8 seekDataText();
  bool8 seekDataBinary();
  
  // internal object manipulation methods:
  //  the public interface is far simpler
  //
  bool8 find(int32 name, int32 tag);
  bool8 add(const SysString& name, int32 size, int32 tag = FREE_TAG);
  bool8 add(int32 name, int32 size, int32 tag = FREE_TAG);
  
  // resize methods:
  //  resize the current entry, preserving current data
  //
  bool8 resize(const SysString& name, int32 tag, int32 size);
  
  // binary i/o methods:
  //  read/write with byte swapping without range checking
  //
  int32 fwrite(const void* ptr, int32 size, int32 nitems);
  int32 fread(void* ptr, int32 size, int32 nitems);
  
  // position methods
  //
  bool8 fseek(int32 offset, File::SEEK whence);
  int32 ftell() const;

  // copy segment methods:
  //  efficient methods for clearing out a section of a file and
  //  copying a section of a file from one place to another.
  //
  bool8 clearSpace(int32 nbytes);
  bool8 copySegment(int32 src_pos, int32 size);
  bool8 copySegment(int32 src_pos, int32 dest_pos, int32 size);
  
  // error pointer setting methods
  //
  bool8 setErrorPointer();

  // register pointer maintaining methods:
  //  maintain an array of all open Sof pointers (part of clean exit)
  //
  bool8 registerPtr();
  bool8  unRegisterPtr();

  //---------------------------------------------------------------------------
  //
  // friend functions and classes:
  //  while friend functions and classes are generally discouraged in the ISIP
  //  environment, they are used in the Sof class to allow the
  //  AudioFile class direct access to Sof's internals for efficiency.
  //
  //---------------------------------------------------------------------------

  // class: AudioFile
  //
  friend class AudioFile;
};

// end of include file
//
#endif
