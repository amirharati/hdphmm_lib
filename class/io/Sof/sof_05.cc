// file: $isip/class/io/Sof/sof_05.cc
// version: $Id: sof_05.cc 5643 2000-11-21 19:50:11Z duncan $
//

// isip include files
//
#include "Sof.h"
#include <Console.h>
#include <MemoryManager.h>

// method: readIndex
//
// arguments: none
//
// return: a bool8 value indicating status
//
// this method reads the index
// note: this needs to be able to compress the symbol table if necessary
//
bool8 Sof::readIndex() {
  
  // read all the objects to the file in binary form
  //
  // the format:
  //  1 byte8 offset to the next entry
  //  4 byte8 position
  //  4 byte8 tag number
  //  4 byte8 size
  //  4 byte8 name index
  //
  //  note that the size of 4 bytes is hardcoded for integers. This is
  //  to facilitate the possibility of different word-length
  //  architectures that will grow into the environment.
  //
  //  for now we just read and write the information, upgrade this to
  //  a true read/write of 4 byte info in the future.
  //
  byte8 entry_buffer[BUFFER_SIZE];
  int32 buf_size = (int32)-1;
  byte8 size = (byte8)0;
  int32 ptr = (int32)0;

  int32 object_tag = (int32)-1;
  int32 object_pos = (int32)-1;
  int32 object_size = (int32)-1;
  int32 object_name = (int32)-1;

  // use the lowest level read, since we decode things by hand
  //
  while((buf_size = fp_d.read(entry_buffer, sizeof(byte8), BUFFER_SIZE)) > 0) {

    // increment position
    //
    cur_pos_d += buf_size * sizeof(byte8);
    
    ptr = 0;
    
    // while we have the minimum number of bytes for an entry
    //
    while ((buf_size - ptr) >= INDEX_SIZE) {
      
      // the first byte of each entry is the size
      //
      size = entry_buffer[ptr + INDEX_OFFSET_NEXT];

      // sanity check on the size
      //
      if (size < INDEX_SIZE) {
	return Error::handle(name(), L"readIndex", ERR_STRUCT,
			     __FILE__, __LINE__, Error::WARNING);
      }

      // read the fields from the binary index
      //
      MemoryManager::memcpy(&object_pos, &entry_buffer[ptr+INDEX_OFFSET_POS],
			    sizeof(int32));
      MemoryManager::memcpy(&object_tag, &entry_buffer[ptr+INDEX_OFFSET_TAG],
			    sizeof(int32));
      MemoryManager::memcpy(&object_size,&entry_buffer[ptr+INDEX_OFFSET_SIZE],
			    sizeof(int32));
      MemoryManager::memcpy(&object_name,&entry_buffer[ptr+INDEX_OFFSET_NAME],
			    sizeof(int32));

      // determine the checksum of the entry
      //
      cksm_d.compute(&entry_buffer[ptr + INDEX_OFFSET_POS], 4 * sizeof(int32));

      // set the fields in the index array
      //
      index_d.add((int32)fp_d.decode(object_name),
		  (int32)fp_d.decode(object_tag),
		  (int32)fp_d.decode(object_pos),
		  (int32)fp_d.decode(object_size));

      // increment the pointer
      //
      ptr += size;
    }
  }
  
  // exit gracefully
  //
  return true;
}

