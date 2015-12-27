// file: $isip/class/math/scalar/MComplexScalar/MComplexScalar.h
// version: $Id: MComplexScalar.h 10636 2007-01-26 22:18:09Z tm334 $
//

// make sure definitions are only made once
//
#ifndef ISIP_MCOMPLEX_SCALAR
#define ISIP_MCOMPLEX_SCALAR

// isip include files
//
#ifndef ISIP_MSCALAR
#include <MScalar.h>
#endif

#ifndef ISIP_MCOMPLEX_SCALAR_METHODS
#include "MComplexScalarMethods.h"
#endif

// MComplexScalar: a class which is the base class for all complex scalar
// classes. it includes commonly used mathematical, logical, DSP, i/o and
// operator overload methods. MComplexScalar methods should not be used by
// users directly. they are intended to be used by other scalar, vector,
// and matrix complex classes.
//
template<class TIntegral, class TSize>
class MComplexScalar : public MScalar<SysComplex<TIntegral>, TSize> {

  //---------------------------------------------------------------------------
  // local typedefs:
  //  these are useful in reducing the amount of text one has to type,
  //  and make the code much more readable. we follow a model here that is
  //  similar to vectors and matrices.
  //---------------------------------------------------------------------------
protected:  
  typedef SysComplex<TIntegral> TCScalar;

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
  static const MComplexScalar<TIntegral, TSize> DEF_VALUE;

  //----------------------------------------
  //
  // error codes
  //
  //----------------------------------------  
  
  static const int32 ERR = 21600;

  //---------------------------------------------------------------------------
  //
  // protected data
  //
  //---------------------------------------------------------------------------
protected:

  // declare a static debug level for all class instantiations:
  //  we don't want every object to waste space on a debug level. let
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
    return MComplexScalarMethods::
      diagnose<MComplexScalar<TIntegral, TSize>, TIntegral>(debug_level);
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
  ~MComplexScalar() {}

  // method: default constructor
  //
  MComplexScalar() {}

  // method: copy constructor
  //
  MComplexScalar(const MComplexScalar& arg) {
    this->value_d = arg.value_d;
  }		

  // method: assign
  //
  bool8 assign(const TCScalar& arg) {
    this->value_d = arg;
    return true;
  }

  // method operator=
  //  we need to have the overloaded operator '=' defined in the
  //  derived classes instead of the base template class. this is
  //  required since c++ predefines the operator '=' for any class by
  //  default and this will hide any other definition of this operator
  //  in the base class.
  //

  // method: sofSize
  //
  int32 sofSize() const {
    return (int32)(sizeof(TSize) * 2);
  }
  
  // method: read
  //
  bool8 read(Sof& sof, int32 tag, const String& name = CLASS_NAME) {
    return MComplexScalarMethods::read(*this, sof, tag, name);
  }
  
  // method: write
  //
  bool8 write(Sof& sof, int32 tag, const String& name = CLASS_NAME) const {
    return MComplexScalarMethods::write(*this, sof, tag, name);
  }

  // method: readData
  //
  bool8 readData(Sof& sof, const String& pname = DEF_PARAM,
			  int32 size = SofParser::FULL_OBJECT,
			  bool8 param = true, bool8 nested = false) {
    return MComplexScalarMethods::
      readData(*this, sof, pname, size, param, nested);
  }

  // method: writeData
  //
  bool8 writeData(Sof& sof, const String& pname = DEF_PARAM) const {
    return MComplexScalarMethods::writeData(*this, sof, pname);
  }

  // eq method is inherited from the MScalar class
  //

  // method: clear
  //
  bool8 clear(Integral::CMODE ctype = Integral::DEF_CMODE) {
    this->value_d = (TCScalar)DEF_VALUE;
    return true;
  }

  //---------------------------------------------------------------------------
  //
  // class-specific public methods:
  //  extensions to required methods
  //
  //---------------------------------------------------------------------------

  // method: constructor
  //
  MComplexScalar(SysComplex<TIntegral> arg) {
    assign(arg);
  }

  // method: constructor
  //  note that this method is useful to have for the diagnose method.
  //  it is masked by higher-level classes that use this as a template
  //  and have their own version of this constructor.
  MComplexScalar(TIntegral arg) {
    assign(arg);
  }

  // method: assign
  //
  template<class TAIntegral>
  bool8 assign(TAIntegral arg) {
    this->value_d = (TCScalar)arg;
    return true;
  }

  // method: assign
  //
  template<class TAIntegral>
  bool8 assign(TAIntegral real, TAIntegral imag) {
    return this->value_d.assign((TIntegral)real, (TIntegral)imag);
  }

  // method: assign
  //
  bool8 assign(const String& arg) {
    arg.get(this->value_d);
    return true;
  }

  //---------------------------------------------------------------------------
  //
  // class-specific public methods:
  //  these methods are either unique to this class or overloaded
  //  to provide alternate implementations. (listed in alphabetical order)
  //
  //---------------------------------------------------------------------------

  // method: angle
  //
  float64 angle() const {
    return this->value_d.angle();
  }

