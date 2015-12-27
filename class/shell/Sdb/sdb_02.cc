// file: $isip/class/shell/Sdb/sdb_02.cc
// version: $Id: sdb_02.cc 9209 2003-06-15 03:41:40Z picone $
//

// isip include files
//
#include "Sdb.h"
#include <Console.h>
#include <CommandLine.h>

// method: diagnose
//
// arguments:
//  Integral::DEBUG level: (input) debug level for diagnostics
//
// return: a bool8 value indicating status
//
bool8 Sdb::diagnose(Integral::DEBUG level_a) {

  //---------------------------------------------------------------------
  //
  // 0. preliminaries
  //
  //---------------------------------------------------------------------

  // output the class name
  //
  if (level_a > Integral::NONE) {
    String output(L"diagnosing class ");
    output.concat(CLASS_NAME);
    output.concat(L": ");
    Console::put(output);
    Console::increaseIndention();
  }

  //--------------------------------------------------------------------
  //
  // 1. required public methods
  //
  //--------------------------------------------------------------------

  // set indentation
  //
  if (level_a > Integral::NONE) {
    Console::put(L"testing required public methods...\n");
    Console::increaseIndention();
  }

  // test constructors
  //
  Sdb sdb;
  String input;
  Filename output;

  input.assign(L"   foo.raw");
  bool8 list = false;
  if ((!sdb.parse(output, list, input))
      || (!output.eq(L"foo.raw"))
      || (list)) {
    return Error::handle(name(), L"parse", Error::TEST, __FILE__, __LINE__);
  }

  
  output.clear();
  input.assign(L"foo.\\");
  if (sdb.parse(output, list, input)
      || (!output.eq(L"foo."))
      || (list)) {
    return Error::handle(name(), L"parse", Error::TEST, __FILE__, __LINE__);
  }

  input.assign(L"raw");
  if ((!sdb.parse(output, list, input))
      || (!output.eq(L"foo.raw"))
      || (list)) {
    return Error::handle(name(), L"parse", Error::TEST, __FILE__, __LINE__);
  }

  output.clear();
  input.assign(L"(list) foo.list");
  if ((!sdb.parse(output, list, input))
      || (!output.eq(L"foo.list"))
      || (!list)) {
    return Error::handle(name(), L"parse", Error::TEST, __FILE__, __LINE__);
  }

  output.clear();
  input.assign(L"(list) foo.\\");
  if ((sdb.parse(output, list, input)) || (!output.eq(L"(list) foo."))) {
    output.debug(L"output");
    return Error::handle(name(), L"parse", Error::TEST, __FILE__, __LINE__);
  }

  input.assign(L"list");
  if ((!sdb.parse(output, list, input))
      || (!output.eq(L"foo.list"))
      || (!list)) {
    return Error::handle(name(), L"parse", Error::TEST, __FILE__, __LINE__);
  }

  // test basic functionality
  //
  Sdb sdb1;
  Sdb sdb2;
  Sdb sdb3;
  Sdb sdb4;

  // append files
  //
  Filename file1[5];
  file1[0].assign(L"foo1.sof");
  sdb1.append(file1[0]);
  file1[1].assign(L"foo2.sof");
  sdb1.append(file1[1]);
  file1[2].assign(L"foo3.sof");
  sdb1.append(file1[2]);
  file1[3].assign(L"foo4.sof");
  sdb1.append(file1[3]);
  file1[4].assign(L"foo5.sof");
  sdb1.append(file1[4]);

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
  
  // write the values
  //
  sdb1.write(tmp_file0, (int32)0);
  sdb1.write(tmp_file1, (int32)0);

  // close the files
  //
  tmp_file0.close();
  tmp_file1.close();

  // now use the basic iterate method
  //
  Filename fn;
  sdb2.append(tmp_filename0, true);
  sdb2.lookahead_d = 2;
  
  if (!sdb2.gotoFirst()) {
    return Error::handle(name(), L"gotoFirst", Error::TEST, __FILE__,
			 __LINE__);
  }

  if ((!sdb2.getName(fn)) || (fn.ne(file1[0]))) {
    fn.debug(L"fn [0]");
    return Error::handle(name(), L"getName", Error::TEST, __FILE__, __LINE__);
  }

  if ((!sdb2.gotoNext()) || (!sdb2.getName(fn)) || (fn.ne(file1[1]))) {
    fn.debug(L"fn [1]");
    return Error::handle(name(), L"getName", Error::TEST, __FILE__, __LINE__);
  }

  if ((!sdb2.gotoNext()) || (!sdb2.getName(fn)) || (fn.ne(file1[2]))) {
    fn.debug(L"fn [2]");
    return Error::handle(name(), L"getName", Error::TEST, __FILE__, __LINE__);
  }

  if ((!sdb2.gotoNext()) || (!sdb2.getName(fn)) || (fn.ne(file1[3]))) {
    fn.debug(L"fn [3]");
    return Error::handle(name(), L"getName", Error::TEST, __FILE__, __LINE__);
  }

  if ((!sdb2.gotoNext()) || (!sdb2.getName(fn)) || (fn.ne(file1[4]))) {
    fn.debug(L"fn [4]");
    return Error::handle(name(), L"getName", Error::TEST, __FILE__, __LINE__);
  }

  if (!sdb2.gotoFirst()) {
    return Error::handle(name(), L"gotoFirst", Error::TEST, __FILE__,
			 __LINE__);
  }

  if ((!sdb2.getName(fn)) || (fn.ne(file1[0]))) {
    fn.debug(L"fn [0]");
    return Error::handle(name(), L"getName", Error::TEST, __FILE__, __LINE__);
  }

  if ((!sdb2.gotoNext()) || (!sdb2.getName(fn)) || (fn.ne(file1[1]))) {
    fn.debug(L"fn [1]");
    return Error::handle(name(), L"getName", Error::TEST, __FILE__, __LINE__);
  }

  if ((!sdb2.gotoNext()) || (!sdb2.getName(fn)) || (fn.ne(file1[2]))) {
    fn.debug(L"fn [2]");
    return Error::handle(name(), L"getName", Error::TEST, __FILE__, __LINE__);
  }

  if ((!sdb2.gotoNext()) || (!sdb2.getName(fn)) || (fn.ne(file1[3]))) {
    fn.debug(L"fn [3]");
    return Error::handle(name(), L"getName", Error::TEST, __FILE__, __LINE__);
  }

  if ((!sdb2.gotoNext()) || (!sdb2.getName(fn)) || (fn.ne(file1[4]))) {
    fn.debug(L"fn [4]");
    return Error::handle(name(), L"getName", Error::TEST, __FILE__, __LINE__);
  }

  if (sdb2.gotoNext()) {
    sdb2.getName(fn);
    fn.debug(L"fn");
    return Error::handle(name(), L"gotoNext", Error::TEST, __FILE__, __LINE__);
  }

  // open the files in read mode
  //
  tmp_file0.open(tmp_filename0);
  tmp_file1.open(tmp_filename1);

  // read the values back in
  //
  if (!sdb2.read(tmp_file0, (int32)0)) {
    return Error::handle(name(), L"read", Error::TEST, __FILE__, __LINE__);
  }
  
  if (!sdb3.read(tmp_file1, (int32)0)) {
    return Error::handle(name(), L"read", Error::TEST, __FILE__, __LINE__);
  }

  if (!sdb2.sameFiles(sdb1)) {
    sdb2.debug(L"sdb2");
    sdb1.debug(L"sdb1");
    return Error::handle(name(), L"read", Error::TEST, __FILE__, __LINE__);
  }

  if (!sdb3.sameFiles(sdb1)) {
    sdb3.debug(L"sdb3");
    sdb1.debug(L"sdb1");
    return Error::handle(name(), L"read", Error::TEST, __FILE__, __LINE__);
  }

  // close the files
  //
  tmp_file0.close();
  tmp_file1.close();

  // remove the files
  //
  File::remove(tmp_filename0);
  File::remove(tmp_filename1);

  // reset indentation
  //
  if (level_a > Integral::NONE) {
    Console::decreaseIndention();
  }

  //---------------------------------------------------------------------------
  //
  // 2. class-specific methods:
  //     append methods
  //
  //---------------------------------------------------------------------------

  // set indentation
  //
  if (level_a > Integral::NONE) {
    Console::put(L"testing class-specific methods: append methods...\n");
    Console::increaseIndention();
  }

  // test append methods
  //
  sdb.append(L"diagnose_main_list.sof", true);
  sdb.append(L"diagnose_file5.sof");
  Sdb sdb_ref;
  sdb_ref.append(L"diagnose_full_list.sof", true);

  if (!sdb.sameFiles(sdb_ref)) {
    sdb.debug(L"main_list");
    sdb_ref.debug(L"ref");
    return Error::handle(name(), L"append", Error::TEST, __FILE__, __LINE__);
  }

  String line(L"run_me.exe -list diagnose_file1.sof diagnose_file2.sof diagnose_file3.sof -list diagnose_file4.sof diagnose_file5.sof");

  CommandLine cmdl(sdb);
  cmdl.parse(line);

  if (!sdb.sameFiles(sdb_ref)) {
    sdb.debug(L"main_list");
    sdb_ref.debug(L"ref");
    return Error::handle(name(), L"append", Error::TEST, __FILE__, __LINE__);
  }
  
  // reset indentation
  //
  if (level_a > Integral::NONE) {
    Console::decreaseIndention();
  }

  //---------------------------------------------------------------------------
  //
  // 3. class-specific methods:
  //     file access and transformation methods
  //
  //---------------------------------------------------------------------------
  
  // set indentation
  //
  if (level_a > Integral::NONE) {
    Console::put(L"testing class-specific methods: file access and transformation methods...\n");
    Console::increaseIndention();
  }

  if (!sdb.gotoFirst()) {
    return Error::handle(name(), L"gotoFirst", Error::TEST,
			 __FILE__, __LINE__);
  }

  Filename tmp_name;

  if (!sdb.getName(tmp_name) ||
      !tmp_name.eq(L"diagnose_file10.sof")) {
    return Error::handle(name(), L"getName", Error::TEST,
			 __FILE__, __LINE__);
  }

  if (!sdb.gotoNext() || !sdb.getName(tmp_name) ||
      !tmp_name.eq(L"diagnose_file11.sof")) {
    return Error::handle(name(), L"getName", Error::TEST,
			 __FILE__, __LINE__);
  }

  if (!sdb.gotoNext() || !sdb.getName(tmp_name) ||
      !tmp_name.eq(L"diagnose_file12.sof")) {
    return Error::handle(name(), L"getName", Error::TEST,
			 __FILE__, __LINE__);
  }

  if (!sdb.gotoNext() || !sdb.getName(tmp_name) ||
      !tmp_name.eq(L"diagnose_file2.sof")) {
    return Error::handle(name(), L"getName", Error::TEST,
			 __FILE__, __LINE__);
  }

  if (!sdb.gotoNext() || !sdb.getName(tmp_name) ||
      !tmp_name.eq(L"diagnose_file3.sof")) {
    return Error::handle(name(), L"getName", Error::TEST,
			 __FILE__, __LINE__);
  }

  // skip over the big chunk of file
  //
  for (int32 i = 0; i < 26; i++) {
    if (!sdb.gotoNext()) {
      return Error::handle(name(), L"diagnose", Error::TEST,
			   __FILE__, __LINE__);
    }
  }
  
  if (!sdb.gotoNext() || ! sdb.getName(tmp_name) ||
      !tmp_name.eq(L"diagnose_file5.sof")) {
    tmp_name.debug(L"tmp_name");
    return Error::handle(name(), L"getName", Error::TEST,
			 __FILE__, __LINE__);
  }

  if (sdb.gotoNext()) {
    return Error::handle(name(), L"gotoNext", Error::TEST, __FILE__, __LINE__);
  }

  // test transformation of filenames
  //
  line.assign(L"run_me.exe -list diagnose_file1.sof diagnose_file2.sof diagnose_file3.sof diagnose_file5.raw");
  CommandLine cmdl0;
  cmdl0.setSdb(sdb);
  cmdl0.parse(line);

  // no output directory, existing sof extension -> transformUniquely
  //
  Filename out_name;
  Filename in_name;
  sdb.gotoFirst();
  sdb.getName(in_name);
  
  if (in_name.ne(L"diagnose_file10.sof") ||
      !sdb.transformName(out_name, in_name) ||
      out_name.ne(L"diagnose_file10_0.sof")) {
    in_name.debug(L"input");
    out_name.debug(L"transformed");
    sdb.debug(L"sdb");
    return Error::handle(name(), L"transformName", Error::TEST,
			 __FILE__, __LINE__);
  }

  sdb.gotoNext();   // file11
  sdb.gotoNext();   // file12
  sdb.gotoNext();   // file2
  sdb.gotoNext();   // file3
  sdb.gotoNext();
  
  // no output directory, existing non-sof extension -> use sof extension
  //
  sdb.getName(in_name);

  if (in_name.ne(L"diagnose_file5.raw") ||
      !sdb.transformName(out_name, in_name) ||
      out_name.ne(L"diagnose_file5.sof")) {
    in_name.debug(L"input");
    out_name.debug(L"transformed");
    return Error::handle(name(), L"transformName", Error::TEST,
			 __FILE__, __LINE__);
  }

  // now specify an output_directory
  //
  line.assign(L"run_me.exe -dir /tmp diagnose_file2.sof diagnose_file3.sof diagnose_file5.raw");
  CommandLine cmdl1;
  cmdl1.setSdb(sdb);
  cmdl1.parse(line);

  // with output directory, change directory
  //
  sdb.gotoFirst();
  sdb.getName(in_name);
  
  if (in_name.ne(L"diagnose_file2.sof") ||
      !sdb.transformName(out_name, in_name) ||
      out_name.ne(L"/tmp/diagnose_file2.sof")) {
    in_name.debug(L"input");
    out_name.debug(L"transformed");
    return Error::handle(name(), L"transformName", Error::TEST,
			 __FILE__, __LINE__);
  }

  sdb.gotoNext();
  sdb.gotoNext();
  sdb.getName(in_name);
  
  if (in_name.ne(L"diagnose_file5.raw") ||
      !sdb.transformName(out_name, in_name) ||
      out_name.ne(L"/tmp/diagnose_file5.sof")) {
    in_name.debug(L"input");
    out_name.debug(L"transformed");
    return Error::handle(name(), L"transformName", Error::TEST,
			 __FILE__, __LINE__);
  }

  in_name.assign(L"-");
  out_name.clear();
  if ((!sdb.transformName(out_name, in_name)) ||
      (out_name.ne(L"-"))) {
    return Error::handle(name(), L"diagnose", Error::TEST, __FILE__, __LINE__);
  }
  
  // reset indention
  //
  if (level_a > Integral::NONE) {
    Console::decreaseIndention();
  }
    
  //---------------------------------------------------------------------------
  //
  // 4. class-specific methods:
  //     binary file operations
  //
  //---------------------------------------------------------------------------

  // set indentation
  //
  if (level_a > Integral::NONE) {
    Console::put(L"testing class-specific methods: binary file methods...\n");
    Console::increaseIndention();
  }

  // we need to copy a few text files to binary sof files
  //
  Sof sof_text;
  Sof sof_bin;
  Filename file_dmlb(L"diagnose_main_list_bin.sof");
  Filename file_df4b(L"diagnose_file4_bin.sof");
  File::registerTemp(file_dmlb);
  File::registerTemp(file_df4b);
  sof_text.open(L"diagnose_main_list.sof");
  sof_bin.open(file_dmlb, File::WRITE_ONLY, File::BINARY);

  sdb1.read(sof_text, 0);

  // modify the list to point to the binary file4, not the text one
  //
  sdb1.files_d.gotoLast();
  sdb1.files_d.getCurr()->first().assign(file_df4b);

  sdb1.write(sof_bin, 0);

  sof_text.close();
  sof_bin.close();
  
  sof_text.open(L"diagnose_file4.sof");
  sof_bin.open(file_df4b, File::WRITE_ONLY, File::BINARY);

  sdb1.read(sof_text, 0);
  sdb1.write(sof_bin, 0);

  sdb1.read(sof_text, 1);
  sdb1.write(sof_bin, 1);

  sdb1.read(sof_text, 9);
  sdb1.write(sof_bin, 9);

  sof_text.close();
  sof_bin.close();

  // now that we have files created, perform the same test
  //
  sdb2.clear();
  sdb2.append(L"diagnose_main_list_bin.sof", true);
  sdb2.append(L"diagnose_file5.sof");

  if (!sdb2.sameFiles(sdb_ref)) {
    return Error::handle(name(), L"iterate", Error::TEST, __FILE__, __LINE__);
  }

  // also test from the command line
  //
  line.assign(L"run_me.exe -list diagnose_file1.sof diagnose_file2.sof diagnose_file3.sof -list diagnose_file4_bin.sof diagnose_file5.sof");
  cmdl.clear();
  cmdl.setSdb(sdb2);
  cmdl.parse(line);

  if (!sdb2.sameFiles(sdb_ref)) {
    sdb2.debug(L"main_list");
    sdb_ref.debug(L"ref");
    return Error::handle(name(), L"append", Error::TEST, __FILE__, __LINE__);
  }
  
  // reset indention
  //
  if (level_a > Integral::NONE) {
    Console::decreaseIndention();
  }

  //---------------------------------------------------------------------------
  //
  // 5. class-specific methods:
  //     test that an Sdb object can reference itself
  //
  //---------------------------------------------------------------------------

  // set indentation
  //
  if (level_a > Integral::NONE) {
    Console::put(L"testing class-specific methods: self-referencing file...\n");
    Console::increaseIndention();
  }

  // append our self-referencing file as a list
  //
  sdb2.clear();
  sdb2.append(L"diagnose_self.sof", true);

  if (!sdb2.getName(fn) || fn.ne(L"diagnose_self.sof")) {
    return Error::handle(name(), L"append", Error::TEST, __FILE__, __LINE__);
  }

  // also test from the command line
  //
  line.assign(L"run_me.exe -list diagnose_self.sof");
  cmdl.clear();
  cmdl.setSdb(sdb2);
  cmdl.parse(line);

  if (!sdb2.getName(fn) || fn.ne(L"diagnose_self.sof")) {
    return Error::handle(name(), L"append", Error::TEST, __FILE__, __LINE__);
  }
  
  // reset indention
  //
  if (level_a > Integral::NONE) {
    Console::decreaseIndention();
  }

  //---------------------------------------------------------------------------
  //
  // 6. class-specific methods:
  //     get and set methods
  //
  //---------------------------------------------------------------------------

  // set indentation
  //
  if (level_a > Integral::NONE) {
    Console::put(L"testing class-specific methods: get and set methods...\n");
    Console::increaseIndention();
  }

  // test getName methods
  //
  sdb.getName(in_name);
  
  if (in_name.ne(L"diagnose_file5.raw")) {
    in_name.debug(L"in_name");
    return Error::handle(name(), L"getName", Error::TEST,
			 __FILE__, __LINE__);
  }

  // get/setOutputExtension methods
  //
  String ext(L"mfc");
  sdb.setOutputExtension(ext);

  if (sdb.getOutputExtension().ne(ext)) {
    return Error::handle(name(), L"getOutputExtension", Error::TEST,
			 __FILE__, __LINE__);
  }

  // test get/setOutputDirectory
  //
  String out_dir(L"/tmp/out");
  sdb.setOutputDirectory(out_dir);

  if (sdb.getOutputDirectory().ne(out_dir)) {
    return Error::handle(name(), L"getOutputDirectory", Error::TEST,
			 __FILE__, __LINE__);
  }

  // test get/setDirPresLevel
  //
  int32 dir_pres = 3;
  sdb.setDirPresLevel(dir_pres);
  
  if (sdb.getDirPresLevel() != dir_pres) {
    return Error::handle(name(), L"getDirPresLevel", Error::TEST,
			 __FILE__, __LINE__);
  }    

  // reset indention
  //
  if (level_a > Integral::NONE) {
    Console::decreaseIndention();
  }

  
  
  //---------------------------------------------------------------------------
  //
  // 7. class-specific public methods: query methods
  //
  //---------------------------------------------------------------------------

  // set indentation
  //
  if (level_a > Integral::NONE) {
    Console::put(L"testing class-specific methods: get and set methods...\n");
    Console::increaseIndention();
  }

  
  // test the isSdb function
  //
  fn.assign(L"diagnose_file1.sof");

  if (!isSdb(fn)) {
    return Error::handle(name(), L"isSdb", Error::TEST, __FILE__, __LINE__);
  }
      
  fn.assign(L"diagnose_file2.sof");

  if (isSdb(fn)) {
    return Error::handle(name(), L"isSdb", Error::TEST, __FILE__, __LINE__);
  }

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

// method: sameFiles
//
// arguments:
//  Sdb& arg: (input) sdb object to compare
//
// return: a bool8 value indicating whether the lists are equivalent
//
bool8 Sdb::sameFiles(Sdb& arg_a) {

  // reset the objects: make sure they have the same return value. if
  // they both fail on gotoFirst, it means they are both empty lists
  // and hence equivalent.
  //
  bool8 n0 = gotoFirst();
  bool8 n1 = arg_a.gotoFirst();

  Long num_compared = 0;

  // if they have different return values, one is empty and the other
  // isn't.
  //
  if (n0 ^ n1) {
    if (debug_level_d >= Integral::DETAILED) {
      num_compared.debug(L"number compared");
    }
    return false;
  }

  Filename fn0;
  Filename fn1;

  if (n0) {
    num_compared += 1;
  }

  // loop while they have files (note n0 must equal n1 or the if
  // branches will return false
  //
  while (n0) {

    // extract the current filenames
    //
    if (!getName(fn0)) {
      return Error::handle(name(), L"sameFiles", ERR, __FILE__, __LINE__);
    }

    if (!arg_a.getName(fn1)) {
      return Error::handle(name(), L"sameFiles", ERR, __FILE__, __LINE__);
    }

    // compare the filenames, possibly provide debug information if they differ
    //
    if (fn0.ne(fn1)) {
      if (debug_level_d >= Integral::DETAILED) {
	fn0.debug(L"fn0");
	fn1.debug(L"fn1");
	num_compared.debug(L"number compared");
      }
      return false;
    }

    n0 = gotoNext();
    n1 = arg_a.gotoNext();

    num_compared += 1;
    
    // if they have different return values, one is out of files and
    // the other isn't.
    //
    if (n0 ^ n1) {
      if (debug_level_d >= Integral::DETAILED) {
	num_compared.debug(L"number compared");
      }
      return false;
    }
  }

  if (debug_level_d >= Integral::DETAILED) {
    num_compared -= 1;
    num_compared.debug(L"number compared");
  }

  // exit gracefully
  //
  return true;
}
