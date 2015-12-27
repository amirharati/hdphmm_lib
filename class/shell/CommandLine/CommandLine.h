// file: $isip/class/misc/CommandLine/CommandLine.h
// version: $Id: CommandLine.h 9248 2003-06-29 10:02:45Z picone $
//

// make sure definitions are only made once
//
#ifndef ISIP_COMMAND_LINE
#define ISIP_COMMAND_LINE

// isip include files
//
#ifndef ISIP_FILENAME
#include <Filename.h>
#endif

#ifndef ISIP_DEBUG_LEVEL
#include <DebugLevel.h>
#endif

#ifndef ISIP_SDB
#include <Sdb.h>
#endif

#ifndef ISIP_BOOLEAN
#include <Boolean.h>
#endif

#ifndef ISIP_VECTOR
#include <Vector.h>
#endif

#ifndef ISIP_SINGLE_LINKED_LIST
#include <SingleLinkedList.h>
#endif

// forward class definitions
//
class Sdb;

// CommandLine: a class to handle the parsing of command line arguments.
//
//  since there are certain options that all utilities share,
//  command line is configured, by default, to support options
//  such as help, debug, extension, and preserve. for user programs
//  to get access to these values, we also provide get functions.
//  
class CommandLine {

  //---------------------------------------------------------------------------
  //
  // public constants
  //
  //---------------------------------------------------------------------------
public:
  
  // the class name
  //
  static const String CLASS_NAME;

  //----------------------------------------
  //
  // other important constants
  //
  //----------------------------------------

  //----------------------------------------
  //
  // default values and arguments
  //
  //----------------------------------------  

  // default values for parameters for command line parsing
  //
  static const String DEF_PARAM_PREFIX;
  static const String DEF_PARAM_SPACE;

  // define constants for option names expected to be standardized
  // across all utilities. programs should reference these
  // definitions rather than duplicate them.
  //
  static const String DEF_PARAM_DEBUG;
  static const String DEF_PARAM_LFILE;
  static const String DEF_PARAM_PFILE;
  static const String DEF_PARAM_TYPE;
  static const String DEF_PARAM_VERBOSITY;

  // default values for parameters for Sdb filename parsing
  //
  static const String DEF_PARAM_DIRECTORY;
  static const String DEF_PARAM_BASENAME;  
  static const String DEF_PARAM_EXTENSION;
  static const String DEF_PARAM_PRESERVE;
  static const String DEF_PARAM_SUFFIX;

  // default values for message-related parameters
  //
  static const String DEF_PARAM_ECHOC;
  static const String DEF_PARAM_HELP;
  static const String DEF_PARAM_USAGE;
  static const String DEF_PARAM_VERSION;

  // default grow size for temporary space
  //
  static const int32 DEF_OBJECTS_SIZE = 100;

  // default values for selected output strings
  //
  static const String COMMAND_STR;
  static const String NO_VERSION_NAME;
  static const String VERSION_STR;

  static const String REPORT_STR_00;
  static const String REPORT_STR_01;
  static const String REPORT_STR_02;

  // default arguments to methods
  //

  // special code for an Sdb list
  //
  static const int32 OPT_INDEX_SDB = 99999;
  
  // default values for selected command line options
  //
  static const Filename DEF_EMPTY;
  static const Filename DEF_LFILE_NAME;

  //---------------------------------------
  //
  // error codes
  //
  //---------------------------------------

  static const int32 ERR = 45000;
  static const int32 ERR_OPT = 45001;
  static const int32 ERR_OPTAMB = 45002;
  static const int32 ERR_OPTDUPL = 45003;
  static const int32 ERR_OPTMULT = 45004;
  static const int32 ERR_OPTARG = 45005;
  static const int32 ERR_OPTPARS = 45006;

  //---------------------------------------------------------------------------
  //
  // protected data
  //
  //---------------------------------------------------------------------------
protected:

  // command line data structures:
  //  program name: contains the program name passed from the main program
  //  options: contains the names of the user-specified options
  //  types: the names of the data types of the options
  //  used: flags indicating whether a particular option was used
  //  args: strings from the command line that are not related to options
  //  values: string values from the command line that correspond to options
  //
  String prog_name_d;
  Vector<String> options_d;
  Vector<String> types_d;
  Vector<Boolean> used_d;
  Vector<String> args_d;
  Vector<String> values_d;

