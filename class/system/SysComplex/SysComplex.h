// file: $isip/class/system/SysComplex/SysComplex.h
// version: $Id: SysComplex.h 10643 2007-01-27 07:28:58Z tm334 $
//

// isip include files -- this file is used by IntegralTypes.h, so it
// cannot include any other files. this is why it uses bool instead of
// boolean for a return type.
//
#include <Integral.h>

// make sure definitions are only made once
//
#ifndef ISIP_SYS_COMPLEX
#define ISIP_SYS_COMPLEX

// SysComplex: a class that implements a complex numeric type. this class
// is introduced at this level so the mathematical functions defined
// in Integral can also be defined for complex numbers. enough
// functionality and operators are defined in this class for a SysComplex
// number to be treated in code exactly as any other integral type, so
// the math templates can be built atop this class with very little
// modification.
//
// the implementations introduced below can be found in:
//
//   R.V. Churchill, J.W. Brown, and R.F. Verhey,
//   Complex Variables and Applications, Mc-Graw Hill,
//   New York, New York, USA, 1976, pp. 52-71.
//
// see Integral.h for implementations of mathematical functions.
//
// since this class is a template, implementing diagnostics is not as
// straightforward as a self-contained class such as Random.  the
// model here follows what we use in the data structures library, and
// consists of a diagnose class - SysComplexDiagnose.h. the code for
// the diagnose method is contained within this header file as well.
// the class is tested for specific classes (float and double).  this
// is a little simpler than following the model used in more
// complicated classes such as vectors and matrices. the main
// advantages of the approach used here (and in data structures) are
// that it keeps the code simple (all header files) and allows the
// class to be tested directly without running the diagnostics for
// another class.
//
template <class TSCIntegral>
class SysComplex {

  //---------------------------------------------------------------------------
  //
  // public constants: omitted from this class
  // numeric constants: kept in Integral.h
  //
  //---------------------------------------------------------------------------

  //---------------------------------------------------------------------------
  //
  // protected data
  //
  //---------------------------------------------------------------------------
protected:
  TSCIntegral real_d;
  TSCIntegral imag_d;

  //---------------------------------------------------------------------------
  //
  // required public methods
  //
  //---------------------------------------------------------------------------
public:

  // name and debug methods are omitted since this class acts like an
  // Integral type.
  //

  // diagnose method is in the SysComplexDiagnose.h class
  //

  // method: destructor
  //
  ~SysComplex() {}

  // method: default constructor
  //
  SysComplex() {
    real_d = (TSCIntegral)0;
    imag_d = (TSCIntegral)0;    
  }

  // method: copy constructor
  //
  SysComplex(const SysComplex& arg) {
    real_d = arg.real_d;
    imag_d = arg.imag_d;
  }

  // assign and equality methods are omitted since this class acts
  // like an Integral type. use the operators = and == for this class.
  //
  
  // method: operator = (assignment)
  //
  SysComplex& operator = (const SysComplex& arg) {
    real_d = arg.real_d;
    imag_d = arg.imag_d;
    return *this;
  }

  // i/o and memory management methods are omitted since this class
  // acts like an Integral type -- use the complex scalar types in the
  // math/scalar library for this functionality.
  //
  
  //---------------------------------------------------------------------------
  //
  // class-specific public methods: other constructors, assignment,
  // casting, and component extraction methods
  //
  //---------------------------------------------------------------------------
  

  // method: constructor
  //
  SysComplex(TSCIntegral arg_real, TSCIntegral arg_imag) {
    real_d = arg_real;
    imag_d = arg_imag;
  }

  // method: constructor
  //
  SysComplex(float64 arg_real) {
    real_d = (TSCIntegral)arg_real;
    imag_d = (TSCIntegral)0;
  }

  // method: assign
  //
  bool8 assign(TSCIntegral real, TSCIntegral imag = 0) {
    real_d = real;
    imag_d = imag;
    return true;
  }

