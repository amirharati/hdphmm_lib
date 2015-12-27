// file: $isip/class/math/scalar/MScalar/MScalar.h
// version: $Id: MScalar.h 10675 2009-07-21 01:13:30Z tm334 $
//
// note:
// 1- AH (07/28/2010) : I add :mod", "%" and "%=" definitions ;
//                      They probably need change for 128 bit system

// make sure definitions are only made once
//
#ifndef ISIP_MSCALAR
#define ISIP_MSCALAR

#include <typeinfo>

// isip include files
//
#ifndef ISIP_MSCALAR_METHODS
#include "MScalarMethods.h"
#endif

#ifndef ISIP_STRING
#include <String.h>
#endif

#ifndef ISIP_RANDOM
#include <Random.h>
#endif

// MScalar: the scalar template class is inherited by other
// scalar classes. TIntegral is an Integral type, TSize is a size
// specific data type.  most of the methods in this class are inline
// wrappers to the MScalarMethods class functions. this is done to
// allow us to write one method per file, thus avoiding the compilation
// overhead inherent in compiling template classes with multiple
// explicit instantiations.
//
template<class TIntegral, class TSize>
class MScalar {

  //---------------------------------------------------------------------------
  //
  // public constants
  //
  //---------------------------------------------------------------------------
public:

  // define the class name
  //
  static const String CLASS_NAME;

  //----------------------------------------
  //
  // other important constants
  //
  //----------------------------------------
  
  // random number related constants
  //
  static const float64 RAND_BYTE_MAX = ((uint32)1 << 8);
  static const float64 RAND_USHORT_MAX = ((uint32)1 << 16);
  static const float64 RAND_ULONG_MAX = ((uint64)1 << 32);
  static const float64 RAND_ULLONG_MAX = ((uint64)1 << 63) * 2.0;
  static const float64 RAND_SHORT_MAX = ((uint32)1 << 15);
  static const float64 RAND_LONG_MAX = ((uint32)1 << 31);
  static const float64 RAND_LLONG_MAX = ((uint64)1 << 63);///*

  // i/o related constants
  //
  static const String DEF_PARAM;
  
  //----------------------------------------
  //
  // default values and arguments
  //
  //----------------------------------------
  
  // define the default value(s) of the class data
  //
  static const TIntegral DEF_VALUE;

  //----------------------------------------
  //
  // error codes
  //
  //----------------------------------------  
  
  static const int32 ERR = 20000;

  //---------------------------------------------------------------------------
  //
  // protected data
  //
  //---------------------------------------------------------------------------
protected:

  // the container for the value of this item
  //
  TIntegral value_d;

  // declare a static debug level for all class instantiations:
  // we don't want every object to waste space on a debug level. let
  //  them share this across all classes.
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
  static const String& name() {
    return CLASS_NAME;
  }
  
  // method: diagnose
  //
  static bool8 diagnose(Integral::DEBUG debug_level) {
    return MScalarMethods::
      diagnose<MScalar<TIntegral, TSize>, TIntegral>(debug_level);
  }
 
  // method: setDebug
  //
  static bool8 setDebug(Integral::DEBUG level) {
    debug_level_d = level;
    return true;
  }

  // other debug methods
  //
  bool8 debug(const unichar* msg) const;
  
  // method: destructor
  //
  ~MScalar() {}
 
  // method: default constructor
  //
  MScalar() {}

  // method: copy constructor
  //
  MScalar(const MScalar& arg) {
    assign(arg);
  }

  // method: assign
  //
  bool8 assign(const MScalar& arg) {
    value_d = (TIntegral)arg;
    return true;
  }

  // method operator=
  //  we need to have the overloaded operator '=' defined in the
  //  derived classes instead of the base template class. this is
  //  required since c++ predefines the operator '=' for any class by
  //  default and this hides any other definition of this operator in
  //  the base class.
  //

  // method: sofSize
  //
  int32 sofSize() const {
    return (int32)sizeof(TSize);
  }
  