// method: writeIndex
//
// arguments: none
//
// return: a bool8 value indicating status
//
// this method writes the index
//
bool8 Sof::writeIndex() {

  // write all the objects to the file in binary form
  //
  // the format:
  //  1 byte8 offset to the next entry
  //  4 byte8 position
  //  4 byte8 tag number
  //  4 byte8 size
  //  4 byte8 name index
  //
  //  note that the size of 4 bytes is hardcoded for integers. This is
  //  to facilitate the possibility of different word-length
  //  architectures that will grow into the environment.
  //
  //  for now we just read and write the information, upgrade this to
  //  a true read/write of 4 byte info in the future.
  //
  byte8 entry_buffer[BUFFER_SIZE];
  MemoryManager::memset(entry_buffer, 0, BUFFER_SIZE);

  byte8 size = (byte8)INDEX_SIZE;
  int32 ptr = (int32)0;
  byte8 *last_size = &entry_buffer[INDEX_OFFSET_NEXT];

  // loop through all classes
  //
  for (int32 cname = getNameCount() - 1; cname >= 0; cname--) {

    // loop through all instances of this class
    //
    for (int32 tag = index_d.first(cname); tag != NO_TAG;
	 tag = index_d.next(cname, tag)) {

      // if we have a full buffer, write it
      //
      if ((ptr + INDEX_SIZE) > BUFFER_SIZE) {

	// increase last_size so that read will skip over empty pad
	//
	(*last_size) += (BUFFER_SIZE - ptr);

	// write the buffer (we don't want byte swapping, use lowest
	// level write).
	//
	if (fp_d.write(entry_buffer,sizeof(byte8),BUFFER_SIZE) != BUFFER_SIZE) {
	  return Error::handle(name(), L"writeIndex", Error::WRITE,
			       __FILE__, __LINE__);
	}

	cur_pos_d += BUFFER_SIZE * sizeof(byte8);
	
	// clear out the buffer and initialize pointer
	//
	MemoryManager::memset(entry_buffer, 0, BUFFER_SIZE);
	ptr = 0;
      }

      // encode values for this entry
      //
      int32 object_name = fp_d.encode((int32)cname);
      int32 object_tag = fp_d.encode((int32)tag);
      int32 object_pos = fp_d.encode((int32)index_d.getPosition());
      int32 object_size = fp_d.encode((int32)index_d.getSize());
      
      // build the binary index entry
      //
      MemoryManager::memcpy(&entry_buffer[ptr + INDEX_OFFSET_POS],
			    &object_pos, sizeof(int32));
      MemoryManager::memcpy(&entry_buffer[ptr + INDEX_OFFSET_TAG],
			    &object_tag, sizeof(int32));
      MemoryManager::memcpy(&entry_buffer[ptr + INDEX_OFFSET_SIZE],
			    &object_size, sizeof(int32));
      MemoryManager::memcpy(&entry_buffer[ptr + INDEX_OFFSET_NAME],
			    &object_name, sizeof(int32));
      entry_buffer[ptr + INDEX_OFFSET_NEXT] = (byte8)size;

      // compute the checksum for this entry
      //
      cksm_d.compute(&entry_buffer[ptr+INDEX_OFFSET_POS], 4 * sizeof(int32));
      
      // set the last size pointer for the next time around
      //
      last_size = &entry_buffer[ptr + INDEX_OFFSET_NEXT];

      // increment pointer
      //
      ptr += INDEX_SIZE;
    }
  }

  // if there are entries left over, write them out
  //
  if (ptr > 0) {
    if (fp_d.write(entry_buffer, sizeof(byte8), ptr) != ptr) {
      return Error::handle(name(), L"writeIndex", Error::WRITE,
			   __FILE__, __LINE__);
    }
    cur_pos_d += ptr * sizeof(byte8);
  }
  
  // exit gracefully
  //
  return true;
}

