// file: $isip/class/system/SysString/sstr_03.cc
// version: $Id: sstr_03.cc 10564 2006-04-22 03:06:55Z may $
//
// notes:
//
// (1) AH (07/27/2010): We have updated definition for "get" functions to prevent
//     occuring segementation fault on 64-bit Machines. The problem was related to
//     sscanf function, to sollve the problem we have used 64-bit types as intermediate
//     type to read from sscanf. In the futute, when 128-bit Machines became availible,
//     we might need to update this  part  again and use 128-bit Intemediate types instead of
//     64-bit types

// system include files
//  note that we need some basic string functions. these are not included
//  in Integral.h since users are not expected to use these functions.
//
#include <strings.h>

// isip include files
//
#include "SysString.h"
#include <Console.h>
// we need at least two static buffers. one current one, and one
// previous one.
//
static byte8* buff[2] = {(byte8*)NULL, (byte8*)NULL};

// buf_offset points to the next available position within the current
// static buffer
///*
static int64 buf_offset = 0;

// buf_size is the size of the current static buffer
///*
static int64 buf_size = 0;

// buf_index indicates which buffer is current. this probably will
// never change, only if the user tries to get a really large buffer. 
///*
static int64 buf_index = 0;

// method: assign
//
// arguments:
//  const SysString& arg: (input) string to copy
//
// return: a bool8 value indicating status
//
// assign object to arg_a
//
bool8 SysString::assign(const SysString& arg_a) {

  // if these two SysString are already the same, do nothing
  //
  if (value_d == arg_a.value_d) {
    return true;
  }
  
  // possibly delete previous values
  //
  clear(Integral::RESET);
  
  // allocate a bigger buffer if necessary
  //
  if (arg_a.length() > capacity_d) {
    freeMem();
    capacity_d = arg_a.length();
    allocateMem();
  }    
    
  // copy over the contents of the source string
  //
  if (arg_a.length() > 0) {
   MemoryManager::memcpy(value_d, arg_a.value_d,
      sizeof(unichar) * (arg_a.length() + 1)); 
  }

  // exit gracefully
  //
  return true;
}

// method: assign
//
// arguments:
//  const unichar* data: (input) buffer of data
//
// return: a bool8 value indicating status
//
// assign object to data_a
//
bool8 SysString::assign(const unichar* data_a) {

  // possibly free previous values
  //
  clear(Integral::RESET);
  
  // copy over the buffer into our string
  //
  if ((data_a != (unichar*)NULL) && (isip_wcslen(data_a) > 0)) {

   
    // allocate more memory if necessary
    //
    if ((int64)isip_wcslen(data_a) > capacity_d) {
      freeMem();
      capacity_d = isip_wcslen(data_a);
      allocateMem();
    }

    // copy over the buffer
    //
    
    isip_wcscpy(value_d, data_a);
 

  }

  // exit gracefully
 
  return true;
}

// method: assign
//
// arguments:
//  const byte8* data: (input) buffer of data
//  int32 max_size: (input) maximum number of characters to read
//  SysChar::ENCODE encoding: (input) what encoding scheme to use
//
// return: a bool8 value indicating status
//
// assign object to this byte8* of data
//

bool8 SysString::assign(const byte8* data_a, int32 max_size_a,
			  SysChar::ENCODE encoding_a) {

  // possibly free previous values
  //
  clear(Integral::RESET);

  // copy over the buffer into our string
  //
  if ((data_a != (byte8*)NULL) && (strlen((char*)data_a) > 0)) {

    // declare local variables
    //
    SysChar c;
    int32 len;

    // we need a static buffer of unicode characters. this is done so
    // the resultant string need not hold as much memory as max_size_a
    //
    static int32 buf_len = BIG_BUFFER_LENGTH;
    static unichar* buf =
      (unichar*)MemoryManager::newStatic(buf_len * sizeof(unichar));

    // possibly increase the size of our buffer
    //
    if (max_size_a > buf_len) {
      MemoryManager::deleteStatic(buf);
      buf_len = max_size_a;
      buf = (unichar*)MemoryManager::newStatic(buf_len * sizeof(unichar));
    }

    // initialize the buffer to a null string
    //
    buf[0] = (unichar)NULL;

    // convert and copy characters
    //
    int32 i;
    for (i = 0; (i < max_size_a) && (*data_a != (byte8)NULL); i++) {
      if (!c.assign(len, data_a, encoding_a)) {
	return Error::handle(name(), L"assign", SysChar::ERR,
			     __FILE__, __LINE__, Error::WARNING);
      }
      buf[i] = (unichar)c;
      data_a += len;
    }
    buf[i] = (unichar)NULL;
    
    // test overflow
    //
    if (i == max_size_a) {
      Error::handle(name(), L"assign", Error::MEM_OFLOW,
		    __FILE__, __LINE__, Error::WARNING);
    }
    
    // assign our string to be this buffer of unichar's
    //
    return assign(buf);
  }

  // exit gracefully
  //
  return true;
}

// method: assign
//
// arguments:
//  const SysString& arg: (input) string to copy
//  const unichar* fmt: (input) format string
//
// return: a bool8 value indicating status
//
// assign object to arg_a using format string. the %s will be replaced
// by a wide character string.
//
bool8 SysString::assign(const SysString& arg_a, const unichar* fmt_a) {

  // if these two SysString are already the same, do nothing
  //
  if (value_d == arg_a.value_d) {
    return true;
  }

  static byte8 buf[MAX_LENGTH];
  SysString fmt(fmt_a);

  // possibly delete previous values
  //
  clear(Integral::RESET);

  // create and possibly assign the string
  //
  if (sprintf((char*)buf,(char*)(byte8*)fmt, (char*)(byte8*)arg_a) > 0) {
    return assign((byte8*)buf);
  }

  // exit gracefully
  //
  return false;
}

// method: assign
//
// arguments:
//  const unichar* data: (input) buffer of data
//  const unichar* fmt: (input) print format
//
// return: a bool8 value indicating status
//
// assign object to data_a
//
bool8 SysString::assign(const unichar* data_a, const unichar* fmt_a) {

  // create the string
  //
  SysString ws;
  ws.assign(data_a);
  
  // apply the format
  //
  return assign(ws, fmt_a);
}

// method: assign
//
// arguments:
//  const byte8* data: (input) buffer of data
//  const unichar* fmt: (input) print format
//  int32 max_size: (input) maximum number of characters to read
//  SysChar::ENCODE encoding: (input) what encoding scheme to use
//
// return: a bool8 value indicating status
//
// assign object to this byte8* of data
//
bool8 SysString::assign(const byte8* data_a, const unichar* fmt_a,
			  int32 max_size_a, SysChar::ENCODE encoding_a) {

  // create the string
  //
  SysString ws;
  ws.assign(data_a, max_size_a, encoding_a);

  // apply the format
  //
  return assign(ws, fmt_a);
}

// method: swap
//
// arguments:
//  SysString& arg: (input) string to swap with
//
// return: a bool8 value indicating status
//
// assign object to arg_a, and arg_a to object. this is done in a very
// memory-efficient manner.
//
bool8 SysString::swap(SysString& arg_a) {
  
  // we need temporary place-holders
  //
  int32 temp_cap;
  unichar* temp_val;
  
  // make temp be a memory-copy of arg
  //
  temp_cap = arg_a.capacity_d;
  temp_val = arg_a.value_d;
  
  // make arg be a memory-copy of *this
  //
  arg_a.capacity_d = capacity_d;
  arg_a.value_d = value_d;
  
  // make *this be a memory-copy of temp (was arg)
  //
  capacity_d = temp_cap;
  value_d = temp_val;
  
  // exit gracefully
  //
  return true;
}

// method: assign
//
// arguments:
//  const void* arg: (input) pointer to convert
//
// return: a bool8 value indicating status
//
// convert a pointer into a string
//
bool8 SysString::assign(const void* arg_a) {

  // allocate a static buffer for printing
  //
  static char buf[MAX_LENGTH];

  // clear out the current value
  //
  clear(Integral::RESET);

  // if the pointer is null, return that string
  //
  if (arg_a == NULL) {
    return assign((unichar*)NULL_PTR);
  }
  
  // create and possibly assign the string
  //
  if (sprintf(buf, DEF_FMT_VOIDP_8BIT, arg_a) > 0) {
    return assign((byte8*)buf);
  }
    
  // exit gracefully
  //
  return false;
}

// method: assign
//
// arguments:
//  bool8 arg: (input) number to convert
//
// return: a bool8 value indicating status
//
// convert a bool8 value into a string
//
bool8 SysString::assign(bool8 arg_a) {

  // we check for specific values in this case to prevent an
  // out-of-bounds value from being accepted as a bool8.
  //
  if (arg_a) {
    assign((unichar*)BOOL_TRUE);
    return true;
  }
  else {
    assign((unichar*)BOOL_FALSE);
    return true;    
  }

  // exit ungracefully
  //
  return false;
}