  // method: read
  //
  bool8 read(Sof& sof, int32 tag, const String& name = CLASS_NAME) {
    return MScalarMethods::read(*this, sof, tag, name);
  }
  
  // method: write
  //
  bool8 write(Sof& sof, int32 tag, const String& name = CLASS_NAME) const {
    return MScalarMethods::write(*this, sof, tag, name);
  }

  // method: readData
  //
  bool8 readData(Sof& sof, const String& pname = DEF_PARAM,
			  int32 size = SofParser::FULL_OBJECT,
			  bool8 param = true, bool8 nested = false) {
    return MScalarMethods::readData(*this, sof, pname, size, param, nested);
  }

  // method: writeData
  //
  bool8 writeData(Sof& sof, const String& pname = DEF_PARAM) const {
    return MScalarMethods::writeData(*this, sof, pname);
  }
  
  // method: eq
  //
  bool8 eq(const MScalar& arg_a) const {
    return (value_d == arg_a.value_d);
  }

  // memory management methods:
  //  new and delete methods are omitted because they are defined in the
  //  classes that instantiate this template
  //

  // method: clear
  //
  bool8 clear(Integral::CMODE ctype = Integral::DEF_CMODE) {
    value_d = (TIntegral)DEF_VALUE;
    return true;
  }
  
  //---------------------------------------------------------------------------
  //
  // class-specific public methods:
  //  extensions to required methods
  //
  //---------------------------------------------------------------------------

  // method: constructor
  //  note that this method is useful to have for the diagnose method.
  //  it is masked by higher-level classes that use this as a template
  //  and have their own version of this constructor.
  //
  MScalar(TIntegral arg) {
    assign(arg);
  }

  // method: assign
  //
  template<class TAIntegral>
  bool8 assign(TAIntegral arg) {
    value_d = (TIntegral)arg;
    return true;
  }

  // method: assign
  //
  bool8 assign(const String& arg) {
    arg.get(value_d);
    return true;
  }
  
  // method: get
  //
  bool8 get(String& arg) const {
    return arg.assign(value_d);
  }

  // method: memSize
  //
  int32 memSize() const {
    return (int32)sizeof(value_d);
  }

  // method: presentValue
  //  define functions which are used to wrap member functions that have
  //  different implementations for different data types, and return the
  //  correct value by using template specialization.
  //
  TIntegral presentValue(float64 arg) const {
    if ((typeid(TIntegral) == typeid(float32)) ||
	(typeid(TIntegral) == typeid(float64))) {
      return (TIntegral)arg;
    }
    else {
      return (TIntegral)Integral::round(arg);
    }
  }

  complexdouble presentValue(complexdouble arg) const {
    if ((typeid(TSize) == typeid(float32)) ||
        (typeid(TSize) == typeid(float64))) {
	return (complexdouble)arg;
    }
    else {
      return (complexdouble)Integral::round(arg);
    }
  }

  // method: almostEqual
  //
  bool8 almostEqual(TIntegral arg) const {
    return Integral::almostEqual(value_d, arg);
  }

  // method: almostEqual
  //  
  bool8 almostEqual(TIntegral arg, float64 percent,
		      float64 bound = Integral::DEF_BOUND) const {
    return Integral::almostEqual(value_d, arg, percent, bound);
  }

  //---------------------------------------------------------------------------
  //
  // class-specific public methods:
  //  operator overloads
  //
  //---------------------------------------------------------------------------

  // method: operator TIntegral()
  //
  operator TIntegral() const {
    return value_d;
  }

  // method: operator +
  //
  TIntegral operator+ (TIntegral arg) const {
    return value_d + arg;
  }

  // method: operator -
  //
  TIntegral operator- (TIntegral arg) const {
    return value_d - arg;
  }

  // method: operator *
  //
  TIntegral operator* (TIntegral arg) const {
    return value_d * arg;
  }

  // method: operator /
  //
  TIntegral operator/ (TIntegral arg) const {
    return value_d / arg;
  }

