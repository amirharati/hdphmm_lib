// file: $isip/class/math/vector/MVector/mvec_03.cc
// version: $Id: mvec_03.cc 7816 2002-02-27 20:54:30Z alphonso $
//

// isip include files
//
#include "MVectorMethods.h"
#include "MVector.h"

// method: read
//
// arguments:
//  MVector<TScalar,TIntegral>& this: (output) class operand
//  Sof& sof: (input) sof file object
//  int32 tag: (input) sof object instance tag
//  const String& name: (input) sof object instance name
//
// return: a bool8 value indicating status
//
// this method has the object read itself from an Sof file
//
template<class TScalar, class TIntegral>
bool8 MVectorMethods::read(MVector<TScalar,TIntegral>& this_a,
			     Sof& sof_a, int32 tag_a, const String& name_a) {

  // read the instance of the object from the Sof file
  //
  if (!sof_a.find(name_a, tag_a)) {
    return false;
  }
  
  // read the actual data from the sof file
  //
  if (!this_a.readData(sof_a)) {
    return false;
  }

  // exit gracefully
  //
  return true;
}

// explicit instantiations
//
template bool8
MVectorMethods::read<ISIP_TEMPLATE_TARGET>
(MVector<ISIP_TEMPLATE_TARGET>&, Sof&, int32, const String&);

// method: readData
//
// arguments:
//  MVector<TScalar, TIntegral>& this: (output) class operand
//  Sof& sof: (input) sof file object
//  const String& pname: (input) parameter name
//  int32 size: (input) size in bytes of object (or FULL_OBJECT)
//  bool8 param: (input) is the parameter name in the file?
//  bool8 nested: (input) are we nested?
//
// return: a bool8 value indicating status
//
// this method has the object read itself from an Sof file. it assumes
// that the Sof file is already positioned correctly.
//
template<class TScalar, class TIntegral>
bool8 MVectorMethods::readData(MVector<TScalar, TIntegral>& this_a,
				 Sof& sof_a, const String& pname_a,
				 int32 size_a, bool8 param_a,
				 bool8 nested_a) {

  // if ascii, read in a line, else binary read
  //
  if (sof_a.isText()) {
    
    SofParser parser;
    String pname;
    
    // set the parser debug level
    //
    parser.setDebug(this_a.debug_level_d);
    
    // if param is false, this means implicit parameter
    //
    if (!param_a) {
      parser.setImplicitParam();
      pname.assign(parser.implicitPname());
    }
    else {
      pname.assign(pname_a);
    }
    
    // are we nested?
    //
    if (nested_a) {
      parser.setNest();
    }
    
    // load the parse
    //
    parser.load(sof_a, size_a);
    
    // get the size of vector
    //
    int32 new_size = parser.countTokens(pname);
    
    // declare local variables
    //
    int32 pos = 0;
    TIntegral val;

    // declare a string to hold tokenized substrings
    //
    String token;
    
    // debugging statement
    //
    if (this_a.debug_level_d > Integral::BRIEF) {
      String output;
      output.assign(new_size);
      output.insert(L"setting MVector::length_d = ", 0);
      output.concat(L": ");
      output.concat(pname);
      Console::put(output);
    }
    
    if (new_size > 0) {
      
      // set the length
      //
      if (!this_a.setLength((int32)new_size)) {
	this_a.debug(L"this_a");	
        return Error::handle(name(), L"readData", Error::MEM, __FILE__,
                             __LINE__);
      }
      
      // declare local variable
      //
      String data;
      
      // the implicit parameter setting must be set again if necessary
      //
      if (!param_a) {
        parser.setImplicitParam();
      }
      
      // read a block of data at a time
      //
      int32 read_size;
      int32 offset = 0;
      
      if (new_size > MVector<TScalar, TIntegral>::TEXT_READ_SIZE) {
        read_size = MVector<TScalar, TIntegral>::TEXT_READ_SIZE;
        new_size -= MVector<TScalar, TIntegral>::TEXT_READ_SIZE;
      }
      else {
        read_size = new_size;
        new_size = 0;
      }
      
      while (read_size > 0) {
        
        if (this_a.debug_level_d > Integral::DETAILED) {
          data.debug(L"vector data");
        }
        
        
        // read elements [offset, offset + read_size]
        //
        if (!parser.read(data, sof_a, parser.getEntry(sof_a, pname, offset,
                                                      read_size))) {
          // exit with error
          //
          return false;
        }

	// tokenize the input string into substrings, get the integer
	// value from the substring and assign it to test vector. 
	//
	
	// initialize "pos" to be 0 before every call of tokenize for one
	// input string
	//
	pos = 0;
	for (int32 k = 0; k < read_size; k++) {
	  if (data.tokenize(token, pos, SofParser::DEF_DELIMITER_CHAR)) {
	    token.trim();
	    token.get(val);
	    this_a.v_d[k + offset] = val;
	  }
	} 

	// increment the offset by read size
	//
        offset += read_size;
        
        // reduce the number of elements to read
        //
        if (new_size > MVector<TScalar, TIntegral>::TEXT_READ_SIZE) {
          read_size = MVector<TScalar, TIntegral>::TEXT_READ_SIZE;
          new_size -= MVector<TScalar, TIntegral>::TEXT_READ_SIZE;
        }
        else {
          read_size = new_size;
          new_size = 0;
        }       
      }
    }
  }
  else {
    
    // binary read
    //
    
    // first read the size
    //
    Long new_size;
    new_size = (int32)0;
    
    if (!new_size.readData(sof_a, pname_a)) {
      return false;
    }
    
    if ((int32)new_size > 0) {
      
      // set the length
      //
      this_a.setLength((int32)new_size, false);
      
      // now read the data
      //
      for (int32 i = 0; i < (int32)new_size; i++) {
        if (!this_a.v_d[i].readData(sof_a, pname_a)) {
          return false;
        }
      }
    }
  }

  // exit gracefully
  //
  return true;
}