// method: assign
//
// arguments:
//  byte8 arg: (input) number to convert
//
// return: a bool8 value indicating status
//
// convert a byte8 integer into a string
//
bool8 SysString::assign(byte8 arg_a) {

  // allocate a static buffer for printing
  //
  static char buf[MAX_LENGTH];

  // clear out the current value
  //
  clear(Integral::RESET);
  
  // create and possibly assign the string
  //
  if (sprintf(buf, DEF_FMT_LONG_8BIT, (uint32)arg_a) > 0) {
    assign((byte8*)buf);
    return true;
  }
    
  // exit gracefully
  //
  return false;
}

// method: assign
//
// arguments:
//  unichar arg: (input) character to assign to string
//
// return: a bool8 value indicating status
//
// assign object to arg_a
//
bool8 SysString::assign(unichar arg_a) {
  
  // first clear out the string
  //
  clear(Integral::RESET);

  // make sure we have the capacity to hold a single character
  //
  if (capacity_d < 1) {
    setCapacity(1);
  }

  // assign the character
  //
  value_d[0] = arg_a;

  // terminate the string
  //
  value_d[1] = (unichar)NULL;
  
  // exit gracefully
  //
  return true;
}

// method: assign
//
// arguments:
//  uint16 arg: (input) number to convert
//
// return: a bool8 value indicating status
//
// convert an unsigned int16 integer into a string
//
bool8 SysString::assign(uint16 arg_a) {

  // allocate a static buffer for printing
  //
  static char buf[MAX_LENGTH];

  // clear out the current value
  //
  clear(Integral::RESET);
  
  // create and possibly assign the string
  //
  if (sprintf(buf, DEF_FMT_ULONG_8BIT, arg_a) > 0) {
    assign((byte8*)buf);
    return true;
  }
    
  // exit gracefully
  //
  return false;
}

// method: assign
//
// arguments:
//  uint32 arg: (input) number to convert
//
// return: a bool8 value indicating status
//
// convert an unsigned int32 integer into a string
//
bool8 SysString::assign(uint32 arg_a) {

  // allocate a static buffer for printing
  //
  static char buf[MAX_LENGTH];

  // clear out the current value
  //
  clear(Integral::RESET);
  
  // create and possibly assign the string
  //
  if (sprintf(buf, DEF_FMT_ULONG_8BIT, arg_a) > 0) {
    assign((byte8*)buf);
    return true;
  }
    
  // exit gracefully
  //
  return false;
}

// method: assign
//
// arguments:
//  uint64 arg: (input) number to convert
//
// return: a bool8 value indicating status
//
// convert an unsigned int64  integer into a string
//
bool8 SysString::assign(uint64 arg_a) {

  // allocate a static buffer for printing
  //
  static char buf[MAX_LENGTH];

  // clear out the current value
  //
  clear(Integral::RESET);
  
  // create and possibly assign the string
  //
  if (sprintf(buf, DEF_FMT_ULLONG_8BIT, arg_a) > 0) {
    assign((byte8*)buf);
    return true;
  }
    
  // exit gracefully
  //
  return false;
}

// method: assign
//
// arguments:
//  int16 arg: (input) number to convert
//
// return: a bool8 value indicating status
//
// convert a int16 integer into a string
//
bool8 SysString::assign(int16 arg_a) {

  // allocate a static buffer for printing
  //
  static char buf[MAX_LENGTH];

  // clear out the current value
  //
  clear(Integral::RESET);
  
  // create and possibly assign the string
  //
  if (sprintf(buf, DEF_FMT_LONG_8BIT, arg_a) > 0) {
    assign((byte8*)buf);
    return true;
  }
    
  // exit gracefully
  //
  return false;
}

// method: assign
//
// arguments:
//  int32 arg: (input) number to convert
//
// return: a bool8 value indicating status
//
// convert a int32 integer into a string
//
bool8 SysString::assign(int32 arg_a) {

  // allocate a static buffer for printing
  //
  static char buf[MAX_LENGTH];

  // clear out the current value
  //
  clear(Integral::RESET);
  
  // create and possibly assign the string
  //
  if (sprintf(buf, DEF_FMT_LONG_8BIT, arg_a) > 0) {
    assign((byte8*)buf);
    return true;
  }
    
  // exit gracefully
  //
  return false;
}

// method: assign
//
// arguments:
//  int64 arg: (input) number to convert
//
// return: a bool8 value indicating status
//
// convert a long long integer into a string
//
bool8 SysString::assign(int64 arg_a) {

  // allocate a static buffer for printing
  //
  static char buf[MAX_LENGTH];
  
  // clear out the current value
  //
  clear(Integral::RESET);
  
  // create and possibly assign the string
  //
  if (sprintf(buf, DEF_FMT_LLONG_8BIT, arg_a) > 0) {
    assign((byte8*)buf);
    return true;
  }
    
  // exit gracefully
  //
  return false;
}

// method: assign
//
// arguments:
//  float32 arg: (input) number to convert
//
// return: a bool8 value indicating status
//
// convert a float64 precision floating point number into a string
//
bool8 SysString::assign(float32 arg_a) {

  // allocate a static buffer for printing
  //
  static char buf[MAX_LENGTH];

  // clear out the current value
  //
  clear(Integral::RESET);
  
  // create and possibly assign the string
  //
  if (sprintf(buf, DEF_WFMT_FLOAT_8BIT, arg_a) > 0) {
    assign((byte8*)buf);
    return true;
  }
    
  // exit gracefully
  //
  return false;
}

// method: assign
//
// arguments:
//  float64 arg: (input) number to convert
//
// return: a bool8 value indicating status
//
// convert a float64 precision floating point number into a string
//
bool8 SysString::assign(float64 arg_a) {

  // allocate a static buffer for printing
  //
  static char buf[MAX_LENGTH];

  // clear out the current value
  //
  clear(Integral::RESET);
  
  // create and possibly assign the string
  //
  if (sprintf(buf, DEF_WFMT_DOUBLE_8BIT, arg_a) > 0) {
    assign((byte8*)buf);
    return true;
  }
    
  // exit gracefully
  //
  return false;
}

// method: assign
//
// arguments:
//  const SysComplex<TIntegral>& arg: (input) value to print
//
// return: a bool8 value indicating status
//
// convert a complex number into a string
//
template <class TIntegral>
bool8 SysString::assign(const SysComplex<TIntegral>& arg_a) {

  // covert the real part into string
  //
  assign(arg_a.real());

  // case: image part is nonnegative
  //
  if (arg_a.imag() >= 0) {
    concat(L"+");
  }

  // convert the image part into string
  //
  concat(arg_a.imag());

  // concat the identification j and exit gracefully
  //
  return concat(L"j");
}

// explicit instantiations for complex types
//
template
bool8 SysString::assign<float32>(const SysComplex<float32>&);

template
bool8 SysString::assign<float64>(const SysComplex<float64>&);

template
bool8 SysString::assign<int32>(const SysComplex<int32>&);


// ----

// method: assign
//
// arguments:
//  const void* arg: (input) pointer to convert
//  const unichar* fmt: (input) print format
//
// return: a bool8 value indicating status
//
// convert a pointer into a string
//
bool8 SysString::assign(const void* arg_a, const unichar* fmt_a) {

  // allocate a static buffer for printing
  //
  static char buf[MAX_LENGTH];
  static char fmt[MAX_LENGTH];
  static char* fmt_ptr;

  // check the arguments
  //
  if (fmt_a == (unichar*)NULL) {
    return Error::handle(name(), L"assign", Error::ARG, __FILE__, __LINE__);
  }

  SysString temp(fmt_a);
  
  // clear out the current value
  //
  clear(Integral::RESET);

  // if the pointer is null, return that string
  //
  if (arg_a == NULL) {
    SysString p1(L"%p");
    SysString r1(L"%s");
    temp.replace(p1, r1);
    return assign(NULL_PTR, (unichar*)temp);
  }

  temp.getBuffer((byte8*)fmt, MAX_LENGTH);
  fmt_ptr = fmt;
  
  // create and possibly assign the string
  //
  if (sprintf(buf, fmt_ptr, arg_a) > 0) {
    return assign((byte8*)buf);
  }
    
  // exit gracefully
  //
  return false;
}

// method: assign
//
// arguments:
//  bool8 arg: (input) number to convert
//  const unichar* fmt: (input) print format
//
// return: a bool8 value indicating status
//
// convert a bool8 value into a string. note that the format should
// include a %s.
//
bool8 SysString::assign(bool8 arg_a, const unichar* fmt_a) {

  // first convert to a string
  //
  SysString b;
  b.assign(arg_a);

  // now apply the format
  //
  return assign(b, fmt_a);
}

