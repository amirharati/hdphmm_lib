// file: $isip/class/math/vector/MVector/MVector.h
// version: $Id: MVector.h 10636 2007-01-26 22:18:09Z tm334 $
//

// make sure definitions are only made once
//
#ifndef ISIP_MVECTOR
#define ISIP_MVECTOR

// isip include files
//
#ifndef ISIP_BYTE
#include <Byte.h>
#endif

#ifndef ISIP_ULONG
#include <Ulong.h>
#endif

#ifndef ISIP_USHORT
#include <Ushort.h>
#endif

#ifndef ISIP_ULLONG
#include <Ullong.h>
#endif

#ifndef ISIP_SHORT
#include <Short.h>
#endif

#ifndef ISIP_LONG
#include <Long.h>
#endif

#ifndef ISIP_LLONG
#include <Llong.h>
#endif

#ifndef ISIP_FLOAT
#include <Float.h>
#endif

#ifndef ISIP_DOUBLE
#include <Double.h>
#endif

#ifndef ISIP_COMPLEX_LONG
#include <ComplexLong.h>
#endif

#ifndef ISIP_COMPLEX_FLOAT
#include <ComplexFloat.h>
#endif

#ifndef ISIP_COMPLEX_DOUBLE
#include <ComplexDouble.h>
#endif

#ifndef ISIP_STRING
#include <String.h>
#endif

#ifndef ISIP_MVECTOR_METHODS
#include "MVectorMethods.h"
#endif

// MVector: the vector template class which is inherited by other
// vector classes. TScalar is a Scalar class, TIntegral is an Integral
// type. most of the methods in this class are inline wrappers to the
// MVectorMethods class functions. this is done to allow us to remove
// implementations from the header file, and thus avoid the
// compilation overhead inherent in compiling template classes with
// multiple explicit instantiations.
//
template<class TScalar, class TIntegral>
class MVector {
  
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
  // i/o related constants
  //
  //----------------------------------------  
  
  static const String DEF_PARAM;
  
  // i/o data buffering lengths
  //
  static const int32 TEXT_READ_SIZE = 128;
  static const int32 TEXT_PARTIAL_READ_SIZE = 33;
  static const int32 TEXT_WRITE_SIZE = 512;
  
  //----------------------------------------
  //
  // default values and arguments
  //
  //----------------------------------------  
  
  // define the default value(s) of the class data
  //
  static const TIntegral DEF_VALUE;
  static const int32 DEF_LENGTH = 0;
  
  // default arguments to methods
  //
  static const TIntegral DEF_OFFSET;
  static const TIntegral DEF_INCR;
  static const unichar DEF_DELIM = L',';
  static const String DEF_DELIM_STR;
  static const int32 DEF_SHIFT = 1;
  
  //----------------------------------------
  //
  // error codes
  //
  //----------------------------------------  
  
  static const int32 ERR = 22000;
  static const int32 ERR_LEN = 22001;
  
  //---------------------------------------------------------------------------
  //
  // protected data
  //
  //---------------------------------------------------------------------------
protected:
  
  // vector elements
  //
  TScalar* v_d;
  
  // the number of elements of this vector
  //
  Long length_d;
  
  // the maximum number of elements
  //
  Long capacity_d;		     
  
  // declare a static debug level for all class instantiations
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
  
  // other static methods
  //
  static bool8 diagnose(Integral::DEBUG level) {
    return MVectorMethods::
      diagnose<MVector<TScalar, TIntegral>, TScalar, TIntegral>(level);
  }
  
  // method: setDebug
  //
  static bool8 setDebug(Integral::DEBUG level) {
    debug_level_d = level;
    return true;
  }
  
  // method: debug
  //
  bool8 debug(const unichar* message_a) const {
    return debug(name(), message_a);
  }
  
  // method: destructor
  //
  ~MVector();
  
  // method: default constructor
  //
  MVector();
  
  // method: copy constructor
  //
  MVector(const MVector& vector);
  
  // assign methods:
  //  this method is templatized so it can also do conversions
  //
  template<class TAScalar, class TAIntegral>
  bool8 assign(const MVector<TAScalar, TAIntegral>& arg_a);
  
  // operator= methods:
  //  these methods are omitted because they are defined in the
  //  classes that instantiate this template
  //
  
  // i/o methods
  //
  int32 sofSize() const {
    return MVectorMethods::sofSize<TScalar, TIntegral>(*this);
  }
  
  bool8 read(Sof& sof, int32 tag, const String& name = CLASS_NAME) {
    return MVectorMethods::read<TScalar,TIntegral>(*this, sof, tag, name);
  }
  
  bool8 write(Sof& sof, int32 tag, const String& name = CLASS_NAME) const {
    return MVectorMethods::write<TScalar,TIntegral>(*this, sof, tag, name);
  }
  
  bool8 readData(Sof& sof, const String& pname = DEF_PARAM,
		   int32 size = SofParser::FULL_OBJECT,
		   bool8 param = true, bool8 nested = true) {
    return MVectorMethods::readData<TScalar,TIntegral>(*this, sof, pname,
						       size, param, nested);
  }
  
  bool8 writeData(Sof& sof, const String& name = DEF_PARAM) const {
    return MVectorMethods::writeData<TScalar,TIntegral>(*this, sof, name);
  }
  
  // equality methods
  //
  bool8 eq(const MVector& vector) const;
  
  // memory management methods:
  //  the new and delete methods are omitted because they are defined in the
  //  classes that instantiate this template
  //
  bool8 clear(Integral::CMODE cmode = Integral::DEF_CMODE);
  
