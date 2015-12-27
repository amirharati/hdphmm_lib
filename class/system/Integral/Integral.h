// file: $isip/class/system/Integral/Integral.h
// version: $Id: Integral.h 10640 2007-01-27 02:36:04Z tm334 $
//

// notes:
//
// (1) AH (07/08/2010): for gcc 4.4.4 compatibility,
//     we changed:
//        return ::wcsstr((wchar_t*)ws1, (wchar_t*)ws2);
//     to:
//        return ::wcsstr(ws1, ws2);
//
// (2) JP (07/20/2010): for gcc 4.4.4 and 64-bit compatibility,
//     we added a new include file, inttypes.h.
//
// (3) AH (07/21/2010): for 64-bit compatibility we have changed
//     all code according to new defined types
// (4) AH (07/30/2010): for 64-bit compatibility another hash function
//     has been added for 64-bit vectors

// make sure definitions are only made once:
//  the isip convention is to use the class name preceded by "ISIP_"
//
#ifndef ISIP_INTEGRAL
#define ISIP_INTEGRAL

// system include files - since all classes include a debug method
// which calls Console, a FILE* is required. we will include stdio.h
// here, in order that every class need not replicate this. for
// convenience, we also include stdlib.h, since this contains many
// useful C functions. math.h and limits.h define useful constants and
// system functions. unistd.h is included for the definition of
// sleep.
//
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>
#include <unistd.h>
#include <time.h>
#include <iostream>
#include <inttypes.h>
using namespace std;

// system include files needed for non Solaris systems
//
#if ISIP_WCHAR_MODE == ISIP_WCHAR_REDHAT
#include <wchar.h>
#endif

// include the configure output
//
#define ISIP_INTERNAL_USE_ONLY
#include <IntegralConfigure.h>
#undef ISIP_INTERNAL_USE_ONLY

// include the internal integral types
//
#define ISIP_INTERNAL_USE_ONLY
#include <IntegralTypes.h>
#undef ISIP_INTERNAL_USE_ONLY

// include the internal namespace conflict prevention list
//
#define ISIP_INTERNAL_USE_ONLY
#include <IntegralNameSpace.h>
#undef ISIP_INTERNAL_USE_ONLY

// forward class definition(s)
//
class SysString;
class SysChar;

// Integral: define some low level system functions to be used by
// other classes.
//
class Integral {

  //---------------------------------------------------------------------------
  //
  // public constants
  //
  //---------------------------------------------------------------------------
 public:
  
  // define the class name
  //
  static const SysString CLASS_NAME;
  
  //-----------------------------------------
  //
  // operating system related string constants
  //
  //-----------------------------------------  

  // define environmental variables which should be present
  //
  static const SysString ENV_ISIP;
  static const SysString ENV_HOME;

  // define some constants that facilitate parsing of environment variables
  // and file pathnames under unix
  //
  static const SysChar ENV_MARKER;
  static const SysChar DIR_DELIM;
  static const SysChar DIR_HOME;

  // define some unix commands
  //
  static const SysString UNIX_CMD_COPY;
  static const SysString UNIX_CMD_MOVE;
  static const SysString UNIX_CMD_REDIR;

  // define some constants for temporary filename creation
  //
  static const SysString TMPDIR;
  static const SysString TMP_FMT_0;
  static const SysString TMP_FMT_1;
  static const SysString TMP_TEMPLATE;

  // define some constants related to help message generation
  //
  static const SysString HELP_FORMAT;
  static const SysString HELP_OPTION;

  //----------------------------------------
  //
  // operating system related enumerated constants
  //
  //----------------------------------------  

  // define negative and positive sign
  //
  static const int32 NEGATIVE = -1;
  static const int32 POSITIVE = 1;
  
  // define some sorting and comparison constants - they are useful from time
  // to time to have a global notion of the result of the order of things.
  // these constants should be used for sorting classes, comparisons, etc.
  //
  enum ORDER { ASCENDING = 0, DESCENDING, COLLATING, DEF_ORDER = ASCENDING };
  enum COMPARE { LESSER = 0, EQUAL, GREATER, DEF_COMPARE = EQUAL };

