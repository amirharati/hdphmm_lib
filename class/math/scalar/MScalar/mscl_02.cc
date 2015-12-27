// file: $isip/class/math/scalar/MScalar/mscl_02.cc
// version: $Id: mscl_02.cc 10636 2007-01-26 22:18:09Z tm334 $
//

// isip include files
//
#include "MScalarMethods.h"
#include "MScalar.h"
#include <Console.h>
#include <typeinfo>
#include "Float.h"

// method: diagnose
//
// arguments:
//  Integral::DEBUG level: (input) debug level for diagnostics
//
// return: logical error status
//
// this method is split into three methods:
//  diagnose0: tests required methods and operator overloads
//  diagnose1: tests bitwise methods
//  diagnose2: tests math and private methods.
//  
template<class TScalar, class TIntegral>
bool8 MScalarMethods::diagnose(Integral::DEBUG level_a) {

  //----------------------------------------------------------------------
  //
  // preliminaries
  //
  //----------------------------------------------------------------------

  // output the class name
  //
  if (level_a > Integral::NONE) {
    SysString output(L"diagnosing class ");
    output.concat(name());
    output.concat(L": ");
    Console::put(output);
  }
  
  // call the sub diagnose method
  //
  diagnose0<TScalar, TIntegral>(level_a);
  diagnose1<TScalar, TIntegral>(level_a);
  diagnose2<TScalar, TIntegral>(level_a);
  
  //---------------------------------------------------------------------
  //
  //  print completion message
  //
  //---------------------------------------------------------------------

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

// method: diagnose0
//
// arguments:
//  Integral::DEBUG level: (input) debug level for diagnostics
//
// return: logical error status
//
// this method tests basic required methods, operator overloads,
// and logical functions.
//
template<class TScalar, class TIntegral>
bool8 MScalarMethods::diagnose0(Integral::DEBUG level_a) {

  // declare some local variables
  //
  TScalar val0;
  TScalar val1;
  TScalar val2;
  
  //---------------------------------------------------------------------------
  //
  // required public methods
  //
  //---------------------------------------------------------------------------
  
  // set indentation
  //
  if (level_a > Integral::NONE) {
    Console::put(L"testing class-specific public methods: required public methods...\n");
    Console::increaseIndention();
  }
   						   
  // test clear
  //
  val0.clear();
  if (val0 != TScalar::DEF_VALUE) {
    return Error::handle(name(), L"clear", Error::TEST, __FILE__, __LINE__);
  }

  // reset indentation
  //
  if (level_a > Integral::NONE) {
    Console::decreaseIndention();
  }
    
  //---------------------------------------------------------------------------
  //
  // class-specific public methods:
  //  extensions to required methods
  //
  //---------------------------------------------------------------------------

  // set indentation
  //
  if (level_a > Integral::NONE) {
    Console::put(L"testing class-specific public methods: extension to required methods..");
    Console::increaseIndention();
  }
  
  // test assign
  //
  val0.assign((TIntegral)3);
  if (val0 != (TIntegral)3) {
    return Error::handle(name(), L"assign", Error::TEST, __FILE__, __LINE__);
  }

  // test assign from String
  // 
  String in0(L"3.5");
  val0.assign(in0);

  String in1(L"2.5");
  val1.assign(in1);

  val2 = val0 - val1;
  if (val2 != (TIntegral)1) {  
    return Error::handle(name(), L"<String::assign>",
			 Error::TEST, __FILE__, __LINE__);
  }
  // test get from String
  // 
  val0.assign(3.5);
  val0.get(in0);
  val1.assign(in0);
  if (val1 != val0) {  
    return Error::handle(name(), L"<String::get>",
			 Error::TEST, __FILE__, __LINE__);
  }
    
  // test almostEqual
  //
  val0.assign(1.0001);
  val1.assign(1.0002);
  
  if (!val0.almostEqual(val1)) {
    return Error::handle(name(), L"almostEqual", Error::TEST,
			 __FILE__, __LINE__);
  }
  
  val0.assign(1.0);
  val1.assign(2.0);
  
  if (val0.almostEqual(val1)) {
    return Error::handle(name(), L"almostEqual", Error::TEST,
			 __FILE__, __LINE__);
  }

  // reset indentation
  //
  if (level_a > Integral::NONE) {
    Console::decreaseIndention();
  }
  
  //---------------------------------------------------------------------------
  //
  // class-specific public methods:
  //  operator overloads
  //
  //---------------------------------------------------------------------------

  // set indentation
  //
  if (level_a > Integral::NONE) {
    Console::put(L"testing class-specific public methods: operator overloads...\n");
    Console::increaseIndention();
  }

  // test operator TIntegral()
  //
  val0.assign((TIntegral)3);
  if (val0 != (TIntegral)3) {
    return Error::handle(name(), L"TIntegral",
			 Error::TEST, __FILE__, __LINE__);
  }
  
  // test operator +
  //
  val0.assign((TIntegral)3);
  val1.assign((TIntegral)2);
  val2 = val0 + val1;
  if (val2 != (TIntegral)5) {
    return Error::handle(name(), L"+", Error::TEST, __FILE__, __LINE__);
  }

  // test operator -
  //
  val0.assign((TIntegral)3);
  val1.assign((TIntegral)2);
  val2 = val0 - val1;
  if (val2 != (TIntegral)1) {
    return Error::handle(name(), L"operator -",
			 Error::TEST, __FILE__, __LINE__);
  }
 
  // test operator *
  //
  val0.assign((TIntegral)3);
  val1.assign((TIntegral)2);
  val2 = val0 * val1 * val0;
  if (val2 != (TIntegral)18) {
    return Error::handle(name(), L"operator *",
			 Error::TEST, __FILE__, __LINE__);
  }
  
  // test operator /
  //
  val0.assign((TIntegral)3);
  val1.assign((TIntegral)2);
  val2 = val0 / val1;
  if (val2 != (TIntegral)1.5) {
    return Error::handle(name(), L"operator /",
			 Error::TEST, __FILE__, __LINE__);
  }

//   // test operator %
//   //
//   if ((typeid(TIntegral) != typeid(float64)) &&
//       (typeid(TIntegral) != typeid(float32))) {
//     val0.assign((TIntegral)8);
//     val1.assign((TIntegral)3);
//     val2 = val0 % val1;
//     if (val2 != (TIntegral)2.0) {
//       return Error::handle(name(), L"operator%",
// 			   Error::TEST, __FILE__, __LINE__);
//     }
//   }
  
  // test operator ++
  //
  val0.assign((TIntegral)3);
  val1.assign(val0++);
  if (!val0.almostEqual((TIntegral)4) || !val1.almostEqual((TIntegral)3)) {
    return Error::handle(name(), L"operator++",
			 Error::TEST, __FILE__, __LINE__);
  }

  // test operator --
  //
  val0.assign((TIntegral)3);
  val1.assign(val0--);
  if (!val0.almostEqual((TIntegral)2) || !val1.almostEqual((TIntegral)3)) {
    return Error::handle(name(), L"operator--",
			 Error::TEST, __FILE__, __LINE__);
  }

  // test operator ++
  //
  val0.assign((TIntegral)3);
  val1.assign(++val0);
  if (!val0.almostEqual((TIntegral)4) || !val1.almostEqual((TIntegral)4)) {
    return Error::handle(name(), L"operator++",
			 Error::TEST, __FILE__, __LINE__);
  }
  
  // test operator --
  //
  val0.assign((TIntegral)3);
  val1.assign(--val0);
  if (!val0.almostEqual((TIntegral)2) || !val1.almostEqual((TIntegral)2)) {
    return Error::handle(name(), L"operator--",
			 Error::TEST, __FILE__, __LINE__);
  }
    
  // test operator +=
  //
  val0.assign((TIntegral)43);
  val0 += (TIntegral)4;
  if (!val0.almostEqual((TIntegral)47)) {
    return Error::handle(name(), L"operator+=",
			 Error::TEST, __FILE__, __LINE__);
  }
  
  // test operator -=
  //
  val0 -= (TIntegral)7;
  if (!val0.almostEqual((TIntegral)40)) {
    return Error::handle(name(), L"operator-=",
			 Error::TEST, __FILE__, __LINE__);
  }
  
  // test operator *=
  //
  val0 *= (TIntegral)2;
  if (!val0.almostEqual((TIntegral)80)) {
    return Error::handle(name(), L"operator*=",
			 Error::TEST, __FILE__, __LINE__);
  }
  
  // test operator /=
  //
  val0 /= (TIntegral)10;
  if (!val0.almostEqual((TIntegral)8)) {
    return Error::handle(name(), L"operator/=",
			 Error::TEST, __FILE__, __LINE__);
  }
/*
  // test operator %=
  //
  if ((typeid(TIntegral) != typeid(float64)) &&
      (typeid(TIntegral) != typeid(float32))) {
      val0 %= (TIntegral)10;
      if (!val0.almostEqual((TIntegral)8)) {
	  return Error::handle(name(), L"operator%=",
			       Error::TEST, __FILE__, __LINE__);
      }
  }
*/  
  // test operator ==
  //
  val0.assign((TIntegral)3);
  val2 = val0;
  if (!(val0 == val2)) {
    return Error::handle(name(), L"operator==",
			 Error::TEST, __FILE__, __LINE__);
  }

  // test operator !=
  //
  val0.assign((TIntegral)3);
  if (val0 != (TIntegral)3) {
    return Error::handle(name(), L"operator !=",
			 Error::TEST, __FILE__, __LINE__);
  }
  
  // test operator <
  //
  val0.assign((TIntegral)3);
  if (val0 < (TIntegral)3) {
    return Error::handle(name(), L"operator <",
			 Error::TEST, __FILE__, __LINE__);
  }
  
  // test operator <=
  //
  val0.assign((TIntegral)3);
  if (val0 <= (TIntegral)2) {
    return Error::handle(name(), L"operator <=",
			 Error::TEST, __FILE__, __LINE__);
  }
  
  // test operator >
  //
  val0.assign((TIntegral)3);
  if (val0 > (TIntegral)3) {
    return Error::handle(name(), L"operator >",
			 Error::TEST, __FILE__, __LINE__);
  }
  
  // test operator >=
  //						   
  val0.assign((TIntegral)3);
  if (val0 >= (TIntegral)4) {
    return Error::handle(name(), L"operator >=",
			 Error::TEST, __FILE__, __LINE__);
  }

  // reset indentation
  //
  if (level_a > Integral::NONE) {
    Console::decreaseIndention();
  }

  //---------------------------------------------------------------------------
  //
  // class-specific public methods:
  //  equality and comparison methods
  //
  //---------------------------------------------------------------------------

  // set indentation
  //
  if (level_a > Integral::NONE) {
    Console::put
      (L"testing class-specific public methods: equality methods...\n");
    Console::increaseIndention();
  }
  
  // test eq
  //
  val0.assign((TIntegral)4);
  val1.assign((TIntegral)3);
  val2.assign((TIntegral)4);
  if (val2.eq(val0, val1) || !(val0.eq(val2))) {
    return Error::handle(name(), L"eq", Error::TEST, __FILE__, __LINE__);
  }
   
  // test ne
  //
  val0.assign((TIntegral)3);
  val2.assign((TIntegral)3);
  if (val2.ne(val0)) {
    return Error::handle(name(), L"ne", Error::TEST, __FILE__, __LINE__);
  }
  
  // test lt
  //
  val0.assign((TIntegral)4);
  val2.assign((TIntegral)4);
  if (val2.lt(val0)) {
    return Error::handle(name(), L"lt", Error::TEST, __FILE__, __LINE__);
  }

  // test le
  //
  val0.assign((TIntegral)4);
  val2.assign((TIntegral)5);
  if (val2.le(val0)) {
    return Error::handle(name(), L"le", Error::TEST, __FILE__, __LINE__);
  }

  // test gt
  //
  val0.assign((TIntegral)5);
  val2.assign((TIntegral)4);
  if (val2.gt(val0)) {
    return Error::handle(name(), L"gt", Error::TEST, __FILE__, __LINE__);
  } 

  // test ge
  //
  val0.assign((TIntegral)3);
  val1.assign((TIntegral)4);
  val2.assign((TIntegral)4);
  if (val0.ge(val2)) {
    return Error::handle(name(), L"ge", Error::TEST, __FILE__, __LINE__);
  }
  
  // reset indentation
  //
  if (level_a > Integral::NONE) {
    Console::decreaseIndention();
  }
 
  // exit gracefully
  //
  return true;
}

// method: diagnose1
//
// arguments:
//  Integral::DEBUG level: (input) debug level for diagnostics
//
// return: logical error status
//
// this method tests bitwise operations.
//
template<class TScalar, class TIntegral>
bool8 MScalarMethods::diagnose1(Integral::DEBUG level_a) {
  
  //--------------------------------------------------------------------
  //
  //  testing bitwise and integer-specific operations
  //
  //--------------------------------------------------------------------
  
  // declare local variables
  //
  TScalar val0;
  TScalar val1;
  TScalar val2;

  // set indentation
  //
  if (level_a > Integral::NONE) {
    Console::put(L"testing class-specific public methods: bitwise operations...\n");
    Console::increaseIndention();
  }
  
  // reset indentation
  //
  if (level_a > Integral::NONE) {
    Console::decreaseIndention();
  }
    
  // exit gracefully
  //
  return true;
}
  
// method: diagnose2
//
//  arguments:
//  Integral::DEBUG level: (input) debug level for diagnostics
//
// return: logical error status
//
// this method tests math functions and private methods.
//
template<class TScalar, class TIntegral>
bool8 MScalarMethods::diagnose2(Integral::DEBUG level_a) {

  //---------------------------------------------------------------------------
  //
  // class-specific public methods:
  //  basic mathematical methods
  //
  //---------------------------------------------------------------------------

  // declare local variables
  //
  TScalar val0;
  TScalar val1;
  TScalar val2;

  // set indentation
  //
  if (level_a > Integral::NONE) {
    Console::put(L"testing class-specific public methods: basic mathematical methods...\n");
    Console::increaseIndention();
  }
  
  // test add
  //
  val0.assign((TIntegral)3);
  val1.assign((TIntegral)2);
  val2.add(val0, val1);
  if (val2 != (TIntegral)5) {
    return Error::handle(name(), L"add", Error::TEST, __FILE__, __LINE__);
  }
  
  // test sub
  // 
  val0.assign((TIntegral)3);
  val1.assign((TIntegral)2);
  val2.sub(val0, val1);
  if (val2 != (TIntegral)1) {
    return Error::handle(name(), L"sub", Error::TEST, __FILE__, __LINE__);
  }
  
  // test mult
  //
  val0.assign((TIntegral)3);
  val1.assign((TIntegral)2);
  val2.mult(val0, val1);
  if (val2 != (TIntegral)6) {
    return Error::handle(name(), L"mult", Error::TEST, __FILE__, __LINE__);
  }

  // test div
  //
  val0.assign((TIntegral)5);
  val1.assign((TIntegral)2);
  val2.div(val0, val1);
  if (val2 != (TIntegral)2.5) {
    return Error::handle(name(), L"div", Error::TEST, __FILE__, __LINE__);
  }

//   // test mod
//   //
//   if ((typeid(TIntegral) != typeid(float64)) &&
//       (typeid(TIntegral) != typeid(float32))) {
//     val0.assign((TIntegral)8);
//     val1.assign((TIntegral)3);
//     val2.mod(val0, val1);
//     if (val2 != (TIntegral)2) {
//       return Error::handle(name(), L"mod", Error::TEST, __FILE__, __LINE__);
//     }
//   }
  
  // reset indentation
  //
  if (level_a > Integral::NONE) {
    Console::decreaseIndention();
  }
  
  //---------------------------------------------------------------------------
  //
  // class-specific public methods:
  //  other mathematical methods (listed alphabetically)
  //
  //--------------------------------------------------------------------------

  // set indentation
  //
  if (level_a > Integral::NONE) {
    Console::put(L"testing class-specific public methods: other mathematical methods...\n");
    Console::increaseIndention();
  }

  // test abs
  //
  if ((typeid(TIntegral) == typeid(float32)) ||
      (typeid(TIntegral) == typeid(float64)) ||
      (typeid(TIntegral) == typeid(int64)) ||
      (typeid(TIntegral) == typeid(int16)) ||
      (typeid(TIntegral) == typeid(int32)) ) {
    
    val0.abs(200);
    if (!val0.almostEqual(200)) {
      return Error::handle(name(), L"abs", Error::TEST, __FILE__, __LINE__);
    }
    
    val0.abs(-45);
    if (!val0.almostEqual(45)) {
      return Error::handle(name(), L"abs", Error::TEST, __FILE__, __LINE__);
    }
  }

  // test functions only work for floating point
  //  
  if ((typeid(TIntegral) == typeid(float32)) ||
      (typeid(TIntegral) == typeid(float64))) {
    
    // test acos
    //    
    val0.assign(Integral::PI / (float64)3);
    val1.cos(val0);
    if (!val0.almostEqual(val1.acos())) {
      return Error::handle(name(), L"acos", Error::TEST, __FILE__, __LINE__);
    }

    // test acosh
    //
    val0.assign((TIntegral)0.5); 
    val1.cosh(val0);
    if (!val0.almostEqual(val1.acosh())) {
      return Error::handle(name(), L"acosh", Error::TEST, __FILE__, __LINE__);
    }
    
    // test asin
    //
    val0.assign(Integral::PI / (float64)6);
    val1.sin(val0);
    if (!val0.almostEqual(val1.asin())) {
      return Error::handle(name(), L"asin", Error::TEST, __FILE__, __LINE__);
    }
    
    // test asinh
    //
    val0.assign((TIntegral)0.5); 
    val1.sinh(val0);
    if (!val0.almostEqual(val1.asinh())) {
      return Error::handle(name(), L"asinh", Error::TEST, __FILE__, __LINE__);
    }
    
    // test atan
    //
    val0.assign(Integral::QUARTER_PI);
    val1.tan(val0);
    if (!val0.almostEqual(val1.atan())) {
      return Error::handle(name(), L"atan", Error::TEST, __FILE__, __LINE__);
    }
    
    // test atanh
    //
    val0.assign((TIntegral)0.5); 
    val1.tanh(val0);
    if (!val0.almostEqual(val1.atanh())) {
      return Error::handle(name(), L"atanh", Error::TEST, __FILE__, __LINE__);
    }
    
    // test ceil
    //
    val0.ceil((TIntegral)2.4);
    val1.ceil((TIntegral)20.3);
    if ((!val0.almostEqual((TIntegral)3.0)) ||
	(!val1.almostEqual((TIntegral)21.0))) {
      return Error::handle(name(), L"ceil", Error::TEST, __FILE__, __LINE__);
    }
    
    // test centerClip
    //
    val0.assign((int32)24);
    val1.assign((int32)200);
    val2.assign((int32)-34);  
    TScalar res0;
    TScalar res1;
    TScalar res2;
    res0.centerClip(-50, 50, val0);
    res1.centerClip(-50, 50, val1);
    res2.centerClip(-50, 50, val2);
    
    if ((!res0.almostEqual(50))|| (!res1.almostEqual(200)) ||
	(!res2.almostEqual(-50))) {
      return Error::handle(name(), L"centerClip",
			   Error::TEST, __FILE__, __LINE__);
    }
  
    // test cos
    //
    val0.assign(Integral::PI / (float64)3);
    val1.cos(val0);
    if (!val1.almostEqual((TIntegral)0.5)) {
      return Error::handle(name(), L"cos", Error::TEST, __FILE__, __LINE__);
    }
    
    // test cosh
    //
    val0.assign((TIntegral)0.5); 
    val1.cosh(val0);
    val1.acosh();
    if (!val1.almostEqual(val0)) {
      return Error::handle(name(), L"cosh", Error::TEST, __FILE__, __LINE__);
    }
  }
  
  // test exp
  //
  val0.assign((TIntegral)55);                  
  val1.log(val0);
  val1.exp();
  if (!val0.almostEqual(val1))  {
    return Error::handle(name(), L"exp", Error::TEST, __FILE__, __LINE__);
  }
    
  // test exp2
  //
  val0.assign((TIntegral)64);
  val1.log2(val0);
  val1.exp2();
  if (!val0.almostEqual(val1)) {
    return Error::handle(name(), L"exp2", Error::TEST, __FILE__, __LINE__);
  }
    
  // test exp10
  //
  val0.assign((TIntegral)100);
  val1.log10(val0);
  val1.exp10();
  if (!val0.almostEqual(val1)) {
    return Error::handle(name(), L"exp10", Error::TEST, __FILE__, __LINE__);
  }

  // test factorial
  //
  val0.factorial(5);
  if (!val0.almostEqual(120)) {
    return Error::handle(name(), L"factorial", Error::TEST,
			 __FILE__, __LINE__);
  }
 
  // test floor
  //
  if ((typeid(TIntegral) == typeid(float32)) ||
      (typeid(TIntegral) == typeid(float64))) {
    val0.floor((TIntegral)2.4);
    val1.floor((TIntegral)-20.3);
    if ((!val0.almostEqual((TIntegral)2.0)) ||
	(!val1.almostEqual((TIntegral)-21.0))) {
      return Error::handle(name(), L"floor", Error::TEST, __FILE__, __LINE__);
    }
  }
  
  // test fraction
  //
  if ((typeid(TIntegral) == typeid(float32)) &&
      (typeid(TIntegral) == typeid(float64))) {
    val0.fraction((TIntegral)2.4);
    val1.fraction((TIntegral)34.1);
    if ((!val0.almostEqual((TIntegral)0.4)) ||
	(!val0.almostEqual((TIntegral)0.1))) {
      return Error::handle(name(), L"fraction",
			   Error::TEST, __FILE__, __LINE__);
    }
  }
    
  // test grand:
  //  see the section of code below that tests random numbers
  //

  // test hash
  //
  val0.assign((TIntegral)87.30);
  uint32 h1 = val0.hash((int32)104);
  
  if (!(typeid(TIntegral) == typeid(float32) && (h1 == (uint32)16)) &&
      !(typeid(TIntegral) == typeid(float64) && (h1 == (uint32)4)) &&
      !(h1 == (uint32)87)) {
    return Error::handle(name(), L"hash",Error::TEST, __FILE__, __LINE__);
  }
  
  // test inverse
  //
  val0.assign((TIntegral)216);
  val0.inverse();
  if (!val0.almostEqual((TIntegral)0.0046296)) {
    return Error::handle(name(), L"inverse", Error::TEST, __FILE__,__LINE__);
  }

  // declare local variables
  //
  TScalar res0;
  TScalar res1;
  TScalar res2;

  // test limit
  //
  val0.assign((int32)24);
  val1.assign((int32)200);

  res0.limit(0, 100, val0);
  res1.limit(0, 100, val1);
  if ((!res0.almostEqual(24)) ||
      (!res1.almostEqual(100))) {
    return Error::handle(name(), L"limit", Error::TEST, __FILE__, __LINE__);
  }
      
  // test limitMag
  // test limit using negative values
  //
  if ((typeid(TIntegral) == typeid(float32)) ||
      (typeid(TIntegral) == typeid(float64)) ||
      (typeid(TIntegral) == typeid(int32)) ||
      (typeid(TIntegral) == typeid(int16)) ||
      (typeid(TIntegral) == typeid(int64))) {
    
    val2.assign((int32)-34);    
    res1.limit(0, 100, val2);    
    if (!res1.almostEqual(0)) {
      return Error::handle(name(), L"limit", Error::TEST, __FILE__, __LINE__);
    }
    
    res0.limitMag(30, -5, val0);
    res1.limitMag(30, -5, val1);
    res2.limitMag(30, -5, val2);
    
    if ((!res0.almostEqual(24)) ||
	(!res1.almostEqual(-5)) ||
	(!res2.almostEqual(-5))) {
      return Error::handle(name(), L"limitMag", Error::TEST,
			   __FILE__, __LINE__);
    }
  }
  
  // test log
  //
  val0.assign((TIntegral)55);                  
  val1.log(val0);
  if (!val1.almostEqual((TIntegral)4.00733318523)) {
    return Error::handle(name(), L"log", Error::TEST, __FILE__, __LINE__);
  }
  
  // test log2
  //
  val0.assign((TIntegral)64);
  val1.log2(val0);
  if (!val1.almostEqual((TIntegral)6)) {
    return Error::handle(name(), L"log2", Error::TEST, __FILE__, __LINE__);
  }

  // test log10
  //
  val0.assign((TIntegral)100);
  val1.log10(val0);
  if (!val1.almostEqual((TIntegral)2)) {
    return Error::handle(name(), L"log10", Error::TEST, __FILE__, __LINE__);
  }
    
  // test log1p
  //
  val0.assign((TIntegral)54);                
  val1.log1p(val0);
  if (!val1.almostEqual((TIntegral)4.00733318523)) {
    return Error::handle(name(), L"log1p", Error::TEST, __FILE__, __LINE__);
  }

  // test max
  //
  val0.max(43, 52);
  val1.max(43, 33);
  if ((!val0.almostEqual(52)) || (!val1.almostEqual(43))) {
    return Error::handle(name(), L"max", Error::TEST, __FILE__, __LINE__);
  }
  
  // test min
  //   
  val0.min(43, 52);
  val1.min(43, 33);
  if ((!val0.almostEqual(43)) || (!val1.almostEqual(33))) {
    return Error::handle(name(), L"min", Error::TEST, __FILE__, __LINE__);
  }
  
  // test neg
  //
  if ((typeid(TIntegral) == typeid(float32)) ||
      (typeid(TIntegral) == typeid(float64)) ||
      (typeid(TIntegral) == typeid(int64)) ||
      (typeid(TIntegral) == typeid(int32)) ||
      (typeid(TIntegral) == typeid(int16))) {
    val0.neg(-44);
    if (!val0.almostEqual(44)) {
      return Error::handle(name(), L"neg", Error::TEST, __FILE__, __LINE__);
    }

    val0.neg(127);
    if (!val0.almostEqual(-127)) {
      return Error::handle(name(), L"neg", Error::TEST, __FILE__, __LINE__);
    }
  }
     
  // test pow
  //
  val0.assign((TIntegral)5);
  val0.pow((TIntegral)3.0);
  if (!val0.almostEqual(125)) {
    return Error::handle(name(), L"pow", Error::TEST, __FILE__, __LINE__);
  }
 
  // test rand:
  //  see the section of code below that tests random numbers
  //

  // test functions only work for floating point
  //
  if ((typeid(TIntegral) == typeid(float32)) ||
      (typeid(TIntegral) == typeid(float64))) {

    // test rceil
    //
    val0.rceil((TIntegral)2.4);
    val1.rceil((TIntegral)-20.3);
    if ((!val0.almostEqual((TIntegral)0.6)) ||
	(!val1.almostEqual((TIntegral)0.3))) {
      return Error::handle(name(), L"rceil", Error::TEST, __FILE__, __LINE__);
    }

    // test rfloor
    //
    val0.rfloor((TIntegral)2.4);
    val1.rfloor((TIntegral)-20.3);
    if ((!val0.almostEqual((TIntegral)-0.4)) ||
	(!val1.almostEqual((TIntegral)-0.7))) {
      return Error::handle(name(), L"rfloor", Error::TEST, __FILE__, __LINE__);
    }

    // test round
    //
    val0.round((TIntegral)2.4);
    val1.round((TIntegral)2.6);
    if ((!val0.almostEqual((TIntegral)2.0)) ||
	(!val1.almostEqual((TIntegral)3.0))) {
      return Error::handle(name(), L"round", Error::TEST, __FILE__, __LINE__);
    }
  }

  // test functions work for all point
  //
  {
    // test ceil
    //
    val0.ceil((float32)2.4);
    val1.ceil((float32)20.3);
    if ((!val0.almostEqual((TIntegral)3.0)) ||
	(!val1.almostEqual((TIntegral)21.0))) {
      return Error::handle(name(), L"ceil", Error::TEST, __FILE__, __LINE__);
    }

    // test floor
    //
    val0.floor((float32)2.4);
    val1.floor((float32)20.8);
    if ((!val0.almostEqual((TIntegral)2.0)) ||
	(!val1.almostEqual((TIntegral)20.0))) {
      return Error::handle(name(), L"floor", Error::TEST, __FILE__, __LINE__);
    }

    // test round
    //
    val0.round((float32)2.4);
    val1.round((float32)2.6);
    if ((!val0.almostEqual((TIntegral)2.0)) ||
	(!val1.almostEqual((TIntegral)3.0))) {
      return Error::handle(name(), L"round", Error::TEST, __FILE__, __LINE__);
    }
  }
   
  // test sign
  //
  if ((typeid(TIntegral) == typeid(float32)) ||
      (typeid(TIntegral) == typeid(float64)) ||
      (typeid(TIntegral) == typeid(int64)) ||
      (typeid(TIntegral) == typeid(int32)) ||
      (typeid(TIntegral) == typeid(int16))) {
    val0.sign(-44);
    if (!val0.almostEqual(-1)) {
      return Error::handle(name(), L"sign", Error::TEST, __FILE__, __LINE__);
    }
   
    val0.sign(200);
    if (!val0.almostEqual(1)) {
      return Error::handle(name(), L"sign", Error::TEST, __FILE__, __LINE__);
    }
  }

  // test sin
  //
  if ((typeid(TIntegral) == typeid(float32)) ||
      (typeid(TIntegral) == typeid(float64))) {  
    val0.assign(Integral::PI / (float64)6);    
    val1.sin(val0);  
    if (!val1.almostEqual((TIntegral)0.5)) {
      return Error::handle(name(), L"sin", Error::TEST, __FILE__, __LINE__);
    }
  }
  
  // test sinh
  //
  if ((typeid(TIntegral) == typeid(float32)) ||
      (typeid(TIntegral) == typeid(float64))) {  
    val0.assign((TIntegral)0); 
    val1.sinh(val0);
    if (!val1.almostEqual((TIntegral)0)) {
      return Error::handle(name(), L"sinh", Error::TEST, __FILE__, __LINE__);
    }
  }
  
  // test sqrt
  //
  val0.sqrt(81);
  if (!val0.almostEqual(9)) {
    return Error::handle(name(), L"sqrt", Error::TEST, __FILE__, __LINE__);
  }
  
  // test square
  //
  val0.square(9);
  val1.assign(9);
  TIntegral sq_temp = val1.square();
  if (!val0.almostEqual(81) ||
      (sq_temp != (TIntegral)81)) {
    return Error::handle(name(), L"square", Error::TEST, __FILE__, __LINE__);
  }

  // test tan
  //
  if ((typeid(TIntegral) == typeid(float32)) ||
      (typeid(TIntegral) == typeid(float64))) {
    val0.assign(Integral::QUARTER_PI);
    val1.tan(val0);
    if (!val1.almostEqual((TIntegral)1.0)) {
      return Error::handle(name(), L"tan", Error::TEST, __FILE__, __LINE__);
    }
  }
  
  // test tanh
  //
  if ((typeid(TIntegral) == typeid(float32)) ||
      (typeid(TIntegral) == typeid(float64))) {    
    val0.assign((TIntegral)1); 
    val1.tanh(val0);
    if (!val1.almostEqual((TIntegral)0.7615)) {
      return Error::handle(name(), L"tanh", Error::TEST, __FILE__, __LINE__);
    }
  }
  
  // reset indentation
  //
  if (level_a > Integral::NONE) {
    Console::decreaseIndention();
  }

  //---------------------------------------------------------------------------
  //
  // class-specific public methods:
  //  random number generation methods
  //
  //--------------------------------------------------------------------------

  // set indentation
  //
  if (level_a > Integral::NONE) {
    Console::put(L"testing class-specific public methods: random number generation methods...\n");
    Console::increaseIndention();
  }

  // declare local variables
  //
  int32 N = 1000;
    
  float64 min, max, mean;
  float64 expected_min, expected_max, expected_mean;
  float64 comp_mean;
    
  TScalar rand;
    
  //--------------------------------------------------------------------
  //
  // test rand
  //
  //--------------------------------------------------------------------
  
  // determine the expected values based on the specific type
  //
  if (typeid(TIntegral) == typeid(byte8)) {
    expected_min = 0;
    expected_max = TScalar::RAND_BYTE_MAX - 1.0;
    expected_mean = TScalar::RAND_BYTE_MAX / 2.0;
    comp_mean = 126.76;
  }
  
  else if (typeid(TIntegral) == typeid(uint16)) {
    expected_min = 0;
    expected_max = TScalar::RAND_USHORT_MAX - 1.0;
    expected_mean = TScalar::RAND_USHORT_MAX / 2.0;
    comp_mean = 32578.44;
  }
    
  else if (typeid(TIntegral) == typeid(uint32)) {
    expected_min = 0;
    expected_mean = TScalar::RAND_ULONG_MAX / 2.0;
    expected_max = TScalar::RAND_ULONG_MAX - 1.0;
    comp_mean = 2135094016.00;
  }
    
  else if (typeid(TIntegral) == typeid(uint64)) {
    expected_min = 0;
    expected_max = TScalar::RAND_ULLONG_MAX - 1.0;
    expected_mean = TScalar::RAND_ULLONG_MAX / 2.0;
    comp_mean = 9170158972605300736.00;
  }
  
  else if (typeid(TIntegral) == typeid(int16)) {
    expected_min = -TScalar::RAND_SHORT_MAX;
    expected_max = TScalar::RAND_SHORT_MAX - 1.0;
    expected_mean = 0;
    comp_mean = -189.05;
  }
    
  else if (typeid(TIntegral) == typeid(int32)) {
    expected_min = -TScalar::RAND_LONG_MAX;
    expected_max = TScalar::RAND_LONG_MAX - 1.0;
    expected_mean = 0;
    comp_mean = -12389639.00;
  }
    
  else if (typeid(TIntegral) == typeid(int64)) {
    expected_min = -TScalar::RAND_LLONG_MAX;
    expected_max = TScalar::RAND_LLONG_MAX - 1.0;
    expected_mean = 0;
    comp_mean = -53213094314246144.00;
  }
    
  else if ((typeid(TIntegral) == typeid(float32)) ||
	   (typeid(TIntegral) == typeid(float64))) {
    expected_min = 0;
    expected_max = 1.0;
    expected_mean = 0.5;
    comp_mean = 0.500823;
  }
  else {
    return Error::handle(name(), L"rand", Error::TEST, __FILE__, __LINE__);
  }
   // set the seed
  //
  Random::GLOBAL_UNIFORM.seed(27);
    
  // generate N random numbers: use rand()
  //
  mean = (TIntegral)0;
  min = expected_max;
  max = expected_min;
    
  for (int32 i = 0; i < N; i++) {
      
    // take a random sample
    //
    TIntegral tmp = rand.rand();

    // update the mean
    //
    mean += tmp;
      
    // update the min/max
    //
    min = Integral::min(tmp, min);
    max = Integral::max(tmp, max);
  }
  mean /= N;

  // check if the computed values are in the proper range
  //
  
  if (!Integral::almostEqual(mean, comp_mean, 1.0)) {
    SysString out(L"mean = ");
    out.concat(mean);
    out.concat(L"; comp_mean = ");
    out.concat(comp_mean);
    Console::put(out);
    return Error::handle(name(), L"rand", Error::TEST, __FILE__, __LINE__);
  }
  if (min < expected_min) {
    SysString out(L"min = ");
    out.concat(min);
    out.concat(L"expected_min= ");
    out.concat(expected_min);
    Console::put(out);
    return Error::handle(name(), L"rand", Error::TEST, __FILE__, __LINE__);
  }
    
  if (max > expected_max) {
    SysString out(L"max = ");
    out.concat(max);
    out.concat(L"expected_max = ");
    out.concat(expected_max);
    Console::put(out);
    return Error::handle(name(), L"rand", Error::TEST, __FILE__, __LINE__);
  }
  //--------------------------------------------------------------------
  //
  // test rand(expected_min, expected_max)
  //
  //--------------------------------------------------------------------
    
  // determine the expected values based on the specific type
  //
  expected_min = 10.0;
  expected_max = 90.0;
  expected_mean = (expected_min + expected_max) / (float64)2;
    
  if ((typeid(TIntegral) == typeid(byte8)) ||
      (typeid(TIntegral) == typeid(uint16)) ||
      (typeid(TIntegral) == typeid(uint32)) ||
      (typeid(TIntegral) == typeid(uint64)) ||
      (typeid(TIntegral) == typeid(int16)) ||
      (typeid(TIntegral) == typeid(int32)) ||
      (typeid(TIntegral) == typeid(int64))) {
    comp_mean = 49.267;
  }
  else if ((typeid(TIntegral) == typeid(float32)) ||
	   (typeid(TIntegral) == typeid(float64))) {
    comp_mean = 49.769;
  }
  else {
    return Error::handle(name(), L"rand", Error::TEST, __FILE__, __LINE__);
  }
  // set the seed
  //
  Random::GLOBAL_UNIFORM.seed(27);
    
  // generate N random numbers: use rand()
  //
  mean = 0.0;
  min = expected_max;
  max = expected_min;
    
  for (int32 i = 0; i < N; i++) {
      
    // take a random sample
    //
    TIntegral tmp = rand.rand((TIntegral)expected_min,
			      (TIntegral)expected_max);
      
    // update the mean
    //
    mean += tmp;
      
    // update the min/max
    //
    min = Integral::min(tmp, min);
    max = Integral::max(tmp, max);
  }
    
  mean /= (float64)N;
    
  // check if the computed values are in the proper range
  //
  if (!Integral::almostEqual(mean, comp_mean, 1.0)) {
    SysString out(L"mean = ");
    out.concat(mean);
    out.concat(L"; comp_mean = ");
    out.concat(comp_mean);
    Console::put(out);
    return Error::handle(name(), L"rand", Error::TEST, __FILE__, __LINE__);
  }
    
  if (min < expected_min) {
    SysString out(L"min = ");
    out.concat(min);
    out.concat(L"expected_min = ");
    out.concat(expected_min);
    Console::put(out);
    return Error::handle(name(), L"rand", Error::TEST, __FILE__, __LINE__);
  }
    
  if (max > expected_max) {
    SysString out(L"max = ");
    out.concat(max);
    out.concat(L"expected_max = ");
    out.concat(expected_max);
    Console::put(out);
    return Error::handle(name(), L"rand", Error::TEST, __FILE__, __LINE__);
  }
  //--------------------------------------------------------------------
  //
  // test grand(expected_mean, expected_stddev)
  //
  //--------------------------------------------------------------------  
    
  // determine the expected values based on the specific type:
  //  choose a mean and stdev that works for all datatypes
  //
  expected_mean = 128.0;
  float64 expected_stddev = 10.0;
  float64 comp_stddev;
  float64 stddev = 0;
    
  // determine the expected values based on the specific type
  //
  if ((typeid(TIntegral) == typeid(float32)) ||
      (typeid(TIntegral) == typeid(float64))) {
    comp_mean = 128;
    comp_stddev = 3.3166;
  }
  else {
    comp_mean = 127;
    comp_stddev = 11.7047;
  }
    
  // set the seed
  //
  Random::GLOBAL_GAUSSIAN.seed(27);
  mean = 0.0;
    
  // generate N random numbers: use grand()
  //
  for (int32 i = 0; i < N; i++) {
      
    // update the mean / stddev
    //
    TIntegral tmp = rand.grand((TIntegral)expected_mean,
			       (TIntegral)expected_stddev);
    mean += tmp;
      
    // for real numbers simple do simple multiplication
    //
    stddev += tmp*tmp;
  }
    
  // normalize the mean and stddev:
  //  note stddev = sqrt(E(x^2) - (Ex)^2)
  //
  mean = Integral::round((float64)mean / float64(N));
  stddev = Integral::round((float64)stddev / float64(N));
  stddev = Integral::sqrt(stddev - mean * mean);
    
  // check if the computed values are in the proper range
  //
  if (!Integral::almostEqual(mean, comp_mean)) {
    SysString out(L"mean = ");
    out.concat(mean);
    out.concat(L"; computed_mean = ");
    out.concat(comp_mean);
    Console::put(out);
    return Error::handle(name(), L"rand", Error::TEST, __FILE__, __LINE__);
  }
    
  if (!Integral::almostEqual(stddev, comp_stddev)) {
    SysString out(L"stddev = ");
    out.concat(stddev);
    out.concat(L"; computed_stddev = ");
    out.concat(comp_stddev);
    Console::put(out);
    return Error::handle(name(), L"rand", Error::TEST, __FILE__, __LINE__);
  }


  // reset indentation
  //
  if (level_a > Integral::NONE) {
    Console::decreaseIndention();
  }

  //---------------------------------------------------------------------------
  //
  // private methods
  //
  //---------------------------------------------------------------------------

  //  testing conversions
  //

  // set indentation
  //
  if (level_a > Integral::NONE) {
    Console::put(L"testing private methods: conversions...\n");
    Console::increaseIndention();
  }

  // test conversion with Byte
  //
  MScalar<byte8, byte8> scalar_byte;
  
  scalar_byte.assign((byte8)43);
  val0.assign(scalar_byte);
  val1.assign((TIntegral)43);
  val2.value_d = (TIntegral)scalar_byte;

  if ((val0 != val1) || (val0 != val2)) {
    return Error::handle(name(), L"assign(byte8)",
			 Error::TEST, __FILE__, __LINE__);
  }
   
  // test conversion with Int32
  //
  MScalar<int32, int32> scalar_long;
  
  scalar_long.assign((int32)43);
  val0.assign(scalar_long);
  val1.assign((TIntegral)43);
  val2.value_d = (TIntegral)scalar_long;
  
  if ((val0 != val1) || (val0 != val2)) {
    return Error::handle(name(), L"assign(int32)",
			 Error::TEST, __FILE__, __LINE__);
  }
  
  // test conversion with Int64
  //
  MScalar<int64, int64> scalar_llong;
  
  scalar_llong.assign((int64)43);
  val0.assign(scalar_llong);
  val1.assign((TIntegral)43);
  val2.value_d = (TIntegral)scalar_llong;
    
  if ((val0 != val1) || (val0 != val2)) {
    return Error::handle(name(), L"assign(int64)",
			 Error::TEST, __FILE__, __LINE__);
  }
  
  // test conversion with Int16
  //
  MScalar<int16, int16> scalar_short;
  
  scalar_short.assign((int16)43);
  val0.assign(scalar_short);
  val1.assign((TIntegral)43);
  val2.value_d = (TIntegral)scalar_short;
  
  if ((val0 != val1) || (val0 != val2)) {
    return Error::handle(name(), L"assign(int16)",
			 Error::TEST, __FILE__, __LINE__);
  }
  
  // test conversion with Ulong
  //
  MScalar<uint32, uint32> scalar_ulong;
  
  scalar_ulong.assign((uint32)43);
  val0.assign(scalar_ulong);
  val1.assign((TIntegral)43);
  val2.value_d = (TIntegral)scalar_ulong;
  
  if ((val0 != val1) || (val0 != val2)) {
    return Error::handle(name(), L"assign(uint32)",
			 Error::TEST, __FILE__, __LINE__);
  }
  
  // test conversion with Uint64
  //
  MScalar<uint64, uint64> scalar_ullong;
  
  scalar_ullong.assign((uint64)43);
  val0.assign(scalar_ullong);
  val1.assign((TIntegral)43);
  val2.value_d = (TIntegral)scalar_ullong;
  
  if ((val0 != val1) || (val0 != val2)) {
    return Error::handle(name(), L"assign(uint64)",
			 Error::TEST, __FILE__, __LINE__);
  }
  
  // test conversion with Ushort
  //
  MScalar<uint16, uint16> scalar_ushort;
  
  scalar_ushort.assign((uint16)43);
  val0.assign(scalar_ushort);
  val1.assign((TIntegral)43);
  val2.value_d = (TIntegral)scalar_ushort;
  
  if ((val0 != val1) || (val0 != val2)) {
    return Error::handle(name(), L"assign(uint16)",
			 Error::TEST, __FILE__, __LINE__);
  }

  // test conversion with Float64
  //
  MScalar<float64, float64> scalar_double;
  
  scalar_double.assign((float64)43);
  val0.assign(scalar_double);
  val1.assign((TIntegral)43);
  val2.value_d = (TIntegral)scalar_double;

  if ((val0 != val1) || (val0 != val2)) {
    return Error::handle(name(), L"assign(float64)",
			 Error::TEST, __FILE__, __LINE__);
  }
  
  // test conversion with Float
  //
  MScalar<float32, float32> scalar_float;
  
  scalar_float.assign((float32)43);
  val0.assign(scalar_float);
  val1.assign((TIntegral)43);
  val2.value_d = (TIntegral)scalar_float;
  
  if ((val0 != val1) || (val0 != val2)) {
    return Error::handle(name(), L"assign(float32)",
			 Error::TEST, __FILE__, __LINE__);
  }

  // test conversion with String
  //
  String str0;
  str0.assign((TIntegral)val0);
  TIntegral scalar_val;
  str0.get(scalar_val);
  val1.assign(str0);
  if (!val0.almostEqual(val1)) {
    return Error::handle(name(), L"<String::get>",
			 Error::TEST, __FILE__, __LINE__);
  }

  // reset indentation
  //
  if (level_a > Integral::NONE) {
    Console::decreaseIndention();
  }

  // exit gracefully
  //
  return true;
}
 
// declare classes that need to inherit MScalar
//
template bool8
MScalarMethods::diagnose<MScalar<ISIP_TEMPLATE_TARGET>, ISIP_TEMPLATE_T0>
(Integral::DEBUG level);
