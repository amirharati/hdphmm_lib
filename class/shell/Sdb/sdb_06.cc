// file: $isip/class/shell/Sdb/sdb_06.cc
// version: $Id: sdb_06.cc 9209 2003-06-15 03:41:40Z picone $
//

// isip include files
// 
#include "Sdb.h"

// method: append
//
// arguments:
//  const Filename& arg: (input) Filename to append
//  bool8 is_list: (input) is this file a list?
//
// return: a bool8 value indicating status
//
// this method processes all arguments on the command line as input files 
//
bool8 Sdb::append(const Filename& arg_a, bool8 is_list_a) {

  // call the master function
  //
  Pair<Filename, Boolean> pair(arg_a, is_list_a);
  return files_d.insertLast(&pair);
}

// method: append
//
// arguments:
//  const String& arg: (input) string to append
//  bool8 is_list: (input) is this file a list?
//
// return: a bool8 value indicating status
//
// this method processes all arguments on the command line as input files 
//
bool8 Sdb::append(const String& arg_a, bool8 is_list_a) {

  // call the master function
  //
  Filename temp(arg_a);
  return append(temp, is_list_a);
}

// method: append
//
// arguments:
//  const unichar* arg: (input) array of unichar to append
//  bool8 is_list: (input) is this file a list?
//
// return: a bool8 value indicating status
//
// this method processes all arguments on the command line as input files 
//
bool8 Sdb::append(const unichar* arg_a, bool8 is_list_a) {

  // assign input array to Filename and insert onto list
  //
  Filename temp;
  temp.assign(arg_a);
  return append(temp, is_list_a);
}

// method: gotoNext
//
// arguments: none
//
// return: a bool8 value indicating status
//
// this method advances the internal list to the next entry
//
bool8 Sdb::gotoNext() {

  // advance to a new Filename
  //
  Filename fn;

  if (queue_d.isEmpty()) {

    // if no files can be appended, we are at the end
    //
    if (iterate() == 0) {
      return false;
    }
  }

  // we know that it is either not empty or iterate added elements, so
  // we can safely remove the oldest element.
  //
  if (queue_d.remove(&fn) == (Filename*)NULL) {
    return Error::handle(name(), L"gotoNext", ERR, __FILE__, __LINE__);
  }

  // this handles the case of exacly 1 file in the queue before the
  // remove
  //
  if (queue_d.isEmpty()) {

    // if no files can be appended, we are at the end
    //
    if (iterate() == 0) {
      return false;
    }
  }

  // exit gracefully
  //
  return (!queue_d.isEmpty());
}

// method: gotoFirst
//
// arguments: none
//
// return: a bool8 value indicating status
//
// this method sets the internal list to the first entry
//
bool8 Sdb::gotoFirst() {

  // clear out the file buffer
  //
  queue_d.clear();
  
  // close out and clear the stack
  //
  Sof* sof;
  while ((sof = fps_d.pop()) != (Sof*)NULL) {
    Long tag;
    if (tags_d.pop(&tag) == (Long*)NULL) {
      return Error::handle(name(), L"gotoFirst", ERR, __FILE__, __LINE__);
    }
    if (nums_d.pop(&tag) == (Long*)NULL) {
      return Error::handle(name(), L"gotoFirst", ERR, __FILE__, __LINE__);
    }
    sof->close();
    delete sof;
  }

  // if there are items, goto first
  //
  if (!files_d.gotoFirst()) {
    return false;
  }

  // initialize the at_first variable
  //
  at_first_d = true;
  
  // exit gracefully
  //
  return true;
}