  // method: operator %
  //
/*    
   TIntegral operator% (TIntegral arg) const { 
      // return value_d % arg; 
      //Amir;
       int64 temp=(int64)value_d/(int64)arg;
       return value_d-temp*arg;
       
   } 
*/
  // method: operator ++
  //
  TIntegral operator++ () {
    return ++value_d;
  }

  // method: operator --
  //
  TIntegral operator-- () {
    return --value_d;
  }
  
  // method: operator ++
  //
  TIntegral operator++ (int) {
    return value_d++;
  }
  
  // method: operator --
  //
  TIntegral operator-- (int) {
    return value_d--;
  }

  // method: operator +=
  //
  MScalar& operator+= (TIntegral arg) {
    value_d += arg;
    return *this;
  }

  // method: operator -=
  //
  MScalar& operator-= (TIntegral arg) {
    value_d -= arg;
    return *this;
  }

  // method: operator *=
  //
  MScalar& operator*= (TIntegral arg) {
    value_d *= arg;
    return *this;
  }

  // method: operator /=
  //
  MScalar& operator /= (TIntegral arg) {
    value_d /= arg;
    return *this;
  }
/*
  // method: operator %=
  //
  MScalar& operator %= (TIntegral arg) {
      //  value_d %= arg;
      //return *this;
      //change by amir 
      int64 temp=(int64)value_d/(int64)arg;
      value_d= value_d-temp*arg;
      return *this;
      
  }
*/
  // method: operator ==
  //
  bool8 operator == (TIntegral arg) const {
    return eq(arg);
  }

  // method: operator !=
  //
  bool8 operator != (TIntegral arg) const {
    return ne(arg);
  }

  // method: operator <
  //
  bool8 operator < (TIntegral arg) const {
    return lt(arg);
  }

  // method: operator <=
  //
  bool8 operator <= (TIntegral arg) const {
    return le(arg);
  }

  // method: operator >
  //
  bool8 operator > (TIntegral arg) const {
    return gt(arg);
  }

  // method: operator >=
  //
  bool8 operator >= (TIntegral arg) const {
    return ge(arg);
  }

  //---------------------------------------------------------------------------
  //
  // class-specific public methods:
  //  equality and comparison methods
  //
  //---------------------------------------------------------------------------

  // method: eq
  //
  bool8 eq(TIntegral arg) const {
    return (value_d == arg);
  }

  // method: eq
  //
  bool8 eq(TIntegral arg1, TIntegral arg2) const {
    return (arg1 == arg2);
  }

  // method: ne
  //
  bool8 ne(TIntegral arg) const {
    return (value_d != arg);
  }
  
  // method: lt
  //
  bool8 lt(TIntegral arg) const {
    return (value_d < arg);
  }

  // method: le
  //
  bool8 le(TIntegral arg) const {
    return (value_d <= arg);
  }

  // method: gt
  //
  bool8 gt(TIntegral arg) const {
    return (value_d > arg);
  }

  // method: ge
  //
  bool8 ge(TIntegral arg) const {
    return (value_d >= arg);
  }
  
  //---------------------------------------------------------------------------
  //
  // class-specific public methods:
  //  basic mathematical methods
  //
  //---------------------------------------------------------------------------

  // method: add
  //
  TIntegral add(TIntegral arg2) {
    return add(value_d, arg2);
  }

  // method: add
  //
  TIntegral add(TIntegral arg1, TIntegral arg2) {
    return (value_d = arg1 + arg2);
  }

  // method: sub
  //
  TIntegral sub(TIntegral arg2) {
    return sub(value_d, arg2);
  }

  // method: sub
  //
  TIntegral sub(TIntegral arg1, TIntegral arg2) {
    return (value_d = arg1 - arg2);
  }

  // method: mult
  //
  TIntegral mult(TIntegral arg2) {
    return mult(value_d, arg2);
  }

  // method: mult
  //
  TIntegral mult(TIntegral arg1, TIntegral arg2) {
    return (value_d = arg1 * arg2);
  }

