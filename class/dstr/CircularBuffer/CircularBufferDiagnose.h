// file: $isip/class/dstr/CircularBuffer/CircularBufferDiagnose.h
// version: $Id: CircularBufferDiagnose.h 10636 2007-01-26 22:18:09Z tm334 $
//

// make sure definitions are only made once
//
#ifndef ISIP_CIRCULAR_BUFFER_DIAGNOSE
#define ISIP_CIRCULAR_BUFFER_DIAGNOSE

// isip include files
//
#ifndef ISIP_CIRCULAR_BUFFER
#include <CircularBuffer.h>
#endif

// CircularBufferDiagnose: a class that contains the diagnose method
// of the CircularBuffer class.
//
template<class TObject>
class CircularBufferDiagnose : public CircularBuffer<TObject> {
  
  //---------------------------------------------------------------------------
  //
  // public constants
  //
  //---------------------------------------------------------------------------
public:
  
  // define the class name
  //
  
  //----------------------------------------
  //
  // i/o related constants
  //
  //----------------------------------------

  //----------------------------------------
  //
  // default values and arguments
  //
  //----------------------------------------
  
  // default values
  //
  
  // default arguments to methods
  //
  
  //----------------------------------------
  //
  // error codes
  //
  //----------------------------------------  
  
  //---------------------------------------------------------------------------
  //
  // protected data
  //
  //---------------------------------------------------------------------------
protected:
  
  //---------------------------------------------------------------------------
  //
  // required public methods
  //
  //---------------------------------------------------------------------------
public:
  
  // method: name
  //
  static const String& name() {
    return CircularBuffer<TObject>::name();
  }

  // other static methods
  //  
  static bool8 diagnose(Integral::DEBUG debug_level);
  
  // debug methods
  //  these methods are omitted since this class does not have data
  //  members and operations  
  //
  
  // destructor/constructor(s):
  //  these methods are omitted since this class does not have data
  //  members and operations
  //

  // assign methods:
  //  these methods are omitted since this class does not have data
  //  members and operations
  //

  // operator= methods:
  //  these methods are omitted since this class does not have data
  //  members and operations
  //  

  // i/o methods:
  //  these methods are omitted since this class does not have data
  //  members and operations
  //

  // equality methods:
  //  these methods are omitted since this class does not have data
  //  members and operations
  //

  // memory-management methods:
  //  these methods are omitted since this class does not have data
  //  members and operations
  //
  
  //---------------------------------------------------------------------------
  //
  // class-specific public methods:
  //
  //---------------------------------------------------------------------------

  //  these methods are omitted since this class does not have data
  //  members and operations
  //
  
  //---------------------------------------------------------------------------
  //
  // private methods
  //
  //---------------------------------------------------------------------------
private:

};

// below are all the methods for the CircularBufferDiagnose template class
//      

//----------------------------------------------------------------------
//
// required static methods
//
//----------------------------------------------------------------------

