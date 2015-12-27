// file: $isip/class/system/File/file_02.cc
// version: $Id: file_02.cc 10636 2007-01-26 22:18:09Z tm334 $
//

// changed the num_5 value for gcc 4.1.0 compatible
//

// isip include files
//
#include "File.h"
#include <SysString.h>
#include <Console.h>

// method: diagnose
//
// arguments:
//  Integral::DEBUG level: (input) debug level for diagnostics
//
// return: a bool8 value indicating status
//
bool8 File::diagnose(Integral::DEBUG level_a) {

  //---------------------------------------------------------------------------
  //
  // 0. preliminaries
  //
  //---------------------------------------------------------------------------
  
  // output the class name
  //
  if (level_a > Integral::NONE) {
    SysString output(L"diagnosing class ");
    output.concat(CLASS_NAME);
    output.concat(L": ");
    Console::put(output);
    Console::increaseIndention();
  }
  
  //---------------------------------------------------------------------------
  //
  // 1. required public methods
  //
  //---------------------------------------------------------------------------

  // set indentation
  //
  if (level_a > Integral::NONE) {
    Console::put(L"testing required public methods...\n");
    Console::increaseIndention();
  }

  // local variables, test constructor
  //
  File file_1;
  File file_2;
  
  // open an existing file
  //
  file_1.open(L"index.html");
  
  // test the debug methods
  //
  file_1.setDebug(debug_level_d);
  
  if (level_a > Integral::BRIEF) {
    file_1.debug(L"debug");
  }
  
  file_1.close();
  
  // testing memory allocation
  //
  if (level_a > Integral::BRIEF) {
    Console::put(L"testing memory management...\n");
  }
  
  File::setGrowSize((int32)500);
  
  for (int32 j = 1; j <= 10; j++) {
    File** dyn_file = new File*[j * 100];
    
    // create the objects
    //
    for (int32 i = 0; i < j * 100; i++) {
      dyn_file[i] = new File();
    }
    
    // delete objects
    //
    for (int32 i = (j * 100) - 1; i >= 0; i--) {
      delete dyn_file[i];
    }
    
    delete [] dyn_file;
  } 
  
  // reset indentation
  //
  if (level_a > Integral::NONE) {
    Console::decreaseIndention();
  }

  //---------------------------------------------------------------------------
  //
  // 2. class-specific public methods:
  //     extensions to required methods
  //
  //---------------------------------------------------------------------------
  
  // set indentation
  //
  if (level_a > Integral::NONE) {
    Console::put(L"testing class-specific public methods: extensions to required methods...\n");
    Console::increaseIndention();
  }

  // local variables
  //
  File file_3;
  File file_4;
  
  // open file_3
  //
  file_3.open(L"index.html");
  
  // swap the two files
  //
  file_3.swap(file_4);

  // file_4 should be open now, while file_3 is not open
  //
  if (file_4.fp_d == (FILE*)NULL || file_3.fp_d != (FILE*)NULL) {
    return Error::handle(name(), L"swap", Error::TEST, __FILE__, __LINE__);
  }
  
  // get the memsize
  //
  int32 mem_size = file_3.memSize();
  
  if (level_a > Integral::BRIEF) {
    SysString numeric;
    numeric.assign(mem_size);
    SysString output(L"memSize of file_3: ");
    output.concat(numeric);
    Console::put(output);
  }
  
  // close file
  //
  file_4.close();
  
  // reset indentation
  //
  if (level_a > Integral::NONE) {
    Console::decreaseIndention();
  }
  
  //---------------------------------------------------------------------------
  //
  // 3. class-specific public methods:
  //     file operation methods
  //
  //---------------------------------------------------------------------------
  
  // set indentation
  //
  if (level_a > Integral::NONE) {
    Console::put(L"testing class-specific public methods: file operation methods...\n");
    Console::increaseIndention();
  }
  
  // local variables
  //
  File file_read;
  File file_write;
  SysString existing_file;
  existing_file.assign(L"index.html");
  SysString temp_file;
  Integral::makeTemp(temp_file);
  
  // set open retry
  //
  file_read.setOpenRetry(DEF_OPEN_RETRY, DEF_OPEN_DELAY);
  
  // open a file in read text mode
  //
  if (!file_read.open(existing_file)) {
    return Error::handle(name(), L"open", Error::TEST, __FILE__, __LINE__);
  }
  
  // logical test
  //
  if (!file_read.isReadable() || !file_read.isOpen()) {
    return Error::handle(name(), L"open read", Error::TEST, __FILE__,
			 __LINE__);
  }
  
  // open a file in write text mode
  //
  if (!file_write.open(temp_file, File::WRITE_ONLY, File::TEXT)) {
    return Error::handle(name(), L"open", Error::TEST, __FILE__, __LINE__);
  }
  
  // lock the file
  //
  file_write.lock();
  
  // logical test
  //
  if (!file_write.isWritable() || !file_write.isOpen() ||
      !file_write.isLocked()) {
    return Error::handle(name(), L"open lock", Error::TEST, __FILE__,
			 __LINE__);
  }
  
  // unlock the file
  //
  file_write.unlock();
  
  // close the files
  //
  file_read.close();
  file_write.close();
  
  // logical test
  //
  if (file_read.isOpen() || file_write.isOpen() || file_write.isLocked()) {
    return Error::handle(name(), L"close / lock", Error::TEST, __FILE__,
			 __LINE__);
  }

  // open a file in write binary mode
  //
  Integral::makeTemp(temp_file);
  file_write.open(temp_file, File::WRITE_ONLY, File::TEXT);
  
  // write something into it
  //
  int32 data[50];
  for (int32 i = 0; i < 50; i++) {
    data[i] = i;
  }

  if (file_write.write(data, sizeof(int32), 50) != 50) {
    return Error::handle(name(), L"write", Error::TEST, __FILE__, __LINE__);
  }
  
  if (file_write.write(data, sizeof(int32), 10) != 10) {
    return Error::handle(name(), L"write", Error::TEST, __FILE__, __LINE__);
  }

  // test the file size
  //
  int32 pos = file_write.size();

  // the size of file should be the size of 60 int32 numbers
  //
  if (pos != 60 * sizeof(int32)) {
    return Error::handle(name(), L"seek/tell", Error::TEST, __FILE__,
			 __LINE__);
  }
  
  // truncate to having only 50 numbers
  //
  file_write.truncate(50 * sizeof(int32));
  
  // get the file size again
  //
  pos = file_write.size();
  
  // the size of file should be the size of 55 int32 numbers
  //
  if (pos != 50 * sizeof(int32)) {
    printf("pos %ld\n",(long) pos);
    return Error::handle(name(), L"size", Error::TEST, __FILE__,
			 __LINE__);
  }
  
  // close the binary file
  //
  file_write.close();

  // test the size of the file
  //
  if (size(temp_file) != 50 * sizeof(int32)) {
    return Error::handle(name(), L"size", Error::TEST, __FILE__, __LINE__);
  }

  // test an error condition for file size
  //
  SysString err_temp_file;
  Integral::makeTemp(err_temp_file);
  Console::open(err_temp_file);
  int32 size_err = size(L"THIS_FILE_SHOULD_NOT_EXIST");
  Console::close();
  if (size_err != -1) {
    return Error::handle(name(), L"size", Error::TEST, __FILE__, __LINE__);
  }
  
  // open the file in read binary mode
  //
  file_read.open(temp_file, File::READ_ONLY, File::BINARY);

  // read the numbers
  //
  int32 data_read[50];

  // we are trying to read more than the 50 available numbers,
  // the actual number read should still be 50, and an EOF is detected
  //
  if (file_read.read(data_read, sizeof(int32), 55) != 50) {
    return Error::handle(name(), L"write/read", Error::TEST, __FILE__,
			   __LINE__);
  }

  for (int32 i = 0; i < 50; i++) {
    if (data_read[i] != data[i]) {
      return Error::handle(name(), L"write/read", Error::TEST, __FILE__,
			   __LINE__);
    }
  }

  // we are at the end of the file now, an EOF has been detected
  //
  if (!file_read.eof()) {
    return Error::handle(name(), L"eof", Error::TEST, __FILE__, __LINE__);
  }
  
  // rewind the file
  //
  file_read.rewind();
  pos = file_read.tell();
  
  if (pos != 0)  {
    return Error::handle(name(), L"rewind", Error::TEST, __FILE__,
			 __LINE__);
  }
  
  // close the file
  //
  file_read.close();
  
  // reset indentation
  //
  if (level_a > Integral::NONE) {
    Console::decreaseIndention();
  }
  
  //---------------------------------------------------------------------------
  //
  // 4. class-specific public methods:
  //     i/o methods
  //
  //---------------------------------------------------------------------------

  // set indentation
  //
  if (level_a > Integral::NONE) {
    Console::put(L"testing class-specific public methods: i/o methods...\n");
    Console::increaseIndention();
  }
  
  // local variables
  //
  File out(File::ERROR);
  File foo_wo;
  File foo_rp;
  SysString str1, str2;
  SysChar char1, char2;

  // open a file for write only
  //
  foo_wo.open(temp_file, File::WRITE_ONLY, File::TEXT);

  // write a string, a new line char and a char to it
  // 
  str1.assign(L"testing output");
  char1.assign(L'X');

  foo_wo.put(str1);
  foo_wo.put(L"\n");            
  foo_wo.put(char1);
  
  // test the output to stderr
  //
  if (level_a > Integral::BRIEF) {
    Console::put(L"this is testing the stderr");
    out.put(str1);
    out.put(L"\n");
  }
  
  // close the file and reopen it to read
  //
  foo_wo.close();
  foo_rp.open(temp_file, File::READ_PLUS, File::TEXT);

  // get the string and the char
  //
  foo_rp.get(str2);
  foo_rp.get(char2);
  
  if (str2.ne(str1) || char2.ne(char1)) {
    return Error::handle(name(), L"get", Error::TEST, __FILE__, __LINE__);
  }
  
  // close files
  //
  foo_rp.close();
  out.close();
  
  // binary i/o read/write have been tested in the previous session
  //
  
  // reset indentation
  //
  if (level_a > Integral::NONE) {
    Console::decreaseIndention();
  }
  
  //---------------------------------------------------------------------------
  //
  // 5. class-specific public methods:
  //     formatting methods
  //
  //---------------------------------------------------------------------------
  
  // set indentation
  //
  if (level_a > Integral::NONE) {
    Console::put(L"testing class-specific public methods: formatting methods...\n");
    Console::increaseIndention();
  }

  // open a temp file
  //  
  File screen;
  if (!screen.open(temp_file, File::WRITE_ONLY , File::TEXT)) {
    return Error::handle(name(), L"open", Error::TEST, __FILE__, __LINE__);
  }

  // set the line wrap
  //
  int32 line_wrap = 55;
  screen.setLineWrap(line_wrap);
  
  // since no indention yet, the line length should be the same as line wrap
  //
  int32 line_length = screen.getLineWrap();
  if (line_length != line_wrap) {
    return Error::handle(name(),L"getLineWrap",Error::TEST,__FILE__,__LINE__);
  }
  
  // output something into the file, and change its indentation
  //
  SysString output(L"starting output");
  screen.put(output);
  output.assign(L"first indent\n");
  screen.put(output);
  
  // increase the indention, now the line length should decrease the
  // by the length of the indention string
  //
  screen.increaseIndention(); 
  line_length -= INDENT_STR.length();
  
  if (screen.getLineLength() != line_length) {
    return Error::handle(name(), L"getLineLength", Error::TEST,
			 __FILE__, __LINE__);
  }
  
  screen.put(output);
  screen.put(output);
  screen.put(output);

  // increase the indention again
  //
  output.assign(L"second indent\n");
  screen.put(output);
  
  screen.increaseIndention();
  line_length -= INDENT_STR.length();
  
  if (screen.getLineLength() != line_length) {
    return Error::handle(name(), L"getLineLength", Error::TEST,
			 __FILE__, __LINE__);
  }
  
  // put a very int32 message
  //
  output.assign(L"this is a whole lot more text than will probably fit in the single indention, so let's just keep defining\n\n\n\n(just had four newlines) more and more text to just keep wrapping and wrapping.");
  screen.put(output);
  screen.put(output);
  screen.put(output);
  screen.put(output);
  
  // randomly output some message into the file
  //
  screen.increaseIndention();
  screen.increaseIndention();
  output.assign(L"fo ur th in de nt ");

  for (int32 i = 0; i < 25; i++) {
    screen.put(output);
  }
  
  output.assign(L"herewehaveawordtoolongtobreak,soletsseewhatthetokenizerdoes\n\n\n\n\n");
  screen.put(output);
  output.assign(L"this is a whole lot more text than will probably fit in the single indention, so let's just keep defining\n(just had a newline)more and more text to just keep wrapping and wrapping.");
  screen.put(output);
  screen.put(output);
  screen.put(output);
  screen.put(output);
  
  screen.decreaseIndention();
  screen.decreaseIndention();
  
  screen.decreaseIndention();
  output.assign(L"back to first indent\n");
  screen.put(output);
  screen.put(output);
  screen.put(output);
  output.assign(L"thisisawholelotmoretextthanwillprobablyfitinthesingleindention,solet'sjustkeepdefining\n(justhadanewline)moreandmoretexttojustkeepwrappingandwrapping.");
  screen.put(output);
  screen.put(output);
  screen.put(output);
  
  screen.decreaseIndention();
  output.assign(L"back to no indention\n");
  screen.put(output);
  screen.put(output);
  output.assign(L"this is a whole lot more text than will probably fit in the single indention, so let's just keep defining\n(just had a newline)more and more text to just keep wrapping and wrapping.");
  screen.put(output);
  screen.put(output);
  screen.put(output);
  screen.put(output);
  output.assign(L"thisisawholelotmoretextthanwillprobablyfitinthesingleindention,solet'sjustkeepdefining\n(justhadanewline)moreandmoretexttojustkeepwrappingandwrapping.");
  screen.put(output);
  screen.put(output);
  screen.put(output);
  
  // output debug information
  //
  if (level_a > Integral::BRIEF) {
    screen.debug(L"file screen");
  }
  
  // close file
  //
  screen.close();

  // reset indentation
  //
  if (level_a > Integral::NONE) {
    Console::decreaseIndention();
  }

  //---------------------------------------------------------------------------
  //
  // 6. class-specific public methods:
  //     disk file operation methods
  //
  //---------------------------------------------------------------------------

  // set indentation
  //
  if (level_a > Integral::NONE) {
    Console::put(L"testing class-specific public methods: disk file operation methods...\n");
    Console::increaseIndention();
  }
  
  // test the system functions
  //
  if (level_a > Integral::BRIEF) {
    Console::put(L"testing exists, rename, remove methods");
  }

  // make a new temp file
  //
  SysString new_temp;
  Integral::makeTemp(new_temp);
  
  // new_temp should not exist
  //
  if (exists(new_temp)) {
    return  Error::handle(name(), L"exists", Error::TEST, __FILE__, __LINE__);
  }

  // rename the existing temp_file to new_temp
  //
  if (!rename(temp_file, new_temp)) {
    return Error::handle(name(), L"rename", Error::TEST, __FILE__, __LINE__);
  }
  
  // new_temp should exit now, temp_file is gone
  //
  if (!exists(new_temp)) {
    return  Error::handle(name(), L"exists", Error::TEST, __FILE__, __LINE__);
  }
  if (exists(temp_file)) {
    return  Error::handle(name(), L"exists", Error::TEST, __FILE__, __LINE__);
  }
    
  // remove files
  //
  if (!remove(new_temp)) {
    return Error::handle(name(), L"remove", Error::TEST, __FILE__, __LINE__);
  }

  if (exists(new_temp) || exists(temp_file)) {
    return Error::handle(name(), L"exists", Error::TEST, __FILE__, __LINE__);
  }
  
  // test mkdir
  //
  if (level_a > Integral::BRIEF) {
    Console::put(L"testing mkdir and rmdir methods");
  }

  if (!mkdir(L"/tmp/my_new_dir")) {
    return Error::handle(name(), L"mkdir", Error::TEST, __FILE__, __LINE__);
  }
  if (!exists(L"/tmp/my_new_dir")) {
    return Error::handle(name(), L"mkdir", Error::TEST, __FILE__, __LINE__);
  }
  if (!rmdir(L"/tmp/my_new_dir")) {
    return Error::handle(name(), L"rmdir", Error::TEST, __FILE__, __LINE__);
  }
  if (exists(L"/tmp/my_new_dir")) {
    return Error::handle(name(), L"rmdir", Error::TEST, __FILE__, __LINE__);
  }

  // test compare
  //
  if (compare(L"file_02.cc", L"file_03.cc")) {
    return Error::handle(name(), L"compare", Error::TEST, __FILE__, __LINE__);
  }
  if (!compare(L"file_02.cc", L"file_02.cc")) {
    return Error::handle(name(), L"compare", Error::TEST, __FILE__, __LINE__);
  }

  if (compare(L"file_02.o", L"file_06.o")) {
    return Error::handle(name(), L"compare", Error::TEST, __FILE__, __LINE__);
  }
  if (!compare(L"file_02.o", L"file_02.o")) {
    return Error::handle(name(), L"compare", Error::TEST, __FILE__, __LINE__);
  }

  // reset indentation
  //
  if (level_a > Integral::NONE) {
    Console::decreaseIndention();
  }
  
  //---------------------------------------------------------------------------
  //
  // 7. class-specific public methods:
  //     byte-order related methods
  //
  //---------------------------------------------------------------------------

  // set indentation
  //
  if (level_a > Integral::NONE) {
    Console::put(L"testing class-specific public methods: byte-order related methods...\n");
    Console::increaseIndention();
  }

  // test encode method
  //
  File swap_file;
  swap_file.setBMode(SWAP);
  
  // test machine byte order
  //
  SysString machine_type;
  SysString byte_order;
  machine_type.assign(swap_file.getMachineByteOrder());
  byte_order.assign(swap_file.getBMode());

  if (level_a > Integral::BRIEF) {
    
    // these two should one is BIG_ENDIAN, one is LITTLE_ENDIAN
    //
    machine_type.debug(L"machine byte order");
    byte_order.debug(L"file byte order");
  }

  // encode int16
  // a int16 number 1, which is 0x00 01 in hex,
  // after encode, it should be 0x01 00, which is 2^8
  //
  int16 num_1 = 0x0001;
  int16 num_2 = 0x0100;
  if (swap_file.encode(num_1) != num_2) {
    return Error::handle(name(), L"encode int16", Error::TEST,
			 __FILE__, __LINE__);
  }

  // encode int32
  // a int16 number 1, which is 0x00 01 10 11
  // after encode, it should be 0x11 10 01 00
  //
  int32 num_3 = 0x00011011;
  int32 num_4 = 0x11100100;
  if (swap_file.encode(num_3) != num_4) {
    return Error::handle(name(), L"encode int32", Error::TEST,
			 __FILE__, __LINE__);
  }
 
  // encode int64   0x80 00 00 00 00 00 00 00
  // after encode   0x00 00 00 00 00 00 00 80
  //                
  int64 num_5 = (int64)Integral::TWO_EXP63;
  int64 num_6 = 0x0080;
  
  // for the constant Integral::TWO_EXP63,
  //   gcc 4.1.0 will lose 1 for for converting from float64 to int64
  //   gcc 3.2.3 doesn't have this problem
  //
  num_5++;

  if (swap_file.encode(num_5) != num_6) {
    return Error::handle(name(), L"encode int64", Error::TEST,
    			 __FILE__, __LINE__);
  }
  
  // decode the numbers back
  //
  int16 num_1d = swap_file.decode(num_2);
  if (num_1d != num_1) {
    return Error::handle(name(), L"decode int16", Error::TEST,
			 __FILE__, __LINE__);
  }

  int32 num_3d = swap_file.decode(num_4);
  if (num_3d != num_3) {
    return Error::handle(name(), L"decode int32", Error::TEST,
			 __FILE__, __LINE__);
  }
  
  int64 num_5d = swap_file.decode(num_6);
  if (num_5d != num_5) {
    return Error::handle(name(), L"decode int64", Error::TEST,
			 __FILE__, __LINE__);
  }
  
  // reset indentation
  //
  if (level_a > Integral::NONE) {
    Console::decreaseIndention();
  }

  //---------------------------------------------------------------------------
  //
  // 8. class-specific public methods:
  //     string manipulation methods
  //
  //---------------------------------------------------------------------------

  // set indentation
  //
  if (level_a > Integral::NONE) {
    Console::put(L"testing class-specific public methods: string manipulation methods...\n");
    Console::increaseIndention();
  }

  // local variables
  //
  SysString str0(L"Hey, how's it goin?\n Good. You look like you just got up?\n Yeah, I've been snoozin.\n Late night last night?\n Yeah, I had to cram for a bio test. What did you do?");
  File file_5;
  SysString sstr;
  bool8 rc;
  
  // create and write a string to a temporary file
  //
  Integral::makeTemp(temp_file);
  file_5.open(temp_file, WRITE_ONLY);
  file_5.put(str0);
  file_5.close();

  // open the temporary file
  //
  file_5.open(temp_file, READ_ONLY);
  
  // test string manipulation methods
  //
  rc = file_5.substr(sstr, -1, 4);
  if (!rc || !sstr.eq(L"Hey,")) {
    Error::handle(name(), L"substr", Error::TEST, __FILE__, __LINE__);
  }
  
  rc = file_5.substr(sstr, 21, 5);
  if (!rc || !sstr.eq(L"Good.")) {
    Error::handle(name(), L"substr", Error::TEST, __FILE__, __LINE__);
  }

  rc = file_5.substr(sstr, 157, -1);
  if (!rc || !sstr.eq(L" do?")) {
    Error::handle(name(), L"substr", Error::TEST, __FILE__, __LINE__);
  }
  
  rc = file_5.substr(sstr, 157, 16);
  if (!rc || !sstr.eq(L" do?")) {
    Error::handle(name(), L"substr", Error::TEST, __FILE__, __LINE__);
  }

  rc = file_5.substr(sstr, 14, 18);
  if (!rc || !sstr.eq(L"goin?")) {
    Error::handle(name(), L"substr", Error::TEST, __FILE__, __LINE__);
  }

  rc = file_5.substr(sstr, 196, 10);
  if (rc) {
    Error::handle(name(), L"substr", Error::TEST, __FILE__, __LINE__);
  }
  
  rc = file_5.substr(sstr, 12, 0);
  if (rc) {
    Error::handle(name(), L"substr", Error::TEST, __FILE__, __LINE__);
  } 
  

  file_5.close();
  
  File::remove(temp_file);

  // reset indentation
  //
  if (level_a > Integral::NONE) {
    Console::decreaseIndention();
  }
    
  //---------------------------------------------------------------------------
  //
  // 9. class-specific public methods:
  //     string search methods
  //
  //---------------------------------------------------------------------------

  // set indentation
  //
  if (level_a > Integral::NONE) {
    Console::put(L"testing class-specific public methods: string search methods...\n");
    Console::increaseIndention();
  }

  // local variables
  //
  SysString str3(L"Hey");
  SysString str4(L"look like");
  SysString str5(L" do?");
  SysString str6(L"how's");
  SysString str7(L"going");
  
  // create and write a string to a temporary file
  //
  Integral::makeTemp(temp_file);
  file_5.open(temp_file, WRITE_ONLY);
  file_5.put(str0);
  file_5.close();

  // open the temporary file
  //
  file_5.open(temp_file, READ_ONLY);
  
  // test string search methods
  //
  pos = file_5.firstStr(str3);
  if (pos != 0) {
    Error::handle(name(), L"firstStr", Error::TEST, __FILE__, __LINE__);
  }
  pos = file_5.firstStr(str4, 12);
  if (pos != 31) {
    Error::handle(name(), L"firstStr", Error::TEST, __FILE__, __LINE__);
  }
  
  pos = file_5.firstStr(str5);
  if (pos != 157) {
    Error::handle(name(), L"firstStr", Error::TEST, __FILE__, __LINE__);
  }
  
  pos = file_5.firstStr(str6, 36);
  if (pos != Integral::NO_POS) {
    Error::handle(name(), L"firstStr", Error::TEST, __FILE__, __LINE__);
  }

  pos = file_5.firstStr(str7);
  if (pos != Integral::NO_POS) {
    Error::handle(name(), L"firstStr", Error::TEST, __FILE__, __LINE__);
  }

  file_5.close();
  
  File::remove(temp_file);

  // reset indentation
  //
  if (level_a > Integral::NONE) {
    Console::decreaseIndention();
  }
  
  //---------------------------------------------------------------------------
  //
  // 10. print completion message
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
