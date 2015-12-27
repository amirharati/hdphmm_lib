// file: $isip/class/system/SysComplex/SysComplexDiagnose.h
// version: $Id: SysComplexDiagnose.h 10640 2007-01-27 02:36:04Z tm334 $
//

// make sure definitions are made only once
//
#ifndef ISIP_COMPLEX_DIAGNOSE
#define ISIP_COMPLEX_DIAGNOSE

// isip include files
//
#ifndef ISIP_COMPLEX
#include "SysComplex.h"
#endif

#ifndef ISIP_SYS_STRING
#include "SysString.h"
#endif

#ifndef ISIP_CONSOLE
#include "Console.h"
#endif

// SysComplexDiagnose: a class that contains the diagnose method
// of SysComplex class.
//
template<class TObject>
class SysComplexDiagnose : public SysComplex<TObject> {
  
  //---------------------------------------------------------------------------
  //
  // public constants
  //
  //---------------------------------------------------------------------------
public:
  
  // define the class name
  //
  static const SysString CLASS_NAME;

  //----------------------------------------
  //
  // i/o related constants
  //
  //----------------------------------------  
  
  //----------------------------------------
  //
  // default values and arguments
  //
  //----------------------------------------
  
  // default values
  //
  
  // default arguments to methods
  //
  
  //----------------------------------------
  //
  // error codes
  //
  //----------------------------------------  
  
  //---------------------------------------------------------------------------
  //
  // protected data
  //
  //---------------------------------------------------------------------------
protected:
  
  //---------------------------------------------------------------------------
  //
  // required public methods
  //
  //---------------------------------------------------------------------------
public:
  
  // method: name
  //
  static const SysString& name();

  // other static methods
  //  
  static bool8 diagnose(Integral::DEBUG debug_level);
  
  // debug methods
  //  these methods are omitted since this class does not have data
  //  members and operations  
  //
  
  // destructor/constructor(s):
  //  these methods are omitted since this class does not have data
  //  members and operations
  //

  // assign methods:
  //  these methods are omitted since this class does not have data
  //  members and operations
  //

  // operator= methods:
  //  these methods are omitted since this class does not have data
  //  members and operations
  //  

  // i/o methods:
  //  these methods are omitted since this class does not have data
  //  members and operations
  //

  // equality methods:
  //  these methods are omitted since this class does not have data
  //  members and operations
  //

  // memory-management methods:
  //  these methods are omitted since this class does not have data
  //  members and operations
  //

  //---------------------------------------------------------------------------
  //
  // class-specific public methods
  //
  //---------------------------------------------------------------------------

  //  these methods are omitted since this class does not have data
  //  members and operations
  //
  
  //---------------------------------------------------------------------------
  //
  // private methods
  //
  //---------------------------------------------------------------------------
private:

  // additional diagnose methods
  //
  static bool8 diagnose0(Integral::DEBUG debug_level);
  static bool8 diagnose1(Integral::DEBUG debug_level);
  static bool8 diagnose2(Integral::DEBUG debug_level);  

};

// below are all the methods for the SysComplexDiagnose template class
//
template <class TObject>
const SysString SysComplexDiagnose<TObject>::CLASS_NAME(L"SysComplex");

template <class TObject>
const SysString& SysComplexDiagnose<TObject>::name() {
  return CLASS_NAME;
}

//----------------------------------------------------------------------
//
// required static methods
//
//----------------------------------------------------------------------

