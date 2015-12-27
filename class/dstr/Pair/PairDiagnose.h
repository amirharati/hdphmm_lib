// file: $isip/class/dstr/Pair/PairDiagnose.h
// version: $Id: PairDiagnose.h 10636 2007-01-26 22:18:09Z tm334 $
//

// make sure definitions are only made once
//
#ifndef ISIP_PAIR_DIAGNOSE
#define ISIP_PAIR_DIAGNOSE

// isip include files
//
#ifndef ISIP_PAIR
#include <Pair.h>
#endif

// PairDiagnose: a class that contains the diagnose method of Pair class.
//
template<class T1, class T2>
class PairDiagnose : public Pair<T1, T2> {

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
    return Pair<T1, T2>::name();
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
  // class-specific public methods
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

// below are all the methods for the PairDiagnose template class
//

//-----------------------------------------------------------------------------
//
// required static methods
//
//-----------------------------------------------------------------------------

// method: diagnose
//
// arguments:
//  Integral::DEBUG level: (input) debug level for diagnostics
//
// return: a bool8 value indicating status
//
template<class T1, class T2>
bool8 PairDiagnose<T1,T2>::diagnose(Integral::DEBUG level_a) {
  
  //---------------------------------------------------------------------------
  //
  // 0. preliminaries
  //
  //---------------------------------------------------------------------------

  // output the class name
  //
  if (level_a > Integral::NONE) {
    SysString output(L"diagnosing class ");
    output.concat(Pair<T1, T2>::CLASS_NAME);
    output.concat(L": ");
    Console::put(output);
    Console::increaseIndention();
  }
  
  //--------------------------------------------------------------------------
  //
  // 1. required public methods
  //
  //--------------------------------------------------------------------------

  // set indentation
  //
  if (level_a > Integral::NONE) {
    Console::put(L"testing required public methods...\n");
    Console::increaseIndention();
  }

  // check the constructors and destructors for allocating on the dynamic
  // memory heap:
  //  default constructor
  //
  Pair<T1, T2>* def_dyn_node = new Pair<T1, T2>();  

  // set the debug level
  //
  Pair<T1, T2>::setDebug(Integral::NONE);
  
  // copy constructor
  //
  Pair<T1, T2>* copy_dyn_node = new Pair<T1, T2>(*def_dyn_node);
  
  // see if we can dynamically delete
  //
  delete def_dyn_node;
  delete copy_dyn_node;
  
  // test large allocation construction and deletion:
  //  set the memory to a strange block size so we can hopefully catch
  //  any frame overrun errors
  //
  Pair<T1, T2>::setGrowSize((int32)731);
  
  // loop for a large number of times creating and deleting a large number
  // of pairs at each loop. we create both SYSTEM-allocating and
  // USER-allocating pairs.
  //
  for (int32 j = 1; j <= 10; j++) {
    Pair<T1, T2>** system_pairs = new Pair<T1, T2>*[j * 10];
    Pair<T1, T2>** pairs = new Pair<T1, T2>*[j * 10];
    
    // create the pairs
    //
    for (int32 i = 0; i < j * 10; i++) {
      system_pairs[i] = new Pair<T1, T2>();
      pairs[i] = new Pair<T1, T2>;
    }
    
    // delete pairs
    //
    for (int32 i = (j * 10) - 1; i >= 0; i--) {
      delete system_pairs[i];
      delete pairs[i];
    }
    
    delete [] system_pairs;
      delete [] pairs;
  }

  // perform the same test using the new[] and delete [] operators
  //
  for (int32 j = 1; j <= 10; j++) {
    
    // allocate a large number of pairs
    //
    Pair<T1, T2>* system_pairs = new Pair<T1, T2>[j * 10];
    Pair<T1, T2>* pairs = new Pair<T1, T2>[j * 10];
    
    // clean up memory
    //
    delete [] system_pairs;
    delete [] pairs;
  }

  // test i/o methods: 
  //  we need binary and text sof files
  //
  String text_filename;
  Integral::makeTemp(text_filename);
  String bin_filename;
  Integral::makeTemp(bin_filename);
  
  // open files in write mode
  //
  Sof text_file;
  text_file.open(text_filename, File::WRITE_ONLY, File::TEXT);
  Sof bin_file;
  bin_file.open(bin_filename, File::WRITE_ONLY, File::BINARY);
  
  // create some objects to write
  //
  Char write_char(L'a');
  String write_str(L"aye");
  Pair<Char, String> write_pair_node(write_char, write_str);

  // print the pairs
  //
  if (level_a >= Integral::ALL) {
    write_pair_node.debug(L"write_pair_node");
  }
  
  // write the values
  //
  write_pair_node.write(text_file, (int32)0);
  write_pair_node.write(bin_file, (int32)0);  
  
  // close the files
  //
  text_file.close();
  bin_file.close();

  // open the files in read mode
  //
  text_file.open(text_filename);
  bin_file.open(bin_filename);

  // create objects for reading in
  //
  Pair<Char, String> read_pair_node_text;
  Pair<Char, String> read_pair_node_bin;

  // read in the pairs and test for equivalence
  //
  if (!read_pair_node_text.read(text_file, (int32)0) ||
      (!read_pair_node_text.eq(write_pair_node))) {
    return Error::handle(name(), L"read", Error::TEST, __FILE__, __LINE__);
  }

  if (!read_pair_node_bin.read(bin_file, (int32)0) ||
      (!read_pair_node_bin.eq(write_pair_node))) {
    return Error::handle(name(), L"write", Error::TEST, __FILE__, __LINE__);
  }

  // print the pairs out
  //
  if (level_a >= Integral::ALL) {
    read_pair_node_text.debug(L"read_pair_node_text");
    read_pair_node_bin.debug(L"read_pair_node_bin");
  }
  
  // close and delete the temporary files
  //
  text_file.close();
  bin_file.close();
  File::remove(text_filename);
  File::remove(bin_filename);

  // test equality methods
  //
  Char obj1(L'a');
  String obj2(L"boy");
  Float obj3 = (float32)1.0;
  Pair<Char, String> obj_1(obj1, obj2);
  Pair<Char, String> obj_2(obj1, obj2);
  
  if (!obj_1.eq(obj_2)) {
    return Error::handle(name(), L"eq", Error::TEST, __FILE__, __LINE__);
  }
    
  // reset indentation
  //
  if (level_a > Integral::NONE) {
    Console::decreaseIndention();
  }

  //--------------------------------------------------------------------------
  //
  // 2. class-specific public methods:
  //     extensions to required methods
  //
  //--------------------------------------------------------------------------

  // set indentation
  //
  if (level_a > Integral::NONE) {
    Console::put(L"testing class-specific public methods: extensions to required methods...\n");
    Console::increaseIndention();
  }
  
  // create some temporary objects and items
  //  
  T1 item0;
  T2 item1;
  
  Pair<T1, T2> tmp_node;

  tmp_node.assign(item0, item1);

  // reset indentation
  //
  if (level_a > Integral::NONE) {
    Console::decreaseIndention();
  }
  
  //--------------------------------------------------------------------------
  //
  // 2. class-specific public methods:
  //     item access methods
  //
  //--------------------------------------------------------------------------

  // set indentation
  //
  if (level_a > Integral::NONE) {
    Console::put(L"testing class-specific public methods: item access methods...\n");
    Console::increaseIndention();
  }

  // test first and second methods
  //
  Char ret_obj1 = obj_1.first();
  String ret_obj2 = obj_1.second();
  
  if (!obj1.eq(ret_obj1)) {
    return Error::handle(name(), L"first", Error::TEST, __FILE__, __LINE__);
  }

  if (!obj2.eq(ret_obj2)) {
    return Error::handle(name(), L"second", Error::TEST, __FILE__, __LINE__);
  }
  
  // we want to keep up with characters and associated strings. we
  // could do this with parallel vectors, but combining the inner
  // data is more natural.
  //
  Vector< Pair<Char, String> > letters(5);
  
  letters(0).first().assign(L'a');
  letters(1).first().assign(L'b');
  letters(2).first().assign(L'c');
  letters(3).first().assign(L'd');
  letters(4).first().assign(L'e');
  
  letters(0).second().assign(L"aye");
  letters(1).second().assign(L"be");
  letters(2).second().assign(L"see");
  letters(3).second().assign(L"de");
  letters(4).second().assign(L"e");
  
  // we might also want to weight these, so,
  
  Vector <Pair < Long, Pair <Char, String> > > wlet(5);
  
  for (int32 i = 0; i < 5; i++) {
    wlet(i).first().assign(i * 3);
    wlet(i).second().assign(letters(i));
  }

  // test the clear method
  //
  wlet(0).clear();
  if ((((int32)wlet(0).first()) != 0)
      || (wlet(0).second().first() != (unichar)0)
      || (wlet(0).second().second().ne(L""))) {
    return Error::handle(name(), L"clear", Error::TEST, __FILE__, __LINE__);
  }
  
  // reset indentation
  //
  if (level_a > Integral::NONE) {
    Console::decreaseIndention();
  }
  
  //---------------------------------------------------------------------------
  //
  // 6. print completion message
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

// end of include file
//
#endif