  // method: div
  //
  TIntegral div(TIntegral arg2) {
    return div(value_d, arg2);
  }

  // method: div
  //
  TIntegral div(TIntegral arg1, TIntegral arg2) {
    return (value_d = arg1 / arg2);
  }
/*
   // method: mod 
   // 
   TIntegral mod(TIntegral arg2) { 
     return mod(value_d, arg2); 
   } 

   // method: mod 
    // 
   TIntegral mod(TIntegral arg1, TIntegral arg2) { 
     return (value_d = arg1 % arg2); 
   } 
 */
    
  //---------------------------------------------------------------------------
  //
  // class-specific public methods:
  //  other mathematical methods (listed alphabetically)
  //
  //--------------------------------------------------------------------------

  // method: abs
  //
  TIntegral abs() {
    return abs(value_d);
  }

  // method: abs
  //
  TIntegral abs(TIntegral arg) {
    if (arg > (TIntegral)0) {
      value_d = arg;
    }
    else {
      value_d = -arg;
    }
    return value_d;
  }
 
  // method: acos
  //
  TIntegral acos() {
    return acos(value_d);
  }

  // method: acos
  //
  TIntegral acos(TIntegral arg) {
    return (value_d = (TIntegral)Integral::acos(arg));
  }

  // method: acosh
  //
  TIntegral acosh() {
    return acosh(value_d);
  }

  // method: acosh
  //
  TIntegral acosh(TIntegral arg) {
    return (value_d = (TIntegral)Integral::acosh(arg));
  }

  // method: asin
  //
  TIntegral asin() {
    return asin(value_d);
  }

  // method: asin
  //
  TIntegral asin(TIntegral arg) {
    return (value_d = (TIntegral)Integral::asin(arg));
  }

  // method: asinh
  //
  TIntegral asinh() {
    return asinh(value_d);
  }

  // method: asinh
  //
  TIntegral asinh(TIntegral arg) {
    return (value_d = (TIntegral)Integral::asinh(arg));
  }

  // method: atan
  //
  TIntegral atan() {
    return atan(value_d);
  }

  // method: atan
  //
  TIntegral atan(TIntegral arg) {
    return (value_d = (TIntegral)Integral::atan(arg));
  }

  // method: atanh
  //
  TIntegral atanh() {
    return atanh(value_d);
  }

  // method: atanh
  //
  TIntegral atanh(TIntegral arg) {
    return (value_d = (TIntegral)Integral::atanh(arg));
  }

  // method: ceil
  //
  TIntegral ceil() {
    return ceil(value_d);
  }

  // method: ceil
  //
  template <class TAIntegral>
  TIntegral ceil(TAIntegral arg) {
    return (value_d = (TIntegral)Integral::ceil(arg));
  }

  // method: centerClip
  //
  TIntegral centerClip(TIntegral min, TIntegral max) {
    return MScalarMethods::centerClip(*this, min, max, value_d);
  }

  // method: centerClip
  //
  TIntegral centerClip(TIntegral min, TIntegral max, TIntegral val) {
    return MScalarMethods::centerClip(*this, min, max, val);
  }
  
  // method: cos
  //
  TIntegral cos() {
    return cos(value_d);
  }
  
  // method: cos
  //
  TIntegral cos(TIntegral arg) {
    return (value_d = (TIntegral)Integral::cos(arg));
  }

  // method: cosh
  //
  TIntegral cosh() {
    return cosh(value_d);
  }
  
  // method: cosh
  //
  TIntegral cosh(TIntegral arg) {
    return (value_d = (TIntegral)Integral::cosh(arg));
  }

  // method: exp
  //
  TIntegral exp() {
    return exp(value_d);
  }

  // method: exp
  //
  TIntegral exp(TIntegral arg) {
    return (value_d = presentValue(Integral::exp(arg)));
  }

  // method: exp2
  //
  TIntegral exp2() {
    return exp2(value_d);
  }

