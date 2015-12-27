// file: $isip/class/system/Integral/IntegralNameSpace.h
// version: $Id: IntegralNameSpace.h 7328 2001-08-24 20:28:14Z hamaker $
//

// while not standard part of the ANSI standard, some operating
// systems define preprocessor constants that interfere with our
// constant names. since these macros are part of the preprocessor as
// opposed to the compiler, proper namespace isolation is not possible
// since macros are expanded regardless of meaning. we solve this
// problem by simply un-defining all constant names that are known to
// cause conflicts with our names.
//
// please email help@isip.msstate.edu if you encounter a namespace
// conflict and we will add it to the list. these preprocessor
// namespace conflicts are very confusing to the compiler, so the
// error reported by g++ will look something like this:
//
//  g++ -I/isip/tools/include -Wall  -c itgl_abs_00.cc
//  In file included from itgl_abs_00.cc:7:
//  Integral.h:140: `static' can only be specified for objects and functions
//  Integral.h:140: confused by earlier errors, bailing out
//  make: *** [itgl_abs_00.o] Error 1
//
// the `g++ -E` option, show preprocessor output, is very helpful for
// tracking things like this down if they are not obvious.
//
// note that we do not allow conflicts with the Solaris 2.6 or 2.7
// operating system, our primary development environment.
//

// this file is for internal use only
//
#ifdef ISIP_INTERNAL_USE_ONLY

// known to cause problems with Slackware Linux
//
#undef PI

// known to cause problems with RedHat Linux
//
#undef BIG_ENDIAN
#undef LITTLE_ENDIAN

// end of include file
//
#endif

