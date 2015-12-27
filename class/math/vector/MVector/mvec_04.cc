// file: $isip/class/math/vector/MVector/mvec_04.cc
// version: $Id: mvec_04.cc 7816 2002-02-27 20:54:30Z alphonso $
//

// isip include files
//
#include "MVectorMethods.h"
#include "MVector.h"

// method: write
//
// arguments:
//  const MVector<TScalar, TIntegral>& this: (output) class operand
//  Sof& sof: (input) sof file object
//  int32 tag: (input) sof object instance tag
//  const String& name: (input) sof object instance name
//
// return: a bool8 value indicating status
//
// this method has the object write itself to an Sof file
//
template<class TScalar, class TIntegral>
bool8 MVectorMethods::write(const MVector<TScalar, TIntegral>& this_a,
			      Sof& sof_a, int32 tag_a, const String& name_a) {

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
    obj_size = this_a.sofSize();
  }
  
  // write the object into the sof file's index
  //
  if (!sof_a.put(name_a, tag_a, obj_size)) {
    return false;
  }

  // exit gracefully
  //
  return this_a.writeData(sof_a); 
}

// explicit instantiations
//
template bool8
MVectorMethods::write<ISIP_TEMPLATE_TARGET>
(const MVector<ISIP_TEMPLATE_TARGET>&, Sof&, int32, const String&);