  // define constants that control the behavior of the clear method
  //
  enum CMODE { RETAIN = 0, RESET, RELEASE, FREE, DEF_CMODE = RESET };

  // define constants that control the behavior of the graph class
  //
  enum COLOR { WHITE = 0, GREY, BLACK, BLUE, GREEN, DEF_COLOR = WHITE };
  
  // define constants for representing the storage mode of a matrix -
  // it is again useful to have a global notion of the storage type of
  // a matrix:
  //
  //  MatrixFloat a(Integral::SYMMETRIC);
  //  MatrixLong  b(Integral::SYMMETRIC);
  //
  // vs.
  // 
  //  MatrixFloat a(MatrixFloat::SYMMETRIC);
  //  MatrixLong  b(MatrixLong::SYMMETRIC);
  //
  enum MTYPE { FULL = 0, DIAGONAL, SYMMETRIC,
	       LOWER_TRIANGULAR, UPPER_TRIANGULAR, SPARSE,
	       UNCHANGED, UNKNOWN, DEF_MTYPE = FULL };

  // define a return value for exiting
  //
  static const int32 SYS_RETURN_ERROR = 1;
  static const int32 SYS_RETURN_NOERROR = 0;

  // define some debugging constants
  //
  enum DEBUG { NONE = 0, BRIEF, DETAILED, ALL, DEF_DEBUG = NONE };

  //----------------------------------------
  //
  // other numeric constants
  //
  //----------------------------------------  

  // define some maximum sizes (i/o in unix still needs some fixed
  // buffers every now and then)
  //
  static const int32 MAX_FNAME_SIZE = PATH_MAX;

  // define some constants related to geometry and pi
  //
  static const float64 PI = M_PI;
  static const float64 TWO_PI = (2.0*M_PI);
  static const float64 HALF_PI = (M_PI_2);
  static const float64 QUARTER_PI = (M_PI_4);
  static const float64 SQRT_TWO_PI = 2.506628274631;
  static const float64 INV_PI = M_1_PI;
  static const float64 TWO_INV_PI = M_2_PI;
  static const float64 SQRT_TWO = M_SQRT2;
  static const float64 INV_SQRT_TWO_PI = (1.0 / 2.506628274631);
  static const float64 DEGREES_IN_CIRCLE = 360.0;
  
  // define a iteration count for testing random functions in diagnose method
  //
  static const int32 DIAG_ITER_COUNT = 100;

  // default arguments to find methods
  //
  static const int32 NO_POS = -1;
  
  // define important powers of two
  //
  static const float64 TWO_EXP7  = ((uint32)1 << 7);
  static const float64 TWO_EXP8  = ((uint32)1 << 8);
  static const float64 TWO_EXP15 = ((uint32)1 << 15);
  static const float64 TWO_EXP16 = ((uint32)1 << 16);
  static const float64 TWO_EXP23 = ((uint32)1 << 23);
  static const float64 TWO_EXP24 = ((uint32)1 << 24);
  static const float64 TWO_EXP31 = ((uint32)1 << 31);
  static const float64 TWO_EXP32 = ((uint64)1 << 32);
  static const float64 TWO_EXP63 = ((uint64)1 << 63);
  static const float64 TWO_EXP64 = (((uint64)1 << 63) << 1) ;
  
  // define constants related to natural logarithms
  //
  static const float64 E = M_E;
  static const float64 LOG2E = M_LOG2E;
  static const float64 LOG10E = M_LOG10E;
  static const float64 LN2 = M_LN2;
  static const float64 LN10 = M_LN10;

  // define constants related to changing the base of a logarithm:
  //  currently, we only need to accommodate base 2
  //
  static const float64 INV_LN2 = 1.0 / M_LN2;  
  static const float64 INV_LN10 = 1.0 / M_LN10;  

