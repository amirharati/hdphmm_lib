// file: $isip/class/io/Sof/sof_07.cc
// version: $Id: sof_07.cc 4958 2000-09-22 21:35:19Z zhao $
//

// isip include files
//
#include "Sof.h"

// method: put
//
// arguments:
//  const SysString& name: (input) object name
//  int32 size: (input) object size
//
// return: a bool8 value indicating status
//
// put this entry into the file. if it doesn't exist, add it.
//
bool8 Sof::put(const SysString& name_a, int32 size_a) {
  
  // check command line arguments
  //
  if (file_type_d == File::BINARY) {
    return Error::handle(name(), L"put", ERR_BINARY, __FILE__, __LINE__);
  }

  // no need to check if it already exists, all implicitly tagged
  // items are new
  //
  if (!add(name_a, size_a)) {
    return Error::handle(name(), L"put", Error::IO, __FILE__, __LINE__);
  }
  
  // exit gracefully
  //
  return true;
}

// method: put
//
// arguments:
//  const SysString& name: (input) object name
//  int32 tag: (input) object tag
//  int32 size: (input) object size
//
// return: a bool8 value indicating status
//
// put this entry into the file. if it doesn't exist, add it.
//
bool8 Sof::put(const SysString& name_a, int32 tag_a, int32 size_a) {

  // check arguments
  //
  if ((file_type_d == File::BINARY) && (size_a < 0)) {
    return Error::handle(name(), L"put", Error::ARG, __FILE__, __LINE__);
  }

  if (tag_a == FREE_TAG) {
    return put(name_a, size_a);
  }
  else if (tag_a < FREE_TAG) {
    Error::handle(name(), L"put", Error::ARG, __FILE__, __LINE__);
  }
  
  // determine if the name.tag already exists
  //
  if (find(name_a, tag_a)) {

    // it exists, do we know the size
    //
    if (size_a < 0) {
      
      // size not specified, delete and re-insert at end
      //
      if (!remove(name_a, tag_a)) {
	return Error::handle(name(), L"put", Error::IO, __FILE__, __LINE__);
      }
      if (!add(name_a, -1, tag_a)) {
	return Error::handle(name(), L"put", SofList::ERR, __FILE__, __LINE__);
      }
    }
    else {
      
      // for efficiency, delete and re-insert at end
      //
      if (!remove(name_a, tag_a)) {
	return Error::handle(name(), L"put", Error::IO, __FILE__, __LINE__);
      }
      if (!add(name_a, size_a, tag_a)) {
	return Error::handle(name(), L"put", SofList::ERR, __FILE__, __LINE__);
      }
    }
  }
  else {

    // new entry
    //
    if (!add(name_a, size_a, tag_a)) {
      return Error::handle(name(), L"put", Error::IO, __FILE__, __LINE__);
    }
  }
  
  // exit gracefully
  //
  return true;
}

// method: add
//
// arguments:
//  const SysString& name: (input) object name
//  int32 size: (input) object size
//  int32 tag: (input) object tag
//
// return: an int32 value containing the position of the object in the index
//
// add a new instance of specified class to the file
//
bool8 Sof::add(const SysString& name_a, int32 size_a, int32 tag_a) {

  // add to the symbol table
  //
  int32 index = table_d.add(name_a);
  
  if (index == SofSymbolTable::NO_SYMB) {
    return Error::handle(name(), L"add", SofSymbolTable::ERR,
			 __FILE__, __LINE__);
  }
		  
  // call the master function
  //
  return add(index, size_a, tag_a);
}

