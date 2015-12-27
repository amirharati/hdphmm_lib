// file: $isip/class/dstr/Vector/VectorDiagnose.h
// version: $Id: VectorDiagnose.h 10636 2007-01-26 22:18:09Z tm334 $
//

// make sure definitions are made only once
//
#ifndef ISIP_VECTOR_DIAGNOSE
#define ISIP_VECTOR_DIAGNOSE

// isip include files
//
#ifndef ISIP_VECTOR
#include <Vector.h>
#endif

#ifndef ISIP_FILENAME
#include "Filename.h"
#endif

// VectorDiagnose: a class that contains the diagnose method of Vector class.
//
template<class TObject>
class VectorDiagnose : public Vector<TObject> {
  
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
    return Vector<TObject>::name();
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

// below are all the methods for the VectorDiagnose template class
//

//-----------------------------------------------------------------------
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
bool8 VectorDiagnose<TObject>::diagnose(Integral::DEBUG level_a) {

  //---------------------------------------------------------------------------
  //
  // 0. preliminaries
  //
  //---------------------------------------------------------------------------

  // output the class name
  //
  if (level_a > Integral::NONE) {
    SysString output(L"diagnosing class ");
    output.concat(Vector<TObject>::CLASS_NAME);
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

  // prepare items for all the vectors used in this diagnose 
  //
  int32 num_elem = 10;
  Char** items = new Char*[num_elem];
  
  for (int32 i = 0; i < num_elem; i++) {
    items[i] = new Char();
  }

  // test setDebug
  //
  Vector<TObject>::setDebug(Vector<TObject>::debug_level_d);
  
  // test constructors
  //
  
  // check the constructors for allocating on the stack
  //
  Vector<Char> def_vector((int32)3);         // default constructor
  def_vector(0).assign(*items[0]);
  def_vector(1).assign(*items[1]);
  def_vector(2).assign(*items[2]);
  
  Vector<Char> copy_vector(def_vector);     // copy constructor

  Vector<Char> opeq_vector;
  opeq_vector = def_vector;
  
  // the two constructed vectors should have the same items now
  //
  if (def_vector.ne(copy_vector)) {
     return Error::handle(name(), L"copy constructor", Error::TEST, __FILE__,
			  __LINE__);
  }

  // the two constructed vectors should have the same items now
  //
  if (def_vector.ne(opeq_vector)) {
     return Error::handle(name(), L"copy constructor", Error::TEST, __FILE__,
			  __LINE__);
  }

  // check the constructors and destructors for allocating on the dynamic
  // memory heap
  //
  Vector<Char>* def_dyn_vector = new Vector<Char>((int32)3);
  (*def_dyn_vector)(0).assign(*items[0]);
  (*def_dyn_vector)(1).assign(*items[1]);
  (*def_dyn_vector)(2).assign(*items[2]);
  
  Vector<Char>* copy_dyn_vector = new Vector<Char>(*def_dyn_vector);

  // the two constructed vectors should have the same items now
  //
  if (def_dyn_vector->ne(copy_vector)) {
    return Error::handle(name(), L"copy constructor", Error::TEST, __FILE__,
			 __LINE__);
  }
  
  // see if we can dynamically delete
  //
  delete def_dyn_vector;
  delete copy_dyn_vector;
  
  // test memory management
  //
  // set the memory to a strange block size so we can hopefully catch any
  // frame overrun errors
  //
  Vector<Char>::setGrowSize((int32)731);
  
  // loop for a large number of times creating and deleting a large number
  // of vectors at each loop
  //
  for (int32 j = 1; j <= 10; j++) {
    Vector<Char>** vectors = new Vector<Char>*[j * 100];
    
    // create the items
    //
    for (int32 i = 0; i < j * 100; i++) {
      vectors[i] =  new Vector<Char>();
    }
    
    // delete vectors
    //
    for (int32 i = (j * 100) - 1; i >= 0; i--) {
      delete vectors[i];
    }
    
    // clean up memory
    //
    delete [] vectors;
  }

  // clean up
  //
  for (int32 i = 0; i < num_elem; i++) {
    delete items[i];
  }
  delete [] items;
  
  // test assign methods, including operator =
  //

  // create some temporary vectors
  //
  Vector<Char> tmp_vector(def_vector);

  Vector<Char>* tmp_dyn_vector = new Vector<Char>();
  
  // try the vector assign method
  //
  tmp_dyn_vector->assign(tmp_vector);

  if (tmp_dyn_vector->ne(tmp_vector)) {
    return Error::handle(name(), L"vector assign", Error::TEST, __FILE__,
			 __LINE__);
  }

  // test operator =
  //
  Vector<Char> tmp_vector_2;
  tmp_vector_2 = tmp_vector;

  if (tmp_vector_2.ne(tmp_vector)) {
    return Error::handle(name(), L"operator =", Error::TEST, __FILE__,
			 __LINE__);
  }

  // clean up
  //
  delete tmp_dyn_vector;

  // testing equality methods
  //
  
  // initialize Vectors and Char objects to use for testing
  //
  Vector<Char> char_vector(1000);
  unichar tmp_char = L'a';
  
  // initialize the characters and store them in the vectors
  //
  for (int32 i = 0; i < 500; i++) {
    
    // add the character to the vector
    //
    char_vector(i).assign(tmp_char);

    // increment the character value
    //
    tmp_char++;
  }

  // we also want a really big vector for i/o testing
  //
  int32 num_floats = 3050; // BUGBUG: change to 3050
  Vector<Float> float_vec(num_floats);
  for (int32 i = 0; i < num_floats; i++) {
    float_vec(i) = i * 2.0;
  }

  // create another vector the same as this
  //
  Vector<Char> char_copy_vector(char_vector);
  
  if (!char_vector.eq(char_copy_vector)) {
    return Error::handle(name(), L"eq", Error::TEST, __FILE__, __LINE__);
  }

  // test i/o methods
  //

  // we need binary and text sof files
  //
  Filename text_filename;
  Filename bin_filename;
  Integral::makeTemp(text_filename);
  Integral::makeTemp(bin_filename);
  File::registerTemp(text_filename);
  File::registerTemp(bin_filename);
  
  // open files in write mode
  //
  Sof text_file;
  text_file.open(text_filename, File::WRITE_ONLY, File::TEXT);
  Sof bin_file;
  bin_file.open(bin_filename, File::WRITE_ONLY, File::BINARY);

  // prepare items for the vectors
  //
  String write_strings[5];
  
  write_strings[0].assign(L"this ");
  write_strings[1].assign(L"is");
  write_strings[2].assign(L"a");
  write_strings[3].assign(L"Vector");
  write_strings[4].assign(L"String");

  DoubleLinkedList<Char> write_llist[5];
  Char** chars = new Char*[5];
  for (int32 i = 0; i < 5; i++) {
    write_llist[i].setAllocationMode(DstrBase::USER);
    chars[i] = new Char((unichar)((int)'a' + i));
    for (int32 j = 0; j < i + 1; j++) {
      write_llist[i].insert(chars[j]);
    }
  }

  // create vectors to write
  //
  Vector<Char> write_null_vector;          // vector of length 0
  Vector<Char> write_char_vector(1);       // vector of length 1
  Vector<String> write_str_vector(5);
  Vector< DoubleLinkedList<Char> > write_llist_vector(5);
  Vector< Vector<Char> > write_char_vec_vector(3);
  
  write_char_vector(0).assign(*chars[0]);
  for ( int32 i = 0; i < 5; i++) {
    write_str_vector(i).assign(write_strings[i]);
    write_llist_vector(i).assign(write_llist[i]);
  }
  write_char_vec_vector.assign(write_char_vector);

  // write the values
  //
  write_null_vector.write(text_file, (int32)10);
  write_null_vector.write(bin_file, (int32)10);  
  
  write_char_vector.write(text_file, (int32)0);
  write_char_vector.write(bin_file, (int32)0);  

  write_str_vector.write(text_file, (int32)0);
  write_str_vector.write(bin_file, (int32)0);

  write_llist_vector.write(text_file, (int32)0);
  write_llist_vector.write(bin_file, (int32)0);

  write_char_vec_vector.write(text_file, (int32)0);
  write_char_vec_vector.write(bin_file, (int32)0);

  float_vec.write(text_file, (int32)0);
  float_vec.write(bin_file, (int32)0);
  
  // write a compound object with both an empty and non-empty Vector in it.
  //
  String object(L"Object");
  String pname0(L"values0");
  String pname1(L"values1");
  String pname2(L"values2");
  int32 obj_size = write_char_vector.sofSize() +
    write_null_vector.sofSize() + write_llist_vector.sofSize();
  
  text_file.put(object, 0, -1);
  bin_file.put(object, 0, obj_size);

  text_file.writeLabelPrefix(String::EMPTY);
  write_char_vector.writeData(text_file, pname0);
  write_char_vector.writeData(bin_file, pname0);

  write_null_vector.writeData(text_file, pname1);
  write_null_vector.writeData(bin_file, pname1);

  write_llist_vector.writeData(text_file, pname2);
  write_llist_vector.writeData(bin_file, pname2);
  
  text_file.writeLabelSuffix(String::EMPTY);

  // clear methods are tested at the end of the diagnose method
  //
  
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

  text_file.put(write_str_vector.name(), 1, -1);
  bin_file.put(write_str_vector.name(), 1, write_str_vector.sofSize());
      
  int32 pos_text = write_str_vector.writeStart(text_file);
  int32 pos_bin = write_str_vector.writeStart(bin_file);

  write_str_vector.writePartialData(text_file, 0, 2);
  write_str_vector.writePartialData(text_file, 2, 2);
  write_str_vector.writeTerminate(text_file);

  write_str_vector.writePartialData(bin_file, 0, 2);
  write_str_vector.writePartialData(bin_file, 2, 1);
  write_str_vector.writeTerminate(bin_file);
  
  text_file.put(float_vec.name(), 7, -1);

  pos_text = float_vec.writeStart(text_file);
  
  float_vec.writePartialData(text_file, 0, 50);

  for (int32 i = 0; i < 30; i++) {
    float_vec.writePartialData(text_file, 50 + i * 100, 100);
  }
  
  float_vec.writeTerminate(text_file);
  
  bin_file.put(float_vec.name(), 7, float_vec.sofSize());
  pos_bin = float_vec.writeStart(bin_file);

  float_vec.writePartialData(bin_file, 0, 50);

  for (int32 i = 0; i < 30; i++) {
    float_vec.writePartialData(bin_file, 50 + i * 100, 100);
  }
  float_vec.writeTerminate(bin_file);
  
  
  text_file.put(float_vec.name(), 8, -1);

  pos_text = float_vec.writeStart(text_file);
  
  float_vec.writePartialData(text_file, 0, 50);

  for (int32 i = 0; i < 30; i++) {
    float_vec.writePartialData(text_file, 50 + i * 100, 100);
  }
  
  float_vec.writeTerminate(text_file);
  

  bin_file.put(float_vec.name(), 8, float_vec.sofSize());
  pos_bin = float_vec.writeStart(bin_file);
  
  float_vec.writePartialData(bin_file, 0, 100);
  
  for (int32 i = 1; i < 30; i++) {
    float_vec.writePartialData(bin_file, i * 100, 100);
  }
  
  float_vec.writePartialData(bin_file, 3000, 50);

  float_vec.writeTerminate(bin_file);
  

  // close the files
  //
  text_file.close();
  bin_file.close();

  if (level_a > Integral::BRIEF) {
    write_llist_vector.debug(L"write_llist_vector");
  }
  
  // open the files in read mode
  //
  text_file.open(text_filename);
  bin_file.open(bin_filename);

  // read the vector written by partial write 
  //
  Vector<String> read_part_str_text;
  read_part_str_text.read(text_file, (int32)1);

  if (level_a > Integral::BRIEF) {
    read_part_str_text.debug(L"read_part_str");
  }
  
  Vector<String> read_part_str_bin;
  read_part_str_bin.read(bin_file, (int32)1);

  if (level_a > Integral::BRIEF) {  
    read_part_str_bin.debug(L"read_part_bin");
  }
  
  // create objects for reading in
  //
  Vector<Char> read_null_vector_text;
  Vector<Char> read_null_vector_bin;
  Vector<Char> read_char_vector_text;
  Vector<Char> read_char_vector_bin;
  Vector<String> read_str_vector_text;
  Vector<String> read_str_vector_bin;

  Vector<Float> read_float_vec_text;
  Vector<Float> read_float_vec_bin;

  Vector< DoubleLinkedList<Char> > read_llist_vector_text;
  Vector< DoubleLinkedList<Char> > read_llist_vector_bin;

  Vector< Vector<Char> > read_char_vec_vector_text;
  Vector< Vector<Char> > read_char_vec_vector_bin;

  // read in the vectors and test for equivalence
  // if there is error, print out the vectors
  //
  if (!read_null_vector_text.read(text_file, (int32)10) ||
      (read_null_vector_text.ne(write_null_vector))) {
    read_null_vector_text.debug(L"read_null_vector_text");
    return Error::handle(name(), L"read null char text", Error::TEST, __FILE__,
			 __LINE__);
  }
  
  if (!read_null_vector_bin.read(bin_file, (int32)10) ||
      (read_null_vector_bin.ne(write_null_vector))) {
    return Error::handle(name(), L"read null char bin", Error::TEST, __FILE__,
			 __LINE__);
  }
  
  if (!read_char_vector_text.read(text_file, (int32)0) ||
      (read_char_vector_text.ne(write_char_vector))) {
    return Error::handle(name(), L"read char text", Error::TEST, __FILE__,
			 __LINE__);
  }
  
  if (!read_char_vector_bin.read(bin_file, (int32)0) ||
      (read_char_vector_bin.ne(write_char_vector))) {
    return Error::handle(name(), L"read char bin", Error::TEST, __FILE__,
			 __LINE__);
  }
  
  if (!read_str_vector_text.read(text_file, (int32)0) ||
      (read_str_vector_text.ne(write_str_vector))) {
    return Error::handle(name(), L"read str text", Error::TEST, __FILE__, 
			 __LINE__);
  }
    
  if (!read_str_vector_bin.read(bin_file, (int32)0) ||
      (read_str_vector_bin.ne(write_str_vector))) {
    return Error::handle(name(), L"read str bin", Error::TEST, __FILE__,
			 __LINE__);
  }

  if (!read_llist_vector_text.read(text_file, (int32)0) ||
      (read_llist_vector_text.ne(write_llist_vector))) {
    return Error::handle(name(), L"read llist text", Error::TEST, __FILE__, 
			 __LINE__);
  } 
  
  if (!read_llist_vector_bin.read(bin_file, (int32)0) ||
      (read_llist_vector_bin.ne(write_llist_vector))) {
    return Error::handle(name(), L"read llist bin", Error::TEST, __FILE__,
			 __LINE__);
  }
       
  if (!read_char_vec_vector_text.read(text_file, (int32)0) ||
      (read_char_vec_vector_text.ne(write_char_vec_vector))) {
    return Error::handle(name(), L"read str text", Error::TEST, __FILE__, 
			 __LINE__);
  }
	  
  if (!read_char_vec_vector_bin.read(bin_file, (int32)0) ||
      (read_char_vec_vector_bin.ne(write_char_vec_vector))) {
    return Error::handle(name(), L"read str bin", Error::TEST, __FILE__,
			 __LINE__);
  }

  if (!read_float_vec_text.read(text_file, (int32)0) ||
      (read_float_vec_text.ne(float_vec))) {
    return Error::handle(name(), L"read float text", Error::TEST, __FILE__, 
			 __LINE__);
  }

  if (!read_float_vec_bin.read(bin_file, (int32)0) ||
      (read_float_vec_bin.ne(float_vec))) {
    read_float_vec_bin.debug(L"float_vec");
    return Error::handle(name(), L"read float bin", Error::TEST, __FILE__, 
			 __LINE__);
  }

  // read the multi-vector object
  //
  if (!text_file.find(object, 0) || !bin_file.find(object, 0)) {
    return Error::handle(name(), L"find", Error::TEST, __FILE__, __LINE__);
  }

  // read the binary file first
  //
  read_char_vector_bin.clear();
  if (!read_char_vector_bin.readData(bin_file, pname0) ||
      read_char_vector_bin.ne(write_char_vector)) {
    return Error::handle(name(), L"read", Error::TEST, __FILE__, __LINE__);
  }

  read_null_vector_bin.clear();
  if (!read_null_vector_bin.readData(bin_file, pname1) ||
      read_null_vector_bin.ne(write_null_vector)) {
    return Error::handle(name(), L"read", Error::TEST, __FILE__, __LINE__);
  }

  read_llist_vector_bin.clear();
  if (!read_llist_vector_bin.readData(bin_file, pname2) ||
      read_llist_vector_bin.ne(write_llist_vector)) {
    return Error::handle(name(), L"read", Error::TEST, __FILE__, __LINE__);
  }

  // now read the text file
  //
  SofParser obj_parser;
  obj_parser.load(text_file, SofParser::FULL_OBJECT);
  read_char_vector_text.clear();
  if (!read_char_vector_text.readData(text_file, pname0,
				      obj_parser.getEntry(text_file, pname0),
				      false, false) ||
      read_char_vector_text.ne(write_char_vector)) {
    read_char_vector_text.debug(L"read_char_vector");
    write_char_vector.debug(L"write_char_vector");
    return Error::handle(name(), L"read", Error::TEST, __FILE__, __LINE__);
  }

  read_null_vector_text.clear();
  if (!read_null_vector_text.readData(text_file, pname1,
				      obj_parser.getEntry(text_file, pname1),
				      false, false) ||
      read_null_vector_text.ne(write_null_vector)) {
    return Error::handle(name(), L"read", Error::TEST, __FILE__, __LINE__);
  }

  read_llist_vector_text.clear();
  if (!read_llist_vector_text.readData(text_file, pname2,
				       obj_parser.getEntry(text_file, pname2),
				       false, false) ||
      read_llist_vector_text.ne(write_llist_vector)) {
    read_llist_vector_text.debug(L"read_llist_vector");
    write_llist_vector.debug(L"write_llist_vector");
    return Error::handle(name(), L"read", Error::TEST, __FILE__, __LINE__);
  }


  // read the output of the partial write
  //
  read_float_vec_bin.clear();
  if (!read_float_vec_bin.read(bin_file, (int32)7) ||
      (read_float_vec_bin.ne(float_vec))) {
    read_float_vec_bin.debug(L"float_vec");
    return Error::handle(name(), L"read partial float bin", Error::TEST,
			 __FILE__, __LINE__);
  }

  read_float_vec_bin.clear();
  if (!read_float_vec_bin.read(bin_file, (int32)8) ||
      (read_float_vec_bin.ne(float_vec))) {
    read_float_vec_bin.debug(L"float_vec");
    return Error::handle(name(), L"read partial float bin", Error::TEST,
			 __FILE__, __LINE__);
  }

  read_float_vec_text.clear();
  if (!read_float_vec_text.read(text_file, (int32)7) ||
      (read_float_vec_text.ne(float_vec))) {
    read_float_vec_text.debug(L"float_vec");
    return Error::handle(name(), L"read partial float bin", Error::TEST,
			 __FILE__, __LINE__);
  }

  read_float_vec_text.clear();
  if (!read_float_vec_text.read(text_file, (int32)8) ||
      (read_float_vec_text.ne(float_vec))) {
    read_float_vec_text.debug(L"float_vec");
    return Error::handle(name(), L"read partial float bin", Error::TEST,
			 __FILE__, __LINE__);
  }

  if (level_a > Integral::BRIEF) {
    Console::put(L"testing partial read\n");
  }
  
  // create objects for reading partial data in
  //
  Vector<Char> read_partial_char_text;
  Vector<Char> read_partial_char_bin;
  Vector<String> read_partial_str_text;
  Vector<String> read_partial_str_bin;
  
  Vector< DoubleLinkedList<Char> > read_partial_llist_text;
  Vector< DoubleLinkedList<Char> > read_partial_llist_bin;
  
  Vector< Vector<Char> > read_partial_char_vec_text;
  Vector< Vector<Char> > read_partial_char_vec_bin;

  if (!text_file.find(read_partial_char_vec_text.name(), (int32)0)) {
    return Error::handle(name(), L"find", Error::TEST, __FILE__, __LINE__);
  }

  if (!bin_file.find(read_partial_char_vec_text.name(), (int32)0)) {
    return Error::handle(name(), L"find", Error::TEST, __FILE__, __LINE__);
  }

  read_partial_char_vec_text.readStart(text_file);

  
  // partial read for Vector<Vector<Char>>
  //
  if (read_partial_char_vec_text.readPartialData(text_file, 0, 2) != 2) {
    return Error::handle(name(), L"readPartialData", Error::TEST,
			 __FILE__, __LINE__);
  }
  
  if (read_partial_char_vec_text.readPartialData(text_file, 0, 3) != 3) {
    return Error::handle(name(), L"readPartialData", Error::TEST,
			 __FILE__, __LINE__);
  }
  
  if (read_partial_char_vec_text.readPartialData(text_file, 1, 2) != 2) {
    read_partial_char_vec_text.debug(L"read_partial_vec_char_text");
    return Error::handle(name(), L"readPartialData", Error::TEST,
			 __FILE__, __LINE__);
  }

  if (read_partial_char_vec_text.readPartialData(text_file, 2, 1) != 1) {
    read_partial_char_vec_text.debug(L"read_partial_vec_char_text");
    return Error::handle(name(), L"readPartialData", Error::TEST,
			 __FILE__, __LINE__);
  }
  
  // call read terminate to clean
  //
  read_partial_char_vec_text.readTerminate(text_file);

  // partial read for Vector<Char>
  //
  if (!text_file.find(read_partial_char_text.name(), (int32)0)) {
    return Error::handle(name(), L"find", Error::TEST, __FILE__, __LINE__);
  }

  if (!read_partial_char_text.readStart(text_file)) {
    return Error::handle(name(), L"readStart", Error::TEST, __FILE__,
			 __LINE__);
  }
  
  if ((read_partial_char_text.readPartialData(text_file, 0, 1) != 1) ||
      read_partial_char_text(0).ne(*chars[0])) {
    read_partial_char_text.debug(L"read_partial_char_text");
    return Error::handle(name(), L"readPartialData", Error::TEST,
			 __FILE__, __LINE__);
  }    

  // test readTerminate
  //
  read_partial_char_text.readTerminate(text_file);
  
  if (!bin_file.find(read_partial_char_bin.name(), (int32)0)) {
    return Error::handle(name(), L"find", Error::TEST, __FILE__, __LINE__);
  }
  
  if (!read_partial_char_bin.readStart(bin_file)) {
    return Error::handle(name(), L"readStart", Error::TEST, __FILE__,
			 __LINE__);
  }
  
  if ((read_partial_char_bin.readPartialData(bin_file, 0, 1) != (int32)1)
      || (read_partial_char_bin(0).ne(*chars[0]))) {

    read_partial_char_bin.debug(L"read_partial_char_bin");
    return Error::handle(name(), L"read partial char bin", Error::TEST,
			 __FILE__, __LINE__);
  }

  // call readTerminate
  //  
  read_partial_char_bin.readTerminate(bin_file);
  
  // partial read for Vector<String>
  //
  if (!text_file.find(read_partial_str_text.name(), (int32)0)) {
    return Error::handle(name(), L"find", Error::TEST, __FILE__, __LINE__);
  }

  if (!bin_file.find(read_partial_str_text.name(), (int32)0)) {
    return Error::handle(name(), L"find", Error::TEST, __FILE__, __LINE__);
  }

  if (!read_partial_str_text.readStart(text_file)) {
    return Error::handle(name(), L"readStart", Error::TEST, __FILE__,
			 __LINE__);
  }

  if ((read_partial_str_text.readPartialData(text_file, 1, 3) != (int32)3)
      || (read_partial_str_text(0).ne(write_strings[1]))) {
    read_partial_str_text.debug(L"read_partial_str_text");
    return Error::handle(name(), L"read partial str text", Error::TEST,
			 __FILE__, __LINE__);
  }
  
  if ((read_partial_str_text.readPartialData(text_file, 0, 3) != (int32)3)
      || (read_partial_str_text(0).ne(write_strings[0]))) {
    read_partial_str_text.debug(L"read_partial_str_text");
    return Error::handle(name(), L"read partial str text", Error::TEST,
			 __FILE__, __LINE__);
  }

  if ((read_partial_str_text.readPartialData(text_file, 1, 2) != (int32)2)
      || (read_partial_str_text(0).ne(write_strings[1]))) {
    read_partial_str_text.debug(L"read_partial_str_text");
    return Error::handle(name(), L"read partial str text", Error::TEST,
			 __FILE__, __LINE__);
  }

  read_partial_str_text.readTerminate(text_file);
  
  if (!read_partial_str_bin.readStart(bin_file)) {
    return Error::handle(name(), L"readStart", Error::TEST, __FILE__,
			 __LINE__);
  }
  if ((read_partial_str_bin.readPartialData(bin_file, 1, 3) != (int32)3)
      || (read_partial_str_bin(0).ne(write_strings[1]))) {
    
      read_partial_str_bin.debug(L"read_partial_str_bin");
      return Error::handle(name(), L"read partial str bin", Error::TEST,
			 __FILE__, __LINE__);
  }
  read_partial_str_bin.readTerminate(bin_file);

  
  // partial read for Vector<Float>
  //
  read_float_vec_text.clear();
  read_float_vec_bin.clear();
  
  if (!text_file.find(Vector<Float>::name(), (int32)7)) {
    return Error::handle(name(), L"find", Error::TEST, __FILE__, __LINE__);
  }

  if (!bin_file.find(Vector<Float>::name(), (int32)7)) {
    return Error::handle(name(), L"find", Error::TEST, __FILE__, __LINE__);
  }

  if (!read_float_vec_text.readStart(text_file)) {
    return Error::handle(name(), L"readStart", Error::TEST, __FILE__,
			 __LINE__);
  }

  if (!read_float_vec_bin.readStart(bin_file)) {
    return Error::handle(name(), L"readStart", Error::TEST, __FILE__,
			 __LINE__);
  }


  int32 read_size = 50;
  Vector<Float> vecf_expected(read_size);

  VectorLong start_positions(L"0, 3, 98, 99, 100, 130, 180, 290, 340, 391, 443, 980, 1273, 1993, 2000, 2100, 841");

  for (int32 j = 0; j < start_positions.length(); j++) {

    int32 start = start_positions(j);
    
    for (int32 i = 0; i < read_size; i++) {
      vecf_expected(i) = float_vec(i + start);
    }
    if ((read_float_vec_text.readPartialData(text_file,
					     start, read_size) != read_size)
	|| (read_float_vec_text.ne(vecf_expected))) {
      
      read_float_vec_text.debug(L"read_float_vec_text");
      vecf_expected.debug(L"vecf_expected");
      return Error::handle(name(), L"read partial float text", Error::TEST,
			   __FILE__, __LINE__);
    }
    if ((read_float_vec_bin.readPartialData(bin_file, start,
					    read_size) != read_size)
	|| (read_float_vec_bin.ne(vecf_expected))) {
      Long(j).debug(L"j=");
      read_float_vec_bin.debug(L"read_float_vec_bin");
      vecf_expected.debug(L"vecf_expected");
      return Error::handle(name(), L"read partial float bin", Error::TEST,
			   __FILE__, __LINE__);
    }
  }

  read_size = 1;

  for (int32 j = 995; j < float_vec.length() - read_size; j++) {

    int32 start = j;
    
    for (int32 i = 0; i < read_size; i++) {
      vecf_expected(i) = float_vec(i + start);
    }

    if ((read_float_vec_text.readPartialData(text_file,
					     start, read_size) != read_size)
	|| (read_float_vec_text(0).ne(vecf_expected(0)))) {
      
      read_float_vec_text(0).debug(L"read_float_vec_text");
      vecf_expected.debug(L"vecf_expected");
      return Error::handle(name(), L"read partial float text", Error::TEST,
			   __FILE__, __LINE__);
    }

    if ((read_float_vec_bin.readPartialData(bin_file, start,
					    read_size) != read_size)
	|| (read_float_vec_bin(0).ne(vecf_expected(0)))) {
      Long(j).debug(L"j=");
      read_float_vec_bin.debug(L"read_float_vec_bin");
      vecf_expected(0).debug(L"vecf_expected");
      return Error::handle(name(), L"read partial float bin", Error::TEST,
			   __FILE__, __LINE__);
    }
  }
  
  for (int32 j = 0; j < float_vec.length() - read_size; j++) {

    int32 start = j;
    
    for (int32 i = 0; i < read_size; i++) {
      vecf_expected(i) = float_vec(i + start);
    }

    if ((read_float_vec_text.readPartialData(text_file,
					     start, read_size) != read_size)
	|| (read_float_vec_text(0).ne(vecf_expected(0)))) {
      
      read_float_vec_text(0).debug(L"read_float_vec_text");
      vecf_expected.debug(L"vecf_expected");
      return Error::handle(name(), L"read partial float text", Error::TEST,
			   __FILE__, __LINE__);
    }

    if ((read_float_vec_bin.readPartialData(bin_file, start,
					    read_size) != read_size)
	|| (read_float_vec_bin(0).ne(vecf_expected(0)))) {
      Long(j).debug(L"j=");
      read_float_vec_bin.debug(L"read_float_vec_bin");
      vecf_expected(0).debug(L"vecf_expected");
      return Error::handle(name(), L"read partial float bin", Error::TEST,
			   __FILE__, __LINE__);
    }
  }

  read_float_vec_text.readTerminate(text_file);
  read_float_vec_bin.readTerminate(bin_file);

  // close and delete the temporary files
  //
  text_file.close();
  bin_file.close();

  // cleanup the memory that was created by the Vector read
  //
  read_char_vector_text.clear();
  read_char_vector_bin.clear();
  read_str_vector_text.clear();
  read_str_vector_bin.clear();
  read_llist_vector_text.clear();
  read_llist_vector_bin.clear();
  read_char_vec_vector_text.clear();
  read_char_vec_vector_bin.clear();

  read_partial_char_text.clear();
  read_partial_char_bin.clear();
  read_partial_str_text.clear();
  read_partial_str_bin.clear();
  read_partial_char_vec_text.clear();
  read_partial_char_vec_bin.clear(); 
  read_partial_llist_text.clear();
  read_partial_llist_bin.clear();

  write_char_vector.clear();
  write_str_vector.clear();
  write_llist_vector.clear();
  write_char_vec_vector.clear();
  
  for (int32 i = 0; i < 5; i++) {
    delete chars[i];
  }
  delete [] chars; 

  // test the object assign method
  //
  Vector<Long> vec_int32;
  vec_int32.setLength(2);

  // assign the int32 object (note we can not assign((int32)-1) directly)
  //
  Long number((int32)-1);
  vec_int32.assign(number);        

  // test ne methods
  //
  if (char_vector.ne(char_copy_vector)) {
    return Error::handle(name(), L"ne", Error::TEST, __FILE__, __LINE__);
  }
      
  // reset indentation
  //
  if (level_a > Integral::NONE) {
    Console::decreaseIndention();
  }


  //--------------------------------------------------------------------------
  //
  // 3. class-specific public methods:
  //     item access methods
  //
  //--------------------------------------------------------------------------

  // set indentation
  //
  if (level_a > Integral::NONE) {
    Console::put(L"testing class-specific public methods: item access methods...\n");
    Console::increaseIndention();
  }

  // test operator() methods
  //
  if (char_vector(0).ne(L'a')) {
    return Error::handle(name(), L"operator()", Error::TEST,
			 __FILE__, __LINE__);
  }

  // reset indentation
  //
  if (level_a > Integral::NONE) {
    Console::decreaseIndention();
  }

  //---------------------------------------------------------------------------
  //
  // 4. class-specific public methods:
  //     size-related methods
  //
  //---------------------------------------------------------------------------   
  // set indentation
  //
  if (level_a > Integral::NONE) {
    Console::put(L"testing class-specific public methods: size-related methods...\n");
    Console::increaseIndention();
  }

  // testing length methods:
  //  initialize a vector of length 10
  //
  Vector<Char> def_vector_2((int32)10);

  if (def_vector_2.length() != 10) {
    return Error::handle(name(), L"length", Error::TEST, __FILE__,
                         __LINE__);
  }
  
  // set the capacity
  //
  def_vector_2.setCapacity((int32)500);

  if (((int32)def_vector_2.capacity_d) != 500) {
    return Error::handle(name(), L"setCapacity", Error::TEST, __FILE__,
                         __LINE__);
  }

  if (def_vector_2.getCapacity() != 500) {
    return Error::handle(name(), L"getCapacity", Error::TEST, __FILE__,
                         __LINE__);
  }
  
  // set the length to be a large value, the capacity should also grow if the 
  // new length is greater than the capacity
  //
  def_vector_2.setLength((int32)1000);
  
  if (((int32)(def_vector_2.length_d) != 1000) || (((int32)def_vector_2.capacity_d) != 1000)) {
    return Error::handle(name(), L"setLength", Error::TEST, __FILE__,
                         __LINE__);
  }

  // reset indentation
  //
  if (level_a > Integral::NONE) {
    Console::decreaseIndention();
  }

  //---------------------------------------------------------------------------
  //
  // 5. class-specific public methods:
  //     data manipulation methods
  //
  //--------------------------------------------------------------------------

  // set indentation
  //
  if (level_a > Integral::NONE) {
    Console::put(L"testing class-specific public methods: data manipulation methods...\n");
    Console::increaseIndention();
  }

  // test positioning methods:
  //  initialize vectors and chars to use for testing 
  //
  Vector<Char> char_val_0((int32)2);
  Char tmp(L'f');
  char_val_0.assign(tmp);
  
  Vector<Char> char_val_1((int32)5);
  Vector<Char> char_val_2;
  Vector<Char> result((int32)5);
  
  tmp_char = L'a';
  for (int32 i = 0; i < 5; i++) {
    char_val_1(i).assign(tmp_char);
    tmp_char++;
  }

  // move 4 elements starting from the 2nd element in val1, put into val0
  // starting from 2nd element, val0 will be resized
  // 
  char_val_0.move(char_val_1, 4, 1, 1);
  
  result(0).assign(L'f');
  result(1).assign(L'b');
  result(2).assign(L'c');
  result(3).assign(L'd');
  result(4).assign(L'e');
  
  if (char_val_0.ne(result)) {
    char_val_0.debug(L"move ->");
    return Error::handle(name(), L"move", Error::TEST, __FILE__, __LINE__);
  }
  
  // move 2 elements starting from the 2nd element
  // in char_val_1, put into char_val_0 starting from 1st element
  //
  char_val_0.move(char_val_1, 2, 1, 0);

  // char_val_0 was "f, b, c, d, e", and char_val_1 is "a, b, c, d, e",
  // so char_val_0 should be "b, c, c, d, e"
  //
  result(0).assign(L'b');
  result(1).assign(L'c');
  result(2).assign(L'c');
  result(3).assign(L'd');
  result(4).assign(L'e');
  
  if (char_val_0.ne(result)) {
    char_val_0.debug(L"char_val_0");
    return Error::handle(name(), L"move", Error::TEST, __FILE__, __LINE__);
  } 

  // shift char_val_0 2 elements to the right
  //
  char_val_1.shift(char_val_0, 2);
  char_val_0.shift(2);
  result(0).assign(Char::DEF_VALUE);
  result(1).assign(Char::DEF_VALUE);
  result(2).assign(L'b');
  result(3).assign(L'c');
  result(4).assign(L'c');
  
  if (char_val_0.ne(result)) {
    return Error::handle(name(), L"shift", Error::TEST, __FILE__, __LINE__);
  }

  if (char_val_1.ne(result)) {
    char_val_1.debug(L"char_val_1");
    result.debug(L"result");
    return Error::handle(name(), L"shift", Error::TEST, __FILE__, __LINE__);
  }

  // shift char_val_0 1 elements to the left
  //
  char_val_1.shift(char_val_0, -1);
  char_val_0.shift(-1);
  result(0).assign(Char::DEF_VALUE);
  result(1).assign(L'b');
  result(2).assign(L'c');
  result(3).assign(L'c');
  result(4).assign(Char::DEF_VALUE);
  
  if (char_val_0.ne(result)) {
    return Error::handle(name(), L"shift", Error::TEST, __FILE__, __LINE__);
  }

  if (char_val_1.ne(result)) {
    return Error::handle(name(), L"shift", Error::TEST, __FILE__, __LINE__);
  }
  
  // concatenate
  //
  char_val_0.setLength((int32)3);
  tmp.assign(L'a');
  char_val_0.assign(tmp);
  char_val_1.setLength((int32)2);
  tmp.assign(L'b');
  char_val_1.assign(tmp);

  char_val_2.concat(char_val_0, char_val_1);
  char_val_0.concat(char_val_1);

  // char_val_0 was "a, a, a", char_val_1 is "b, b", so the result should
  // be "a,a,a,b,b"
  //
  tmp.assign(L'a');
  result.assign(tmp);
  result(3).assign(L'b');
  result(4).assign(L'b');

  if (char_val_0.ne(result)) {
    return Error::handle(name(), L"concat", Error::TEST, __FILE__, __LINE__);
  } 

  if (char_val_2.ne(result)) {
    return Error::handle(name(), L"concat", Error::TEST, __FILE__, __LINE__);
  } 

  char_val_0.clear(Integral::FREE);
  Char c(L'a');
  char_val_0.concat(c);
  char_val_0.concat(c);
  char_val_0.concat(c);
  c.assign(L'b');
  char_val_0.concat(c);
  char_val_0.concat(c);
  
  if (char_val_0.ne(result)) {
    char_val_0.debug(L"got this char vector");
    result.debug(L"result is this char vector");
    return Error::handle(name(), L"concat", Error::TEST, __FILE__, __LINE__);
  } 

  // test deleteRange
  //
  char_val_1.assign(char_val_0);
  char_val_1.deleteRange(0, 2);

  char_val_2.shift(result, -2);
  char_val_2.setLength(3);
  if (char_val_2.ne(char_val_1)) {
    char_val_2.debug(L"char_val_2");
    char_val_1.debug(L"char_val_1");
    result.debug(L"result");
    return Error::handle(name(), L"deleteRange", Error::TEST, __FILE__,
			 __LINE__);
  }

  // test deleting to the end
  //
  char_val_1.assign(char_val_0);
  char_val_1.deleteRange(3, 2);
  char_val_2.clear();
  char_val_2.setLength(3);
  char_val_2(0).assign(L'a');
  char_val_2(1).assign(L'a');
  char_val_2(2).assign(L'a');
  if (char_val_2.ne(char_val_1)) {
    char_val_2.debug(L"char_val_2");
    char_val_1.debug(L"char_val_1");
    char_val_0.debug(L"char_val_0");
    return Error::handle(name(), L"deleteRange", Error::TEST, __FILE__,
			 __LINE__);
  }

  // test deleting in the middle
  //
  char_val_1.assign(char_val_0);
  char_val_1.deleteRange(1, 3);
  char_val_2.clear();
  char_val_2.setLength(2);
  char_val_2(0).assign(L'a');
  char_val_2(1).assign(L'b');
  if (char_val_2.ne(char_val_1)) {
    char_val_2.debug(L"char_val_2");
    char_val_1.debug(L"char_val_1");
    char_val_0.debug(L"char_val_0");
    return Error::handle(name(), L"deleteRange", Error::TEST, __FILE__,
			 __LINE__);
  }


  // test deleteRange
  //
  char_val_1.deleteRange(char_val_0, 0, 2);

  char_val_2.shift(result, -2);
  char_val_2.setLength(3);
  if (char_val_2.ne(char_val_1)) {
    char_val_2.debug(L"char_val_2");
    char_val_1.debug(L"char_val_1");
    result.debug(L"result");
    return Error::handle(name(), L"deleteRange", Error::TEST, __FILE__,
			 __LINE__);
  }

  // test deleting to the end
  //
  char_val_1.deleteRange(char_val_0, 3, 2);
  char_val_2.clear();
  char_val_2.setLength(3);
  char_val_2(0).assign(L'a');
  char_val_2(1).assign(L'a');
  char_val_2(2).assign(L'a');
  if (char_val_2.ne(char_val_1)) {
    char_val_2.debug(L"char_val_2");
    char_val_1.debug(L"char_val_1");
    char_val_0.debug(L"char_val_0");
    return Error::handle(name(), L"deleteRange", Error::TEST, __FILE__,
			 __LINE__);
  }

  // test deleting in the middle
  //
  char_val_1.deleteRange(char_val_0, 1, 3);
  char_val_2.clear();
  char_val_2.setLength(2);
  char_val_2(0).assign(L'a');
  char_val_2(1).assign(L'b');
  if (char_val_2.ne(char_val_1)) {
    char_val_2.debug(L"char_val_2");
    char_val_1.debug(L"char_val_1");
    char_val_0.debug(L"char_val_0");
    return Error::handle(name(), L"deleteRange", Error::TEST, __FILE__,
			 __LINE__);
  }
  
  // test setValue
  //
  char_val_1.assign(char_val_0);

  c.assign(L'd');
  char_val_1.setRange(2, 2, c);
  
  char_val_2.setLength(5);
  char_val_2(0).assign(L'a');
  char_val_2(1).assign(L'a');
  char_val_2(2).assign(L'd');
  char_val_2(3).assign(L'd');
  char_val_2(4).assign(L'b');
  if (char_val_2.ne(char_val_1)) {
    char_val_2.debug(L"char_val_2");
    char_val_1.debug(L"char_val_1");
    char_val_0.debug(L"char_val_0");
    return Error::handle(name(), L"deleteRange", Error::TEST, __FILE__,
			 __LINE__);
  }

  // test sort methods:
  //  initialize vectors and Char objects to use for testing
  //
  Vector<Char> char_vector_1((int32)10);
  Vector<Char> char_vector_2((int32)10);
  Vector<Char> char_vector_3((int32)10);
  unichar low_tmp_char = L'a';
  unichar up_tmp_char = L'A';
  
  // initialize the characters and store them in reverse order in two vectors
  //
  for (int32 i = 0; i < 10; i++) {

    // add the character to the end of the vector 1 (ascending)
    //
    char_vector_1(i).assign(low_tmp_char);

    // add the character to the beginning of the vector 2 (descending)
    //
    char_vector_2(10 - i -1).assign(low_tmp_char);

    // add the uppercase character to the end of the vector 3 (descending)
    //
    char_vector_3(10 - i -1).assign(up_tmp_char);
    
    // increment the character value
    //
    low_tmp_char++;
    up_tmp_char++;
  }

  // sort the vector 2 in ASCENDING order
  //
  char_vector_2.sort();
  
  // the vector 2 should be the same as the vector 1 now
  //
  if (char_vector_1.ne(char_vector_2)) {
    return Error::handle(name(), L"sort", Error::TEST, __FILE__, __LINE__);
  } 

  // sort the vector 1 in DESCENDING order
  //
  char_vector_1.sort(Integral::DESCENDING);
  
//  char_vector_1.sort();
  
  // apply a method to all the nodes in vector 1
  //
  char_vector_1.apply(&Char::toUpper);
  
  // vector 1 should be the same as the vector 3 now 
  //
  if (char_vector_1.ne(char_vector_3)) {
    return Error::handle(name(), L"apply", Error::TEST, __FILE__, __LINE__);
  }

  // declare a Vector<Long> [5, 3, 2, 6, 4, 1, 3, 7]
  //
  Vector<Long> nums(8);
  nums(0) = 5;
  nums(1) = 3;
  nums(2) = 2;
  nums(3) = 6;
  nums(4) = 4;
  nums(5) = 1;
  nums(6) = 3;
  nums(7) = 7;
  
  // insertion sort
  //
  nums.sort(Integral::ASCENDING, Vector<Long>::INSERTION);

  for (int32 i = 0; i < 7; i++) {
    if (nums(i) > nums(i + 1)) {
      nums.debug(L"insertion sort, ascending");
      return Error::handle(name(), L"insertion sort", Error::TEST, __FILE__,
			   __LINE__);
    }
  }

  if (level_a > Integral::BRIEF) {
    nums.debug(L"insertion sort, ascending");
  }

  // insertion sort in descending order
  //
  nums.sort(Integral::DESCENDING, Vector<Long>::INSERTION);

  for (int32 i = 0; i < 7; i++) {
    if (nums(i) < nums(i + 1)) {
      nums.debug(L"insertion sort, ascending");
      return Error::handle(name(), L"insertionSort", Error::TEST, __FILE__,
			   __LINE__);
    }
  }

  // change some numbers in the Vector
  //
  nums(0) = -1;
  nums(4) = -2;

  // randomized quick sort in descending order
  //
  nums.sort(Integral::DESCENDING, Vector<Long>::RAND_QUICK);
  for (int32 i = 0; i < 7; i++) {
    if (nums(i) < nums(i + 1)) {
      nums.debug(L"randQuickSort, descending");
      return Error::handle(name(), L"randQuickSort", Error::TEST, __FILE__,
			   __LINE__);
    }
  }

  // randomized quick sort in ascending order
  //  
  nums(6) = -8;
  nums(7) = 20;
  nums.sort(Integral::ASCENDING, Vector<Long>::RAND_QUICK);
  for (int32 i = 0; i < 7; i++) {
    if (nums(i) > nums(i + 1)) {
      nums.debug(L"randQuickSort, ascending");
      return Error::handle(name(), L"insertion sort", Error::TEST, __FILE__,
			   __LINE__);
    }
  }

  // reset indentation
  //
  if (level_a > Integral::NONE) {
    Console::decreaseIndention();
  }


  //---------------------------------------------------------------------------
  //
  // 6. class-specific public methods:
  //     item location and containment methods
  //
  //--------------------------------------------------------------------------

  // set indentation
  //
  if (level_a > Integral::NONE) {
    Console::put(L"testing class-specific public methods: location/containment methods...\n");
    Console::increaseIndention();
  }

  // declare local variables
  //
  int32 index = 0;
  Char* value = new Char(L'g');

  // char_val_0 is "a,a,a,b,b", so it should contain 'b, but not 'g'
  //
  if (char_val_0.contains(index, value)) {
    return Error::handle(name(), L"contains", Error::TEST, __FILE__, __LINE__);
  }

  if (char_val_0.contains(value)) {
    return Error::handle(name(), L"contains", Error::TEST, __FILE__, __LINE__);
  }

  // test for the existence of 'b'
  //
  value->assign(L'b');
  if ((!char_val_0.contains(index, value)) || (index != 3)) {
    return Error::handle(name(), L"contains", Error::TEST, __FILE__, __LINE__);
  }

  // find the first 'b' in char_val_0
  //
  if (char_val_0.first(*value) != 3) {
    return Error::handle(name(), L"first", Error::TEST, __FILE__, __LINE__);
  }

  // find the last 'a' in char_val_0
  //
  value->assign(L'a');

  if (char_val_0.last(*value) != 2) {
    return Error::handle(name(), L"last", Error::TEST, __FILE__, __LINE__);
  }

  // clean up
  //
  delete value;

  // reset indentation
  //
  if (level_a > Integral::NONE) {
    Console::decreaseIndention();
  }

  //--------------------------------------------------------------------------
  //
  // 7. class-specific public methods:
  //     apply methods
  //
  //--------------------------------------------------------------------------

  // set indentation
  //
  if (level_a > Integral::NONE) {
    Console::put(L"testing class-specific public methods: apply methods...\n");
    Console::increaseIndention();
  }

  // initialize lists and Char objects to use for testing
  //
  Vector<Char> char_vec_apply_1((int32)10);
  Vector<Char> char_vec_apply_2((int32)10);
  Vector<Char> char_vec_apply_3((int32)10);
  
  // initialize the characters and store them in reverse order in two vectors
  //
  for (int32 i = 0; i < 10; i++) {
    
    // add the character to the end of the vector 1 (ascending)
    //
    char_vec_apply_1(i).assign(low_tmp_char);

    // add the character to the beginning of the vector 2 (descending)
    //
    char_vec_apply_2(10 - i -1).assign(low_tmp_char);

    // add the uppercase character to the end of the vector 3 (descending)
    //
    char_vec_apply_3(10 - i -1).assign(up_tmp_char);
    
    // increment the character value
    //
    low_tmp_char++;
    up_tmp_char++;
  }

  // sort vector 1 and apply a method to all the elements in vector
  //
  char_vec_apply_1.sort(Integral::DESCENDING);
  char_vec_apply_1.apply(&Char::toUpper);
  
  // vector 1 should be the same as the vector 3 now 
  //
  if (char_vec_apply_1.ne(char_vec_apply_3)) {
    return Error::handle(name(), L"apply", Error::TEST, __FILE__,
			 __LINE__);
  }

  // apply a method to all the elements in vector 2
  //
  char_vec_apply_2.apply(&Char::toUpper);
  
  // vector 2 should be the same as the vector 3 now 
  //
  if (char_vec_apply_2.ne(char_vec_apply_3)) {
    return Error::handle(name(), L"apply", Error::TEST, __FILE__,
			 __LINE__);
  }

  // reset indentation
  //
  if (level_a > Integral::NONE) {
    Console::decreaseIndention();
  }

  // testing clear methods:
  //  clear the char_vector_1
  //
  char_vector_1.clear(Integral::RETAIN);
  
  if (char_vector_1.length() != 10) {
     return Error::handle(name(), L"clear", Error::TEST, __FILE__, __LINE__);
  }
  
  // clear the char_vector_3
  //
  char_vector_3.clear(Integral::FREE);
  if (char_vector_3.length() != 0) {
    return Error::handle(name(), L"clear(FREE)", Error::TEST,
			 __FILE__, __LINE__);
  } 

  //---------------------------------------------------------------------------
  //
  // 9. print completion message
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