// explicit instantiations
//
template bool8
MVectorMethods::readData<ISIP_TEMPLATE_TARGET>
(MVector<ISIP_TEMPLATE_TARGET>&, Sof&, const String&, int32, bool8, bool8);

// method: readStart
//
// arguments:
//  MVector<TScalar,TIntegral>& this: (output) class operand
//  Sof& sof: (input) sof file object
//  const String& pname: (input) parameter name
//  int32 size: (input) size in bytes of object (or FULL_OBJECT)
//  bool8 param: (input) is the parameter name in the file?
//  bool8 nested: (input) are we nested?
//
// return: a bool8 value indicating status
//
// this method has the object read itself from an Sof file. it assumes
// that the Sof file is already positioned correctly.
//
template<class TScalar, class TIntegral>
bool8 MVectorMethods::readStart(MVector<TScalar,TIntegral>& this_a,
				  Sof& sof_a, const String& pname_a,
				  int32 size_a, bool8 param_a,
				  bool8 nested_a) {
  
  // local variable
  //
  Long new_size((int32)0);
  
  // first cleanup the list
  //
  if (!this_a.clear(Integral::RELEASE)) {
    this_a.debug(L"this_a");    
    return Error::handle(name(), L"readStart", Error::MEM, __FILE__, __LINE__);
  }

  // start the partial read in Sof
  //
  sof_a.startPartialRead();
  
  // if text, read in a line, else binary read
  //
  if (sof_a.isText()) {
    
    String pname;

    // set the parser debug level
    //
    sof_a.getVecParser().setDebug(this_a.debug_level_d);
    
    // if param is false, this means implicit parameter
    //
    if (!param_a) {
      sof_a.getVecParser().setImplicitParam();
      pname.assign(SofParser::implicitPname());
    }
    else {
      pname.assign(pname_a);
    }
    
    // are we nested?
    //
    if (nested_a) {
      sof_a.getVecParser().setNest();
    }
    
    // load the parse
    //
    sof_a.getVecParser().load(sof_a, size_a);

    new_size = sof_a.getVecParser().countTokens(pname);
  }
  
  // binary mode
  //
  else {

    // set the start position of the vector
    //
    sof_a.setStartPos(sof_a.tell());

    // read the actual size of the vector
    //
    if (!new_size.readData(sof_a, String::EMPTY)) {
      return false;
    }
  }

  // set the vector size and index of current element
  //
  sof_a.setVecSize((int32)new_size);
  sof_a.setVecCurrentElement((int32)0);
  
  // exit gracefully
  //
  return true;
}

// explicit instantiations
//
template bool8
MVectorMethods::readStart<ISIP_TEMPLATE_TARGET>
(MVector<ISIP_TEMPLATE_TARGET>&, Sof&, const String&, int32, bool8, bool8);