// method: assign
//
// arguments:
//  byte8 arg: (input) number to convert
//  const unichar* fmt: (input) print format
//
// return: a bool8 value indicating status
//
// convert a byte8 integer into a string
//
bool8 SysString::assign(byte8 arg_a, const unichar* fmt_a) {

  // allocate a static buffer for printing
  //
  static char buf[MAX_LENGTH];
  static char fmt[MAX_LENGTH];
  static char* fmt_ptr;

  // check the arguments
  //
  if (fmt_a == (unichar*)NULL) {
    return Error::handle(name(), L"assign", Error::ARG, __FILE__, __LINE__);
  }

  SysString temp(fmt_a);
  temp.getBuffer((byte8*)fmt, MAX_LENGTH);
  fmt_ptr = fmt;
  
  // clear out the current value
  //
  clear(Integral::RESET);
  
  // create and possibly assign the string
  //
  if (sprintf(buf, fmt_ptr, (uint32)arg_a) > 0) {
    assign((byte8*)buf);
    return true;
  }
    
  // exit gracefully
  //
  return false;
}

// method: assign
//
// arguments:
//  unichar arg: (input) character to assign to string
//  const unichar* fmt: (input) print format
//
// return: a bool8 value indicating status
//
// assign object to arg_a
//
bool8 SysString::assign(unichar arg_a, const unichar* fmt_a) {

  // allocate a static buffer for printing
  //
  static char buf[MAX_LENGTH];
  static char fmt[MAX_LENGTH];
  static char* fmt_ptr;

  // check the arguments
  //
  if (fmt_a == (unichar*)NULL) {
    return Error::handle(name(), L"assign", Error::ARG, __FILE__, __LINE__);
  }

  SysString temp(fmt_a);
  temp.getBuffer((byte8*)fmt, MAX_LENGTH);
  fmt_ptr = fmt;
  
  // clear out the current value
  //
  clear(Integral::RESET);
  
  // create and possibly assign the string
  //
  if (sprintf(buf, fmt_ptr, (char)arg_a) > 0) {
    assign((byte8*)buf);
    return true;
  }
    
  // exit gracefully
  //
  return false;
}

// method: assign
//
// arguments:
//  uint16 arg: (input) number to convert
//  const unichar* fmt: (input) print format
//
// return: a bool8 value indicating status
//
// convert an unsigned int16 integer into a string
//
bool8 SysString::assign(uint16 arg_a, const unichar* fmt_a) {

  // allocate a static buffer for printing
  //
  static char buf[MAX_LENGTH];
  static char fmt[MAX_LENGTH];
  static char* fmt_ptr;

  // check the arguments
  //
  if (fmt_a == (unichar*)NULL) {
    return Error::handle(name(), L"assign", Error::ARG, __FILE__, __LINE__);
  }

  SysString temp(fmt_a);
  temp.getBuffer((byte8*)fmt, MAX_LENGTH);
  fmt_ptr = fmt;
  
  // clear out the current value
  //
  clear(Integral::RESET);
  
  // create and possibly assign the string
  //
  if (sprintf(buf, fmt_ptr, arg_a) > 0) {
    assign((byte8*)buf);
    return true;
  }
    
  // exit gracefully
  //
  return false;
}

// method: assign
//
// arguments:
//  uint32 arg: (input) number to convert
//  const unichar* fmt: (input) print format
//
// return: a bool8 value indicating status
//
// convert an unsigned int32 integer into a string
//
bool8 SysString::assign(uint32 arg_a, const unichar* fmt_a) {

  // allocate a static buffer for printing
  //
  static char buf[MAX_LENGTH];
  static char fmt[MAX_LENGTH];
  static char* fmt_ptr;
  
  // check the arguments
  //
  if (fmt_a == (unichar*)NULL) {
    return Error::handle(name(), L"assign", Error::ARG, __FILE__, __LINE__);
  }

  SysString temp(fmt_a);
  
  temp.getBuffer((byte8*)fmt, MAX_LENGTH);
  fmt_ptr = fmt;
  
  // clear out the current value
  //
  clear(Integral::RESET);
  
  // create and possibly assign the string
  //
  if (sprintf(buf, fmt_ptr, arg_a) > 0) {
    assign((byte8*)buf);
    return true;
  }
    
  // exit gracefully
  //
  return false;
}

// method: assign
//
// arguments:
//  uint64 arg: (input) number to convert
//  const unichar* fmt: (input) print format
//
// return: a bool8 value indicating status
//
// convert an unsigned int64 integer into a string
//
bool8 SysString::assign(uint64 arg_a, const unichar* fmt_a) {

  // allocate a static buffer for printing
  //
  static char buf[MAX_LENGTH];
  static char fmt[MAX_LENGTH];
  static char* fmt_ptr;

  // check the arguments
  //
  if (fmt_a == (unichar*)NULL) {
    return Error::handle(name(), L"assign", Error::ARG, __FILE__, __LINE__);
  }

  SysString temp(fmt_a);
  temp.getBuffer((byte8*)fmt, MAX_LENGTH);
  fmt_ptr = fmt;
  
  // clear out the current value
  //
  clear(Integral::RESET);
  
  // create and possibly assign the string
  //
  if (sprintf(buf, fmt_ptr, arg_a) > 0) {
    assign((byte8*)buf);
    return true;
  }
    
  // exit gracefully
  //
  return false;
}

// method: assign
//
// arguments:
//  int16 arg: (input) number to convert
//  const unichar* fmt: (input) print format
//
// return: a bool8 value indicating status
//
// convert a int16 integer into a string
//
bool8 SysString::assign(int16 arg_a, const unichar* fmt_a) {

  // allocate a static buffer for printing
  //
  static char buf[MAX_LENGTH];
  static char fmt[MAX_LENGTH];
  static char* fmt_ptr;

  if (fmt_a == (unichar*)NULL) {
    return Error::handle(name(), L"assign", Error::ARG, __FILE__, __LINE__);
  }

  SysString temp(fmt_a);
  temp.getBuffer((byte8*)fmt, MAX_LENGTH);
  fmt_ptr = fmt;
  
  // clear out the current value
  //
  clear(Integral::RESET);
  
  // create and possibly assign the string
  //
  if (sprintf(buf, fmt_ptr, arg_a) > 0) {
    assign((byte8*)buf);
    return true;
  }
    
  // exit gracefully
  //
  return false;
}

// method: assign
//
// arguments:
//  int32 arg: (input) number to convert
//  const unichar* fmt: (input) print format
//
// return: a bool8 value indicating status
//
// convert a int32 integer into a string
//
bool8 SysString::assign(int32 arg_a, const unichar* fmt_a) {

  // allocate a static buffer for printing
  //
  static char buf[MAX_LENGTH];
  static char fmt[MAX_LENGTH];
  static char* fmt_ptr;

  // check the arguments
  //  
  if (fmt_a == (unichar*)NULL) {
    return Error::handle(name(), L"assign", Error::ARG, __FILE__, __LINE__);
  }
 
  SysString temp(fmt_a);
  
  temp.getBuffer((byte8*)fmt, MAX_LENGTH);
  fmt_ptr = fmt;
 
  // clear out the current value
  //
  clear(Integral::RESET);
  
  // create and possibly assign the string
  //
  if (sprintf(buf, fmt_ptr, arg_a) > 0) {
    assign((byte8*)buf);
    return true;
  }
    
  // exit gracefully
  //
  return false;
}

// method: assign
//
// arguments:
//  int64 arg: (input) number to convert
//  const unichar* fmt: (input) print format
//
// return: a bool8 value indicating status
//
// convert a long long integer into a string
//
bool8 SysString::assign(int64 arg_a, const unichar* fmt_a) {

  // allocate a static buffer for printing
  //
  static char buf[MAX_LENGTH];
  static char fmt[MAX_LENGTH];
  static char* fmt_ptr;

  // check the arguments
  //  
  if (fmt_a == (unichar*)NULL) {
    return Error::handle(name(), L"assign", Error::ARG, __FILE__, __LINE__);
  }

  SysString temp(fmt_a);
  temp.getBuffer((byte8*)fmt, MAX_LENGTH);
  fmt_ptr = fmt;
  
  // clear out the current value
  //
  clear(Integral::RESET);
  
  // create and possibly assign the string
  //
  if (sprintf(buf, fmt_ptr, arg_a) > 0) {
    assign((byte8*)buf);
    return true;
  }
    
  // exit gracefully
  //
  return false;
}