// method: add
//
// arguments:
//  int32 name: (input) object name
//  int32 size: (input) object size
//  int32 tag: (input) object tag
//
// return: an int32 value containing the position of the object in the index
//
// add a new instance of specified class to the file
//
bool8 Sof::add(int32 name_a, int32 size_a, int32 tag_a) {

  // make sure we are not in partial write mode
  //
  if (partial_write_d) {
    return Error::handle(name(), L"add", ERR_PARTIAL, __FILE__, __LINE__);
  }
  
  // write the tag to the file
  //
  int32 pos = 0;

  // check the tag for the implicit flag
  //
  if (tag_a == FREE_TAG) {
    tag_a = implicit_count_d++;

    // check to make sure we didn't overflow
    //
    if (implicit_count_d > IMPLICIT_END) {
      Error::handle(name(), L"add", ERR_IMPLIC, __FILE__, __LINE__,
		    Error::WARNING);
      
      // recover from error
      //
      table_d.remove(name_a);
      implicit_count_d--;
      return false;
    }
  }
  
  if (index_d.add(name_a, tag_a, (int32)-1, size_a)) {
    
    if (file_type_d == File::TEXT) {
      
      // NOTE: future editions might do there own garbage collecting and
      // add items back into the middle of the file if convenient
      //
      if (!fseek(0, File::POS_PLUS_END)) {
	return Error::handle(name(), L"add", Error::SEEK, __FILE__, __LINE__);
      }

      // save the position
      //
      pos = ftell();
      
      // write the label to the file at the current position
      //
      if (!writeLabel(name_a, tag_a)) {
	Error::handle(name(), L"add", ERR_LABEL, __FILE__, __LINE__);
      }

      // set current data pointer
      //
      cur_data_d = ftell();
    }
    else {
      
      // seek to the end of the data segment
      //
      if (!fseek(end_of_data_d, File::POS)) {
	return Error::handle(name(), L"add", Error::SEEK, __FILE__, __LINE__);
      }

      // save the positions
      //
      pos = ftell();
      cur_data_d = pos;
      end_of_data_d += size_a;
    }
    
    // now fill the space with nulls if size was specified
    //
    if (size_a > 0) {
      if (!clearSpace(size_a)) {
	return Error::handle(name(), L"add", Error::IO, __FILE__, __LINE__);
      }
      if (!fseek(-size_a, File::POS_PLUS_CUR)) {
	return Error::handle(name(), L"add", Error::SEEK, __FILE__, __LINE__);
      }
    }
    
    // set the position in the index
    //
    if (!index_d.setPosition(pos)) {
      return Error::handle(name(), L"add", Error::INTERNAL_DATA,
			   __FILE__, __LINE__);
    }
  }
  else {
    Error::handle(name(), L"add", SofList::ERR, __FILE__, __LINE__,
		  Error::WARNING);
    
    // recover from warning
    //
    table_d.remove(name_a);
    return false;
  }
  
  // exit gracefully
  //
  return true;
}

// method: remove
//
// arguments:
//  const SysString& name: (input) class name 
//  int32 tag: (input) object tag
//
// return: a bool8 value indicating status
//
// remove specified object from Sof file
//
bool8 Sof::remove(const SysString& name_a, int32 tag_a) {

  // get the index of the name from symbol table
  //
  int32 oname = table_d.getIndex(name_a);
  
  if (oname < 0) {
    return Error::handle(name(), L"remove", SofSymbolTable::ERR_NOTFND,
			 __FILE__, __LINE__);
  }
  
  // call the master function
  //
  return remove(oname, tag_a);
}

// method: remove
//
// arguments:
//  int32 name: (input) class name 
//  int32 tag: (input) object tag
//
// return: a bool8 value indicating status
//
// remove specified object from Sof file
//
bool8 Sof::remove(int32 name_a, int32 tag_a) {

  // check the file mode
  //
  if (!fp_d.isWritable()) {
    return Error::handle(name(), L"remove", Error::MOD_READONLY,
			 __FILE__, __LINE__);
  }

  // make sure we are not in partial write mode
  //
  if (partial_write_d) {
    return Error::handle(name(), L"remove", ERR_PARTIAL, __FILE__, __LINE__);
  }

  // find the current entry
  //
  if (!index_d.find(name_a, tag_a)) {
    return Error::handle(name(), L"remove", ERR_NOOBJ,
			 __FILE__, __LINE__, Error::WARNING);
  }
  
  // seekData is called here because we circumvented the normal Sof
  // indexing (which automatically positions)
  //
  if (!seekData()) {
    return Error::handle(name(), L"remove", Error::SEEK, __FILE__, __LINE__);
  }

  int32 obj_size = index_d.getSize();
  int32 obj_pos = index_d.getPosition();
  
  int32 tag_size = ftell() - index_d.getPosition();

  if (!fseek(-tag_size, File::POS_PLUS_CUR)) {
    return Error::handle(name(), L"remove", Error::SEEK, __FILE__, __LINE__);
  }
  
  if (!clearSpace(tag_size + getObjectSize())) {
    return Error::handle(name(), L"remove", Error::WRITE, __FILE__, __LINE__);
  }

  if (isBinary() && ((obj_size + obj_pos) == end_of_data_d)) {
    end_of_data_d -= obj_size;
  }
  
  // delete instance of name from the symbol table
  //
  if (!table_d.remove(name_a)) {
    return Error::handle(name(), L"remove", SofSymbolTable::ERR,
			 __FILE__, __LINE__);
  }

  // remove node from index list
  //
  if (!index_d.remove()) {
    return Error::handle(name(), L"remove", SofList::ERR, __FILE__, __LINE__);
  }
  
  // exit gracefully
  //
  return true;
}