  // method: exp2
  //
  TIntegral exp2(TIntegral arg) {
    return (value_d = presentValue(Integral::exp2(arg)));
  }

  // method: exp10
  //
  TIntegral exp10() {
    return exp10(value_d);
  }

  // method: exp10
  //
  TIntegral exp10(TIntegral arg) {
    return (value_d =  presentValue(Integral::exp10(arg)));
  }
  
  // method: factorial
  //
  TIntegral factorial() {
    return factorial(value_d);
  }
  
  // method: factorial
  //
  TIntegral factorial(TIntegral arg) {
    value_d = 1;    
    for (TIntegral count = 2; count <= arg; count++) {
      value_d *= count;
    }
    return value_d;
  }

  // method: floor
  //
  TIntegral floor() {
    return floor(value_d);
  }

  // method: floor
  //
  template <class TAIntegral>
  TIntegral floor(TAIntegral arg) {
    return (value_d = (TIntegral)Integral::floor(arg));
  }

  // method: fraction
  //
  TIntegral fraction() {
    return fraction(value_d);
  }
  
  // method: fraction
  //
  TIntegral fraction(TIntegral arg) {
    return (value_d = (TIntegral)0);
  }
  
  // gaussian random number generation methods
  //
  TIntegral grand(TIntegral mean, TIntegral stddev,
		  Random& generator = Random::GLOBAL_GAUSSIAN);

  // method: hash
  //
  uint32 hash(uint32 hsize) const{
    // Integral::hash() will give wrong result for the first time invoked with -O2 open
    //
    Integral::hash(value_d, hsize);
    return Integral::hash(value_d, hsize);
  }  
  
  // method: inverse
  //
  TIntegral inverse() {
    return inverse(value_d);
  }
  
  // method: inverse
  //
  TIntegral inverse(TIntegral arg) {
    value_d = 1;
    return (value_d /= arg);
  }

  // method: limit
  //
  TIntegral limit(TIntegral min, TIntegral max) {
    return MScalarMethods::limit(*this, min, max, value_d);
  }
  
  // method: limit
  //
  TIntegral limit(TIntegral min, TIntegral max, TIntegral val) {
    return MScalarMethods::limit(*this, min, max, val);
  }
  
  // method: limitMag
  //
  TIntegral limitMag(TIntegral thresh, TIntegral output) {
    return MScalarMethods::limitMag(*this, thresh, output, value_d);
  }
  
  // method: limitMag
  //
  TIntegral limitMag(TIntegral thresh, TIntegral output, TIntegral val) {
    return MScalarMethods::limitMag(*this, thresh, output, val);
  }

  // method: log
  //
  TIntegral log() {
    return log(value_d);
  }
  
  // method: log
  //
  TIntegral log(TIntegral arg) {

    value_d = presentValue(Integral::log(arg));
    return value_d;
  }

  // method: log2
  //
  TIntegral log2() {
    return log2(value_d);
  }

  // method: log2
  //
  TIntegral log2(TIntegral arg) {
    return (value_d = presentValue(Integral::log2(arg)));
  }
  
  // method: log10
  //
  TIntegral log10() {
    return log10(value_d);
  }
  
  // method: log10
  //
  TIntegral log10(TIntegral arg) {
    return (value_d = presentValue(Integral::log10(arg)));
  }
   
  // method: log1p
  //
  TIntegral log1p() {
    return log1p(value_d);
  }
   
  // method: log1p
  //
  TIntegral log1p(TIntegral arg) {
    return (value_d = presentValue(Integral::log1p(arg)));
  }
   
  // method: max
  //
  TIntegral max(TIntegral arg) {
    return max(value_d, arg);
  }
 
  // method: max
  //
  TIntegral max(TIntegral arg_1, TIntegral arg_2) {
    if (arg_1 > arg_2) {
      return (value_d = arg_1);
    }
    return (value_d = arg_2);
  }
  
  // method: min
  //
  TIntegral min(TIntegral arg) {
    return min(value_d, arg);
  }
  