// method: getName
//
// arguments:
//  Filename& name: (output) filename
//
// return: a bool8 value indicating status
//
// this method returns the current filename
//
bool8 Sdb::getName(Filename& name_a) {

  // declare local variables
  //
  const Filename* ptr = (Filename*)NULL;

  if (!queue_d.isEmpty()) {
    ptr = queue_d.peek();
  }

  // if the element is NULL, try expanding the structure
  //
  if (ptr == (Filename*)NULL) {
    if (iterate() == 0) {
      return false;
    }
    ptr = queue_d.peek();

    // if the element is still NULL, error
    //
    if (ptr == (Filename*)NULL) {
      return Error::handle(name(), L"getName", Error::ARG, __FILE__, __LINE__);
    }
  }

  // assign the name
  //
  name_a.assign(*ptr);

  // exit gracefully
  //
  return true;
}

// method: transformName
//
// arguments:
//  Filename& out_name: (output) output filename
//  const Filename& in_name: (input) input filename
//
// return: a bool8 value indicating status
//
// this method transforms the input filename into an output filename
// given the Sdb specified transformation rules.
//
bool8 Sdb::transformName(Filename& out_name_a,
			   const Filename& in_name_a) {

  // clear the content of the output filename
  //
  out_name_a.clear();

  // if the input name is the stream code, just copy to output
  //
  if (in_name_a.eq(File::STREAM_FILE)) {
    out_name_a.assign(in_name_a);
    return true;
  }

  // get the extension of the input filename
  //
  String extension;
  in_name_a.getExt(extension);

  // if no output directory is specified, just transform the name
  // uniquely
  //
  if (output_directory_d.length() == 0) {

    if (extension.eq(output_extension_d)) {
      out_name_a.transformUniquely(in_name_a);
    }
    else {
      out_name_a.assign(in_name_a);
      out_name_a.transform(output_extension_d, output_suffix_d);
    }
  }

  // output directory specified, so combine the old name (truncated by
  // the number of directory levels to preserve) with the new
  // directory.
  //
  else {
    out_name_a.assign(in_name_a);
    out_name_a.transform(output_directory_d, output_extension_d,
			 output_suffix_d, dir_pres_d);
  }

  // now use buildPath to make sure the output path exists
  //
  String dir;
  out_name_a.getDir(dir);
  if (dir.length() > 0) {
    Filename::buildPath(dir);
  }

  // make sure the input file exists
  //
  if (!File::exists(in_name_a)) {
    return false;
  }

  // exit gracefully
  //
  return true;
}

