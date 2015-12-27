// file: $isip/class/system/SysHeap/sh_02.cc
// version: $Id: sh_02.cc 5463 2000-11-05 01:31:27Z hamaker $
//

// isip include files
//
#include "SysHeap.h"
#include <SysString.h>
#include <Console.h>

// method: diagnose
//
// arguments:
//  Integral::DEBUG level: (input) debug level for diagnostics
//
// return: a bool8 value indicating status
//
bool8 SysHeap::diagnose(Integral::DEBUG level_a) {

  //----------------------------------------------------------------------
  //
  // 0. preliminaries
  //
  //----------------------------------------------------------------------
  
  // output the class name
  //
  if (level_a > Integral::NONE) {
    SysString output(L"diagnosing class ");
    output.concat(CLASS_NAME);
    output.concat(L": ");
    Console::put(output);
    Console::increaseIndention();
  }
  
  //---------------------------------------------------------------------
  //
  // 1. required public methods
  //
  //---------------------------------------------------------------------

  // set indentation
  //
  if (level_a > Integral::NONE) {
    Console::put(L"testing required public methods...\n");
    Console::increaseIndention();
  }

  // testing the debug method
  //
  setDebug(debug_level_d);
  
  if (level_a > Integral::BRIEF) {
    SysHeap tmp;
    tmp.debug(L"debug");
  }

  // testing class constructor
  //
  SysHeap sh_1;
  
  // check values of class data
  //
  if (sh_1.capacity_d != 0) {
    return Error::handle(name(), L"constructor", Error::TEST,
                         __FILE__, __LINE__);
  }
  if (sh_1.num_elements_d != 0) {
    return Error::handle(name(), L"constructor", Error::TEST,
                         __FILE__, __LINE__);
  }
  if (sh_1.grow_factor_d != 2) {
    return Error::handle(name(), L"constructor", Error::TEST,
                         __FILE__, __LINE__);
  }

  // testing the equality method
  //
  if (!sh_1.eq(sh_1)) {
    return Error::handle(name(), L"eq", Error::TEST,
                         __FILE__, __LINE__);
  }
  
  // reset indentation
  //
  if (level_a > Integral::NONE) {
    Console::decreaseIndention();
  }

  //---------------------------------------------------------------------
  //
  // 2. class-specific public methods:
  //     heap information methods
  //
  //---------------------------------------------------------------------

  // set indentation
  //
  if (level_a > Integral::NONE) {
    Console::put(L"testing class-specific public methods: data manipulation methods...\n");
    Console::increaseIndention();
  }

  // declare a SysHeap object
  //
  SysHeap heap;
  heap.setLength(10);
  heap.data_d[0] = (void*)8;
  heap.data_d[1] = (void*)14;
  heap.data_d[2] = (void*)7;
  heap.data_d[3] = (void*)11;
  heap.data_d[4] = (void*)10;
  heap.data_d[5] = (void*)1;
  heap.data_d[6] = (void*)4;
  heap.data_d[7] = (void*)2;
  heap.data_d[8] = (void*)3;
  heap.data_d[9] = (void*)9;
  
  // testing build heap method
  //
  heap.build();

  // testing isEmpty method
  //
  if (heap.isEmpty()) {
    return Error::handle(name(), L"isEmpty", Error::TEST,
                         __FILE__, __LINE__);
  }

  if (((int64)heap.data_d[0] != 14) || ((int64)heap.data_d[1] != 11) ||
      ((int64)heap.data_d[2] != 7) || ((int64)heap.data_d[3] != 8) ||
      ((int64)heap.data_d[4] != 10) || ((int64)heap.data_d[5] != 1) ||
      ((int64)heap.data_d[6] != 4) || ((int64)heap.data_d[7] != 2) ||
      ((int64)heap.data_d[8] != 3) || ((int64)heap.data_d[9] != 9) ||
      (heap.num_elements_d != 10)) {
    heap.debug(L"heap");
    return Error::handle(name(), L"build", Error::TEST,
                         __FILE__, __LINE__);
  }

  // testing length method
  //
  int32 len = heap.length();

  if (len != 10) {
    return Error::handle(name(), L"length", Error::TEST,
                         __FILE__, __LINE__);
  }
    
  // reset indentation
  //
  if (level_a > Integral::NONE) {
    Console::decreaseIndention();
  }
  
  //---------------------------------------------------------------------
  //
  // 3. class-specific public methods:
  //     data manipulation methods  
  //
  //---------------------------------------------------------------------

  // set indentation
  //
  if (level_a > Integral::NONE) {
    Console::put(L"testing class-specific public methods: specific heap property methods...\n");
    Console::increaseIndention();
  }
  
  // testing insert methods
  //
  void* ptr_ins;
  ptr_ins = (void*)12;
  heap.insert(ptr_ins);

  if (((int64)heap.data_d[0] != 14) || ((int64)heap.data_d[1] != 12) ||
      ((int64)heap.data_d[2] != 7) || ((int64)heap.data_d[3] != 8) ||
      ((int64)heap.data_d[4] != 11) || ((int64)heap.data_d[5] != 1) ||
      ((int64)heap.data_d[6] != 4) || ((int64)heap.data_d[7] != 2) ||
      ((int64)heap.data_d[8] != 3) || ((int64)heap.data_d[9] != 9) ||
      ((int64)heap.data_d[10] != 10) ||(heap.num_elements_d != 11)) {
    heap.debug(L"after insert");
    return Error::handle(name(), L"insert", Error::TEST,
                         __FILE__, __LINE__);
  }

  // testing find heap methods
  //
  void* ptr_find_0;
  ptr_find_0 = (void*)11;
  int32 i = heap.find(ptr_find_0);
  
  if (i != 4) {
    return Error::handle(name(), L"find", Error::TEST,
                         __FILE__, __LINE__);
  }

  void* ptr_find_1;
  ptr_find_1 = (void*)9;
  int32 j = heap.find(ptr_find_1);
  
  if (j != 9) {
    return Error::handle(name(), L"find", Error::TEST,
                         __FILE__, __LINE__);
  }

  // testing extract max method
  //
  void* ptr_ext;
  heap.extractMax(ptr_ext);
  
  if (((int64)heap.data_d[0] != 12) || ((int64)heap.data_d[1] != 11) ||
      ((int64)heap.data_d[2] != 7) || ((int64)heap.data_d[3] != 8) ||
      ((int64)heap.data_d[4] != 10) || ((int64)heap.data_d[5] != 1) ||
      ((int64)heap.data_d[6] != 4) || ((int64)heap.data_d[7] != 2) ||
      ((int64)heap.data_d[8] != 3) || ((int64)heap.data_d[9] != 9) ||
      (heap.num_elements_d != 10)) {
    heap.debug(L"after extractMax");
    return Error::handle(name(), L"extractMax", Error::TEST,
                         __FILE__, __LINE__);
  }
  
  // testing extract methods
  //
  void* ptr_ex_0;
  ptr_ex_0 = (void*)11;
  heap.extract(ptr_ex_0);
  
  if (((int64)heap.data_d[0] != 12) || ((int64)heap.data_d[1] != 10) ||
      ((int64)heap.data_d[2] != 7) || ((int64)heap.data_d[3] != 8) ||
      ((int64)heap.data_d[4] != 9) || ((int64)heap.data_d[5] != 1) ||
      ((int64)heap.data_d[6] != 4) || ((int64)heap.data_d[7] != 2) ||
      ((int64)heap.data_d[8] != 3) || (heap.num_elements_d != 9)) {
    heap.debug(L"after extract 11");
    return Error::handle(name(), L"extract", Error::TEST,
                         __FILE__, __LINE__);
  }

  void* ptr_ex_1;
  ptr_ex_1 = (void*)3;
  heap.extract(ptr_ex_1);
  
  if (((int64)heap.data_d[0] != 12) || ((int64)heap.data_d[1] != 10) ||
      ((int64)heap.data_d[2] != 7) || ((int64)heap.data_d[3] != 8) ||
      ((int64)heap.data_d[4] != 9) || ((int64)heap.data_d[5] != 1) ||
      ((int64)heap.data_d[6] != 4) || ((int64)heap.data_d[7] != 2) ||
      (heap.num_elements_d != 8)) {
    heap.debug(L"after extract 3");
    return Error::handle(name(), L"extract", Error::TEST,
                         __FILE__, __LINE__);
  }

  void* ptr_ex_2;
  ptr_ex_2 = (void*)12;
  heap.extract(ptr_ex_2);

  if (((int64)heap.data_d[0] != 10) || ((int64)heap.data_d[1] != 9) ||
      ((int64)heap.data_d[2] != 7) || ((int64)heap.data_d[3] != 8) ||
      ((int64)heap.data_d[4] != 2) || ((int64)heap.data_d[5] != 1) ||
      ((int64)heap.data_d[6] != 4) || (heap.num_elements_d != 7)) {
    heap.debug(L"after extract 12");
    return Error::handle(name(), L"extract", Error::TEST,
                         __FILE__, __LINE__);
  }

  // check boundary case of removing the last item in the heap
  //
  void* ptr_ex_3;
  ptr_ex_3 = (void*)4;
  heap.extract(ptr_ex_3);

  if (((int64)heap.data_d[0] != 10) || ((int64)heap.data_d[1] != 9) ||
      ((int64)heap.data_d[2] != 7) || ((int64)heap.data_d[3] != 8) ||
      ((int64)heap.data_d[4] != 2) || ((int64)heap.data_d[5] != 1) ||
      (heap.num_elements_d != 6)) {
    heap.debug(L"after extract 4");
    return Error::handle(name(), L"extract", Error::TEST,
                         __FILE__, __LINE__);
  }
  
  // testing length and capacity methods
  //
  heap.setLength(1);
  int32 cap2 = heap.capacity_d;

  if (cap2 != 10) {
    return Error::handle(name(), L"setLength", Error::TEST,
                         __FILE__, __LINE__);
  }

  // stress/regression testing of the insert/extract methods 
  //
  SysHeap heap_test;

  int32 A = 50;
  int32 B = 50;

  int32 val = 0;
  
  for (int32 a = 0; a < A; a++) {
    for (int32 b = 0; b < A * B; b += A) {
        val = (B + b) * A + a;
        heap_test.insert((void*)val);
    }
  }
    
  for (int32 a = 0; a < 40; a++) {
    for (int32 b = 0; b < A * B; b += A) {
      val = (B + b) * A + a;
      heap_test.extract((void*)val);
    }
  }

  // reset indentation
  //
  if (level_a > Integral::NONE) {
    Console::decreaseIndention();
  }

  // another stress test of SysHeap
  //
  SysHeap dh;
  for (int32 j = 1; j <= 10; j++) {
    
    float64** dyn_cal = new float64*[j * 100];
    
    // create the objects
    //
    for (int32 i = 0; i < j * 100; i++) {
      dyn_cal[i] = new float64;
      dh.insert(dyn_cal[i]);
    }

    // delete the objects
    //
    for (int32 i = (j * 100) - 1; i >= 0; i--) {
      dh.extract(dyn_cal[i]);
      delete dyn_cal[i];
    }
    
    delete [] dyn_cal;
  }
  
  //---------------------------------------------------------------------------
  //
  // 4. print completion message
  //
  //---------------------------------------------------------------------------

  // reset indentation
  //
  if (level_a > Integral::NONE) {
    Console::decreaseIndention();
  }
  
  if (level_a > Integral::NONE) {
    SysString output(L"diagnostics passed for class ");
    output.concat(name());
    output.concat(L"\n");
    Console::put(output);
  }

  // exit gracefully
  //
  return true;
}