  // message-related variables
  //
  Boolean echoc_flag_d;
  Boolean help_flag_d;
  Boolean usage_flag_d;
  Boolean version_flag_d;

  String help_msg_d;
  String usage_msg_d;
  String version_msg_d;

  // define a string to hold the expanded command line
  //
  String expanded_d;

  // link to an Sdb object
  //
  Sdb* sdb_d;
  
  // space to hold objects corresponding to expected arguments
  //
  int32 objects_size_d;
  void** objects_d;

  // define some internal flags
  //
  bool8 usage_printed_d;		// has a usage message been printed?
  static bool8 test_mode_d;		// diagnose mode -- don't exit

  // the debug level
  //
  static Integral::DEBUG debug_level_d;
  
  // static memory manager
  //
  static MemoryManager mgr_d;
  
  //---------------------------------------------------------------------------
  //
  // required public methods
  //
  //---------------------------------------------------------------------------
public:

  // method: name
  //
  inline static const String& name() {
    return CLASS_NAME;
  }

  // other static methods
  //
  static bool8 diagnose(Integral::DEBUG level);
  
  // method: setDebug
  //
  inline bool8 setDebug(Integral::DEBUG level) {
    debug_level_d = level;
    return true;
  }

  // other debug methods
  //
  bool8 debug(const unichar* message) const;
  
  // destructor/constructor(s)
  //
  ~CommandLine();
  CommandLine(); 
  CommandLine(const CommandLine& arg); 

  // assign methods 
  //
  bool8 assign(const CommandLine& arg);

  // method: operator=
  //
  CommandLine& operator=(const CommandLine& arg) {
    assign(arg);
    return *this;
  }
  
  // i/o methods:
  //  these methods are omitted because CommandLine object can not
  //  write itself to an Sof file
  //
  
  // method: eq
  //
  bool8 eq(const CommandLine& arg) const {
    return ((options_d.eq(arg.options_d) &&
	     types_d.eq(arg.types_d) &&
	     (objects_size_d == arg.objects_size_d) &&
	     help_flag_d.eq(arg.help_flag_d) &&
	     usage_flag_d.eq(arg.usage_flag_d) &&
	     version_flag_d.eq(arg.version_flag_d) &&
	     echoc_flag_d.eq(arg.echoc_flag_d)));
  }
  
  // method: new
  //
  static void* operator new(size_t size) {
    return mgr_d.get();
  }

  // method: new[]
  //
  static void* operator new[](size_t size) {
    return mgr_d.getBlock(size);
  }

  // method: delete
  //
  static void operator delete(void* ptr) {
    mgr_d.release(ptr);
  }

  // method: delete[]
  //
  static void operator delete[](void* ptr) {
    mgr_d.releaseBlock(ptr);
  }
  
  // method: setGrowSize
  //
  static bool8 setGrowSize(int32 grow_size) {
    return mgr_d.setGrow(grow_size);
  }

  // clear methods
  //
  bool8 clear(Integral::CMODE cmode = Integral::DEF_CMODE);
  
  //---------------------------------------------------------------------------
  //
  // class-specific public methods
  //
  //---------------------------------------------------------------------------

  // constructor 
  //
  CommandLine(Sdb& arg);
  
  // assign methods
  //
  bool8 assign(const String& str);
  
  //----------------------------------------
  //
  // class-specific public methods
  //  set methods
  //
  //----------------------------------------
  
  // set help file and set usage file methods
  //

  // method: setHelp
  //
  bool8 setHelp(const unichar* help_message) {
    return help_msg_d.assign(help_message);
  }

  // method: setUsage
  //
  bool8 setUsage(const unichar* usage_message) {
    return usage_msg_d.assign(usage_message);
  }

  // method: setVersion
  //
  bool8 setVersion(const unichar* version_message) {
    return version_msg_d.assign(version_message);
  }

  bool8 setIdent(const char* rev_str,
		   const char* name_str,
		   const char* date_str);
  
  // methods that interface with Sdb
  //
  bool8 setSdb(Sdb& arg_a);

  //----------------------------------------
  //
  // class-specific public methods
  //  print methods
  //
  //----------------------------------------
  
