// file: $isip/class/io/Sof/sof_09.cc
// version: $Id: sof_09.cc 4958 2000-09-22 21:35:19Z zhao $
//

// isip include files
//
#include "Sof.h"

// method: resize
//
// arguments:
//  const SysString& name: (input) class name
//  int32 tag: (input) class tag
//  int32 size: (input) new required size
//
// return: a bool8 value indicating status
//
// resize the current entry, preserving current data
//
bool8 Sof::resize(const SysString& name_a, int32 tag_a, int32 size_a) {
  
  // find the object and seek to the beginning of the data
  //
  if (!find(name_a, tag_a)) {
    return Error::handle(name(), L"resize", ERR_NOOBJ,
			 __FILE__, __LINE__);
  }

  // check argument
  //
  if (size_a < 0) {
    return Error::handle(name(), L"resize", Error::ARG, __FILE__, __LINE__);
  }

  int32 obj_size = getObjectSize();
  int32 obj_pos = index_d.getPosition();
  
  if (obj_size == size_a) {

    // do nothing
    //
    return true;
  }
  else if (obj_size > size_a) {

    if (!fseek(size_a, File::POS_PLUS_CUR)) {
      return Error::handle(name(), L"resize", Error::SEEK, __FILE__, __LINE__);
    }

    // clear space
    //
    if (!clearSpace(obj_size - size_a)) {
      return Error::handle(name(), L"resize", Error::IO, __FILE__, __LINE__);
    }

    // reposition the file pointer to the beginning of the object's data
    //
    if (!rewind()) {
      return Error::handle(name(), L"resize", Error::SEEK, __FILE__, __LINE__);
    }

    // possibly shrink the file, if this is the last object
    //
    if ((obj_pos + obj_size) == end_of_data_d) {
      end_of_data_d -= (obj_size - size_a);
    }

    // reset the size in the index
    //
    return index_d.setSize(size_a);
  }
  else if (obj_size < size_a) {

    // here's the tricky part: delete the current entry and make a new
    // one at the end
    //
    int32 new_pos;
    int32 new_data_pos;
      
    // get the new position (end of file)
    //
    if (isText()) {

      // seek to the end of file
      //
      if (!fseek(0, File::POS_PLUS_END)) {
	return Error::handle(name(), L"resize", Error::SEEK,
			     __FILE__, __LINE__);
      }

      // this is the new position (beginning of label)
      //
      new_pos = ftell();
      
      // write the label
      //
      if (!writeLabel(name_a, tag_a)) {
	return Error::handle(name(), L"resize", ERR_LABEL,
			     __FILE__, __LINE__);
      }

      // set the new position for the data
      //
      new_data_pos = ftell();
    }

    // for binary, seek to end_of_data_d
    //
    else {
      
      if (!fseek(end_of_data_d, File::POS)) {
	return Error::handle(name(), L"resize", Error::SEEK,
			     __FILE__, __LINE__);
      }

      end_of_data_d += size_a;
      
      // both position and data position are the same for binary
      //
      new_pos = ftell();
      new_data_pos = new_pos;
    }

    // clear out the new space before we copy data over
    //
    if (!clearSpace(size_a)) {
      return Error::handle(name(), L"resize", Error::IO, __FILE__, __LINE__);
    }
    
    // copy the data currently in the object to the end of the file
    //
    if (!copySegment(cur_data_d, new_data_pos, obj_size)) {
      return Error::handle(name(), L"resize", Error::IO, __FILE__, __LINE__);
    }

    // now empty the old space
    //
    if (!rewind()) {
      return Error::handle(name(), L"resize", Error::SEEK, __FILE__, __LINE__);
    }
    if (!clearSpace(obj_size + cur_data_d - obj_pos)) {
      return Error::handle(name(), L"resize", Error::IO, __FILE__, __LINE__);
    }
    
    // change the values of position and size for this object
    //
    index_d.setPosition(new_pos);
    index_d.setSize(size_a);
    
    // position us back to the beginning of the new object (this will
    // also set cur_data_d)
    //
    if (!seekData()) {
      return Error::handle(name(), L"resize", Error::SEEK, __FILE__, __LINE__);
    }
  }

  // exit gracefully
  //
  return true;
}

