// file: $isip/class/math/vector/MVector/MVectorMethods.h
// version: $Id: MVectorMethods.h 7799 2002-02-22 22:31:35Z wang $
//

// make sure definitions are only made once
//
#ifndef ISIP_MVECTOR_METHODS
#define ISIP_MVECTOR_METHODS

// isip include files
//
#include <MScalar.h>
#include <Long.h>

// forward class definitions
//
template<class TScalar, class TIntegral> class MVector;

// MVectorMethods: a friend class to MVector. Its purpose is mainly to
// provide a mechanism to get source code out of the header file and into
// implementation files.
//
class MVectorMethods {
  
  //---------------------------------------------------------------------------
  //
  // required public methods
  //
  //---------------------------------------------------------------------------
public:
  
  // static methods
  //
  template <class TVector, class TScalar, class TIntegral>
  static bool8 diagnose(Integral::DEBUG level);

  // i/o methods
  //
  template <class TScalar, class TIntegral>
  static int32 sofSize(const MVector<TScalar,TIntegral>& obj);
  
  template <class TScalar, class TIntegral>
  static bool8 read(MVector<TScalar,TIntegral>& obj, Sof& sof,
		      int32 tag, const String& name);
  
  template <class TScalar, class TIntegral>
  static bool8 write(const MVector<TScalar,TIntegral>& obj,
		       Sof& sof, int32 tag, const String& name);
  
  template <class TScalar, class TIntegral>
  static bool8 readData(MVector<TScalar,TIntegral>& obj, Sof& sof,
			  const String& pname, int32 size, bool8 param,
			  bool8 nested);
  
  template <class TScalar, class TIntegral>
  static bool8 writeData(const MVector<TScalar,TIntegral>& obj,
			   Sof& sof, const String& name);
  
  //-------------------------------------------------------------------------
  //
  // class-specific public methods
  //
  //-------------------------------------------------------------------------
  
  // array conversion methods
  //
  template <class TScalar, class TIntegral, class TAIntegral>
  static bool8 assign(MVector<TScalar,TIntegral>& obj, int32 num_elem,
			const TAIntegral* arg);
  
  template <class TScalar, class TIntegral>
  static bool8 assign(MVector<TScalar,TIntegral>& obj, int32 num_elem,
			const String* arg);
  
  // conversion from string using parsing
  //
  template <class TScalar, class TIntegral>
  static bool8 assign(MVector<TScalar,TIntegral>& obj, const String& arg,
			unichar delim);
  
  template <class TScalar, class TIntegral>
  static bool8 assign(MVector<TScalar,TIntegral>& obj, const unichar* arg,
			unichar delim);
  
  // conversion to string
  //
  template <class TScalar, class TIntegral>
  static bool8 get(const MVector<TScalar,TIntegral>& obj, String& output,
		     const String& delim);

  // swap the current vector with the input vector
  //
  template <class TScalar, class TIntegral>
  static bool8 swap(MVector<TScalar,TIntegral>& obj,
		      MVector<TScalar,TIntegral>& arg);
  
  // partial i/o methods
  //
  template <class TScalar, class TIntegral>
  static bool8 readStart(MVector<TScalar,TIntegral>& obj, Sof& sof,
			   const String& pname, int32 size,
			   bool8 param, bool8 nested);

  template <class TScalar, class TIntegral>
  static int32 readPartialData(MVector<TScalar,TIntegral>& obj, Sof& sof,
			      int32 start_pos, int32 num_elem,
			      const String& pname, int32 size,
			      bool8 param, bool8 nested);
  
  template <class TScalar, class TIntegral>
  static bool8 writeStart(const MVector<TScalar,TIntegral>& obj, Sof& sof,
			    const String& pname);

  template <class TScalar, class TIntegral>
  static int32 writePartialData(const MVector<TScalar,TIntegral>& obj,
			       Sof& sof, int32 start_pos, int32 num_elem);

  template <class TScalar, class TIntegral>
  static bool8 writeTerminate(const MVector<TScalar,TIntegral>& obj,
				Sof& sof, const String& pname);
  
  // memory size methods
  //
  template <class TScalar, class TIntegral>
  static int32 memSize(const MVector<TScalar,TIntegral>& obj);

  // comparison methods
  //
  template <class TScalar, class TIntegral>
  static bool8 eq(const MVector<TScalar,TIntegral>& obj, TIntegral value);
  
  template <class TScalar, class TIntegral>
  static bool8 ne(const MVector<TScalar,TIntegral>& obj,
		    const MVector<TScalar,TIntegral>& vector);
  
  template <class TScalar, class TIntegral>
  static bool8 ne(const MVector<TScalar,TIntegral>& obj, TIntegral value);
  
  template <class TScalar, class TIntegral>
  static bool8 gt(const MVector<TScalar,TIntegral>& obj,
		    const MVector<TScalar,TIntegral>& vector);
  
  template <class TScalar, class TIntegral>
  static bool8 gt(const MVector<TScalar,TIntegral>& obj, TIntegral value);
  