  //-------------------------------------------------------------------------
  //
  // class-specific public methods:
  //  extensions to required methods
  //
  //-------------------------------------------------------------------------
  
  // debug methods:
  //  this second debug method is used so that template instantiations can use
  //  a common debug method and just pass in their name
  //
  bool8 debug(const String& name, const unichar* message) const;
  
  // constructor(s)
  //
  MVector(int32 len);
  
  // assign methods
  //
  bool8 assign(TIntegral value);    
  bool8 assign(int32 length, TIntegral value);
  
  // array conversion methods
  //
  template<class TAIntegral>
  bool8 assign(int32 num_elem, const TAIntegral* arg) {
    return MVectorMethods::assign<TScalar,TIntegral>(*this, num_elem, arg);
  }
  
  // conversion from string methods
  //
  bool8 assign(const String& arg, unichar delim = DEF_DELIM) {
    return MVectorMethods::assign<TScalar,TIntegral>(*this, arg, delim);
  }
  
  bool8 assign(const unichar* arg, unichar delim = DEF_DELIM) {
    return MVectorMethods::assign<TScalar,TIntegral>(*this, arg, delim);
  }
  
  // conversion to string methods
  //
  bool8 get(String& output, const String& delim = DEF_DELIM_STR) const {
    return MVectorMethods::get(*this, output, delim);
  }
  
  bool8 get(String& output, const unichar* delim) const {
    String delim_str(delim);
    return MVectorMethods::get(*this, output, delim_str);
  }
  
  // swap methods:
  //  swap the current vector with the input vector
  //
  bool8 swap(MVector& arg) {
    return MVectorMethods::swap<TScalar, TIntegral>(*this, arg);
  }
  
  // partial read methods
  //
  bool8 readStart(Sof& sof, const String& pname = DEF_PARAM,
		    int32 size = SofParser::FULL_OBJECT,
		    bool8 param = true,
		    bool8 nested = true) {
    return MVectorMethods::
      readStart<TScalar, TIntegral>(*this, sof, pname, size, param, nested);
  }
  
  int32 readPartialData(Sof& sof, int32 start_pos, int32 num_elem,
		       const String& pname = DEF_PARAM,
		       int32 size = SofParser::FULL_OBJECT,
		       bool8 param = true,
		       bool8 nested = false) {
    return MVectorMethods::
      readPartialData<TScalar,TIntegral>(*this, sof, start_pos,
					 num_elem, pname, size, param, nested);
  }
  
  // method: readTerminate
  //
  bool8 readTerminate(Sof& sof) {
    return sof.stopPartialRead();
  }
  
  // partial write methods
  //
  bool8 writeStart(Sof& sof, const String& pname = DEF_PARAM) const {
    return MVectorMethods::writeStart<TScalar,TIntegral>(*this, sof, pname);
  }
  
  int32 writePartialData(Sof& sof, int32 start_pos, int32 num_elem) const {
    return MVectorMethods::
      writePartialData<TScalar, TIntegral>(*this, sof, start_pos, num_elem);
  }
  
  bool8 writeTerminate(Sof& sof, const String& pname = DEF_PARAM) const {
    return MVectorMethods::
      writeTerminate<TScalar, TIntegral>(*this, sof, pname);
  }
  
  // memory size methods
  //
  int32 memSize() const {
    return MVectorMethods::memSize<TScalar, TIntegral>(*this);
  }
  
  //---------------------------------------------------------------------------
  //
  // class-specific public methods:
  //  equality and comparison methods
  //
  //---------------------------------------------------------------------------
  
  // method: eq
  //
  bool8 eq(TIntegral value) const {
    return apply(value, &TScalar::eq);
  }
  
  // method: ne
  //
  bool8 ne(const MVector& vector) const {
    return (!eq(vector));
  }
  
  // method: ne
  //
  bool8 ne(TIntegral value) const {
    return apply(value, &TScalar::ne);
  }
  
  // method: lt
  //
  bool8 lt(TIntegral value) const {
    return apply(value, &TScalar::lt);
  }
  
  // method: le
  //
  bool8 le(TIntegral value) const {
    return apply(value, &TScalar::le);
  }
  
  // method: gt
  //
  bool8 gt(TIntegral value) const {
    return apply(value, &TScalar::gt);
  }
  
  // method: ge
  //
  bool8 ge(TIntegral value) const {
    return apply(value, &TScalar::ge);
  }
  
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
  
  // almostEqual methods
  //
  bool8 almostEqual(const MVector& vector,
		      float64 percent = Integral::DEF_PERCENTAGE,
		      float64 bound = Integral::DEF_BOUND) const;
  bool8 almostEqual(TIntegral value,
		      float64 percent = Integral::DEF_PERCENTAGE,
		      float64 bound = Integral::DEF_BOUND) const;
  
  //---------------------------------------------------------------------------
  //
  // class-specific public methods:
  //  operator overloads, get and set methods
  //
  //---------------------------------------------------------------------------
  
  // method: operator()
  //
  TScalar& operator()(int32 index_a) {
    return v_d[index_a];
  }
  
  // method: operator()
  //
  const TScalar& operator()(int32 index_a) const {
    return v_d[index_a];
  }
  
  // method: length
  //
  int32 length() const {
    return (int32)length_d;
  }
  
  // method: getCapacity
  //
  int32 getCapacity() const {
    return (int32)capacity_d;
  }
  
  // resize methods
  //
  bool8 setLength(int32 length, bool8 preserve_values = true);
  bool8 setCapacity(int32 capacity, bool8 preserve_values = true);
  