// method: remove
//
// arguments:
//  const SysString& name: (input) class name to delete
//
// return: a bool8 value indicating status
//
// this method deletes all objects of the specified name from the sof file.
//
bool8 Sof::remove(const SysString& name_a) {
  
  // find the name in the symbol table
  //
  int32 oname = table_d.getIndex(name_a);
  
  if (oname < 0) {
    return Error::handle(name(), L"remove", SofSymbolTable::ERR_NOTFND,
			 __FILE__, __LINE__);
  }

  // call the master function
  //
  return remove((int32)oname);
}

// method: remove
//
// arguments:
//  int32 name: (input) class name to delete
//
// return: a bool8 value indicating status
//
// this method deletes all objects of the specified name from the sof
// file.
//
bool8 Sof::remove(int32 name_a) {

  // check argument
  //
  if (name_a == SofSymbolTable::NO_SYMB) {
    return Error::handle(name(), L"remove", Error::ARG, __FILE__, __LINE__);
  }
  
  // check mode
  //
  if (!fp_d.isWritable()) {
    return Error::handle(name(), L"remove", Error::MOD_READONLY,
			 __FILE__, __LINE__);
  }
  
  // find the first tag
  //
  int32 tag = index_d.first(name_a);

  while (tag != NO_TAG) {
    if (!remove(name_a, tag)) {
      return Error::handle(name(), L"remove", SofList::ERR_DELETE,
			   __FILE__, __LINE__);
    }
    tag = index_d.next(name_a, tag);
  }
  
  // exit gracefully
  //
  return true;
}

// method: copy
//
// arguments:
//  int32 new_obj_tag: (input) destination file object tag
//  Sof& sof: (input) file object from which to copy
//  const SysString& obj_name: (input) class name to copy
//  int32 obj_tag: (input) object tag
//
// return: a bool8 value indicating status
//
// copy a single object from one sof object to another sof object
//
bool8 Sof::copy(int32 new_obj_tag_a, Sof& sof_a, const SysString& obj_name_a,
		  int32 obj_tag_a) {
  
  int32 oname = sof_a.table_d.getIndex(obj_name_a);

  if (name < 0) {
    return Error::handle(name(), L"copy", SofSymbolTable::ERR_NOTFND,
			 __FILE__, __LINE__);
  }
		    
  // call the master function
  //
  return copy(new_obj_tag_a, sof_a, oname, obj_tag_a);
}

// method: copy
//
// arguments:
//  int32 new_obj_tag: (input) destination file object tag
//  Sof& sof: (input) file object from which to copy
//  int32 obj_name: (input) class name to copy
//  int32 obj_tag: (input) object tag
//
// return: a bool8 value indicating status
//
// copy a single object from one sof object to another sof object
//
bool8 Sof::copy(int32 new_obj_tag_a, Sof& sof_a, int32 obj_name_a,
		  int32 obj_tag_a) {
  
  if (file_type_d != sof_a.file_type_d) {
    return Error::handle(name(), L"copy", Error::ARG, __FILE__, __LINE__);
  }

  // make sure we are not in partial write mode
  //
  if (partial_write_d) {
    return Error::handle(name(), L"copy", ERR_PARTIAL, __FILE__, __LINE__);
  }

  // find this object in the source file
  //
  if (!sof_a.index_d.find(obj_name_a, obj_tag_a)) {
    return false;
  }
  
  // position files
  //
  if (!fseek(0, File::POS_PLUS_END)) {
    return Error::handle(name(), L"copy", Error::SEEK, __FILE__, __LINE__);
  }

  // seekData is called here because we circumvented the normal Sof
  // indexing (which automatically positions)
  //
  if (!sof_a.seekData()) {
    return Error::handle(name(), L"copy", Error::SEEK, __FILE__, __LINE__);
  }

  int32 size = sof_a.getObjectSize();
  
  SysString obj_name_str;
  if (!sof_a.table_d.getSymbol(obj_name_str, obj_name_a)) {
    return Error::handle(name(), L"copy", Error::ARG, __FILE__, __LINE__);
  }
  
  // add this object to the new file
  //
  if (!add(obj_name_str, size, new_obj_tag_a)) {
    return Error::handle(name(),L"copy",SofList::ERR_ADD,__FILE__,__LINE__);
  }

  // now copy the actual data
  //
  byte8* buffer[sof_a.index_d.getSize()];

  if (sof_a.fp_d.read(buffer, sizeof(byte8), size) != size) {
    return Error::handle(name(), L"copy", Error::READ, __FILE__, __LINE__);
  }

  if (isBinary()) {
    sof_a.cur_pos_d += size * sizeof(byte8);
  }
  
  if (fp_d.write(buffer, sizeof(byte8), size) != size) {
    return Error::handle(name(), L"copy", Error::WRITE, __FILE__, __LINE__);
  }

  if (isBinary()) {
    cur_pos_d += size * sizeof(byte8);
  }

  // exit gracefully
  //
  return true;
}