// method: assign
//
// arguments:
//  float32 arg: (input) number to convert
//  const unichar* fmt: (input) print format
//
// return: a bool8 value indicating status
//
// convert a float64 precision floating point number into a string
//
bool8 SysString::assign(float32 arg_a, const unichar* fmt_a) {

  // allocate a static buffer for printing
  //
  static char buf[MAX_LENGTH];
  static char fmt[MAX_LENGTH];
  static char* fmt_ptr;

  // check the arguments
  //
  if (fmt_a == (unichar*)NULL) {
    return Error::handle(name(), L"assign", Error::ARG, __FILE__, __LINE__);
  }

  SysString temp(fmt_a);
  temp.getBuffer((byte8*)fmt, MAX_LENGTH);
  fmt_ptr = fmt;

  // clear out the current value
  //
  clear(Integral::RESET);
  
  // create and possibly assign the string
  //
  if (sprintf(buf, fmt_ptr, arg_a) > 0) {
    assign((byte8*)buf);
    return true;
  }
    
  // exit gracefully
  //
  return false;
}

// method: assign
//
// arguments:
//  float64 arg: (input) number to convert
//  const unichar* fmt: (input) print format
//
// return: a bool8 value indicating status
//
// convert a float64 precision floating point number into a string
//
bool8 SysString::assign(float64 arg_a, const unichar* fmt_a) {

  // allocate a static buffer for printing
  //
  static char buf[MAX_LENGTH];
  static char fmt[MAX_LENGTH];
  static char* fmt_ptr;

  // check the arguments
  //
  if (fmt_a == (unichar*)NULL) {
    return Error::handle(name(), L"assign", Error::ARG, __FILE__, __LINE__);
  }

  SysString temp(fmt_a);
  temp.getBuffer((byte8*)fmt, MAX_LENGTH);
  fmt_ptr = fmt;
  
  // clear out the current value
  //
  clear(Integral::RESET);
  
  // create and possibly assign the string
  //
  if (sprintf(buf, fmt_ptr, arg_a) > 0) {
    assign((byte8*)buf);
    return true;
  }
    
  // exit gracefully
  //
  return false;
}

// method: assign
//
// arguments:
//  const SysComplex<TIntegral>& arg: (input) value to print
//  const unichar* fmt: (input) print format
//
// return: a bool8 value indicating status
//
// convert a complex number into a string
//
template <class TIntegral>
bool8 SysString::assign(const SysComplex<TIntegral>& arg_a,
			  const unichar* fmt_a) {

  // first assign to string
  //
  SysString c;
  c.assign(arg_a);

  // now apply the format
  //
  return assign(c, fmt_a);
}

// explicit instantiations for complex types
//
template
bool8 SysString::assign<float32>(const SysComplex<float32>&, const unichar*);

template
bool8 SysString::assign<float64>(const SysComplex<float64>&, const unichar*);

template
bool8 SysString::assign<int32>(const SysComplex<int32>&, const unichar*);

// method: assign
//
// arguments:
//  Integral::DEBUG arg: (input) value to print
//
// return: a bool8 value indicating status
//
// convert a debug level into a string
//
bool8 SysString::assign(Integral::DEBUG arg_a) {

  // branch on debug level and assign
  //
  if (arg_a == Integral::NONE) {
    assign(DBG_NONE);
  }
  else if (arg_a == Integral::BRIEF) {
    assign(DBG_BRIEF);
  }
  else if (arg_a == Integral::DETAILED) {
    assign(DBG_DETAILED);
  }
  else if (arg_a == Integral::ALL) {
    assign(DBG_ALL);
  }
  else {
    return Error::handle(name(), L"assign", Error::ARG, __FILE__, __LINE__);
  }
  
  // exit gracefully
  //
  return true;
}

// method: assign
//
// arguments:
//  Integral::COMPARE arg: (input) value to print
//
// return: a bool8 value indicating status
//
// convert a compare level into a string
//
bool8 SysString::assign(Integral::COMPARE arg_a) {

  // branch on compare level and assign
  //
  if (arg_a == Integral::EQUAL) {
    assign(CMP_EQUAL);
  }
  else if (arg_a == Integral::GREATER) {
    assign(CMP_GREATER);
  }
  else if (arg_a == Integral::LESSER) {
    assign(CMP_LESSER);
  }
  else {
    return Error::handle(name(), L"assign", Error::ARG, __FILE__, __LINE__);
  }
  
  // exit gracefully
  //
  return true;
}

// method: assign
//
// arguments:
//  File::MODE arg: (input) value to print
//
// return: a bool8 value indicating status
//
// convert a compare level into a string
//
bool8 SysString::assign(File::MODE arg_a) {

  // branch on file modes and assign
  //
  if (arg_a == File::READ_ONLY) {
    assign(MODE_READ_ONLY);
  }
  else if (arg_a == File::READ_PLUS) {
    assign(MODE_READ_PLUS);
  }
  else if (arg_a == File::WRITE_ONLY) {
    assign(MODE_WRITE_ONLY);
  }
  else if (arg_a == File::WRITE_PLUS) {
    assign(MODE_WRITE_PLUS);
  }
  else if (arg_a == File::APPEND_ONLY) {
    assign(MODE_APPEND_ONLY);
  }
  else if (arg_a == File::APPEND_PLUS) {
    assign(MODE_APPEND_PLUS);
  }
  else {
    return Error::handle(name(), L"assign", Error::ARG, __FILE__, __LINE__);
  }
  
  // exit gracefully
  //
  return true;
}

// method: assign
//
// arguments:
//  File::BMODE arg: (input) value to print
//
// return: a bool8 value indicating status
//
// convert a file binary mode into a string
//
bool8 SysString::assign(File::BMODE arg_a) {

  // branch on binary modes and assign
  //
  if (arg_a == File::NATIVE) {
    assign(BMODE_NATIVE);
  }
  else if (arg_a == File::SWAP) {
    assign(BMODE_SWAP);
  }
  else if (arg_a == File::BIG_ENDIAN) {
    assign(BMODE_BIG_ENDIAN);
  }
  else if (arg_a == File::LITTLE_ENDIAN) {
    assign(BMODE_LITTLE_ENDIAN);
  }
  else {
    return Error::handle(name(), L"assign", Error::ARG, __FILE__, __LINE__);
  }
  
  // exit gracefully
  //
  return true;
}

// method: assign
//
// arguments:
//  File::TYPE arg: (input) value to print
//
// return: a bool8 value indicating status
//
// convert a compare level into a string
//
bool8 SysString::assign(File::TYPE arg_a) {

  // branch on file type and assign
  //
  if (arg_a == File::TEXT) {
    assign(TYPE_TEXT);
  }
  else if (arg_a == File::BINARY) {
    assign(TYPE_BINARY);
  }
  else {
    return Error::handle(name(), L"assign", Error::ARG, __FILE__, __LINE__);
  }
  
  // exit gracefully
  //
  return true;
}

// method: assign
//
// arguments:
//  SysChar::ENCODE arg: (input) value to print
//
// return: a bool8 value indicating status
//
// convert a encoding into a string
//
bool8 SysString::assign(SysChar::ENCODE arg_a) {

  // branch on encodes and assign
  //
  if (arg_a == SysChar::ENCODE_ASCII) {
    assign(ENCODE_ASCII);
  }
  else if (arg_a == SysChar::ENCODE_UTF8) {
    assign(ENCODE_UTF8);
  }
  else if (arg_a == SysChar::ENCODE_UTF16) {
    assign(ENCODE_UTF16);
  }
  else {
    return Error::handle(name(), L"assign", Error::ARG, __FILE__, __LINE__);
  }
  
  // exit gracefully
  //
  return true;
}

// method: assign
//
// arguments:
//  MemoryManager::MODE arg: (input) value to print
//
// return: a bool8 value indicating status
//
// convert a file binary mode into a string
//
bool8 SysString::assign(MemoryManager::MODE arg_a) {

  // branch on modes and assign
  //
  if (arg_a == MemoryManager::OPTIMIZE) {
    assign(MMGR_MODE_OPTIMIZE);
  }
  else if (arg_a == MemoryManager::TRACK) {
    assign(MMGR_MODE_TRACK);
  }
  else {
    return Error::handle(name(), L"assign", Error::ARG, __FILE__, __LINE__);
  }
  
  // exit gracefully
  //
  return true;
}
// method: getBuffer
//
// arguments:
//  unichar* data: (output) buffer of data
//  int32 len: (input) maximum number of characters to copy
//
// return: number of characters in buffer
//
// this method returns object data in data* buffer
//*
int64 SysString::getBuffer(unichar* data_a, int32 len_a) const {

  // check the arguments
  //
  if (data_a == (unichar*)NULL) {
    return Error::handle(name(), L"getBuffer", Error::ARG, __FILE__, __LINE__);
  }

  // copy over the buffer
  //
  isip_wcsncpy(data_a, value_d, (len_a - 1));
  //
  data_a[len_a - 1] = (unichar)NULL;
  
  // return the length
  //
  return isip_wcslen(data_a);
}

