// file: $isip/class/shell/Filename/fn_02.cc
// version: $Id: fn_02.cc 9209 2003-06-15 03:41:40Z picone $
//

// isip include files
//
#include "Filename.h"
#include <String.h>
#include <Console.h>

// method: diagnose
//
// arguments:
//  Integral::DEBUG level: (input) debug level for diagnostics
//
// return: a bool8 value indicating status
//
bool8 Filename::diagnose(Integral::DEBUG level_a) {

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

  // test the debug methods
  //
  setDebug(level_a);
  
  if (level_a > Integral::BRIEF) {
    Filename tmp;
    tmp.debug(L"fn1");
  }

  // test constructors
  //
  Filename fn1(L"/isip/tools/index.html");
  Filename fn2(fn1);
  
  // test the i/o methods
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
  
  // write the values
  //
  fn1.write(tmp_file0, (int32)0);
  fn1.write(tmp_file1, (int32)0);

  fn2.write(tmp_file0, (int32)1);
  fn2.write(tmp_file1, (int32)1);

  // close the files
  //
  tmp_file0.close();
  tmp_file1.close();

  // open the files in read mode
  //
  tmp_file0.open(tmp_filename0);
  tmp_file1.open(tmp_filename1);

  // read the values back in
  //
  Filename val1;
  Filename val2;
 
  setDebug(Integral::NONE);
  
  if (!val1.read(tmp_file0, (int32)0) || (val1.ne(fn1))) {
    val1.debug(L"val1: read from text");
    return Error::handle(name(), L"read", Error::TEST, __FILE__, __LINE__);
  }
 
  val1.clear();
  
  if (!val1.read(tmp_file1, (int32)0) || (val1.ne(fn1))) {
    val1.debug(L"val1: read from binary");
    return Error::handle(name(), L"read", Error::TEST, __FILE__, __LINE__);
  }

  if (!val2.read(tmp_file0, (int32)1) || (val2.ne(fn2))) {
    val2.debug(L"val2: read from text");
    return Error::handle(name(), L"read", Error::TEST, __FILE__, __LINE__);
  }

  val2.clear();
  
  if (!val2.read(tmp_file1, (int32)1) || (val2.ne(fn2))) {
    val2.debug(L"val2: read from binary");
    return Error::handle(name(), L"read", Error::TEST, __FILE__, __LINE__);
  }

  // close and delete the temporary files
  //
  tmp_file0.close();
  tmp_file1.close();
  File::remove(tmp_filename0);
  File::remove(tmp_filename1);

  // reset indention
  //
  if (level_a > Integral::NONE) {
    Console::decreaseIndention();
  }
   
  //---------------------------------------------------------------------
  //
  // 2. class-specific methods:
  //     extensions to required methods
  //
  //---------------------------------------------------------------------

  // set indentation
  //
  if (level_a > Integral::NONE) {
    Console::put(L"testing class-specific methods: extensions to required methods...\n");
    Console::increaseIndention();
  }

  // test constructors
  //
  String cstr_str(L"/isip/tools/configure");
  Filename cstr_fn(cstr_str);

  if (!cstr_fn.eq(cstr_str)) {
    return Error::handle(name(), L"constructor", Error::TEST,
			 __FILE__, __LINE__);
  }
  
  // reset indention
  //
  if (level_a > Integral::NONE) {
    Console::decreaseIndention();
  }
   
  //---------------------------------------------------------------------
  //
  // 3. class-specific methods:
  //     filename parsing methods
  //
  //---------------------------------------------------------------------

  // set indentation
  //
  if (level_a > Integral::NONE) {
    Console::put(L"testing class-specific methods: filename parsing methods...\n");
    Console::increaseIndention();
  }

  // test transform methods
  //
  String new_dir;
  String new_ext;
  String new_suffix;
  String old_name;
  
  fn1.assign(L"fn_cstr_00.cc");
  if (level_a > Integral::BRIEF) {
    fn1.debug(L"fn1");
  }

  new_dir.assign(L"/u0/srivasta/");
  new_ext.assign(L"c");
  
  fn1.transform(new_dir, new_ext, new_suffix);
  if (fn1.ne(L"/u0/srivasta/fn_cstr_00.c")) {
    fn1.debug(L"transform");
    Error::handle(name(), L"transform", Error::TEST, __FILE__, __LINE__);
  }

  new_dir.assign(L"/u0/srivasta");
  new_ext.assign(L"c");
  
  fn1.transform(new_dir, new_ext, new_suffix);
  if (fn1.ne(L"/u0/srivasta/fn_cstr_00.c")) {
    fn1.debug(L"transform");
    Error::handle(name(), L"transform", Error::TEST, __FILE__, __LINE__);
  }

  old_name.assign(L"/tools/fn_xx_00.cc");
  if (level_a > Integral::BRIEF) {
    fn1.debug(L"fn1");
  }
  
  Filename fn;
  fn.transform(old_name, new_dir, new_ext, new_suffix);

  if (fn.ne(L"/u0/srivasta/fn_xx_00.c")) {
    fn.debug(L"transform");
    Error::handle(name(), L"transform", Error::TEST, __FILE__, __LINE__);
  }

  // test transform with partial preservation
  //
  fn1.assign(L"/isip/d00/tidigits/data/raw_8k/test/ah/foo.raw");
  new_dir.assign(L"/u2/duncan/data");
  new_ext.assign(L"sof");
  fn2.transform(fn1, new_dir, new_ext, new_suffix);
    
  if (fn2.ne(L"/u2/duncan/data/foo.sof")) {
    fn2.debug(L"fn2");
    return Error::handle(name(), L"transform", Error::TEST,
			 __FILE__, __LINE__);
  }
    
  fn2.transform(fn1, new_dir, new_ext, new_suffix, 1);
    
  if (fn2.ne(L"/u2/duncan/data/ah/foo.sof")) {
    fn2.debug(L"fn2");
    return Error::handle(name(), L"transform", Error::TEST,
			 __FILE__, __LINE__);
  }
    
  fn2.transform(fn1, new_dir, new_ext, new_suffix, 2);
  
  if (fn2.ne(L"/u2/duncan/data/test/ah/foo.sof")) {
    fn2.debug(L"fn2");
    return Error::handle(name(), L"transform", Error::TEST,
			 __FILE__, __LINE__);
  }
  
  fn2.transform(fn1, new_dir, new_ext, new_suffix, 3);
  
  if (fn2.ne(L"/u2/duncan/data/raw_8k/test/ah/foo.sof")) {
    fn2.debug(L"fn2");
    return Error::handle(name(), L"transform", Error::TEST,
			 __FILE__, __LINE__);
  }
  
  fn2.transform(fn1, new_dir, new_ext, new_suffix, 6);
  
  if (fn2.ne(L"/u2/duncan/data/d00/tidigits/data/raw_8k/test/ah/foo.sof")) {
    fn2.debug(L"fn2");
    return Error::handle(name(), L"transform", Error::TEST,
			 __FILE__, __LINE__);
  }
  
  fn2.transform(fn1, new_dir, new_ext, new_suffix, 7);
  
  if (fn2.ne(L"/u2/duncan/data/isip/d00/tidigits/data/raw_8k/test/ah/foo.sof")) {
    fn2.debug(L"fn2");
    return Error::handle(name(), L"transform", Error::TEST,
			 __FILE__, __LINE__);
  }
  
  fn2.transform(fn1, new_dir, new_ext, new_suffix, 8);
  
  if (fn2.ne(L"/isip/d00/tidigits/data/raw_8k/test/ah/foo.sof")) {
    fn2.debug(L"fn2");
    return Error::handle(name(), L"transform", Error::TEST,
			 __FILE__, __LINE__);
  }
  
  fn2.assign(L"asdf.raw");
  fn2.transform(new_dir, new_ext, 2);
  
  if (fn2.ne(L"/u2/duncan/data/asdf.sof")) {
    fn2.debug(L"fn2");
    return Error::handle(name(), L"transform", Error::TEST,
			 __FILE__, __LINE__);
  }
  
  fn2.assign(L"asdf.raw");
  fn2.transform(new_dir, new_ext, new_suffix, 2);
  
  if (fn2.ne(L"/u2/duncan/data/asdf.sof")) {
    fn2.debug(L"fn2");
    return Error::handle(name(), L"transform", Error::TEST,
			 __FILE__, __LINE__);
  }
  
  fn2.assign(L"./asdf.raw");
  new_dir.clear();
  fn2.transform(new_dir, new_ext, new_suffix);
  
  if (fn2.ne(L"./asdf.sof")) {
    fn2.debug(L"fn2");
    return Error::handle(name(), L"transform", Error::TEST,
			 __FILE__, __LINE__);
  }
  
  fn2.assign(L"./asdf.raw");
  fn2.transform(new_dir, new_ext, 2);
  
  if (fn2.ne(L"./asdf.sof")) {
    fn2.debug(L"fn2");
    return Error::handle(name(), L"transform", Error::TEST,
			 __FILE__, __LINE__);
  }
  
  fn2.assign(L"asdf.raw");
  fn2.transform(new_dir, new_ext, 2);
  
  if (fn2.ne(L"asdf.sof")) {
    fn2.debug(L"fn2");
    return Error::handle(name(), L"transform", Error::TEST,
			 __FILE__, __LINE__);
  }

  // test transformUniquely methods
  //
  File foo;
  fn1.assign(L"Joe_test.sof");
  fn2.assign(fn1);
  foo.open(fn1, File::WRITE_ONLY);
  foo.close();
  fn2.transformUniquely();
  foo.remove(fn1);

  if (fn2.ne(L"Joe_test_0.sof")) {
    fn2.debug(L"transformedUniquely name");
    Error::handle(name(), L"transformUniquely",
		  Error::TEST, __FILE__, __LINE__);
  }
  
  // reset indention
  //
  if (level_a > Integral::NONE) {
    Console::decreaseIndention();
  }

  //------------------------------------------------------------------
  //
  // 4. class-specific public methods:
  //     replace methods
  //
  //------------------------------------------------------------------
  
  // set indentation
  //
  if (level_a > Integral::NONE) {
    Console::put(L"testing class-specific methods: replace methods...\n");
    Console::increaseIndention();
  }

  fn1.assign(L"/tools/fn_xx.cc");
  if (level_a > Integral::BRIEF) {
    fn1.debug(L"fn1");
  }

  String new_name;
  
  old_name.assign(L"fn_xx");
  new_name.assign(L"fn_xx_00");
  
  fn1.replace(old_name, new_name);
  if (fn1.ne(L"/tools/fn_xx_00.cc")) {
    fn1.debug(L"replace");
    Error::handle(name(), L"replace 1", Error::TEST, __FILE__, __LINE__);
  }

  fn1.assign(L"fn_xx.cc");
  if (level_a > Integral::BRIEF) {
    fn1.debug(L"fn1");
  }

  {
    Filename in_file_name;
    String new_file_name;
    in_file_name.assign(L"test.text");
    new_file_name.assign(in_file_name);
    bool8 file_name_changed = new_file_name.replace(L"$", L"");
    file_name_changed |= new_file_name.replace(L"?", L"-");
    if (file_name_changed) {
      return Error::handle(name(), L"replace", Error::TEST, __FILE__, __LINE__);
    }
  }
  
  // reset indention
  //
  if (level_a > Integral::NONE) {
    Console::decreaseIndention();
  }

  //------------------------------------------------------------------
  //
  // 5. class-specific public methods:
  //     get methods
  //
  //------------------------------------------------------------------

  // set indentation
  //
  if (level_a > Integral::NONE) {
    Console::put(L"testing class-specific methods: get methods...\n");
    Console::increaseIndention();
  }

  fn1.assign(L"/tools/Filename.h");
  if (level_a > Integral::BRIEF) {
    fn1.debug(L"fn1");
  }

  String base;
  String ext;
  String dir;
  String filename;
  
  fn1.getBase(base);
  if (base.ne(L"Filename")) {
    base.debug(L"base value");
    Error::handle(name(), L"getBase", Error::TEST, __FILE__, __LINE__);
  }

  fn1.getExt(ext);
  if (ext.ne(L"h")) {
    ext.debug(L"extension value");
    Error::handle(name(), L"getExt", Error::TEST, __FILE__, __LINE__);
  }

  fn1.getDir(dir);
  if (dir.ne(L"/tools")) {
    dir.debug(L"directory");
    Error::handle(name(), L"getDir", Error::TEST, __FILE__, __LINE__);
  }
  
  fn1.getName(filename);
  if (filename.ne(L"Filename.h")) {
    filename.debug(L"filename");
    Error::handle(name(), L"getName", Error::TEST, __FILE__, __LINE__);
  }

  // reset indention
  //
  if (level_a > Integral::NONE) {
    Console::decreaseIndention();
  }
  
  //------------------------------------------------------------------
  //
  // 6. class-specific public methods:
  //     temporary filename methods
  //
  //------------------------------------------------------------------

  // set indentation
  //
  if (level_a > Integral::NONE) {
    Console::put(L"testing class-specific methods: temporary filename methods...\n");
    Console::increaseIndention();
  }

  fn1.makeTemp();
  if (level_a > Integral::BRIEF) {
    fn1.debug(L"makeTemp");
  }

  String val;
  val.assign(L"file_XXXXXX");
  if (level_a > Integral::BRIEF) {
    fn2.makeTemp(val);
    fn2.debug(L"makeTemp");
  }

  // reset indention
  //
  if (level_a > Integral::NONE) {
    Console::decreaseIndention();
  }

  //------------------------------------------------------------------
  //
  // 7. class-specific public methods:
  //     buildpath methods
  //
  //------------------------------------------------------------------

  // set indentation
  //
  if (level_a > Integral::NONE) {
    Console::put(L"testing class-specific methods: buildpath methods...\n");
    Console::increaseIndention();
  }

  String new_file(L"/tmp/as/df/qwer/tyui/xcvb");
  if (!buildPath(new_file)) {
    return Error::handle(name(), L"buildPath", Error::TEST, __FILE__,
			 __LINE__);
  }

  if (!File::exists(L"/tmp/as/df/qwer/tyui/xcvb")) {
    return Error::handle(name(), L"buildPath", Error::TEST, __FILE__,
			 __LINE__);
  }

  if ((!File::rmdir(L"/tmp/as/df/qwer/tyui/xcvb"))
      || (!File::rmdir(L"/tmp/as/df/qwer/tyui"))
      || (!File::rmdir(L"/tmp/as/df/qwer"))
      || (!File::rmdir(L"/tmp/as/df"))
      || (!File::rmdir(L"/tmp/as"))) {
    return Error::handle(name(), L"rmdir", Error::IO, __FILE__, __LINE__);
  }

  // reset indention
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
  
  if (level_a > Integral::NONE) {
    String output(L"diagnostics passed for class ");
    output.concat(name());
    output.concat(L"\n");
    Console::put(output);
  }
  
  // exit gracefully
  //
  return true;
}
