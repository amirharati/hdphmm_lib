// file: $isip/class/system/SysHeap/SysHeap.h
// version: $Id: SysHeap.h 4924 2000-09-20 20:17:12Z hamaker $
//

// make sure definitions are only made once
//
#ifndef ISIP_SYSHEAP
#define ISIP_SYSHEAP

// isip include files
//
#ifndef ISIP_INTEGRAL
#include <Integral.h>
#endif

#ifndef ISIP_ERROR
#include <Error.h>
#endif

#ifndef ISIP_SYS_STRING
#include <SysString.h>
#endif

// SysHeap: a class that implements a heap for pointers. it is a data
// structure but it is placed in system library since it is used by the
// MemoryManager class
//
// The binary heap data structure is an array that can be viewed as a
// complete binary tree. Each node of the tree corresponds to an
// element of the array that stores the value in the node. The tree is
// completely filled on all levels except possibly the lowest, which
// is filled from the left up to a point.
//
// If an array A is used to represents a heap, A[0] is the root of the
// tree. Also, given the index i of a node the following indices can
// be found:
//
//  Parent (i)      = i / 2     
//  Left Child (i)  = 2 * i + 1
//  Right Child (i) = 2 * i + 2
//
// A good tutorial on heaps can be found at :
// 
//  T.H. Cormen, C.E. Leiserson and R.L. Rivest, "Introduction to
//  Algorithms," McGraw-Hill, New York, New York, USA, pp. 140-149, 1997.
//
class SysHeap {

  //---------------------------------------------------------------------------
  //
  // public constants
  //
  //---------------------------------------------------------------------------
public:
  
  // define the class name
  //
  static const unichar CLASS_NAME[];

  //----------------------------------------
  //
  // other important constants
  //
  //----------------------------------------
  
  //----------------------------------------
  //
  // default values and arguments
  //
  //----------------------------------------  

  // define the default value(s) of the class data
  //
  static const int32 DEF_NUM_ELEMENTS = 0;
  static const int32 DEF_CAPACITY = 0;
  static const int32 DEF_GROW_FACTOR = 2;
  
  //----------------------------------------
  //
  // error codes
  //
  //----------------------------------------  
  
  static const int32 ERR = 1700;
  static const int32 ERR_HEMPTY = 1701;
  static const int32 ERR_INVPTR = 1702;    
  
  //---------------------------------------------------------------------------
  //
  // protected data
  //
  //---------------------------------------------------------------------------
protected:
  
  // array of void pointers
  //
  void** data_d;

  // capacity of heap
  //
  int32 capacity_d;

  // number of elements in heap
  //
  int32 num_elements_d;

  // growth factor of heap
  //
  int32 grow_factor_d;
  
  // declare a static debug level for all class instantiations
  //
  static Integral::DEBUG debug_level_d;
  
  //---------------------------------------------------------------------------
  //
  // required public methods
  //
  //---------------------------------------------------------------------------
public:
    
  // method: name 
  //
  static const SysString& name() {
    static SysString temp((unichar*)CLASS_NAME);
    return temp;
  }

  // other static methods
  //  
  static bool8 diagnose(Integral::DEBUG debug_level);
  
  // method: setDebug 
  //  
  static bool8 setDebug(Integral::DEBUG level) {
    debug_level_d = level;
    return true;
  }

  // other debug methods
  //
  bool8 debug(const unichar* msg) const;
  
  // destructor/constructor(s)
  //
  ~SysHeap();  
  SysHeap();

  // assign methods:
  //  these methods are omitted because SysHeap cannot be duplicated
  //
  
  // operator= methods:
  //  these methods are omitted because SysHeap cannot be duplicated
  //
  
  // i/o methods:
  //  these methods are omitted because SysHeap can not write itself
  //  to an sof file
  //
  
  // equality methods
  //
  bool8 eq(const SysHeap& arg);
  
  // memory management methods
  //  new and delete are omitted because memory for SysHeap objects is
  //  not managed by the MemoryManager class
  //
  bool8 clear(Integral::CMODE ctype_a = Integral::DEF_CMODE);

  //---------------------------------------------------------------------------
  //
  // class-specific public methods:
  //  heap information methods
  //
  //---------------------------------------------------------------------------

  // method: build
  //
  bool8 build();

  // method: isEmpty
  //
  bool8 isEmpty() const {
    return (num_elements_d == 0);
  }

  // method: length
  //
  int32 length() const {
    return num_elements_d;
  }

  //---------------------------------------------------------------------------
  //
  // class-specific public methods:
  //  data manipulation methods
  //
  //---------------------------------------------------------------------------

  // insert methods:
  //  these methods add a pointer to the heap
  //
  bool8 insert(void* ptr);

  // find methods:
  //  these methods are used to find elements in the heap
  //
  int32 find(void* ptr, int32 start_index = 0) const;  
  
  // extract methods:
  //  these methods remove a pointer from the heap
  //
  bool8 extractMax(void*& ptr);  
  bool8 extract(void* ptr);
  bool8 extract(void* ptr, int32 pos);
  
  // set methods:
  //  these methods set parameters associated with the heap
  //
  bool8 setLength(int32 len);
  bool8 setCapacity(int32 cap);

  // method: setGrow
  //
  bool8 setGrow(int32 grow_factor) {
    if (grow_factor < 2) {
      return Error::handle(name(), L"setGrow", Error::ARG, __FILE__, __LINE__);
    }
    grow_factor_d = grow_factor;
    return true;
  }    
  
  //---------------------------------------------------------------------------
  //
  // private methods
  //
  //---------------------------------------------------------------------------
private:

  // copy constructor:
  //  this copy constructor cannot be called for the SysHeap class
  //
  SysHeap(const SysHeap& arg);
  
  // heapify methods
  //
  bool8 heapify(int32 index);

  // bubble up methods
  //
  bool8 bubbleUp(int32 index);
  
  // method: parent
  //
  int32 parent(int32 index) const {
    if (index <= 0) {
      return Error::handle(name(), L"parent", ERR, __FILE__, __LINE__);
    }  
    return ((index + 1) / 2 - 1);
  }

  // method: left
  //  since the heap is zero based the left child will be at 2 * i + 1
  //
  int32 left(int32 index) const {
    return (2 * index + 1);
  }

  // method: right
  //  since the heap is zero based the right child will be at 2 * i + 2  
  //
  int32 right(int32 index) const {
    return (2 * index + 2);
  }
};

// end of include file
// 
#endif