  // method: operator = (assignment)
  //
  SysComplex& operator = (TSCIntegral arg) {
    real_d = arg;
    imag_d = 0;
    return *this;
  }

  // method: cast operator
  //
  // this method allows any complex type to be cast to any other
  // complex type. note that you cannot cast a complex to a real, you
  // have to use either real(), imag(), mag(), or angle().
  //
  template <class TAIntegral>
  operator SysComplex<TAIntegral>() const {
    return SysComplex<TAIntegral>((TAIntegral)real_d, (TAIntegral)imag_d);
  }

  // method: real
  //
  TSCIntegral real() const {
    return real_d;
  }

  // method: imag
  //
  TSCIntegral imag() const {
    return imag_d;
  }
  
  // method: abs
  //
  float64 abs() const {
    return mag();
  }
  
  // method: mag
  //
  float64 mag() const {
    return sqrt((float64)real_d * (float64)real_d +
      (float64)imag_d * (float64)imag_d);
  }

  // method: angle
  //
  // note that we call atan2, the four quadrant inverse tangent
  //
  // atan2(Y,X) is the four quadrant arctangent of the real parts of the
  // elements of X and Y.  -pi <= atan2(Y,X) <= pi
  //    
  inline float64 angle() const {
    return ::atan2((float64)imag_d, (float64)real_d);
  }

  //---------------------------------------------------------------------------
  //
  // class-specific public methods:
  //  accumulative arithmetic functions with SysComplex and TSCIntegral types
  //
  //---------------------------------------------------------------------------

  // method: operator +=
  //
  const SysComplex& operator += (const SysComplex& arg) {
    real_d += arg.real_d;
    imag_d += arg.imag_d;
    return *this;
  }

  // method: operator -=
  //
  const SysComplex& operator -= (const SysComplex& arg) {
    real_d -= arg.real_d;
    imag_d -= arg.imag_d;
    return *this;
  }

  // method: operator *=
  //
  const SysComplex& operator *= (const SysComplex& arg) {
    *this = *this * arg;
    return *this;
  }

  // method: operator /=
  //
  const SysComplex& operator /=(const SysComplex& arg) {
    *this = (SysComplex<float64>)*this / (SysComplex<float64>)arg;
    return *this;
  }

  // method: operator +=
  //
  SysComplex& operator += (TSCIntegral arg) {
    real_d += arg;
    return *this;
  }

  // method: operator -=
  //
  SysComplex& operator -= (TSCIntegral arg) {
    real_d -= arg;
    return *this;
  }

  // method: operator *=
  //
  SysComplex& operator *= (TSCIntegral arg) {
    real_d *= arg;
    imag_d *= arg;
    return *this;
  }

  // method: operator /=
  //
  SysComplex& operator /= (TSCIntegral arg) {
    real_d /= arg;
    imag_d /= arg;
    return *this;
  }
  
  // method: operator ++ (post-increment)
  //
  SysComplex<TSCIntegral>& operator ++ () {
    real_d++;
    return *this;
  }

  // method: operator -- (post-decrement)
  //
  SysComplex<TSCIntegral>& operator -- () {
    real_d--;
    return *this;
  }

  // method: operator ++ (pre-increment)
  //
  SysComplex<TSCIntegral> operator ++ (int) {
    SysComplex<TSCIntegral> ret(*this);
    real_d++;
    return ret;
  }

  // method: operator -- (pre-decrement)
  //
  SysComplex<TSCIntegral> operator -- (int) {
    SysComplex<TSCIntegral> ret(*this);
    real_d--;
    return ret;
  }

  //---------------------------------------------------------------------------
  //
  // class-specific public methods:
  //  relational functions with SysComplex and TSCIntegral types
  //
  //---------------------------------------------------------------------------
  
  // method: operator == (equality)
  //
  bool8 operator == (const SysComplex& arg) const {
    return (real_d == arg.real_d) && (imag_d == arg.imag_d);
  }