  // define the square root and inverse of square root of 2
  //
  static const float64 SQRT2 = M_SQRT2;
  static const float64 INV_SQRT2 = M_SQRT1_2;
  
  // define dB constants
  //  
  static const float64 DB_POW_MIN_VALUE = 1.0e-10;
  static const float64 DB_POW_SCALE_FACTOR = 10.0;
  
  static const float64 DB_MAG_MIN_VALUE = 1.0e-10;
  static const float64 DB_MAG_SCALE_FACTOR = 20.0;

  static const float64 DB_LOG_MIN_VALUE = -1.0e10;  
  static const float64 DB_MIN_VALUE = -100.0;

  // define dB limits:
  //  1. MIN_LOG_VALUE is computed as follows:
  //     MIN_SCORE = -1e+10 = -1 / exp(MIN_LOG_SCORE)
  //
  static const float64 MIN_LOG_VALUE = -23.02585093;

  //----------------------------------------
  //
  // default values and arguments
  //
  //----------------------------------------  

  // default arguments to methods
  //
  static const int32 DEF_GROW_SIZE = 1024;
  
  // default precision values
  //
  // the almostEqual method compares two numbers to a user-specified
  // level of precision.  the precision is specified as a percentage
  // of the arguments.  the scale is used to control the range over
  // which the comparison is imposed.
  //
  static const float64 DEF_PERCENTAGE = 0.1;
  static const float64 DEF_BOUND = 0.01;

  //---------------------------------------
  //
  // error codes
  //
  //---------------------------------------

  static const int32 ERR = 1500;

  //---------------------------------------------------------------------------
  //
  // protected data
  //
  //---------------------------------------------------------------------------
 protected:

  // declare a static debug level:
  //  the debug flag is static because the Integral class is never instantiated
  //
  static Integral::DEBUG debug_level_d;
  
  //---------------------------------------------------------------------------
  //
  // required public methods
  //
  //---------------------------------------------------------------------------
 public:
  
  // method: name
  //
  static const SysString& name() {
    return CLASS_NAME;
  }

  // other static methods
  //
  static bool8 diagnose(DEBUG debug_level);
  
  // method: setDebug
  //
  static bool8 setDebug(Integral::DEBUG level) {
    debug_level_d = level;
    return true;
  }

  // other debug methods:
  //  generally, the debug method is non-static. however,
  //  here it must be static so that the class can be called without being
  //  instantiated
  //
  static bool8 debug(const unichar* message);
  
  // destructor/constructor(s) are private
  //

  // assign methods:
  //  these methods are omitted because Integral objects
  //  can not be instantiated
  //

  // operator= methods:
  //  these methods are omitted because Integral objects
  //  can not be instantiated
  //
  
  // i/o methods:
  //  these methods are omitted because Integral objects
  //  can not be instantiated
  //

  // equality methods:
  //  these methods are omitted because Integral objects
  //  can not be instantiated
  //

  // memory management methods:
  //  these methods are omitted because Integral objects
  //  can not be instantiated
  //

  //---------------------------------------------------------------------------
  //
  // class-specific public methods:
  //  general operating system methods
  //
  //---------------------------------------------------------------------------

  // wrappers for operating system methods:
  //  environmental variables
  //
  static bool8 getEnv(SysString& val, const SysString& var);
  static bool8 getLoginDir(SysString& directory,
			     const SysString& login_name);
  static bool8 expandName(SysString& exp_file, const SysString& in_file);

  // method: getPid
  //  get a process id number
  //
  static int32 getPid() {
    return (int32)(getpid());
  }

  // method: getParentPid
  //  get the parent process id number
  //
  static int32 getParentPid() {
    return (int32)getppid();
  }
  
  // method: getHostid
  //  get a host id number
  //
  static int32 getHostid() {
    return (int32)(gethostid());
  }
  
  // wrapper for operating system methods:
  //  cleanly exit a program by invoking proper garbage collection
  //
  static int32 exit();
  