// method: getBuffer
//
// arguments:
//  byte8* data: (output) buffer of data
//  int32 len: (input) maximum number of characters to copy
//  SysChar::ENCODE encoding: (input) what encoding to use
//
// return: number of byte8s in buffer
//
// this method passes the objects data back in a buffer, encoded as specified
//*
int64 SysString::getBuffer(byte8* data_a, int32 len_a,
			  SysChar::ENCODE encoding_a) const {

  // check the arguments
  //
  if (data_a == (byte8*)NULL) {
    return Error::handle(name(), L"getBuffer", Error::ARG, __FILE__, __LINE__);
  }

  // declare local variables
  //
  SysChar c;
  int32 len = 0;
  /*
    slen was originaly long but it is saving a pointer which on 64 bit machines is 8 Byte   so  we should
    use int64 type here not int32
  */
  int64 slen = (int64)data_a;
  
  if ((length() + 1) < len_a) {
    len_a = length() + 1;
  }
  
  // copy over the buffer
  //
  for (int32 i = 0; i < (len_a - 1); i++) {
    c.assign(value_d[i]);
    if (!c.get(len, data_a, encoding_a)) {
      return Error::handle(name(), L"getBuffer", SysChar::ERR,
			   __FILE__, __LINE__, Error::WARNING);
    }
    data_a += len;
  }
  
  // figure out the length
  //
  slen = (int64)data_a - slen;
  
  // null terminate the string
  //
  *data_a = (byte8)NULL;
  
  // return the number of bytes written
  //
  return slen;
}

// method: clear
//
// arguments:
//  Integral::CMODE cmode: (input) clear mode 
//
// return: a bool8 value indicating status
//
// this method clears the string
//
bool8 SysString::clear(Integral::CMODE cmode_a) {

  // for release and free, ensure that memory is actually deleted
  //
  if (cmode_a >= Integral::RELEASE) {

    // delete all memory associated with this string
    //    
    freeMem();

    // assign null string to class data
    //
     allocateMem();
  }

  // for reset and retain, just clear value
  //
  else {

    // make the string a zero-length string. 
    //
    if (capacity_d > 0) {
      value_d[0] = (unichar)NULL;
    }
  }

  // exit gracefully
  //
  return true;
}

// method: setCapacity
//
// arguments:
//  int32 cap: (input) new capacity for this string
//
// return: a bool8 value indicating status
//
// this method increases the capacity of the string to given value
//
bool8 SysString::setCapacity(int32 cap_a) {

  // for now, let's ignore user's requests to shrink memory. i don't
  // think this will give us a performance hit. the spirit of this
  // method is to ensure a given capacity before multiple functions
  // which would each slightly increase the needed memory.
  //
  if (cap_a > capacity_d) {

    // growMem is a nice method in that it saves any current data when
    // moving to the new memory.
    //
    growMem(cap_a);
  }

  // exit gracefully
  //
  return true;
}

// method: operator byte8*
//
// arguments: none
//
// return: a byte8* pointer to the data, encoded in ASCII
//
// this method is a simple interface to the ASCII conversion routine. static
// buffers are maintained to prevent memory leaks.
//
SysString::operator byte8*() const {

   // allocate the static buffer the first time
   //
   if (buff[buf_index] == (byte8*)NULL) {

     // set the size of the current static buffer
     //
     buf_size = MAX_LENGTH * STATIC_BUFFER_SIZE * sizeof(unichar);

      // allocate and register the pointer
      //
      buff[buf_index] = (byte8*)MemoryManager::newStatic(buf_size);
   } 

   // right now we only deal with fixed length strings
   //
   int32 len = length() + 1;

   // if the buffer is not large enough to hold N instances of the string,
   // allocate a larger buffer. we have to keep around the old buffer
   // for a little while in case other code is still pointing to it,
   // so it will be left around until another buffer resize is done,
   // probably forever
   //
   if (len > (buf_size / STATIC_BUFFER_SIZE)) {

     // increment the current buffer
     //
     buf_index++;
     if (buf_index > 1) {
       buf_index = 0;
     }
     if (buff[buf_index] != (byte8*)NULL) {

       // debugging message
       //
       if (debug_level_d >= Integral::ALL) {
	 SysString temp;
	 /*
	   buff is 64 bit  so  we  need to use (int64) here
	  */
	 temp.assign((int64)buff[buf_index]);
	 temp.insert(L"Deleting cast static memory space ", 0);
	  Console::put(temp);
       }
       
       // unregister and delete the pointer
       //
       MemoryManager::deleteStatic(buff[buf_index]);
       
     }

     // set the size of the current static buffer
     //
     buf_size = len * STATIC_BUFFER_SIZE * sizeof(unichar);
     
     // allocate and register the pointer
     //
     buff[buf_index] = (byte8*)MemoryManager::newStatic(buf_size);

     // reset the size of the current static buffer
     //
     buf_offset = 0;

     // debugging message
     //
     if (debug_level_d >= Integral::ALL) {
       SysString temp;
       temp.assign((void*)buff[buf_index]);
       temp.insert(L"Increasing cast static memory space with ", 0);
       Console::put(temp);
     }
   }
   
   // wrap the pointer within the buffer. hopefully the user is done
   // with all previous values returned, they are going to be
   // overwritten. obviously we can't do something as nice as a memset
   // here, as it would defeat the entire purpose
   //
   if (len + buf_offset > buf_size) {
     buf_offset = 0;
   }
   
   // read the data starting at the buf_offset'th position of the
   // buf_index'th buffer, increment buf_offset to point to the next
   // available space
   //
   getBuffer(&buff[buf_index][buf_offset], len);
   buf_offset += len;

   // return the buffer
   //
   return &buff[buf_index][buf_offset - len];
}

// method: operator unichar*
//
// arguments: none
//
// return: a unichar* pointer to the data
//
// this method is a simple interface to the unichar* conversion routine. static
// buffers are maintained to prevent memory leaks.
//

SysString::operator unichar*() const {

   // allocate the static buffer the first time
   //
   if (buff[buf_index] == (byte8*)NULL) {
      buf_size = MAX_LENGTH * STATIC_BUFFER_SIZE * sizeof(unichar);

      // allocate and register the pointer
      //
      buff[buf_index] = (byte8*)MemoryManager::newStatic(buf_size);
   } 

   // right now we only deal with fixed length strings
   //
   int32 len = length() + 1;

   // if the buffer is not large enough to hold N instances of the string,
   // allocate a larger buffer. we have to keep around the old buffer
   // for a little while in case other code is still pointing to it,
   // so it will be left around until another buffer resize is done,
   // probably forever
   //
   if (len * (int32)sizeof(unichar) > (buf_size / STATIC_BUFFER_SIZE)) {
      buf_index++;
      if (buf_index > 1) {
	 buf_index = 0;
      }
      if (buff[buf_index] != (byte8*)NULL) {

	// debugging message
	//
	if (debug_level_d >= Integral::ALL) {
	  SysString temp;
	  temp.assign((int64)buff[buf_index]);
	  temp.insert(L"Deleting cast static memory space ", 0);
	   Console::put(temp);
	}

	// unregister and delete the pointer
	//
	MemoryManager::deleteStatic(buff[buf_index]);
      }
      buf_size = len * STATIC_BUFFER_SIZE * sizeof(unichar);

      // allocate and register the pointer
      //
      buff[buf_index] = (byte8*)MemoryManager::newStatic(buf_size);
      
      buf_offset = 0;

      // debugging message
      //
      if (debug_level_d >= Integral::ALL) {
	SysString temp;
	temp.assign((void*)buff[buf_index]);
	temp.insert(L"Increasing cast static memory space with ", 0);
	Console::put(temp);  
      }
   }

   // word-align the byte8* buffer for the larger characters
   //
   while (((int64)&buff[buf_index][buf_offset] % sizeof(unichar)) != 0) {
     buff[buf_index][buf_offset] = (byte8)0;
     buf_offset++;
   }
   
   // wrap the pointer within the buffer. hopefully the user is done
   // with all previous values returned, they are going to be
   // overwritten. obviously we can't do something as nice as a memset
   // here, as it would defeat the entire purpose
   //
   if (len * (int32)sizeof(unichar) + buf_offset > buf_size) {
     buf_offset = 0;
   }
   
   // read the data starting at the buf_offset'th position of the
   // buf_index'th buffer, increment buf_offset to point to the next
   // available space
   //
   getBuffer((unichar*)&buff[buf_index][buf_offset], len);
   buf_offset += len * sizeof(unichar);

   // return the buffer
   //
   return (unichar*)&buff[buf_index][buf_offset - len*sizeof(unichar)];
}
// method: concat
//
// arguments:
//  const SysString& str: (input) string to concatenate
//
// return: a bool8 value indicating status
//
// this method concatenates str to the current object
//
bool8 SysString::concat(const SysString& str_a) {

  // if the argument is null, we are done
  //
  if (str_a.length() == 0) {
    return true;
  }
  
  // if two strings are same, then error off
  //
  if (str_a.value_d == value_d) {
    return Error::handle(name(), L"concat", Error::MEM, __FILE__, __LINE__);
  }
  
  // possibly expand the size of the string
  //
  if ((length() + str_a.length()) > capacity_d) {

    if (!growMem(length() + str_a.length())) {
      return Error::handle(name(), L"concat", Error::MEM, __FILE__, __LINE__);
    }
  }

  // concatenate the new string
  //
  isip_wcscat(value_d, str_a.value_d);
  
  // exit gracefully
  //
  return true;
}