  // method: conjugate
  //
  TCScalar conjugate() const {
    return this->value_d.conjugate();
  }

  // gaussian random number generation methods
  //
  TCScalar grand(TCScalar mean, TCScalar stddev,
		  Random& generator = Random::GLOBAL_GAUSSIAN);

  // method: hash
  //
  uint32 hash(uint32 hsize) const {
    // Integral::hash() gives wrong result for the first time invoked with -O2 open
    //
    Integral::hash(mag(),  hsize);
    return Integral::hash(mag(),  hsize);
  }  
  
  // method: imag
  //
  TIntegral imag() const {
    return this->value_d.imag();
  }
  
  // method: abs
  //
  float64 abs() const {
    return this->value_d.abs();
  }
  
  // method: mag
  //
  float64 mag() const {
    return this->value_d.mag();
  }

  // random number generation methods
  //
  SysComplex<TIntegral> rand(Random& generator = Random::GLOBAL_UNIFORM);
  SysComplex<TIntegral> rand(TCScalar min, TCScalar max,
			     Random& generator = Random::GLOBAL_UNIFORM);
  
  // methods to extract components of the complex number
  //

  // method: real
  //
  TIntegral real() const {
    return this->value_d.real();
  }

  // method: sign
  //  the sign method is overloaded here because we use the real
  //  component of the complex number to get the sign
  //
  TCScalar sign(TCScalar arg) {
    if (arg.real() < (TSize)0.0) {
      return (this->value_d = (TCScalar)Integral::NEGATIVE);
    }
    return (this->value_d = (TCScalar)Integral::POSITIVE);    
  }
  
  //---------------------------------------------------------------------------
  //
  // class-specific public methods:
  //  other mathematical methods (listed alphabetically)
  //
  //--------------------------------------------------------------------------

  // method: centerClip
  //
  TCScalar centerClip(TIntegral min, TIntegral max) {
    return centerClip(min, max, this->value_d);
  }
    
  // method: centerClip
  //
  TCScalar centerClip(TIntegral min, TIntegral max, TCScalar arg) {
    if ((min > max) || (min < 0))
      return Error::handle(name(), L"centerClip", Error::ARG,
			   __FILE__, __LINE__);

    float64 magnitude = arg.mag();

    if ((magnitude >= max) || (magnitude <= min))
      this->value_d = arg;
    else if (magnitude < ((min + max) / 2)) {
      this->value_d = SysComplex<TIntegral>
	((TIntegral)(arg.real() * min / magnitude),
	 (TIntegral)(arg.imag() * min / magnitude));
    }
    else {
     this->value_d = SysComplex<TIntegral>
       ((TIntegral)(arg.real() * max / magnitude),
	(TIntegral)(arg.imag() * max / magnitude));
    }
    return this->value_d;
  }

  // method: fraction
  //
  TCScalar fraction() {
    return fraction(this->value_d);
  }

  // method: fraction
  //
  TCScalar fraction(TCScalar arg) {
    return (this->value_d = SysComplex<TIntegral>
      ((TIntegral)Integral::fraction(arg.real()),
       (TIntegral)Integral::fraction(arg.imag())));
  }

  // method: limitMag
  //
  TCScalar limitMag(TIntegral thresh, TIntegral output) {
    return limitMag(thresh, output, this->value_d);
  }

  // method: limitMag
  //
  TCScalar limitMag(TIntegral thresh, TIntegral output, TCScalar arg) {
    float64 magnitude = arg.mag();
    if (magnitude > thresh) {
      return (this->value_d = SysComplex<TIntegral>
	      ((TIntegral)(arg.real() * output / magnitude),
	       (TIntegral)(arg.imag() * output / magnitude)));
    }
    return (this->value_d = arg);
  }
  
  //---------------------------------------------------------------------------
  //
  // private methods
  //
  //---------------------------------------------------------------------------
private:

  // since this is a template, we must be careful to block functions
  // that make no sense for complex numbers.  the "using" directive
  // prevents these functions from being available to programmers.
  // if you desire to block these functions for all classes, you can
  // define them here. if you want to block them only for specific classes
  // (e.g., ComplexFloat), you can block them in the respective class.
  //
/*   using MScalar<TCScalar, TSize>::operator %; */
/*   using MScalar<TCScalar, TSize>::operator %=; */
/*   using MScalar<TCScalar, TSize>::band; */
/*   using MScalar<TCScalar, TSize>::bor; */
/*   using MScalar<TCScalar, TSize>::bxor; */
/*   using MScalar<TCScalar, TSize>::brs; */
/*   using MScalar<TCScalar, TSize>::bls; */
/*   using MScalar<TCScalar, TSize>::bcmpl; */

/*   using MScalar<TCScalar, TSize>::mod; */

  using MScalar<TCScalar, TSize>::limit;

  // friend functions:
  // generally friend functions are discouraged but are used in the
  // MComplexScalar class to circumvent the template delayed
  // compilation problem.
  //
  friend class MComplexScalarMethods;
  friend class MScalarMethods;

};

// end of include file
//
#endif
