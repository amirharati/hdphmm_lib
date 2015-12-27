// file: $isip/class/system/Integral/itgl_02.cc
// version: $Id: itgl_02.cc 10636 2007-01-26 22:18:09Z tm334 $
//

// isip include files
//
#include "Integral.h"

#include <Console.h>
#include <SysString.h>


// method: diagnose
//
// arguments:
//  DEBUG level: (input) debug level for diagnostics
//
// return: a boolean value indicating status
//
bool8 Integral::diagnose(DEBUG level_a) {


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
  
  // test the debug methods
  //
  setDebug(debug_level_d);
  
  if (level_a > Integral::BRIEF) {
    Integral::debug(L"debug");
  }
  
  // reset indentation
  //
  if (level_a > Integral::NONE) {
    Console::decreaseIndention();
  }
  
  //--------------------------------------------------------------------------
  //
  // 2. class-specific public methods:
  //     general operating system methods
  //
  //--------------------------------------------------------------------------

  // set indentation
  //
  if (level_a > Integral::NONE) {
    Console::put(L"testing class-specific public methods: general operating system methods...\n");
    Console::increaseIndention();
  }
  
  // test getEnv
  //
  SysString var(L"HOME");
  SysString val;
  bool8 ret;
  
  ret = Integral::getEnv(val, var);
   
  if (level_a > Integral::DETAILED) {
    var.debug(L"var");
    val.debug(L"val");
    Console::put(L"\n");
  }
  if ((!ret) || (val.length() == 0)) {
    Error::handle(name(), L"getEnv", Error::TEST, __FILE__, __LINE__);
  }
  
  // test getLoginDir
  //
  var.assign(L"root");
  ret = Integral::getLoginDir(val, var);
  if (level_a > Integral::DETAILED) {
    var.debug(L"var");
    val.debug(L"val");
    Console::put(L"\n");
  }
  if ((!ret) || (val.length() == 0)) {
    Error::handle(name(), L"getLoginDir", Error::TEST, __FILE__, __LINE__);
  }
  
  // test expandName
  //
  var.assign(L"$isip_ifc/include/Integral.h");
  ret = Integral::expandName(val, var);
  if (level_a > Integral::DETAILED) {
    var.debug(L"var");
    val.debug(L"val");
    Console::put(L"\n");
  }
  if ((!ret) || (val.length() == 0)) {
    val.debug(L"val");
    var.debug(L"var");
    Error::handle(name(), L"expandName", Error::TEST, __FILE__, __LINE__);
  }
  
  var.assign(L"/tmp/\\$isip_ifc/include/Integral.h");
  ret = Integral::expandName(val, var);
  if ((!ret) || (!val.eq(L"/tmp/$isip_ifc/include/Integral.h"))) {
    var.debug(L"var");
    val.debug(L"val");
    Error::handle(name(), L"expandName", Error::TEST, __FILE__, __LINE__);
  }
  
  var.assign(L"~/login/editor_emacs_bindings.el");
  ret = Integral::expandName(val, var);
  if (level_a > Integral::DETAILED) {
    var.debug(L"var");
    val.debug(L"val");
    Console::put(L"\n");
  }
  if ((!ret) || (val.length() == 0)) {
    Error::handle(name(), L"expandName", Error::TEST, __FILE__, __LINE__);
  }
  
  var.assign(L"~/login/$ISIP_BINARY/editor_emacs_bindings.el");
  ret = Integral::expandName(val, var);
  if (level_a > Integral::DETAILED) {
    var.debug(L"var");
    val.debug(L"val");
    Console::put(L"\n");
  }
  if ((!ret) || (val.length() == 0)) {

    Error::handle(name(), L"expandName", Error::TEST, __FILE__, __LINE__);
  }
  
  var.assign(L"~root/$NO_VARIABLE_EXISTS/editor_emacs_bindings.el");
  ret = Integral::expandName(val, var);
  if (level_a > Integral::DETAILED) {
    var.debug(L"var");
    val.debug(L"val");
    Console::put(L"\n");
  }
  if ((ret) || (val.length() == 0)) {
    Error::handle(name(), L"expandName", Error::TEST, __FILE__, __LINE__);
  }
  
  var.assign(L"~root");
  ret = Integral::expandName(val, var);
  if (level_a > Integral::DETAILED) {
    var.debug(L"var");
    val.debug(L"val");
    Console::put(L"\n");
  }
  if ((!ret) || (val.length() == 0)) {
    Error::handle(name(), L"expandName", Error::TEST, __FILE__, __LINE__);
  }
  
  var.assign(L"~");
  ret = Integral::expandName(val, var);
  if (level_a > Integral::DETAILED) {
    var.debug(L"var");
    val.debug(L"val");
    Console::put(L"\n");
  }
  if ((!ret) || (val.length() == 0)) {
    Error::handle(name(), L"expandName", Error::TEST, __FILE__, __LINE__);
  }
  
  var.assign(L"~/");
  ret = Integral::expandName(val, var);
  if (level_a > Integral::DETAILED) {
    var.debug(L"var");
    val.debug(L"val");
    Console::put(L"\n");
  }
  if ((!ret)|| (val.length() == 0)) {
    Error::handle(name(), L"expandName", Error::TEST, __FILE__, __LINE__);
  }

  var.assign(L"/tmp/tmp_\\$\\$\\$");
  ret = Integral::expandName(val, var);
  if ((!ret) || (val.ne(L"/tmp/tmp_$$$"))) {
    var.debug(L"var");
    val.debug(L"val");
    Error::handle(name(), L"expandName", Error::TEST, __FILE__, __LINE__);
  }
  
  // test getPid and getParentPid
  //
  int32 pid = getPid();
  int32 ppid = getParentPid();

  if (level_a > Integral::DETAILED) {
    val.assign(pid);
    var.debugStr(name(), L"diagnose", L"pid", val);
    Console::put(var);
  }

  if (level_a > Integral::DETAILED) {
    val.assign(ppid);
    var.debugStr(name(), L"diagnose", L"ppid", val);
    Console::put(var);
  }
  
  // test exit(): we can't really test exit() in this method

  // test maketemp
  //
  makeTemp(val);
  if (level_a > Integral::DETAILED) {
    val.debug(L"makeTemp");
  }

  // reset indentation
  //
  if (level_a > Integral::NONE) {
    Console::decreaseIndention();
  }
  
  //--------------------------------------------------------------------------
  //
  // 3. class-specific public methods:
  //     bit-level methods
  //
  //--------------------------------------------------------------------------

  // set indentation
  //
  if (level_a > Integral::NONE) {
    Console::put(L"testing class-specific public methods: bit-level methods...\n");
    Console::increaseIndention();
  }
  
  // test almostEqual
  //
  if (!almostEqual(3.0001, 3.0000)) {
    return Error::handle(name(), L"almostEqual", Error::TEST,
			 __FILE__, __LINE__);
  }

  if (!almostEqual(3.1, 3.0, 10.0)) {
    return Error::handle(name(), L"almostEqual", Error::TEST,
			 __FILE__, __LINE__);
  }

  if (!almostEqual(3.0, 3.1, 10.0)) {
    return Error::handle(name(), L"almostEqual", Error::TEST,
			 __FILE__, __LINE__);
  }

  if (almostEqual((int32)300001, (int32)300002)) {
    return Error::handle(name(), L"almostEqual", Error::TEST,
			 __FILE__, __LINE__);
  }

  // reset indentation
  //
  if (level_a > Integral::NONE) {
    Console::decreaseIndention();
  }
  
  //--------------------------------------------------------------------------
  //
  // 4. class-specific public methods:
  //     inlined wrappers for math and other C functions
  //
  //--------------------------------------------------------------------------

  // set indentation
  //
  if (level_a > Integral::NONE) {
    Console::put(L"testing class-specific public methods: inline wrappers...\n");
    Console::increaseIndention();
  }
  
  if (!almostEqual(abs(-27.0), (float64)27.0)) {
    return Error::handle(name(), L"abs", Error::TEST, __FILE__, __LINE__);
  }

  if (!almostEqual(acos(0.0), M_PI_2)) {
    return Error::handle(name(), L"acos", Error::TEST, __FILE__, __LINE__);
  }

  if (!almostEqual(asin(1.0), M_PI_2)) {
    return Error::handle(name(), L"asin", Error::TEST, __FILE__, __LINE__);
  }

  if (!almostEqual(asinh(2.3013), M_PI_2)) {
    return Error::handle(name(), L"asinh", Error::TEST, __FILE__, __LINE__);
  }

  if (!almostEqual(atan(1.0), M_PI_4)) {
    return Error::handle(name(), L"atan", Error::TEST, __FILE__, __LINE__);
  }

  if (!almostEqual(atanh(0.9172), M_PI_2)) {
    return Error::handle(name(), L"atanh", Error::TEST, __FILE__, __LINE__);
  }

  if (!almostEqual(ceil(26.1), 27.0)) {
    return Error::handle(name(), L"ceil", Error::TEST, __FILE__, __LINE__);
  }

  if (!almostEqual(cos(M_PI_2), 0.0)) {
    return Error::handle(name(), L"cos", Error::TEST, __FILE__, __LINE__);
  }

  if (!almostEqual(cosh(0.0), 1.0)) {
    return Error::handle(name(), L"cosh", Error::TEST, __FILE__, __LINE__);
  }

  if (!almostEqual(exp(1.0), M_E)) {
    return Error::handle(name(), L"exp", Error::TEST, __FILE__, __LINE__);
  }

  if (!almostEqual(exp2(1.0), 2.0)) {
    return Error::handle(name(), L"exp2", Error::TEST, __FILE__, __LINE__);
  }

  if (!almostEqual(exp10(1.0), 10.0)) {
    return Error::handle(name(), L"exp10", Error::TEST, __FILE__, __LINE__);
  }

  if (!almostEqual(floor(27.1), 27.0)) {
    return Error::handle(name(), L"floor", Error::TEST, __FILE__, __LINE__);
  }

  if (!almostEqual(fraction(27.1), 0.1)) {
    return Error::handle(name(), L"fraction", Error::TEST, __FILE__, __LINE__);
  }

  uint32 foo[] = {5, 27, 99, 10192, 3932};
  if (hash(foo, 5, 128) != 53) {
    return Error::handle(name(), L"hash", Error::TEST, __FILE__, __LINE__);
  }
  
  if (!almostEqual(integer(27.1), 27.0)) {
    return Error::handle(name(), L"integer", Error::TEST, __FILE__, __LINE__);
  }

  if (!almostEqual(log(M_E), 1.0)) {
    return Error::handle(name(), L"log", Error::TEST, __FILE__, __LINE__);
  }

  if (!almostEqual(log2(2.0) / log2(M_E), log(2.0))) {
    return Error::handle(name(), L"log2", Error::TEST, __FILE__, __LINE__);
  }

  if (!almostEqual(log10(10.0) / log10(M_E), log(10.0))) {
    return Error::handle(name(), L"log10", Error::TEST, __FILE__, __LINE__);
  }

  if (!almostEqual(log1p(M_E - 1.0), 1.0)) {
    return Error::handle(name(), L"log1p", Error::TEST, __FILE__, __LINE__);
  }

  if (!almostEqual(max(1.0, 2.0), 2.0)) {
    return Error::handle(name(), L"max", Error::TEST, __FILE__, __LINE__);
  }

  if (!almostEqual(min(1.0, 2.0), 1.0)) {
    return Error::handle(name(), L"min", Error::TEST, __FILE__, __LINE__);
  }

  if (!almostEqual(pow(M_E, 2.0), exp(2.0))) {
    return Error::handle(name(), L"pow", Error::TEST, __FILE__, __LINE__);
  }

  if ((!almostEqual(round(27.49), 27.0)) ||
      (!almostEqual(round(26.51), 27.0)) ||
      (!almostEqual(round(-27.1), -27.0)) ||
      (!almostEqual(round(-26.51), -27.0))) {
    return Error::handle(name(), L"round", Error::TEST, __FILE__, __LINE__);
  }

  if (!almostEqual(sin(M_PI_2), 1.0)) {
    return Error::handle(name(), L"sin", Error::TEST, __FILE__, __LINE__);
  }

  if (!almostEqual(sinh(M_PI_2), 2.3013)) {
    return Error::handle(name(), L"sinh", Error::TEST, __FILE__, __LINE__);
  }

  // test sleep:
  //  there is no easy way to test this since the unix time function is not
  //  very accurate and we can't guarantee this program won't be preempted.
  //
  sleep(1);

  if (!almostEqual(sqrt(pow(M_E, 2.0)), M_E)) {
    return Error::handle(name(), L"sqrt", Error::TEST, __FILE__, __LINE__);
  }

  if (!almostEqual(tan(M_PI_4), 1.0)) {
    return Error::handle(name(), L"tan", Error::TEST, __FILE__, __LINE__);
  }

  if (!almostEqual(tanh(M_PI_2), 0.9172)) {
    return Error::handle(name(), L"tanh", Error::TEST, __FILE__, __LINE__);
  }

  // reset indentation
  //
  if (level_a > Integral::NONE) {
    Console::decreaseIndention();
  }
  
  //--------------------------------------------------------------------------
  //
  // 5. class-specific public methods:
  //     math functions for complex numbers
  //
  //--------------------------------------------------------------------------
 

// set indentation
  //
  if (level_a > Integral::NONE) {
    Console::put(L"testing class-specific public methods: complex number math functions...\n");
    Console::increaseIndention();
  }

  const complexdouble c0(4.0, 2.0);
  const complexdouble c1(3.5, 2.2);

  if (Integral::almostEqual(c0, c1)) {
    return Error::handle(name(), L"almostEqual",
			 Error::TEST, __FILE__, __LINE__);
  }

  if (!Integral::almostEqual(c0, complexdouble(4.00001, 1.99999))) {
    return Error::handle(name(), L"almostEqual",
			 Error::TEST, __FILE__, __LINE__);
  }

  if (!Integral::almostEqual(abs(c0), 4.4721)) {
    return Error::handle(name(), L"abs", Error::TEST, __FILE__, __LINE__);
  }

  if (!Integral::almostEqual(acos(c0), complexdouble(0.4739, -2.1836))) {
    return Error::handle(name(), L"acos", Error::TEST, __FILE__, __LINE__);
  }

  if (!Integral::almostEqual(acosh(c0), complexdouble(2.1836, 0.4739))) {
    return Error::handle(name(), L"acosh", Error::TEST, __FILE__, __LINE__);
  }

  if (!Integral::almostEqual(asin(c0), complexdouble(1.0969, 2.1836))) {
    return Error::handle(name(), L"asin", Error::TEST, __FILE__, __LINE__);
  }

  if (!Integral::almostEqual(asinh(c0), complexdouble(2.1986, 0.4539))) {
    return Error::handle(name(), L"asinh", Error::TEST, __FILE__, __LINE__);
  }

  if (!Integral::almostEqual(atan(c0), complexdouble(1.3715, 0.0964))) {
    return Error::handle(name(), L"atan", Error::TEST, __FILE__, __LINE__);
  }

  if (!Integral::almostEqual(atanh(c0), complexdouble(0.2006, 1.4670))) {
    return Error::handle(name(), L"atanh", Error::TEST, __FILE__, __LINE__);
  }

  if (!Integral::almostEqual(ceil(c0), complexdouble(4.0000, 2.0000))) {
    return Error::handle(name(), L"ceil", Error::TEST, __FILE__, __LINE__);
  }

  if (!Integral::almostEqual(cos(c0), complexdouble(-2.4591, 2.7448))) {
    return Error::handle(name(), L"cos", Error::TEST, __FILE__, __LINE__);
  }

  if (!Integral::almostEqual(cosh(c0), complexdouble(-11.3642, 24.8147))) {
    return Error::handle(name(), L"cosh", Error::TEST, __FILE__, __LINE__);
  }

  if (!Integral::almostEqual(exp(c0), complexdouble(-22.7208, 49.6460))) {
    return Error::handle(name(), L"exp", Error::TEST, __FILE__, __LINE__);
  }

  if (!Integral::almostEqual(exp2(c0), complexdouble(2.9353, 15.7284))) {
    return Error::handle(name(), L"exp2", Error::TEST, __FILE__, __LINE__);
  }

  if (!Integral::almostEqual(exp10(c0), complexdouble(-1070.1, -9942.6))) {
    return Error::handle(name(), L"exp10", Error::TEST, __FILE__, __LINE__);
  }

  if (!Integral::almostEqual(floor(c0), complexdouble(4.000, 2.0000))) {
    return Error::handle(name(), L"floor", Error::TEST, __FILE__, __LINE__);
  }

  if (!Integral::almostEqual(log(c0), complexdouble(1.4979, 0.4636))) {
    return Error::handle(name(), L"log", Error::TEST, __FILE__, __LINE__);
  }

  if (!Integral::almostEqual(log2(c0), complexdouble(2.1610, 0.6689))) {
    return Error::handle(name(), L"log2", Error::TEST, __FILE__, __LINE__);
  }

  if (!Integral::almostEqual(log10(c0), complexdouble(0.6505, 0.2014))) {
    return Error::handle(name(), L"log10", Error::TEST, __FILE__, __LINE__);
  }

  if (!Integral::almostEqual(log1p(c0), complexdouble(1.6836, 0.3805))) {
    return Error::handle(name(), L"log1p", Error::TEST, __FILE__, __LINE__);
  }

  if (!Integral::almostEqual(max(c0, c1), c0)) {
    return Error::handle(name(), L"max", Error::TEST, __FILE__, __LINE__);
  }

  if (!Integral::almostEqual(min(c0, c1), c1)) {
    return Error::handle(name(), L"min", Error::TEST, __FILE__, __LINE__);
  }

  if (!Integral::almostEqual(pow(c0, c1), complexdouble(13.9298, -66.7666))) {
    return Error::handle(name(), L"pow", Error::TEST, __FILE__, __LINE__);
  }

  if (!Integral::almostEqual(round(c0), c0)) {
    return Error::handle(name(), L"round", Error::TEST, __FILE__, __LINE__);
  }

  if (!Integral::almostEqual(sin(c0), complexdouble(-2.8472, -2.3707))) {
    return Error::handle(name(), L"sin", Error::TEST, __FILE__, __LINE__);
  }

  if (!Integral::almostEqual(sinh(c0), complexdouble(-11.3566, 24.8313))) {
    return Error::handle(name(), L"sinh", Error::TEST, __FILE__, __LINE__);
  }

  if (!Integral::almostEqual(sqrt(c0), complexdouble(2.0582, 0.4859))) {
    return Error::handle(name(), L"sqrt", Error::TEST, __FILE__, __LINE__);
  }

  if (!Integral::almostEqual(tan(c0), complexdouble(0.0364, 1.0047))) {
    return Error::handle(name(), L"tan", Error::TEST, __FILE__, __LINE__);
  }

  if (!Integral::almostEqual(tanh(c0), complexdouble(1.0004, -0.0005))) {
    return Error::handle(name(), L"tanh", Error::TEST, __FILE__, __LINE__);
  }

  // reset indentation
  //
  if (level_a > Integral::NONE) {
    Console::decreaseIndention();
  }

  
  //--------------------------------------------------------------------------
  //
  // 6. class-specific public methods:
  //     other math functions useful for speech research
  //
  //--------------------------------------------------------------------------

  // set indentation
  //
  if (level_a > Integral::NONE) {
    Console::put(L"testing class-specific public methods: other math functions...\n");
    Console::increaseIndention();
  }
  
  // test logAddLog
  //
  if (!almostEqual(logAddLog(log(2.0), log(3.0)), (float64)1.609437912)) {
    return Error::handle(name(), L"logAddLog",
			 Error::TEST, __FILE__, __LINE__);
  }

  // reset indentation
  //
  if (level_a > Integral::NONE) {
    Console::decreaseIndention();
  }

  //--------------------------------------------------------------------------
  //
  // 7. class-specific public methods:
  //     time functions that are useful for time measurements. time
  //     functions can't be explicitly tested because the return value
  //     varies with time
  //--------------------------------------------------------------------------

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
    SysString output(L"diagnostics passed for class ");
    output.concat(name());
    output.concat(L"\n");
    Console::put(output);
  }

  // exit gracefully
  //
  return true;
}
