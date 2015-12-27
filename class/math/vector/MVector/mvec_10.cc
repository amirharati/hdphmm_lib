// file: $isip/class/math/vector/MVector/mvec_10.cc
// version: $Id: mvec_10.cc 10636 2007-01-26 22:18:09Z tm334 $
//

// isip include files
//
#include "MVectorMethods.h"
#include "MVector.h"

// method: sort
//
// arguments:
//  MVector<TScalar, TIntegral>& this: (output) class operand
//  const MVector<TScalar, TIntegral>& v: (input) operand
//  Integral::ORDER order: (input) order for sorting
//
// return: a bool8 value indicating status
//
// this method sorts the input vector elements in the specified
// (ascending or descending) order and stores the result in the
// current vector.
//
// this method uses a randomized version of quicksort that
// includes a random pivot. see:
//
//  T. Cormen, C. Leiserson, R. Rivest, "Introduction to Algorithms,"
//  MIT Press, pp. 161-163, 1998.
//
template<class TScalar, class TIntegral>
bool8 MVectorMethods::sort(MVector<TScalar, TIntegral>& this_a,
			     const MVector<TScalar, TIntegral>& v_a,
			     Integral::ORDER order_a) {

  // if not working on this, copy to this
  //
  if (&this_a != &v_a) {
    this_a.assign(v_a);
  }

  // declare the sort order to be true if the order is ascending and
  // false if the order is descending - this will help us in deciding
  // that whether we want to go to right or left
  //
  bool8 order = true;
  if (order_a == Integral::DESCENDING) {
    order = false;
  }

  // declare the temporary variables
  //
  int32 i, j;
  TIntegral x;
  bool8 is_equal;
  MVector<Long, int32> p_stack;
  MVector<Long, int32> r_stack;

  // set the length of the vectors which act like a stack
  //
  p_stack.setLength(1);
  r_stack.setLength(1);

  int32 ptr = 0;
  
  // load the first operands onto the vectors
  //
  p_stack(ptr) = 0;
  r_stack(ptr) = this_a.length() - 1;
  
  while (ptr >= 0) {
    
    // use the p & r values at the start of the vectors, this is similar
    // to the top of the new function call
    //
    int32 p = p_stack(ptr);
    int32 r = r_stack(ptr--);

    // decrement the length of the vectors
    //
    p_stack.setLength(p_stack.length() - 1);
    r_stack.setLength(r_stack.length() - 1);
    
    // this is the partition method
    //
    if (p < r) {

      // select a number at random between p and r
      //
      Long rand_pivot;
      rand_pivot.rand(p, r);

      // error if the value does not lie between p and r
      //
      if ((rand_pivot < p) || (rand_pivot > r)) {
	v_a.debug(L"v_a");	
	this_a.debug(L"this_a");	
	return Error::handle(name(), L"sort", Error::ARG, __FILE__, __LINE__);
      }

      x = this_a(rand_pivot);
      i = p - 1;
      j = r + 1;
      
      do {
        do {
          j--;
	  ((int32)rand_pivot == j) ? is_equal = true : is_equal = false;
        } while ((order && (j > p) && (this_a.v_d[j] > x) && !is_equal) ||
		 (!order && (j > p) && (this_a.v_d[j] < x) && !is_equal));

	do {
          i++;
	  ((int32)rand_pivot == i) ? is_equal = true : is_equal = false;  
        } while ((order && (i < r) && (this_a.v_d[i] < x) && !is_equal) ||
		 (!order && (i < r) && (this_a.v_d[i] > x) && !is_equal));
        
        if (i < j) {
          TIntegral temp = this_a.v_d[j];
          this_a.v_d[j] = this_a.v_d[i];
          this_a.v_d[i] = temp;
        }
      } while (i < j);

      // now add p & r values to the vectors, similar to making new
      // function calls but with much less overhead
      //
      //   Quicksort2(A, p, j);
      //
      if (ptr == (1048586 - 3)) {
	v_a.debug(L"v_a");	
	this_a.debug(L"this_a");	
	return Error::handle(name(), L"internal stack overflow", Error::ARG,
			     __FILE__, __LINE__);
      }
      
      p_stack.setLength(p_stack.length() + 2);
      r_stack.setLength(r_stack.length() + 2);
      
      p_stack(++ptr) = p;
      r_stack(ptr) = j;

      //   Quicksort2(A, j+1, r);
      //
      p_stack(++ptr) = j+1;
      r_stack(ptr) = r;
    }
  }

  // exit gracefully
  //
  return true; 
}