  // wrappers for operating system methods:
  //  temporary files
  //
  static bool8 makeTemp(SysString& tmp_file, const SysString& name);
  static bool8 makeTemp(SysString& tmp_file);

  //---------------------------------------------------------------------------
  //
  // class-specific public methods:
  //  bit-level methods
  //
  //---------------------------------------------------------------------------

  // method: almostEqual (generalized case)
  //  the general implementation of almostEqual performs a bitwise comparison
  //  between the arguments and checks for equality. this is useful
  //  for types such as integers and chars. this is not the main use
  //  of this method. it is really intended to compare floating point
  //  quantities to a user-specified level of precision. note that the
  //  default values supplied here are essentially ignored.
  //
  //  note that overloads are used as opposed to default values since
  //  default values do not work in concert with template specializations.
  //
  template <class TIntegral>
    static bool8 almostEqual(TIntegral arg1, TIntegral arg2,
			       float64 percent = DEF_PERCENTAGE,
			       float64 bound = DEF_BOUND) {
    return (arg1 == arg2);
  }

  // method: almostEqual
  //  define a specialized version for floats. the main reason for this
  //  method is to make sure the float64 version gets called for floating
  //  point numbers (avoiding type ambiguity).
  //
  static bool8 almostEqual(float32 arg1, float32 arg2,
			     float64 percent = DEF_PERCENTAGE,
			     float64 bound = DEF_BOUND) {
    return almostEqual((float64)arg1, (float64)arg2, percent, bound);
  }

  // method: almostEqual
  //  define a specialized version for doubles
  //
  static bool8 almostEqual(float64 arg1, float64 arg2,
			     float64 percent = DEF_PERCENTAGE,
			     float64 bound = DEF_BOUND);
  
  // method: almostEqual
  //  define a specialized version for complexfloats. the main reason
  //  for this method is to make sure the double version gets called
  //  for floating point numbers (avoiding type ambiguity).
  //
  static bool8 almostEqual(const complexfloat& arg1,
			     const complexfloat& arg2,
			     float64 percent = DEF_PERCENTAGE,
			     float64 bound = DEF_BOUND) {
    return (almostEqual(arg1.real(), arg2.real(), percent, bound) &&
	    almostEqual(arg1.imag(), arg2.imag(), percent, bound));
  }

  // method: almostEqual
  //  define a specialized version for complexdouble. the main reason
  //  for this method is to make sure the double version gets called
  //  for floating point numbers (avoiding type ambiguity).
  //
  static bool8 almostEqual(const complexdouble& arg1,
			     const complexdouble& arg2,
			     float64 percent = DEF_PERCENTAGE,
			     float64 bound = DEF_BOUND) {
    return (almostEqual(arg1.real(), arg2.real(), percent, bound) &&
	    almostEqual(arg1.imag(), arg2.imag(), percent, bound));
  }

  //---------------------------------------------------------------------------
  //
  // class-specific public methods:
  //  inlined wrappers for math and other C functions (listed alphabetically)
  //
  //---------------------------------------------------------------------------

  // method: abs
  //
  static float64 abs(float64 arg) {
    return ::fabs(arg);
  }

  // method: acos
  //
  static float64 acos(float64 arg) {
    return ::acos(arg);
  }

  // method: acosh
  //
  static float64 acosh(float64 arg) {
    return ::log(arg + ::sqrt(arg * arg - (float64)1));
  }

  // method: asin
  //
  static float64 asin(float64 arg) {
    return ::asin(arg);
  }

  // method: asinh
  //
  static float64 asinh(float64 arg) {
    return ::log(arg + ::sqrt(arg * arg + (float64)1));
  }

  // method: atan
  //
  static float64 atan(float64 arg) {
    return ::atan(arg);
  }

  // method: atanh
  //
  static float64 atanh(float64 arg) {
    return 0.5 * ::log(((float64)1 + arg) / ((float64)1 - arg));
  }

  // method: ceil
  //
  static float64 ceil(float64 arg) {
    return ::ceil(arg);
  }