// method: concat
//
// arguments:
//  const SysString& str1: (input) string to concatenate
//  const SysString& str2: (input) string to concatenate
//
// return: a bool8 value indicating status
//
// this method concatenates str1 & str2 to the current object
//
bool8 SysString::concat(const SysString& str1_a, const SysString& str2_a) {

  // delete any current values in this object
  //
  clear(Integral::RESET);
  
  // possibly expand the size of the string
  //
  if ((str1_a.length() + str2_a.length()) > capacity_d) {
    freeMem();
    capacity_d = str1_a.length() + str2_a.length();
    allocateMem();
  }

  // assign the first string
  //
  assign(str1_a);

  // concatenate the second string
  //
  concat(str2_a);
  
  // exit gracefully
  //
  return true;
}

// method: get
//
// arguments:
//  void*& val: (output) pointer value
//
// return: a bool8 value indicating status
//
// this method converts the object into an address pointer
//
bool8 SysString::get(void*& val_a) const {

  // declare a null pointer
  //
  val_a = (void*)NULL;

  // check if string is null string
  //
  if (firstStr((unichar*)NULL_PTR) >= 0) {
    return true;
  }
    
  // use the 8-bit character conversion
  //
  if (sscanf((char*)(byte8*)(*this),
	     (char*)DEF_FMT_VOIDP_8BIT, &val_a) != 1) {
    return false;
  }

  // exit gracefully
  //
  return true;
}

// method: get
//
// arguments:
//  bool8& val: (output) bool8 value
//
// return: a bool8 value indicating status
//
// this method converts the string into a bool8 value
//
bool8 SysString::get(bool8& val_a) const {

  // initialize the return value
  //
  bool8 status = false;
  
  // return bool8 true or false
  //
  if (eq((unichar*)BOOL_TRUE)) {
    val_a = true;
    status = true;
  }
  else if (eq((unichar*)BOOL_FALSE)) {
    val_a = false;
    status = true;
  }

  // exit gracefully
  //
  return status;
}

// method: get
//
// arguments:
//  byte8& val: (output) byte value
//
// return: a bool8 value indicating status
//
// this method converts the object into a ubyte8 integer
//
bool8 SysString::get(byte8& val_a) const {

  // read in the integer
  // We have changed all intermediate variables, used in sscanf to int64
  // so, the program can be used similary on both 32/64- machines; In the future,
  // when 128-bit Machines comes around this sould be revised accordingly.  
  int64 val = 0;

  // use the 8-bit character conversion
  //
  if (sscanf((char*)(byte8*)(*this),
	     (char*)DEF_FMT_LLONG_8BIT, &val) != 1) {
    return false;
  }

  // assign it to a byte8
  //
  val_a = (byte8)val;
  
  // exit gracefully
  //
  return true;
}

// method: get
//
// arguments:
//  unichar& val: (output) unichar value
//
// return: a bool8 value indicating status
//
// this method converts the string into a unichar value
//
bool8 SysString::get(unichar& val_a) const {

  // if length is 1 then assign zeroth element to unichar
  //
  if (length() == 1) {
    val_a = value_d[0];
    return true;
  }

  // exit ungracefully
  //
  return false;
}

// method: get
//
// arguments:
//  uint16& val: (output) uint16 value
//
// return: a bool8 value indicating status
//
// this method converts the object into a uint16 integer
//
bool8 SysString::get(uint16& val_a) const {

  // declare local variables
  ///*
  uint64 tmp_val = 0;

  // use the 8-bit character conversion
  //
  if (sscanf((char*)(byte8*)(*this),
	     (char*)DEF_FMT_ULLONG_8BIT, &tmp_val) != 1) {
    return false;
  }

  // set the output
  //*
  val_a =(uint16) tmp_val;

  // exit gracefully
  //
  return true;
}

// method: get
//
// arguments:
//  uint32& val: (output) uint32 value
//
// return: a bool8 value indicating status
//
// this method converts the object into a uint32 integer
//
bool8 SysString::get(uint32& val_a) const {

  // declare local variables
  //
  val_a = 0;
  ///*
  uint64 val_a_temp;
  val_a_temp=0;
  
  // use the 8-bit character conversion
  //
  if (sscanf((char*)(byte8*)(*this),
	     (char*)DEF_FMT_ULLONG_8BIT, &val_a_temp) != 1) {
      ///*
      val_a=(uint32)val_a_temp;
      return false;
   
  }
  ///*
  val_a=(uint32)val_a_temp;
  // exit gracefully
  //
  return true;
}

// method: get
//
// arguments:
//  uint64& val: (output) uint64 value
//
// return: a bool8 value indicating status
//
// this method converts the object into a uint64 integer
//
bool8 SysString::get(uint64& val_a) const {

  // declare local variables
  //
  val_a = 0;

  // use the 8-bit character conversion
  //
  if
      (sscanf((char*)(byte8*)(*this),
	     (char*)DEF_FMT_ULLONG_8BIT, &val_a) != 1) {
    return false;
  }

  // exit gracefully
  //
  return true;
}

// method: get
//
// arguments:
//  int16& val: (output) int16 value
//
// return: a bool8 value indicating status
//
// this method converts the object into a int16 integer
//
bool8 SysString::get(int16& val_a) const {

  // declare local variable
  ///*
  int64 tmp_val = 0;

  // use the 8-bit character conversion
  //
  if (sscanf((char*)(byte8*)(*this),
	     (char*)DEF_FMT_LLONG_8BIT, &tmp_val) != 1) {
    return false;
  }

  // set the output
  //
  val_a = tmp_val;
  
  // exit gracefully
  //
  return true;
}

// method: get
//
// arguments:
//  int32& val: (output) int32 value
//
// return: a bool8 value indicating status
//
// this method converts the object into a int32 integer
//
bool8 SysString::get(int32& val_a) const {

  // declare local variables
  //
  val_a = 0;
  ///*
  int64 val_a_temp=0;
  
  // use the 8-bit character string conversion
  //
  if (sscanf((char*)(byte8*)(*this),
	     (char*)DEF_FMT_LLONG_8BIT, &val_a_temp) != 1) {
    ///*
    val_a=(int32)val_a_temp;
    return false;
  }
  //
  val_a=(int32)val_a_temp;
  // exit gracefully
  //
  return true;
}

// method: get
//
// arguments:
//  int64& val: (output) int64 value
//
// return: a bool8 value indicating status
//
// this method converts the object into a int64 integer
//
bool8 SysString::get(int64& val_a) const {

  // declare local variables
  //
  val_a = 0;

  // use the 8-bit character conversion
  //
  if (sscanf((char*)(byte8*)(*this),
	     (char*)DEF_FMT_LLONG_8BIT, &val_a) != 1) {
    return false;
  }

  // exit gracefully
  //
  return true;
}

// method: get
//
// arguments:
//  float32& val: (output) float32 value
//
// return: a bool8 value indicating status
//
// this method converts the object to a single precision floating point number
//
bool8 SysString::get(float32& val_a) const {

  // declare local variables
  //
  val_a = (float32)0.0;

  // use the 8-bit character conversion
  //
  if (sscanf((char*)(byte8*)(*this),
	     (char*)DEF_RFMT_FLOAT_8BIT, &val_a) != 1) {
    return false;
  }

  // exit gracefully
  //
  return true;
}

// method: get
//
// arguments:
//  float64& val: (output) float64 value
//
// return: a bool8 value indicating status
//
// this method converts the object to a float64 precision floating point number
//
bool8 SysString::get(float64& val_a) const {

  // declare local variables
  //
  val_a = (float64)0.0;

  // use the 8-bit character conversion
  //
  if (sscanf((char*)(byte8*)(*this),
	     (char*)DEF_RFMT_DOUBLE_8BIT, &val_a) != 1) {
    return false;
  }

  // exit gracefully
  //
  return true;
}