// method: copy
//
// arguments:
//  Sof& sof: (input) file object from which to copy
//  const SysString& obj_name: (input) class name to copy
//
// return: a bool8 value indicating status
//
// copy all objects with specified name from one Sof file to another
//
bool8 Sof::copy(Sof& sof_a, const SysString& obj_name_a) {

  int32 oname = sof_a.table_d.getIndex(obj_name_a);
  if (name < 0) {
    return Error::handle(name(), L"copy", SofSymbolTable::ERR_NOTFND,
			 __FILE__, __LINE__);
  }

  // call the master function
  //
  return copy(sof_a, oname);
}

// method: copy
//
// arguments:
//  Sof& sof: (input) file object from which to copy
//  int32 name: (input) class name to copy
//
// return: a bool8 value indicating status
//
// copy all objects with specified name from one Sof file to another
//
bool8 Sof::copy(Sof& sof_a, int32 name_a) {

  // check the type
  //
  if (file_type_d != sof_a.file_type_d) {
    return Error::handle(name(), L"copy", Error::ARG, __FILE__, __LINE__);
  }

  if (name_a < 0) {
    return Error::handle(name(), L"copy", Error::ARG, __FILE__, __LINE__);
  }

  // find the tag
  //
  int32 tag = sof_a.index_d.first(name_a);
  
  while (tag != NO_TAG) {
    if (!copy(tag, sof_a, name_a, tag)) {
      return Error::handle(name(), L"copy", SofList::ERR_COPY,
			   __FILE__, __LINE__);
    }
    tag = sof_a.index_d.next(name_a, tag);
  }
  
  // exit gracefully
  //
  return true;
}

// method: getObjectSize
//
// arguments:
//  const SysString& name: (input) class name
//  int32 tag: (input) class tag
//
// return: int32 value
//
// the size of the current object
//
int32 Sof::getObjectSize(const SysString& name_a, int32 tag_a) {
  
  // make sure we are not in partial write mode
  //
  if (partial_write_d) {
    return Error::handle(name(), L"getObjectSize", ERR_PARTIAL,
			 __FILE__, __LINE__);
  }

  // find the object
  //
  if (!index_d.find(table_d.getIndex(name_a), tag_a)) {
    Error::handle(name(), L"getObjectSize", ERR_NOOBJ,
		  __FILE__, __LINE__);
    return (int32)-1;
  }
  
  // call the master function
  //
  return getObjectSize();
}

// method: getObjectSize
//
// arguments: none
//
// return: int32 value
//
// find the size of this object
//
int32 Sof::getObjectSize() {
  
  int32 size = index_d.getSize();

  if (size >= 0) {
    return size;
  }

  // for a text file, if no size is specified we must figure it out
  //
  if (!isText()) {
    Error::handle(name(), L"getObjectSize", SofList::ERR, __FILE__, __LINE__);
    return (int32)-1;
  }
				     
  // save the current position
  //
  int32 prev_pos = ftell();
  
  // seek to the beginning of the data
  //
  if ((prev_pos != cur_data_d) && (!rewind())) {
    Error::handle(name(), L"getObjectSize", Error::SEEK, __FILE__, __LINE__);
    return -1;
  }
  
  SysString buf;
  SysString temp_name;
  int32 temp_tag;
  int32 cur_line_pos = cur_data_d;
  
  // seek to the next tag. we use repeated calls to ftell rather than
  // trying to add up the length of the string to increase machine
  // independence. remember that some operating systems use a two byte
  // sequence for newlines, we'd rather not have to worry about it and
  // use the low level text fgets function instead. getBin is used
  // rather than get so that preceding null characters will be
  // skipped in looking for the newline character.
  //
  while (fp_d.get(buf)) {
    
    // is this line a label ??
    //
    if (parseLabel(temp_name, temp_tag, buf)) {
      break;
    }
    
    // save the position of the beginning of this next line
    //
    cur_line_pos = ftell();
  }

  // set the size
  //
  size = cur_line_pos - cur_data_d;

  // possibly seek back to the previous position
  //
  if ((prev_pos != cur_data_d) &&
      (!fseek(prev_pos, File::POS))) {
    Error::handle(name(), L"getObjectSize", Error::SEEK, __FILE__, __LINE__);
    return (int32)-1;
  }

  // return the size
  //
  return size;
}