  // method: cos
  //
  static float64 cos(float64 arg) {
    return ::cos(arg);
  }

  // method: cosh
  //
  static float64 cosh(float64 arg) {
    return ::cosh(arg);
  }

  // method: exp
  //
  static float64 exp(float64 arg) {
    return ::exp(arg);
  }

  // method: exp2
  //
  static float64 exp2(float64 arg) {
    return ::exp(arg * LN2);
  }

  // method: exp10
  //
  static float64 exp10(float64 arg) {
    return ::exp(arg * LN10);
  }

#if ISIP_WCHAR_MODE == ISIP_WCHAR_NONE
  
  // method: fgetc
  //
  static int32 fgetc(FILE* stream) {
    return ::fgetc(stream);
  }
#endif
  
#if ISIP_WCHAR_MODE == ISIP_WCHAR_NONE

  // method: fgets
  //
  static byte8* fgets(byte8* s, int32 n, FILE* stream) {
    return (byte8*)::fgets((char*)s, n, stream);
  }
#endif

#if ISIP_WCHAR_MODE != ISIP_WCHAR_NONE

  // method: fgetwc
  //
  static wint_t fgetwc(FILE* stream) {
    return ::fgetwc(stream);
  }
#endif

#if ISIP_WCHAR_MODE != ISIP_WCHAR_NONE

  // method: fgetws
  //
  static unichar* fgetws(unichar* s, int32 n, FILE* stream) {
    return ::fgetws(s, n, stream);
  }
#endif
  
  // method: floor
  //
  static float64 floor(float64 arg) {
    return ::floor(arg);
  }


#if ISIP_WCHAR_MODE == ISIP_WCHAR_NONE
  
  // method: fputc
  //
  static int32 fputc(int32 c, FILE* stream) {
    return ::fputc(c, stream);
  }
#endif
  
#if ISIP_WCHAR_MODE == ISIP_WCHAR_NONE

  // method: fputs
  //
  static int32 fputs(byte8* s, FILE* stream) {
    return ::fputs((char*)s, stream);
  }
#endif
  
#if ISIP_WCHAR_MODE != ISIP_WCHAR_NONE

  // method: fputwc
  //
  static wint_t fputwc(wint_t c, FILE* stream) {
    return ::fputwc(c, stream);
  }
#endif
  
#if ISIP_WCHAR_MODE != ISIP_WCHAR_NONE
  
  // method: fputws
  //
  static int32 fputws(const unichar* s, FILE* stream) {
    return ::fputws(s, stream);
  }  
#endif
  
  // method: fraction
  //
  static float64 fraction(float64 arg) {
    static float64 temp;
    return ::modf(arg, &temp);
  }

  // method: fseek
  //
  static int32 fseek(FILE* fptr, int32 offset, int32 whence) {
    return fseek(fptr, offset, whence);
  }
  
  // method: hash
  // hash methods for byte8, uint16, int16, uint32, int64, uint64,
  // float, float64, int32.
  static uint32 hash(byte8 val, uint32 capacity) {
    uint32 temp = (uint32)val;
    return hash_32(temp, capacity);    
  }
  
  static uint32 hash(uint16 val, uint32 capacity) {
    uint32 temp = (uint32)val;
    return hash_32(temp, capacity);            
  }
  
  static uint32 hash(int16 val, uint32 capacity) {
    int32 copy = (int32) val;
    int32 temp = *((int32*) &copy);
    return hash_32(temp, capacity);        
  }
  
  static uint32 hash(uint32 val, uint32 capacity) {
    return hash_32(val, capacity);            
  }
  
  static uint32 hash(int64 val, uint32 capacity) {
    int64 copy = (int64) val;
    int64 temp = *((int64*) &copy);
    return hash_64(temp, capacity);        
  }
  
  static uint32 hash(uint64 val, uint32 capacity) {
    uint64 temp = (uint64)val;
    return hash_64(temp, capacity);        
  }
  