// method: get
//
// arguments:
//  SysComplex<TIntegral>& arg: (output) complex value
//
// return: a bool8 value indicating status
//
// this method converts the object to a complex number
// 
template <class TIntegral>
bool8 SysString::get(SysComplex<TIntegral>& arg_a) const {

  // declare local variable
  //
  SysString str(*this);
  str.trim();
  int32 imag_pos = str.firstChr(L'j');
  if ((imag_pos > 0) && (imag_pos != str.length() - 1)) {
    return Error::handle(name(), L"get", Error::ARG, __FILE__, __LINE__);
  }

  // if there is not 'j' in the string, convert directly
  //
  if (imag_pos < 0) {
    TIntegral val;
    str.get(val);
    arg_a = SysComplex<TIntegral>(val, 0);

    int32 pos = 0;
    int32 len = str.length();
    SysString num;

    // search letters '+' or '-' in the string
    //
    str.tokenize(num, pos, L'+');
    if (pos >= len - 1) {
      pos = 0;
      str.tokenize(num, pos, L'-');
    }

    // if '+' or '-' exists in the string
    //
    if (pos < len - 1 ) {
      str.debug(L"value");
      return Error::handle(name(), L"invalid format - complex numbers should be in the format: a+bj", Error::ARG, __FILE__, __LINE__);
    }
  }

  else {

    // declare local variable
    //
    int32 pos = 0;
    int32 len = str.length();
    bool8 isPositive = true;
    TIntegral val0, val1;
    SysString num;

    // search letters '+' or '-' in the string
    //
    str.tokenize(num, pos, L'+');
    if (pos >= len - 1) {
      pos = 0;
      str.tokenize(num, pos, L'-');
      isPositive = false;
    }

    // if '+' or '-' exists in the string
    //
    if (pos < len - 1 ) {

      // get the real part of the complex number
      //
      num.trim();
      num.get(val0);

      // set the appropriate sign for real part if necessary
      //
      if ((str(0) != num(0)) && (str(0) == '-')) {
	val0 = -val0;
      }

      // get the image part of the complex number
      //
      pos++;
      str.tokenize(num, pos, L'j');
      num.trim();
      if (num.length() == 0) {
	val1 = 1;
      }
      else {
	if (!num.get(val1)) {
	  str.debug(L"value");
	  return Error::handle(name(), L"invalid format - complex numbers should be in the format: a+bj", Error::ARG, __FILE__, __LINE__);
	}
      }

      // set the corresponding sign for the image part
      //
      if (!isPositive) {
	val1 = -val1;
      }

      // copy temporary complex number to output argument
      //
      arg_a = SysComplex<TIntegral>(val0, val1);
    }

    // only real part or image part exists in the string
    //
    else {
      
      // delete the letter 'j'
      //
      str.deleteRange(imag_pos, 1);

      // get the image part of the complex number
      //
      TIntegral val;
      str.trim();
      if (str.length() == 0 || str.eq(L"+")) {
	val = 1;
      }
      else if (str.eq(L"-")) {
	val = -1;
      }
      else {
	if (!str.get(val)) {
	  str.debug(L"value");
	  return Error::handle(name(), L"invalid format - complex numbers should be in the format: a+bj", Error::ARG, __FILE__, __LINE__);
	}
      }
      
      // copy temporary complex number to output argument
      //
      arg_a = SysComplex<TIntegral>(0, val);
    }
  }

  // exit gracefully
  //
  return true;
}
  
// explicit instantiations for complex types
//
template
bool8 SysString::get<float32>(SysComplex<float32>&) const;

template
bool8 SysString::get<float64>(SysComplex<float64>&) const;

template
bool8 SysString::get<int32>(SysComplex<int32>&) const;

// method: get
//
// arguments:
//  SysChar& val: (output) SysChar value
//
// return: a bool8 value indicating status
//
// this method converts the object into a SysChar
//
bool8 SysString::get(SysChar& val_a) const {

  // if length is 1 then assign the element to output SysChar
  //
  if (length() == 1) {
    return val_a.assign(value_d[0]);
  }

  // exit ungracefully
  //
  return false;
}

// method: memSize
//
// arguments: none
//
// return: the size of the class in bytes
//
// return the size of the class in bytes
//
int32 SysString::memSize() const {

  // start with the size of the pointer
  //
  int32 s = sizeof(value_d);

  // add the dynamically allocated string memory
  //
  s += sizeof(unichar) * (capacity_d + 1);

  // add the capacity
  //
  s += sizeof(capacity_d);

  // return the size
  //
  return s;
}
//
// method: substr
//
// arguments:
//  SysString& str: (output) the substring
//  int32 offset: (input) where to start copying from
//  int32 num_elements: (input) number of characters to copy
//
// return: a bool8 value indicating status
//
// return a substring of the current object
//
bool8 SysString::substr(SysString& str_a, int32 offset_a,
			  int32 num_elements_a) const {

  // check the arguments
  //
  if (&str_a == this) {
    return Error::handle(name(), L"substr", Error::MEM, __FILE__, __LINE__);
  }

  // offset can't be negative
  //
  if (offset_a < 0) {
    offset_a = 0;
  }

  // clear the string and exit ungracefully if offset is greater than
  // the length of this or number of characters to copy is 0
  //
  if ((offset_a > length()) || (num_elements_a == 0)) {
    str_a.clear(Integral::RESET);
    return false;
  }

  // number of characters to copy can't be negative
  //
  if (num_elements_a < 0) {
    num_elements_a = length() - offset_a;
  }

  // allocate a buffer and assign the values
  //
  unichar buffer[num_elements_a + 1];
  isip_wcsncpy(buffer, &value_d[offset_a], num_elements_a);
  buffer[num_elements_a] = (unichar)NULL;
  str_a.assign(buffer);
  
  // exit gracefully
  //
  return true;
}

// method: insert
//
// arguments:
//  const unichar* str: (output) the substring
//  int32 offset: (input) where to start copying into
//
// return: a bool8 value indicating status
//
// insert string str into current string
//
bool8 SysString::insert(const unichar* str_a, int32 offset_a) {

  // declare local variable
  //
  SysString temp;

  // assign the input buffer to a string
  //
  temp.assign(str_a);
  
  // call the master function
  //
  return insert(temp, offset_a);
}
  
// method: insert
//
// arguments:
//  const SysString& str: (output) the substring
//  int32 offset: (input) where to start copying into
//
// return: a bool8 value indicating status
//
// insert string str into current string
//
bool8 SysString::insert(const SysString& str_a, int32 offset_a) {

  // check if the offset is greater that the length
  //
  if (offset_a > length()) {
    return concat(str_a);
  }

  // make sure the argument isn't the object
  //
  if (&str_a == this) {
    return Error::handle(name(), L"insert", Error::MEM, __FILE__, __LINE__);
  }
  
  // if offset is negative then set it to zero
  //
  if (offset_a <= 0) {

    offset_a = 0;

    // make a new string which copies the input string (preserves argument)
    //
    SysString temp(str_a);

    // concatenate this string to temporary
    //
    temp.concat(*this);

    // swap pointers
    //
    return swap(temp);
  }

  // make sure we have a large enough buffer
  //
  if ((length() + str_a.length()) > capacity_d) {
    if (!growMem(length() + str_a.length())) {
      return Error::handle(name(), L"insert", Error::MEM, __FILE__, __LINE__);
    }
  }

  // get the length of the input and this string
  //
  int32 len0 = length();
  int32 len1 = str_a.length();

  // now insert
  //
  for (int32 i = len0 + len1; i >= offset_a + len1; i--) {
    value_d[i] = value_d[i - len1];
  }

  for (int32 i = offset_a + len1 - 1; i >= offset_a; i--) {
    value_d[i] = str_a.value_d[i - offset_a];
  }

  // exit gracefully
  //
  return true;
}

// method: replace
//
// arguments:
//  const unichar* str: (output) the substring
//  int32 offset: (input) where to start copying into
//
// return: a bool8 value indicating status
//
// insert string str into current string
//
bool8 SysString::replace(const unichar* str_a, int32 offset_a) {

  // declare local variables
  //
  static SysString temp;

  // assign the unichar* to a string
  //
  temp.assign(str_a);

  // call the master function
  //
  return replace(temp, offset_a);
}

