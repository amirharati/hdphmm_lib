// file: $isip/class/math/scalar/MComplexScalar/mcscl_02.cc
// version: $Id: mcscl_02.cc 10636 2007-01-26 22:18:09Z tm334 $
//

// isip include files
//
#include "MComplexScalarMethods.h"
#include "MComplexScalar.h"
#include <typeinfo>

// method: diagnose
//
// arguments:
//  Integral::DEBUG level: (input) debug level for diagnostics
//
// return: logical error status
//
template<class TCScalar, class TIntegral>
bool8 MComplexScalarMethods::diagnose(Integral::DEBUG level_a) {

  //----------------------------------------------------------------------
  //
  // 0. preliminaries
  //
  //----------------------------------------------------------------------

  // output the class name
  //
  if (level_a > Integral::NONE) {
    SysString output(L"diagnosing class ");
    output.concat(name());
    output.concat(L": ");
    Console::put(output);
    Console::increaseIndention();
  }

  // call the sub diagnose methods
  //
  diagnose0<TCScalar, TIntegral>(level_a);
  diagnose1<TCScalar, TIntegral>(level_a);
  diagnose2<TCScalar, TIntegral>(level_a);
   
  //---------------------------------------------------------------------
  //
  // print completion message
  //
  //---------------------------------------------------------------------
  
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

// method: diagnose0
//
// arguments:
//  Integral::DEBUG level: (input) debug level for diagnostics
//
// return: logical error status
//
// this method tests required methods. note that i/o methods will be
// tested in the type-specific complex classes.
// 
template<class TCScalar, class TIntegral>
bool8 MComplexScalarMethods::diagnose0(Integral::DEBUG level_a) {

  //--------------------------------------------------------------------
  //
  // 1. testing required methods
  //
  //--------------------------------------------------------------------

  // set indentation
  //
  if (level_a > Integral::NONE) {
    Console::put(L"testing required public methods...\n");
    Console::increaseIndention();
  }

  // declare local variables
  TCScalar val6;

  // test the debug method
  //
  val6.setDebug(level_a);
  if (val6.debug_level_d != level_a) {
    return Error::handle(name(), L"debug", Error::TEST, __FILE__, __LINE__);
  }
 
  // test assign
  //
  val6.assign(3);
  if (val6 != 3) {
    return Error::handle(name(), L"assign", Error::TEST, __FILE__, __LINE__);
  }

  // test the copy constructor
  //
  TCScalar val7(val6);
  if (val6 != val7) {
    return Error::handle(name(), L"copy", Error::TEST, __FILE__, __LINE__);
  }
  
  // test the sizeof method
  //
  printf("val6.sofSize()=%d  sizeof(val6)=%ld  ",val6.sofSize(), sizeof(val6));
  if (val6.sofSize() != sizeof(val6)) {
    return Error::handle(name(), L"sofSize",
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

// method: diagnose1
//
// arguments:
//  Integral::DEBUG level: (input) debug level for diagnostics
//
// return: logical error status
//
// this method tests all functions inherited from MScalar for the
// case of complex numbers.
//
template<class TCScalar, class TIntegral>
bool8 MComplexScalarMethods::diagnose1(Integral::DEBUG level_a) {

  //--------------------------------------------------------------------
  //
  // 2. testing methods inherited from MScalar
  //
  //--------------------------------------------------------------------
  
  // declare some local variables
  //
  TCScalar val4;
  TCScalar val5;
  TCScalar val6;

  // set indentation
  //
  if (level_a > Integral::NONE) {
    Console::put(L"testing methods inherited from MScalar...\n");
    Console::increaseIndention();
  }
  
  // test assign method
  //
  val5.assign(3, 4);
  if ((val5.real() != 3) || (val5.imag() != 4)) {
  return Error::handle(name(), L"assign", Error::TEST, __FILE__, __LINE__);
  }
  
  // test operator +
  //
  val4.assign(1, 2);
  val6 = val4 + val5;
  if ((val6.real() != (TIntegral)4) || (val6.imag() != (TIntegral)6)) {
    return Error::handle(name(), L"operator +", Error::TEST, __FILE__, __LINE__);
  }      

  // test operator -
  //
  val6 = val5 - val4;
  if ((val6.real() != (TIntegral)2) || (val6.imag() != (TIntegral)2)) {
    return Error::handle(name(), L"operator -",
			 Error::TEST, __FILE__, __LINE__);
  }

  // test operator *
  //
  val6 = val4 * val5;
  if ((val6.real() != (TIntegral)-5) || (val6.imag() != (TIntegral)10)) {
    return Error::handle(name(), L"operator *",
			 Error::TEST, __FILE__, __LINE__);
  }

  // test operator /
  //
  val6 = val5 / val4;
    if ((!val6.almostEqual(SysComplex<TIntegral>
			   ((TIntegral)2.2, (TIntegral)-0.4)))) {
    return Error::handle(name(),
			 L"operator /", Error::TEST, __FILE__, __LINE__);
  }

  // test operator %
  // not done for complex numbers
  //
  
  // test operator ++ (post increment)
  //
  val6.assign(val4++);
  if ((val6.real() != (TIntegral)1) || (val6.imag() != (TIntegral)2)) {
    return Error::handle(name(), L"operator ++",
			 Error::TEST, __FILE__, __LINE__);
  }
   
  // test operator -- (post decrement)
  //
  val6.assign(val4--);  
  if ((val6.real() != (TIntegral)1) || (val6.imag() != (TIntegral)2)) {
    return Error::handle(name(), L"operator --",
			 Error::TEST, __FILE__, __LINE__);
  }
  
  // test operator ++ (pre increment)
  //
  val6.assign(++val4);
  if ((val6.real() != (TIntegral)2) || (val6.imag() != (TIntegral)2)) {
    return Error::handle(name(), L"++",
			 Error::TEST, __FILE__, __LINE__);  

  }
  
  // test operator -- (pre decrement)
  //
  val6.assign(--val4);
  if ((val6.real() != (TIntegral)0) || (val6.imag() != (TIntegral)2)) {
    return Error::handle(name(), L"--",
			 Error::TEST, __FILE__, __LINE__);
  }
  
  // test operator +=
  //
  val6 = val5;
  val6 += val4;
  if ((val6.real() != (TIntegral)4) || (val6.imag() != (TIntegral)6)) {
    return Error::handle(name(), L"+=", Error::TEST, __FILE__, __LINE__);
  }      

  // test operator -=
  //
  val6 = val5;
  val6 -= val4;
  if ((val6.real() != (TIntegral)2) || (val6.imag() != (TIntegral)2)) {
    return Error::handle(name(), L"-=", Error::TEST, __FILE__, __LINE__);
  }    

  // test operator *=
  //
  val6 = val5;
  val6 *= val4;
  if ((val6.real() != (TIntegral)-5) || (val6.imag() != (TIntegral)10)) {
    return Error::handle(name(), L"*=", Error::TEST, __FILE__, __LINE__);
  } 
  
  // test operator /=
  //
  val6 = val5;
  val6 /= val4;
  if ((!val6.almostEqual(SysComplex<TIntegral>((TIntegral)2.2))) ||
      (!val6.almostEqual(SysComplex<TIntegral>((TIntegral)0.4)))) {
    return Error::handle(name(), L"/=", Error::TEST, __FILE__, __LINE__);
  }
  
  // test operator ==
  //
  val6 = val5;
  if ((!val6.real() == (TIntegral)3) || (!val6.imag() == (TIntegral)4)) {
    return Error::handle(name(), L"==", Error::TEST, __FILE__, __LINE__);
  }
  
  // test operator !=
  //
  val6 = val5;
  if ((val6.real() != (TIntegral)3) || (val6.imag() != (TIntegral)4)) {
    return Error::handle(name(), L"!=", Error::TEST, __FILE__, __LINE__);
  }
    
  // test operator <
  //
  if ((val5.real() < (TIntegral)1) || (val5.imag() < (TIntegral)2)) {
    return Error::handle(name(), L"<", Error::TEST, __FILE__, __LINE__);
  }
   
  // test operator <=
  //
  if ((val5.real() <= (TIntegral)1) || (val5.imag() <= (TIntegral)2)) {
    return Error::handle(name(), L"<=", Error::TEST, __FILE__, __LINE__);
  }
    
  // test operator >
  //
  if ((!val5.real() > (TIntegral)1) || (!val5.imag() > (TIntegral)2)) {
    return Error::handle(name(), L">", Error::TEST, __FILE__, __LINE__);
  }
  
  // test operator >=
  //
  if ((!val5.real() >= (TIntegral)3) || (!val5.imag() > (TIntegral)2)) {
    return Error::handle(name(), L">=", Error::TEST, __FILE__, __LINE__);
  }
    
  //---------------------------------------------------------------------------
  //
  // class-specific public methods:
  //  equality and comparison methods
  //
  //---------------------------------------------------------------------------
  
  // test eq
  //
  if (val4.eq(val5)) {
    return Error::handle(name(), L"eq", Error::TEST, __FILE__, __LINE__);
  }
   
  // test ne
  //
  val6 = val5;
  if (val6.ne(val5)) {
    return Error::handle(name(), L"ne", Error::TEST, __FILE__, __LINE__);
  }
  
  // test lt
  //
  if (val5.lt(val4)) {
    return Error::handle(name(), L"lt", Error::TEST, __FILE__, __LINE__);
  }
  
  // test le
  //
  if (val5.le(val4)) {
    return Error::handle(name(), L"le", Error::TEST, __FILE__, __LINE__);
  }
  
  // test gt
  //
  if (val4.gt(val5)) {
    return Error::handle(name(), L"gt", Error::TEST, __FILE__, __LINE__);
  }
    
  // test ge
  //
  if (val4.ge(val5)) {
    return Error::handle(name(), L"ge", Error::TEST, __FILE__, __LINE__);
  }

  // bitwise and integer-specific operations not tested for complex numbers
  //
  
  //---------------------------------------------------------------------------
  //
  // class-specific public methods:
  //  basic mathematical methods
  //
  //---------------------------------------------------------------------------

  // test add
  //
  val6.add(val5, val4);
  if ((val6.real() != (TIntegral)4) || (val6.imag() != (TIntegral)6)) {
    return Error::handle(name(), L"add",
			 Error::TEST, __FILE__, __LINE__);
  }

  // test sub
  //
  val6.sub(val5, val4);
  if ((val6.real() != (TIntegral)2) || (val6.imag() != (TIntegral)2)) {
    return Error::handle(name(), L"sub",
			 Error::TEST, __FILE__, __LINE__);
  }
  
  // test mult
  //
  val6.mult(val5, val4);
  if ((val6.real() != (TIntegral)-5) || (val6.imag() != (TIntegral)10)) {
    return Error::handle(name(), L"mult",
			 Error::TEST, __FILE__, __LINE__);
  }
 
  // test div
  //
  val6.div(val5, val4);
  if (!Integral::almostEqual(val6.real(), (TIntegral)2.2) &&
      !Integral::almostEqual(val6.imag(), (TIntegral)-0.4)) {
    return Error::handle(name(), L"div",
 			 Error::TEST, __FILE__, __LINE__);
  }

  // declare some local variables
  //
  TCScalar val0;
  TCScalar val1;
    
  // test functions work for floating point
  //
  if ((typeid(TIntegral) != typeid(int32))) {
    
    // test acos
    //    
    val0.assign(SysComplex<TIntegral>
		((TIntegral)(Integral::PI / (TIntegral)3), (TIntegral)0.5));
    val1.cos(val0);
    if (!val0.almostEqual(val1.acos())) {
      val0.debug(L"val0.acos");
      val1.debug(L"val1.acos");      
      return Error::handle(name(), L"acos", Error::TEST, __FILE__, __LINE__);
    }

    // test acosh
    //
    val0.assign(SysComplex<TIntegral>
		((TIntegral)(Integral::PI / (TIntegral)3), (TIntegral)0.5));
    val1.cosh(val0);
    if (!val0.almostEqual(val1.acosh())) {
      val0.debug(L"val0.acosh");
      val1.debug(L"val1.acosh");      
      return Error::handle(name(), L"acosh", Error::TEST, __FILE__, __LINE__);
    }
  
    // test asin
    //
    val0.assign(SysComplex<TIntegral>
		((TIntegral)(Integral::PI / (TIntegral)6), (TIntegral)0.5));
    val1.sin(val0);
    if (!val0.almostEqual(val1.asin())) {
      val0.debug(L"val0.asin");
      val1.debug(L"val1.asin");          
      return Error::handle(name(), L"asin", Error::TEST, __FILE__, __LINE__);
    }

    // test asinh
    //
    val0.assign(SysComplex<TIntegral>
		((TIntegral)(Integral::PI / (TIntegral)6), (TIntegral)0.5));
    val1.sinh(val0);
    if (!val0.almostEqual(val1.asinh())) {
      val0.debug(L"val0.asinh");
      val1.debug(L"val1.asinh");              
      return Error::handle(name(), L"asinh", Error::TEST, __FILE__, __LINE__);
    }
    
    // test atan
    //
    val0.assign(SysComplex<TIntegral>
		((TIntegral)(Integral::QUARTER_PI), (TIntegral)0.5));
    val1.tan(val0);
    if (!val0.almostEqual(val1.atan())) {
      val0.debug(L"val0.atan");
      val1.debug(L"val1.atan");              
      return Error::handle(name(), L"atan", Error::TEST, __FILE__, __LINE__);
    }
  
    // test atanh
    //
    val0.assign(SysComplex<TIntegral>
		((TIntegral)(Integral::QUARTER_PI), (TIntegral)0.5));    
    val1.tanh(val0);
    if (!val0.almostEqual(val1.atanh())) {
      val0.debug(L"val0.atanh");
      val1.debug(L"val1.atanh");              
      return Error::handle(name(), L"atanh", Error::TEST, __FILE__, __LINE__);
    }
 
    // test ceil
    //
    val0.assign ((TIntegral)3.3, (TIntegral)4.3);
    val1.ceil((SysComplex<TIntegral>)val0);
    if ((!val1.almostEqual(SysComplex<TIntegral>
			   ((TIntegral)4, (TIntegral)5)))) {
      return Error::handle(name(), L"ceil", Error::TEST, __FILE__, __LINE__);
    }

    // test centerClip
    // not tested for complex numbers
  
    // test cos
    //
    val0.assign(SysComplex<TIntegral>
		((TIntegral)(Integral::PI / 3), (TIntegral)0.5));    
    val1.cos(val0);
    if (!val1.almostEqual(SysComplex<TIntegral>
			  ((TIntegral)0.5638, (TIntegral)-0.4513))) {
      val0.debug(L"val0.cos");
      val1.debug(L"val1.cos");                  
      return Error::handle(name(), L"cos", Error::TEST, __FILE__, __LINE__);
    }
  
    // test cosh
    //
    val0.assign(SysComplex<TIntegral>
		((TIntegral)(Integral::PI / 3), (TIntegral)0.5));        
    val1.cosh(val0);
    if (!val1.almostEqual(SysComplex<TIntegral>
			  ((TIntegral)1.404, (TIntegral)0.599))) {
      val0.debug(L"val0.cosh");
      val1.debug(L"val1.cosh");                      
      return Error::handle(name(), L"cosh", Error::TEST, __FILE__, __LINE__);
    }
  
//     // test exp
//     //
//     val0.assign (4, 3);
//     val1.log(val0);
//     val1.exp();
//     if (!val0.almostEqual(val1)) {
//       val1.debug(L"exp");
//       return Error::handle(name(), L"exp", Error::TEST, __FILE__, __LINE__);
//     }
 
//     // test exp2
//     //
//     val1.log2(val0);
//     val1.exp2();
//     if (!val0.almostEqual(val1)) {
//       val1.debug(L"exp2 test");
//       return Error::handle(name(), L"exp2", Error::TEST, __FILE__, __LINE__);
//     }

//     // test exp10
//     //
//     val1.log10(val0);
//     val1.exp10();
//     if (!val0.almostEqual(val1)) {
//       val1.debug(L"exp10 test");
//       return Error::handle(name(), L"exp10", Error::TEST, __FILE__, __LINE__);
//     }
    
    // test floor
    //
    val0.assign((TIntegral)3.3, (TIntegral)4.3);
    val1.floor((SysComplex<TIntegral>)val0);
    if ((!val1.almostEqual(SysComplex<TIntegral>
			   ((TIntegral)3, (TIntegral)4)))) {
      return Error::handle(name(), L"floor", Error::TEST, __FILE__, __LINE__);
    }
  }
   
  // test fraction
  // not tested for complex numbers
  //
   
  // test hash
  //
  val0.assign(4, 3);
  uint32 h1 = val0.hash((int32)104);
  if (!(h1 == (uint32)42)) {
    return Error::handle(name(), L"hash",Error::TEST, __FILE__, __LINE__);
  }

  // test inverse
  //
  TCScalar val8;
  val8.assign(4, 3);
  val8.inverse();
  if ((!val8.almostEqual(SysComplex<TIntegral>
			 ((TIntegral)0.16, (TIntegral)-0.12)))) {
    return Error::handle(name(), L"inverse", Error::TEST, __FILE__, __LINE__);
  }

  // test centerClip
  //
  val0.assign(40, 30);
  val1.assign(-25, 36);
  val8.assign(-18, -19);  
  val0.centerClip(20, 45);
  val1.centerClip(20, 45);
  val8.centerClip(20, 45);

  if ((!val0.almostEqual(SysComplex<TIntegral>
			 ((TIntegral)40, (TIntegral)30))) ||
      (!val1.almostEqual(SysComplex<TIntegral>
			 ((TIntegral)-25.6678, (TIntegral)36.9616))) ||
      (!val8.almostEqual(SysComplex<TIntegral>
			 ((TIntegral)-13.7549, (TIntegral)-14.5191)))) {
    return Error::handle(name(), L"centerClip",
			 Error::TEST, __FILE__, __LINE__);
  }

  // test fraction
  //
  if (typeid(TIntegral) != typeid(int32)) {
    val0.fraction();
    val1.fraction();
    if ((!val0.almostEqual(SysComplex<TIntegral>
			   ((TIntegral)0, (TIntegral)0))) ||
	(!val1.almostEqual(SysComplex<TIntegral>
			   ((TIntegral)-0.6678, (TIntegral)0.9616)))) {
      return Error::handle(name(), L"fraction",
			   Error::TEST, __FILE__, __LINE__);
    }
  }

  // test limitMag
  // not tested for complex numbers
  //
  TCScalar val9, val_res;
  val_res.assign(SysComplex<TIntegral>((TIntegral)1.6, (TIntegral)1.2));
  val9.assign(4, 3);
  val9.limitMag(4, 2);
  if (!val9.almostEqual(val_res)) {
    val9.debug(L"val9");
    val_res.debug(L"val_res");
      return Error::handle(name(), L"limitMag", Error::TEST, __FILE__, __LINE__);    
    }
  
   // test functions work for floating point
   //
   if ((typeid(TIntegral) != typeid(int32))) {
    
    // test log
    //    
    val0.assign (4, 3);
    val1.log(val0);
    if (!val1.almostEqual(SysComplex<TIntegral>
			  ((TIntegral)1.60944, (TIntegral)0.643501))) {
      val1.debug(L"log");
      return Error::handle(name(), L"log", Error::TEST, __FILE__, __LINE__);
    }

//     // test log2
//     //
//     val1.log2(val0);
//     if (!val1.almostEqual(SysComplex<TIntegral>
// 			  ((TIntegral)2.32193, (TIntegral)0.928376))) {
//       val1.debug(L"log2");
//       return Error::handle(name(), L"log2", Error::TEST, __FILE__, __LINE__);
//     }

//     // test log10
//     //
//     val1.log10(val0);
//     if (!val1.almostEqual(SysComplex<TIntegral>
// 			  ((TIntegral)0.69897, (TIntegral)0.279469))) {
//       val1.debug(L"log10");
//       return Error::handle(name(), L"log10", Error::TEST, __FILE__, __LINE__);
//     }
    
//     // test log1p
//     //
//     val1.log1p(val0);
//     if (!val1.almostEqual(SysComplex<TIntegral>
// 			  ((TIntegral)1.76318, (TIntegral)0.54042))) {
//       val1.debug(L"log1p");
//       return Error::handle(name(), L"log1p", Error::TEST, __FILE__, __LINE__);
//     }

   }

  // test max
  //
  val1.assign (2, 3);
  val0.assign (3, 4);
  TCScalar val2;
  val2.max(val0, val1);
  if ((!val2.almostEqual(val0))) {
    return Error::handle(name(), L"max", Error::TEST, __FILE__, __LINE__);
  }
      
  // test min
  // 
  val2.min(val0, val1);
  if ((!val2.almostEqual(val1))) {
    return Error::handle(name(), L"min", Error::TEST, __FILE__, __LINE__);
  }
  
  // test neg
  //
  val2.neg(val0);
  if ((!val2.almostEqual(SysComplex<TIntegral>
			 ((TIntegral)-3, (TIntegral)-4)))) {
    val2.debug(L"neg");
    return Error::handle(name(), L"neg", Error::TEST, __FILE__, __LINE__);
  }

  // test pow
  //
  val0.pow((TIntegral)2);
  if ((!val0.almostEqual(SysComplex<TIntegral>
			 ((TIntegral)-7, (TIntegral)24)))) {
    val2.debug(L"pow");
    return Error::handle(name(), L"pow", Error::TEST, __FILE__, __LINE__);
  }

  if ((typeid(TIntegral) != typeid(int32))) {   

    // test rceil
    //
    val0.assign ((TIntegral)3.3, (TIntegral)4.3);
    val2.rceil(val0);
    if ((!val2.almostEqual(SysComplex<TIntegral>
			   ((TIntegral)0.7, (TIntegral)0.7)))) {
      val2.debug(L"rceil");
      return Error::handle(name(), L"rceil", Error::TEST, __FILE__, __LINE__);
    }
    
    // test rfloor
    //
    val2.rfloor(val0);
    if ((!val2.almostEqual(SysComplex<TIntegral>
			   ((TIntegral)-0.3, (TIntegral)-0.3)))) {
      val2.debug(L"rfloor");
      return Error::handle(name(), L"rfloor", Error::TEST, __FILE__, __LINE__);
    }
    
    // test round
    //
    val2.round((SysComplex<TIntegral>)val0);
    if ((!val2.almostEqual(SysComplex<TIntegral>
			   ((TIntegral)3, (TIntegral)4)))) {
      val2.debug(L"round");
      return Error::handle(name(), L"round", Error::TEST, __FILE__, __LINE__);
    } 
    
    // test sign
    //
    val2.sign(val0);
    if ((!val2.almostEqual(SysComplex<TIntegral>
			   ((TIntegral)1, (TIntegral)0)))) {
      val2.debug(L"sign");
      return Error::handle(name(), L"sign", Error::TEST, __FILE__, __LINE__);
    }
    
    // test sin
    //
    val0.assign(SysComplex<TIntegral>
		((TIntegral)(Integral::PI / (float64)6), (TIntegral)0.5));
    val1.sin(val0);
    if (!val1.almostEqual(SysComplex<TIntegral>
			  ((TIntegral)0.5638, (TIntegral)0.4513))) {
      val0.debug(L"val0.sin");
      val1.debug(L"val1.sin");
      return Error::handle(name(), L"sin", Error::TEST, __FILE__, __LINE__);
    }
    
    // test sinh
    //
    val0.assign(SysComplex<TIntegral>
		((TIntegral)(Integral::PI / (float64)6), (TIntegral)0.5));  
    val1.sinh(val0);
    if (!val1.almostEqual(SysComplex<TIntegral>
			  ((TIntegral)0.4808, (TIntegral)0.5467)))  {
      val0.debug(L"val0.sinh");
      val1.debug(L"val1.sinh");    
      return Error::handle(name(), L"sinh", Error::TEST, __FILE__, __LINE__);
    }

    // test sqrt
    //
    val0.assign ((TIntegral)3.3, (TIntegral)4.3);
    val2.sqrt(val0);
    if ((!val2.almostEqual(SysComplex<TIntegral>
			   ((TIntegral)2.0881, (TIntegral)1.02964)))) {
      val2.debug(L"sqrt");
      return Error::handle(name(), L"sqrt", Error::TEST, __FILE__, __LINE__);
    }

  } // end of if != typeid(int32) 

  // test square
  //
  val0.assign (3, 4);
  val2.square(val0);
  if ((!val2.almostEqual(SysComplex<TIntegral>
			 ((TIntegral)-7, (TIntegral)24)))) {
    return Error::handle(name(), L"square", Error::TEST, __FILE__, __LINE__);
  }
  
  if ((typeid(TIntegral) != typeid(int32))) { 
    // test tan
    //
    val0.assign(SysComplex<TIntegral>
		((TIntegral)Integral::QUARTER_PI, (TIntegral)0.5));
    val1.tan(val0);
    if (!val1.almostEqual(SysComplex<TIntegral>
			  ((TIntegral)0.648, (TIntegral)0.7616))) {
      val0.debug(L"val0.tan");
      val1.debug(L"val1.tan");          
      return Error::handle(name(), L"tan", Error::TEST, __FILE__, __LINE__);
    }
    
    // test tanh
    //
    val0.assign(SysComplex<TIntegral>
		((TIntegral)1.0, (TIntegral)0.5));
    val1.tanh(val0);
    if (!val1.almostEqual(SysComplex<TIntegral>
			  ((TIntegral)0.8430, (TIntegral)0.1956))) {
      val0.debug(L"val0.tanh");
      val1.debug(L"val1.tanh");                
      return Error::handle(name(), L"tanh", Error::TEST, __FILE__, __LINE__);
    }
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
// arguments:
//  Integral::DEBUG level: (input) debug level for diagnostics
//
// return: logical error status
//
// this method tests all non-required methods found in MScalarComplex.h
// (functions not implemented via MScalar and not part of the required
// methods section).
//

template<class TCScalar, class TIntegral>
bool8 MComplexScalarMethods::diagnose2(Integral::DEBUG level_a) {

  //--------------------------------------------------------------------
  //
  // 3. testing the random number generation methods
  //
  //--------------------------------------------------------------------

  // set indentation
  //
  if (level_a > Integral::NONE) {
    Console::put(L"testing methods not implemented via MComplexScalar...\n");
    Console::increaseIndention();
  }
  
  // declare local variables
  //
  int32 N = 100000;
  
  SysComplex<TIntegral> min, max, mean;
  SysComplex<TIntegral> expected_min, expected_max, expected_mean;
  SysComplex<TIntegral> comp_mean;
  
  TCScalar rand;

  //--------------------------------------------------------------------
  //
  // test rand()
  //
  //--------------------------------------------------------------------
    
  // determine the expected values based on the specific type
  //
  if ((typeid(TIntegral) == typeid(float32)) ||
      (typeid(TIntegral) == typeid(float64))) {
    expected_min = 0;
    expected_max = SysComplex<TIntegral>(1, 1);
    expected_mean = SysComplex<TIntegral>((TIntegral)0.5, (TIntegral)0.5);
    comp_mean = SysComplex<TIntegral>((TIntegral)0.5, (TIntegral)0.5);
  }
  else if (typeid(TIntegral) == typeid(int32)) {
    expected_min = SysComplex<TIntegral>((int32)-100,(int32)-100);
    expected_max = SysComplex<TIntegral>((int32)100,
					 (int32)100);
    expected_mean = SysComplex<TIntegral>(0, 0);
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
    SysComplex<TIntegral> tmp = rand.rand(expected_min, expected_max);
  
    // update the mean
    //
    mean += tmp;
  
    // update the min/max
    //
    min = SysComplex<TIntegral>((TIntegral)Integral::min(tmp.real(),
							 min.real()),
				(TIntegral)Integral::min(tmp.imag(),
							 min.imag()));
    max = SysComplex<TIntegral>((TIntegral)Integral::max(tmp.real(),
							 max.real()),
				(TIntegral)Integral::max(tmp.imag(),
							 max.imag()));
  }
  
  mean /= N;
   
  // check if the computed values are in the proper range
  //
  if (!Integral::almostEqual(mean, comp_mean, 2.0)) {
    SysString out(L"mean = ");
    out.concat(mean);
    out.concat(L"; comp_mean = ");
    out.concat(comp_mean);
    Console::put(out);
    return Error::handle(name(), L"rand", Error::TEST, __FILE__, __LINE__);
  }

  if (min.real() < expected_min.real() || min.imag() < expected_min.imag()) {
    SysString out(L"min = ");
    out.concat(min);
    out.concat(L"expected_min");
    out.concat(expected_min);
    Console::put(out);
    return Error::handle(name(), L"rand", Error::TEST, __FILE__, __LINE__);
  }

  if (max.real() > expected_max.real() || max.imag() > expected_max.imag()) {
    SysString out(L"max = ");
    out.concat(max);
    out.concat(L"expected_max");
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
  expected_min = SysComplex<TIntegral>((TIntegral)-10.0, (TIntegral)-5.0);
  expected_max = SysComplex<TIntegral>((TIntegral)30.0, (TIntegral)15.0);
  expected_mean = (expected_min + expected_max) / (TIntegral)2;
  
  if ((typeid(TIntegral) == typeid(float32)) ||
      (typeid(TIntegral) == typeid(float64))) {
    comp_mean = SysComplex<TIntegral>((TIntegral)10.0, (TIntegral)5.0);
  }
  else if (typeid(TIntegral) == typeid(int32)) {
    comp_mean = SysComplex<TIntegral>(9, 4);
  }
  else {
    return Error::handle(name(), L"rand", Error::TEST, __FILE__, __LINE__);
  }
  
  // set the seed
  //
  Random::GLOBAL_UNIFORM.seed(27);
  
  // generate N random numbers: use rand()
  //
  mean = (TIntegral)0.0;
  min = expected_max;
  max = expected_min;

  for (int32 i = 0; i < N; i++) {

    // take a random sample
    //
    SysComplex<TIntegral> tmp = rand.rand((SysComplex<TIntegral>)expected_min,
					  (SysComplex<TIntegral>)expected_max);
    // update the mean
    //
    mean += tmp;
  
    // update the min/max
    //
    min = SysComplex<TIntegral>((TIntegral)Integral::min(tmp.real(),
							 min.real()),
				(TIntegral)Integral::min(tmp.imag(),
							 min.imag()));
    max = SysComplex<TIntegral>((TIntegral)Integral::max(tmp.real(),
							 max.real()),
				(TIntegral)Integral::max(tmp.imag(),
							 max.imag()));
  }

  mean /= (TIntegral)N;
  
  // check if the computed values are in the proper range
  //
  if (!Integral::almostEqual(mean, comp_mean, 4.0)) {
    SysString out(L"mean = ");
    out.concat(mean);
    out.concat(L"; comp_mean = ");
    out.concat(comp_mean);
    Console::put(out);
    return Error::handle(name(), L"rand", Error::TEST, __FILE__, __LINE__);
  }
  
  if (min.real() < expected_min.real() || min.imag() < expected_min.imag()) {
    SysString out(L"min = ");
    out.concat(min);
    out.concat(L"expected_min");
    out.concat(expected_min);
    Console::put(out);
    return Error::handle(name(), L"rand", Error::TEST, __FILE__, __LINE__);
  }

  if (max.real() > expected_max.real() || max.imag() > expected_max.imag()) {
    SysString out(L"max = ");
    out.concat(max);
    out.concat(L"expected_max");
    out.concat(expected_max);
    Console::put(out);
    return Error::handle(name(), L"rand", Error::TEST, __FILE__, __LINE__);
  }
  
  //---------------------------------------------------------------------------
  //
  // test grand(expected_mean, expected_stddev)
  //
  //---------------------------------------------------------------------------

  // determine the expected values based on the specific type:
  //  choose a mean and stdev that works for all datatypes
  //
  expected_mean = SysComplex<TIntegral>((TIntegral)128.0, (TIntegral)-14.0);
  SysComplex<TIntegral> expected_stddev((TIntegral)10.0, (TIntegral)30.0);
  SysComplex<TIntegral> comp_stddev;
  float64 stddev_r = 0.0;
  float64 stddev_i = 0.0;
  float64 mean_r = 0.0;
  float64 mean_i = 0.0;
  
  // set the seed
  //
  Random::GLOBAL_GAUSSIAN.seed(27);
  mean = (TIntegral)0.0;
 
  // generate N random numbers: use grand()
  //
  for (int32 i = 0; i < N; i++) {

    // generate a random number
    //
    SysComplex<TIntegral> tmp =
      rand.grand((SysComplex<TIntegral>)expected_mean,
		 (SysComplex<TIntegral>)expected_stddev);

    // update the mean / stddev
    //
    mean += tmp;
    stddev_r += tmp.real() * tmp.real();
    stddev_i += tmp.imag() * tmp.imag();
  } 
  
  // normalize the mean and stddev:
  //  note stddev = sqrt(E(x^2) - (Ex)^2)
  //
  // use the same equation for real and complex, but for complex we
  // want to calculate each channel independently.
  //
  mean_r = (float64)mean.real() / (float64)N;
  stddev_r = (float64)stddev_r / (float64)N;
  stddev_r = Integral::sqrt(stddev_r - mean_r * mean_r);
  
  mean_i = (float64)mean.imag() / (float64)N;
  stddev_i = (float64)stddev_i / (float64)N;
  stddev_i = Integral::sqrt(stddev_i - mean_i * mean_i);

  // change to float64 to compare
  //  
  SysComplex<float64> mean_temp(mean_r, mean_i);
  SysComplex<float64> comp_mean_temp(expected_mean);
  
  // check if the computed values are in the proper range
  //
  if (!Integral::almostEqual(mean_temp, comp_mean_temp, 5.0)) {
    SysString out(L"expected_mean = ");
    out.concat(comp_mean_temp);
    out.concat(L"; computed_mean = ");
    out.concat(mean_temp);
    Console::put(out);
    return Error::handle(name(), L"rand", Error::TEST, __FILE__, __LINE__);
  }

  // change to float64 to compare
  //  
  SysComplex<float64> stddev_temp(stddev_r, stddev_i);
  SysComplex<float64> comp_stddev_temp(expected_stddev);
  
  if (!Integral::almostEqual(stddev_temp, comp_stddev_temp, 5.0)) {
    SysString out(L"expected_stddev = ");
    out.concat(comp_stddev_temp);
    out.concat(L"; computed_stddev = ");
    out.concat(stddev_temp);
    Console::put(out);
    return Error::handle(name(), L"rand", Error::TEST, __FILE__, __LINE__);
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

template bool8
MComplexScalarMethods::diagnose<MComplexScalar<ISIP_TEMPLATE_TARGET>, ISIP_TEMPLATE_T0>(Integral::DEBUG level_a);