  //---------------------------------------------------------------------------
  //
  // class-specific public methods:
  //  bitwise methods, report error if TIntegral is float32 or float64
  //
  //--------------------------------------------------------------------------
  
  // method: band
  //
  bool8 band(const MVector& v2) {
    return apply(*this, v2, &TScalar::band);
  }
  
  // method: band
  //
  bool8 band(const MVector& v1, const MVector& v2) {
    return apply(v1, v2, &TScalar::band);
  }
  
  // method: band
  //
  bool8 band(TIntegral value) {
    return apply(*this, value, &TScalar::band);
  }
  
  // method: band
  //
  bool8 band(const MVector& v1, TIntegral value) {
    return apply(v1, value, &TScalar::band);
  }
  
  // method: bor
  //
  bool8 bor(const MVector& v2) {
    return apply(*this, v2, &TScalar::bor);
  }
  
  // method: bor
  //
  bool8 bor(const MVector& v1, const MVector& v2) {
    return apply(v1, v2, &TScalar::bor);
  }
  
  // method: bor
  //
  bool8 bor(TIntegral value) {
    return apply(*this, value, &TScalar::bor);
  }
  
  // method: bor
  //
  bool8 bor(const MVector& v1, TIntegral value) {
    return apply(v1, value, &TScalar::bor);
  }
  
  // method: bxor
  //
  bool8 bxor(const MVector& v2) {
    return apply(*this, v2, &TScalar::bxor);
  }
  
  // method: bxor
  //
  bool8 bxor(const MVector& v1, const MVector& v2) {
    return apply(v1, v2, &TScalar::bxor);
  }
  
  // method: bxor
  //
  bool8 bxor(TIntegral value) {
    return apply(*this, value, &TScalar::bxor);
  }
  
  // method: bxor
  //
  bool8 bxor(const MVector& v1, TIntegral value) {
    return apply(v1, value, &TScalar::bxor);
  }
  
  // method: brs
  //
  bool8 brs(TIntegral shift_amount = DEF_SHIFT) {
    return apply(*this, shift_amount, &TScalar::brs);
  }
  
  // method: brs
  //
  bool8 brs(const MVector& v1, TIntegral shift_amount = DEF_SHIFT) {
    return apply(v1, shift_amount, &TScalar::brs);
  }
  
  // method: bls
  //
  bool8 bls(TIntegral shift_amount = DEF_SHIFT) {
    return apply(*this, shift_amount, &TScalar::bls);
  }
  
  // method: bls
  //
  bool8 bls(const MVector& v1, TIntegral shift_amount = DEF_SHIFT) {
    return apply(v1, shift_amount, &TScalar::bls);
  }
  
  // method: bcmpl
  //
  bool8 bcmpl(const MVector& v1) {
    return apply(v1, &TScalar::bcmpl);
  }
  
  // method: bcmpl
  //
  bool8 bcmpl() {
    return apply(*this, &TScalar::bcmpl);
  }
  
  //---------------------------------------------------------------------------
  //
  // class-specific public methods:
  //  basic mathematical methods
  //
  //--------------------------------------------------------------------------
  
  // method: add
  //
  template<class TAScalar, class TAIntegral>
  bool8 add(const MVector<TAScalar, TAIntegral>& vector) {
    return apply(*this, vector, &TScalar::add);
  }
  
  // method: add
  //
  template<class TAScalar, class TAIntegral>
  bool8 add(const MVector& v1, const MVector<TAScalar, TAIntegral>& v2) {
    return apply(v1, v2, &TScalar::add);
  }
  
  // method: add
  //
  bool8 add(TIntegral value) {
    return apply(*this, value, &TScalar::add);
  }
  
  // method: add
  //
  bool8 add(const MVector& vector, TIntegral value) {
    return apply(vector, value, &TScalar::add);
  }
  
  // method: sub
  //
  template<class TAScalar, class TAIntegral>
  bool8 sub(const MVector<TAScalar, TAIntegral>& vector) {
    return apply(*this, vector, &TScalar::sub);
  }
  
  // method: sub
  //
  template<class TAScalar, class TAIntegral>
  bool8 sub(const MVector& v1, const MVector<TAScalar, TAIntegral>& v2) {
    return apply(v1, v2, &TScalar::sub);
  }
  
  // method: sub
  //
  bool8 sub(TIntegral value) {
    return apply(*this, value, &TScalar::sub);
  }
  
  // method: sub
  //
  bool8 sub(const MVector& vector, TIntegral value) {
    return apply(vector, value, &TScalar::sub);
  }
  
  // method: mult
  //
  template<class TAScalar, class TAIntegral>
  bool8 mult(const MVector<TAScalar, TAIntegral>& vector) {
    return apply(*this, vector, &TScalar::mult);
  }
  
  // method: mult
  //
  template<class TAScalar, class TAIntegral>
  bool8 mult(const MVector& v1, const MVector<TAScalar, TAIntegral>& v2) {
    return apply(v1, v2, &TScalar::mult);
  }
  
  // method: mult
  //
  bool8 mult(TIntegral value) {
    return apply(*this, value, &TScalar::mult);
  }
  
  // method: mult
  //
  bool8 mult(const MVector& vector, TIntegral value) {
    return apply(vector, value, &TScalar::mult);
  }
  
  // method: div
  //
  template<class TAScalar, class TAIntegral>
  bool8 div(const MVector<TAScalar, TAIntegral>& vector) {
    return apply(*this, vector, &TScalar::div);
  }
  
