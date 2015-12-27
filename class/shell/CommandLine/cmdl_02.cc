// file: $isip/class/shell/CommandLine/cmdl_02.cc
// version: $Id: cmdl_02.cc 9240 2003-06-23 21:59:42Z parihar $
//

// isip include files
//
#include "CommandLine.h"
#include <Float.h>
#include <Console.h>

// method: diagnose
//
// arguments:
//  Integral::DEBUG level: (input) debug level for diagnostics
//
// return: a bool8 value indicating status
//
bool8 CommandLine::diagnose(Integral::DEBUG level_a) {
  
  // set test_mode_d to true so help messages will not halt
  //
  test_mode_d = true;

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

  // test new and delete
  //
  CommandLine* ptr;
  String str0(L"i am commandline");
  
  CommandLine::setGrowSize((int32)31);

  for (int32 j = 1; j <= 100; j++) {
    ptr = new CommandLine();
    ptr->assign(str0);
    delete ptr;

    ptr = new CommandLine[100];
    delete [] ptr;
  }


  // test parsing and setting of arguments from String
  //
  CommandLine cmdl01;
  String line(L"run_me.exe fileA.sof file2.sof file3.sof fileD.sof fileE.sof");
  cmdl01.parse(line);

  if (cmdl01.numArguments() != 5) {
    return Error::handle(cmdl01.name(), L"numArguments",
                         ERR,  __FILE__, __LINE__);
  }

  String a0;
  String a1;
  String a2;
  String a3;
  String a4;

  cmdl01.getArgument(a0, 0);
  cmdl01.getArgument(a1, 1);
  cmdl01.getArgument(a2, 2);
  cmdl01.getArgument(a3, 3);
  cmdl01.getArgument(a4, 4);

  if (level_a > Integral::BRIEF) {
    a0.debug(L"a0");
    a1.debug(L"a1");
    a2.debug(L"a2");
    a3.debug(L"a3");
    a4.debug(L"a4");
  }
  
  if (a0.ne(L"fileA.sof") || a1.ne(L"file2.sof")
      || a2.ne(L"file3.sof") || a3.ne(L"fileD.sof")
      || a4.ne(L"fileE.sof")) {
    return Error::handle(cmdl01.name(), L"getArgument", ERR,  __FILE__, __LINE__);
  }

  // test constructors
  //
  CommandLine cmdl0;
  String str(L"i am commandline");
  cmdl0.assign(str);

  CommandLine cmdl1(cmdl0);

  if (!cmdl0.eq(cmdl1)) {
    return Error::handle(name(), L"assign", Error::TEST, __FILE__, __LINE__);
  }

  // we need binary and text sof files
  //
  String tmp_filename0;
  Integral::makeTemp(tmp_filename0);
  if (level_a > Integral::BRIEF) {
    tmp_filename0.debug(L"temporary filename");
  }

  // open the file
  //
  if (level_a > Integral::BRIEF) {
    Console::open(tmp_filename0);
  }
  
  // perform full diagnostic
  //
  if (level_a > Integral::BRIEF) {
    Integral::debug(L"starting diagnostic");
  }

  // test the setDebug method
  //
  CommandLine dbg_cmdl;

  dbg_cmdl.setDebug(Integral::NONE);
  if (dbg_cmdl.debug_level_d != Integral::NONE) {
    return Error::handle(name(), L"setDebug", Error::TEST, __FILE__, __LINE__);
  }

  dbg_cmdl.setDebug(Integral::ALL);
  if (dbg_cmdl.debug_level_d != Integral::ALL) {
    return Error::handle(name(), L"setDebug", Error::TEST, __FILE__, __LINE__);
  }
  
  // create a command line
  //
  static char argstr[] = "foo.exe -swap -sf 7000.0 -nbytes 4 -num_chan 3 -v 2 -bytes 10 -mode stereo file1.raw file2.raw";

  char *arg0[16];
  arg0[0] = (char*)&argstr[0]; 
  argstr[7] = (char)NULL;
  arg0[1] = (char*)&argstr[8];
  argstr[13] = (char)NULL;
  arg0[2] = (char*)&argstr[14];
  argstr[17] = (char)NULL;
  arg0[3] = (char*)&argstr[18];
  argstr[24] = (char)NULL;
  arg0[4] = (char*)&argstr[25];
  argstr[32] = (char)NULL;
  arg0[5] = (char*)&argstr[33];
  argstr[34] = (char)NULL;
  arg0[6] = (char*)&argstr[35];
  argstr[44] = (char)NULL;
  arg0[7] = (char*)&argstr[45];
  argstr[46] = (char)NULL;
  arg0[8] = (char*)&argstr[47];
  argstr[49] = (char)NULL;
  arg0[9] = (char*)&argstr[50];
  argstr[51] = (char)NULL;
  arg0[10] = (char*)&argstr[52];
  argstr[58] = (char)NULL;
  arg0[11] = (char*)&argstr[59];
  argstr[61] = (char)NULL;
  arg0[12] = (char*)&argstr[62];
  argstr[67] = (char)NULL;
  arg0[13] = (char*)&argstr[68];
  argstr[74] = (char)NULL;
  arg0[14] = (char*)&argstr[75];
  argstr[84] = (char)NULL;
  arg0[15] = (char*)&argstr[85];
   
  // create a command line object
  //
  CommandLine cmdl;
  
  // set up the parameters name for the application
  //
  String sf_param(L"sf");
  String nbytes_param(L"nbytes");
  String num_chan_param(L"num_chan");
  String v_param(L"v");
   
  String num_param(L"num");
  String bytes_param(L"bytes");
  String mode_param(L"mode");
  String filename_param(L"filename");
  String freq_param(L"freq");
  String val_short_param(L"val_short");
  String val_ushort_param(L"val_ushort");
  String val_llng_param(L"val_llng");
  String val_ulng_param(L"val_ulng");
  String val_ullng_param(L"val_ullng");
   
  // set up the default values of the parameter
  //
  float32 sf_def = 16000.0;
  int32 nbytes_def = 2;
  int32 num_chan_def = 1;
  int32 v_def = 1;
  int32 num_def = 1;
  byte8 bytes_def = 100;
  float64 freq_def = 8000.0;
  short val_short_def = 4;
  ushort val_ushort_def = 2;
  String mode_def(L"stereo");
  String filename_def(L"sample");
  int64 val_llng_def = 10;
  uint32 val_ulng_def = 100;
  uint64 val_ullng_def = 256;
  String version_message_d(L"1.0");
 
  // test clear and clean up
  //  
  cmdl.clear();

  if (level_a > Integral::BRIEF) {
    Console::close();
    File::remove(tmp_filename0);
    Console::put(L"closed and removed temp console");
  }
  
  // reset indentation
  //
  if (level_a > Integral::NONE) {
    Console::decreaseIndention();
  }

  //---------------------------------------------------------------------------
  //
  // 1. class-specific public methods:
  //     extension to required methods     
  //
  //---------------------------------------------------------------------------

  // set indentation
  //
  if (level_a > Integral::NONE) {
    Console::put(L"testing class-specific public methods: extension to required methods...\n");
    Console::increaseIndention();
  }

  // create a temporary object
  //  
  CommandLine cmdl_1;
  
  cmdl_1.assign(cmdl);
  
  if (!(cmdl.eq(cmdl_1))) {
     return Error::handle(name(), L"assign", Error::TEST,__FILE__, __LINE__);
  }

  // reset indentation
  //
  if (level_a > Integral::NONE) {
    Console::decreaseIndention();
  }
  
  //---------------------------------------------------------------------------
  //
  // 2. class-specific public methods:
  //     set methods     
  //
  //---------------------------------------------------------------------------

  // set indentation
  //
  if (level_a > Integral::NONE) {
    Console::put(L"testing class-specific public methods: set methods...\n");
    Console::increaseIndention();
  }

  // set the help & usage method
  //
  cmdl.setUsage(L"synopsis: isip_doit [options] <files>\n");
  cmdl.setHelp(
  #include "dbg_help.help"
  ); 

  // set the version string through ident. we have to be careful here
  // and build the mock ident strings carefully so cvs doesn't replace
  // them.
  //
  String rev_str(L"Revision: 1.12 $");
  String name_str(L"Name: isip_r00_n02 $");
  String date_str(L"Date: 2001/02/14 15:08:05 $");

  rev_str.insert(L"$", 0);
  name_str.insert(L"$", 0);
  date_str.insert(L"$", 0);

  cmdl.setIdent((char*)(byte8*)rev_str,
		(char*)(byte8*)name_str,
		(char*)(byte8*)date_str);

  if (cmdl.version_msg_d.ne(L"Version: 1.12 (isip_r00_n02) 2001/02/14 15:08:05")) {
    return Error::handle(name(), L"setIdent", Error::TEST, __FILE__, __LINE__);
  }

  name_str.assign(L"Name: $");
  name_str.insert(L"$", 0);
  
  cmdl.setIdent((char*)(byte8*)rev_str,
		(char*)(byte8*)name_str,
		(char*)(byte8*)date_str);

  if (cmdl.version_msg_d.ne(L"Version: 1.12 (not released) 2001/02/14 15:08:05")) {
    return Error::handle(name(), L"setIdent", Error::TEST, __FILE__, __LINE__);
  }
  
  // reset indentation
  //
  if (level_a > Integral::NONE) {
    Console::decreaseIndention();
  }
  
  //---------------------------------------------------------------------------
  //
  // 3. class-specific public methods
  //     print methods
  //
  //---------------------------------------------------------------------------

  // set indentation
  //
  if (level_a > Integral::BRIEF) {
    Console::put(L"testing class-specific public methods: print methods...\n");
    Console::increaseIndention();
  }

  if (level_a > Integral::BRIEF) {
    
    // set the print methods
    //
    cmdl.printUsage();
    cmdl.printHelp();
    cmdl.printVersion();
  }
  
  // reset indentation
  //
  if (level_a > Integral::BRIEF) {
    Console::decreaseIndention();
  }
  
  //---------------------------------------------------------------------------
  //
  // 4. class-specific public methods
  //     add flag parameter method
  //
  //---------------------------------------------------------------------------
 
  // set indentation
  //
  if (level_a > Integral::NONE) {
    Console::put(L"testing class-specific public methods: add flag parameter methods...\n");
    Console::increaseIndention();
  }

  // check whether the flag is specified or not
  //
  String flag_param(L"swap");
  Boolean swap;
  cmdl.addFlagParam(swap, flag_param);

  // reset indentation
  //
  if (level_a > Integral::NONE) {
    Console::decreaseIndention();
  }
  
  //--------------------------------------------------------------------------
  //
  // 5. class-specific public methods
  //     add option parameter methods
  //
  //--------------------------------------------------------------------------

  // set indentation
  //
  if (level_a > Integral::NONE) {
    Console::put(L"testing class-specific public methods: add option parameter methods...\n");
    Console::increaseIndention();
  }

  // add the sample frequency
  //
  Float sf;
  cmdl.addOptionParam(sf, sf_param, sf_def);
     
  // add the number of bytes
  //
  Long nbytes;
  cmdl.addOptionParam(nbytes, nbytes_param, nbytes_def);
  
  // add the number of channels(int32)
  //
  Long num_chan;
  cmdl.addOptionParam(num_chan, num_chan_param, num_chan_def);
   
  // add the volume(int32)
  //
  Long v;
  cmdl.addOptionParam(v, v_param, v_def);

  // add the number of parameters(int32)
  //
  Long num;
  cmdl.addOptionParam(num, num_param, num_def);
 
  // add the byte8(byte)
  //
  Byte bytes;
  cmdl.addOptionParam(bytes, bytes_param, bytes_def);
  
  // add the play mode(string)
  //
  String mode;
  cmdl.addOptionParam(mode, mode_param, mode_def);

  // add the filename(string)
  //
  String filename;
  cmdl.addOptionParam(filename, filename_param, filename_def);

  // add the debug level(Integral::DEBUG)
  //
  DebugLevel debuglevel;
  cmdl.addOptionParam(debuglevel);

  // add the double value
  //
  Double freq;
  cmdl.addOptionParam(freq, freq_param, freq_def);

  // add the short value
  //
  Short val_short;
  cmdl.addOptionParam(val_short, val_short_param, val_short_def);

  // add the ushort value
  //
  Ushort val_ushort;
  cmdl.addOptionParam(val_ushort, val_ushort_param, val_ushort_def);

  // add the int64 value
  //
  Llong val_llng;
  cmdl.addOptionParam(val_llng, val_llng_param, val_llng_def);

  // add the uint32 value
  //
  Ulong val_ulng;
  cmdl.addOptionParam(val_ulng, val_ulng_param, val_ulng_def);

  // add the ullong value
  //
  Ullong val_ullng;
  cmdl.addOptionParam(val_ullng, val_ullng_param, val_ullng_def);

  // test parse methods
  //
  // parse the commandline
  //
  cmdl.parse(16, (const char**)arg0);
  
  // check the arguments
  //
  if (!swap) {
    return Error::handle(name(), L"addFlagParam", Error::TEST,
			 __FILE__, __LINE__);
  }
  
  if (!sf.almostEqual(7000.0)) {
    return Error::handle(name(), L"addOptionParam", Error::TEST,
			 __FILE__, __LINE__);
  }
  
  if (!nbytes.eq(4)) {
    return Error::handle(name(), L"addOptionParam", Error::TEST,
			 __FILE__, __LINE__);
  }

  if (!num_chan.eq(3)) {
    return Error::handle(name(), L"addOptionParam", Error::TEST,
			 __FILE__, __LINE__);
  }

  if (!v.eq(2)) {
    return Error::handle(name(), L"addOptionParam", Error::TEST,
			 __FILE__, __LINE__);
  }

  if (!num.eq(1)) {
    return Error::handle(name(), L"addOptionParam", Error::TEST,
			 __FILE__, __LINE__);
  }

  if (!mode.eq(L"stereo")) {
    return Error::handle(name(), L"addOptionParam", Error::TEST,
			 __FILE__, __LINE__);
  }

  if (!filename.eq(L"sample")) {
    return Error::handle(name(), L"addOptionParam", Error::TEST,
			 __FILE__, __LINE__);
  }

  if (!debuglevel.eq(Integral::DEF_DEBUG)) {
    return Error::handle(name(), L"addOptionParam", Error::TEST,
			 __FILE__, __LINE__);
  }
  
  if (!freq.almostEqual(8000.0)) {
    return Error::handle(name(), L"addOptionParam", Error::TEST,
			 __FILE__, __LINE__);
  }

  if (!val_short.eq(4)) {
    return Error::handle(name(), L"addOptionParam", Error::TEST,
			 __FILE__, __LINE__);
  }
  
  if (!val_ushort.eq(2)) {
    return Error::handle(name(), L"addOptionParam", Error::TEST,
			 __FILE__, __LINE__);
  }
  
  if (!val_llng.eq(10)) {
    return Error::handle(name(), L"addOptionParam", Error::TEST,
			 __FILE__, __LINE__);
  }
  
  if (!val_ulng.eq(100)) {
    return Error::handle(name(), L"addOptionParam", Error::TEST,
			 __FILE__, __LINE__);
  }
  
  if (!val_ullng.eq(256)) {
    return Error::handle(name(), L"addOptionParam", Error::TEST,
			 __FILE__, __LINE__);
  }
  
  // test basic parse method
  //
  String arg_string(L"foo.exe -debug ALL file1.raw file2.raw");
  CommandLine cmdl2;
  DebugLevel dbg_2;
  cmdl2.addOptionParam(dbg_2);
  
  cmdl2.parse(arg_string);
  if (!dbg_2.eq(Integral::ALL)) {
    return Error::handle(name(), L"parse", Error::TEST, __FILE__, __LINE__);
  }

  // create another command line
  //
  String arg_string1(L"foo.exe file2.raw -dbl 3500.0 -byte 2 -type mix -dbl 3600.0 -b 3 -ty stereo");
  CommandLine cmdl3;
  
  String dbl_param(L"dbl");
  String byte_param(L"byte");
  String type_param(L"type");
  
  SingleLinkedList<Double> dbl_res;
  SingleLinkedList<Byte> byte_res;
  SingleLinkedList<String> type_res;

  Double dbl_temp;
  dbl_temp = 3500.0;
  dbl_res.insert(&dbl_temp);
  dbl_temp = 3600.0;
  dbl_res.insert(&dbl_temp);

  Byte byte_temp;
  byte_temp = 2;
  byte_res.insert(&byte_temp);
  byte_temp = 3;
  byte_res.insert(&byte_temp);

  String type_temp;
  type_temp.assign(L"mix");
  type_res.insert(&type_temp);
  type_temp.assign(L"stereo");
  type_res.insert(&type_temp);

  // add the single-linked list of double value
  //
  SingleLinkedList<Double> dbl1;
  cmdl3.addOptionParam(dbl1, dbl_param);

  // add the single-linked list of byte value
  //
  SingleLinkedList<Byte> byte1;
  cmdl3.addOptionParam(byte1, byte_param);

  // add the single-linked list of string value
  //
  SingleLinkedList<String> type1;
  cmdl3.addOptionParam(type1, type_param);

  // test parse methods
  //
  // parse the commandline
  //
  cmdl3.parse(arg_string1);
  
  // check the arguments
  //
  if (!dbl1.eq(dbl_res)) {
    dbl_res.debug(L"expected result:");
    dbl1.debug(L"wrong result:");
    return Error::handle(name(), L"addOptionParam", Error::TEST,
			 __FILE__, __LINE__);
  }

  if (!byte1.eq(byte_res)) {
    byte_res.debug(L"expected result:");
    byte1.debug(L"wrong result:");
    return Error::handle(name(), L"addOptionParam", Error::TEST,
			 __FILE__, __LINE__);
  }

  if (!type1.eq(type_res)) {
    type_res.debug(L"expected result:");
    type1.debug(L"wrong result:");
    return Error::handle(name(), L"addOptionParam", Error::TEST,
			 __FILE__, __LINE__);
  }

  // test getExpanded method
  //
  String dump_expected(L"foo.exe file2.raw -dbl 3500.0 -byte 2 -type mix -dbl 3600.0 -byte 3 -type stereo");
  String dump_actual;
  cmdl3.getExpanded(dump_actual);
  if (dump_expected.ne(dump_actual)) {
    dump_expected.debug(L"expected result:");
    dump_actual.debug(L"wrong result:");
    return Error::handle(name(), L"getExpanded", Error::TEST, __FILE__,
			 __LINE__);
  }

  // test isPresent method
  //
  String param_name(L"dbl");
  if (!cmdl3.isPresent(param_name)) {
    return Error::handle(name(), L"isPresent",
			 Error::TEST, __FILE__, __LINE__);
  }

  // test getValue method
  //
  String param_value(L"3600.0");
  if ((!cmdl3.getValue(dump_actual, param_name, false)) ||
      (param_value.ne(dump_actual))) {
    return Error::handle(name(), L"getValue",
			 Error::TEST, __FILE__, __LINE__);
  }

  // test parse method echoing the -echo_cmdl option
  //
  if (level_a > Integral::BRIEF) {
    String arg_string2(arg_string1);
    arg_string2.concat(L" -echo_cmdl");
    String running_msg(L"Command: ");
    running_msg.concat(dump_expected);
    
    CommandLine cmdl4;
    cmdl4.addOptionParam(dbl1, dbl_param);
    cmdl4.addOptionParam(byte1, byte_param);
    cmdl4.addOptionParam(type1, type_param);

    // call parse method and print the expanded commmand line to Console
    //
    cmdl4.parse(arg_string2);
  }

  // test parse method "-list" option
  //
  Sdb sdb;
  CommandLine cmdl5(sdb);
  String arg_string4;
  arg_string4.assign(L"foo.exe -list id_sdb.sof");
  
  // call parse method
  //
  cmdl5.parse(arg_string4);

  // reset indentation
  //
  if (level_a > Integral::NONE) {
    Console::decreaseIndention();
  }
  
  //------------------------------------------------------------------------
  //
  // 6. class-specific public methods
  //     get methods
  //
  //-------------------------------------------------------------------------
  
  // set indentation
  //
  if (level_a > Integral::NONE) {
    Console::put(L"testing class-specific public methods: get methods...\n");
    Console::increaseIndention();
  }

  // get number of unused arguments
  //
  int32 num_arg = cmdl.numArguments();
  if (num_arg != 2) {
    cmdl.debug(L"cmdl");
    Console::put(num_arg);
    return Error::handle(cmdl.name(), L"numArguments", ERR,
			 __FILE__, __LINE__);
  }
  
  // get used arguments
  //
  String arg;
  if ((!cmdl.getArgument(arg, 0)) || (arg.ne(L"file1.raw"))) {
    return Error::handle(cmdl.name(), L"getArgument", ERR, __FILE__, __LINE__);	       
  }
  
  if ((!cmdl.getArgument(arg, 1)) || (arg.ne(L"file2.raw"))) {
    return Error::handle(cmdl.name(), L"getArgument", ERR,  __FILE__, __LINE__);
  }
  
  // reset indentation
  //
  if (level_a > Integral::NONE) {
    Console::decreaseIndention();
  }
  
  //---------------------------------------------------------------------------
  //
  // 7. print completion message
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