  template <class TScalar, class TIntegral>
  static bool8 lt(const MVector<TScalar,TIntegral>& obj,
		    const MVector<TScalar,TIntegral>& vector);
  
  template <class TScalar, class TIntegral>
  static bool8 lt(const MVector<TScalar,TIntegral>& obj, TIntegral value);
  
  template <class TScalar, class TIntegral>
  static bool8 ge(const MVector<TScalar,TIntegral>& obj,
		    const MVector<TScalar,TIntegral>& vector);
  
  template <class TScalar, class TIntegral>
  static bool8 ge(const MVector<TScalar,TIntegral>& obj, TIntegral value);
    
  template <class TScalar, class TIntegral>
  static bool8 le(const MVector<TScalar,TIntegral>& obj,
		    const MVector<TScalar,TIntegral>& vector);
  
  template <class TScalar, class TIntegral>
  static bool8 le(const MVector<TScalar,TIntegral>& obj, TIntegral value);
  
  // common mathematical functions
  //
  template <class TScalar, class TIntegral>
  static bool8 pow(MVector<TScalar,TIntegral>& obj,
		     const MVector<TScalar,TIntegral>& x, float64 y);
  
  template <class TScalar, class TIntegral>
  static bool8 sort(MVector<TScalar,TIntegral>& obj,
		      const MVector<TScalar,TIntegral>& vector,
		      Integral::ORDER order = Integral::DEF_ORDER);

  template <class TScalar, class TIntegral>
  static bool8 index(MVector<TScalar,TIntegral>& obj, 
		       Integral::ORDER order,
                       MVector<Long,int32>& sort_index);


  template <class TScalar, class TIntegral>
  static bool8 randperm(MVector<TScalar,TIntegral>& obj, int32 size);

  // mathematical limits, ceiling, floor and rounding functions
  //  
  template <class TScalar, class TIntegral>
  static TIntegral max(const MVector<TScalar,TIntegral>& obj, int32& position);
    
  template <class TScalar, class TIntegral>
  static TIntegral min(const MVector<TScalar,TIntegral>& obj, int32& position);
    
  template <class TScalar, class TIntegral>
  static float64 minMag(const MVector<TScalar,TIntegral>& obj,
			  int32& position);
    
  template <class TScalar, class TIntegral>
  static float64 maxMag(const MVector<TScalar,TIntegral>& obj,
			  int32& position);
    
  // function generation methods
  //
  template <class TScalar, class TIntegral>
  static bool8 ramp(MVector<TScalar,TIntegral>& obj,
		      TIntegral offset, TIntegral incr);
  
  template <class TScalar, class TIntegral>
  static bool8 ramp(MVector<TScalar,TIntegral>& obj,
		      TIntegral offset, TIntegral incr, TIntegral end);
  
  // vector to scalar mathematical methods
  //
  template <class TScalar, class TIntegral>
  static TIntegral sum(const MVector<TScalar,TIntegral>& obj);
  
  template <class TScalar, class TIntegral>
  static TIntegral sumSquare(const MVector<TScalar,TIntegral>& obj);
  
  template <class TScalar, class TIntegral>
  static TIntegral mean(const MVector<TScalar,TIntegral>& obj);

  template <class TScalar, class TIntegral>
  static TIntegral median(const MVector<TScalar,TIntegral>& obj);
  
  template <class TScalar, class TIntegral>
  static TIntegral rms(const MVector<TScalar,TIntegral>& obj);
  
  template <class TScalar, class TIntegral>
  static TIntegral var(const MVector<TScalar,TIntegral>& obj);
  
  template <class TScalar, class TIntegral>
  static TIntegral stdev(const MVector<TScalar,TIntegral>& obj);
  
  template <class TScalar, class TIntegral>
  static TIntegral dotProduct(const MVector<TScalar,TIntegral>& obj,
			      const MVector<TScalar,TIntegral>& vector);
  
  template <class TScalar, class TIntegral>
  static TIntegral distanceSquare(const MVector<TScalar,TIntegral>& obj,
				  const MVector<TScalar,TIntegral>& vector);
  
  template <class TScalar, class TIntegral>
  static int32 numEqual(const MVector<TScalar,TIntegral>& obj,
		       TIntegral test_value);
  
  template <class TScalar, class TIntegral>
  static int32 numNotEqual(const MVector<TScalar,TIntegral>& obj,
			  TIntegral test_value);
  
  // dsp methods
  // 
  template <class TScalar, class TIntegral>
  static bool8 limit(MVector<TScalar,TIntegral>& obj,
		       TIntegral min_val, TIntegral max_val,
		       const MVector<TScalar,TIntegral>& vector);
  
  template <class TScalar, class TIntegral>
  static bool8 limitMin(MVector<TScalar,TIntegral>& obj,
			  TIntegral min_val,
			  const MVector<TScalar,TIntegral>& vector);
    
  template <class TScalar, class TIntegral>
  static bool8 limitMax(MVector<TScalar,TIntegral>& obj,
			  TIntegral max_val,
			  const MVector<TScalar,TIntegral>& vector);
    