// method: writeData
//
// arguments:
//  const MVector<TScalar, TIntegral>& this: (output) class operand
//  Sof& sof: (input) sof file object
//  const String& pname: (input) sof object instance name
//
// return: a bool8 value indicating status
//
// this method has the object writeData itself to an Sof file
//
template<class TScalar, class TIntegral>
bool8 MVectorMethods::writeData(const MVector<TScalar, TIntegral>& this_a,
				  Sof& sof_a, const String& pname_a) {

  // if ascii, write a line, else binary write
  //
  if (sof_a.isText()) {
    
    static String output(MVector<TScalar, TIntegral>::TEXT_WRITE_SIZE);
    output.clear();
    
    if (pname_a.length() > 0) {
      output.assign(pname_a);
      output.concat(L" = ");
    }
    
    String numeric;

    int32 len = 0;
    int32 num_len = 0;
    
    // assign each member from the string
    //
    for (int32 i = 0; i < (int32)this_a.length_d; i++) {
      
      numeric.assign((TIntegral)this_a.v_d[i]);

      num_len = numeric.length() + 1;

      if (((len + num_len) > MVector<TScalar, TIntegral>::TEXT_WRITE_SIZE)
	  && (i < ((int32)(this_a.length_d) - 1))) {
        sof_a.puts(output);
        output.clear();
        len = 0;
      }

      output.concat(numeric);
      output.concat(L",");

      len += num_len;
    }

    output.trimRight(L",");
    
    if (pname_a.length() > 0) {
      output.concat(L";\n");
    }
    
    sof_a.puts(output);
  }    
  else {
    
    // binary write
    //
    
    // first write the size
    //
    if (!this_a.length_d.writeData(sof_a)) {
      return false;
    }
    
    // now write the data
    //
    if ((int32)(this_a.length_d) > 0) {
      if (sof_a.write(this_a.v_d, sizeof(TIntegral), this_a.length_d)
	  != this_a.length_d) {
        return false;
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
MVectorMethods::writeData<ISIP_TEMPLATE_TARGET>
(const MVector<ISIP_TEMPLATE_TARGET>&, Sof&, const String&);

// method: writeStart
//
// arguments:
//  const MVector<TScalar, TIntegral>& this: (output) class operand
//  Sof& sof: (input) sof file object
//  const String& pname: (input) parameter name
//
// return: position of the length
//
// this method writes data an existing vector object
//
template<class TScalar, class TIntegral>
bool8 MVectorMethods::writeStart(const MVector<TScalar, TIntegral>& this_a,
				   Sof& sof_a, const String& pname_a) {

  // set sof into partial write mode
  //
  sof_a.startPartialWrite();

  // store the length position
  //
  sof_a.setStartPos(sof_a.tell());
  sof_a.setVecSize(0);
  
  // text mode
  //
  if (sof_a.isText()) {

    // write the parameter name
    //
    if (pname_a.length() > 0) {
      String output;
      output.assign(pname_a);
      output.concat(L" = ");
      if (!sof_a.puts(output)) {
	this_a.debug(L"this_a");	
	return Error::handle(name(), L"writeStart", Error::IO,
			     __FILE__, __LINE__);
      }
    }
  }

  // binary mode
  //
  else {

    sof_a.resize(sof_a.getObjectSize() + this_a.length_d.sofSize());

    // write out a zero length
    //
    Long len = 0;
    if (!len.writeData(sof_a)) {
      this_a.debug(L"this_a");      
      return Error::handle(name(), L"writeStart", Error::ARG,
			   __FILE__, __LINE__);
    }
  }

  // exit gracefully
  //
  return true;
}

// explicit instantiations
//
template bool8
MVectorMethods::writeStart<ISIP_TEMPLATE_TARGET>
(const MVector<ISIP_TEMPLATE_TARGET>&, Sof&, const String&);

// method: writePartialData
//
// arguments:
//  const MVector<TScalar, TIntegral>& this: (output) class operand
//  Sof& sof: (input) sof file object
//  int32 start_pos: (input) the index of the Vector to start to write
//  int32 num_elem: (input) the number of elements to write
//
// return: a bool8 value indicating status
//
// this method writes data an existing vector object
//
template<class TScalar, class TIntegral>
int32 MVectorMethods::writePartialData(const MVector<TScalar, TIntegral>& this_a,
				      Sof& sof_a, int32 start_pos_a,
				      int32 num_elem_a) {

  // make sure we are in partial write mode
  //
  if (!sof_a.getPartialWrite()) {
    this_a.debug(L"this_a");    
    Error::handle(name(), L"writePartialData",
		  MVector<TScalar, TIntegral>::ERR, __FILE__, __LINE__);
    return 0;
  }

  // get the length of current vector
  //
  int32 len = this_a.length();

  // check whether the length of current vector and start position are
  // available
  //
  if ((len <= 0) || (start_pos_a >= len) || (num_elem_a <= 0)) {
    this_a.debug(L"this_a");    
    Error::handle(name(), L"writePartialData",
		  MVector<TScalar, TIntegral>::ERR, __FILE__, __LINE__);
    return 0;
  }

  // adjust the true length of written vector
  //
  if ((num_elem_a + start_pos_a) > len) {
    num_elem_a = len - start_pos_a;
  }
  
  // branch on mode
  //
  if (sof_a.isText()) {

    // is this the first write?
    //
    bool8 is_first = (sof_a.getVecSize() == 0);
  
    static String output(MVector<TScalar, TIntegral>::TEXT_WRITE_SIZE);
    output.clear();

    if (!is_first) {
      output.concat(L",");
    }

    // declare local variable
    //
    String numeric;
    int32 line_len = 0;
    int32 num_len = 0;
    
    // assign each member from the string
    //
    for (int32 i = start_pos_a; i < start_pos_a + num_elem_a; i++) {

      // convert the element into string
      //
      numeric.assign((TIntegral)this_a.v_d[i]);

      // calculate the length of the string
      //
      num_len = numeric.length() + 1;

      // check whether the string buffer will be full
      //
      if ((line_len + num_len) > MVector<TScalar, TIntegral>::TEXT_WRITE_SIZE) {
        sof_a.puts(output);
        output.clear();
        line_len = 0;
      }

      output.concat(numeric);
      output.concat(L",");

      line_len += num_len;
    }

    // remove the last character and output the string buffer
    //
    output.trimRight(L",");
    sof_a.puts(output);
  }

  // binary mode
  //
  else {

    // increment the object's size
    //
    int32 new_size = sof_a.getObjectSize()
      + num_elem_a * this_a.v_d[0].sofSize();
    sof_a.resize(new_size);

    // write the data
    //
    if (sof_a.write(&this_a.v_d[start_pos_a],
		    sizeof(TIntegral), num_elem_a) != num_elem_a) {
      this_a.debug(L"this_a");      
      Error::handle(name(), L"writePartialData",
		    MVector<TScalar, TIntegral>::ERR, __FILE__, __LINE__);
      return 0;
    }
  }

  // increment the vector's size in Sof file
  //
  sof_a.setVecSize(sof_a.getVecSize() + num_elem_a);

  // exit gracefully
  //
  return num_elem_a;
}

// explicit instantiations
//
template int32
MVectorMethods::writePartialData<ISIP_TEMPLATE_TARGET>
(const MVector<ISIP_TEMPLATE_TARGET>&, Sof&, int32, int32);

// method: writeTerminate
//
// arguments:
//  const MVector<TScalar, TIntegral>& this: (output) class operand
//  Sof& sof: (input) sof file object
//  const String& pname: (input) parameter name
//
// return: a bool8 value indicating status
//
// this method closes out a partial write
//
template<class TScalar, class TIntegral>
bool8 MVectorMethods::writeTerminate(const MVector<TScalar, TIntegral>& this_a,
				       Sof& sof_a,
				       const String& pname_a) {

  // check if we are in write partial mode
  //
  if (!sof_a.getPartialWrite()) {
    this_a.debug(L"this_a");    
    return Error::handle(name(), L"writeTerminate",
			 MVector<TScalar, TIntegral>::ERR, __FILE__, __LINE__);
  }

  // write the terminal string
  //
  if (sof_a.isText()) {
    
    // write the close brace
    //
    if (sof_a.getVecSize() > 0) {
      static String output(L";\n");
      sof_a.puts(output);
    }
    
    // possibly terminate the statement
    //
    else if (pname_a.length() > 0) {
      static String output(L"\n");
      sof_a.puts(output);
    }
  }

  // for binary mode, go back and write the actual size
  //
  else {

    // jump back to where the length is stored
    //
    sof_a.seek(sof_a.getStartPos(), File::POS);
    Long size(sof_a.getVecSize());
    
    if (this_a.debug_level_d >= Integral::ALL) {
      String output(L"writing size = ");
      output.concat(size);
      output.concat(L" to position ");
      output.concat(sof_a.tell());
      Console::put(output);
    }

    // rewrite the real size of the written vector
    //
    size.writeData(sof_a);
    sof_a.seek(0, File::POS_PLUS_END);
  }

  // we no longer need to be in partial write mode
  //
  sof_a.stopPartialWrite();

  // exit gracefully
  //
  return true;
}

// explicit instantiations
//
template bool8 
MVectorMethods::writeTerminate<ISIP_TEMPLATE_TARGET>
(const MVector<ISIP_TEMPLATE_TARGET>&, Sof&, const String&);

// method: sofSize
//
// arguments:
//  const MVector<TScalar, TIntegral>& this: (output) class operand
//
// return: size of the object
//
template<class TScalar, class TIntegral>
int32 MVectorMethods::sofSize(const MVector<TScalar, TIntegral>& this_a) {

  // start with the length
  //
  int32 bytes = this_a.length_d.sofSize();
  
  // add each element
  //
  for (int32 i = 0; i < this_a.length_d; i++) {
    bytes += this_a.v_d[i].sofSize();
  }
  
  // return the number
  //
  return bytes;
}

// explicit instantiations
//
template int32
MVectorMethods::sofSize<ISIP_TEMPLATE_TARGET>
(const MVector<ISIP_TEMPLATE_TARGET>&);