  // method: operator !=
  //
  bool8 operator != (const SysComplex& arg) const {
    return (real_d != arg.real_d) || (imag_d != arg.imag_d);
  }

  // method: operator <
  //
  inline bool8 operator < (const SysComplex<TSCIntegral>& arg) const {
    return sumSquare() < arg.sumSquare();
  }

  // method: operator >
  //
  inline bool8 operator > (const SysComplex<TSCIntegral>& arg) const {
    return sumSquare() > arg.sumSquare();
  }

  // method: operator <=
  //
  inline bool8 operator <= (const SysComplex<TSCIntegral>& arg) const {
    return sumSquare() <= arg.sumSquare();
  }

  // method: operator >=
  //
  inline bool8 operator >= (const SysComplex<TSCIntegral>& arg) const {
    return sumSquare() >= arg.sumSquare();
  }

  // method: operator ==
  //
  bool8 operator == (TSCIntegral arg) const {
    return (real_d == arg) && (imag_d == 0);
  }

  // method: operator !=
  //
  bool8 operator !=(TSCIntegral arg) const {
    return !((*this) == arg);
  }

  // method: operator <
  //
  inline bool8 operator < (TSCIntegral arg) const {
    return real_d < arg;
  }

  // method: operator >
  //
  inline bool8 operator > (TSCIntegral arg) const {
    return real_d > arg;
  }

  // method: operator <=
  //
  inline bool8 operator <= (TSCIntegral arg) const {
    return real_d <= arg;
  }

  // method: operator >=
  //
  inline bool8 operator >= (TSCIntegral arg) const {
    return real_d >= arg;
  }

  //---------------------------------------------------------------------------
  //
  // class-specific public methods:
  //  arithmetic functions with two complex arguments
  //
  //---------------------------------------------------------------------------
  
  // method: operator +
  //
  inline SysComplex<TSCIntegral> operator + (const SysComplex<TSCIntegral>& arg) const {
    return SysComplex<TSCIntegral>(real_d + arg.real_d, imag_d + arg.imag_d);
  }

  // method: operator -
  //
  inline SysComplex<TSCIntegral> operator - (const SysComplex<TSCIntegral>& arg) const {
    return SysComplex<TSCIntegral>(real_d - arg.real_d, imag_d - arg.imag_d);
  }

  // method: operator *
  //
  inline SysComplex<TSCIntegral> operator * (const SysComplex<TSCIntegral>& arg) const {
    return SysComplex<TSCIntegral>(real_d * arg.real_d - imag_d * arg.imag_d,
				 real_d * arg.imag_d + imag_d * arg.real_d);
  }

  // method: operator /
  //
  inline SysComplex<TSCIntegral> operator / (const SysComplex<TSCIntegral>& arg) const {

    // declare local variables instead a calling a function
    //
    float64 real_tmp = arg.real_d;
    float64 imag_tmp= arg.imag_d;
    
    float64 denom = real_tmp * real_tmp + imag_tmp * imag_tmp;
    return SysComplex<TSCIntegral>((TSCIntegral)((real_d*real_tmp + imag_d*imag_tmp) / denom),
				 (TSCIntegral)((-real_d*imag_tmp + imag_d*real_tmp) / denom));
  }

  //---------------------------------------------------------------------------
  //
  // class-specific public methods:
  //  arithmetic functions with one complex and one real arg. since the
  //  complex arg is to the left this can be a member function.
  //
  //---------------------------------------------------------------------------

  // method: operator +
  //
  inline SysComplex<TSCIntegral> operator + (const TSCIntegral arg) const {
    return SysComplex<TSCIntegral>(real_d + arg, imag_d);
  }

  // method: operator -
  //
  inline SysComplex<TSCIntegral> operator - (const TSCIntegral arg) const {
    return SysComplex<TSCIntegral>(real_d - arg, imag_d);
  }

  // method: operator *
  //
  inline SysComplex<TSCIntegral> operator * (const TSCIntegral arg) const {
    return SysComplex<TSCIntegral>(real_d * arg, imag_d * arg);
  }