// method: diagnose
//
// arguments:
//  Integral::DEBUG level: (input) debug level for diagnostics
//
// return: a bool8 value indicating status
//
// this method is a wrapper that tests three specific types: float32, float64,
// and int32.
//
template<class TObject>
bool8 SysComplexDiagnose<TObject>::diagnose(Integral::DEBUG level_a) {

  // test the type "float32"
  //
  diagnose0(level_a);
  
  // test the type "float64"
  //
  diagnose1(level_a);
  
  // test the type "int32"
  //
  diagnose2(level_a);

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

// method: diagnose0
//
// arguments:
//  Integral::DEBUG level: (input) debug level for diagnostics
//
// return: a bool8 value indicating status
//
// this method performs diagnostics for the type "float32"
//
template<class TObject>
bool8 SysComplexDiagnose<TObject>::diagnose0(Integral::DEBUG level_a) {

  //----------------------------------------------------------------------
  //
  //  preliminaries
  //
  //----------------------------------------------------------------------

  // output the class name
  //
  if (level_a > Integral::NONE) {
    SysString output(L"diagnosing class ");
    output.concat(CLASS_NAME);
    output.concat(L" for the type float32: ");
    Console::put(output);
    Console::increaseIndention();
  }
  
  //---------------------------------------------------------------------
  //
  //  required public methods:
  //
  //---------------------------------------------------------------------

  // set indentation
  //
  if (level_a > Integral::NONE) {
    Console::put
      (L"testing class-specific public methods: required methods...\n");
    Console::increaseIndention();
  }

  // test constructor
  //
  const SysComplex<float32> c0(4.0, 2.0);
  const SysComplex<float32> c1(5);
  const SysComplex<float32> c2(0, 3.3);
  SysComplex<float32> t(3.4, 5.6);
  float32 r1 = 5;
		     
  // test copy constructor
  //
  SysComplex<float32> c3(c0);
  if (!Integral::almostEqual(c3, c0)) {
    return Error::handle(name(), L"almostEqual",
			 Error::TEST, __FILE__, __LINE__);
  }
  
  // test operator = (assignment)
  //
  c3 = c2;
  if (!Integral::almostEqual(c3, c2)) {
   return Error::handle(name(), L"almostEqual",
			 Error::TEST, __FILE__, __LINE__);
  }
  
  // reset indentation
  //
  if (level_a > Integral::NONE) {
    Console::decreaseIndention();
  }

  //---------------------------------------------------------------------
  //
  // class-specific public methods: other constructors, assignment,
  // casting, and component extraction methods
  //
  //---------------------------------------------------------------------

  // set indentation
  //
  if (level_a > Integral::NONE) {
    Console::put
      (L"testing class-specific public methods: assignment, casting...\n");
    Console::increaseIndention();
  }

  // test assign
  //
  c3.assign(5, 6);
  if (!Integral::almostEqual(c3, SysComplex<float32>(5, 6))) {
   return Error::handle(name(), L"almostEqual",
			 Error::TEST, __FILE__, __LINE__);
  }
  
  // test operator = (assignment)
  //
  c3 = t;
  if (!Integral::almostEqual(c3, t)) {
   return Error::handle(name(), L"almostEqual",
			 Error::TEST, __FILE__, __LINE__);
  }

  // test cast operator
  //
  if (!Integral::almostEqual(SysComplex<int32>(c0) , SysComplex<int32>(4, 2))) { 
   return Error::handle(name(), L"almostEqual",
			 Error::TEST, __FILE__, __LINE__);
  }
  
  // test real
  //
  if (!Integral::almostEqual(c3.real(), t.real())) {
   return Error::handle(name(), L"almostEqual",
			 Error::TEST, __FILE__, __LINE__);
  }
  
  // test imag
  //
  if (!Integral::almostEqual((float64)c2.imag(), 3.3)) {
   return Error::handle(name(), L"almostEqual",
			 Error::TEST, __FILE__, __LINE__);
  }
  
  // test mag
  //
  if (!Integral::almostEqual(c0.mag(), 4.4721)) {
   return Error::handle(name(), L"almostEqual",
			 Error::TEST, __FILE__, __LINE__);
  }
  
  // test angle
  //
  if (!Integral::almostEqual(c0.angle(), 0.4636)) {
   return Error::handle(name(), L"almostEqual",
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
  //  accumulative arithmetic functions with SysComplex and TIntegral types
  //
  //---------------------------------------------------------------------------

  // set indentation
  //
  if (level_a > Integral::NONE) {
    Console::put(L"testing class-specific public methods: accumulative...\n");
    Console::increaseIndention();
  }
  
  // test operator +=
  //
  c3 = c2;
  c3 += c0;
  if (!Integral::almostEqual(c3 , SysComplex<float32>(4, 5.3))) {
   return Error::handle(name(), L"almostEqual",
			 Error::TEST, __FILE__, __LINE__);
  }
  
  // test operator -=
  //
  c3 = c2;
  c3 -= c0;
  if (!Integral::almostEqual(c3 , SysComplex<float32>(-4, 1.3))) {
   return Error::handle(name(), L"almostEqual",
			 Error::TEST, __FILE__, __LINE__);
  }

  // test operator *=
  //
  c3 = c2;
  c3 *= c0;
  if (!Integral::almostEqual(c3 , SysComplex<float32>(-6.6, 13.2))) {
   return Error::handle(name(), L"almostEqual",
			 Error::TEST, __FILE__, __LINE__);
  }
    
  // test operator /=
  //
  if (!Integral::almostEqual(c0 / c2, SysComplex<float32>(0.6061, -1.2121))) {
   return Error::handle(name(), L"operator /", Error::TEST, __FILE__, __LINE__);
  }
    
  // test operator +=
  //
  c3 = c2;
  c3 += 2;
  if (!Integral::almostEqual(c3 , SysComplex<float32>(2, 3.3))) {
   return Error::handle(name(), L"almostEqual",
			 Error::TEST, __FILE__, __LINE__);
  }

  // test operator -=
  //
  c3 = c2;
  c3 -= 2;
  if (!Integral::almostEqual(c3 , SysComplex<float32>(-2, 3.3))) {
   return Error::handle(name(), L"almostEqual",
			 Error::TEST, __FILE__, __LINE__);
  }

  // test operator *=
  //
  c3 = c2;
  c3 *= 2;
  if (!Integral::almostEqual(c3 , SysComplex<float32>(0, 6.6))) {
   return Error::handle(name(), L"almostEqual",
			 Error::TEST, __FILE__, __LINE__);
  }  

  // test operator /=
  //
  c3 = c2;
  c3 /= 2;
  if (!Integral::almostEqual(c3 , SysComplex<float32>(0, 1.65))) {
   return Error::handle(name(), L"almostEqual",
			 Error::TEST, __FILE__, __LINE__);
  }  

  // test operator ++ (post-increment)
  //
  c3 = c1;
  c3 = c3++;
  if (!Integral::almostEqual(c3, 5)) {
   return Error::handle(name(), L"almostEqual",
			 Error::TEST, __FILE__, __LINE__);
  }  
  
  // test operator -- (post-decrement)
  //
  c3 = c1;
  c3 = c3--; 
  if (!Integral::almostEqual(c3, 5)) {
   return Error::handle(name(), L"almostEqual",
			 Error::TEST, __FILE__, __LINE__);
  }
  
  // test operator ++ (pre-increment)
  //
  c3 = c1;
  c3 = ++c3; 
  if (!Integral::almostEqual(c3, 6)) {
   return Error::handle(name(), L"almostEqual",
			 Error::TEST, __FILE__, __LINE__);
  }
  
  // test operator -- (pre-decrement)
  //
  c3 = c1;
  c3 = --c3; 
  if (!Integral::almostEqual(c3, 4)) {
   return Error::handle(name(), L"almostEqual",
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
  //  relational functions with SysComplex and TIntegral types
  //
  //---------------------------------------------------------------------------

  // set indentation
  //
  if (level_a > Integral::NONE) {
    Console::put(L"testing class-specific public methods: relational...\n");
    Console::increaseIndention();
  }

  // test operator == (equality)
  //
  c3 = c2;
  if (!(c3 == c2)) {
   return Error::handle(name(), L"operator<",
			Error::TEST, __FILE__, __LINE__);
  }
  
  // test operator !=
  //
  c3 = c0;
  if (c3 != c0) {
   return Error::handle(name(), L"operator<",
			Error::TEST, __FILE__, __LINE__);
  }
  
  // test operator <
  //
  if (c0 < c2) {
   return Error::handle(name(), L"operator<",
			Error::TEST, __FILE__, __LINE__);
  }
  
  // test operator >
  //
  if (!(c0 > c2)) {
   return Error::handle(name(), L"operator>",
			Error::TEST, __FILE__, __LINE__);
  }

  // test operator <=
  //
  if (c0 <= c2) {
    return Error::handle(name(), L"operator<=",
			 Error::TEST, __FILE__, __LINE__);
  }

  // test operator >=
  //
  if (!(c0 >= c2)) {
    return Error::handle(name(), L"operator>=",
			 Error::TEST, __FILE__, __LINE__);
  }
  
  // test operator ==
  //
  c3 = 5;
  if (!(c3 == 5)) {
   return Error::handle(name(), L"operator<",
			Error::TEST, __FILE__, __LINE__);
  }
  
  // test operator !=
  //
  c3 = 5;
  if (c3 != 5) {
   return Error::handle(name(), L"operator<",
			Error::TEST, __FILE__, __LINE__);
  }
  
  // test operator <
  //
  if (r1 < c2) {
    return Error::handle(name(), L"operator<",
			 Error::TEST, __FILE__, __LINE__);
  }
  
  // test operator >
  //
  if (!(r1 > c2)) {
    return Error::handle(name(), L"operator>",
			 Error::TEST, __FILE__, __LINE__);
  }
  
  // test operator <=
  //
  if (!(c0 <= r1)) {
    return Error::handle(name(), L"operator<=",
			 Error::TEST, __FILE__, __LINE__);
  }

  // test operator >=
  //
  if (!(r1 >= c2)) {
    return Error::handle(name(), L"operator>=",
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
  //  arithmetic functions with two complex arguments
  //
  //---------------------------------------------------------------------------

  // set indentation
  //
  if (level_a > Integral::NONE) {
    Console::put
      (L"testing class-specific public methods: two complex arguments...\n");
    Console::increaseIndention();
  }
  
  // test operator +
  //
  if (!Integral::almostEqual((c0 + c2), SysComplex<float32>(4, 5.3))) {
    return Error::handle(name(), L"operator +",
			 Error::TEST, __FILE__, __LINE__);
  }
  
  // test operator -
  //
  if (!Integral::almostEqual((c0 - c2) , SysComplex<float32>(4, -1.3))) {
    return Error::handle(name(), L"operator -",
			 Error::TEST, __FILE__, __LINE__);
  }

  // test operator *
  //
  if (!Integral::almostEqual((c0 * c2) , SysComplex<float32>(-6.6, 13.2))) {
    return Error::handle(name(), L"operator *",
			 Error::TEST, __FILE__, __LINE__);
  }
    
  // test operator /
  //
  if (!Integral::almostEqual(c0 / c2, SysComplex<float32>(0.6061, -1.2121))) {
    return Error::handle(name(), L"operator /",
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
  //  arithmetic functions with one complex and one real arg. since the
  //  complex arg is to the left this can be a member function.
  //
  //---------------------------------------------------------------------------

  // set indentation
  //
  if (level_a > Integral::NONE) {
    Console::put
      (L"testing class-specific public methods: complex to the left...\n");
    Console::increaseIndention();
  }
  
  // test operator +
  //
  if (!Integral::almostEqual((c0 + r1), SysComplex<float32>(9, 2))) {
    return Error::handle(name(), L"operator +=",
			 Error::TEST, __FILE__, __LINE__);
  }

  // test operator -
  //
  if (!Integral::almostEqual((c0 - r1) , SysComplex<float32>(-1, 2))) {
    return Error::handle(name(), L"operator -",
			 Error::TEST, __FILE__, __LINE__);
  }

  // test operator *
  //
  if (!Integral::almostEqual((c0 * r1) , SysComplex<float32>(20, 10))) {
    return Error::handle(name(), L"operator *",
			 Error::TEST, __FILE__, __LINE__);
  }
  
  // test operator /
  //
  if (!Integral::almostEqual((c0 / c1), SysComplex<float32>(0.8, 0.4))) {
    return Error::handle(name(), L"operator /",
			 Error::TEST, __FILE__, __LINE__);
  }
  
  // test inverse
  //
  if (!Integral::almostEqual(c0.inverse(), SysComplex<float32>(0.2, -0.1))) {
   return Error::handle(name(), L"almostEqual",
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
  //  miscellaneous complex methods
  //
  //--------------------------------------------------------------------------

  // set indentation
  //
  if (level_a > Integral::NONE) {
    Console::put(L"testing class-specific public methods: miscellaneous...\n");
    Console::increaseIndention();
  }
  
  // test conjugate
  //
  if (!Integral::almostEqual(c0.conjugate(), SysComplex<float32>(4, -2))) {
   return Error::handle(name(), L"almostEqual",
			 Error::TEST, __FILE__, __LINE__);
  }

  // test polar
  //
  if (!Integral::almostEqual(c0.polar(4.472, 0.436)
			       , SysComplex<float32>(4.05, 1.887))) {
   return Error::handle(name(), L"almostEqual",
			 Error::TEST, __FILE__, __LINE__);
  }
  
  // reset indentation
  //
  if (level_a > Integral::NONE) {
    Console::decreaseIndention();
  }
  
  //---------------------------------------------------------------------------
  //
  // class-specific *public methods*:
  //  arithmetic functions with one complex and one real arg. since the
  //  complex arg is to the right these cannot be member functions.
  //
  //---------------------------------------------------------------------------

  // set indentation
  //
  if (level_a > Integral::NONE) {
    Console::put
      (L"testing class-specific public methods: complex to the right...\n");
    Console::increaseIndention();
  }
  
  // test operator +
  //
  if (!Integral::almostEqual((r1 + c2), SysComplex<float32>(5, 3.3))) {
    return Error::handle(name(), L"operator +=",
			 Error::TEST, __FILE__, __LINE__);
  }

  // test operator -
  //
  if (!Integral::almostEqual((r1 - c2) , SysComplex<float32>(5, -3.3))) {
    return Error::handle(name(), L"operator -",
			 Error::TEST, __FILE__, __LINE__);
  }

  // test operator *
  //
  if (!Integral::almostEqual((r1 * c2) ,  SysComplex<float32>(0, 16.5))) {
    return Error::handle(name(), L"operator *",
			 Error::TEST, __FILE__, __LINE__);
  }
  
  // test operator /
  //
  if (!Integral::almostEqual(r1 / c2, SysComplex<float32>(0, -1.5152))) {
    return Error::handle(name(), L"operator /",
			 Error::TEST, __FILE__, __LINE__);
  }

  // test operator - (negation)
  //
  if (!Integral::almostEqual(-c2, SysComplex<float32>(0, -3.3))) {
    return Error::handle(name(), L"operator -",
			 Error::TEST, __FILE__, __LINE__);
  }
  
  // reset indentation
  //
  if (level_a > Integral::NONE) {
    Console::decreaseIndention();
  }

 //---------------------------------------------------------------------------
 //
 // class-specific *public methods*:
 //  relational functions with TIntegral and complex types. since the
 //  complex arg is to the right these cannot be member functions.
 //
 //---------------------------------------------------------------------------

 // set indentation
 //
  if (level_a > Integral::NONE) {
    Console::increaseIndention();
  }

  // test operator >
  //  
  if (!(r1 > c2)) {
    return Error::handle(name(), L"operator>",
			 Error::TEST, __FILE__, __LINE__);
  }
  
  // test operator <
  //
  if (r1 < c2) {
    return Error::handle(name(), L"operator<",
			 Error::TEST, __FILE__, __LINE__);
  }

  // test operator >=
  //
  if (!(r1 >= c2)) {
    return Error::handle(name(), L"operator>=",
			 Error::TEST, __FILE__, __LINE__);
  }  
  
  // test operator <=
  //
  if (r1 <= c2) {
    return Error::handle(name(), L"operator<=",
			 Error::TEST, __FILE__, __LINE__);
  }
  
  // reset indentation
  //
  if (level_a > Integral::NONE) {
    Console::decreaseIndention();
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
// return: a bool8 value indicating status
//
// this method performs diagnostics for the type "float64"
//
template<class TObject>
bool8 SysComplexDiagnose<TObject>::diagnose1(Integral::DEBUG level_a) {

  //----------------------------------------------------------------------
  //
  //  preliminaries
  //
  //----------------------------------------------------------------------
  
  // output the class name
  //
  if (level_a > Integral::NONE) {
    SysString output(L"diagnosing class ");
    output.concat(CLASS_NAME);
    output.concat(L" for the type float64: ");
    Console::put(output);
    Console::increaseIndention();
  }
  
  //---------------------------------------------------------------------
  //
  //  required public methods:
  //
  //---------------------------------------------------------------------

  // set indentation
  //
  if (level_a > Integral::NONE) {
   Console::put
     (L"testing class-specific public methods: required methods...\n"); 
   Console::increaseIndention();
  }
  
  // test constructor
  //
  const SysComplex<float64> c8(4.0, 2.0);
  const SysComplex<float64> c9(5);
  const SysComplex<float64> c10(0, 3.3);
  SysComplex<float64> t(9.9,11.0);
  float64 r1 = 5;
  
  // test copy constructor
  //
  SysComplex<float64> c11(c8);
  if (!Integral::almostEqual(c11, c8)) {
    return Error::handle(name(), L"copy constructor",
			 Error::TEST, __FILE__, __LINE__);
  }
  
  // test operator = (assignment)
  //
  c11 = c10;
  if (!Integral::almostEqual(c11, c10)) {
   return Error::handle(name(), L"operator =",
			 Error::TEST, __FILE__, __LINE__);
  }
  
  // reset indentation
  //
  if (level_a > Integral::NONE) {
    Console::decreaseIndention();
  }

  //---------------------------------------------------------------------
  //
  // class-specific public methods:other constructors, assignment,
  // casting, and component extraction methods
  //
  //---------------------------------------------------------------------

  // set indentation
  //
  if (level_a > Integral::NONE) {
    Console::put
      (L"testing class-specific public methods: assignment, casting...\n");
    Console::increaseIndention();
  }

  // test assign
  //
  c11.assign(5, 6);
  if (!Integral::almostEqual(c11, SysComplex<float64>(5, 6))) {
   return Error::handle(name(), L"assign",
			 Error::TEST, __FILE__, __LINE__);
  }
  
  // test operator = (assignment)
  //
  c11 = t;
  if (!Integral::almostEqual(c11, t)) {
   return Error::handle(name(), L"operator=",
			 Error::TEST, __FILE__, __LINE__);
  }

  // test cast operator
  //
  if (!Integral::almostEqual(SysComplex<int32>(c8) , SysComplex<int32>(4, 2))) { 
   return Error::handle(name(), L"cast operator",
			 Error::TEST, __FILE__, __LINE__);
  }
  
  // test real
  //
  if (!Integral::almostEqual(c11.real(), t.real())) {
   return Error::handle(name(), L"almostEqual",
			 Error::TEST, __FILE__, __LINE__);
  }
  
  // test imag
  //
  if (!Integral::almostEqual(c10.imag(), 3.3)) {
   return Error::handle(name(), L"almostEqual",
			 Error::TEST, __FILE__, __LINE__);
  }
  
  // test mag
  //
  if (!Integral::almostEqual(c8.mag(), 4.4721)) {
   return Error::handle(name(), L"almostEqual",
			 Error::TEST, __FILE__, __LINE__);
  }
  
  // test angle
  //
  if (!Integral::almostEqual(c8.angle(), 0.4636)) {
   return Error::handle(name(), L"almostEqual",
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
  //  accumulative arithmetic functions with SysComplex and TIntegral types
  //
  //---------------------------------------------------------------------------

  // set indentation
  //
  if (level_a > Integral::NONE) {
    Console::put(L"testing class-specific public methods: accumulative...\n");
    Console::increaseIndention();
  }

  // test operator +=
  //
  c11 = c10;
  c11 += c8;
  if (!Integral::almostEqual(c11 , SysComplex<float64>(4, 5.3))) {
   return Error::handle(name(), L"almostEqual",
			 Error::TEST, __FILE__, __LINE__);
  }

  // test operator -=
  //
  c11 = c10;
  c11 -= c8;
  if (!Integral::almostEqual(c11 , SysComplex<float64>(-4, 1.3))) {
   return Error::handle(name(), L"almostEqual",
			 Error::TEST, __FILE__, __LINE__);
  }

  // test operator *=
  //
  c11 = c10;
  c11 *= c8;
  if (!Integral::almostEqual(c11 , SysComplex<float64>(-6.6, 13.2))) {
   return Error::handle(name(), L"almostEqual",
			 Error::TEST, __FILE__, __LINE__);
  }

  // test operator /=
  //
  if (!Integral::almostEqual(c8 / c10, SysComplex<float64>(0.6061, -1.2121))) {
   return Error::handle(name(), L"operator /",
			Error::TEST, __FILE__, __LINE__);
  }
    
  // test operator +=
  //
  c11 = c10;
  c11 += 2;
  if (!Integral::almostEqual(c11 , SysComplex<float64>(2, 3.3))) {
   return Error::handle(name(), L"almostEqual",
			 Error::TEST, __FILE__, __LINE__);
  }
  
  // test operator -=
  //
  c11 = c10;
  c11 -= 2;
  if (!Integral::almostEqual(c11 , SysComplex<float64>(-2, 3.3))) {
   return Error::handle(name(), L"almostEqual",
			 Error::TEST, __FILE__, __LINE__);
  }

  // test operator *=
  //
  c11 = c10;
  c11 *= 2;
  if (!Integral::almostEqual(c11 , SysComplex<float64>(0, 6.6))) {
   return Error::handle(name(), L"almostEqual",
			 Error::TEST, __FILE__, __LINE__);
  }
  
  // test operator /=
  //
  c11 = c10;
  c11 /= 2;
  if (!Integral::almostEqual(c11 , SysComplex<float64>(0, 1.65))) {
   return Error::handle(name(), L"almostEqual",
			 Error::TEST, __FILE__, __LINE__);
  }

  // test operator ++ (post-increment)
  //
  c11 = c9;
  c11 = c11++;
  if (!Integral::almostEqual(c11, 5)) {
   return Error::handle(name(), L"almostEqual",
			 Error::TEST, __FILE__, __LINE__);
  }  
  
  // test operator -- (post-decrement)
  //
  c11 = c9;
  c11 = c11--; 
  if (!Integral::almostEqual(c11, 5)) {
   return Error::handle(name(), L"almostEqual",
			 Error::TEST, __FILE__, __LINE__);
  }
  
  // test operator ++ (pre-increment)
  //
  c11 = c9;
  c11 = ++c11; 
  if (!Integral::almostEqual(c11, 6)) {
   return Error::handle(name(), L"almostEqual",
			 Error::TEST, __FILE__, __LINE__);
  }
  
  // test operator -- (pre-decrement)
  //
  c11 = c9;
  c11 = --c11; 
  if (!Integral::almostEqual(c11, 4)) {
   return Error::handle(name(), L"almostEqual",
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
  //  relational functions with SysComplex and TIntegral types
  //
  //---------------------------------------------------------------------------

  // set indentation
  //
  if (level_a > Integral::NONE) {
    Console::put
     (L"testing class-specific public methods: relational...\n");
    Console::increaseIndention();
  }

  // test operator == (equality)
  //
  c11 = c10;
  if (!(c11 == c10)) {
   return Error::handle(name(), L"operator<",
			Error::TEST, __FILE__, __LINE__);
  }
  
  // test operator !=
  //
  c11 = c8;
  if (c11 != c8) {
   return Error::handle(name(), L"operator<",
			Error::TEST, __FILE__, __LINE__);
  }
  
  // test operator <
  //
  if (c8 < c10) {
   return Error::handle(name(), L"operator<",
			Error::TEST, __FILE__, __LINE__);
  }
  
  // test operator >
  //
  if (!(c8 > c10)) {
   return Error::handle(name(), L"operator>",
			Error::TEST, __FILE__, __LINE__);
  }

  // test operator <=
  //
  if (c8 <= c10) {
    return Error::handle(name(), L"operator<=",
			 Error::TEST, __FILE__, __LINE__);
  }

  // test operator >=
  //
  if (!(c8 >= c10)) {
    return Error::handle(name(), L"operator>=",
			 Error::TEST, __FILE__, __LINE__);
  }
  
  // test operator ==
  //
  c11 = 5;
  if (!(c11 == 5)) {
   return Error::handle(name(), L"operator<",
			Error::TEST, __FILE__, __LINE__);
  }
  
  // test operator !=
  //
  c11 = 5;
  if (c11 != 5) {
   return Error::handle(name(), L"operator<",
			Error::TEST, __FILE__, __LINE__);
  }
  
  // test operator <
  //
  if (r1 < c10) {
    return Error::handle(name(), L"operator<",
			 Error::TEST, __FILE__, __LINE__);
  }
  
  // test operator >
  //
  if (!(r1 > c10)) {
    return Error::handle(name(), L"operator>",
			 Error::TEST, __FILE__, __LINE__);
  }
  
  // test operator <=
  //
  if (!(c8 <= r1)) {
    return Error::handle(name(), L"operator<=",
			 Error::TEST, __FILE__, __LINE__);
  }

  // test operator >=
  //
  if (!(r1 >= c10)) {
    return Error::handle(name(), L"operator>=",
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
  //  arithmetic functions with two complex arguments
  //
  //---------------------------------------------------------------------------

  // set indentation
  //
  if (level_a > Integral::NONE) {
    Console::put
      (L"testing class-specific public methods: two complex arguments...\n");
    Console::increaseIndention();
  }
  
  // test operator +
  //
  if (!Integral::almostEqual((c8 + c10), SysComplex<float64>(4, 5.3))) {
    return Error::handle(name(), L"operator +",
			 Error::TEST, __FILE__, __LINE__);
  }
  
  // test operator -
  //
  if (!Integral::almostEqual((c8 - c10) , SysComplex<float64>(4, -1.3))) {
    return Error::handle(name(), L"operator -",
			 Error::TEST, __FILE__, __LINE__);
  }

  // test operator *
  //
  if (!Integral::almostEqual((c8 * c10) , SysComplex<float64>(-6.6, 13.2))) {
    return Error::handle(name(), L"operator *",
			 Error::TEST, __FILE__, __LINE__);
  }

  // test operator /
  //
  if (!Integral::almostEqual(c8 / c10, SysComplex<float64>(0.6061, -1.2121))) {
    return Error::handle(name(), L"operator /",
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
  //  arithmetic functions with one complex and one real arg. since the
  //  complex arg is to the left this can be a member function.
  //
  //---------------------------------------------------------------------------

  if (level_a > Integral::NONE) {
    Console::put
      (L"testing class-specific public methods: complex to the left...\n");
    Console::increaseIndention();
    Console::increaseIndention();
  }
  
  // test operator +
  //
  if (!Integral::almostEqual((c8 + r1), SysComplex<float64>(9, 2))) {
    return Error::handle(name(), L"operator +=",
			 Error::TEST, __FILE__, __LINE__);
  }

  // test operator -
  //
  if (!Integral::almostEqual((c8 - r1) , SysComplex<float64>(-1, 2))) {
    return Error::handle(name(), L"operator -",
			 Error::TEST, __FILE__, __LINE__);
  }

  // test operator *
  //
  if (!Integral::almostEqual((c8 * r1) , SysComplex<float64>(20, 10))) {
    return Error::handle(name(), L"operator *",
			 Error::TEST, __FILE__, __LINE__);
  }

  // test operator /
  //
  if (!Integral::almostEqual((c8 / c9), SysComplex<float64>(0.8, 0.4))) {
    return Error::handle(name(), L"operator /",
			 Error::TEST, __FILE__, __LINE__);
  }

  // test inverse
  //
  if (!Integral::almostEqual(c8.inverse(), SysComplex<float64>(0.2, -0.1))) {
   return Error::handle(name(), L"almostEqual",
			 Error::TEST, __FILE__, __LINE__);
  }
  
  // reset indentation
  //
  if (level_a > Integral::NONE) {
    Console::decreaseIndention();
    Console::decreaseIndention();
  }
 
  //---------------------------------------------------------------------------
  //
  // class-specific public methods:
  //  miscellaneous complex methods
  //
  //--------------------------------------------------------------------------

  // set indentation
  //
  if (level_a > Integral::NONE) {
    Console::put(L"testing class-specific public methods: miscellaneous...\n");
    Console::increaseIndention();
  }
  
  // test conjugate
  //
  if (!Integral::almostEqual(c8.conjugate(), SysComplex<float64>(4, -2))) {
   return Error::handle(name(), L"almostEqual",
			 Error::TEST, __FILE__, __LINE__);
  }

  // test polar
  //
  if (!Integral::almostEqual(c8.polar(4.472, 0.436)
			       , SysComplex<float64>(4.05, 1.887))) {
   return Error::handle(name(), L"almostEqual",
			 Error::TEST, __FILE__, __LINE__);
  }
    
  // reset indentation
  //
  if (level_a > Integral::NONE) {
    Console::decreaseIndention();
  }
  
  //---------------------------------------------------------------------------
  //
  // class-specific *public methods*:
  //  arithmetic functions with one complex and one real arg. since the
  //  complex arg is to the right these cannot be member functions.
  //
  //---------------------------------------------------------------------------

  // set indentation
  //
  if (level_a > Integral::NONE) {
    Console::put
      (L"testing class-specific public methods: complex to the right...\n");
    Console::increaseIndention();
  }

  // test operator +
  //
  if (!Integral::almostEqual(((float64)r1 + c10) ,
			     SysComplex<float64>(5, 3.3))) {
    return Error::handle(name(), L"operator +=",
			 Error::TEST, __FILE__, __LINE__);
  }

  // test operator -
  //
  if (!Integral::almostEqual(((float64)r1 - c10) ,
			     SysComplex<float64>(5, -3.3))) {
    return Error::handle(name(), L"operator -",
			 Error::TEST, __FILE__, __LINE__);
  } 

  // test operator *
  //
  if (!Integral::almostEqual(((float64)r1 * c10) ,
			     SysComplex<float64>(0, 16.5))) {
    return Error::handle(name(), L"operator *",
			 Error::TEST, __FILE__, __LINE__);
  }
    
  // test operator /
  //
  if (!Integral::almostEqual(((float64)r1 / c10) ,
			     SysComplex<float64>(0, -1.5152))) {
    return Error::handle(name(), L"operator /",
			 Error::TEST, __FILE__, __LINE__);
  }
   
  // test operator - (negation)
  //
  if (!Integral::almostEqual(-c10, SysComplex<float64>(0, -3.3))) {
    return Error::handle(name(), L"operator -",
			 Error::TEST, __FILE__, __LINE__);
  }

 //---------------------------------------------------------------------------
 //
 // class-specific *public methods*:
 //  relational functions with TIntegral and complex types. since the
 //  complex arg is to the right these cannot be member functions.
 //
 //---------------------------------------------------------------------------

 // set indentation
 //
  if (level_a > Integral::NONE) {
    Console::increaseIndention();
  }

  // test operator >
  //  
  if (!(r1 > c10)) {
    return Error::handle(name(), L"operator>",
			 Error::TEST, __FILE__, __LINE__);
  }
  
  // test operator <
  //
  if (r1 < c10) {
    return Error::handle(name(), L"operator<",
			 Error::TEST, __FILE__, __LINE__);
  }

  // test operator >=
  //
  if (!(r1 >= c10)) {
    return Error::handle(name(), L"operator>=",
			 Error::TEST, __FILE__, __LINE__);
  }  
  
  // test operator <=
  //
  if (r1 <= c10) {
    return Error::handle(name(), L"operator<=",
			 Error::TEST, __FILE__, __LINE__);
  }
  
  // reset indentation
  //
  if (level_a > Integral::NONE) {
    Console::decreaseIndention();
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
// return: a bool8 value indicating status
//
// this method performs diagnostics for the type "int32"
//
template<class TObject>
bool8 SysComplexDiagnose<TObject>::diagnose2(Integral::DEBUG level_a) {

  //----------------------------------------------------------------------
  //
  //  preliminaries
  //
  //----------------------------------------------------------------------

  // reset indentation
  //
  if (level_a > Integral::NONE) {
    Console::decreaseIndention();
  }
  
  // output the class name
  //
  if (level_a > Integral::NONE) {
    SysString output(L"diagnosing class ");
    output.concat(CLASS_NAME);
    output.concat(L" for the type int32: ");
    Console::put(output);
  }
  
  //---------------------------------------------------------------------
  //
  //  required public methods:
  //
  //---------------------------------------------------------------------

  // set indentation
  //
  if (level_a > Integral::NONE) {
    Console::increaseIndention(); 
    Console::put
      (L"testing class-specific public methods: required methods...\n");
    Console::increaseIndention();
  }

  // test constructor
  //
  const SysComplex<int32> c4(4, 2);
  const SysComplex<int32> c5(5);
  const SysComplex<int32> c6(0, 3);
  SysComplex<int32> t;
  int32 r1 = 5;

  // test copy constructor
  //
  SysComplex<int32> c7(c4);
  if (!Integral::almostEqual(c7, c4)) {
    return Error::handle(name(), L"copy constructor",
			 Error::TEST, __FILE__, __LINE__);
  }
  
  // test operator = (assignment)
  //
  c7 = c6;
  if (!Integral::almostEqual(c7, c6)) {
   return Error::handle(name(), L"operator=",
			 Error::TEST, __FILE__, __LINE__);
  }
  
  // reset indentation
  //
  if (level_a > Integral::NONE) {
    Console::decreaseIndention();
  }

  //---------------------------------------------------------------------
  //
  // class-specific public methods: other constructors, assignment,
  // casting, and component extraction methods
  //
  //---------------------------------------------------------------------

  // set indentation
  //
  if (level_a > Integral::NONE) {
    Console::put
      (L"testing class-specific public methods: assignment, casting...\n");
    Console::increaseIndention();
  }
  
  // test assign
  //
  c7.assign(5, 6);
  if (!Integral::almostEqual(c7, SysComplex<float32>(5, 6))) {
   return Error::handle(name(), L"assign",
			 Error::TEST, __FILE__, __LINE__);
  }
  
  // test operator = (assignment)
  //
  c7 = t;
  if (!Integral::almostEqual(c7, t)) {
   return Error::handle(name(), L"almostEqual",
			 Error::TEST, __FILE__, __LINE__);
  }

  // test cast operator
  //
  if (!Integral::almostEqual
      (SysComplex<float32>(c4) , SysComplex<float32>(4, 2))) { 
   return Error::handle(name(), L"almostEqual",
			 Error::TEST, __FILE__, __LINE__);
  }
  
  // test real
  //
  if (!Integral::almostEqual(c7.real(), (int32)t.real())) {
   return Error::handle(name(), L"almostEqual",
			 Error::TEST, __FILE__, __LINE__);
  }
  
  // test imag
  //
  if (!Integral::almostEqual(c6.imag(), (int32)3)) {
   return Error::handle(name(), L"almostEqual",
			 Error::TEST, __FILE__, __LINE__);
  }
  
  // test mag
  //
  if (!Integral::almostEqual((int32)c4.mag(), (int32)4.4721)) {
   return Error::handle(name(), L"almostEqual",
			 Error::TEST, __FILE__, __LINE__);
  }
  
  // test angle
  //
  if (!Integral::almostEqual((int32)c4.angle(), (int32)0)) {
   return Error::handle(name(), L"almostEqual",
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
  //  accumulative arithmetic functions with SysComplex and TIntegral types
  //
  //---------------------------------------------------------------------------

  // set indentation
  //
  if (level_a > Integral::NONE) {
    Console::put(L"testing class-specific public methods: accumulative...\n");
    Console::increaseIndention();
  }
  
  // test operator +=
  //
  c7 = c6;
  c7 += c4;
  if (!Integral::almostEqual(c7 , SysComplex<int32>(4, 5))) {
   return Error::handle(name(), L"almostEqual",
			 Error::TEST, __FILE__, __LINE__);
  }
  
  // test operator -=
  //
  c7 = c6;
  c7 -= c4;
  if (!Integral::almostEqual(c7 , SysComplex<int32>(-4, 1))) {
   return Error::handle(name(), L"almostEqual",
			 Error::TEST, __FILE__, __LINE__);
  }
  
  // test operator *=
  //
  c7 = c5;
  c7 *= c4;
  if (!Integral::almostEqual(c7 , SysComplex<int32>(20, 10))) {
   return Error::handle(name(), L"almostEqual",
			 Error::TEST, __FILE__, __LINE__);
  }

  // test operator /=
  //
  c7 = c5;
  c7 /= c4;
  if (!Integral::almostEqual(c7 , SysComplex<int32>(1, -0))) {
   return Error::handle(name(), L"almostEqual",
			 Error::TEST, __FILE__, __LINE__);
  }

  // test operator +=
  //
  c7 = c6;
  c7 += 2;
  if (!Integral::almostEqual(c7 , SysComplex<int32>(2, 3))) {
   return Error::handle(name(), L"almostEqual",
			 Error::TEST, __FILE__, __LINE__);
  }
  
  // test operator -=
  //  
  c7 = c6;
  c7 -= 2;
  if (!Integral::almostEqual(c7 , SysComplex<int32>(-2, 3))) {
   return Error::handle(name(), L"almostEqual",
			 Error::TEST, __FILE__, __LINE__);
  }
  
  // test operator *=
  //
  c7 = c6;
  c7 *= 2;
  if (!Integral::almostEqual(c7 , SysComplex<int32>(0, 6))) {
   return Error::handle(name(), L"almostEqual",
			 Error::TEST, __FILE__, __LINE__);
  }
  
  // test operator /=
  //  
  c7 = c6;
  c7 /= 2;
  if (!Integral::almostEqual(c7 , SysComplex<int32>(0, 1))) {
   return Error::handle(name(), L"almostEqual",
			 Error::TEST, __FILE__, __LINE__);
  }

  // test operator ++ (post-increment)
  //
  c7 = 4;
  c7 = c7++;
  if (c7 == 5) {
   return Error::handle(name(), L"almostEqual",
			 Error::TEST, __FILE__, __LINE__);
  }  
  
  // test operator -- (post-decrement)
  //
  c7 = 4;
  c7 = c7--; 
  if (c7 == 3) {
   return Error::handle(name(), L"almostEqual",
			 Error::TEST, __FILE__, __LINE__);
  }
  
  // test operator ++ (pre-increment)
  //
  c7 = 5;
  c7 = ++c7; 
  if (c7 == 5) {
   return Error::handle(name(), L"almostEqual",
			 Error::TEST, __FILE__, __LINE__);
  }
  
  // test operator -- (pre-decrement)
  //
  c7 = 5;
  c7 = --c7; 
  if (c7 == 5) {
   return Error::handle(name(), L"almostEqual",
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
  //  relational functions with SysComplex and TIntegral types
  //
  //---------------------------------------------------------------------------

  // set indentation
  //
  if (level_a > Integral::NONE) {
   Console::put
    (L"testing class-specific public methods: relational...\n");
    Console::increaseIndention();
  }

  // test operator == (equality)
  //
  c7 = c6;
  if (!(c7 == c6)) {
   return Error::handle(name(), L"operator<",
			Error::TEST, __FILE__, __LINE__);
  }
  
  // test operator !=
  //
  c7 = c4;
  if (c7 != c4) {
   return Error::handle(name(), L"operator<",
			Error::TEST, __FILE__, __LINE__);
  }
  
  // test operator <
  //
  if (c4 < c6) {
   return Error::handle(name(), L"operator<",
			Error::TEST, __FILE__, __LINE__);
  }
  
  // test operator >
  //
  if (!(c4 > c6)) {
   return Error::handle(name(), L"operator>",
			Error::TEST, __FILE__, __LINE__);
  }

  // test operator <=
  //
  if (c4 <= c6) {
    return Error::handle(name(), L"operator<=",
			 Error::TEST, __FILE__, __LINE__);
  }

  // test operator >=
  //
  if (!(c4 >= c6)) {
    return Error::handle(name(), L"operator>=",
			 Error::TEST, __FILE__, __LINE__);
  }
  
  // test operator ==
  //
  c7 = 5;
  if (!(c7 == 5)) {
   return Error::handle(name(), L"operator<",
			Error::TEST, __FILE__, __LINE__);
  }
  
  // test operator !=
  //
  c7 = 5;
  if (c7 != 5) {
   return Error::handle(name(), L"operator<",
			Error::TEST, __FILE__, __LINE__);
  }
  
  // test operator <
  //
  if (r1 < c6) {
    return Error::handle(name(), L"operator<",
			 Error::TEST, __FILE__, __LINE__);
  }
  
  // test operator >
  //
  if (!(r1 > c6)) {
    return Error::handle(name(), L"operator>",
			 Error::TEST, __FILE__, __LINE__);
  }
  
  // test operator <=
  //
  if (!(c4 <= r1)) {
    return Error::handle(name(), L"operator<=",
			 Error::TEST, __FILE__, __LINE__);
  }

  // test operator >=
  //
  if (!(r1 >= c6)) {
    return Error::handle(name(), L"operator>=",
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
  //  arithmetic functions with two complex arguments
  //
  //---------------------------------------------------------------------------

  // set indentation
  //
  if (level_a > Integral::NONE) {
    Console::put
      (L"testing class-specific public methods: two complex arguments...\n");
    Console::increaseIndention();
  }
  
  // test operator +
  //
  if (!Integral::almostEqual((c4 + c6), SysComplex<int32>(4, 5))) {
    return Error::handle(name(), L"operator +",
			 Error::TEST, __FILE__, __LINE__);
  }
  
  // test operator -
  //
  if (!Integral::almostEqual((c4 - c6), SysComplex<int32>(4, -1))) {
    return Error::handle(name(), L"operator +",
			 Error::TEST, __FILE__, __LINE__);
  }
  
  // test operator *
  //
  if (!Integral::almostEqual((c4 * c5), SysComplex<int32>(20, 10))) {
    return Error::handle(name(), L"operator +",
			 Error::TEST, __FILE__, __LINE__);
  }
  
  // test operator /
  //
  if (!Integral::almostEqual((c4 / c6), SysComplex<int32>(0, -1))) {
    return Error::handle(name(), L"operator +",
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
  //  arithmetic functions with one complex and one real arg. since the
  //  complex arg is to the left this can be a member function.
  //
  //---------------------------------------------------------------------------

  // set indentation
  //
  if (level_a > Integral::NONE) {
    Console::put
      (L"testing class-specific public methods: complex to the left...\n");
    Console::increaseIndention();
  }
  
  // test operator +
  //
  if (!Integral::almostEqual((c4 + r1), SysComplex<int32>(9, 2))) {
    return Error::handle(name(), L"operator +",
			 Error::TEST, __FILE__, __LINE__);
  }

  // test operator -
  //
  if (!Integral::almostEqual((c6 - r1), SysComplex<int32>(-5, 3))) {
    return Error::handle(name(), L"operator -",
			 Error::TEST, __FILE__, __LINE__);
  }
 
  // test operator *
  //

  if (!Integral::almostEqual((c4 * r1), SysComplex<int32>(20, 10))) {
    return Error::handle(name(), L"operator *",
			 Error::TEST, __FILE__, __LINE__);
  }
  
  // test operator /
  if (!Integral::almostEqual((c4 / r1), SysComplex<int32>(0, 0))) {
    return Error::handle(name(), L"operator /",
			 Error::TEST, __FILE__, __LINE__);
  }
  
  // test inverse
  //
  if (!Integral::almostEqual(c4.inverse(), SysComplex<int32>(0, 0))) {
   return Error::handle(name(), L"almostEqual",
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
  //  miscellaneous complex methods
  //
  //--------------------------------------------------------------------------

  // set indentation
  //
  if (level_a > Integral::NONE) {
    Console::put(L"testing class-specific public methods: miscellaneous...\n");
    Console::increaseIndention();
  }
  
  // test conjugate
  //
  if (!Integral::almostEqual(c4.conjugate(), SysComplex<int32>(4, -2))) {
   return Error::handle(name(), L"almostEqual",
			 Error::TEST, __FILE__, __LINE__);
  }

  // test polar
  //
  if (!Integral::almostEqual(c4.polar(4, 0), SysComplex<int32>(4, 0))) {
   return Error::handle(name(), L"almostEqual",
			 Error::TEST, __FILE__, __LINE__);
  }
  
  // reset indentation
  //
  if (level_a > Integral::NONE) {
    Console::decreaseIndention();
  }
  
  //---------------------------------------------------------------------------
  //
  // class-specific *public methods*:
  //  arithmetic functions with one complex and one real arg. since the
  //  complex arg is to the right these cannot be member functions.
  //
  //---------------------------------------------------------------------------

  // set indentation
  //
  if (level_a > Integral::NONE) {
    Console::put
      (L"testing class-specific public methods: complex to the right...\n");
    Console::increaseIndention();
  }

  // test operator +
  //   

  if (!Integral::almostEqual(((int32)5 + c6), SysComplex<int32>(5, 3))) {
    return Error::handle(name(), L"operator +",
			 Error::TEST, __FILE__, __LINE__);
  }
  
  // test operator -
  //
  if (!Integral::almostEqual(((int32)r1 - c6) , SysComplex<int32>(5, -3))) {
    return Error::handle(name(), L"operator -",
			 Error::TEST, __FILE__, __LINE__);
  }
  
  // test operator *
  //
  if (!Integral::almostEqual(((int32)r1 * c4) ,  SysComplex<int32>(20, 10))) {
    return Error::handle(name(), L"operator *",
			 Error::TEST, __FILE__, __LINE__);
  }
  
  // test operator /
  //  
  if (!Integral::almostEqual(((int32)r1 / c6), SysComplex<int32>(0, -1))) {
    return Error::handle(name(), L"operator /",
			 Error::TEST, __FILE__, __LINE__);
  }
  
  // test operator - (negation)
  //
  if (!Integral::almostEqual(-c6, SysComplex<int32>(0, -3))) {
    return Error::handle(name(), L"operator -",
			 Error::TEST, __FILE__, __LINE__);
  }
  
  // reset indentation
  //
  if (level_a > Integral::NONE) {
    Console::decreaseIndention();
  }
  
 //---------------------------------------------------------------------------
 //
 // class-specific *public methods*:
 //  relational functions with TIntegral and complex types. since the
 //  complex arg is to the right these cannot be member functions.
 //
 //---------------------------------------------------------------------------

  // set indentation
  //
  if (level_a > Integral::NONE) {
    Console::increaseIndention();
  }


  // test operator >
  //  
  if (!(r1 > c6)) {
    return Error::handle(name(), L"operator>",
			 Error::TEST, __FILE__, __LINE__);
  }
  
  // test operator <
  //
  if (r1 < c6) {
    return Error::handle(name(), L"operator<",
			 Error::TEST, __FILE__, __LINE__);
  }

  // test operator >=
  //
  if (!(r1 >= c6)) {
    return Error::handle(name(), L"operator>=",
			 Error::TEST, __FILE__, __LINE__);
  }  
  
  // test operator <=
  //
  if (r1 <= c6) {
    return Error::handle(name(), L"operator<=",
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

// end of include file
//
#endif