// method: resize
//
// arguments:
//  int32 size: (input) new required size
//
// return: a bool8 value indicating status
//
// resize the current entry that is in partial write mode, preserving
// current data. this is only for partial_write mode
//
bool8 Sof::resize(int32 size_a) {
  
  // make sure we are in partial write mode
  //
  if (!partial_write_d) {
    return Error::handle(name(), L"resize", ERR_RESIZE, __FILE__, __LINE__);
  }
  
  // check argument
  //
  if (size_a < 0) {
    debug(L"size went to zero");
    return Error::handle(name(), L"resize", Error::ARG, __FILE__, __LINE__);
  }
  
  int32 obj_size = getObjectSize();
  int32 obj_pos = index_d.getPosition();
  
  // make sure it is the last entry
  //
  if (isBinary() && ((obj_size + obj_pos) != end_of_data_d)) {
    return Error::handle(name(), L"resize", ERR, __FILE__, __LINE__);
  }

  if (obj_size == size_a) {

    // do nothing
    //
    return true;
  }
  else if (obj_size > size_a) {

    if (!fseek(size_a, File::POS_PLUS_CUR)) {
      return Error::handle(name(), L"resize", Error::SEEK, __FILE__, __LINE__);
    }

    // clear space
    //
    if (!clearSpace(obj_size - size_a)) {
      return Error::handle(name(), L"resize", Error::IO, __FILE__, __LINE__);
    }
    
    // reposition the file pointer to where it was before
    //
    if (!fseek(-size_a, File::POS_PLUS_CUR)) {
      return Error::handle(name(), L"resize", Error::SEEK, __FILE__, __LINE__);
    }
    
    if (isBinary()) {

      // reset the size in the index
      //
      index_d.setSize(size_a);

      // adjust end_of_data_d
      //
      end_of_data_d += (size_a - obj_size);
    }
  }
  else if (obj_size < size_a) {
    
    if (isBinary()) {

      // reset the size in the index
      //
      index_d.setSize(size_a);

      // adjust end_of_data_d
      //
      end_of_data_d += (size_a - obj_size);
    }
  }

  // exit gracefully
  //
  return true;
}

// method: copySegment
//
// arguments:
//  int32 src_pos: (input) file position of source
//  int32 nbytes: (input) number of bytes to copy
//
// return: a bool8 value indicating status
//
// this method copies a chunk of nbytes data from src_pos to the end
// of the file
//
bool8 Sof::copySegment(int32 src_pos_a, int32 nbytes_a) {

  // seek the POS_PLUS_END
  //
  if (!fseek(0, File::POS_PLUS_END)) {
    return Error::handle(name(), L"copySegment", Error::SEEK,
			 __FILE__, __LINE__);
  }

  // call the master function
  //
  return copySegment(src_pos_a, ftell(), nbytes_a);
}

// method: copySegment
//
// arguments:
//  int32 src_pos: (input) file position of source
//  int32 dst_pos: (input) file position of destination
//  int32 nbytes: (input) number of bytes to copy
//
// return: a bool8 value indicating status
//
// this method copies a chunk of nbytes data from src_pos to the end
// of the file
//
bool8 Sof::copySegment(int32 src_pos_a, int32 dst_pos_a, int32 nbytes_a) {

  // seek to the destination
  //
  if (!fseek(dst_pos_a, File::POS)) {
    return Error::handle(name(), L"copySegment", Error::SEEK,
			 __FILE__, __LINE__);
  }
  
  // copy one buffer at a time
  //
  static byte8 buffer[BUFFER_SIZE];
  int32 pass_size;
  
  int32 diff_pos = dst_pos_a - src_pos_a;
  
  for (int32 i = nbytes_a; i > 0; i -= BUFFER_SIZE) { 

    if (i > BUFFER_SIZE) {
      pass_size = BUFFER_SIZE;
    }
    else {
      pass_size = i;
    }

    // seek to the position to copy
    //
    if (!fseek(-diff_pos, File::POS_PLUS_CUR)) {
      return Error::handle(name(), L"copySegment", Error::SEEK,
			   __FILE__, __LINE__);
    }
    
    if (fp_d.read(buffer, sizeof(byte8), pass_size) != pass_size) {
      return Error::handle(name(), L"copySegment", Error::READ,
			   __FILE__, __LINE__);
    }

    if (isBinary()) {
      cur_pos_d += pass_size * sizeof(byte8);
    }

    // seek to the position to write
    //
    if (!fseek(diff_pos - pass_size, File::POS_PLUS_CUR)) {
      return Error::handle(name(), L"copySegment", Error::SEEK,
			   __FILE__, __LINE__);
    }
    
    if (fp_d.write(buffer, sizeof(byte8), pass_size) != pass_size) {
      return Error::handle(name(), L"copySegment", Error::WRITE,
			   __FILE__, __LINE__);
    }
    
    if (isBinary()) {
      cur_pos_d += pass_size * sizeof(byte8);
    }
  }      
  
  // exit gracefully
  //
  return true;
}
