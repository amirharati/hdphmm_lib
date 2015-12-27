// file: $isip/class/math/scalar/MScalar/MScalarMethods.h
// version: $Id: MScalarMethods.h 7365 2001-09-10 15:19:14Z bahety $
//

// make sure definitions are only made once
//
#ifndef ISIP_MSCALAR_METHODS
#define ISIP_MSCALAR_METHODS

// isip include files
//
#ifndef ISIP_INTEGRAL
#include <Integral.h>
#endif

// forward class definitions
//
template<class TIntegral, class TSize> class MScalar;
class String;
class Random;
class Sof;

// MScalarMethods: provide implementations of more complicated methods
// found in the MScalar template class.
//
class MScalarMethods {

  //---------------------------------------------------------------------------
  //
  // public constants
  //
  //---------------------------------------------------------------------------
public:

  // define the class name
  //

  //----------------------------------------
  //
  // other important constants
  //
  //----------------------------------------
  
  //----------------------------------------
  //
  // default values and arguments
  //
  //----------------------------------------  

  // define the default value(s) of the class data
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

  // static methods:
  //  note that name is not inlined to avoid a circular include file problem.
  //
  static const String& name();
  
  template <class TScalar, class TIntegral>
  static bool8 diagnose(Integral::DEBUG debug_level);

  // debug methods:
  //  these methods are not required for this class.
  //

  // destructor/constructor(s):
  //  these methods are private in this class.
  //

  // assign methods:
  //  these methods are not required for this class.
  //

  // i/o methods
  //
  template <class TIntegral, class TSize>
  static bool8 read(MScalar<TIntegral, TSize>& obj, Sof& sof,
		      int32 tag, const String& name);
  
  template <class TIntegral, class TSize>
  static bool8 write(const MScalar<TIntegral, TSize>&,
		       Sof& sof, int32 tag, const String& name);
  
  template <class TIntegral, class TSize>
  static bool8 readData(MScalar<TIntegral, TSize>&, Sof& sof,
			  const String& pname,
			  int32 size, bool8 param_a , bool8 nested_a);
  
  template <class TIntegral, class TSize>
  static bool8 writeData(const MScalar<TIntegral, TSize>&, Sof& sof,
			   const String& pname);
  
  // equality methods:
  //  these methods are not required for this class.
  //

  //---------------------------------------------------------------------------
  //
  // class-specific public methods
  //
  //---------------------------------------------------------------------------

  // digital signal processing methods
  //
  template <class TIntegral, class TSize>
  static TIntegral centerClip(MScalar<TIntegral, TSize>&, TIntegral min,
			      TIntegral max, TIntegral val);
  
  template <class TIntegral, class TSize>
  static TIntegral limit(MScalar<TIntegral, TSize>&, TIntegral min,
			 TIntegral max, TIntegral val);
  
  template <class TIntegral, class TSize>
  static TIntegral limitMag(MScalar<TIntegral, TSize>&, TIntegral thresh,
			    TIntegral output, TIntegral val);
  
  //---------------------------------------------------------------------------
  //
  // private methods
  //
  //---------------------------------------------------------------------------
private:

  // destructor/constructor(s):
  //  the constructors and destructors are declared private so that a
  //  compilation error will be generated if the user tries to construct an
  //  object of this type
  //
  ~MScalarMethods();
  MScalarMethods();
  MScalarMethods(const MScalarMethods& arg);

  // additional diagnose methods: because of the complexity of diagnose,
  // we break it into smaller functions.
  //
  template <class TScalar, class TIntegral>
  static bool8 diagnose0(Integral::DEBUG level);

  template <class TScalar, class TIntegral>
  static bool8 diagnose1(Integral::DEBUG level);

  template <class TScalar, class TIntegral>
  static bool8 diagnose2(Integral::DEBUG level);

};

// end of include file
//
#endif
