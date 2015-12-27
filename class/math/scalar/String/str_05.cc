// file: $isip/class/math/scalar/String/str_05.cc
// version: $Id: str_05.cc 5518 2000-11-13 23:37:29Z duncan $
//

// isip include files
//
#include "String.h"
#include <Long.h>
#include <Char.h>

// method: rand
//
// arguments:
//  long min_len: (input) minimum number of characters
//  long max_len: (input) maximum number of characters
//
// return: a bool8 value indicating status
//
// randomize the value of this string, restricting all characters to
// be alphanumeric or punctuation.
//
bool8 String::rand(int32 min_len_a, int32 max_len_a) {

  // clear the current values
  //
  clear();

  // determine the new length
  //
  Long new_len;
  new_len.rand(min_len_a, max_len_a);

  // local variables
  //
  Char c;
  Long num;

  // loop until we have enough chars
  //
  for (int32 i = 0; i < (int32)new_len; ) {

    num.rand(0, 127);
    c.assign((unichar)(int32)num);

    if (c.isAlnum() || c.isPunct()) {
      concat(c);
      i++;
    }
  }

  // exit gracefully
  //
  return true;
}

// method: hash
//
// arguments:
//  int32 capacity: (input) upper bound on hash value
//
// return: a hash of the String value
//
// this is a generic hash function, as defined by Knuth's "The Art of
// Computer Programming", volume 3, "Sorting and Searching", chapter
// 6.4.
//
int32 String::hash(int32 capacity_a) const {

  // local variable
  //
  uint32 hash = 0;

  // hash function
  //
  for (int32 i = length() - 1; i >= 0; i--) {
    hash = (hash << 5) ^ (hash >> 27) ^ (uint32)value_d[i];
  }
  
  // set the modulus to be the capacity - 1, so that the hash will
  // most likely not be a multiple of 2 or 10
  //
  return (hash % (capacity_a - 1));
}