  // method: min
  //
  TIntegral min(TIntegral arg_1, TIntegral arg_2) {
    if (arg_1 > arg_2) {
      return (value_d = arg_2);
    }
    else {
      return (value_d = arg_1);    
    }
  }

  // method: neg
  //
  TIntegral neg() {
    return neg(value_d);
  }
  
  // method: neg
  //
  TIntegral neg(TIntegral arg) {
    return (value_d = -arg);
  }

  // method: pow
  //
  TIntegral pow(TIntegral exponent) {
    return pow(value_d, exponent);
  }
  
  // method: pow
  //
  TIntegral pow(TIntegral arg, TIntegral exponent) {
    return (value_d = presentValue(Integral::pow(arg, exponent)));
  }

  // random number generation methods
  //
  TIntegral rand(Random& generator = Random::GLOBAL_UNIFORM);
  TIntegral rand(TIntegral min, TIntegral max,
		 Random& generator = Random::GLOBAL_UNIFORM);
  
  // method: rceil
  //
  TIntegral rceil() {
    return rceil(value_d);
  }

  // method: rceil
  //
  TIntegral rceil(TIntegral arg) {
    return (value_d = (TIntegral)(Integral::ceil(arg) - arg));
  }

  // method: rfloor
  //
  TIntegral rfloor() {
    return rfloor(value_d);
  }

  // method: rfloor
  //
  TIntegral rfloor(TIntegral arg) {
    return (value_d = (TIntegral)(Integral::floor(arg) - arg));
  }

  // method: round
  //
  TIntegral round() {
    return round(value_d);
  }

  // method: round
  //
  template <class TAIntegral>
  TIntegral round(TAIntegral arg) {
    return (value_d = (TIntegral)Integral::round(arg));
  }

  // method: sign
  //
  TIntegral sign() {
    return sign(value_d);
  }
  
  // method: sign
  //
  TIntegral sign(TIntegral arg) {
    if (arg < (TIntegral)0.0) {
      return (value_d = (TIntegral)Integral::NEGATIVE);
    }
    return (value_d = (TIntegral)Integral::POSITIVE);    
  }
  
  // method: sin
  //
  TIntegral sin() {
    return sin(value_d);
  }

  // method: sin
  //
  TIntegral sin(TIntegral arg) {
    return (value_d = (TIntegral)Integral::sin(arg));
  }

  // method: sinh
  //
  TIntegral sinh() {
    return sinh(value_d);
  }

  // method: sinh
  //
  TIntegral sinh(TIntegral arg) {
    return (value_d = (TIntegral)Integral::sinh(arg));
  }

  // method: sqrt
  //
  TIntegral sqrt() {
    return sqrt(value_d);
  }
   
  // method: sqrt
  //
  TIntegral sqrt(TIntegral arg) {
    return (value_d = presentValue(Integral::sqrt(arg)));
  }

  // method: square
  //
  TIntegral square() {
    return (value_d * value_d);
  }
   
  // method: square
  //
  TIntegral square(TIntegral arg) {
    return (value_d = arg * arg);
  }

  // method: tan
  //
  TIntegral tan() {
    return tan(value_d);
  }

  // method: tan
  //
  TIntegral tan(TIntegral arg) {
    return (value_d = (TIntegral)Integral::tan(arg));
  }

  // method: tanh
  //
  TIntegral tanh() {
    return tanh(value_d);
  }

  // method: tanh
  //
  TIntegral tanh(TIntegral arg) {
    return (value_d = (TIntegral)Integral::tanh(arg));
  }

  //---------------------------------------------------------------------------
  //
  // private methods
  //
  //---------------------------------------------------------------------------

private:
  
  // friend functions:
  //  while friend functions are generally discouraged in the ISIP
  //  environment, they are used in the MScalar class to circumvent the
  //  template delayed compilation problem. 
  //
  friend class MScalarMethods;
};

  
// end of include file
//
#endif