// method: readTable
//
// arguments: none
//
// return: a bool8 value indicating status
//
// this method reads the symbol table. note how nasty such functions
// are, dealing with low level byte ordering and such. This is why all
// code people use is written ABOVE Sof.
//
bool8 Sof::readTable() {

  // read all the objects to the file in binary form
  //
  // the format:
  //  1 byte8 offset to the next entry
  //  4 byte8 position
  //  4 byte8 tag number
  //  <246 byte8 null terminated string for the name
  //
  //  note that the size of 4 bytes is hardcoded for integers. This is
  //  to facilitate the possibility of different word-length
  //  architectures that will grow into the environment.
  //
  //  for now we just read and write the information, upgrade this to
  //  a true read/write of 4 byte info in the future.
  //
  byte8 entry_buffer[BUFFER_SIZE];
  byte8 size = (byte8)0;
  int32 ptr = (int32)sizeof(int32);
  int32 buf_size;
  int32 num_classes = (int32)-1;
  int32 num = (int32)0;
  int32 object_index;
  int32 object_refs;
  byte8* object_name;
  SysString name_str;
  int16 encoding_int;	// this is unicode encoding, not byte order
  SysChar::ENCODE encoding;

  MemoryManager::memset(entry_buffer, 0, BUFFER_SIZE);

  // keep track of file position for error messages
  //
  int32 file_pos = ftell();
  
  // the number of classes is the first thing in the table's binary space
  //  cur_pos_d updated inside the do/while loop
  //
  buf_size = fp_d.read(entry_buffer, sizeof(byte8), BUFFER_SIZE);
  MemoryManager::memcpy(&num_classes, entry_buffer, sizeof(int32));
  
  // read what encoding we should read
  //
  MemoryManager::memcpy(&encoding_int, &entry_buffer[ptr], sizeof(int16));
  
  ptr += sizeof(int16);
  
  // decode the values
  //
  num_classes = fp_d.decode(num_classes);
  encoding_int = fp_d.decode(encoding_int);
  encoding = (SysChar::ENCODE)encoding_int;
  
  if ((buf_size < ptr) || (num_classes < 0)) {
    return Error::handle(name(), L"readTable", ERR_STRUCT,
			 __FILE__, __LINE__, Error::WARNING);
  }
  
  if (debug_level_d > Integral::BRIEF) {
    SysString output;
    output.assign((int32)num_classes);
    output.insert(L"<Sof::readTable> Reading ", 0);
    output.concat(L" table entries");
    Console::put(output);
  }

  // since we needed that first 4 bytes for the table size, we need to
  // use a do loop for the rest of the data.
  //
  do {

    // increment cur_pos
    //
    cur_pos_d += buf_size * sizeof(byte8);
    
    while (((buf_size - ptr) >= SYMBOL_BASE) && (num < num_classes)) {

      // the first byte of each entry is the size
      //
      size = entry_buffer[ptr + SYMBOL_OFFSET_NEXT];
      
      // sanity check on the size
      //
      if (size < SYMBOL_BASE) {
	return Error::handle(name(), L"readTable", ERR_STRUCT,
			     __FILE__, __LINE__, Error::WARNING);
      }

      // read the fields from the binary index
      //
      MemoryManager::memcpy(&object_index,
			    &entry_buffer[ptr + SYMBOL_OFFSET_IND],
			    sizeof(int32));
      MemoryManager::memcpy(&object_refs,
			    &entry_buffer[ptr + SYMBOL_OFFSET_REFS],
			    sizeof(int32));
      object_name = &entry_buffer[ptr + SYMBOL_OFFSET_NAME];

      // assign the name string
      //
      name_str.assign(object_name, SysString::BIG_BUFFER_LENGTH, encoding);

      // note that this is NOT UNICODE SAFE
      //
      int32 slen = name_str.length();

      // compute the checksum
      //
      cksm_d.compute(&entry_buffer[ptr + SYMBOL_OFFSET_IND],
		     2 * sizeof(int32) + slen);

      // add the entry into the symbol table
      //
      table_d.add((int32)fp_d.decode(object_index),
		       (int32)fp_d.decode(object_refs), name_str);

      // increment pointers and counters
      //
      ptr += size;
      num++;
    }

    // once we have the last entry, reset pointer
    //
    if (num < num_classes) {
      ptr = 0;
    }

    // keep reading data until we have all the classes read in
    //
  }
  while ((num < num_classes) &&
	 ((buf_size =
	   fp_d.read(entry_buffer, sizeof(byte8), BUFFER_SIZE)) > 0)
	 && (file_pos = ftell()));
  
  // seek back to the end of the table
  //
  if (!fseek(ptr - buf_size, File::POS_PLUS_CUR)) {
    return Error::handle(name(), L"readTable", Error::SEEK,
			 __FILE__, __LINE__, Error::WARNING);
  }

  // exit gracefully
  //
  return true;
}

