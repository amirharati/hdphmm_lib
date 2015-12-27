// file: $isip/class/dstr/DoubleLinkedList/DoubleLinkedListDiagnose.h
// version: $Id: DoubleLinkedListDiagnose.h 10636 2007-01-26 22:18:09Z tm334 $
//

// make sure definitions are made only once
//
#ifndef ISIP_DOUBLE_LINKED_LIST_DIAGNOSE
#define ISIP_DOUBLE_LINKED_LIST_DIAGNOSE

// isip include files
//
#ifndef ISIP_DOUBLE_LINKED_LIST
#include "DoubleLinkedList.h"
#endif

// DoubleLinkedListDiagnose: a class that contains the diagnose method
// of DoubleLinkedList class.
//
template<class TObject>
class DoubleLinkedListDiagnose : public DoubleLinkedList<TObject> {
  
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
    return DoubleLinkedList<TObject>::name();
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

// below are all the methods for the DoubleLinkedListDiagnose template class
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
bool8 DoubleLinkedListDiagnose<TObject>::diagnose(Integral::DEBUG level_a) {

  //----------------------------------------------------------------------
  //
  // 0. preliminaries
  //
  //----------------------------------------------------------------------

  // output the class name
  //
  if (level_a > Integral::NONE) {
    SysString output(L"diagnosing class ");
    output.concat(DoubleLinkedList<TObject>::CLASS_NAME);
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
  DoubleLinkedList<TObject>::setDebug(DoubleLinkedList<TObject>::debug_level_d);
  
  if (level_a > Integral::BRIEF) {
    Integral::debug(L"debug");
  }

  // prepare items for all the lists used in this diagnose 
  //
  int32 num_elem = 10;
  Char** items = new Char*[num_elem];
  
  for (int32 i = 0; i < num_elem; i++) {
    items[i] = new Char((unichar)((int32)'a' + i));
  }
  
  // test constructors and memory management
  //
  DoubleLinkedList<Char> def_list;
  def_list.insertFirst(items[0]);
  def_list.insert(items[1]);
  def_list.insertLast(items[2]);

  // copy constructor
  //
  DoubleLinkedList<Char> copy_list(def_list);     
  
  // the two constructed lists should have the same items in the nodes now
  //
  if (def_list.ne(copy_list)) {
    return Error::handle(name(), L"copy constructor", Error::TEST, __FILE__,
			 __LINE__);
  }

  // print out the list
  //
  if (level_a >= Integral::ALL) {
    def_list.debug(L"def_list");
  }
  
  // check the constructors and destructors for allocating on the dynamic
  // memory heap
  //
  DoubleLinkedList<Char>* def_dyn_list = new DoubleLinkedList<Char>();
  def_dyn_list->insertFirst(items[0]);
  def_dyn_list->insert(items[1]);
  def_dyn_list->insertLast(items[2]);
  
  DoubleLinkedList<Char>* copy_dyn_list =
    new DoubleLinkedList<Char>(*def_dyn_list);
  
  // the two constructed lists should have the same items in their nodes now
  //
  if (def_dyn_list->ne(copy_list)) {
    return Error::handle(name(), L"copy constructor", Error::TEST, __FILE__,
			 __LINE__);
  }
  
  // see if we can dynamically delete
  //
  delete def_dyn_list;
  delete copy_dyn_list;
  
  // when memory is USER-allocated
  //
  
  // check the constructors for allocating on the stack
  //
  DoubleLinkedList<Char> def_list_2;
  def_list_2.setAllocationMode(DstrBase::USER);
  def_list_2.insertFirst(items[0]);
  def_list_2.insert(items[1]);
  def_list_2.insertLast(items[2]);
  
  DoubleLinkedList<Char> copy_list_2(def_list_2);
  
  // the two constructed lists should have the same items in the nodes now
  //
  if (def_list_2.ne(copy_list_2)) {
    return Error::handle(name(), L"copy constructor", Error::TEST, __FILE__,
			 __LINE__);
  }

  if (def_list_2.getAllocationMode() != copy_list_2.getAllocationMode()) {
    return Error::handle(name(), L"copy constructor", Error::TEST, __FILE__, __LINE__);
  }
  
  // check the constructors and destructors for allocating on the dynamic
  // memory heap
  //
  DoubleLinkedList<Char>* def_dyn_list_2 =
    new DoubleLinkedList<Char>(DstrBase::USER);
  
  def_dyn_list_2->insertFirst(items[0]);
  def_dyn_list_2->insert(items[1]);
  def_dyn_list_2->insertLast(items[2]);
  
  DoubleLinkedList<Char>* copy_dyn_list_2 =
    new DoubleLinkedList<Char>(*def_dyn_list_2);
  
  // the two constructed lists should have the same items in their nodes now
  //
  if (def_dyn_list_2->ne(copy_list_2)) {
    return Error::handle(name(), L"copy constructor", Error::TEST, __FILE__,
			 __LINE__);
  }
  
  // see if we can dynamically delete
  //
  delete def_dyn_list_2;
  delete copy_dyn_list_2;
  
  // test large allocation construction and deletion
  //
  if (level_a >= Integral::ALL) {
    
    // output an informative message
    //
    Console::put(L"\ntesting large chunk memory allocation and deletion:\n");
    
    // set the memory to a strange block size so we can hopefully catch any
    // frame overrun errors
    //
    DoubleLinkedList<Char>::setGrowSize((int32)731);
    
    // loop for a large number of times creating and deleting a large number
    // of lists at each loop
    //
    for (int32 j = 1; j <= 10; j++) {
      DoubleLinkedList<Char>** system_lists =
	new DoubleLinkedList<Char>*[j * 100];
      DoubleLinkedList<Char>** lists =
	new DoubleLinkedList<Char>*[j * 100];
      
      // create the items
      //
      for (int32 i = 0; i < j * 100; i++) {
	system_lists[i] =  new DoubleLinkedList<Char>(DstrBase::USER);
	lists[i] =  new DoubleLinkedList<Char>();
      }
      
      // delete lists
      //
      for (int32 i = (j * 100) - 1; i >= 0; i--) {
	delete system_lists[i];
	delete lists[i];
      }
      
      // clean up memory
      //
      delete [] system_lists;
      delete [] lists;
    }

    // perform the same test using the new[] and delete [] operators
    //
    for (int32 j = 1; j <= 10; j++) {
      
      // allocate a large number of nodes
      //
      DoubleLinkedList<TObject>* system_lists =
	new DoubleLinkedList<TObject>[j * 100];
      //      DoubleLinkedList<TObject>* lists =
      //	new DoubleLinkedList<TObject>[j * 100](DstrBase::USER);

      // clean up memory
      //
      delete [] system_lists;
      //      delete [] lists;
    }
  }
  
  // test assign methods
  //  
  DoubleLinkedList<Char> tmp_list;         
  DoubleLinkedList<Char>* tmp_dyn_list = new DoubleLinkedList<Char>();

  DoubleLinkedList<Char> tmp_list_1(DstrBase::USER); 
  DoubleLinkedList<Char>* tmp_dyn_list_1 = new DoubleLinkedList<Char>(DstrBase::USER);

  Char* item_ptr = (Char*)NULL;

  // insert an item into the list
  //
  tmp_list.insert(items[0]);
  tmp_list_1.insert(items[0]);
  
  // try the list assign method
  //
  tmp_dyn_list->assign(tmp_list);
  tmp_dyn_list_1->assign(tmp_list_1);
  
  if (tmp_dyn_list->ne(tmp_list) || tmp_dyn_list->ne(tmp_list_1)) {
    return Error::handle(name(), L"list assign", Error::TEST, __FILE__,
			 __LINE__);
  }
  
  if (tmp_dyn_list_1->ne(tmp_list) || tmp_dyn_list_1->ne(tmp_list_1)) {
    return Error::handle(name(), L"list assign", Error::TEST, __FILE__,
			 __LINE__);
  }
  
  // clean up
  //
  delete tmp_dyn_list;
  delete tmp_dyn_list_1;
  
  // testing i/o methods
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
  
  // prepare items for the lists
  //
  Char** write_chars = new Char*[5];
  String** write_strings = new String*[5];
  
  unichar tmp_char = L'a';
  
  for (int32 j = 0; j < 5; j++) {
    write_chars[j] = new Char(tmp_char);
    write_strings[j] = new String();
    tmp_char++;
  }
  
  write_strings[0]->assign(L"this ");
  write_strings[1]->assign(L"is");
  write_strings[2]->assign(L"a");
  write_strings[3]->assign(L"DoubleLinkedList");
  write_strings[4]->assign(L"String");
  
  // create lists to write
  //
  DoubleLinkedList<Char> write_null_list;
  DoubleLinkedList<Char> write_char_list(DstrBase::USER);

  write_char_list.insert(write_chars[0]);
  
  DoubleLinkedList<String> write_str_list(DstrBase::USER);

  for (int32 i = 0; i < 5; i++) {
    write_str_list.insert(write_strings[i]);
  }
  
  DoubleLinkedList< DoubleLinkedList<Char> >
    write_char_list_list(DstrBase::USER);
  DoubleLinkedList< DoubleLinkedList< DoubleLinkedList<Char> > >
    write_char_lll(DstrBase::USER);
  
  // create objects for reading in, all read lists are SYSTEM-allocated
  //
  DoubleLinkedList<Char> read_null_list_text;
  DoubleLinkedList<Char> read_null_list_bin;
  DoubleLinkedList<Char> read_char_list_text;
  DoubleLinkedList<Char> read_char_list_bin;
  DoubleLinkedList<String> read_str_list_text;
  DoubleLinkedList<String> read_str_list_bin;
  
  DoubleLinkedList< DoubleLinkedList<Char> > read_char_list_list_bin;
  DoubleLinkedList< DoubleLinkedList<Char> > read_char_list_list_text;
  
  DoubleLinkedList< DoubleLinkedList< DoubleLinkedList<Char> > >
    read_char_lll_bin, read_char_lll_text;
  
  int32 s1 = 3;
  int32 s2 = 5;
  
  // create items for writing
  //
  DoubleLinkedList< DoubleLinkedList<Char> >* wc_ll_0 =
    new DoubleLinkedList< DoubleLinkedList<Char> >(DstrBase::USER);
  DoubleLinkedList< DoubleLinkedList<Char> >* wc_ll_1 =
    new DoubleLinkedList< DoubleLinkedList<Char> >(DstrBase::USER);
  
  // write_char_list_list is in USER mode, each sub-list
  // is in USER mode.
  //
  for (int32 i = 0; i < s1; i++) {
    
    DoubleLinkedList<Char>* temp = new DoubleLinkedList<Char>(DstrBase::USER);
    DoubleLinkedList<Char>* t1 = new DoubleLinkedList<Char>(DstrBase::USER);
    DoubleLinkedList<Char>* t2 = new DoubleLinkedList<Char>(DstrBase::USER);
    
    for (int32 j = 0; j < s2; j++) {
      Char* c1 = new Char();
      Char* c2 = new Char();
      Char* c3 = new Char();
      c1->assign((unichar)(i * (s2+1) + j + (int)'A'));
      c2->assign((unichar)(i * (s2+1) + j + (int)'A'));
      c3->assign((unichar)(i * (s2+1) + j + (int)'a'));
      temp->insert(c1);
      t1->insert(c2);
      t2->insert(c3);
    }
    
    write_char_list_list.insert(temp);
    
    wc_ll_0->insert(t1);
    wc_ll_1->insert(t2);
  }
  
  // 10 channel vector data
  //
  s1 = 3;
  s2 = 20;
  
  DoubleLinkedList<VectorLong> write_signal_data(DstrBase::USER);
  DoubleLinkedList<VectorLong> read_signal_data_text;
  DoubleLinkedList<VectorLong> read_signal_data_bin;
  
  for (int32 i = 0; i < s1; i++) {
    
    VectorLong* ptr = new VectorLong(s2);
    ptr->setLength(s2);
    
    for (int32 j = 0; j < s2; j++) {
      (*ptr)(j) = i * 1000 + j * 3 + 7;
    }
    write_signal_data.insert(ptr);
  }
  
  write_char_lll.insert(wc_ll_0);
  write_char_lll.insert(wc_ll_1);
  
  // print some lists out
  //
  if (level_a >= Integral::ALL) {
    write_char_list_list.debug(L"write list<list<Char>>");
    write_signal_data.debug(L"write list<VectorLong>");
  }
  
  // write the values
  //
  write_null_list.write(text_file, (int32)11);
  write_null_list.write(bin_file, (int32)11);

  write_char_list.write(text_file, (int32)0);
  write_char_list.write(bin_file, (int32)0);  
  
  write_str_list.write(text_file, (int32)0);
  write_str_list.write(bin_file, (int32)0); 
  
  write_char_list_list.write(text_file, (int32)0);
  write_char_list_list.write(bin_file, (int32)0);  
  
  write_char_lll.write(text_file, (int32)0);
  write_char_lll.write(bin_file, (int32)0);  
  
  write_signal_data.write(text_file, (int32)0);
  write_signal_data.write(bin_file, (int32)0);  
  
  // close the files
  //
  text_file.close();
  bin_file.close();
  
  // open the files in read mode
  //
  text_file.open(text_filename);
  bin_file.open(bin_filename);
  
  // read in the lists and test for equivalence
  // if there is error, print out the lists
  //
  if (!read_null_list_text.read(text_file, (int32)11) ||
      (read_null_list_text.ne(write_null_list))) {
    read_null_list_text.debug(L"read_null_list_text");
    return Error::handle(name(), L"read null text", Error::TEST, __FILE__,
			 __LINE__);
  }
  
  if (!read_null_list_bin.read(bin_file, (int32)11) ||
      (read_null_list_bin.ne(write_null_list))) {
    read_null_list_bin.debug(L"read_null_list_bin");
    return Error::handle(name(), L"read null bin", Error::TEST, __FILE__,
			 __LINE__);
  }
  
  if (!read_char_list_text.read(text_file, (int32)0) ||
      (read_char_list_text.ne(write_char_list))) {

    read_char_list_text.debug(L"read_char_list_text");
    return Error::handle(name(), L"read char text", Error::TEST, __FILE__,
			 __LINE__);
  }

  if (!read_char_list_bin.read(bin_file, (int32)0) ||
      (read_char_list_bin.ne(write_char_list))) {
    read_char_list_bin.debug(L"read_char_list_bin");
    return Error::handle(name(), L"write char bin", Error::TEST, __FILE__,
			 __LINE__);
  }
  
  if (!read_str_list_text.read(text_file, (int32)0) ||
      (read_str_list_text.ne(write_str_list))) {
    read_str_list_text.debug(L"read_str_list_text");
    return Error::handle(name(), L"read str text", Error::TEST, __FILE__, 
			 __LINE__);
  }
  
  if (!read_str_list_bin.read(bin_file, (int32)0) ||
      (read_str_list_bin.ne(write_str_list))) {
    read_str_list_bin.debug(L"read_str_list_bin");
    return Error::handle(name(), L"write str bin", Error::TEST, __FILE__,
			 __LINE__);
  }
  
  if (!read_char_list_list_text.read(text_file, (int32)0) ||
      (read_char_list_list_text.ne(write_char_list_list))) {
    read_char_list_list_text.debug(L"read_char_list_list_text");
    return Error::handle(name(), L"read chr chr text", Error::TEST, __FILE__, 
			 __LINE__);
  }

  if (!read_char_list_list_bin.read(bin_file, (int32)0) ||
      (read_char_list_list_bin.ne(write_char_list_list))) {
    read_char_list_list_bin.debug(L"read_char_list_list_bin");
    return Error::handle(name(), L"read chr chr bin", Error::TEST, __FILE__, 
			 __LINE__);
  }
  
  if (!read_char_lll_text.read(text_file, (int32)0) ||
      (read_char_lll_text.ne(write_char_lll))) {
    read_char_lll_text.debug(L"read_char_lll_text");
    return Error::handle(name(), L"read chr chr chr text", Error::TEST,
			 __FILE__, __LINE__);
  }
  
  if (!read_char_lll_bin.read(bin_file, (int32)0) ||
      (read_char_lll_bin.ne(write_char_lll))) {
    read_char_lll_bin.debug(L"read_char_lll_bin");
    return Error::handle(name(), L"read chr chr bin", Error::TEST, __FILE__, 
			 __LINE__);
  }

  if (!read_signal_data_text.read(text_file, (int32)0) ||
      (read_signal_data_text.ne(write_signal_data))) {
    read_signal_data_text.debug(L"read_signal_data_text");
    return Error::handle(name(), L"read chr chr text", Error::TEST, __FILE__, 
			 __LINE__);
  }
  
  if (!read_signal_data_bin.read(bin_file, (int32)0) ||
      (read_signal_data_bin.ne(write_signal_data))) {
    read_signal_data_bin.debug(L"read_signal_data_bin");
    return Error::handle(name(), L"read chr chr bin", Error::TEST, __FILE__, 
			 __LINE__);
  }

  // close and delete the temporary files
  //
  text_file.close();
  bin_file.close();
  File::remove(text_filename);
  File::remove(bin_filename);
  
  // clean the memory that was created by the DoubleLinkedList read and write
  //
  read_char_list_text.clear();
  read_char_list_bin.clear();
  read_str_list_text.clear();
  read_str_list_bin.clear();

  read_char_list_list_bin.clear();
  read_char_list_list_text.clear();
  read_char_lll_text.clear();
  read_char_lll_bin.clear();
  read_signal_data_bin.clear();
  read_signal_data_text.clear();
  
  write_char_list_list.clear(Integral::FREE);
  write_char_lll.clear(Integral::FREE);
  write_signal_data.clear(Integral::FREE);
  
  for (int32 i = 0; i < 5; i++) {
    delete write_chars[i];
    delete write_strings[i];
  }
  delete [] write_chars;
  delete [] write_strings;
  
  // testing equality methods
  //
  DoubleLinkedList<Char>* char_list = new DoubleLinkedList<Char>;
  
  Char* characters = new Char[500];
  unichar temp_char = L'a';
  
  // initialize the characters and store them in the lists
  //
  for (int32 i = 0; i < 500; i++) {
    characters[i].assign(temp_char);
    
    // insert the character to the list
    //
    char_list->insert(&characters[i]);
    
    // increment the character value
    //
    temp_char++;
  }
  
  // SYSTEM-allocated
  //
  DoubleLinkedList<Char>* char_copy_list_1 = new DoubleLinkedList<Char>();
  char_copy_list_1->assign(*char_list);
  
  // USER-allocated
  //
  DoubleLinkedList<Char>* char_copy_list_2 =
    new DoubleLinkedList<Char>(DstrBase::USER);
  char_copy_list_2->assign(*char_list);
  
  // char_copy_list_1 and char_copy_list_2 should be the same as the
  // char_list
  //
  if (!char_list->eq(*char_copy_list_1)) {
    return Error::handle(name(), L"eq", Error::TEST, __FILE__, __LINE__);
  }
  
  if (char_list->ne(*char_copy_list_1)) {
    return Error::handle(name(), L"ne", Error::TEST, __FILE__, __LINE__);
  }
  
  if (!char_list->eq(*char_copy_list_2)) {
    return Error::handle(name(), L"eq", Error::TEST, __FILE__, __LINE__);
  }
  
  if (char_list->ne(*char_copy_list_2)) {
    return Error::handle(name(), L"ne", Error::TEST, __FILE__, __LINE__);
  }
  
  // clean up
  //
  delete char_list;
  delete char_copy_list_1;
  delete char_copy_list_2;
  delete [] characters;

  // reset indentation
  //
  if (level_a > Integral::NONE) {
    Console::decreaseIndention();
  }

  // --------------------------------------------------------------------
  //
  // 2. class-specific public methods:
  //     positioning methods
  //
  // --------------------------------------------------------------------

  // set indentation
  //
  if (level_a > Integral::NONE) {
    Console::put(L"testing class-specific public methods: positioning methods...\n");
    Console::increaseIndention(); 
  }

  // test positioning, node and data accessing methods
  //
  DoubleLinkedList<Char> tmp_list_2;
  
  tmp_list_2.insert(items[0]);
  tmp_list_2.insert(items[1]);
  tmp_list_2.insert(items[2]);
  tmp_list_2.insert(items[3]);
  
  // goto the first node
  //
  if (!tmp_list_2.gotoFirst()) {
    return Error::handle(name(), L"gotoFirst", Error::TEST, __FILE__,
			 __LINE__);
  }

  // make sure this is the first node
  //
  if (!tmp_list_2.isFirst()) {
    return Error::handle(name(), L"isFirst", Error::TEST, __FILE__, __LINE__);
  }

  // make sure this is not the last node
  //
  if (tmp_list_2.isLast()) {
    return Error::handle(name(), L"isLast", Error::TEST, __FILE__, __LINE__);
  }

  if (tmp_list_2.first_d->getItem()->ne(*items[0]) ||
      tmp_list_2.curr_d->getItem()->ne(*items[0])) {
    return Error::handle(name(), L"gotoFirst", Error::TEST, __FILE__,
			 __LINE__);
  }

  // goto the next node
  //
  if (!tmp_list_2.gotoNext()) {
    return Error::handle(name(), L"gotoNext", Error::TEST, __FILE__,
			 __LINE__);
  }
  
  if (tmp_list_2.curr_d->getItem()->ne(*items[1])) {
    return Error::handle(name(), L"gotoNext", Error::TEST, __FILE__,
			 __LINE__);
  }
  
  // is mark_d set?
  //
  if (tmp_list_2.markIsSet()) {
    return Error::handle(name(), L"markIsSet", Error::TEST, __FILE__,
			 __LINE__);
  }

  // reset indentation
  //
  if (level_a > Integral::NONE) {
    Console::decreaseIndention();
  }
  
  //--------------------------------------------------------------------------
  //
  // 3. class-specific public methods:
  //     marking methods
  //
  //--------------------------------------------------------------------------

  // set indentation
  //
  if (level_a > Integral::NONE) {
    Console::put(L"testing class-specific public methods: marking methods...\n");
    Console::increaseIndention();
  }
  
  // set a mark here - the second node 
  //
  tmp_list_2.setMark();

  
  if (tmp_list_2.mark_d->getItem()->ne(*items[1])) {
    return Error::handle(name(), L"setMark", Error::TEST, __FILE__,
			 __LINE__);
  }
  
  
  if (!tmp_list_2.isMarkedElement()) {
    return Error::handle(name(), L"isMarkedElement", Error::TEST, __FILE__,
			 __LINE__);
  }
  
  if (!tmp_list_2.markIsSet()) {
    return Error::handle(name(), L"markIsSet", Error::TEST, __FILE__,
			 __LINE__);
  }
  
  // goto the last node
  //
  if (!tmp_list_2.gotoLast()) {
    return Error::handle(name(), L"gotoLast", Error::TEST, __FILE__,
			 __LINE__);
  }

  // make sure this is not the first node
  //
  if (tmp_list_2.isFirst()) {
    return Error::handle(name(), L"isFirst", Error::TEST, __FILE__, __LINE__);
  }

  // make sure this is the last node
  //
  if (!tmp_list_2.isLast()) {
    return Error::handle(name(), L"isLast", Error::TEST, __FILE__, __LINE__);
  }


  if (tmp_list_2.last_d->getItem()->ne(*items[3]) ||
      tmp_list_2.curr_d->getItem()->ne(*items[3])) {
    return Error::handle(name(), L"gotoLast", Error::TEST, __FILE__,
			 __LINE__);
  }
  
  if (tmp_list_2.isMarkedElement()) {
    return Error::handle(name(), L"isMarkedElement", Error::TEST, __FILE__,
			 __LINE__);
  }
  
  // when there is no next node, gotoNext should stay at the current position
  // and return false
  //
  tmp_list_2.gotoLast();
  if (tmp_list_2.gotoNext()) {
    return Error::handle(name(), L"gotoNext", Error::TEST, __FILE__,
			 __LINE__);
  }
    
  if (tmp_list_2.curr_d != tmp_list_2.last_d) {
    return Error::handle(name(), L"gotoNext", Error::TEST, __FILE__,
			 __LINE__);
  }
  
  // goto the previous node 
  //
  if (!tmp_list_2.gotoPrev()) {
    return Error::handle(name(), L"gotoPrev", Error::TEST, __FILE__,
			 __LINE__);
  }
  
  if (tmp_list_2.curr_d->getItem()->ne(*items[2])) {
    return Error::handle(name(), L"gotoPrev", Error::TEST, __FILE__,
			 __LINE__);
  }
  
  // when there is no previous node, gotoPrev should stay at the current
  // position and return false
  //
  tmp_list_2.gotoFirst();
  
  if (tmp_list_2.gotoPrev()) {
    return Error::handle(name(), L"gotoPrev", Error::TEST, __FILE__,
			 __LINE__);
  }
  
  if (tmp_list_2.curr_d != tmp_list_2.first_d) {
    return Error::handle(name(), L"gotoPrev", Error::TEST, __FILE__,
			 __LINE__);
  }
  
  // goto the marked node 
  //
  if (!tmp_list_2.gotoMark()) {
    return Error::handle(name(), L"gotoMark", Error::TEST, __FILE__,
			 __LINE__);
  }
  
  if (tmp_list_2.curr_d->getItem()->ne(*items[1]) ||
      tmp_list_2.mark_d->getItem()->ne(*items[1])) {
    return Error::handle(name(), L"gotoMark", Error::TEST, __FILE__,
			 __LINE__);
  }
  
  // reset indentation
  //
  if (level_a > Integral::NONE) {
    Console::decreaseIndention();
  }

  //--------------------------------------------------------------------------
  //
  // 4. class-specific public methods:
  //     element access methods
  //
  //--------------------------------------------------------------------------

  // set indentation
  //
  if (level_a > Integral::NONE) {
    Console::put(L"testing class-specific public methods: element access methods...\n");
    Console::increaseIndention();
  }
    
  // get the element of the current node
  //
  if (tmp_list_2.getCurr()->ne(*items[1])) {
    return Error::handle(name(), L"getCurr", Error::TEST, __FILE__,
			 __LINE__);
  }


  for (int32 i = 0; i < 4; i++) {
    if (tmp_list_2(i).ne(*items[i])) {
      return Error::handle(name(), L"operator", Error::TEST,
			   __FILE__, __LINE__);
    }
  }

  for (int32 i = 0; i < 4; i++) {
    if (!tmp_list_2(i).assign(*items[i + 1])) {
      return Error::handle(name(), L"operator", Error::TEST,
			   __FILE__, __LINE__);
    }
  }

  for (int32 i = 0; i < 4; i++) {
    if (tmp_list_2(i).ne(*items[i + 1])) {
      return Error::handle(name(), L"operator", Error::TEST,
			   __FILE__, __LINE__);
    }
  }

  for (int32 i = 0; i < 4; i++) {
    if (!tmp_list_2(i).assign(*items[i])) {
      return Error::handle(name(), L"operator", Error::TEST,
			   __FILE__, __LINE__);
    }
  }

  // test getPosition
  //
  if (tmp_list_2.getPosition() != 1) {
    return Error::handle(name(), L"getPosition", Error::TEST, __FILE__,
			 __LINE__);
  }

  // test gotoPosition for all cases
  //
  for (int32 i = 0; i < 4; i++) {
    tmp_list_2.gotoPosition(i);
    if (tmp_list_2.getPosition() != i) {
      return Error::handle(name(), L"getPosition", Error::TEST, __FILE__,
			   __LINE__);
    }
  }

  // test the contains method
  //
  tmp_list_2.gotoLast();
  for (int32 i = 0; i < 4; i++) {
    if (!tmp_list_2.contains(items[i])) {
      return Error::handle(name(), L"contains", Error::TEST, __FILE__,
			   __LINE__);
    }
  }

  tmp_list_2.gotoLast();
  for (int32 i = 0; i < 4; i++) {
    if (!tmp_list_2.find(items[i])) {
      return Error::handle(name(), L"find", Error::TEST, __FILE__,
			   __LINE__);
    }
    if (tmp_list_2.getPosition() != i) {
      return Error::handle(name(), L"getPosition", Error::TEST, __FILE__,
			   __LINE__);
    }
  }

  // restore the position
  //
  tmp_list_2.gotoPosition(1);

  // set the element of the current node
  //
  tmp_list_2.remove();
  tmp_list_2.gotoPrev();
  tmp_list_2.insert(items[4]);
  tmp_list_2.setMark();
  
  item_ptr = tmp_list_2.getCurr();
  if ((item_ptr == (Char*)NULL) || item_ptr->ne(*items[4])) {
    return Error::handle(name(), L"getCurr", Error::TEST, __FILE__,
			 __LINE__);
  }
  
  // get the item of the first node
  //  note now the contents of the list are 0423
  //
  item_ptr = tmp_list_2.getFirst();
  if ((item_ptr == (Char*)NULL) || item_ptr->ne(*items[0])) {
    return Error::handle(name(), L"getFirst", Error::TEST, __FILE__,
			 __LINE__);
  }
  
  // get the item of the last node
  //
  item_ptr = tmp_list_2.getLast();
  if ((item_ptr == (Char*)NULL) || item_ptr->ne(*items[3])) {
    return Error::handle(name(), L"getLast", Error::TEST, __FILE__,
			 __LINE__);
  }
  
  // get the item of the marked node, which is at the third node
  //  
  item_ptr = tmp_list_2.getMark();
  if ((item_ptr == (Char*)NULL) || item_ptr->ne(*items[4])) {
    return Error::handle(name(), L"getMark", Error::TEST, __FILE__,
			 __LINE__);
  }
  
  // get the item of the previous and next node 
  //  
  item_ptr = tmp_list_2.getPrev();
  if ((item_ptr == (Char*)NULL) || item_ptr->ne(*items[0])) {
    return Error::handle(name(), L"getPrev", Error::TEST, __FILE__,
			 __LINE__);
  }
  
  item_ptr = tmp_list_2.getNext();
  if ((item_ptr == (Char*)NULL) || item_ptr->ne(*items[2])) {
    return Error::handle(name(), L"getNext", Error::TEST, __FILE__,
			 __LINE__);
  }
  
  // when there is no previous node, getPrev should return false
  //
  tmp_list_2.gotoFirst();
  if (tmp_list_2.getPrev() != (Char*)NULL) {
    return Error::handle(name(), L"getPrev", Error::TEST, __FILE__,
			 __LINE__);
  }
  
  // when there is no next node, getNext should return false
  //
  tmp_list_2.gotoLast();
  if (tmp_list_2.getNext() != (Char*)NULL) {
    return Error::handle(name(), L"getNext", Error::TEST, __FILE__,
			 __LINE__);
  }
  
  // clear mark
  //
  tmp_list_2.clearMark();
  
  if (tmp_list_2.gotoMark()) {
    return Error::handle(name(), L"clearMark", Error::TEST, __FILE__,
			 __LINE__);
  }

  // reset indentation
  //
  if (level_a > Integral::NONE) {
    Console::decreaseIndention();
  }
  
  //--------------------------------------------------------------------------
  //
  // 5. class-specific public methods:
  //     insert and remove methods
  //
  //--------------------------------------------------------------------------

  // set indentation
  //
  if (level_a > Integral::NONE) {
    Console::put(L"testing class-specific public methods: insert and remove methods...\n");
    Console::increaseIndention();
  }

  // test the insert last method on an empty list in system mode
  //
  DoubleLinkedList<Char> tmplist_test_0;
  tmplist_test_0.insertLast(items[0]);
  DoubleLinkedList<Char>* tmplist_test_ptr_0 = new DoubleLinkedList<Char>();  
  tmplist_test_ptr_0->insertLast(items[0]);
  delete tmplist_test_ptr_0;
    
  // test the insert last method on an empty list in user mode
  //  
  DoubleLinkedList<Char> tmplist_test_1(DstrBase::USER);
  tmplist_test_1.insertLast(items[0]);
  DoubleLinkedList<Char>* tmplist_test_ptr_1 =
    new DoubleLinkedList<Char>(DstrBase::USER);  
  tmplist_test_ptr_1->insertLast(items[0]);
  delete tmplist_test_ptr_1;
  
  // testing item manipulation methods
  //
  DoubleLinkedList<Char>* list_ptr_0 =
    new DoubleLinkedList<Char>(DstrBase::USER);
  DoubleLinkedList<Char>* list_ptr_1 =
    new DoubleLinkedList<Char>(DstrBase::USER);
  
  // SYSTEM-allocated
  //
  DoubleLinkedList<Char>* list_ptr_2 = new DoubleLinkedList<Char>;
  
  // insertFirst
  //  note the numbers in the right-hand comments are indicating the contents
  //  of the current list by using their indices in items[]
  //
  // insert a single item to the beginning of the list
  //
  list_ptr_0->insertFirst(items[0]);              // 0
  list_ptr_0->insertFirst(items[1]);              // 1 0
  
  // we do the same operation on list_ptr_2 as on the list_ptr_0
  //
  list_ptr_2->insertFirst(items[0]);              // 0
  list_ptr_2->insertFirst(items[1]);              // 1 0

  
  if ((list_ptr_0->first_d->getItem()->ne(*items[1])) ||
      (list_ptr_0->length() != 2)) {
    return Error::handle(name(), L"insertFirst (first_d)", Error::TEST,
			 __FILE__, __LINE__);
  }
  
  if ((list_ptr_2->first_d->getItem()->ne(*items[1])) ||
      (list_ptr_2->length() != 2)) {
    return Error::handle(name(), L"insertFirst (first_d)", Error::TEST,
			 __FILE__, __LINE__);
  }
  
  // curr_d should be the same as the first_d now
  //
  if (list_ptr_0->curr_d != list_ptr_0->first_d) {
    return Error::handle(name(), L"insertFirst (curr_d)", Error::TEST,
			 __FILE__, __LINE__);
  }
  
  if (list_ptr_2->curr_d != list_ptr_2->first_d) {
    return Error::handle(name(), L"insertFirst (curr_d)", Error::TEST,
			 __FILE__, __LINE__);
  }
  
  // last_d should contain items[0] now
  //
  if (list_ptr_0->last_d->getItem()->ne(*items[0])) {
    return Error::handle(name(), L"insertFirst (last_d)", Error::TEST,
			 __FILE__, __LINE__);
  }
  
  if (list_ptr_2->last_d->getItem()->ne(*items[0])) {
    return Error::handle(name(), L"insertFirst (last_d)", Error::TEST,
			 __FILE__, __LINE__);
  }
  
  // insert an array of items to the beginning of the list
  //
  for (int32 i = 1; i >= 0; i--) {
    list_ptr_0->insertFirst(items[i]);        // 01 10
    list_ptr_2->insertFirst(items[i]);        // 01 10
  }
    
  if ((list_ptr_0->first_d->getItem()->ne(*items[0])) ||
      (list_ptr_0->length() != 4)) {
    return Error::handle(name(), L"insertFirst (first_d)", Error::TEST,
			 __FILE__, __LINE__);
  }
  
  if ((list_ptr_2->first_d->getItem()->ne(*items[0])) ||
      (list_ptr_2->length() != 4)) {
    return Error::handle(name(), L"insertFirst (first_d)", Error::TEST,
			 __FILE__, __LINE__);
  }
  
  // curr_d should be the same as the first_d now
  //
  if (list_ptr_0->curr_d != list_ptr_0->first_d) {
    return Error::handle(name(), L"insertFirst (curr_d)", Error::TEST,
			 __FILE__, __LINE__);
  }
  
  if (list_ptr_2->curr_d != list_ptr_2->first_d) {
    return Error::handle(name(), L"insertFirst (curr_d)", Error::TEST,
			 __FILE__, __LINE__);
  }
  
  
  // move the current node pointer to the end of the list
  //
  list_ptr_0->gotoLast();
  list_ptr_2->gotoLast();
  
  // insert a single item to the list (the curr_d is at the end of the list now) 
  //
  list_ptr_0->insert(items[3]);                      // 0110 3
  list_ptr_2->insert(items[3]);                      // 0110 3
  
  
  if ((list_ptr_0->curr_d->getItem()->ne(*items[3])) ||
      (list_ptr_0->length() != 5)) {
    return Error::handle(name(), L"insert (curr_d)", Error::TEST, __FILE__,
			 __LINE__);
  }
  
  if ((list_ptr_2->curr_d->getItem()->ne(*items[3])) ||
      (list_ptr_2->length() != 5)) {
    return Error::handle(name(), L"insert (curr_d)", Error::TEST, __FILE__,
			 __LINE__);
  }
  
  // the curr_d should be the same as the last_d now
  //
  if (list_ptr_0->curr_d != list_ptr_0->last_d) {
    return Error::handle(name(), L"insert (last_d)", Error::TEST, __FILE__,
			 __LINE__);
  }
  
  if (list_ptr_2->curr_d != list_ptr_2->last_d) {
    return Error::handle(name(), L"insert (last_d)", Error::TEST, __FILE__,
			 __LINE__);
  }
  
  // insert an array of items to the list (the curr_d is at the end of the
  // list now) 
  //
  for (int32 i = 0; i < 3; i++) {
    list_ptr_0->insert(items[i]);                // 01103 012
    list_ptr_2->insert(items[i]);                // 01103 012
  }
  
  if ((list_ptr_0->curr_d->getItem()->ne(*items[2])) ||
      (list_ptr_0->length() != 8)) {
    return Error::handle(name(), L"insert (curr_d)", Error::TEST, __FILE__,
			 __LINE__);
  }
  
  if ((list_ptr_2->curr_d->getItem()->ne(*items[2])) ||
      (list_ptr_2->length() != 8)) {
    return Error::handle(name(), L"insert (curr_d)", Error::TEST, __FILE__,
			 __LINE__);
  }
  
  // the curr_d should be the same as the last_d now
  //
  if (list_ptr_0->curr_d != list_ptr_0->last_d) {
    return Error::handle(name(), L"insert (last_d)", Error::TEST, __FILE__,
			 __LINE__);
  }
  
  if (list_ptr_2->curr_d != list_ptr_2->last_d) {
    return Error::handle(name(), L"insert (last_d)", Error::TEST, __FILE__,
			 __LINE__);
  }
  
  // move the current node pointer to somewhere inside the list
  //
  list_ptr_0->gotoPrev();
  list_ptr_2->gotoPrev();
  
  // insert a single item to the middle of the list
  //
  list_ptr_0->insert(items[3]);                      // 0110301 3 2
  list_ptr_2->insert(items[3]);                      // 0110301 3 2
  
  if ((list_ptr_0->curr_d->getItem()->ne(*items[3])) ||
      (list_ptr_0->length() != 9)) {
    return Error::handle(name(), L"insert (curr_d)", Error::TEST, __FILE__,
			 __LINE__);
  }
  
  if ((list_ptr_2->getCurr()->ne(*items[3])) ||
      (list_ptr_2->length() != 9)) {
    return Error::handle(name(), L"insert (curr_d)", Error::TEST, __FILE__,
			 __LINE__);
  }
  
  if (list_ptr_0->getNext()->ne(*items[2])) {
    return Error::handle(name(), L"insert (curr_d)", Error::TEST, __FILE__,
			 __LINE__);
  }
  
  if (list_ptr_2->getNext()->ne(*items[2])) {
    return Error::handle(name(), L"insert (curr_d)", Error::TEST, __FILE__,
			 __LINE__);
  }
  
  // insert an array of items to the middle of the list
  //
  for (int32 i = 0; i < 2; i++) {
    list_ptr_0->insert(items[i]);                       // 01103013 01 2
    list_ptr_2->insert(items[i]);                       // 01103013 01 2
  }
  
  if ((list_ptr_0->getCurr()->ne(*items[1])) ||
      (list_ptr_0->length() != 11)) {
    return Error::handle(name(), L"insert (curr_d)", Error::TEST, __FILE__,
			 __LINE__);
  }
  
  if ((list_ptr_2->getCurr()->ne(*items[1])) ||
      (list_ptr_2->length() != 11)) {
    return Error::handle(name(), L"insert (curr_d)", Error::TEST, __FILE__,
			 __LINE__);
  }
  
  if (list_ptr_0->getNext()->ne(*items[2])) {
    return Error::handle(name(), L"insert (curr_d)", Error::TEST, __FILE__,
			 __LINE__);
  }
  
  if (list_ptr_2->getNext()->ne(*items[2])) {
    return Error::handle(name(), L"insert (curr_d)", Error::TEST, __FILE__,
			 __LINE__);
  }
  
  // insert a single item to the end of the list
  // 
  list_ptr_0->insertLast(items[4]);                   // 01103013012 4
  list_ptr_2->insertLast(items[4]);                   // 01103013012 4
  
  if ((list_ptr_0->curr_d->getItem()->ne(*items[4])) ||
      (list_ptr_0->length() != 12)) {
    return Error::handle(name(), L"insert (curr_d)", Error::TEST, __FILE__,
			 __LINE__);
  }
  
  if ((list_ptr_2->curr_d->getItem()->ne(*items[4])) ||
      (list_ptr_2->length() != 12)) {
    return Error::handle(name(), L"insert (curr_d)", Error::TEST, __FILE__,
			 __LINE__);
  }
  
  if (list_ptr_0->curr_d != list_ptr_0->last_d) {
    return Error::handle(name(), L"insert (last_d)", Error::TEST, __FILE__,
			 __LINE__);
  }
  
  if (list_ptr_2->curr_d != list_ptr_2->last_d) {
    return Error::handle(name(), L"insert (last_d)", Error::TEST, __FILE__,
			 __LINE__);
  }
  
  // insert an array of items to the end of the list
  // 
  for (int32 i = 0; i < 3; i++) {
    list_ptr_0->insertLast(items[i]);           // 011030130124 012
    list_ptr_2->insertLast(items[i]);           // 011030130124 012
  }
  
  if ((list_ptr_0->curr_d->getItem()->ne(*items[2])) ||
      (list_ptr_0->length() != 15)) {
    return Error::handle(name(), L"insertLast (curr_d)", Error::TEST, __FILE__,
			 __LINE__);
  }
  
  if ((list_ptr_2->curr_d->getItem()->ne(*items[2])) ||
      (list_ptr_2->length() != 15)) {
    return Error::handle(name(), L"insertLast (curr_d)", Error::TEST, __FILE__,
			 __LINE__);
  }
  
  if (list_ptr_0->curr_d != list_ptr_0->last_d) {
    return Error::handle(name(), L"insert (last_d)", Error::TEST, __FILE__,
			 __LINE__);
  }
  
  if (list_ptr_2->curr_d != list_ptr_2->last_d) {
    return Error::handle(name(), L"insert (last_d)", Error::TEST, __FILE__,
			 __LINE__);
  }
  
  // prepare a sub list to insert into another list
  // and also test the insert method when curr_d is at the beginning of the list
  //
  list_ptr_1->insert(items[4]);                   // 4
  for (int32 i = 0; i < 4; i++) {
    list_ptr_1->insert(items[i]);             // 4 0123
  }
  
  list_ptr_1->gotoFirst();
  if (list_ptr_1->getFirst()->ne(*items[4]) ||
      list_ptr_1->getCurr()->ne(*items[4]) ||
      list_ptr_1->first_d->getItem()->ne(*items[4]) ||
      (list_ptr_1->length() != 5)) {
    return Error::handle(name(), L"insert (2nd)", Error::TEST, __FILE__,
			 __LINE__);
  }
  
  if (list_ptr_1->getNext()->ne(*items[0])) {
    return Error::handle(name(), L"insert (2nd)", Error::TEST, __FILE__,
			 __LINE__);
  }
  
  if (list_ptr_1->getLast()->ne(*items[3])) {
    return Error::handle(name(), L"insert (2nd)", Error::TEST, __FILE__,
			 __LINE__);
  }
  
  // mark a node
  //
  list_ptr_0->gotoFirst();                      // 0 11030130124012
  list_ptr_0->setMark();                        // ^   
  
  list_ptr_2->gotoFirst();                      // 0 11030130124012
  list_ptr_2->setMark();                        // ^   
  
  // insert a list into the beginning of another list
  //
  list_ptr_0->insertFirst(*list_ptr_1);           // 40123 011030130124012
  list_ptr_2->insertFirst(*list_ptr_1);           // 40123 011030130124012
  
  if (list_ptr_0->getFirst()->ne(*items[4]) ||
      (list_ptr_0->length() != 20)) {
    return Error::handle(name(), L"insertFirst(list)", Error::TEST, __FILE__,
			 __LINE__);
  }
  
  if (list_ptr_2->getFirst()->ne(*items[4]) ||
      (list_ptr_2->length() != 20)) {
    return Error::handle(name(), L"insertFirst(list)", Error::TEST, __FILE__,
			 __LINE__);
  }
  
  // go to the marked node position
  //
  list_ptr_0->gotoMark();
  list_ptr_2->gotoMark();
  
  if (list_ptr_0->getPrev()->ne(*items[3])) {
    return Error::handle(name(), L"insertFirst(list)", Error::TEST, __FILE__,
			 __LINE__);
  }
  
  if (list_ptr_2->getPrev()->ne(*items[3])) {
    return Error::handle(name(), L"insertFirst(list)", Error::TEST, __FILE__,
			 __LINE__);
  }
  
  // insert a list into the middle of another list
  //
  list_ptr_0->insert(*list_ptr_1);           // 401230 40123 11030130124012
  list_ptr_2->insert(*list_ptr_1);           // 401230 40123 11030130124012
  
  if ((list_ptr_0->getCurr()->ne(*items[3])) ||
      (list_ptr_0->length() != 25)) {
    return Error::handle(name(), L"insert(list)", Error::TEST, __FILE__,
			 __LINE__);
  }
  
  if ((list_ptr_2->getCurr()->ne(*items[3])) ||
      (list_ptr_2->length() != 25)) {
    return Error::handle(name(), L"insert(list)", Error::TEST, __FILE__,
			 __LINE__);
  }
  
  if (list_ptr_0->getNext()->ne(*items[1])) {
    return Error::handle(name(), L"insert(list)", Error::TEST, __FILE__,
			 __LINE__);
  }
  
  if (list_ptr_2->getNext()->ne(*items[1])) {
    return Error::handle(name(), L"insert(list)", Error::TEST, __FILE__,
			 __LINE__);
  }
  
  // insert a list into the end of another list
  //
  list_ptr_0->insertLast(*list_ptr_1);       // 4012304012311030130124012 40123
  list_ptr_2->insertLast(*list_ptr_1);       // 4012304012311030130124012 40123
  
  if ((list_ptr_0->getLast()->ne(*items[3])) ||
      (list_ptr_0->length() != 30)) {
    return Error::handle(name(), L"insertLast(list)", Error::TEST, __FILE__,
			 __LINE__);
  }
  
  if ((list_ptr_2->getLast()->ne(*items[3])) ||
      (list_ptr_2->length() != 30)) {
    return Error::handle(name(), L"insertLast(list)", Error::TEST, __FILE__,
			 __LINE__);
  }
  
  if (list_ptr_0->curr_d != list_ptr_0->last_d) {
    return Error::handle(name(), L"insertLast(list)", Error::TEST, __FILE__,
			 __LINE__);
  }
  
  if (list_ptr_2->curr_d != list_ptr_2->last_d) {
    return Error::handle(name(), L"insertLast(list)", Error::TEST, __FILE__,
			 __LINE__);
  }
  
  // test removeFirst
  //
  Char* tmp_item = (Char*)NULL;      // the pointer to the removed item
  
  list_ptr_0->gotoFirst();
  list_ptr_0->removeFirst(tmp_item);       // 01230401231103013012401240123
  
  if ((list_ptr_0->first_d != list_ptr_0->curr_d) ||
      (list_ptr_0->first_d->getItem()->ne(*items[0]))) {
    return Error::handle(name(), L"removeFirst", Error::TEST, __FILE__,
			 __LINE__);
  }
  
  if ((tmp_item->ne(*items[4])) || (list_ptr_0->length() != 29)) {
    return Error::handle(name(), L"removeFirst", Error::TEST, __FILE__,
			 __LINE__);
  }
  
  list_ptr_2->gotoFirst();
  list_ptr_2->removeFirst();              // 01230401231103013012401240123
  
  if ((list_ptr_2->first_d != list_ptr_2->curr_d) ||
      (list_ptr_2->length() != 29) ||
      (list_ptr_2->first_d->getItem()->ne(*items[0]))) {
    return Error::handle(name(), L"removeFirst", Error::TEST, __FILE__,
			 __LINE__);
  }
  
  // test remove when the current pointer is at the first position
  //
  list_ptr_0->gotoFirst();
  list_ptr_0->remove(tmp_item);           // 1230401231103013012401240123
  
  if (list_ptr_0->curr_d != list_ptr_0->first_d ||
      (list_ptr_0->curr_d->getItem()->ne(*items[1]))) {
    return Error::handle(name(), L"remove", Error::TEST, __FILE__, __LINE__);
  }
  
  if ((tmp_item->ne(*items[0])) || (list_ptr_0->length() != 28)) {
    return Error::handle(name(), L"remove (first)", Error::TEST, __FILE__,
			 __LINE__);
  }
  
  list_ptr_2->gotoFirst();
  list_ptr_2->remove();                  // 1230401231103013012401240123
  
  if (list_ptr_2->curr_d != list_ptr_2->first_d ||
      (list_ptr_2->length() != 28) ||
      (list_ptr_2->curr_d->getItem()->ne(*items[1]))) {
    return Error::handle(name(), L"remove", Error::TEST, __FILE__, __LINE__);
  }
  
  // move the current node pointer to somewhere inside the list
  //
  list_ptr_0->gotoNext();
  list_ptr_0->gotoNext();                  // 12 3 0401231103013012401240123
  
  list_ptr_2->gotoNext();
  list_ptr_2->gotoNext();                  // 12 3 0401231103013012401240123
  
  // remove when the current pointer is inside the list
  // (at the third position now)
  //
  list_ptr_0->remove(tmp_item);            // 12 0401231103013012401240123
  
  if ((tmp_item->ne(*items[3])) ||
      (list_ptr_0->curr_d->getItem()->ne(*items[0])) ||
      (list_ptr_0->length() != 27)) {
    return Error::handle(name(), L"remove (inside)", Error::TEST, __FILE__,
			 __LINE__);
  }
  
  list_ptr_2->remove();                   // 12 0401231103013012401240123
  
  if ((list_ptr_0->curr_d->getItem()->ne(*items[0])) ||
      (list_ptr_0->length() != 27)) {
    return Error::handle(name(), L"remove (inside)", Error::TEST, __FILE__,
			 __LINE__);
  }
  
  // go to the end of the list
  //
  list_ptr_0->gotoLast();
  list_ptr_2->gotoLast();
  
  // remove when the current pointer is at the end of the list
  //
  list_ptr_0->remove(tmp_item);            // 12040123110301301240124012
  
  if ((list_ptr_0->curr_d != list_ptr_0->last_d) ||
      (list_ptr_0->curr_d->getItem()->ne(*items[2]))) {
    return Error::handle(name(), L"remove (last)", Error::TEST, __FILE__,
			 __LINE__);
  }
  
  if ((tmp_item->ne(*items[3])) || (list_ptr_0->length() != 26)) {
    return Error::handle(name(), L"remove (last)", Error::TEST, __FILE__,
			 __LINE__);
  }
  
  list_ptr_2->remove();            // 12040123110301301240124012
  
  if ((list_ptr_2->curr_d != list_ptr_2->last_d) ||
      (list_ptr_2->length() != 26) ||
      (list_ptr_2->curr_d->getItem()->ne(*items[2]))) {
    return Error::handle(name(), L"remove (last)", Error::TEST, __FILE__,
			 __LINE__);
  }
  
  // test removeLast
  //
  list_ptr_0->removeLast(tmp_item);          // 1204012311030130124012401
  
  if ((list_ptr_0->curr_d != list_ptr_0->last_d) ||
      (list_ptr_0->curr_d->getItem()->ne(*items[1]))) {
    return Error::handle(name(), L"removeLast", Error::TEST, __FILE__,
			 __LINE__);
  }
  
  if ((tmp_item->ne(*items[2])) || (list_ptr_0->length() != 25)) {
    return Error::handle(name(), L"removeLast", Error::TEST, __FILE__,
			 __LINE__);
  }
  
  list_ptr_2->removeLast();          // 1204012311030130124012401
  
  if ((list_ptr_2->curr_d != list_ptr_2->last_d) ||
      (list_ptr_0->length() != 25) ||
      (list_ptr_2->curr_d->getItem()->ne(*items[1]))) {
    return Error::handle(name(), L"removeLast", Error::TEST, __FILE__,
			 __LINE__);
  }
  
  // reset indentation
  //
  if (level_a > Integral::NONE) {
    Console::decreaseIndention();
  }
  
  //--------------------------------------------------------------------------
  //
  // 6. class-specific public methods:
  //     property methods
  //
  //--------------------------------------------------------------------------

  // set indentation
  //
  if (level_a > Integral::NONE) {
    Console::put(L"testing class-specific public methods: property methods...\n");
    Console::increaseIndention();
  }
  
  // testing list occupancy methods and the clear method
  //
  if (list_ptr_0->isEmpty()) {
    return Error::handle(name(), L"isEmpty", Error::TEST, __FILE__, __LINE__);
  }
  
  if (list_ptr_2->isEmpty()) {
    return Error::handle(name(), L"isEmpty", Error::TEST, __FILE__, __LINE__);
  }
  
  // clear the contents of the list
  //
  list_ptr_0->clear();
  
  if (!(list_ptr_0->isEmpty()) || list_ptr_0->length() != 0) {
    return Error::handle(name(), L"clear / isEmpty", Error::TEST, __FILE__,
			 __LINE__);
  }
  
  list_ptr_2->clear();
  
  if (!(list_ptr_2->isEmpty()) || list_ptr_2->length() != 0) {
    return Error::handle(name(), L"clear / isEmpty", Error::TEST, __FILE__,
			 __LINE__);
  }
  
  // clean up memory
  //
  delete list_ptr_0;
  delete list_ptr_1;
  delete list_ptr_2;

  for (int32 i = 0; i < num_elem; i++) {
    delete items[i];
  }
  delete [] items;

  // reset indentation
  //
  if (level_a > Integral::NONE) {
    Console::decreaseIndention();
  }

  //--------------------------------------------------------------------------
  //
  // 7. class-specific public methods:
  //     ordering methods
  //
  //--------------------------------------------------------------------------

  // set indentation
  //
  if (level_a > Integral::NONE) {
    Console::put(L"testing class-specific public methods: ordering methods...\n");
    Console::increaseIndention();
  }
  
  // testing the sort and apply method
  //
  DoubleLinkedList<Char> char_list_1;
  DoubleLinkedList<Char> char_list_2;
  DoubleLinkedList<Char> char_list_3;
  
  Char* low_chars = new Char[10];
  Char* up_chars = new Char[10];
  unichar low_tmp_char = L'a';
  unichar up_tmp_char = L'A';
  
  // initialize the characters and store them in reverse order in two lists
  //
  for (int32 i = 0; i < 10; i++) {
    
    low_chars[i].assign(low_tmp_char);
    
    // insert the character to the end of the list 1
    //
    char_list_1.insert(&low_chars[i]);
    
    // insert the character to the beginning of the list 2
    //
    char_list_2.insertFirst(&low_chars[i]);
    
    // insert the uppercase character to the end of the list 3
    //
    up_chars[i].assign(up_tmp_char);
    char_list_3.insert(&up_chars[i]);
    
    // increment the character value
    //
    low_tmp_char++;
    up_tmp_char++;
  }
    
  // reverse the elements in list 2
  //
  char_list_2.reverse();
  
  // the list 2 should be the same as the list 1 now
  //
  if (char_list_1.ne(char_list_2)) {
    char_list_1.debug(L"reversed list_1");
    return Error::handle(name(), L"reverse", Error::TEST, __FILE__,
			 __LINE__);
  } 

  // reset indentation
  //
  if (level_a > Integral::NONE) {
    Console::decreaseIndention();
  }

  //--------------------------------------------------------------------------
  //
  // 8. class-specific public methods:
  //     apply methods
  //
  //--------------------------------------------------------------------------

  // set indentation
  //
  if (level_a > Integral::NONE) {
    Console::put(L"testing class-specific public methods: apply methods...\n");
    Console::increaseIndention();
  }
  
  // apply a method to all the nodes in list 1
  //
  char_list_2.apply(&Char::toUpper, char_list_1);
  char_list_1.apply(&Char::toUpper);
  
  // list 1 should be the same as the list 3 now 
  //
  if (char_list_1.ne(char_list_3)) {
    char_list_1.debug(L"upper cased list_1");
    return Error::handle(name(), L"apply", Error::TEST, __FILE__, __LINE__);
  }

  // list 2 should be the same as the list 3 now 
  //
  if (char_list_2.ne(char_list_3)) {
    char_list_2.debug(L"upper cased list_2");
    return Error::handle(name(), L"apply", Error::TEST, __FILE__, __LINE__);
  }
  
  // clean up
  //
  delete [] low_chars;
  delete [] up_chars;

  // test sort and swap methods
  //
  DoubleLinkedList<Long> int32_list;
  
  VectorLong nums(L"5, 3, 2, 6, 4, 1, 3, 7");
  for (int32 i = 0; i < 8; i++) {
    int32_list.insert(&nums(i));
  }

  // test insertion sort algorithm (ascending)
  // the list now is  "1 2 3 3 4 5 6 7"
  //
  int32_list.sort(Integral::ASCENDING, DoubleLinkedList<Long>::INSERTION);

  for (int32 i = 0; i < 7; i++) {
    if (int32_list(i) > int32_list(i + 1)) {
      int32_list.debug(L"insertion sort, ascending");
      return Error::handle(name(), L"insertion sort", Error::TEST,
			   __FILE__, __LINE__);
    }
  }
  
  // swap two nodes with values "1" and "6", whose indices are 0 and 6 
  //
  int32_list.swap(0, 6);
  
  if ((int32)int32_list(0) != 6 || (int32)int32_list(6) != 1) {
    int32_list.debug(L"swap");
    return Error::handle(name(), L"swap", Error::TEST, __FILE__,
			 __LINE__);
  }
  
  // test insertion sort algorithm (descending)
  // the list now is  "7 6 5 4 3 3 2 1"
  //
  int32_list.sort(Integral::DESCENDING, DoubleLinkedList<Long>::INSERTION);

  for (int32 i = 0; i < 7; i++) {
    if (int32_list(i) < int32_list(i + 1)) {
      int32_list.debug(L"insertion sort, descending");
      return Error::handle(name(), L"insertion sort", Error::TEST,
			   __FILE__, __LINE__);
    }
  }

  // test quick sort algorithm (ascending)
  // the list now is  "1 2 3 3 4 5 6 7"
  //
  int32_list.sort(Integral::ASCENDING, DoubleLinkedList<Long>::RAND_QUICK);

  for (int32 i = 0; i < 7; i++) {
    if (int32_list(i) > int32_list(i + 1)) {
      int32_list.debug(L"randQuick sort, ascending");
      return Error::handle(name(), L"randQuickSort", Error::TEST,
			   __FILE__, __LINE__);
    }
  }

  // test quick sort algorithm (descending)
  // the list now is  "7 6 5 4 3 3 2 1"  
  //
  int32_list.sort(Integral::DESCENDING, DoubleLinkedList<Long>::RAND_QUICK);
  
  for (int32 i = 0; i < 7; i++) {
    if (int32_list(i) < int32_list(i + 1)) {
      int32_list.debug(L"randQuick sort, descending");
      return Error::handle(name(), L"randQuickSort", Error::TEST,
			   __FILE__, __LINE__);
    }
  }

  // reset indentation
  //
  if (level_a > Integral::NONE) {
    Console::decreaseIndention();
  }

  //---------------------------------------------------------------------
  //
  // 9. print completion message
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

