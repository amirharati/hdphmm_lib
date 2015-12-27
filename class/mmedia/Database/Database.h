// file: Database.h
// version: $Id: Database.h 10636 7/10/2013
//
// Updated : 7/10/2013 by Amir Harati
// 
//
// make sure definitions are only made once
//
#ifndef ISIP_DATABASE
#define ISIP_DATABASE

// isip include files:
//
#ifndef ISIP_SYS_STRING
#include <SysString.h>
#endif

#ifndef ISIP_MEMORY_MANAGER
#include <MemoryManager.h>
#endif

#ifndef ISIP_CIRCULAR_BUFFER
#include <CircularBuffer.h>
#endif

#ifndef  ISIP_MATRIX_DOUBLE
#include <MatrixDouble.h>
#endif

#ifndef  ISIP_INTEGRAL
#include <Integral.h>
#endif

#ifndef ISIP_VECTOR_FLOAT
#include <VectorFloat.h>
#endif

// Database: a class that implements a database structure to read/manipulate sequential data  
//
// each data record is a matrix; the database consists of a CircularBuffer that read the data from data file
// and made them avalible for user
//
class Database {

  //---------------------------------------------------------------------------
  //
  // public constants
  //
  //---------------------------------------------------------------------------
public:
  
  // define the class name
  //
  static const String CLASS_NAME;
  
  // define i/o related constants
  //
  static const String DEF_PARAM;
  static const String PARAM_DATA;
  static const String PARAM_LABELS;
  static const String PARAM_RECORD;
  //----------------------------------------
  //
  // other important constants
  //
  //----------------------------------------
  static long MAX_BUFF_SIZE;

  enum MODE { READ = 0, WRITE, DEF_MODE = READ};
 
  enum DATABASE_TYPE { DIRECT = 0 , HTK, DEF_DATABASE_TYPE = 0};
  //----------------------------------------
  //
  // default values and arguments
  //
  //----------------------------------------  

  // define the default value(s) of the class data
  //
  
  // default arguments to methods
  //


  //----------------------------------------
  //
  // error codes
  //
  //----------------------------------------  

  static const int32 ERR = 1900;

  //---------------------------------------------------------------------------
  //
  // protected data
  //
  //---------------------------------------------------------------------------
protected:

  // "data" is  a buffer that contains all instances of data.
  //
  CircularBuffer<MatrixDouble> data_d;
  
  //  "labels"  is a  buffer that contains labels for data instances 
  //
  CircularBuffer<VectorLong> labels_d;

  CircularBuffer<String> fnames_d;

  
  // database_type
  //
  DATABASE_TYPE database_type_d;

  // file name
  //
  String filename_d;

  // number of records
  //
  long records_no_d;

  // buffer size
  //
  long buff_size_d;

  // current index
  //
  long current_index_d;
  
  // first index : first index currently in the buffer
  //
  long first_index_d;

  // last index : last index currently in the buffer
  //
  long last_index_d;
  
  // define temp variables used internally for reading data from SOF files
  //
  MatrixDouble data_temp_d;
  VectorLong labels_temp_d; 
  String fname_temp_d;

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

  // define variables for reteriving data using get
  //
  MatrixDouble curr_data_d;
  VectorLong curr_labels_d;
  String curr_fname_d;

  // frame_rate_a : it is assumed that all files in a Db has
  // same  frame rate. For direct model fr=10.
  // frame rate is in msec
  //
  Double db_fr_d;
  
  //data dimension
  //
  long dim_d;

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

  // method: destructor
  //
  ~Database() {}

  // other constructor(s)
  //
  Database(){
    
    // set current index to zero
    //
    current_index_d = 0;
  }

  // assign methods:
  //
  //bool8 assign(const Database& arg);
    
  // i/o methods
  //
  int32 sofSize() const{
    return (curr_data_d.sofSize() + curr_labels_d.sofSize()+curr_fname_d.sofSize());
  }
  bool8 read(Sof& sof, int32 tag, const String& name = PARAM_RECORD);
  bool8 write(Sof& sof, int32 tag, const String& name = PARAM_RECORD) const;
  
  bool8 readData(Sof& sof, const String& pname = DEF_PARAM,
		   int32 size = SofParser::FULL_OBJECT,
		   bool8 param = true,
		   bool8 nested = false);
  bool8 writeData(Sof& sof, const String& param = DEF_PARAM) const;
  
  
  
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
  //bool8 clear(Integral::CMODE ctype_a = Integral::DEF_CMODE);


  //---------------------------------------------------------------------------
  //
  // class-specific public methods:
  //  extensions to required methods
  //
  //---------------------------------------------------------------------------
  
  // method: constructor
  //
  
  //---------------------------------------------------------------------------
  //
  // class-specific public methods:
  //  
  //
  //---------------------------------------------------------------------------
  // get number of records
  //
  long get_records_no(){ 
    return records_no_d;
  }

  // set maximum buffer size
  //
  bool8 set_max_buff_size(long bsize){
    MAX_BUFF_SIZE = bsize;

    // return
    //
    return true;

  }

  // get max buffer size
  //
  long get_max_buff_size(){
    return MAX_BUFF_SIZE;
  }

  // init the buffer
  //
  bool8 init(String fname);

  // get data succesively  from the buffer
  // the result will be saved in curr_data and curr_labels
  //
  bool8 get();

  // get data by index
  //
  bool8 get(int32 index);

  // put  data successively into the file
  // the data should be saven in curr_data and cur_labels
  //
  bool8 put(Sof & sof_a);
  

  
  // read from HTK  files
  //
  bool8 read_HTK(String filename,int32 start_frame,int32 end_frame);

  //---------------------------------------------------------------------------
  //
  // class-specific public methods:
  //  initialization and computation methods
  //
  //---------------------------------------------------------------------------
    
  //---------------------------------------------------------------------------
  //
  // private methods
  //
  //---------------------------------------------------------------------------
 private:

  // fill the buffer from Sof file
  // This function read the from begining of the file
  //
  bool8 readFrom(long offset = 0);

  
};

// end of include file
//
#endif
