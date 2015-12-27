// file: $isip/class/...
// version: $Id: database_03.cc 7/10/2013
//

// isip include files
//
#include "Database.h"
#include <Sof.h>

// method: read
//
// arguments:
//  Sof& sof: (input) sof file object
//  int32 tag: (input) sof object instance tag
//  const String& name: (input) sof object instance name
//
// return: a bool8 indicating status
//
// this method has the object read itself from an Sof file
//
bool8 Database::read(Sof& sof_a, int32 tag_a, const String& name_a) {

  // get the instance of the object from the Sof file
  //
  if (!sof_a.find(name_a, tag_a)) {
    return false;
  }

  // read the actual data from the sof file
  //
  return readData(sof_a,name_a);
}

// method: readData
//
// arguments:
//  Sof& sof: (input) sof file object
//  const String& pname: (input) parameter name
//  int32 size: (input) number of bytes in file
//  bool8 param: (input) is the parameter specified?
//  bool8 nested: (input) is this nested?
//
// return: logical error status
//
// this method has the object read itself from an Sof file. it assumes
// that the Sof file is already positioned correctly.
//
bool8 Database::readData(Sof& sof_a, const String& pname_a,
				    int32 size_a,
				    bool8 param_a, bool8 nested_a) {

Integral::DEBUG debug_level = Integral::NONE;

  SofParser parser;

  parser.setDebug(debug_level);
    
  // ignore implicit parameter setting
  //
  
  // are we nested?
  //
  if (nested_a) {
    parser.setNest();
  }

  // load the parse
  //
  if (!parser.load(sof_a, size_a)) {
    return Error::handle(name(), L"readData", Error::READ,
			 __FILE__, __LINE__, Error::WARNING);
  }

  if (pname_a.eq(L"info")){
    String tmp;
    if(!tmp.readData(sof_a,L"database_type",parser.getEntry(sof_a,L"database_type"),true, false)) {
      return Error::handle(name(), L"readData", Error::READ,
			   __FILE__, __LINE__, Error::WARNING);
    }	   
   
    if(tmp.eq(L"DIRECT"))
      database_type_d = DIRECT;
    else if (tmp.eq(L"HTK"))
      database_type_d = HTK;
    else
      Error::handle(name(), L"readData", Error::READ,
		    __FILE__, __LINE__, Error::WARNING);
   
  }
  // if it a "record" field
  //
  if (pname_a.eq(PARAM_RECORD) && database_type_d == DIRECT){
  	    
    // for direct mode fr = 10 msec
    //
    db_fr_d = 10;
    
    // get the matrix of data
    //
    if (!data_temp_d.readData(sof_a, PARAM_DATA,
			      parser.getEntry(sof_a, PARAM_DATA),
			      true, true)) {
      return Error::handle(name(), L"readData", Error::READ,
			   __FILE__, __LINE__, Error::WARNING);
    }	    
  
    // get the vector of labels 
    //
    if (!labels_temp_d.readData(sof_a, PARAM_LABELS,
				parser.getEntry(sof_a, PARAM_LABELS),
				true, true)) {
      return Error::handle(name(), L"readData", Error::READ,
			   __FILE__, __LINE__, Error::WARNING);
    }
    fname_temp_d.assign(L"****");
  }
  else if (pname_a.eq(PARAM_RECORD) && database_type_d == HTK){
    String filename;
    Long st_fr;
    Long en_fr;
   
    if (!filename.readData(sof_a, L"file_name",
				parser.getEntry(sof_a, L"file_name"),
				true, true)) {
      return Error::handle(name(), L"readData", Error::READ,
			   __FILE__, __LINE__, Error::WARNING);
    }
      if (!st_fr.readData(sof_a, L"start_frame",
			  parser.getEntry(sof_a, L"start_frame"),
			  true, true)) {
	return Error::handle(name(), L"readData", Error::READ,
			     __FILE__, __LINE__, Error::WARNING);
      }
      
      if (!en_fr.readData(sof_a, L"end_frame",
			  parser.getEntry(sof_a, L"end_frame"),
			  true, true)) {
	return Error::handle(name(), L"readData", Error::READ,
			     __FILE__, __LINE__, Error::WARNING);
      }
      fname_temp_d.assign(filename);
      read_HTK(filename,st_fr,en_fr);

  }

  // exit gracefully
  //
  return true;

}

// method: write
//
// arguments:
//  Sof& sof: (input) sof file object
//  int32 tag: (input) sof object instance tag
//  const String& name: (input) sof object instance name
//
// return: bool8 value indicating status
//
// this method has the object write itself to an Sof file
//
bool8 Database::write(Sof& sof_a, int32 tag_a,
			     const String& name_a) const {

  int32 obj_size = 0;
  
  // write the instance of the object into the Sof file
  //
  if (sof_a.isText()) {

    // set the size to by dynamic
    //
    obj_size = Sof::ANY_SIZE;
  }
  else {

    // the size index and the size of each element
    //
    obj_size = sofSize();
  }

  // write the object into the sof file's index
  //
  if (!sof_a.put(name_a, tag_a, obj_size)) {
    return false;
  }
  
  // exit gracefully
  //
  return writeData(sof_a);
}

// method: writeData
//
// arguments:
//  Sof& sof: (input) sof file object
//  const String& pname: (input) parameter name
//
// return: bool8 value indicating status
//
// this method has the object write itself to an Sof file. it assumes
// that the Sof file is already positioned correctly.
//
bool8 Database::writeData(Sof& sof_a, const String& pname_a) const {

  // write  data and labels
  //
  if(!curr_data_d.writeData(sof_a,PARAM_DATA))
    return Error::handle(name(), L"writeData", Error::WRITE,
			 __FILE__, __LINE__, Error::WARNING);

  if(! curr_labels_d.writeData(sof_a,PARAM_LABELS))
    return Error::handle(name(), L"writeData", Error::WRITE,
			 __FILE__, __LINE__, Error::WARNING);

  return true;
}
