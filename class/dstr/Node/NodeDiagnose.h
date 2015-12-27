// file: $isip/class/dstr/Node/NodeDiagnose.h
// version: $Id: NodeDiagnose.h 10636 2007-01-26 22:18:09Z tm334 $
//

// make sure definitions are only made once
//
#ifndef ISIP_NODE_DIAGNOSE
#define ISIP_NODE_DIAGNOSE

// isip include files
//
#ifndef ISIP_NODE
#include "Node.h"
#endif

// NodeDiagnose: a class that contains the diagnose method of Node class.
//
template<class TObject>
class NodeDiagnose : public Node<TObject> {

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

  // methods: name
  //
  static const String& name() {
    return Node<TObject>::name();
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

// below are all the methods for the NodeDiagnose template class
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
bool8 NodeDiagnose<TObject>::diagnose(Integral::DEBUG level_a) {
    
  //---------------------------------------------------------------------------
  //
  // 0. preliminaries
  //
  //---------------------------------------------------------------------------

  // output the class name
  //
  if (level_a > Integral::NONE) {
    SysString output(L"diagnosing class ");
    output.concat(name());
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

  // test destructor/constructor(s):
  //
  Node<TObject> def_node;		// default constructor
  TObject item;
  def_node.assign(&item);

  Node<TObject> copy_node(def_node);	// copy constructor
  Node<TObject> assign_node(&item);	// assignment constructor

  // all of the constructed nodes should contain the same item now
  //
  if ((def_node.item_d != copy_node.item_d) ||
      (def_node.item_d != assign_node.item_d) ||
      (copy_node.item_d != assign_node.item_d)) {
    return Error::handle(name(), L"constructors", Error::TEST, __FILE__,
			 __LINE__);
  }

  // test memory-management methods:
  //  set the memory to a strange block size so we can hopefully catch any
  //  frame overrun errors
  //
  Node<TObject>::setGrowSize((int32)31);
  
  // loop for a large number of times creating and deleting a large number
  // of nodes at each loop.
  //
  for (int32 j = 1; j <= 20; j++) {
    Node<TObject>** nodes = new Node<TObject>*[j * 53];
    
    // create the nodes
    //
    for (int32 i = 0; i < j * 53; i++) {
      nodes[i] = new Node<TObject>;
    }
    
    // delete nodes
    //
    for (int32 i = (j * 53) - 1; i >= 0; i--) {
      delete nodes[i];
    }
    
    delete [] nodes;
  }
  
  // perform the same test using the new[] and delete [] operators
  //
  for (int32 j = 1; j <= 20; j++) {
    
    // allocate a large number of nodes
    //
    Node<TObject>* nodes = new Node<TObject>[j * 53];
    
    // clean up memory
    //
    delete [] nodes;
  }

  // test the debug method
  // 
  Node<Char> dbg_node;
  dbg_node.setDebug(Integral::ALL);
  if (dbg_node.debug_level_d != Integral::ALL) {
    return Error::handle(name(), L"setDebug", Error::TEST,
			 __FILE__, __LINE__);
  }

  dbg_node.setDebug(Integral::NONE);
  if (dbg_node.debug_level_d != Integral::NONE) {
    return Error::handle(name(), L"setDebug", Error::TEST,
			 __FILE__, __LINE__);
  }

  Node<TObject> debug_node;		// default constructor
  TObject debug_item;
  debug_node.assign(&debug_item);

  if (level_a > Integral::BRIEF) {
    debug_node.debug(L"debug");
  }

  // test assign methods:
  //  create some temporary objects and items
  //  
  TObject item0;
  TObject item1;
  
  Node<TObject>* tmp_node = new Node<TObject>();
  Node<TObject>* tmp_node_2 = new Node<TObject>;
  
  // try the item assign method
  //
  tmp_node->assign(&item1);
  tmp_node_2->assign(&item1);
  
  if (tmp_node->item_d->ne(item1) || tmp_node_2->item_d->ne(item1)
      || (tmp_node_2->item_d != &item1)) {
    return Error::handle(name(), L"assign", Error::TEST,
			 __FILE__, __LINE__);
  }

  // clean up
  //
  delete tmp_node;
  delete tmp_node_2;

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
  Node<Char> write_char_node(&write_char);
  String write_string(L"gfedcba");
  
  Node<String> write_str_node(&write_string);
  
  // create embedded nodes
  //
  Node<Node<Char > > write_char_nn(&write_char_node);
  Node<Node<Node<Char > > > write_char_nnn(&write_char_nn);
  Node<Node<String > > write_str_nn(&write_str_node);
  Node<Node<Node<String > > > write_str_nnn(&write_str_nn);

  // print the nodes
  //
  if (level_a >= Integral::ALL) {
    write_char_node.debug(L"write_char_node");
    write_str_node.debug(L"write_str_node");
    write_char_nn.debug(L"write_char_nn");
    write_str_nn.debug(L"write_str_nn");
    write_char_nnn.debug(L"write_char_nnn");
    write_str_nnn.debug(L"write_str_nnn");
  }
  
  // write the values
  //
  write_char_node.write(text_file, (int32)0);
  write_char_node.write(bin_file, (int32)0);  
  
  write_str_node.write(text_file, (int32)0);
  write_str_node.write(bin_file, (int32)0);  
  
  write_char_nn.write(text_file, (int32)0);
  write_char_nn.write(bin_file, (int32)0);  
  
  write_str_nn.write(text_file, (int32)0);
  write_str_nn.write(bin_file, (int32)0);  
  
  write_char_nnn.write(text_file, (int32)0);
  write_char_nnn.write(bin_file, (int32)0);  

  write_str_nnn.write(text_file, (int32)0);
  write_str_nnn.write(bin_file, (int32)0);  
  
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
  Node<Char> read_char_node_text;
  Node<Char> read_char_node_bin;
  Node<String> read_str_node_text;
  Node<String> read_str_node_bin;

  // create embedded nodes for reading
  //
  Node<Node<Char > > read_char_nn_text;
  Node<Node<Char > > read_char_nn_bin;
  Node<Node<String > > read_str_nn_text;
  Node<Node<String > > read_str_nn_bin;
  Node<Node<Node<Char > > > read_char_nnn_text;
  Node<Node<Node<Char > > > read_char_nnn_bin;
  Node<Node<Node<String > > > read_str_nnn_text;
  Node<Node<Node<String > > > read_str_nnn_bin;
  
  // read in the nodes and test for equivalence
  //
  if (!read_char_node_text.read(text_file, (int32)0) ||
      (read_char_node_text.ne(write_char_node))) {
    return Error::handle(name(), L"read", Error::TEST, __FILE__, __LINE__);
  }

  if (!read_char_node_bin.read(bin_file, (int32)0) ||
      (read_char_node_bin.ne(write_char_node))) {
    return Error::handle(name(), L"write", Error::TEST, __FILE__, __LINE__);
  }

  if (!read_str_node_text.read(text_file, (int32)0) ||
      (read_str_node_text.ne(write_str_node))) {
    return Error::handle(name(), L"read", Error::TEST, __FILE__, __LINE__);
  }

  if (!read_str_node_bin.read(bin_file, (int32)0) ||
      (read_str_node_bin.ne(write_str_node))) {
    return Error::handle(name(), L"write", Error::TEST, __FILE__, __LINE__);
  }

  if (!read_char_nn_text.read(text_file, (int32)0) ||
      (read_char_nn_text.ne(write_char_nn))) {
    return Error::handle(name(), L"read", Error::TEST, __FILE__, __LINE__);
  }

  if (!read_char_nn_bin.read(bin_file, (int32)0) ||
      (read_char_nn_bin.ne(write_char_nn))) {
    return Error::handle(name(), L"write", Error::TEST, __FILE__, __LINE__);
  }

  if (!read_str_nn_text.read(text_file, (int32)0) ||
      (read_str_nn_text.ne(write_str_nn))) {
    return Error::handle(name(), L"read", Error::TEST, __FILE__, __LINE__);
  }

  if (!read_str_nn_bin.read(bin_file, (int32)0) ||
      (read_str_nn_bin.ne(write_str_nn))) {
    return Error::handle(name(), L"write", Error::TEST, __FILE__, __LINE__);
  }

  if (!read_char_nnn_text.read(text_file, (int32)0) ||
      (read_char_nnn_text.ne(write_char_nnn))) {
    return Error::handle(name(), L"read", Error::TEST, __FILE__, __LINE__);
  }

  if (!read_char_nnn_bin.read(bin_file, (int32)0) ||
      (read_char_nnn_bin.ne(write_char_nnn))) {
    return Error::handle(name(), L"write", Error::TEST, __FILE__, __LINE__);
  }

  if (!read_str_nnn_text.read(text_file, (int32)0) ||
      (read_str_nnn_text.ne(write_str_nnn))) {
    return Error::handle(name(), L"read", Error::TEST, __FILE__, __LINE__);
  }

  if (!read_str_nnn_bin.read(bin_file, (int32)0) ||
      (read_str_nnn_bin.ne(write_str_nnn))) {
    return Error::handle(name(), L"write", Error::TEST, __FILE__, __LINE__);
  }

  // print the nodes out
  //
  if (level_a >= Integral::ALL) {
    read_char_node_text.debug(L"read_char_node_text");
    read_char_node_bin.debug(L"read_char_node_bin");
    read_str_node_text.debug(L"read_str_node_text");
    read_str_node_bin.debug(L"read_str_node_bin");

    read_char_nn_text.debug(L"read_char_nn_text");
    read_char_nn_bin.debug(L"read_char_nn_bin");
    read_str_nn_text.debug(L"read_str_nn_text");
    read_str_nn_bin.debug(L"read_str_nn_bin");

    read_char_nnn_text.debug(L"read_char_nnn_text");
    read_char_nnn_bin.debug(L"read_char_nnn_bin");
    read_str_nnn_text.debug(L"read_str_nnn_text");
    read_str_nnn_bin.debug(L"read_str_nnn_bin");
  }
  
  // close and delete the temporary files
  //
  text_file.close();
  bin_file.close();
  File::remove(text_filename);
  File::remove(bin_filename);

  // cleanup the memory that was created by the Node read
  //
  read_char_node_text.clear(Integral::FREE);
  read_char_node_bin.clear(Integral::FREE);
  read_str_node_text.clear(Integral::FREE);
  read_str_node_bin.clear(Integral::FREE);
    
  read_char_nn_text.clear(Integral::FREE);
  read_char_nn_bin.clear(Integral::FREE);
  read_str_nn_text.clear(Integral::FREE);
  read_str_nn_bin.clear(Integral::FREE);
    
  read_char_nnn_text.clear(Integral::FREE);
  read_char_nnn_bin.clear(Integral::FREE);
  read_str_nnn_text.clear(Integral::FREE);
  read_str_nnn_bin.clear(Integral::FREE);

  // test equality methods:
  //  allocate nodes and Char objects to use for testing
  //
  Node<Char> char_node_0;
  Node<Char> char_node_1;                 
  Node<Char> char_node_2; 
  
  Char character(L'a');
   
  // initialize the characters and store them in the nodes
  //
  char_node_0.setItem(&character);

  // copy the node
  //
  char_node_1.assign(char_node_0);
  char_node_2.assign(char_node_0);

  // char_node_1 and char_node_2 should be the same as the char_node_0
  //
  if (char_node_0.ne(char_node_1) || char_node_0.ne(char_node_2)) {
    return Error::handle(name(), L"ne", Error::TEST, __FILE__,
			 __LINE__);      
  }
  
  if (!char_node_0.eq(char_node_1) || !char_node_0.eq(char_node_2)) {
    return Error::handle(name(), L"eq", Error::TEST, __FILE__,
			 __LINE__);      
  }

  // test comparison functions for Char
  //
  Char charA(L'A');
  Char charB(L'B');
  char_node_0.assign(&charA);
  char_node_1.assign(&charB);

  if (!char_node_0.lt(char_node_1)) {
    return Error::handle(name(), L"lt", Error::TEST, __FILE__, __LINE__);
  }

  if (char_node_0.gt(char_node_1)) {
    return Error::handle(name(), L"gt", Error::TEST, __FILE__, __LINE__);
  }

  if (char_node_0.gt(char_node_0)) {
    return Error::handle(name(), L"gt", Error::TEST, __FILE__, __LINE__);
  }

  // reset indentation
  //
  if (level_a > Integral::NONE) {
    Console::decreaseIndention();
  }
  
  //--------------------------------------------------------------------------
  //
  // 2. class-specific public methods:
  //     item manipulation methods
  //
  //--------------------------------------------------------------------------

  // set indentation
  //
  if (level_a > Integral::NONE) {
    Console::put(L"testing class-specific public methods: item manipulation methods...\n");
    Console::increaseIndention();
  }

  // create a pool of objects
  //
  TObject* objects = new TObject[500];
  
  // create an array of nodes
  //
  Node<TObject>* nodes = new Node<TObject>[1000];

  // place the object in the node arrays in order
  //
  for (int32 i = 0; i < 500; i++) {
    if (!nodes[i].setItem(&objects[i]))
      return Error::handle(name(), L"setItem", Error::TEST, __FILE__,
			   __LINE__);
  }

  // now create the mirror of that in the second part of the node array
  //
  for (int32 i = 0; i < 500; i++) {
    if (!nodes[i + 500].setItem(nodes[500 - i - 1].getItem()))
      return Error::handle(name(), L"setItem", Error::TEST, __FILE__,
			   __LINE__);
  }
  
  // compare the items
  //
  for (int32 i = 0; i < 500; i++) {
    if ((nodes[i + 500].getItem())->ne(*nodes[500 - i - 1].getItem())) {
      return Error::handle(name(), L"getItem", Error::TEST, __FILE__,
			   __LINE__);
    }
  }

  // remove all the items without storing the removed pointer
  //
  for (int32 i = 0; i < 1000; i++) {
    
    // remove the items
    //
    if (!nodes[i].clear()) {
      return Error::handle(name(), L"clear", Error::TEST, __FILE__,
			   __LINE__);
    }
  }
  
  // now loop and make sure that all of the nodes contain NULL
  //
  for (int32 i = 0; i < 1000; i++) {
    if (nodes[i].getItem() != (TObject*)NULL) {
      return Error::handle(name(), L"clear", Error::TEST, __FILE__,
			   __LINE__);
    }
  }
  
  // clean up
  //
  delete [] objects;
  delete [] nodes;

  // test the clear method
  //
  TObject obj;
  Node<TObject> clear_node(&obj);
  
  clear_node.clear();
  
  if (clear_node.item_d != (TObject*)NULL) {
    return Error::handle(name(), L"clear", Error::TEST, __FILE__,
			 __LINE__);
  }

  // reset indentation
  //
  if (level_a > Integral::NONE) {
    Console::decreaseIndention();
  }

  //---------------------------------------------------------------------------
  //
  // 4. print completion message
  //
  //---------------------------------------------------------------------------

  // set indentation
  //
  if (level_a > Integral::NONE) {
    Console::put(L"testing class-specific public methods: high level item manipulation methods...\n");
    Console::increaseIndention();
  }

  // test accessByMode
  //
  Node<Char> foo;
  Char a(L'a');
  foo.setItem(&a);
  Char* char_ptr;
  Char b;
  
  char_ptr = foo.accessByMode(&b, DstrBase::SYSTEM);
  if ((char_ptr != &b) || (char_ptr == (Char*)NULL) || (char_ptr->ne(a))) {
    return Error::handle(name(), L"accessByMode", Error::TEST,
			 __FILE__, __LINE__);
  }
  
  char_ptr = foo.accessByMode((Char*)NULL, DstrBase::USER);
  if (char_ptr != &a) {
    return Error::handle(name(), L"accessByMode", Error::TEST,
			 __FILE__, __LINE__);
  }

  // test assignByMode
  //
  foo.assignByMode(&a, DstrBase::SYSTEM);
  if ((foo.getItem() == &a) || (foo.getItem() == (Char*)NULL)
      || (foo.getItem()->ne(a))) {
    return Error::handle(name(), L"assignByMode", Error::TEST, __FILE__,
			 __LINE__);
  }

  // normally the dstr code would do this, but for the test we have to
  // do it by hand
  //
  delete foo.getItem();
  
  foo.assignByMode(&a, DstrBase::USER);
  if (foo.getItem() != &a) {
    return Error::handle(name(), L"assignByMode", Error::TEST, __FILE__,
			 __LINE__);
  }
  
  // reset indentation
  //
  if (level_a > Integral::NONE) {
    Console::decreaseIndention();
  }

  //---------------------------------------------------------------------------
  //
  // 5. print completion message
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