// method: writeTable
//
// arguments: none
//
// return: a bool8 value indicating status
//
// this method writes the symbol table. note how nasty such functions
// are, dealing with low level byte ordering and such. This is why all
// code people use is written ABOVE Sof.
//
bool8 Sof::writeTable() {

  // write the symbol table to the file
  //
  // the format:
  //  1 byte offset to the next entry
  //  4 byte index
  //  4 byte reference count
  //  <246 byte null terminated string for the name
  //
  //  note that the size of 4 bytes is hardcoded for integers. This is
  //  to facilitate the possibility of different word-length
  //  architectures that will grow into the environment.
  //
  //  for now we just read and write the information, upgrade this to
  //  a true read/write of 4 byte info in the future.
  //
  byte8 entry_buffer[BUFFER_SIZE];
  MemoryManager::memset(entry_buffer, 0, BUFFER_SIZE);

  byte8 size = (byte8)0;
  int32 ptr = (int32)sizeof(int32);

  // the first thing written is the size of the table
  //
  int32 num_classes = fp_d.encode((int32)table_d.getCount());
  MemoryManager::memcpy(entry_buffer, &num_classes, sizeof(int32));

  // write the encoding we will use (use ASCII until we support UTF8)
  //
  SysChar::ENCODE encoding = SysChar::ENCODE_ASCII;
  int16 encoding_int = (int16)encoding;
  int16 val = fp_d.encode(encoding_int);
  MemoryManager::memcpy(&entry_buffer[ptr], &val, sizeof(int16));
  ptr += sizeof(int16);
  
  // pointer to the last size entry
  //
  byte8 *last_size = &entry_buffer[ptr + SYMBOL_OFFSET_NEXT];
  
  // handle converting names from the symbol table to utf8 encoding
  //
  SysString name_str;
  int32 slen = 0;

  // we call this the max name length. it should allow ample room for
  // any utf8 characters to be expanded to full length
  //
  const int32 max_name_length = SofSymbolTable::MAX_SYM_LENGTH * 6;
  
  static byte8 name_buf[max_name_length];
  int32 count = 0;
  int32 refs = 0;
  int32 ind = 0;
  
  // loop through integers until all names are written
  //
  for (int32 i = 0; count < table_d.getCount(); i++) {

    // is this index a name?
    //
    if (table_d.getSymbol(name_str, i)) {

      // encode the values
      //
      refs = fp_d.encode((int32)table_d.getRefCount(name_str));
      ind = fp_d.encode((int32)i);
      count++;

      // encode the name_str
      //
      slen = name_str.getBuffer((byte8*)name_buf, max_name_length, encoding);
      size = SYMBOL_BASE + slen + 1;

      // if we have a full buffer, write it
      //
      if (ptr + size > BUFFER_SIZE) {

	// increase last_size so that read will skip over empty pad
	//
	(*last_size) += (BUFFER_SIZE - ptr);

	// write the buffer (we don't want byte swapping, use lowest
	// level write).
	//
	if (fp_d.write(entry_buffer,sizeof(byte8),BUFFER_SIZE) != BUFFER_SIZE) {
	  return Error::handle(name(), L"writeTable", Error::WRITE,
			       __FILE__, __LINE__);
	}
	cur_pos_d += BUFFER_SIZE * sizeof(byte8);
	
	// clear out the buffer and initialize pointer
	//
	MemoryManager::memset(entry_buffer, 0, BUFFER_SIZE);
	ptr = 0;
      }

      // build the binary entry
      //
      entry_buffer[ptr + SYMBOL_OFFSET_NEXT] = (byte8)size;
      MemoryManager::memcpy(&entry_buffer[ptr + SYMBOL_OFFSET_IND],
			    &ind, sizeof(int32));
      MemoryManager::memcpy(&entry_buffer[ptr + SYMBOL_OFFSET_REFS],
			    &refs, sizeof(int32));
      MemoryManager::memcpy(&entry_buffer[ptr + SYMBOL_OFFSET_NAME],
			    name_buf, slen);
      entry_buffer[ptr + SYMBOL_OFFSET_NAME + slen] = (byte8)NULL;

      // compute the checksum
      //
      cksm_d.compute(&entry_buffer[ptr + SYMBOL_OFFSET_IND],
		     2 * sizeof(int32) + slen);

      // set the last size pointer for the next time around
      //
      last_size = &entry_buffer[ptr + INDEX_OFFSET_NEXT];

      // increment pointer
      //
      ptr += size;
    }
  }

  // if there are entries left over, write them out
  //
  if (ptr > 0) {
    if (fp_d.write(entry_buffer, sizeof(byte8), ptr) != ptr) {
      return Error::handle(name(), L"writeTable", Error::WRITE,
			   __FILE__, __LINE__);
    }
    cur_pos_d += ptr * sizeof(byte8);
  }

  // exit gracefully
  //
  return true;
}