  // print methods
  //
  bool8 printUsage();
  bool8 printHelp() const;
  bool8 printVersion() const;
  bool8 printCommandLine() const;
  static bool8 printFinalReport(const String& prog_name, int32 ncmpl,
				  int32 natt);

  // method: printFinalReport
  //
  bool8 printFinalReport(int32 ncmpl, int32 natt) const {
    return printFinalReport(prog_name_d, ncmpl, natt);
  }
  
  //----------------------------------------
  //
  // class-specific public methods
  //  add flag parameter method
  //
  //----------------------------------------
 
  // method: addFlagParam
  //
  bool8 addFlagParam(Boolean& var, const String& param) {
    var.assign(false);
    return addOptionParam(&var, var.name(), param);
  }

  //----------------------------------------
  //
  // class-specific public methods
  //  add option parameter methods
  //
  //  these are listed in order of the position they appear in the
  //  isip class hierarchy
  //
  //----------------------------------------

  // method: addOptionParam 
  //   
  bool8 addOptionParam(File::TYPE& var, const String& param,
			 const File::TYPE& def_value = File::DEF_TYPE) {
    var = def_value;
    return addOptionParam(&var, L"File::TYPE", param);
  }

  // method: addOptionParam 
  //   
  bool8 addOptionParam(String& var, const String& param,
			 const String& def_value) {
    var.assign(def_value);
    return addOptionParam(&var, var.name(), param);
  }

  // method: addOptionParam 
  //   
  bool8 addOptionParam(Filename& var, const String& param,
			 const Filename& def_value) {
    var.assign(def_value);
    return addOptionParam(&var, var.name(), param);
  }

  // method: addOptionParam 
  //
  bool8 addOptionParam(DebugLevel& var,
			 const String& param = DebugLevel::DEF_PARAM,
			 Integral::DEBUG def_value = Integral::DEF_DEBUG) {
    var = def_value;
    return addOptionParam(&var, var.name(), param);
  }

  // add option methods:
  //  convert to integral types. if the argument is
  //  not present on the command line return the default value
  //

  // method: addOptionParam 
  //   
  bool8 addOptionParam(Byte& var, const String& param, byte8 def_value) {
    var.assign(def_value);
    return addOptionParam(&var, var.name(), param);
  }

  // method: addOptionParam 
  //   
  bool8 addOptionParam(Short& var, const String& param, int16 def_value) {
    var.assign(def_value);
    return addOptionParam(&var, var.name(), param);
  }

  // method: addOptionParam 
  //
  bool8 addOptionParam(Long& var, const String& param, int32 def_value) {
    var.assign(def_value);
    return addOptionParam(&var, var.name(), param);
  }

  // method: addOptionParam 
  //
  bool8 addOptionParam(Llong& var, const String& param, int64 def_value) {
    var.assign(def_value);
    return addOptionParam(&var, var.name(), param);
  }

  // method: addOptionParam 
  //
  bool8 addOptionParam(Ushort& var, const String& param, uint16 def_value) {
    var.assign(def_value);
    return addOptionParam(&var, var.name(), param);
  }

  // method: addOptionParam 
  //
  bool8 addOptionParam(Ulong& var, const String& param, uint32 def_value)  {
    var.assign(def_value);
    return addOptionParam(&var, var.name(), param);
  }

  // method: addOptionParam 
  //
  bool8 addOptionParam(Ullong& var, const String& param, uint64 def_value) {
    var.assign(def_value);
    return addOptionParam(&var, var.name(), param);
  }

  // method: addOptionParam 
  //
  bool8 addOptionParam(Float& var, const String& param, float32 def_value) {
    var.assign(def_value);
    return addOptionParam(&var, var.name(), param);
  }

  // method: addOptionParam 
  //
  bool8 addOptionParam(Double& var, const String& param, float64 def_value) {
    var.assign(def_value);
    return addOptionParam(&var, var.name(), param);
  }

  // method: addOptionParam 
  //
  bool8 addOptionParam(SingleLinkedList<String>& var, const String& param) {
    var.clear();
    return addOptionParam(&var, var.name(), param);
  }

  // method: addOptionParam 
  //
  bool8 addOptionParam(SingleLinkedList<Filename>& var, const String& param) {
    var.clear();
    return addOptionParam(&var, var.name(), param);
  }