  // method: div
  //
  template<class TAScalar, class TAIntegral>
  bool8 div(const MVector& v1, const MVector<TAScalar, TAIntegral>& v2) {
    return apply(v1, v2, &TScalar::div);
  }
  
  // method: div
  //
  bool8 div(TIntegral value) {
    return apply(*this, value, &TScalar::div);
  }
  
  // method: div
  //
  bool8 div(const MVector& vector, TIntegral value) {
    return apply(vector, value, &TScalar::div);
  }
  
  // method: mod
  //
  bool8 mod(const MVector& vector) {
    return apply(*this, vector, &TScalar::mod);
  }
  
  // method: mod
  //
  bool8 mod(const MVector& v1, const MVector& v2) {
    return apply(v1, v2, &TScalar::mod);
  }
  
  // method: mod
  //
  bool8 mod(TIntegral value) {
    return apply(*this, value, &TScalar::mod);
  }
  
  // method: mod
  //
  bool8 mod(const MVector& vector, TIntegral value) {
    return apply(vector, value, &TScalar::mod);
  }
  
  //---------------------------------------------------------------------------
  //
  // class-specific public methods:
  //  other mathematical methods
  //
  //--------------------------------------------------------------------------
  
  // common mathematical methods
  //
  bool8 pow(float64 y) {
    return MVectorMethods::pow<TScalar, TIntegral>(*this, *this, y);
  }
  
  bool8 pow(const MVector& x, float64 y) {
    return MVectorMethods::pow<TScalar, TIntegral>(*this, x, y);
  }
  
  // method: exp
  //
  bool8 exp() {
    return apply(*this, &TScalar::exp);
  }
  
  // method: exp
  //
  bool8 exp(const MVector& vector) {
    return apply(vector, &TScalar::exp);
  }
  
  // method: exp2
  //
  bool8 exp2() {
    return apply(*this, &TScalar::exp2);
  }
  
  // method: exp2
  //
  bool8 exp2(const MVector& vector) {
    return apply(vector, &TScalar::exp2);
  }
  
  // method: exp10
  //
  bool8 exp10() {
    return apply(*this, &TScalar::exp10);
  }
  
  // method: exp10
  //
  bool8 exp10(const MVector& vector) {
    return apply(vector, &TScalar::exp10);
  }
  
  // method: factorial
  //
  bool8 factorial() {
    return apply(*this, &TScalar::factorial);
  }
  
  // method: factorial
  //
  bool8 factorial(const MVector& vector) {
    return apply(vector, &TScalar::factorial);
  }
  
  // method: log
  //
  bool8 log() {
    return apply(*this, &TScalar::log);
  }
  
  // method: log
  //
  bool8 log(const MVector& vector) {
    return apply(vector, &TScalar::log);
  }
  
  // method: log1p
  //
  bool8 log1p() {
    return apply(*this, &TScalar::log1p);
  }
  
  // method: log1p
  //
  bool8 log1p(const MVector& vector) {
    return apply(vector, &TScalar::log1p);
  }
  
  // method: log2
  //
  bool8 log2() {
    return apply(*this, &TScalar::log2);
  }
  
  // method: log2
  //
  bool8 log2(const MVector& vector) {
    return apply(vector, &TScalar::log2);
  }
  
  // method: log10
  //
  bool8 log10() {
    return apply(*this, &TScalar::log10);
  }
  
  // method: log10
  //
  bool8 log10(const MVector& vector) {
    return apply(vector, &TScalar::log10);
  }
  
  // sorting and indexing methods
  //
  bool8 sort(Integral::ORDER order = Integral::DEF_ORDER) {
    return MVectorMethods::sort<TScalar, TIntegral>(*this, *this, order);
  }
  
  bool8 sort(const MVector& vector,
	       Integral::ORDER order = Integral::DEF_ORDER) {
    return MVectorMethods::sort<TScalar, TIntegral>(*this, vector, order);
  }  
  
  bool8 index(MVector<Long, int32>& sort_index,
		Integral::ORDER order = Integral::DEF_ORDER) {
    return MVectorMethods::index<TScalar, TIntegral>(*this, order, sort_index);
  }
  
  bool8 randperm(int32 size) {
    return MVectorMethods::randperm(*this, size);
  }
  
  // method: abs
  //
  bool8 abs() {
    return apply(*this, &TScalar::abs);
  }
  
  // method: abs
  //
  bool8 abs(const MVector& vector) {
    return apply(vector, &TScalar::abs);
  }
  
  // mathematical limits, ceiling, floor and rounding methods
  //
  TIntegral max() const {
    static int32 pos;
    return MVectorMethods::max<TScalar, TIntegral>(*this, pos);
  }
  
  TIntegral max(int32& position) const {
    return MVectorMethods::max<TScalar, TIntegral>(*this, position);
  }
  
  TIntegral min() const {
    static int32 pos;
    return MVectorMethods::min<TScalar, TIntegral>(*this, pos);
  }
  
  TIntegral min(int32& position) const {
    return MVectorMethods::min<TScalar, TIntegral>(*this, position);
  }
  
  float64 minMag() const {
    static int32 pos;
    return MVectorMethods::minMag<TScalar, TIntegral>(*this, pos);
  }
  
  float64 minMag(int32& position) const {
    return MVectorMethods::minMag<TScalar, TIntegral>(*this, position);
  }
  
  float64 maxMag() const {
    static int32 pos;
    return MVectorMethods::maxMag<TScalar, TIntegral>(*this, pos);
  }
  
  float64 maxMag(int32& position) const {
    return MVectorMethods::maxMag<TScalar, TIntegral>(*this, position);
  }
  