  static uint32 hash(float32 val, uint32 capacity) {
    // we don't know what size a float is so we move it to a 32 bit number
    // so we can guarantee the size
    //    
    float32 copy = (float32) val;

    // we want to reinterpret those 32 bits as an integer. If we were to
    // cast then we would greatly reduce the variability in the possible
    // numbers. Instead, we cast the location pointer to an integer pointer
    // so the the 32-bit float will be interpreted as a 32-bit integer
    // the full range of variablity in the 32 bits is preserved
    //
    int32 temp = *((int32*) &copy);
    cout << "Integral::hash(float32, uint32)" << endl;
    cout << val << endl;
    cout << temp<< endl;
    cout << capacity << endl;
    return hash_32(temp, capacity);    
  }
  
  static uint32 hash(float64 val, uint32 capacity) {
    float64 copy = (float64) val;
    int64 temp = *((int64*) &copy);
    cout << "Integral::hash(float64, uint32)" << endl;
    cout << val << endl;
    cout << temp<< endl;
    cout << capacity << endl;
    return hash_64(temp, capacity);        
  }
  
  static uint32 hash(int32 val, uint32 capacity) {
    int32 copy = (int32) val;
    int32 temp = *((int32*) &copy);
    return hash_32(temp, capacity);        
  }

  // method: hash
  // for 32 bits single value
  static uint32 hash_32(uint32 val, uint32 capacity) {
    return val % (capacity - 1);
  }
  
  // method: hash_64
  // for 64 bits single value
  static uint32 hash_64(uint64 val, uint32 capacity) {
    return val % (capacity - 1);
  }  
  
  // for 32 bits vector
  static int32 hash(uint32* vector, int32 num_elements, int32 capacity);

// for 64 bits vector
  static int64 hash(uint64* vector, int32 num_elements, int32 capacity);
    
    
  // method: integer
  //
  static float64 integer(float64 arg) {
    static float64 integ;
    ::modf(arg, &integ);
    return integ;
  }

  // method: log
  //
  static float64 log(float64 arg) {
    return ::log(arg);
  }

  // method: log2
  //
  static float64 log2(float64 arg) {
    return ::log(arg) * INV_LN2;
  }

  // method: log10
  //
  static float64 log10(float64 arg) {
    return ::log10(arg);
  }

  // method: log1p
  //
  static float64 log1p(float64 arg) {
    return ::log((float64)1 + arg);
  }

  // method: max
  //
  static float64 max(float64 arg1, float64 arg2) {
    if (arg1 > arg2) {
      return arg1;
    }
    else {
      return arg2;
    }
  }

  // method: min
  //
  static float64 min(float64 arg1, float64 arg2) {
    if (arg1 < arg2) {
      return arg1;
    }
    else {
      return arg2;
    }
  }

  // method: pow
  //
  static float64 pow(float64 arg, float64 exponent) {
    return ::pow(arg, exponent);
  }

  // method: round
  //
  static float64 round(float64 arg) {
    if (arg > (float64)0) {
      return ::floor(arg + 0.5);
    }
    else {
      return ::ceil(arg - 0.5);
    }
  }

  // method: sin
  //
  static float64 sin(float64 arg) {
    return ::sin(arg);
  }

  // method: sinh
  //
  static float64 sinh(float64 arg) {
    return ::sinh(arg);
  }

  // method: sleep
  //
  static bool8 sleep(int32 sleep_seconds) {
    ::sleep(sleep_seconds);
    return true;
  }
  
  // method: sqrt
  //
  static float64 sqrt(float64 arg) {
    return ::sqrt(arg);
  }

  // method: tan
  //
  static float64 tan(float64 arg) {
    return ::tan(arg);
  }

  // method: tanh
  //
  static float64 tanh(float64 arg) {
    return ::tanh(arg);
  }
  
#if ISIP_WCHAR_MODE == ISIP_WCHAR_SOLARIS
  
