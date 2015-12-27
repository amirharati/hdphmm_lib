// file: $isip/class/shell/Sdb/sdb_04.cc
// version: $Id: sdb_04.cc 6807 2001-04-24 15:28:14Z peng $
//

// isip include files
//
#include "Sdb.h"

// method: sofSize
//
// arguments: none
//
// return: size of object as written to disk via the i/o methods
//
// this method determines the size of the object on disk
//
int32 Sdb::sofSize() const {
  
  // declare temporary variables
  //
  int32 new_size;
  new_size = files_d.sofSize();

  // exit gracefully
  //
  return new_size;
}

// method: write
//
// arguments:
//  Sof& sof: (input) sof file object
//  int32 tag: (input) sof object instance tag
//  const String& name: (input) sof object instance name
//
// return: a bool8 value indicating status
//
// this method has the object write itself to an Sof file
//
bool8 Sdb::write(Sof& sof_a, int32 tag_a, const String& name_a) const {

  // declare local variables
  //
  int32 obj_size;

  // set the object size to be "-1" in case of text and sofSize in
  // case of binary files
  //
  if (sof_a.isText()) {
    obj_size = Sof::ANY_SIZE;
  }
  else {
    obj_size = sofSize();
  }
  
  // put the object into the sof file's index
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
// return: a bool8 value indicating status
//
// this method has the object write itself to an Sof file. it assumes
// that the Sof file is already positioned correctly.
//
bool8 Sdb::writeData(Sof& sof_a, const String& pname_a) const {
  
  // different for text or binary -- text mode will write out the
  // files one per line.
  //
  if (sof_a.isText()) {
    
    Filename new_file;
    String buffer;
    String newline(L"\n");

    // use the mark to preserve location
    //
    const_cast<Sdb*>(this)->files_d.setMark();

    if (const_cast<Sdb*>(this)->files_d.gotoFirst()) {
      do {
	const Filename* ptr = &(files_d.getCurr()->first());
	
	if (!sof_a.puts(*ptr)) {
	  return Error::handle(name(), L"writeData", Error::WRITE,
			       __FILE__, __LINE__, Error::WARNING);
	  return false;
	}
	if (!sof_a.puts(newline)) {
	  return Error::handle(name(), L"writeData", Error::WRITE,
			       __FILE__, __LINE__, Error::WARNING);
	  return false;
	}
      } while (const_cast<Sdb*>(this)->files_d.gotoNext());
    }

    // restore location with the mark
    //
    const_cast<Sdb*>(this)->files_d.gotoMark();
  }

  // for binary files use standard Sof
  //
  else {
    files_d.writeData(sof_a, pname_a);
  }

  // exit gracefully
  //
  return true;
}