  // method: neg
  //
  bool8 neg() {
    return apply(*this, &TScalar::neg);
  }
  
  // method: neg
  //
  bool8 neg(const MVector& vector) {
    return apply(vector, &TScalar::neg);
  }
  
  // method: round
  //
  bool8 round() {
    return apply(*this, &TScalar::round);
  }
  
  // method: round
  //
  bool8 round(const MVector& vector) {
    return apply(vector, &TScalar::round);
  }
  
  // method: ceil
  //
  bool8 ceil() {
    return apply(*this, &TScalar::ceil);
  }
  
  // method: ceil
  //
  bool8 ceil(const MVector& vector) {
    return apply(vector, &TScalar::ceil);
  }
  
  // method: rceil
  //
  bool8 rceil() {
    return apply(*this, &TScalar::rceil);
  }
  
  // method: rceil
  //
  bool8 rceil(const MVector& vector) {
    return apply(vector, &TScalar::rceil);
  }
  
  // method: floor
  //
  bool8 floor() {
    return apply(*this, &TScalar::floor);
  }
  
  // method: floor
  //
  bool8 floor(const MVector& vector) {
    return apply(vector, &TScalar::floor);
  }
  
  // method: rfloor
  //
  bool8 rfloor() {
    return apply(*this, &TScalar::rfloor);
  }
  
  // method: rfloor
  //
  bool8 rfloor(const MVector& vector) {
    return apply(vector, &TScalar::rfloor);
  }
  
  // method: fraction
  //
  bool8 fraction() {
    return apply(*this, &TScalar::fraction);
  }
  
  // method: fraction
  //
  bool8 fraction(const MVector& vector) {
    return apply(vector, &TScalar::fraction);
  }
  
  // method: sign
  //
  bool8 sign() {
    return apply(*this, &TScalar::sign);
  }
  
  // method: sign
  //
  bool8 sign(const MVector& vector) {
    return apply(vector, &TScalar::sign);
  }
  
  // method: sin
  //
  bool8 sin() {
    return apply(*this, &TScalar::sin);
  }
  
  // method: sin
  //
  bool8 sin(const MVector& vector) {
    return apply(vector, &TScalar::sin);
  }
  
  // method: sinh
  //
  bool8 sinh() {
    return apply(*this, &TScalar::sinh);
  }
  
  // method: sinh
  //
  bool8 sinh(const MVector& vector) {
    return apply(vector, &TScalar::sinh);
  }
  
  // method: cos
  //
  bool8 cos() {
    return apply(*this, &TScalar::cos);
  }
  
  // method: cos
  //
  bool8 cos(const MVector& vector) {
    return apply(vector, &TScalar::cos);
  }
  
  // method: cosh
  //
  bool8 cosh() {
    return apply(*this, &TScalar::cosh);
  }
  
  // method: cosh
  //
  bool8 cosh(const MVector& vector) {
    return apply(vector, &TScalar::cosh);
  }  
  
  // method: tan
  //
  bool8 tan() {
    return apply(*this, &TScalar::tan);
  }
  
  // method: tan
  //
  bool8 tan(const MVector& vector) {
    return apply(vector, &TScalar::tan);
  }

  // method: tanh
  //
  bool8 tanh() {
    return apply(*this, &TScalar::tanh);
  }
  
  // method: tanh
  //
  bool8 tanh(const MVector& vector) {
    return apply(vector, &TScalar::tanh);
  }
    
  // method: asin
  //
  bool8 asin() {
    return apply(*this, &TScalar::asin);
  }
  
  // method: asin
  //
  bool8 asin(const MVector& vector) {
    return apply(vector, &TScalar::asin);
  }

  // method: asinh
  //
  bool8 asinh() {
    return apply(*this, &TScalar::asinh);
  }
  
  // method: asinh
  //
  bool8 asinh(const MVector& vector) {
    return apply(vector, &TScalar::asinh);
  }  
  
  // method: acos
  //
  bool8 acos() {
    return apply(*this, &TScalar::acos);
  }
  
  // method: acos
  //
  bool8 acos(const MVector& vector) {
    return apply(vector, &TScalar::acos);
  }

  // method: acosh
  //
  bool8 acosh() {
    return apply(*this, &TScalar::acosh);
  }
  
  // method: acosh
  //
  bool8 acosh(const MVector& vector) {
    return apply(vector, &TScalar::acosh);
  }
  
  // method: atan
  //
  bool8 atan() {
    return apply(*this, &TScalar::atan);
  }
  
  // method: atan
  //
  bool8 atan(const MVector& vector) {
    return apply(vector, &TScalar::atan);
  }
  
  // method: atanh
  //
  bool8 atanh() {
    return apply(*this, &TScalar::atanh);
  }
  
  // method: atanh
  //
  bool8 atanh(const MVector& vector) {
    return apply(vector, &TScalar::atanh);
  }
  
  // ramp function generation methods
  //
  bool8 ramp(TIntegral offset = DEF_OFFSET, TIntegral incr = DEF_INCR) {
    return MVectorMethods::ramp<TScalar,TIntegral>(*this, offset, incr);
  }
  
  // method: ramp
  //
  bool8 ramp(TIntegral offset, TIntegral incr, TIntegral end) {
    return MVectorMethods::ramp<TScalar,TIntegral>(*this, offset, incr, end);
  }
  
  // method: sqrt
  //
  bool8 sqrt() {
    return apply(*this, &TScalar::sqrt);
  }
  