// explicit instantiations
//
template bool8
MVectorMethods::sort<ISIP_TEMPLATE_TARGET>
(MVector<ISIP_TEMPLATE_TARGET>&, const MVector<ISIP_TEMPLATE_TARGET>&, Integral::ORDER);

// method: index
//
// arguments:
//  MVector<TScalar, TIntegral>& this: (input) class operand
//  Integral::ORDER order: (input) sort order
//  MVector<Long, int32>& sort_index: (output) operand
//
// return: a bool8 value indicating status
//
// "randomized version of quicksort" using random pivot
// taken from:
// T. Cormen, C. Leiserson, R. Rivest, Introduction to Algorithms,
// MIT Press, 1998.  modified to eliminate recursion
//
// this method creates an index for the input vector elements,
// sorts it in ascending order of vector elements and
// stores the result in the supplied VectorLong
//
template<class TScalar, class TIntegral>
bool8 MVectorMethods::index(MVector<TScalar, TIntegral>& this_a,
			      Integral::ORDER order_a,
			      MVector<Long, int32>& sort_index_a) {


  // declare and load an index array
  //
  sort_index_a.setLength(this_a.length());
  for (int32 i = 0; i < this_a.length(); i++) {
    sort_index_a(i) = i;
  }

  // declare the sort order to be true if the order is ascending and
  // false if the order is descending - this will help us in deciding
  // that whether we want to go to right or left
  //
  bool8 order = true;
  if (order_a == Integral::DESCENDING) {
    order = false;
  }
  
  // declare the temporary variables
  //
  int32 i, j;
  TIntegral x;
  bool8 is_equal;
  MVector<Long, int32> p_stack;
  MVector<Long, int32> r_stack;

  // set the length of the vectors which act like a stack
  //
  p_stack.setLength(1);
  r_stack.setLength(1);

  int32 ptr = 0;

  // load the first operands onto the vectors
  //
  p_stack(ptr) = 0;
  r_stack(ptr) = this_a.length() - 1;
  
  while (ptr >= 0) {
    
    // use the p & r values at the start of the vectors, this is similar
    // to the top of the new function call
    //
    int32 p = p_stack(ptr);
    int32 r = r_stack(ptr--);

    // decrement the length of the vectors
    //
    p_stack.setLength(p_stack.length() - 1);
    r_stack.setLength(r_stack.length() - 1);
    
    // this is the partition method
    //
    if (p < r) {

      // select a number at random between p and r
      //
      Long rand_pivot;
      rand_pivot.rand(p, r);

      // error if the value does not lie between p and r
      //
      if ((rand_pivot < p) || (rand_pivot > r)) {
	this_a.debug(L"this_a");	
	return Error::handle(name(), L"index", Error::ARG, __FILE__, __LINE__);
      }

      x = this_a(sort_index_a(rand_pivot));
      i = p - 1;
      j = r + 1;

      do {
        do {
          j--;
	  ((int32)rand_pivot == j) ? is_equal = true : is_equal = false;
        } while ((order && (j > p) && (this_a.v_d[sort_index_a(j)] > x) && !is_equal) ||
		 (!order && (j > p) && (this_a.v_d[sort_index_a(j)] < x) && !is_equal));

	do {
          i++;
	  ((int32)rand_pivot == i) ? is_equal = true : is_equal = false;  
        } while ((order && (i < r) && (this_a.v_d[sort_index_a(i)] < x) && !is_equal) ||
		 (!order && (i < r) && (this_a.v_d[sort_index_a(i)] > x) && !is_equal));
        
        if (i < j) {
          int32 temp = sort_index_a(j);
          sort_index_a(j) = sort_index_a(i);
          sort_index_a(i) = temp;
        }
      } while (i < j);

      // now add p & r values to the vectors, similar to making new
      // function calls but with much less overhead
      //
      //   Quicksort2(A, p, j);
      //
      p_stack.setLength(p_stack.length() + 2);
      r_stack.setLength(r_stack.length() + 2);
      
      p_stack(++ptr) = p;
      r_stack(ptr) = j;

      // Quicksort2(A, j+1, r);
      //
      p_stack(++ptr) = j+1;
      r_stack(ptr) = r;
    }
  }

  // exit gracefully
  //
  return true;
}