  // method: operator /
  //
  inline SysComplex<TSCIntegral> operator / (const TSCIntegral arg) const {
    return SysComplex<TSCIntegral>(real_d / arg, imag_d / arg);
  }

  // method: inverse
  //
  inline SysComplex<TSCIntegral> inverse() const {
    float64 denom = real_d * real_d + imag_d * imag_d;
    return SysComplex<TSCIntegral>(TSCIntegral(real_d / denom),
				 TSCIntegral(-imag_d / denom));
  }
  
  //---------------------------------------------------------------------------
  //
  // class-specific public methods:
  //  miscellaneous complex methods
  //
  //---------------------------------------------------------------------------

  // method: conjugate
  //
  SysComplex<TSCIntegral> conjugate() const {
    return SysComplex<TSCIntegral>(real_d, -imag_d);
  }

  // method: polar
  //
  static SysComplex<TSCIntegral> polar(float64 mag, float64 angle) {
    return SysComplex<TSCIntegral>(TSCIntegral(mag * ::cos(angle)),
				TSCIntegral( mag * ::sin(angle)));
  }


    //---------------------------------------------------------------------------
  //
  // private methods
  //
  //---------------------------------------------------------------------------
private:


  // method: sumSquare
  //
  TSCIntegral sumSquare() const {
    return (real_d * real_d + imag_d * imag_d);
  }

};

//---------------------------------------------------------------------------
//
// class-specific *public methods*:
//  arithmetic functions with one complex and one real arg. since the
//  complex arg is to the right these cannot be member functions.
//
//---------------------------------------------------------------------------


// method: operator +
//
template <class TSCIntegral> inline SysComplex<TSCIntegral>
operator + (TSCIntegral x, const SysComplex<TSCIntegral>& y)
{
  return SysComplex<TSCIntegral> (x + y.real(), y.imag());
}

// method: operator -
//
template <class TSCIntegral> inline SysComplex<TSCIntegral>
operator - (TSCIntegral x, const SysComplex<TSCIntegral>& y)
{
  return SysComplex<TSCIntegral> (x - y.real(), - y.imag());
}

// method: operator * 
 //
template <class TSCIntegral> inline SysComplex<TSCIntegral>
operator * (TSCIntegral x, const SysComplex<TSCIntegral>& y)
{
  return SysComplex<TSCIntegral> (x * y.real(), x * y.imag());
}

// method: operator /
//
template <class TSCIntegral> inline SysComplex<TSCIntegral>
operator / (TSCIntegral x, const SysComplex<TSCIntegral>& y)
{
  return (SysComplex<TSCIntegral>)x / y ;
}

// method: operator - (negation)
//
// this cannot be a member function
//
template <class TSCIntegral> inline SysComplex<TSCIntegral>
operator - (const SysComplex<TSCIntegral>& x)
{
  return SysComplex<TSCIntegral> (- x.real(), - x.imag());
}

//---------------------------------------------------------------------------
//
// class-specific *public methods*:
//  relational functions with TSCIntegral and complex types. since the
//  complex arg is to the right these cannot be member functions.
//
//---------------------------------------------------------------------------

// method: operator >
//
template <class TSCIntegral> inline bool8
operator > (TSCIntegral x, const SysComplex<TSCIntegral>& y)
{
  return x > y.real();
}

// method: operator <
//
template <class TSCIntegral> inline bool8
operator < (TSCIntegral x, const SysComplex<TSCIntegral>& y)
{
  return x < y.real();
}

// method: operator >=
//
template <class TSCIntegral> inline bool8
operator >= (TSCIntegral x, const SysComplex<TSCIntegral>& y)
{
  return x >= y.real();
}

// method: operator <=
//
template <class TSCIntegral> inline bool8
operator <= (TSCIntegral x, const SysComplex<TSCIntegral>& y)
{
  return x <= y.real();
}
 
#endif