// method: iterate
//
// arguments: none
//
// return: a int32 value containing the number of files added to
// available list
//
// this method is fed a new filename to be appended to the list. the
// file is tested. if it is an Sof file containing an Sdb object, then
// the file will be opened and each entry will be added.
//
int32 Sdb::iterate() {

  // initialize the mode to be reference
  //
  //  bool8 self_reference = false;

  String next_line;
  Pair<Filename, Boolean> bin_entry;

  int32 i = 0;
  
  // add lookahead files to the list, the increment is inside
  // the loop
  //
  for (; i < lookahead_d; ) {

    next_line.clear();
    bool8 read_entry = false;
    Filename new_file;
    bool8 is_list = false;
    
    // if we have an open file, read from it
    //
    while (!fps_d.isEmpty()) {

      // for text mode: if we can read from the file, break
      //
      if (fps_d.peek()->isText() && fps_d.peek()->gets(next_line)) {

	// make sure the line has at least one character
	//
	if (next_line.length() == 0) {
	  continue;
	}
	read_entry = true;
	break;
      }

      // for binary mode: if we can read from the file, break
      //
      else if (fps_d.peek()->isBinary()
	       && nums_d.peek()->gt(0)  // make sure there are still elements
	       && bin_entry.readData(*(fps_d.peek()),
				     String::getEmptyString())) {
	
	// copy the data over
	//
	new_file.assign(bin_entry.first());
	is_list = bin_entry.second();

	// decrement the number to read in this object and break
	//
	nums_d.peek()->sub(*(nums_d.peek()), 1);
	read_entry = true;
	
	break;
      }
      
      // the read failed, try to move on to the next Sdb object in this file
      //
      Long tag;
      if (tags_d.pop(&tag) == (Long*)NULL) {
	return Error::handle(name(), L"iterate", ERR, __FILE__, __LINE__);
      }
      tag = fps_d.peek()->next(CLASS_NAME, (int32)tag);

      // if there is another Sdb object, move to it
      //
      if (tag != Sof::NO_TAG) {

	// position the Sof file
	//
	if (!fps_d.peek()->find(CLASS_NAME, (int32)tag)) {
	  return Error::handle(name(), L"iterate", Sdb::ERR, __FILE__,
			       __LINE__, Error::WARNING);
	}

	// for binary mode read the number of elements and place it on
	// the stack
	//
	if (fps_d.peek()->isBinary()) {
	  nums_d.peek()->readData(*(fps_d.peek()));
	}

	// place the tag on the stack
	//
	tags_d.push(&tag);

	// continue back to the top-level loop
	//
	continue;
      }
      
      // no more Sdb objects: cleanup the Sof object
      //
      Sof* sof;
      sof = fps_d.pop();
      sof->close();
      delete sof;

      // pop the num stack as well
      //
      Long num;
      nums_d.pop(&num);
    }


    // if no entry was read, use the next file on the list
    //
    if (!read_entry) {

      // if we are at the first entry, use it. else gotoNext
      //
      if (at_first_d) {

	// make sure the list is not empty
	//
	if (files_d.isEmpty()) {
	  return 0;
	}

	new_file.assign(files_d.getCurr()->first());
	is_list = files_d.getCurr()->second();
	at_first_d = false;
      }

      else {
	
	// terminal condition -- no more files to expand
	//
	if (files_d.isLast()) {
	  break;
	}
	
	// advance the position in the list
	//
	files_d.gotoNext();
	
	// assign the entry line to this next file
	//
	new_file.assign(files_d.getCurr()->first());
	if (new_file.length() == 0) {
	  return Error::handle(name(), L"iterate", ERR, __FILE__, __LINE__);
	}
	is_list = files_d.getCurr()->second();
      }
    }

    // parse the line if we didn't get it from the list directly
    //
    if (new_file.length() == 0) {
      if (!parse(new_file, is_list, next_line)) {
	continue;
      }
    }

    // determine if the line is a list or a single file entry
    //
    if (is_list) {
      
      Sof* sof = new Sof;

      // open the file with error checking
      //
      if (!sof->open(new_file)) {
	delete sof;
	Console::put(new_file);
	return Error::handle(name(), L"iterate", Sof::ERR_NOTSOF, __FILE__,
			     __LINE__, Error::WARNING);
      }

      // determine the tag
      //
      Long tag = sof->first(CLASS_NAME);

      // find the Sdb object with error checking
      //
      if (tag == Sof::NO_TAG) {
	delete sof;
	Console::put(new_file);
	return Error::handle(name(), L"iterate", Sdb::ERR_NOTSDB, __FILE__,
			     __LINE__, Error::WARNING);
      }
      
      // position the Sof file
      //
      if (!sof->find(CLASS_NAME, (int32)tag)) {
	delete sof;
	Console::put(new_file);
	return Error::handle(name(), L"iterate", Sdb::ERR, __FILE__,
			     __LINE__, Error::WARNING);
      }

      // for binary, read the number of elements and push it onto the
      // stack
      //
      Long num_elem;
      if (sof->isBinary()) {
	num_elem.readData(*sof);
      }
      nums_d.push(&num_elem);
      
      // now that the object is ready place it on the stack
      //
      fps_d.push((WSof*)sof);
      tags_d.push(&tag);
    }

    // else this is a plain file, so place it onto new_files and
    // increment the counter
    //
    else {
      queue_d.add(&new_file);
      i++;
    }
	
  }     

  // exit gracefully -- if we get this far we must have looped far enough
  //
  return i;
}
