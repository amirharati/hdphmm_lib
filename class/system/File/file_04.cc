// file: $isip/class/system/File/file_04.cc
// version: $Id: file_04.cc 4884 2000-09-20 13:06:57Z hamaker $
//

// isip include files
//
#include "File.h"
#include <SysString.h>

// method: getBMode
//
// arguments: none
//
// return: the byte-order mode of this file
//
// this method gets the actual byte-order mode of this file 
// -- BIG_ENDIAN or LITTLE_ENDIAN
//
File::BMODE File::getBMode() const {
  
  // if the mode is native, return the machine's byte-order
  //
  if (byte_mode_d == NATIVE) {
    return getMachineByteOrder();
  }
  
  // if the mode is swap, reverse the machine's byte-order
  //
  else if (byte_mode_d == SWAP) {
    if (getMachineByteOrder() == BIG_ENDIAN) {
      return LITTLE_ENDIAN;
    }
    else {
      return BIG_ENDIAN;
    }
  }
  
  // else return the byte_mode directly
  //
  return byte_mode_d;
}

// method: setBMode
//
// arguments:
//  BMODE byte_mode: (input) the byte-order mode to set
//
// return: a bool8 value indicating status
//
// this method sets the absolute byte-order of this file, it also sets the
// byte_swap flag
//
bool8 File::setBMode(BMODE byte_mode_a) {
  
  // if the input byte_mode is a relative order to the machine
  //
  if (byte_mode_a == NATIVE) {
    byte_mode_d = getMachineByteOrder();
    byte_swap_d = false;
    
    // exit gracefully
    //
    return true;
  }
  else if (byte_mode_a == SWAP) {
    if (getMachineByteOrder() == BIG_ENDIAN) {
      byte_mode_d = LITTLE_ENDIAN;
    }
    else {
      byte_mode_d = BIG_ENDIAN;
    }
    byte_swap_d = true;
    
    // exit gracefully
    //
    return true;
  }

  // else set the byte-order directly
  //
  byte_mode_d = byte_mode_a;
    
  // possibly set the swap flag
  //
  if (byte_mode_a != getMachineByteOrder()) {
    byte_swap_d = true;
  }
  else {
    byte_swap_d = false;
  }
    
  //  exit gracefully
  //
  return true;
}

// method: getMachineByteOrder
//
// arguments: none
//
// return: a bool8 value indicating status
//
// this method detects the machine's byte-order 
//
File::BMODE File::getMachineByteOrder() const {

  // declare a variable for testing
  //
  int16 w = 0x0001;
  char* byte = (char*)&w;
  
  // if the msb is set, this must be a little-endian machine
  //
  if (byte[0]) {
    return LITTLE_ENDIAN;
  }
  
  // else it must be a big-endian machine 
  //
  return BIG_ENDIAN;
}

// method: read
//
// arguments:
//  void* ptr: (output) buffer to write data
//  int32 size: (input) size of each element
//  int32 nelem: (input) number of elements
//  
// return: number of elements read
//
// this is buffered binary input, it reads nelem_a elements from file into
// array ptr_a, each element is of size_a
//
int32 File::read(void* ptr_a, int32 size_a, int32 nelem_a) {
  
  // do some error checking
  //
  if (ptr_a == (void*)NULL) {
    Error::handle(name(), L"read", Error::ARG, __FILE__, __LINE__);
    return BAD_COUNT;
  }
  
  if ((fp_d == (void*)NULL) || (mode_d == WRITE_ONLY)) {
    Error::handle(name(), L"read", Error::READ_CLOSED, __FILE__, __LINE__);
    return BAD_COUNT;
  }
  
  // call the system function
  //
  int32 n = ::fread(ptr_a, size_a, nelem_a, fp_d);

  // do byte swapping if necessary
  //
  if ((n > 0) && (byte_swap_d)) {
    if (!decode(ptr_a, size_a, n)) {
      return Error::handle(name(), L"read", ERR_DECODE, __FILE__, __LINE__);
    }
  }
  
  // return  the number of elements being read
  //
  return n;
}