  // method: sqrt
  //
  bool8 sqrt(const MVector<TScalar,TIntegral>& vec) {
    return apply(vec, &TScalar::sqrt);
  }
  
  // method: square
  //
  bool8 square() {
    return apply(*this, &TScalar::square);
  }
  
  // method: square
  //
  bool8 square(const MVector<TScalar, TIntegral>& x) {
    return apply(x, &TScalar::square);
  }
  
  // inverse methods
  //
  bool8 inverse() {
    return apply(*this, &TScalar::inverse);
  }
  
  bool8 inverse(const MVector<TScalar, TIntegral>& x) {
    return apply(x, &TScalar::inverse);
  }
  
  // vector to scalar mathematical methods
  //
  TIntegral sum() const {
    return MVectorMethods::sum<TScalar, TIntegral>(*this);
  }
  
  TIntegral sumSquare() const {
    return MVectorMethods::sumSquare<TScalar, TIntegral>(*this);
  }
  
  TIntegral mean() const {
    return MVectorMethods::mean<TScalar, TIntegral>(*this);
  }
  
  TIntegral median() const {
    return MVectorMethods::median<TScalar, TIntegral>(*this);
  }
  
  TIntegral rms() const {
    return MVectorMethods::rms<TScalar, TIntegral>(*this);
  }
  
  TIntegral var() const {
    return MVectorMethods::var<TScalar, TIntegral>(*this);
  }
  
  TIntegral stdev() const {
    return MVectorMethods::stdev<TScalar, TIntegral>(*this);
  }
  
  TIntegral dotProduct(const MVector& vector) const {
    return MVectorMethods::dotProduct<TScalar, TIntegral>(*this, vector);
  }
  
  // method: norm
  //
  TIntegral norm() const {
    return (TIntegral)Integral::sqrt(dotProduct(*this));
  }
  
  // method: distance
  //
  TIntegral distance(const MVector& vector) const {
    return (TIntegral)Integral::sqrt(distanceSquare(vector));
  }
  
  TIntegral distanceSquare(const MVector& vector) const {
    return MVectorMethods::distanceSquare<TScalar, TIntegral>(*this, vector);
  }
  
  int32 numEqual(TIntegral test_value) const {
    return MVectorMethods::numEqual<TScalar, TIntegral>(*this, test_value);
  }
  
  int32 numNotEqual(TIntegral test_value) const {
    return MVectorMethods::numNotEqual<TScalar, TIntegral>(*this, test_value);
  }
  
  //---------------------------------------------------------------------------
  //
  // class-specific public methods:
  //  dsp related methods 
  //
  //--------------------------------------------------------------------------

  // dsp methods
  // 
#ifdef ISIP_TEMPLATE_complex
  bool8 limit(TIntegral min_val, TIntegral max_val) {
    return false;
  }
  
  bool8 limit(TIntegral min_val, TIntegral max_val, const MVector& vector) {
    return false;
  }
  
  bool8 limitMin(TIntegral min_val) {
    return false;
  }
  
  bool8 limitMin(TIntegral min_val, const MVector& vector) {
    return false;
  }
  
  bool8 limitMax(TIntegral max_val) {
    return false;
  }
  
  bool8 limitMax(TIntegral max_val, const MVector& vector) {
    return false;
  }
  
  bool8 limitMag(TIntegral cmp_val, TIntegral new_val) {
    return false;
  }
  
  bool8 limitMag(TIntegral cmp_val, TIntegral new_val,
		   const MVector& vector) { 
    return false;
  }
  
  bool8 centerClip(TIntegral min_val, TIntegral max_val) {
    return false;
  }
  
  bool8 centerClip(TIntegral min_val, TIntegral max_val,
		     const MVector& vector) {
    return false;
  }
#else
  bool8 limit(TIntegral min_val, TIntegral max_val) {
    return MVectorMethods::limit<TScalar, TIntegral>(*this, min_val, max_val,
						     *this);
  }
  
  bool8 limit(TIntegral min_val, TIntegral max_val, const MVector& vector) {
    return MVectorMethods::limit<TScalar, TIntegral>(*this, min_val, max_val,
						     vector);
  }
  
  bool8 limitMin(TIntegral min_val) {
    return MVectorMethods::limitMin<TScalar, TIntegral>(*this, min_val, *this);
  }
  
  bool8 limitMin(TIntegral min_val, const MVector& vector) {
    return MVectorMethods::
      limitMin<TScalar, TIntegral>(*this, min_val, vector);
  }
  
  bool8 limitMax(TIntegral max_val) {
    return MVectorMethods::limitMax<TScalar, TIntegral>(*this, max_val, *this);
  }
  
  bool8 limitMax(TIntegral max_val, const MVector& vector) {
    return MVectorMethods::
      limitMax<TScalar, TIntegral>(*this, max_val, vector);
  }
  
  bool8 limitMag(TIntegral cmp_val, TIntegral new_val) {
    return MVectorMethods::limitMag<TScalar, TIntegral>(*this, cmp_val,
							new_val, *this);
  }
  
  bool8 limitMag(TIntegral cmp_val, TIntegral new_val,
		   const MVector& vector) { 
    return MVectorMethods::limitMag<TScalar, TIntegral>(*this, cmp_val,
							new_val, vector);
  }
  
  bool8 centerClip(TIntegral min_val, TIntegral max_val) {
    return MVectorMethods::centerClip<TScalar, TIntegral>(*this, min_val,
							  max_val, *this);
  }
  
  bool8 centerClip(TIntegral min_val, TIntegral max_val,
		     const MVector& vector) {
    return MVectorMethods::centerClip<TScalar, TIntegral>(*this, min_val,
							  max_val, vector);
  }
#endif
  