  // method: addOptionParam 
  //
  bool8 addOptionParam(SingleLinkedList<Byte>& var, const String& param) {
    var.clear();
    return addOptionParam(&var, var.name(), param);
  }

  // method: addOptionParam 
  //
  bool8 addOptionParam(SingleLinkedList<Short>& var, const String& param) {
    var.clear();
    return addOptionParam(&var, var.name(), param);
  }

  // method: addOptionParam 
  //
  bool8 addOptionParam(SingleLinkedList<Long>& var, const String& param) {
    var.clear();
    return addOptionParam(&var, var.name(), param);
  }

  // method: addOptionParam 
  //
  bool8 addOptionParam(SingleLinkedList<Llong>& var, const String& param) {
    var.clear();
    return addOptionParam(&var, var.name(), param);
  }

  // method: addOptionParam 
  //
  bool8 addOptionParam(SingleLinkedList<Ushort>& var, const String& param) {
    var.clear();
    return addOptionParam(&var, var.name(), param);
  }

  // method: addOptionParam 
  //
  bool8 addOptionParam(SingleLinkedList<Ulong>& var, const String& param) {
    var.clear();
    return addOptionParam(&var, var.name(), param);
  }

  // method: addOptionParam 
  //
  bool8 addOptionParam(SingleLinkedList<Ullong>& var, const String& param) {
    var.clear();
    return addOptionParam(&var, var.name(), param);
  }

  // method: addOptionParam 
  //
  bool8 addOptionParam(SingleLinkedList<Float>& var, const String& param) {
    var.clear();
    return addOptionParam(&var, var.name(), param);
  }

  // method: addOptionParam 
  //
  bool8 addOptionParam(SingleLinkedList<Double>& var, const String& param) {
    var.clear();
    return addOptionParam(&var, var.name(), param);
  }

  //----------------------------------------
  //
  // class-specific public methods
  //  get methods
  //
  //----------------------------------------

  // method: getProgName
  //
  const String& getProgName() const{
    return prog_name_d;
  }

  // get unused argument methods:
  //  corresponding to the ordinal number specified, returns class data and
  //  checks leftovers (is there anything left after all good parameters were
  //  parsed?)
  //
  bool8 getArgument(String& arg, int32 ordinal_number) const;

  // method: numArguments
  //
  int32 numArguments() const {
    return args_d.length();
  }

  // method: getExpanded
  //
  bool8 getExpanded(String& arg) {
    return arg.assign(expanded_d);
  }

  // other get methods
  //
  int32 getOptionIndex(const String& param_name, bool8 prefix = false);
  bool8 getValue(String& value, const String& opt_name,
		   bool8 prefix = false);
  bool8 isPresent(const String& opt_name, bool8 prefix = false);

  //----------------------------------------
  //
  // class-specific public methods
  //  parse methods
  //
  //----------------------------------------

  // parse methods
  //
  bool8 parse(int argc, const char** argv);
  bool8 parse(const String& line);

  //---------------------------------------------------------------------------
  //
  // private methods
  //
  //---------------------------------------------------------------------------
private:

  // general add option methods
  //
  bool8 addOptionParam(void* var, const String& name, const String& param);

  // method: isMultipleParam
  //
  bool8 isMultipleParam(int32 index) {

    return (types_d(index).eq(SingleLinkedList<String>::name()) ||
	    types_d(index).eq(SingleLinkedList<Filename>::name()) ||
	    types_d(index).eq(SingleLinkedList<Byte>::name()) ||
	    types_d(index).eq(SingleLinkedList<Short>::name()) ||
	    types_d(index).eq(SingleLinkedList<Long>::name()) ||
	    types_d(index).eq(SingleLinkedList<Llong>::name()) ||
	    types_d(index).eq(SingleLinkedList<Ushort>::name()) ||
	    types_d(index).eq(SingleLinkedList<Ulong>::name()) ||
	    types_d(index).eq(SingleLinkedList<Ullong>::name()) ||
	    types_d(index).eq(SingleLinkedList<Float>::name()) ||
	    types_d(index).eq(SingleLinkedList<Double>::name()));
  }
};

// end of include file
//
#endif