  // method: wcswcs
  //  
  static unichar* wcswcs(const unichar* ws1, const unichar* ws2) {
    
    // call the solaris 2.6 system function
    //
    return ::wcswcs(ws1, ws2);
  }
#endif
  
#if ISIP_WCHAR_MODE != ISIP_WCHAR_SOLARIS
  
  // method: wcsstr
  //
  static unichar* wcsstr(const unichar* ws1, const unichar* ws2) {
    
    // call the more standard system function
    //
    return (unichar*)::wcsstr(ws1, ws2);    
  }
#endif

#if ISIP_WCHAR_MODE == ISIP_WCHAR_SOLARIS
  
  // method: wcstok
  //
  static unichar* wcstok(unichar* ws, const unichar* delim, unichar** ptr) {
    
    // solaris 2.6 needs an older version of wcstok
    //
    return ::wcstok(ws, delim);
  }
#endif
  
#if ISIP_WCHAR_MODE != ISIP_WCHAR_SOLARIS

  // method: wcstok
  //
  static unichar* wcstok(unichar* ws, const unichar* delim, unichar** ptr) {
    
    // any other supporting operating system uses the new definition
    //
    return ::wcstok(ws, delim, ptr);    
  }  
#endif
  
  //---------------------------------------------------------------------------
  //
  // class-specific public methods:
  //  complex versions of math and other C functions (listed alphabetically)
  //
  //  the implementations used below can be found in:
  //
  //   R.V. Churchill, J.W. Brown, and R.F. Verhey,
  //   Complex Variables and Applications, Mc-Graw Hill,
  //   New York, New York, USA, 1976, pp. 52-71.
  //
  //---------------------------------------------------------------------------

  // method: abs
  //
  static float64 abs(const complexdouble& arg) {
    return arg.mag();
  }

  // method: acos
  //
  static complexdouble acos(const complexdouble& arg) {
    static const complexdouble j(0, 1);
    return (complexdouble)-1 * j *
      log(arg + j * sqrt((complexdouble)1 - arg * arg));
  }

  // method: acosh
  //
  static complexdouble acosh(const complexdouble& arg) {
    return complexdouble (log(arg + sqrt(arg * arg - (complexdouble)1)));
  }

  // method: asin
  //
  static complexdouble asin(const complexdouble& arg) {
    static const complexdouble j(0, 1);
    return (complexdouble)-1 * j *
      log((j * arg) + sqrt((complexdouble)1 - (arg * arg)));
  }

  // method: asinh
  //
  static complexdouble asinh(const complexdouble& arg) {
    return complexdouble(log(arg + sqrt(arg * arg + (complexdouble)1)));
  }

  // method: atan
  //
  static complexdouble atan(const complexdouble& arg) {
    static const complexdouble j(0, 1);
    return log((j + arg) / (j - arg)) * j / (complexdouble)2;
  }

  // method: atanh
  //
  static complexdouble atanh(const complexdouble& arg) {
    return log(((complexdouble)1 + arg) / 
	       ((complexdouble)1 - arg)) / (complexdouble)2;
  }

  // method: ceil
  //
  static complexdouble ceil(const complexdouble& arg) {
    return complexdouble(ceil(arg.real()), ceil(arg.imag()));
  }

  // method: cos
  //
  static complexdouble cos(const complexdouble& arg) {
    return complexdouble(cos(arg.real()) * cosh(arg.imag()),
			 - sin(arg.real()) * sinh(arg.imag()));
  }
  
  // method: cosh
  //
  static complexdouble cosh(const complexdouble& arg) {
    return complexdouble(cosh(arg.real()) * cos(arg.imag()),
			 + sinh(arg.real()) * sin(arg.imag()));
  }

  // method: exp
  //
  static complexdouble exp(const complexdouble& arg) {
    return complexdouble::polar(exp(arg.real()), arg.imag());
  }

  // method: exp2
  //
  static complexdouble exp2(const complexdouble& arg) {
    return exp(arg * LN2);
  }

  // method: exp10
  //
  static complexdouble exp10(const complexdouble& arg) {
    return exp(arg * LN10);
  }
  
