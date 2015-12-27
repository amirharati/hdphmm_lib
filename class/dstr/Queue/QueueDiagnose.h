// file: $isip/class/dstr/Queue/QueueDiagnose.h
// version: $Id: QueueDiagnose.h 10636 2007-01-26 22:18:09Z tm334 $
//

// make sure definitions are only made once
//
#ifndef ISIP_QUEUE_DIAGNOSE
#define ISIP_QUEUE_DIAGNOSE

// isip include files
//
#ifndef ISIP_QUEUE
#include <Queue.h>
#endif

// QueueDiagnose: a class that contains the diagnose method of Queue class.
//
template<class TObject>
class QueueDiagnose : public Queue<TObject> {

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
    return Queue<TObject>::name();
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

// below are all the methods for the QueueDiagnose template class
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
template<class TObject>
bool8 QueueDiagnose<TObject>::diagnose(Integral::DEBUG level_a) {

  //---------------------------------------------------------------------------
  //
  // 0. preliminaries
  //
  //---------------------------------------------------------------------------

  // output the class name
  //
  if (level_a > Integral::NONE) {
    SysString output(L"diagnosing class ");
    output.concat(Queue<TObject>::CLASS_NAME);
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
  //  prepare all of the character items to use in this queue diagnose
  //  we will use the letters of the english alphabet
  //
  int32 num_elem = 26;
  Char** items = new Char*[num_elem];
  for (int32 i = 0; i < num_elem; i++) {
    items[i] = new Char((unichar)((int32)(L'a') + i));
  }

  // check the constructors for allocating on the queue
  //
  Queue<Char> def_queue;                // default constructor
  def_queue.add(items[0]);
  def_queue.add(items[1]);
  def_queue.add(items[2]);

  Queue<TObject>::setDebug(Queue<TObject>::debug_level_d);
  
  Queue<Char> copy_queue(def_queue);     // copy constructor

  if (copy_queue.getAllocationMode() != DstrBase::SYSTEM) {
    return Error::handle(name(), L"getAllocationMode", Error::TEST, __FILE__,
			 __LINE__);
  }
  
  // the two constructed queues should have the same items in them now
  //
  if (def_queue.ne(copy_queue)) {
    return Error::handle(name(), L"copy constructor", Error::TEST, __FILE__,
			 __LINE__);
  }

  // check the constructors and destructors for allocating on the dynamic
  // memory heap
  //
  Queue<Char>* def_dyn_queue = new Queue<Char>;
  def_dyn_queue->add(items[0]);
  def_dyn_queue->add(items[1]);
  def_dyn_queue->add(items[2]);
  
  Queue<Char>* copy_dyn_queue = new Queue<Char>(*def_dyn_queue);
  
  // the two constructed queues should have the same items in them now
  //
  if (def_dyn_queue->ne(copy_queue)) {
    return Error::handle(name(), L"copy constructor", Error::TEST, __FILE__,
			 __LINE__);
  }
  
  // see if we can dynamically delete
  //
  delete def_dyn_queue;
  delete copy_dyn_queue;

  {
    // test destructor/consturctor(s) in self-allocation mode
    //  prepare all of the character items to use in this queue diagnose
    //  we will use the letters of the english alphabet
    //
    Queue<Char> def_queue(DstrBase::USER);          // default constructor
    def_queue.add(items[0]);
    def_queue.add(items[1]);
    def_queue.add(items[2]);
    
    Queue<Char> copy_queue(def_queue);     // copy constructor
    
    // the two constructed queues should have the same items in them now
    //
    if (def_queue.ne(copy_queue)) {
      return Error::handle(name(), L"copy constructor", Error::TEST, __FILE__,
			   __LINE__);
    }
    
    // check the constructors and destructors for allocating on the dynamic
    // memory heap
    //
    Queue<Char>* def_dyn_queue = new Queue<Char>(DstrBase::USER);
    def_dyn_queue->add(items[0]);
    def_dyn_queue->add(items[1]);
    def_dyn_queue->add(items[2]);
    
    Queue<Char>* copy_dyn_queue = new Queue<Char>(*def_dyn_queue);
    
    // the two constructed queues should have the same items in them now
    //
    if (def_dyn_queue->ne(copy_queue)) {
      return Error::handle(name(), L"copy constructor", Error::TEST, __FILE__,
			   __LINE__);
    }
    
    // see if we can dynamically delete
    //
    delete def_dyn_queue;
    delete copy_dyn_queue;
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
    Queue<TObject>::setGrowSize((int32)731);
    
    // loop for a large number of times creating and deleting a large number
    // of Queues at each loop
    //
    for (int32 j = 1; j <= 100; j++) {
      Queue<Char>** queues = new Queue<Char>*[j * 100];
      
      // create the items
      //
      for (int32 i = 0; i < j * 100; i++) {
	queues[i] =  new Queue<Char>();
      }
      
      // delete lists
      //
      for (int32 i = (j * 100) - 1; i >= 0; i--) {
	delete queues[i];
      }
      
      // clean up memory
      //
      delete [] queues;
    }
  }

  {
    // test large allocation construction and deletion in self-allocation mode
    //
    if (level_a >= Integral::ALL) {
      
      // output an informative message
      //
      Console::put(L"testing large chunk memory allocation and deletion\n");
      
      // set the memory to a strange block size so we can hopefully catch any
      // frame overrun errors
      //
      Queue<TObject>::setGrowSize((int32)731);
      
      // loop for a large number of times creating and deleting a large number
      // of Queues at each loop
      //
      for (int32 j = 1; j <= 100; j++) {
	Queue<Char>** queues = new Queue<Char>*[j * 100];
	
	// create the items
	//
	for (int32 i = 0; i < j * 100; i++) {
	  queues[i] =  new Queue<Char>(DstrBase::USER);
	}
	
	// delete lists
	//
	for (int32 i = (j * 100) - 1; i >= 0; i--) {
	  delete queues[i];
	}
	
	// clean up memory
	//
	delete [] queues;
      }
    }    
  }
  
  // test assign methods in reference mode
  //
  Queue<Char> tmp_queue;
  Queue<Char>* tmp_dyn_queue = new Queue<Char>;
  
  // add all items onto the queue
  //
  tmp_queue.add(items, num_elem);
  
  // try the list assign method
  //
  tmp_dyn_queue->assign(tmp_queue);
  
  if (tmp_dyn_queue->ne(tmp_queue)) {
    return Error::handle(name(), L"list assign", Error::TEST, __FILE__,
			 __LINE__);
  }

  // clean up memory
  //
  delete tmp_dyn_queue;  
  
  {
    // test assign methods in self-allocation mode
    //
    Queue<Char> tmp_queue(DstrBase::USER);
    Queue<Char>* tmp_dyn_queue = new Queue<Char>(DstrBase::USER);
    
    // add all items onto the queue
    //
    tmp_queue.add(items, num_elem);
    
    // try the list assign method
    //
    tmp_dyn_queue->assign(tmp_queue);
    
    if (tmp_dyn_queue->ne(tmp_queue)) {
      return Error::handle(name(), L"list assign", Error::TEST, __FILE__,
			   __LINE__);
    }
    
    // clean up memory
    //
    delete tmp_dyn_queue;
  }
  
  // testing i/o methods in self-allocation mode
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
  write_strings[3]->assign(L"Queue");
  write_strings[4]->assign(L"String");
  
  // create queues to write
  //
  Queue<Char> write_char_queue;
  write_char_queue.add(write_chars, 5);
  
  Queue<String> write_str_queue;
  write_str_queue.add(write_strings, 5);
  
  Queue<Queue<Char > > write_char_queue_queue;  
  Queue<Queue<Queue<Char > > > write_char_sss;
  
  // create objects for reading in
  //
  Queue<Char> read_char_queue_text;
  Queue<Char> read_char_queue_bin;
  Queue<String> read_str_queue_text;
  Queue<String> read_str_queue_bin;
  
  Queue<Queue<Char > > read_char_queue_queue_bin;
  Queue<Queue<Char > > read_char_queue_queue_text;
  
  Queue<Queue<Queue<Char > > > read_char_sss_bin;
  Queue<Queue<Queue<Char > > > read_char_sss_text;
  
  Queue<Queue<Char > >* wc_ss_0 = new Queue<Queue<Char > >;
  Queue<Queue<Char > >* wc_ss_1 = new Queue<Queue<Char > >;
  
  int32 s1 = 2;
  int32 s2 = 5;
  
  for (int32 i = 0; i < s1; i++) {
    
    Queue<Char>* temp = new Queue<Char>;
    
    Queue<Char>* t1 = new Queue<Char>;
    Queue<Char>* t2 = new Queue<Char>;
    
    for (int32 j = 0; j < s2; j++) {
      Char* c1 = new Char();
      Char* c2 = new Char();
      Char* c3 = new Char();
      
      c1->assign((unichar)(i * (s2+1) + j + (int)'A'));
      c2->assign((unichar)(i * (s2+1) + j + (int)'A'));
      c3->assign((unichar)(i * (s2+1) + j + (int)'a'));
      
      temp->add(c1);
      t1->add(c2);
      t2->add(c3);
      
      delete c1;
      delete c2;
      delete c3;
    }
    
    write_char_queue_queue.add(temp);
    wc_ss_0->add(t1);
    wc_ss_1->add(t2);
    
    delete temp;
    delete t1;
    delete t2;
  }
  
  // 10 channel vector data
  //
  s1 = 3;
  s2 = 20;
  
  write_char_sss.add(wc_ss_0);
  write_char_sss.add(wc_ss_1);
  
  // write the values
  //
  write_char_queue.write(text_file, (int32)0);
  write_char_queue.write(bin_file, (int32)0);  
  
  write_str_queue.write(text_file, (int32)0);
  write_str_queue.write(bin_file, (int32)0);  
  
  write_char_queue_queue.write(text_file, (int32)0);
  write_char_queue_queue.write(bin_file, (int32)0);  
  
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
  if (!read_char_queue_text.read(text_file, (int32)0) ||
      (read_char_queue_text.ne(write_char_queue))) {
    return Error::handle(name(), L"read char text", Error::TEST, __FILE__,
			 __LINE__);
  }
  
  if (!read_str_queue_text.read(text_file, (int32)0) ||
      (read_str_queue_text.ne(write_str_queue))) {
    return Error::handle(name(), L"read str text", Error::TEST, __FILE__, 
			 __LINE__);
  }
  
  if (!read_char_queue_bin.read(bin_file, (int32)0) ||
      (read_char_queue_bin.ne(write_char_queue))) {
    return Error::handle(name(), L"write char bin", Error::TEST, __FILE__,
			 __LINE__);
  }
  
  if (!read_str_queue_bin.read(bin_file, (int32)0) ||
      (read_str_queue_bin.ne(write_str_queue))) {
    return Error::handle(name(), L"write str bin", Error::TEST, __FILE__,
			 __LINE__);
  }
  
  if (!read_char_queue_queue_text.read(text_file, (int32)0) ||
      (read_char_queue_queue_text.ne(write_char_queue_queue))) {
    return Error::handle(name(), L"read chr chr text", Error::TEST, __FILE__, 
			 __LINE__);
  }
  
  if (!read_char_queue_queue_bin.read(bin_file, (int32)0) ||
      (read_char_queue_queue_bin.ne(write_char_queue_queue))) {
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
  
  // cleanup the memory that was created by the Queue read
  //
  read_char_queue_text.clear(Integral::FREE);
  read_char_queue_bin.clear(Integral::FREE);
  read_str_queue_text.clear(Integral::FREE);
  read_str_queue_bin.clear(Integral::FREE);
  
  // delete things from the nested queues
  //
  Queue<Char> temp_queue2;
  while (write_char_queue_queue.remove(&temp_queue2) != (Queue<Char>*)NULL) {
    Char temp_char1;
    while ((temp_queue2.remove(&temp_char1)) != (Char*)NULL) {
    }
  }
  
  while (read_char_queue_queue_bin.remove(&temp_queue2)
	!= (Queue<Char>*)NULL) {
    Char temp_char1;
    while ((temp_queue2.remove(&temp_char1)) != (Char*)NULL) {
    }
  }
  
  while (read_char_queue_queue_text.remove(&temp_queue2)
	!= (Queue<Char>*)NULL) {
    Char temp_char1;
    while ((temp_queue2.remove(&temp_char1)) != (Char*)NULL) {
    }
  }
  
  // delete things from the triple-nested queues
  //
  Queue< Queue<Char> > temp_ss;
  while(write_char_sss.remove(&temp_ss) != (Queue< Queue<Char> >*)NULL) {
    Queue<Char> temp_s;
    while (temp_ss.remove(&temp_s) != (Queue<Char>*)NULL) {
      Char temp_char1;
      while (temp_s.remove(&temp_char1) != (Char*)NULL) {
      }
    }
  }
  
  while(read_char_sss_text.remove(&temp_ss) != (Queue< Queue<Char> >*)NULL) {
    Queue<Char> temp_s;
    while (temp_ss.remove(&temp_s) != (Queue<Char>*)NULL) {
      Char temp_char1;
      while (temp_s.remove(&temp_char1) != (Char*)NULL) {
      }
    }
  }
  
  while(read_char_sss_bin.remove(&temp_ss) != (Queue< Queue<Char> >*)NULL) {
    Queue<Char> temp_s;
    while (temp_ss.remove(&temp_s) != (Queue<Char>*)NULL) {
      Char temp_char1;
      while (temp_s.remove(&temp_char1) != (Char*)NULL) {
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
    write_strings[3]->assign(L"Queue");
    write_strings[4]->assign(L"String");
    
    // create queues to write
    //
    Queue<Char> write_char_queue(DstrBase::USER);
    write_char_queue.add(write_chars, 5);
    
    Queue<String> write_str_queue(DstrBase::USER);
    write_str_queue.add(write_strings, 5);
    
    Queue<Queue<Char > > write_char_queue_queue(DstrBase::USER);    
    Queue<Queue<Queue<Char > > > write_char_sss(DstrBase::USER);
    
    Queue<Queue<Char > >* wc_ss_0 = new Queue<Queue<Char > >(DstrBase::USER);
    Queue<Queue<Char > >* wc_ss_1 = new Queue<Queue<Char > >(DstrBase::USER);
    
    // create objects for reading in
    //
    Queue<Char> read_char_queue_text(DstrBase::USER);
    Queue<Char> read_char_queue_bin(DstrBase::USER);
    Queue<String> read_str_queue_text(DstrBase::USER);
    Queue<String> read_str_queue_bin(DstrBase::USER);
    Queue<Queue<Char > > read_char_queue_queue_bin(DstrBase::USER);
    
    Queue<Queue<Char > > read_char_queue_queue_text(DstrBase::USER);
    
    Queue<Queue<Queue<Char > > > read_char_sss_bin(DstrBase::USER);
    Queue<Queue<Queue<Char > > > read_char_sss_text(DstrBase::USER);
    
    int32 s1 = 2;
    int32 s2 = 5;
    
    for (int32 i = 0; i < s1; i++) {
      
      Queue<Char>* temp = new Queue<Char>(DstrBase::USER);
      
      Queue<Char>* t1 = new Queue<Char>(DstrBase::USER);
      Queue<Char>* t2 = new Queue<Char>(DstrBase::USER);
      
      for (int32 j = 0; j < s2; j++) {
	Char* c1 = new Char();
	Char* c2 = new Char();
	Char* c3 = new Char();
	
	c1->assign((unichar)(i * (s2+1) + j + (int)'A'));
	c2->assign((unichar)(i * (s2+1) + j + (int)'A'));
	c3->assign((unichar)(i * (s2+1) + j + (int)'a'));
	
	temp->add(c1);
	
	t1->add(c2);
	t2->add(c3);
      }
      
      write_char_queue_queue.add(temp);
      wc_ss_0->add(t1);
      wc_ss_1->add(t2);
    }
    
    // 10 channel vector data
    //
    s1 = 3;
    s2 = 20;
    
    write_char_sss.add(wc_ss_0);
    write_char_sss.add(wc_ss_1);
    
    // write the values
    //
    write_char_queue.write(text_file, (int32)0);
    write_char_queue.write(bin_file, (int32)0);  
    
    write_str_queue.write(text_file, (int32)0);
    write_str_queue.write(bin_file, (int32)0);  
    
    write_char_queue_queue.write(text_file, (int32)0);
    write_char_queue_queue.write(bin_file, (int32)0);  
    
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
    if (!read_char_queue_text.read(text_file, (int32)0) ||
	(read_char_queue_text.ne(write_char_queue))) {
      return Error::handle(name(), L"read char text", Error::TEST, __FILE__,
			   __LINE__);
    }
    
    if (!read_str_queue_text.read(text_file, (int32)0) ||
	(read_str_queue_text.ne(write_str_queue))) {
      return Error::handle(name(), L"read str text", Error::TEST, __FILE__, 
			   __LINE__);
    }
    
    if (!read_char_queue_bin.read(bin_file, (int32)0) ||
	(read_char_queue_bin.ne(write_char_queue))) {
      return Error::handle(name(), L"write char bin", Error::TEST, __FILE__,
			   __LINE__);
    }
    
    if (!read_str_queue_bin.read(bin_file, (int32)0) ||
	(read_str_queue_bin.ne(write_str_queue))) {
      return Error::handle(name(), L"write str bin", Error::TEST, __FILE__,
			   __LINE__);
    }
    
    if (!read_char_queue_queue_text.read(text_file, (int32)0) ||
	(read_char_queue_queue_text.ne(write_char_queue_queue))) {
      return Error::handle(name(), L"read chr chr text", Error::TEST,
			   __FILE__, __LINE__);
    }
    
    if (!read_char_queue_queue_bin.read(bin_file, (int32)0) ||
	(read_char_queue_queue_bin.ne(write_char_queue_queue))) {
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
    
    // cleanup the memory that was created by the Queue read
    //
    read_char_queue_text.clear(Integral::FREE);
    read_char_queue_bin.clear(Integral::FREE);
    read_str_queue_text.clear(Integral::FREE);
    read_str_queue_bin.clear(Integral::FREE);
    
    // delete things from the nested queues
    //
    Queue<Char>* temp_queue2;
    
    while ((temp_queue2 = write_char_queue_queue.remove())
	  != (Queue<Char>*)NULL) {
      
      Char* temp_char;
      
      while ((temp_char = temp_queue2->remove()) != (Char*) NULL) {
	delete temp_char;
      }
      delete temp_queue2;
    }
    
    while ((temp_queue2 = read_char_queue_queue_bin.remove())
	  != (Queue<Char>*)NULL) {
      Char temp_char1;
      while ((temp_queue2->remove(&temp_char1)) != (Char*)NULL) {
      }
      delete temp_queue2;
    }
    
    while ((temp_queue2 = read_char_queue_queue_text.remove())
	  != (Queue<Char>*)NULL) {
      Char temp_char1;
      while ((temp_queue2->remove(&temp_char1)) != (Char*)NULL) {
      }
      delete temp_queue2;
    }      
    
    // delete things from the triple-nested queues
    //
    Queue< Queue<Char> >* temp_ss;
    
    while ((temp_ss = write_char_sss.remove())
	  != (Queue< Queue<Char> >*)NULL) {
      
      Queue<Char>* temp_s;
      
      while ((temp_s = temp_ss->remove()) != (Queue<Char>*)NULL) {
	
	Char* temp_char;
	
	while ((temp_char = temp_s->remove()) != (Char*)NULL) {
	  delete temp_char;
	}
	delete temp_s;
      }
      delete temp_ss;
    }
    
    while ((temp_ss = read_char_sss_text.remove())
	  != (Queue< Queue<Char> >*)NULL) {
      temp_ss->setAllocationMode(DstrBase::USER);
      Queue<Char>* temp_s;
      
      while ((temp_s = temp_ss->remove()) != (Queue<Char>*)NULL) {
	temp_s->setAllocationMode(DstrBase::USER);
	Char* temp_char;
	
	while ((temp_char = temp_s->remove()) != (Char*)NULL) {
	  delete temp_char;
	}
	delete temp_s;
      }
      delete temp_ss;
    }
    
    while ((temp_ss = read_char_sss_bin.remove())
	  != (Queue< Queue<Char> >*)NULL) {
      temp_ss->setAllocationMode(DstrBase::USER);
      Queue<Char>* temp_s;
      
      while ((temp_s = temp_ss->remove()) != (Queue<Char>*)NULL) {
	temp_s->setAllocationMode(DstrBase::USER);
	Char* temp_char;
	
	while ((temp_char = temp_s->remove()) != (Char*)NULL) {
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
  //  extensions to required methods
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
  Queue<Char>* char_queue = new Queue<Char>;
  
  Char* characters = new Char[500];
  unichar temp_char = L'a';
  Char* tmp_char_ptr = new Char();
  
  // initialize the characters and store them in the queues
  //
  for (int32 i = 0; i < 500; i++) {
    
    characters[i].assign(temp_char);
    
    // add the character to the queue
    //
    char_queue->add(&characters[i]);
    
    // increment the character value
    //
    temp_char++;
  }
  
  // copy this queue over
  //
  Queue<Char>* char_copy_queue = new Queue<Char>;
  char_copy_queue->assign(*char_queue);
  
  // both queues should be the same
  //
  if (!char_queue->eq(*char_copy_queue)) {
    return Error::handle(name(), L"eq", Error::TEST, __FILE__,
			 __LINE__);
  }
  
  if (char_queue->ne(*char_copy_queue)) {
    return Error::handle(name(), L"ne", Error::TEST, __FILE__,
			 __LINE__);
  }
  
  // now test that ne() works
  //
  char_queue->remove(tmp_char_ptr);
  
  // the queues should be different now.
  //
  // both queues should be the same
  //
  if (char_queue->eq(*char_copy_queue)) {
    return Error::handle(name(), L"eq", Error::TEST, __FILE__,
			 __LINE__);
  }
  
  if (!char_queue->ne(*char_copy_queue)) {
    return Error::handle(name(), L"ne", Error::TEST, __FILE__,
			 __LINE__);
  }
  
  // clean up memory
  //
  delete char_queue;
  delete char_copy_queue;
  delete [] characters;
  
  {
    // test equality methods for self-allocation mode
    //
    Queue<Char>* char_queue = new Queue<Char>(DstrBase::USER);
    
    Char* characters = new Char[500];
    unichar temp_char = L'a';
    
    // initialize the characters and store them in the queues
    //
    for (int32 i = 0; i < 500; i++) {
      
      characters[i].assign(temp_char);
      
      // add the character to the queue
      //
      char_queue->add(&characters[i]);
      
      // increment the character value
      //
      temp_char++;
    }
    
    // copy this queue over
    //
    Queue<Char>* char_copy_queue = new Queue<Char>(DstrBase::USER);
    char_copy_queue->assign(*char_queue);
    
    // both queues should be the same
    //
    if (!char_queue->eq(*char_copy_queue)) {
      return Error::handle(name(), L"eq", Error::TEST, __FILE__,
			   __LINE__);
    }
    
    if (char_queue->ne(*char_copy_queue)) {
      return Error::handle(name(), L"ne", Error::TEST, __FILE__,
			   __LINE__);
    }
    
    // now test that ne() works
    //
    char_queue->remove();
    
    // the queues should be different now.
    //
    // both queues should be the same
    //
    if (char_queue->eq(*char_copy_queue)) {
      return Error::handle(name(), L"eq", Error::TEST, __FILE__,
			   __LINE__);
    }
    
    if (!char_queue->ne(*char_copy_queue)) {
      return Error::handle(name(), L"ne", Error::TEST, __FILE__,
			   __LINE__);
    }
    
    // clean up memory
    //
    delete char_queue;
    delete char_copy_queue;
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
  //  queue add and remove methods
  //
  //--------------------------------------------------------------------------
  
  // set indentation
  //
  if (level_a > Integral::NONE) {
    Console::put(L"testing class-specific public methods: queue add and remove methods...\n");
    Console::increaseIndention();
  }
  
  // test add, remove, peek and marking methods for self-allocation mode
  //
  Queue<Char> pos_queue_1;
  Queue<Char> pos_queue_2;
  Queue<Char> pos_queue_3;
  Queue<Char> pos_queue_4;
  Queue<Char> temp_clear_queue;
  
  // test the various "add" methods in self-allocation mode
  //  populate the first queue with all of the letters from 'a' - 'n' in
  //  reverse order, marking the 'i'
  //
  for (int32 i = 0; i < 9; i++) {
    pos_queue_1.add(items[i]);
  }
  pos_queue_1.setMark();
  for (int32 i = 9; i < 14; i++) {
    pos_queue_1.add(items[i]);
  }
  
  // make sure that the top element is the 'a'
  //
  if (*pos_queue_1.peek() != *items[0]) {
    return Error::handle(name(), L"add", Error::TEST, __FILE__,
			 __LINE__);
  }
  
  // make sure that the mark is set
  //
  if (!pos_queue_1.markIsSet()) {
    return Error::handle(name(), L"setMark/markIsSet", Error::TEST, __FILE__,
			 __LINE__);
  }
  
  // populate the second queue with the entire alphabet
  //
  pos_queue_2.add(items, num_elem);
  
  // populate the third queue with all alphabets as well, but copied from
  // the second queue
  //
  pos_queue_3.add(pos_queue_2);
  
  // make sure that the second and third queue are the same
  //
  if (!pos_queue_2.eq(pos_queue_3)) {
    return Error::handle(name(), L"add", Error::TEST, __FILE__,
			 __LINE__);
  }

  // remove the first queue to the mark - it should now have 'i' - 'n' on it
  //
  pos_queue_1.removeToMark(temp_clear_queue);

  // make sure the top item is the marked item
  //
  if (!(pos_queue_1.markIsSet() && pos_queue_1.isMarkedElement())) {
    pos_queue_1.debug(L"pos_queue_1");
    return Error::handle(name(), L"isMarkedElement", Error::TEST, __FILE__,
			 __LINE__);
  }
  
  // make sure the top item is the 'i'
  //
  if (*pos_queue_1.peek() != *items[8]) {
    return Error::handle(name(), L"removeToMark", Error::TEST, __FILE__,
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
  //  queue marker positioning methods
  //
  //--------------------------------------------------------------------------
  
  // set indentation
  //
  if (level_a > Integral::NONE) {
    Console::put(L"testing class-specific public methods: queue marker positioning methods...\n");
    Console::increaseIndention();
  }
  
  // make sure the clearMark method works
  //
  pos_queue_1.clearMark();
  if (pos_queue_1.markIsSet() || pos_queue_1.isMarkedElement()) {
    return Error::handle(name(), L"clearMark", Error::TEST, __FILE__,
			 __LINE__);
  }
  
  // mark the item again, the 'n' is marked
  //
  pos_queue_1.setMark();
  
  // the second queue currently holds 'a' - 'z'. remove until we reach the 'r'
  // add the items removed onto the fourth queue
  //
  while ((pos_queue_2.peek())->ne(*items[18])) {
    pos_queue_2.remove(tmp_char_ptr);
    pos_queue_4.add(tmp_char_ptr);
  }
  
  // the second queue now holds 'r' - 'z' and the fourth queue now holds
  // 'a' - 'q'. remove the fourth queue so that it holds 'j' - 'q'
  //
  pos_queue_4.remove(temp_clear_queue, 9);
  
  // now the first queue holds 'i' - 'n', the second queue holds 's' - 'z',
  // the third queue holds 'a' - 'z' and the fourth holds 'j' - 'q'.
  //
  
  // call removeAll to put all items from the third queue onto the temp queue
  //
  pos_queue_3.removeAll(temp_clear_queue);
  
  // reset indentation
  //
  if (level_a > Integral::NONE) {
    Console::decreaseIndention();
  }

  //--------------------------------------------------------------------------
  //
  // 5. class-specific public methods:
  //  queue property methods
  //
  //--------------------------------------------------------------------------
  
  // set indentation
  //
  if (level_a > Integral::NONE) {
    Console::put(L"testing class-specific public methods: queue property methods...\n");
    Console::increaseIndention();
  }
  
  // make sure the third queue is empty
  //
  if (!pos_queue_3.isEmpty()) {
    return Error::handle(name(), L"removeAll", Error::TEST, __FILE__,
			 __LINE__);
  }
  
  // now remove elements off of the temp queue until we reach the 'p'
  //
  while ((temp_clear_queue.peek())->ne(*items[15])) {
    temp_clear_queue.remove(tmp_char_ptr);
  }
  
  // remove the 'p' from the temp queue and add to the third queue
  //
  temp_clear_queue.remove(pos_queue_3, 1);
  
  // now the first queue should have an 'i' at the top, the second queue
  // should have a 's' at the top, the third queue should have a 'p' at the
  // top, and the fourth queue should have a 'j' at the top. 
  //
  if (pos_queue_1.peek()->ne(*items[8]) || pos_queue_1.length() != 6) {
    return Error::handle(name(), L"add/remove/mark methods failed",
			 Error::TEST, __FILE__, __LINE__);
  }
  
  if (pos_queue_2.peek()->ne(*items[18]) || pos_queue_2.length() != 8) {
    return Error::handle(name(), L"add/remove/mark methods failed",
			 Error::TEST, __FILE__, __LINE__);
  }
  
  if (pos_queue_3.peek()->ne(*items[15]) || pos_queue_3.length() != 1) {
    return Error::handle(name(), L"add/remove/mark methods failed",
			 Error::TEST, __FILE__, __LINE__);
  }
  
  if (pos_queue_4.peek()->ne(*items[9]) || pos_queue_4.length() != 9) {
    return Error::handle(name(), L"add/remove/mark methods failed",
			 Error::TEST, __FILE__, __LINE__);
  }
  
  {
    // test add, remove, peek and marking methods for reference mode
    //
    Queue<Char> pos_queue_1(DstrBase::USER);
    Queue<Char> pos_queue_2(DstrBase::USER);
    Queue<Char> pos_queue_3(DstrBase::USER);
    Queue<Char> pos_queue_4(DstrBase::USER);
    Queue<Char> temp_clear_queue(DstrBase::USER);
    
    // test the various "add" methods in self-allocation mode
    //  populate the first queue with all of the letters from 'a' - 'n' in
    //  reverse order, marking the 'i'
    //
    for (int32 i = 0; i < 9; i++) {
      pos_queue_1.add(items[i]);
    }
    pos_queue_1.setMark();
    for (int32 i = 9; i < 14; i++) {
      pos_queue_1.add(items[i]);
    }
    
    // make sure that the top element is the 'a'
    //
    if (pos_queue_1.peek() != items[0]) {
      return Error::handle(name(), L"add", Error::TEST, __FILE__,
			   __LINE__);
    }
    
    // make sure that the mark is set
    //
    if (!pos_queue_1.markIsSet()) {
      return Error::handle(name(), L"setMark/markIsSet", Error::TEST, __FILE__,
			   __LINE__);
    }
    
    // populate the second queue with the entire alphabet
    //
    pos_queue_2.add(items, num_elem);
    
    // populate the third queue with all alphabets as well, but copied from
    // the second queue
    //
    pos_queue_3.add(pos_queue_2);
    
    // make sure that the second and third queue are the same
    //
    if (!pos_queue_2.eq(pos_queue_3)) {
      return Error::handle(name(), L"add", Error::TEST, __FILE__,
			   __LINE__);
    }
    
    // remove the first queue to the mark - it should now have 'i' - 'n' on it
    //
    pos_queue_1.removeToMark(temp_clear_queue);
    
    // make sure the top item is the marked item
    //
    if (!(pos_queue_1.markIsSet() && pos_queue_1.isMarkedElement())) {
      return Error::handle(name(), L"isMarkedElement", Error::TEST, __FILE__,
			   __LINE__);
    }
    
    // make sure the top item is the 'i'
    //
    if (pos_queue_1.peek() != items[8]) {
      return Error::handle(name(), L"removeToMark", Error::TEST, __FILE__,
			   __LINE__);
    }
    
    // make sure the clearMark method works
    //
    pos_queue_1.clearMark();
    if (pos_queue_1.markIsSet() || pos_queue_1.isMarkedElement()) {
      return Error::handle(name(), L"clearMark", Error::TEST, __FILE__,
			   __LINE__);
    }
    
    // mark the item again, the 'n' is marked
    //
    pos_queue_1.setMark();
    
    // the second queue currently holds 'a' - 'z'. remove until we reach the 'r'
    // add the items removed onto the fourth queue
    //
    while ((pos_queue_2.peek())->ne(*items[18])) {
      Char* tmp_char_ptr2;
      tmp_char_ptr2 = pos_queue_2.remove();
      pos_queue_4.add(tmp_char_ptr2);
    }
    
    // the second queue now holds 'r' - 'z' and the fourth queue now holds
    // 'a' - 'q'. remove the fourth queue so that it holds 'j' - 'q'
    //
    pos_queue_4.remove(temp_clear_queue, 9);
    
    // now the first queue holds 'i' - 'n', the second queue holds 's' - 'z',
    // the third queue holds 'a' - 'z' and the fourth holds 'j' - 'q'.
    //
    
    // call removeAll to put all items from the third queue onto the temp queue
    //
    pos_queue_3.removeAll(temp_clear_queue);
    
    // make sure the third queue is empty
    //
    if (!pos_queue_3.isEmpty()) {
      return Error::handle(name(), L"removeAll", Error::TEST, __FILE__,
			   __LINE__);
    }
    
    // now remove elements off of the temp queue until we reach the 'p'
    //
    while ((temp_clear_queue.peek())->ne(*items[15])) {
      temp_clear_queue.remove();
    }
    
    // remove the 'p' from the temp queue and add to the third queue
    //
    temp_clear_queue.remove(pos_queue_3, 1);
    
    // now the first queue should have an 'i' at the top, the second queue
    // should have a 's' at the top, the third queue should have a 'p' at the
    // top, and the fourth queue should have a 'j' at the top. 
    //
    if (pos_queue_1.peek()->ne(*items[8]) || pos_queue_1.length() != 6) {
      return Error::handle(name(), L"add/remove/mark methods failed",
			   Error::TEST, __FILE__, __LINE__);
    }
    
    if (pos_queue_2.peek()->ne(*items[18]) || pos_queue_2.length() != 8) {
      return Error::handle(name(), L"add/remove/mark methods failed",
			   Error::TEST, __FILE__, __LINE__);
    }
    
    if (pos_queue_3.peek()->ne(*items[15]) || pos_queue_3.length() != 1) {
      return Error::handle(name(), L"add/remove/mark methods failed",
			   Error::TEST, __FILE__, __LINE__);
    }
    
    if (pos_queue_4.peek()->ne(*items[9]) || pos_queue_4.length() != 9) {
      return Error::handle(name(), L"add/remove/mark methods failed",
			   Error::TEST, __FILE__, __LINE__);
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
  //  queue computation methods
  //
  //--------------------------------------------------------------------------
  
  // set indentation
  //
  if (level_a > Integral::NONE) {
    Console::put(L"testing class-specific public methods: queue computation methods...\n");
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
  
  // initialize queues and Char objects to use for testing
  //
  Queue<Char> char_queue_1;
  Queue<Char> char_queue_2;
  Queue<Char> char_queue_3;
  Queue<Char> char_queue_4;
  Queue<Char> temp_queue;
  
  // add all of the lower case characters to the first queue 'a' - 'z'
  //
  char_queue_1.add(low_chars, num_elem);
  
  // create an upper case version of these in the second queue 'A' - 'Z'
  //
  char_queue_2.add(up_chars, num_elem);
  char_queue_2.apply(&Char::toUpper);
  
  // add all of the lower case elements to the third queue and upcase them
  // 'A' - 'Z'
  //
  char_queue_3.apply(&Char::toUpper, char_queue_1);
  
  // the third queue should be the same as the second queue now
  //
  if (char_queue_2.ne(char_queue_3)) {
    return Error::handle(name(), L"apply", Error::TEST, __FILE__,
			 __LINE__);
  }
  
  // create an upper case queue in reverse order in the fourth queue
  // 'Z' - 'A'
  //
  for (int32 i = 0; i < num_elem; i++) {
    char_queue_4.add(items[num_elem - i - 1]);
  }
  char_queue_4.apply(&Char::toUpper);
  
  // reverse the order of the third queue 
  //
  char_queue_3.reverse();
  
  // the third queue should be the same as the fourth queue now
  //
  if (char_queue_3.ne(char_queue_4)) {
    return Error::handle(name(), L"reverseElement", Error::TEST, __FILE__,
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
  //  queue element ordering methods
  //
  //--------------------------------------------------------------------------
  
  // set indentation
  //
  if (level_a > Integral::NONE) {
    Console::put(L"testing class-specific public methods: queue element ordering methods...\n");
    Console::increaseIndention();
  }
  
  // sort
  //
  char_queue_3.sort();
  char_queue_4.sort(Integral::ASCENDING, Queue<Char>::INSERTION);
  
  // all these three queues should be 'A' to 'Z'
  //
  if (char_queue_3.ne(char_queue_2) || char_queue_4.ne(char_queue_2)) {
    return Error::handle(name(), L"sort", Error::TEST, __FILE__,
			 __LINE__);
  }
  
  // see if the fourth queue contains the letter 'm'
  //
  char_queue_4.apply(&Char::toLower);
  if (!char_queue_4.contains(items[12])) {
    return Error::handle(name(), L"contains", Error::TEST, __FILE__,
			 __LINE__);
  }
  
  // make sure that 'A' is the current item
  //
  if (char_queue_4.peek()->ne(*items[0])) {
    return Error::handle(name(), L"contains", Error::TEST, __FILE__,
			 __LINE__);
  }
  
  // test the find method
  //
  if (!char_queue_4.find(items[12])) {
    return Error::handle(name(), L"find", Error::TEST, __FILE__,
			 __LINE__);
  }

  // make sure that items[12] is marked
  //
  if (char_queue_4.getMark()->ne(*items[12])) {
    return Error::handle(name(), L"find", Error::TEST, __FILE__,
			 __LINE__);
  }
  
  {
    // testing the sort/apply/reverse methods for self-allocation mode
    //
    Queue<Char> char_queue_1(DstrBase::USER);
    Queue<Char> char_queue_2(DstrBase::USER);
    Queue<Char> char_queue_3(DstrBase::USER);
    Queue<Char> char_queue_4(DstrBase::USER);
    Queue<Char> temp_queue(DstrBase::USER);
    
    // add all of the lower case characters to the first queue 'a' - 'z'
    //
    char_queue_1.add(low_chars, num_elem);
    
    // create an upper case version of these in the second queue 'A' - 'Z'
    //
    char_queue_2.add(up_chars, num_elem);
    char_queue_2.apply(&Char::toUpper);
    
    // add all of the lower case elements to the third queue and upcase them
    // 'A' - 'Z'
    //
    char_queue_3.apply(&Char::toUpper, char_queue_1);
    
    // the third queue should be the same as the second queue now
    //
    if (char_queue_2.ne(char_queue_3)) {
      return Error::handle(name(), L"apply", Error::TEST, __FILE__,
			   __LINE__);
    }
    
    // create an upper case queue in reverse order in the fourth queue
    // 'Z' - 'A'
    //
    for (int32 i = 0; i < num_elem; i++) {
      char_queue_4.add(items[num_elem - i - 1]);
    }
    char_queue_4.apply(&Char::toUpper);
    
    // reverse the order of the third queue 
    //
    char_queue_3.reverse();
    
    // the third queue should be the same as the fourth queue now
    //
    if (char_queue_3.ne(char_queue_4)) {
      return Error::handle(name(), L"reverseElement", Error::TEST, __FILE__,
			   __LINE__);
    }
    
    // sort
    //
    char_queue_3.sort();
    char_queue_4.sort(Integral::ASCENDING, Queue<Char>::INSERTION);
    
    // all these three queues should be 'A' to 'Z'
    //
    if (char_queue_3.ne(char_queue_2) || char_queue_4.ne(char_queue_2)) {
      return Error::handle(name(), L"sort", Error::TEST, __FILE__,
			   __LINE__);
    }
    
    // see if the fourth queue contains the letter 'm'
    //
    char_queue_4.apply(&Char::toLower);
    if (!char_queue_4.contains(items[12])) {
      return Error::handle(name(), L"contains", Error::TEST, __FILE__,
			   __LINE__);
    }
    
    // make sure that 'A' is the current item
    //
    if (char_queue_4.peek()->ne(*items[0])) {
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