// explicit instantiations
//
template bool8
MVectorMethods::index<ISIP_TEMPLATE_TARGET>
(MVector<ISIP_TEMPLATE_TARGET>&, Integral::ORDER, MVector<Long, int32>&);

// method: randperm
//
// arguments:
//  MVector<TScalar, TIntegral>& this: (output) class operand
//  int32 size: (input) output size of permutation
//
// return: a bool8 value indicating status
//
// this method creates a random permutation for the integers from 0 to
// size - 1.
//  example: randperm(4) = [2 0 1 3]
//
template<class TScalar, class TIntegral>
bool8 MVectorMethods::randperm(MVector<TScalar, TIntegral>& this_a,
				 int32 size_a) {

  // declare an index array which will contain our random permutation
  //
  MVector<Long, int32> index_array;
  
  // create a random array
  //
  if (size_a < 1) {
    this_a.debug(L"this_a");    
    return Error::handle(this_a.name(), L"randperm", Error::ARG,
			 __FILE__, __LINE__);
  }
  MVector<Double, float64> tmp(size_a);
  tmp.rand();

  // use the sort indices of the random array to populate our index
  // array
  //
  tmp.index(index_array);
  
  // populate the output array with the indices
  //
  this_a.assign(index_array);
  
  // exit gracefully
  //
  return true;
}

// explicit instantiations
//
template bool8
MVectorMethods::randperm<ISIP_TEMPLATE_TARGET>
(MVector<ISIP_TEMPLATE_TARGET>&, int32);

// method: first
//
// arguments:
//  MVector<TScalar, TIntegral>& this: (output) class operand
//  TIntegral value: (input) value to be found
//  int32 start_pos: (input) position to start searching from
//
// return: a int32 value of the element index
//
// this method finds the index of the first element after the start_pos
// (count from 0) in "this" equal to value_a, if the value is not found,
// NO_POS is returned.
//
template<class TScalar, class TIntegral>
int32 MVectorMethods::first(MVector<TScalar, TIntegral>& this_a,
			   TIntegral value_a, int32 start_pos_a) {
  
  int32 last_index = (int32)this_a.length_d;
  
  // make sure the range of start_pos_a is between [0, length_d-1]
  //
  if ((start_pos_a == Integral::NO_POS) || (start_pos_a >= this_a.length_d)) {
    start_pos_a = 0;
  }
  
  // check all values
  //
  for (int32 index = start_pos_a; index < last_index; index++) {
    if ((TIntegral)this_a.v_d[index] == value_a) {
      return index;
    }
  }
  
  // exit gracefully - no match found
  // 
  return Integral::NO_POS;
}

// explicit instantiations
//
template int32 
MVectorMethods::first<ISIP_TEMPLATE_TARGET>
(MVector<ISIP_TEMPLATE_TARGET>&, ISIP_TEMPLATE_T1, int32);

// method: last
//
// arguments:
//  MVector<TScalar, TIntegral>& this: (output) class operand
//  TIntegral value: (input) value to be found
//  int32 end_pos: (input) position to start searching from
//
// return: a int32 value of the element index
//
// this method finds the index of the first element before the end_pos
// in "this" equal to value_a, if the value is not found, NO_POS is returned. 
//
template<class TScalar, class TIntegral>
int32 MVectorMethods::last(MVector<TScalar, TIntegral>& this_a,
			  TIntegral value_a, int32 end_pos_a) {
  
  // make sure the range of end_pos_a is between [0, length_d-1]
  //
  if (end_pos_a == Integral::NO_POS || end_pos_a >= this_a.length_d) {
    end_pos_a = (int32)(this_a.length_d) - 1;
  }
  
  // check all values
  //
  for (int32 index = end_pos_a; index >= 0; index--) {
    if ((TIntegral)this_a.v_d[index] == value_a) {
      return index;
    }
  }
  
  // exit gracefully - no match found
  // 
  return Integral::NO_POS;
}

