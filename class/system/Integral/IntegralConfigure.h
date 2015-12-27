// file: $isip/class/system/Integral/IntegralConfigure.h.in
// version: $Id: IntegralConfigure.h.in 5264 2000-10-09 22:06:16Z duncan $
//

// this file is parsed by configure to provide the platform dependent
// variables. it is included by Integral.h so that all code has access
// to these macros and definitions
//

// this file is for internal use only
//
#ifdef ISIP_INTERNAL_USE_ONLY

// any non-solaris system (include redhat specifically as the same value)
//
#define ISIP_WCHAR_NONE 0   
#define ISIP_WCHAR_REDHAT 0

// any solaris except 2.7
//
#define ISIP_WCHAR_SOLARIS 1 

// solaris 2.7
//
#define ISIP_WCHAR_SOLARIS_27 2 

#define ISIP_WCHAR_MODE ISIP_WCHAR_NONE

// end of file
//
#endif