// method: isSof
//
// arguments: none
//
// return: a bool8 value indicating status
//
// check if the file is an Sof file. if it is, all values from the header are
// automatically read.
//
bool8 Sof::isSof() {

  // initialize strings
  //
  cname_d.clear();
  version_d.clear();
  magic_d.clear();

  // make sure the file is open
  //
  if (!fp_d.isReadable()) {
    return false;
  }
  
  // read the first line from the file
  //
  SysString buf;
  fp_d.rewind();
  fp_d.get(buf);
  
  // fetch the header
  //
  SysChar delim_beg, delim_end;

  // try to get the first delimiter char
  //
  int32 index0 = buf.firstNotSpace();
  int32 index1 = -1;
  if (index0 < 0) {
    return false;
  }
  delim_beg.assign(buf(index0));

  // try to get the class name (Sof)
  //
  index0 = buf.firstNotSpace(index0 + 1);
  index1 = buf.firstSpace(index0);
  if ((index0 < 0) || (index1 < 0)) {
    return false;
  }
  buf.substr(cname_d, index0, index1 - index0);

  // try to get the version
  //
  index0 = buf.firstNotSpace(index1 + 1);
  index1 = buf.firstSpace(index0);
  if ((index0 < 0) || (index1 < 0)) {
    return false;
  }
  buf.substr(version_d, index0, index1 - index0);

  // try to get either the delimiter or the magic string
  //
  index0 = buf.firstNotSpace(index1 + 1);
  if (index0 < 0) {
    return false;
  }

  // if this index is the last character on the line, then we are in
  // a text file and no magic string was specified.
  //
  if (buf.firstNotSpace(index0 + 1) < 0) {
    file_type_d = File::TEXT;

    delim_end = buf(index0);
  }

  // else this better be a binary sof file
  //
  else {
    
    file_type_d = File::BINARY;
    
    index1 = buf.firstSpace(index0);
    if ((index1 < 0) || ((index1 - index0) != BSTR_LEN)) {
      return false;
    }
    buf.substr(magic_d, index0, BSTR_LEN);
    
    index0 = buf.firstNotSpace(index1 + 1);
    if (index0 < 0) {
      return false;
    }
    
    // the delimiter should be the last character on the line
    //
    if (buf.firstNotSpace(index0 + 1) < 0) {
      delim_end = buf(index0);
    }
    else {
      return false;
    }

    // check byte mode
    //
    int32 x = 0;
    float32 y = 0;
    byte8 magic_buf[sizeof(x) + 1];
    
    magic_d.getBuffer((byte8*)magic_buf, sizeof(x) + 1);

    MemoryManager::memcpy(&x, magic_buf, sizeof(x));
    MemoryManager::memcpy(&y, magic_buf, sizeof(y));

    if (x == BCODE_NATIVE) {
      fp_d.setBMode(File::NATIVE);
    }
    else if (x == BCODE_SWAP) {
      fp_d.setBMode(File::SWAP);
    }
    else {
      return false;
    }

    // check floating point encoding
    //
    if ((y != IEEE_FLOAT_NATIVE) && (y != IEEE_FLOAT_SWAP)) {
      return false;
    }

    // read in the end of data pointer
    //
    int32 val;
    if (fp_d.read(&val, sizeof(int32), 1) != 1) {
      return false;
    }
    end_of_data_d = val;
    
    // sanity check on end_of_data_d
    //
    if (end_of_data_d < 1) {
      return false;
    }

    // read in the checksum
    //
    uint16 checksum;
    if (fp_d.read(&checksum, sizeof(uint16), 1) != 1) {
      return false;
    }
    file_checksum_d = checksum;

    if (debug_level_d >= Integral::DETAILED) {
      SysString output;
      output.assign(file_checksum_d);
      output.insert(L"read file_checksum_d = ", 0);
      Console::put(output);
    }
  }

  // save the position
  //
  end_of_header_d = fp_d.tell();
  cur_pos_d = end_of_header_d;
  
  // provide some debug information
  //
  if (debug_level_d > Integral::DETAILED) {
    debug(L"isSof");
  }
  
  // check the class name and version
  //
  if (!cname_d.eq(CLASS_NAME)) {
    return false;
  }
  if (!version_d.eq(VERSION)) {
    return false;
  }

  // make sure the delimiters are equal
  //
  if (delim_beg != delim_end) {
    return false;
  }
  else {
    delimiter_d = delim_beg;
  }

  // exit gracefully
  //
  return true;
}