  // method: floor
  //
  static complexdouble floor(const complexdouble& arg) {
    return complexdouble(floor(arg.real()), floor(arg.imag()));
  }
   
  // method: log
  //
  static complexdouble log(const complexdouble& arg) {
    return complexdouble(log(arg.mag()), arg.angle());
  }

  // method: log2
  //
  static complexdouble log2(const complexdouble& arg) {
    return log(arg) * INV_LN2;
  }

  // method: log10
  //
  static complexdouble log10(const complexdouble& arg) {
    return log(arg) * INV_LN10;
  }

  // method: log1p
  //
  static complexdouble log1p(const complexdouble& arg) {
    return log((complexdouble)1 + arg);
  }

  // method: max
  //
  static complexdouble max(const complexdouble& arg1,
			   const complexdouble& arg2) {
    if (arg1 >= arg2) {
      return arg1;
    }
    else {
      return arg2;
    }
  }

  // method: min
  //
  static complexdouble min(const complexdouble& arg1,
			   const complexdouble& arg2) {
    if (arg1 < arg2) {
      return arg1;
    }
    else {
      return arg2;
    }
  }

  // method: pow
  //
  static complexdouble pow(const complexdouble& arg,
			   const complexdouble& exponent) {
    return exp(exponent * log(arg));
  }

  // method: round
  //
  static complexdouble round(const complexdouble& arg) {
    return complexdouble(round(arg.real()), round(arg.imag()));
  }

  // method: sin
  //
  static complexdouble sin(const complexdouble& arg) {
    return complexdouble(sin(arg.real()) * cosh(arg.imag()),
			 cos(arg.real()) * sinh(arg.imag()));
  }

  // method: sinh
  //
  static complexdouble sinh(const complexdouble& arg) {
    return complexdouble(sinh(arg.real()) * cos(arg.imag()),
			 cosh(arg.real()) * sin(arg.imag()));
  }

  // method: sqrt
  //
  static complexdouble sqrt(const complexdouble& arg) {
    float64 r = arg.mag();
    float64 nr, ni;
    if (r == 0.0) {
      ni = r;
      nr = r;
    }
    else if (arg.real() > 0) {
      nr = sqrt(0.5 * (r + arg.real()));
      ni = arg.imag() / nr;
      ni /= 2;
    }
    else {
      ni = sqrt(0.5 * (r - arg.real()));
      if (arg.imag() < 0) {
	ni = -ni;
      }
      nr = arg.imag() / ni;
      nr /= 2;
    }
    return complexdouble(nr, ni);
  }

  // method: tan
  //
  static complexdouble tan(const complexdouble& arg) {
    return sin(arg) / cos(arg);
  }

  // method: tanh
  //
  static complexdouble tanh(const complexdouble& arg) {
    return sinh(arg) / cosh(arg);
  }

  //---------------------------------------------------------------------------
  //
  // class-specific public methods:
  //  other math functions that are useful for speech research
  //
  //---------------------------------------------------------------------------

  // logarithm-related methods
  //
  static double logAddLog(const float64 x, const float64 y);

  //---------------------------------------------------------------------------
  //
  // class-specific public methods:
  //  functions that are useful for time measurements
  //
  //---------------------------------------------------------------------------
  
  // method: time
  //  method that returns the time in seconds since the Epoch (00:00:00
  //  January 1, 1970, Coordinated Universal Time (UTC))
  //
  static int32 time() {
    time_t* p = (time_t*)NULL;
    return (int32)::time(p);
  }

  // method: cTime
  //
  static bool8 cTime(SysString& time);
  
  // method: utcTime
  //
  static bool8 utcTime(SysString& time);
  
  //---------------------------------------------------------------------------
  //
  // private methods
  //
  //---------------------------------------------------------------------------
 private:

  // destructor/constructor(s):
  //  these methods are private so the class cannot be instantiated.
  //
  ~Integral();
  Integral();
  Integral(const Integral& arg);
};

  // end of include file
  //
#endif