// method: readPartialData
//
// arguments:
//  MVector<TScalar,TIntegral>& this: (output) class operand
//  Sof& sof: (input) sof file object
//  int32 start_pos: (input) first entry to read
//  int32 num_elem: (input) number of elements to read
//  const String& pname: (input) parameter name
//  int32 size: (input) size in bytes of object (or FULL_OBJECT)
//  bool8 param: (input) is the parameter name in the file?
//  bool8 nested: (input) are we nested?
//
// return: a bool8 value indicating status
//
// this method has the object read itself from an Sof file. it assumes
// that the Sof file is already positioned correctly.
//
template<class TScalar, class TIntegral>
int32 MVectorMethods::readPartialData(MVector<TScalar,TIntegral>& this_a,
				     Sof& sof_a, int32 start_pos_a,
				     int32 num_elem_a, const String& pname_a,
				     int32 size_a, bool8 param_a,
				     bool8 nested_a) {
  
  // check arguments
  //
  if (num_elem_a <= 0) {
    this_a.setLength(0);
    return (int32)0;
  }
  
  if (start_pos_a < 0) {
    this_a.debug(L"this_a");    
    return Error::handle(name(), L"readPartialData", Error::ARG,
                         __FILE__, __LINE__);
  }

  // declare local variable
  //
  String pname;
  
  // if param is false, this means implicit parameter
  //
  if (!param_a) {
    sof_a.getVecParser().setImplicitParam();
    pname.assign(SofParser::implicitPname());
  }
  else {
    pname.assign(pname_a);
  }

  // if text, read in a line, else binary read
  //
  if (sof_a.isText()) {
    
    int32 new_size = sof_a.getVecParser().countTokens(pname);

    // declare local variables
    //
    int32 pos = 0;
    TIntegral val;

    // declare a string to hold tokenized substrings
    //
    String token;

    // debugging statement
    //
    if (this_a.debug_level_d > Integral::BRIEF) {
      String output;
      output.assign(new_size);
      output.insert(L"full MVector::length_d = ", 0);
      output.concat(L": ");
      output.concat(pname);
      Console::put(output);
    }
    
    if (new_size > 0) {
      
      if (start_pos_a > new_size) {
        return (int32)0;
      }
      else if ((start_pos_a + num_elem_a) > new_size) {
        new_size = new_size - start_pos_a;
      }
      else {
        new_size = num_elem_a;
      }
      
      // recreate the vector for the new size
      //
      if (!this_a.setLength((int32)new_size)) {
	this_a.debug(L"this_a");	
        return Error::handle(name(), L"readPartialData", Error::NOMEM,
                             __FILE__, __LINE__);
      }

      // this is the actual number of elements to read
      //
      num_elem_a = new_size;
      
      // read in entire row of data, then tokenize
      //
      String data;
      
      // read a block of data at a time
      //
      int32 read_size;
      int32 offset = (int32)0;
      
      if (new_size > MVector<TScalar,TIntegral>::TEXT_PARTIAL_READ_SIZE) {
        read_size = MVector<TScalar,TIntegral>::TEXT_PARTIAL_READ_SIZE;
        new_size -= MVector<TScalar,TIntegral>::TEXT_PARTIAL_READ_SIZE;
      }
      else {
        read_size = new_size;
        new_size = 0;
      }
      
      while (read_size > 0) {
        
        // read the elements
        // [offset + start_pos_a, offset + start_pos_a + read_size]
        //
        sof_a.getVecParser().read(data, sof_a,
				  sof_a.getVecParser().getEntry(sof_a, pname,
								offset +
								start_pos_a,
								read_size));
        
        if (this_a.debug_level_d > Integral::DETAILED) {
          data.debug(L"vector data");
        }

	// tokenize the "data" string into substrings, get the integer
	// value from the substring and assign it to test vector. 
	//
	
	// initialize "pos" to be 0 before every call of tokenize for one
	// input string
	//
	pos = 0;
	for (int32 k = 0; k < read_size; k++) {
	  if (data.tokenize(token, pos, SofParser::DEF_DELIMITER_CHAR)) {
	    token.trim();
	    token.get(val);
	    this_a.v_d[k + offset] = val;
	  }
	} 

	// increment the offset by read size
	//
        offset += read_size;
        
        // reduce the number of elements to read
        //
        if (new_size > MVector<TScalar,TIntegral>::TEXT_PARTIAL_READ_SIZE) {
          read_size = MVector<TScalar,TIntegral>::TEXT_PARTIAL_READ_SIZE;
          new_size -= MVector<TScalar,TIntegral>::TEXT_PARTIAL_READ_SIZE;
        }
        else {
          read_size = new_size;
          new_size = 0;
        }
      }
      return num_elem_a;
    }
  }
  
  else {
    
    // binary read
    //
    
    // first read the size
    //
    int32 new_size = sof_a.getVecSize();
    
    if (new_size > 0) {
      
      if (start_pos_a >= new_size) {
        return (int32)0;
      }
      else if ((start_pos_a + num_elem_a) > new_size) {
        new_size -= start_pos_a;
      }
      else {
        new_size = num_elem_a;
      }
      
      // recreate the vector for the new size
      //
      if (!this_a.setLength(new_size)) {
	this_a.debug(L"this_a");	
        return Error::handle(name(), L"readPartialData", Error::NOMEM,
                             __FILE__, __LINE__);
      }
      
      // skip to start_pos_a
      //
      if (!sof_a.seek(sizeof(TIntegral) * start_pos_a, File::POS_PLUS_CUR)) {
        return (int32)0;
      }
      
      // now read the data
      //
      for (int32 i = 0; i < new_size; i++) {
        if (!this_a.v_d[i].readData(sof_a, pname_a)) {
          return (int32)0;
        }
      }
      return new_size;
    }
  }

  // exit gracefully
  //
  return (int32)0;                       
}

// explicit instantiations
//
template int32
MVectorMethods::readPartialData<ISIP_TEMPLATE_TARGET>
(MVector<ISIP_TEMPLATE_TARGET>&, Sof&, int32, int32,
 const String&, int32, bool8, bool8);