// method: replace
//
// arguments:
//  const SysString& str: (output) the substring
//  int32 offset: (input) where to start copying into
//
// return: a bool8 value indicating status
//
// insert string str into current string
//
bool8 SysString::replace(const SysString& str_a, int32 offset_a) {

  // check the length of string
  //
  if (str_a.length() > 0) {

    // concat str_a if offset is greater than the length of the
    // current string
    //
    if (offset_a > length()) {
      return concat(str_a);
    }

    // if the new string will be longer than the old string, we don't
    // have to worry about trailing characters
    //
    if (str_a.length() >= (length() - offset_a)) {
      
      // cut the current value at the insertion point
      //
      value_d[offset_a] = (unichar)NULL;
    
      // concatenate the new string
      //
      concat(str_a);
    }

    // the old string is plenty big enough, just copy new characters
    // in by hand
    //
    else {
      int32 max = str_a.length();
      for (int32 i = 0; i < max; i++) {
	value_d[i + offset_a] = str_a.value_d[i];
      }
    }
  }

  // exit gracefully
  //
  return true;
}

// method: replace
//
// arguments:
//  const SysString& pattern: (input) the pattern to search for
//  const SysString& new_stuff: (input) the replacement string
//
// return: a bool8 value indicating status
//
// search for a pattern string and replace it with the new_stuff
//
bool8 SysString::replace(const SysString& pattern_a,
			   const SysString& new_stuff_a) {

  // find the first instance of the pattern
  //
  int32 index = firstStr(pattern_a);

  // if no instance is found, return false
  //
  if (index == Integral::NO_POS) {
    return false;
  }
  
  deleteRange(index, pattern_a.length());
  insert(new_stuff_a, index);

  // exit gracefully
  //
  return true;
}
  
// method: replaceAll
//
// arguments:
//  const SysString& pattern: (input) the pattern to search for
//  const SysString& new_stuff: (input) the replacement string
//
// return: a bool8 value indicating status
//
// search for a pattern string and replace it with the new_stuff
//
bool8 SysString::replaceAll(const SysString& pattern_a,
                              const SysString& new_stuff_a) {

  // local variables
  //
  int32 count = 0;
  int32 len = 0;  
  int32 index = 0;
  
  // get the length of the new string
  //
  len = new_stuff_a.length();

  // replace all instances of the pattern
  //
  while ((index = firstStr(pattern_a, index)) != Integral::NO_POS) {
    deleteRange(index, pattern_a.length());
    insert(new_stuff_a, index);
    index += len;    
  }
  
  // exit gracefully
  //
  return (count > 0);
}
  

// method: deleteRange
//
// arguments:
//  int32 offset: (input) where to start deleting
//  int32 num_elements: (input) number of elements to delete
//
// return: a bool8 value indicating status
//
// delete a range of characters from the current string
//
bool8 SysString::deleteRange(int32 offset_a, int32 num_elements_a) {

  // check the arguments
  //
  if ((offset_a < 0) || (offset_a >= length()) ||
      ((offset_a + num_elements_a) > length())) {
    return Error::handle(name(), L"deleteRange", Error::ARG,
			 __FILE__, __LINE__);
  }

  // check for number of elements
  //
  if (num_elements_a < 0) {
    num_elements_a = length() - offset_a;
  }
  
  // see if we need to worry about trailing characters, or if we can
  // just get away with deleting.
  //
  if ((offset_a + num_elements_a) >= length()) {
    value_d[offset_a] = (unichar)NULL;
    return true;
  }

  // we do need to worry about trailing characters
  //
  value_d[offset_a] = (unichar)NULL;

  // concatenate the trailing characters
  //
  concat(&value_d[offset_a + num_elements_a]);

  // exit gracefully
  //
  return true;
}

// method: isip_wcsstr
//
// arguments:
//  const unichar* ws1: (input) wc string to search
//  const unichar* ws2: (input) wc substring to find
//
// return: unichar* ptr to first occurrence of a ws2 in ws1
//
// wrap system wcsstr method
//
unichar* SysString::isip_wcsstr(const unichar* ws1_a,
				const unichar* ws2_a) {

  // which system function has to do with which operating system
  //
#if ISIP_WCHAR_MODE == ISIP_WCHAR_SOLARIS
  
  // call the solaris 2.6 system function
  //
  return Integral::wcswcs(ws1_a, ws2_a);

#else

  // call the more standard system function
  //
  return Integral::wcsstr(ws1_a, ws2_a);
  
#endif
}

// method: isip_wcstok
//
// arguments:
//  unichar* ws: (input) wc string to tokenize
//  const unichar* delim: (input) delimiter character
//  unichar** ptr: (input) temporary workspace
//
// return: unichar* ptr to first occurrence of a needle in the haystack
//
// wrap system wcschr method
//
unichar* SysString::isip_wcstok(unichar* ws_a, const unichar* delim_a,
				unichar** ptr_a) {

  // which system function has to do with which operating system
  //
#if ISIP_WCHAR_MODE == ISIP_WCHAR_SOLARIS

  // solaris 2.6 needs an older version of wcstok
  //
  return Integral::wcstok(ws_a, delim_a);
  
#else
  
  // any other supporting operating system uses the new definition
  //
  return Integral::wcstok(ws_a, delim_a, ptr_a);

#endif  
}

// method: isip_fputws
//
// arguments:
//  const unichar* s: (input) string to write
//  FILE* stream: (input) stream to write to
//
// return: a non-negative number
//
// wrap system fputws function
//
int32 SysString::isip_fputws(const unichar* s_a, FILE* stream_a) {
  
  // call the system function
  //
#if ISIP_WCHAR_MODE != ISIP_WCHAR_NONE
  return Integral::fputws(s_a, stream_a);
#else
  
  // build a string from the input (without copying)
  //
  SysString temp_string;
  temp_string.value_d = (unichar*)s_a;
  temp_string.capacity_d = isip_wcslen(s_a);

  // write this string
  //
  int32 ret = Integral::fputs((byte8*)temp_string, stream_a);
  
  // make sure we don't delete the users buffer
  //
  temp_string.value_d = (unichar*)NULL;
  temp_string.capacity_d = 0;
  temp_string.allocateMem();

  // return the system return value
  //
  return ret;
#endif
}

// method: isip_fgetws
//
// arguments:
//  unichar* s: (output) string read
//  int32n: (input) maximum number of characters to read
//  FILE* stream: (input) stream to read from
//
// return: pointer to read string
//
// wrap system fgetws function
//
unichar* SysString::isip_fgetws(unichar* s_a, int32 n_a, FILE* stream_a) {
  
  // call the system function
  //
#if ISIP_WCHAR_MODE != ISIP_WCHAR_NONE
  return Integral::fgetws(s_a, n_a, stream_a);
#else
  
  // read in the characters
  //
  char* input_buffer = new char[n_a + 1];
  MemoryManager::memset(input_buffer, 0, n_a + 1);  

  // call the system fgets function, check return value
  //
  if ((char*)Integral::fgets((byte8*)input_buffer, n_a, stream_a) ==(char*) NULL) {
    delete [] input_buffer;
    return (unichar*)NULL;
  }

  // declare a SysChar to hold characters
  //
  SysChar c;
  
  // loop through each character, converting from char to SysChar
  //
  for (int32 i = 0; i < n_a; i++) {

    c.assign((byte8)input_buffer[i]);
    c.get(s_a[i]);
  }
    
  delete [] input_buffer;
  
  // return the pointer
  //
  return s_a;
#endif
}

// method: isip_fputwc
//
// arguments:
//  wint_t c: (input) character to write
//  FILE* stream: (input) stream to write to
//
// return: a non-negative number
//
// wrap system fputws function
//
wint_t SysString::isip_fputwc(wint_t c_a, FILE* stream_a) {
  
  // call the system function
  //
#if ISIP_WCHAR_MODE != ISIP_WCHAR_NONE
  return Integral::fputwc(c_a, stream_a);
#else
  
  // build a SysChar from the input
  //
  SysChar c((unichar)c_a);
  byte8 output;
  c.get(output);

  // write this string
  //
  int32 ret = Integral::fputc(output, stream_a);

  // return the system return value
  //
  return (wint_t)ret;
#endif
}

// method: isip_fgetwc
//
// arguments:
//  FILE* stream: (input) stream to read from
//
// return: pointer to read string
//
// wrap system fgetws function
//
wint_t SysString::isip_fgetwc(FILE* stream_a) {
  
  // call the system function
  //
#if ISIP_WCHAR_MODE != ISIP_WCHAR_NONE
  return Integral::fgetwc(stream_a);
#else
  
  // read in the characters
  //
  int32 input;
  input = Integral::fgetc(stream_a);
  
  // check for end of file and do the appropriate conversion
  //
  if (input == (int)EOF) {
    return (wint_t)WEOF;
  }
  
  // build a SysChar from the input
  //
  SysChar c((byte8)input);

  // return the character
  //
  return (unichar)c;
#endif
}