// method: isSof
//
// arguments:
//  const SysString& fname: (input) filename
//
// return: a bool8 value indicating status
//
// check if this file is an Sof file
//
bool8 Sof::isSof(const SysString& fname_a) {
  
  // we need an Sof object
  //
  Sof sof;
  
  // open the file
  //
  if (!sof.fp_d.open(fname_a)) {
    return false;
  }

  // check if it is sof
  //
  if (!sof.isSof()) {

    // close the file pointers and return false
    //
    sof.fp_d.close();
    return false;
  }
  
  // close the file pointer
  //
  sof.fp_d.close();
  
  // exit gracefully
  //
  return true;
}

// method: update
//
// arguments: none
//
// return: a bool8 value indicating status
//
// this method updates the header and index
//
bool8 Sof::update() {

  // local variables
  //
  SysString buf;
  buf.assign(L"  ");
  buf(0) = delimiter_d;
  buf.concat(cname_d);
  buf.concat(L" ");
  buf.concat(version_d);

  // start from the beginning of the file
  //
  fp_d.rewind();
  
  // text files are simpler
  //
  if (file_type_d == File::TEXT) {
    
    // concatenate the last delimiter and write string
    //
    buf.concat(L"  \n");
    buf(buf.length() - 2) = delimiter_d;
    fp_d.put(buf);
    fp_d.flush();
    end_of_header_d = ftell();
    return true;
  }

  // binary file, build magic string from bmode
  //
  int32 x[2];
  File::BMODE byte_mode = fp_d.getBMode();
  File::BMODE mach_byte_mode = fp_d.getMachineByteOrder();
  
  if (byte_mode == mach_byte_mode) {
    x[0] = BCODE_NATIVE;
  }
  else {
    x[0] = BCODE_SWAP;
  }

  x[1] = (int32)0;
  magic_d.assign((byte8*)&x);
  
  buf.concat(L" ");
  buf.concat(magic_d);

  // concatenate the last delimiter and write string
  //
  buf.concat(L"  \n");
  buf(buf.length() - 2) = delimiter_d;
  fp_d.put(buf);

  int32 val = (int32)end_of_data_d;
  
  if (fp_d.write(&val, sizeof(int32), 1) != 1) {
    return Error::handle(name(), L"update", Error::WRITE, __FILE__, __LINE__);
  } 

  // write out a null checksum (we'll update it after we write the
  // index and table)
  //
  uint16 valc = 0;
  if (fp_d.write(&valc, sizeof(uint16), 1) != 1) {
    return Error::handle(name(), L"update", Error::WRITE, __FILE__, __LINE__);
  } 
  
  // set end of header, possibly set end of data
  //
  end_of_header_d = fp_d.tell();
  cur_pos_d = end_of_header_d;
  if (end_of_data_d < end_of_header_d) {
    end_of_data_d = end_of_header_d;
  }

  // if end of data exists, seek to it
  //
  else {
    
    // seek to the end of the data
    //
    if (!fseek(end_of_data_d, File::POS)) {
      return Error::handle(name(), L"update", Error::SEEK, __FILE__, __LINE__);
    }
  }

  // clear the checksum object so it can accumulate a new checksum
  //
  cksm_d.clear(Integral::RETAIN);
  
  // write out the symbol table
  //
  if (debug_level_d > Integral::BRIEF) {
    SysString output;
    output.assign((int32)end_of_data_d);
    output.insert(L"<Sof::update> writing table to position ", 0);
    Console::put(output);
  }
  if (!writeTable()) {
    return Error::handle(name(), L"update", SofSymbolTable::ERR,
			 __FILE__, __LINE__);
  }

  // update the index at the end of the file
  //
  if (debug_level_d > Integral::BRIEF) {
    SysString output;
    output.assign((int32)ftell());
    output.insert(L"<Sof::update> writing index to position ", 0);
    Console::put(output);
  }
  if (!writeIndex()) {
    return Error::handle(name(), L"update", SofList::ERR, __FILE__, __LINE__);
  }
  
  // truncate the file if necessary
  //
  int32 end_of_file = ftell();
  
  if (!fseek(0, File::POS_PLUS_END)) {
    return Error::handle(name(), L"update", Error::SEEK, __FILE__, __LINE__);
  }
  
  if (ftell() > (end_of_file + 1)) {

    // give debug message
    //
    if (debug_level_d > Integral::BRIEF) {

      SysString output;
      SysString numeric;

      output.assign(L"<Sof::update> truncating file [");
      numeric.assign(ftell());
      output.concat(numeric);

      output.concat(L" - ");
      numeric.assign(end_of_file);
      output.concat(numeric);
      output.concat(L"]");
      
      Console::put(output);
    }

    // truncate file
    //
    if (!fp_d.truncate(end_of_file + 1)) {
      return Error::handle(name(), L"update", Error::IO, __FILE__, __LINE__);
    }
  }

  // write out the checksum
  //
  if (!fseek(end_of_header_d - sizeof(uint16), File::POS)) {
    return Error::handle(name(), L"update", Error::SEEK, __FILE__, __LINE__);
  }

  
  valc = cksm_d.get();
  if (fp_d.write(&valc, sizeof(uint16), 1) != 1) {
    return Error::handle(name(), L"update", Error::WRITE, __FILE__, __LINE__);
  } 

  if (debug_level_d >= Integral::DETAILED) {
    SysString output;
    output.assign(valc);
    output.insert(L"writing checksum = ", 0);
    Console::put(output);
  }

  
  // seek back to the beginning of the current object, if set
  //
  if (cur_data_d >= end_of_header_d) {
    rewind();
  }
  
  fp_d.flush();

  // exit gracefully
  //
  return true;
}