// method: write
//
// arguments:
//  const void* ptr: (input) buffer of data
//  int32 size: (input) size of each element
//  int32 nelem: (input) number of elements
//  
// return: number of elements written
//
// this is buffered binary write, it writes nelem_a elements from array
// ptr_a into file, each element is of size_a
//
int32 File::write(const void* ptr_a, int32 size_a, int32 nelem_a) {

  // do some error checking
  //
  if (ptr_a == (void*)NULL) {
    Error::handle(name(), L"write", Error::ARG, __FILE__, __LINE__);
    return BAD_COUNT;
  }
  if (fp_d == (void*)NULL) {
    Error::handle(name(), L"write", Error::WRITE_CLOSED, __FILE__, __LINE__);
    return BAD_COUNT;
  }

  if (mode_d == READ_ONLY) {
    return Error::handle(name(), L"write", Error::MOD_READONLY,
			 __FILE__, __LINE__);
  }
  
  // call the system function, do byte swapping if necessary
  //
  int32 n = 0;
  
  if (byte_swap_d && (size_a % 2 == 0)) {
    
    static byte8 scratch[BUF_SIZE];
    int32 num_pass = BUF_SIZE / size_a;
    
    // loop until all data written
    //
    while (n < nelem_a) {
      
      // check underflow on the last write
      //
      if (num_pass > (nelem_a - n)) {
	num_pass = nelem_a - n;
      }

      // get the current position of the output buffer
      //
        /*
	  Casting to a Pointer should be done  with int64
	 */
      void* ptr = (void*)((int64)ptr_a + n * size_a);
      
      // encode the buffer
      //
      if (!encode(scratch, ptr, size_a, num_pass)) {
	return Error::handle(name(), L"write", ERR_DECODE,
			     __FILE__, __LINE__);
      }
      
      // write the buffer
      //
      n += ::fwrite(scratch, size_a, num_pass, fp_d);
    }
  }
  else {
    
    // just write the whole thing
    //
    n = ::fwrite(ptr_a, size_a, nelem_a, fp_d);
  }
  
  // return the number of elements being written
  //
  return n;
}

// method: encode
//
// arguments:
//  int16 arg: (input) value to be encoded
//
// return: encoded value
//
// encode an int16 integer
//
int16 File::encode(int16 arg_a) const {

  // define the return value
  //
  int16 ret = arg_a;
  
  // do byte swapping if necessary
  //
  if (byte_swap_d) {
    byte8* in = (byte8*)&arg_a;
    byte8* out = (byte8*)&ret;
    out[0] = in[1];
    out[1] = in[0];
  }

  // exit gracefully
  //
  return ret;
}

// method: encode
//
// arguments:
//  int32 arg: (input) value to be encoded
//
// return: encoded value
//
// encode an int32 integer
//
int32 File::encode(int32 arg_a) const {

  // define the return value
  //
  int32 ret = arg_a;
  
  // do byte swapping if necessary
  //
  if (byte_swap_d) {
    byte8* in = (byte8*)&arg_a;
    byte8* out = (byte8*)&ret;
    out[0] = in[3];
    out[1] = in[2];
    out[2] = in[1];
    out[3] = in[0];
  }

  // exit gracefully
  //
  return ret;
}

// method: encode
//
// arguments:
//  int64 arg: (input) value to be encoded
//
// return: encoded value
//
// encode an int64 integer
//
int64 File::encode(int64 arg_a) const {

  // define the return value
  //
  int64 ret = arg_a;
  
  // do byte swapping if necessary
  //
  if (byte_swap_d) {
    byte8* in = (byte8*)&arg_a;
    byte8* out = (byte8*)&ret;
    out[0] = in[7];
    out[1] = in[6];
    out[2] = in[5];
    out[3] = in[4];
    out[4] = in[3];
    out[5] = in[2];
    out[6] = in[1];
    out[7] = in[0];
  }

  // exit gracefully
  //
  return ret;
}

// method: decode
//
// arguments:
//  int16 arg: (input) value to be decoded
//
// return: decoded value
//
// decode an int16 integer
//
int16 File::decode(int16 arg_a) const {

  // define the return value
  //
  int16 ret = arg_a;
  
  // do byte swapping if necessary
  //
  if (byte_swap_d) {
    byte8* in = (byte8*)&arg_a;
    byte8* out = (byte8*)&ret;
    out[0] = in[1];
    out[1] = in[0];
  }

  // exit gracefully
  //
  return ret;
}

// method: decode
//
// arguments:
//  int32 arg: (input) value to be decoded
//
// return: decoded value
//
// decode an int32 integer
//
int32 File::decode(int32 arg_a) const {

  // define the return value
  //
  int32 ret = arg_a;
  
  // do byte swapping if necessary
  //
  if (byte_swap_d) {
    byte8* in = (byte8*)&arg_a;
    byte8* out = (byte8*)&ret;
    out[0] = in[3];
    out[1] = in[2];
    out[2] = in[1];
    out[3] = in[0];
  }

  // exit gracefully
  //
  return ret;
}