// explicit instantiations
//
template int32 
MVectorMethods::last<ISIP_TEMPLATE_TARGET>
(MVector<ISIP_TEMPLATE_TARGET>&, ISIP_TEMPLATE_T1, int32);

// method: reorder
//
// arguments:
//  MVector<TScalar, TIntegral>& this: (output) class operand
//  const MVector<Long, int32>& index: (input) input Vector
//
// return: a bool8 value indicating status
//
// this method orders elements in this according to the indexing vector:
//    this(i) = this(index_a(i));
// it is typically used in combination with a sorting operation.
//
template<class TScalar, class TIntegral>
bool8 MVectorMethods::reorder(MVector<TScalar, TIntegral>& this_a,
				const MVector<Long, int32>& index_a) {
  
  // create temporary copy of the current vector
  //
  MVector<TScalar, TIntegral> temp(this_a);
  
  // call the master function
  //
  return this_a.reorder(temp, index_a);
}

// explicit instantiations
//
template bool8 
MVectorMethods::reorder<ISIP_TEMPLATE_TARGET>
(MVector<ISIP_TEMPLATE_TARGET>&, const MVector<Long, int32>&);

// method: reorder
//
// arguments:
//  MVector<TScalar, TIntegral>& this: (output) class operand
//  const MVector<TScalar, TIntegral>& vector: (input) data Vector
//  const MVector<Long, int32>& index: (input) input Vector
//
// return: a bool8 value indicating status
//
// this method orders elements in this according to the indexing vector:
//    this(i) = this(index_a(i));
// it is typically used in combination with a sorting operation.
//
template<class TScalar, class TIntegral>
bool8 MVectorMethods::reorder(MVector<TScalar, TIntegral>& this_a,
				const MVector<TScalar, TIntegral>& vector_a,
				const MVector<Long, int32>& index_a) {
  
  // check lengths
  //
  int32 last_index = vector_a.length();
  if (last_index != index_a.length()) {
    this_a.debug(L"this_a");        
    vector_a.debug(L"vector_a");    
    return Error::handle(name(), L"reorder",
			 MVector<TScalar, TIntegral>::ERR_LEN,
			 __FILE__, __LINE__);
  }
  
  if (!this_a.setLength(last_index, false)) {
    this_a.debug(L"this_a");
    vector_a.debug(L"vector_a");    
    return Error::handle(name(), L"reorder", Error::NOMEM, __FILE__, __LINE__);
  }
  
  // rearrange
  //
  for (int32 i = 0; i < last_index; i++) {
    this_a.v_d[i] = vector_a.v_d[index_a(i)];
  }
  
  // exit gracefully
  // 
  return true;
}

// explicit instantiations
//
template bool8 
MVectorMethods::reorder<ISIP_TEMPLATE_TARGET>
(MVector<ISIP_TEMPLATE_TARGET>&, const MVector<ISIP_TEMPLATE_TARGET>&,
 const MVector<Long, int32>&);

// method: reverse
//
// arguments:
//  MVector<TScalar, TIntegral>& this: (output) class operand
// return: a bool8 value indicating status
//
// this method reverses elements in this 
//
template<class TScalar, class TIntegral>
bool8 MVectorMethods::reverse(MVector<TScalar, TIntegral>& this_a) {
  
  // check lengths
  //
  int32 last_index = this_a.length();

  int32 i = 0;
  int32 j = last_index - 1;

  // reverse
  //
  while (i < j) {
    TIntegral tmp = this_a.v_d[i];
    this_a.v_d[i] = this_a.v_d[j];
    this_a.v_d[j] = tmp;
    i++;
    j--;
  }

  // exit gracefully
  // 
  return true;
}

// explicit instantiations
//
template bool8 
MVectorMethods::reverse<ISIP_TEMPLATE_TARGET>
(MVector<ISIP_TEMPLATE_TARGET>&);