  // random number generation methods  
  //
  bool8 rand(Random& generator = Random::GLOBAL_UNIFORM) {
    return MVectorMethods::rand<TScalar, TIntegral>(*this, generator);
  }
  
  bool8 rand(TIntegral min_val, TIntegral max_val,
	       Random& generator = Random::GLOBAL_UNIFORM) {
    return MVectorMethods::rand<TScalar, TIntegral>(*this, min_val,
						    max_val, generator);
  }
  
  bool8 grand(TIntegral mean, TIntegral stdev,
		Random& generator = Random::GLOBAL_GAUSSIAN) {
    return MVectorMethods::grand<TScalar, TIntegral>(*this, mean,
						     stdev, generator);
  }
  
  //---------------------------------------------------------------------------
  //
  // class-specific public methods:
  //  position operation and search methods
  //
  //--------------------------------------------------------------------------
  
  // position operation methods
  //
  bool8 move(const MVector& vector, int32 num_elements,
	       int32 source_offset, int32 dest_offset) {
    return MVectorMethods::move<TScalar, TIntegral>(*this,
						    vector, num_elements,
						    source_offset,
						    dest_offset);
  }
  
  bool8 shift(int32 delta) {
    return MVectorMethods::shift<TScalar, TIntegral>(*this, delta);
  }
  
  bool8 shift(const MVector& vector, int32 delta) {
    return MVectorMethods::shift<TScalar, TIntegral>(*this, vector, delta);
  }
  
  bool8 concat(const MVector& v2) {
    return MVectorMethods::concat<TScalar, TIntegral>(*this, v2);
  }
  
  bool8 concat(const MVector& v1, const MVector& v2) {
    return MVectorMethods::concat<TScalar, TIntegral>(*this, v1, v2);
  }
  
  bool8 deleteRange(int32 offset, int32 num_elements) {
    return MVectorMethods::deleteRange<TScalar, TIntegral>(*this, *this,
							   offset,
							   num_elements);
  }
  
  bool8 deleteRange(const MVector& v1, int32 offset, int32 num_elements) {
    return MVectorMethods::deleteRange<TScalar, TIntegral>(*this,
							   v1,
							   offset,
							   num_elements);
  }
  
  bool8 setRange(int32 offset, int32 num_elements, TIntegral value) {
    return MVectorMethods::setRange<TScalar, TIntegral>(*this, offset,
							num_elements, value);
  }
  
  // search and ordering methods
  //
  int32 first(TIntegral value, int32 start_pos = Integral::NO_POS) {
    return MVectorMethods::first<TScalar, TIntegral>(*this, value, start_pos);
  }
  
  int32 last(TIntegral value, int32 end_pos = Integral::NO_POS) {
    return MVectorMethods::last<TScalar, TIntegral>(*this, value, end_pos);
  }
  
  bool8 reorder(const MVector<Long, int32>& indexes) {
    return MVectorMethods::reorder<TScalar, TIntegral>(*this, indexes);
  }
  
  bool8 reorder(const MVector& arg, const MVector<Long,int32>& indexes) {
    return MVectorMethods::reorder<TScalar, TIntegral>(*this, arg, indexes);
  }
  
  bool8 reverse() {
    return MVectorMethods::reverse<TScalar, TIntegral>(*this);
  }

  
  //---------------------------------------------------------------------------
  //
  // private methods
  //
  //---------------------------------------------------------------------------
private:
  
  // apply methods:
  //  these methods apply the specified function to each element of the vector
  //  
  bool8 apply(const MVector& arg1, TIntegral (TScalar::*method)(TIntegral));
  
  template<class TAScalar, class TAIntegral>
  bool8 apply(const MVector& arg1, const MVector<TAScalar,TAIntegral>& arg2,
		TIntegral (TScalar::*method) (TIntegral, TIntegral));
  
  bool8 apply(const MVector& arg1, TIntegral arg2,
		TIntegral (TScalar::*method) (TIntegral, TIntegral));
  
  bool8 apply(TIntegral arg2,
		bool8 (TScalar::*method) (TIntegral) const) const;
  
  // friend classes:
  //  while friend classes and functions are generally discouraged,
  //  they are used in the MVector class to circumvent the
  //  template delayed compilation problem. 
  //
  friend class MVectorMethods;
};


// method: apply
// 
// arguments:
//  const MVector& v: (input) input vector
//  TIntegral (TScalar::*method_a) (TIntegral,TIntegral): (input) function
//                                                        pointer
//  
// return: a bool8 value indicating status
//
// this method applies method_a function to every element of v_a
//
template<class TScalar, class TIntegral>
bool8 MVector<TScalar, TIntegral>::
apply(const MVector& v_a, TIntegral (TScalar::*method_a) (TIntegral arg)) {
  
  if (!setLength((int32)v_a.length_d, false)) {
    v_a.debug(L"v_a");
    return Error::handle(name(), L"apply", Error::NOMEM, 
			 __FILE__, __LINE__);
  }
  
  // compute piecewise
  //
  for (int32 index = (int32)length_d - 1; index >= 0; index--) {
    (v_d[index].*method_a)(v_a.v_d[index]);
  }

  // exit gracefully
  // 
  return true;  
}

