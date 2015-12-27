// file: $isip/class/dstr/Stack/StackDiagnose.h
// version: $Id: StackDiagnose.h 10636 2007-01-26 22:18:09Z tm334 $
//

// make sure definitions are made only once
//
#ifndef ISIP_STACK_DIAGNOSE
#define ISIP_STACK_DIAGNOSE

// isip include files
//
#ifndef ISIP_STACK
#include <Stack.h>
#endif

// StackDiagnose: a class that contains the diagnose method of Stack class.
//
template<class TObject>
class StackDiagnose : public Stack<TObject> {
  
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
    return Stack<TObject>::name();
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

// below are all the methods for the StackDiagnose template class
//

//---------------------------------------------------------------------
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
bool8 StackDiagnose<TObject>::diagnose(Integral::DEBUG level_a) {

  //---------------------------------------------------------------------------
  //
  // 0. preliminaries
  //
  //---------------------------------------------------------------------------

  // output the class name
  //
  if (level_a > Integral::NONE) {
    SysString output(L"diagnosing class ");
    output.concat(Stack<TObject>::CLASS_NAME);
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

  // test destructor/consturctor(s) in refernece mode
  //  prepare all of the character items to use in this stack diagnose
  //  we will use the letters of the english alphabet
  //
  int32 num_elem = 26;
  Char** items = new Char*[num_elem];
  for (int32 i = 0; i < num_elem; i++) {
    items[i] = new Char((unichar)((int32)(L'a') + i));
  }

  // test setDebug
  //
  Stack<TObject>::setDebug(Stack<TObject>::debug_level_d);
  
  // check the constructors for allocating on the stack
  //
  Stack<Char> def_stack;                // default constructor
  def_stack.push(items[0]);
  def_stack.push(items[1]);
  def_stack.push(items[2]);
  
  Stack<Char> copy_stack(def_stack);     // copy constructor
  
  // the two constructed stacks should have the same items in them now
  //
  if (def_stack.ne(copy_stack)) {
    return Error::handle(name(), L"copy constructor", Error::TEST, __FILE__,
			 __LINE__);
  }

  // check the constructors and destructors for allocating on the dynamic
  // memory heap
  //
  Stack<Char>* def_dyn_stack = new Stack<Char>();
  def_dyn_stack->push(items[0]);
  def_dyn_stack->push(items[1]);
  def_dyn_stack->push(items[2]);
  
  Stack<Char>* copy_dyn_stack = new Stack<Char>(*def_dyn_stack);
  
  // the two constructed stacks should have the same items in them now
  //
  if (def_dyn_stack->ne(copy_stack)) {
    return Error::handle(name(), L"copy constructor", Error::TEST, __FILE__,
			 __LINE__);
  }
  
  // see if we can dynamically delete
  //
  delete def_dyn_stack;
  delete copy_dyn_stack;
	     
  {
    // test destructor/consturctor(s) in reference mode
    //  prepare all of the character items to use in this stack diagnose
    //  we will use the letters of the english alphabet
    //
    Stack<Char> def_stack(DstrBase::USER);          // default constructor
    def_stack.push(items[0]);
    def_stack.push(items[1]);
    def_stack.push(items[2]);
    
    Stack<Char> copy_stack(def_stack);     // copy constructor
    
    // the two constructed stacks should have the same items in them now
    //
    if (def_stack.ne(copy_stack)) {
      return Error::handle(name(), L"copy constructor", Error::TEST, __FILE__,
			   __LINE__);
    }
    
    // check the constructors and destructors for allocating on the dynamic
    // memory heap
    //
    Stack<Char>* def_dyn_stack = new Stack<Char>;
    def_dyn_stack->setAllocationMode(DstrBase::USER);
    if (def_dyn_stack->getAllocationMode() != DstrBase::USER) {
      return Error::handle(name(), L"getAllocationMode", Error::TEST,
			   __FILE__, __LINE__);
    }
    
    def_dyn_stack->push(items[0]);
    def_dyn_stack->push(items[1]);
    def_dyn_stack->push(items[2]);
    
    Stack<Char>* copy_dyn_stack = new Stack<Char>(*def_dyn_stack);
    
    // the two constructed stacks should have the same items in them now
    // 
    if (def_dyn_stack->ne(copy_stack)) {
      return Error::handle(name(), L"copy constructor", Error::TEST, __FILE__,
			   __LINE__);
    }
    
    // see if we can dynamically delete
    //
    delete def_dyn_stack;
    delete copy_dyn_stack;
  }
  
  // test large allocation construction and deletion in reference mode
  //
  if (level_a >= Integral::ALL) {
    
    // output an informative message
    //
    Console::put(L"testing large chunk memory allocation and deletion\n");
    
    // set the memory to a strange block size so we can hopefully catch any
    // frame overrun errors
    //
    Stack<TObject>::setGrowSize((int32)731);
    
    // loop for a large number of times creating and deleting a large number
    // of Stacks at each loop
    //
    for (int32 j = 1; j <= 100; j++) {
      Stack<Char>** stacks = new Stack<Char>*[j * 100];
      
      // create the items
      //
      for (int32 i = 0; i < j * 100; i++) {
	stacks[i] =  new Stack<Char>();
      }
      
      // delete lists
      //
      for (int32 i = (j * 100) - 1; i >= 0; i--) {
	delete stacks[i];
      }
      
      // clean up memory
      //
      delete [] stacks;
    }
  }

  {
    // test large allocation construction and deletion in
    // SYSTEM-allocation mode
    //
    if (level_a >= Integral::ALL) {
      
      // output an informative message
      //
      Console::put(L"testing large chunk memory allocation and deletion\n");
      
      // set the memory to a strange block size so we can hopefully catch any
      // frame overrun errors
      //
      Stack<TObject>::setGrowSize((int32)731);
      
      // loop for a large number of times creating and deleting a large number
      // of Stacks at each loop
      //
      for (int32 j = 1; j <= 100; j++) {
	Stack<Char>** stacks = new Stack<Char>*[j * 100];
	
	// create the items
	//
	for (int32 i = 0; i < j * 100; i++) {
	  stacks[i] =  new Stack<Char>(DstrBase::USER);
	}
	
	// delete lists
	//
	for (int32 i = (j * 100) - 1; i >= 0; i--) {
	  delete stacks[i];
	}
	
	// clean up memory
	//
	delete [] stacks;
      }
    }    
  }
  
  // test assign methods in reference mode
  //
  Stack<Char> tmp_stack;
  Stack<Char>* tmp_dyn_stack = new Stack<Char>;
  
  // add all items onto the stack
  //
  tmp_stack.push(items, num_elem);
  
  // try the list assign method
  //
  tmp_dyn_stack->assign(tmp_stack);
  
  if (tmp_dyn_stack->ne(tmp_stack)) {
    return Error::handle(name(), L"list assign", Error::TEST, __FILE__,
			 __LINE__);
  }

  // clean up memory
  //
  delete tmp_dyn_stack;
  
  {
    // test assign methods in reference mode
    //
    Stack<Char> tmp_stack(DstrBase::USER);
    Stack<Char>* tmp_dyn_stack = new Stack<Char>(DstrBase::USER);
    
    // add all items onto the stack
    //
    tmp_stack.push(items, num_elem);
    
    // try the list assign method
    //
    tmp_dyn_stack->assign(tmp_stack);
    
    if (tmp_dyn_stack->ne(tmp_stack)) {
      return Error::handle(name(), L"list assign", Error::TEST, __FILE__,
			   __LINE__);
    }
    
    // clean up memory
    //
    delete tmp_dyn_stack;
  }

  // testing i/o methods in SYSTEM-allocation mode
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
  
  for (int32 i = 0; i < 5; i++) {
    write_chars[i] = new Char(tmp_char);
    write_strings[i] = new String();
    tmp_char++;
  }
  
  write_strings[0]->assign(L"this ");
  write_strings[1]->assign(L"is");
  write_strings[2]->assign(L"a");
  write_strings[3]->assign(L"Stack");
  write_strings[4]->assign(L"String");
  
  // create stacks to write
  //
  Stack<Char> write_char_stack;
  write_char_stack.push(write_chars, 5);
  
  Stack<String> write_str_stack;
  write_str_stack.push(write_strings, 5);
  
  Stack<Stack<Char > > write_char_stack_stack;
  
  Stack<Stack<Stack<Char > > > write_char_sss;
  
  // create objects for reading in
  //
  Stack<Char> read_char_stack_text;
  Stack<Char> read_char_stack_bin;
  Stack<String> read_str_stack_text;
  Stack<String> read_str_stack_bin;
  Stack<Stack<Char > > read_char_stack_stack_bin;
  
  Stack<Stack<Char > > read_char_stack_stack_text;
  
  Stack<Stack<Stack<Char > > > read_char_sss_bin;
  Stack<Stack<Stack<Char > > > read_char_sss_text;
  
  Stack<Stack<Char > >* wc_ss_0 = new Stack<Stack<Char > >;
  Stack<Stack<Char > >* wc_ss_1 = new Stack<Stack<Char > >;
  
  int32 s1 = 2;
  int32 s2 = 5;
  
  for (int32 i = 0; i < s1; i++) {
    
    Stack<Char>* temp = new Stack<Char>;
    
    Stack<Char>* t1 = new Stack<Char>;
    Stack<Char>* t2 = new Stack<Char>;
    
    for (int32 j = 0; j < s2; j++) {
      Char* c1 = new Char();
      Char* c2 = new Char();
      Char* c3 = new Char();
      
      c1->assign((unichar)(i * (s2+1) + j + (int)'A'));
      c2->assign((unichar)(i * (s2+1) + j + (int)'A'));
      c3->assign((unichar)(i * (s2+1) + j + (int)'a'));
      
      temp->push(c1);
      
      t1->push(c2);
      t2->push(c3);
      
      delete c1;
      delete c2;
      delete c3;
    }
    
    write_char_stack_stack.push(temp);
    wc_ss_0->push(t1);
    wc_ss_1->push(t2);
    
    delete temp;
    delete t1;
    delete t2;
  }
  
  // 10 channel vector data
  //
  s1 = 3;
  s2 = 20;
  
  write_char_sss.push(wc_ss_0);
  write_char_sss.push(wc_ss_1);
  
  // write the values
  //
  write_char_stack.write(text_file, (int32)0);
  write_char_stack.write(bin_file, (int32)0);  
  
  write_str_stack.write(text_file, (int32)0);
  write_str_stack.write(bin_file, (int32)0);  
  
  write_char_stack_stack.write(text_file, (int32)0);
  write_char_stack_stack.write(bin_file, (int32)0);  
  
  write_char_sss.write(text_file, (int32)0);
  write_char_sss.write(bin_file, (int32)0);  
  
  // close the files
  //
  text_file.close();
  bin_file.close();
  
  // open the files in read mode
  //
  text_file.open(text_filename);
  bin_file.open(bin_filename);
  
  // read in the lists and test for equivalence
  //
  if (!read_char_stack_text.read(text_file, (int32)0) ||
      (read_char_stack_text.ne(write_char_stack))) {
    return Error::handle(name(), L"read char text", Error::TEST, __FILE__,
			 __LINE__);
  }
  
  if (!read_str_stack_text.read(text_file, (int32)0) ||
      (read_str_stack_text.ne(write_str_stack))) {
    return Error::handle(name(), L"read str text", Error::TEST, __FILE__, 
			 __LINE__);
  }
  
  if (!read_char_stack_bin.read(bin_file, (int32)0) ||
      (read_char_stack_bin.ne(write_char_stack))) {
    return Error::handle(name(), L"write char bin", Error::TEST, __FILE__,
			 __LINE__);
  }
  
  if (!read_str_stack_bin.read(bin_file, (int32)0) ||
      (read_str_stack_bin.ne(write_str_stack))) {
    return Error::handle(name(), L"write str bin", Error::TEST, __FILE__,
			 __LINE__);
  }
  
  if (!read_char_stack_stack_text.read(text_file, (int32)0) ||
      (read_char_stack_stack_text.ne(write_char_stack_stack))) {
    return Error::handle(name(), L"read chr chr text", Error::TEST, __FILE__, 
			 __LINE__);
  }
  
  if (!read_char_stack_stack_bin.read(bin_file, (int32)0) ||
      (read_char_stack_stack_bin.ne(write_char_stack_stack))) {
    return Error::handle(name(), L"read chr chr bin", Error::TEST, __FILE__, 
			 __LINE__);
  }
  
  if (!read_char_sss_text.read(text_file, (int32)0) ||
      (read_char_sss_text.ne(write_char_sss))) {
    return Error::handle(name(), L"read chr chr chr text", Error::TEST,
			 __FILE__, __LINE__);
  }
  
  if (!read_char_sss_bin.read(bin_file, (int32)0) ||
      (read_char_sss_bin.ne(write_char_sss))) {
    return Error::handle(name(), L"read chr chr bin", Error::TEST, __FILE__, 
			 __LINE__);
  }
  
  // close and delete the temporary files
  //
  text_file.close();
  bin_file.close();
  File::remove(text_filename);
  File::remove(bin_filename);
  
  // cleanup the memory that was created by the Stack read
  //
  read_char_stack_text.clear(Integral::FREE);
  read_char_stack_bin.clear(Integral::FREE);
  read_str_stack_text.clear(Integral::FREE);
  read_str_stack_bin.clear(Integral::FREE);
  
  // delete things from the nested stacks
  //
  Stack<Char> temp_stack2;
  while((write_char_stack_stack.pop(&temp_stack2)) != (Stack<Char>*)NULL) {
    Char temp_char1;
    while ((temp_stack2.pop(&temp_char1)) != (Char*)NULL) {
    }
  }
  
  while ((read_char_stack_stack_bin.pop(&temp_stack2))
	!= (Stack<Char>*)NULL) {
    Char temp_char1;
    while ((temp_stack2.pop(&temp_char1)) != (Char*)NULL) {
    }
  }
  
  while ((read_char_stack_stack_text.pop(&temp_stack2))
	!= (Stack<Char>*)NULL) {
    Char temp_char1;
    while ((temp_stack2.pop(&temp_char1)) != (Char*)NULL) {
    }
  }
  
  // delete things from the triple-nested stacks
  //
  Stack< Stack<Char> > temp_ss;
  while (write_char_sss.pop(&temp_ss) != (Stack< Stack<Char> >*)NULL) {
    Stack<Char> temp_s;
    while (temp_ss.pop(&temp_s) != (Stack<Char>*)NULL) {
      Char temp_char1;
      while (temp_s.pop(&temp_char1) != (Char*)NULL) {
      }
    }
  }
  
  while (read_char_sss_text.pop(&temp_ss) != (Stack< Stack<Char> >*)NULL) {
    Stack<Char> temp_s;
    while (temp_ss.pop(&temp_s) != (Stack<Char>*)NULL) {
      Char temp_char1;
      while (temp_s.pop(&temp_char1) != (Char*)NULL) {
      }
    }
  }
  
  while (read_char_sss_bin.pop(&temp_ss) != (Stack< Stack<Char> >*)NULL) {
    Stack<Char> temp_s;
    while (temp_ss.pop(&temp_s) != (Stack<Char>*)NULL) {
      Char temp_char1;
      while (temp_s.pop(&temp_char1) != (Char*)NULL) {
      }
    }
  }
  
  // cleanup dynamically allocated memory
  //
  for (int32 i = 0; i < 5; i++) {
    delete  write_chars[i];
    delete write_strings[i];
  }
  
  delete [] write_chars;
  delete [] write_strings;
  
  delete wc_ss_0;
  delete wc_ss_1;  
  
  {
    // testing i/o methods for reference mode
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
    
    Char** write_chars = new Char*[5];
    String** write_strings = new String*[5];
    unichar tmp_char = L'a';
    
    for (int32 i = 0; i < 5; i++) {
      write_chars[i] = new Char(tmp_char);
      write_strings[i] = new String();
      tmp_char++;
    }
  
    write_strings[0]->assign(L"this ");
    write_strings[1]->assign(L"is");
    write_strings[2]->assign(L"a");
    write_strings[3]->assign(L"Stack");
    write_strings[4]->assign(L"String");
  
    // create stacks to write
    //
    Stack<Char> write_char_stack(DstrBase::USER);
    write_char_stack.push(write_chars, 5);
    
    Stack<String> write_str_stack(DstrBase::USER);
    write_str_stack.push(write_strings, 5);
    
    Stack<Stack<Char > > write_char_stack_stack(DstrBase::USER);    
    Stack<Stack<Stack<Char > > > write_char_sss(DstrBase::USER);

    Stack<Stack<Char > >* wc_ss_0 = new Stack<Stack<Char > >(DstrBase::USER);
    Stack<Stack<Char > >* wc_ss_1 = new Stack<Stack<Char > >(DstrBase::USER);
    
    // create objects for reading in
    //
    Stack<Char> read_char_stack_text(DstrBase::USER);
    Stack<Char> read_char_stack_bin(DstrBase::USER);
    Stack<String> read_str_stack_text(DstrBase::USER);
    Stack<String> read_str_stack_bin(DstrBase::USER);
    Stack<Stack<Char > > read_char_stack_stack_bin(DstrBase::USER);
    
    Stack<Stack<Char > > read_char_stack_stack_text(DstrBase::USER);
    
    Stack<Stack<Stack<Char > > > read_char_sss_bin(DstrBase::USER);
    Stack<Stack<Stack<Char > > > read_char_sss_text(DstrBase::USER);
        
    int32 s1 = 2;
    int32 s2 = 5;
    
    for (int32 i = 0; i < s1; i++) {
      
      Stack<Char>* temp = new Stack<Char>(DstrBase::USER);
      
      Stack<Char>* t1 = new Stack<Char>(DstrBase::USER);
      Stack<Char>* t2 = new Stack<Char>(DstrBase::USER);
      
      for (int32 j = 0; j < s2; j++) {
	Char* c1 = new Char();
	Char* c2 = new Char();
	Char* c3 = new Char();
	
	c1->assign((unichar)(i * (s2+1) + j + (int)'A'));
	c2->assign((unichar)(i * (s2+1) + j + (int)'A'));
	c3->assign((unichar)(i * (s2+1) + j + (int)'a'));
	
	temp->push(c1);
	
	t1->push(c2);
	t2->push(c3);
      }
      
      write_char_stack_stack.push(temp);
      wc_ss_0->push(t1);
      wc_ss_1->push(t2);
    }
    
    // 10 channel vector data
    //
    s1 = 3;
    s2 = 20;
    
    write_char_sss.push(wc_ss_0);
    write_char_sss.push(wc_ss_1);
    
    // write the values
    //
    write_char_stack.write(text_file, (int32)0);
    write_char_stack.write(bin_file, (int32)0);  

    write_str_stack.write(text_file, (int32)0);
    write_str_stack.write(bin_file, (int32)0);  
    
    write_char_stack_stack.write(text_file, (int32)0);
    write_char_stack_stack.write(bin_file, (int32)0);  
    
    write_char_sss.write(text_file, (int32)0);
    write_char_sss.write(bin_file, (int32)0);  
    
    // close the files
    //
    text_file.close();
    bin_file.close();
    
    // open the files in read mode
    //
    text_file.open(text_filename);
    bin_file.open(bin_filename);
    
    // read in the lists and test for equivalence
    //
    if (!read_char_stack_text.read(text_file, (int32)0) ||
	(read_char_stack_text.ne(write_char_stack))) {
      return Error::handle(name(), L"read char text", Error::TEST, __FILE__,
			   __LINE__);
    }

    if (!read_str_stack_text.read(text_file, (int32)0) ||
	(read_str_stack_text.ne(write_str_stack))) {
      return Error::handle(name(), L"read str text", Error::TEST, __FILE__, 
			   __LINE__);
    }

    if (!read_char_stack_bin.read(bin_file, (int32)0) ||
	(read_char_stack_bin.ne(write_char_stack))) {
      return Error::handle(name(), L"write char bin", Error::TEST, __FILE__,
			   __LINE__);
    }
    
    if (!read_str_stack_bin.read(bin_file, (int32)0) ||
	(read_str_stack_bin.ne(write_str_stack))) {
      return Error::handle(name(), L"write str bin", Error::TEST, __FILE__,
			   __LINE__);
    }
    
    if (!read_char_stack_stack_text.read(text_file, (int32)0) ||
	(read_char_stack_stack_text.ne(write_char_stack_stack))) {
      return Error::handle(name(), L"read chr chr text", Error::TEST, __FILE__, 
			   __LINE__);
    }
    
    if (!read_char_stack_stack_bin.read(bin_file, (int32)0) ||
	(read_char_stack_stack_bin.ne(write_char_stack_stack))) {
      return Error::handle(name(), L"read chr chr bin", Error::TEST, __FILE__, 
			   __LINE__);
    }
    
    if (!read_char_sss_text.read(text_file, (int32)0) ||
	(read_char_sss_text.ne(write_char_sss))) {
      return Error::handle(name(), L"read chr chr chr text", Error::TEST,
			   __FILE__, __LINE__);
    }
    
    if (!read_char_sss_bin.read(bin_file, (int32)0) ||
	(read_char_sss_bin.ne(write_char_sss))) {
      return Error::handle(name(), L"read chr chr bin", Error::TEST, __FILE__, 
			   __LINE__);
    }
    
    // close and delete the temporary files
    //
    text_file.close();
    bin_file.close();
    File::remove(text_filename);
    File::remove(bin_filename);
    
    // cleanup the memory that was created by the Stack read
    //
    read_char_stack_text.clear(Integral::FREE);
    read_char_stack_bin.clear(Integral::FREE);
    read_str_stack_text.clear(Integral::FREE);
    read_str_stack_bin.clear(Integral::FREE);
    
    // delete things from the nested stacks
    //
    Stack<Char>* temp_stack2;
    
    while((temp_stack2 = write_char_stack_stack.pop()) != (Stack<Char>*)NULL) {
      
      Char* temp_char;
      
      while ((temp_char = temp_stack2->pop()) != (Char*)NULL) {
	delete temp_char;
      }
      delete temp_stack2;
    }
    
    while ((temp_stack2 = read_char_stack_stack_bin.pop())
	  != (Stack<Char>*)NULL) {
      
      Char temp_char1;
      
      while ((temp_stack2->pop(&temp_char1)) != (Char*)NULL) {
      }
      delete temp_stack2;      
    }
      
    while ((temp_stack2 = read_char_stack_stack_text.pop())
	  != (Stack<Char>*)NULL) {
      
      Char temp_char1;
      
      while ((temp_stack2->pop(&temp_char1)) != (Char*)NULL) {
      }
      delete temp_stack2;
    }
    
    // delete things from the triple-nested stacks
    //
    Stack<Stack<Char > >* temp_ss;
    
    while ((temp_ss = write_char_sss.pop()) != (Stack< Stack<Char> >*)NULL) {
      
      Stack<Char>* temp_s;
	
      while ((temp_s = temp_ss->pop()) != (Stack<Char>*)NULL) {

	Char* temp_char;
	    
	while ((temp_char = temp_s->pop()) != (Char*)NULL) {
	  delete temp_char;
	}
	delete temp_s;
      }
      delete temp_ss;
    }
    
    while ((temp_ss = read_char_sss_text.pop())
	  != (Stack< Stack<Char> >*)NULL) {
      temp_ss->setAllocationMode(DstrBase::USER);      
      Stack<Char>* temp_s;
	
      while ((temp_s = temp_ss->pop()) != (Stack<Char>*)NULL) {

	temp_s->setAllocationMode(DstrBase::USER);
	Char* temp_char;
	    
	while ((temp_char = temp_s->pop()) != (Char*)NULL) {
	  delete temp_char;
	}
	delete temp_s;
      }
      delete temp_ss;
    }
    
    while ((temp_ss = read_char_sss_bin.pop())
	   != (Stack< Stack<Char> >*)NULL) {
      
      temp_ss->setAllocationMode(DstrBase::USER);
      Stack<Char>* temp_s;
	
      while ((temp_s = temp_ss->pop()) != (Stack<Char>*)NULL) {

	temp_s->setAllocationMode(DstrBase::USER);
	Char* temp_char;
	    
	while ((temp_char = temp_s->pop()) != (Char*)NULL) {
	  delete temp_char;
	}
	delete temp_s;
      }
      delete temp_ss;
    }

    // cleanup dynamically allocated memory
    //
    for (int32 i = 0; i < 5; i++) {
      delete  write_chars[i];
      delete write_strings[i];
    }

    delete [] write_chars;
    delete [] write_strings;

    // we do not delete wc_ss_0 and wc_ss_1 because they have been deleted
    // in write_char_sss object
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

  // test equality methods for reference mode
  //
  Stack<Char>* char_stack = new Stack<Char>;
  
  Char* characters = new Char[500];
  unichar temp_char = L'a';
  Char* tmp_char_ptr = new Char();

  // initialize the characters and store them in the stacks
  //
  for (int32 i = 0; i < 500; i++) {
    
    characters[i].assign(temp_char);
    
    // add the character to the stack
    //
    char_stack->push(&characters[i]);
    
    // increment the character value
    //
    temp_char++;
  }

  // copy this stack over
  //
  Stack<Char>* char_copy_stack = new Stack<Char>;
  char_copy_stack->assign(*char_stack);
  
  // both stacks should be the same
  //
  if (!char_stack->eq(*char_copy_stack)) {
    return Error::handle(name(), L"eq", Error::TEST, __FILE__,
			 __LINE__);
  }
  
  if (char_stack->ne(*char_copy_stack)) {
    return Error::handle(name(), L"ne", Error::TEST, __FILE__,
			 __LINE__);
  }

  // now test that ne() works
  //
  char_stack->pop(tmp_char_ptr);

  // the stacks should be different now.
  //
  // both stacks should be the same
  //
  if (char_stack->eq(*char_copy_stack)) {
    return Error::handle(name(), L"eq", Error::TEST, __FILE__,
			 __LINE__);
  }
  
  if (!char_stack->ne(*char_copy_stack)) {
    return Error::handle(name(), L"ne", Error::TEST, __FILE__,
			 __LINE__);
  }
  
  // clean up memory
  //
  delete char_stack;
  delete char_copy_stack;
  delete [] characters;
  
  {
    // test equality methods for reference mode
    //
    Stack<Char>* char_stack = new Stack<Char>(DstrBase::USER);
    
    Char* characters = new Char[500];
    unichar temp_char = L'a';
    
    // initialize the characters and store them in the stacks
    //
    for (int32 i = 0; i < 500; i++) {
      
      characters[i].assign(temp_char);
      
      // add the character to the stack
      //
      char_stack->push(&characters[i]);
      
      // increment the character value
      //
      temp_char++;
    }
    
    // copy this stack over
    //
    Stack<Char>* char_copy_stack = new Stack<Char>(DstrBase::USER);
    char_copy_stack->assign(*char_stack);
    
    // both stacks should be the same
    //
    if (!char_stack->eq(*char_copy_stack)) {
      return Error::handle(name(), L"eq", Error::TEST, __FILE__,
			   __LINE__);
    }
    
    if (char_stack->ne(*char_copy_stack)) {
      return Error::handle(name(), L"ne", Error::TEST, __FILE__,
			   __LINE__);
    }
    
    // now test that ne() works
    //
    char_stack->pop();
    
    // the stacks should be different now.
    //
    // both stacks should be the same
    //
    if (char_stack->eq(*char_copy_stack)) {
      return Error::handle(name(), L"eq", Error::TEST, __FILE__,
			   __LINE__);
    }
    
    if (!char_stack->ne(*char_copy_stack)) {
      return Error::handle(name(), L"ne", Error::TEST, __FILE__,
			   __LINE__);
    }
    
    // clean up memory
    //
    delete char_stack;
    delete char_copy_stack;
    delete [] characters;
  }

  // reset indentation
  //
  if (level_a > Integral::NONE) {
    Console::decreaseIndention();
  }

  //--------------------------------------------------------------------------
  //
  // 3. class-specific public methods:
  //     manipulation methods
  //
  //--------------------------------------------------------------------------
  
  // set indentation
  //
  if (level_a > Integral::NONE) {
    Console::put(L"testing class-specific public methods: manipulation methods...\n");
    Console::increaseIndention();
  }
  
  // test push, pop, peek and marking methods for reference mode
  //
  Stack<Char> pos_stack_1;
  Stack<Char> pos_stack_2;
  Stack<Char> pos_stack_3;
  Stack<Char> pos_stack_4;
  Stack<Char> temp_clear_stack;

  // test the various "push" methods
  //  populate the first stack with all of the letters from 'a' - 'n' in
  //  reverse order, marking the 'i'
  //
  for (int32 i = 0; i < 9; i++) {
    pos_stack_1.push(items[i]);
  }
  pos_stack_1.setMark();
  for (int32 i = 9; i < 14; i++) {
    pos_stack_1.push(items[i]);
  }

  // make sure that the top element is the 'n'
  //
  if (*pos_stack_1.peek() != *items[13]) {
    return Error::handle(name(), L"push", Error::TEST, __FILE__,
			 __LINE__);
  }

  // make sure that the mark is set
  //
  if (!pos_stack_1.markIsSet()) {
    return Error::handle(name(), L"setMark/markIsSet", Error::TEST, __FILE__,
			 __LINE__);
  }

  // populate the second stack with the entire alphabet
  //
  pos_stack_2.push(items, num_elem);

  // populate the third stack with all alphabets as well, but copied from
  // the second stack
  //
  pos_stack_3.push(pos_stack_2);

  // make sure that the second and third stack are the same
  //
  if (!pos_stack_2.eq(pos_stack_3)) {
    return Error::handle(name(), L"push", Error::TEST, __FILE__,
			 __LINE__);
  }

  // pop the first stack to the mark - it should now have 'i' - 'a' on it
  //
  pos_stack_1.popToMark(temp_clear_stack);

  // make sure the top item is the marked item
  //
  if (!(pos_stack_1.markIsSet() && pos_stack_1.isMarkedElement())) {
    return Error::handle(name(), L"isMarkedElement", Error::TEST, __FILE__,
			 __LINE__);
  }

  // make sure the top item is the 'i'
  //
  if (*pos_stack_1.peek() != *items[8]) {
    return Error::handle(name(), L"popToMark", Error::TEST, __FILE__,
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
  //     marker positioning methods
  //
  //--------------------------------------------------------------------------

  // set indentation
  //
  if (level_a > Integral::NONE) {
    Console::put(L"testing class-specific public methods: marker positioning methods...\n");
    Console::increaseIndention();
  }
  
  // make sure the clearMark method works
  //
  pos_stack_1.clearMark();
  if (pos_stack_1.markIsSet() || pos_stack_1.isMarkedElement()) {
    return Error::handle(name(), L"clearMark", Error::TEST, __FILE__,
			 __LINE__);
  }

  // mark the item again
  //
  pos_stack_1.setMark();
  if (!(pos_stack_1.markIsSet() && pos_stack_1.isMarkedElement())) {
    return Error::handle(name(), L"setMark", Error::TEST, __FILE__,
			 __LINE__);
  }

  // pop'ing the item off of the first stack should clear the mark
  //
  pos_stack_1.pop(tmp_char_ptr);
  if (pos_stack_1.markIsSet() || pos_stack_1.isMarkedElement()) {
    return Error::handle(name(), L"isMarkedElement", Error::TEST, __FILE__,
			 __LINE__);
  }

  // put the 'i' back onto the stack so that the first stack holds 'i' - 'a'
  //
  pos_stack_1.push(tmp_char_ptr);

  // the second stack currently holds 'a' - 'z'. pop until we reach the 's'
  // push the items pop'd onto the fourth stack
  //
  while ((pos_stack_2.peek())->ne(*items[18])) {
    pos_stack_2.pop(tmp_char_ptr);
    pos_stack_4.push(tmp_char_ptr);
  }

  // the second stack now holds 's' - 'z' and the fourth stack now holds
  // 'r' - 'a'. pop the fourth stack so that it holds 'i' - 'a'
  //
  pos_stack_4.pop(temp_clear_stack, 9);

  // now the first stack holds 'i' - 'a', the second stack holds 's' - 'z',
  // the fourth stack holds 'i' - 'a' and the third holds 'a' - 'z'.
  //
  
  // call popAll to put all items from the third stack onto the temp stack
  //
  pos_stack_3.popAll(temp_clear_stack);

  // reset indentation
  //
  if (level_a > Integral::NONE) {
    Console::decreaseIndention();
  }
  
  //--------------------------------------------------------------------------
  //
  // 5. class-specific public methods:
  //     property methods
  //
  //--------------------------------------------------------------------------

  // set indentation
  //
  if (level_a > Integral::NONE) {
    Console::put(L"testing class-specific public methods: property methods...\n");
    Console::increaseIndention();
  }
  
  // make sure the third stack is empty
  //
  if (!pos_stack_3.isEmpty()) {
    return Error::handle(name(), L"popAll", Error::TEST, __FILE__,
			 __LINE__);
  }

  // now pop elements off of the temp stack until we reach the 'p'
  //
  while ((temp_clear_stack.peek())->ne(*items[15])) {
    temp_clear_stack.pop(tmp_char_ptr);
  }

  // pop the 'p' from the temp stack to the third stack
  //
  temp_clear_stack.pop(pos_stack_3, 1);

  // now the first stack should have an 'i' at the top, the second stack
  // should have a 's' at the top, the third stack should have a 'p' at the
  // top, and the fourth stack should have a 'i' at the top. put all of these
  // together to get "isip"
  //
  String isip_string_i1, isip_string_s, isip_string_i2, isip_string_p;
  isip_string_i1.assign(*(pos_stack_1.peek()));
  isip_string_s.assign(*(pos_stack_2.peek()));
  isip_string_i2.assign(*(pos_stack_4.peek()));
  isip_string_p.assign(*(pos_stack_3.peek()));

  String isip_string;
  isip_string.concat(isip_string_i1);
  isip_string.concat(isip_string_s);
  isip_string.concat(isip_string_i2);
  isip_string.concat(isip_string_p);

  // compare the generated string to the set string
  //
  String comp_string(L"isip");
  
  if (comp_string.ne(isip_string)) {
    return Error::handle(name(), L"push/pop/mark methods failed",
			 Error::TEST, __FILE__, __LINE__);
  }
  
  // test the clear, isEmpty and length methods
  //
  if (!temp_clear_stack.clear() || !temp_clear_stack.isEmpty() ||
      (temp_clear_stack.length() != (int32)0)) {
    return Error::handle(name(), L"clear, isEmpty, length", Error::TEST,
			 __FILE__, __LINE__);
  }

  // check that the length on one of the occupied stacks is valid
  //
  if (pos_stack_2.isEmpty() || (pos_stack_2.length() != 8)) {
    return Error::handle(name(), L"length", Error::TEST,
			 __FILE__, __LINE__);
  }
    
  {
    // test push, pop, peek and marking methods for reference mode
    //
    Stack<Char> pos_stack_1(DstrBase::USER);
    Stack<Char> pos_stack_2(DstrBase::USER);
    Stack<Char> pos_stack_3(DstrBase::USER);
    Stack<Char> pos_stack_4(DstrBase::USER);
    Stack<Char> temp_clear_stack(DstrBase::USER);
    
    // test the various "push" methods
    //  populate the first stack with all of the letters from 'a' - 'n' in
    //  reverse order, marking the 'i'
    //
    for (int32 i = 0; i < 9; i++) {
      pos_stack_1.push(items[i]);
    }
    pos_stack_1.setMark();
    for (int32 i = 9; i < 14; i++) {
      pos_stack_1.push(items[i]);
    }
    
    // make sure that the top element is the 'n'
    //
    if (pos_stack_1.peek() != items[13]) {
      return Error::handle(name(), L"push", Error::TEST, __FILE__,
			   __LINE__);
    }
    
    // make sure that the mark is set
    //
    if (!pos_stack_1.markIsSet()) {
      return Error::handle(name(), L"setMark/markIsSet", Error::TEST, __FILE__,
			   __LINE__);
    }
    
    // populate the second stack with the entire alphabet
    //
    pos_stack_2.push(items, num_elem);
    
    // populate the third stack with all alphabets as well, but copied from
    // the second stack
    //
    pos_stack_3.push(pos_stack_2);
    
    // make sure that the second and third stack are the same
    //
    if (!pos_stack_2.eq(pos_stack_3)) {
      return Error::handle(name(), L"push", Error::TEST, __FILE__,
			   __LINE__);
    }
    
    // pop the first stack to the mark - it should now have 'i' - 'a' on it
    //
    pos_stack_1.popToMark(temp_clear_stack);
    
    // make sure the top item is the marked item
    //
    if (!(pos_stack_1.markIsSet() && pos_stack_1.isMarkedElement())) {
      return Error::handle(name(), L"isMarkedElement", Error::TEST, __FILE__,
			   __LINE__);
    }
    
    // make sure the top item is the 'i'
    //
    if (pos_stack_1.peek() != items[8]) {
      return Error::handle(name(), L"popToMark", Error::TEST, __FILE__,
			   __LINE__);
    }
    
    // make sure the clearMark method works
    //
    pos_stack_1.clearMark();
    if (pos_stack_1.markIsSet() || pos_stack_1.isMarkedElement()) {
      return Error::handle(name(), L"clearMark", Error::TEST, __FILE__,
			   __LINE__);
    }
    
    // mark the item again
    //
    pos_stack_1.setMark();
    if (!(pos_stack_1.markIsSet() && pos_stack_1.isMarkedElement())) {
      return Error::handle(name(), L"setMark", Error::TEST, __FILE__,
			   __LINE__);
    }
    
    // pop'ing the item off of the first stack should clear the mark
    //
    Char* tmp_char_ptr3;
    tmp_char_ptr3 = pos_stack_1.pop();
    if (pos_stack_1.markIsSet() || pos_stack_1.isMarkedElement()) {
      return Error::handle(name(), L"isMarkedElement", Error::TEST, __FILE__,
			   __LINE__);
    }
    
    // put the 'i' back onto the stack so that the first stack holds 'i' - 'a'
    //
    pos_stack_1.push(tmp_char_ptr3);
    
    // the second stack currently holds 'a' - 'z'. pop until we reach the 'p'
    // push the items pop'd onto the fourth stack
    //
    while ((pos_stack_2.peek())->ne(*items[18])) {
      Char* tmp_char_ptr2;
      tmp_char_ptr2 = pos_stack_2.pop();
      pos_stack_4.push(tmp_char_ptr2);
    }
    
    // the second stack now holds 's' - 'z' and the fourth stack now holds
    // 'r' - 'a'. pop the fourth stack so that it holds 'i' - 'a'
    //
    pos_stack_4.pop(temp_clear_stack, 9);
    
    // now the first stack holds 'i' - 'a', the second stack holds 's' - 'z',
    // the fourth stack holds 'i' - 'a' and the third holds 'a' - 'z'.
    //
    
    // call popAll to put all items from the third stack onto the temp stack
    //
    pos_stack_3.popAll(temp_clear_stack);
    
    // make sure the third stack is empty
    //
    if (!pos_stack_3.isEmpty()) {
      return Error::handle(name(), L"popAll", Error::TEST, __FILE__,
			   __LINE__);
    }
    
    // now pop elements off of the temp stack until we reach the 'p'
    //
    while ((temp_clear_stack.peek())->ne(*items[15])) {
      temp_clear_stack.pop();
    }
    
    // pop the 'p' from the temp stack to the third stack
    //
    temp_clear_stack.pop(pos_stack_3, 1);
    
    // now the first stack should have an 'i' at the top, the second stack
    // should have a 's' at the top, the third stack should have a 'p' at the
    // top, and the fourth stack should have a 'i' at the top. put all of these
    // together to get "isip"
    //
    String isip_string_i1, isip_string_s, isip_string_i2, isip_string_p;
    isip_string_i1.assign(*(pos_stack_1.peek()));
    isip_string_s.assign(*(pos_stack_2.peek()));
    isip_string_i2.assign(*(pos_stack_4.peek()));
    isip_string_p.assign(*(pos_stack_3.peek()));
    
    String isip_string;
    isip_string.concat(isip_string_i1);
    isip_string.concat(isip_string_s);
    isip_string.concat(isip_string_i2);
    isip_string.concat(isip_string_p);
    
    // compare the generated string to the set string
    //
    String comp_string(L"isip");
    
    if (comp_string.ne(isip_string)) {
      return Error::handle(name(), L"push/pop/mark methods failed",
			   Error::TEST, __FILE__, __LINE__);
    }

    // test the clear, isEmpty and length methods
    //
    if (!temp_clear_stack.clear() || !temp_clear_stack.isEmpty() ||
	(temp_clear_stack.length() != (int32)0)) {
      return Error::handle(name(), L"clear, isEmpty, length", Error::TEST,
			   __FILE__, __LINE__);
    }
    
    // check that the length on one of the occupied stacks is valid
    //
    if (pos_stack_2.isEmpty() || (pos_stack_2.length() != 8)) {
      return Error::handle(name(), L"length", Error::TEST,
			   __FILE__, __LINE__);
    }
  }

  // reset indentation
  //
  if (level_a > Integral::NONE) {
    Console::decreaseIndention();
  }
  
  //--------------------------------------------------------------------------
  //
  // 6. class-specific public methods:
  //     computation methods
  //
  //--------------------------------------------------------------------------

  // set indentation
  //
  if (level_a > Integral::NONE) {
    Console::put(L"testing class-specific public methods: computation methods...\n");
    Console::increaseIndention();
  }
  
  // testing the sort/apply/reverse methods for reference mode
  //
  Char** low_chars = new Char*[num_elem];
  for (int32 i = 0; i < num_elem; i++) {
    low_chars[i] = new Char(*items[i]);
  }

  Char** up_chars = new Char*[num_elem];
  for (int32 i = 0; i < num_elem; i++) {
    up_chars[i] = new Char(*items[i]);
  }
  
  // initialize stacks and Char objects to use for testing
  //
  Stack<Char> char_stack_1;
  Stack<Char> char_stack_2;
  Stack<Char> char_stack_3;
  Stack<Char> char_stack_4;
  Stack<Char> temp_stack;

  // add all of the lower case characters to the first stack 'a' - 'z'
  //
  char_stack_1.push(low_chars, num_elem);
  
  // create an upper case version of these in the second stack 'A' - 'Z'
  //
  char_stack_2.push(up_chars, num_elem);
  char_stack_2.apply(&Char::toUpper);

  // add all of the lower case elements to the third stack and upcase them
  // all, then reverse them 'Z' - 'A'
  //
  char_stack_3.apply(&Char::toUpper, char_stack_1);
  char_stack_3.reverse();

  // create the fourth stack with all lower case elements
  //
  char_stack_4.push(items, num_elem);
  
  // copy the fourth stack onto the third stack 'a' - 'z', 'Z' - 'A'
  //
  char_stack_3.push(char_stack_4);

  // move the lower case letters off of the third stack and onto the temp
  // stack 'a' - 'z', the third stack now has 'Z' - 'A'
  //
  char_stack_3.pop(temp_stack, 26);

  // reverse the letters in the second stack 'Z' - 'A'
  //
  char_stack_2.reverse();
  
  // the third stack should be the same as the second stack now and the
  // temp stack should be the same as the fourth stack
  //
  if (char_stack_2.ne(char_stack_3) || temp_stack.ne(char_stack_4)) {
    return Error::handle(name(), L"sort/apply", Error::TEST, __FILE__,
			 __LINE__);
  }

  // reset indentation
  //
  if (level_a > Integral::NONE) {
    Console::decreaseIndention();
  }
    
  //--------------------------------------------------------------------------
  //
  // 7. class-specific public methods:
  //     element ordering methods
  //
  //--------------------------------------------------------------------------

  // set indentation
  //
  if (level_a > Integral::NONE) {
    Console::put(L"testing class-specific public methods: element ordering methods...\n");
    Console::increaseIndention();
  }
    
  // sort the third stack in ascending order, 'A' - 'Z', 'a' - 'z'
  //
  char_stack_2.sort();
  char_stack_3.sort(Integral::ASCENDING, Stack<Char>::INSERTION);
  char_stack_4.apply(&Char::toUpper);

  // all these three list should be 'A' - 'Z'
  //
  if (char_stack_2.ne(char_stack_3) || char_stack_2.ne(char_stack_4)) {
    return Error::handle(name(), L"sort", Error::TEST, __FILE__,
			 __LINE__);
  }

  if (level_a >= Integral::ALL) {
    char_stack_2.debug(L"sorted list");
  }

  // lower case the forth stack
  //
  char_stack_4.apply(&Char::toLower);
    
  // see if the fourth stack contains the letter 'm'
  //
  if (!char_stack_4.contains(items[12])) {
    return Error::handle(name(), L"contains", Error::TEST, __FILE__,
			 __LINE__);
  }

  // make sure that 'a' is still the current item
  //
  if (char_stack_4.peek()->ne(*items[0])) {
    return Error::handle(name(), L"contains", Error::TEST, __FILE__,
			 __LINE__);
  }

  // test the find method
  //
  if (!char_stack_4.find(items[12])) {
    return Error::handle(name(), L"find", Error::TEST, __FILE__,
			 __LINE__);
  }

  // make sure that items[12] is marked
  //
  if (char_stack_4.getMark()->ne(*items[12])) {
    return Error::handle(name(), L"find", Error::TEST, __FILE__,
			 __LINE__);
  }

  {
    // testing the sort/apply/reverse methods for reference mode
    //
    Stack<Char> char_stack_1(DstrBase::USER);
    Stack<Char> char_stack_2(DstrBase::USER);
    Stack<Char> char_stack_3(DstrBase::USER);
    Stack<Char> char_stack_4(DstrBase::USER);
    Stack<Char> temp_stack(DstrBase::USER);
    
    // add all of the lower case characters to the first stack 'a' - 'z'
    //
    char_stack_1.push(low_chars, num_elem);
    
    // create an upper case version of these in the second stack 'A' - 'Z'
    //
    char_stack_2.push(up_chars, num_elem);
    char_stack_2.apply(&Char::toUpper);
    
    // add all of the lower case elements to the third stack and upcase them
    // all, then reverse them 'Z' - 'A'
    //
    char_stack_3.apply(&Char::toUpper, char_stack_1);
    char_stack_3.reverse();
    
    // create the fourth stack with all lower case elements
    //
    char_stack_4.push(items, num_elem);
    
    // copy the fourth stack onto the third stack 'a' - 'z', 'Z' - 'A'
    //
    char_stack_3.push(char_stack_4);
    
    // move the lower case letters off of the third stack and onto the temp
    // stack 'a' - 'z', the third stack now has 'Z' - 'A'
    //
    char_stack_3.pop(temp_stack, 26);
    
    // reverse the letters in the second stack 'Z' - 'A'
    //
    char_stack_2.reverse();

    // the third stack should be the same as the second stack now and the
    // temp stack should be the same as the fourth stack
    //
    if (char_stack_2.ne(char_stack_3) || temp_stack.ne(char_stack_4)) {
      return Error::handle(name(), L"sort/apply", Error::TEST, __FILE__,
			   __LINE__);
    }
    
    // sort the third stack in ascending order, 'A' - 'Z', 'a' - 'z'
    //
    char_stack_2.sort();
    char_stack_3.sort(Integral::ASCENDING, Stack<Char>::INSERTION);
    
    char_stack_4.apply(&Char::toUpper);
    
    // all these three list should be 'A' - 'Z'
    //
    if (char_stack_2.ne(char_stack_3) || char_stack_2.ne(char_stack_4)) {
      return Error::handle(name(), L"sort", Error::TEST, __FILE__,
			   __LINE__);
    }
    
    if (level_a >= Integral::ALL) {
      char_stack_2.debug(L"sorted list");
    }
    
    // see if the fourth stack contains the letter 'm'
    //
    if (!char_stack_4.contains(items[12])) {
      return Error::handle(name(), L"contains", Error::TEST, __FILE__,
			   __LINE__);
    }
    
    // make sure that 'a' is still the current item
    //
    if (char_stack_4.peek()->ne(*items[0])) {
      return Error::handle(name(), L"contains", Error::TEST, __FILE__,
			   __LINE__);
    }
  }

  // clean up memory
  //
  for (int32 i = 0; i < num_elem; i++) {
    delete items[i];
    delete up_chars[i];
    delete low_chars[i];
  }
  delete [] items;
  delete [] up_chars;
  delete [] low_chars;
  delete tmp_char_ptr;
  
  // reset indentation
  //
  if (level_a > Integral::NONE) {
    Console::decreaseIndention();
  }

  //---------------------------------------------------------------------------
  //
  // 8. print completion message
  //
  //---------------------------------------------------------------------------

  // reset indentation
  //
  if (level_a > Integral::NONE) {
    Console::decreaseIndention();
  }
  
  // possibly print completion message
  //
  if (level_a > Integral::NONE) {
    String output(L"diagnostics completed successfully for class ");
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
