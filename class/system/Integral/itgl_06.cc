// file: $isip/class/system/Integral/itgl_06.cc
// version: $Id: itgl_06.cc 9809 2004-10-03 16:55:34Z parihar $
//
// note:
// AH (07/30/2010) : hash function for 64 bit vectors added
// isip include files
//
#include "Integral.h"
#include <SysString.h>

// method: logAddLog
//
// arguments:
//  const float64 x: (input) first log value to add.
//  const float64 y: (input) second log value to add
//
// return: float64 value returning the log addition of the two numbers
//
// this method computes the log addition of two numbers which are
// themselves log values.
// 
// the below derivation is due to a private correspondence with Aravind
// Ganapathiraju, September 14, 2000.
//
//   We have in hand log(x) and log(y) . We want Log(x+y).
//   
//   Consider, log(1+exp(log(x) - log(y))):
//   
//   log(1+exp(log(x) - log(y)))= log(1+ exp(log(x/y)))
//                              = log(1+ x/y)
//                              = log((x+y)/y)
//                              = log(x+y) - log(y)
//   
//   If we take score as log(y) and tmp_score as log(x), then
//   
//      log(x+y) = log(y) + log(1 + exp(log(x) - log(y)))
//   
//   In the below code this is done using: return (log(1.0 + exp(tmp)));
//
//   If an underflow occurs, the input values whose absolute value is
//   lesser will be returned.
// 
float64 Integral::logAddLog(const float64 x_a, const float64 y_a) {

  // define the variables to hold the gaussian score
  //
  float64 tmp = 0;
  float64 tmp_value = y_a;
  float64 output_value = x_a;
  
  // find the minimum component so that the sign of tmp is negative below
  //
  if (output_value < tmp_value) {
    tmp = output_value;
    output_value = tmp_value;
    tmp_value = tmp;
  }

  // find the difference between the two values. the output of this will
  // always be negative since output_value >= tmp_value
  //
  tmp = tmp_value - output_value;

  // do not allow the score to underflow.
  //
  if (tmp >= MIN_LOG_VALUE) {
    output_value += Integral::log1p(Integral::exp(tmp));
  }

  // exit gracefully
  //
  return output_value;
}

// method: hash
//
// arguments:
//  uint32* vec: (input) values to hash
//  int32 num_elem: (input) size of vector
//  int32 capacity: (input) upper bound on hash output
//
// return: a hash of the input vector
//
// this is a generic hash function, as defined by Knuth's "The Art of
// Computer Programming", volume 3, "Sorting and Searching", chapter
// 6.4.
//

int32 Integral::hash(uint32* vec_a, int32 num_elem_a, int32 capacity_a) {

  // local variable
  //
  uint32 hash = 0;

  for (int32 i = 0; i < num_elem_a; i++) {
    hash = (hash << 5) ^ (hash >> 27) ^ (uint32)vec_a[i];
  }

  // set the modulus to be the capacity - 1, so that the hash will
  // most likely not be a multiple of 2 or 10
  //
  return (hash % (capacity_a - 1));
}


// method: hash
//
// arguments:
//  uint64* vec: (input) values to hash
//  int32 num_elem: (input) size of vector
//  int32 capacity: (input) upper bound on hash output
//
// return: a hash of the input vector
//
// this is a generic hash function, as defined by Knuth's "The Art of
// Computer Programming", volume 3, "Sorting and Searching", chapter
// 6.4.
//

int64 Integral::hash(uint64* vec_a, int32 num_elem_a, int32 capacity_a) {

    // local variable
    ///*
    uint64 hash = 0;

    for (int64 i = 0; i < num_elem_a; i++) {
	hash = (hash << 5) ^ (hash >> 27) ^ (uint64)vec_a[i];
    }

    // set the modulus to be the capacity - 1, so that the hash will
    // most likely not be a multiple of 2 or 10
    //
    return (hash % (capacity_a - 1));
}

 
// method: cTime  
// arguments:
//  SysString& time: (output) string indicating calendar time
//
// return: a bool8 value indicating status
//
//  method that returns the calendar time as a string of the form
//  "Sun Oct  3 09:50:40 2004\n", expressed relative to the local
//  standard time  
//

bool8 Integral::cTime(SysString& time_a) {
  
  // call system ctime function to get calendar time
  //
  time_t t;
  ::time(&t);
  byte8* val = (byte8*)::ctime(&t);
  
  // if it is not null then assign assign calendar time to output
  // string
  //
  if (val != (byte8*)NULL) {
    time_a.assign((byte8*)val);
  }
  
  // if calendar time is NULL then clear the output string
  // 
  else {
    time_a.clear();
    return false;
  }
  
  // exit gracefully
  //
  return true;
}

// method: utcTime
// arguments:
//  SysString& time: (output) string indicating calendar time
//
//  method that returns the calendar time as a string of the form
//  "Sun Oct  3 14:50:40 2004\n", expressed in Coordinated Universal
//  Time (UTC)
//

bool8 Integral::utcTime(SysString& time_a) {
  
  // call system ctime function to get calendar time
  //
  time_t t;
  ::time(&t);
  byte8* val = (byte8*)::asctime(gmtime(&t));
  // if it is not null then assign assign calendar time to output
  // string
  //
  if (val != (byte8*)NULL) {
    time_a.assign((byte8*)val);
  }
  
  // if calendar time is NULL then clear the output string
  // 
  else {
    time_a.clear();
    return false;
  }
  
  // exit gracefully
  //
  return true;
}
