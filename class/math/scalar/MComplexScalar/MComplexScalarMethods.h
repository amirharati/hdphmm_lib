// file: $isip/class/math/scalar/MComplexScalar/MComplexScalarMethods.h
// version: $Id: MComplexScalarMethods.h 10636 2007-01-26 22:18:09Z tm334 $
//

// make sure definitions are only made once
//
#ifndef ISIP_MCOMPLEX_SCALAR_METHODS
#define ISIP_MCOMPLEX_SCALAR_METHODS

// isip include files
//
#ifndef ISIP_INTEGRAL
#include <Integral.h>
#endif

// forward class definitions
//
template<class TIntegral, class TSize> class MComplexScalar;
class String;
class Random;
class Sof;

// MComplexScalarMethods: provide implementations of more complex methods
// found in the MComplexScalar template class.
//
class MComplexScalarMethods {

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
  //  note that name() is not inlined to avoid a circular include file problem.
  //
  static const String& name();

  template <class TCScalar, class TIntegral>
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
  static bool8 read(MComplexScalar<TIntegral, TSize>& obj, Sof& sof,
		      int32 tag, const String& name);
  
  template <class TIntegral, class TSize>
  static bool8 write(const MComplexScalar<TIntegral, TSize>&,
		       Sof& sof, int32 tag, const String& name);
  
  template <class TIntegral, class TSize>
  static bool8 readData(MComplexScalar<TIntegral, TSize>&, Sof& sof,
			  const String& pname,
			  int32 size, bool8 param_a , bool8 nested_a);
  
  template <class TIntegral, class TSize>
  static bool8 writeData(const MComplexScalar<TIntegral, TSize>&, Sof& sof,
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

  //---------------------------------------------------------------------------
  //
  // private methods
  //
  //---------------------------------------------------------------------------
public:

  // destructor/constructor(s):
  //  the destructors and constructors are declared private so that a
  //  compilation error will be generated if the user tries to construct an
  //  object of this type
  //
  ~MComplexScalarMethods();
  MComplexScalarMethods();
  MComplexScalarMethods(const MComplexScalarMethods& arg);

  // additional diagnose methods: because of the complexity of diagnose,
  // we break it into smaller functions.
  //
  template <class TCScalar, class TIntegral>
  static bool8 diagnose0(Integral::DEBUG debug_level);

  template <class TCScalar, class TIntegral>
  static bool8 diagnose1(Integral::DEBUG debug_level);

  template <class TCScalar, class TIntegral>
  static bool8 diagnose2(Integral::DEBUG debug_level);
};

// end of include file
//
#endif