// method: decode
//
// arguments:
//  int64 arg: (input) value to be decoded
//
// return: decoded value
//
// decode an int64 integer
//
int64 File::decode(int64 arg_a) const {

  // define the return value
  //
  int64 ret = arg_a;
  
  // do byte swapping if necessary
  //
  if (byte_swap_d) {
    byte8* in = (byte8*)&arg_a;
    byte8* out = (byte8*)&ret;
    out[0] = in[7];
    out[1] = in[6];
    out[2] = in[5];
    out[3] = in[4];
    out[4] = in[3];
    out[5] = in[2];
    out[6] = in[1];
    out[7] = in[0];
  }

  // exit gracefully
  //
  return ret;
}

// method: decode
//
// arguments:
//  void* obuf: (output) buffer of decoded data
//  const void* ibuf: (input) buffer of data
//  int32 size: (input) size (in bytes) of data type
//  int32 nitems: (input) number of elements
//
// return: a bool8 value indicating status
//
// decode a buffer of data
//
bool8 File::decode(void* obuf_a, const void* ibuf_a,
		     int32 size_a, int32 nitems_a) const {
  
  // check arguments
  //
  if ((ibuf_a == NULL) || (obuf_a == NULL)
      || (size_a < 1) || (nitems_a < 1)) {
    return Error::handle(name(), L"decode", Error::ARG, __FILE__, __LINE__);
  }

  // if we need byte swap
  //
  if (byte_swap_d) {

    // branch on mode
    //
    if ((size_a % 8) == 0) {
      int64* idata = (int64*)ibuf_a;
      int64* odata = (int64*)obuf_a;
      for (int32 i = 0; i < (size_a * nitems_a / 8); i++) {
	odata[i] = decode(idata[i]);
      }
    }
    else if ((size_a % 4) == 0) {
      int32* idata = (int32*)ibuf_a;
      int32* odata = (int32*)obuf_a;
      for (int32 i = 0; i < (size_a * nitems_a / 4); i++) {
	odata[i] = decode(idata[i]);
      }
    }
    else if ((size_a % 2) == 0) {
      int16* idata = (int16*)ibuf_a;
      int16* odata = (int16*)obuf_a;
      for (int32 i = 0; i < (size_a * nitems_a / 2); i++) {
	odata[i] = decode(idata[i]);
      }
    }
  }
  else {
    return Error::handle(name(), L"decode", ERR_DECODE, __FILE__, __LINE__);
  }
  
  // exit gracefully
  //
  return true;
}

// method: encode
//
// arguments:
//  void* obuf: (output) buffer of encoded data
//  const void* ibuf: (input) buffer of data
//  int32 size: (input) size (in bytes) of data type
//  int32 nitems: (input) number of elements
//
// return: a bool8 value indicating status
//
// encode a buffer of data
//
bool8 File::encode(void* obuf_a, const void* ibuf_a,
		     int32 size_a, int32 nitems_a) const {

  // check arguments
  //
  if ((ibuf_a == NULL)|| (obuf_a == NULL)
      || (size_a < 1) || (nitems_a < 1)) {
    return Error::handle(name(), L"encode", Error::ARG, __FILE__, __LINE__);
  }
  
  // if we need byte swap
  //
  if (byte_swap_d) {

    // branch on mode
    //
    if ((size_a % 8) == 0) {
      int64* idata = (int64*)ibuf_a;
      int64* odata = (int64*)obuf_a;
      for (int32 i = 0; i < (size_a * nitems_a / 8); i++) {
	odata[i] = encode(idata[i]);
      }
    }
    else if ((size_a % 4) == 0) {
      int32* idata = (int32*)ibuf_a;
      int32* odata = (int32*)obuf_a;
      for (int32 i = 0; i < (size_a * nitems_a / 4); i++) {
	odata[i] = encode(idata[i]);
      }
    }
    else if ((size_a % 2) == 0) {
      int16* idata = (int16*)ibuf_a;
      int16* odata = (int16*)obuf_a;
      for (int32 i = 0; i < (size_a * nitems_a / 2); i++) {
	odata[i] = encode(idata[i]);
      }
    }
  }
  else {
    return Error::handle(name(), L"encode", ERR_DECODE, __FILE__, __LINE__);
  }

  // exit gracefully
  //
  return true;
}