// method: apply
// 
// arguments:
//  const MVector& v1: (input) input vector
//  const MVector<TAScalar, TAIntegral>& v2: (input) input vector
//  TIntegral (TScalar::*method_a) (TIntegral,TIntegral): (input) function
//                                                        pointer
//
// return: a bool8 value indicating status
//
// this method applies method_a function to every element of v1_a and v2_a
//
template<class TScalar, class TIntegral>
template<class TAScalar, class TAIntegral>
bool8 MVector<TScalar, TIntegral>::
apply(const MVector& v1_a, const MVector<TAScalar, TAIntegral>& v2_a,
      TIntegral (TScalar::*method_a) (TIntegral,TIntegral)) {
  
  // make sure the lengths are equal
  //
  int32 last_index = (int32)v1_a.length_d;
  
  if (last_index != (int32)v2_a.length()) {
    v1_a.debug(L"v1_a");        
    v2_a.debug(L"v2_a");    
    return Error::handle(name(), L"apply", Error::ARG, __FILE__, __LINE__);
    
  }
  
  // resize
  //
  if (!setLength(last_index, false)) {
    this->debug(L"this");
    return Error::handle(name(), L"apply", Error::NOMEM, __FILE__, __LINE__);
  }
  
  // loop through each element
  //
  for (int32 index = 0; index < last_index; index++) {
    (v_d[index].*method_a)((TIntegral)v1_a.v_d[index], 
			   (TIntegral)v2_a(index));
  }

  // exit gracefully
  //
  return true;
}

// method: apply
// 
// arguments:
//  const MVector& v: (input) input vector
//  TIntegral val: (input) input parameter
//  TIntegral (TScalar::*method_a) (TIntegral,TIntegral): (input) function
//                                                        pointer
//  
// return: a bool8 value indicating status
//
// this method applies method_a function to every element of v with
// parameter val
//
template<class TScalar, class TIntegral>
bool8 MVector<TScalar, TIntegral>::
apply(const MVector& v_a, TIntegral val_a,
      TIntegral (TScalar::*method_a) (TIntegral,TIntegral)) {
  
  // make sure the lengths are equal
  //
  int32 last_index = (int32)v_a.length_d;
  
  // resize
  //
  if (!setLength(last_index, false)) {
    v_a.debug(L"v_a");        
    this->debug(L"this");
    return Error::handle(name(), L"apply", Error::NOMEM, __FILE__, __LINE__);
  }
  
  // loop through each element
  //
  for (int32 index = 0; index < last_index; index++) {
    (v_d[index].*method_a)((TIntegral)v_a.v_d[index], val_a);
  }

  // exit gracefully
  //
  return true;
}

// method: apply
// 
// arguments:
//  TIntegral val: (input) input parameter
//  TIntegral (TScalar::*method_a) (TIntegral,TIntegral): (input) function
//                                                        pointer
//  
// return: a bool8 value indicating status
//
// this method applies method_a function to every element of the current vector
//
template<class TScalar, class TIntegral>
bool8 MVector<TScalar, TIntegral>::
apply(TIntegral val_a, bool8 (TScalar::*method_a) (TIntegral) const) const {
  
  // make sure the lengths are equal
  //
  int32 last_index = (int32)length_d;
  
  // loop through each element
  //
  for (int32 index = 0; index < last_index; index++) {
    if (!(v_d[index].*method_a)(val_a)) {
      return false;
    }
  }

  // exit gracefully
  //
  return true;
}

// method: assign
//
// arguments:
//  const MVector<TAScalar, TAIntegral>& vector: (input) operand
//
// return: a bool8 value indicating status
//
// this method copies the input vector to the current vector
// 
template<class TScalar, class TIntegral>
template<class TAScalar, class TAIntegral>
bool8 MVector<TScalar, TIntegral>::
assign(const MVector<TAScalar, TAIntegral>& vector_a) {
  
  // resize
  // 
  if (!setLength(vector_a.length(), false)) {
    this->debug(L"this");
    vector_a.debug(L"vector_a");        
    return Error::handle(name(), L"assign", Error::NOMEM, __FILE__, __LINE__);
  }
  if (!setCapacity(vector_a.getCapacity(), false)) {
    this->debug(L"this");
    vector_a.debug(L"vector_a");        
    return Error::handle(name(), L"assign", Error::NOMEM, __FILE__, __LINE__);
  }
  
  // copy the data
  // 
  int32 last_index = (int32)length_d;
  for (int32 index = 0; index < last_index; index++) {
    v_d[index] = (TIntegral)vector_a(index);
  }
  
  // exit gracefully
  // 
  return true;
}

// method: assign
//
// arguments:
//  MVector<TScalar, TIntegral>& this: (output) class operand
//  int32 length: (input) length
//  const TAIntegral* v: (input) Vector data
//
// return: a bool8 value indicating status
//
// this method creates a vector from a TAIntegral* array
//
template<class TScalar, class TIntegral, class TAIntegral>
bool8  MVectorMethods::assign(MVector<TScalar, TIntegral>& this_a, 
			       int32 length_a, const TAIntegral* v_a) {
  
  // check argument
  //
  if (length_a <= 0) {
    this_a.debug(L"this_a");        
    return Error::handle(name(), L"assign", Error::ARG, __FILE__, __LINE__);
  }
  
  // resize
  // 
  if (!this_a.setLength(length_a, false)) {
    this_a.debug(L"this_a");    
    return Error::handle(name(), L"assign", Error::NOMEM, __FILE__, __LINE__);
  }
  
  // copy the data
  //
  TAIntegral* ptr_cdata = (TAIntegral*)v_a;
  
  for (int32 index = 0; index < length_a; index++) {
    this_a.v_d[index] = (TIntegral)(*ptr_cdata++);
  }
  
  // exit gracefully
  // 
  return true;
}

// end of include file
//
#endif
