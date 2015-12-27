// file: $isip/class/system/Integral/IntegralTypes.h
// version: $Id: IntegralTypes.h 10641 2007-01-27 06:03:30Z tm334 $
//
// notes:
//
// (1) JP (07/19/2010): with the advent of 64-bit machines, we overhauled
//     the way isip handles data types. instead of allowing them to
//     be automatically promoted to different sizes, we did away
//     with our internal typedefs (e.g., ullong) and simply used
//     standard C types such as uint64_t.
//
// (2) AH (07/20/2010): we had to move the include file for SysComplex
//     until after all the basic scalar typedefs because SysComplex
//     needs these definitions. now that we are not using standard C
//     types, such as float, and using our typedef float32 instead,
//     we had to move the include after these defines.
//

// system include file
//
#define __lint
#include <wctype.h>

// this is the basic isip environment include file. all Integral types
// are defined in this file. these are also implemented as C++ classes.
// all software must be built upon these basic types.
//
// these definitions follow a format in which the data type is related
// to particular machine defined formats. 

// this file is for internal use only
//
#ifdef ISIP_INTERNAL_USE_ONLY

// make sure definitions are only made once
// follow the standard isip convention in defining the symbol to be
// used to signal the preprocessor
//
#ifndef ISIP_INTEGRAL_TYPES
#define ISIP_INTEGRAL_TYPES

// Integral type #1: boolean or boolean variables
//
typedef bool bool8;

// Integral type #2: a single byte of data
//
typedef unsigned char byte8;
typedef unsigned char ubyte8;

// Integral type #3: a character
//
// a character object is a multi-byte unicode index number. in order
// to support unicode in our environment, the classes SysChar and
// SysString exist at the lowest levels (the system library) with
// automatic conversions for both standard C strings (7-bit
// characters) and other standard encoding schemes.
//
typedef wchar_t unichar;

// Integral type #4: an unsigned integer
//
typedef uint16_t      uint16;
typedef uint32_t      uint32; 
typedef uint64_t      uint64;
//typedef __uint128_t uint128;

// Integral type #5: a signed integer
//
typedef int16_t       int16;
typedef int32_t       int32; 
typedef int64_t       int64;
//typedef __int128_t  int128;

// Integral type #6: a real floating point number
//
typedef float         float32;
typedef double        float64;

// we include the complex number class so we can define complex number integral
// types. we have to do this after the basic types have been defined because
// these types are used in SysComplex.
//
#ifndef ISIP_SYS_COMPLEX
#include <SysComplex.h>
#endif

// Integral type #7: a complex number

typedef SysComplex<float32> complexfloat;
typedef SysComplex<float64> complexdouble;
typedef SysComplex<int32>   complexlong;

// end of include file
//
#endif
#endif