  template <class TScalar, class TIntegral>
  static bool8 limitMag(MVector<TScalar,TIntegral>& obj,
			  TIntegral cmp_val, TIntegral new_val,
			  const MVector<TScalar,TIntegral>& vector);
  
  template <class TScalar, class TIntegral>
  static bool8 centerClip(MVector<TScalar,TIntegral>& obj,
			    TIntegral min_val, TIntegral max_val,
			    const MVector<TScalar,TIntegral>& vector);
  
  // random number generation methods
  //
  template <class TScalar, class TIntegral>
  static bool8 rand(MVector<TScalar,TIntegral>& obj,
		      Random& generator);
  
  template <class TScalar, class TIntegral>
  static bool8 rand(MVector<TScalar,TIntegral>& obj,
		      TIntegral min_val, TIntegral max_val,
		      Random& generator);
  
  template <class TScalar, class TIntegral>
  static bool8 grand(MVector<TScalar,TIntegral>& obj,
		       TIntegral mean, TIntegral stdev, Random& generator);
  
  // position operation methods
  //
  template <class TScalar, class TIntegral>
  static bool8 move(MVector<TScalar,TIntegral>& obj,
		      const MVector<TScalar,TIntegral>& source_vector,
		      int32 num_elements, int32 source_offset, int32 dest_offset);
  
  template <class TScalar, class TIntegral>
  static bool8 shift(MVector<TScalar,TIntegral>& obj, int32 delta);
  
  template <class TScalar, class TIntegral>
  static bool8 shift(MVector<TScalar,TIntegral>& obj,
		       const MVector<TScalar,TIntegral>& source_vector,
		       int32 delta);  
  
  template <class TScalar, class TIntegral>
  static bool8 concat(MVector<TScalar,TIntegral>& obj,
			const MVector<TScalar,TIntegral>& v2);
  
  template <class TScalar, class TIntegral>
  static bool8 concat(MVector<TScalar,TIntegral>& obj,
			const MVector<TScalar,TIntegral>& v1,
			const MVector<TScalar,TIntegral>& v2);
  
  template <class TScalar, class TIntegral>
  static bool8 deleteRange(MVector<TScalar,TIntegral>& obj,
			     const MVector<TScalar,TIntegral>& source_vector,
			     int32 offset, int32 num_elements);
  
  template <class TScalar, class TIntegral>
  static bool8 setRange(MVector<TScalar,TIntegral>& obj,
			  int32 offset, int32 num_elements, TIntegral value);

  // element location and ordering methods
  //
  template <class TScalar, class TIntegral>
  static int32 first(MVector<TScalar,TIntegral>& obj,
		    TIntegral value, int32 start_pos);
  
  template <class TScalar, class TIntegral>
  static int32 last(MVector<TScalar,TIntegral>& obj,
		   TIntegral value, int32 end_pos);
  
  template <class TScalar, class TIntegral>
  static bool8 reorder(MVector<TScalar,TIntegral>& obj,
			 const MVector<Long,int32>& indexes);
  
  template <class TScalar, class TIntegral>
  static bool8 reorder(MVector<TScalar,TIntegral>& obj,
			 const MVector<TScalar,TIntegral>& arg,
			 const MVector<Long,int32>& indexes);

  template <class TScalar, class TIntegral>
  static bool8 reverse(MVector<TScalar,TIntegral>& obj);
  
  //---------------------------------------------------------------------------
  //
  // private methods
  //
  //---------------------------------------------------------------------------
private:
  
  // destructor/constructor(s):
  // the constructors and destructors are declared private so that a
  // compilation error will be generated if the user tries to construct an
  // object of this type
  //
  ~MVectorMethods();
  MVectorMethods();
  MVectorMethods(const MVectorMethods& arg);

  // additional diagnose methods: because of the complexity of diagnose,
  // we break it into smaller functions.
  //

  template <class TVector, class TScalar, class TIntegral>
  static bool8 diagnose1(Integral::DEBUG level);  

  template <class TVector, class TScalar, class TIntegral>
  static bool8 diagnose2(Integral::DEBUG level);

  template <class TVector, class TScalar, class TIntegral>
  static bool8 diagnose3(Integral::DEBUG level);

  template <class TVector, class TScalar, class TIntegral>
  static bool8 diagnose4(Integral::DEBUG level);

  template <class TVector, class TScalar, class TIntegral>
  static bool8 diagnose5(Integral::DEBUG level);
  
  template <class TVector, class TScalar, class TIntegral>
  static bool8 diagnose6(Integral::DEBUG level);
  
  template <class TVector, class TScalar, class TIntegral>
  static bool8 diagnose7(Integral::DEBUG level);
  
  template <class TVector, class TScalar, class TIntegral>
  static bool8 diagnose8(Integral::DEBUG level);

  template <class TVector, class TScalar, class TIntegral>
  static bool8 diagnose9(Integral::DEBUG level);  
  
  // dummy name methods
  //
  static const String& name();
};

// end of include file
//
#endif