// method: diagnose
//
// arguments:
//  Integral::DEBUG level: (input) debug level for diagnostics
//
// return: a bool8 value indicating status
//
template<class TObject>
bool8 CircularBufferDiagnose<TObject>::diagnose(Integral::DEBUG level_a) {

  //----------------------------------------------------------------------
  //
  // 0. preliminaries
  //
  //----------------------------------------------------------------------

  // output the class name
  //
  if (level_a > Integral::NONE) {
    SysString output(L"diagnosing class ");
    output.concat(CircularBuffer<TObject>::CLASS_NAME);
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

  // test the debug methods
  //
  CircularBuffer<TObject>::setDebug(CircularBuffer<TObject>::debug_level_d);
  
  if (level_a > Integral::BRIEF) {
    Integral::debug(L"debug");
  }

  // test constructors
  //
  CircularBuffer<Float> cbuf(100);

  // test getCapacity
  //
  if (cbuf.getCapacity() != 100) {
    return Error::handle(name(), L"constructor/getCapacity", Error::TEST,
			 __FILE__, __LINE__);
  }

  // test isEmpty
  //
  if (!cbuf.isEmpty()) {
    return Error::handle(name(), L"constructor/isEmpty", Error::TEST,
			 __FILE__, __LINE__);
  }

  // testing copy constructor
  //   
  CircularBuffer<Float> copy_cbuf(cbuf);
    
  if (!cbuf.eq(copy_cbuf)) {

    if (level_a >= Integral::ALL) {
      copy_cbuf.debug(L"copy_cbuf");
      cbuf.debug(L"cbuf");
    }
    
    return Error::handle(name(), L"copy constructor/eq", Error::TEST,
			 __FILE__, __LINE__);
  }
  
  // testing memory allocation and deletion
  //
  CircularBuffer<TObject>::setGrowSize((int32)731);
  CircularBuffer<TObject>** cbufs = new CircularBuffer<TObject>*[100];
  
  // test new operator
  //
  for (int32 i = 0; i < 100; i++) {
    cbufs[i] =  new CircularBuffer<TObject>();
  }
  
  // test delete operator
  //
  for (int32 i = 99; i >= 0; i--) {
    delete cbufs[i];
  }
  
  // test delete[] operator
  //
  delete [] cbufs;

  // test the i/o methods
  //
  CircularBuffer<Float> cb2(150);
  CircularBuffer<Float> cb3;
  CircularBuffer<Float> cb4;

  // prepare some data  
  //
  Vector<Float> val_assign(200);
  for (int32 i = 0; i < 200; i++) {
    val_assign(i) = (float32)i;
  }
  
  // append single element at a time
  // [0 - 49] were appended
  //
  for (int32 i = 0; i < 50; i++) {
    cb2.append(val_assign(i));                      
  }

  int32 fowd = cb2.getNumForward();
  cb2.seekCurr(fowd);
  cb2.setRead(fowd);

  // [50 - 199] were appended
  //
  cb2.append(val_assign, 100, 50);                 
  cb2.seekCurr(fowd);
  
  // we need binary and text sof files
  //
  String tmp_filename0;
  Integral::makeTemp(tmp_filename0);
  String tmp_filename1;
  Integral::makeTemp(tmp_filename1);

  // open files in write mode
  //
  Sof tmp_file0;
  tmp_file0.open(tmp_filename0, File::WRITE_ONLY, File::TEXT);
  Sof tmp_file1;
  tmp_file1.open(tmp_filename1, File::WRITE_ONLY, File::BINARY);

  cb2.write(tmp_file0, (int32)0);
  cb2.write(tmp_file1, (int32)0);

  // close the files
  //
  tmp_file0.close();
  tmp_file1.close();

  // open the files in read mode
  //
  tmp_file0.open(tmp_filename0);
  tmp_file1.open(tmp_filename1);

  // read the value back
  //
  cb3.read(tmp_file0, (int32)0);

  if (!cb3.eq(cb2)) {
    if (level_a >= Integral::ALL) {
      cb3.debug(L"cb3 is circular buffer read");
    }
    return Error::handle(name(), L"read", Error::TEST, __FILE__, __LINE__);
  }

  cb4.read(tmp_file0, (int32)0);
  if (!cb4.eq(cb2)) {
    if (level_a >= Integral::ALL) {
      cb4.debug(L"cb4");
    }
    return Error::handle(name(), L"read", Error::TEST, __FILE__, __LINE__);
  }

  // close and  delete the temporary files
  //
  tmp_file0.close();
  tmp_file1.close();

  File::remove(tmp_filename0);
  File::remove(tmp_filename1);

  // reset indentation
  //
  if (level_a > Integral::NONE) {
    Console::decreaseIndention();
  }
  
  // --------------------------------------------------------------------
  //
  // 2. testing class-specific public methods
  //     operator overload methods
  //
  // --------------------------------------------------------------------

  // set indentation
  //
  if (level_a > Integral::NONE) {
    Console::put(L"testing class-specific public methods: operator overload methods...\n");
    Console::increaseIndention(); 
  }
  
  // test some basic operation
  //
  CircularBuffer<Float> cbuf1;
  Float f = 0.1;
  cbuf1.append(f);
  cbuf1.setRead(1);
  f.assign(0.2);
  cbuf1.append(f);

  if ((cbuf1.getNumElements() != 1) ||
      (cbuf1.getNumForward() != 0) ||
      (cbuf1.getNumBackward() != 0) ||
      (!cbuf1(0).almostEqual(0.2))) {
    cbuf1.debug(L"cbuf1");
    return Error::handle(name(), L"diagnose", Error::TEST, __FILE__, __LINE__);
  }

  // test some basic operation
  //
  CircularBuffer<Float> cbuf2(20);
  f = 0.1;
  cbuf2.append(f);
  f.assign(0.2);
  cbuf2.append(f);

  if ((cbuf2.getNumElements() != 2) ||
      (cbuf2.getNumForward() != 1) ||
      (cbuf2.getNumBackward() != 0) ||
      (!cbuf2(0).almostEqual(0.1)) ||
      (!cbuf2(1).almostEqual(0.2))) {
    cbuf2.debug(L"cbuf2");
    return Error::handle(name(), L"diagnose", Error::TEST, __FILE__, __LINE__);
  }

  // test prepen
  //
  f = 0.4;
  cbuf2.prepend(f);
  if ((cbuf2.getNumElements() != 3) ||
      (cbuf2.getNumForward() != 1) ||
      (cbuf2.getNumBackward() != 1) ||
      (!cbuf2(1).almostEqual(0.2)) ||
      (!cbuf2(0).almostEqual(0.1)) ||
      (!cbuf2(-1).almostEqual(0.4))) {
    cbuf2.debug(L"cbuf2");
    return Error::handle(name(), L"diagnose", Error::TEST, __FILE__, __LINE__);
  }

  f = 0.3;
  cbuf2.append(f);
  if ((cbuf2.getNumElements() != 4) ||
      (cbuf2.getNumForward() != 2) ||
      (cbuf2.getNumBackward() != 1) ||
      (!cbuf2(2).almostEqual(0.3)) ||
      (!cbuf2(1).almostEqual(0.2)) ||
      (!cbuf2(0).almostEqual(0.1)) ||
      (!cbuf2(-1).almostEqual(0.4))) {
    cbuf2.debug(L"cbuf2");
    return Error::handle(name(), L"diagnose", Error::TEST, __FILE__, __LINE__);
  }

  f = 0.7;
  cbuf2.prepend(f);
  if ((cbuf2.getNumElements() != 5) ||
      (cbuf2.getNumForward() != 2) ||
      (cbuf2.getNumBackward() != 2) ||
      (!cbuf2(2).almostEqual(0.3)) ||
      (!cbuf2(1).almostEqual(0.2)) ||
      (!cbuf2(0).almostEqual(0.1)) ||
      (!cbuf2(-1).almostEqual(0.4)) ||
      (!cbuf2(-2).almostEqual(0.7))) {
    cbuf2.debug(L"cbuf2");
    return Error::handle(name(), L"diagnose", Error::TEST, __FILE__, __LINE__);
  }
  
  // reset indentation
  //
  if (level_a > Integral::NONE) {
    Console::decreaseIndention();
  }

  // --------------------------------------------------------------------
  //
  // 3. testing class-specific public methods
  //     get methods
  //
  // --------------------------------------------------------------------
  
  // set indentation
  //
  if (level_a > Integral::NONE) {
    Console::put(L"testing class-specific public methods: get methods...\n");
    Console::increaseIndention(); 
  }
  
  if (cbuf1.getNumElements() != 1) {
    return Error::handle(name(), L"append", Error::TEST, __FILE__, __LINE__);
  }
  
  // prepare data  
  //
  Vector<Float> floats(200);
  for (int32 i = 0; i < 200; i++) {
    floats(i) = (float32)i;
  }
  
  // append single element at a time
  // [0 - 49] were appended
  //
  for (int32 i = 0; i < 50; i++) {
    cbuf.append(floats(i));
  }
  
  if (cbuf.getNumElements() != 50) {
    return Error::handle(name(), L"append", Error::TEST, __FILE__, __LINE__);
  }
  
  // append a vector of numbers at a time
  // [50 - 99] were appended
  //
  cbuf.append(floats, 50, 50);
  
  // test some basic operation
  //
  CircularBuffer<Float> cbuf3(100);
  
  // prepend single element at a time
  // [50 - 99] were prepended
  //
  for (int32 i = 0; i < 50; i++) {
    cbuf3.prepend(floats(i));
  }
  
  if (cbuf3.getNumElements() != 50) {
    return Error::handle(name(), L"prepend", Error::TEST, __FILE__, __LINE__);
  }
  
  // append a vector of numbers at a time
  // [0 - 49] were appended
  //
  cbuf3.prepend(floats, 49, 50);
  
  // reset indentation
  //
  if (level_a > Integral::NONE) {
    Console::decreaseIndention();
  }
  
  // --------------------------------------------------------------------
  //
  // 4. testing class-specific public methods
  //     class property methods
  //
  // --------------------------------------------------------------------

  // set indentation
  //
  if (level_a > Integral::NONE) {
    Console::put(L"testing class-specific public methods: class property methods...\n");
    Console::increaseIndention(); 
  }
  
  // the buffer should be full now
  //
  if (!cbuf.isFull()) {
    return Error::handle(name(), L"isFull", Error::TEST, __FILE__, __LINE__);
  }
  
  if (cbuf.getNumElements() != 100) {
    return Error::handle(name(), L"append", Error::TEST, __FILE__, __LINE__);
  }
  
  for (int32 i = 0; i < 100; i++) {
    if (cbuf(i) != (float32)i) {
      return Error::handle(name(), L"append", Error::TEST, __FILE__, __LINE__);
    }
  }
  
  // move the curr and read index
  // release [0 - 49]
  //
  cbuf.setRead((int32)50);                           
  cbuf.resetCurr();
  
  // the valid number of elements should be reduced now
  //
  if (cbuf.getNumElements() != 50) {
    return Error::handle(name(), L"setRead", Error::TEST, __FILE__, __LINE__);
  }

  // reset indentation
  //
  if (level_a > Integral::NONE) {
    Console::decreaseIndention();
  }
  
  // --------------------------------------------------------------------
  //
  // 5. testing class-specific public methods
  //     data manipulation methods
  //
  // --------------------------------------------------------------------

  // set indentation
  //
  if (level_a > Integral::NONE) {
    Console::put(L"testing class-specific public methods: data manipulation methods...\n");
    Console::increaseIndention(); 
  }

  // add more data into the CircularBuffer
  // [100 - 149] overwrote the [0 - 49]
  //
  cbuf.append(floats, 50, 100);

  // get the number
  //
  for (int32 i = 0; i < 100; i++) {
    if (cbuf(i) != (float32)(50 + i)) {
      return Error::handle(name(), L"append", Error::TEST, __FILE__, __LINE__);
    }
  }
  
  // prepare data  
  //
  Vector<Float> vfloats(200);
  for (int32 i = 0; i < 200; i++) {
    vfloats(i) = (float32)i;
  }

  CircularBuffer<Float> cbuf7;
  CircularBuffer<Float> cbuf8;  
  
  // append single element at a time
  // buffer contains [0 - 199]
  //
  for (int32 i = 0; i < 200; i++) {
    cbuf7.append(vfloats(i));
  }

  // append the vector
  // buffer contains [0 - 199]
  //
  cbuf8.append(vfloats);

  if (!cbuf7.eq(cbuf8)) {
    return Error::handle(name(), L"append", Error::TEST, __FILE__, __LINE__);
  }

  // append a portion of the vector
  //
  cbuf7.append(vfloats, 50, 50);
  cbuf8.append(vfloats, 50, 50);   

  if (!cbuf7.eq(cbuf8)) {
    return Error::handle(name(), L"append", Error::TEST, __FILE__, __LINE__);
  }

  CircularBuffer<Float> cbuf5;
  CircularBuffer<Float> cbuf6;  
  
  // prepend single element at a time
  // buffer contains [199 - 0]
  //
  for (int32 i = 0; i < 200; i++) {
    cbuf5.prepend(vfloats(i));
  }

  // prepend the vector
  // buffer contains [199 - 0]
  //
  cbuf6.prepend(vfloats);

  if (!cbuf5.eq(cbuf6)) {
    return Error::handle(name(), L"prepend", Error::TEST, __FILE__, __LINE__);
  }

  // prepend a portion of the vector
  //
  cbuf5.prepend(vfloats, 50, 50);
  cbuf6.prepend(vfloats, 50, 50);   

  if (!cbuf5.eq(cbuf6)) {
    return Error::handle(name(), L"prepend", Error::TEST, __FILE__, __LINE__);
  }  
  
  // reset indentation
  //
  if (level_a > Integral::NONE) {
    Console::decreaseIndention();
  }
  
  // --------------------------------------------------------------------
  //
  // 6. testing class-specific public methods
  //     operator overload methods
  //
  // --------------------------------------------------------------------

  // set indentation
  //
  if (level_a > Integral::NONE) {
    Console::put(L"testing class-specific public methods: positioning methods...\n");
    Console::increaseIndention(); 
  }
  
  // move the curr_d
  //
  cbuf.seekCurr((int32)50);

  if (cbuf.getNumForward() != 49 ) {
    return Error::handle(name(), L"getNumForward", Error::TEST, __FILE__,
			 __LINE__);
  }
  if (cbuf.getNumBackward() != 50 ) {
    return Error::handle(name(), L"getNumBackward", Error::TEST, __FILE__,
			 __LINE__);
  }
  
  // get a vector of elements
  //
  Vector<Float> tmp_vec;

  // get [100 - 119]
  //
  cbuf.getElement(tmp_vec, 20, 0);
  
  for (int32 i = 0; i < 20; i++) {
    if (tmp_vec(i) != (float32)(100 + i)) {
      if (level_a >= Integral::ALL) {
	tmp_vec.debug(L"tmp_vec");
      }
      return Error::handle(name(), L"getElement", Error::TEST, __FILE__,
			   __LINE__);
    }
  }
  
  // print out the debug information
  // only the last 10 numbers [140 - 149] are still valid
  //
  cbuf.setRead((int32)90);               
  cbuf.setDebug(Integral::NONE);
  if (level_a >= Integral::ALL) {
    cbuf.debug(L"cbuf");
  }

  // test seekCurr and get the element with negative offset
  //
  cbuf.seekCurr(9);
  
  if (cbuf(0) != (float32)149 || cbuf(-2) != (float32)147) {
    return Error::handle(name(), L"seekCurr", Error::TEST, __FILE__, __LINE__);
  }
  
  cbuf.seekCurr(-5);
  
  if (cbuf(0) != (float32)144 || cbuf(-4) != (float32)140 ||
      cbuf(4) != (float32)148) {
    return Error::handle(name(), L"seekCurr", Error::TEST, __FILE__, __LINE__);
  }
  
  // test a smaller buffer
  //
  CircularBuffer<Long> buf;
  cbuf.setCapacity(20);
  
  for (int32 i = 0; i < 100; i++) {
    
    if (i > 20) {
      buf.setRead(1);
    }
    
    Long l = (int32)i;
    buf.append(l);
    if (i > 1) {
      buf.seekCurr(1);
    }
  }

  // test clear
  //
  buf.clear();
  if (buf.getNumElements() != 0) {
    return Error::handle(name(), L"clear", Error::TEST, __FILE__, __LINE__);
  }

  // reset indentation
  //
  if (level_a > Integral::NONE) {
    Console::decreaseIndention();
  }
  
  //---------------------------------------------------------------------
  //
  // 3. print completion message
  //
  //---------------------------------------------------------------------

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

// end of include file
//
#endif
